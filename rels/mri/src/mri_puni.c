#include "mri_puni.h"
#include "driver/camdrv.h"
#include "memory.h"
#include <string.h>
#include "forcedata.h"
#include "mario/mariost.h"
#include "driver/icondrv.h"

#include "driver/swdrv.h"
#include "pmario_sound.h"
#include "evt/evt_bero.h"
#include "manager/evtmgr_cmd.h"
#include "driver/punidrv.h"
#include "driver/mapdrv.h"
#include <dolphin/gx.h>
extern int rand(void);
void PuniDokuritsu(PuniData* p);
void puniMapdata_MRI_06_getidx(f32 x, f32 z, s32* bx, s32* bz);
void puniMapdata_MRI_09_getidx(f32 x, f32 z, s32* bx, s32* bz);
void puniMapdata_MRI_16_getidx(f32 x, f32 z, s32* bx, s32* bz);
void puniMapdata_MRI_09_getpos(s32 bx, s32 bz, f32* x, f32* z);
extern int abs(int);
EffectEntry* effPuniBalloonEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
void envSetYami(MapTevCallbackInfo* info);


//.data
// clang-format off
extend_data(0,
     u64, negone_one, 0xBF8000003F800000,
     u32, neg_one, 0xBF800000,
     f32, __local_PI, 3.1415926535897932384626433832795f,
     f32, __local_3PIO2, 3.0f * 1.57079632679489661923132169163975f,
     u64, one_negone, 0x3F800000BF800000,
     f32, __local_PIO2, 1.57079632679489661923132169163975f,
     f32, one, 1.0f);
extend_data(1,
     u64, negone_one, 0xBF8000003F800000,
     u32, neg_one, 0xBF800000,
     f32, __local_PI, 3.1415926535897932384626433832795f,
     f32, __local_3PIO2, 3.0f * 1.57079632679489661923132169163975f,
     u64, one_negone, 0x3F800000BF800000,
     f32, __local_PIO2, 1.57079632679489661923132169163975f,
     f32, one, 1.0f)
// clang-format on
u16 puni_nom_patern_data[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,    21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 0,  1,  2,  3,  4,  5,     6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,    31, 32, 33, 34,
    35, 36, 37, 38, 39, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,    16, 40, 41, 42,
    43, 44, 45, 46, 47, 48, 49, 51, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 65535,
};
u16 puni_wlk_patern_data[] = {
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 65535,
};
u16 puni_run_patern_data[] = { 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 65535 };
u16 puni_dmg_patern_data[] = { 72, 65535 };
u16 puni_dwn_patern_data[] = { 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 65535 };
u16 puni_rol_patern_data[] = { 83, 65535 };
u16 puni_hag_patern_data[] = { 0, 65535 };
u16 puni_jpu_patern_data[] = { 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 65534 };
u16 puni_jpd_patern_data[] = { 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 65534 };
u16 puni_wan_patern_data[] = { 104, 105, 106, 107, 108, 109, 110, 111, 65534 };
u16* puni_patern_table[] = { puni_nom_patern_data, puni_wlk_patern_data, puni_run_patern_data, puni_dmg_patern_data,
                             puni_dwn_patern_data, puni_rol_patern_data, puni_hag_patern_data, puni_jpu_patern_data,
                             puni_jpd_patern_data, puni_wan_patern_data };

u16 toge_nom_patern_data[25] = {
    84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 65535,
};
u16 toge_wlk_patern_data[] = { 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 65535 };
u16 toge_run_patern_data[] = { 108, 110, 112, 114, 116, 118, 65535 };
u16 toge_dmg_patern_data[] = { 120, 65535 };
u16 toge_dwn_patern_data[] = { 121, 122, 123, 124, 125, 126, 127, 128, 65535 };
u16 toge_rol_patern_data[] = { 129, 65535 };
u16 toge_hag_patern_data[] = { 65535 };
u16* toge_patern_table[] = { toge_nom_patern_data, toge_wlk_patern_data, toge_run_patern_data, toge_dmg_patern_data,
                             toge_dwn_patern_data, toge_rol_patern_data, toge_hag_patern_data, toge_hag_patern_data,
                             toge_hag_patern_data, toge_hag_patern_data };

//.bss
PuniMap* Punimap;
PuniTexInfo* Punitex;
PuniWork* Punigp;
PuniData* Punidat;

PuniData* puniGetPunidat(void) {
    return Punidat;
}

PuniWork* puniGetPunigp(void) {
    return Punigp;
}

PuniTexInfo* puniGetTex(void) {
    return Punitex;
}

void evt_icon_disp_func(CameraId camId, void* param) {
    s32 i;
    if (Punigp->unk328 == 9 || Punigp->unk328 == 12) {
        for (i = 1; i < 211; i++) {
            PuniData* p = &Punidat[i];
            if ((p->unk4 & 0x400) && !(p->unk4 & 0x804000)) {
                Vec a;
                Vec b;
                a = p->pos;
                if (p->unk8 & 1) {
                    p->unk121++;
                    if ((s8)p->unk121 > 30) {
                        p->unk121 = 0;
                        p->unk8 &= ~1;
                    }
                }
                if (p->unk8 & 2) {
                    b = a;
                    puniSinCosRet(p->unk118 + gp->retraceCount * 10, &a.z, &a.x, 9.0f, 9.0f);
                    a.y += 13.0f;
                    iconDispGx(&a, 0, 0x14d, 0.6f);
                    puniSinCosRet(p->unk118 + gp->retraceCount * 10 + 180, &b.z, &b.x, 9.0f, 9.0f);
                    b.y += 15.0f;
                    iconDispGx(&b, 0, 0x14d, 0.5f);
                }
            }
        }
    }
}

PuniTexInfo* _make_texbuf(PuniTexInfo* texbuf, s32 count, const char* a3, const char* a4, f32 a5) {
    s32 i;

    for (i = 0; i < count; i++) {
        texbuf->unk0 = _mapAlloc(0xC);
        texbuf->unk4 = _mapAlloc(0xC);
        strcpy(texbuf->unk0, a3);
        strcpy(texbuf->unk4, a4);
        texbuf->unk8 = a5;
        a5 += 1.0f;
        texbuf++;
    }
    return texbuf;
}

USER_FUNC(evt_make_texbuf) {
    PuniTexInfo* texbuf = Punitex;

    texbuf = Punitex;
    texbuf = _make_texbuf(texbuf, 40, "c_puni", "S_1", 0.0f);
    texbuf = _make_texbuf(texbuf, 12, "c_puni", "S_1", 97.0f);
    texbuf = _make_texbuf(texbuf, 20, "c_puni", "W_1", 0.0f);
    texbuf = _make_texbuf(texbuf, 1, "c_puni", "D_1", 0.0f);
    texbuf = _make_texbuf(texbuf, 10, "c_puni", "D_2", 0.0f);
    texbuf = _make_texbuf(texbuf, 1, "c_puni", "F_1", 0.0f);

    if (Punigp->unk328 == 9 || Punigp->unk328 == 12) {
        texbuf = _make_texbuf(texbuf, 24, "c_toge", "S_1", 0.0f);
        texbuf = _make_texbuf(texbuf, 12, "c_toge", "W_1", 0.0f);
        texbuf = _make_texbuf(texbuf, 1, "c_toge", "D_1", 0.0f);
        texbuf = _make_texbuf(texbuf, 8, "c_toge", "D_2", 0.0f);
        texbuf = _make_texbuf(texbuf, 1, "c_toge", "F_1", 0.0f);
    } else {
        texbuf = _make_texbuf(texbuf, 10, "c_puni", "J_1A", 0.0f);
        texbuf = _make_texbuf(texbuf, 10, "c_puni", "J_1B", 0.0f);
        texbuf = _make_texbuf(texbuf, 8, "c_puni", "B_1", 0.0f);
    }
    texbuf->unk0 = 0;
    texbuf->unk4 = 0;
    texbuf->unk8 = 0.0f;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_mem_init) {
    Punigp = _mapAlloc(sizeof(PuniWork));
    memset(Punigp, 0, sizeof(PuniWork));
    Punidat = _mapAlloc(sizeof(PuniData) * PUNI_DATA_MAX);
    memset(Punidat, 0, sizeof(PuniData) * PUNI_DATA_MAX);
    Punitex = _mapAlloc(sizeof(PuniTexInfo) * PUNI_TEX_INFO_MAX);
    memset(Punitex, 0, sizeof(PuniTexInfo) * PUNI_TEX_INFO_MAX);
    return EVT_RETURN_DONE;
}

USER_FUNC(puni_disp_info_sub) {
    /*int i;
    int v3;

    for (i = 1; i < 103; i++) {
        if ((Punidat[i].unk4 & 0x400) && !(Punidat[i].unk4 & 0x804000) && !(Punidat[i].unk4 & 0x80)) {
            if ((Punidat[i].unkC != 16 && Punidat[i].unkC != 15)) {
                v3++;
            }
        }
    }*/

    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_dir) {
    s32* args = event->args;
    evtSetValue(event, args[1], (s32)Punidat[evtGetValue(event, args[0])].dir);
    return EVT_RETURN_DONE;
}

void puniAnimCount(s16* pattern, s16* count, s16* end) {
    s16 n = 0;
    s32 i = 0;

    while (TRUE) {
        if (pattern[i] == -1) {
            *end = pattern[i];
            break;
        }
        if (pattern[i] == -2) {
            *end = pattern[i];
            break;
        }
        n++;
        i++;
    }
    *count = n;
}

f32 _chukanhosei(f32 a, f32 b, f32 c) {
    f32 t = (20.0f + b - a) / 20.0f;
    if (t > 0.5f) {
        t = (t - 0.5f) / 0.5f;
    } else {
        t = 0.0f;
    }
    return 10.0f * t + c;
}

BOOL _areacheck(f32 x, f32 z, f32 r, f32 px, f32 pz) {
    BOOL ret = TRUE;
    if (x - r > px) {
        ret = FALSE;
    }
    if (x + r < px) {
        ret = FALSE;
    }
    if (z - r > pz) {
        ret = FALSE;
    }
    if (z + r < pz) {
        ret = FALSE;
    }
    return ret;
}

#define YSTEP(thr, base)                          \
    if (p->pos.z <= (thr)) {                      \
        f32 t = ((thr) - p->pos.z) / 20.0f;       \
        f32 u;                                    \
        if (t > 0.5f) {                           \
            u = (t - 0.5f) / 0.5f;                \
        } else {                                  \
            u = 0.0f;                             \
        }                                         \
        p->pos.y = 10.0f * u + (base);            \
    }

void _ymode_mri_09(PuniData* p) {
    if (p->pos.x <= 400.0f && p->pos.x > 200.0f && p->pos.y <= 100.0f && p->pos.y >= 0.0f) {
        if (p->pos.z <= -55.0f) {
            p->pos.y = 100.0f;
        } else YSTEP(-35.0f, 90.0f)
        else YSTEP(-15.0f, 80.0f)
        else YSTEP(5.0f, 70.0f)
        else YSTEP(25.0f, 60.0f)
        else YSTEP(45.0f, 50.0f)
        else YSTEP(65.0f, 40.0f)
        else YSTEP(85.0f, 30.0f)
        else YSTEP(105.0f, 20.0f)
        else YSTEP(125.0f, 10.0f)
        else YSTEP(145.0f, 0.0f)
        else {
            p->pos.y = 0.0f;
        }
    }
    if (p->pos.x >= -170.0f && p->pos.x <= 170.0f && p->pos.z >= -80.0f && p->pos.z <= 140.0f) {
        p->pos.y = 0.0f;
    }
}

