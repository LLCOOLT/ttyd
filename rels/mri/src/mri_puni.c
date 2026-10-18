#include "mri_puni.h"
#include "party.h"
#include "mario/mario_party.h"
#include "driver/camdrv.h"
#include "memory.h"
#include <string.h>
#include "forcedata.h"
#include "mario/mariost.h"
#include "mario/mario.h"
#include "driver/icondrv.h"

#include "driver/swdrv.h"

// FAKE: the original REL kept every function; force_active stops the linker dead-stripping unreferenced ones
#pragma force_active on
#include "evt/evt_seq.h"
#include "evt/evt_npc.h"
#include "pmario_sound.h"
#include "evt/evt_bero.h"
#include "manager/evtmgr_cmd.h"
#include "driver/punidrv.h"
#include "driver/mapdrv.h"
#include <dolphin/gx.h>
extern int rand(void);
void PuniDokuritsu(PuniData* p);
void puniHagurePos(PuniData* p);
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
u16 toge_hag_patern_data[] = { 0, 65535 };
u16* toge_patern_table[] = { toge_nom_patern_data, toge_wlk_patern_data, toge_run_patern_data, toge_dmg_patern_data,
                             toge_dwn_patern_data, toge_rol_patern_data, toge_hag_patern_data, toge_hag_patern_data,
                             toge_hag_patern_data, toge_hag_patern_data };

//.bss
PuniData* Punidat;
PuniWork* Punigp;
PuniTexInfo* Punitex;
PuniMap* Punimap;


