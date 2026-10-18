#include "system.h"
#include "driver/arcdrv.h"
#include "driver/mapdrv.h"
#include "manager/dvdmgr.h"
#include "memory.h"
#include "mario/mariost.h"
extern void camShiftInit(void);
typedef struct CamRoadCurve {
    char name[0x28];
    s32 off;               // 0x28
    u8 pad[0xb8 - 0x2c];
} CamRoadCurve;
typedef struct CamRoadCam {
    u8 pad0[0x20];
    u32 f_20;              // 0x20
    u8 pad1[0x40 - 0x24];
    s32 f_40;              // 0x40
    s32 f_44;              // 0x44
    u8 pad2[0x7c - 0x48];
    f32 f_7c;              // 0x7c
} CamRoadCam;
typedef struct CamRoadMap {
    u8 pad0[0x44];
    char version[0x84];    // 0x44
    s32 curveNum;          // 0xc8
    u8 pad1[0xe8 - 0xcc];
    Vec* f_e8;             // 0xe8
    CamRoadCurve* curves;  // 0xec
    void* f_f0;
    void* f_f4;
    void* f_f8;
    void* f_fc;
    void* f_100;
    void* f_104;
    void* f_108;
} CamRoadMap;
typedef struct CamRoadState {
    s32 on;                // 0x00
    s32 f_04;              // 0x04
    s32 f_08;              // 0x08
    f32 in[6];             // 0x0c
    CamRoadCam* cam;       // 0x24
    Vec pos;               // 0x28
    Vec dir;               // 0x34
    f32 dist;              // 0x40
    f32 angle;             // 0x44
    f32 rot;               // 0x48
    f32 f_4c;              // 0x4c
    OSTime time;           // 0x50
    f32 f_58;              // 0x58
    f32 shiftXRate;        // 0x5c
} CamRoadState;
typedef struct CamRoadOut {
    Vec f_0;
    Vec pos;               // 0xc
    Vec at;                // 0x18
} CamRoadOut;
typedef struct CamRoadWork {
    CamRoadMap* map;       // 0x0
    u8 pad0[4];
    CamRoadState cur;      // 0x8
    CamRoadState next;     // 0x68
    s32 f_c8;              // 0xc8
    s32 hokanType;         // 0xcc
    f32 hokanT;            // 0xd0
    f32 hokanSpeed;        // 0xd4
    CamRoadState prev;     // 0xd8
    CamRoadState start;    // 0x138
    u32 cmpFlags;          // 0x198
    f32 f_19c[11];         // 0x19c
    OSTime time;           // 0x1c8
    u32 state;             // 0x1d0
    u8 pad5[0x1ec - 0x1d4];
    f32 in[6];             // 0x1ec
    s32 f_204;
    s32 f_208;
    u8 pad6[0x210 - 0x20c];
} CamRoadWork;
typedef struct CamRoadCurveX {
    u8 pad0[0x20];
    u32 f_20;              // 0x20
    f32 f_24;              // 0x24
    u32 off;               // 0x28
    u8 pad1[0x58 - 0x2c];
    f32 f_58;              // 0x58
    u8 pad2[0x64 - 0x5c];
    f32 f_64;              // 0x64
    u8 pad3[0x70 - 0x68];
    f32 f_70;              // 0x70
    u8 pad4[0x7c - 0x74];
    f32 f_7c;              // 0x7c
    u8 pad5[0x8c - 0x80];
    f32 height;            // 0x8c
    u8 pad6[0xa8 - 0x90];
    s32 grpOfs;            // 0xa8
    s32 grpNum;            // 0xac
    s32 f_b0;              // 0xb0
    s32 f_b4;              // 0xb4
} CamRoadCurveX;
typedef struct CamRoadGroup {
    u8 pad0[0x58];
    s32 vtxOfs;            // 0x58
    u8 pad1[4];
    s32 stripOfs;          // 0x60
    s32 stripNum;          // 0x64
} CamRoadGroup;
typedef struct CamRoadStrip {
    s32 idxOfs;
    s32 num;
} CamRoadStrip;
typedef struct CamRoadHit {
    f32 t;                 // 0x00
    f32 f_04;              // 0x04
    f32 y;                 // 0x08
    Vec pos;               // 0x0c
    Vec dir;               // 0x18
    s32 f_24;              // 0x24
    u32 flags;             // 0x28
} CamRoadHit;
extern int strcmp(const char*, const char*);
extern void* memset(void*, int, unsigned long);
extern int sprintf(char*, const char*, ...);
double sin(double);
double cos(double);
double acos(double);
double atan2(double, double);
extern int __float_nan[];
static inline s32 cr_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 cr_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (cr_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#ifdef NONMATCHING
static const Vec unk_vec0 = {0.0f, 1.0f, 0.0f};
static const Vec unk_vec1 = {90.0f, 110.0f, 13.0f};
static const Vec unk_vec2 = {-110.0f, -70.0f, -190.0f};
#endif
static CamRoadWork work;
static CamRoadWork* wp = &work;
void OSReport(const char* msg, ...);
void calcCurrentCamState(CamRoadOut* out);
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* speed);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);
static inline void crCheck(BOOL b) {}

#ifdef NONMATCHING
void camRoadStrippedReport(const char* p, s32 a, s32 b) {
    OSReport("%scam = %d\n", p, a);
    OSReport("%scurve = %d\n", p, b);
}
#endif