#define YSTEPX(thr, base)                             if (p->pos.x <= (thr)) {                              f32 t = ((thr) - p->pos.x) / 20.0f;               f32 u;                                            if (t > 0.5f) {                                       u = (t - 0.5f) / 0.5f;                        } else {                                              u = 0.0f;                                     }                                                 p->pos.y = 10.0f * u + (base);                }

void _ymode_mri_16_00(PuniData* p) {
    u32 old = p->unk8;
    p->unk8 &= ~8;
    if (p->pos.y <= -200.0f && p->pos.y >= -400.0f) {
        if (p->pos.x <= 40.0f && p->pos.x >= -210.0f && p->pos.z <= -76.46314f && p->pos.z >= -200.0f) {
            if (p->pos.x <= -190.0f) {
                p->pos.y = -320.0f;
            } else YSTEPX(-170.0f, -330.0f)
            else YSTEPX(-150.0f, -340.0f)
            else YSTEPX(-130.0f, -350.0f)
            else YSTEPX(-110.0f, -360.0f)
            else YSTEPX(-90.0f, -370.0f)
            else YSTEPX(-70.0f, -380.0f)
            else YSTEPX(-50.0f, -390.0f)
            else YSTEPX(-30.0f, -400.0f)
            else {
                p->pos.y = -400.0f;
            }
            if (p->pos.y < -320.0f && p->pos.y > -400.0f) {
                p->unk8 |= 8;
            }
        }
        if (p->pos.x <= 40.0f && p->pos.x >= -200.0f && p->pos.z > -76.46314f && p->pos.z < 200.0f) {
            p->pos.y = -400.0f;
        }
    }
    if (!(p->unk8 & 4) && !(p->unk8 & 8) && (old & 8)) {
        if (p->pos.z > -76.46314f && p->unk138.z <= -76.46314f) {
            p->pos.x = p->unk138.x;
            p->pos.y = p->unk138.y;
            p->pos.z = p->unk138.z;
            p->pos.z -= 0.0002f;
        }
    }
}

void _ymode_mri_16_01(PuniData* p) {
    u32 old = p->unk8;
    p->unk8 &= ~8;
    if (p->pos.y <= 100.0f && p->pos.y >= 0.0f) {
        if (p->pos.x <= 40.0f && p->pos.x >= -200.0f && p->pos.z > -200.0f && p->pos.z < 200.0f) {
            p->pos.y = 0.0f;
        }
        if (p->pos.x <= 40.0f && p->pos.x >= -210.0f && p->pos.z <= 60.0f && p->pos.z >= -10.0f) {
            if (p->pos.x <= -190.0f) {
                p->pos.y = 80.0f;
            } else YSTEPX(-170.0f, 70.0f)
            else YSTEPX(-150.0f, 60.0f)
            else YSTEPX(-130.0f, 50.0f)
            else YSTEPX(-110.0f, 40.0f)
            else YSTEPX(-90.0f, 30.0f)
            else YSTEPX(-70.0f, 20.0f)
            else YSTEPX(-50.0f, 10.0f)
            else YSTEPX(-30.0f, 0.0f)
            else {
                p->pos.y = 0.0f;
            }
            if (p->pos.y < 80.0f && p->pos.y > 0.0f) {
                p->unk8 |= 8;
            }
        }
    }
    if (!(p->unk8 & 4) && !(p->unk8 & 8) && (old & 8)) {
        if (p->pos.z > 60.0f && p->unk138.z <= 60.0f) {
            p->pos.x = p->unk138.x;
            p->pos.y = p->unk138.y;
            p->pos.z = p->unk138.z;
            p->pos.z -= 0.0002f;
        }
        if (p->pos.z < -10.0f && p->unk138.z >= -10.0f) {
            p->pos.x = p->unk138.x;
            p->pos.y = p->unk138.y;
            p->pos.z = p->unk138.z;
            p->pos.z += 0.0002f;
        }
    }
}

#define AC(p, x0, x1, z0, z1) (_aok = 1, ((x0) > (p)->pos.x ? _aok = 0 : 0), ((x1) < (p)->pos.x ? _aok = 0 : 0), ((z0) > (p)->pos.z ? _aok = 0 : 0), ((z1) < (p)->pos.z ? _aok = 0 : 0), _aok)
extern f32 getMri02Yuka(void);
//(x0,x1,z0,z1) (ok = 1, (p->pos.x < (x0) ? ok = 0 : 0), (p->pos.x > (x1) ? ok = 0 : 0), (p->pos.z < (z0) ? ok = 0 : 0), (p->pos.z > (z1) ? ok = 0 : 0), ok)
void puniSetYPosition(PuniData* p) {
    if (p->unk4 & 1) {
        BOOL _aok;
        switch (Punigp->ymode) {
            case 1:
                p->pos.y = 0.0f;
                if (AC(p, -49.0f, 49.0f, -69.0f, 29.0f)) {
                    p->pos.y = getMri02Yuka();
                }
                break;
            case 2:
                _ymode_mri_09(p);
                if (!swGet(0xB23)) {
                    if (AC(p, -35.0f, 35.0f, -40.0f, 110.0f)) {
                        p->pos.y = 6.0f;
                    }
                }
                break;
            case 3:
                p->pos.y = 0.0f;
                if (!swGet(0xB2A)) {
                    if (AC(p, -80.0f, -10.0f, -99.0f, -29.0f)) {
                        p->pos.y = 6.0f;
                    }
                }
                break;
            case 4:
                _ymode_mri_16_00(p);
                break;
            case 5:
                _ymode_mri_16_01(p);
                break;
            case 6:
                p->pos.y = 0.0f;
                if (!swGet(0xB37)) {
                    if (AC(p, -35.0f, 35.0f, -70.0f, 0.0f)) {
                        p->pos.y = 6.0f;
                    }
                }
                break;
        }
        if (Punigp->ymode < 7 && Punigp->ymode >= 2) {
            if (__fabs(p->unk138.y - p->pos.y) < 11.0) {
                p->pos.y = p->unk138.y;
            }
        }
    }
}

void puniMapdata_MRI_06_getidx(f32 x, f32 z, s32* bx, s32* bz) {
    if (x <= -420.0) {
        *bx = -1;
    } else if (x <= -350.0) {
        *bx = 1;
    } else if (x <= -250.0) {
        *bx = 2;
    } else if (x <= -200.0) {
        *bx = 3;
    } else if (x <= -100.0) {
        *bx = 4;
    } else if (x <= -50.0) {
        *bx = 5;
    } else if (x <= 50.0) {
        *bx = 6;
    } else if (x <= 100.0) {
        *bx = 7;
    } else if (x <= 200.0) {
        *bx = 8;
    } else if (x <= 250.0) {
        *bx = 9;
    } else if (x <= 350.0) {
        *bx = 10;
    } else if (x <= 400.0) {
        *bx = 11;
    } else {
        *bx = -1;
    }
    if (z <= -150.0) {
        *bz = -1;
    } else if (z <= -50.0) {
        *bz = 1;
    } else if (z <= 110.0) {
        *bz = 2;
    } else if (z <= 162.0) {
        *bz = 3;
    } else {
        *bz = -1;
    }
}

void puniMapdata_MRI_06_getpos(s32 bx, s32 bz, f32* x, f32* z) {
    switch (bx) {
        case 1:
            *x = -375.0f;
            break;
        case 2:
            *x = -300.0f;
            break;
        case 3:
            *x = -225.0f;
            break;
        case 4:
            *x = -150.0f;
            break;
        case 5:
            *x = -75.0f;
            break;
        case 6:
            *x = 0.0f;
            break;
        case 7:
            *x = 75.0f;
            break;
        case 8:
            *x = 150.0f;
            break;
        case 9:
            *x = 225.0f;
            break;
        case 10:
            *x = 300.0f;
            break;
        case 11:
            *x = 375.0f;
            break;
        default:
            *x = -1000.0f;
            break;
    }
    switch (bz) {
        case 1:
            *z = -100.0f;
            break;
        case 2:
            *z = 30.0f;
            break;
        case 3:
            *z = 135.0f;
            break;
        default:
            *z = -1000.0f;
            break;
    }
}

void puniMapdata_MRI_09_getidx(f32 x, f32 z, s32* bx, s32* bz) {
    if (x <= -300.0) {
        *bx = -1;
    } else if (x <= -200.0) {
        *bx = 1;
    } else if (x <= -90.0) {
        *bx = 2;
    } else if (x <= 90.0) {
        *bx = 3;
    } else if (x <= 200.0) {
        *bx = 4;
    } else if (x <= 320.0) {
        *bx = 5;
    } else {
        *bx = -1;
    }
    if (z <= -150.0) {
        *bz = -1;
    } else if (z <= -100.0) {
        *bz = 1;
    } else if (z <= 100.0) {
        *bz = 2;
    } else if (z <= 120.0) {
        *bz = 3;
    } else if (z <= 200.0) {
        *bz = 4;
    } else {
        *bz = -1;
    }
}

void puniMapdata_MRI_16_getidx(f32 x, f32 z, s32* bx, s32* bz) {
    if (x <= -350.0) {
        *bx = -1;
    } else if (x <= -200.0) {
        *bx = 1;
    } else if (x <= -150.0) {
        *bx = 2;
    } else if (x <= -100.0) {
        *bx = 3;
    } else if (x <= -50.0) {
        *bx = 4;
    } else if (x <= 0.0) {
        *bx = 5;
    } else if (x <= 50.0) {
        *bx = 6;
    } else if (x <= 100.0) {
        *bx = 7;
    } else if (x <= 150.0) {
        *bx = 8;
    } else if (x <= 350.0) {
        *bx = 9;
    } else {
        *bx = -1;
    }
    if (z <= -150.0) {
        *bz = -1;
    } else if (z <= -80.0) {
        *bz = 1;
    } else if (z <= -10.0) {
        *bz = 2;
    } else if (z <= 60.0) {
        *bz = 3;
    } else if (z <= 90.0) {
        *bz = 4;
    } else if (z <= 120.0) {
        *bz = 5;
    } else if (z <= 150.0) {
        *bz = 6;
    } else if (z <= 180.0) {
        *bz = 7;
    } else {
        *bz = -1;
    }
}

void puniMapdata_MRI_16_getpos(s32 bx, s32 bz, f32* x, f32* z) {
    switch (bx) {
        case 1: *x = -220.0f; break;
        case 2: *x = -175.0f; break;
        case 3: *x = -125.0f; break;
        case 4: *x = -75.0f; break;
        case 5: *x = -25.0f; break;
        case 6: *x = 25.0f; break;
        case 7: *x = 75.0f; break;
        case 8: *x = 125.0f; break;
        case 9: *x = 170.0f; break;
        default: *x = -1000.0f; break;
    }
    switch (bz) {
        case 1: *z = -120.0f; break;
        case 2: *z = -45.0f; break;
        case 3: *z = 25.0f; break;
        case 4: *z = 75.0f; break;
        case 5: *z = 105.0f; break;
        case 6: *z = 135.0f; break;
        case 7: *z = 165.0f; break;
        default: *z = -1000.0f; break;
    }
}