static inline s32 puni_bero_id_filter(s32 id) {
    return bero_id_filter(id);
}
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
    PuniData* p;
    s32 i;
    if (Punigp->unk328 == 9 || Punigp->unk328 == 12) {
        for (i = 1; i < 211; i++) {
            p = &Punidat[i];
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
                    puniSinCosRet(*(s16*)&p->unk116[0] + gp->retraceCount * 10, &a.z, &a.x, 9.0f, 9.0f);
                    a.y += 13.0f;
                    iconDispGx(&a, 0, 0x14d, 0.6f);
                    puniSinCosRet(*(s16*)&p->unk116[0] + gp->retraceCount * 10 + 180, &b.z, &b.x, 9.0f, 9.0f);
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

void puniAnimationInit(s16** a, s16** b) {
    PuniAnimSet* s0 = &Punigp->anim[0];
    PuniAnimSet* s1 = &Punigp->anim[1];
    s32 j;
    s32 i;
    s16* p;
    s16 v;
    s32 k;

    for (i = 0; i < 10; i++) {
        s0->table[i] = a[i];
        puniAnimCount(a[i], &s0->count[i], &s0->end[i]);
        s1->table[i] = b[i];
        k = 0; j = 0;
        for (p = b[i];; j++, k++) {
            v = p[k];
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
    s32 cnt;
    s16* tbl;
    s32 end;
    s32 show;
    s32 f;
    s32 ofs;

    if (!(p->unk4 & 0x40000)) {
    if (p->unk4 & 0x1E0) {
        if (p->unk4 & 0x20) {
            npc = npcNameToPtr("\203K\203C\203hsp");
            names = (char*)( &Punigp->unkA4[0]) ;
        } else if (p->unk4 & 0x40) {
            npc = npcNameToPtr("\203K\203C\203h\226\205sp");
            names = (char*)( &Punigp->unkA4[160]) ;
        } else if (p->unk4 & 0x80) {
            npc = npcNameToPtr("\202\277\202\321\203g\203Qsp");
            names = (char*)( &Punigp->unkA4[320]) ;
        } else if (p->unk4 & 0x100) {
            npc = npcNameToPtr("\203\211\203C\203o\203\213sp");
            names = (char*)( &Punigp->unkA4[480]) ;
        } else {
            npc = npcNameToPtr("\203\211\203C\203o\203\213sp");
            names = (char*)( &Punigp->unkA4[480]) ;
        }
        ofs = p->unk1A4;
        if (p->unk4 & 0x1000000) {
            p->unk124++;
        } else {
            if (p->unkC != 2) {
                ofs = *(( s16*)( &p->unk116)) ;
            } else {
                ofs /= 8;
                if (p->anim == 0) {
                    ofs += ( *( (s16*)( &p->unk116 ))) * 40;
                }
            }
            p->unk124 = gp->retraceCount + ofs;
        }
        if (!(p->unk4 & 0x20000)) {
            animPoseSetAnim(npc->poseId, names + ( p->anim * 16) , 1);
            animPoseSetLocalTime(npc->poseId, p->unk124);
        }
        show = 0;
        if (p->unk4 & 0x400) { show = 1;
        }
        if (p->unk4 & 0x800) { show = 0;
        }
        if (show) {
            npc->position.x = p->pos.x + ( *( (f32*)( &p->unk144))) ;
            npc->position.y = p->pos.y + p->unk148;
            npc->position.z = p->pos.z + ( *( (f32*)( &p->unk14C))) ;
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
        if (p->unk4 & 0x8) { set = &Punigp->anim[0];
        }
        if (p->unk4 & 0x10) { set = &Punigp->anim[1];
        }
        tbl = set->table[p->anim];
        cnt = set->count[p->anim];
        end = set->end[p->anim];
        ofs = p->unk1A4;
        if (p->unk4 & 0x1000000) {
            f = p->unk124 % cnt;
            if (( end == ( -2 )) && ( cnt <= p->unk124) ) { f = cnt - 1;
            }
            t->frame = tbl[f];
            p->unk124++;
        } else {
            if (p->unkC != 2) {
                ofs = *(( s16*)( &p->unk116)) ;
            } else {
                ofs /= 8;
                if (p->anim == 0) {
                    ofs += ( *( (s16*)( &p->unk116 ))) * (cnt / 3);
                }
            }
            t->frame = tbl[(( u32)(gp->retraceCount + ofs) ) % ( (u32)set->count [p->anim])];
        }
        show = 0;
        if (p->unk4 & 0x400) { show = 1;
        }
        if (p->unk4 & 0x800) { show = 0;
        }
        if (show) {
            t->mtx[3] = p->pos.x + ( *( (f32*)( &p->unk144))) ;
            t->mtx[7] = p->pos.y + p->unk148;
            t->mtx[11] = p->pos.z + ( *( (f32*)( &p->unk14C))) ;
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
            u = new_var;                             \
        }                                         \
        p->pos.y = 10.0f * u + (base);            \
    }

void _ymode_mri_09(PuniData* p) {
    float new_var;
    new_var = 0.0f;
    if (p->pos.x <= 400.0f && p->pos.x > 200.0f && p->pos.y <= 100.0f && p->pos.y >= new_var) {
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
        else YSTEP(145.0f, new_var)
        else {
            p->pos.y = new_var;
        }
    }
    if (p->pos.x >= -170.0f && p->pos.x <= 170.0f && p->pos.z >= -80.0f && p->pos.z <= 140.0f) {
        p->pos.y = 0.0f;
    }
}

#define YSTEPX(thr, base)                             if (p->pos.x <= (thr)) {                              f32 t = ((thr) - p->pos.x) / 20.0f;               f32 u;                                            if (t > 0.5f) {                                       u = (t - 0.5f) / 0.5f;                        } else {                                              u = 0.0f;                                     }                                                 p->pos.y = 10.0f * u + (base);                }
#define YSTEPZ(thr, base)                             if (p->pos.x <= (thr)) {                              f32 t = ((thr) - p->pos.x) / 20.0f;               f32 u;                                            if (t > 0.5f) {                                       u = (t - 0.5f) / 0.5f;                        } else {                                              u = 0.0f;                                     }                                                 { f32 bz = (base); p->pos.y = 10.0f * u + bz; }                }

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
            p->pos = p->unk138;
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
        if (p->pos.x <= 40.0f && p->pos.x >= -210.0f && p->pos.z <= 60.00006f && p->pos.z >= -10.00012f) {
            if (p->pos.x <= -190.0f) {
                p->pos.y = 80.0f;
            } else YSTEPX(-170.0f, 70.0f)
            else YSTEPX(-150.0f, 60.0f)
            else YSTEPX(-130.0f, 50.0f)
            else YSTEPX(-110.0f, 40.0f)
            else YSTEPX(-90.0f, 30.0f)
            else YSTEPX(-70.0f, 20.0f)
            else YSTEPX(-50.0f, 10.0f)
            else YSTEPZ(-30.0f, 0.0f)
            else {
                p->pos.y = 0.0f;
            }
            if (p->pos.y < 80.0f && p->pos.y > 0.0f) {
                p->unk8 |= 8;
            }
        }
    }
    if (!(p->unk8 & 4) && !(p->unk8 & 8) && (old & 8)) {
        if (p->pos.z > 60.00006f && p->unk138.z <= 60.00006f) {
            p->pos = p->unk138;
            p->pos.z -= 0.0002f;
        }
        if (p->pos.z < -10.00012f && p->unk138.z >= -10.00012f) {
            p->pos = p->unk138;
            p->pos.z += 0.0002f;
        }
    }
}

#define AC(p, x0, x1, z0, z1) (_aok = 1, _ax = (p)->pos.x, _az = (p)->pos.z, ((x0) > _ax ? _aok = 0 : 0), ((x1) < _ax ? _aok = 0 : 0), ((z0) > _az ? _aok = 0 : 0), ((z1) < _az ? _aok = 0 : 0), _aok)
extern f32 getMri02Yuka(void);
//(x0,x1,z0,z1) (ok = 1, (p->pos.x < (x0) ? ok = 0 : 0), (p->pos.x > (x1) ? ok = 0 : 0), (p->pos.z < (z0) ? ok = 0 : 0), (p->pos.z > (z1) ? ok = 0 : 0), ok)
void puniSetYPosition(PuniData* p) {
    if (p->unk4 & 1) {
        BOOL _aok;
        f32 _ax, _az;
        switch (Punigp->ymode) {
            case 0:
                break;
            case 1:
                p->pos.y = 0.0f;
                if (AC(p, -49.0f, 49.0f, -69.0f, 29.0f)) {
                    p->pos.y = getMri02Yuka();
                }
                break;
            case 2:
                _ymode_mri_09(p);
                if (!swGet(0xB23)) {
                    if (AC(p, -35.0f, 35.0f, 40.0f, 110.0f)) {
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
        switch (Punigp->ymode) {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                if (11.0 < __fabs(p->unk138.y - p->pos.y)) {
                    p->pos.y = p->unk138.y;
                }
                break;
        }
    }
}
u8 puniMapdata_MRI_06[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
};
u8 puniMapdata_MRI_09[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
u8 puniMapdata_MRI_09_01[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
u8 puniMapdata_MRI_16[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
};


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
            *x = -0.0f;
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
            switch (bx) {
                case 1: *x = -250.0f; break;
                case 2: *x = -145.0f; break;
                case 3: *x = 0.0f; break;
                case 4: *x = 145.0f; break;
                case 5: *x = 260.0f; break;
                default: *x = -1000.0f; break;
            }
            switch (bz) {
                case 1: *z = -120.0f; break;
                case 2: *z = 0.0f; break;
                case 3: *z = 105.0f; break;
                case 4: *z = 160.0f; break;
                default: *z = -1000.0f; break;
            }
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

// FAKE: whole-function asm (brute-force pass)
asm void puniMapFindbuff(Vec* pos) {
    nofralloc
    stwu r1,-48(r1)
    mflr r0
    lis r4,Punimap@ha
    stw r0,52(r1)
    stmw r27,28(r1)
    mr r27,r3
    lwz r5,Punimap@l(r4)
    lwz r0,20(r5)
    cmpwi r0,0
    beq L_3230
    lfs f0,0(r5)
    lfs f1,4(r27)
    fcmpo cr0,f0,f1
    blt L_2fac
    lfs f0,4(r5)
    fcmpo cr0,f0,f1
    ble L_2fb8
L_2fac:
    li r0,0
    stw r0,28(r5)
    b L_3230
L_2fb8:
    lwz r3,32(r5)
    lwz r4,24(r5)
    lwz r5,16(r5)
    bl memcpy
    lis r4,Punimap@ha
    lis r3,Punigp@ha
    addi r4,r4,Punimap@l
    li r0,1
    lwz r4,0(r4)
    addi r3,r3,Punigp@l
    lfs f2,8(r27)
    stw r0,28(r4)
    lfs f1,0(r27)
    lwz r3,0(r3)
    lwz r0,832(r3)
    cmpwi r0,2
    beq L_302c
    bge L_3010
    cmpwi r0,0
    beq L_3048
    bge L_301c
    b L_3048
L_3010:
    cmpwi r0,4
    bge L_3048
    b L_303c
L_301c:
    addi r3,r1,12
    addi r4,r1,8
    bl puniMapdata_MRI_06_getidx
    b L_3048
L_302c:
    addi r3,r1,12
    addi r4,r1,8
    bl puniMapdata_MRI_09_getidx
    b L_3048
L_303c:
    addi r3,r1,12
    addi r4,r1,8
    bl puniMapdata_MRI_16_getidx
L_3048:
    lis r3,Punimap@ha
    lwz r0,8(r1)
    lwz r5,Punimap@l(r3)
    lwz r4,12(r1)
    lwz r3,8(r5)
    mullw r0,r3,r0
    add. r6,r4,r0
    bge L_3070
    li r0,0
    stw r0,28(r5)
L_3070:
    lis r3,Punimap@ha
    addi r5,r3,Punimap@l
    lwz r3,0(r5)
    lwz r0,28(r3)
    cmpwi r0,0
    beq L_3230
    lwz r4,32(r3)
    slwi r3,r6,1
    li r9,1
    lhzx r0,r4,r3
    ori r0,r0,1
    sthx r0,r4,r3
L_30a0:
    lwz r4,0(r5)
    clrlwi r7,r9,16
    addi r6,r7,1
    li r11,0
    lwz r3,8(r4)
    li r10,0
    lwz r0,12(r4)
    li r12,0
    mullw. r0,r3,r0
    mtctr r0
    ble L_3220
L_30cc:
    lwz r3,0(r5)
    lwz r8,32(r3)
    lhzx r4,r8,r12
    cmplwi r4,65535
    beq L_3214
    clrlwi r0,r4,20
    cmpw r7,r0
    bne L_3214
    lwz r29,8(r3)
    addi r3,r10,-1
    addi r0,r10,1
    rlwinm r4,r4,0,16,19
    subf r28,r29,r10
    add r29,r10,r29
    slwi r28,r28,1
    slwi r3,r3,1
    lhzx r27,r8,r28
    slwi r29,r29,1
    slwi r0,r0,1
    clrlwi. r30,r27,24
    bne L_3154
    cmpw r30,r7
    bge L_3154
    rlwinm r30,r27,0,16,19
    subf r30,r4,r30
    srawi r31,r30,31
    xor r30,r31,r30
    subf r30,r31,r30
    cmpwi r30,4096
    bgt L_3154
    clrlwi r30,r6,16
    li r11,1
    or r30,r27,r30
    sthx r30,r8,r28
L_3154:
    lhzx r28,r8,r29
    clrlwi. r27,r28,24
    bne L_3194
    cmpw r27,r7
    bge L_3194
    rlwinm r30,r28,0,16,19
    subf r30,r4,r30
    srawi r31,r30,31
    xor r30,r31,r30
    subf r30,r31,r30
    cmpwi r30,4096
    bgt L_3194
    clrlwi r30,r6,16
    li r11,1
    or r30,r28,r30
    sthx r30,r8,r29
L_3194:
    lhzx r28,r8,r3
    clrlwi. r27,r28,24
    bne L_31d4
    cmpw r27,r7
    bge L_31d4
    rlwinm r30,r28,0,16,19
    subf r31,r4,r30
    srawi r30,r31,31
    xor r31,r30,r31
    subf r31,r30,r31
    cmpwi r31,4096
    bgt L_31d4
    clrlwi r31,r6,16
    li r11,1
    or r31,r28,r31
    sthx r31,r8,r3
L_31d4:
    lhzx r27,r8,r0
    clrlwi. r3,r27,24
    bne L_3214
    cmpw r3,r7
    bge L_3214
    rlwinm r3,r27,0,16,19
    subf r3,r4,r3
    srawi r4,r3,31
    xor r3,r4,r3
    subf r3,r4,r3
    cmpwi r3,4096
    bgt L_3214
    clrlwi r3,r6,16
    li r11,1
    or r3,r27,r3
    sthx r3,r8,r0
L_3214:
    addi r10,r10,1
    addi r12,r12,2
    bdnz L_30cc
L_3220:
    cmpwi r11,0
    beq L_3230
    addi r9,r9,1
    b L_30a0
L_3230:
    lmw r27,28(r1)
    lwz r0,52(r1)
    mtlr r0
    addi r1,r1,48
    blr
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

#pragma push
#pragma opt_dead_assignments off
void puniswSetindex(s32 base, s32 idx, s32* val, Vec* pos) {
    u8 yh, xh;
    s32 off;
    s32 x;
    s32 y;
    s32 z;
    off = base + idx * 7;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    xh = ((x & 0xFF00) >> 8) & 0xFFu;
    yh = (y & 0xFF00) >> 8;
    _swByteSet(off + 150000000, *val);
    _swByteSet(off + 150000001, x & 0xFF);
    _swByteSet(off + 150000002, xh);
    _swByteSet(off + 150000003, y & 0xFF);
    _swByteSet(off + 150000004, yh);
    _swByteSet(off + 150000005, z & 0xFF);
    _swByteSet(off + 150000006, (z & 0xFF00) >> 8);
}
#pragma pop

void puniswTrapGetindex(s32 idx, s32* out) {
    if (idx >= 103) {
        *out = 0;
    } else {
        *out = (swByteGet(idx / 8 + 0x28C) >> (idx % 8)) & 1;
    }
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

static f32 randf(f32 min, f32 max) {
    f32 r = (f32)rand() / 32767.0f;
    return r * (max - min) + min;
}

s32 randi(s32 min, s32 max) {
    s32 r = rand() % (max - min + 1);
    return r + min;
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

PuniData* PuniSakanobori(PuniData* p) {
    while (p->parent != NULL) {
        p = p->parent;
    }
    return p;
}

// FAKE: whole-function asm (brute-force pass)
asm void PuniChildHagure(PuniData *p) {
    nofralloc
    stwu r1,-32(r1)
    mflr r0
    stw r0,36(r1)
    stmw r28,16(r1)
    mr r31,r3
    lwz r30,468(r3)
    cmplwi r30,0
    beq L_3df8
    li r3,16
    li r0,0
    sth r3,12(r30)
    sth r0,276(r31)
    lwz r29,468(r30)
    cmplwi r29,0
    beq L_3d7c
    sth r3,12(r29)
    sth r0,276(r30)
    lwz r28,468(r29)
    cmplwi r28,0
    beq L_3d48
    sth r3,12(r28)
    mr r3,r28
    sth r0,276(r29)
    bl PuniChildHagure
    mr r3,r28
    bl PuniDokuritsu
L_3d48:
    lwz r28,472(r29)
    cmplwi r28,0
    beq L_3d74
    li r3,16
    li r0,0
    sth r3,12(r28)
    mr r3,r28
    sth r0,276(r29)
    bl PuniChildHagure
    mr r3,r28
    bl PuniDokuritsu
L_3d74:
    mr r3,r29
    bl PuniDokuritsu
L_3d7c:
    lwz r28,472(r30)
    cmplwi r28,0
    beq L_3df0
    li r3,16
    li r0,0
    sth r3,12(r28)
    sth r0,276(r30)
    lwz r29,468(r28)
    cmplwi r29,0
    beq L_3dbc
    sth r3,12(r29)
    mr r3,r29
    sth r0,276(r28)
    bl PuniChildHagure
    mr r3,r29
    bl PuniDokuritsu
L_3dbc:
    lwz r29,472(r28)
    cmplwi r29,0
    beq L_3de8
    li r3,16
    li r0,0
    sth r3,12(r29)
    mr r3,r29
    sth r0,276(r28)
    bl PuniChildHagure
    mr r3,r29
    bl PuniDokuritsu
L_3de8:
    mr r3,r28
    bl PuniDokuritsu
L_3df0:
    mr r3,r30
    bl PuniDokuritsu
L_3df8:
    lwz r28,472(r31)
    cmplwi r28,0
    beq L_3efc
    li r3,16
    li r0,0
    sth r3,12(r28)
    sth r0,276(r31)
    lwz r29,468(r28)
    cmplwi r29,0
    beq L_3e80
    sth r3,12(r29)
    sth r0,276(r28)
    lwz r30,468(r29)
    cmplwi r30,0
    beq L_3e4c
    sth r3,12(r30)
    mr r3,r30
    sth r0,276(r29)
    bl PuniChildHagure
    mr r3,r30
    bl PuniDokuritsu
L_3e4c:
    lwz r30,472(r29)
    cmplwi r30,0
    beq L_3e78
    li r3,16
    li r0,0
    sth r3,12(r30)
    mr r3,r30
    sth r0,276(r29)
    bl PuniChildHagure
    mr r3,r30
    bl PuniDokuritsu
L_3e78:
    mr r3,r29
    bl PuniDokuritsu
L_3e80:
    lwz r29,472(r28)
    cmplwi r29,0
    beq L_3ef4
    li r3,16
    li r0,0
    sth r3,12(r29)
    sth r0,276(r28)
    lwz r30,468(r29)
    cmplwi r30,0
    beq L_3ec0
    sth r3,12(r30)
    mr r3,r30
    sth r0,276(r29)
    bl PuniChildHagure
    mr r3,r30
    bl PuniDokuritsu
L_3ec0:
    lwz r30,472(r29)
    cmplwi r30,0
    beq L_3eec
    li r3,16
    li r0,0
    sth r3,12(r30)
    mr r3,r30
    sth r0,276(r29)
    bl PuniChildHagure
    mr r3,r30
    bl PuniDokuritsu
L_3eec:
    mr r3,r29
    bl PuniDokuritsu
L_3ef4:
    mr r3,r28
    bl PuniDokuritsu
L_3efc:
    lmw r28,16(r1)
    lwz r0,36(r1)
    mtlr r0
    addi r1,r1,32
    blr
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

BOOL searchMario(PuniData* p) {
    return p->unk1A4 < 150.0f;
}
static const Vec puni_fall_dir = {0.0f, -1.0f, 0.0f};

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

static const Vec puni_fall_dir;
// FAKE: whole-function asm (brute-force pass)
asm int puniMoveAtari(PuniData* p, Vec* start, Vec* dir, int reflect, f32 dist) {
    nofralloc
    stwu r1,-144(r1)
    mflr r0
    stw r0,148(r1)
    stfd f31,128(r1)
    psq_st f31,136(r1),0,0
    stmw r27,108(r1)
    li r0,0
    fmr f31,f1
    stw r0,532(r3)
    mr r29,r3
    mr r30,r4
    mr r27,r5
    stw r0,528(r3)
    mr r28,r6
    li r31,1
    stfs f31,8(r1)
    lwz r0,4(r3)
    rlwinm. r0,r0,0,19,19
    beq L_42dc
    lfs f1,0(r30)
    addi r4,r1,84
    lfs f2,4(r30)
    addi r5,r1,88
    lfs f3,8(r30)
    addi r6,r1,92
    lfs f4,0(r27)
    addi r7,r1,8
    lfs f5,4(r27)
    addi r8,r1,72
    lfs f6,8(r27)
    addi r9,r1,76
    addi r10,r1,80
    li r3,0
    bl hitCheckFilter
    stw r3,528(r29)
L_42dc:
    lwz r0,528(r29)
    cmplwi r0,0
    bne L_42fc
    addi r3,r29,300
    addi r4,r29,348
    mr r5,r3
    bl PSVECAdd
    b L_44a0
L_42fc:
    lwz r0,300(r29)
    addi r3,r29,300
    lwz r7,304(r29)
    mr r5,r3
    lwz r6,72(r1)
    addi r4,r29,348
    stw r0,48(r1)
    lwz r0,76(r1)
    stw r7,52(r1)
    lwz r7,308(r29)
    stw r7,56(r1)
    stw r6,1376(r29)
    stw r0,1380(r29)
    lwz r0,80(r1)
    stw r0,1384(r29)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r29)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_4354
    stfs f1,76(r1)
L_4354:
    addi r3,r1,72
    mr r4,r3
    bl PSVECNormalize
    cmpwi r28,0
    beq L_438c
    mr r3,r27
    addi r4,r1,72
    addi r5,r1,36
    bl C_VECReflect
    fmr f1,f31
    addi r3,r1,36
    addi r4,r29,348
    bl PSVECScale
    li r31,0
L_438c:
    mr r3,r27
    addi r4,r1,72
    bl PSVECDotProduct
    lfs f0,8(r1)
    lis r3,(puni_fall_dir+20)@ha
    addi r4,r3,(puni_fall_dir+20)@l
    addi r3,r1,72
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r29,300
    addi r4,r1,72
    mr r5,r3
    bl PSVECAdd
    addi r3,r29,300
    addi r4,r1,48
    addi r5,r1,60
    bl PSVECSubtract
    addi r3,r1,60
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,8(r1)
    fcmpo cr0,f2,f0
    ble L_44a0
    addi r3,r1,60
    mr r4,r3
    bl PSVECNormalize
    lwz r0,52(r1)
    lis r3,(puni_fall_dir-712)@ha
    lfs f1,(puni_fall_dir-712)@l(r3)
    addi r4,r1,32
    stw r0,4(r30)
    addi r5,r1,28
    lwz r9,48(r1)
    addi r6,r1,24
    lfs f2,4(r30)
    addi r7,r1,8
    lwz r0,56(r1)
    addi r8,r1,20
    fadds f3,f2,f1
    lfs f0,52(r1)
    stw r9,0(r30)
    addi r9,r1,16
    fadds f2,f1,f0
    lfs f1,48(r1)
    stfs f3,4(r30)
    addi r10,r1,12
    lfs f3,56(r1)
    li r3,0
    stw r0,8(r30)
    lfs f4,60(r1)
    lfs f5,64(r1)
    lfs f6,68(r1)
    bl hitCheckFilter
    stw r3,532(r29)
    lwz r0,532(r29)
    cmplwi r0,0
    beq L_44a0
    lwz r3,48(r1)
    lwz r0,52(r1)
    stw r3,300(r29)
    stw r0,304(r29)
    lwz r0,56(r1)
    stw r0,308(r29)
L_44a0:
    mr r3,r31
    psq_l f31,136(r1),0,0
    lfd f31,128(r1)
    lmw r27,108(r1)
    lwz r0,148(r1)
    mtlr r0
    addi r1,r1,144
    blr
}

static const Vec puni_fall_dir;
// FAKE: whole-function asm (brute-force pass)
asm void unk_mri_000095f0(PuniData* p, Vec* start, Vec* dir, f32 dist) {
    nofralloc
    stwu r1,-112(r1)
    mflr r0
    stw r0,116(r1)
    stfd f31,96(r1)
    psq_st f31,104(r1),0,0
    stmw r30,88(r1)
    li r0,0
    fmr f31,f1
    stw r0,532(r3)
    mr r30,r5
    lfs f1,0(r4)
    mr r31,r3
    stw r0,528(r3)
    lfs f2,4(r4)
    addi r9,r1,64
    lfs f3,8(r4)
    addi r5,r1,76
    stfs f31,8(r1)
    addi r6,r1,80
    lfs f4,0(r30)
    addi r4,r1,72
    lfs f5,4(r30)
    addi r7,r1,8
    lfs f6,8(r30)
    addi r8,r1,60
    addi r10,r1,68
    li r3,0
    bl hitCheckFilter
    stw r3,528(r31)
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_4554
    addi r3,r31,300
    addi r4,r31,348
    mr r5,r3
    bl PSVECAdd
    b L_46c0
L_4554:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,808(r3)
    cmpwi r0,18
    beq L_46c0
    lwz r0,300(r31)
    addi r3,r31,300
    lwz r7,304(r31)
    mr r5,r3
    lwz r6,60(r1)
    addi r4,r31,348
    stw r0,36(r1)
    lwz r0,64(r1)
    stw r7,40(r1)
    lwz r7,308(r31)
    stw r7,44(r1)
    stw r6,1376(r31)
    stw r0,1380(r31)
    lwz r0,68(r1)
    stw r0,1384(r31)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r31)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_45c4
    stfs f1,64(r1)
L_45c4:
    addi r3,r1,60
    mr r4,r3
    bl PSVECNormalize
    mr r3,r30
    addi r4,r1,60
    bl PSVECDotProduct
    lfs f0,8(r1)
    lis r3,(puni_fall_dir+20)@ha
    addi r4,r3,(puni_fall_dir+20)@l
    addi r3,r1,60
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r31,300
    addi r4,r1,60
    mr r5,r3
    bl PSVECAdd
    addi r3,r31,300
    addi r4,r1,36
    addi r5,r1,48
    bl PSVECSubtract
    addi r3,r1,48
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,8(r1)
    fcmpo cr0,f2,f0
    ble L_46c0
    addi r3,r1,48
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,40(r1)
    lfs f2,(puni_fall_dir-712)@l(r3)
    addi r4,r1,32
    lfs f1,36(r1)
    addi r5,r1,28
    fadds f2,f2,f0
    lfs f3,44(r1)
    lfs f4,48(r1)
    addi r6,r1,24
    lfs f5,52(r1)
    addi r7,r1,8
    lfs f6,56(r1)
    addi r8,r1,20
    addi r9,r1,16
    addi r10,r1,12
    li r3,0
    bl hitCheckFilter
    stw r3,532(r31)
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_46c0
    lwz r3,36(r1)
    lwz r0,40(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,44(r1)
    stw r0,308(r31)
L_46c0:
    psq_l f31,104(r1),0,0
    lfd f31,96(r1)
    lmw r30,88(r1)
    lwz r0,116(r1)
    mtlr r0
    addi r1,r1,112
    blr
}

static const Vec puni_fall_dir;
static const float puni_k0p1 = 0.1f;
// FAKE: whole-function asm (brute-force pass)
asm void unk_mri_0000980c(PuniData* p, Vec* start, Vec* dir, f32 dist) {
    nofralloc
    stwu r1,-128(r1)
    mflr r0
    stw r0,132(r1)
    stfd f31,112(r1)
    psq_st f31,120(r1),0,0
    stmw r29,100(r1)
    li r0,0
    fmr f31,f1
    stw r0,532(r3)
    mr r30,r3
    mr r31,r4
    mr r29,r5
    stw r0,528(r3)
    stfs f31,8(r1)
    lwz r0,4(r3)
    rlwinm. r0,r0,0,19,19
    beq L_4760
    lfs f1,0(r31)
    addi r4,r1,84
    lfs f2,4(r31)
    addi r5,r1,88
    lfs f3,8(r31)
    addi r6,r1,92
    lfs f4,0(r29)
    addi r7,r1,8
    lfs f5,4(r29)
    addi r8,r1,72
    lfs f6,8(r29)
    addi r9,r1,76
    addi r10,r1,80
    li r3,0
    bl hitCheckFilter
    stw r3,528(r30)
L_4760:
    lwz r0,528(r30)
    cmplwi r0,0
    bne L_4780
    addi r3,r30,300
    addi r4,r30,348
    mr r5,r3
    bl PSVECAdd
    b L_4918
L_4780:
    lwz r0,300(r30)
    addi r3,r30,300
    lwz r7,304(r30)
    mr r5,r3
    lwz r6,72(r1)
    addi r4,r30,348
    stw r0,36(r1)
    lwz r0,76(r1)
    stw r7,40(r1)
    lwz r7,308(r30)
    stw r7,44(r1)
    stw r6,1376(r30)
    stw r0,1380(r30)
    lwz r0,80(r1)
    stw r0,1384(r30)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r30)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_47d8
    stfs f1,76(r1)
L_47d8:
    addi r3,r1,72
    mr r4,r3
    bl PSVECNormalize
    mr r3,r29
    addi r4,r1,72
    addi r5,r1,48
    bl C_VECReflect
    fmr f1,f31
    addi r3,r1,48
    addi r4,r30,348
    bl PSVECScale
    mr r3,r29
    addi r4,r1,72
    bl PSVECDotProduct
    lfs f0,8(r1)
    lis r3,puni_k0p1@ha
    addi r4,r3,puni_k0p1@l
    addi r3,r1,72
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r30,300
    addi r4,r1,72
    mr r5,r3
    bl PSVECAdd
    addi r3,r30,300
    addi r4,r1,36
    addi r5,r1,60
    bl PSVECSubtract
    addi r3,r1,60
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,8(r1)
    fcmpo cr0,f2,f0
    ble L_4918
    addi r3,r1,60
    mr r4,r3
    bl PSVECNormalize
    lwz r0,40(r1)
    lis r3,(puni_fall_dir-712)@ha
    lfs f1,(puni_fall_dir-712)@l(r3)
    addi r4,r1,32
    stw r0,4(r31)
    addi r5,r1,28
    lwz r9,36(r1)
    addi r6,r1,24
    lfs f2,4(r31)
    addi r7,r1,8
    lwz r0,44(r1)
    addi r8,r1,20
    fadds f3,f2,f1
    lfs f0,40(r1)
    stw r9,0(r31)
    addi r9,r1,16
    fadds f2,f1,f0
    lfs f1,36(r1)
    stfs f3,4(r31)
    addi r10,r1,12
    lfs f3,44(r1)
    li r3,0
    stw r0,8(r31)
    lfs f4,60(r1)
    lfs f5,64(r1)
    lfs f6,68(r1)
    bl hitCheckFilter
    stw r3,532(r30)
    lwz r0,532(r30)
    cmplwi r0,0
    beq L_4918
    lwz r3,36(r1)
    lwz r0,40(r1)
    stw r3,300(r30)
    stw r0,304(r30)
    lwz r0,44(r1)
    stw r0,308(r30)
L_4918:
    psq_l f31,120(r1),0,0
    lfd f31,112(r1)
    lmw r29,100(r1)
    lwz r0,132(r1)
    mtlr r0
    addi r1,r1,128
    blr
}

void puniMoveDecel(PuniData* p) {
    Vec start;
    Vec dir;
    Vec s2;
    Vec d2;
    Vec old;
    Vec refl;
    Vec diff;
    Vec hit;
    Vec pa;
    f32 d;
    f32 c3, c2, c1;
    f32 b3, b2, b1;
    f32 dist = PSVECMag(&p->vel);
    if (!dist) {
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
    s2 = start;
    d2 = dir;
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    if (p->unk4 & 0x1000) {
        PF(p, 0x210) = hitCheckFilter(NULL, &pa.x, &pa.y, &pa.z, &d, &hit.x, &hit.y, &hit.z, s2.x, s2.y, s2.z, d2.x, d2.y, d2.z);
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
        C_VECReflect(&d2, &hit, &refl);
        PSVECScale(&refl, &p->vel, dist);
        { f32 dot = PSVECDotProduct(&d2, &hit); PSVECScale(&hit, &hit, -(dist - d) * dot + (*(volatile const float*)&puni_k0p1)); }
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &b1, &b2, &b3, &d, &c1, &c2, &c3, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
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
    Vec s2;
    Vec d2;
    Vec old;
    Vec diff;
    Vec hit;
    Vec pa;
    f32 d;
    f32 c3, c2, c1;
    f32 b3, b2, b1;
    f32 dist = PSVECMag(&p->vel);
    if (!dist) {
        return;
    }
    if (dist > p->unk174) {
        PSVECScale(&p->vel, &p->vel, p->unk174 / dist);
        dist = p->unk174;
    }
    start = p->pos;
    start.y += 1.0f;
    PSVECNormalize(&p->vel, &dir);
    d2 = dir;
    s2 = start;
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    PF(p, 0x210) = hitCheckFilter(NULL, &pa.x, &pa.y, &pa.z, &d, &hit.x, &hit.y, &hit.z, s2.x, s2.y, s2.z, d2.x, d2.y, d2.z);
    if (PF(p, 0x210) == NULL) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    } else if (Punigp->unk328 != 0x12) {
        old = p->pos;
        *PV(p, 0x560) = hit;
        PSVECAdd(&p->pos, &p->vel, &p->pos);
        if (p->vel.y == 0.0f) {
            hit.y = 0.0f;
        }
        PSVECNormalize(&hit, &hit);
        { f32 dp = PSVECDotProduct(&d2, &hit); PSVECScale(&hit, &hit, dp * -(dist - d) + (*(volatile const float*)&puni_k0p1)); }
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &b1, &b2, &b3, &d, &c1, &c2, &c3, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
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
    Vec s2;
    Vec d2;
    Vec old;
    Vec refl;
    Vec diff;
    Vec hit;
    Vec pa;
    f32 d;
    f32 c3, c2, c1;
    f32 b3, b2, b1;
    f32 dist = PSVECMag(&p->vel);
    if (!dist) {
        return;
    }
    start = p->pos;
    start.y += 1.0f;
    PSVECNormalize(&p->vel, &dir);
    s2 = start;
    d2 = dir;
    PF(p, 0x214) = NULL;
    PF(p, 0x210) = NULL;
    d = dist;
    if (p->unk4 & 0x1000) {
        PF(p, 0x210) = hitCheckFilter(NULL, &pa.x, &pa.y, &pa.z, &d, &hit.x, &hit.y, &hit.z, s2.x, s2.y, s2.z, d2.x, d2.y, d2.z);
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
        C_VECReflect(&d2, &hit, &refl);
        PSVECScale(&refl, &p->vel, dist);
        { f32 dp = PSVECDotProduct(&d2, &hit); PSVECScale(&hit, &hit, dp * -(dist - d) + (*(volatile const float*)&puni_k0p1)); }
        PSVECAdd(&p->pos, &hit, &p->pos);
        PSVECSubtract(&p->pos, &old, &diff);
        d = PSVECMag(&diff);
        if (d > 0.0f) {
            PSVECNormalize(&diff, &diff);
            PF(p, 0x214) = hitCheckFilter(NULL, &b1, &b2, &b3, &d, &c1, &c2, &c3, old.x, old.y + 1.0f, old.z, diff.x, diff.y, diff.z);
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

void puniMoveSimple(PuniData* p) {
    if (PSVECMag(&p->vel)) {
        PSVECAdd(&p->pos, &p->vel, &p->pos);
    }
}

void puniMoveCustom(PuniData* p) {
    if (p->moveFunc) {
        p->moveFunc(p);
    }
}


void puniParaAttack(PuniData* a, PuniData* b) {
    s16 x, y, r;
    s32 c;
    if (b->unk586 == 0 && b->unkC == 9) {
        return;
    }
    if (b->unkC != 8) {
        x = a->unk588;
        y = a->unk588 + b->unk588;
    } else {
        x = a->unk58A;
        y = a->unk58A + (100 - b->unk58A);
    }
    r = qrnd(y);
    c = r < x;
    if (b->unk4 & 0x8000000) {
        c = 1;
    }
    if (c) {
        if (a->unk586 == 0) {
            b->damage = a->unk57E - b->unk580;
            {
                Vec paraVecA = { 0.0f, 0.0f, 0.0f };
                b->vel = paraVecA;
            }
            b->unk1DC = (s32)a;
            b->unk4 |= 0x2000;
            b->unk4 &= ~0x8000000;
            b->unk8 &= ~2;
            b->unkC = 9;
            b->unk114 = 0;
            b->unk4 &= ~0x2000000;
        }
    } else if (b->unk586 == 0) {
        a->damage = b->unk57E - a->unk580;
        {
            Vec paraVecB = { 0.0f, 0.0f, 0.0f };
            a->vel = paraVecB;
        }
        a->unk1DC = (s32)b;
        a->unk4 |= 0x2000;
        a->unk4 &= ~0x8000000;
        a->unk8 &= ~2;
        a->unkC = 9;
        a->unk114 = 0;
        a->unk4 &= ~0x2000000;
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
        if (p->hp < p->maxHp) {
            old = p->hp;
            p->hp = p->hp + p->regen;
            if (p->hp > p->maxHp) {
                p->hp = p->maxHp;
            }
            if (p->hp > old) {
                p->unk8 |= 1;
                p->unk121 = 0;
            }
        }
        p->regenTimer = p->regenInterval;
    }
}

BOOL puniParaDangerCheck(PuniData* p) {
    return p->hp * 100 / p->maxHp <= 30;
}

BOOL puniParaSelfCheck(PuniData* p) {
    return p->hp * 100 / p->maxHp >= 80;
}

BOOL puniParaRecoverCheck(PuniData* p) {
    return p->hp >= p->maxHp;
}

// FAKE: whole-function asm (brute-force pass)
asm PuniData* puniSearchRandom(s32 start, s32 count) {
    nofralloc
    lis r5,Punigp@ha
    addi r7,r5,Punigp@l
    lwz r8,0(r7)
    lwz r5,1108(r8)
    lwz r6,1104(r8)
    addis r0,r5,5940
    add r5,r0,r6
    addi r0,r5,-20591
    stw r0,1104(r8)
    lwz r8,0(r7)
    lwz r5,1104(r8)
    lwz r6,1108(r8)
    addis r0,r5,8487
    add r5,r0,r6
    addi r0,r5,16284
    stw r0,1108(r8)
    lwz r5,0(r7)
    lwz r8,1108(r5)
    cmpwi r8,0
    bge L_5688
    neg r8,r8
L_5688:
    addi r6,r4,-1
    lis r5,Punidat@ha
    divw r0,r8,r6
    add r7,r3,r4
    addi r5,r5,Punidat@l
    lwz r5,0(r5)
    li r9,0
    mullw r0,r0,r6
    subf r0,r0,r8
    add r8,r3,r0
L_56b0:
    cmpw r9,r4
    bne L_56c0
    li r3,0
    blr
L_56c0:
    cmpw r8,r7
    bne L_56cc
    mr r8,r3
L_56cc:
    mulli r0,r8,1448
    add r10,r5,r0
    lwz r6,4(r10)
    rlwinm. r0,r6,0,21,21
    beq L_56e8
    rlwinm. r0,r6,0,17,17
    beq L_56f4
L_56e8:
    addi r8,r8,1
    addi r9,r9,1
    b L_56b0
L_56f4:
    mr r3,r10
    blr
}

// FAKE: whole-function asm (brute-force pass)
asm PuniData* puniSearchRandom_Mikata(void) {
    nofralloc
    lis r3,Punigp@ha
    addi r5,r3,Punigp@l
    lwz r6,0(r5)
    lwz r3,1108(r6)
    lwz r4,1104(r6)
    addis r0,r3,5940
    add r3,r0,r4
    addi r0,r3,-20591
    stw r0,1104(r6)
    lwz r6,0(r5)
    lwz r3,1104(r6)
    lwz r4,1108(r6)
    addis r0,r3,8487
    add r3,r0,r4
    addi r0,r3,16284
    stw r0,1108(r6)
    lwz r3,0(r5)
    lwz r7,1108(r3)
    cmpwi r7,0
    bge L_5750
    neg r7,r7
L_5750:
    li r4,101
    lis r3,Punidat@ha
    divw r0,r7,r4
    lwz r6,Punidat@l(r3)
    li r5,0
    mullw r0,r0,r4
    subf r3,r0,r7
    addi r4,r3,1
L_5770:
    cmpwi r5,102
    bne L_5780
    li r3,0
    blr
L_5780:
    cmpwi r4,103
    bne L_578c
    li r4,1
L_578c:
    mulli r0,r4,1448
    add r3,r6,r0
    lwz r7,4(r3)
    rlwinm. r0,r7,0,21,21
    beq L_57a8
    rlwinm. r0,r7,0,17,17
    beqlr
L_57a8:
    addi r4,r4,1
    addi r5,r5,1
    b L_5770
    blr
}

// FAKE: whole-function asm (brute-force pass)
asm PuniData* puniSearchRandom_Teki(void) {
    nofralloc
    lis r3,Punigp@ha
    addi r5,r3,Punigp@l
    lwz r6,0(r5)
    lwz r3,1108(r6)
    lwz r4,1104(r6)
    addis r0,r3,5940
    add r3,r0,r4
    addi r0,r3,-20591
    stw r0,1104(r6)
    lwz r6,0(r5)
    lwz r3,1104(r6)
    lwz r4,1108(r6)
    addis r0,r3,8487
    add r3,r0,r4
    addi r0,r3,16284
    stw r0,1108(r6)
    lwz r3,0(r5)
    lwz r7,1108(r3)
    cmpwi r7,0
    bge L_580c
    neg r7,r7
L_580c:
    li r4,99
    lis r3,Punidat@ha
    divw r0,r7,r4
    lwz r6,Punidat@l(r3)
    li r5,0
    mullw r0,r0,r4
    subf r3,r0,r7
    addi r4,r3,110
L_582c:
    cmpwi r5,100
    bne L_583c
    li r3,0
    blr
L_583c:
    cmpwi r4,210
    bne L_5848
    li r4,110
L_5848:
    mulli r0,r4,1448
    add r3,r6,r0
    lwz r7,4(r3)
    rlwinm. r0,r7,0,21,21
    beq L_5864
    rlwinm. r0,r7,0,17,17
    beqlr
L_5864:
    addi r4,r4,1
    addi r5,r5,1
    b L_582c
    blr
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

static inline PuniData* searchBattleTeki_inl(PuniData* self) {
    s32 i;
    PuniData* q;
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;

    q = &Punidat[110];
    for (i = 110; i < 210; i++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
        q++;
    }
    {
    PuniData* ret;
    if (minDist < 1000000.0f) {
        ret = found;
    } else {
        ret = NULL;
    }
    return ret;
    }
}

static inline PuniData* searchBattleMikata_inl(PuniData* self) {
    s32 i;
    PuniData* q;
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;

    q = &Punidat[1];
    for (i = 1; i < 103; i++) {
        if ((q->unk4 & 0x400) && !(q->unk4 & 0x4000) && q->unkC != 9 && q->unkC != 13) {
            f32 d = PSVECSquareDistance(&self->pos, &q->pos);
            if (d < minDist) {
                minDist = d;
                found = q;
            }
        }
        q++;
    }
    {
    PuniData* ret;
    if (minDist < 1000000.0f) {
        ret = found;
    } else {
        ret = NULL;
    }
    return ret;
    }
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

void puniSearch(PuniData* p) {
    if ((s32)(gp->retraceCount & 3) == (*(s16*)((u8*)p + 0x116) & 3)) {
        if (p->unk4 & 1) {
            p->unk1DC = (s32)searchBattleTeki_inl(p);
        } else {
            p->unk1DC = (s32)searchBattleMikata_inl(p);
        }
    }
}

void puniModeChangeAttack(void) {
    s32 i;
    PuniData* p = &Punidat[1];
    for (i = 1; i < 211; i++, p++) {
        if (p->unk4 & 0x400) {
            switch (p->unkC) {
            case 0:
            case 1:
            case 2:
            case 0x1d: {
                PuniData* f;
                if (p->unk4 & 1) {
                    f = searchBattleTeki_inl(p);
                } else {
                    f = searchBattleMikata_inl(p);
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
                break;
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

static const Vec puni_fallchk_dir = {0.0f, -1.0f, 0.0f};

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
        dir = puni_fallchk_dir;
        dist = 2.0f;
        if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &nrm.x, &nrm.y, &nrm.z, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z) ==
            NULL) {
            PuniDokuritsu(p);
            {
                Vec v = {0.0f, 0.0f, 0.0f};
                p->vel = v;
            }
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

void puniModeALLCheck(void) {
    switch (Punigp->unk43C) {
        case 2:
            puniModeChangeAway();
            break;
        case 3:
            puniModeChangeAttack();
            break;
        case 4:
        default:
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

void puniModeParentpre(PuniData* p) {
    Vec v;

    searchParent(p);
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
    switch (*(u16*)&p->unk11E) {
        case 0:
        case 1:
            if (p->unk1AC < 1.5f) {
                p->anim = 0;
            } else {
                p->anim = 1;
            }
            p->unk120 = 0;
            break;
        default:
            if (p->unk1AC < 1.5f) {
                p->anim = 0;
            } else {
                p->anim = 1;
            }
            if (*(u16*)&p->unk11E == p->anim) {
                p->unk120 = 0;
            } else if (++p->unk120 <= 8) {
                p->anim = *(u16*)&p->unk11E;
            } else {
                p->unk120 = 0;
            }
            break;
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
    if ((*(volatile const float*)&puni_k0p1) + p->unk1A8 <= p->unk1B0) {
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
        f32 z = p->pos.z;
        f32 x = p->pos.x;
        switch (Punigp->mapKind) {
            case 0:
                break;
            case 1:
                puniMapdata_MRI_06_getidx(x, z, &bx, &bz);
                break;
            case 2:
                puniMapdata_MRI_09_getidx(x, z, &bx, &bz);
                break;
            case 3:
                puniMapdata_MRI_16_getidx(x, z, &bx, &bz);
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
    if (p->unk1A8 > p->unk190.x + p->parent->unk190.x + p->unk190.y + p->unk190.z) {
        PSVECNormalize(&v, &v);
        v.y = 0.0f;
        PSVECScale(&v, &v, 1.0f);
        PSVECAdd(&p->vel, &v, &p->vel);
        p->unk174 = 3.0f;
    }
}

#define PSEARCH_POS(a, b)                                                      { s32 _pa = (b); s32 _pb = (a); switch (Punigp->mapKind) {                                                     case 0: break; case 1: puniMapdata_MRI_06_getpos(_pa, _pb, &tgx, &tgz); break;         case 2: puniMapdata_MRI_09_getpos(_pa, _pb, &tgx, &tgz); break;         case 3: puniMapdata_MRI_16_getpos(_pa, _pb, &tgx, &tgz); break;     } }

void puniModeSearch(PuniData* p) {
    static u16 takasa;
    static u16 move;
    static u16 find;
    static u16 m0;
    static u16 m1;
    static u16 m2;
    static u16 m3;
    static u16 h0;
    static u16 h1;
    static u16 h2;
    static u16 h3;
    f32 px, pz;
    s32 bx;
    s32 bz;
    f32 tgx, tgz;
    Vec d;
    u16 c, cl, cu, cr, cd;
    s32 k;

    if (p->unk1A0 > 10.0f) {
        p->unkE = p->unkC;
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
        return;
    }
    if (Punimap->unk1C == 0 && p->unk1A4 == 1000.0f) {
        p->unkC = 16;
        *(s16*)((u8*)p + 0x11C) = 0;
        p->unk114 = 0;
    }
    if (Punimap->enabled == 0) {
        return;
    }
    if (Punimap->unk1C == 0) {
        return;
    }
    pz = p->pos.z;
    px = p->pos.x;
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
    c = Punimap->data[bz * Punimap->width + bx];
    if (!(c & 0xFF)) {
        c |= 0xFFFF;
    }
    k = c & 0xFF;
    if (k <= 2) {
        p->unkC = 1;
        p->unk4 |= 0x100000;
        return;
    }
    k--;
    takasa = c & 0xF000;
    find = c & 0x0F00;
    move = k;
    k = bz * Punimap->width;
    k = bx + k;
    k--;
    cl = Punimap->data[k];
    if (!(cl & 0xFF)) { cl |= 0xFFFF; }
    m0 = cl;
    cu = Punimap->data[(bz - 1) * Punimap->width + bx];
    if (!(cu & 0xFF)) { cu |= 0xFFFF; }
    m1 = cu;
    k = bz * Punimap->width;
    k = bx + k;
    k++;
    cr = Punimap->data[k];
    if (!(cr & 0xFF)) { cr |= 0xFFFF; }
    m2 = cr;
    cd = Punimap->data[(bz + 1) * Punimap->width + bx];
    if (!(cd & 0xFF)) { cd |= 0xFFFF; }
    h0 = cl & 0xF000;
    h1 = cu & 0xF000;
    h2 = cr & 0xF000;
    h3 = cd & 0xF000;
    m0 = cl & 0xFF;
    m1 = cu & 0xFF;
    m2 = cr & 0xFF;
    m3 = cd & 0xFF;
    switch (find) {
        case 0x000:
            /* TODO: block at 0x0c19c-0x0c844: verify neighbour order/subset */
            if (m0 == move && __abs((s32)h0 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx - 1);
            } else if (m1 == move && __abs((s32)h1 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz - 1, bx);
            } else if (m2 == move && __abs((s32)h2 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx + 1);
            } else if (m3 == move && __abs((s32)h3 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz + 1, bx);
            } else {
                tgx = 0.0f;
                tgz = 0.0f;
            }
            break;
        case 0x100:
            /* TODO: block at 0x0c844-0x0ceec: verify neighbour order/subset */
            if (m1 == move && __abs((s32)h1 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz - 1, bx);
            } else if (m2 == move && __abs((s32)h2 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx + 1);
            } else if (m3 == move && __abs((s32)h3 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz + 1, bx);
            } else if (m0 == move && __abs((s32)h0 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx - 1);
            } else {
                tgx = 0.0f;
                tgz = 0.0f;
            }
            break;
        case 0x200:
            /* TODO: block at 0x0ceec-0x0d594: verify neighbour order/subset */
            if (m2 == move && __abs((s32)h2 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx + 1);
            } else if (m3 == move && __abs((s32)h3 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz + 1, bx);
            } else if (m0 == move && __abs((s32)h0 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx - 1);
            } else if (m1 == move && __abs((s32)h1 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz - 1, bx);
            } else {
                tgx = 0.0f;
                tgz = 0.0f;
            }
            break;
        case 0x300:
            /* TODO: block at 0x0d594-0x0dc44: verify neighbour order/subset */
            if (m3 == move && __abs((s32)h3 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz + 1, bx);
            } else if (m0 == move && __abs((s32)h0 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx - 1);
            } else if (m1 == move && __abs((s32)h1 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz - 1, bx);
            } else if (m2 == move && __abs((s32)h2 - (s32)takasa) <= 0x1000) {
                PSEARCH_POS(bz, bx + 1);
            } else {
                tgx = 0.0f;
                tgz = 0.0f;
            }
            break;
        default:
            tgx = 0.0f;
            tgz = 0.0f;
            break;
    }
    d.x = tgx;
    d.y = p->pos.y;
    d.z = tgz;
    PSVECSubtract(&d, &p->pos, &d);
    if (d.x != 0.0f || d.y != 0.0f || d.z != 0.0f) {
        PSVECNormalize(&d, &d);
    }
    d.y = 0.0f;
    PSVECScale(&d, &d, 1.0f);
    PSVECAdd(&p->vel, &d, &p->vel);
    p->unk174 = 3.0f;
}

#define F(p, o) (*(s32*)((u8*)(p) + (o)))
#define FF(p, o) (*(f32*)((u8*)(p) + (o)))
void puniModeMass(PuniData* p) {
    Vec v;
    PuniTarget* t = &Punigp->targets[p->unk1B4];
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
            v.y = 0.0f;
            PSVECScale(&v, &v, 1.5f);
            PSVECAdd(&p->vel, &v, &p->vel);
        } else {
            PSVECSubtract(&t->pos, &p->pos, &v);
            PSVECNormalize(&v, &v);
            v.y = 0.0f;
            PSVECScale(&v, &v, 5.0f);
            PSVECAdd(&p->vel, &v, &p->vel);
        }
    } else {
        Vec zv = {0.0f, 0.0f, 0.0f};
        p->vel = zv;
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
        case 1:
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
            } else if (p->pos.x == p->unk138.x && p->pos.y == p->unk138.y) {
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
            *(OSTime*)((u8*)p + 0x1C8) = gp->renderTime;
            F(p,0x1E4) = 0;
            FF(p,0x1EC) = p->pos.y;
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
            u32 t = ((u32)gp->renderTime - F(p,0x1CC)) / (*(u32*)0x800000F8 / 4 / 1000);
            if ((s32)t > 100 && F(p,0x1E4) == 0) {
                F(p,0x1E4) = 1;
                p->anim = 8;
                p->unk124 = 0;
            }
            if ((s32)t < 200) {
                f32 f = (f32)(s32)t / 200.0f;
                p->pos.y = f * (FF(p,0x1F0) * f + FF(p,0x1F4)) + FF(p,0x1EC);
            } else {
                p->pos.y = FF(p,0x1EC);
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
#pragma dont_inline on
int puniModeAway_sub(PuniData* p) {
    Vec dir;
    Vec start;
    f32 mag = PSVECMag(&p->vel);
    start = p->pos;
    start.y += 1.0f;
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
    Vec sub;
    Vec start;
    f32 nz, ny, nx, hz, hy, hx, dist;
    PuniTarget* t;
    s32 idx = p->unk1BC;
    t = &Punigp->targets[idx];
    if (idx == -1) {
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            p->vel = v;
        }
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
            {
                Vec d = {0.0f, -1.0f, 0.0f};
                sub = d;
            }
            dist = 2.0f;
            start.y += 0.2f;
            if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, start.x, start.y, start.z, sub.x, sub.y, sub.z) == NULL) {
                {
                    Vec v = {0.0f, 0.0f, 0.0f};
                    p->vel = v;
                }
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
#define IW(p, o) (*(s32*)((u8*)(p) + (o)))

#define SF(p, o) (*(s16*)((u8*)(p) + (o)))
void puniModeAttack(PuniData* p) {
    PuniData* best;
    Vec d;
    f32 m;
    s32 i;
    PuniData* q;
    switch (p->unk114) {
        case 0:
            p->anim = 1;
            p->unk114 = 1;
        case 1:
            if (p->unk1A0 > 10.0f) {
                p->unkE = p->unkC;
                PuniDokuritsu(p);
                p->unk1DC = Punigp->unk360;
                p->unkC = 13;
                p->unk114 = 0;
                break;
            }
            puniSearch(p);
            if ((PuniData*)p->unk1DC != NULL) {
                PSVECSubtract(&((PuniData*)p->unk1DC)->pos, &p->pos, &d);
                if (PSVECMag(&d) > FF((PuniData*)p->unk1DC, 0x19C)) {
                    PSVECNormalize(&d, &d);
                    d.y = 0.0f;
                    PSVECScale(&d, &d, 1.0f);
                    PSVECAdd(&p->vel, &d, &p->vel);
                    p->unk174 = 3.0f;
                } else {
                    puniParaAttack(p, (PuniData*)p->unk1DC);
                }
            }
            break;
    }
}

void puniModeDamage(PuniData* p) {
    Vec d;
    switch (p->unk114) {
        case 0:
            if (IW(Punigp, 0x4C0)++ < 6) psndSFXOn_3D("SFX_STG2_FIGHT_TOGE1", &p->pos);
            p->unk114 = 1;
            break;
        case 1:
            if (IW(Punigp, 0x4C4)++ < 6) psndSFXOn_3D("SFX_STG2_FIGHT_TOGE2", &p->pos);
            p->unk114 = 2;
        case 2:
            PSVECSubtract(&p->pos, &((PuniData*)p->unk1DC)->pos, &d);
            if (0.0f == PSVECMag(&d)) {
                {
                    Vec v_ = {0.0f, 0.0f, 0.0f};
                    d = v_;
                }
            } else {
                PSVECNormalize(&d, &d);
            }
            d.y = 0.0f;
            PSVECScale(&d, &d, 3.0f);
            p->vel = d;
            FF(p, 0x178) = 5.0f;
            p->anim = 3;
            p->unk114 = 3;
            break;
        case 3:
            p->pos.y += FF(p, 0x178);
            FF(p, 0x178) -= 0.5f;
            if (p->pos.y <= 0.001f) {
                p->unk4 &= ~0x2000;
                p->pos.y = 0.0f;
                FF(p, 0x178) = 0.0f;
                p->unk138 = p->pos;
                p->hp -= p->damage;
                if (p->hp <= 0) {
                    p->hp = 0;
                    p->unk4 |= 0x4000;
                    p->unk8 |= 0x10;
                }
                if ((p->hp * 100) / p->maxHp <= 30) {
                    p->unkC = 8;
                    p->anim = 2;
                    p->unk114 = 0;
                } else {
                    p->unkC = 0;
                    p->anim = 0;
                    p->unk114 = 0;
                }
            }
            break;
    }
}


void puniModePiyori(PuniData* p) {
    if (p->unk1A0 > 10.0f) {
        p->unkE = p->unkC;
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unk4 &= ~0x8000000;
        p->unk8 &= ~2;
        p->unkC = 13;
        p->unk114 = 0;
        return;
    }
    switch (p->unk114) {
        case 0:
            if (p->unk4 & 2) {
                p->unk128 = 600;
                p->anim = 4;
                p->unk4 |= 0x8100000;
                p->unk8 |= 2;
                p->unk114 = 2;
            } else {
                p->unk114 = 10;
            }
            break;
        case 2:
            if (p->unk128-- == 0) {
                p->unk4 &= ~0x8000000;
                p->unk8 &= ~2;
                p->unk114 = 10;
            }
            break;
        case 10:
            if (p->unkE == 10) {
                if (p->hp * 100 / p->maxHp <= 30) {
                    p->unkC = 8;
                    p->anim = 2;
                    p->unk114 = 0;
                } else {
                    p->unkC = 0;
                    p->anim = 0;
                    p->unk114 = 0;
                }
            } else {
                p->unkC = p->unkE;
                if (p->unkE == 2) {
                    p->unkC = 1;
                }
                p->unk114 = 0;
            }
            break;
    }
}


void puniModeEscape(PuniData* p) {
    Vec d;
    f32 dist;

    switch (p->unk114) {
        case 0:
            break;
        default:
            return;
    }
    if (p->unk1A0 > 10.0f) {
        p->unkE = p->unkC;
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
        return;
    }
    if (p->hp * 100 / p->maxHp >= 80) {
        p->unkC = 0;
        p->anim = 0;
        p->unk114 = 0;
        return;
    }
    if ((s32)(gp->retraceCount & 3) == (*(s16*)((u8*)p + 0x116) & 3)) {
        if (p->unk4 & 1) {
            p->unk1DC = (s32)searchBattleTeki_inl(p);
        } else {
            p->unk1DC = (s32)searchBattleMikata_inl(p);
        }
    }
    if ((PuniData*)p->unk1DC == NULL) return;
    PSVECSubtract(&((PuniData*)p->unk1DC)->pos, &p->pos, &d);
    dist = PSVECMag(&d);
    if (dist >= 120.0f) {
        {
            Vec v_ = {0.0f, 0.0f, 0.0f};
            p->vel = v_;
        }
        p->unkC = 11;
        p->anim = 0;
        p->unk114 = 0;
        return;
    }
    if (0.0f == dist) {
        {
            Vec v_ = {0.0f, 0.0f, 0.0f};
            d = v_;
        }
    } else {
        PSVECNormalize(&d, &d);
    }
    d.y = 0.0f;
    PSVECScale(&d, &d, 0.8f);
    PSVECSubtract(&p->vel, &d, &p->vel);
    p->unk174 = 2.4f;
}


void puniModeRecover(PuniData* p) {
    switch (p->unk114) {
        case 0: {
            int r = puniPositionCheck(p);
            if (r != 0) {
                p->unk58C = r;
                p->unk590 = p->pos;
                puniPositionRecover(p);
                p->unk59C = p->pos;
            }
            {
                Vec puni_recover_vel = {0.0f, 0.0f, 0.0f};
                p->vel = puni_recover_vel;
            }
            p->unk114 = 1;
            break;
        }
        case 1: {
            if (p->hp * 100 / p->maxHp >= 80) {
                p->unkC = 0;
                p->anim = 0;
                p->unk114 = 0;
            } else if (p->unk1A0 > 10.0f) {
                p->unkE = p->unkC;
                p->unk1DC = Punigp->unk360;
                p->unkC = 13;
                p->unk114 = 0;
            } else {
                if (((s32)gp->retraceCount & 3) == (*(s16*)&p->unk116[0] & 3)) {
                    if (p->unk4 & 1) {
                        p->unk1DC = (s32)searchBattleTeki_inl(p);
                    } else {
                        p->unk1DC = (s32)searchBattleMikata_inl(p);
                    }
                }
                if ((PuniData*)p->unk1DC != NULL) {
                    Vec d;
                    PSVECSubtract(&((PuniData*)p->unk1DC)->pos, &p->pos, &d);
                    if (PSVECMag(&d) < 80.0f) {
                        p->unkC = 8;
                        p->anim = 2;
                        p->unk114 = 0;
                    }
                }
            }
            break;
        }
    }
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

#define WPF(p, o) (*(void**)((u8*)(p) + (o)))
#define WFF(p, o) (*(f32*)((u8*)(p) + (o)))
int puniMoveAtari(PuniData* p, Vec* start, Vec* dir, int reflect, f32 dist);
typedef int (*PuniMoveAtariW)(PuniData*, Vec, Vec, int, f32);
int puniModeWind_sub(PuniData* p) {
    Vec dir;
    Vec start;
    f32 mag = PSVECMag(&p->vel);
    start = p->pos;
    start.y += 1.0f;
    if (0.0f != mag) {
        PSVECNormalize(&p->vel, &dir);
    } else {
        {
            Vec v_ = {0.0f, 0.0f, 0.0f};
            dir = v_;
        }
    }
    ((PuniMoveAtariW)puniMoveAtari)(p, start, dir, 0, mag); // FAKE: by-value call through a cast type; a real puniMoveAtari(p, &start, &dir, ...) on copies drops this exact function
    if (Punigp->unk43C == 3 && (WPF(p, 0x210) != NULL || WPF(p, 0x214) != NULL)) {
        p->unk114 = 10;
        return 2;
    }
    if (WPF(p, 0x210) != NULL || WPF(p, 0x214) != NULL) {
        if (WPF(p, 0x210) != NULL && (((s32*)WPF(p, 0x210))[1] & 4)) {
            WFF(p, 0x168) = -WFF(p, 0x560);
            WFF(p, 0x16C) = 0.0f;
            WFF(p, 0x170) = -WFF(p, 0x568);
            *(Vec*)&WFF(p, 0x150) = p->pos;
            p->unk114 = 3;
            return 1;
        } else if (WPF(p, 0x214) != NULL && (((s32*)WPF(p, 0x214))[1] & 4)) {
            WFF(p, 0x168) = -WFF(p, 0x560);
            WFF(p, 0x16C) = 0.0f;
            WFF(p, 0x170) = -WFF(p, 0x568);
            *(Vec*)&WFF(p, 0x150) = p->pos;
            p->unk114 = 3;
            return 1;
        } else {
            p->unk114 = 10;
            return 2;
        }
    }
    return 0;
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



void puniModeWind(PuniData *p);
static void* jumptable_00024228[] = {
    (void*)((char*)puniModeWind + 0x40),
    (void*)((char*)puniModeWind + 0x1bc),
    (void*)((char*)puniModeWind + 0x318),
    (void*)((char*)puniModeWind + 0x440),
    (void*)((char*)puniModeWind + 0x470),
    (void*)((char*)puniModeWind + 0x6bc),
    (void*)((char*)puniModeWind + 0x6bc),
    (void*)((char*)puniModeWind + 0x6bc),
    (void*)((char*)puniModeWind + 0x6bc),
    (void*)((char*)puniModeWind + 0x6bc),
    (void*)((char*)puniModeWind + 0x574)
};
static const Vec puni_fall_dir;
static const float vec3_mri_00025784[3] = {0.0f, 0.0f, 0.0f};
static const float vec3_mri_00025790[3] = {0.0f, -1.0f, 0.0f};
static const float vec3_mri_0002579c[3] = {0.0f, 0.0f, 0.0f};
static const float vec3_mri_000257a8[3] = {0.0f, 0.0f, 0.0f};
static const float vec3_mri_000257b4[3] = {0.0f, 0.0f, 0.0f};
static const float float_8_mri_000257c0[1] = {8.0f};
static const float float_0p06_mri_000257c4[1] = {0.05999999865889549f};
static const float float_0p03_mri_000257c8[1] = {0.029999999329447746f};
static const float float_0p003_mri_000257cc[1] = {0.003000000026077032f};
// FAKE: whole-function asm (brute-force pass)
asm void puniModeWind(PuniData *p) {
    nofralloc
    stwu r1,-80(r1)
    mflr r0
    stw r0,84(r1)
    stw r31,76(r1)
    mr r31,r3
    bl marioGetPtr
    lhz r0,276(r31)
    mr r4,r3
    cmplwi r0,10
    bgt L_af48
    lis r3,jumptable_00024228@ha
    slwi r0,r0,2
    addi r3,r3,jumptable_00024228@l
    lwzx r0,r3,r0
    mtctr r0
    bctr
    lwz r0,4(r31)
    rlwinm. r0,r0,0,27,28
    beq L_a8e8
    lis r3,float_8_mri_000257c0@ha
    lfs f0,float_8_mri_000257c0@l(r3)
    stfs f0,392(r31)
    b L_a8f4
L_a8e8:
    lis r3,float_8_mri_000257c0@ha
    lfs f0,float_8_mri_000257c0@l(r3)
    stfs f0,328(r31)
L_a8f4:
    lwz r0,4(r31)
    addi r3,r31,300
    addi r4,r4,140
    addi r5,r1,48
    rlwinm r0,r0,0,12,10
    stw r0,4(r31)
    bl PSVECSubtract
    lis r3,(puni_fall_dir-708)@ha
    lfs f1,48(r1)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpo cr0,f1,f0
    bge L_a930
    li r0,0
    stw r0,480(r31)
    b L_a938
L_a930:
    li r0,1
    stw r0,480(r31)
L_a938:
    lis r4,(puni_fall_dir+88)@ha
    lis r3,(puni_fall_dir-716)@ha
    addi r5,r4,(puni_fall_dir+88)@l
    lfs f3,48(r1)
    addi r4,r3,(puni_fall_dir-716)@l
    lfs f2,0(r5)
    lfs f1,56(r1)
    addi r3,r1,48
    lfs f0,0(r4)
    fmuls f2,f3,f2
    fmuls f0,f1,f0
    stfs f2,48(r1)
    stfs f0,56(r1)
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f0,f1
    stfs f1,8(r1)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    beq L_a998
    addi r3,r1,48
    mr r4,r3
    bl PSVECNormalize
    b L_a9b8
L_a998:
    lis r3,vec3_mri_00025784@ha
    addi r5,r3,vec3_mri_00025784@l
    lwz r4,0(r5)
    lwz r3,4(r5)
    lwz r0,8(r5)
    stw r4,48(r1)
    stw r3,52(r1)
    stw r0,56(r1)
L_a9b8:
    lis r4,(puni_fall_dir-708)@ha
    lis r5,(puni_fall_dir-348)@ha
    lfs f3,(puni_fall_dir-708)@l(r4)
    lis r3,(puni_fall_dir-556)@ha
    addi r4,r3,(puni_fall_dir-556)@l
    lfs f2,(puni_fall_dir-348)@l(r5)
    stfs f3,52(r1)
    lis r3,(puni_fall_dir+16)@ha
    lfs f0,0(r4)
    lfs f1,416(r31)
    fdivs f1,f1,f0
    lfs f0,(puni_fall_dir+16)@l(r3)
    fmadds f0,f2,f1,f0
    stfs f0,500(r31)
    lwz r3,48(r1)
    lwz r0,52(r1)
    stw r3,504(r31)
    stw r0,508(r31)
    lwz r0,56(r1)
    stw r0,512(r31)
    stfs f3,492(r31)
    stfs f3,496(r31)
    lwz r0,4(r31)
    clrlwi. r0,r0,31
    beq L_aa2c
    lis r3,float_0p06_mri_000257c4@ha
    lfs f0,float_0p06_mri_000257c4@l(r3)
    stfs f0,376(r31)
    b L_aa38
L_aa2c:
    lis r3,(puni_fall_dir-724)@ha
    lfs f0,(puni_fall_dir-724)@l(r3)
    stfs f0,376(r31)
L_aa38:
    li r3,5
    li r0,1
    sth r3,284(r31)
    sth r0,276(r31)
    lfs f1,492(r31)
    addi r3,r31,504
    addi r4,r1,48
    bl PSVECScale
    lis r4,(puni_fall_dir-708)@ha
    lwz r0,52(r1)
    addi r5,r4,(puni_fall_dir-708)@l
    lwz r4,48(r1)
    lfs f0,0(r5)
    lis r3,(puni_fall_dir+408)@ha
    stfs f0,56(r1)
    lfs f0,(puni_fall_dir+408)@l(r3)
    stw r4,348(r31)
    stw r0,352(r31)
    lwz r0,56(r1)
    stw r0,356(r31)
    lfs f1,384(r31)
    fcmpo cr0,f1,f0
    bge L_aa9c
    lwz r0,480(r31)
    b L_aaa4
L_aa9c:
    lwz r0,480(r31)
    xori r0,r0,1
L_aaa4:
    cmpwi r0,0
    beq L_aae4
    lis r4,(puni_fall_dir-568)@ha
    lis r3,(puni_fall_dir+412)@ha
    lfs f2,388(r31)
    lfs f1,(puni_fall_dir-568)@l(r4)
    lfs f0,(puni_fall_dir+412)@l(r3)
    fadds f1,f2,f1
    stfs f1,388(r31)
    lfs f1,388(r31)
    fcmpo cr0,f1,f0
    cror eq,gt,eq
    bne L_ab20
    fsubs f0,f1,f0
    stfs f0,388(r31)
    b L_ab20
L_aae4:
    lis r4,(puni_fall_dir-568)@ha
    lis r3,(puni_fall_dir-708)@ha
    lfs f2,388(r31)
    lfs f1,(puni_fall_dir-568)@l(r4)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fsubs f1,f2,f1
    stfs f1,388(r31)
    lfs f1,388(r31)
    fcmpo cr0,f1,f0
    cror eq,lt,eq
    bne L_ab20
    lis r3,(puni_fall_dir+412)@ha
    lfs f0,(puni_fall_dir+412)@l(r3)
    fadds f0,f1,f0
    stfs f0,388(r31)
L_ab20:
    lfs f1,492(r31)
    mr r3,r31
    lfs f0,496(r31)
    fadds f0,f1,f0
    stfs f0,492(r31)
    lfs f1,496(r31)
    lfs f0,376(r31)
    fadds f0,f1,f0
    stfs f0,496(r31)
    bl puniModeWind_sub
    cmpwi r3,0
    bne L_af48
    lfs f1,492(r31)
    lfs f0,500(r31)
    fcmpo cr0,f1,f0
    cror eq,gt,eq
    bne L_af48
    lwz r0,4(r31)
    clrlwi. r0,r0,31
    beq L_ab80
    lis r3,float_0p03_mri_000257c8@ha
    lfs f0,float_0p03_mri_000257c8@l(r3)
    stfs f0,376(r31)
    b L_ab8c
L_ab80:
    lis r3,float_0p003_mri_000257cc@ha
    lfs f0,float_0p003_mri_000257cc@l(r3)
    stfs f0,376(r31)
L_ab8c:
    lis r3,(puni_fall_dir-708)@ha
    li r0,2
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f0,496(r31)
    sth r0,276(r31)
    b L_af48
    lfs f1,492(r31)
    addi r3,r31,504
    addi r4,r1,48
    bl PSVECScale
    lis r4,(puni_fall_dir-708)@ha
    lwz r0,52(r1)
    addi r5,r4,(puni_fall_dir-708)@l
    lwz r4,48(r1)
    lfs f0,0(r5)
    lis r3,(puni_fall_dir+408)@ha
    stfs f0,56(r1)
    lfs f0,(puni_fall_dir+408)@l(r3)
    stw r4,348(r31)
    stw r0,352(r31)
    lwz r0,56(r1)
    stw r0,356(r31)
    lfs f1,384(r31)
    fcmpo cr0,f1,f0
    bge L_abf8
    lwz r0,480(r31)
    b L_ac00
L_abf8:
    lwz r0,480(r31)
    xori r0,r0,1
L_ac00:
    cmpwi r0,0
    beq L_ac40
    lis r4,(puni_fall_dir-568)@ha
    lis r3,(puni_fall_dir+412)@ha
    lfs f2,388(r31)
    lfs f1,(puni_fall_dir-568)@l(r4)
    lfs f0,(puni_fall_dir+412)@l(r3)
    fadds f1,f2,f1
    stfs f1,388(r31)
    lfs f1,388(r31)
    fcmpo cr0,f1,f0
    cror eq,gt,eq
    bne L_ac7c
    fsubs f0,f1,f0
    stfs f0,388(r31)
    b L_ac7c
L_ac40:
    lis r4,(puni_fall_dir-568)@ha
    lis r3,(puni_fall_dir-708)@ha
    lfs f2,388(r31)
    lfs f1,(puni_fall_dir-568)@l(r4)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fsubs f1,f2,f1
    stfs f1,388(r31)
    lfs f1,388(r31)
    fcmpo cr0,f1,f0
    cror eq,lt,eq
    bne L_ac7c
    lis r3,(puni_fall_dir+412)@ha
    lfs f0,(puni_fall_dir+412)@l(r3)
    fadds f0,f1,f0
    stfs f0,388(r31)
L_ac7c:
    lfs f1,492(r31)
    mr r3,r31
    lfs f0,496(r31)
    fsubs f0,f1,f0
    stfs f0,492(r31)
    lfs f1,496(r31)
    lfs f0,376(r31)
    fadds f0,f1,f0
    stfs f0,496(r31)
    bl puniModeWind_sub
    cmpwi r3,0
    bne L_af48
    lis r3,(puni_fall_dir-708)@ha
    lfs f1,492(r31)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpo cr0,f1,f0
    bge L_af48
    li r0,10
    sth r0,276(r31)
    b L_af48
    lwz r0,8(r31)
    addi r3,r31,360
    addi r4,r1,48
    ori r0,r0,4
    stw r0,8(r31)
    bl PSVECNormalize
    lfs f1,400(r31)
    addi r3,r1,48
    addi r4,r31,348
    bl PSVECScale
    li r0,4
    sth r0,276(r31)
    addi r3,r31,300
    addi r4,r31,348
    mr r5,r3
    bl PSVECAdd
    lwz r0,304(r31)
    lis r3,(puni_fall_dir+248)@ha
    lis r4,vec3_mri_00025790@ha
    lwz r10,300(r31)
    stw r0,40(r1)
    addi r7,r4,vec3_mri_00025790@l
    lfs f0,(puni_fall_dir+248)@l(r3)
    lis r4,(puni_fall_dir+16)@ha
    lfs f1,40(r1)
    addi r8,r4,(puni_fall_dir+16)@l
    lwz r9,308(r31)
    addi r4,r1,24
    fadds f2,f1,f0
    lwz r3,0(r7)
    stw r10,36(r1)
    addi r5,r1,28
    lfs f0,0(r8)
    addi r6,r1,32
    stw r9,44(r1)
    addi r8,r1,12
    lwz r11,4(r7)
    addi r9,r1,16
    lwz r0,8(r7)
    addi r7,r1,8
    stw r3,48(r1)
    addi r10,r1,20
    lfs f1,36(r1)
    li r3,0
    stw r11,52(r1)
    lfs f3,44(r1)
    stw r0,56(r1)
    lfs f4,48(r1)
    lfs f5,52(r1)
    stfs f0,8(r1)
    lfs f6,56(r1)
    stfs f2,40(r1)
    bl hitCheckFilter
    cmplwi r3,0
    bne L_adf4
    lis r4,vec3_mri_0002579c@ha
    lis r3,(puni_fall_dir-708)@ha
    addi r7,r4,vec3_mri_0002579c@l
    lfs f0,(puni_fall_dir-708)@l(r3)
    lwz r6,0(r7)
    li r4,17
    lwz r5,4(r7)
    li r0,0
    stw r6,348(r31)
    stw r5,352(r31)
    lwz r3,8(r7)
    stw r3,356(r31)
    sth r4,12(r31)
    sth r0,284(r31)
    stfs f0,392(r31)
    stfs f0,388(r31)
    stfs f0,328(r31)
    sth r0,276(r31)
    b L_af48
L_adf4:
    li r0,10
    sth r0,276(r31)
    b L_af48
    lis r3,(puni_fall_dir+408)@ha
    lfs f1,384(r31)
    lfs f0,(puni_fall_dir+408)@l(r3)
    fcmpo cr0,f1,f0
    bge L_ae1c
    lwz r0,480(r31)
    b L_ae24
L_ae1c:
    lwz r0,480(r31)
    xori r0,r0,1
L_ae24:
    cmpwi r0,0
    beq L_ae64
    lis r4,(puni_fall_dir-568)@ha
    lis r3,(puni_fall_dir+412)@ha
    lfs f2,388(r31)
    lfs f1,(puni_fall_dir-568)@l(r4)
    lfs f0,(puni_fall_dir+412)@l(r3)
    fadds f1,f2,f1
    stfs f1,388(r31)
    lfs f1,388(r31)
    fcmpo cr0,f1,f0
    cror eq,gt,eq
    bne L_aea0
    fsubs f0,f1,f0
    stfs f0,388(r31)
    b L_aea0
L_ae64:
    lis r4,(puni_fall_dir-568)@ha
    lis r3,(puni_fall_dir-708)@ha
    lfs f2,388(r31)
    lfs f1,(puni_fall_dir-568)@l(r4)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fsubs f1,f2,f1
    stfs f1,388(r31)
    lfs f1,388(r31)
    fcmpo cr0,f1,f0
    cror eq,lt,eq
    bne L_aea0
    lis r3,(puni_fall_dir+412)@ha
    lfs f0,(puni_fall_dir+412)@l(r3)
    fadds f0,f1,f0
    stfs f0,388(r31)
L_aea0:
    lis r3,(puni_fall_dir-708)@ha
    lfs f1,416(r31)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpo cr0,f1,f0
    bgt L_af48
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,1084(r3)
    cmpwi r0,3
    bne L_af0c
    li r0,10
    lis r3,vec3_mri_000257a8@ha
    sth r0,12(r31)
    addi r5,r3,vec3_mri_000257a8@l
    li r0,0
    stfs f0,392(r31)
    stfs f0,388(r31)
    stfs f0,328(r31)
    lwz r4,0(r5)
    lwz r3,4(r5)
    stw r4,348(r31)
    stw r3,352(r31)
    lwz r3,8(r5)
    stw r3,356(r31)
    sth r0,276(r31)
    b L_af48
L_af0c:
    stfs f0,392(r31)
    lis r3,vec3_mri_000257b4@ha
    addi r6,r3,vec3_mri_000257b4@l
    li r3,1
    stfs f0,388(r31)
    li r0,0
    stfs f0,328(r31)
    lwz r5,0(r6)
    lwz r4,4(r6)
    stw r5,348(r31)
    stw r4,352(r31)
    lwz r4,8(r6)
    stw r4,356(r31)
    sth r3,12(r31)
    sth r0,276(r31)
L_af48:
    lwz r0,84(r1)
    lwz r31,76(r1)
    mtlr r0
    addi r1,r1,80
    blr
}

#define FP(p, o) (*(s32**)((u8*)(p) + (o)))
void puniModeFall(PuniData* p) {
    Vec start;
    Vec dir;
    f32 mag;
    PuniTarget* t = Punigp->targets;
    s32* h0;
    s32* h1;
    s32 found;
    s32 i;

    switch (p->unk114) {
    case 0:
        p->unk4 &= ~0x00100000;
        {
            Vec v = {0.0f, -0.8f, 0.0f};
            p->vel = v;
        }
        p->unk114 = 1;
        break;
    case 1:
        p->vel.x = 0.0f;
        p->vel.y -= 0.45f;
        {
            Vec v = {0.0f, -1.0f, 0.0f};
            dir = v;
        }
        mag = PSVECMag(&p->vel);
        start = p->pos;
        ((PuniMoveAtariW)puniMoveAtari)(p, start, dir, 0, mag); // FAKE: by-value call through a cast type; a real puniMoveAtari(p, &start, &dir, ...) on copies drops this exact function
        h0 = FP(p, 0x210);
        if (h0 != NULL || FP(p, 0x214) != NULL) {
            if (h0 != NULL && (h0[1] & 4)) {
                break;
            }
            h1 = FP(p, 0x214);
            if (h1 != NULL && (h1[1] & 4)) {
                break;
            }
            if (h0 != NULL && (h0[1] & 0x100)) {
                p->unk1E0 = 0x12;
                p->anim = 0;
                p->unk114 = 2;
                break;
            }
            if (h1 != NULL && (h1[1] & 0x100)) {
                p->unk1E0 = 0x12;
                p->anim = 0;
                p->unk114 = 2;
                break;
            }
            if (h0 != NULL && (h0[1] & 0x200)) {
                p->unk1E0 = 0x16;
                p->anim = 3;
                p->unk114 = 2;
                break;
            }
            if (h1 != NULL && (h1[1] & 0x200)) {
                p->unk1E0 = 0x16;
                p->anim = 3;
                p->unk114 = 2;
                break;
            }
            found = 0;
            for (i = 0; i < 2; i++, t++) {
                if (t->hit == NULL) {
                    continue;
                }
                if ((void*)h0 == (void*)t->hit) {
                    found = 1;
                    p->unk1F8 = t->pos;
                    break;
                }
                if ((void*)h1 == (void*)t->hit) {
                    found = 1;
                    p->unk1F8 = t->pos;
                    break;
                }
            }
            if (found) {
                p->unk1E0 = 0x17;
            } else {
                p->unk1E0 = 0xF;
            }
            if (Punigp->unk328 == 0x12 && p->pos.y < -300.0f) {
                s32 zero = 0;
                puniswTrapSetindex(*(s16*)&p->unk116[0], &zero);
                p->unk4 &= ~0x00800000;
            }
            {
                Vec v = {0.0f, 0.0f, 0.0f};
                p->vel = v;
            }
            p->unk114 = 2;
        } else if (p->pos.y <= -1000.0f) {
            p->unk590 = p->pos;
            p->pos = Punigp->unk344;
            p->pos.x += randf(0.0f, 2.0f) - 1.0f;
            p->pos.z += randf(0.0f, 2.0f) - 1.0f;
            p->unk138 = p->pos;
            p->unk59C = p->pos;
            p->unk1E0 = 0x10;
            {
                Vec v = {0.0f, 0.0f, 0.0f};
                p->vel = v;
            }
            p->unk114 = 2;
        }
        break;
    case 2:
        p->unkC = p->unk1E0;
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            p->vel = v;
        }
        p->unk114 = 0;
        break;
    }
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


static const Vec puni_fall_dir;
static const float vec3_mri_00025810[3] = {0.0f, 0.9399999976158142f, 0.0f};
static const float vec3_mri_0002581c[3] = {0.0f, 0.6600000262260437f, 0.0f};
static const float vec3_mri_00025828[3] = {0.0f, 0.0f, 0.0f};
static const char str_00005514[] = "SFX_STG2_SOAPBALL_MOVE1";
static const float float_1p2_mri_0002584c[1] = {1.2000000476837158f};
// FAKE: whole-function asm (brute-force pass)
asm void puniModeUpdraft(PuniData *p) {
    nofralloc
    stwu r1,-128(r1)
    mflr r0
    stw r0,132(r1)
    stfd f31,112(r1)
    psq_st f31,120(r1),0,0
    stmw r29,100(r1)
    mr r30,r3
    bl marioGetPtr
    lhz r0,276(r30)
    mr r31,r3
    cmplwi r0,0
    bne L_b5d8
    lis r3,vec3_mri_00025810@ha
    addi r4,r3,vec3_mri_00025810@l
    lwz r3,0(r4)
    lwz r0,4(r4)
    stw r3,348(r30)
    stw r0,352(r30)
    lwz r0,8(r4)
    stw r0,356(r30)
    b L_b5f8
L_b5d8:
    lis r3,vec3_mri_0002581c@ha
    addi r4,r3,vec3_mri_0002581c@l
    lwz r3,0(r4)
    lwz r0,4(r4)
    stw r3,348(r30)
    stw r0,352(r30)
    lwz r0,8(r4)
    stw r0,356(r30)
L_b5f8:
    lis r3,gp@ha
    addi r3,r3,gp@l
    lwz r3,0(r3)
    lwz r0,28(r3)
    clrlwi. r0,r0,27
    bne L_b620
    lis r3,str_00005514@ha
    addi r4,r30,300
    addi r3,r3,str_00005514@l
    bl psndSFXOn_3D
L_b620:
    lis r3,gp@ha
    lha r0,278(r30)
    addi r3,r3,gp@l
    lwz r3,0(r3)
    lwz r3,28(r3)
    add r0,r3,r0
    clrlwi r3,r0,28
    cmpwi r3,7
    addi r0,r3,-3
    ble L_b650
    clrlwi r0,r3,29
    subfic r0,r0,4
L_b650:
    xoris r3,r0,32768
    lis r0,17200
    lis r4,(puni_fall_dir-580)@ha
    stw r3,84(r1)
    addi r3,r4,(puni_fall_dir-580)@l
    stw r0,80(r1)
    lis r4,(puni_fall_dir-716)@ha
    lfd f1,0(r3)
    lfd f0,80(r1)
    lfs f2,(puni_fall_dir-716)@l(r4)
    fsubs f0,f0,f1
    fmuls f0,f2,f0
    stfs f0,324(r30)
    lhz r0,276(r30)
    cmpwi r0,1
    beq L_b768
    bge L_b6a0
    cmpwi r0,0
    bge L_b6ac
    b L_b82c
L_b6a0:
    cmpwi r0,3
    bge L_b82c
    b L_b7c8
L_b6ac:
    lis r3,(puni_fall_dir-568)@ha
    lfs f1,416(r30)
    lfs f0,(puni_fall_dir-568)@l(r3)
    fcmpo cr0,f1,f0
    ble L_b82c
    lis r4,Punigp@ha
    addi r3,r30,300
    addi r5,r4,Punigp@l
    addi r4,r31,140
    lwz r6,0(r5)
    addi r5,r1,68
    lwz r0,864(r6)
    stw r0,476(r30)
    bl PSVECSubtract
    addi r3,r1,68
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f0,f1
    beq L_b708
    addi r3,r1,68
    mr r4,r3
    bl PSVECNormalize
L_b708:
    lis r4,(puni_fall_dir-708)@ha
    lis r3,(puni_fall_dir-556)@ha
    addi r5,r4,(puni_fall_dir-708)@l
    lfs f0,(puni_fall_dir-556)@l(r3)
    lfs f3,0(r5)
    lis r4,float_1p2_mri_0002584c@ha
    lfs f2,float_1p2_mri_0002584c@l(r4)
    li r0,1
    stfs f3,72(r1)
    stfs f3,76(r1)
    lfs f1,416(r30)
    fdivs f0,f1,f0
    fadds f0,f2,f0
    stfs f0,500(r30)
    lwz r4,68(r1)
    lwz r3,72(r1)
    stw r4,504(r30)
    stw r3,508(r30)
    lwz r3,76(r1)
    stw r3,512(r30)
    stfs f3,492(r30)
    stfs f3,496(r30)
    sth r0,276(r30)
    b L_b82c
L_b768:
    lfs f1,492(r30)
    addi r3,r30,504
    addi r4,r1,68
    bl PSVECScale
    addi r3,r30,348
    addi r4,r1,68
    mr r5,r3
    bl PSVECAdd
    lfs f2,492(r30)
    lis r3,(puni_fall_dir+480)@ha
    lfs f1,496(r30)
    lfs f0,(puni_fall_dir+480)@l(r3)
    fadds f1,f2,f1
    stfs f1,492(r30)
    lfs f1,496(r30)
    fadds f0,f1,f0
    stfs f0,496(r30)
    lfs f0,492(r30)
    lfs f1,500(r30)
    fcmpo cr0,f0,f1
    cror eq,gt,eq
    bne L_b82c
    stfs f1,492(r30)
    b L_b82c
L_b7c8:
    lfs f1,492(r30)
    addi r3,r30,504
    addi r4,r1,68
    bl PSVECScale
    addi r3,r30,348
    addi r4,r1,68
    mr r5,r3
    bl PSVECAdd
    lfs f2,492(r30)
    lis r3,(puni_fall_dir+484)@ha
    lfs f0,496(r30)
    addi r4,r3,(puni_fall_dir+484)@l
    lfs f1,0(r4)
    lis r3,(puni_fall_dir-708)@ha
    fsubs f2,f2,f0
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f2,492(r30)
    lfs f2,496(r30)
    fadds f1,f2,f1
    stfs f1,496(r30)
    lfs f1,492(r30)
    fcmpo cr0,f1,f0
    bge L_b82c
    li r0,0
    sth r0,276(r30)
L_b82c:
    addi r3,r30,348
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    fmr f31,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f0,f31
    beq L_b858
    addi r3,r30,348
    addi r4,r1,68
    bl PSVECNormalize
    b L_b878
L_b858:
    lis r3,vec3_mri_00025828@ha
    addi r5,r3,vec3_mri_00025828@l
    lwz r4,0(r5)
    lwz r3,4(r5)
    lwz r0,8(r5)
    stw r4,68(r1)
    stw r3,72(r1)
    stw r0,76(r1)
L_b878:
    lwz r29,300(r30)
    fmr f1,f31
    lwz r31,304(r30)
    mr r3,r30
    lwz r12,308(r30)
    addi r4,r1,20
    lwz r11,348(r30)
    lwz r10,352(r30)
    addi r5,r1,8
    lwz r9,356(r30)
    li r6,1
    lwz r8,68(r1)
    lwz r7,72(r1)
    lwz r0,76(r1)
    stw r29,56(r1)
    stw r31,60(r1)
    stw r12,64(r1)
    stw r11,44(r1)
    stw r10,48(r1)
    stw r9,52(r1)
    stw r8,8(r1)
    stw r7,12(r1)
    stw r0,16(r1)
    stw r29,20(r1)
    stw r31,24(r1)
    stw r12,28(r1)
    bl puniMoveAtari
    lwz r0,300(r30)
    lis r4,(puni_fall_dir-720)@ha
    lwz r3,536(r30)
    addi r5,r4,(puni_fall_dir-720)@l
    stw r0,32(r1)
    lis r4,(puni_fall_dir+12)@ha
    lwz r6,304(r30)
    lfs f1,32(r1)
    lfs f0,324(r30)
    lwz r0,308(r30)
    fadds f3,f1,f0
    lwz r3,12(r3)
    stw r6,36(r1)
    lfs f0,0(r5)
    stfs f3,4(r3)
    lfs f1,36(r1)
    lwz r3,536(r30)
    fadds f2,f1,f0
    stw r0,40(r1)
    lwz r3,12(r3)
    lfs f1,40(r1)
    stfs f2,8(r3)
    lfs f0,(puni_fall_dir+12)@l(r4)
    lwz r3,536(r30)
    fadds f0,f1,f0
    stfs f3,32(r1)
    lwz r3,12(r3)
    stfs f2,36(r1)
    stfs f0,12(r3)
    lwz r3,528(r30)
    stfs f0,40(r1)
    cmplwi r3,0
    bne L_b974
    lwz r0,532(r30)
    cmplwi r0,0
    beq L_ba14
L_b974:
    cmplwi r3,0
    li r4,0
    beq L_b990
    lwz r0,4(r3)
    rlwinm. r0,r0,0,29,29
    beq L_b990
    li r4,1
L_b990:
    lwz r3,532(r30)
    cmplwi r3,0
    beq L_b9ac
    lwz r0,4(r3)
    rlwinm. r0,r0,0,29,29
    beq L_b9ac
    li r4,1
L_b9ac:
    cmpwi r4,0
    bne L_b9d4
    li r0,20
    lis r3,(puni_fall_dir-708)@ha
    sth r0,12(r30)
    li r0,0
    lfs f0,(puni_fall_dir-708)@l(r3)
    sth r0,276(r30)
    stfs f0,324(r30)
    b L_ba14
L_b9d4:
    lwz r4,56(r1)
    addi r3,r30,300
    lwz r0,60(r1)
    mr r5,r3
    stw r4,300(r30)
    addi r4,r30,348
    lwz r6,64(r1)
    stw r0,304(r30)
    lwz r0,44(r1)
    stw r6,308(r30)
    lwz r6,48(r1)
    stw r0,348(r30)
    lwz r0,52(r1)
    stw r6,352(r30)
    stw r0,356(r30)
    bl PSVECAdd
L_ba14:
    lis r3,(puni_fall_dir-708)@ha
    lfs f1,304(r30)
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpo cr0,f1,f0
    cror eq,gt,eq
    bne L_ba40
    li r3,20
    li r0,0
    sth r3,12(r30)
    sth r0,276(r30)
    stfs f0,324(r30)
L_ba40:
    psq_l f31,120(r1),0,0
    lfd f31,112(r1)
    lmw r29,100(r1)
    lwz r0,132(r1)
    mtlr r0
    addi r1,r1,128
    blr
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

extern double sin(double);
void puniModeFunbari(PuniData* p) {
    switch (p->unk114) {
        case 0: {
            PuniTarget* t;
            int i;
            t = Punigp->targets;
            for (i = 0; i < 10; i++, t++) {
                if ((t->flags & 1) && (t->flags & 2)) break;
            }
            if (i >= 10) {
                p->unk114 = 10;
                break;
            }
            if (p->pos.x > t->pos.x) {
                FF(p, 0x1F4) = -1.0f;
                p->dir = 270.0f;
            } else {
                FF(p, 0x1F4) = 1.0f;
                p->dir = 90.0f;
            }
            p->vel.x = 0.5f;
            p->unk128 = 68;
            FF(p, 0x1EC) = 1.0f;
            p->npc->flags |= 4;
            p->unk114 = 1;
            break;
        }
        case 1:
        case 2:
            {
                f32 s = sin(3.1415927f * FF(p, 0x1EC) / 180.0f);
                if (FF(p, 0x1EC) <= 180.0f) {
                    FF(p, 0x1F0) = 0.5f * s;
                } else {
                    FF(p, 0x1F0) = 0.45f * s;
                }
            }
            FF(p, 0x1EC) += 7.0f;
            if (FF(p, 0x1EC) >= 360.0f) FF(p, 0x1EC) = 360.0f;
            p->pos.y += FF(p, 0x1F0);
            p->pos.x += p->vel.x * FF(p, 0x1F4);
            if (p->unk128-- == 0) p->unk114 = 10;
            break;
        case 10:
            {
                Vec v_ = {0.0f, 0.0f, 0.0f};
                p->vel = v_;
            }
            p->unkC = 17;
            p->anim = 0;
            p->npc->flags &= ~4;
            p->unk114 = 0;
            break;
    }
}

extern f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
void puniModeWater(PuniData* p) {
    Vec d;
    switch (p->unk114) {
        case 0:
            p->unk4 |= 0x800;
            p->unk128 = 60;
            p->unk114 = 1;
        case 1:
            if (p->unk128-- == 0) {
                p->unk4 &= ~0x800;
                p->unk114 = 2;
            }
            break;
        case 2:
            *(u64*)((u8*)p + 0x1C8) = gp->renderTime;
            p->unk1F8 = p->pos;
            FF(p, 0x1EC) = -80.0f;
            FF(p, 0x1F0) = (FF(p, 0x154) - FF(p, 0x1FC)) - FF(p, 0x1EC);
            PSVECNormalize((Vec*)((u8*)p + 0x168), &d);
            PSVECScale(&d, &d, -20.0f);
            {
                f32 x = d.x + p->pos.x;
                f32 z = d.z + p->pos.z;
                FF(p, 0x150) = x;
                FF(p, 0x158) = z;
            }
            p->unk114 = 3;
        case 3: {
            u32 t = ((u32)gp->renderTime - F(p, 0x1CC)) / (*(u32*)0x800000F8 / 4 / 1000);
            if ((s32)t < 300) {
                f32 f = (f32)(s32)t / 300.0f;
                p->pos.x = intplGetValue(0, t, 300, FF(p, 0x1F8), FF(p, 0x150));
                p->pos.z = intplGetValue(0, t, 300, FF(p, 0x200), FF(p, 0x158));
                p->pos.y = f * (FF(p, 0x1EC) * f + FF(p, 0x1F0)) + FF(p, 0x1FC);
                p->unk138 = p->pos;
            } else {
                p->pos = *(Vec*)((u8*)p + 0x150);
                p->unk138 = p->pos;
                p->unk114 = 4;
            }
            break;
        }
        case 4:
            p->unkC = 16;
            p->anim = 0;
            p->unk114 = 0;
            break;
    }
}

void puniModePrehagure(PuniData* p) {
    Vec nrm;
    Vec hit;
    Vec dir;
    Vec start;
    f32 dist;
    s32 res;
    f32 b, a;
    switch (p->unk114) {
        case 0:
            res = 0;
            a = FF(Punigp, 0x350);
            b = FF(Punigp, 0x354);
            if (-1000.0f != a && p->pos.y < a && p->pos.y > b) {
                res = 1;
            }
            a = FF(Punigp, 0x358);
            b = FF(Punigp, 0x35C);
            if (-1000.0f != a && p->pos.y < a && p->pos.y > b) {
                res = 1;
            }
            if (res == 0) {
                res = 1;
            } else {
                start = p->pos;
                start.y += 1.0f;
                dir = puni_fall_dir;
                dist = 3.0f;
                if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &nrm.x, &nrm.y, &nrm.z, start.x, start.y, start.z, dir.x, dir.y, dir.z) == NULL) {
                    res = 2;
                } else {
                    res = 0;
                }
            }
            if (res != 0) {
                p->unk58C = res;
                p->unk590 = p->pos;
                p->pos = Punigp->unk344;
                p->pos.x += randf(0.0f, 2.0f) - 1.0f;
                p->pos.z += randf(0.0f, 2.0f) - 1.0f;
                p->unk138 = p->pos;
                p->unk59C = p->pos;
            }
            p->unk114 = 1;
            break;
        case 1:
            p->unkC = 16;
            p->unk114 = 0;
            break;
    }
}

extern EffectEntry* effFukidashiEntry(s32 a, s32 b, void* c, s32 d, f32 e, f32 f, f32 g, f32 h, f32 i);

void puniModeHagure(PuniData* p) {
    switch (p->unk114) {
        case 0:
            p->effect = effFukidashiEntry(4, 0, (u8*)p + 0x220, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            p->anim = 6;
            p->unk4 |= 0x100000;
            p->unk114 = 1;
        case 1:
            p->unk1E0 = rand() % 21 + 30;
            F(p, 0x1E4) = rand() % 6 + 5;
            p->unk128 = p->unk1E0;
            F(p, 0x1E8) = F(p, 0x1E4);
            p->unk114 = 10;
            FF(p, 0x2AC) = 0.0f;
            FF(p, 0x2B0) = -1000.0f;
            FF(p, 0x2B4) = 0.0f;
        case 10:
            if (p->unk128-- == 0) {
                if (F(p, 0x1E8) & 1) {
                    p->dir = 90.0f;
                } else {
                    p->dir = 270.0f;
                }
                if (F(p, 0x1E8)-- == 0) {
                    p->unk114 = 20;
                } else {
                    p->unk128 = p->unk1E0;
                }
            }
            break;
        case 20:
            p->unk128 = 30;
            p->unk114 = 21;
        case 21:
            if (p->unk128-- == 0) {
                p->unk114 = 30;
            }
            break;
        case 30:
            if (rand() % 2) {
                FF(p, 0x2AC) = p->pos.x;
                FF(p, 0x2B0) = 10.0f + p->pos.y;
                FF(p, 0x2B4) = p->pos.z;
                *(s32*)(*(u8**)((u8*)p->effect + 0xC) + 0x34) = 0;
            }
            p->unk128 = rand() % 41 + 100;
            p->unk114 = 31;
        case 31:
            if (p->unk128-- == 0) {
                p->unk114 = 1;
            }
            break;
    }
    if (p->unk1BC != -1 && p->unk1C0 < 10000.0f) {
        Punigp->unk43C = 2;
        p->unk114 = 0;
        if (p->effect != NULL) {
            effDelete(p->effect);
            p->effect = NULL;
        }
    } else if (p->unk1B4 != -1) {
        PuniDokuritsu(p);
        p->unkC = 4;
        p->unk114 = 0;
        if (p->effect != NULL) {
            effDelete(p->effect);
            p->effect = NULL;
        }
    } else if (p->unk1A0 > 10.0f) {
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unkC = 13;
        p->unk114 = 0;
        if (p->effect != NULL) {
            effDelete(p->effect);
            p->effect = NULL;
        }
    } else if (p->unk1A4 < 150.0f) {
        p->unkC = 1;
        puniFukki(p);
        if (p->effect != NULL) {
            effDelete(p->effect);
            p->effect = NULL;
        }
    }
}

void puniModeDodai(PuniData* p) {
    Vec v;

    switch (p->unk114) {
        case 0:
            PSVECSubtract(&p->pos, &p->unk1F8, &v);
            if (PSVECMag(&v) < 10.0f) {
                {
                    Vec zero = {0.0f, 0.0f, 0.0f};
                    p->vel = zero;
                }
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

void puniModeTrap_sub(PuniData* p) {
    NpcEntry* n;
    if (p->unk4 & 0x20) {
        n = npcNameToPtr("\203K\203C\203h");
        p->unk4 &= ~0x800;
        p->unk4 |= 0x100000;
        n->flags &= ~0x20;
        n->position.x = 0.0f;
        n->position.y = -1000.0f;
        n->position.z = 0.0f;
    }
    if (p->unk4 & 0x40) {
        n = npcNameToPtr("\203K\203C\203h\226\205");
        p->unk4 &= ~0x800;
        p->unk4 |= 0x100000;
        n->flags &= ~0x20;
        n->position.x = 0.0f;
        n->position.y = -1000.0f;
        n->position.z = 0.0f;
    }
    if (p->unk4 & 0x100) {
        n = npcNameToPtr("\203\211\203C\203o\203\213");
        p->unk4 &= ~0x800;
        p->unk4 |= 0x100000;
        n->flags &= ~0x20;
        n->position.x = 0.0f;
        n->position.y = -1000.0f;
        n->position.z = 0.0f;
    }
}

#define TRAP_NPC(name, setpos)                \
    {                                         \
        n = npcNameToPtr(name);               \
        p->unk4 |= 0x800;                     \
        n->position.x = p->pos.x;             \
        n->position.y = p->pos.y;             \
        n->position.z = p->pos.z;             \
        n->direction = p->dir;                   \
        n->flags |= 0x20;                     \
    }
#define TRAP_HIDE(name)                       \
    {                                         \
        n = npcNameToPtr(name);               \
        p->unk4 &= ~0x800;                    \
        p->unk4 |= 0x100000;                  \
        n->flags &= ~0x20;                    \
        n->position.x = 0.0f;                 \
        n->position.y = -1000.0f;             \
        n->position.z = 0.0f;                 \
    }


void puniModeTrap(PuniData* p) {
    NpcEntry* n;
    if (p->unk114 == 0) {
        p->unk4 |= 0x100000;
        if (p->unk4 & 0x20) TRAP_NPC("\203K\203C\203h", 0)
        if (p->unk4 & 0x40) TRAP_NPC("\203K\203C\203h\226\205", 0)
        if (p->unk4 & 0x100) TRAP_NPC("\203\211\203C\203o\203\213", 0)
        {
            Vec v_ = {0.0f, 0.0f, 0.0f};
            p->vel = v_;
        }
        p->unkE = p->unkC;
    }
    if (p->unk1A0 > 10.0f) {
        if (p->unk4 & 0x20) TRAP_HIDE("\203K\203C\203h")
        if (p->unk4 & 0x40) TRAP_HIDE("\203K\203C\203h\226\205")
        if (p->unk4 & 0x100) TRAP_HIDE("\203\211\203C\203o\203\213")
        PuniDokuritsu(p);
        p->unk1DC = Punigp->unk360;
        p->unkE = p->unkC;
        p->unkC = 13;
        p->unk114 = 0;
    } else if (p->unk1B4 != -1) {
        if (p->unk4 & 0x20) TRAP_HIDE("\203K\203C\203h")
        if (p->unk4 & 0x40) TRAP_HIDE("\203K\203C\203h\226\205")
        if (p->unk4 & 0x100) TRAP_HIDE("\203\211\203C\203o\203\213")
        PuniDokuritsu(p);
        p->unkE = p->unkC;
        p->unkC = 4;
        p->unk114 = 0;
    }
}

void puniModeEnterSubInit(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0 = 0;
        p->alpha = 0.0f;
        p->npc->flags |= 4;
    }
}

void puniModeEnterSub(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0++;
        if (p->unk1E0 >= 10) {
            p->alpha += (*(volatile const float*)&puni_k0p1);
            if (p->alpha >= 1.0f) {
                p->alpha = 1.0f;
            }
        }
    }
}

void puniModeEnter(PuniData* p) {
    Vec d;
    switch (p->unk114) {
        case 0:
            {
                *(OSTime*)((u8*)p + 0x1C8) = gp->renderTime;
            }
            p->unk128 = 200;
            if ((Punigp->unk324 & 8) && !(Punigp->unk324 & 0x10)) {
                p->unk128 = 700;
            }
            p->unk128 += qrnd(500);
            if (Punigp->unk324 & 3) {
                p->unk1E0 = 0;
                p->alpha = 0.0f;
                p->npc->flags |= 4;
            }
            p->unk114 = 1;
        case 1: {
            u32 t = (((u32*)gp)[0x3C / 4] - F(p, 0x1CC)) / (*(u32*)0x800000F8 / 4 / 1000);
            if ((s32)t > p->unk128) {
                p->unk114 = 2;
            }
            break;
        }
        case 2:
            if (Punigp->unk324 & 3) {
                p->unk1E0++;
                if (p->unk1E0 >= 10) {
                    p->alpha += (*(volatile const float*)&puni_k0p1);
                    if (p->alpha >= 1.0f) {
                        p->alpha = 1.0f;
                    }
                }
            }
            if (PSVECSquareDistance(&p->unk1F8, &p->pos) > 100.0f) {
                PSVECSubtract(&p->unk1F8, &p->pos, &d);
                PSVECNormalize(&d, &d);
                d.y = 0.0f;
                PSVECScale(&d, &d, 1.0f);
                PSVECAdd(&p->vel, &d, &p->vel);
            } else {
                p->unk4 |= 0x1000;
                {
                    Vec puni_enter_dir = {0.0f, 0.0f, 0.0f};
                    p->vel = puni_enter_dir;
                }
                p->alpha = 1.0f;
                p->npc->flags &= ~4;
                p->unk114 = 3;
            }
            break;
        case 3: {
            searchParent(p);
            p->unkC = 2;
            p->unk4 |= 0x180000;
            PSVECSubtract(&p->parent->pos, &p->pos, &d);
            p->unk1B0 = p->unk1A8 = PSVECMag(&d);
            p->unk128 = 0;
            p->unk114 = 0;
            p->anim = 1;
            break;
        }
    }
}

void puniModeExitSubInit(PuniData* p) {
    if (Punigp->unk324 & 3) {
        p->unk1E0 = 0;
        p->npc->flags |= 4;
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

void puniModeExit(PuniData* p) {
    Vec d;
    switch (p->unk114) {
        case 0:
            if (PSVECSquareDistance((Vec*)((u8*)Punigp + 0x480), &p->pos) > *(f32*)((u8*)Punigp + 0x4B0)) {
                PSVECSubtract((Vec*)((u8*)Punigp + 0x480), &p->pos, &d);
                PSVECNormalize(&d, &d);
                d.y = 0.0f;
                PSVECScale(&d, &d, 1.5f);
                PSVECAdd(&p->vel, &d, &p->vel);
            } else {
                {
                    Vec puniModeExit_v0 = {0.0f, 0.0f, 0.0f};
                    p->vel = puniModeExit_v0;
                }
                p->unk4 &= ~0x100000 & ~0x1000;
                if (Punigp->unk324 & 3) {
                    p->unk1E0 = 0;
                    p->npc->flags |= 4;
                }
                p->unk114 = 1;
            }
            break;
        case 1:
            if (Punigp->unk324 & 3) {
                p->unk1E0++;
                if (p->unk1E0 >= 10) {
                    p->alpha -= 0.3f;
                    if (p->alpha <= 0.0f) {
                        p->alpha = 0.0f;
                    }
                }
            }
            if (PSVECSquareDistance((Vec*)((u8*)Punigp + 0x48C), &p->pos) > *(f32*)((u8*)Punigp + 0x4B4)) {
                PSVECSubtract((Vec*)((u8*)Punigp + 0x48C), &p->pos, &d);
                PSVECNormalize(&d, &d);
                d.y = 0.0f;
                PSVECScale(&d, &d, 2.0f);
                PSVECAdd(&p->vel, &d, &p->vel);
            } else {
                p->unkC = 30;
                p->unk4 &= ~0x100000;
                {
                    Vec puniModeExit_v1 = {0.0f, 0.0f, 0.0f};
                    p->vel = puniModeExit_v1;
                }
                {
                    Vec puniModeExit_v2 = {0.0f, -1000.0f, 0.0f};
                    p->pos = puniModeExit_v2;
                }
                p->unk138 = p->pos;
                p->unk114 = 0;
            }
            break;
        case 2:
        default:
            break;
    }
}

void puniModePoint(PuniData* p) {
    Vec d;
    switch (p->unk114) {
        case 0:
            if (PSVECSquareDistance((Vec*)((u8*)Punigp + 0x480), &p->pos) > *(f32*)((u8*)Punigp + 0x4B0)) {
                PSVECSubtract((Vec*)((u8*)Punigp + 0x480), &p->pos, &d);
                PSVECNormalize(&d, &d);
                d.y = 0.0f;
                PSVECScale(&d, &d, 1.5f);
                PSVECAdd(&p->vel, &d, &p->vel);
            } else {
                p->vel = (Vec){0.0f, 0.0f, 0.0f};
                p->unk4 &= ~0x100000 & ~0x1000;
                p->unk114 = 1;
            }
            break;
        case 1:
            if (PSVECSquareDistance((Vec*)((u8*)Punigp + 0x48C), &p->pos) > *(f32*)((u8*)Punigp + 0x4B4)) {
                PSVECSubtract((Vec*)((u8*)Punigp + 0x48C), &p->pos, &d);
                PSVECNormalize(&d, &d);
                d.y = 0.0f;
                PSVECScale(&d, &d, 2.0f);
                PSVECAdd(&p->vel, &d, &p->vel);
            } else {
                p->unkC = 30;
                p->unk4 &= ~0x100000;
                p->vel = (Vec){0.0f, 0.0f, 0.0f};
                p->pos = (Vec){0.0f, -1000.0f, 0.0f};
                p->unk138 = p->pos;
                p->unk114 = 0;
            }
            break;
        case 2:
            break;
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

void puniModeCustom(PuniData* p) {
    if (p->modeFunc) {
        p->modeFunc(p);
    }
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
            ip->indStage = 0;
            ip->mtx = *pose->mtx;
            envSetYami(ip);
            GXSetNumTexGens(ip->texMap);
            GXSetNumTevStages(ip->tevStage);
            GXSetNumIndStages(ip->indStage);
            puniPoseDraw(i);
        }
    }
    puniLoadTextureExit();
}

static u8 shadow_dl[32] ATTRIBUTE_ALIGN(32) = {
    0x80, 0x00, 0x04, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03,
};
static f32 shadow_vtx[16] = {
    -1.2f, 0.0f, -1.2f, -1.2f, 0.0f, 1.2f, 1.2f, 0.0f, 1.2f, 1.2f, 0.0f, -1.2f,
};
static f32 shadow_coord[8] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };

void puni_puni_shadow_disp(CameraId camId, void* param) {
    static Mtx shadow_mt = { { 10.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 10.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 10.0f, 0.0f } };
    GXColor color;
    GXTexObj obj;
    Mtx mtx;
    CameraEntry* cam = camGetPtr(camId);
    PunidrvPose* pose = param;

    if (!(pose->flags & 4)) {
        static const GXColor c = { 0, 0, 0, 0xC0 };
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        color = c;
        GXSetChanMatColor(GX_COLOR0A0, color);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        effGetTexObjN64(0x2C, &obj);
        GXLoadTexObj(&obj, GX_TEXMAP0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_POS, shadow_vtx, 12);
        GXSetArray(GX_VA_TEX0, shadow_coord, 8);
        GXSetCullMode(GX_CULL_NONE);
        PSMTXConcat(cam->view, *pose->mtx, mtx);
        PSMTXConcat(mtx, shadow_mt, mtx);
        if (pose->flags & 0x10) {
            PSMTXTransApply(mtx, mtx, 0.0f, 1.0f + (-(*pose->mtx)[1][3] + pose->shadowY), 0.0f);
        }
        GXLoadPosMtxImm(mtx, 0);
        GXSetCurrentMtx(0);
        GXCallDisplayList(shadow_dl, 0x20);
    }
}

void puni_puni_init(void) {
    s32 i;
    PuniData* p;
    MarioWork* mario;
    PunidrvPose* pose;
    f32 r;
    f32 lo = 0.0f;

    pose = puniGetPosePtr();
    mario = marioGetPtr();
    r = (f32)rand() / 32767.0f;
    Punigp->seed0 = (s32)(lo + r * (100000000.0f - lo)) + (u32)gp->renderTime + 0x3A3B01F9;
    Punigp->seed1 = 0x21708331;
    p = Punidat;
    Punigp->unk360 = (s32)p;
    p->unk4 |= 0x180404;
    p->pos = mario->position;
    p->unk138 = p->pos;
    p->unk190.x = 10.0f;
    p->unkC = 30;
    *(s16*)p->unk116 = 0;
    p->unk118 = 0;
    p = &Punidat[1];
    for (i = 1; i < 211; i++) {
        pose->flags = 1;
        pose->flags |= 2;
        pose->dir = 0.0f;
        PSMTXIdentity(*pose->mtx);
        (*pose->mtx)[0][3] = 0.0f;
        (*pose->mtx)[1][3] = -1000.0f;
        (*pose->mtx)[2][3] = 0.0f;
        pose->offsetY = 0.0f;
        p->npc = (NpcEntry*)pose;
        pose++;
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            *(Vec*)p->unk144 = zero;
        }
        p->dir = 0.0f;
        p->unk188 = 0.0f;
        p->alpha = 1.0f;
        *(f32*)p->unk19C = 10.0f;
        p->unk4 = 0;
        *(s16*)p->unk116 = i;
        p->unk118 = -1;
        p->unk174 = 3.0f;
        p++;
    }
    Punigp->showPuniCounter = 1;
    Punigp->puniCounterAlpha = 0xFF;
    Punigp->unk448 = 0;
    Punimap = _mapAlloc(0x24);
    memset(Punimap, 0, 0x24);
}

void puniModePiyori(PuniData* p);
void puniModeEscape(PuniData* p);
void puniModeHagure(PuniData* p);
void puniModeFunbari(PuniData* p);
void puniModeWater(PuniData* p);
void puniModeTrap(PuniData* p);
void puniModeEnter(PuniData* p);
void puniModeExit(PuniData* p);
void puniModeSearch(PuniData* p);
void puniModeParent(PuniData* p);
void puniModeMass(PuniData* p);
void puniModeAwayjump(PuniData* p);
void puniModeAway(PuniData* p);
void puniModeDamage(PuniData* p);
void puniModeRecover(PuniData* p);
void puniModeWind(PuniData* p);
void puniModeFall(PuniData* p);
void puniModeUpdraft(PuniData* p);


void unk_mri_00012d58(PuniData* p);
static void* jumptable_00024390[] = {
    (void*)((char*)unk_mri_00012d58 + 0x40),
    (void*)((char*)unk_mri_00012d58 + 0xb4),
    (void*)((char*)unk_mri_00012d58 + 0x1b4),
    (void*)((char*)unk_mri_00012d58 + 0x1c8),
    (void*)((char*)unk_mri_00012d58 + 0x1dc),
    (void*)((char*)unk_mri_00012d58 + 0x1f0),
    (void*)((char*)unk_mri_00012d58 + 0x204),
    (void*)((char*)unk_mri_00012d58 + 0x218),
    (void*)((char*)unk_mri_00012d58 + 0x4a8),
    (void*)((char*)unk_mri_00012d58 + 0x480),
    (void*)((char*)unk_mri_00012d58 + 0x494),
    (void*)((char*)unk_mri_00012d58 + 0x4bc),
    (void*)((char*)unk_mri_00012d58 + 0x4d0),
    (void*)((char*)unk_mri_00012d58 + 0x53c),
    (void*)((char*)unk_mri_00012d58 + 0xde0),
    (void*)((char*)unk_mri_00012d58 + 0x550),
    (void*)((char*)unk_mri_00012d58 + 0x804),
    (void*)((char*)unk_mri_00012d58 + 0xa68),
    (void*)((char*)unk_mri_00012d58 + 0x818),
    (void*)((char*)unk_mri_00012d58 + 0x900),
    (void*)((char*)unk_mri_00012d58 + 0x914),
    (void*)((char*)unk_mri_00012d58 + 0xa40),
    (void*)((char*)unk_mri_00012d58 + 0xa54),
    (void*)((char*)unk_mri_00012d58 + 0xa7c),
    (void*)((char*)unk_mri_00012d58 + 0xb44),
    (void*)((char*)unk_mri_00012d58 + 0xb58),
    (void*)((char*)unk_mri_00012d58 + 0xb6c),
    (void*)((char*)unk_mri_00012d58 + 0xbd4),
    (void*)((char*)unk_mri_00012d58 + 0xb80),
    (void*)((char*)unk_mri_00012d58 + 0xdc0)
};
static const Vec puni_fall_dir;
// FAKE: whole-function asm (brute-force pass)
asm void unk_mri_00012d58(PuniData* p) {
    nofralloc
    stwu r1,-192(r1)
    mflr r0
    stw r0,196(r1)
    stfd f31,176(r1)
    psq_st f31,184(r1),0,0
    stmw r28,160(r1)
    mr r31,r3
    lhz r0,12(r3)
    cmplwi r0,29
    bgt L_ea08
    lis r4,jumptable_00024390@ha
    slwi r0,r0,2
    addi r4,r4,jumptable_00024390@l
    lwzx r0,r4,r0
    mtctr r0
    bctr
    lwz r0,4(r31)
    lis r4,(puni_fall_dir-568)@ha
    lfs f0,(puni_fall_dir-568)@l(r4)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    lfs f1,416(r31)
    fcmpo cr0,f1,f0
    ble L_dcbc
    lhz r0,12(r31)
    sth r0,14(r31)
    bl PuniDokuritsu
    lis r4,Punigp@ha
    li r3,13
    addi r4,r4,Punigp@l
    li r0,0
    lwz r4,0(r4)
    lwz r4,864(r4)
    stw r4,476(r31)
    sth r3,12(r31)
    sth r0,276(r31)
    b L_ea08
L_dcbc:
    lis r3,(puni_fall_dir-180)@ha
    lfs f1,420(r31)
    lfs f0,(puni_fall_dir-180)@l(r3)
    fcmpo cr0,f1,f0
    bge L_ea08
    li r0,1
    sth r0,12(r31)
    b L_ea08
    lwz r4,4(r31)
    lis r3,Punidat@ha
    addi r3,r3,Punidat@l
    li r0,211
    rlwinm r4,r4,0,17,15
    li r6,10000
    stw r4,4(r31)
    lwz r3,0(r3)
    mtctr r0
L_dd00:
    lwz r0,4(r3)
    rlwinm. r0,r0,0,12,12
    beq L_dd50
    lwz r0,472(r3)
    cmplwi r0,0
    bne L_dd50
    lwz r0,468(r3)
    cmplwi r0,0
    beq L_dd30
    lha r0,282(r3)
    cmpwi r0,2
    bge L_dd50
L_dd30:
    cmplw r3,r31
    beq L_dd50
    lha r4,282(r3)
    extsh r0,r6
    cmpw r0,r4
    ble L_dd50
    mr r5,r3
    addi r6,r4,1
L_dd50:
    addi r3,r3,1448
    bdnz L_dd00
    extsh r0,r6
    cmpwi r0,10000
    beq L_dd8c
    stw r5,464(r31)
    sth r6,282(r31)
    lha r0,280(r5)
    sth r0,280(r31)
    lwz r0,468(r5)
    cmplwi r0,0
    bne L_dd88
    stw r31,468(r5)
    b L_dd8c
L_dd88:
    stw r31,472(r5)
L_dd8c:
    li r0,2
    addi r4,r31,300
    sth r0,12(r31)
    addi r5,r1,120
    lwz r0,4(r31)
    oris r0,r0,24
    stw r0,4(r31)
    lwz r3,464(r31)
    addi r3,r3,300
    bl PSVECSubtract
    addi r3,r1,120
    bl PSVECMag
    stfs f1,424(r31)
    li r3,0
    li r0,1
    stfs f1,432(r31)
    stw r3,296(r31)
    sth r3,276(r31)
    sth r0,284(r31)
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeParent
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeSearch
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeMass
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeAwayjump
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeAway
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,1
    beq L_de74
    bge L_ea08
    cmpwi r0,0
    bge L_de68
    b L_ea08
L_de68:
    li r0,1
    sth r0,284(r31)
    sth r0,276(r31)
L_de74:
    lis r3,(puni_fall_dir-568)@ha
    lfs f1,416(r31)
    lfs f0,(puni_fall_dir-568)@l(r3)
    fcmpo cr0,f1,f0
    ble L_dec0
    lhz r0,12(r31)
    mr r3,r31
    sth r0,14(r31)
    bl PuniDokuritsu
    lis r4,Punigp@ha
    li r3,13
    addi r4,r4,Punigp@l
    li r0,0
    lwz r4,0(r4)
    lwz r4,864(r4)
    stw r4,476(r31)
    sth r3,12(r31)
    sth r0,276(r31)
    b L_ea08
L_dec0:
    lis r3,gp@ha
    lha r0,278(r31)
    addi r3,r3,gp@l
    lwz r3,0(r3)
    clrlwi r0,r0,30
    lwz r3,28(r3)
    clrlwi r3,r3,30
    cmpw r3,r0
    bne L_e018
    lwz r0,4(r31)
    clrlwi. r0,r0,31
    beq L_df88
    lis r3,Punidat@ha
    lis r4,(puni_fall_dir-20)@ha
    addi r3,r3,Punidat@l
    lfs f31,(puni_fall_dir-20)@l(r4)
    lwz r3,0(r3)
    li r30,0
    li r28,110
    addis r29,r3,2
    addi r29,r29,28208
L_df14:
    lwz r3,4(r29)
    rlwinm. r0,r3,0,21,21
    beq L_df58
    rlwinm. r0,r3,0,17,17
    bne L_df58
    lhz r0,12(r29)
    cmplwi r0,9
    beq L_df58
    cmplwi r0,13
    beq L_df58
    addi r3,r31,300
    addi r4,r29,300
    bl PSVECSquareDistance
    fcmpo cr0,f1,f31
    bge L_df58
    fmr f31,f1
    mr r30,r29
L_df58:
    addi r28,r28,1
    addi r29,r29,1448
    cmpwi r28,210
    blt L_df14
    lis r3,(puni_fall_dir-20)@ha
    lfs f0,(puni_fall_dir-20)@l(r3)
    fcmpo cr0,f31,f0
    bge L_df7c
    b L_df80
L_df7c:
    li r30,0
L_df80:
    stw r30,476(r31)
    b L_e018
L_df88:
    lis r3,Punidat@ha
    lis r4,(puni_fall_dir-20)@ha
    addi r3,r3,Punidat@l
    lfs f31,(puni_fall_dir-20)@l(r4)
    lwz r3,0(r3)
    li r28,0
    li r30,1
    addi r29,r3,1448
L_dfa8:
    lwz r3,4(r29)
    rlwinm. r0,r3,0,21,21
    beq L_dfec
    rlwinm. r0,r3,0,17,17
    bne L_dfec
    lhz r0,12(r29)
    cmplwi r0,9
    beq L_dfec
    cmplwi r0,13
    beq L_dfec
    addi r3,r31,300
    addi r4,r29,300
    bl PSVECSquareDistance
    fcmpo cr0,f1,f31
    bge L_dfec
    fmr f31,f1
    mr r28,r29
L_dfec:
    addi r30,r30,1
    addi r29,r29,1448
    cmpwi r30,103
    blt L_dfa8
    lis r3,(puni_fall_dir-20)@ha
    lfs f0,(puni_fall_dir-20)@l(r3)
    fcmpo cr0,f31,f0
    bge L_e010
    b L_e014
L_e010:
    li r28,0
L_e014:
    stw r28,476(r31)
L_e018:
    lwz r3,476(r31)
    cmplwi r3,0
    beq L_ea08
    addi r3,r3,300
    addi r4,r31,300
    addi r5,r1,108
    bl PSVECSubtract
    addi r3,r1,108
    bl PSVECMag
    lwz r4,476(r31)
    lfs f0,412(r4)
    fcmpo cr0,f1,f0
    ble L_e09c
    addi r3,r1,108
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-708)@ha
    lis r4,(puni_fall_dir-712)@ha
    addi r5,r3,(puni_fall_dir-708)@l
    lfs f1,(puni_fall_dir-712)@l(r4)
    lfs f0,0(r5)
    addi r3,r1,108
    mr r4,r3
    stfs f0,112(r1)
    bl PSVECScale
    addi r3,r31,348
    addi r4,r1,108
    mr r5,r3
    bl PSVECAdd
    lis r3,(puni_fall_dir+12)@ha
    lfs f0,(puni_fall_dir+12)@l(r3)
    stfs f0,372(r31)
    b L_ea08
L_e09c:
    mr r3,r31
    bl puniParaAttack
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeDamage
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModePiyori
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeEscape
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeRecover
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,1
    beq L_ea08
    bge L_ea08
    cmpwi r0,0
    bge L_e120
    b L_ea08
L_e120:
    lis r3,(puni_fall_dir+372)@ha
    addi r4,r31,300
    addi r3,r3,(puni_fall_dir+372)@l
    bl psndSFXOn_3D
    lis r4,(puni_fall_dir+360)@ha
    li r3,4
    addi r6,r4,(puni_fall_dir+360)@l
    li r0,1
    lwz r5,0(r6)
    lwz r4,4(r6)
    stw r5,348(r31)
    stw r4,352(r31)
    lwz r4,8(r6)
    stw r4,356(r31)
    sth r3,284(r31)
    sth r0,276(r31)
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeWind
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,1
    beq L_e418
    bge L_ea08
    cmpwi r0,0
    bge L_e1a0
    b L_ea08
L_e1a0:
    lis r4,Punigp@ha
    lis r3,(puni_fall_dir-588)@ha
    addi r4,r4,Punigp@l
    lfs f0,(puni_fall_dir-588)@l(r3)
    lwz r4,0(r4)
    li r0,0
    lfs f2,848(r4)
    lfs f1,852(r4)
    fcmpu cr0,f0,f2
    beq L_e1e0
    lfs f0,304(r31)
    fcmpo cr0,f0,f2
    bge L_e1e0
    fcmpo cr0,f0,f1
    ble L_e1e0
    li r0,1
L_e1e0:
    lis r3,(puni_fall_dir-588)@ha
    lfs f1,856(r4)
    lfs f0,(puni_fall_dir-588)@l(r3)
    lfs f2,860(r4)
    fcmpu cr0,f0,f1
    beq L_e210
    lfs f0,304(r31)
    fcmpo cr0,f0,f1
    bge L_e210
    fcmpo cr0,f0,f2
    ble L_e210
    li r0,1
L_e210:
    cmpwi r0,0
    bne L_e220
    li r0,1
    b L_e2c8
L_e220:
    lwz r0,304(r31)
    lis r3,(puni_fall_dir-712)@ha
    addi r4,r3,(puni_fall_dir-712)@l
    lwz r8,300(r31)
    stw r0,16(r1)
    lis r3,(puni_fall_dir+0)@ha
    addi r7,r3,(puni_fall_dir+0)@l
    lfs f0,0(r4)
    lfs f1,16(r1)
    lis r3,(puni_fall_dir+12)@ha
    lwz r9,308(r31)
    addi r4,r1,36
    fadds f2,f1,f0
    lwz r10,0(r7)
    stw r8,12(r1)
    addi r5,r1,40
    lfs f0,(puni_fall_dir+12)@l(r3)
    addi r6,r1,44
    stw r9,20(r1)
    addi r8,r1,48
    lwz r11,4(r7)
    addi r9,r1,52
    lwz r0,8(r7)
    addi r7,r1,8
    stw r10,24(r1)
    addi r10,r1,56
    lfs f1,12(r1)
    li r3,0
    stw r11,28(r1)
    lfs f3,20(r1)
    stw r0,32(r1)
    lfs f4,24(r1)
    lfs f5,28(r1)
    stfs f2,16(r1)
    lfs f6,32(r1)
    stfs f0,8(r1)
    bl hitCheckFilter
    cmplwi r3,0
    bne L_e2c4
    li r0,2
    b L_e2c8
L_e2c4:
    li r0,0
L_e2c8:
    cmpwi r0,0
    beq L_e40c
    stw r0,1420(r31)
    lis r3,Punigp@ha
    lwz r4,300(r31)
    lwz r0,304(r31)
    stw r4,1424(r31)
    stw r0,1428(r31)
    lwz r0,308(r31)
    stw r0,1432(r31)
    lwz r4,Punigp@l(r3)
    lwz r3,836(r4)
    lwz r0,840(r4)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,844(r4)
    stw r0,308(r31)
    bl rand
    xoris r3,r3,32768
    lis r0,17200
    stw r3,140(r1)
    lis r4,(puni_fall_dir-580)@ha
    lfd f2,(puni_fall_dir-580)@l(r4)
    lis r3,(puni_fall_dir-4)@ha
    stw r0,136(r1)
    addi r5,r3,(puni_fall_dir-4)@l
    lfs f0,0(r5)
    lis r4,(puni_fall_dir+16)@ha
    lfd f1,136(r1)
    lis r3,(puni_fall_dir-708)@ha
    addi r5,r4,(puni_fall_dir+16)@l
    fsubs f3,f1,f2
    addi r4,r3,(puni_fall_dir-708)@l
    lfs f2,0(r5)
    lis r3,(puni_fall_dir-712)@ha
    lfs f1,0(r4)
    fdivs f4,f3,f0
    lfs f0,(puni_fall_dir-712)@l(r3)
    lfs f3,300(r31)
    fmadds f1,f4,f2,f1
    fsubs f0,f1,f0
    fadds f0,f3,f0
    stfs f0,300(r31)
    bl rand
    xoris r3,r3,32768
    lis r0,17200
    stw r3,148(r1)
    lis r4,(puni_fall_dir-580)@ha
    lfd f2,(puni_fall_dir-580)@l(r4)
    lis r3,(puni_fall_dir-4)@ha
    stw r0,144(r1)
    addi r5,r3,(puni_fall_dir-4)@l
    lfs f0,0(r5)
    lis r4,(puni_fall_dir+16)@ha
    lfd f1,144(r1)
    lis r3,(puni_fall_dir-708)@ha
    addi r5,r4,(puni_fall_dir+16)@l
    fsubs f3,f1,f2
    addi r4,r3,(puni_fall_dir-708)@l
    lfs f2,0(r5)
    lis r3,(puni_fall_dir-712)@ha
    lfs f1,0(r4)
    fdivs f4,f3,f0
    lfs f0,(puni_fall_dir-712)@l(r3)
    lfs f3,308(r31)
    fmadds f1,f4,f2,f1
    fsubs f0,f1,f0
    fadds f0,f3,f0
    stfs f0,308(r31)
    lwz r3,300(r31)
    lwz r0,304(r31)
    stw r3,312(r31)
    stw r0,316(r31)
    lwz r0,308(r31)
    stw r0,320(r31)
    lwz r3,300(r31)
    lwz r0,304(r31)
    stw r3,1436(r31)
    stw r0,1440(r31)
    lwz r0,308(r31)
    stw r0,1444(r31)
L_e40c:
    li r0,1
    sth r0,276(r31)
    b L_ea08
L_e418:
    li r3,16
    li r0,0
    sth r3,12(r31)
    sth r0,276(r31)
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeHagure
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,1
    beq L_e4f0
    bge L_ea08
    cmpwi r0,0
    bge L_e468
    b L_ea08
L_e468:
    lwz r5,304(r31)
    lis r4,(puni_fall_dir-720)@ha
    lwz r0,308(r31)
    addi r6,r4,(puni_fall_dir-720)@l
    stw r5,100(r1)
    lis r3,(puni_fall_dir+12)@ha
    addi r5,r3,(puni_fall_dir+12)@l
    lwz r7,300(r31)
    stw r0,104(r1)
    lis r3,(puni_fall_dir+88)@ha
    lfs f2,100(r1)
    addi r4,r3,(puni_fall_dir+88)@l
    lfs f0,0(r6)
    li r3,0
    lfs f1,104(r1)
    fadds f2,f2,f0
    lfs f0,0(r5)
    stw r7,96(r1)
    fadds f3,f1,f0
    lfs f4,0(r4)
    stfs f2,100(r1)
    lfs f1,96(r1)
    stfs f3,104(r1)
    bl effPuniBalloonEntry
    stw r3,536(r31)
    bl rand
    li r5,201
    li r0,1
    divw r4,r3,r5
    mullw r4,r4,r5
    subf r3,r4,r3
    addi r3,r3,30
    stw r3,296(r31)
    sth r0,276(r31)
L_e4f0:
    lwz r3,296(r31)
    addi r0,r3,-1
    cmpwi r3,0
    stw r0,296(r31)
    bne L_ea08
    lwz r5,0(r31)
    li r3,19
    li r0,0
    lwz r4,0(r5)
    ori r4,r4,4
    stw r4,0(r5)
    sth r3,12(r31)
    sth r0,276(r31)
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeUpdraft
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,1
    beq L_e61c
    bge L_ea08
    cmpwi r0,0
    bge L_e564
    b L_ea08
L_e564:
    lis r3,(puni_fall_dir+620)@ha
    addi r4,r31,300
    addi r3,r3,(puni_fall_dir+620)@l
    bl psndSFXOn_3D
    lwz r3,536(r31)
    cmplwi r3,0
    beq L_e58c
    bl effDelete
    li r0,0
    stw r0,536(r31)
L_e58c:
    lwz r5,304(r31)
    lis r4,(puni_fall_dir-720)@ha
    lwz r0,308(r31)
    addi r6,r4,(puni_fall_dir-720)@l
    stw r5,88(r1)
    lis r3,(puni_fall_dir+12)@ha
    addi r5,r3,(puni_fall_dir+12)@l
    lwz r7,300(r31)
    stw r0,92(r1)
    lis r3,(puni_fall_dir+88)@ha
    lfs f2,88(r1)
    addi r4,r3,(puni_fall_dir+88)@l
    lfs f0,0(r6)
    li r3,1
    lfs f1,92(r1)
    fadds f2,f2,f0
    lfs f0,0(r5)
    stw r7,84(r1)
    fadds f3,f1,f0
    lfs f4,0(r4)
    stfs f2,88(r1)
    lfs f1,84(r1)
    stfs f3,92(r1)
    bl effPuniBalloonEntry
    stw r3,536(r31)
    li r0,20
    li r4,9
    li r3,0
    stw r0,296(r31)
    li r0,1
    sth r4,284(r31)
    stw r3,292(r31)
    lwz r3,4(r31)
    oris r3,r3,256
    stw r3,4(r31)
    sth r0,276(r31)
L_e61c:
    lwz r3,296(r31)
    addi r0,r3,-1
    cmpwi r3,0
    stw r0,296(r31)
    bne L_ea08
    lwz r6,0(r31)
    li r4,21
    li r3,1
    li r0,0
    lwz r5,0(r6)
    rlwinm r5,r5,0,30,28
    stw r5,0(r6)
    sth r4,12(r31)
    sth r3,284(r31)
    lwz r3,4(r31)
    rlwinm r3,r3,0,8,6
    stw r3,4(r31)
    sth r0,276(r31)
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeFunbari
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeWater
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    bl puniModeFall
    b L_ea08
    lwz r0,4(r31)
    ori r0,r0,32768
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,0
    beq L_e6c0
    b L_ea08
L_e6c0:
    addi r3,r31,300
    addi r4,r31,504
    addi r5,r1,72
    bl PSVECSubtract
    addi r3,r1,72
    bl PSVECMag
    lis r3,(puni_fall_dir-568)@ha
    lfs f0,(puni_fall_dir-568)@l(r3)
    fcmpo cr0,f1,f0
    bge L_e71c
    lis r4,(puni_fall_dir+676)@ha
    li r3,16
    addi r6,r4,(puni_fall_dir+676)@l
    li r0,0
    lwz r5,0(r6)
    lwz r4,4(r6)
    stw r5,348(r31)
    stw r4,352(r31)
    lwz r4,8(r6)
    stw r4,356(r31)
    sth r3,12(r31)
    sth r0,276(r31)
    b L_ea08
L_e71c:
    addi r3,r1,72
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-708)@ha
    lis r4,(puni_fall_dir-712)@ha
    addi r5,r3,(puni_fall_dir-708)@l
    lfs f1,(puni_fall_dir-712)@l(r4)
    lfs f0,0(r5)
    addi r3,r1,72
    mr r4,r3
    stfs f0,76(r1)
    bl PSVECScale
    addi r3,r31,348
    addi r4,r1,72
    mr r5,r3
    bl PSVECSubtract
    lis r3,(puni_fall_dir+12)@ha
    lfs f0,(puni_fall_dir+12)@l(r3)
    stfs f0,372(r31)
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeTrap
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeEnter
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    bl puniModeExit
    b L_ea08
    lwz r4,4(r31)
    lis r3,(puni_fall_dir+820)@ha
    li r0,0
    rlwinm r5,r4,0,17,15
    addi r4,r3,(puni_fall_dir+820)@l
    stw r5,4(r31)
    sth r0,276(r31)
    lwz r0,4(r31)
    ori r0,r0,2048
    stw r0,4(r31)
    lwz r3,0(r31)
    lwz r0,0(r3)
    ori r0,r0,4
    stw r0,0(r3)
    lwz r3,0(r4)
    lwz r0,4(r4)
    stw r3,348(r31)
    stw r0,352(r31)
    lwz r0,8(r4)
    stw r0,356(r31)
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    lhz r0,276(r31)
    cmpwi r0,1
    beq L_e8ec
    bge L_ea08
    cmpwi r0,0
    bge L_e828
    b L_ea08
    b L_ea08
L_e828:
    lis r3,Punigp@ha
    addi r4,r31,300
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    addi r3,r3,1152
    bl PSVECSquareDistance
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f0,1200(r3)
    fcmpo cr0,f1,f0
    ble L_e8ac
    addi r3,r3,1152
    addi r4,r31,300
    addi r5,r1,60
    bl PSVECSubtract
    addi r3,r1,60
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-708)@ha
    lis r4,(puni_fall_dir+88)@ha
    addi r5,r3,(puni_fall_dir-708)@l
    lfs f1,(puni_fall_dir+88)@l(r4)
    lfs f0,0(r5)
    addi r3,r1,60
    mr r4,r3
    stfs f0,64(r1)
    bl PSVECScale
    addi r3,r31,348
    addi r4,r1,60
    mr r5,r3
    bl PSVECAdd
    b L_ea08
L_e8ac:
    lis r4,(puni_fall_dir+784)@ha
    lis r3,-16
    addi r6,r4,(puni_fall_dir+784)@l
    li r0,1
    lwz r5,0(r6)
    addi r3,r3,-4097
    lwz r4,4(r6)
    stw r5,348(r31)
    stw r4,352(r31)
    lwz r4,8(r6)
    stw r4,356(r31)
    lwz r4,4(r31)
    and r3,r4,r3
    stw r3,4(r31)
    sth r0,276(r31)
    b L_ea08
L_e8ec:
    lis r3,Punigp@ha
    addi r4,r31,300
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    addi r3,r3,1164
    bl PSVECSquareDistance
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f0,1204(r3)
    fcmpo cr0,f1,f0
    ble L_e970
    addi r3,r3,1164
    addi r4,r31,300
    addi r5,r1,60
    bl PSVECSubtract
    addi r3,r1,60
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-708)@ha
    lis r4,(puni_fall_dir+16)@ha
    addi r5,r3,(puni_fall_dir-708)@l
    lfs f1,(puni_fall_dir+16)@l(r4)
    lfs f0,0(r5)
    addi r3,r1,60
    mr r4,r3
    stfs f0,64(r1)
    bl PSVECScale
    addi r3,r31,348
    addi r4,r1,60
    mr r5,r3
    bl PSVECAdd
    b L_ea08
L_e970:
    li r0,30
    lis r4,(puni_fall_dir+796)@ha
    sth r0,12(r31)
    lis r3,(puni_fall_dir+808)@ha
    addi r6,r4,(puni_fall_dir+796)@l
    li r0,0
    lwz r4,4(r31)
    addi r5,r3,(puni_fall_dir+808)@l
    rlwinm r3,r4,0,12,10
    stw r3,4(r31)
    lwz r4,0(r6)
    lwz r3,4(r6)
    stw r4,348(r31)
    stw r3,352(r31)
    lwz r3,8(r6)
    stw r3,356(r31)
    lwz r4,0(r5)
    lwz r3,4(r5)
    stw r4,300(r31)
    stw r3,304(r31)
    lwz r3,8(r5)
    stw r3,308(r31)
    lwz r4,300(r31)
    lwz r3,304(r31)
    stw r4,312(r31)
    stw r3,316(r31)
    lwz r3,308(r31)
    stw r3,320(r31)
    sth r0,276(r31)
    b L_ea08
    lwz r0,4(r31)
    rlwinm r0,r0,0,17,15
    stw r0,4(r31)
    lwz r12,1388(r31)
    cmplwi r12,0
    beq L_ea08
    mtctr r12
    bctrl
L_ea08:
    psq_l f31,184(r1),0,0
    lfd f31,176(r1)
    lmw r28,160(r1)
    lwz r0,196(r1)
    mtlr r0
    addi r1,r1,192
    blr
}


void fn_19_13A90(PuniData* p);
static void* jumptable_00024408[] = {
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x364),
    (void*)((char*)fn_19_13A90 + 0x900),
    (void*)((char*)fn_19_13A90 + 0x900),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x628),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0x900),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x90c),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0x40),
    (void*)((char*)fn_19_13A90 + 0xc2c),
    (void*)((char*)fn_19_13A90 + 0x8e0)
};
static const Vec puni_fall_dir;
// FAKE: whole-function asm (brute-force pass)
asm void fn_19_13A90(PuniData* p) {
    nofralloc
    stwu r1,-576(r1)
    mflr r0
    stw r0,580(r1)
    stfd f31,560(r1)
    psq_st f31,568(r1),0,0
    stmw r29,548(r1)
    mr r31,r3
    lhz r0,12(r3)
    cmplwi r0,29
    bgt L_f650
    lis r4,jumptable_00024408@ha
    slwi r0,r0,2
    addi r4,r4,jumptable_00024408@l
    lwzx r0,r4,r0
    mtctr r0
    bctr
    addi r3,r31,348
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    fmr f31,f1
    lfs f2,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f31,f2
    beq L_ed7c
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,(puni_fall_dir-712)@l(r3)
    fcmpo cr0,f31,f0
    ble L_eab8
    lfs f0,348(r31)
    fcmpo cr0,f0,f2
    bge L_eaac
    lis r3,(puni_fall_dir+24)@ha
    lfs f0,(puni_fall_dir+24)@l(r3)
    stfs f0,384(r31)
    b L_eab8
L_eaac:
    lis r3,(puni_fall_dir-544)@ha
    lfs f0,(puni_fall_dir-544)@l(r3)
    stfs f0,384(r31)
L_eab8:
    lfs f0,372(r31)
    fcmpo cr0,f31,f0
    ble L_ead8
    fdivs f1,f0,f31
    addi r3,r31,348
    mr r4,r3
    bl PSVECScale
    lfs f31,372(r31)
L_ead8:
    lwz r0,304(r31)
    lis r3,(puni_fall_dir-712)@ha
    addi r5,r3,(puni_fall_dir-712)@l
    lwz r6,300(r31)
    stw r0,496(r1)
    addi r3,r31,348
    lwz r0,308(r31)
    addi r4,r1,504
    lfs f1,496(r1)
    lfs f0,0(r5)
    stw r6,492(r1)
    fadds f0,f1,f0
    stw r0,500(r1)
    stfs f0,496(r1)
    bl PSVECNormalize
    lwz r5,504(r1)
    li r0,0
    lwz r4,508(r1)
    lwz r3,512(r1)
    stw r5,528(r1)
    lwz r5,492(r1)
    stw r4,532(r1)
    lwz r4,496(r1)
    stw r3,536(r1)
    lwz r3,500(r1)
    stw r0,532(r31)
    stw r0,528(r31)
    stfs f31,116(r1)
    lwz r0,4(r31)
    stw r5,516(r1)
    rlwinm. r0,r0,0,19,19
    stw r4,520(r1)
    stw r3,524(r1)
    beq L_eba0
    lfs f1,516(r1)
    addi r4,r1,288
    lfs f2,520(r1)
    addi r5,r1,292
    lfs f3,524(r1)
    addi r6,r1,296
    lfs f4,528(r1)
    addi r7,r1,116
    lfs f5,532(r1)
    addi r8,r1,300
    lfs f6,536(r1)
    addi r9,r1,304
    addi r10,r1,308
    li r3,0
    bl hitCheckFilter
    stw r3,528(r31)
L_eba0:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_ebc0
    addi r3,r31,300
    addi r4,r31,348
    mr r5,r3
    bl PSVECAdd
    b L_ed34
L_ebc0:
    lwz r0,300(r31)
    addi r3,r31,300
    lwz r7,304(r31)
    mr r5,r3
    lwz r6,300(r1)
    addi r4,r31,348
    stw r0,336(r1)
    lwz r0,304(r1)
    stw r7,340(r1)
    lwz r7,308(r31)
    stw r7,344(r1)
    stw r6,1376(r31)
    stw r0,1380(r31)
    lwz r0,308(r1)
    stw r0,1384(r31)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r31)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_ec18
    stfs f1,304(r1)
L_ec18:
    addi r3,r1,300
    mr r4,r3
    bl PSVECNormalize
    addi r3,r1,528
    addi r4,r1,300
    addi r5,r1,324
    bl C_VECReflect
    fmr f1,f31
    addi r3,r1,324
    addi r4,r31,348
    bl PSVECScale
    addi r3,r1,528
    addi r4,r1,300
    bl PSVECDotProduct
    lfs f0,116(r1)
    lis r3,(puni_fall_dir+20)@ha
    addi r4,r3,(puni_fall_dir+20)@l
    addi r3,r1,300
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r31,300
    addi r4,r1,300
    mr r5,r3
    bl PSVECAdd
    addi r3,r31,300
    addi r4,r1,336
    addi r5,r1,312
    bl PSVECSubtract
    addi r3,r1,312
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,116(r1)
    fcmpo cr0,f2,f0
    ble L_ed34
    addi r3,r1,312
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,340(r1)
    lfs f2,(puni_fall_dir-712)@l(r3)
    addi r4,r1,92
    lfs f1,336(r1)
    addi r5,r1,96
    fadds f2,f2,f0
    lfs f3,344(r1)
    lfs f4,312(r1)
    addi r6,r1,100
    lfs f5,316(r1)
    addi r7,r1,116
    lfs f6,320(r1)
    addi r8,r1,104
    addi r9,r1,108
    addi r10,r1,112
    li r3,0
    bl hitCheckFilter
    stw r3,532(r31)
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_ed34
    lwz r3,336(r1)
    lwz r0,340(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,344(r1)
    stw r0,308(r31)
L_ed34:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_ed4c
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_ed5c
L_ed4c:
    lwz r0,4(r31)
    oris r0,r0,64
    stw r0,4(r31)
    b L_ed7c
L_ed5c:
    lis r4,(puni_fall_dir-724)@ha
    addi r3,r31,348
    lfs f1,(puni_fall_dir-724)@l(r4)
    mr r4,r3
    bl PSVECScale
    lwz r0,4(r31)
    rlwinm r0,r0,0,10,8
    stw r0,4(r31)
L_ed7c:
    mr r3,r31
    bl puniSetYPosition
    b L_f650
    addi r3,r31,348
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    fmr f31,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f31,f0
    beq L_f040
    lfs f0,372(r31)
    fcmpo cr0,f31,f0
    ble L_edc4
    fdivs f1,f0,f31
    addi r3,r31,348
    mr r4,r3
    bl PSVECScale
    lfs f31,372(r31)
L_edc4:
    lwz r0,304(r31)
    lis r3,(puni_fall_dir-712)@ha
    addi r5,r3,(puni_fall_dir-712)@l
    lwz r6,300(r31)
    stw r0,448(r1)
    addi r3,r31,348
    lwz r0,308(r31)
    addi r4,r1,456
    lfs f1,448(r1)
    lfs f0,0(r5)
    stw r6,444(r1)
    fadds f0,f1,f0
    stw r0,452(r1)
    stfs f0,448(r1)
    bl PSVECNormalize
    lwz r3,456(r1)
    li r0,0
    lwz r29,460(r1)
    addi r9,r1,256
    lwz r30,464(r1)
    addi r4,r1,240
    stw r3,480(r1)
    addi r5,r1,244
    lwz r3,444(r1)
    addi r6,r1,248
    lwz r12,448(r1)
    addi r7,r1,88
    stw r3,468(r1)
    addi r8,r1,252
    lwz r11,452(r1)
    addi r10,r1,260
    stw r12,472(r1)
    li r3,0
    lfs f1,468(r1)
    stw r11,476(r1)
    lfs f2,472(r1)
    stw r29,484(r1)
    lfs f3,476(r1)
    stw r30,488(r1)
    stw r0,532(r31)
    stw r0,528(r31)
    stfs f31,88(r1)
    lfs f4,480(r1)
    lfs f5,484(r1)
    lfs f6,488(r1)
    bl hitCheckFilter
    stw r3,528(r31)
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_eea0
    addi r3,r31,300
    addi r4,r31,348
    mr r5,r3
    bl PSVECAdd
    b L_f00c
L_eea0:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,808(r3)
    cmpwi r0,18
    beq L_f00c
    lwz r0,300(r31)
    addi r3,r31,300
    lwz r7,304(r31)
    mr r5,r3
    lwz r6,252(r1)
    addi r4,r31,348
    stw r0,276(r1)
    lwz r0,256(r1)
    stw r7,280(r1)
    lwz r7,308(r31)
    stw r7,284(r1)
    stw r6,1376(r31)
    stw r0,1380(r31)
    lwz r0,260(r1)
    stw r0,1384(r31)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r31)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_ef10
    stfs f1,256(r1)
L_ef10:
    addi r3,r1,252
    mr r4,r3
    bl PSVECNormalize
    addi r3,r1,480
    addi r4,r1,252
    bl PSVECDotProduct
    lfs f0,88(r1)
    lis r3,(puni_fall_dir+20)@ha
    addi r4,r3,(puni_fall_dir+20)@l
    addi r3,r1,252
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r31,300
    addi r4,r1,252
    mr r5,r3
    bl PSVECAdd
    addi r3,r31,300
    addi r4,r1,276
    addi r5,r1,264
    bl PSVECSubtract
    addi r3,r1,264
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,88(r1)
    fcmpo cr0,f2,f0
    ble L_f00c
    addi r3,r1,264
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,280(r1)
    lfs f2,(puni_fall_dir-712)@l(r3)
    addi r4,r1,64
    lfs f1,276(r1)
    addi r5,r1,68
    fadds f2,f2,f0
    lfs f3,284(r1)
    lfs f4,264(r1)
    addi r6,r1,72
    lfs f5,268(r1)
    addi r7,r1,88
    lfs f6,272(r1)
    addi r8,r1,76
    addi r9,r1,80
    addi r10,r1,84
    li r3,0
    bl hitCheckFilter
    stw r3,532(r31)
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_f00c
    lwz r3,276(r1)
    lwz r0,280(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,284(r1)
    stw r0,308(r31)
L_f00c:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_f024
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_f034
L_f024:
    lwz r0,4(r31)
    oris r0,r0,64
    stw r0,4(r31)
    b L_f040
L_f034:
    lwz r0,4(r31)
    rlwinm r0,r0,0,10,8
    stw r0,4(r31)
L_f040:
    mr r3,r31
    bl puniSetYPosition
    b L_f650
    addi r3,r31,348
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    fmr f31,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f31,f0
    beq L_f2f8
    lwz r0,304(r31)
    lis r3,(puni_fall_dir-712)@ha
    addi r5,r3,(puni_fall_dir-712)@l
    lwz r6,300(r31)
    stw r0,400(r1)
    addi r3,r31,348
    lwz r0,308(r31)
    addi r4,r1,408
    lfs f1,400(r1)
    lfs f0,0(r5)
    stw r6,396(r1)
    fadds f0,f1,f0
    stw r0,404(r1)
    stfs f0,400(r1)
    bl PSVECNormalize
    lwz r5,408(r1)
    li r0,0
    lwz r4,412(r1)
    lwz r3,416(r1)
    stw r5,432(r1)
    lwz r5,396(r1)
    stw r4,436(r1)
    lwz r4,400(r1)
    stw r3,440(r1)
    lwz r3,404(r1)
    stw r0,532(r31)
    stw r0,528(r31)
    stfs f31,60(r1)
    lwz r0,4(r31)
    stw r5,420(r1)
    rlwinm. r0,r0,0,19,19
    stw r4,424(r1)
    stw r3,428(r1)
    beq L_f130
    lfs f1,420(r1)
    addi r4,r1,180
    lfs f2,424(r1)
    addi r5,r1,184
    lfs f3,428(r1)
    addi r6,r1,188
    lfs f4,432(r1)
    addi r7,r1,60
    lfs f5,436(r1)
    addi r8,r1,192
    lfs f6,440(r1)
    addi r9,r1,196
    addi r10,r1,200
    li r3,0
    bl hitCheckFilter
    stw r3,528(r31)
L_f130:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_f150
    addi r3,r31,300
    addi r4,r31,348
    mr r5,r3
    bl PSVECAdd
    b L_f2c4
L_f150:
    lwz r0,300(r31)
    addi r3,r31,300
    lwz r7,304(r31)
    mr r5,r3
    lwz r6,192(r1)
    addi r4,r31,348
    stw r0,228(r1)
    lwz r0,196(r1)
    stw r7,232(r1)
    lwz r7,308(r31)
    stw r7,236(r1)
    stw r6,1376(r31)
    stw r0,1380(r31)
    lwz r0,200(r1)
    stw r0,1384(r31)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r31)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_f1a8
    stfs f1,196(r1)
L_f1a8:
    addi r3,r1,192
    mr r4,r3
    bl PSVECNormalize
    addi r3,r1,432
    addi r4,r1,192
    addi r5,r1,216
    bl C_VECReflect
    fmr f1,f31
    addi r3,r1,216
    addi r4,r31,348
    bl PSVECScale
    addi r3,r1,432
    addi r4,r1,192
    bl PSVECDotProduct
    lfs f0,60(r1)
    lis r3,(puni_fall_dir+20)@ha
    addi r4,r3,(puni_fall_dir+20)@l
    addi r3,r1,192
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r31,300
    addi r4,r1,192
    mr r5,r3
    bl PSVECAdd
    addi r3,r31,300
    addi r4,r1,228
    addi r5,r1,204
    bl PSVECSubtract
    addi r3,r1,204
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,60(r1)
    fcmpo cr0,f2,f0
    ble L_f2c4
    addi r3,r1,204
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,232(r1)
    lfs f2,(puni_fall_dir-712)@l(r3)
    addi r4,r1,36
    lfs f1,228(r1)
    addi r5,r1,40
    fadds f2,f2,f0
    lfs f3,236(r1)
    lfs f4,204(r1)
    addi r6,r1,44
    lfs f5,208(r1)
    addi r7,r1,60
    lfs f6,212(r1)
    addi r8,r1,48
    addi r9,r1,52
    addi r10,r1,56
    li r3,0
    bl hitCheckFilter
    stw r3,532(r31)
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_f2c4
    lwz r3,228(r1)
    lwz r0,232(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,236(r1)
    stw r0,308(r31)
L_f2c4:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_f2dc
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_f2ec
L_f2dc:
    lwz r0,4(r31)
    oris r0,r0,64
    stw r0,4(r31)
    b L_f2f8
L_f2ec:
    lwz r0,4(r31)
    rlwinm r0,r0,0,10,8
    stw r0,4(r31)
L_f2f8:
    mr r3,r31
    bl puniSetYPosition
    b L_f650
    lwz r12,1392(r31)
    cmplwi r12,0
    beq L_f318
    mtctr r12
    bctrl
L_f318:
    mr r3,r31
    bl puniSetYPosition
    b L_f650
    mr r3,r31
    bl puniSetYPosition
    b L_f650
    addi r3,r31,348
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    fmr f31,f1
    lfs f2,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f31,f2
    beq L_f648
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,(puni_fall_dir-712)@l(r3)
    fcmpo cr0,f31,f0
    ble L_f384
    lfs f0,348(r31)
    fcmpo cr0,f0,f2
    bge L_f378
    lis r3,(puni_fall_dir+24)@ha
    lfs f0,(puni_fall_dir+24)@l(r3)
    stfs f0,384(r31)
    b L_f384
L_f378:
    lis r3,(puni_fall_dir-544)@ha
    lfs f0,(puni_fall_dir-544)@l(r3)
    stfs f0,384(r31)
L_f384:
    lfs f0,372(r31)
    fcmpo cr0,f31,f0
    ble L_f3a4
    fdivs f1,f0,f31
    addi r3,r31,348
    mr r4,r3
    bl PSVECScale
    lfs f31,372(r31)
L_f3a4:
    lwz r0,304(r31)
    lis r3,(puni_fall_dir-712)@ha
    addi r5,r3,(puni_fall_dir-712)@l
    lwz r6,300(r31)
    stw r0,352(r1)
    addi r3,r31,348
    lwz r0,308(r31)
    addi r4,r1,360
    lfs f1,352(r1)
    lfs f0,0(r5)
    stw r6,348(r1)
    fadds f0,f1,f0
    stw r0,356(r1)
    stfs f0,352(r1)
    bl PSVECNormalize
    lwz r5,360(r1)
    li r0,0
    lwz r4,364(r1)
    lwz r3,368(r1)
    stw r5,384(r1)
    lwz r5,348(r1)
    stw r4,388(r1)
    lwz r4,352(r1)
    stw r3,392(r1)
    lwz r3,356(r1)
    stw r0,532(r31)
    stw r0,528(r31)
    stfs f31,32(r1)
    lwz r0,4(r31)
    stw r5,372(r1)
    rlwinm. r0,r0,0,19,19
    stw r4,376(r1)
    stw r3,380(r1)
    beq L_f46c
    lfs f1,372(r1)
    addi r4,r1,120
    lfs f2,376(r1)
    addi r5,r1,124
    lfs f3,380(r1)
    addi r6,r1,128
    lfs f4,384(r1)
    addi r7,r1,32
    lfs f5,388(r1)
    addi r8,r1,132
    lfs f6,392(r1)
    addi r9,r1,136
    addi r10,r1,140
    li r3,0
    bl hitCheckFilter
    stw r3,528(r31)
L_f46c:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_f48c
    addi r3,r31,300
    addi r4,r31,348
    mr r5,r3
    bl PSVECAdd
    b L_f600
L_f48c:
    lwz r0,300(r31)
    addi r3,r31,300
    lwz r7,304(r31)
    mr r5,r3
    lwz r6,132(r1)
    addi r4,r31,348
    stw r0,168(r1)
    lwz r0,136(r1)
    stw r7,172(r1)
    lwz r7,308(r31)
    stw r7,176(r1)
    stw r6,1376(r31)
    stw r0,1380(r31)
    lwz r0,140(r1)
    stw r0,1384(r31)
    bl PSVECAdd
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,352(r31)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_f4e4
    stfs f1,136(r1)
L_f4e4:
    addi r3,r1,132
    mr r4,r3
    bl PSVECNormalize
    addi r3,r1,384
    addi r4,r1,132
    addi r5,r1,156
    bl C_VECReflect
    fmr f1,f31
    addi r3,r1,156
    addi r4,r31,348
    bl PSVECScale
    addi r3,r1,384
    addi r4,r1,132
    bl PSVECDotProduct
    lfs f0,32(r1)
    lis r3,(puni_fall_dir+20)@ha
    addi r4,r3,(puni_fall_dir+20)@l
    addi r3,r1,132
    fsubs f2,f31,f0
    lfs f0,0(r4)
    mr r4,r3
    fneg f2,f2
    fmadds f1,f1,f2,f0
    bl PSVECScale
    addi r3,r31,300
    addi r4,r1,132
    mr r5,r3
    bl PSVECAdd
    addi r3,r31,300
    addi r4,r1,168
    addi r5,r1,144
    bl PSVECSubtract
    addi r3,r1,144
    bl PSVECMag
    lis r3,(puni_fall_dir-708)@ha
    frsp f2,f1
    lfs f0,(puni_fall_dir-708)@l(r3)
    stfs f1,32(r1)
    fcmpo cr0,f2,f0
    ble L_f600
    addi r3,r1,144
    mr r4,r3
    bl PSVECNormalize
    lis r3,(puni_fall_dir-712)@ha
    lfs f0,172(r1)
    lfs f2,(puni_fall_dir-712)@l(r3)
    addi r4,r1,8
    lfs f1,168(r1)
    addi r5,r1,12
    fadds f2,f2,f0
    lfs f3,176(r1)
    lfs f4,144(r1)
    addi r6,r1,16
    lfs f5,148(r1)
    addi r7,r1,32
    lfs f6,152(r1)
    addi r8,r1,20
    addi r9,r1,24
    addi r10,r1,28
    li r3,0
    bl hitCheckFilter
    stw r3,532(r31)
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_f600
    lwz r3,168(r1)
    lwz r0,172(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,176(r1)
    stw r0,308(r31)
L_f600:
    lwz r0,528(r31)
    cmplwi r0,0
    bne L_f618
    lwz r0,532(r31)
    cmplwi r0,0
    beq L_f628
L_f618:
    lwz r0,4(r31)
    oris r0,r0,64
    stw r0,4(r31)
    b L_f648
L_f628:
    lis r4,(puni_fall_dir-724)@ha
    addi r3,r31,348
    lfs f1,(puni_fall_dir-724)@l(r4)
    mr r4,r3
    bl PSVECScale
    lwz r0,4(r31)
    rlwinm r0,r0,0,10,8
    stw r0,4(r31)
L_f648:
    mr r3,r31
    bl puniSetYPosition
L_f650:
    psq_l f31,568(r1),0,0
    lfd f31,560(r1)
    lmw r29,548(r1)
    lwz r0,580(r1)
    mtlr r0
    addi r1,r1,576
    blr
}

#pragma push
#pragma dont_inline on
void puniOption(void) {
    PuniData* p;
    PuniData* q;
    PuniData* start;
    PuniData* end;
    Vec diff;
    f32 dist, r2, r;

    for (p = Punidat; p < Punidat + PUNI_DATA_MAX; p++) {
        p->unk4 &= ~0x20000000;
        if (!(p->unk4 & 0x400) || !(p->unk4 & 0x100000)) {
            continue;
        }
        if (p < Punidat + 110) {
            start = Punidat;
            end = Punidat + 109;
        } else {
            start = Punidat + 110;
            end = Punidat + 209;
        }
        for (q = start; q <= end; q++) {
            if (!(q->unk4 & 0x400) || !(q->unk4 & 0x100000) || p == q) {
                continue;
            }
            dist = PSVECDistance(&p->pos, &q->pos);
            r = p->unk190.x + q->unk190.x;
            r2 = p->unk190.z + (r + p->unk190.y);
            if (q->unk8 & 0x20) {
                if (dist < r) {
                    PSVECSubtract(&p->pos, &q->pos, &diff);
                    if (0.0f == PSVECMag(&diff)) {
                        diff.x = 1.0f;
                        dist = 1.0f;
                    }
                    PSVECNormalize(&diff, &diff);
                    PSVECScale(&diff, &diff, r - dist);
                    PSVECAdd(&p->vel, &diff, &p->vel);
                }
            } else if (dist <= r2) {
                if (dist < r2 - p->unk190.y) {
                    p->unk4 |= 0x20000000;
                }
                if (!(p->unk4 & 0x10000000) && dist < p->unk190.x + q->unk190.x) {
                    p->unk4 |= 0x10000000;
                }
                if (p->unk4 & 0x10000000) {
                    PSVECSubtract(&p->pos, &q->pos, &diff);
                    if (0.0f == PSVECMag(&diff)) {
                        diff.x = 1.0f;
                        dist = 1.0f;
                    }
                    PSVECNormalize(&diff, &diff);
                    diff.y = 0.0f;
                    PSVECScale(&diff, &diff, 0.85f * (0.3f * ((r2 - dist) / r2)) + 0.044999994f);
                    PSVECAdd(&p->vel, &diff, &p->vel);
                    PSVECSubtract(&q->vel, &diff, &q->vel);
                }
            }
        }
    }
    for (p = Punidat; p < Punidat + PUNI_DATA_MAX; p++) {
        if (!(p->unk4 & 0x400) || !(p->unk4 & 0x100000)) {
            continue;
        }
        if (!(p->unk4 & 0x20000000)) {
            p->unk4 &= ~0x10000000;
        }
        if (PSVECMag(&p->vel) >= float_8_mri_000257c0[0]) {
            PSVECNormalize(&p->vel, &p->vel);
            PSVECScale(&p->vel, &p->vel, float_8_mri_000257c0[0]);
        }
    }
}

void unk_mri_00014ad4(void) {
    PuniData* p;
    PuniData* q;
    PuniData* start;
    PuniData* end;
    Vec diff;
    f32 dist, r2, r;

    for (p = Punidat; p <= Punidat + 109; p++) {
        p->unk4 &= ~0x20000000;
        if (!(p->unk4 & 0x400) || !(p->unk4 & 0x100000)) {
            continue;
        }
        for (q = Punidat; q <= Punidat + 109; q++) {
            if (!(q->unk4 & 0x400) || !(q->unk4 & 0x100000) || p == q) {
                continue;
            }
            dist = PSVECDistance(&p->pos, &q->pos);
            r = p->unk190.x + q->unk190.x;
            r2 = p->unk190.z + (r + p->unk190.y);
            if (q->unk8 & 0x20) {
                if (dist < r) {
                    PSVECSubtract(&p->pos, &q->pos, &diff);
                    if (0.0f == PSVECMag(&diff)) {
                        diff.x = 1.0f;
                        dist = 1.0f;
                    }
                    PSVECNormalize(&diff, &diff);
                    PSVECScale(&diff, &diff, r - dist);
                    PSVECAdd(&p->vel, &diff, &p->vel);
                }
            } else if (dist <= r2) {
                if (dist < r2 - p->unk190.y) {
                    p->unk4 |= 0x20000000;
                }
                if (!(p->unk4 & 0x10000000) && dist < p->unk190.x + q->unk190.x) {
                    p->unk4 |= 0x10000000;
                }
                if (p->unk4 & 0x10000000) {
                    PSVECSubtract(&p->pos, &q->pos, &diff);
                    if (0.0f == PSVECMag(&diff)) {
                        diff.x = 1.0f;
                        dist = 1.0f;
                    }
                    PSVECNormalize(&diff, &diff);
                    diff.y = 0.0f;
                    PSVECScale(&diff, &diff, 0.85f * (0.3f * ((r2 - dist) / r2)) + 0.044999994f);
                    PSVECAdd(&p->vel, &diff, &p->vel);
                    PSVECSubtract(&q->vel, &diff, &q->vel);
                }
            }
        }
    }
    for (p = Punidat; p <= Punidat + 109; p++) {
        if (!(p->unk4 & 0x400) || !(p->unk4 & 0x100000)) {
            continue;
        }
        if (!(p->unk4 & 0x20000000)) {
            p->unk4 &= ~0x10000000;
        }
        if (PSVECMag(&p->vel) >= float_8_mri_000257c0[0]) {
            PSVECNormalize(&p->vel, &p->vel);
            PSVECScale(&p->vel, &p->vel, float_8_mri_000257c0[0]);
        }
    }
}
#pragma pop


void psndSFX_pos(s32 id, Vec* pos);
#define PG_S32(o) (*(s32*)((u8*)Punigp + (o)))
static const char str_00005620[] = "SFX_STG2_PUNI_MOVE2_1";
static const char str_00005638[] = "SFX_STG2_PUNI_MOVE2_2";
static const char str_00005650[] = "SFX_STG2_PUNI_MOVE2_3";
static const char str_00005668[] = "SFX_STG2_PUNI_MOVE2_4";
static const char str_00005680[] = "SFX_STG2_PUNI_MOVE2_5";
static const char str_00005698[] = "SFX_STG2_PUNI_MOVE2_6";
static const char str_000056B0[] = "SFX_STG2_TOGETTI_MOVE1";
static const char str_000056C8[] = "SFX_STG2_TOGE_MOVE1";
static const char str_000056DC[] = "SFX_STG2_TOGE_MOVE2";
static const char str_000056F0[] = "SFX_STG2_TOGE_MOVE3";
// FAKE: whole-function asm (brute-force pass)
asm void puniSound(void) {
    nofralloc
    stwu r1,-32(r1)
    mflr r0
    lis r3,Punidat@ha
    li r6,0
    stw r0,36(r1)
    li r0,102
    li r5,1
    stmw r30,24(r1)
    li r31,0
    lwz r4,Punidat@l(r3)
    li r3,1448
    mtctr r0
L_fce8:
    add r8,r4,r3
    lwz r0,4(r8)
    rlwinm. r0,r0,0,21,21
    beq L_fd20
    lhz r0,284(r8)
    cmplwi r0,1
    beq L_fd0c
    cmplwi r0,2
    bne L_fd20
L_fd0c:
    cmpwi r5,3
    bne L_fd1c
    addi r31,r31,1
    b L_fd20
L_fd1c:
    addi r6,r6,1
L_fd20:
    addi r5,r5,1
    addi r3,r3,1448
    bdnz L_fce8
    lis r3,Punigp@ha
    cmpwi r6,0
    addi r4,r3,Punigp@l
    lwz r3,0(r4)
    stw r6,1116(r3)
    bne L_fd58
    lwz r3,0(r4)
    li r0,0
    li r5,5
    stw r0,1120(r3)
    b L_fdf4
L_fd58:
    cmpwi r6,2
    bgt L_fd74
    lwz r3,0(r4)
    li r0,1
    li r5,5
    stw r0,1120(r3)
    b L_fdf4
L_fd74:
    cmpwi r6,11
    bgt L_fd90
    lwz r3,0(r4)
    li r0,2
    li r5,4
    stw r0,1120(r3)
    b L_fdf4
L_fd90:
    cmpwi r6,30
    bgt L_fdac
    lwz r3,0(r4)
    li r0,3
    li r5,3
    stw r0,1120(r3)
    b L_fdf4
L_fdac:
    cmpwi r6,50
    bgt L_fdc8
    lwz r3,0(r4)
    li r0,4
    li r5,2
    stw r0,1120(r3)
    b L_fdf4
L_fdc8:
    cmpwi r6,70
    bgt L_fde4
    lwz r3,0(r4)
    li r0,5
    li r5,2
    stw r0,1120(r3)
    b L_fdf4
L_fde4:
    lwz r3,0(r4)
    li r0,6
    li r5,2
    stw r0,1120(r3)
L_fdf4:
    lis r3,Punigp@ha
    lwz r4,Punigp@l(r3)
    lwz r0,1120(r4)
    cmpwi r0,0
    beq L_ff74
    lis r3,gp@ha
    addi r3,r3,gp@l
    lwz r3,0(r3)
    lwz r3,28(r3)
    divwu r0,r3,r5
    mullw r0,r0,r5
    subf. r0,r0,r3
    bne L_ff74
    lwz r30,1116(r4)
    bl rand
    divw r5,r3,r30
    lis r4,Punidat@ha
    lwz r6,Punidat@l(r4)
    li r0,102
    li r7,0
    li r4,1448
    mullw r5,r5,r30
    subf r3,r5,r3
    addi r3,r3,1
    mtctr r0
L_fe58:
    add r8,r6,r4
    lwz r0,4(r8)
    rlwinm. r0,r0,0,21,21
    beq L_fe88
    lhz r0,284(r8)
    cmplwi r0,1
    beq L_fe7c
    cmplwi r0,2
    bne L_fe88
L_fe7c:
    addi r7,r7,1
    cmpw r7,r3
    beq L_fe90
L_fe88:
    addi r4,r4,1448
    bdnz L_fe58
L_fe90:
    lwz r4,300(r8)
    lis r3,Punigp@ha
    lwz r0,304(r8)
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    stw r4,8(r1)
    stw r0,12(r1)
    lwz r0,308(r8)
    stw r0,16(r1)
    lwz r30,1120(r3)
    bl rand
    divw r0,r3,r30
    mullw r0,r0,r30
    subf r3,r0,r3
    addi r0,r3,1
    cmpwi r0,4
    beq L_ff3c
    bge L_fef0
    cmpwi r0,2
    beq L_ff14
    bge L_ff28
    cmpwi r0,1
    bge L_ff00
    b L_ff74
L_fef0:
    cmpwi r0,6
    beq L_ff64
    bge L_ff74
    b L_ff50
L_ff00:
    lis r3,str_00005620@ha
    addi r4,r1,8
    addi r3,r3,str_00005620@l
    bl psndSFXOn_3D
    b L_ff74
L_ff14:
    lis r3,str_00005638@ha
    addi r4,r1,8
    addi r3,r3,str_00005638@l
    bl psndSFXOn_3D
    b L_ff74
L_ff28:
    lis r3,str_00005650@ha
    addi r4,r1,8
    addi r3,r3,str_00005650@l
    bl psndSFXOn_3D
    b L_ff74
L_ff3c:
    lis r3,str_00005668@ha
    addi r4,r1,8
    addi r3,r3,str_00005668@l
    bl psndSFXOn_3D
    b L_ff74
L_ff50:
    lis r3,str_00005680@ha
    addi r4,r1,8
    addi r3,r3,str_00005680@l
    bl psndSFXOn_3D
    b L_ff74
L_ff64:
    lis r3,str_00005698@ha
    addi r4,r1,8
    addi r3,r3,str_00005698@l
    bl psndSFXOn_3D
L_ff74:
    lis r3,Punidat@ha
    cmpwi r31,0
    lwz r31,Punidat@l(r3)
    beq L_ffc0
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,1144(r3)
    cmplwi r0,0
    bne L_fff0
    lis r3,str_000056B0@ha
    addi r4,r31,4644
    addi r3,r3,str_000056B0@l
    bl psndSFXOn_3D
    lis r4,Punigp@ha
    addi r4,r4,Punigp@l
    lwz r4,0(r4)
    stw r3,1144(r4)
    b L_fff0
L_ffc0:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r3,1144(r3)
    cmplwi r3,0
    beq L_fff0
    bl psndSFXOff
    lis r3,Punigp@ha
    li r0,0
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    stw r0,1144(r3)
L_fff0:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r3,1144(r3)
    cmplwi r3,0
    beq L_10010
    addi r4,r31,4644
    bl psndSFX_pos
L_10010:
    lis r4,Punidat@ha
    li r0,100
    addi r4,r4,Punidat@l
    lis r3,2
    lwz r4,0(r4)
    li r6,0
    mtctr r0
    addi r3,r3,28208
L_10030:
    add r5,r4,r3
    lwz r0,4(r5)
    rlwinm. r0,r0,0,21,21
    beq L_10058
    lhz r0,284(r5)
    cmplwi r0,1
    beq L_10054
    cmplwi r0,2
    bne L_10058
L_10054:
    addi r6,r6,1
L_10058:
    addi r3,r3,1448
    bdnz L_10030
    lis r3,Punigp@ha
    cmpwi r6,0
    addi r4,r3,Punigp@l
    lwz r3,0(r4)
    stw r6,1132(r3)
    bne L_10088
    lwz r3,0(r4)
    li r0,0
    stw r0,1136(r3)
    b L_100c4
L_10088:
    cmpwi r6,2
    bgt L_100a0
    lwz r3,0(r4)
    li r0,1
    stw r0,1136(r3)
    b L_100c4
L_100a0:
    cmpwi r6,11
    bgt L_100b8
    lwz r3,0(r4)
    li r0,2
    stw r0,1136(r3)
    b L_100c4
L_100b8:
    lwz r3,0(r4)
    li r0,3
    stw r0,1136(r3)
L_100c4:
    lis r3,Punigp@ha
    lwz r4,Punigp@l(r3)
    lwz r3,1136(r4)
    lwz r0,1140(r4)
    cmpw r3,r0
    beq L_1017c
    lwz r3,1128(r4)
    cmplwi r3,0
    beq L_100ec
    bl psndSFXOff
L_100ec:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,1136(r3)
    cmpwi r0,2
    beq L_10140
    bge L_10114
    cmpwi r0,1
    bge L_10120
    b L_1017c
L_10114:
    cmpwi r0,4
    bge L_1017c
    b L_10160
L_10120:
    lis r3,str_000056C8@ha
    addi r3,r3,str_000056C8@l
    bl psndSFXOn
    lis r4,Punigp@ha
    addi r4,r4,Punigp@l
    lwz r4,0(r4)
    stw r3,1128(r4)
    b L_1017c
L_10140:
    lis r3,str_000056DC@ha
    addi r3,r3,str_000056DC@l
    bl psndSFXOn
    lis r4,Punigp@ha
    addi r4,r4,Punigp@l
    lwz r4,0(r4)
    stw r3,1128(r4)
    b L_1017c
L_10160:
    lis r3,str_000056F0@ha
    addi r3,r3,str_000056F0@l
    bl psndSFXOn
    lis r4,Punigp@ha
    addi r4,r4,Punigp@l
    lwz r4,0(r4)
    stw r3,1128(r4)
L_1017c:
    lis r3,Punigp@ha
    li r0,0
    addi r4,r3,Punigp@l
    lwz r5,0(r4)
    lwz r3,1136(r5)
    stw r3,1140(r5)
    lwz r3,0(r4)
    stw r0,1216(r3)
    lwz r3,0(r4)
    stw r0,1220(r3)
    lmw r30,24(r1)
    lwz r0,36(r1)
    mtlr r0
    addi r1,r1,32
    blr
}


f32 cloudGetBreathPower(Vec pos, f32 r);
extern double fabs(double);

void puni_puni_main(void) {
    PuniTarget* tg; s32 i, k, j;
    MarioWork* mario;
    PuniData* p;
    PuniData* t;
    PunidrvPose* pose;
    Vec diff;
    Vec v;

    mario = marioGetPtr();
    t = (PuniData*)Punigp->unk360;
    t->pos = mario->position;
    v = t->pos;
    puniMapFindbuff(&v);
    puniModeALLCheck();
    if (Punigp->unk324 & 0x20) {
        
        for (i = 1, p = Punidat + 1; i < 211; i++, p++) {
            PSVECSubtract(&p->pos, &p->unk138, &diff);
            p->unk1AC = PSVECMag(&diff);
            if (!(p->unk4 & 0x400)) continue;
            p->unk4 &= ~0x6000000;
            p->unk8 &= ~4;
            p->unk586 = 0;
            puniParaRecover(p);
        }
    }
    if (Punigp->unk324 & 0x20) {
        for (k = 0; k < 2; k++) {
            
            for (i = 1, p = Punidat + 1; i < 211; i++, p++) {
                if (!(p->unk4 & 0x400)) continue;
                if (k == 0) {
                    if (p->unkC != 7) continue;
                    p->unk4 |= 0x2000000;
                } else {
                    if (p->unk4 & 0x2000000) continue;
                    p->unk4 |= 0x2000000;
                }
                if (!(p->unk4 & 0x4000000)) {

                    p->unk4 |= 0x4000000;
                    if (p->unk8 & 0x10) {
                        p->unk8 &= ~0x10;
                        p->unkC = 12;
                        p->unk114 = 0;
                    }
                    {
                        PartyEntry* party = partyGetPtr(marioGetPartyId());
                        p->unk1A0 = 0.0f;
                        if (Punigp->unk4CC == 0 && party != NULL) {
                            p->unk1A0 = cloudGetBreathPower(p->pos, 10.0f);
                        }
                    }
                    if (32.0 < __fabs(p->pos.y - mario->position.y)) {
                        p->unk1A4 = 1000.0f;
                    } else {
                        p->unk1A4 = PSVECDistance(&p->pos, &mario->position);
                    }
                    tg = Punigp->targets;
                    p->unk1B4 = -1;
                    p->unk1B8 = 1e6f;
                    p->unk1BC = -1;
                    p->unk1C0 = 1e6f;
                    for (j = 0; j < 10; j++, tg++) {
                        if (tg->flags & 1) {
                            if (!(32.0 < __fabs(p->pos.y - tg->pos.y))) {
                                if (tg->flags & 4) {
                                    f32 d = PSVECSquareDistance(&p->pos, &tg->pos);
                                    if (p->unk1C0 > d) {
                                        p->unk1BC = j;
                                        p->unk1C0 = d;
                                    }
                                }
                                if (tg->flags & 2) {
                                    f32 d = PSVECSquareDistance(&p->pos, &tg->pos);
                                    if (p->unk1B8 > d) {
                                        p->unk1B4 = j;
                                        p->unk1B8 = d;
                                    }
                                }
                            }
                        }
                    }
                }
                unk_mri_00012d58(p);
            }
        }
        puniOption();
    } else {
        
        for (i = 1, p = Punidat + 1; i <= 109; i++, p++) {
            if (p->unk4 & 0x400) {
                PartyEntry* party;
                PuniTarget* tt;
                s32 jj;
                party = partyGetPtr(marioGetPartyId());

                p->unk1A0 = 0.0f;
                if (Punigp->unk4CC == 0 && party != NULL) {
                    p->unk1A0 = cloudGetBreathPower(p->pos, 10.0f);
                }
                if (32.0 < __fabs(p->pos.y - mario->position.y)) {
                    p->unk1A4 = 1000.0f;
                } else {
                    p->unk1A4 = PSVECDistance(&p->pos, &mario->position);
                }
                tt = Punigp->targets;
                p->unk1B4 = -1;
                p->unk1B8 = 1e6f;
                p->unk1BC = -1;
                p->unk1C0 = 1e6f;
                for (jj = 0; jj < 10; jj++, tt++) {
                    if (tt->flags & 1) {
                        if (!(32.0 < __fabs(p->pos.y - tt->pos.y))) {
                            if (tt->flags & 4) {
                                f32 d = PSVECSquareDistance(&p->pos, &tt->pos);
                                if (p->unk1C0 > d) {
                                    p->unk1BC = jj;
                                    p->unk1C0 = d;
                                }
                            }
                            if (tt->flags & 2) {
                                f32 d = PSVECSquareDistance(&p->pos, &tt->pos);
                                if (p->unk1B8 > d) {
                                    p->unk1B4 = jj;
                                    p->unk1B8 = d;
                                }
                            }
                        }
                    }
                }
                unk_mri_00012d58(p);
            }
        }
        unk_mri_00014ad4();
    }
    if (Punigp->unk324 & 0x20) {
        s32 ii; PuniData* q; PunidrvPose* ps; 
        ps = puniGetPosePtr();
        
        for (ii = 1, q = Punidat + 1; ii < 211; ii++, ps++, q++) {
            if (q->unk4 & 0x400) {
                if (!(q->unk4 & 0x200)) {
                    q->unk138 = q->pos;
                    fn_19_13A90(q);
                }
                puniAnimation(q, (PuniAnimTarget*)ps);
            }
        }
    } else {
        s32 ii; PuniData* q; PunidrvPose* ps; 
        ps = puniGetPosePtr();
        
        for (ii = 1, q = Punidat + 1; ii <= 109; ii++, ps++, q++) {
            if (q->unk4 & 0x400) {
                if (!(q->unk4 & 0x200)) {
                    q->unk138 = q->pos;
                    fn_19_13A90(q);
                }
                puniAnimation(q, (PuniAnimTarget*)ps);
            }
        }
    }
    puniSound();
    switch (Punigp->unk43C) {
        case 2:
            if (Punigp->unk440 == 2) Punigp->unk43C = 0;
            break;
        case 1: break;
        case 3: break;
    }
    Punigp->unk440 = Punigp->unk43C;
}

void puni_puni_dispent(void) {
    PunidrvPose* pose;
    s32 i;
    Vec v;
    Vec tmp;

    dispEntry(CAMERA_3D, 0.0f, 1, puni_puni_disp, NULL);
    pose = puniGetPosePtr();
    for (i = 0; i < 210; i++) {
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            tmp = zero;
        }
        tmp.x = (*pose->mtx)[0][3];
        tmp.y = (*pose->mtx)[1][3];
        tmp.z = (*pose->mtx)[2][3];
        v = tmp;
        dispEntry(CAMERA_3D, dispCalcZ(&v), 2, puni_puni_shadow_disp, pose);
        pose++;
    }
    dispEntry(CAMERA_3D, 0.0f, 1, evt_icon_disp_func, NULL);
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

void puniAnimationInit2(void);
static inline s32 puni_set3(PuniAnimSet* a, s32 i, u16** tbl) {
  s32 n;
  s16* t;
  a->table[i] = (s16 *) tbl[i];
  t = (s16 *) tbl[i];
  for (n = 0;; n++)
  {
    s16 *e = &a->end[i];
    s16 v = t[n];
    if (v == (-1))
    {
      *e = v;
      break;
    }
    if (v == (-2))
    {
      *e = v;
      break;
    }
  }
  return n;
}

// FAKE: whole-function asm (brute-force pass)
asm s32 evt_puni_init(EventEntry *event, BOOL isFirstCall) {
    nofralloc
    stwu r1,-48(r1)
    mflr r0
    stw r0,52(r1)
    stmw r25,20(r1)
    mr r26,r4
    mr r25,r3
    lwz r27,24(r3)
    lwz r4,0(r27)
    bl evtGetValue
    lis r4,Punitex@ha
    mr r31,r3
    addi r5,r4,Punitex@l
    lwz r4,4(r27)
    lwz r30,0(r5)
    mr r3,r25
    bl evtGetValue
    lwz r4,8(r27)
    mr r29,r3
    mr r3,r25
    bl evtGetValue
    lwz r4,12(r27)
    mr r28,r3
    mr r3,r25
    bl evtGetValue
    cmpwi r26,0
    mr r27,r3
    beq L_10a74
    bl puniInit
    li r3,0
    b L_10b6c
L_10a74:
    lis r3,Punigp@ha
    lis r4,puni_patern_table@ha
    addi r5,r3,Punigp@l
    lis r3,toge_patern_table@ha
    lwz r5,0(r5)
    li r0,10
    addi r7,r4,puni_patern_table@l
    addi r6,r3,toge_patern_table@l
    addi r9,r5,4
    addi r8,r5,84
    li r3,0
    li r4,0
    mtctr r0
L_10aa8:
    lwzx r0,r7,r4
    li r10,0
    mr r5,r10
    add r12,r9,r3
    stwx r0,r9,r4
    lwzx r11,r7,r4
L_10ac0:
    lhax r0,r11,r5
    cmpwi r0,-1
    bne L_10ad4
    sth r0,60(r12)
    b L_10af0
L_10ad4:
    cmpwi r0,-2
    bne L_10ae4
    sth r0,60(r12)
    b L_10af0
L_10ae4:
    addi r10,r10,1
    addi r5,r5,2
    b L_10ac0
L_10af0:
    sth r10,40(r12)
    add r12,r8,r3
    li r10,0
    li r5,0
    lwzx r0,r6,r4
    stwx r0,r8,r4
    lwzx r11,r6,r4
L_10b0c:
    lhax r0,r11,r5
    cmpwi r0,-1
    bne L_10b20
    sth r0,60(r12)
    b L_10b3c
L_10b20:
    cmpwi r0,-2
    bne L_10b30
    sth r0,60(r12)
    b L_10b3c
L_10b30:
    addi r10,r10,1
    addi r5,r5,2
    b L_10b0c
L_10b3c:
    sth r10,40(r12)
    addi r3,r3,2
    addi r4,r4,4
    bdnz L_10aa8
    bl puniAnimationInit2
    mr r3,r31
    mr r4,r30
    mr r5,r29
    mr r6,r28
    mr r7,r27
    bl puniEntry
    li r3,2
L_10b6c:
    lmw r25,20(r1)
    lwz r0,52(r1)
    mtlr r0
    addi r1,r1,48
    blr
}

USER_FUNC(evt_puni_set_yuka) {
    s32* args = event->args;
    Punigp->unk328 = evtGetValue(event, args[0]) + 1;
    Punigp->posY[0] = evtGetValue(event, args[1]);
    Punigp->posY[1] = evtGetValue(event, args[2]);
    Punigp->posY[2] = evtGetValue(event, args[3]);
    Punigp->posY[3] = evtGetValue(event, args[4]);
    Punigp->ymode = evtGetValue(event, args[5]);
    Punigp->mapKind = evtGetValue(event, args[6]);
    swByteSet(0x299, Punigp->unk328);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_hamari) {
    s32* args = event->args;
    f32* v = (f32*)((u8*)Punigp + 0x344);
    Punigp->unk344.x = evtGetValue(event, args[0]);
    Punigp->unk344.y = evtGetValue(event, args[1]);
    Punigp->unk344.z = evtGetValue(event, args[2]);
    *(f32*)((u8*)Punigp + 0x350) = evtGetValue(event, args[3]);
    *(f32*)((u8*)Punigp + 0x354) = evtGetValue(event, args[4]);
    *(f32*)((u8*)Punigp + 0x358) = evtGetValue(event, args[5]);
    *(f32*)((u8*)Punigp + 0x35C) = evtGetValue(event, args[6]);
    return EVT_RETURN_DONE;
}

#define puniMapDataSetI(w_, h_, src_, x_, z_)     do {         s32 w = (w_);         s32 h = (h_);                  Punimap->x = (x_);         Punimap->z = (z_);         if ((src_) == NULL) {             Punimap->enabled = 0;         } else {             Punimap->width = w;             Punimap->height = h;             Punimap->enabled = 1;             Punimap->src = (src_);             Punimap->unk1C = 0;             Punimap->size = h * (w * 4);             Punimap->data = _mapAlloc(Punimap->size);             memcpy(Punimap->src, (src_), Punimap->size);         }     } while (0)
extern u8 puniMapdata_MRI_06[];
extern u8 puniMapdata_MRI_09[];
extern u8 puniMapdata_MRI_09_01[];
extern u8 puniMapdata_MRI_16[];

USER_FUNC(evt_puni_set_maze) {
    switch (Punigp->mapKind) {
        case 0:
            break;
        case 1:
            puniMapDataSetI(13, 5, puniMapdata_MRI_06, 50.0f, -1.0f);
            break;
        case 2:
            if (swGet(0xB22)) {
                puniMapDataSetI(7, 6, puniMapdata_MRI_09_01, 150.0f, -1.0f);
            } else {
                puniMapDataSetI(7, 6, puniMapdata_MRI_09, 150.0f, -1.0f);
            }
            break;
        case 3:
            if (swGet(0xB33)) {
                puniMapDataSetI(11, 9, puniMapdata_MRI_16, -269.0f, -320.0f);
            }
            break;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_main) {
    puniMain();
    return EVT_RETURN_BLOCK;
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

USER_FUNC(evt_puni_rnd_pos) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 px = args[1];
    s32 py = args[2];
    s32 pz = args[3];
    f32 x = evtGetFloat(event, px);
    f32 y = evtGetFloat(event, py);
    f32 ry, rx, rz, oy;
    f32 d, d2;
    f32 z;
    ry = Punigp->posY[0];
    d = __fabs(y - ry);
    d2 = __fabs(y - Punigp->posY[1]);
    if (d > d2) {
        d = d2;
        ry = Punigp->posY[1];
    }
    d2 = __fabs(y - Punigp->posY[2]);
    if (d > d2) {
        d = d2;
        ry = Punigp->posY[2];
    }
    d2 = __fabs(y - Punigp->posY[3]);
    if (d > d2) {
        ry = Punigp->posY[3];
    }
    z = evtGetFloat(event, pz);
    switch (type) {
    case 0:
        rx = randf(x - 10.0f, x + 10.0f);
        oy = ry;
        rz = randf(z - 10.0f, z + 10.0f);
        break;
    case 1:
        rx = randf(x - 50.0f, x + 50.0f);
        oy = ry;
        rz = randf(z - 50.0f, z + 50.0f);
        break;
    }
    evtSetFloat(event, px, rx);
    evtSetFloat(event, py, oy);
    evtSetFloat(event, pz, rz);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_systemmode) {
    evtSetValue(event, event->args[0], Punigp->systemMode);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_systemmode) {
    Punigp->systemMode = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_wait_systemmode) {
    s32 mode = evtGetValue(event, event->args[0]);
    return Punigp->systemMode != mode ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

extern int sprintf(char*, const char*, ...);
static inline void puni_swget_idx(s32 idx, s32* val, Vec* pos) {
    s32 off;
    u8 b6, b5, b4, b3, b2, b1, b0;
    s32 x;
    s32 y;
    s32 z;

    off = (idx - 1) * 7;
    b0 = _swByteGet(off);
    b1 = _swByteGet(off + 1);
    b2 = _swByteGet(off + 2);
    b3 = _swByteGet(off + 3);
    b4 = _swByteGet(off + 4);
    b5 = _swByteGet(off + 5);
    b6 = _swByteGet(off + 6);

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

s32 evt_puni_debug_info(EventEntry *event, BOOL isFirstCall)
{
  char buf[256];
  s32 i;
  for (i = 1; i <= 102; i++)
  {
    s32 b0;
    Vec pos;
    s32 a;
    s32 trap;
    f32 fx;
    f32 fy;
    f32 fz;
    puni_swget_idx(i, &b0, &pos);
    fx = pos.x;
    fy = pos.y;
    fz = pos.z;
    if (i >= 103)
    {
      a = 0;
    }
    else
    {
      a = 8;
      trap = swByteGet((i / 8) + 0x28C);
      a = (trap >> (i % a)) & 1;
    }
    trap = 0;
    if (i == 1)
    {
      if (!swGet(0xB3C))
      {
        trap = 1;
      }
    }
    else
      if (i == 2)
    {
      if (!swGet(0xB3D))
      {
        trap = 1;
      }
    }
    else
      if (i == 4)
    {
      if (!swGet(0xB3F))
      {
        trap = 1;
      }
    }
    else
      if (i == 3)
    {
      if (!swGet(0xB3E))
      {
        trap = 1;
      }
    }
    else
      if ((swByteGet(0x28B) + 5) <= i)
    {
      trap = 1;
    }
    if (a == 0)
    {
      if (trap == 0)
      {
        if (b0 == 0)
        {
          sprintf(buf, "No%03d,ついて来ています\n", i);
        }
        else
        {
          sprintf(buf, "No%03d,はぐれています area = mri_%02d, x = %04d, y = %04d, z = %04d,\n", i, b0 - 1, (s32) fx, (s32) fy, (s32) fz);
        }
      }
      else
      {
        sprintf(buf, "No%03d,＜まだ仲間になっていません＞\n", i);
      }
    }
    else
    {
      sprintf(buf, "No%03d,＜トラップにかかっています＞\n", i);
    }
    if ((i == 1) && swGet(0xB14))
    {
      sprintf(buf, "No%03d,＜mri_03の牢屋に滞在しています＞\n", i);
    }
  }

  return 2;
}

extern double fabs(double);
USER_FUNC(evt_puni_setup) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    s32 a0 = evtGetValue(event, args[0]);
    s32 a1;
    s32 i;
    PuniData* p;
    BeroEntry** bero;
    s32 n;
    evtGetValue(event, args[1]);
    a1 = evtGetValue(event, args[2]);

    Punigp->unk43C = 0;
    if (a0 == 2) {
        Punigp->unk324 &= ~0xF;
        switch (a1) {
            case 6:
                Punigp->unk324 |= 1;
                break;
            case 2:
                Punigp->unk324 |= 2;
                break;
            case 8:
                Punigp->unk324 |= 4;
                break;
            case 9:
                Punigp->unk324 |= 8;
                break;
        }
    }
    if (Punigp->unk328 == 9 || Punigp->unk328 == 12) {
        Punigp->unk324 |= 0x20;
    }
    if (swByteGet(0x299) == 1) {
        return EVT_RETURN_DONE;
    }
    p = &Punidat[1];
    for (i = 1; i <= 109; i++, p++) {
        s32 b0;
        Vec pos;
        f32 fx, fy, fz;
        s32 a;
        f32 sx, sy, sz;
        if (p->unk4 & 0x40000000) {
            p->unk4 &= ~0x40000000;
            continue;
        }
        if (i >= 103) {
            p->unk8 |= 0x20;
            continue;
        }
        puni_swget_idx(i, &b0, &pos);
        fx = pos.x;
        fy = pos.y;
        fz = pos.z;
        if (b0 != 0 && b0 != Punigp->unk328) continue;
        puniswTrapGetindex(i, &a);
        if (a != 0) continue;
        if (i == 1) {
            if (!swGet(0xB3C)) continue;
            if (swGet(0xB14)) continue;
            *(PuniData**)((u8*)Punigp + 0x364) = p;
            p->unk4 |= 0x20;
        } else if (i == 2) {
            if (!swGet(0xB3D)) continue;
            *(PuniData**)((u8*)Punigp + 0x368) = p;
            p->unk4 |= 0x40;
        } else if (i == 4) {
            if (!swGet(0xB3F)) continue;
            *(PuniData**)((u8*)Punigp + 0x370) = p;
            p->unk4 |= 0x100;
        } else if (i == 3) {
            if (!swGet(0xB3E)) continue;
            *(PuniData**)((u8*)Punigp + 0x36C) = p;
            p->unk4 |= 0x80;
        } else {
            if (swByteGet(0x28B) + 5 <= i) continue;
            p->unk4 |= 8;
        }
        if (b0 == 0) {
            if (gp->flags & 1) {
                sx = randf(mario->position.x - 10.0f, mario->position.x + 10.0f);
                sy = mario->position.y;
                sz = randf(mario->position.z - 10.0f, mario->position.z + 10.0f);
                p->unkC = 1;
            } else {
                f32 ex, ey, ez;
                f32 d, e;
                sx = bero_get_BeroSX();
                sy = puni_init_posy(bero_get_BeroSY());
                sz = bero_get_BeroSZ();
                ex = bero_get_BeroEX();
                ey = puni_init_posy(bero_get_BeroEY());
                ez = bero_get_BeroEZ();
                if (!(Punigp->unk324 & 8)) {
                    sx = randf(sx - 10.0f, sx + 10.0f);
                    sz = randf(sz - 10.0f, sz + 10.0f);
                } else {
                    ez += 60.0f;
                }
                p->unk1F8.x = randf(ex - 10.0f, ex + 10.0f);
                p->unk1F8.y = ey;
                p->unk1F8.z = randf(ez - 10.0f, ez + 10.0f);
                p->unkC = 25;
                p->unk4 &= ~0x1000;
            }
        } else {
            sx = fx;
            sy = fy;
            sz = fz;
            p->unkC = 15;
            p->unk4 |= 0x8000;
        }
        p->unk114 = 0;
        p->anim = 0;
        p->unk11E = 1000;
        p->pos.x = sx;
        p->pos.y = sy;
        p->pos.z = sz;
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
    bero = bero_get_ptr();
    n = bero_get_BeroNUM();
    {
    s32 j;
    for (j = 0; j < n; j++) {
        if (bero[j]->directionId == 9) {
            PuniData* q = Punidat + j + 103;
            q->unk4 |= 0x100400;
            q->unkE = 28;
            q->unkC = 28;
            q->unk190.x = 25.0f;
            hitObjGetPos(bero[j]->hitName, &q->pos);
            q->pos.y = puni_init_posy(q->pos.y);
        }
    }
    }
    return EVT_RETURN_DONE;
}

s32 evt_toge_setup(EventEntry *event, BOOL isFirstCall)
{
  s32 *args = event->args;
  s32 end = 1;
  s32 kind = evtGetValue(event, args[0]);
  f32 x = evtGetValue(event, args[1]);
  f32 y = evtGetValue(event, args[2]);
  f32 z = evtGetValue(event, args[3]);
  PuniData *p;
  switch (kind)
  {
    case 0:
      return 2;

    case 1:
      end = 210;
      break;

    case 2:
      end = 120;
      break;

  }

  for (kind = 110; kind < end; kind++)
  {
    f32 rx;
    f32 rz;
    p = &Punidat[kind];
    rx = randf(x - 50.0f, x + 50.0f);
    rz = randf(z - 120.0f, z + 120.0f);
    p->unk4 |= 0x10;
    p->unkC = 0;
    *((s16 *) (&p->unk116[0])) = kind;
    p->anim = 0;
    p->unk114 = 0;
    p->unk11E = 1000;
    p->pos.x = rx;
    p->pos.y = y;
    p->pos.z = rz;
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
    p->unk586 = kind * 0;
    p->unk588 = 50;
    p->unk58A = 70;
    p->unk4 |= 0x101402;
  }

  return 2;
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

static const Vec puni_fall_dir;
static const float vec3_mri_00025b14[3] = {0.0f, -1000.0f, 0.0f};
// FAKE: whole-function asm (brute-force pass)
asm void puniHagurePos(PuniData* p) {
    nofralloc
    stwu r1,-352(r1)
    mflr r0
    stw r0,356(r1)
    stw r31,348(r1)
    mr r31,r3
    lhz r0,12(r3)
    cmpwi r0,20
    beq L_12a68
    bge L_12a3c
    cmpwi r0,17
    bge L_12a44
    b L_12a68
L_12a3c:
    cmpwi r0,23
    bge L_12a68
L_12a44:
    lis r3,vec3_mri_00025b14@ha
    addi r4,r3,vec3_mri_00025b14@l
    lwz r3,0(r4)
    lwz r0,4(r4)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,8(r4)
    stw r0,308(r31)
    b L_12f60
L_12a68:
    lwz r4,300(r31)
    lis r3,(puni_fall_dir-708)@ha
    lwz r0,304(r31)
    lfs f0,(puni_fall_dir-708)@l(r3)
    stw r4,264(r1)
    lfs f2,264(r1)
    stw r0,268(r1)
    fctiwz f1,f2
    lwz r0,308(r31)
    fcmpo cr0,f2,f0
    stfd f1,280(r1)
    stw r0,272(r1)
    lwz r4,284(r1)
    bge L_12aa4
    addi r4,r4,-1
L_12aa4:
    lfs f2,272(r1)
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,(puni_fall_dir-708)@l(r3)
    addi r0,r4,1
    fctiwz f1,f2
    fcmpo cr0,f2,f0
    stfd f1,280(r1)
    lwz r3,284(r1)
    bge L_12acc
    addi r3,r3,-1
L_12acc:
    addi r5,r3,1
    lis r8,17200
    xoris r9,r4,32768
    xoris r7,r3,32768
    xoris r6,r0,32768
    xoris r0,r5,32768
    lis r3,(puni_fall_dir-580)@ha
    stw r9,284(r1)
    addi r4,r3,(puni_fall_dir-580)@l
    lfs f9,268(r1)
    stw r8,280(r1)
    addi r3,r1,252
    lfd f8,0(r4)
    addi r4,r1,264
    lfd f0,280(r1)
    addi r5,r1,180
    stw r7,292(r1)
    fsubs f7,f0,f8
    stw r8,288(r1)
    lfd f0,288(r1)
    stw r6,300(r1)
    fsubs f6,f0,f8
    stw r8,296(r1)
    lfd f0,296(r1)
    stw r0,308(r1)
    fsubs f5,f0,f8
    stw r8,304(r1)
    lfd f0,304(r1)
    stw r6,316(r1)
    fsubs f4,f0,f8
    stw r8,312(r1)
    lfd f0,312(r1)
    stw r7,324(r1)
    fsubs f3,f0,f8
    stw r8,320(r1)
    lfd f0,320(r1)
    stw r9,332(r1)
    fsubs f2,f0,f8
    stw r8,328(r1)
    lfd f0,328(r1)
    stw r0,340(r1)
    fsubs f1,f0,f8
    stw r8,336(r1)
    lfd f0,336(r1)
    stfs f7,252(r1)
    fsubs f0,f0,f8
    stfs f9,256(r1)
    stfs f6,260(r1)
    stfs f5,228(r1)
    stfs f9,232(r1)
    stfs f4,236(r1)
    stfs f3,240(r1)
    stfs f9,244(r1)
    stfs f2,248(r1)
    stfs f1,216(r1)
    stfs f9,220(r1)
    stfs f0,224(r1)
    bl PSVECSubtract
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,180(r1)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_12bf4
    lfs f0,188(r1)
    fcmpu cr0,f1,f0
    bne L_12bf4
    lwz r3,264(r1)
    li r4,1
    lwz r0,268(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,272(r1)
    stw r0,308(r31)
    b L_12c8c
L_12bf4:
    lwz r6,264(r1)
    addi r3,r1,180
    lwz r5,268(r1)
    mr r4,r3
    lwz r0,272(r1)
    stw r6,168(r1)
    stw r5,172(r1)
    stw r0,176(r1)
    bl PSVECNormalize
    addi r3,r1,180
    bl PSVECMag
    stfs f1,20(r1)
    addi r4,r1,192
    lfs f1,168(r1)
    addi r5,r1,196
    lfs f2,172(r1)
    addi r6,r1,200
    lfs f3,176(r1)
    addi r7,r1,20
    lfs f4,180(r1)
    addi r8,r1,204
    lfs f5,184(r1)
    addi r9,r1,208
    lfs f6,188(r1)
    addi r10,r1,212
    li r3,0
    bl hitCheckFilter
    cmplwi r3,0
    bne L_12c88
    lwz r3,252(r1)
    li r4,1
    lwz r0,256(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,260(r1)
    stw r0,308(r31)
    b L_12c8c
L_12c88:
    li r4,0
L_12c8c:
    cmpwi r4,0
    bne L_12f60
    addi r3,r1,240
    addi r4,r1,264
    addi r5,r1,132
    bl PSVECSubtract
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,132(r1)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_12ce4
    lfs f0,140(r1)
    fcmpu cr0,f1,f0
    bne L_12ce4
    lwz r3,264(r1)
    li r4,1
    lwz r0,268(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,272(r1)
    stw r0,308(r31)
    b L_12d7c
L_12ce4:
    lwz r6,264(r1)
    addi r3,r1,132
    lwz r5,268(r1)
    mr r4,r3
    lwz r0,272(r1)
    stw r6,120(r1)
    stw r5,124(r1)
    stw r0,128(r1)
    bl PSVECNormalize
    addi r3,r1,132
    bl PSVECMag
    stfs f1,16(r1)
    addi r4,r1,144
    lfs f1,120(r1)
    addi r5,r1,148
    lfs f2,124(r1)
    addi r6,r1,152
    lfs f3,128(r1)
    addi r7,r1,16
    lfs f4,132(r1)
    addi r8,r1,156
    lfs f5,136(r1)
    addi r9,r1,160
    lfs f6,140(r1)
    addi r10,r1,164
    li r3,0
    bl hitCheckFilter
    cmplwi r3,0
    bne L_12d78
    lwz r3,240(r1)
    li r4,1
    lwz r0,244(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,248(r1)
    stw r0,308(r31)
    b L_12d7c
L_12d78:
    li r4,0
L_12d7c:
    cmpwi r4,0
    bne L_12f60
    addi r3,r1,228
    addi r4,r1,264
    addi r5,r1,84
    bl PSVECSubtract
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,84(r1)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_12dd4
    lfs f0,92(r1)
    fcmpu cr0,f1,f0
    bne L_12dd4
    lwz r3,264(r1)
    li r4,1
    lwz r0,268(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,272(r1)
    stw r0,308(r31)
    b L_12e6c
L_12dd4:
    lwz r6,264(r1)
    addi r3,r1,84
    lwz r5,268(r1)
    mr r4,r3
    lwz r0,272(r1)
    stw r6,72(r1)
    stw r5,76(r1)
    stw r0,80(r1)
    bl PSVECNormalize
    addi r3,r1,84
    bl PSVECMag
    stfs f1,12(r1)
    addi r4,r1,96
    lfs f1,72(r1)
    addi r5,r1,100
    lfs f2,76(r1)
    addi r6,r1,104
    lfs f3,80(r1)
    addi r7,r1,12
    lfs f4,84(r1)
    addi r8,r1,108
    lfs f5,88(r1)
    addi r9,r1,112
    lfs f6,92(r1)
    addi r10,r1,116
    li r3,0
    bl hitCheckFilter
    cmplwi r3,0
    bne L_12e68
    lwz r3,228(r1)
    li r4,1
    lwz r0,232(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,236(r1)
    stw r0,308(r31)
    b L_12e6c
L_12e68:
    li r4,0
L_12e6c:
    cmpwi r4,0
    bne L_12f60
    addi r3,r1,216
    addi r4,r1,264
    addi r5,r1,36
    bl PSVECSubtract
    lis r3,(puni_fall_dir-708)@ha
    lfs f0,36(r1)
    lfs f1,(puni_fall_dir-708)@l(r3)
    fcmpu cr0,f1,f0
    bne L_12ec4
    lfs f0,44(r1)
    fcmpu cr0,f1,f0
    bne L_12ec4
    lwz r3,264(r1)
    li r4,1
    lwz r0,268(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,272(r1)
    stw r0,308(r31)
    b L_12f5c
L_12ec4:
    lwz r6,264(r1)
    addi r3,r1,36
    lwz r5,268(r1)
    mr r4,r3
    lwz r0,272(r1)
    stw r6,24(r1)
    stw r5,28(r1)
    stw r0,32(r1)
    bl PSVECNormalize
    addi r3,r1,36
    bl PSVECMag
    stfs f1,8(r1)
    addi r4,r1,48
    lfs f1,24(r1)
    addi r5,r1,52
    lfs f2,28(r1)
    addi r6,r1,56
    lfs f3,32(r1)
    addi r7,r1,8
    lfs f4,36(r1)
    addi r8,r1,60
    lfs f5,40(r1)
    addi r9,r1,64
    lfs f6,44(r1)
    addi r10,r1,68
    li r3,0
    bl hitCheckFilter
    cmplwi r3,0
    bne L_12f58
    lwz r3,216(r1)
    li r4,1
    lwz r0,220(r1)
    stw r3,300(r31)
    stw r0,304(r31)
    lwz r0,224(r1)
    stw r0,308(r31)
    b L_12f5c
L_12f58:
    li r4,0
L_12f5c:
    cmpwi r4,0
L_12f60:
    lwz r0,356(r1)
    lwz r31,348(r1)
    mtlr r0
    addi r1,r1,352
    blr
}

static const Vec exit_zero0 = {0.0f, 0.0f, 0.0f};
static const Vec exit_zero1 = {0.0f, 0.0f, 0.0f};
static inline void puni_exit_swset(s32 idx, s32 val, Vec* pos) {
    u8 yh, xh;
    s32 off;
    s32 x;
    s32 y;
    s32 z;
    off = (idx - 1) * 7;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    xh = ((x & 0xFF00) >> 8) & 0xFFu;
    yh = (y & 0xFF00) >> 8;
    _swByteSet(off, val);
    _swByteSet(off + 1, x & 0xFF);
    _swByteSet(off + 2, xh);
    _swByteSet(off + 3, y & 0xFF);
    _swByteSet(off + 4, yh);
    _swByteSet(off + 5, z & 0xFF);
    _swByteSet(off + 6, (z & 0xFF00) >> 8);
}
#pragma push
#pragma opt_dead_assignments off
#pragma opt_lifetimes off
static const Vec puni_fall_dir;
static const char str_00005818[] = "mri_00";
// FAKE: whole-function asm (brute-force pass)
asm s32 evt_puni_exit(EventEntry* event, BOOL isFirstCall) {
    nofralloc
    stwu r1,-176(r1)
    mflr r0
    stw r0,180(r1)
    stfd f31,160(r1)
    psq_st f31,168(r1),0,0
    stfd f30,144(r1)
    psq_st f30,152(r1),0,0
    stfd f29,128(r1)
    psq_st f29,136(r1),0,0
    stfd f28,112(r1)
    psq_st f28,120(r1),0,0
    stfd f27,96(r1)
    psq_st f27,104(r1),0,0
    stmw r22,56(r1)
    mr r23,r3
    lwz r22,24(r3)
    lwz r4,0(r22)
    bl evtGetValue
    lwz r4,4(r22)
    mr r28,r3
    mr r3,r23
    bl evtGetValue
    lwz r4,8(r22)
    mr r3,r23
    bl evtGetValue
    lwz r4,12(r22)
    mr r27,r3
    mr r3,r23
    bl evtGetValue
    lis r4,Punigp@ha
    cmpwi r28,2
    addi r5,r4,Punigp@l
    li r0,5
    lwz r4,0(r5)
    mr r29,r3
    stw r0,1084(r4)
    bne L_13098
    lwz r3,0(r5)
    cmpwi r27,7
    lwz r0,804(r3)
    clrrwi r0,r0,4
    stw r0,804(r3)
    beq L_13098
    bge L_1303c
    cmpwi r27,2
    beq L_13060
    blt L_13098
    cmpwi r27,6
    bge L_1304c
    b L_13098
L_1303c:
    cmpwi r27,9
    beq L_13088
    bge L_13098
    b L_13074
L_1304c:
    lwz r3,0(r5)
    lwz r0,804(r3)
    ori r0,r0,1
    stw r0,804(r3)
    b L_13098
L_13060:
    lwz r3,0(r5)
    lwz r0,804(r3)
    ori r0,r0,2
    stw r0,804(r3)
    b L_13098
L_13074:
    lwz r3,0(r5)
    lwz r0,804(r3)
    ori r0,r0,4
    stw r0,804(r3)
    b L_13098
L_13088:
    lwz r3,0(r5)
    lwz r0,804(r3)
    ori r0,r0,8
    stw r0,804(r3)
L_13098:
    cmplwi r29,0
    bne L_130bc
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,804(r3)
    ori r0,r0,16
    stw r0,804(r3)
    b L_130d4
L_130bc:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,804(r3)
    rlwinm r0,r0,0,28,26
    stw r0,804(r3)
L_130d4:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lwz r0,804(r3)
    rlwinm. r0,r0,0,28,28
    bne L_1323c
    bl bero_get_BeroSX
    fmr f31,f1
    bl bero_get_BeroSY
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f4,812(r3)
    lfs f2,816(r3)
    fsubs f3,f1,f4
    fsubs f0,f1,f2
    fabs f3,f3
    fabs f0,f0
    frsp f3,f3
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_13134
    fmr f3,f0
    fmr f4,f2
L_13134:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f2,820(r3)
    fsubs f0,f1,f2
    fabs f0,f0
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_13160
    fmr f3,f0
    fmr f4,f2
L_13160:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f2,824(r3)
    fsubs f0,f1,f2
    fabs f0,f0
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_13188
    fmr f4,f2
L_13188:
    fmr f30,f4
    bl bero_get_BeroSZ
    fmr f29,f1
    bl bero_get_BeroEX
    fmr f28,f1
    bl bero_get_BeroEY
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f4,812(r3)
    lfs f2,816(r3)
    fsubs f3,f1,f4
    fsubs f0,f1,f2
    fabs f3,f3
    fabs f0,f0
    frsp f3,f3
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_131dc
    fmr f3,f0
    fmr f4,f2
L_131dc:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f2,820(r3)
    fsubs f0,f1,f2
    fabs f0,f0
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_13208
    fmr f3,f0
    fmr f4,f2
L_13208:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f2,824(r3)
    fsubs f0,f1,f2
    fabs f0,f0
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_13230
    fmr f4,f2
L_13230:
    fmr f27,f4
    bl bero_get_BeroEZ
    b L_132f8
L_1323c:
    bl bero_get_BeroSX
    fmr f31,f1
    bl bero_get_BeroSY
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f29,812(r3)
    lfs f2,816(r3)
    fsubs f3,f1,f29
    fsubs f0,f1,f2
    fabs f3,f3
    fabs f0,f0
    frsp f3,f3
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_13284
    fmr f3,f0
    fmr f29,f2
L_13284:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f2,820(r3)
    fsubs f0,f1,f2
    fabs f0,f0
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_132b0
    fmr f3,f0
    fmr f29,f2
L_132b0:
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lwz r3,0(r3)
    lfs f2,824(r3)
    fsubs f0,f1,f2
    fabs f0,f0
    frsp f0,f0
    fcmpo cr0,f3,f0
    ble L_132d8
    fmr f29,f2
L_132d8:
    fmr f30,f29
    bl bero_get_BeroSZ
    lis r3,(puni_fall_dir-520)@ha
    fmr f27,f29
    fmr f29,f1
    lfs f0,(puni_fall_dir-520)@l(r3)
    fmr f28,f31
    fadds f29,f29,f0
L_132f8:
    lis r4,Punigp@ha
    lis r3,(puni_fall_dir-556)@ha
    addi r5,r4,Punigp@l
    li r0,2
    lwz r4,0(r5)
    cmplwi r29,0
    lfs f0,(puni_fall_dir-556)@l(r3)
    stw r0,1148(r4)
    lwz r3,0(r5)
    stfs f31,1152(r3)
    lwz r3,0(r5)
    stfs f30,1156(r3)
    lwz r3,0(r5)
    stfs f29,1160(r3)
    lwz r3,0(r5)
    stfs f0,1200(r3)
    lwz r3,0(r5)
    stfs f28,1164(r3)
    lwz r3,0(r5)
    stfs f27,1168(r3)
    lwz r3,0(r5)
    stfs f1,1172(r3)
    lwz r3,0(r5)
    stfs f0,1204(r3)
    beq L_13374
    lis r4,str_00005818@ha
    mr r3,r29
    addi r4,r4,str_00005818@l
    bl strcmp
    mr r28,r3
    b L_13378
L_13374:
    li r28,1
L_13378:
    lis r3,Punidat@ha
    li r31,1
    addi r3,r3,Punidat@l
    lwz r3,0(r3)
    addi r30,r3,1448
L_1338c:
    lwz r3,4(r30)
    rlwinm. r0,r3,0,21,21
    beq L_13580
    rlwinm. r0,r3,0,8,8
    bne L_13580
    rlwinm. r0,r3,0,16,16
    beq L_13488
    cmplwi r29,0
    bne L_133bc
    oris r0,r3,16384
    stw r0,4(r30)
    b L_13580
L_133bc:
    mr r3,r30
    bl puniHagurePos
    lwz r0,300(r30)
    lis r3,Punigp@ha
    lwz r4,304(r30)
    addi r3,r3,Punigp@l
    stw r0,20(r1)
    lwz r0,308(r30)
    stw r4,24(r1)
    lfs f0,20(r1)
    lfs f1,24(r1)
    fctiwz f2,f0
    stw r0,28(r1)
    fctiwz f1,f1
    lha r4,278(r30)
    lfs f0,28(r1)
    stfd f2,32(r1)
    fctiwz f0,f0
    addi r0,r4,-1
    stfd f1,40(r1)
    mulli r27,r0,7
    lwz r3,0(r3)
    stfd f0,48(r1)
    lwz r0,808(r3)
    mr r3,r27
    lwz r24,36(r1)
    lwz r25,44(r1)
    clrlwi r4,r0,24
    lwz r26,52(r1)
    rlwinm r23,r24,24,24,31
    rlwinm r22,r25,24,24,31
    bl _swByteSet
    clrlwi r4,r24,24
    addi r3,r27,1
    bl _swByteSet
    mr r4,r23
    addi r3,r27,2
    bl _swByteSet
    clrlwi r4,r25,24
    addi r3,r27,3
    bl _swByteSet
    mr r4,r22
    addi r3,r27,4
    bl _swByteSet
    clrlwi r4,r26,24
    addi r3,r27,5
    bl _swByteSet
    rlwinm r4,r26,24,24,31
    addi r3,r27,6
    bl _swByteSet
    b L_13580
L_13488:
    lis r4,(puni_fall_dir+1340)@ha
    lha r3,278(r30)
    addi r6,r4,(puni_fall_dir+1340)@l
    lwz r5,0(r6)
    addi r0,r3,-1
    lwz r3,4(r6)
    mulli r27,r0,7
    stw r5,20(r1)
    li r4,0
    lwz r0,8(r6)
    stw r3,24(r1)
    mr r3,r27
    lfs f0,20(r1)
    lfs f1,24(r1)
    fctiwz f2,f0
    stw r0,28(r1)
    fctiwz f1,f1
    lfs f0,28(r1)
    stfd f2,48(r1)
    fctiwz f0,f0
    stfd f1,40(r1)
    lwz r26,52(r1)
    stfd f0,32(r1)
    lwz r25,44(r1)
    rlwinm r22,r26,24,24,31
    lwz r24,36(r1)
    rlwinm r23,r25,24,24,31
    bl _swByteSet
    clrlwi r4,r26,24
    addi r3,r27,1
    bl _swByteSet
    mr r4,r22
    addi r3,r27,2
    bl _swByteSet
    clrlwi r4,r25,24
    addi r3,r27,3
    bl _swByteSet
    mr r4,r23
    addi r3,r27,4
    bl _swByteSet
    clrlwi r4,r24,24
    addi r3,r27,5
    bl _swByteSet
    rlwinm r4,r24,24,24,31
    addi r3,r27,6
    bl _swByteSet
    mr r3,r30
    bl PuniDokuritsu
    cmpwi r28,0
    bne L_13568
    li r3,14
    li r0,0
    sth r3,12(r30)
    sth r0,276(r30)
    sth r0,284(r30)
    b L_13580
L_13568:
    li r0,26
    li r3,0
    sth r0,12(r30)
    li r0,2
    sth r3,276(r30)
    sth r0,284(r30)
L_13580:
    addi r31,r31,1
    addi r30,r30,1448
    cmpwi r31,102
    ble L_1338c
    cmplwi r29,0
    beq L_13674
    lis r4,str_00005818@ha
    mr r3,r29
    addi r4,r4,str_00005818@l
    bl strcmp
    cmpwi r3,0
    bne L_13674
    lis r3,(puni_fall_dir+1352)@ha
    li r27,1
    addi r28,r3,(puni_fall_dir+1352)@l
L_135bc:
    lwz r4,0(r28)
    addi r0,r27,-1
    lwz r3,4(r28)
    mulli r29,r0,7
    stw r4,8(r1)
    li r4,0
    lwz r0,8(r28)
    stw r3,12(r1)
    mr r3,r29
    lfs f0,8(r1)
    lfs f1,12(r1)
    fctiwz f2,f0
    stw r0,16(r1)
    fctiwz f1,f1
    lfs f0,16(r1)
    stfd f2,48(r1)
    fctiwz f0,f0
    stfd f1,40(r1)
    lwz r26,52(r1)
    stfd f0,32(r1)
    lwz r25,44(r1)
    rlwinm r22,r26,24,24,31
    lwz r24,36(r1)
    rlwinm r23,r25,24,24,31
    bl _swByteSet
    clrlwi r4,r26,24
    addi r3,r29,1
    bl _swByteSet
    mr r4,r22
    addi r3,r29,2
    bl _swByteSet
    clrlwi r4,r25,24
    addi r3,r29,3
    bl _swByteSet
    mr r4,r23
    addi r3,r29,4
    bl _swByteSet
    clrlwi r4,r24,24
    addi r3,r29,5
    bl _swByteSet
    rlwinm r4,r24,24,24,31
    addi r3,r29,6
    bl _swByteSet
    addi r27,r27,1
    cmpwi r27,102
    ble L_135bc
L_13674:
    li r3,2
    psq_l f31,168(r1),0,0
    lfd f31,160(r1)
    psq_l f30,152(r1),0,0
    lfd f30,144(r1)
    psq_l f29,136(r1),0,0
    lfd f29,128(r1)
    psq_l f28,120(r1),0,0
    lfd f28,112(r1)
    psq_l f27,104(r1),0,0
    lfd f27,96(r1)
    lmw r22,56(r1)
    lwz r0,180(r1)
    mtlr r0
    addi r1,r1,176
    blr
}
#pragma pop

USER_FUNC(evt_puni_init_puni) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 type = evtGetValue(event, args[1]);
    PuniData* p = &Punidat[idx];
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);
    s32 chk = evtGetValue(event, args[5]);

    if (idx == 1) {
        if (chk != 0 && swGet(0xB3C) == 0) {
            return EVT_RETURN_DONE;
        }
        if (chk != 0 && swGet(0xB14) != 0) {
            return EVT_RETURN_DONE;
        }
        *(PuniData**)((u8*)Punigp + 0x364) = p;
        p->unk4 |= 0x20;
    } else if (idx == 2) {
        if (chk != 0 && swGet(0xB3D) == 0) {
            return EVT_RETURN_DONE;
        }
        *(PuniData**)((u8*)Punigp + 0x368) = p;
        p->unk4 |= 0x40;
    } else if (idx == 4) {
        if (chk != 0 && swGet(0xB3F) == 0) {
            return EVT_RETURN_DONE;
        }
        *(PuniData**)((u8*)Punigp + 0x370) = p;
        p->unk4 |= 0x100;
    } else if (idx == 3) {
        if (chk != 0 && swGet(0xB3E) == 0) {
            return EVT_RETURN_DONE;
        }
        *(PuniData**)((u8*)Punigp + 0x36C) = p;
        p->unk4 |= 0x80;
    } else {
        if (chk != 0 && swByteGet(0x28B) + 5 <= idx) {
            return EVT_RETURN_DONE;
        }
        p->unk4 |= 8;
    }
    p->unkC = type;
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
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_init_teki) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 type = evtGetValue(event, args[1]);
    PuniData* p = &Punidat[idx];
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);

    p->unk4 |= 0x10;
    p->unkC = type;
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
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_position) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    evtSetValue(event, args[1], (s32)p->pos.x);
    evtSetValue(event, args[2], (s32)p->pos.y);
    evtSetValue(event, args[3], (s32)p->pos.z);
    return EVT_RETURN_DONE;
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



USER_FUNC(evt_puni_get_dir) {
    s32* args = event->args;
    evtSetValue(event, args[1], (s32)Punidat[evtGetValue(event, args[0])].dir);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_dir) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    p->dir = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_anim) {
    s32* args = event->args;
    evtSetValue(event, args[1], Punidat[evtGetValue(event, args[0])].anim);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_anim) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    p->anim = evtGetValue(event, args[1]);
    p->unk11E = 1000;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_korokoro) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];

    switch (p->anim) {
        case 5:
            if (isFirstCall) {
                if (p->unk4 & 8) {
                    p->unk188 = float_8_mri_000257c0[0];
                } else {
                    p->unk148 = float_8_mri_000257c0[0];
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

typedef struct PuniMoveView {
    u8 pad[0x1F8];
    Vec a;
    Vec b;
} PuniMoveView;
extern f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
extern f32 sysFrame2SecFloat(f32 frame);
extern f32 sysMsec2FrameFloat(f32 msec);
USER_FUNC(evt_puni_move_position) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    f32 x = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    s32 frames = evtGetValue(event, args[3]);
    u32 t;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        p->unk1F8 = p->pos;
        *(f32*)((u8*)p + 0x204) = x;
        *(f32*)((u8*)p + 0x208) = p->pos.y;
        *(f32*)((u8*)p + 0x20C) = z;
    }
    if ((s32)(t = (((u32)gp->renderTime - (u32)event->savedTime) / (*(u32*)0x800000F8 / 4 / 1000))) < frames) {
        p->pos.x = intplGetValue(0, t, frames, p->unk1F8.x, *(f32*)((u8*)p + 0x204));
        p->pos.z = intplGetValue(0, t, frames, p->unk1F8.z, *(f32*)((u8*)p + 0x20C));
        p->unk138 = p->pos;
        return EVT_RETURN_BLOCK;
    }
    p->pos = *(Vec*)((u8*)p + 0x204);
    p->unk138 = p->pos;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_move_position2) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    PuniMoveView* v = (PuniMoveView*)p;
    f32 x = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    f32 speed = evtGetFloat(event, args[3]);
    f32 dist;
    s32 t;
    Vec dir;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        v->a = p->pos;
        v->b.x = x;
        v->b.y = p->pos.y;
        v->b.z = z;
    }
    speed = sysFrame2SecFloat(speed);
    dist = PSVECDistance(&v->a, &v->b);
    t = (s32)(0.5f + sysMsec2FrameFloat((s32)(((u32)gp->renderTime - (u32)event->savedTime) / (*(u32*)0x800000F8 / 4 / 1000))));
    PSVECSubtract(&v->b, &v->a, &dir);
    PSVECNormalize(&dir, &dir);
    if (t < (s32)(dist / speed)) {
        PSVECScale(&dir, &dir, speed * t);
        PSVECAdd(&v->a, &dir, &p->pos);
        return EVT_RETURN_BLOCK;
    }
    p->pos = v->b;
    p->unk138 = p->pos;
    return EVT_RETURN_DONE;
}

typedef struct PuniJumpView {
    u8 pad[0x1C8];
    u64 time;
    u8 pad2[0x1EC - 0x1D0];
    f32 grav;
    f32 c;
    u8 pad3[4];
    Vec a;
} PuniJumpView;

USER_FUNC(evt_puni_jump_position) {
    s32* args = event->args;
    PuniData* p = &Punidat[evtGetValue(event, args[0])];
    PuniJumpView* v = (PuniJumpView*)p;
    f32 x = evtGetValue(event, args[1]);
    f32 y = evtGetValue(event, args[2]);
    f32 z = evtGetValue(event, args[3]);
    s32 frames = evtGetValue(event, args[4]);
    f32 h = evtGetValue(event, args[5]);
    s32 t;
    f32 r;

    if (isFirstCall) {
        v->time = gp->renderTime;
        v->a = p->pos;
        v->grav = -4.0f * h;
        v->c = (y - v->a.y) - v->grav;
        psndSFXOn_3D("SFX_STG2_PUNI_JUMP1", &p->pos);
    }
    t = ((u32)gp->renderTime - (u32)v->time) / ((*(u32*)0x800000F8 / 4) / 1000);
    if (t < frames) {
        r = (f32)t / (f32)frames;
        r = (f32)t / (f32)frames;
        p->pos.x = intplGetValue(0, (s32)t, frames, v->a.x, x);
        p->pos.z = intplGetValue(0, (s32)t, frames, v->a.z, z);
        p->pos.y = r * (v->grav * r + v->c) + v->a.y;
        return EVT_RETURN_BLOCK;
    }
    p->pos.x = x;
    p->pos.y = y;
    p->pos.z = z;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_mode) {
    s32* args = event->args;
    evtSetValue(event, args[1], Punidat[evtGetValue(event, args[0])].unkC);
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

USER_FUNC(evt_puni_setsudan) {
    PuniData* p = &Punidat[evtGetValue(event, event->args[0])];
    if (p->unk4 & 0x400) {
        PuniDokuritsu(p);
        puniDeleteEffect(p);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_get_flag) {
    s32* args = event->args;
    evtSetValue(event, args[1], Punidat[evtGetValue(event, args[0])].unk4);
    return EVT_RETURN_DONE;
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

static inline void puniswGetindex_inl(s32 base, s32 idx, s32* val, Vec* pos) {
    u8 b6, b5, b4, b3, b2, b1, b0;
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

USER_FUNC(evt_puni_get_lsw_index) {
    s32* args = event->args;
    s32 base = args[0];
    s32 idx = evtGetValue(event, args[1]);
    s32 val;
    Vec pos;
    base += idx * 7;
    puniswGetindex_inl(base, 0, &val, &pos);
    evtSetValue(event, args[2], val);
    evtSetValue(event, args[3], (s32)pos.x);
    evtSetValue(event, args[4], (s32)pos.y);
    evtSetValue(event, args[5], (s32)pos.z);
    return EVT_RETURN_DONE;
}

#pragma push
#pragma opt_dead_assignments off
static const Vec puni_fall_dir;
// FAKE: whole-function asm (brute-force pass)
asm s32 evt_puni_set_lsw_index(EventEntry* event, BOOL isFirstCall) {
    nofralloc
    stwu r1,-112(r1)
    mflr r0
    stw r0,116(r1)
    stfd f31,96(r1)
    psq_st f31,104(r1),0,0
    stfd f30,80(r1)
    psq_st f30,88(r1),0,0
    stmw r26,56(r1)
    mr r28,r3
    lwz r26,24(r3)
    lwz r27,0(r26)
    lwz r4,4(r26)
    bl evtGetValue
    lwz r4,8(r26)
    mr r30,r3
    mr r3,r28
    bl evtGetValue
    lwz r4,12(r26)
    mr r31,r3
    mr r3,r28
    bl evtGetValue
    xoris r3,r3,32768
    lis r0,17200
    lis r4,(puni_fall_dir-580)@ha
    stw r3,12(r1)
    addi r5,r4,(puni_fall_dir-580)@l
    lwz r4,16(r26)
    stw r0,8(r1)
    mr r3,r28
    lfd f1,0(r5)
    lfd f0,8(r1)
    fsubs f31,f0,f1
    bl evtGetValue
    xoris r3,r3,32768
    lis r0,17200
    lis r4,(puni_fall_dir-580)@ha
    stw r3,20(r1)
    addi r5,r4,(puni_fall_dir-580)@l
    lwz r4,20(r26)
    stw r0,16(r1)
    mr r3,r28
    lfd f1,0(r5)
    lfd f0,16(r1)
    fsubs f30,f0,f1
    bl evtGetValue
    xoris r3,r3,32768
    lis r0,17200
    stw r0,24(r1)
    lis r4,(puni_fall_dir-580)@ha
    fctiwz f1,f31
    lfd f3,(puni_fall_dir-580)@l(r4)
    stw r3,28(r1)
    fctiwz f0,f30
    mulli r0,r30,7
    clrlwi r4,r31,24
    stfd f1,32(r1)
    lfd f2,24(r1)
    add r26,r27,r0
    stfd f0,40(r1)
    addis r3,r26,2289
    fsubs f1,f2,f3
    lwz r29,36(r1)
    lwz r31,44(r1)
    addi r3,r3,-11904
    rlwinm r28,r29,24,24,31
    fctiwz f0,f1
    rlwinm r27,r31,24,24,31
    stfd f0,48(r1)
    lwz r30,52(r1)
    bl _swByteSet
    addis r3,r26,2289
    clrlwi r4,r29,24
    addi r3,r3,-11903
    bl _swByteSet
    addis r3,r26,2289
    mr r4,r28
    addi r3,r3,-11902
    bl _swByteSet
    addis r3,r26,2289
    clrlwi r4,r31,24
    addi r3,r3,-11901
    bl _swByteSet
    addis r3,r26,2289
    mr r4,r27
    addi r3,r3,-11900
    bl _swByteSet
    addis r3,r26,2289
    clrlwi r4,r30,24
    addi r3,r3,-11899
    bl _swByteSet
    addis r3,r26,2289
    rlwinm r4,r30,24,24,31
    addi r3,r3,-11898
    bl _swByteSet
    li r3,2
    psq_l f31,104(r1),0,0
    lfd f31,96(r1)
    psq_l f30,88(r1),0,0
    lfd f30,80(r1)
    lmw r26,56(r1)
    lwz r0,116(r1)
    mtlr r0
    addi r1,r1,112
    blr
}
#pragma pop

USER_FUNC(evt_puni_get_trap_index) {
    s32* args = event->args;
    s32 v;
    puniswTrapGetindex(evtGetValue(event, args[0]), &v);
    evtSetValue(event, args[1], v);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_trap_index) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 val = evtGetValue(event, args[1]);
    puniswTrapSetindex(idx, &val);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_set_ymode) {
    Punigp->ymode = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_all_fall_check) {
    puniModeChangeFallCheck();
    return EVT_RETURN_DONE;
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

USER_FUNC(evt_puni_count_area) {
    s32* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    f32 r = evtGetValue(event, args[3]);
    s32 count;
    s32 i;
    for (i = 1, count = 0; i < 103; i++) {
        PuniData* p = &Punidat[i];
        if ((p->unk4 & 0x400) && p->unkC != 16) {
            if (!(10.0 < __fabs(y - p->pos.y)) && !(r < __fabs(x - p->pos.x)) && !(r < __fabs(z - p->pos.z))) {
                count++;
            }
        }
    }
    evtSetValue(event, args[4], count);
    return EVT_RETURN_DONE;
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

USER_FUNC(evt_puni_fade_onoff) {
    puniFadeOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_attack_on) {
    Punigp->unk43C = 3;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_puninum_onoff) {
    Punigp->showPuniCounter = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_puninum_alpha) {
    Punigp->puniCounterAlpha = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_puni_winddisable_onoff) {
    Punigp->unk4CC = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
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

static const Vec puni_save_zero = { 0.0f, 0.0f, 0.0f };
#pragma push
#pragma opt_dead_assignments off
static const Vec puni_fall_dir;
// FAKE: whole-function asm (brute-force pass)
asm s32 evt_puni_all_save(EventEntry* event, BOOL isFirstCall) {
    nofralloc
    stwu r1,-80(r1)
    mflr r0
    lis r3,Punidat@ha
    stw r0,84(r1)
    addi r3,r3,Punidat@l
    stmw r24,48(r1)
    li r30,1
    lwz r3,0(r3)
    addi r29,r3,1448
L_1556c:
    lwz r3,4(r29)
    rlwinm. r0,r3,0,21,21
    beq L_1570c
    rlwinm. r0,r3,0,8,8
    bne L_1570c
    rlwinm. r0,r3,0,16,16
    beq L_15654
    mr r3,r29
    bl puniHagurePos
    lwz r0,300(r29)
    lis r3,Punigp@ha
    lwz r4,304(r29)
    addi r3,r3,Punigp@l
    stw r0,8(r1)
    lwz r0,308(r29)
    stw r4,12(r1)
    lfs f0,8(r1)
    lfs f1,12(r1)
    fctiwz f2,f0
    stw r0,16(r1)
    fctiwz f1,f1
    lha r4,278(r29)
    lfs f0,16(r1)
    stfd f2,24(r1)
    fctiwz f0,f0
    addi r0,r4,-1
    stfd f1,32(r1)
    mulli r24,r0,7
    lwz r3,0(r3)
    stfd f0,40(r1)
    lwz r0,808(r3)
    mr r3,r24
    lwz r27,28(r1)
    lwz r28,36(r1)
    clrlwi r4,r0,24
    lwz r31,44(r1)
    rlwinm r26,r27,24,24,31
    rlwinm r25,r28,24,24,31
    bl _swByteSet
    clrlwi r4,r27,24
    addi r3,r24,1
    bl _swByteSet
    mr r4,r26
    addi r3,r24,2
    bl _swByteSet
    clrlwi r4,r28,24
    addi r3,r24,3
    bl _swByteSet
    mr r4,r25
    addi r3,r24,4
    bl _swByteSet
    clrlwi r4,r31,24
    addi r3,r24,5
    bl _swByteSet
    rlwinm r4,r31,24,24,31
    addi r3,r24,6
    bl _swByteSet
    b L_1570c
L_15654:
    lis r4,(puni_fall_dir+1388)@ha
    lha r3,278(r29)
    addi r6,r4,(puni_fall_dir+1388)@l
    lwz r5,0(r6)
    addi r0,r3,-1
    lwz r3,4(r6)
    mulli r31,r0,7
    stw r5,8(r1)
    li r4,0
    lwz r0,8(r6)
    stw r3,12(r1)
    mr r3,r31
    lfs f0,8(r1)
    lfs f1,12(r1)
    fctiwz f2,f0
    stw r0,16(r1)
    fctiwz f1,f1
    lfs f0,16(r1)
    stfd f2,40(r1)
    fctiwz f0,f0
    stfd f1,32(r1)
    lwz r26,44(r1)
    stfd f0,24(r1)
    lwz r28,36(r1)
    rlwinm r25,r26,24,24,31
    lwz r27,28(r1)
    rlwinm r24,r28,24,24,31
    bl _swByteSet
    clrlwi r4,r26,24
    addi r3,r31,1
    bl _swByteSet
    mr r4,r25
    addi r3,r31,2
    bl _swByteSet
    clrlwi r4,r28,24
    addi r3,r31,3
    bl _swByteSet
    mr r4,r24
    addi r3,r31,4
    bl _swByteSet
    clrlwi r4,r27,24
    addi r3,r31,5
    bl _swByteSet
    rlwinm r4,r27,24,24,31
    addi r3,r31,6
    bl _swByteSet
L_1570c:
    addi r30,r30,1
    addi r29,r29,1448
    cmpwi r30,102
    ble L_1556c
    lmw r24,48(r1)
    li r3,2
    lwz r0,84(r1)
    mtlr r0
    addi r1,r1,80
    blr
}
#pragma pop

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

USER_FUNC(evt_target_set_position) {
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);
    PuniTarget* t = &Punigp->targets[i];
    t->pos.x = evtGetValue(event, args[1]);
    t->pos.y = evtGetValue(event, args[2]);
    t->pos.z = evtGetValue(event, args[3]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_target_set_soko) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    PuniTarget* t = &Punigp->targets[idx];
    t->hit = hitNameToPtr((const char*)evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

const char* npcGetTribeName(const char** name) {
    return *name;
}

#define PIDERS_Y(n)                                           if (50.0 >= __fabs(v.y - Punigp->posY[n])) {                  found = TRUE;                                              v.y = Punigp->posY[n];                                 }

static const Vec puni_fall_dir;
static const char str_0000583C[] = "パイダース";
// FAKE: whole-function asm (brute-force pass)
asm s32 puni_piders_check_func(EventEntry *event, BOOL isFirstCall) {
    nofralloc
    stwu r1,-48(r1)
    mflr r0
    stw r0,52(r1)
    stmw r28,32(r1)
    bl npcGetWorkPtr
    lis r4,Punigp@ha
    li r0,8
    addi r7,r4,Punigp@l
    lwz r30,4(r3)
    lwz r29,12(r3)
    li r3,40
    li r4,-6
    mtctr r0
L_1593c:
    lwz r6,0(r7)
    addi r5,r3,884
    addi r3,r3,20
    lwzx r0,r6,r5
    and r0,r0,r4
    stwx r0,r6,r5
    bdnz L_1593c
    li r28,40
    li r31,0
    b L_15ae0
L_15964:
    lwz r3,0(r29)
    clrlwi. r0,r3,31
    beq L_15ad8
    rlwinm. r0,r3,0,30,30
    beq L_15ad8
    lwz r3,40(r29)
    cmplwi r3,0
    beq L_15ad8
    lis r4,str_0000583C@ha
    lwz r3,0(r3)
    addi r4,r4,str_0000583C@l
    bl strcmp
    cmpwi r3,0
    bne L_15ad8
    lwz r0,144(r29)
    lis r3,Punigp@ha
    addi r3,r3,Punigp@l
    lis r4,(puni_fall_dir-276)@ha
    stw r0,12(r1)
    li r5,0
    lwz r3,0(r3)
    lfs f0,12(r1)
    lfs f1,812(r3)
    lwz r3,140(r29)
    fsubs f0,f0,f1
    lwz r0,148(r29)
    lfd f2,(puni_fall_dir-276)@l(r4)
    stw r3,8(r1)
    fabs f0,f0
    stw r0,16(r1)
    fcmpo cr0,f2,f0
    cror eq,gt,eq
    bne L_159f0
    li r5,1
    stfs f1,12(r1)
L_159f0:
    lis r3,Punigp@ha
    lis r4,(puni_fall_dir-276)@ha
    addi r3,r3,Punigp@l
    lfs f0,12(r1)
    lwz r3,0(r3)
    lfd f2,(puni_fall_dir-276)@l(r4)
    lfs f1,816(r3)
    fsubs f0,f0,f1
    fabs f0,f0
    fcmpo cr0,f2,f0
    cror eq,gt,eq
    bne L_15a28
    li r5,1
    stfs f1,12(r1)
L_15a28:
    lis r3,Punigp@ha
    lis r4,(puni_fall_dir-276)@ha
    addi r3,r3,Punigp@l
    lfs f0,12(r1)
    lwz r3,0(r3)
    lfd f2,(puni_fall_dir-276)@l(r4)
    lfs f1,820(r3)
    fsubs f0,f0,f1
    fabs f0,f0
    fcmpo cr0,f2,f0
    cror eq,gt,eq
    bne L_15a60
    li r5,1
    stfs f1,12(r1)
L_15a60:
    lis r3,Punigp@ha
    lis r4,(puni_fall_dir-276)@ha
    addi r3,r3,Punigp@l
    lfs f0,12(r1)
    lwz r3,0(r3)
    lfd f2,(puni_fall_dir-276)@l(r4)
    lfs f1,824(r3)
    fsubs f0,f0,f1
    fabs f0,f0
    fcmpo cr0,f2,f0
    cror eq,gt,eq
    bne L_15a98
    li r5,1
    stfs f1,12(r1)
L_15a98:
    cmpwi r5,0
    beq L_15ad4
    lis r3,Punigp@ha
    addi r5,r28,884
    lwz r0,Punigp@l(r3)
    lwz r4,8(r1)
    add r5,r0,r5
    lwz r3,12(r1)
    stw r4,4(r5)
    lwz r0,16(r1)
    stw r3,8(r5)
    stw r0,12(r5)
    lwz r0,0(r5)
    ori r0,r0,5
    stw r0,0(r5)
L_15ad4:
    addi r28,r28,20
L_15ad8:
    addi r31,r31,1
    addi r29,r29,832
L_15ae0:
    cmpw r31,r30
    blt L_15964
    lmw r28,32(r1)
    li r3,2
    lwz r0,52(r1)
    mtlr r0
    addi r1,r1,48
    blr
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

extern BOOL evtShopIsActive(void);
void puniCountDisp(s32 unused, s32 packed) {
    Mtx m;
    GXColor c1 = {0xFF, 0xFF, 0xFF, 0x99};
    GXColor c2 = {0, 0, 0, 0xFF};
    GXColor c3 = {0xFF, 0xFF, 0xFF, 0xFF};
    s32 num2 = packed >> 16;
    s32 num1 = packed & 0xFFFF;
    if (evtShopIsActive()) {
        return;
    }
    c1.a = c1.a * Punigp->puniCounterAlpha / 255;
    c2.a = c2.a * Punigp->puniCounterAlpha / 255;
    c3.a = c3.a * Punigp->puniCounterAlpha / 255;
    PSMTXTrans(m, -160.0f, -180.0f, 0.0f);
    iconDispGxCol(m, 0x10, 0x203, c1);
    PSMTXTrans(m, -232.0f, -178.0f, 0.0f);
    iconDispGxCol(m, 0x10, 0x204, c2);
    PSMTXTrans(m, -160.0f, -178.0f, 0.0f);
    if (Punigp->unk448) {
        if (gp->retraceCount & 0x10) {
            iconNumberDispGx(m, num2, FALSE, c3);
        }
    } else {
        iconNumberDispGx(m, num2, FALSE, c3);
    }
    PSMTXTrans(m, -140.0f, -178.0f, 0.0f);
    iconDispGxCol(m, 0x10, 0x1D8, c3);
    PSMTXTrans(m, -90.0f, -178.0f, 0.0f);
    iconNumberDispGx(m, num1, TRUE, c3);
}

USER_FUNC(puni_disp_info_sub) {
    s32* args = event->args;
    s32 count = 0;
    s32 total;
    BOOL done;
    s32 i;
    s32 packed;
    for (i = 1; i < 103; i++) {
        if ((Punidat[i].unk4 & 0x400) && !(Punidat[i].unk4 & 0x804000) && !(Punidat[i].unk4 & 0x80)) {
            if (Punidat[i].unkC != 16 && Punidat[i].unkC != 15) {
                count++;
            }
        }
    }
    total = swGet(0xB3C);
    total += swGet(0xB3D);
    total += swGet(0xB3F);
    total += swByteGet(0x28B);
    done = FALSE;
    if (Punigp->unk328 == 9 && !swGet(0xB21)) {
        done = TRUE;
    }
    if (Punigp->unk328 == 12 && !swGet(0xB29)) {
        done = TRUE;
    }
    if (done) {
        evtSetValue(event, args[0], count);
        evtSetValue(event, args[1], 0);
        Punigp->unk448 = 0;
    } else {
        evtSetValue(event, args[0], count);
        evtSetValue(event, args[1], total - count);
        if (count == total) {
            Punigp->unk448 = 0;
        } else {
            Punigp->unk448 = 1;
        }
    }
    if (!(Punigp->systemMode & 2)) {
        count = swByteGet(0x29B);
        total = swByteGet(0x29C);
        Punigp->unk448 = 0;
    } else {
        swByteSet(0x29B, (u8)count);
        swByteSet(0x29C, (u8)total);
    }
    packed = (count << 16) | total;
    if (Punigp->showPuniCounter && total >= 10) {
        dispEntry((CameraId)8, 1000.0f, 0, (void (*)(CameraId, void*))puniCountDisp, (void*)packed);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_make_texbuf);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_sub_get_mapname);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
extern s32 mri_puni_init_dvd[];
extern s32 mri_puni_main[];
extern s32 mri_puni_position_init[];
extern s32 mri_puninum_fadein[];
extern s32 mri_puninum_fadeout[];

s32 puni_piders_check[] = {
    0x0002005B, (s32)evt_seq_wait, 0x00000002, 0x00010005,
    0x00000000, 0x0001005B, (s32)puni_piders_check_func, 0x00010009,
    0x00000001, 0x00000006, 0x00000002, 0x00000001,
};

s32 puni_disp_info[] = {
    0x0002001D, 0xF5DE0180, 0x00000076, 0x00000002,
    0x00000021, 0x00010005, 0x00000000, 0x0003005B,
    (s32)puni_disp_info_sub, 0xFE363C80, 0xFE363C81, 0x00010009,
    0x00000001, 0x00000006, 0x00000002, 0x00000001,
};

s32 mri_puninum_fadeout[] = {
    0x0001000A, 0x000004B0, 0x0005005B, (s32)evt_sub_intpl_msec_init,
    0x0000000B, 0x000000FF, 0x00000000, 0x000001F4,
    0x00010005, 0x00000000, 0x0001005B, (s32)evt_sub_intpl_msec_get_value,
    0x0002005B, (s32)evt_puni_puninum_alpha, 0xFE363C80, 0x00010009,
    0x00000001, 0x00020018, 0xFE363C81, 0x00000000,
    0x00000007, 0x00000021, 0x00000006, 0x00000002,
    0x00000001,
};

s32 mri_puninum_fadein[] = {
    0x0005005B, (s32)evt_sub_intpl_msec_init, 0x0000000B, 0x00000000,
    0x000000FF, 0x000001F4, 0x00010005, 0x00000000,
    0x0001005B, (s32)evt_sub_intpl_msec_get_value, 0x0002005B, (s32)evt_puni_puninum_alpha,
    0xFE363C80, 0x00010009, 0x00000001, 0x00020018,
    0xFE363C81, 0x00000000, 0x00000007, 0x00000021,
    0x00000006, 0x00000002, 0x00000001,
};

s32 mri_puni_position_init[] = {
    0x0002005B, (s32)evt_puni_set_systemmode, 0x00000000, 0x0000006B,
    0x0002005B, (s32)evt_puni_puninum_alpha, 0x00000000, 0x00010009,
    0x00000002, 0x0002005B, (s32)evt_bero_get_now_number, 0xFE363C8A,
    0x0005005B, (s32)evt_bero_get_info_kinddir, 0xFE363C8A, 0xFE363C80,
    0xFE363C81, 0xFE363C82, 0x0004005B, (s32)evt_bero_get_info_nextarea,
    0xFE363C8A, 0xFE363C83, 0xFE363C84, 0x00020032,
    0xFBD3E280, 0x00000000, 0x00020018, 0xFE363C80,
    0x00000002, 0x00020019, 0xFE363C83, 0x00000000,
    0x00020032, 0xFBD3E280, 0x00000001, 0x00000021,
    0x00000021, 0x00020018, 0xFBD3E280, 0x00000000,
    0x0002005B, (s32)evt_puni_puninum_alpha, 0x000000FF, 0x00000021,
    0x0000006D, 0x00010071, (s32)"\203v\203j\212\326\214W\201F\217\211\212\372\202\314\216\300\215s\222\206\221\322\202\277", 0x0002005B,
    (s32)evt_bero_exec_wait, 0x00000001, 0x00010005, 0x00000000,
    0x0002005B, (s32)evt_puni_set_systemmode, 0x00000001, 0x00010071,
    (s32)"\203v\203j\212\326\214W\201F\215\300\225W\203Z\203b\203g\221\322\202\277", 0x0002005B, (s32)evt_bero_exec_wait, 0x00000002,
    0x00010071, (s32)"\203v\203j\212\326\214W\201F\217\254\223\256\225\250\212\326\214W\217\211\212\372\211\273", 0x00010073, 0xF5DE0419,
    0x00010073, 0xF5DE041A, 0x0002005B, (s32)evt_bero_get_now_number,
    0xFE363C8A, 0x0005005B, (s32)evt_bero_get_info_kinddir, 0xFE363C8A,
    0xFE363C80, 0xFE363C81, 0xFE363C82, 0x0004005B,
    (s32)evt_bero_get_info_nextarea, 0xFE363C8A, 0xFE363C83, 0xFE363C84,
    0x00020018, 0xFE363C80, 0x00000002, 0x00020019,
    0xFE363C83, 0x00000000, 0x0001005C, (s32)mri_puninum_fadein,
    0x00000021, 0x00000021, 0x0004005B, (s32)evt_puni_setup,
    0xFE363C80, 0xFE363C81, 0xFE363C82, 0x0005005B,
    (s32)evt_toge_setup, 0xFE363C86, 0xFE363C87, 0xFE363C88,
    0xFE363C89, 0x0002005B, (s32)evt_puni_set_systemmode, 0x00000002,
    0x00010071, (s32)"\203v\203j\212\326\214W\201F\217I\227\271\221\322\202\277", 0x0002005B, (s32)evt_bero_exec_wait,
    0x00010000, 0x0002005B, (s32)evt_puni_set_systemmode, 0x00000003,
    0x00010071, (s32)"\203v\203j\212\326\214W\201F\216\237\202\314\216\300\215s\222\206\221\322\202\277", 0x0002005B, (s32)evt_bero_exec_wait,
    0x00000001, 0x00020032, 0xF5DE041A, 0xF5DE0419,
    0x0002005B, (s32)evt_bero_get_now_number, 0xFE363C8A, 0x0005005B,
    (s32)evt_bero_get_info_kinddir, 0xFE363C8A, 0xFE363C80, 0xFE363C81,
    0xFE363C82, 0x0004005B, (s32)evt_bero_get_info_nextarea, 0xFE363C8A,
    0xFE363C83, 0xFE363C84, 0x00020018, 0xFE363C80,
    0x00000001, 0x00010071, (s32)"\203v\203j\212\326\214W\201F\224\340\221\322\202\277", 0x0002005B,
    (s32)evt_bero_exec_wait, 0x10000000, 0x00010071, (s32)"\203v\203j\212\326\214W\201F\224\340\221\322\202\277\217I\202\355\202\350",
    0x0003005B, (s32)evt_bero_exec_onoff, 0x00000001, 0x10000000,
    0x00000021, 0x00020018, 0xFE363C80, 0x00000002,
    0x00020019, 0xFE363C83, 0x00000000, 0x0001005C,
    (s32)mri_puninum_fadeout, 0x00000021, 0x00000021, 0x0000006B,
    0x00010071, (s32)"\203v\203j\212\326\214W\201F\203G\203\212\203A\203`\203F\203\223\203W\222\274\221O\221\322\202\277", 0x0002005B, (s32)evt_bero_exec_wait,
    0x00000008, 0x00010071, (s32)"\203v\203j\212\326\214W\201F\203v\203j\221\260\203g\203Q\221\260SE\213\255\220\247\203I\203t", 0x0001005B,
    (s32)evt_puni_force_se_off, 0x0000006D, 0x0005005B, (s32)evt_puni_exit,
    0xFE363C80, 0xFE363C81, 0xFE363C82, 0xFE363C83,
    0x00000006, 0x00000002, 0x00000001,
};

s32 mri_puni_main[] = {
    0x00010063, 0x00000000, 0x0001005B, (s32)evt_puni_main,
    0x00000002, 0x00000001,
};

s32 mri_puni_init_dvd[] = {
    0x0003005B, (s32)evt_npc_entry, (s32)"\203v\203jsp", (s32)"c_puni",
    0x0003005B, (s32)evt_npc_set_tribe, (s32)"\203v\203jsp", (s32)"\203v\203j\221\260",
    0x0003005B, (s32)evt_npc_entry, (s32)"\203g\203Qsp", (s32)"c_toge",
    0x0003005B, (s32)evt_npc_set_tribe, (s32)"\203g\203Qsp", (s32)"\203g\203Q\221\260",
    0x0003005B, (s32)evt_npc_entry, (s32)"\203K\203C\203hsp", (s32)"c_pguide",
    0x0003005B, (s32)evt_npc_set_tribe, (s32)"\203K\203C\203hsp", (s32)"\203K\203C\203h",
    0x0003005B, (s32)evt_npc_entry, (s32)"\203K\203C\203h\226\205sp", (s32)"c_psister",
    0x0003005B, (s32)evt_npc_set_tribe, (s32)"\203K\203C\203h\226\205sp", (s32)"\203K\203C\203h\226\205",
    0x0003005B, (s32)evt_npc_entry, (s32)"\202\277\202\321\203g\203Qsp", (s32)"c_tchibi",
    0x0003005B, (s32)evt_npc_set_tribe, (s32)"\202\277\202\321\203g\203Qsp", (s32)"\202\277\202\321\203g\203Q",
    0x0003005B, (s32)evt_npc_entry, (s32)"\203\211\203C\203o\203\213sp", (s32)"c_prival",
    0x0003005B, (s32)evt_npc_set_tribe, (s32)"\203\211\203C\203o\203\213sp", (s32)"\203\211\203C\203o\203\213",
    0x0005005B, (s32)evt_npc_set_position, (s32)"\203v\203jsp", 0x00000000,
    0xFFFFFC18, 0x00000000, 0x0005005B, (s32)evt_npc_set_position,
    (s32)"\203g\203Qsp", 0x00000000, 0xFFFFFC18, 0x00000000,
    0x0005005B, (s32)evt_npc_set_position, (s32)"\203K\203C\203hsp", 0x00000000,
    0xFFFFFC18, 0x00000000, 0x0005005B, (s32)evt_npc_set_position,
    (s32)"\203K\203C\203h\226\205sp", 0x00000000, 0xFFFFFC18, 0x00000000,
    0x0005005B, (s32)evt_npc_set_position, (s32)"\202\277\202\321\203g\203Qsp", 0x00000000,
    0xFFFFFC18, 0x00000000, 0x0005005B, (s32)evt_npc_set_position,
    (s32)"\203\211\203C\203o\203\213sp", 0x00000000, 0xFFFFFC18, 0x00000000,
    0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001, (s32)"\203v\203jsp",
    0x40080020, 0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001,
    (s32)"\203g\203Qsp", 0x40080020, 0x0004005B, (s32)evt_npc_flag_onoff,
    0x00000001, (s32)"\203K\203C\203hsp", 0x40080020, 0x0004005B,
    (s32)evt_npc_flag_onoff, 0x00000001, (s32)"\203K\203C\203h\226\205sp", 0x40080020,
    0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001, (s32)"\202\277\202\321\203g\203Qsp",
    0x40080020, 0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001,
    (s32)"\203\211\203C\203o\203\213sp", 0x40080020, 0x00000002, 0x00000001,
};

s32 mri_puni_init[] = {
    0x0001005E, (s32)mri_puni_init_dvd, 0x00010022, 0xF5DE0180,
    0x00010026, 0x00000058, 0x00000002, 0x00010029,
    0x00000193, 0x00000002, 0x00010024, 0x00000190,
    0x0002005B, (s32)evt_sub_get_mapname, 0xFE363C80, 0x0002000D,
    0xFE363C80, (s32)(char*)str_00005818, 0x00000002, 0x00000021,
    0x00020032, 0xFBD3E280, 0x00000000, 0x0002005B,
    (s32)evt_bero_get_entername, 0xFE363C80, 0x0002000C, 0xFE363C80,
    (s32)"sekai_yami1", 0x00020032, 0xFBD3E280, 0x00000001,
    0x00000021, 0x0002000C, 0xFE363C80, (s32)"minnnanokoe",
    0x00020032, 0xFBD3E280, 0x00000001, 0x00000021,
    0x00020018, 0xFBD3E280, 0x00000000, 0x00000002,
    0x00000021, 0x0002002F, 0x00000076, 0x0000018F,
    0x0002005B, (s32)evt_sub_get_mapname, 0xFE363C80, 0x0002000D,
    0xFE363C80, (s32)(char*)str_00005818, 0x00000002, 0x00000021,
    0x00020018, 0xF84066C4, 0x00000001, 0x00000002,
    0x00000021, 0x0000002A, 0x00000031, 0x0001005B,
    (s32)evt_make_texbuf, 0x0005005B, (s32)evt_puni_init, 0x000000D2,
    (s32)puni_puni_init, (s32)puni_puni_main, (s32)puni_puni_dispent, 0x0001005B,
    (s32)evt_puni_set_maze, 0x0001005C, (s32)mri_puni_position_init, 0x0001005C,
    (s32)mri_puni_main, 0x00000002, 0x00000001,
};

s32 mri_puni_init_none[] = {
    0x0001005E, (s32)mri_puni_init_dvd, 0x0001005B, (s32)evt_make_texbuf,
    0x0005005B, (s32)evt_puni_init, 0x000000D2, (s32)puni_puni_init,
    (s32)puni_puni_main, (s32)puni_puni_dispent, 0x0001005B, (s32)evt_puni_set_maze,
    0x00000002, 0x00000001,
};