#ifdef NONMATCHING
s32 camRoadSetup(const char* name) {
    char path[128];
    u32 size;
    DVDEntry* entry;
    crCheck((BOOL)"%scam = %d\n");
    crCheck((BOOL)"%scurve = %d\n\0\0");
    memset(wp, 0, 0x210);
    wp->f_c8 = 0;
    wp->prev.on = 0;
    wp->prev.on = 0;
    wp->f_19c[0] = 0.005f;
    wp->f_19c[1] = 0.0f;
    wp->f_19c[2] = 0.004f;
    wp->f_19c[3] = 0.008f;
    wp->f_19c[4] = 1.0f;
    wp->f_19c[5] = 1.0f;
    wp->f_19c[6] = 2.0f;
    wp->f_19c[7] = 1.0f;
    wp->f_19c[8] = 1.0f;
    wp->f_19c[9] = 3.0f;
    wp->f_19c[10] = 1.0f;
    wp->f_204 = -1;
    wp->f_208 = 0;
    camShiftInit();
    arcOpen(name, (void**)&wp->map, &size);
    if (!wp->map) {
        sprintf(path, "%s/%s", getMapDataDvdRoot(), name);
        entry = DVDMgrOpen(path, 2, 0);
        if (entry) {
            size = DVDMgrGetLength(entry);
            wp->map = _mapAlloc((size + 0x1f) & ~0x1f);
            DVDMgrRead(entry, wp->map, (size + 0x1f) & ~0x1f, 0);
            DVDMgrClose(entry);
        } else {
            return 0;
        }
    }
    if ((u32)wp->map->f_e8 < (u32)wp->map) {
        wp->map->f_e8 = (Vec*)((u32)wp->map->f_e8 + (u32)wp->map);
        wp->map->curves = (CamRoadCurve*)((u32)wp->map->curves + (u32)wp->map);
        wp->map->f_f0 = (void*)((u32)wp->map->f_f0 + (u32)wp->map);
        wp->map->f_f4 = (void*)((u32)wp->map->f_f4 + (u32)wp->map);
        wp->map->f_f8 = (void*)((u32)wp->map->f_f8 + (u32)wp->map);
        wp->map->f_fc = (void*)((u32)wp->map->f_fc + (u32)wp->map);
        wp->map->f_100 = (void*)((u32)wp->map->f_100 + (u32)wp->map);
        wp->map->f_104 = (void*)((u32)wp->map->f_104 + (u32)wp->map);
        wp->map->f_108 = (void*)((u32)wp->map->f_108 + (u32)wp->map);
    }
    if (strcmp(wp->map->version, "1.01") == 0) {
        wp->state = 0x65;
    } else {
        wp->state = 0x64;
    }
    return 1;
}
#endif
#ifdef NONMATCHING
void calcCurrentCamState(CamRoadOut* out) {
    Mtx m;
    Vec v;
    Vec res;
    Vec axis;
    f32 rot, x, y, z, dx, dz, dist, a, ox, oy, oz;
    CamRoadState* s;
    Vec* p;
    p = wp->map->f_e8;
    out->f_0.x = p->x;
    out->f_0.y = p->y;
    out->f_0.z = p->z;
    s = &wp->cur;
    if (!s->on) {
        out->pos.x = 0.0f;
        out->pos.y = 100.0f;
        out->pos.z = 100.0f;
        out->at.x = 0.0f;
        out->at.y = 0.0f;
        out->at.z = 0.0f;
        return;
    }
    a = 3.141592f * s->angle / 180.0f;
    x = s->pos.x;
    y = s->pos.y;
    z = s->pos.z;
    dx = s->dir.x;
    dz = s->dir.z;
    dist = s->dist;
    rot = s->rot;
    ox = dx * dist * (f32)cos(a);
    oy = dist * (f32)sin(a);
    oz = dz * dist * (f32)cos(a);
    out->pos.x = x + ox;
    out->pos.y = y + oy;
    out->pos.z = z + oz;
    axis.x = -dz;
    axis.y = 0.0f;
    axis.z = dx;
    PSMTXRotAxisRad(m, &axis, 0.017453292f * rot);
    v.x = -ox;
    v.y = -oy;
    v.z = -oz;
    PSMTXMultVec(m, &v, &res);
    out->at.x = out->pos.x + res.x;
    out->at.y = out->pos.y + res.y;
    out->at.z = out->pos.z + res.z;
}
#endif
static inline Vec crVecSub(Vec a, Vec b) {
    Vec r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
static inline Vec crVecAdd(Vec a, Vec b) {
    Vec r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}
static inline Vec crVecScale(Vec a, f32 s) {
    Vec r;
    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    return r;
}
static inline Vec crVecCross(Vec a, Vec b) {
    Vec r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}
static inline f32 crVecDot(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
static inline BOOL crVecIsZero(Vec a) {
    if (a.x == 0.0f && a.y == 0.0f && a.z == 0.0f) {
        return TRUE;
    }
    return FALSE;
}
#pragma dont_inline on
#ifdef NONMATCHING
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist) {
    Vec dir = {0.0f, -1.0f, 0.0f};
    Vec nz;
    Vec hit;
    Vec e2, e1, e3, n;
    f32 nd, t;
    e2 = crVecSub(C, A);
    e1 = crVecSub(A, B);
    e3 = crVecSub(B, C);
    n = crVecCross(e2, e1);
    nz = n;
    if (nz.x == 0.0f && nz.y == 0.0f && nz.z == 0.0f) {
        return 0;
    }
    nd = crVecDot(n, crVecSub(P, A));
    if (nd > 0.0f) {
        if (crVecDot(n, dir) >= 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, A), crVecCross(e2, dir)) > 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, B), crVecCross(e1, dir)) > 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, C), crVecCross(e3, dir)) > 0.0) {
            return 0;
        }
    } else {
        if (crVecDot(n, dir) <= 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, A), crVecCross(e2, dir)) < 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, B), crVecCross(e1, dir)) < 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, C), crVecCross(e3, dir)) < 0.0) {
            return 0;
        }
    }
    t = -nd / crVecDot(n, dir);
    { Vec h2 = crVecAdd(P, crVecScale(dir, t)); hit = h2; }
    if (hit.y < *dist) {
        return 0;
    }
    *dist = hit.y;
    return 1;
}
#endif
// CC_BEGIN
typedef struct CamRoadCC {
    u8 pad0[0x40];
    s32 idxA;              // 0x40
    s32 idxB;              // 0x44
    f32 limA;              // 0x48
    f32 limB;              // 0x4c
    u8 pad1[0x84 - 0x50];
    s32 flag;              // 0x84
    u8 pad2[0xa0 - 0x88];
    s32 vtxOfs;            // 0xa0
    s32 vtxNum;            // 0xa4
} CamRoadCC;
 static inline f32 crLen2(f32 x, f32 z) {
    f32 l = x * x + z * z;
    if (l != 0.0) {
        l = cr_sqrtf(l);
    }
    return l;
}
#ifdef NONMATCHING
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit) {
    f32 lx0;
    f32 ang0, yA, yB, minDist, cx, side;
    f32 dpx, dpz, sgn, s, limA, limB, x0, y0, z0, x1, z1, cz, r0, r1, rp, r0x, r0z, c1;
    f32 u0x, u0z, u1x, u1z, t, c0, ang1, ratio, d, d0, yy, cross, n1x, n1z;
    f32 r1x, r1z;
    f32 lz0, px, pz, qx, qz, dx, dz, su1x, st, dist, dx2, dz2, cr;
    s32 ret;
    s32 i;
    s32 half;
    s32 idxA, idxB;
    s32 flag, isGrp;
    s32 fl;
    s32 ok;
    Vec* pt;
    Vec* nrm;
    minDist = 100000000.0f;
    ret = 0;
    if (mode == 0) {
        CamRoadCC* c = (CamRoadCC*)curve;
        isGrp = 0;
        half = c->vtxNum / 2;
        pt = &((Vec*)wp->map->f_f8)[c->vtxOfs];
        nrm = &((Vec*)wp->map->f_f8)[c->vtxOfs + half];
        limA = c->limA;
        limB = c->limB;
        idxA = c->idxA;
        idxB = c->idxB;
        flag = c->flag;
    } else {
        CamRoadGroup* g = (CamRoadGroup*)curve;
        idxA = 0;
        idxB = 1;
        half = g->stripNum / 2;
        limB = limA = 0.0f;
        pt = &((Vec*)wp->map->f_f8)[g->stripOfs];
        nrm = &((Vec*)wp->map->f_f8)[g->stripOfs + half];
        flag = 0;
        isGrp = 1;
    }
    yA = nrm[idxA].y;
    yB = nrm[idxB].y;
    if (__fabs(yB - yA) < 0.0001f) {
        yA = yB;
    }
    if (isGrp) {
        flag = 0;
    }
    for (i = 0; i < half - 1; i++) {
        fl = 0;
        x0 = pt[i].x;
        y0 = pt[i].y;
        z0 = pt[i].z;
        x1 = pt[i + 1].x;
        z1 = pt[i + 1].z;
        n1x = -nrm[i + 1].x;
        n1z = -nrm[i + 1].z;
        if (nrm[i].x * (pos.x - x0) + nrm[i].z * (pos.z - z0) < 0.0f) {
            continue;
        }
        if (n1x * (pos.x - x1) + n1z * (pos.z - z1) < 0.0f) {
            continue;
        }
        u0x = -nrm[i].z;
        u0z = nrm[i].x;
        u1x = n1z;
        u1z = -n1x;
        if (__fabs(u0x - u1x) < 0.01f && __fabs(u0z - u1z) < 0.01f) {
            u0x = u1x = 0.5f * (u0x + u1x);
            u0z = u1z = 0.5f * (u0z + u1z);
        }
        if (u0x != u1x || u0z != u1z) {
            side = sgn = 1.0f;
            if (u1x != 0.0) {
                t = (u1z * ((x0 - x1) / u1x) + z1 - z0) / (u0z - u1z * (u0x / u1x));
            } else if (u1z != 0.0) {
                t = (u1x * ((z0 - z1) / u1z) + x1 - x0) / (u0x - u1x * (u0z / u1z));
            } else {
                t = 0.0f;
            }
            cz = t * u0z + z0;
            cx = t * u0x + x0;
            r0z = z0 - cz;
            r0x = x0 - cx;
            r0 = r0x * r0x + r0z * r0z;
            if (r0 != 0.0) {
                r0 = cr_sqrtf(r0);
            }
            dpz = pos.z - cz;
            dpx = pos.x - cx;
            rp = dpx * dpx + dpz * dpz;
            if (rp != 0.0) {
                rp = cr_sqrtf(rp);
            }
            r1z = z1 - cz;
            r1x = x1 - cx;
            r1 = r1x * r1x + r1z * r1z;
            if (r1 != 0.0) {
                r1 = cr_sqrtf(r1);
            }
            c0 = (r0x * dpx + r0z * dpz) / (r0 * rp);
            c1 = (r1x * dpx + r1z * dpz) / (r1 * rp);
            if (c0 < -1.0f) {
                c0 = -1.0f;
            } else if (c0 > 1.0f) {
                c0 = 1.0f;
            }
            if (c1 < -1.0f) {
                c1 = -1.0f;
            } else if (c1 > 1.0f) {
                c1 = 1.0f;
            }
            ang0 = acos(c0);
            ang1 = acos(c1);
            d0 = rp - r0;
            ratio = ang0 / (ang0 + ang1);
            d = ratio * ((rp - r1) - d0) + d0;
            if (d < 0.0f) {
                sgn = -1.0f;
                d = -d;
            }
            if (d >= minDist) {
                continue;
            }
            minDist = d;
            cross = r0x * -(z1 - z0) + r0z * (x1 - x0);
            yy = ratio * (nrm[i + 1].y - nrm[i].y) + nrm[i].y;
            if (flag) {
                if (yy < yA) {
                    if (cross > 0.0) {
                        if (sgn < 0.0f) {
                            if (d > limA) { d = limA; fl |= 2; }
                        } else {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        }
                    } else {
                        if (sgn < 0.0f) {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        } else {
                            if (d > limA) { d = limA; fl |= 2; }
                        }
                    }
                    ret = 1;
                    hit->t = yA;
                    hit->pos.x = pt[idxA].x + d * nrm[idxA].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxA].z - d * nrm[idxA].x;
                    hit->dir.x = nrm[idxA].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxA].z;
                    hit->y = y0;
                    hit->f_24 = idxA;
                    hit->flags = fl | 1;
                    continue;
                }
                if (yy > yB) {
                    if (cross > 0.0) {
                        if (sgn < 0.0f) {
                            if (d > limA) { d = limA; fl |= 2; }
                        } else {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        }
                    } else {
                        if (sgn < 0.0f) {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        } else {
                            if (d > limA) { d = limA; fl |= 2; }
                        }
                    }
                    ret = 1;
                    hit->t = yB;
                    hit->pos.x = pt[idxB].x + d * nrm[idxB].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxB].z - d * nrm[idxB].x;
                    hit->dir.x = nrm[idxB].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxB].z;
                    hit->y = y0;
                    hit->f_24 = idxB;
                    hit->flags = fl | 1;
                    continue;
                }
                if (cross > 0.0) {
                    if (sgn < 0.0f) {
                        if (d > limA) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp += d - limA;
                            dpx *= rp; dpz *= rp;
                        }
                    } else {
                        if (d > limB) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp -= d - limB;
                            dpx *= rp; dpz *= rp;
                        }
                    }
                } else {
                    if (sgn < 0.0f) {
                        if (d > limB) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp += d - limB;
                            dpx *= rp; dpz *= rp;
                        }
                    } else {
                        if (d > limA) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp -= d - limA;
                            dpx *= rp; dpz *= rp;
                        }
                    }
                    side = -1.0f;
                }
            } else if (isGrp) {
                if (cross > 0.0) {
                    if (!(sgn < 0.0f) && d > 0.0f) {
                        dpx /= rp; dpz /= rp; fl = 3;
                        rp -= d;
                        dpx *= rp; dpz *= rp;
                    }
                } else {
                    if (sgn < 0.0f && d > 0.0f) {
                        dpx /= rp; dpz /= rp; fl = 3;
                        rp += d;
                        dpx *= rp; dpz *= rp;
                    }
                    side = -1.0f;
                }
            } else {
                if (!(cross > 0.0)) {
                    side = -1.0f;
                }
            }
            hit->pos.x = cx + dpx;
            hit->pos.y = 0.0f;
            hit->pos.z = cz + dpz;
            if (side < 0.0f) {
                hit->dir.x = -dpz / rp;
                hit->dir.y = 0.0f;
                hit->dir.z = dpx / rp;
            } else {
                hit->dir.x = dpz / rp;
                hit->dir.y = 0.0f;
                hit->dir.z = -dpx / rp;
            }
            hit->t = yy;
            ret = 1;
            hit->y = y0;
            hit->f_24 = i;
            hit->flags = fl;
        } else {
            lz0 = pt[i].z;
            dz = pt[i + 1].z - lz0;
            lx0 = pt[i].x;
            dx = pt[i + 1].x - lx0;
            px = pos.x;
            pz = pos.z;
            su1x = -dz;
            if (__fabs(su1x) > __fabs(dx)) {
                st = (dx * ((lx0 - px) / su1x) + pz - lz0) / (dz - dx * (dx / su1x));
            } else if (dx != 0.0) {
                st = (su1x * ((lz0 - pz) / dx) + px - lx0) / (dx - su1x * (dz / dx));
            } else {
                st = 0.0f;
            }
            qx = st * dx + lx0;
            qz = st * dz + lz0;
            if (__fabs(dx) > __fabs(dz)) {
                s = (qx - lx0) / dx;
                ok = (s < -0.0000001 || s > 1.0000001);
            } else if (dz != 0.0) {
                s = (qz - lz0) / dz;
            }
            dz2 = pz - qz;
            dx2 = px - qx;
            yy = s * (nrm[i + 1].y - nrm[i].y) + nrm[i].y;
            dist = dx2 * dx2 + dz2 * dz2;
            if (dist > 0.0) {
                dist = cr_sqrtf(dist);
            }
            if (dist >= minDist) {
                continue;
            }
            minDist = dist;
            if (flag) {
                if (yy < yA) {
                    cr = dx2 * su1x + dz2 * dx;
                    if (cr < 0.0f) {
                        if (dist > limA) { dist = limA; fl |= 2; }
                    } else {
                        if (dist > limB) { dist = limB; fl |= 2; }
                        dist = -dist;
                    }
                    ret = 1;
                    hit->t = yA;
                    hit->pos.x = pt[idxA].x + dist * nrm[idxA].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxA].z - dist * nrm[idxA].x;
                    hit->dir.x = nrm[idxA].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxA].z;
                    hit->y = y0;
                    hit->f_24 = idxA;
                    hit->flags = fl | 1;
                    continue;
                }
                if (yy > yB) {
                    cr = dx2 * su1x + dz2 * dx;
                    if (cr < 0.0f) {
                        if (dist > limA) { dist = limA; fl |= 2; }
                    } else {
                        if (dist > limB) { dist = limB; fl |= 2; }
                        dist = -dist;
                    }
                    ret = 1;
                    hit->t = yB;
                    hit->pos.x = pt[idxB].x + dist * nrm[idxB].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxB].z - dist * nrm[idxB].x;
                    hit->dir.x = nrm[idxB].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxB].z;
                    hit->y = y0;
                    hit->f_24 = idxB;
                    hit->flags = fl | 1;
                    continue;
                }
                cr = dx2 * su1x + dz2 * dx;
                if (cr < 0.0f) {
                    if (dist > limA) {
                        dx2 = limA * (dx2 / dist);
                        dz2 = limA * (dz2 / dist);
                        fl |= 2;
                    }
                } else {
                    if (dist > limB) {
                        dx2 = limB * (dx2 / dist);
                        dz2 = limB * (dz2 / dist);
                        fl |= 2;
                    }
                }
            }
            hit->t = yy;
            hit->pos.x = qx + dx2;
            hit->pos.y = 0.0f;
            hit->pos.z = qz + dz2;
            ret = 1;
            hit->dir.x = s * (nrm[i + 1].x - nrm[i].x) + nrm[i].x;
            hit->dir.y = 0.0f;
            hit->dir.z = s * (nrm[i + 1].z - nrm[i].z) + nrm[i].z;
            hit->y = y0;
            hit->f_24 = i;
            hit->flags = fl;
        }
    }
    return ret;
}
#endif
// CC_END
#ifdef NONMATCHING
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
    f32 nx;
    f32 ny;
    f32 nz;
    f32 mnz;
    f32 cs, sn, w, ox, oz;
    s32 cnt;
    s32* idxp;
    s32 j;
    s32 l;
    CamRoadCurveX* curve;
    void* hitCurve;
    s32 n;
    CamRoadGroup* grp;
    Vec* verts;
    s32 m;
    CamRoadStrip* strip;
    s32 k;
    s32* idx;
    f32 pz, qz, qx;
    CamRoadState** pp;
    f32 cs2;
    f32 angle;
    f32 rot;
    f32 f4c;
    f32 spd1;
    f32 spd2;
    CamRoadHit hit;
    CamRoadHit hit2;
    CamRoadHit hit3;
    Vec posA;
    Vec posB;
    Vec q;
    Vec p;
    Vec p2;
    Vec v1;
    Vec v2;
    Vec dA;
    Vec dB;
    Vec r1;
    Vec r2;
    f32 best;
    f32 zoom;
    f32 px;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 s, t, sgn1, sgn2, len2, len;
    u32 flags;
    s32 found, found2;
    s32 i;
    f32 fov;
    f32 l1, l2, lim2, lim1;
    curve = (CamRoadCurveX*)wp->map->curves;
    best = -100000000.0f;
    hitCurve = NULL;
    posA.x = a;
    posA.y = b;
    posA.z = c;
    posB.x = d;
    posB.y = e;
    posB.z = f;
    for (i = 0; i < wp->map->curveNum; i++, curve++) {
        grp = &((CamRoadGroup*)wp->map->f_f0)[curve->grpOfs];
        n = curve->grpNum;
        if (wp->state == 0x65 && curve->off != 0) {
            continue;
        }
        if (n == 0) {
            if (curve->height > e) {
                continue;
            }
            if (curve->height > best) {
                best = curve->height;
                hitCurve = curve;
            }
            continue;
        }
        for (j = 0; j < n; j++, grp++) {
            verts = &((Vec*)wp->map->f_fc)[grp->vtxOfs];
            m = grp->stripNum;
            strip = &((CamRoadStrip*)wp->map->f_f4)[grp->stripOfs];
            for (k = 0; k < m; k++, strip++) {
                cnt = strip->num;
        cnt = cnt - 1;
                idx = &((s32*)wp->map->f_100)[strip->idxOfs];
                idxp = idx + 1;
                for (l = 1; cnt > l; idxp++, l++) {
                    if (collisionTri_simple(posB, verts[idx[0]], verts[idxp[0]], verts[idxp[1]], &best)) {
                        hitCurve = curve;
                        break;
                    }
                }
            }
        }
    }
    if (hitCurve != NULL) {
        hit.y = -1000000.0f;
        hit.dir.x = 0.0f;
        hit.dir.y = 0.0f;
        hit.dir.z = 0.0f;
        if (!collisionCurve(0, hitCurve, posA, &hit)) {
            hitCurve = NULL;
        }
    }
    curve = (CamRoadCurveX*)hitCurve;
    if (curve == NULL) {
        curve = prev->on ? (CamRoadCurveX*)prev->cam : NULL;
        if (curve == NULL) {
            ((f32*)((u8*)wp + 0x1d4))[0] = a;
            ((f32*)((u8*)wp + 0x1d4))[1] = b;
            ((f32*)((u8*)wp + 0x1d4))[2] = c;
            ((f32*)((u8*)wp + 0x1d4))[3] = d;
            ((f32*)((u8*)wp + 0x1d4))[4] = e;
            ((f32*)((u8*)wp + 0x1d4))[5] = f;
            return;
        }
        x = a;
        if (wp->state == 0x65 && curve != NULL && curve->f_20 != 0) {
            y = curve->f_24;
        } else {
            y = b;
        }
        z = c;
        nx = -prev->dir.x;
        ny = -prev->dir.y;
        nz = -prev->dir.z;
        angle = prev->angle;
        dist = prev->dist;
        rot = prev->rot;
        f4c = prev->f_4c;
        flags = 0;
    } else {
        if (hit.t < 0.0f) {
            hit.t = 0.0f;
        }
        if (hit.t > 1.0f) {
            hit.t = 1.0f;
        }
        angle = curve->f_64;
        rot = curve->f_70;
        dist = curve->f_58;
        x = hit.pos.x;
        if (wp->state == 0x65 && curve->f_20 != 0) {
            y = curve->f_24;
        } else {
            y = b;
        }
        nx = -hit.dir.z;
        len2 = nx * nx + hit.dir.x * hit.dir.x;
        f4c = hit.f_24;
        nz = hit.dir.x;
        z = hit.pos.z;
        flags = hit.flags;
        ny = hit.dir.y;
        if (len2 != 0.0) {
            len = cr_sqrtf(len2);
            nx = nx / len;
            ny = 0.0f;
            nz = nz / len;
        }
        nx *= -1.0f;
        ny *= -1.0f;
        nz *= -1.0f;
    }
    if (curve->f_b4 != 0) {
        grp = &((CamRoadGroup*)wp->map->f_104)[curve->f_b0];
        q.y = 100000000.0f;
        q.x = x;
        q.z = z;
        hit.y = -1000000.0f;
        if (collisionCurve(1, grp, q, &hit)) {
            flags |= hit.flags;
            x = hit.pos.x;
            z = hit.pos.z;
        }
    }
    if (curve != NULL) {
        fov = 3.1415927f * (wp->map->f_e8->x * 0.5f / 180.0f);
        zoom = 1.0f;
        if (g && hitCurve != NULL && prev->on) {
            cs = (f32)cos(fov);
            sn = (f32)sin(fov);
            mnz = -nz;
            w = 0.01f * (prev->f_58 * (zoom * (640.0f * (dist * sn / cs) / 480.0f)));
            found = 0;
            p = posA;
            p.y = 1000000.0f;
            hit2.y = -1000000.0f;
            hit2.dir.z = 0.0f;
            hit2.dir.y = 0.0f;
            hit2.dir.x = 0.0f;
            ox = w * mnz;
            oz = w * nx;
            p.x = p.x + ox;
            p.z = p.z + oz;
            if (collisionCurve(0, curve, p, &hit2)) {
                found = 1;
                p.x = hit2.pos.x;
                p.y = y;
                p.z = hit2.pos.z;
            }
            if (curve->f_b4 != 0) {
                grp = &((CamRoadGroup*)wp->map->f_104)[curve->f_b0];
                hit2.y = -1000000.0f;
                if (collisionCurve(1, grp, p, &hit2)) {
                    found = 1;
                    p.x = hit2.pos.x;
                    p.y = y;
                    p.z = hit2.pos.z;
                }
            }
            if (found) {
                qx = p.x;
                qz = p.z;
            } else {
                qx = x;
                qz = z;
            }
            
            cs2 = (f32)cos(fov);
            sn = (f32)sin(fov);
            w = 0.01f * (g * (zoom * (640.0f * (dist * sn / cs2) / 480.0f)));
            found2 = 0;
            flags = 0;
            p2 = posA;
            p2.y = 1000000.0f;
            hit3.y = -1000000.0f;
            hit3.dir.z = 0.0f;
            hit3.dir.y = 0.0f;
            hit3.dir.x = 0.0f;
            ox = w * mnz;
            oz = w * nx;
            p2.x = p2.x + ox;
            p2.z = p2.z + oz;
            if (collisionCurve(0, curve, p2, &hit3)) {
                found2 = 1;
                flags = hit3.flags;
                p2.x = hit3.pos.x;
                p2.y = y;
                p2.z = hit3.pos.z;
            }
            if (curve->f_b4 != 0) {
                grp = &((CamRoadGroup*)wp->map->f_104)[curve->f_b0];
                hit3.y = -1000000.0f;
                if (collisionCurve(1, grp, p2, &hit3)) {
                    found2 = 1;
                    p2.x = hit3.pos.x;
                    flags |= hit3.flags;
                    p2.z = hit3.pos.z;
                }
            }
            if (found2) {
                px = p2.x;
                pz = p2.z;
                if (!(hit3.flags & 1) && (prev->f_08 & 1)) {
                    wp->f_19c[4] = 0.0f;
                }
                if (!(hit3.flags & 2) && (prev->f_08 & 2)) {
                    wp->f_19c[5] = 0.0f;
                }
            } else {
                px = x;
                pz = z;
            }
            v1.x = qx - prev->pos.x;
            v1.y = 0.0f;
            v1.z = qz - prev->pos.z;
            v2.x = px - prev->pos.x;
            v2.y = 0.0f;
            v2.z = pz - prev->pos.z;
            lim1 = PSVECMag(&v1);
            lim2 = PSVECMag(&v2);
            lim1 += getV60FPS(wp->f_19c[0], prev->time, gp->renderFieldTime);
            lim2 = getV60FPS(wp->f_19c[1], prev->time, gp->renderFieldTime);
            l1 = lim1 * wp->f_19c[4];
            l2 = lim1 * wp->f_19c[5];
            spd1 = lim2 * wp->f_19c[4];
            spd2 = lim2 * wp->f_19c[5];
            dA.x = mnz;
            dA.z = nx;
            dB.x = -dA.z;
            dB.z = dA.x;
            dA.y = 0.0f;
            dB.y = 0.0f;
            r1.y = 0.0f;
            r2.y = 0.0f;
            if (__fabs(dA.z) > __fabs(dA.x)) {
                t = (v2.x - dA.x * (v2.z / dA.z)) / (dB.x - dB.z * (dA.x / dA.z));
                s = (v2.z - t * dB.z) / dA.z;
            } else {
                t = (v2.z - dA.z * (v2.x / dA.x)) / (dB.z - dA.z * (dB.x / dA.x));
                s = (v2.x - t * dB.x) / dA.x;
            }
            r1.x = s * dA.x;
            r1.z = s * dA.z;
            r2.x = t * dB.x;
            r2.z = t * dB.z;
            sgn2 = t < 0.0f ? -1.0f : 1.0f;
            sgn1 = s < 0.0f ? -1.0f : 1.0f;
            lim1 = PSVECMag(&r1);
            lim2 = PSVECMag(&r2);
            if (lim1 > l1 && lim1 > spd1) {
                PSVECScale(&dA, &r1, l1 * sgn1);
            }
            if (lim2 > l2 && lim2 > spd2) {
                PSVECScale(&dB, &r2, l2 * sgn2);
            }
            x = prev->pos.x;
            z = prev->pos.z;
            x += r1.x + r2.x;
            z += r1.z + r2.z;
        }
    }
    wp->f_19c[4] += wp->f_19c[2];
    if (wp->f_19c[4] > 1.0f) {
        wp->f_19c[4] = 1.0f;
    }
    wp->f_19c[5] += wp->f_19c[3];
    if (wp->f_19c[5] > 1.0f) {
        wp->f_19c[5] = 1.0f;
    }
    out->on = 1;
    out->f_04 = hitCurve != NULL;
    out->f_08 = flags;
    out->in[0] = a;
    out->in[1] = b;
    out->in[2] = c;
    out->in[3] = d;
    out->in[4] = e;
    out->in[5] = f;
    out->cam = (CamRoadCam*)curve;
    out->pos.x = x;
    out->pos.y = y;
    out->pos.z = z;
    out->dir.x = -nx;
    out->dir.y = -ny;
    out->dir.z = -nz;
    out->dist = dist;
    out->angle = angle;
    out->rot = rot;
    out->f_4c = f4c;
    out->time = gp->renderFieldTime;
    out->f_58 = g;
    out->shiftXRate = curve->f_7c;
}
#endif
#pragma dont_inline reset
static inline f32 crSq(f32 x) { return x * x; }
#ifdef NONMATCHING
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed) {
    u32 flags = 0;
    s32 d;
    s32 n;
    f32 dot, ang, speed, t, dx, dy, dz, d2, dist;
    if (!b->on) {
        return 0;
    }
    if (a->cam == b->cam && !(a->f_04 == 1 && b->f_04 == 0) && !(a->f_04 == 0 && b->f_08 == 1)) {
        d = (s32)a->f_4c - (s32)b->f_4c;
        if (__abs(d) <= 1) {
            return 0;
        }
        n = a->cam->f_44 - a->cam->f_40;
        if (__abs(d) >= --n) {
            return 0;
        }
        if (__abs(d) >= --n) {
            flags |= 0x20;
        }
    }
    if (a->cam != b->cam) {
        flags |= 1;
    }
    if (a->f_04 == 1 && b->f_04 == 0) {
        flags |= 2;
    }
    if (a->f_04 == 0 && b->f_08 == 1) {
        flags |= 4;
    }
    if (!(__fabs(a->f_4c - b->f_4c) <= 1.0)) {
        flags |= 8;
    }
    dot = a->dir.x * b->dir.x + a->dir.z * b->dir.z;
    if (dot > 1.0f) {
        dot = 1.0f;
    }
    ang = __fabsf(57.29578f * (f32)acos(dot));
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f;
    speed = t * wp->f_19c[6];
    ang = __fabsf(a->angle - b->angle);
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f;
    t *= wp->f_19c[7];
    if (t > speed) {
        speed = t;
    }
    ang = __fabsf(a->rot - b->rot);
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f;
    t *= wp->f_19c[8];
    if (t > speed) {
        speed = t;
    }
    t = __fabsf(a->dist - b->dist);
    t *= wp->f_19c[9];
    if (t > speed) {
        speed = t;
    }
    dx = a->pos.x - b->pos.x;
    dy = a->pos.y - b->pos.y;
    dz = a->pos.z - b->pos.z;
    dist = crSq(dx);
    dist += crSq(dy);
    dist += crSq(dz);
    if (dist) {
        if (dist > 0.0f) {
            f64 guess = __frsqrte(dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            dist = dist * guess;
        } else if (dist < 0.0) {
            dist = *(f32*)__float_nan;
        } else if (cr_fpclassifyf(dist) == 1) {
            dist = *(f32*)__float_nan;
        }
    } else {
        dist = 0.0f;
    }
    if (speed < 0.01f && dist < 0.3f) {
        return 0;
    }
    t = dist * wp->f_19c[10];
    if (t > speed) {
        speed = t;
    }
    if (speed > 90.0f) {
        speed = 90.0f;
    }
    if (speed < 20.0f) {
        speed = 20.0f;
    }
    *outSpeed = 1.0f / speed;
    if (!flags) {
        flags |= 0x10;
    }
    return flags;
}
#endif
static inline f32 hokanRate(f32 t, f32 a, f32 b, f32 k, f32 o) {
    f32 c1, c0, c2, r;
    c0 = (f32)((double (*)(f32))cos)(a);
    c1 = (f32)((double (*)(f32))cos)(b);
    c2 = (f32)cos(3.141592f * t * k + o);
    r = (2.0f / (1.0f + c0)) * (0.5f * (1.0f - c1) + c2);
    r = 0.500001f * (2.0f - (1.0f + r));
    if (r > 1.0f) {
        r = 1.0f;
    }
    return r;
}
static inline f32 angleLerp(f32 a0, f32 a1, f32 r) {
    while (a0 - a1 > 3.1415927f) {
        a0 -= 6.2831855f;
    }
    while (a0 - a1 < -3.1415927f) {
        a0 += 6.2831855f;
    }
    return r * (a1 - a0) + a0;
}
#pragma dont_inline on
#ifdef NONMATCHING
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t) {
    f32 r, a0, a1, a2;
    r = hokanRate(t, 0.0f, 0.0f, 1.0f, 0.0f);
    if (type) {
        out->pos.x = r * (to->pos.x - from->pos.x) + from->pos.x;
        out->pos.y = r * (to->pos.y - from->pos.y) + from->pos.y;
        out->pos.z = r * (to->pos.z - from->pos.z) + from->pos.z;
    } else {
        out->pos.x = to->pos.x;
        out->pos.y = to->pos.y;
        out->pos.z = to->pos.z;
    }
    a2 = (f32)atan2(from->dir.x, from->dir.z);
    a0 = a2;
    a1 = (f32)atan2(to->dir.x, to->dir.z);
    while (a0 - a1 > 3.1415927f) {
        a0 -= 6.2831855f;
    }
    while (a0 - a1 < -3.1415927f) {
        a0 += 6.2831855f;
    }
    a0 = r * (a1 - a0) + a0;
    out->dir.x = (f32)sin(a0);
    out->dir.z = (f32)cos(a0);
    out->dir.y = r * (to->dir.y - from->dir.y) + from->dir.y;
    out->dist = r * (to->dist - from->dist) + from->dist;
    out->angle = r * (to->angle - from->angle) + from->angle;
    out->rot = r * (to->rot - from->rot) + from->rot;
    out->shiftXRate = r * (to->shiftXRate - from->shiftXRate) + from->shiftXRate;
}
#endif
#pragma dont_inline reset
#define CAMROAD_HOKAN_START(src, flags)                                                                     \
    {                                                                                                         \
        wp->cmpFlags = flags;                                                                                 \
        wp->f_c8 = 1;                                                                                         \
        wp->time = gp->renderFieldTime;                                                                       \
        wp->hokanT = 0.0f;                                                                                    \
        wp->start = src;                                                                                      \
        wp->prev = wp->next;                                                                                  \
        if (wp->prev.f_08 || wp->start.f_08 ||                                                                \
            (wp->state == 0x65 &&                                                                             \
             ((wp->prev.cam && wp->prev.cam->f_20) || (wp->start.cam && wp->start.cam->f_20))) ||             \
            (wp->prev.cam && wp->prev.cam->f_7c) || (wp->start.cam && wp->start.cam->f_7c)) {                 \
            wp->hokanType = 1;                                                                                \
        } else {                                                                                              \
            wp->hokanType = 0;                                                                                \
        }                                                                                                     \
    }
