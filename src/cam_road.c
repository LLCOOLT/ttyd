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

static CamRoadWork work;
static CamRoadWork* wp = &work;

void calcCurrentCamState(CamRoadOut* out);
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* speed);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);

s32 camRoadSetup(const char* name) {
    char path[128];
    u32 size;
    DVDEntry* entry;

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
    hit = crVecAdd(P, crVecScale(dir, t));
    if (hit.y < *dist) {
        return 0;
    }
    *dist = hit.y;
    return 1;
}
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

s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit) {
    f32 minDist;
    s32 ret;
    s32 i;
    s32 half;
    s32 idxA, idxB;
    s32 flag, isGrp;
    s32 fl;
    f32 limA, limB;
    f32 yA, yB;
    Vec* pt;
    Vec* nrm;
    f32 x0, y0, z0, x1, z1;
    f32 u0x, u0z, u1x, u1z, t;
    f32 cx, cz, r0x, r0z, dpx, dpz, r0, rp, r1, c0, c1, ang0, ang1, ratio, d, d0, yy, cross;
    f32 sgn, side;
    f32 dx, dz, qx, qz, s, dx2, dz2, dist, cr;

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
        limA = limB = 0.0f;
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
        if (nrm[i].x * (pos.x - x0) + nrm[i].z * (pos.z - z0) < 0.0) {
            continue;
        }
        if (-nrm[i + 1].x * (pos.x - x1) + -nrm[i + 1].z * (pos.z - z1) < 0.0) {
            continue;
        }
        u0x = -nrm[i].z;
        u0z = nrm[i].x;
        u1x = -nrm[i + 1].z;
        u1z = nrm[i + 1].x;
        if (__fabs(u0x - u1x) < 0.01f && __fabs(u0z - u1z) < 0.01f) {
            u0x = u1x = 0.5f * (u0x + u1x);
            u0z = u1z = 0.5f * (u0z + u1z);
        }
        if (u0x != u1x || u0z != u1z) {
            sgn = side = 1.0f;
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
            r0 = crLen2(r0x, r0z);
            dpz = pos.z - cz;
            dpx = pos.x - cx;
            rp = crLen2(dpx, dpz);
            r1 = crLen2(x1 - cx, z1 - cz);
            c0 = (r0x * dpx + r0z * dpz) / (r0 * rp);
            c1 = ((x1 - cx) * dpx + (z1 - cz) * dpz) / (r1 * rp);
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
            yy = ratio * (nrm[i + 1].y - nrm[i].y) + nrm[i].y;
            cross = r0x * -(z1 - z0) + r0z * (x1 - x0);
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
                    hit->pos.x = d * nrm[idxA].z + pt[idxA].x;
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
                    hit->pos.x = d * nrm[idxB].z + pt[idxB].x;
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
                    if (sgn >= 0.0f && d > 0.0f) {
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
                if (cross <= 0.0) {
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
            dz = z1 - z0;
            dx = x1 - x0;
            u1x = -dz;
            if (__fabs(u1x) > __fabs(dx)) {
                t = (dx * ((x0 - pos.x) / u1x) + pos.z - z0) / (dz - dx * (dx / u1x));
            } else if (dx != 0.0) {
                t = (u1x * ((z0 - pos.z) / dx) + pos.x - x0) / (dx - u1x * (dz / dx));
            } else {
                t = 0.0f;
            }
            qx = t * dx + x0;
            qz = t * dz + z0;
            if (__fabs(dx) > __fabs(dz)) {
                s = (qx - x0) / dx;
                if (s < -0.0000001 || s > 1.0000001) {
                }
            } else if (dz != 0.0) {
                s = (qz - z0) / dz;
            }
            dz2 = pos.z - qz;
            dx2 = pos.x - qx;
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
                    cr = dx2 * u1x + dz2 * dx;
                    if (cr < 0.0f) {
                        if (dist > limA) { dist = limA; fl |= 2; }
                    } else {
                        if (dist > limB) { dist = limB; fl |= 2; }
                        dist = -dist;
                    }
                    ret = 1;
                    hit->t = yA;
                    hit->pos.x = dist * nrm[idxA].z + pt[idxA].x;
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
                    cr = dx2 * u1x + dz2 * dx;
                    if (cr < 0.0f) {
                        if (dist > limA) { dist = limA; fl |= 2; }
                    } else {
                        if (dist > limB) { dist = limB; fl |= 2; }
                        dist = -dist;
                    }
                    ret = 1;
                    hit->t = yB;
                    hit->pos.x = dist * nrm[idxB].z + pt[idxB].x;
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
                cr = dx2 * u1x + dz2 * dx;
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
// CC_END
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
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
    f32 nx;
    f32 ny;
    f32 nz;
    f32 px;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 fov;
    f32 cs, sn, w, ox, oz;
    f32 pz, qx, qz;
    f32 lim1, lim2, l1, l2;
    f32 s, t, sgn1, sgn2, len2, len;
    u32 flags;
    s32 found, found2;
    s32 i, j, k, l;
    s32 n, m, cnt;
    CamRoadCurveX* curve;
    CamRoadGroup* grp;
    CamRoadStrip* strip;
    Vec* verts;
    s32* idx;
    s32* idxp;
    CamRoadCurveX* hitCurve;

    posA.x = a;
    posA.y = b;
    posA.z = c;
    posB.x = d;
    posB.y = e;
    posB.z = f;
    best = -100000000.0f;
    hitCurve = NULL;
    curve = (CamRoadCurveX*)wp->map->curves;
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
                idx = &((s32*)wp->map->f_100)[strip->idxOfs];
                cnt = strip->num - 1;
                idxp = idx + 1;
                for (l = 1; l < cnt; l++, idxp++) {
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
    curve = hitCurve;
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
        nz = hit.dir.x;
        len2 = nz * nz + nx * nx;
        f4c = hit.f_24;
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
        q.y = 100000000.0f;
        q.x = x;
        q.z = z;
        hit.y = -1000000.0f;
        if (collisionCurve(1, &((CamRoadGroup*)wp->map->f_104)[curve->f_b0], q, &hit)) {
            flags |= hit.flags;
            x = hit.pos.x;
            z = hit.pos.z;
        }
    }
    if (curve != NULL) {
        fov = 3.1415927f * (wp->map->f_e8->x * 0.5f / 180.0f);
        if (g && hitCurve != NULL && prev->on) {
            cs = (f32)cos(fov);
            sn = (f32)sin(fov);
            px = -nz;
            w = 0.01f * (prev->f_58 * (1.0f * (640.0f * (dist * sn / cs) / 480.0f)));
            found = 0;
            hit2.y = -1000000.0f;
            hit2.dir.z = 0.0f;
            hit2.dir.y = 0.0f;
            hit2.dir.x = 0.0f;
            p = posA;
            p.y = 1000000.0f;
            ox = w * px;
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
                hit2.y = -1000000.0f;
                if (collisionCurve(1, &((CamRoadGroup*)wp->map->f_104)[curve->f_b0], p, &hit2)) {
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
            w = 0.01f * (g * (1.0f * (640.0f * (dist * sn / cs2) / 480.0f)));
            found2 = 0;
            flags = 0;
            hit3.y = -1000000.0f;
            hit3.dir.z = 0.0f;
            hit3.dir.y = 0.0f;
            hit3.dir.x = 0.0f;
            p2 = posA;
            p2.y = 1000000.0f;
            ox = w * px;
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
                hit3.y = -1000000.0f;
                if (collisionCurve(1, &((CamRoadGroup*)wp->map->f_104)[curve->f_b0], p2, &hit3)) {
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
            dA.x = -nz;
            dA.y = 0.0f;
            dA.z = nx;
            dB.x = -nx;
            dB.y = 0.0f;
            dB.z = -nz;
            r1.y = 0.0f;
            r2.y = 0.0f;
            l1 = lim1 * wp->f_19c[4];
            spd1 = lim2 * wp->f_19c[4];
            spd2 = lim2 * wp->f_19c[5];
            l2 = lim1 * wp->f_19c[5];
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
            sgn1 = s < 0.0f ? -1.0f : 1.0f;
            sgn2 = t < 0.0f ? -1.0f : 1.0f;
            lim1 = PSVECMag(&r1);
            lim2 = PSVECMag(&r2);
            if (lim1 > l1 && lim1 > spd1) {
                PSVECScale(&dA, &r1, l1 * sgn1);
            }
            if (lim2 > l2 && lim2 > spd2) {
                PSVECScale(&dB, &r2, l2 * sgn2);
            }
            x = prev->pos.x + (r1.x + r2.x);
            z = prev->pos.z + (r1.z + r2.z);
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
#pragma dont_inline reset

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
        if (__abs(d) >= a->cam->f_44 - a->cam->f_40 - 1) {
            return 0;
        }
        if (__abs(d) >= a->cam->f_44 - a->cam->f_40 - 2) {
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
    speed = 6.2831855f * a->dist * ang / 360.0f * wp->f_19c[6];
    ang = __fabsf(a->angle - b->angle);
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f * wp->f_19c[7];
    if (t > speed) {
        speed = t;
    }
    ang = __fabsf(a->rot - b->rot);
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f * wp->f_19c[8];
    if (t > speed) {
        speed = t;
    }
    t = __fabsf(a->dist - b->dist) * wp->f_19c[9];
    if (t > speed) {
        speed = t;
    }
    dx = a->pos.x - b->pos.x;
    dy = a->pos.y - b->pos.y;
    dz = a->pos.z - b->pos.z;
    d2 = dx * dx + dy * dy + dz * dz;
    if (d2) {
        dist = cr_sqrtf(d2);
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
    a1 = (f32)atan2(to->dir.x, to->dir.z);
    a0 = a2;
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

void* camRoadGetWorkPtr(void) {
    return wp;
}

f32 camRoadGetCurrentShiftXRate(void) {
    if (wp->next.on) {
        return wp->next.shiftXRate;
    }
    return 0.0f;
}

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