void puniMapPos2Blk(Vec* pos, s32* blk) {
    switch (Punigp->mapKind) {
        case 0:
            break;
        case 1:
            ((void (*)(Vec*, s32*))puniMapdata_MRI_06_getidx)(pos, blk);
            break;
        case 2:
            ((void (*)(Vec*, s32*))puniMapdata_MRI_09_getidx)(pos, blk);
            break;
        case 3:
            ((void (*)(Vec*, s32*))puniMapdata_MRI_16_getidx)(pos, blk);
            break;
    }
}

void puniMapBlk2Pos(s32 bx, s32 bz, f32* x, f32* z) {
    switch (Punigp->mapKind) {
        case 0:
            break;
        case 1:
            puniMapdata_MRI_06_getpos(bx, bz, x, z);
            break;
        case 2:
            puniMapdata_MRI_09_getpos(bx, bz, x, z);
            break;
        case 3:
            puniMapdata_MRI_16_getpos(bx, bz, x, z);
            break;
    }
}

u16 puniMapGetInfo(s32 x, s32 y) {
    u16 v = Punimap->data[x + y * Punimap->width];
    if (!(v & 0xFF)) {
        v |= 0xFFFF;
    }
    return v;
}

void puniMapInit(void) {
    Punimap = _mapAlloc(sizeof(PuniMap));
    memset(Punimap, 0, sizeof(PuniMap));
}

s32 randi(s32 min, s32 max) {
    s32 r = rand() % (max - min + 1);
    return r + min;
}

static f32 randf(f32 min, f32 max) {
    f32 r = (f32)rand() / 32767.0f;
    return r * (max - min) + min;
}

void qrndseed(s32 seed) {
    Punigp->seed0 = seed + 0x3A3B01F9;
    Punigp->seed1 = 0x21708331;
}

s32 qrnd(s32 n) {
    s32 v;
    Punigp->seed0 += Punigp->seed1 + 0x1733AF91;
    Punigp->seed1 += Punigp->seed0 + 0x21273F9C;
    v = Punigp->seed1 < 0 ? -Punigp->seed1 : Punigp->seed1;
    return v % n;
}

void fn_19_A820(void) {
}

void fn_19_A8DC(void) {
}

USER_FUNC(evt_puni_attack_on) {
    Punigp->unk43C = 3;
    return EVT_RETURN_DONE;
}

BOOL puniParaRecoverCheck(PuniData* p) {
    return p->hp >= p->maxHp;
}

BOOL puniParaDangerCheck(PuniData* p) {
    return p->hp * 100 / p->maxHp <= 30;
}

BOOL puniParaSelfCheck(PuniData* p) {
    return p->hp * 100 / p->maxHp >= 80;
}

BOOL searchMario(PuniData* p) {
    return p->unk1A4 < 150.0f;
}

USER_FUNC(evt_puni_main) {
    puniMain();
    return EVT_RETURN_BLOCK;
}

USER_FUNC(evt_puni_fade_onoff) {
    puniFadeOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

void puniModeCustom(PuniData* p) {
    if (p->modeFunc) {
        p->modeFunc(p);
    }
}

void puniMoveCustom(PuniData* p) {
    if (p->moveFunc) {
        p->moveFunc(p);
    }
}

USER_FUNC(evt_puni_get_systemmode) {
    evtSetValue(event, event->args[0], Punigp->systemMode);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_puninum_alpha) {
    Punigp->puniCounterAlpha = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_puninum_onoff) {
    Punigp->showPuniCounter = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_systemmode) {
    Punigp->systemMode = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_ymode) {
    Punigp->ymode = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

void puniDeleteEffect(PuniData* p) {
    if (p->effect) {
        effDelete(p->effect);
        p->effect = NULL;
    }
}

void _daime_change(PuniData* p) {
    if (p->child1) {
        p->child1->unk11A--;
        _daime_change(p->child1);
    }
    if (p->child2) {
        p->child2->unk11A--;
        _daime_change(p->child2);
    }
}

void PuniDokuritsu(PuniData* p) {
    PuniData* c1;
    PuniData* c2;
    PuniData* par;
    p->unk118 = -1;
    p->unk4 &= ~0x80000;
    p->unk11A = 0;
    c1 = p->child1;
    par = p->parent;
    c2 = p->child2;
    p->parent = NULL;
    p->child1 = NULL;
    p->child2 = NULL;
    if (c1) {
        c1->unk11A--;
        _daime_change(c1);
        c1->parent = par;
        if (c1->parent) {
            if (par->child1 == p) {
                par->child1 = c1;
            } else if (par->child2 == p) {
                par->child2 = c1;
            }
        }
        c1->child2 = c2;
        if (c1->child2) {
            c1->child2->parent = c1;
        }
    } else if (c2) {
        c2->unk11A--;
        _daime_change(c2);
        c2->parent = par;
        if (c2->parent) {
            if (par->child1 == p) {
                par->child1 = c2;
            } else if (par->child2 == p) {
                par->child2 = c2;
            }
        }
        c2->child1 = c1;
        if (c2->child1) {
            c2->child1->parent = c2;
        }
    } else if (par) {
        if (par->child1 == p) {
            par->child1 = NULL;
        } else if (par->child2 == p) {
            par->child2 = NULL;
        }
    }
}

static Vec paraVecA = {0.0f, 0.0f, 0.0f};
static Vec paraVecB = {0.0f, 0.0f, 0.0f};

void puniParaAttack(PuniData* a, PuniData* b) {
    s16 x, y, r;
    if (b->unk586 == 0 && b->unkC == 9) {
        return;
    }
    if (b->unkC != 8) {
        x = a->unk588;
        y = x + b->unk588;
    } else {
        x = a->unk58A;
        y = x + (100 - b->unk58A);
    }
    r = qrnd(y);
    if (x < r || (b->unk4 & 0x8000000)) {
        if (a->unk586 == 0) {
            b->damage = a->unk57E - b->unk580;
            b->vel = paraVecA;
            b->unk1DC = (s32)a;
            b->unk4 |= 0x2000;
            b->unk4 &= ~0x7000000;
            b->unk8 &= ~2;
            b->unkC = 9;
            b->unk114 = 0;
            b->unk4 &= ~0x1000000;
        }
    } else if (b->unk586 == 0) {
        a->damage = b->unk57E - a->unk580;
        a->vel = paraVecB;
        a->unk1DC = (s32)b;
        a->unk4 |= 0x2000;
        a->unk4 &= ~0x7000000;
        a->unk8 &= ~2;
        a->unkC = 9;
        a->unk114 = 0;
        a->unk4 &= ~0x1000000;
    }
    a->unk586 = 1;
    b->unk586 = 1;
}

void puniParaDamage(PuniData* p) {
    p->hp -= p->damage;
    if (p->hp <= 0) {
        p->hp = 0;
        p->unk4 |= 0x4000;
        p->unk8 |= 0x10;
    }
}

void puniModeDokan(PuniData* p) {
    p->unk114 = 0;
    p->unk4 |= 0x800;
    p->npc->flags |= 4;
    {
        Vec v = {0.0f, 0.0f, 0.0f};
        p->vel = v;
    }
}

USER_FUNC(evt_puni_wait_systemmode) {
    s32 mode = evtGetValue(event, event->args[0]);
    return Punigp->systemMode != mode ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

void puniModeALLCheck(void) {
    s32 i, j;
    PuniData* p;
    PuniData* q;
    PuniData* best;
    f32 minDist;

    switch (Punigp->unk43C) {
        case 2:
            p = &Punidat[1];
            for (i = 1; i <= 102; i++, p++) {
                if ((p->unk4 & 0x400) && p->unk1C0 != 1000000.0f) {
                    switch (p->unkC) {
                        case 0:
                        case 1:
                        case 2:
                        case 4:
                        case 16:
                            PuniDokuritsu(p);
                            p->unkE = p->unkC;
                            p->unkC = 5;
                            p->unk114 = 0;
                            if (p->effect != NULL) {
                                effDelete(p->effect);
                                p->effect = NULL;
                            }
                            break;
                    }
                }
            }
            break;
        case 3:
            p = &Punidat[1];
            for (i = 1; i < 211; i++, p++) {
                if (!(p->unk4 & 0x400)) {
                    continue;
                }
                switch (p->unkC) {
                    case 0:
                    case 1:
                    case 2:
                    case 29:
                        break;
                    default:
                        continue;
                }
                if (p->unk4 & 1) {
                    q = &Punidat[110];
                    minDist = 1000000.0f;
                    best = NULL;
                    for (j = 110; j < 210; j++, q++) {
                        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
                            f32 d = PSVECSquareDistance(&p->pos, &q->pos);
                            if (d < minDist) {
                                minDist = d;
                                best = q;
                            }
                        }
                    }
                    if (!(minDist < 1000000.0f)) {
                        best = NULL;
                    }
                } else {
                    q = &Punidat[1];
                    minDist = 1000000.0f;
                    best = NULL;
                    for (j = 1; j < 103; j++, q++) {
                        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
                            f32 d = PSVECSquareDistance(&p->pos, &q->pos);
                            if (d < minDist) {
                                minDist = d;
                                best = q;
                            }
                        }
                    }
                                    if (!(minDist < 1000000.0f)) {
                        best = NULL;
                    }
                }
                if (best != NULL) {
                    p->unk1DC = (s32)best;
                    p->unkC = 7;
                    p->unk114 = 0;
                    p->unk11A = 0;
                    p->unk4 |= 0x100000;
                    PuniDokuritsu(p);
                    if (p->effect != NULL) {
                        effDelete(p->effect);
                        p->effect = NULL;
                    }
                }
            }
            break;
    }
}

void puniModeALLEndCheck(void) {
    switch (Punigp->unk43C) {
        case 1:
            break;
        case 2:
            if (Punigp->unk440 == 2) {
                Punigp->unk43C = 0;
            }
            break;
        case 3:
            break;
    }
    Punigp->unk440 = Punigp->unk43C;
}

void puniMoveSimple(PuniData* p) {
    if (PSVECMag(&p->vel)) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    }
}

USER_FUNC(evt_puni_force_se_off) {
    if (Punigp->sfx458) {
        psndSFXOff(Punigp->sfx458);
    }
    if (Punigp->sfx468) {
        psndSFXOff(Punigp->sfx468);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_anim) {
    s32* args = event->args;
    evtSetValue(event, args[1], Punidat[evtGetValue(event, args[0])].anim);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_flag) {
    s32* args = event->args;
    evtSetValue(event, args[1], Punidat[evtGetValue(event, args[0])].unk4);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_mode) {
    s32* args = event->args;
    evtSetValue(event, args[1], Punidat[evtGetValue(event, args[0])].unkC);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_anim) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    p->anim = evtGetValue(event, args[1]);
    p->unk11E = 1000;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_target_set_soko) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    PuniTarget* t = &Punigp->targets[idx];
    t->hit = hitNameToPtr((const char*)evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

void puniModeEnterSub(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0++;
        if (p->unk1E0 >= 10) {
            p->alpha += 0.1f;
            if (p->alpha >= 1.0f) {
                p->alpha = 1.0f;
            }
        }
    }
}

void puniModeExitSub(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0++;
        if (p->unk1E0 >= 10) {
            p->alpha -= 0.3f;
            if (p->alpha <= 0.0f) {
                p->alpha = 0.0f;
            }
        }
    }
}