#ifdef NONMATCHING
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
    u32 flags;
    wp->in[0] = a;
    wp->in[1] = b;
    wp->in[2] = c;
    wp->in[3] = d;
    wp->in[4] = e;
    wp->in[5] = f;
    calcCamRoad(&wp->next, &wp->prev, a / 10.0f, b / 10.0f, c / 10.0f, d / 10.0f, e / 10.0f, f / 10.0f, g);
    if (wp->f_c8) {
        flags = compareCamRoad(&wp->prev, &wp->next, &wp->hokanSpeed);
        if (flags) {
            CAMROAD_HOKAN_START(wp->cur, flags)
        } else {
            wp->prev = wp->next;
        }
    }
    if (!wp->f_c8) {
        flags = compareCamRoad(&wp->next, &wp->prev, &wp->hokanSpeed);
        if (flags) {
            CAMROAD_HOKAN_START(wp->prev, flags)
        }
    }
    if (wp->f_c8) {
        wp->hokanT += getV60FPS(wp->hokanSpeed, wp->time, gp->renderFieldTime);
        if (wp->hokanT > 1.0f) {
            wp->hokanT = 1.0f;
        }
        wp->time = gp->renderFieldTime;
        calcHokanCamRoad(wp->hokanType, &wp->start, &wp->prev, &wp->next, &wp->cur, wp->hokanT);
        if (wp->hokanType) {
            wp->cur.f_08 = 1;
        } else {
            wp->cur.f_08 = 0;
        }
        if (1.0f == wp->hokanT) {
            wp->cur = wp->prev;
            wp->f_c8 = 0;
        }
    } else {
        wp->cur = wp->prev = wp->next;
    }
    calcCurrentCamState(out);
    out->at.x *= 10.0f;
    out->at.y *= 10.0f;
    out->at.z *= 10.0f;
    out->pos.x *= 10.0f;
    out->pos.y *= 10.0f;
    out->pos.z *= 10.0f;
}
#endif
#ifdef NONMATCHING
void* camRoadGetWorkPtr(void) {
    return wp;
}
#endif
#ifdef NONMATCHING
f32 camRoadGetCurrentShiftXRate(void) {
    if (wp->next.on) {
        return wp->next.shiftXRate;
    }
    return 0.0f;
}
#endif
#ifdef NONMATCHING
void camRoadReset(void) {
    s32 a = wp->f_204;
    CamRoadMap* m = wp->map;
    u32 s = wp->state;
    memset(wp, 0, 0x210);
    wp->f_c8 = 0;
    wp->prev.on = 0;
    wp->prev.on = 0;
    wp->f_19c[0] = 0.005f;
    wp->f_19c[1] = 0.0f;
    wp->f_19c[2] = 0.004f;
    wp->f_19c[3] = 0.008f;
    wp->f_19c[4] = 1.0f;
    wp->f_19c[5] = 1.0f;
    wp->f_19c[6] = 2.0f;
    wp->f_19c[7] = 1.0f;
    wp->f_19c[8] = 1.0f;
    wp->f_19c[9] = 3.0f;
    wp->f_19c[10] = 1.0f;
    wp->f_204 = -1;
    wp->f_208 = 0;
    wp->f_204 = a;
    wp->map = m;
    wp->state = s;
}
#endif
#ifdef NONMATCHING
void camRoadCurveOn(const char* name) {
    CamRoadCurve* c = wp->map->curves;
    s32 i;
    if (wp->state == 0x65) {
        for (i = 0; i < wp->map->curveNum; i++, c++) {
            if (strcmp(c->name, name) == 0) {
                c->off = 0;
                break;
            }
        }
    }
}
#endif
#ifdef NONMATCHING
void camRoadCurveOff(const char* name) {
    CamRoadCurve* c = wp->map->curves;
    s32 i;
    if (wp->state == 0x65) {
        for (i = 0; i < wp->map->curveNum; i++, c++) {
            if (strcmp(c->name, name) == 0) {
                c->off = 1;
                break;
            }
        }
    }
}
#endif


