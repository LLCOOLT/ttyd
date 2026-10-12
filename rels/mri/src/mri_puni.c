#include "mri_puni.h"
#include "driver/camdrv.h"
#include "memory.h"
#include <string.h>
#include "forcedata.h"

#include "driver/swdrv.h"
#include "pmario_sound.h"
#include "evt/evt_bero.h"
#include "manager/evtmgr_cmd.h"
#include "driver/punidrv.h"
#include "driver/mapdrv.h"
#include <dolphin/gx.h>
extern int rand(void);
void PuniDokuritsu(PuniData* p);
void puniMapdata_MRI_06_getidx(Vec* pos, s32* blk);
void puniMapdata_MRI_09_getidx(Vec* pos, s32* blk);
void puniMapdata_MRI_16_getidx(Vec* pos, s32* blk);
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

void puniMapPos2Blk(Vec* pos, s32* blk) {
    switch (Punigp->mapKind) {
        case 0:
            break;
        case 1:
            puniMapdata_MRI_06_getidx(pos, blk);
            break;
        case 2:
            puniMapdata_MRI_09_getidx(pos, blk);
            break;
        case 3:
            puniMapdata_MRI_16_getidx(pos, blk);
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
    if (PSVECMag(&p->vel) != 0.0f) {
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
    s32 i = 0;
    PuniData* p;

    while (TRUE) {
        if (i == 102) {
            return NULL;
        }
        if (idx == 103) {
            idx = 1;
        }
        p = &Punidat[idx];
        if ((p->unk4 & 0x400) && !(p->unk4 & 0x4000)) {
            return p;
        }
        idx++;
        i++;
    }
}

PuniData* puniSearchRandom_Teki(void) {
    s32 idx = qrnd(99) + 110;
    s32 i = 0;
    PuniData* p;

    while (TRUE) {
        if (i == 100) {
            return NULL;
        }
        if (idx == 210) {
            idx = 110;
        }
        p = &Punidat[idx];
        if ((p->unk4 & 0x400) && !(p->unk4 & 0x4000)) {
            return p;
        }
        idx++;
        i++;
    }
}

PuniData* searchMikata(PuniData* self) {
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;
    s32 i;
    PuniData* q = &Punidat[1];

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
    s32 i;
    PuniData* q = &Punidat[1];

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
    s32 i;
    PuniData* q = &Punidat[110];

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
    s32 x = pos->x;
    s32 y = pos->y;
    s32 z = pos->z;
    _swByteSet(off + 150000000, *val);
    _swByteSet(off + 150000001, x & 0xFF);
    _swByteSet(off + 150000002, (x >> 8) & 0xFF);
    _swByteSet(off + 150000003, y & 0xFF);
    _swByteSet(off + 150000004, (y >> 8) & 0xFF);
    _swByteSet(off + 150000005, z & 0xFF);
    _swByteSet(off + 150000006, (z >> 8) & 0xFF);
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
    s32 off = base + idx * 7;
    u8 b0 = _swByteGet(off + 150000000);
    u8 b1 = _swByteGet(off + 150000001);
    u8 b2 = _swByteGet(off + 150000002);
    u8 b3 = _swByteGet(off + 150000003);
    u8 b4 = _swByteGet(off + 150000004);
    u8 b5 = _swByteGet(off + 150000005);
    u8 b6 = _swByteGet(off + 150000006);
    s32 x;
    s32 y;
    s32 z;

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
    PuniTarget* t = &Punigp->targets[evtGetValue(event, args[0])];
    t->pos.x = evtGetValue(event, args[1]);
    t->pos.y = evtGetValue(event, args[2]);
    t->pos.z = evtGetValue(event, args[3]);
    return EVT_RETURN_DONE;
}

void puniAnimationInit(s16** a, s16** b) {
    PuniAnimSet* s0 = &Punigp->anim[0];
    PuniAnimSet* s1 = &Punigp->anim[1];
    s32 i;
    s32 j;
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

PuniData* searchBattle(PuniData* self, s32 start, s32 count, f32 maxDist) {
    f32 minDist = 1000000.0f;
    PuniData* found = NULL;
    s32 i;
    PuniData* q = &Punidat[start];

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
                static const Vec zero = {0.0f, 0.0f, 0.0f};
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

    for (i = 0; i < 211; i++, q++) {
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
    s32 i;

    puniLoadRenderMode();
    puniLoadVertex();
    puniLoadTexture();
    puniLoadTev();
    if (!_swGet(3)) {
        puniDraw();
    } else {
        for (i = 0; i < puniGetPoseNum(); i++) {
            PunidrvPose* pose = &puniGetPosePtr()[i];
            info.tevStage = 1;
            info.texCoord = 1;
            info.texMap = 1;
            info.field_0x18 = 0;
            info.mtx = *pose->mtx;
            envSetYami(&info);
            GXSetNumTexGens(info.texMap);
            GXSetNumTevStages(info.texMap);
            GXSetNumIndStages(info.field_0x18);
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

USER_FUNC(evt_puni_all_fall_check) {
    PuniData* p = &Punidat[1];
    s32 i;
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

void puniPositionRecover(PuniData* p) {
    p->pos = Punigp->unk344;
    p->pos.x += randf(0.0f, 2.0f) - 1.0f;
    p->pos.z += randf(0.0f, 2.0f) - 1.0f;
    p->unk138 = p->pos;
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