USER_FUNC(evt_puni_setsudan) {
    PuniData* p = &Punidat[evtGetValue(event, event->args[0])];
    if (p->unk4 & 0x400) {
        PuniDokuritsu(p);
        puniDeleteEffect(p);
    }
    return EVT_RETURN_DONE;
}

void puniswTrapGetindex(s32 idx, s32* out) {
    if (idx >= 103) {
        *out = 0;
    } else {
        *out = (swByteGet(idx / 8 + 0x28C) >> (idx % 8)) & 1;
    }
}

USER_FUNC(evt_puni_all_movestop) {
    s32 stop = evtGetValue(event, event->args[0]);
    s32 i;
    for (i = 1; i < 103; i++) {
        PuniData* p = &Punidat[i];
        if (p->unk4 & 0x400) {
            if (stop == 0) {
                p->unk4 &= ~0x200;
            } else {
                p->unk4 |= 0x200;
            }
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_dir) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    p->dir = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(puni_disp_info_kassencheck) {
    s32* args = event->args;
    BOOL ret = FALSE;
    if (Punigp->unk328 == 9 || Punigp->unk328 == 12) {
        ret = TRUE;
    }
    evtSetValue(event, args[0], ret);
    return EVT_RETURN_DONE;
}

const char* npcGetTribeName(const char** name) {
    return *name;
}

PuniData* PuniSakanobori(PuniData* p) {
    while (p->parent != NULL) {
        p = p->parent;
    }
    return p;
}

void PuniChildHagure(PuniData* p) {
    PuniData* c1 = p->child1;
    if (c1 != NULL) {
        PuniData* c;
        c1->unkC = 16;
        p->unk114 = 0;
        c = c1->child1;
        if (c != NULL) {
            PuniData* d;
            c->unkC = 16;
            c1->unk114 = 0;
            d = c->child1;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            d = c->child2;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            PuniDokuritsu(c);
        }
        c = c1->child2;
        if (c != NULL) {
            PuniData* d;
            c->unkC = 16;
            c1->unk114 = 0;
            d = c->child1;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            d = c->child2;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            PuniDokuritsu(c);
        }
        PuniDokuritsu(c1);
    }
    c1 = p->child2;
    if (c1 != NULL) {
        PuniData* c;
        c1->unkC = 16;
        p->unk114 = 0;
        c = c1->child1;
        if (c != NULL) {
            PuniData* d;
            c->unkC = 16;
            c1->unk114 = 0;
            d = c->child1;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            d = c->child2;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            PuniDokuritsu(c);
        }
        c = c1->child2;
        if (c != NULL) {
            PuniData* d;
            c->unkC = 16;
            c1->unk114 = 0;
            d = c->child1;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            d = c->child2;
            if (d != NULL) {
                d->unkC = 16;
                c->unk114 = 0;
                PuniChildHagure(d);
                PuniDokuritsu(d);
            }
            PuniDokuritsu(c);
        }
        PuniDokuritsu(c1);
    }
}

void puniModeExitSubInit(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0 = 0;
        p->npc->flags |= 4;
    }
}

USER_FUNC(evt_puni_winddisable_onoff) {
    Punigp->unk4CC = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

void puniModeEnterSubInit(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0 = 0;
        p->alpha = 0.0f;
        p->npc->flags |= 4;
    }
}

USER_FUNC(evt_puni_pera_onoff) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    if (evtGetValue(event, args[1])) {
        p->npc->flags &= ~2;
    } else {
        p->npc->flags |= 2;
    }
    return EVT_RETURN_DONE;
}

void puniswTrapSetindex(s32 idx, s32* val) {
    if (idx < 103) {
        s32 byte = idx / 8;
        s32 bit = idx % 8;
        s32 v = swByteGet(byte + 0x28C);
        v &= (1 << bit) ^ 0xFF;
        v |= *val << bit;
        swByteSet(byte + 0x28C, (u8)v);
    }
}

USER_FUNC(evt_puni_get_trap_index) {
    s32* args = event->args;
    s32 v;
    puniswTrapGetindex(evtGetValue(event, args[0]), &v);
    evtSetValue(event, args[1], v);
    return EVT_RETURN_DONE;
}

void puniModeDead(PuniData* p) {
    switch (p->unk114) {
        case 0:
            psndSFXOn_3D("SFX_STG2_FIGHT_TOGE3", &p->pos);
            {
                Vec v = {0.0f, 0.0f, 0.0f};
                p->vel = v;
            }
            p->anim = 4;
            p->unk114 = 1;
            break;
        case 1:
            break;
    }
}

USER_FUNC(evt_puni_flag_onoff) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    s32 on = evtGetValue(event, args[1]);
    s32 mask = evtGetValue(event, args[2]);
    if (on) {
        p->unk4 &= ~mask;
    } else {
        p->unk4 |= mask;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_mode) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    s32 mode = evtGetValue(event, args[1]);
    p->unkC = mode;
    p->unkE = mode;
    p->unk114 = 0;
    p->unk11E = 1000;
    PuniDokuritsu(p);
    puniDeleteEffect(p);
    return EVT_RETURN_DONE;
}

void puniModeNormal(PuniData* p) {
    if (p->unk1A0 > 10.0f) {
        p->unkE = p->unkC;
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
    } else if (searchMario(p)) {
        p->unkC = 1;
    }
}

static inline s32 puni_bero_id_filter(s32 id) {
    return bero_id_filter(id);
}

USER_FUNC(evt_puni_dokan_onoff) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    PuniData* p = &Punidat[puni_bero_id_filter(id)] + 103;
    if (on == 0) {
        p->unk4 |= 0x100000;
    } else {
        p->unk4 &= ~0x100000;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_target_flag_onoff) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    s32 mask = evtGetValue(event, args[2]);
    PuniTarget* t = &Punigp->targets[idx];
    if (on) {
        t->flags &= ~mask;
    } else {
        t->flags |= mask;
    }
    return EVT_RETURN_DONE;
}

f32 puni_init_posy(f32 y) {
    f32 best = Punigp->posY[0];
    f32 d = __fabs(y - best);
    f32 d2;

    d2 = __fabs(y - Punigp->posY[1]);
    if (d > d2) {
        d = d2;
        best = Punigp->posY[1];
    }
    d2 = __fabs(y - Punigp->posY[2]);
    if (d > d2) {
        d = d2;
        best = Punigp->posY[2];
    }
    d2 = __fabs(y - Punigp->posY[3]);
    if (d > d2) {
        best = Punigp->posY[3];
    }
    return best;
}

USER_FUNC(evt_puni_get_position) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    evtSetValue(event, args[1], (s32)p->pos.x);
    evtSetValue(event, args[2], (s32)p->pos.y);
    evtSetValue(event, args[3], (s32)p->pos.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_trap_index) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 val = evtGetValue(event, args[1]);
    puniswTrapSetindex(idx, &val);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_count) {
    s32* args = event->args;
    s32 start, end, i;
    s32 count;

    if (evtGetValue(event, args[0]) == 0) {
        start = 1;
        end = 103;
    } else {
        start = 110;
        end = 210;
    }
    count = 0;
    for (i = start; i < end; i++) {
        if ((Punidat[i].unk4 & 0x400) && !(Punidat[i].unk4 & 0x8000)) {
            count++;
        }
    }
    evtSetValue(event, args[1], count);
    return EVT_RETURN_DONE;
}

void puniModeWind_kaiten(PuniData* p) {
    BOOL dir;
    if (p->dir < 180.0f) {
        dir = p->unk1E0;
    } else {
        dir = p->unk1E0 ^ 1;
    }
    if (dir) {
        p->spin += 10.0f;
        if (p->spin >= 360.0f) {
            p->spin -= 360.0f;
        }
    } else {
        p->spin -= 10.0f;
        if (p->spin <= 0.0f) {
            p->spin += 360.0f;
        }
    }
}

void puniParaRecover(PuniData* p) {
    static PuniData* debug;
    s16 old;

    debug = p;
    if (p->unk1AC > 0.001f || p->unkC == 13 || p->unkC == 10) {
        p->regenTimer = p->regenInterval;
        return;
    }
    p->regenTimer--;
    if (p->regenTimer == 0) {
        old = p->hp;
        if (old < p->maxHp) {
            p->hp = old + p->regen;
            {
                s16 m;
                if (p->hp > (m = p->maxHp)) {
                    p->hp = m;
                }
            }
            if (p->hp > old) {
                p->unk8 |= 1;
                p->unk121 = 0;
            }
        }
        p->regenTimer = p->regenInterval;
    }
}

BOOL searchParent(PuniData* p) {
    s32 level = 10000;
    PuniData* found;
    PuniData* q = Punidat;
    s32 i;

    for (i = 0; i < PUNI_DATA_MAX; i++, q++) {
        if ((q->unk4 & 0x80000) && q->child2 == NULL && (q->child1 == NULL || q->unk11A < 2) && q != p &&
            (s16)level > q->unk11A) {
            found = q;
            level = q->unk11A + 1;
        }
    }
    if ((s16)level == 10000) {
        return FALSE;
    }
    p->parent = found;
    p->unk11A = level;
    p->unk118 = found->unk118;
    if (found->child1 == NULL) {
        found->child1 = p;
    } else {
        found->child2 = p;
    }
    return TRUE;
}

PuniData* puniSearchRandom_Mikata(void) {
    s32 idx = qrnd(101) + 1;
    s32 i;
    PuniData* p;
    u32 f;

    for (i = 0; ; i++) {
        if (i == 102) {
            return NULL;
        }
        if (idx == 103) {
            idx = 1;
        }
        p = &Punidat[idx];
        f = p->unk4;
        if ((f & 0x400) && !(f & 0x4000)) {
            return p;
        }
        idx++;
    }
}

PuniData* puniSearchRandom_Teki(void) {
    s32 idx = qrnd(99) + 110;
    s32 i;
    PuniData* p;
    u32 f;

    for (i = 0; ; i++) {
        if (i == 100) {
            return NULL;
        }
        if (idx == 210) {
            idx = 110;
        }
        p = &Punidat[idx];
        f = p->unk4;
        if ((f & 0x400) && !(f & 0x4000)) {
            return p;
        }
        idx++;
    }
}

PuniData* searchMikata(PuniData* self) {
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;
    PuniData* q = &Punidat[1];
    s32 i;

    for (i = 1; i < 103; i++, q++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
    }
    if (minDist < 2500.0f) {
        return found;
    }
    return NULL;
}

PuniData* searchTeki(PuniData* self) {
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;
    PuniData* q = &Punidat[110];
    s32 i;

    for (i = 110; i < 210; i++, q++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
    }
    if (minDist < 2500.0f) {
        return found;
    }
    return NULL;
}

void toge_init_para(PuniData* p, f32 x, f32 y, f32 z) {
    p->anim = 0;
    p->unk114 = 0;
    p->unk11E = 1000;
    p->pos.x = x;
    p->pos.y = y;
    p->pos.z = z;
    p->unk138 = p->pos;
    p->unk190.x = 6.0f;
    p->unk190.y = 2.0f;
    p->unk190.z = 3.0f;
    p->hp = 60;
    p->maxHp = 60;
    p->regen = 10;
    p->regenTimer = 60;
    p->regenInterval = 60;
    p->unk57E = 20;
    p->unk580 = 10;
    p->unk582 = 10;
    p->damage = 0;
    p->unk586 = 0;
    p->unk588 = 50;
    p->unk58A = 70;
    p->unk4 |= 0x101402;
}