// prototypes for asm stopgap forward references
void camRoadCurveOff(const char* name);
void camRoadCurveOn(const char* name);
void camRoadReset(void);
f32 camRoadGetCurrentShiftXRate(void);
void* camRoadGetWorkPtr(void);
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed);
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit);
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist);
void calcCurrentCamState(CamRoadOut* out);
s32 camRoadSetup(const char* name);
#ifndef NONMATCHING
// ASM-STOPGAP: camRoadSetup (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c12d0[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c12dc[3] = { 90.0f, 110.0f, 13.0f };
__declspec(section ".rodata") const f32 vec3_802c12e8[3] = { -110.0f, -70.0f, -190.0f };
__declspec(section ".rodata") const f32 vec3_802c12f4[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f64 double_1_802c1300 = 1;
__declspec(section ".rodata") const f64 double_0p5_802c1308 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c1310 = 3;
__declspec(section ".rodata") const f64 double_0_802c1318 = 0;
__declspec(section ".rodata") const f64 double_to_int_802c1320 = 4503601774854144;
__declspec(section ".rodata") const f64 double_0p0001_802c1328 = 0.00009999999747378752;
__declspec(section ".rodata") const f64 double_0p01_802c1330 = 0.009999999776482582;
__declspec(section ".rodata") const f64 double_neg1Eneg07_802c1338 = -0.0000001;
__declspec(section ".rodata") const f64 double_1_802c1340 = 1.0000001;
__declspec(section ".rodata") const char str_802C1348[] = "%scam = %d\n";
__declspec(section ".rodata") const char str_802C1354[] = "%scurve = %d\n\000\000";
__declspec(section ".rodata") const u32 gap_04_802C1364_rodata[1] = { 0x00000000 };
__declspec(section ".sdata2") const f32 float_0p005_80419548 = 0.005f;
__declspec(section ".sdata2") const f32 float_0_8041954c = 0.0f;
__declspec(section ".sdata2") const f32 float_0p004_80419550 = 0.004f;
__declspec(section ".sdata2") const f32 float_0p008_80419554 = 0.008f;
__declspec(section ".sdata2") const f32 float_1_80419558 = 1.0f;
__declspec(section ".sdata2") const f32 float_2_8041955c = 2.0f;
__declspec(section ".sdata2") const f32 float_3_80419560 = 3.0f;
__declspec(section ".sdata2") const f32 float_10_80419564 = 10.0f;
__declspec(section ".sdata2") const f32 float_3p1416_80419568 = 3.141592f;
__declspec(section ".sdata2") const f32 float_0p5_8041956c = 0.5f;
__declspec(section ".sdata2") const f32 float_0p5_80419570 = 0.500001f;
__declspec(section ".sdata2") const f32 float_6p2832_80419574 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_3p1416_80419578 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_neg3p1416_8041957c = -3.1415927f;
__declspec(section ".sdata2") const f32 float_rad2deg_80419580 = 57.29578f;
__declspec(section ".sdata2") const f32 float_360_80419584 = 360.0f;
__declspec(section ".sdata2") const f32 float_180_80419588 = 180.0f;
__declspec(section ".sdata2") const f32 float_0p01_8041958c = 0.01f;
__declspec(section ".sdata2") const f32 float_0p3_80419590 = 0.3f;
__declspec(section ".sdata2") const f32 float_90_80419594 = 90.0f;
__declspec(section ".sdata2") const f32 float_20_80419598 = 20.0f;
__declspec(section ".sdata2") const f32 dat_8041959c = -100000000.0f;
__declspec(section ".sdata2") const f32 float_neg1E06_804195a0 = -1000000.0f;
__declspec(section ".sdata2") const f32 float_neg1_804195a4 = -1.0f;
__declspec(section ".sdata2") const f32 dat_804195a8 = 100000000.0f;
__declspec(section ".sdata2") const f32 float_640_804195ac = 640.0f;
__declspec(section ".sdata2") const f32 float_480_804195b0 = 480.0f;
__declspec(section ".sdata2") const f32 float_1E06_804195b4 = 1000000.0f;
__declspec(section ".sdata2") const f32 float_100_804195b8 = 100.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_804195bc = 0.017453292f;
__declspec(section ".sdata2") const char str_804195C0[8] = "%s/%s\0\0";
__declspec(section ".sdata2") const char str_804195C8[8] = "1.01\0\0\0";

asm void camRoadCurveOff(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r4, wp(r13)
	lwz r0, 0x1d0(r4)
	lwz r3, 0x0(r4)
	cmplwi r0, 0x65
	lwz r31, 0xec(r3)
	bne @1
	li r30, 0x0
	b @2
	@3:
	mr r3, r31
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	li r0, 0x1
	stw r0, 0x28(r31)
	b @1
	@4:
	addi r30, r30, 0x1
	addi r31, r31, 0xb8
	@2:
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xc8(r3)
	cmpw r30, r0
	blt @3
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void camRoadCurveOn(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r4, wp(r13)
	lwz r0, 0x1d0(r4)
	lwz r3, 0x0(r4)
	cmplwi r0, 0x65
	lwz r31, 0xec(r3)
	bne @1
	li r30, 0x0
	b @2
	@3:
	mr r3, r31
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	li r0, 0x0
	stw r0, 0x28(r31)
	b @1
	@4:
	addi r30, r30, 0x1
	addi r31, r31, 0xb8
	@2:
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xc8(r3)
	cmpw r30, r0
	blt @3
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void camRoadReset(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	li r4, 0x0
	li r5, 0x210
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, wp(r13)
	lwz r31, 0x204(r3)
	lwz r30, 0x0(r3)
	lwz r29, 0x1d0(r3)
	bl memset
	lwz r3, wp(r13)
	li r4, 0x0
	lfs f6, float_0p005_80419548(r2)
	li r0, -0x1
	stw r4, 0xc8(r3)
	lfs f5, float_0_8041954c(r2)
	lwz r3, wp(r13)
	lfs f4, float_0p004_80419550(r2)
	stw r4, 0xd8(r3)
	lfs f3, float_0p008_80419554(r2)
	lwz r3, wp(r13)
	lfs f2, float_1_80419558(r2)
	stw r4, 0xd8(r3)
	lfs f1, float_2_8041955c(r2)
	lwz r3, wp(r13)
	lfs f0, float_3_80419560(r2)
	stfs f6, 0x19c(r3)
	lwz r3, wp(r13)
	stfs f5, 0x1a0(r3)
	lwz r3, wp(r13)
	stfs f4, 0x1a4(r3)
	lwz r3, wp(r13)
	stfs f3, 0x1a8(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1ac(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1b0(r3)
	lwz r3, wp(r13)
	stfs f1, 0x1b4(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1b8(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1bc(r3)
	lwz r3, wp(r13)
	stfs f0, 0x1c0(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1c4(r3)
	lwz r3, wp(r13)
	stw r0, 0x204(r3)
	lwz r3, wp(r13)
	stw r4, 0x208(r3)
	lwz r3, wp(r13)
	stw r31, 0x204(r3)
	lwz r3, wp(r13)
	stw r30, 0x0(r3)
	lwz r3, wp(r13)
	stw r29, 0x1d0(r3)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm f32 camRoadGetCurrentShiftXRate(void) {
	nofralloc
	lwz r3, wp(r13)
	lwz r0, 0x68(r3)
	cmpwi r0, 0x0
	beq @1
	lfs f1, 0xc4(r3)
	blr
	@1:
	lfs f1, float_0_8041954c(r2)
	blr
}

asm void* camRoadGetWorkPtr(void) {
	nofralloc
	lwz r3, wp(r13)
	blr
}

asm void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lfs f0, float_10_80419564(r2)
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r4, wp(r13)
	stfs f1, 0x1ec(r4)
	fdivs f1, f1, f0
	lwz r3, wp(r13)
	stfs f2, 0x1f0(r3)
	lwz r3, wp(r13)
	stfs f3, 0x1f4(r3)
	lwz r3, wp(r13)
	stfs f4, 0x1f8(r3)
	fdivs f2, f2, f0
	lwz r3, wp(r13)
	stfs f5, 0x1fc(r3)
	lwz r3, wp(r13)
	stfs f6, 0x200(r3)
	lwz r4, wp(r13)
	addi r3, r4, 0x68
	fdivs f3, f3, f0
	addi r4, r4, 0xd8
	fdivs f4, f4, f0
	fdivs f5, f5, f0
	fdivs f6, f6, f0
	bl calcCamRoad
	lwz r5, wp(r13)
	lwz r0, 0xc8(r5)
	cmpwi r0, 0x0
	beq @1
	addi r3, r5, 0xd8
	addi r4, r5, 0x68
	addi r5, r5, 0xd4
	bl compareCamRoad
	cmplwi r3, 0x0
	beq @2
	lwz r5, wp(r13)
	li r4, 0x1
	lfs f0, float_0_8041954c(r2)
	li r0, 0xc
	stw r3, 0x198(r5)
	lwz r3, wp(r13)
	stw r4, 0xc8(r3)
	lwz r5, gp(r13)
	lwz r3, wp(r13)
	lwz r4, 0x40(r5)
	lwz r5, 0x44(r5)
	stw r5, 0x1cc(r3)
	stw r4, 0x1c8(r3)
	lwz r3, wp(r13)
	stfs f0, 0xd0(r3)
	lwz r3, wp(r13)
	addi r5, r3, 0x134
	addi r4, r3, 0x4
	mtctr r0
	@3:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @3
	lwz r3, wp(r13)
	li r0, 0xc
	addi r5, r3, 0xd4
	addi r4, r3, 0x64
	mtctr r0
	@4:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @4
	lwz r3, wp(r13)
	lwz r0, 0xe0(r3)
	cmpwi r0, 0x0
	bne @5
	lwz r0, 0x140(r3)
	cmpwi r0, 0x0
	bne @5
	lwz r0, 0x1d0(r3)
	cmplwi r0, 0x65
	bne @6
	lwz r4, 0xfc(r3)
	cmplwi r4, 0x0
	beq @7
	lwz r0, 0x20(r4)
	cmplwi r0, 0x0
	bne @5
	@7:
	lwz r4, 0x15c(r3)
	cmplwi r4, 0x0
	beq @6
	lwz r0, 0x20(r4)
	cmplwi r0, 0x0
	bne @5
	@6:
	lwz r4, 0xfc(r3)
	cmplwi r4, 0x0
	beq @8
	lfs f1, 0x7c(r4)
	lfs f0, float_0_8041954c(r2)
	fcmpu cr0, f1, f0
	bne @5
	@8:
	lwz r4, 0x15c(r3)
	cmplwi r4, 0x0
	beq @9
	lfs f1, 0x7c(r4)
	lfs f0, float_0_8041954c(r2)
	fcmpu cr0, f1, f0
	beq @9
	@5:
	li r0, 0x1
	stw r0, 0xcc(r3)
	b @1
	@9:
	li r0, 0x0
	stw r0, 0xcc(r3)
	b @1
	@2:
	lwz r3, wp(r13)
	li r0, 0xc
	addi r5, r3, 0xd4
	addi r4, r3, 0x64
	mtctr r0
	@10:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @10
	@1:
	lwz r5, wp(r13)
	lwz r0, 0xc8(r5)
	cmpwi r0, 0x0
	bne @11
	addi r3, r5, 0x68
	addi r4, r5, 0xd8
	addi r5, r5, 0xd4
	bl compareCamRoad
	cmplwi r3, 0x0
	beq @11
	lwz r5, wp(r13)
	li r4, 0x1
	lfs f0, float_0_8041954c(r2)
	li r0, 0xc
	stw r3, 0x198(r5)
	lwz r3, wp(r13)
	stw r4, 0xc8(r3)
	lwz r5, gp(r13)
	lwz r3, wp(r13)
	lwz r4, 0x40(r5)
	lwz r5, 0x44(r5)
	stw r5, 0x1cc(r3)
	stw r4, 0x1c8(r3)
	lwz r3, wp(r13)
	stfs f0, 0xd0(r3)
	lwz r3, wp(r13)
	addi r5, r3, 0x134
	addi r4, r3, 0xd4
	mtctr r0
	@12:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @12
	lwz r3, wp(r13)
	li r0, 0xc
	addi r5, r3, 0xd4
	addi r4, r3, 0x64
	mtctr r0
	@13:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @13
	lwz r3, wp(r13)
	lwz r0, 0xe0(r3)
	cmpwi r0, 0x0
	bne @14
	lwz r0, 0x140(r3)
	cmpwi r0, 0x0
	bne @14
	lwz r0, 0x1d0(r3)
	cmplwi r0, 0x65
	bne @15
	lwz r4, 0xfc(r3)
	cmplwi r4, 0x0
	beq @16
	lwz r0, 0x20(r4)
	cmplwi r0, 0x0
	bne @14
	@16:
	lwz r4, 0x15c(r3)
	cmplwi r4, 0x0
	beq @15
	lwz r0, 0x20(r4)
	cmplwi r0, 0x0
	bne @14
	@15:
	lwz r4, 0xfc(r3)
	cmplwi r4, 0x0
	beq @17
	lfs f1, 0x7c(r4)
	lfs f0, float_0_8041954c(r2)
	fcmpu cr0, f1, f0
	bne @14
	@17:
	lwz r4, 0x15c(r3)
	cmplwi r4, 0x0
	beq @18
	lfs f1, 0x7c(r4)
	lfs f0, float_0_8041954c(r2)
	fcmpu cr0, f1, f0
	beq @18
	@14:
	li r0, 0x1
	stw r0, 0xcc(r3)
	b @11
	@18:
	li r0, 0x0
	stw r0, 0xcc(r3)
	@11:
	lwz r7, wp(r13)
	lwz r0, 0xc8(r7)
	cmpwi r0, 0x0
	beq @19
	lwz r6, gp(r13)
	lfs f1, 0xd4(r7)
	lwz r3, 0x1c8(r7)
	lwz r4, 0x1cc(r7)
	lwz r5, 0x40(r6)
	lwz r6, 0x44(r6)
	bl getV60FPS
	lwz r3, wp(r13)
	lfs f0, float_1_80419558(r2)
	lfs f2, 0xd0(r3)
	fadds f1, f2, f1
	stfs f1, 0xd0(r3)
	lwz r3, wp(r13)
	lfs f1, 0xd0(r3)
	fcmpo cr0, f1, f0
	ble @20
	stfs f0, 0xd0(r3)
	@20:
	lwz r4, gp(r13)
	lwz r3, wp(r13)
	lwz r0, 0x40(r4)
	lwz r4, 0x44(r4)
	stw r4, 0x1cc(r3)
	stw r0, 0x1c8(r3)
	lwz r7, wp(r13)
	lwz r3, 0xcc(r7)
	addi r4, r7, 0x138
	lfs f1, 0xd0(r7)
	addi r5, r7, 0xd8
	addi r6, r7, 0x68
	addi r7, r7, 0x8
	bl calcHokanCamRoad
	lwz r3, wp(r13)
	lwz r0, 0xcc(r3)
	cmpwi r0, 0x0
	beq @21
	li r0, 0x1
	stw r0, 0x10(r3)
	b @22
	@21:
	li r0, 0x0
	stw r0, 0x10(r3)
	@22:
	lwz r3, wp(r13)
	lfs f1, float_1_80419558(r2)
	lfs f0, 0xd0(r3)
	fcmpu cr0, f1, f0
	bne @23
	li r0, 0xc
	addi r5, r3, 0x4
	addi r4, r3, 0xd4
	mtctr r0
	@24:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @24
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xc8(r3)
	b @23
	@19:
	li r0, 0xc
	addi r5, r7, 0xd4
	addi r4, r7, 0x64
	mtctr r0
	@25:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @25
	lwz r3, wp(r13)
	li r0, 0xc
	addi r4, r7, 0xd4
	addi r5, r3, 0x4
	mtctr r0
	@26:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @26
	@23:
	mr r3, r31
	bl calcCurrentCamState
	lfs f0, 0x18(r31)
	lfs f1, float_10_80419564(r2)
	fmuls f0, f0, f1
	stfs f0, 0x18(r31)
	lfs f0, 0x1c(r31)
	fmuls f0, f0, f1
	stfs f0, 0x1c(r31)
	lfs f0, 0x20(r31)
	fmuls f0, f0, f1
	stfs f0, 0x20(r31)
	lfs f0, 0xc(r31)
	fmuls f0, f0, f1
	stfs f0, 0xc(r31)
	lfs f0, 0x10(r31)
	fmuls f0, f0, f1
	stfs f0, 0x10(r31)
	lfs f0, 0x14(r31)
	fmuls f0, f0, f1
	stfs f0, 0x14(r31)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stfd f29, 0x20(r1)
	psq_st f29, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	fmr f29, f1
	lfs f1, float_0_8041954c(r2)
	mr r28, r3
	mr r29, r4
	mr r30, r5
	mr r31, r7
	bl cos
	frsp f31, f1
	lfs f1, float_0_8041954c(r2)
	bl cos
	lfs f0, float_3p1416_80419568(r2)
	frsp f30, f1
	lfs f1, float_1_80419558(r2)
	fmuls f2, f0, f29
	lfs f0, float_0_8041954c(r2)
	fmadds f1, f2, f1, f0
	bl cos
	lfs f4, float_1_80419558(r2)
	frsp f6, f1
	lfs f5, float_2_8041955c(r2)
	fadds f3, f4, f31
	lfs f2, float_0p5_8041956c(r2)
	fsubs f0, f4, f30
	lfs f1, float_0p5_80419570(r2)
	fdivs f3, f5, f3
	fmadds f0, f2, f0, f6
	fmuls f0, f3, f0
	fadds f0, f4, f0
	fsubs f0, f5, f0
	fmuls f31, f1, f0
	fcmpo cr0, f31, f4
	ble @1
	fmr f31, f4
	@1:
	cmpwi r28, 0x0
	beq @2
	lfs f1, 0x28(r29)
	lfs f0, 0x28(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x28(r31)
	lfs f1, 0x2c(r29)
	lfs f0, 0x2c(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x2c(r31)
	lfs f1, 0x30(r29)
	lfs f0, 0x30(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x30(r31)
	b @3
	@2:
	lfs f0, 0x28(r30)
	stfs f0, 0x28(r31)
	lfs f0, 0x2c(r30)
	stfs f0, 0x2c(r31)
	lfs f0, 0x30(r30)
	stfs f0, 0x30(r31)
	@3:
	lfs f1, 0x34(r29)
	lfs f2, 0x3c(r29)
	bl atan2
	frsp f0, f1
	lfs f1, 0x34(r30)
	lfs f2, 0x3c(r30)
	fmr f30, f0
	bl atan2
	frsp f3, f1
	lfs f2, float_6p2832_80419574(r2)
	lfs f0, float_3p1416_80419578(r2)
	b @4
	@5:
	fsubs f30, f30, f2
	@4:
	fsubs f1, f30, f3
	fcmpo cr0, f1, f0
	bgt @5
	lfs f2, float_6p2832_80419574(r2)
	lfs f0, float_neg3p1416_8041957c(r2)
	b @6
	@7:
	fadds f30, f30, f2
	@6:
	fsubs f1, f30, f3
	fcmpo cr0, f1, f0
	blt @7
	fsubs f0, f3, f30
	fmadds f30, f31, f0, f30
	fmr f1, f30
	bl sin
	frsp f0, f1
	fmr f1, f30
	stfs f0, 0x34(r31)
	bl cos
	frsp f0, f1
	stfs f0, 0x3c(r31)
	lfs f1, 0x38(r29)
	lfs f0, 0x38(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x38(r31)
	lfs f1, 0x40(r29)
	lfs f0, 0x40(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x40(r31)
	lfs f1, 0x44(r29)
	lfs f0, 0x44(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x44(r31)
	lfs f1, 0x48(r29)
	lfs f0, 0x48(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x48(r31)
	lfs f1, 0x5c(r29)
	lfs f0, 0x5c(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x5c(r31)
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	psq_l f29, 0x28(r1), 0, 0
	lfd f29, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x54(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r27, 0x2c(r1)
	mr r28, r4
	lis r4, vec3_802c12d0@ha
	mr r27, r3
	mr r29, r5
	li r30, 0x0
	addi r31, r4, vec3_802c12d0@l
	lwz r0, 0x0(r28)
	cmpwi r0, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, 0x24(r27)
	lwz r0, 0x24(r28)
	cmplw r3, r0
	bne @3
	lwz r3, 0x4(r27)
	cmpwi r3, 0x1
	bne @4
	lwz r0, 0x4(r28)
	cmpwi r0, 0x0
	beq @3
	@4:
	cmpwi r3, 0x0
	bne @5
	lwz r0, 0x8(r28)
	cmpwi r0, 0x1
	beq @3
	@5:
	lfs f1, 0x4c(r28)
	lfs f0, 0x4c(r27)
	fctiwz f1, f1
	fctiwz f0, f0
	stfd f1, 0x10(r1)
	stfd f0, 0x18(r1)
	lwz r3, 0x14(r1)
	lwz r0, 0x1c(r1)
	subf r6, r3, r0
	srawi r3, r6, 31
	xor r0, r3, r6
	subf r0, r3, r0
	cmpwi r0, 0x1
	bgt @6
	li r3, 0x0
	b @2
	@6:
	lwz r5, 0x24(r27)
	srawi r3, r6, 31
	xor r0, r3, r6
	lwz r4, 0x40(r5)
	subf r0, r3, r0
	lwz r3, 0x44(r5)
	subf r4, r4, r3
	subi r3, r4, 0x1
	cmpw r0, r3
	blt @7
	li r3, 0x0
	b @2
	@7:
	srawi r3, r6, 31
	subi r4, r4, 0x2
	xor r0, r3, r6
	subf r0, r3, r0
	cmpw r0, r4
	blt @3
	ori r30, r30, 0x20
	@3:
	lwz r3, 0x24(r27)
	lwz r0, 0x24(r28)
	cmplw r3, r0
	beq @8
	ori r30, r30, 0x1
	@8:
	lwz r3, 0x4(r27)
	cmpwi r3, 0x1
	bne @9
	lwz r0, 0x4(r28)
	cmpwi r0, 0x0
	bne @9
	ori r30, r30, 0x2
	@9:
	cmpwi r3, 0x0
	bne @10
	lwz r0, 0x8(r28)
	cmpwi r0, 0x1
	bne @10
	ori r30, r30, 0x4
	@10:
	lfs f2, 0x4c(r27)
	lfs f1, 0x4c(r28)
	lfd f0, 0x30(r31)
	fsubs f1, f2, f1
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	mfcr r0
	extrwi. r0, r0, 1, 2
	bne @11
	ori r30, r30, 0x8
	@11:
	lfs f1, 0x3c(r27)
	lfs f0, 0x3c(r28)
	lfs f3, 0x34(r27)
	fmuls f1, f1, f0
	lfs f2, 0x34(r28)
	lfs f0, float_1_80419558(r2)
	fmadds f1, f3, f2, f1
	fcmpo cr0, f1, f0
	ble @12
	fmr f1, f0
	@12:
	bl acos
	frsp f2, f1
	lfs f1, float_rad2deg_80419580(r2)
	lfs f0, float_180_80419588(r2)
	fmuls f1, f1, f2
	fabs f3, f1
	fcmpo cr0, f3, f0
	ble @13
	lfs f0, float_360_80419584(r2)
	fsubs f3, f0, f3
	@13:
	lfs f1, float_6p2832_80419574(r2)
	lfs f0, 0x40(r27)
	lwz r3, wp(r13)
	fmuls f2, f1, f0
	lfs f4, float_360_80419584(r2)
	lfs f1, 0x44(r27)
	lfs f0, 0x44(r28)
	fmuls f3, f2, f3
	lfs f2, 0x1b4(r3)
	fsubs f0, f1, f0
	lfs f1, float_180_80419588(r2)
	fdivs f3, f3, f4
	fabs f5, f0
	fmuls f0, f3, f2
	fcmpo cr0, f5, f1
	ble @14
	fsubs f5, f4, f5
	@14:
	lfs f2, float_6p2832_80419574(r2)
	lfs f1, 0x40(r27)
	lwz r3, wp(r13)
	fmuls f3, f2, f1
	lfs f2, float_360_80419584(r2)
	lfs f1, 0x1b8(r3)
	fmuls f3, f3, f5
	fdivs f2, f3, f2
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble @15
	fmr f0, f2
	@15:
	lfs f3, 0x48(r27)
	lfs f2, 0x48(r28)
	lfs f1, float_180_80419588(r2)
	fsubs f2, f3, f2
	fabs f5, f2
	fcmpo cr0, f5, f1
	ble @16
	lfs f1, float_360_80419584(r2)
	fsubs f5, f1, f5
	@16:
	lfs f1, float_6p2832_80419574(r2)
	lfs f4, 0x40(r27)
	lwz r3, wp(r13)
	fmuls f3, f1, f4
	lfs f2, float_360_80419584(r2)
	lfs f1, 0x1bc(r3)
	fmuls f3, f3, f5
	fdivs f2, f3, f2
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble @17
	fmr f0, f2
	@17:
	lfs f1, 0x40(r28)
	lwz r3, wp(r13)
	fsubs f2, f4, f1
	lfs f1, 0x1c0(r3)
	fabs f2, f2
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble @18
	fmr f0, f2
	@18:
	lfs f4, 0x28(r27)
	lfs f3, 0x28(r28)
	lfs f2, 0x2c(r27)
	lfs f1, 0x2c(r28)
	fsubs f4, f4, f3
	lfs f3, 0x30(r27)
	fsubs f5, f2, f1
	lfs f2, 0x30(r28)
	fmuls f6, f4, f4
	lfs f1, float_0_8041954c(r2)
	fsubs f2, f3, f2
	fmuls f3, f5, f5
	fmuls f2, f2, f2
	fadds f6, f6, f3
	fadds f6, f6, f2
	fcmpu cr0, f6, f1
	beq @19
	fcmpo cr0, f6, f1
	ble @20
	frsqrte f2, f6
	lfd f4, 0x38(r31)
	lfd f3, 0x40(r31)
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f6, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f6, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f6, f1, f3
	fmul f1, f2, f1
	fmul f6, f6, f1
	frsp f6, f6
	b @21
	@20:
	lfd f1, 0x48(r31)
	fcmpo cr0, f6, f1
	bge @22
	lis r3, __float_nan@ha
	lfs f6, __float_nan@l(r3)
	b @21
	@22:
	stfs f6, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @23
	bge @24
	cmpwi r3, 0x0
	beq @25
	b @24
	@23:
	clrlwi. r0, r4, 9
	beq @26
	li r0, 0x1
	b @27
	@26:
	li r0, 0x2
	b @27
	@25:
	clrlwi. r0, r4, 9
	beq @28
	li r0, 0x5
	b @27
	@28:
	li r0, 0x3
	b @27
	@24:
	li r0, 0x4
	@27:
	cmpwi r0, 0x1
	bne @21
	lis r3, __float_nan@ha
	lfs f6, __float_nan@l(r3)
	b @21
	@19:
	fmr f6, f1
	@21:
	lfs f1, float_0p01_8041958c(r2)
	fcmpo cr0, f0, f1
	bge @29
	lfs f1, float_0p3_80419590(r2)
	fcmpo cr0, f6, f1
	bge @29
	li r3, 0x0
	b @2
	@29:
	lwz r3, wp(r13)
	lfs f1, 0x1c4(r3)
	fmuls f1, f6, f1
	fcmpo cr0, f1, f0
	ble @30
	fmr f0, f1
	@30:
	lfs f1, float_90_80419594(r2)
	fcmpo cr0, f0, f1
	ble @31
	fmr f0, f1
	@31:
	lfs f1, float_20_80419598(r2)
	fcmpo cr0, f0, f1
	bge @32
	fmr f0, f1
	@32:
	lfs f1, float_1_80419558(r2)
	cmplwi r30, 0x0
	fdivs f0, f1, f0
	stfs f0, 0x0(r29)
	bne @33
	ori r30, r30, 0x10
	@33:
	mr r3, r30
	@2:
	lmw r27, 0x2c(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
	nofralloc
	stwu r1, -0x330(r1)
	mflr r0
	stw r0, 0x334(r1)
	stfd f31, 0x320(r1)
	psq_st f31, 0x328(r1), 0, 0
	stfd f30, 0x310(r1)
	psq_st f30, 0x318(r1), 0, 0
	stfd f29, 0x300(r1)
	psq_st f29, 0x308(r1), 0, 0
	stfd f28, 0x2f0(r1)
	psq_st f28, 0x2f8(r1), 0, 0
	stfd f27, 0x2e0(r1)
	psq_st f27, 0x2e8(r1), 0, 0
	stfd f26, 0x2d0(r1)
	psq_st f26, 0x2d8(r1), 0, 0
	stfd f25, 0x2c0(r1)
	psq_st f25, 0x2c8(r1), 0, 0
	stfd f24, 0x2b0(r1)
	psq_st f24, 0x2b8(r1), 0, 0
	stfd f23, 0x2a0(r1)
	psq_st f23, 0x2a8(r1), 0, 0
	stfd f22, 0x290(r1)
	psq_st f22, 0x298(r1), 0, 0
	stfd f21, 0x280(r1)
	psq_st f21, 0x288(r1), 0, 0
	stfd f20, 0x270(r1)
	psq_st f20, 0x278(r1), 0, 0
	stfd f19, 0x260(r1)
	psq_st f19, 0x268(r1), 0, 0
	stfd f18, 0x250(r1)
	psq_st f18, 0x258(r1), 0, 0
	stfd f17, 0x240(r1)
	psq_st f17, 0x248(r1), 0, 0
	stfd f16, 0x230(r1)
	psq_st f16, 0x238(r1), 0, 0
	stfd f15, 0x220(r1)
	psq_st f15, 0x228(r1), 0, 0
	stfd f14, 0x210(r1)
	psq_st f14, 0x218(r1), 0, 0
	stmw r14, 0x1c8(r1)
	lwz r5, wp(r13)
	fmr f16, f1
	fmr f17, f2
	lis r6, vec3_802c12d0@ha
	lwz r5, 0x0(r5)
	fmr f18, f3
	fmr f19, f4
	fmr f20, f5
	fmr f21, f6
	addi r0, r6, vec3_802c12d0@l
	lwz r24, 0xec(r5)
	fmr f22, f7
	lfs f0, dat_8041959c(r2)
	stfs f16, 0x104(r1)
	mr r15, r3
	li r23, 0x0
	stfs f0, 0x10(r1)
	li r14, 0x0
	stw r4, 0x8(r1)
	stw r0, 0x1b8(r1)
	stfs f17, 0x108(r1)
	stfs f18, 0x10c(r1)
	stfs f19, 0xf8(r1)
	stfs f20, 0xfc(r1)
	stfs f21, 0x100(r1)
	b @1
	@2:
	lwz r3, 0xa8(r24)
	lwz r0, 0x1d0(r5)
	mulli r3, r3, 0x68
	lwz r4, 0xf0(r4)
	cmplwi r0, 0x65
	lwz r22, 0xac(r24)
	add r21, r4, r3
	bne @3
	lwz r0, 0x28(r24)
	cmplwi r0, 0x0
	bne @4
	@3:
	cmpwi r22, 0x0
	bne @5
	lfs f1, 0x8c(r24)
	fcmpo cr0, f1, f20
	bgt @4
	lfs f0, 0x10(r1)
	fcmpo cr0, f1, f0
	ble @4
	stfs f1, 0x10(r1)
	mr r23, r24
	b @4
	@5:
	lwz r28, 0xf8(r1)
	li r26, 0x0
	lwz r29, 0xfc(r1)
	lwz r30, 0x100(r1)
	b @6
	@7:
	lwz r4, wp(r13)
	li r17, 0x0
	lwz r3, 0x58(r21)
	lwz r6, 0x0(r4)
	lwz r0, 0x60(r21)
	mulli r4, r3, 0xc
	lwz r5, 0xfc(r6)
	lwz r3, 0xf4(r6)
	slwi r0, r0, 3
	lwz r19, 0x64(r21)
	add r20, r5, r4
	add r18, r3, r0
	b @8
	@9:
	lwz r3, wp(r13)
	li r25, 0x1
	lwz r0, 0x0(r18)
	lwz r3, 0x0(r3)
	lwz r4, 0x4(r18)
	slwi r0, r0, 2
	lwz r3, 0x100(r3)
	subi r31, r4, 0x1
	add r16, r3, r0
	addi r27, r16, 0x4
	b @10
	@11:
	lwz r0, 0x4(r27)
	addi r3, r1, 0x80
	addi r4, r1, 0x74
	addi r5, r1, 0x68
	mulli r0, r0, 0xc
	addi r6, r1, 0x5c
	addi r7, r1, 0x10
	add r9, r20, r0
	lwz r8, 0x0(r9)
	lwz r0, 0x4(r9)
	stw r8, 0x5c(r1)
	stw r0, 0x60(r1)
	lwz r0, 0x8(r9)
	stw r0, 0x64(r1)
	lwz r0, 0x0(r27)
	mulli r0, r0, 0xc
	add r9, r20, r0
	lwz r8, 0x0(r9)
	lwz r0, 0x4(r9)
	stw r8, 0x68(r1)
	stw r0, 0x6c(r1)
	lwz r0, 0x8(r9)
	stw r0, 0x70(r1)
	lwz r0, 0x0(r16)
	mulli r0, r0, 0xc
	add r9, r20, r0
	lwz r8, 0x0(r9)
	lwz r0, 0x4(r9)
	stw r8, 0x74(r1)
	stw r0, 0x78(r1)
	lwz r0, 0x8(r9)
	stw r0, 0x7c(r1)
	stw r28, 0x80(r1)
	stw r29, 0x84(r1)
	stw r30, 0x88(r1)
	bl collisionTri_simple
	cmpwi r3, 0x0
	beq @12
	mr r23, r24
	b @13
	@12:
	addi r27, r27, 0x4
	addi r25, r25, 0x1
	@10:
	cmpw r25, r31
	blt @11
	@13:
	addi r17, r17, 0x1
	addi r18, r18, 0x8
	@8:
	cmpw r17, r19
	blt @9
	addi r26, r26, 0x1
	addi r21, r21, 0x68
	@6:
	cmpw r26, r22
	blt @7
	@4:
	addi r14, r14, 0x1
	addi r24, r24, 0xb8
	@1:
	lwz r5, wp(r13)
	lwz r4, 0x0(r5)
	lwz r0, 0xc8(r4)
	cmpw r14, r0
	blt @2
	cmplwi r23, 0x0
	beq @14
	lfs f0, float_0_8041954c(r2)
	mr r4, r23
	lfs f1, float_neg1E06_804195a0(r2)
	addi r5, r1, 0x50
	lwz r8, 0x104(r1)
	addi r6, r1, 0x168
	lwz r7, 0x108(r1)
	li r3, 0x0
	lwz r0, 0x10c(r1)
	stfs f1, 0x170(r1)
	stfs f0, 0x180(r1)
	stfs f0, 0x184(r1)
	stfs f0, 0x188(r1)
	stw r8, 0x50(r1)
	stw r7, 0x54(r1)
	stw r0, 0x58(r1)
	bl collisionCurve
	cmpwi r3, 0x0
	bne @14
	li r23, 0x0
	@14:
	cmplwi r23, 0x0
	mr r14, r23
	bne @15
	lwz r3, 0x8(r1)
	lwz r0, 0x0(r3)
	cmpwi r0, 0x0
	beq @16
	lwz r14, 0x24(r3)
	b @17
	@16:
	li r14, 0x0
	@17:
	cmplwi r14, 0x0
	bne @18
	lwz r3, wp(r13)
	stfs f16, 0x1d4(r3)
	lwz r3, wp(r13)
	stfs f17, 0x1d8(r3)
	lwz r3, wp(r13)
	stfs f18, 0x1dc(r3)
	lwz r3, wp(r13)
	stfs f19, 0x1e0(r3)
	lwz r3, wp(r13)
	stfs f20, 0x1e4(r3)
	lwz r3, wp(r13)
	stfs f21, 0x1e8(r3)
	b @19
	@18:
	lwz r3, wp(r13)
	fmr f27, f16
	lwz r0, 0x1d0(r3)
	cmplwi r0, 0x65
	bne @20
	cmplwi r14, 0x0
	beq @20
	lwz r0, 0x20(r14)
	cmplwi r0, 0x0
	beq @20
	lfs f26, 0x24(r14)
	b @21
	@20:
	fmr f26, f17
	@21:
	lwz r3, 0x8(r1)
	fmr f25, f18
	li r16, 0x0
	lfs f0, 0x3c(r3)
	lfs f2, 0x34(r3)
	fneg f29, f0
	lfs f0, 0x44(r3)
	lfs f1, 0x38(r3)
	fneg f31, f2
	stfs f0, 0x1b0(r1)
	lfs f0, 0x48(r3)
	fneg f30, f1
	lfs f24, 0x40(r3)
	stfs f0, 0x1ac(r1)
	lfs f0, 0x4c(r3)
	stfs f0, 0x1a8(r1)
	b @22
	@15:
	lfs f1, 0x168(r1)
	lfs f0, float_0_8041954c(r2)
	fcmpo cr0, f1, f0
	bge @23
	stfs f0, 0x168(r1)
	@23:
	lfs f1, 0x168(r1)
	lfs f0, float_1_80419558(r2)
	fcmpo cr0, f1, f0
	ble @24
	stfs f0, 0x168(r1)
	@24:
	lwz r3, wp(r13)
	lfs f0, 0x64(r14)
	lwz r0, 0x1d0(r3)
	stfs f0, 0x1b0(r1)
	lfs f0, 0x70(r14)
	cmplwi r0, 0x65
	lfs f24, 0x58(r14)
	stfs f0, 0x1ac(r1)
	lfs f27, 0x174(r1)
	bne @25
	lwz r0, 0x20(r14)
	cmplwi r0, 0x0
	beq @25
	lfs f26, 0x24(r14)
	b @26
	@25:
	fmr f26, f17
	@26:
	lwz r3, 0x18c(r1)
	lis r0, 0x4330
	lfs f2, 0x180(r1)
	lfs f1, 0x188(r1)
	stw r0, 0x198(r1)
	xoris r0, r3, 0x8000
	lwz r3, 0x1b8(r1)
	fmuls f0, f2, f2
	fneg f31, f1
	stw r0, 0x19c(r1)
	lfd f3, 0x50(r3)
	fmr f29, f2
	lfd f1, 0x198(r1)
	fmadds f0, f31, f31, f0
	lfd f2, 0x48(r3)
	fsubs f1, f1, f3
	lfs f25, 0x17c(r1)
	fcmpu cr0, f2, f0
	lwz r16, 0x190(r1)
	stfs f1, 0x1a8(r1)
	lfs f30, 0x184(r1)
	beq @27
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f0, f1
	ble @28
	frsqrte f2, f0
	lfd f4, 0x38(r3)
	lfd f3, 0x40(r3)
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f0, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f0, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f0, f1, f3
	fmul f1, f2, f1
	fmul f0, f0, f1
	frsp f0, f0
	b @29
	@28:
	fcmpo cr0, f0, f2
	bge @30
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b @29
	@30:
	stfs f0, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
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
	lfs f0, __float_nan@l(r3)
	@29:
	fdivs f31, f31, f0
	lfs f30, float_0_8041954c(r2)
	fdivs f29, f29, f0
	@27:
	lfs f0, float_neg1_804195a4(r2)
	fmuls f31, f31, f0
	fmuls f30, f30, f0
	fmuls f29, f29, f0
	@22:
	lwz r0, 0xb4(r14)
	cmpwi r0, 0x0
	beq @37
	lwz r4, wp(r13)
	addi r5, r1, 0x44
	lwz r0, 0xb0(r14)
	addi r6, r1, 0x168
	lfs f0, dat_804195a8(r2)
	li r3, 0x1
	lwz r4, 0x0(r4)
	mulli r0, r0, 0x68
	stfs f0, 0xf0(r1)
	lwz r4, 0x104(r4)
	stfs f27, 0xec(r1)
	lfs f0, float_neg1E06_804195a0(r2)
	add r4, r4, r0
	stfs f25, 0xf4(r1)
	lwz r8, 0xec(r1)
	lwz r7, 0xf0(r1)
	lwz r0, 0xf4(r1)
	stfs f0, 0x170(r1)
	stw r8, 0x44(r1)
	stw r7, 0x48(r1)
	stw r0, 0x4c(r1)
	bl collisionCurve
	cmpwi r3, 0x0
	beq @37
	lwz r0, 0x190(r1)
	lfs f27, 0x174(r1)
	lfs f25, 0x17c(r1)
	or r16, r16, r0
	@37:
	cmplwi r14, 0x0
	beq @38
	lwz r3, wp(r13)
	lfs f0, float_0_8041954c(r2)
	lwz r3, 0x0(r3)
	lfs f1, float_0p5_8041956c(r2)
	fcmpu cr0, f22, f0
	lwz r3, 0xe8(r3)
	lfs f0, float_180_80419588(r2)
	lfs f2, 0x0(r3)
	lfs f3, float_3p1416_80419568(r2)
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	fmuls f23, f3, f0
	beq @38
	cmplwi r23, 0x0
	beq @38
	lwz r3, 0x8(r1)
	lwz r0, 0x0(r3)
	cmpwi r0, 0x0
	beq @38
	fmr f1, f23
	bl cos
	frsp f15, f1
	fmr f1, f23
	bl sin
	frsp f0, f1
	lwz r3, 0x104(r1)
	lwz r0, 0x10c(r1)
	fneg f28, f29
	stw r3, 0xe0(r1)
	mr r4, r14
	fmuls f0, f24, f0
	lwz r3, 0x8(r1)
	stw r0, 0xe8(r1)
	addi r5, r1, 0x38
	lfs f7, 0x58(r3)
	addi r6, r1, 0x13c
	fdivs f0, f0, f15
	lfs f1, float_640_804195ac(r2)
	lwz r0, 0x108(r1)
	li r16, 0x0
	lfs f2, float_480_804195b0(r2)
	li r3, 0x0
	fmuls f3, f1, f0
	lfs f0, float_0_8041954c(r2)
	lfs f1, float_neg1E06_804195a0(r2)
	lfs f6, float_1_80419558(r2)
	fdivs f5, f3, f2
	stfs f1, 0x144(r1)
	lfs f8, float_0p01_8041958c(r2)
	stw r0, 0xe4(r1)
	lfs f3, float_1E06_804195b4(r2)
	stfs f0, 0x15c(r1)
	fmuls f1, f6, f5
	stfs f3, 0xe4(r1)
	lfs f4, 0xe0(r1)
	lwz r0, 0xe4(r1)
	fmuls f1, f7, f1
	stfs f0, 0x158(r1)
	lfs f2, 0xe8(r1)
	stfs f0, 0x154(r1)
	fmuls f3, f8, f1
	stw r0, 0x3c(r1)
	fmuls f1, f3, f28
	fmuls f0, f3, f31
	fadds f1, f4, f1
	fadds f0, f2, f0
	stfs f1, 0xe0(r1)
	stfs f0, 0xe8(r1)
	lwz r7, 0xe0(r1)
	lwz r0, 0xe8(r1)
	stw r7, 0x38(r1)
	stw r0, 0x40(r1)
	bl collisionCurve
	cmpwi r3, 0x0
	beq @39
	lfs f1, 0x148(r1)
	li r16, 0x1
	lfs f0, 0x150(r1)
	stfs f1, 0xe0(r1)
	stfs f26, 0xe4(r1)
	stfs f0, 0xe8(r1)
	@39:
	lwz r0, 0xb4(r14)
	cmpwi r0, 0x0
	beq @40
	lwz r3, wp(r13)
	addi r5, r1, 0x2c
	lwz r0, 0xb0(r14)
	addi r6, r1, 0x13c
	lwz r4, 0x0(r3)
	li r3, 0x1
	mulli r0, r0, 0x68
	lfs f0, float_neg1E06_804195a0(r2)
	lwz r4, 0x104(r4)
	lwz r8, 0xe0(r1)
	lwz r7, 0xe4(r1)
	add r4, r4, r0
	lwz r0, 0xe8(r1)
	stfs f0, 0x144(r1)
	stw r8, 0x2c(r1)
	stw r7, 0x30(r1)
	stw r0, 0x34(r1)
	bl collisionCurve
	cmpwi r3, 0x0
	beq @40
	lfs f1, 0x148(r1)
	li r16, 0x1
	lfs f0, 0x150(r1)
	stfs f1, 0xe0(r1)
	stfs f26, 0xe4(r1)
	stfs f0, 0xe8(r1)
	@40:
	cmpwi r16, 0x0
	beq @41
	lfs f15, 0xe0(r1)
	lfs f14, 0xe8(r1)
	b @42
	@41:
	fmr f15, f27
	fmr f14, f25
	@42:
	fmr f1, f23
	bl cos
	frsp f0, f1
	fmr f1, f23
	stfs f0, 0x1b4(r1)
	bl sin
	frsp f0, f1
	lfs f1, float_0_8041954c(r2)
	lwz r3, 0x104(r1)
	mr r4, r14
	lwz r0, 0x10c(r1)
	addi r5, r1, 0x20
	fmuls f2, f24, f0
	lfs f0, 0x1b4(r1)
	stw r3, 0xd4(r1)
	addi r6, r1, 0x110
	lwz r7, 0x108(r1)
	li r17, 0x0
	fdivs f3, f2, f0
	lfs f4, float_640_804195ac(r2)
	lfs f0, float_neg1E06_804195a0(r2)
	li r16, 0x0
	lfs f2, float_480_804195b0(r2)
	li r3, 0x0
	fmuls f3, f4, f3
	lfs f6, float_1_80419558(r2)
	stfs f0, 0x118(r1)
	lfs f7, float_0p01_8041958c(r2)
	fdivs f5, f3, f2
	stw r0, 0xdc(r1)
	lfs f4, 0xd4(r1)
	stfs f1, 0x130(r1)
	lfs f2, 0xdc(r1)
	stfs f1, 0x12c(r1)
	fmuls f0, f6, f5
	stfs f1, 0x128(r1)
	lfs f3, float_1E06_804195b4(r2)
	stw r7, 0xd8(r1)
	fmuls f0, f22, f0
	stfs f3, 0xd8(r1)
	fmuls f0, f7, f0
	lwz r0, 0xd8(r1)
	stw r0, 0x24(r1)
	fmuls f1, f0, f28
	fmuls f0, f0, f31
	fadds f1, f4, f1
	fadds f0, f2, f0
	stfs f1, 0xd4(r1)
	stfs f0, 0xdc(r1)
	lwz r7, 0xd4(r1)
	lwz r0, 0xdc(r1)
	stw r7, 0x20(r1)
	stw r0, 0x28(r1)
	bl collisionCurve
	cmpwi r3, 0x0
	beq @43
	lfs f1, 0x11c(r1)
	li r17, 0x1
	lfs f0, 0x124(r1)
	lwz r16, 0x138(r1)
	stfs f1, 0xd4(r1)
	stfs f26, 0xd8(r1)
	stfs f0, 0xdc(r1)
	@43:
	lwz r0, 0xb4(r14)
	cmpwi r0, 0x0
	beq @44
	lwz r3, wp(r13)
	addi r5, r1, 0x14
	lwz r0, 0xb0(r14)
	addi r6, r1, 0x110
	lwz r4, 0x0(r3)
	li r3, 0x1
	mulli r0, r0, 0x68
	lfs f0, float_neg1E06_804195a0(r2)
	lwz r4, 0x104(r4)
	lwz r8, 0xd4(r1)
	lwz r7, 0xd8(r1)
	add r4, r4, r0
	lwz r0, 0xdc(r1)
	stfs f0, 0x118(r1)
	stw r8, 0x14(r1)
	stw r7, 0x18(r1)
	stw r0, 0x1c(r1)
	bl collisionCurve
	cmpwi r3, 0x0
	beq @44
	lfs f1, 0x11c(r1)
	li r17, 0x1
	lfs f0, 0x124(r1)
	lwz r0, 0x138(r1)
	stfs f1, 0xd4(r1)
	or r16, r16, r0
	stfs f0, 0xdc(r1)
	@44:
	cmpwi r17, 0x0
	beq @45
	lwz r0, 0x138(r1)
	lfs f2, 0xd4(r1)
	clrlwi. r0, r0, 31
	lfs f4, 0xdc(r1)
	bne @46
	lwz r3, 0x8(r1)
	lwz r0, 0x8(r3)
	clrlwi. r0, r0, 31
	beq @46
	lfs f0, float_0_8041954c(r2)
	lwz r3, wp(r13)
	stfs f0, 0x1ac(r3)
	@46:
	lwz r0, 0x138(r1)
	rlwinm. r0, r0, 0, 30, 30
	bne @47
	lwz r3, 0x8(r1)
	lwz r0, 0x8(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq @47
	lfs f0, float_0_8041954c(r2)
	lwz r3, wp(r13)
	stfs f0, 0x1b0(r3)
	b @47
	@45:
	fmr f2, f27
	fmr f4, f25
	@47:
	lwz r3, 0x8(r1)
	lfs f3, float_0_8041954c(r2)
	lfs f0, 0x28(r3)
	addi r3, r1, 0xc8
	lwz r4, 0x8(r1)
	fsubs f1, f15, f0
	stfs f3, 0xcc(r1)
	fsubs f0, f2, f0
	stfs f1, 0xc8(r1)
	lfs f2, 0x30(r4)
	fsubs f1, f14, f2
	stfs f0, 0xbc(r1)
	fsubs f0, f4, f2
	stfs f3, 0xc0(r1)
	stfs f1, 0xd0(r1)
	stfs f0, 0xc4(r1)
	bl PSVECMag
	fmr f14, f1
	addi r3, r1, 0xbc
	bl PSVECMag
	lwz r4, wp(r13)
	lwz r6, gp(r13)
	lwz r3, 0x8(r1)
	lfs f1, 0x19c(r4)
	lwz r4, 0x8(r1)
	lwz r5, 0x40(r6)
	lwz r3, 0x50(r3)
	lwz r4, 0x54(r4)
	lwz r6, 0x44(r6)
	bl getV60FPS
	lwz r4, wp(r13)
	fadds f14, f14, f1
	lwz r6, gp(r13)
	lwz r3, 0x8(r1)
	lfs f1, 0x1a0(r4)
	lwz r4, 0x8(r1)
	lwz r5, 0x40(r6)
	lwz r3, 0x50(r3)
	lwz r4, 0x54(r4)
	lwz r6, 0x44(r6)
	bl getV60FPS
	frsp f2, f31
	lwz r3, wp(r13)
	frsp f0, f28
	lfs f5, float_0_8041954c(r2)
	lfs f7, 0x1ac(r3)
	fabs f4, f2
	lfs f8, 0x1b0(r3)
	fabs f3, f0
	fneg f6, f2
	fmuls f23, f14, f7
	stfs f28, 0xb0(r1)
	fcmpo cr0, f4, f3
	fmuls f3, f1, f7
	stfs f31, 0xb8(r1)
	fmuls f1, f1, f8
	fmuls f14, f14, f8
	stfs f6, 0xa4(r1)
	stfs f3, 0x1a4(r1)
	stfs f1, 0x1a0(r1)
	stfs f0, 0xac(r1)
	stfs f5, 0xb4(r1)
	stfs f5, 0xa8(r1)
	stfs f5, 0x9c(r1)
	stfs f5, 0x90(r1)
	ble @48
	lfs f7, 0xc4(r1)
	fdivs f3, f0, f2
	lfs f4, 0xbc(r1)
	fdivs f5, f7, f2
	frsp f1, f6
	fnmsubs f4, f0, f5, f4
	fnmsubs f1, f0, f3, f1
	fdivs f5, f4, f1
	fnmsubs f0, f5, f0, f7
	fdivs f6, f0, f2
	b @49
	@48:
	frsp f6, f6
	lfs f7, 0xbc(r1)
	lfs f3, 0xc4(r1)
	fdivs f4, f7, f0
	fdivs f1, f6, f0
	fnmsubs f3, f2, f4, f3
	fnmsubs f1, f2, f1, f0
	fdivs f5, f3, f1
	fnmsubs f1, f5, f6, f7
	fdivs f6, f1, f0
	@49:
	lfs f1, 0xb0(r1)
	lfs f2, 0xb8(r1)
	lfs f0, 0xa4(r1)
	fmuls f4, f6, f1
	lfs f1, 0xac(r1)
	fmuls f3, f6, f2
	fmuls f2, f5, f0
	lfs f0, float_0_8041954c(r2)
	fmuls f1, f5, f1
	fcmpo cr0, f6, f0
	stfs f4, 0x98(r1)
	stfs f3, 0xa0(r1)
	stfs f2, 0x8c(r1)
	stfs f1, 0x94(r1)
	bge @50
	lfs f15, float_neg1_804195a4(r2)
	b @51
	@50:
	lfs f15, float_1_80419558(r2)
	@51:
	lfs f0, float_0_8041954c(r2)
	fcmpo cr0, f5, f0
	bge @52
	lfs f28, float_neg1_804195a4(r2)
	b @53
	@52:
	lfs f28, float_1_80419558(r2)
	@53:
	addi r3, r1, 0x98
	bl PSVECMag
	fmr f27, f1
	addi r3, r1, 0x8c
	bl PSVECMag
	fmr f25, f1
	fcmpo cr0, f27, f23
	ble @54
	lfs f0, 0x1a4(r1)
	fcmpo cr0, f27, f0
	ble @54
	fmuls f1, f23, f15
	addi r3, r1, 0xb0
	addi r4, r1, 0x98
	bl PSVECScale
	@54:
	fcmpo cr0, f25, f14
	ble @55
	lfs f0, 0x1a0(r1)
	fcmpo cr0, f25, f0
	ble @55
	fmuls f1, f14, f28
	addi r3, r1, 0xa4
	addi r4, r1, 0x8c
	bl PSVECScale
	@55:
	lfs f3, 0x98(r1)
	lwz r3, 0x8(r1)
	lfs f2, 0x8c(r1)
	lfs f1, 0xa0(r1)
	lfs f0, 0x94(r1)
	fadds f2, f3, f2
	lfs f27, 0x28(r3)
	fadds f0, f1, f0
	lfs f25, 0x30(r3)
	fadds f27, f27, f2
	fadds f25, f25, f0
	@38:
	lwz r3, wp(r13)
	lfs f0, float_1_80419558(r2)
	lfs f2, 0x1ac(r3)
	lfs f1, 0x1a4(r3)
	fadds f1, f2, f1
	stfs f1, 0x1ac(r3)
	lwz r3, wp(r13)
	lfs f1, 0x1ac(r3)
	fcmpo cr0, f1, f0
	ble @56
	stfs f0, 0x1ac(r3)
	@56:
	lwz r3, wp(r13)
	lfs f0, float_1_80419558(r2)
	lfs f2, 0x1b0(r3)
	lfs f1, 0x1a8(r3)
	fadds f1, f2, f1
	stfs f1, 0x1b0(r3)
	lwz r3, wp(r13)
	lfs f1, 0x1b0(r3)
	fcmpo cr0, f1, f0
	ble @57
	stfs f0, 0x1b0(r3)
	@57:
	neg r0, r23
	li r3, 0x1
	or r0, r0, r23
	stw r3, 0x0(r15)
	srwi r0, r0, 31
	fneg f2, f31
	stw r0, 0x4(r15)
	fneg f1, f30
	fneg f0, f29
	stw r16, 0x8(r15)
	stfs f16, 0xc(r15)
	stfs f17, 0x10(r15)
	stfs f18, 0x14(r15)
	stfs f19, 0x18(r15)
	stfs f20, 0x1c(r15)
	stfs f21, 0x20(r15)
	stw r14, 0x24(r15)
	stfs f27, 0x28(r15)
	stfs f26, 0x2c(r15)
	stfs f25, 0x30(r15)
	stfs f2, 0x34(r15)
	stfs f1, 0x38(r15)
	stfs f0, 0x3c(r15)
	lfs f0, 0x1b0(r1)
	stfs f24, 0x40(r15)
	stfs f0, 0x44(r15)
	lfs f0, 0x1ac(r1)
	stfs f0, 0x48(r15)
	lfs f0, 0x1a8(r1)
	stfs f0, 0x4c(r15)
	lwz r3, gp(r13)
	lwz r0, 0x40(r3)
	lwz r3, 0x44(r3)
	stw r3, 0x54(r15)
	stw r0, 0x50(r15)
	stfs f22, 0x58(r15)
	lfs f0, 0x7c(r14)
	stfs f0, 0x5c(r15)
	@19:
	psq_l f31, 0x328(r1), 0, 0
	lfd f31, 0x320(r1)
	psq_l f30, 0x318(r1), 0, 0
	lfd f30, 0x310(r1)
	psq_l f29, 0x308(r1), 0, 0
	lfd f29, 0x300(r1)
	psq_l f28, 0x2f8(r1), 0, 0
	lfd f28, 0x2f0(r1)
	psq_l f27, 0x2e8(r1), 0, 0
	lfd f27, 0x2e0(r1)
	psq_l f26, 0x2d8(r1), 0, 0
	lfd f26, 0x2d0(r1)
	psq_l f25, 0x2c8(r1), 0, 0
	lfd f25, 0x2c0(r1)
	psq_l f24, 0x2b8(r1), 0, 0
	lfd f24, 0x2b0(r1)
	psq_l f23, 0x2a8(r1), 0, 0
	lfd f23, 0x2a0(r1)
	psq_l f22, 0x298(r1), 0, 0
	lfd f22, 0x290(r1)
	psq_l f21, 0x288(r1), 0, 0
	lfd f21, 0x280(r1)
	psq_l f20, 0x278(r1), 0, 0
	lfd f20, 0x270(r1)
	psq_l f19, 0x268(r1), 0, 0
	lfd f19, 0x260(r1)
	psq_l f18, 0x258(r1), 0, 0
	lfd f18, 0x250(r1)
	psq_l f17, 0x248(r1), 0, 0
	lfd f17, 0x240(r1)
	psq_l f16, 0x238(r1), 0, 0
	lfd f16, 0x230(r1)
	psq_l f15, 0x228(r1), 0, 0
	lfd f15, 0x220(r1)
	psq_l f14, 0x218(r1), 0, 0
	lfd f14, 0x210(r1)
	lmw r14, 0x1c8(r1)
	lwz r0, 0x334(r1)
	mtlr r0
	addi r1, r1, 0x330
	blr
}

asm s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit) {
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
	stfd f20, 0xe0(r1)
	psq_st f20, 0xe8(r1), 0, 0
	stfd f19, 0xd0(r1)
	psq_st f19, 0xd8(r1), 0, 0
	stfd f18, 0xc0(r1)
	psq_st f18, 0xc8(r1), 0, 0
	stfd f17, 0xb0(r1)
	psq_st f17, 0xb8(r1), 0, 0
	stfd f16, 0xa0(r1)
	psq_st f16, 0xa8(r1), 0, 0
	stfd f15, 0x90(r1)
	psq_st f15, 0x98(r1), 0, 0
	stfd f14, 0x80(r1)
	psq_st f14, 0x88(r1), 0, 0
	stmw r15, 0x3c(r1)
	lfs f0, dat_804195a8(r2)
	cmpwi r3, 0x0
	lis r3, vec3_802c12d0@ha
	mr r16, r5
	stfs f0, 0x20(r1)
	mr r17, r6
	addi r31, r3, vec3_802c12d0@l
	li r24, 0x0
	bne @1
	lwz r5, 0xa4(r4)
	li r19, 0x0
	lwz r3, wp(r13)
	srwi r0, r5, 31
	lwz r6, 0xa0(r4)
	add r0, r0, r5
	lwz r5, 0x0(r3)
	srawi r3, r0, 1
	lfs f27, 0x48(r4)
	add r0, r6, r3
	lwz r7, 0xf8(r5)
	mulli r5, r6, 0xc
	lfs f26, 0x4c(r4)
	lwz r22, 0x40(r4)
	lwz r21, 0x44(r4)
	mulli r0, r0, 0xc
	lwz r20, 0x84(r4)
	add r6, r7, r5
	add r7, r7, r0
	b @2
	@1:
	lwz r3, 0x64(r4)
	li r22, 0x0
	lwz r5, wp(r13)
	li r21, 0x1
	srwi r0, r3, 31
	lwz r4, 0x60(r4)
	add r0, r0, r3
	lfs f27, float_0_8041954c(r2)
	srawi r3, r0, 1
	lwz r5, 0x0(r5)
	add r0, r4, r3
	fmr f26, f27
	mulli r4, r4, 0xc
	lwz r5, 0xf8(r5)
	li r20, 0x0
	li r19, 0x1
	mulli r0, r0, 0xc
	add r6, r5, r4
	add r7, r5, r0
	@2:
	mulli r0, r22, 0xc
	lfd f2, 0x58(r31)
	add r4, r7, r0
	lfs f0, 0x4(r4)
	mulli r5, r21, 0xc
	stfs f0, 0x28(r1)
	add r4, r7, r5
	lfs f0, 0x4(r4)
	frsp f1, f0
	stfs f0, 0x24(r1)
	lfs f0, 0x28(r1)
	fsubs f0, f1, f0
	fabs f0, f0
	fcmpo cr0, f0, f2
	bge @3
	lfs f0, 0x24(r1)
	stfs f0, 0x28(r1)
	@3:
	cmpwi r19, 0x0
	beq @4
	li r20, 0x0
	@4:
	lfs f0, float_0_8041954c(r2)
	mr r30, r6
	mr r29, r7
	add r28, r7, r0
	stfd f0, 0x30(r1)
	add r27, r6, r0
	add r26, r7, r5
	add r25, r6, r5
	subi r15, r3, 0x1
	li r23, 0x0
	b @5
	@6:
	lfs f23, 0x8(r30)
	li r18, 0x0
	lfs f3, 0x8(r16)
	lfs f1, 0xc(r29)
	fsubs f0, f3, f23
	lfs f5, 0x8(r29)
	lfs f25, 0x0(r30)
	fneg f7, f1
	lfs f4, 0x0(r16)
	fmuls f0, f5, f0
	fsubs f1, f4, f25
	lfs f6, 0x0(r29)
	lfs f2, 0x14(r29)
	lfs f24, 0x4(r30)
	fmadds f1, f6, f1, f0
	lfd f0, 0x30(r1)
	fneg f8, f2
	lfs f22, 0xc(r30)
	lfs f21, 0x14(r30)
	fcmpo cr0, f1, f0
	blt @7
	fsubs f0, f3, f21
	fsubs f1, f4, f22
	fmuls f0, f8, f0
	fmadds f1, f7, f1, f0
	lfd f0, 0x30(r1)
	fcmpo cr0, f1, f0
	blt @7
	fneg f2, f5
	lfd f1, 0x60(r31)
	fmr f3, f6
	fmr f4, f8
	fsubs f0, f2, f8
	fneg f5, f7
	fabs f0, f0
	fcmpo cr0, f0, f1
	bge @8
	fsubs f0, f6, f5
	fabs f0, f0
	fcmpo cr0, f0, f1
	bge @8
	fadds f1, f2, f8
	lfs f2, float_0p5_8041956c(r2)
	fadds f0, f6, f5
	fmuls f4, f2, f1
	fmuls f5, f2, f0
	fmr f2, f4
	fmr f3, f5
	@8:
	fcmpu cr0, f2, f4
	bne @9
	fcmpu cr0, f3, f5
	beq @10
	@9:
	lfd f0, 0x48(r31)
	lfs f29, float_1_80419558(r2)
	fcmpu cr0, f0, f4
	stfs f29, 0x18(r1)
	beq @11
	fsubs f1, f25, f22
	fdivs f0, f2, f4
	fdivs f1, f1, f4
	fmadds f1, f5, f1, f21
	fnmsubs f0, f5, f0, f3
	fsubs f1, f1, f23
	fdivs f0, f1, f0
	b @12
	@11:
	fcmpu cr0, f0, f5
	beq @13
	fsubs f1, f23, f21
	fdivs f0, f3, f5
	fdivs f1, f1, f5
	fmadds f1, f4, f1, f22
	fnmsubs f0, f4, f0, f2
	fsubs f1, f1, f25
	fdivs f0, f1, f0
	b @12
	@13:
	lfs f0, float_0_8041954c(r2)
	@12:
	fmadds f20, f0, f3, f23
	lfd f1, 0x48(r31)
	fmadds f0, f0, f2, f25
	fsubs f15, f23, f20
	stfs f0, 0x1c(r1)
	frsp f0, f0
	fsubs f16, f25, f0
	fmuls f0, f15, f15
	fmadds f19, f16, f16, f0
	fcmpu cr0, f1, f19
	beq @14
	lfs f0, float_0_8041954c(r2)
	fcmpo cr0, f19, f0
	ble @15
	frsqrte f1, f19
	lfd f3, 0x38(r31)
	lfd f2, 0x40(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f19, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f19, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f19, f0, f2
	fmul f0, f1, f0
	fmul f0, f19, f0
	frsp f0, f0
	b @16
	@15:
	fcmpo cr0, f19, f1
	bge @17
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b @16
	@17:
	stfs f19, 0x14(r1)
	lis r0, 0x7f80
	lwz r4, 0x14(r1)
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
	bne @24
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b @16
	@24:
	fmr f0, f19
	@16:
	fmr f19, f0
	@14:
	lfs f0, 0x8(r16)
	lfs f2, 0x0(r16)
	fsubs f30, f0, f20
	lfs f0, 0x1c(r1)
	lfd f1, 0x48(r31)
	fsubs f31, f2, f0
	fmuls f0, f30, f30
	fmadds f17, f31, f31, f0
	fcmpu cr0, f1, f17
	beq @25
	lfs f0, float_0_8041954c(r2)
	fcmpo cr0, f17, f0
	ble @26
	frsqrte f1, f17
	lfd f3, 0x38(r31)
	lfd f2, 0x40(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f17, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f17, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f17, f0, f2
	fmul f0, f1, f0
	fmul f0, f17, f0
	frsp f0, f0
	b @27
	@26:
	fcmpo cr0, f17, f1
	bge @28
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b @27
	@28:
	stfs f17, 0x10(r1)
	lis r0, 0x7f80
	lwz r4, 0x10(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @29
	bge @30
	cmpwi r3, 0x0
	beq @31
	b @30
	@29:
	clrlwi. r0, r4, 9
	beq @32
	li r0, 0x1
	b @33
	@32:
	li r0, 0x2
	b @33
	@31:
	clrlwi. r0, r4, 9
	beq @34
	li r0, 0x5
	b @33
	@34:
	li r0, 0x3
	b @33
	@30:
	li r0, 0x4
	@33:
	cmpwi r0, 0x1
	bne @35
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b @27
	@35:
	fmr f0, f17
	@27:
	fmr f17, f0
	@25:
	fsubs f1, f21, f20
	lfs f0, 0x1c(r1)
	lfd f3, 0x48(r31)
	fsubs f0, f22, f0
	fmuls f2, f1, f1
	fmadds f18, f0, f0, f2
	fcmpu cr0, f3, f18
	beq @36
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f18, f2
	ble @37
	frsqrte f3, f18
	lfd f5, 0x38(r31)
	lfd f4, 0x40(r31)
	fmul f2, f3, f3
	fmul f3, f5, f3
	fnmsub f2, f18, f2, f4
	fmul f3, f3, f2
	fmul f2, f3, f3
	fmul f3, f5, f3
	fnmsub f2, f18, f2, f4
	fmul f3, f3, f2
	fmul f2, f3, f3
	fmul f3, f5, f3
	fnmsub f2, f18, f2, f4
	fmul f2, f3, f2
	fmul f2, f18, f2
	frsp f2, f2
	b @38
	@37:
	fcmpo cr0, f18, f3
	bge @39
	lis r3, __float_nan@ha
	lfs f2, __float_nan@l(r3)
	b @38
	@39:
	stfs f18, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @40
	bge @41
	cmpwi r3, 0x0
	beq @42
	b @41
	@40:
	clrlwi. r0, r4, 9
	beq @43
	li r0, 0x1
	b @44
	@43:
	li r0, 0x2
	b @44
	@42:
	clrlwi. r0, r4, 9
	beq @45
	li r0, 0x5
	b @44
	@45:
	li r0, 0x3
	b @44
	@41:
	li r0, 0x4
	@44:
	cmpwi r0, 0x1
	bne @46
	lis r3, __float_nan@ha
	lfs f2, __float_nan@l(r3)
	b @38
	@46:
	fmr f2, f18
	@38:
	fmr f18, f2
	@36:
	fmuls f3, f15, f30
	lfs f2, float_neg1_804195a4(r2)
	fmuls f1, f1, f30
	fmuls f4, f19, f17
	fmadds f5, f16, f31, f3
	fmadds f3, f0, f31, f1
	fmuls f0, f18, f17
	fdivs f1, f5, f4
	fdivs f14, f3, f0
	fcmpo cr0, f1, f2
	bge @47
	fmr f1, f2
	b @48
	@47:
	lfs f0, float_1_80419558(r2)
	fcmpo cr0, f1, f0
	ble @48
	fmr f1, f0
	@48:
	lfs f0, float_neg1_804195a4(r2)
	fcmpo cr0, f14, f0
	bge @49
	fmr f14, f0
	b @50
	@49:
	lfs f0, float_1_80419558(r2)
	fcmpo cr0, f14, f0
	ble @50
	fmr f14, f0
	@50:
	bl acos
	frsp f0, f1
	fmr f1, f14
	stfs f0, 0x2c(r1)
	bl acos
	frsp f3, f1
	lfs f0, 0x2c(r1)
	fsubs f4, f17, f19
	lfs f1, float_0_8041954c(r2)
	fsubs f2, f17, f18
	fadds f3, f0, f3
	fsubs f2, f2, f4
	fdivs f5, f0, f3
	fmadds f0, f5, f2, f4
	fcmpo cr0, f0, f1
	bge @51
	lfs f29, float_neg1_804195a4(r2)
	fneg f0, f0
	@51:
	lfs f1, 0x20(r1)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	beq @7
	fsubs f3, f21, f23
	lfs f4, 0x4(r29)
	fsubs f2, f22, f25
	lfs f1, 0x10(r29)
	cmpwi r20, 0x0
	stfs f0, 0x20(r1)
	fsubs f1, f1, f4
	fneg f3, f3
	fmuls f2, f15, f2
	fmadds f1, f5, f1, f4
	fmadds f3, f16, f3, f2
	beq @52
	lfs f2, 0x28(r1)
	fcmpo cr0, f1, f2
	bge @53
	lfd f1, 0x48(r31)
	fcmpo cr0, f3, f1
	ble @54
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge @55
	fcmpo cr0, f0, f27
	ble @56
	fmr f0, f27
	ori r18, r18, 0x2
	b @56
	@55:
	fcmpo cr0, f0, f26
	ble @57
	fmr f0, f26
	ori r18, r18, 0x2
	@57:
	fneg f0, f0
	b @56
	@54:
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge @58
	fcmpo cr0, f0, f26
	ble @59
	fmr f0, f26
	ori r18, r18, 0x2
	@59:
	fneg f0, f0
	b @56
	@58:
	fcmpo cr0, f0, f27
	ble @56
	fmr f0, f27
	ori r18, r18, 0x2
	@56:
	lfs f1, 0x28(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f1, 0x0(r17)
	lfs f2, 0x8(r28)
	lfs f1, 0x0(r27)
	fmadds f1, f0, f2, f1
	stfs f1, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r28)
	lfs f1, 0x8(r27)
	fnmsubs f0, f0, f2, f1
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r28)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r28)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r22, 0x24(r17)
	stw r0, 0x28(r17)
	b @7
	@53:
	lfs f2, 0x24(r1)
	fcmpo cr0, f1, f2
	ble @60
	lfd f1, 0x48(r31)
	fcmpo cr0, f3, f1
	ble @61
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge @62
	fcmpo cr0, f0, f27
	ble @63
	fmr f0, f27
	ori r18, r18, 0x2
	b @63
	@62:
	fcmpo cr0, f0, f26
	ble @64
	fmr f0, f26
	ori r18, r18, 0x2
	@64:
	fneg f0, f0
	b @63
	@61:
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge @65
	fcmpo cr0, f0, f26
	ble @66
	fmr f0, f26
	ori r18, r18, 0x2
	@66:
	fneg f0, f0
	b @63
	@65:
	fcmpo cr0, f0, f27
	ble @63
	fmr f0, f27
	ori r18, r18, 0x2
	@63:
	lfs f1, 0x24(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f1, 0x0(r17)
	lfs f2, 0x8(r26)
	lfs f1, 0x0(r25)
	fmadds f1, f0, f2, f1
	stfs f1, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r26)
	lfs f1, 0x8(r25)
	fnmsubs f0, f0, f2, f1
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r26)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r26)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r21, 0x24(r17)
	stw r0, 0x28(r17)
	b @7
	@60:
	lfd f2, 0x48(r31)
	fcmpo cr0, f3, f2
	ble @67
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	bge @68
	fcmpo cr0, f0, f27
	ble @69
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f27
	fadds f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b @69
	@68:
	fcmpo cr0, f0, f26
	ble @69
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f26
	fsubs f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b @69
	@67:
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	bge @70
	fcmpo cr0, f0, f26
	ble @71
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f26
	fadds f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b @71
	@70:
	fcmpo cr0, f0, f27
	ble @71
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f27
	fsubs f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	@71:
	lfs f0, float_neg1_804195a4(r2)
	stfs f0, 0x18(r1)
	b @69
	@52:
	cmpwi r19, 0x0
	beq @72
	lfd f2, 0x48(r31)
	fcmpo cr0, f3, f2
	ble @73
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	blt @69
	fcmpo cr0, f0, f2
	ble @69
	fdivs f31, f31, f17
	li r18, 0x3
	fdivs f30, f30, f17
	fsubs f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b @69
	@73:
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	bge @74
	fcmpo cr0, f0, f2
	ble @74
	fdivs f31, f31, f17
	li r18, 0x3
	fdivs f30, f30, f17
	fadds f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	@74:
	lfs f0, float_neg1_804195a4(r2)
	stfs f0, 0x18(r1)
	b @69
	@72:
	lfd f0, 0x48(r31)
	fcmpo cr0, f3, f0
	bgt @69
	lfs f0, float_neg1_804195a4(r2)
	stfs f0, 0x18(r1)
	@69:
	lfs f0, 0x1c(r1)
	fadds f2, f20, f30
	lfs f3, float_0_8041954c(r2)
	fadds f4, f0, f31
	lfs f0, 0x18(r1)
	fcmpo cr0, f0, f3
	stfs f4, 0xc(r17)
	stfs f3, 0x10(r17)
	stfs f2, 0x14(r17)
	bge @75
	fneg f2, f30
	fdivs f0, f31, f17
	fdivs f2, f2, f17
	stfs f2, 0x18(r17)
	stfs f3, 0x1c(r17)
	stfs f0, 0x20(r17)
	b @76
	@75:
	fdivs f2, f30, f17
	fneg f0, f31
	stfs f2, 0x18(r17)
	stfs f3, 0x1c(r17)
	fdivs f0, f0, f17
	stfs f0, 0x20(r17)
	@76:
	stfs f1, 0x0(r17)
	li r24, 0x1
	stfs f24, 0x8(r17)
	stw r23, 0x24(r17)
	stw r18, 0x28(r17)
	b @7
	@10:
	lfs f0, 0x8(r30)
	lfs f1, 0x14(r30)
	lfs f10, 0x0(r30)
	fsubs f6, f1, f0
	lfs f2, 0xc(r30)
	lfs f1, 0x0(r16)
	fsubs f5, f2, f10
	lfs f2, 0x8(r16)
	fneg f7, f6
	fabs f3, f5
	fabs f4, f7
	fcmpo cr0, f4, f3
	ble @77
	fsubs f4, f10, f1
	fdivs f3, f5, f7
	fdivs f4, f4, f7
	fmadds f4, f5, f4, f2
	fnmsubs f3, f5, f3, f6
	fsubs f4, f4, f0
	fdivs f4, f4, f3
	b @78
	@77:
	lfd f3, 0x48(r31)
	fcmpu cr0, f3, f5
	beq @79
	fsubs f4, f0, f2
	fdivs f3, f6, f5
	fdivs f4, f4, f5
	fmadds f4, f7, f4, f1
	fnmsubs f3, f7, f3, f5
	fsubs f4, f4, f10
	fdivs f4, f4, f3
	b @78
	@79:
	lfs f4, float_0_8041954c(r2)
	@78:
	fabs f9, f5
	fabs f8, f6
	fmadds f3, f4, f5, f10
	fmadds f4, f4, f6, f0
	fcmpo cr0, f9, f8
	ble @80
	fsubs f6, f3, f10
	lfd f0, 0x68(r31)
	fdivs f28, f6, f5
	fcmpo cr0, f28, f0
	blt @81
	b @81
	@80:
	lfd f8, 0x48(r31)
	fcmpu cr0, f8, f6
	beq @81
	fsubs f0, f4, f0
	fdivs f28, f0, f6
	@81:
	fsubs f6, f2, f4
	lfs f10, 0x4(r29)
	lfs f8, 0x10(r29)
	fsubs f2, f1, f3
	lfd f9, 0x48(r31)
	fmuls f0, f6, f6
	fsubs f8, f8, f10
	fmadds f1, f2, f2, f0
	fmadds f0, f28, f8, f10
	fcmpo cr0, f1, f9
	ble @82
	lfs f8, float_0_8041954c(r2)
	fcmpo cr0, f1, f8
	ble @83
	frsqrte f9, f1
	lfd f11, 0x38(r31)
	lfd f10, 0x40(r31)
	fmul f8, f9, f9
	fmul f9, f11, f9
	fnmsub f8, f1, f8, f10
	fmul f9, f9, f8
	fmul f8, f9, f9
	fmul f9, f11, f9
	fnmsub f8, f1, f8, f10
	fmul f9, f9, f8
	fmul f8, f9, f9
	fmul f9, f11, f9
	fnmsub f8, f1, f8, f10
	fmul f8, f9, f8
	fmul f1, f1, f8
	frsp f1, f1
	b @82
	@83:
	fcmpo cr0, f1, f9
	bge @84
	lis r3, __float_nan@ha
	lfs f1, __float_nan@l(r3)
	b @82
	@84:
	stfs f1, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @85
	bge @86
	cmpwi r3, 0x0
	beq @87
	b @86
	@85:
	clrlwi. r0, r4, 9
	beq @88
	li r0, 0x1
	b @89
	@88:
	li r0, 0x2
	b @89
	@87:
	clrlwi. r0, r4, 9
	beq @90
	li r0, 0x5
	b @89
	@90:
	li r0, 0x3
	b @89
	@86:
	li r0, 0x4
	@89:
	cmpwi r0, 0x1
	bne @82
	lis r3, __float_nan@ha
	lfs f1, __float_nan@l(r3)
	@82:
	lfs f8, 0x20(r1)
	fcmpo cr0, f1, f8
	cror eq, gt, eq
	beq @7
	cmpwi r20, 0x0
	stfs f1, 0x20(r1)
	beq @91
	lfs f8, 0x28(r1)
	fcmpo cr0, f0, f8
	bge @92
	fmuls f3, f6, f5
	lfs f0, float_0_8041954c(r2)
	fmadds f2, f2, f7, f3
	fcmpo cr0, f2, f0
	bge @93
	fcmpo cr0, f1, f27
	ble @94
	fmr f1, f27
	ori r18, r18, 0x2
	b @94
	@93:
	fcmpo cr0, f1, f26
	ble @95
	fmr f1, f26
	ori r18, r18, 0x2
	@95:
	fneg f1, f1
	@94:
	lfs f0, 0x28(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f0, 0x0(r17)
	lfs f2, 0x8(r28)
	lfs f0, 0x0(r27)
	fmadds f0, f1, f2, f0
	stfs f0, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r28)
	lfs f0, 0x8(r27)
	fnmsubs f0, f1, f2, f0
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r28)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r28)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r22, 0x24(r17)
	stw r0, 0x28(r17)
	b @7
	@92:
	lfs f8, 0x24(r1)
	fcmpo cr0, f0, f8
	ble @96
	fmuls f3, f6, f5
	lfs f0, float_0_8041954c(r2)
	fmadds f2, f2, f7, f3
	fcmpo cr0, f2, f0
	bge @97
	fcmpo cr0, f1, f27
	ble @98
	fmr f1, f27
	ori r18, r18, 0x2
	b @98
	@97:
	fcmpo cr0, f1, f26
	ble @99
	fmr f1, f26
	ori r18, r18, 0x2
	@99:
	fneg f1, f1
	@98:
	lfs f0, 0x24(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f0, 0x0(r17)
	lfs f2, 0x8(r26)
	lfs f0, 0x0(r25)
	fmadds f0, f1, f2, f0
	stfs f0, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r26)
	lfs f0, 0x8(r25)
	fnmsubs f0, f1, f2, f0
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r26)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r26)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r21, 0x24(r17)
	stw r0, 0x28(r17)
	b @7
	@96:
	fmuls f8, f6, f5
	lfs f5, float_0_8041954c(r2)
	fmadds f7, f2, f7, f8
	fcmpo cr0, f7, f5
	bge @100
	fcmpo cr0, f1, f27
	ble @91
	fdivs f2, f2, f1
	ori r18, r18, 0x2
	fdivs f1, f6, f1
	fmuls f2, f27, f2
	fmuls f6, f27, f1
	b @91
	@100:
	fcmpo cr0, f1, f26
	ble @91
	fdivs f2, f2, f1
	ori r18, r18, 0x2
	fdivs f1, f6, f1
	fmuls f2, f26, f2
	fmuls f6, f26, f1
	@91:
	fadds f2, f3, f2
	stfs f0, 0x0(r17)
	lfs f1, float_0_8041954c(r2)
	fadds f0, f4, f6
	li r24, 0x1
	stfs f2, 0xc(r17)
	stfs f1, 0x10(r17)
	stfs f0, 0x14(r17)
	lfs f2, 0x0(r29)
	lfs f0, 0xc(r29)
	fsubs f0, f0, f2
	fmadds f0, f28, f0, f2
	stfs f0, 0x18(r17)
	stfs f1, 0x1c(r17)
	lfs f1, 0x8(r29)
	lfs f0, 0x14(r29)
	fsubs f0, f0, f1
	fmadds f0, f28, f0, f1
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r23, 0x24(r17)
	stw r18, 0x28(r17)
	@7:
	addi r30, r30, 0xc
	addi r29, r29, 0xc
	addi r23, r23, 0x1
	@5:
	cmpw r23, r15
	blt @6
	mr r3, r24
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
	psq_l f20, 0xe8(r1), 0, 0
	lfd f20, 0xe0(r1)
	psq_l f19, 0xd8(r1), 0, 0
	lfd f19, 0xd0(r1)
	psq_l f18, 0xc8(r1), 0, 0
	lfd f18, 0xc0(r1)
	psq_l f17, 0xb8(r1), 0, 0
	lfd f17, 0xb0(r1)
	psq_l f16, 0xa8(r1), 0, 0
	lfd f16, 0xa0(r1)
	psq_l f15, 0x98(r1), 0, 0
	lfd f15, 0x90(r1)
	psq_l f14, 0x88(r1), 0, 0
	lfd f14, 0x80(r1)
	lmw r15, 0x3c(r1)
	lwz r0, 0x1a4(r1)
	mtlr r0
	addi r1, r1, 0x1a0
	blr
}

asm s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist) {
	nofralloc
	stwu r1, -0x410(r1)
	lis r8, vec3_802c12f4@ha
	lwz r10, 0x0(r5)
	stmw r26, 0x3f8(r1)
	addi r28, r8, vec3_802c12f4@l
	lwz r29, 0x0(r4)
	lwz r31, 0x4(r4)
	lwz r9, 0x4(r5)
	lwz r30, 0x8(r4)
	lwz r8, 0x8(r5)
	lwz r12, 0x0(r6)
	stw r10, 0x398(r1)
	lwz r11, 0x4(r6)
	lwz r6, 0x8(r6)
	stw r29, 0x3a4(r1)
	lfs f0, 0x398(r1)
	lfs f1, 0x3a4(r1)
	stw r12, 0x3bc(r1)
	fsubs f7, f1, f0
	lwz r26, 0x0(r28)
	stw r9, 0x39c(r1)
	lfs f4, 0x3bc(r1)
	stw r31, 0x3a8(r1)
	lfs f0, 0x39c(r1)
	lwz r27, 0x4(r28)
	lfs f1, 0x3a8(r1)
	stw r31, 0x3b4(r1)
	fsubs f6, f1, f0
	lwz r28, 0x8(r28)
	stw r8, 0x3a0(r1)
	lfs f2, 0x3b4(r1)
	stw r30, 0x3ac(r1)
	lfs f0, 0x3a0(r1)
	lfs f1, 0x3ac(r1)
	stw r11, 0x3c0(r1)
	fsubs f5, f1, f0
	stw r29, 0x3b0(r1)
	lfs f3, 0x3c0(r1)
	lfs f1, 0x3b0(r1)
	stw r30, 0x3b8(r1)
	fsubs f9, f3, f2
	fsubs f10, f4, f1
	stw r6, 0x3c4(r1)
	lfs f0, 0x3b8(r1)
	lfs f1, 0x3c4(r1)
	stw r10, 0x38c(r1)
	fsubs f8, f1, f0
	stw r12, 0x380(r1)
	lfs f4, 0x38c(r1)
	stw r11, 0x384(r1)
	lfs f1, 0x380(r1)
	stw r6, 0x388(r1)
	fsubs f4, f4, f1
	lfs f2, 0x384(r1)
	stw r9, 0x390(r1)
	lfs f0, 0x388(r1)
	stw r8, 0x394(r1)
	lfs f3, 0x390(r1)
	lfs f1, 0x394(r1)
	stfs f7, 0x104(r1)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	stfs f6, 0x108(r1)
	lwz r5, 0x104(r1)
	stfs f5, 0x10c(r1)
	lwz r4, 0x108(r1)
	lwz r0, 0x10c(r1)
	stw r26, 0x3e0(r1)
	stw r27, 0x3e4(r1)
	stw r28, 0x3e8(r1)
	stw r29, 0x2c(r1)
	stw r31, 0x30(r1)
	stw r30, 0x34(r1)
	stw r12, 0x20(r1)
	stw r11, 0x24(r1)
	stw r6, 0x28(r1)
	stfs f10, 0x110(r1)
	stfs f9, 0x114(r1)
	stfs f8, 0x118(r1)
	stw r10, 0x14(r1)
	stw r9, 0x18(r1)
	stw r8, 0x1c(r1)
	stfs f4, 0xf8(r1)
	stfs f2, 0xfc(r1)
	stfs f0, 0x100(r1)
	stw r5, 0x368(r1)
	stw r4, 0x36c(r1)
	stw r0, 0x370(r1)
	lwz r0, 0x118(r1)
	lwz r4, 0x114(r1)
	stw r0, 0x37c(r1)
	lwz r0, 0x110(r1)
	lfs f6, 0x37c(r1)
	lfs f7, 0x36c(r1)
	stw r4, 0x378(r1)
	fmuls f0, f6, f7
	lfs f3, 0x370(r1)
	stw r0, 0x374(r1)
	lfs f1, 0x378(r1)
	lfs f4, 0x368(r1)
	fmsubs f5, f1, f3, f0
	lfs f2, 0x374(r1)
	fmuls f0, f1, f4
	lfs f1, float_0_8041954c(r2)
	fmuls f3, f2, f3
	stfs f5, 0xec(r1)
	fmsubs f2, f2, f7, f0
	fmsubs f0, f6, f4, f3
	lwz r0, 0xec(r1)
	stw r0, 0x3d4(r1)
	stfs f0, 0xf0(r1)
	lfs f0, 0x3d4(r1)
	stfs f2, 0xf4(r1)
	lwz r4, 0xf0(r1)
	fcmpu cr0, f1, f0
	lwz r0, 0xf4(r1)
	stw r4, 0x3d8(r1)
	stw r0, 0x3dc(r1)
	bne @1
	lfs f0, 0x3d8(r1)
	fcmpu cr0, f1, f0
	bne @1
	lfs f0, 0x3dc(r1)
	fcmpu cr0, f1, f0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r6, 0x4(r3)
	lwz r10, 0x30(r1)
	stw r6, 0x348(r1)
	lwz r8, 0x0(r3)
	stw r10, 0x33c(r1)
	lwz r11, 0x2c(r1)
	lwz r5, 0x8(r3)
	stw r11, 0x338(r1)
	lwz r9, 0x34(r1)
	stw r8, 0x344(r1)
	lfs f1, 0x348(r1)
	lfs f0, 0x33c(r1)
	stw r9, 0x340(r1)
	fsubs f0, f1, f0
	lwz r0, 0xf0(r1)
	stw r5, 0x34c(r1)
	lwz r30, 0xec(r1)
	stfs f0, 0xe4(r1)
	lwz r31, 0xf4(r1)
	lwz r3, 0xe4(r1)
	stw r0, 0x360(r1)
	lfs f1, 0x344(r1)
	lfs f0, 0x338(r1)
	stw r3, 0x354(r1)
	fsubs f3, f1, f0
	lfs f1, 0x34c(r1)
	lfs f0, 0x340(r1)
	stw r30, 0x35c(r1)
	fsubs f2, f1, f0
	lfs f1, 0x360(r1)
	stfs f3, 0xe0(r1)
	lfs f0, 0x354(r1)
	lwz r3, 0xe0(r1)
	stfs f2, 0xe8(r1)
	fmuls f0, f1, f0
	lfs f2, 0x35c(r1)
	stw r3, 0x350(r1)
	lwz r3, 0xe8(r1)
	lfs f1, 0x350(r1)
	stw r3, 0x358(r1)
	fmadds f1, f2, f1, f0
	lfs f0, float_0_8041954c(r2)
	stw r31, 0x364(r1)
	lfs f2, 0x358(r1)
	lfs f3, 0x364(r1)
	stw r8, 0x8(r1)
	fmadds f1, f3, f2, f1
	stw r6, 0xc(r1)
	fcmpo cr0, f1, f0
	stw r5, 0x10(r1)
	ble @3
	lwz r3, 0x3e4(r1)
	lis r4, double_0_802c1318@ha
	stw r0, 0x330(r1)
	addi r12, r4, double_0_802c1318@l
	lwz r4, 0x3e0(r1)
	stw r3, 0x324(r1)
	lfs f2, 0x330(r1)
	lfs f0, 0x324(r1)
	stw r4, 0x320(r1)
	lwz r0, 0x3e8(r1)
	fmuls f0, f2, f0
	stw r30, 0x32c(r1)
	lfs f2, 0x320(r1)
	lfs f3, 0x32c(r1)
	stw r0, 0x328(r1)
	fmadds f2, f3, f2, f0
	lfd f0, 0x0(r12)
	stw r31, 0x334(r1)
	lfs f3, 0x328(r1)
	lfs f4, 0x334(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @4
	li r3, 0x0
	b @2
	@4:
	lwz r31, 0x110(r1)
	stw r0, 0x2e0(r1)
	lwz r12, 0x118(r1)
	stw r31, 0x2e4(r1)
	lfs f9, 0x2e0(r1)
	lfs f6, 0x2e4(r1)
	stw r4, 0x2d8(r1)
	lwz r31, 0x114(r1)
	fmuls f2, f6, f9
	stw r3, 0x2dc(r1)
	lfs f5, 0x2d8(r1)
	stw r12, 0x2ec(r1)
	lfs f10, 0x2dc(r1)
	lfs f3, 0x2ec(r1)
	stw r10, 0x300(r1)
	fmsubs f7, f3, f5, f2
	stw r6, 0x30c(r1)
	fmuls f8, f3, f10
	lfs f2, 0x300(r1)
	lfs f3, 0x30c(r1)
	stw r31, 0x2e8(r1)
	fsubs f4, f3, f2
	lfs f2, 0x2e8(r1)
	stw r11, 0x2fc(r1)
	fmsubs f8, f2, f9, f8
	stw r8, 0x308(r1)
	fmuls f5, f2, f5
	lfs f2, 0x2fc(r1)
	lfs f3, 0x308(r1)
	stw r9, 0x304(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x310(r1)
	lfs f2, 0x304(r1)
	stfs f7, 0xcc(r1)
	lfs f3, 0x310(r1)
	stfs f4, 0xd8(r1)
	lwz r10, 0xcc(r1)
	fsubs f4, f3, f2
	lwz r9, 0xd8(r1)
	stfs f8, 0xc8(r1)
	stfs f5, 0xd4(r1)
	lwz r12, 0xc8(r1)
	stw r10, 0x2f4(r1)
	lwz r10, 0xd4(r1)
	stw r9, 0x318(r1)
	lfs f2, 0x2f4(r1)
	stfs f6, 0xd0(r1)
	lfs f3, 0x318(r1)
	stfs f4, 0xdc(r1)
	lwz r11, 0xd0(r1)
	fmuls f2, f3, f2
	stw r12, 0x2f0(r1)
	lwz r9, 0xdc(r1)
	stw r10, 0x314(r1)
	lfs f3, 0x2f0(r1)
	lfs f4, 0x314(r1)
	stw r11, 0x2f8(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x31c(r1)
	lfs f3, 0x2f8(r1)
	lfs f4, 0x31c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	ble @5
	li r3, 0x0
	b @2
	@5:
	lwz r10, 0x104(r1)
	stw r0, 0x298(r1)
	lwz r9, 0x10c(r1)
	stw r10, 0x29c(r1)
	lwz r10, 0x18(r1)
	stw r4, 0x290(r1)
	lwz r12, 0x108(r1)
	stw r3, 0x294(r1)
	lwz r11, 0x14(r1)
	stw r9, 0x2a4(r1)
	lwz r9, 0x1c(r1)
	stw r10, 0x2b8(r1)
	lfs f8, 0x298(r1)
	lfs f6, 0x29c(r1)
	stw r6, 0x2c4(r1)
	fmuls f2, f6, f8
	lfs f3, 0x2a4(r1)
	lfs f10, 0x294(r1)
	lfs f5, 0x290(r1)
	stw r12, 0x2a0(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x2c4(r1)
	lfs f9, 0x2a0(r1)
	lfs f2, 0x2b8(r1)
	stw r11, 0x2b4(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x2c0(r1)
	fmuls f5, f9, f5
	lfs f2, 0x2b4(r1)
	lfs f3, 0x2c0(r1)
	stw r9, 0x2bc(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x2c8(r1)
	lfs f2, 0x2bc(r1)
	stfs f7, 0xb4(r1)
	lfs f3, 0x2c8(r1)
	stfs f4, 0xc0(r1)
	lwz r10, 0xb4(r1)
	fsubs f4, f3, f2
	lwz r9, 0xc0(r1)
	stfs f8, 0xb0(r1)
	stfs f5, 0xbc(r1)
	lwz r12, 0xb0(r1)
	stw r10, 0x2ac(r1)
	lwz r10, 0xbc(r1)
	stw r9, 0x2d0(r1)
	lfs f2, 0x2ac(r1)
	stfs f6, 0xb8(r1)
	lfs f3, 0x2d0(r1)
	stfs f4, 0xc4(r1)
	lwz r11, 0xb8(r1)
	fmuls f2, f3, f2
	stw r12, 0x2a8(r1)
	lwz r9, 0xc4(r1)
	stw r10, 0x2cc(r1)
	lfs f3, 0x2a8(r1)
	lfs f4, 0x2cc(r1)
	stw r11, 0x2b0(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x2d4(r1)
	lfs f3, 0x2b0(r1)
	lfs f4, 0x2d4(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	ble @6
	li r3, 0x0
	b @2
	@6:
	lwz r9, 0xf8(r1)
	stw r0, 0x250(r1)
	lwz r0, 0x100(r1)
	stw r9, 0x254(r1)
	lwz r9, 0x24(r1)
	stw r4, 0x248(r1)
	lwz r4, 0xfc(r1)
	stw r3, 0x24c(r1)
	lwz r3, 0x20(r1)
	stw r0, 0x25c(r1)
	lwz r0, 0x28(r1)
	stw r9, 0x270(r1)
	lfs f8, 0x250(r1)
	lfs f6, 0x254(r1)
	stw r6, 0x27c(r1)
	fmuls f2, f6, f8
	lfs f3, 0x25c(r1)
	lfs f10, 0x24c(r1)
	lfs f5, 0x248(r1)
	stw r4, 0x258(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x27c(r1)
	lfs f9, 0x258(r1)
	lfs f2, 0x270(r1)
	stw r3, 0x26c(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x278(r1)
	fmuls f5, f9, f5
	lfs f2, 0x26c(r1)
	lfs f3, 0x278(r1)
	stw r0, 0x274(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x280(r1)
	lfs f2, 0x274(r1)
	stfs f7, 0x9c(r1)
	lfs f3, 0x280(r1)
	stfs f4, 0xa8(r1)
	lwz r3, 0x9c(r1)
	fsubs f4, f3, f2
	lwz r0, 0xa8(r1)
	stfs f8, 0x98(r1)
	stfs f5, 0xa4(r1)
	lwz r5, 0x98(r1)
	stw r3, 0x264(r1)
	lwz r3, 0xa4(r1)
	stw r0, 0x288(r1)
	lfs f2, 0x264(r1)
	stfs f6, 0xa0(r1)
	lfs f3, 0x288(r1)
	stfs f4, 0xac(r1)
	lwz r4, 0xa0(r1)
	fmuls f2, f3, f2
	stw r5, 0x260(r1)
	lwz r0, 0xac(r1)
	stw r3, 0x284(r1)
	lfs f3, 0x260(r1)
	lfs f4, 0x284(r1)
	stw r4, 0x268(r1)
	fmadds f2, f4, f3, f2
	stw r0, 0x28c(r1)
	lfs f3, 0x268(r1)
	lfs f4, 0x28c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	ble @7
	li r3, 0x0
	b @2
	@3:
	lwz r3, 0x3e4(r1)
	lis r4, double_0_802c1318@ha
	stw r0, 0x240(r1)
	addi r12, r4, double_0_802c1318@l
	lwz r4, 0x3e0(r1)
	stw r3, 0x234(r1)
	lfs f2, 0x240(r1)
	lfs f0, 0x234(r1)
	stw r4, 0x230(r1)
	lwz r0, 0x3e8(r1)
	fmuls f0, f2, f0
	stw r30, 0x23c(r1)
	lfs f2, 0x230(r1)
	lfs f3, 0x23c(r1)
	stw r0, 0x238(r1)
	fmadds f2, f3, f2, f0
	lfd f0, 0x0(r12)
	stw r31, 0x244(r1)
	lfs f3, 0x238(r1)
	lfs f4, 0x244(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne @8
	li r3, 0x0
	b @2
	@8:
	lwz r31, 0x110(r1)
	stw r0, 0x1f0(r1)
	lwz r12, 0x118(r1)
	stw r31, 0x1f4(r1)
	lfs f9, 0x1f0(r1)
	lfs f6, 0x1f4(r1)
	stw r4, 0x1e8(r1)
	lwz r31, 0x114(r1)
	fmuls f2, f6, f9
	stw r3, 0x1ec(r1)
	lfs f5, 0x1e8(r1)
	stw r12, 0x1fc(r1)
	lfs f10, 0x1ec(r1)
	lfs f3, 0x1fc(r1)
	stw r10, 0x210(r1)
	fmsubs f7, f3, f5, f2
	stw r6, 0x21c(r1)
	fmuls f8, f3, f10
	lfs f2, 0x210(r1)
	lfs f3, 0x21c(r1)
	stw r31, 0x1f8(r1)
	fsubs f4, f3, f2
	lfs f2, 0x1f8(r1)
	stw r11, 0x20c(r1)
	fmsubs f8, f2, f9, f8
	stw r8, 0x218(r1)
	fmuls f5, f2, f5
	lfs f2, 0x20c(r1)
	lfs f3, 0x218(r1)
	stw r9, 0x214(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x220(r1)
	lfs f2, 0x214(r1)
	stfs f7, 0x84(r1)
	lfs f3, 0x220(r1)
	stfs f4, 0x90(r1)
	lwz r10, 0x84(r1)
	fsubs f4, f3, f2
	lwz r9, 0x90(r1)
	stfs f8, 0x80(r1)
	stfs f5, 0x8c(r1)
	lwz r12, 0x80(r1)
	stw r10, 0x204(r1)
	lwz r10, 0x8c(r1)
	stw r9, 0x228(r1)
	lfs f2, 0x204(r1)
	stfs f6, 0x88(r1)
	lfs f3, 0x228(r1)
	stfs f4, 0x94(r1)
	lwz r11, 0x88(r1)
	fmuls f2, f3, f2
	stw r12, 0x200(r1)
	lwz r9, 0x94(r1)
	stw r10, 0x224(r1)
	lfs f3, 0x200(r1)
	lfs f4, 0x224(r1)
	stw r11, 0x208(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x22c(r1)
	lfs f3, 0x208(r1)
	lfs f4, 0x22c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	bge @9
	li r3, 0x0
	b @2
	@9:
	lwz r10, 0x104(r1)
	stw r0, 0x1a8(r1)
	lwz r9, 0x10c(r1)
	stw r10, 0x1ac(r1)
	lwz r10, 0x18(r1)
	stw r4, 0x1a0(r1)
	lwz r12, 0x108(r1)
	stw r3, 0x1a4(r1)
	lwz r11, 0x14(r1)
	stw r9, 0x1b4(r1)
	lwz r9, 0x1c(r1)
	stw r10, 0x1c8(r1)
	lfs f8, 0x1a8(r1)
	lfs f6, 0x1ac(r1)
	stw r6, 0x1d4(r1)
	fmuls f2, f6, f8
	lfs f3, 0x1b4(r1)
	lfs f10, 0x1a4(r1)
	lfs f5, 0x1a0(r1)
	stw r12, 0x1b0(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x1d4(r1)
	lfs f9, 0x1b0(r1)
	lfs f2, 0x1c8(r1)
	stw r11, 0x1c4(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x1d0(r1)
	fmuls f5, f9, f5
	lfs f2, 0x1c4(r1)
	lfs f3, 0x1d0(r1)
	stw r9, 0x1cc(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x1d8(r1)
	lfs f2, 0x1cc(r1)
	stfs f7, 0x6c(r1)
	lfs f3, 0x1d8(r1)
	stfs f4, 0x78(r1)
	lwz r10, 0x6c(r1)
	fsubs f4, f3, f2
	lwz r9, 0x78(r1)
	stfs f8, 0x68(r1)
	stfs f5, 0x74(r1)
	lwz r12, 0x68(r1)
	stw r10, 0x1bc(r1)
	lwz r10, 0x74(r1)
	stw r9, 0x1e0(r1)
	lfs f2, 0x1bc(r1)
	stfs f6, 0x70(r1)
	lfs f3, 0x1e0(r1)
	stfs f4, 0x7c(r1)
	lwz r11, 0x70(r1)
	fmuls f2, f3, f2
	stw r12, 0x1b8(r1)
	lwz r9, 0x7c(r1)
	stw r10, 0x1dc(r1)
	lfs f3, 0x1b8(r1)
	lfs f4, 0x1dc(r1)
	stw r11, 0x1c0(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x1e4(r1)
	lfs f3, 0x1c0(r1)
	lfs f4, 0x1e4(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	bge @10
	li r3, 0x0
	b @2
	@10:
	lwz r9, 0xf8(r1)
	stw r0, 0x160(r1)
	lwz r0, 0x100(r1)
	stw r9, 0x164(r1)
	lwz r9, 0x24(r1)
	stw r4, 0x158(r1)
	lwz r4, 0xfc(r1)
	stw r3, 0x15c(r1)
	lwz r3, 0x20(r1)
	stw r0, 0x16c(r1)
	lwz r0, 0x28(r1)
	stw r9, 0x180(r1)
	lfs f8, 0x160(r1)
	lfs f6, 0x164(r1)
	stw r6, 0x18c(r1)
	fmuls f2, f6, f8
	lfs f3, 0x16c(r1)
	lfs f10, 0x15c(r1)
	lfs f5, 0x158(r1)
	stw r4, 0x168(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x18c(r1)
	lfs f9, 0x168(r1)
	lfs f2, 0x180(r1)
	stw r3, 0x17c(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x188(r1)
	fmuls f5, f9, f5
	lfs f2, 0x17c(r1)
	lfs f3, 0x188(r1)
	stw r0, 0x184(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x190(r1)
	lfs f2, 0x184(r1)
	stfs f7, 0x54(r1)
	lfs f3, 0x190(r1)
	stfs f4, 0x60(r1)
	lwz r3, 0x54(r1)
	fsubs f4, f3, f2
	lwz r0, 0x60(r1)
	stfs f8, 0x50(r1)
	stfs f5, 0x5c(r1)
	lwz r5, 0x50(r1)
	stw r3, 0x174(r1)
	lwz r3, 0x5c(r1)
	stw r0, 0x198(r1)
	lfs f2, 0x174(r1)
	stfs f6, 0x58(r1)
	lfs f3, 0x198(r1)
	stfs f4, 0x64(r1)
	lwz r4, 0x58(r1)
	fmuls f2, f3, f2
	stw r5, 0x170(r1)
	lwz r0, 0x64(r1)
	stw r3, 0x194(r1)
	lfs f3, 0x170(r1)
	lfs f4, 0x194(r1)
	stw r4, 0x178(r1)
	fmadds f2, f4, f3, f2
	stw r0, 0x19c(r1)
	lfs f3, 0x178(r1)
	lfs f4, 0x19c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	bge @7
	li r3, 0x0
	b @2
	@7:
	lwz r5, 0x3e4(r1)
	fneg f3, f1
	lwz r0, 0xf0(r1)
	stw r5, 0x144(r1)
	lwz r6, 0x3e0(r1)
	stw r0, 0x150(r1)
	lwz r3, 0xec(r1)
	lwz r4, 0x3e8(r1)
	stw r6, 0x140(r1)
	lwz r0, 0xf4(r1)
	stw r3, 0x14c(r1)
	lfs f1, 0x150(r1)
	lfs f0, 0x144(r1)
	stw r4, 0x148(r1)
	fmuls f0, f1, f0
	lfs f2, 0x14c(r1)
	lfs f1, 0x140(r1)
	stw r0, 0x154(r1)
	fmadds f0, f2, f1, f0
	lfs f1, 0x148(r1)
	lfs f2, 0x154(r1)
	stw r5, 0x120(r1)
	fmadds f0, f2, f1, f0
	lwz r0, 0xc(r1)
	stw r6, 0x11c(r1)
	lwz r3, 0x8(r1)
	fdivs f5, f3, f0
	lfs f1, 0x120(r1)
	stw r4, 0x124(r1)
	lfs f2, 0x11c(r1)
	lfs f0, 0x124(r1)
	stw r0, 0x138(r1)
	fmuls f3, f1, f5
	lwz r0, 0x10(r1)
	fmuls f4, f2, f5
	lfs f2, 0x138(r1)
	fmuls f1, f0, f5
	stw r3, 0x134(r1)
	stfs f3, 0x48(r1)
	lfs f3, 0x134(r1)
	lwz r3, 0x48(r1)
	stfs f4, 0x44(r1)
	lfs f0, 0x0(r7)
	stw r3, 0x12c(r1)
	lwz r4, 0x44(r1)
	stfs f1, 0x4c(r1)
	lfs f1, 0x12c(r1)
	lwz r3, 0x4c(r1)
	fadds f2, f2, f1
	stw r4, 0x128(r1)
	stw r3, 0x130(r1)
	lfs f1, 0x128(r1)
	stw r0, 0x13c(r1)
	fadds f3, f3, f1
	lfs f1, 0x130(r1)
	stfs f2, 0x3c(r1)
	lfs f2, 0x13c(r1)
	lwz r0, 0x3c(r1)
	fadds f1, f2, f1
	stfs f3, 0x38(r1)
	stw r0, 0x3cc(r1)
	lwz r3, 0x38(r1)
	stfs f1, 0x40(r1)
	lfs f1, 0x3cc(r1)
	lwz r0, 0x40(r1)
	fcmpo cr0, f1, f0
	stw r3, 0x3c8(r1)
	stw r0, 0x3d0(r1)
	bge @11
	li r3, 0x0
	b @2
	@11:
	stfs f1, 0x0(r7)
	li r3, 0x1
	@2:
	lmw r26, 0x3f8(r1)
	addi r1, r1, 0x410
	blr
}

asm void calcCurrentCamState(CamRoadOut* out) {
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
	stfd f27, 0xb0(r1)
	psq_st f27, 0xb8(r1), 0, 0
	stfd f26, 0xa0(r1)
	psq_st f26, 0xa8(r1), 0, 0
	stfd f25, 0x90(r1)
	psq_st f25, 0x98(r1), 0, 0
	stfd f24, 0x80(r1)
	psq_st f24, 0x88(r1), 0, 0
	stfd f23, 0x70(r1)
	psq_st f23, 0x78(r1), 0, 0
	stw r31, 0x6c(r1)
	lwz r4, wp(r13)
	mr r31, r3
	lwz r3, 0x0(r4)
	lwz r3, 0xe8(r3)
	lfs f0, 0x0(r3)
	stfs f0, 0x0(r31)
	lfs f0, 0x4(r3)
	stfs f0, 0x4(r31)
	lfs f0, 0x8(r3)
	stfs f0, 0x8(r31)
	lwz r3, wp(r13)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x0
	bne @1
	lfs f1, float_0_8041954c(r2)
	lfs f0, float_100_804195b8(r2)
	stfs f1, 0xc(r31)
	stfs f0, 0x10(r31)
	stfs f0, 0x14(r31)
	stfs f1, 0x18(r31)
	stfs f1, 0x1c(r31)
	stfs f1, 0x20(r31)
	b @2
	@1:
	lfs f2, float_3p1416_80419568(r2)
	lfs f1, 0x4c(r3)
	lfs f0, float_180_80419588(r2)
	fmuls f1, f2, f1
	lfs f30, 0x30(r3)
	lfs f29, 0x34(r3)
	lfs f28, 0x38(r3)
	fdivs f24, f1, f0
	lfs f27, 0x3c(r3)
	lfs f26, 0x44(r3)
	lfs f25, 0x48(r3)
	lfs f31, 0x50(r3)
	fmr f1, f24
	bl cos
	frsp f2, f1
	fmuls f0, f27, f25
	fmr f1, f24
	fmuls f23, f0, f2
	bl sin
	frsp f0, f1
	fmr f1, f24
	fmuls f24, f25, f0
	bl cos
	frsp f4, f1
	lfs f0, float_deg2rad_804195bc(r2)
	fmuls f1, f26, f25
	lfs f2, float_0_8041954c(r2)
	fadds f3, f30, f23
	addi r3, r1, 0x2c
	fmuls f25, f1, f4
	addi r4, r1, 0x8
	fadds f1, f29, f24
	stfs f3, 0xc(r31)
	fneg f3, f26
	fadds f4, f28, f25
	stfs f1, 0x10(r31)
	fmuls f1, f0, f31
	stfs f4, 0x14(r31)
	stfs f3, 0x8(r1)
	stfs f2, 0xc(r1)
	stfs f27, 0x10(r1)
	bl PSMTXRotAxisRad
	fneg f2, f23
	addi r3, r1, 0x2c
	fneg f1, f24
	addi r4, r1, 0x20
	fneg f0, f25
	addi r5, r1, 0x14
	stfs f2, 0x20(r1)
	stfs f1, 0x24(r1)
	stfs f0, 0x28(r1)
	bl PSMTXMultVec
	lfs f1, 0xc(r31)
	lfs f0, 0x14(r1)
	fadds f0, f1, f0
	stfs f0, 0x18(r31)
	lfs f1, 0x10(r31)
	lfs f0, 0x18(r1)
	fadds f0, f1, f0
	stfs f0, 0x1c(r31)
	lfs f1, 0x14(r31)
	lfs f0, 0x1c(r1)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	@2:
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	psq_l f27, 0xb8(r1), 0, 0
	lfd f27, 0xb0(r1)
	psq_l f26, 0xa8(r1), 0, 0
	lfd f26, 0xa0(r1)
	psq_l f25, 0x98(r1), 0, 0
	lfd f25, 0x90(r1)
	psq_l f24, 0x88(r1), 0, 0
	lfd f24, 0x80(r1)
	psq_l f23, 0x78(r1), 0, 0
	lfd f23, 0x70(r1)
	lwz r0, 0x104(r1)
	lwz r31, 0x6c(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm s32 camRoadSetup(const char* name) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	li r4, 0x0
	li r5, 0x210
	stw r0, 0xa4(r1)
	stw r31, 0x9c(r1)
	mr r31, r3
	lwz r3, wp(r13)
	bl memset
	lwz r3, wp(r13)
	li r4, 0x0
	lfs f6, float_0p005_80419548(r2)
	li r0, -0x1
	stw r4, 0xc8(r3)
	lfs f5, float_0_8041954c(r2)
	lwz r3, wp(r13)
	lfs f4, float_0p004_80419550(r2)
	stw r4, 0xd8(r3)
	lfs f3, float_0p008_80419554(r2)
	lwz r3, wp(r13)
	lfs f2, float_1_80419558(r2)
	stw r4, 0xd8(r3)
	lfs f1, float_2_8041955c(r2)
	lwz r3, wp(r13)
	lfs f0, float_3_80419560(r2)
	stfs f6, 0x19c(r3)
	lwz r3, wp(r13)
	stfs f5, 0x1a0(r3)
	lwz r3, wp(r13)
	stfs f4, 0x1a4(r3)
	lwz r3, wp(r13)
	stfs f3, 0x1a8(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1ac(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1b0(r3)
	lwz r3, wp(r13)
	stfs f1, 0x1b4(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1b8(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1bc(r3)
	lwz r3, wp(r13)
	stfs f0, 0x1c0(r3)
	lwz r3, wp(r13)
	stfs f2, 0x1c4(r3)
	lwz r3, wp(r13)
	stw r0, 0x204(r3)
	lwz r3, wp(r13)
	stw r4, 0x208(r3)
	bl camShiftInit
	lwz r4, wp(r13)
	mr r3, r31
	addi r5, r1, 0x8
	bl arcOpen
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	cmplwi r0, 0x0
	bne @1
	bl getMapDataDvdRoot
	mr r5, r3
	mr r6, r31
	addi r3, r1, 0xc
	la r4, str_804195C0(r2)
	crclr 6
	bl sprintf
	addi r3, r1, 0xc
	li r4, 0x2
	li r5, 0x0
	bl DVDMgrOpen
	mr. r31, r3
	beq @2
	bl DVDMgrGetLength
	stw r3, 0x8(r1)
	addi r0, r3, 0x1f
	clrrwi r3, r0, 5
	bl _mapAlloc
	lwz r4, wp(r13)
	li r6, 0x0
	stw r3, 0x0(r4)
	mr r3, r31
	lwz r4, wp(r13)
	lwz r5, 0x8(r1)
	lwz r4, 0x0(r4)
	addi r0, r5, 0x1f
	clrrwi r5, r0, 5
	bl DVDMgrRead
	mr r3, r31
	bl DVDMgrClose
	b @1
	@2:
	li r3, 0x0
	b @3
	@1:
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xe8(r3)
	cmplw r0, r3
	bge @4
	add r0, r0, r3
	stw r0, 0xe8(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xec(r3)
	add r0, r0, r3
	stw r0, 0xec(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xf0(r3)
	add r0, r0, r3
	stw r0, 0xf0(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xf4(r3)
	add r0, r0, r3
	stw r0, 0xf4(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xf8(r3)
	add r0, r0, r3
	stw r0, 0xf8(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0xfc(r3)
	add r0, r0, r3
	stw r0, 0xfc(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0x100(r3)
	add r0, r0, r3
	stw r0, 0x100(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0x104(r3)
	add r0, r0, r3
	stw r0, 0x104(r3)
	lwz r3, wp(r13)
	lwz r3, 0x0(r3)
	lwz r0, 0x108(r3)
	add r0, r0, r3
	stw r0, 0x108(r3)
	@4:
	lwz r3, wp(r13)
	la r4, str_804195C8(r2)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x44
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	lwz r3, wp(r13)
	li r0, 0x65
	stw r0, 0x1d0(r3)
	b @6
	@5:
	lwz r3, wp(r13)
	li r0, 0x64
	stw r0, 0x1d0(r3)
	@6:
	li r3, 0x1
	@3:
	lwz r0, 0xa4(r1)
	lwz r31, 0x9c(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}
// clang-format on
#endif