void puniMapDataSet(s32 w, s32 h, void* src, f32 x, f32 z) {
    Punimap->x = x;
    Punimap->z = z;
    if (src == NULL) {
        Punimap->enabled = 0;
        return;
    }
    Punimap->width = w;
    Punimap->height = h;
    Punimap->enabled = 1;
    Punimap->src = src;
    Punimap->unk1C = 0;
    Punimap->size = h * (w * 4);
    Punimap->data = _mapAlloc(Punimap->size);
    memcpy(Punimap->src, src, Punimap->size);
}

PuniData* searchBattleMikata(PuniData* self) {
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;
    PuniData* q = &Punidat[1];
    s32 i;

    for (i = 1; i < 103; i++, q++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
    }
    if (minDist < 1000000.0f) {
        return found;
    }
    return NULL;
}

PuniData* searchBattleTeki(PuniData* self) {
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;
    PuniData* q = &Punidat[110];
    s32 i;

    for (i = 110; i < 210; i++, q++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
    }
    if (minDist < 1000000.0f) {
        return found;
    }
    return NULL;
}

PuniData* puniSearchRandom(s32 start, s32 count) {
    s32 idx = qrnd(count - 1) + start;
    s32 i = 0;
    PuniData* p;

    while (TRUE) {
        if (i == count) {
            return NULL;
        }
        if (idx == start + count) {
            idx = start;
        }
        p = &Punidat[idx];
        if ((p->unk4 & 0x400) && !(p->unk4 & 0x4000)) {
            break;
        }
        idx++;
        i++;
    }
    return p;
}

void puniSearch(PuniData* p) {
    if (((s16)(*(s16*)&p->unk116) & 3) == (*(s32*)((u8*)Punigp + 0x1C) & 3)) {
        if (p->unk4 & 1) {
            p->unk1DC = (s32)searchTeki(p);
        } else {
            p->unk1DC = (s32)searchMikata(p);
        }
    }
}

void puniModeChangeAttack(void) {
    s32 i;
    PuniData* p = &Punidat[1];
    for (i = 1; i < 211; i++, p++) {
        if (p->unk4 & 0x400) {
            if ((s32)(s16)p->unkC == 0x1d || ((s32)(s16)p->unkC >= 0 && (s32)(s16)p->unkC < 3)) {
                PuniData* f;
                if (p->unk4 & 1) {
                    f = searchMikata(p);
                } else {
                    f = searchTeki(p);
                }
                if (f) {
                    p->unk1DC = (s32)f;
                    p->unkC = 7;
                    p->unk114 = 0;
                    p->unk11A = 0;
                    p->unk4 |= 0x100000;
                    PuniDokuritsu(p);
                    if (p->effect) {
                        effDelete(p->effect);
                        p->effect = NULL;
                    }
                }
            }
        }
    }
}

void puniModeChangeAway(void) {
    s32 i;
    PuniData* p = &Punidat[1];

    for (i = 1; i <= 102; i++, p++) {
        if (!(p->unk4 & 0x400)) {
            continue;
        }
        if (1000000.0f == p->unk1C0) {
            continue;
        }
        switch (p->unkC) {
            case 0:
            case 1:
            case 2:
            case 4:
            case 16:
                PuniDokuritsu(p);
                p->unkE = p->unkC;
                p->unkC = 5;
                p->unk114 = 0;
                if (p->effect != NULL) {
                    effDelete(p->effect);
                    p->effect = NULL;
                }
                break;
        }
    }
}

void puniswSetindex(s32 base, s32 idx, s32* val, Vec* pos) {
    s32 off = base + idx * 7;
    s32 z = pos->z;
    s32 y = pos->y;
    s32 x = pos->x;
    _swByteSet(off + 150000000, *val);
    _swByteSet(off + 150000001, x & 0xFF);
    _swByteSet(off + 150000002, (x & 0xFF00) >> 8);
    _swByteSet(off + 150000003, y & 0xFF);
    _swByteSet(off + 150000004, (y & 0xFF00) >> 8);
    _swByteSet(off + 150000005, z & 0xFF);
    _swByteSet(off + 150000006, (z & 0xFF00) >> 8);
}

USER_FUNC(evt_puni_zenmetsu_check) {
    s32* args = event->args;
    s32 start;
    s32 end;
    s32 i;
    s32 count;

    if (evtGetValue(event, args[0]) == 0) {
        start = 1;
        end = 103;
    } else {
        start = 110;
        end = 210;
    }
    count = 0;
    for (i = start; i < end; i++) {
        if ((Punidat[i].unk4 & 0x400) && !(Punidat[i].unk4 & 0x4000)) {
            count++;
        }
    }
    if (count == 0) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}

void puniswGetindex(s32 base, s32 idx, s32* val, Vec* pos) {
    u8 b0, b1, b2, b3, b4, b5, b6;
    s32 off;
    s32 x;
    s32 y;
    s32 z;

    off = base + idx * 7;
    b0 = _swByteGet(off + 150000000);
    b1 = _swByteGet(off + 150000001);
    b2 = _swByteGet(off + 150000002);
    b3 = _swByteGet(off + 150000003);
    b4 = _swByteGet(off + 150000004);
    b5 = _swByteGet(off + 150000005);
    b6 = _swByteGet(off + 150000006);

    *val = b0;
    x = b1 + (b2 << 8);
    if (x & 0x8000) {
        x |= 0xFFFF0000;
    }
    y = b3 + (b4 << 8);
    if (y & 0x8000) {
        y |= 0xFFFF0000;
    }
    z = b5 + (b6 << 8);
    if (z & 0x8000) {
        z |= 0xFFFF0000;
    }
    pos->x = x;
    pos->y = y;
    pos->z = z;
}

void puniMapFindbuff(Vec* pos) {
    s32 bx, bz;
    s32 idx;
    u16 lvl;
    s32 i, n, w;
    s32 changed;
    f32 px, pz;
    if (Punimap->enabled) {
        if (Punimap->x < pos->y && Punimap->z > pos->y) {
            memcpy(Punimap->data, Punimap->src, Punimap->size);
            Punimap->unk1C = 1;
            px = pos->x;
            pz = pos->z;
            switch (Punigp->mapKind) {
                case 0:
                    break;
                case 1:
                    puniMapdata_MRI_06_getidx(px, pz, &bx, &bz);
                    break;
                case 2:
                    puniMapdata_MRI_09_getidx(px, pz, &bx, &bz);
                    break;
                case 3:
                    puniMapdata_MRI_16_getidx(px, pz, &bx, &bz);
                    break;
            }
            idx = bx + Punimap->width * bz;
            if (idx < 0) {
                Punimap->unk1C = 0;
            }
            if (Punimap->unk1C) {
                Punimap->data[idx] |= 1;
                lvl = 1;
                do {
                    changed = 0;
                    n = Punimap->width * Punimap->height;
                    for (i = 0; i < n; i++) {
                        u16* d = Punimap->data;
                        u16 v = d[i];
                        if (v != 0xFFFF && lvl == (v & 0xFFF)) {
                            u16 nv;
                            int df, sg;
                            w = Punimap->width;
#define CHK(k)     nv = d[k];     if ((nv & 0xFF) == 0 && (nv & 0xFF) < lvl) {         df = (nv & 0xF000) - (v & 0xF000);         sg = df >> 31;         if (((df ^ sg) - sg) <= 0x1000) {             changed = 1;             d[k] = nv | (u16)(lvl + 1);         }     }
                            CHK(i - w)
                            CHK(i + w)
                            CHK(i - 1)
                            CHK(i + 1)
#undef CHK
                        }
                    }
                    lvl++;
                } while (changed);
            }
        } else {
            Punimap->unk1C = 0;
        }
    }
}

void puniTargetSearch(PuniData* p) {
    s32 i;
    PuniTarget* t = Punigp->targets;
    f32 d;

    p->unk1B4 = -1;
    p->unk1B8 = 1000000.0f;
    p->unk1BC = -1;
    p->unk1C0 = 1000000.0f;
    for (i = 0; i < 10; i++, t++) {
        if (!(t->flags & 1)) {
            continue;
        }
        if (32.0 < __fabs(p->pos.y - t->pos.y)) {
            continue;
        }
        if (t->flags & 4) {
            d = PSVECSquareDistance(&p->pos, &t->pos);
            if (p->unk1C0 > d) {
                p->unk1BC = i;
                p->unk1C0 = d;
            }
        }
        if (t->flags & 2) {
            d = PSVECSquareDistance(&p->pos, &t->pos);
            if (p->unk1B8 > d) {
                p->unk1B4 = i;
                p->unk1B8 = d;
            }
        }
    }
}

USER_FUNC(evt_puni_landon_check) {
    s32* args = event->args;
    s32 kind = evtGetValue(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    s32 start;
    s32 end;
    s32 i;
    s32 count;
    PuniData* p;

    if (kind == 0) {
        start = 1;
        end = 103;
    } else {
        start = 110;
        end = 210;
    }
    count = 0;
    for (i = start; i < end; i++) {
        p = &Punidat[i];
        if ((p->unk4 & 0x400) && p->pos.y > y) {
            count++;
        }
    }
    if (count == 0) {
        evtSetValue(event, args[2], 1);
    } else {
        evtSetValue(event, args[2], 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_target_set_position) {
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);
    PuniTarget* t = &Punigp->targets[i];
    t->pos.x = evtGetValue(event, args[1]);
    t->pos.y = evtGetValue(event, args[2]);
    t->pos.z = evtGetValue(event, args[3]);
    return EVT_RETURN_DONE;
}

void puniAnimationInit(s16** a, s16** b) {
    PuniAnimSet* s0 = &Punigp->anim[0];
    PuniAnimSet* s1 = &Punigp->anim[1];
    s32 j;
    s32 i;
    s16 v;

    for (i = 0; i < 10; i++) {
        s0->table[i] = a[i];
        for (j = 0;; j++) {
            v = a[i][j];
            if (v == -1) {
                s0->end[i] = v;
                break;
            }
            if (v == -2) {
                s0->end[i] = v;
                break;
            }
        }
        s0->count[i] = j;
        s1->table[i] = b[i];
        for (j = 0;; j++) {
            v = b[i][j];
            if (v == -1) {
                s1->end[i] = v;
                break;
            }
            if (v == -2) {
                s1->end[i] = v;
                break;
            }
        }
        s1->count[i] = j;
    }
}

void puniAnimationInit2(void) {
    char (*n)[16];
    n = (char (*)[16])&Punigp->unkA4[0];
    strcpy(n[0], "S_1"); strcpy(n[1], "W_1"); strcpy(n[2], "R_1"); strcpy(n[3], "D_1"); strcpy(n[4], "D_2");
    strcpy(n[5], "F_1"); strcpy(n[6], "Z_1"); strcpy(n[7], "J_1A"); strcpy(n[8], "J_1B"); strcpy(n[9], "B_1");
    n = (char (*)[16])&Punigp->unkA4[160];
    strcpy(n[0], "S_1"); strcpy(n[1], "W_1"); strcpy(n[2], "R_1"); strcpy(n[3], "D_1"); strcpy(n[4], "D_2");
    strcpy(n[5], "F_1"); strcpy(n[6], "Z_1"); strcpy(n[7], "J_1A"); strcpy(n[8], "J_1B"); strcpy(n[9], "B_1");
    n = (char (*)[16])&Punigp->unkA4[320];
    strcpy(n[0], "S_1"); strcpy(n[1], "W_1"); strcpy(n[2], "R_1"); strcpy(n[3], "D_1"); strcpy(n[4], "D_2");
    strcpy(n[5], "F_1"); strcpy(n[6], "Z_1"); strcpy(n[7], "J_1A"); strcpy(n[8], "J_1B"); strcpy(n[9], "B_1");
    n = (char (*)[16])&Punigp->unkA4[480];
    strcpy(n[0], "S_1"); strcpy(n[1], "W_1"); strcpy(n[2], "R_1"); strcpy(n[3], "D_2"); strcpy(n[4], "D_2");
    strcpy(n[5], "F_1"); strcpy(n[6], "Z_1"); strcpy(n[7], "J_1A"); strcpy(n[8], "J_1B"); strcpy(n[9], "B_1");
}


void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames);

typedef struct PuniAnimTarget {
    u8 unk0[4];
    f32 rotY;     // 0x4
    f32 rotZ;     // 0x8
    f32 rotX;     // 0xC
    u8 unk10[4];
    f32 alpha;    // 0x14
    f32* mtx;     // 0x18
    s32 frame;    // 0x1C
} PuniAnimTarget;

void puniAnimation(PuniData* p, PuniAnimTarget* t) {
    NpcEntry* npc;
    char* names;
    PuniAnimSet* set;
    s32 ofs;
    s32 show;
    s16* tbl;
    s32 cnt;
    s32 end;
    s32 f;

    if (p->unk4 & 0x40000) {
    } else if (p->unk4 & 0x1E0) {
        if (p->unk4 & 0x20) {
            npc = npcNameToPtr("\203K\203C\203hsp");
            names = (char*)&Punigp->unkA4[0];
        } else if (p->unk4 & 0x40) {
            npc = npcNameToPtr("\203K\203C\203h\226\205sp");
            names = (char*)&Punigp->unkA4[160];
        } else if (p->unk4 & 0x80) {
            npc = npcNameToPtr("\202\277\202\321\203g\203Qsp");
            names = (char*)&Punigp->unkA4[320];
        } else if (p->unk4 & 0x100) {
            npc = npcNameToPtr("\203\211\203C\203o\203\213sp");
            names = (char*)&Punigp->unkA4[480];
        } else {
            npc = npcNameToPtr("\203\211\203C\203o\203\213sp");
            names = (char*)&Punigp->unkA4[480];
        }
        ofs = p->unk1A4;
        if (p->unk4 & 0x1000000) {
            p->unk124++;
        } else {
            if (p->unkC != 2) {
                ofs = *(s16*)&p->unk116;
            } else {
                ofs /= 8;
                if (p->anim == 0) {
                    ofs += *(s16*)&p->unk116 * 40;
                }
            }
            p->unk124 = gp->retraceCount + ofs;
        }
        if (!(p->unk4 & 0x20000)) {
            animPoseSetAnim(npc->poseId, names + p->anim * 16, 1);
            animPoseSetLocalTime(npc->poseId, p->unk124);
        }
        show = 0;
        if (p->unk4 & 0x400) show = 1;
        if (p->unk4 & 0x800) show = 0;
        if (show) {
            npc->position.x = p->pos.x + *(f32*)&p->unk144;
            npc->position.y = p->pos.y + p->unk148;
            npc->position.z = p->pos.z + *(f32*)&p->unk14C;
        } else {
            npc->position.x = 0.0f;
            npc->position.y = -1000.0f;
            npc->position.z = 0.0f;
        }
        t->mtx[3] = 0.0f;
        t->mtx[7] = -1000.0f;
        t->mtx[11] = 0.0f;
        npc->scale.x = p->alpha;
        npc->scale.y = p->alpha;
        npc->direction = p->dir;
        npc->rotation.z = p->spin;
        npc->rotationOffset.y = p->unk188;
    } else {
        set = &Punigp->anim[0];
        if (p->unk4 & 0x8) set = &Punigp->anim[0];
        if (p->unk4 & 0x10) set = &Punigp->anim[1];
        tbl = set->table[p->anim];
        cnt = set->count[p->anim];
        end = set->end[p->anim];
        ofs = p->unk1A4;
        if (p->unk4 & 0x1000000) {
            f = p->unk124 % cnt;
            if (end == -2 && cnt <= p->unk124) f = cnt - 1;
            t->frame = tbl[f];
            p->unk124++;
        } else {
            if (p->unkC != 2) {
                ofs = *(s16*)&p->unk116;
            } else {
                ofs /= 8;
                if (p->anim == 0) {
                    ofs += *(s16*)&p->unk116 * (cnt / 3);
                }
            }
            t->frame = tbl[(u32)(gp->retraceCount + ofs) % (u32)cnt];
        }
        show = 0;
        if (p->unk4 & 0x400) show = 1;
        if (p->unk4 & 0x800) show = 0;
        if (show) {
            t->mtx[3] = p->pos.x + *(f32*)&p->unk144;
            t->mtx[7] = p->pos.y + p->unk148;
            t->mtx[11] = p->pos.z + *(f32*)&p->unk14C;
        } else {
            t->mtx[3] = 0.0f;
            t->mtx[7] = -1000.0f;
            t->mtx[11] = 0.0f;
        }
        t->alpha = p->alpha;
        t->rotY = -p->dir;
        t->rotZ = p->spin;
        t->rotX = p->unk188;
    }
    p->unk11E = p->anim;
}

PuniData* searchBattle(PuniData* self, s32 start, s32 count, f32 maxDist) {
    s32 i;
    PuniData* q;
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;

    q = &Punidat[start];
    for (i = start; i < start + count; i++, q++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
    }
    if (minDist < maxDist) {
        return found;
    }
    return NULL;
}

void puniModeDodai(PuniData* p) {
    Vec v;

    switch (p->unk114) {
        case 0:
            PSVECSubtract(&p->pos, &p->unk1F8, &v);
            if (PSVECMag(&v) < 10.0f) {
                static Vec zero = {0.0f, 0.0f, 0.0f};
                p->vel = zero;
                p->unkC = 16;
                p->unk114 = 0;
            } else {
                PSVECNormalize(&v, &v);
                v.y = 0.0f;
                PSVECScale(&v, &v, 1.0f);
                PSVECSubtract(&p->vel, &v, &p->vel);
                p->unk174 = 3.0f;
            }
            break;
    }
}

USER_FUNC(evt_puni_set_position) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    p->pos.x = evtGetValue(event, args[1]);
    p->pos.y = evtGetValue(event, args[2]);
    p->pos.z = evtGetValue(event, args[3]);
    p->unk138 = p->pos;
    return EVT_RETURN_DONE;
}

void puni_init_para(PuniData* p, f32 x, f32 y, f32 z) {
    p->unk114 = 0;
    p->anim = 0;
    p->unk11E = 1000;
    p->pos.x = x;
    p->pos.y = y;
    p->pos.z = z;
    p->unk138 = p->pos;
    p->unk190.x = 6.0f;
    p->unk190.y = 2.0f;
    p->unk190.z = 3.0f;
    p->hp = 60;
    p->maxHp = 60;
    p->regen = 10;
    p->regenTimer = 60;
    p->regenInterval = 60;
    p->unk57E = 20;
    p->unk580 = 10;
    p->unk582 = 10;
    p->damage = 0;
    p->unk586 = 0;
    p->unk588 = 50;
    p->unk58A = 70;
    p->parent = NULL;
    p->child1 = NULL;
    p->child2 = NULL;
    PuniDokuritsu(p);
    p->unk4 |= 0x1401;
}

void puniModePreupdraft(PuniData* p) {
    Vec pos;

    switch (p->unk114) {
        case 0:
            pos = p->pos;
            pos.y += 15.0f;
            pos.z += 3.0f;
            p->effect = effPuniBalloonEntry(0, pos.x, pos.y, pos.z, 1.5f);
            p->unk128 = rand() % 201 + 30;
            p->unk114 = 1;
        case 1:
            if (p->unk128-- == 0) {
                p->npc->flags |= 4;
                p->unkC = 19;
                p->unk114 = 0;
            }
            break;
    }
}

void puniModeParentpre(PuniData* p) {
    s16 best = 10000;
    PuniData* found;
    PuniData* q = Punidat;
    s32 i;
    Vec v;

    for (i = 211; i != 0; i--, q++) {
        if (!(q->unk4 & 0x80000)) {
            continue;
        }
        if (q->child2 != NULL) {
            continue;
        }
        if (q->child1 != NULL && q->unk11A >= 2) {
            continue;
        }
        if (q == p) {
            continue;
        }
        if (best > q->unk11A) {
            found = q;
            best = q->unk11A;
            best++;
        }
    }
    if (best != 10000) {
        p->parent = found;
        p->unk11A = best;
        p->unk118 = found->unk118;
        if (found->child1 == NULL) {
            found->child1 = p;
        } else {
            found->child2 = p;
        }
    }
    p->unkC = 2;
    p->unk4 |= 0x180000;
    PSVECSubtract(&p->parent->pos, &p->pos, &v);
    p->unk1B0 = p->unk1A8 = PSVECMag(&v);
    p->unk128 = 0;
    p->unk114 = 0;
    p->anim = 1;
}

void puniModeParent(PuniData* p) {
    Vec v;
    s32 bx, bz;
    s32 flag;
    u16 info;
    if ((u16)p->unk11E < 2) {
        p->anim = (p->unk1AC < 1.5f) ? 0 : 1;
        p->unk120 = 0;
    } else {
        p->anim = (p->unk1AC < 1.5f) ? 0 : 1;
        if ((u16)p->unk11E == p->anim) {
            p->unk120 = 0;
        } else if (++p->unk120 <= 8) {
            p->anim = p->unk11E;
        } else {
            p->unk120 = 0;
        }
    }
    if (p->unk4 & 0x200) {
        return;
    }
    flag = 0;
    PSVECSubtract(&p->parent->pos, &p->pos, &v);
    p->unk1A8 = PSVECMag(&v);
    if (!(bero_get_BeroEXEC() & 1)) {
        if (32.0 < __fabs(p->pos.y - p->parent->pos.y)) {
            flag = 1;
        } else if (p->unk1A8 > 80.0f) {
            flag = 1;
        } else {
            p->unk128 = 0;
        }
    }
    if (0.1f + p->unk1A8 <= p->unk1B0) {
        flag = 0;
        p->unk128 = 0;
    }
    if (Punimap->unk1C != 0) {
        flag = 0;
    }
    if (flag) {
        if (++p->unk128 > 30) {
            p->unkC = 16;
            p->unk114 = 0;
            PuniChildHagure(p);
            PuniDokuritsu(p);
            return;
        }
    }
    p->unk1B0 = p->unk1A8;
    if (p->unk1A0 > 10.0f) {
        p->unkE = p->unkC;
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
        return;
    }
    if (p->unk1BC != -1 && p->unk1C0 < 10000.0f) {
        Punigp->unk43C = 2;
        return;
    }
    if (p->unk1B4 != -1) {
        PuniDokuritsu(p);
        p->unkC = 4;
        p->unk114 = 0;
        return;
    }
    if (Punimap->enabled != 0 && Punimap->unk1C != 0) {
        switch (Punigp->mapKind) {
            case 0:
                break;
            case 1:
                puniMapdata_MRI_06_getidx(p->pos.x, p->pos.z, &bx, &bz);
                break;
            case 2:
                puniMapdata_MRI_09_getidx(p->pos.x, p->pos.z, &bx, &bz);
                break;
            case 3:
                puniMapdata_MRI_16_getidx(p->pos.x, p->pos.z, &bx, &bz);
                break;
        }
        info = puniMapGetInfo(bx, bz);
        if (info != 0xFFFF && (info & 0xFFF) > 2) {
            PuniDokuritsu(p);
            p->unkC = 3;
            p->unk114 = 0;
            return;
        }
    }
    if (p->unk1A8 > p->parent->alpha + p->unk190.x + p->unk190.y + p->unk190.z) {
        PSVECNormalize(&v, &v);
        v.y = 0.0f;
        PSVECScale(&v, &v, 1.0f);
        PSVECAdd(&p->vel, &v, &p->vel);
        p->unk174 = 3.0f;
    }
}

USER_FUNC(evt_puni_korokoro) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];

    switch (p->anim) {
        case 5:
            if (isFirstCall) {
                if (p->unk4 & 8) {
                    p->unk188 = 8.0f;
                } else {
                    p->unk148 = 8.0f;
                }
            }
            p->spin += evtGetValue(event, args[1]);
            return EVT_RETURN_BLOCK;
        default:
            if (p->unk4 & 8) {
                p->unk188 = 0.0f;
            } else {
                p->unk148 = 0.0f;
            }
            p->spin = evtGetValue(event, args[2]);
            return EVT_RETURN_DONE;
    }
}

#define F(p, o) (*(s32*)((u8*)(p) + (o)))
#define FF(p, o) (*(f32*)((u8*)(p) + (o)))
void puniModeMass(PuniData* p) {
    PuniTarget* t = &Punigp->targets[p->unk1B4];
    Vec v;
    s32 a, b;
    if (p->unk1B4 == -1) {
        if (p->unkE == 24) {
            p->unkC = 24;
        } else {
            p->unkC = 1;
        }
        p->anim = 0;
        p->unk114 = 0;
        return;
    }
    if (p->unk1BC != -1 && p->unk1C0 < 10000.0f) {
        Punigp->unk43C = 2;
        return;
    }
    a = gp->retraceCount & 0xF;
    b = *(s16*)&p->unk116 & 0xF;
    if (Punigp->unk328 == 18) {
        a = b;
    }
    if (a == b && p->unk1A0 > 10.0f) {
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
        return;
    }
    if (p->unk1B8 > 100.0f) {
        if (p->unk1B8 < 3600.0f && (qrnd(3) == 0)) {
            PSVECSubtract(&p->pos, &t->pos, &v);
            PSVECNormalize(&v, &v);
            v.z = 0.0f;
            PSVECScale(&v, &v, 1.5f);
            PSVECAdd(&p->vel, &v, &p->vel);
        } else {
            PSVECSubtract(&t->pos, &p->pos, &v);
            PSVECNormalize(&v, &v);
            v.z = 0.0f;
            PSVECScale(&v, &v, 5.0f);
            PSVECAdd(&p->vel, &v, &p->vel);
        }
    } else {
        p->vel.x = 0.0f;
        p->vel.y = 0.0f;
        p->vel.z = 0.0f;
    }
    switch (p->unk114) {
        case 0:
            if (p->vel.x < 0.0f) {
                p->dir = 270.0f;
            } else {
                p->dir = 90.0f;
            }
            p->unk114 = 1;
            if (Punigp->unk328 == 13) {
                p->unk114 = 10;
            }
            if (Punigp->unk328 == 18) {
                p->unk114 = 10;
            }
            p->unk1E0 = 0;
            F(p,0x1E4) = 0;
            break;
        case 10:
            if (p->unk1E0 == 120) {
                p->unk1E0 = 0;
                F(p,0x1E4) = 0;
                if (rand() % 2) {
                    p->unk1F8 = (Vec){0.0f, 0.0f, 2.0f};
                } else {
                    p->unk1F8 = (Vec){0.0f, 0.0f, -2.0f};
                }
                p->unk114 = 11;
            } else if (p->pos.x == p->unk138.x && p->pos.z == p->unk138.z) {
                p->unk1E0++;
            }
            break;
        case 11:
            if (F(p,0x1E4) == 30) {
                p->unk114 = 10;
            } else {
                PSVECAdd(&p->vel, &p->unk1F8, &p->vel);
                F(p,0x1E4)++;
            }
            break;
    }
}

void puniModeAwayjump(PuniData* p) {
    switch (p->unk114) {
        case 0:
            F(p,0x1C8) = ((s32*)&gp->renderTime)[0];
            F(p,0x1CC) = ((s32*)&gp->renderTime)[1];
            F(p,0x1E4) = 0;
            FF(p,0x1EC) = p->pos.z;
            FF(p,0x1F0) = -72.0f;
            FF(p,0x1F4) = -FF(p,0x1F0);
            p->unk114 = 1;
            p->anim = 7;
            p->unk124 = 0;
            p->unk4 |= 0x1000000;
            if (p->unk4 & 0x80) {
                psndSFXOn_3D("SFX_STG2_TOGETTI_JUMP1", &p->pos);
            } else {
                psndSFXOn_3D("SFX_STG2_PUNI_JUMP1", &p->pos);
            }
        case 1: {
            u32 t = (((u32*)&gp->renderTime)[1] - F(p,0x1CC)) / (*(u32*)0x800000F8 / 4 / 1000);
            if (t > 100 && F(p,0x1E4) == 0) {
                F(p,0x1E4) = 1;
                p->anim = 8;
                p->unk124 = 0;
            }
            if ((s32)t < 200) {
                f32 f = (f32)(s32)t / 200.0f;
                p->pos.z = f * (FF(p,0x1F0) * f + FF(p,0x1F4)) + FF(p,0x1EC);
            } else {
                p->pos.z = FF(p,0x1EC);
                p->unkC = 6;
                p->anim = 2;
                p->unk4 &= ~0x1000000;
                p->unk114 = 0;
            }
            break;
        }
    }
}

#define PF(p, o) (*(void**)((u8*)(p) + (o)))
int puniMoveAtari(PuniData* p, Vec* start, Vec* dir, int reflect, f32 dist);

typedef int (*PuniMoveAtariV)(PuniData*, Vec, Vec, int, f32);
static const Vec puni_away_zero0 = {0.0f, 0.0f, 0.0f};
static const Vec puni_away_zero1 = {0.0f, 0.0f, 0.0f};
static const Vec puni_away_down = {0.0f, -1.0f, 0.0f};
static const Vec puni_away_zero2 = {0.0f, 0.0f, 0.0f};
#pragma dont_inline on
int puniModeAway_sub(PuniData* p) {
    Vec dir;
    Vec start;
    f32 mag = PSVECMag(&p->vel);
    start = p->pos;
    start.y = start.y + 1.0f;
    if (0.0f != mag) {
        PSVECNormalize(&p->vel, &dir);
    } else {
        dir = puni_away_zero0;
    }
    ((PuniMoveAtariV)puniMoveAtari)(p, start, dir, 0, mag);
    if (PF(p, 0x210) != NULL || PF(p, 0x214) != NULL) {
        if (PF(p, 0x210) != NULL && (((s32*)PF(p, 0x210))[1] & 4)) {
            FF(p, 0x168) = -FF(p, 0x560);
            FF(p, 0x16C) = -FF(p, 0x564);
            FF(p, 0x170) = -FF(p, 0x568);
            p->unk114 = 1;
            return 1;
        } else if (PF(p, 0x214) != NULL && (((s32*)PF(p, 0x214))[1] & 4)) {
            FF(p, 0x168) = -FF(p, 0x560);
            FF(p, 0x16C) = -FF(p, 0x564);
            FF(p, 0x170) = -FF(p, 0x568);
            p->unk114 = 1;
            return 1;
        } else {
            p->unk114 = 10;
            return 2;
        }
    }
    return 0;
}
#pragma dont_inline reset

void puniModeAway(PuniData* p) {
    PuniTarget* t = &Punigp->targets[p->unk1BC];
    Vec sub;
    Vec start;
    Vec dir;
    f32 dist, hx, hy, hz, nx, ny, nz;
    if (p->unk1BC == -1) {
        p->vel = puni_away_zero1;
        p->unkC = 1;
        p->unk114 = 0;
        p->anim = 0;
        return;
    }
    if (p->unk1A0 > 10.0f) {
        p->unkE = p->unkC;
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
        return;
    }
    switch (p->unk114) {
        case 0:
            if (p->unk1C0 < 90000.0f) {
                PSVECSubtract(&p->pos, &t->pos, &sub);
                PSVECNormalize(&sub, &sub);
                sub.y = 0.0f;
                PSVECScale(&sub, &sub, 1.4f);
                PSVECAdd(&p->vel, &sub, &p->vel);
                p->unk174 = 4.2f;
                puniModeAway_sub(p);
            }
            break;
        case 1:
            p->unk8 |= 4;
            PSVECNormalize((Vec*)&FF(p, 0x168), &sub);
            PSVECScale(&sub, &p->vel, p->unk190.x);
            PSVECAdd(&p->pos, &p->vel, &p->pos);
            start = p->pos;
            start.y = 1.0f + start.y;
            start.y = start.y + 0.2f;
            dir = puni_away_down;
            dist = 2.0f;
            if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, start.x, start.y, start.z, dir.x, dir.y, dir.z) == NULL) {
                p->vel = puni_away_zero2;
                p->unkC = 17;
                p->anim = 0;
                p->unk114 = 0;
            } else {
                p->unk114 = 0;
            }
            break;
        case 10:
            break;
    }
}

void puniMapdata_MRI_09_getpos(s32 bx, s32 bz, f32* x, f32* z) {
    switch (bx) {
        case 1:
            *x = -250.0f;
            break;
        case 2:
            *x = -145.0f;
            break;
        case 3:
            *x = 0.0f;
            break;
        case 4:
            *x = 145.0f;
            break;
        case 5:
            *x = 260.0f;
            break;
        default:
            *x = -1000.0f;
            break;
    }
    switch (bz) {
        case 1:
            *z = -120.0f;
            break;
        case 2:
            *z = 0.0f;
            break;
        case 3:
            *z = 105.0f;
            break;
        case 4:
            *z = 160.0f;
            break;
        default:
            *z = -1000.0f;
            break;
    }
}

BOOL _puniVAtari(PuniData* p, Vec* from, Vec* to) {
    Vec start;
    Vec dir;
    f32 hz;
    f32 hy;
    f32 hx;
    f32 nz;
    f32 ny;
    f32 nx;
    f32 dist;

    PSVECSubtract(to, from, &dir);
    if (0.0f == dir.x && 0.0f == dir.z) {
        p->pos = *from;
        return TRUE;
    }
    start = *from;
    PSVECNormalize(&dir, &dir);
    dist = PSVECMag(&dir);
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, start.x, start.y, start.z, dir.x, dir.y, dir.z) ==
        NULL) {
        p->pos = *to;
        return TRUE;
    }
    return FALSE;
}

void puni_puni_disp(CameraId camId, void* param) {
    MapTevCallbackInfo info;
    s32 off;
    MapTevCallbackInfo* ip;
    s32 i;
    PunidrvPose* pose;

    puniLoadRenderMode();
    puniLoadVertex();
    puniLoadTexture();
    puniLoadTev();
    if (!_swGet(3)) {
        puniDraw();
    } else {
        for (ip = &info, i = 0, off = 0; i < puniGetPoseNum(); i++, off += sizeof(PunidrvPose)) {
            pose = (PunidrvPose*)((u8*)puniGetPosePtr() + off);
            ip->tevStage = 1;
            ip->texCoord = 1;
            ip->texMap = 1;
            ip->field_0x18 = 0;
            ip->mtx = *pose->mtx;
            envSetYami(ip);
            GXSetNumTexGens(ip->texMap);
            GXSetNumTevStages(ip->tevStage);
            GXSetNumIndStages(ip->field_0x18);
            puniPoseDraw(i);
        }
    }
    puniLoadTextureExit();
}

static const Vec puni_fall_dir = {0.0f, -1.0f, 0.0f};
static const Vec puni_fall_vel = {0.0f, 0.0f, 0.0f};

void puniModeChangeFallCheck(void) {
    Vec dir;
    Vec pos;
    Vec nrm;
    Vec hit;
    f32 dist;
    s32 i;
    PuniData* p = &Punidat[1];

    for (i = 1; i <= 102; i++, p++) {
        if (!(p->unk4 & 0x400)) {
            continue;
        }
        pos = p->pos;
        pos.y = 1.0f + pos.y;
        dir = puni_fall_dir;
        dist = 2.0f;
        if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &nrm.x, &nrm.y, &nrm.z, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z) ==
            NULL) {
            PuniDokuritsu(p);
            p->vel = puni_fall_vel;
            p->unkC = 17;
            p->unk114 = 0;
            if (p->effect != NULL) {
                effDelete(p->effect);
                p->effect = NULL;
            }
        }
    }
}

void puniFukki(PuniData* self) {
    s32 i;
    PuniData* p = &Punidat[1];

    for (i = 1; i <= 102; i++, p++) {
        if ((p->unk4 & 0x400) && p->unkC == 16) {
            if (!(32.0 < __fabs(self->pos.y - p->pos.y)) && PSVECSquareDistance(&self->pos, &p->pos) < 900.0f) {
                p->unkC = 1;
                puniFukki(p);
                puniDeleteEffect(p);
            }
        }
    }
}

USER_FUNC(evt_puni_all_fall_check) {
    s32 i;
    PuniData* p = &Punidat[1];
    Vec hit;
    Vec nrm;
    Vec pos;
    Vec dir;
    f32 dist;

    for (i = 1; i <= 102; i++, p++) {
        if (!(p->unk4 & 0x400)) {
            continue;
        }
        pos = p->pos;
        pos.y = 1.0f + pos.y;
        dir = puni_fall_dir;
        dist = 2.0f;
        if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &nrm.x, &nrm.y, &nrm.z, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z) ==
            NULL) {
            PuniDokuritsu(p);
            p->vel = puni_fall_vel;
            p->unkC = 17;
            p->unk114 = 0;
            if (p->effect != NULL) {
                effDelete(p->effect);
                p->effect = NULL;
            }
        }
    }
    return EVT_RETURN_DONE;
}

s32 puniPositionCheck(PuniData* p) {
    f32* r = (f32*)Punigp->unk350;
    s32 in = 0;
    Vec pos;
    Vec dir;
    Vec hit;
    Vec nrm;
    f32 dist;
    f32 hi, lo;
    hi = r[0];
    lo = r[1];
    if (-1000.0f != hi && p->pos.y < hi && p->pos.y > lo) {
        in = 1;
    }
    hi = r[2];
    lo = r[3];
    if (-1000.0f != hi && p->pos.y < hi && p->pos.y > lo) {
        in = 1;
    }
    if (in == 0) {
        return 1;
    }
    pos = p->pos;
    dir = puni_fall_dir;
    pos.y += 1.0f;
    dist = 3.0f;
    if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &nrm.x, &nrm.y, &nrm.z, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z) == NULL) {
        return 2;
    }
    return 0;
}

void puniPositionRecover(PuniData* p) {
    p->pos = Punigp->unk344;
    p->pos.x += randf(0.0f, 2.0f) - 1.0f;
    p->pos.z += randf(0.0f, 2.0f) - 1.0f;
    p->unk138 = p->pos;
}

#define PF(p, o) (*(void**)((u8*)(p) + (o)))
#define PV(p, o) ((Vec*)((u8*)(p) + (o)))

int puniMoveAtari(PuniData* p, Vec* start, Vec* dir, int reflect, f32 dist) {
    Vec hit;
    Vec old;
    Vec diff;
    Vec refl;
    f32 d;
    int ret = 1;
    f32 nx, ny, nz;
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    if (p->unk4 & 0x1000) {
        PF(p, 0x210) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start->x, start->y, start->z, dir->x, dir->y, dir->z);
    }
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        if (reflect) {
            C_VECReflect(dir, &hit, &refl);
            PSVECScale(&refl, &p->vel, dist);
            ret = 0;
        }
        PSVECScale(&hit, &hit, -(dist - d) * PSVECDotProduct(dir, &hit) + 0.1f);
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            start->x = old.x;
            start->y = old.y;
            start->z = old.z;
            start->y += 1.0f;
            PF(p, 0x214) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start->x, start->y + 1.0f, start->z, diff.x, diff.y, diff.z);
            if (PF(p, 0x214) != NULL) {
                p->pos = old;
            }
        }
    }
    return ret;
}

void unk_mri_000095f0(PuniData* p, Vec* start, Vec* dir, f32 dist) {
    Vec hit;
    Vec old;
    Vec diff;
    f32 d;
    f32 nx, ny, nz;
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    PF(p, 0x210) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start->x, start->y, start->z, dir->x, dir->y, dir->z);
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else if (Punigp->unk328 != 18) {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        PSVECScale(&hit, &hit, -(dist - d) * PSVECDotProduct(dir, &hit) + 0.1f);
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
            if (PF(p, 0x214) != NULL) {
                p->pos = old;
            }
        }
    }
}

void unk_mri_0000980c(PuniData* p, Vec* start, Vec* dir, f32 dist) {
    Vec hit;
    Vec old;
    Vec diff;
    Vec refl;
    f32 d;
    f32 nx, ny, nz;
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    if (p->unk4 & 0x1000) {
        PF(p, 0x210) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start->x, start->y, start->z, dir->x, dir->y, dir->z);
    }
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        C_VECReflect(dir, &hit, &refl);
        PSVECScale(&refl, &p->vel, dist);
        PSVECScale(&hit, &hit, -(dist - d) * PSVECDotProduct(dir, &hit) + 0.1f);
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            start->x = old.x;
            start->y = old.y;
            start->z = old.z;
            start->y += 1.0f;
            PF(p, 0x214) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start->x, start->y + 1.0f, start->z, diff.x, diff.y, diff.z);
            if (PF(p, 0x214) != NULL) {
                p->pos = old;
            }
        }
    }
}

void puniMoveDecel(PuniData* p) {
    Vec start;
    Vec dir;
    Vec hit;
    Vec old;
    Vec diff;
    Vec refl;
    f32 d;
    f32 nx, ny, nz;
    f32 dist = PSVECMag(&p->vel);
    if (dist == 0.0f) {
        return;
    }
    if (dist > 1.0f) {
        if (p->vel.x < 0.0f) {
            p->dir = 270.0f;
        } else {
            p->dir = 90.0f;
        }
    }
    if (dist > p->unk174) {
        PSVECScale(&p->vel, &p->vel, p->unk174 / dist);
        dist = p->unk174;
    }
    start = p->pos;
    start.y += 1.0f;
    PSVECNormalize(&p->vel, &dir);
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    if (p->unk4 & 0x1000) {
        PF(p, 0x210) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start.x, start.y, start.z, dir.x, dir.y, dir.z);
    }
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        C_VECReflect(&dir, &hit, &refl);
        PSVECScale(&refl, &p->vel, dist);
        PSVECScale(&hit, &hit, -(dist - d) * PSVECDotProduct(&dir, &hit) + 0.1f);
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
            if (PF(p, 0x214) != NULL) {
                p->pos = old;
            }
        }
    }
    if (PF(p, 0x210) != NULL || PF(p, 0x214) != NULL) {
        p->unk4 |= 0x400000;
    } else {
        PSVECScale(&p->vel, &p->vel, 0.6f);
        p->unk4 &= ~0x400000;
    }
}

void puniMoveLimitedNormal(PuniData* p) {
    Vec start;
    Vec dir;
    Vec hit;
    Vec old;
    Vec diff;
    Vec refl;
    f32 d;
    f32 nx, ny, nz;
    f32 dist = PSVECMag(&p->vel);
    if (dist == 0.0f) {
        return;
    }
    if (dist > p->unk174) {
        PSVECScale(&p->vel, &p->vel, p->unk174 / dist);
        dist = p->unk174;
    }
    start = p->pos;
    start.y += 1.0f;
    PSVECNormalize(&p->vel, &dir);
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    PF(p, 0x210) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start.x, start.y, start.z, dir.x, dir.y, dir.z);
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        PSVECScale(&hit, &hit, -(dist - d) * PSVECDotProduct(&dir, &hit) + 0.1f);
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
            if (PF(p, 0x214) != NULL) {
                p->pos = old;
            }
        }
    }
    if (PF(p, 0x210) != NULL || PF(p, 0x214) != NULL) {
        p->unk4 |= 0x400000;
    } else {
        p->unk4 &= ~0x400000;
    }
}

void puniMoveNormal(PuniData* p) {
    Vec start;
    Vec dir;
    Vec hit;
    Vec old;
    Vec diff;
    Vec refl;
    f32 d;
    f32 nx, ny, nz;
    f32 dist = PSVECMag(&p->vel);
    if (dist == 0.0f) {
        return;
    }
    start = p->pos;
    start.y += 1.0f;
    PSVECNormalize(&p->vel, &dir);
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    if (p->unk4 & 0x1000) {
        PF(p, 0x210) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, start.x, start.y, start.z, dir.x, dir.y, dir.z);
    }
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        C_VECReflect(&dir, &hit, &refl);
        PSVECScale(&refl, &p->vel, dist);
        PSVECScale(&hit, &hit, -(dist - d) * PSVECDotProduct(&dir, &hit) + 0.1f);
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &d, &nx, &ny, &nz, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
            if (PF(p, 0x214) != NULL) {
                p->pos = old;
            }
        }
    }
    if (PF(p, 0x210) != NULL || PF(p, 0x214) != NULL) {
        p->unk4 |= 0x400000;
    } else {
        p->unk4 &= ~0x400000;
    }
}

void puniModeWonder(PuniData* p) {
    Vec pos;

    switch (p->unk114) {
        case 0:
            psndSFXOn_3D("SFX_STG2_SOAPBALL_BREAK1", &p->pos);
            if (p->effect != NULL) {
                effDelete(p->effect);
                p->effect = NULL;
            }
            pos = p->pos;
            pos.y += 15.0f;
            pos.z += 3.0f;
            p->effect = effPuniBalloonEntry(1, pos.x, pos.y, pos.z, 1.5f);
            p->unk128 = 20;
            p->anim = 9;
            p->unk124 = 0;
            p->unk4 |= 0x1000000;
            p->unk114 = 1;
        case 1:
            if (p->unk128-- == 0) {
                p->npc->flags &= ~4;
                p->unkC = 21;
                p->anim = 1;
                p->unk4 &= ~0x1000000;
                p->unk114 = 0;
            }
            break;
    }
}
