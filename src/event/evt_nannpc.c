// FAKE: whole-unit ASM-STOPGAP (C3b 2026-10-18): asm_inline.py + C3b aifix/rodatagen (.rodata/.sdata2/.sdata in target order, mt$544 as file-scope mt_544), unused inlines under NONMATCHING, force_active. C kept under NONMATCHING. See docs/FAKES.md.
#include "evt/evt_cmd.h"
#include "driver/dispdrv.h"
#include "driver/hitdrv.h"
#include "mario/mariost.h"
#include "manager/evtmgr_cmd.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>
#pragma force_active on
extern void __div2u();
__declspec(section ".rodata") const u32 vec3_802f2ff8[3] = {0x00000000, 0xC47A0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802f3004[3] = {0x00000000, 0xC47A0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802f3010[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802f301c[3] = {0x00000000, 0xC47A0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802f3028[3] = {0x00000000, 0xC47A0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802f3034[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 double_to_int_802f3040[2] = {0x43300000, 0x80000000};
__declspec(section ".sdata2") const u32 dat_8041c568[1] = {0xFFFFFFFF};
__declspec(section ".sdata2") const u32 dat_8041c56c[1] = {0xFFFFFFFF};
__declspec(section ".sdata2") const u32 dat_8041c570[1] = {0xFFFFFFFF};
__declspec(section ".sdata2") const u32 str_8041C574[2] = {0x25303678, 0x00000000};
__declspec(section ".sdata2") const u32 float_neg4_8041c57c[1] = {0xC0800000};
__declspec(section ".sdata2") const u32 float_1000_8041c580[1] = {0x447A0000};
__declspec(section ".sdata2") const u32 float_32_8041c584[1] = {0x42000000};
__declspec(section ".sdata2") const u32 float_0_8041c588[1] = {0x00000000};
__declspec(section ".sdata2") const u32 float_neg1000_8041c58c[1] = {0xC47A0000};
__declspec(section ".sdata2") const u32 float_1_8041c590[1] = {0x3F800000};
__declspec(section ".sdata2") const u32 float_0p5_8041c594[1] = {0x3F000000};
__declspec(section ".sdata2") const u32 float_0p8_8041c598[1] = {0x3F4CCCCD};
__declspec(section ".sdata2") const u32 float_10_8041c59c[1] = {0x41200000};
__declspec(section ".sdata2") const u32 float_5_8041c5a0[1] = {0x40A00000};
__declspec(section ".sdata2") const u32 float_0p6_8041c5a4[1] = {0x3F19999A};
__declspec(section ".sdata2") const u32 float_0p1_8041c5a8[1] = {0x3DCCCCCD};
__declspec(section ".sdata2") const u32 gap_sdata2_44[1] = {0x00000000};
__declspec(section ".sdata") u32 mt_544[12] = {0x41200000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41200000, 0x00000000, 0x3DCCCCCD, 0x00000000, 0x00000000, 0x41200000, 0x00000000};
__declspec(section ".sdata") u32 gap_sdata_30[6] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};

extern int sprintf(char* str, const char* format, ...);
void qqsort(void* array, s32 num, s32 size, s32 (*cmp)(void*, void*));

typedef struct ExtPose {
    u32 flags;   // 0x0
    f32 rot;     // 0x4
    f32 shadowY; // 0x8
    Mtx* mtx;    // 0xC
    s32 poseId;  // 0x10
    u8 pad[0xC];
} ExtPose;

ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
void extPoseDraw(s32 idx);
void extLoadShadowMtx(Mtx mtx);
void extLoadShadowRenderMode(void);
void extLoadShadowVertex(void);
void extLoadShadowTev(void);
void extDrawShadow(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTextureExit(void);
void extLoadRenderMode(void);
void extLoadTev(void);
void extDraw(void);
void extEntry(s32 count, void* name, void* initf, void* mainf, void* dispf);

typedef struct NanNPC {
    s8 name[0x10];    // 0x0
    ExtPose* pose;    // 0x10
    u16 flags;        // 0x14
    u16 field_16;     // 0x16
    Vec pos;          // 0x18
    Vec hosei;        // 0x24
    Vec field_30;     // 0x30
    Vec move;         // 0x3C
    f32 sizeX;        // 0x48
    f32 sizeY;        // 0x4C
    OSTime startTime; // 0x50
    s16* animtbl;     // 0x58
    s16 animnum;      // 0x5C
    s16 anim;         // 0x5E
    f32 dir;          // 0x60
    void (*func)(struct NanNPC*); // 0x64
    s32 ipos[3];      // 0x68
    u8 pad_74[0x14];  // 0x74
    Vec startPos;     // 0x88
    u8 pad_94[0x10];  // 0x94
    s32 work[4];      // 0xA4
    HitEntry* hit0;   // 0xB4
    HitEntry* hit1;   // 0xB8
    GXColor color;    // 0xBC
} NanNPC;

typedef struct NanNPCSort {
    s32 idx;
    f32 z;
} NanNPCSort;

typedef struct NanNPCWork {
    NanNPC* npc;       // 0x0
    NanNPCSort* sort;  // 0x4
    s16* tbl;          // 0x8
    s32 num;           // 0xC
    u32 flags;         // 0x10
    void (*func14)();  // 0x14
    void (*func18)();  // 0x18
    void (*func1c)();  // 0x1C
} NanNPCWork;
void evt_nannpc_set_animtbl_sub(NanNPC* npc, s16* tbl);
s32 evt_nannpc_entry(EventEntry *event, BOOL isFirstCall);
void nannpc_ext_dispent();
void nannpc_ext_main();
void nannpc_ext_main_sub_fast();
void nannpc_ext_main_sub();
void nannpc_ext_init();
void nannpc_ext_shadow_disp();
void nannpc_ext_disp();
s32 nannpc_zcompare(NanNPCSort* a, NanNPCSort* b);
void nanNPCOption(void);
USER_FUNC(evt_nannpcwork_flag_onoff);
USER_FUNC(evt_nannpc_set_color);
USER_FUNC(evt_nannpc_set_shadow_position);
USER_FUNC(evt_nannpc_set_func);
USER_FUNC(evt_nannpc_ppflag_onoff);
USER_FUNC(evt_nannpc_flag_onoff);
USER_FUNC(evt_nannpc_jump_position);
USER_FUNC(evt_nannpc_move_position2);
USER_FUNC(evt_nannpc_get_work);
USER_FUNC(evt_nannpc_set_work);
USER_FUNC(evt_nannpc_set_dir);
USER_FUNC(evt_nannpc_set_animtbl);
USER_FUNC(evt_nannpc_set_size);
USER_FUNC(evt_nannpc_set_hosei_position);
USER_FUNC(evt_nannpc_get_position);
USER_FUNC(evt_nannpc_set_position);
USER_FUNC(evt_nannpc_set_subfunc);
USER_FUNC(evt_nannpc_init);

s32 gap_08_8041899C_sbss;
NanNPCWork* nanNPCWork;
char makestring[16];

void nannpc_ext_disp();
void nannpc_ext_shadow_disp();
void nannpc_ext_dispent();
void nannpc_ext_main();
void nannpc_ext_main_sub();
void nannpc_ext_init();

#ifdef NONMATCHING /* not in the target object (dead code stripped at link) */
static inline NanNPC* nanNPCSearch(char* name) {
    s32 i;
    NanNPC* p;
    NanNPCWork* w = nanNPCWork;
    for (i = 0; i < w->num; i++) {
        p = &w->npc[i];
        if (!((u32)name & 0x80000000)) {
            sprintf(makestring, "%06x", name);
            name = makestring;
        }
        if (!strcmp((char*)p->name, name)) {
            return p;
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
void nanNPCOption(void) {
    s32 clear;
    NanNPC* q;
    void* w;
    NanNPC* p;
    NanNPC* r;
    Vec diff;
    Vec v84;
    Vec v78;
    Vec v6c;
    Vec v60;
    Vec v54;
    Vec v48;
    Vec v3c;
    Vec n;
    Vec h;
    f32 mag;
    f32 dist;
    f32 d20;
    f32 nz, ny, nx, hz, hy, hx;

    w = nanNPCWork;
    for (p = ((NanNPCWork*)w)->npc; p < ((NanNPCWork*)w)->npc + ((NanNPCWork*)w)->num; p++) {
        if (p->flags & 4) {
            for (q = ((NanNPCWork*)w)->npc; q < ((NanNPCWork*)w)->npc + ((NanNPCWork*)w)->num; q++) {
                if (p != q && (q->flags & 4)) {
                    dist = PSVECDistance(&p->pos, &q->pos);
                    PSVECSubtract(&p->pos, &q->pos, &diff);
                    if (dist <= p->sizeY) {
                        mag = PSVECMag(&diff);
                        if (mag == 0.0f) {
                            diff.x = 1.0f;
                        }
                        PSVECNormalize(&diff, &diff);
                        diff.y = 0.0f;
                        PSVECScale(&diff, &diff, 0.5f);
                        PSVECAdd(&p->move, &diff, &p->move);
                        PSVECSubtract(&q->move, &diff, &q->move);
                    }
                }
            }
        }
    }
    for (p = ((NanNPCWork*)w)->npc; p < ((NanNPCWork*)w)->npc + ((NanNPCWork*)w)->num; p++) {
        if (p->flags & 4) {
            PSVECSubtract(&p->field_30, &p->pos, &diff);
            mag = PSVECMag(&diff);
            if (mag > 0.8f * p->sizeY) {
                PSVECNormalize(&diff, &diff);
                diff.y = 0.0f;
                PSVECScale(&diff, &diff, 0.5f);
                PSVECAdd(&p->move, &diff, &p->move);
            }
        }
    }
    for (r = ((NanNPCWork*)w)->npc; r < ((NanNPCWork*)w)->npc + ((NanNPCWork*)w)->num; r++) {
        if (r->flags & 4) {
            mag = PSVECMag(&r->move);
            if (mag) {
                if (mag > 10.0f) {
                    PSVECScale(&r->move, &r->move, 5.0f / mag);
                    mag = 5.0f;
                }
                v60 = r->pos;
                v60.y += 1.0f;
                PSVECNormalize(&r->move, &v6c);
                if (r->flags & 8) {
                    PSVECAdd(&r->pos, &r->move, &r->pos);
                    PSVECScale(&r->move, &r->move, 0.6f);
                } else {
                    clear = 1;
                    v84 = v6c;
                    v78 = v60;
                    r->hit1 = NULL;
                    r->hit0 = NULL;
                    d20 = mag;
                    r->hit0 = hitCheckFilter(NULL, &h.x, &h.y, &h.z, &d20, &n.x, &n.y, &n.z,
                                             v78.x, v78.y, v78.z, v84.x, v84.y, v84.z);
                    if (!r->hit0) {
                        PSVECAdd(&r->pos, &r->move, &r->pos);
                    } else {
                        v48 = r->pos;
                        PSVECAdd(&r->pos, &r->move, &r->pos);
                        if (r->move.y == 0.0f) {
                            n.y = 0.0f;
                        }
                        PSVECNormalize(&n, &n);
                        C_VECReflect(&v84, &n, &v54);
                        PSVECScale(&v54, &r->move, mag);
                        clear = 0;
                        PSVECScale(&n, &n, PSVECDotProduct(&v84, &n) * -(mag - d20) + 0.1f);
                        PSVECAdd(&r->pos, &n, &r->pos);
                        PSVECSubtract(&r->pos, &v48, &v3c);
                        d20 = PSVECMag(&v3c);
                        if ((f32)d20 > 0.0f) {
                            PSVECNormalize(&v3c, &v3c);
                            v78 = v48;
                            r->hit1 = hitCheckFilter(
                                NULL, &hx, &hy, &hz, &d20, &nx, &ny, &nz, v48.x, 1.0f + v48.y, v48.z,
                                v3c.x, v3c.y, v3c.z);
                            if (r->hit1) {
                                r->pos = v78;
                            }
                        }
                    }
                    if (clear) {
                        PSVECScale(&r->move, &r->move, 0.6f);
                    }
                }
            }
        }
    }
}
#endif


#ifdef NONMATCHING
s32 nannpc_zcompare(NanNPCSort* a, NanNPCSort* b) {
    if (a->z < b->z) {
        return 1;
    }
    if (a->z > b->z) {
        return -1;
    }
    return 0;
}
#endif

#ifdef NONMATCHING /* not in the target object (dead code stripped at link) */
static inline void nannpc_loadTev(void) {
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevColorIn(0, 15, 8, 2, 15);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 7, 4, 1, 7);
    GXSetNumChans(0);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetFog(0, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){255, 255, 255, 255});
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
}
#endif
#ifdef NONMATCHING
void nannpc_ext_disp() {
    NanNPCWork* w = nanNPCWork;
    s32 i;
    s32 idx;
    NanNPCSort* sp;
    NanNPC* np;
    if (w->flags & 1) {
        extLoadVertex();
        extLoadTexture();
        nannpc_loadTev();
        for (i = extGetPoseNum() - 1; i >= 0; i--) {
            np = w->npc + i;
            sp = w->sort + i;
            sp->idx = i;
            sp->z = np->pos.z;
        }
        qqsort(w->sort, w->num, 8, (s32(*)(void*, void*))nannpc_zcompare);
        for (i = extGetPoseNum() - 1; i >= 0; i--) {
            idx = w->sort[i].idx;
            GXSetTevColor(1, w->npc[idx].color);
            extPoseDraw(idx);
        }
        extLoadTextureExit();
    } else {
        extLoadRenderMode();
        extLoadVertex();
        extLoadTexture();
        extLoadTev();
        extDraw();
        extLoadTextureExit();
    }
}
#endif

#ifdef NONMATCHING
void nannpc_ext_shadow_disp() {
    static Mtx mt = {{10.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 10.0f, 0.0f, 0.1f}, {0.0f, 0.0f, 10.0f, 0.0f}};
    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}
#endif

#ifdef NONMATCHING
void nannpc_ext_init() {
    s32 i;
    ExtPose* pose = extGetPosePtr();
    for (i = extGetPoseNum() - 1; i >= 0; i--, pose++) {
        pose->flags = 3;
        pose->rot = 0.0f;
        PSMTXIdentity(*pose->mtx);
        (*pose->mtx)[0][3] = 0.0f;
        (*pose->mtx)[1][3] = -1000.0f;
        (*pose->mtx)[2][3] = 0.0f;
    }
}
#endif

#ifdef NONMATCHING
void nannpc_ext_main_sub() {
    s32 i;
    NanNPCWork* w = nanNPCWork;
    for (i = extGetPoseNum() - 1; i >= 0; i--) {
        NanNPC* p = &w->npc[i];
        if (p->name[0] && p->func) {
            p->func(p);
        }
    }
}
#endif

#ifdef NONMATCHING
void nannpc_ext_main_sub_fast() {
    s32 i;
    NanNPC* p;
    NanNPCWork* w = nanNPCWork;
    for (i = extGetPoseNum() - 1; i >= 0; i--) {
        p = &w->npc[i];
        if (p->name[0]) {
            if (p->func) {
                p->func(p);
            }
            if (p->animtbl) {
                p->anim = p->animtbl[(gp->retraceCount + i * i) % p->animnum];
            }
            p->pose->poseId = p->anim;
            p->pose->rot = -p->dir;
            if (p->flags & 2) {
                (*p->pose->mtx)[0][3] = 0.0f;
                (*p->pose->mtx)[1][3] = -1000.0f;
                (*p->pose->mtx)[2][3] = 0.0f;
            } else {
                (*p->pose->mtx)[0][3] = p->pos.x;
                (*p->pose->mtx)[1][3] = p->pos.y;
                (*p->pose->mtx)[2][3] = p->pos.z;
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void nannpc_ext_main() {
    NanNPCWork* w = nanNPCWork;
    if (w->func14) {
        w->func14();
    }
    if (w->func18) {
        w->func18();
    }
    if (w->func1c) {
        w->func1c();
    }
}
#endif

#ifdef NONMATCHING
void nannpc_ext_dispent() {
    if (!(nanNPCWork->flags & 1)) {
        dispEntry(4, 0.0f, 1, nannpc_ext_disp, 0);
        dispEntry(4, 0.0f, 2, nannpc_ext_shadow_disp, 0);
    } else {
        dispEntry(4, 0.0f, 2, nannpc_ext_disp, 0);
        dispEntry(4, 0.0f, 2, nannpc_ext_shadow_disp, 0);
    }
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_init) {
    s32* args = event->args;
    NanNPCWork* w;
    s32 i;
    s32 name = evtGetValue(event, args[0]);
    s16* tbl = (s16*)evtGetValue(event, args[1]);
    void* initf = (void*)evtGetValue(event, args[2]);
    void* mainf = (void*)evtGetValue(event, args[3]);
    void* dispf = nannpc_ext_dispent;
    if (isFirstCall) {
        return 0;
    }
    nanNPCWork = _mapAlloc(0x20);
    memset(nanNPCWork, 0, 0x20);
    w = nanNPCWork;
    w->num = evtGetValue(event, args[4]);
    w->npc = _mapAlloc(w->num * 0xC0);
    memset(w->npc, 0, w->num * 0xC0);
    w->sort = _mapAlloc(w->num * 8);
    memset(w->sort, 0, w->num * 8);
    w->tbl = _mapAlloc(0x14);
    memset(w->tbl, 0, 0x14);
    w->func14 = NULL;
    nanNPCWork->func18 = nannpc_ext_main_sub;
    w->func1c = NULL;
    if (!initf) {
        initf = nannpc_ext_init;
    }
    if (!mainf) {
        mainf = nannpc_ext_main;
    }
    extEntry(w->num, (void*)name, initf, mainf, dispf);
    for (i = 0; i < w->num; i++) {
        NanNPC* p = &w->npc[i];
        p->name[0] = 0;
        p->pose = NULL;
        p->flags = 0;
        p->field_16 = 0;
        p->pos = (Vec){0.0f, -1000.0f, 0.0f};
        p->field_30 = (Vec){0.0f, -1000.0f, 0.0f};
        p->hosei = (Vec){0.0f, 0.0f, 0.0f};
        p->sizeX = 32.0f;
        p->sizeY = 32.0f;
        p->startTime = 0;
        p->animtbl = NULL;
        p->animnum = 0;
        p->anim = 0;
        p->dir = 0.0f;
        p->func = NULL;
        p->color = (GXColor){255, 255, 255, 255};
    }
    if (!tbl) {
        return 2;
    }
    for (i = 0; i < 5; i++) {
        if (tbl[i * 2] == -1) {
            break;
        }
        w->tbl[i * 2] = tbl[i * 2];
        w->tbl[i * 2 + 1] = tbl[i * 2 + 1];
    }
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_subfunc) {
    s32* args = event->args;
    s32 kind = evtGetValue(event, args[0]);
    NanNPCWork* w = nanNPCWork;
    switch (kind) {
        case 0:
            w->func14 = (void (*)())evtGetValue(event, args[1]);
            break;
        case 1:
            w->func18 = (void (*)())evtGetValue(event, args[1]);
            break;
        case 2:
            w->func1c = (void (*)())evtGetValue(event, args[1]);
            break;
    }
    return 2;
}
#endif

#ifdef NONMATCHING
s32 evt_nannpc_entry(EventEntry *event, BOOL isFirstCall)
{
  NanNPC *p;
  ExtPose *pose;
  char *str;
  s32 off;
  s32 name;
  s32 i;
  s32 *args;
  NanNPCWork *w;
  args = event->args;
  pose = extGetPosePtr();
  name = (long long) evtGetValue(event, args[0]);
  w = nanNPCWork;
  for (i = 0, off = 0; i < w->num; off += sizeof(NanNPC), i++)
  {
    p = (NanNPC *) (((u8 *) w->npc) - (-off));
    str = (char *) name;
    if (!(((u32) str) & 0x80000000))
    {
 do { } while (0);
      sprintf(makestring, "%06x", name);
      str = makestring;
    }
    strcmp((char *) p->name, str);
    if (!p->pose)
    {
      strcpy((char *) p->name, str);
      p->pose = &pose[i];
      p->flags = 0;
      p->field_16 = 0;
      p->pos = (Vec){0.0f, -1000.0f, 0.0f};
      p->field_30 = (Vec){0.0f, -1000.0f, 0.0f};
      p->hosei = (Vec){0.0f, 0.0f, 0.0f};
      p->sizeX = 32.0f;
      p->sizeY = 32.0f;
      p->startTime = 0;
      p->animnum = 0;
      p->dir = 0.0f;
      p->pose->rot = -p->dir;
      p->color = (GXColor){255, 255, 255, 255};
      break;
    }
  }

  return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_position) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    f32 x = evtGetFloat(event, args[1]);
    npc->pos.x = x;
    npc->field_30.x = x;
    x = evtGetFloat(event, args[2]);
    npc->pos.y = x;
    npc->field_30.y = x;
    x = evtGetFloat(event, args[3]);
    npc->pos.z = x;
    npc->field_30.z = x;
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_get_position) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    evtSetFloat(event, args[1], npc->pos.x);
    evtSetFloat(event, args[2], npc->pos.y);
    evtSetFloat(event, args[3], npc->pos.z);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_hosei_position) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->hosei.x = evtGetFloat(event, args[1]);
    npc->hosei.y = evtGetFloat(event, args[2]);
    npc->hosei.z = evtGetFloat(event, args[3]);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_size) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->sizeX = evtGetFloat(event, args[1]);
    npc->sizeY = evtGetFloat(event, args[2]);
    return 2;
}
#endif

#ifdef NONMATCHING
void evt_nannpc_set_animtbl_sub(NanNPC* npc, s16* tbl) {
    s32 n;
    npc->animtbl = tbl;
    n = 0;
    while (TRUE) {
        if (*tbl == -1) {
            break;
        }
        tbl++;
        n++;
    }
    npc->animnum = n;
    if (npc->animnum == 0) {
        npc->animtbl = NULL;
    }
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_animtbl) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    s16* tbl = (s16*)evtGetValue(event, args[1]);
    s32 n;
    npc->animtbl = tbl;
    n = 0;
    while (TRUE) {
        if (*tbl == -1) {
            break;
        }
        tbl++;
        n++;
    }
    npc->animnum = n;
    if (npc->animnum == 0) {
        npc->animtbl = NULL;
    }
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_dir) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->dir = evtGetValue(event, args[1]);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_work) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    s32 idx = evtGetValue(event, args[1]);
    npc->work[idx] = evtGetValue(event, args[2]);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_get_work) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[2], npc->work[evtGetValue(event, args[1])]);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_move_position2) {
    NanNPC* npc;
    OSTime now;
    s32* args;
    f32 speed;
    s32 total;
    s32 elapsed;
    Vec target;
    Vec diff;
    Vec step;
    args = event->args;
    npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    if (gp->inBattle) {
        now = gp->renderTime;
    } else {
        now = gp->renderFieldTime;
    }
    target.x = evtGetValue(event, args[1]);
    target.y = evtGetValue(event, args[2]);
    target.z = evtGetValue(event, args[3]);
    speed = evtGetFloat(event, args[4]);
    if (isFirstCall) {
        event->savedTime = now;
        npc->startPos = npc->pos;
    }
    PSVECSubtract(&target, &npc->startPos, &diff);
    total = (s32)(1000.0f * PSVECMag(&diff) / speed);
    elapsed = (u64)(s32)((u32)now - (u32)event->savedTime) / (OS_TIMER_CLOCK / 1000);
    PSVECScale(&diff, &step, (f32)elapsed / (f32)total);
    if (elapsed < total) {
        PSVECAdd(&npc->startPos, &step, &npc->pos);
        return 0;
    }
    npc->pos = target;
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_jump_position) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    f32 x = evtGetValue(event, args[1]);
    f32 y = evtGetValue(event, args[2]);
    f32 z = evtGetValue(event, args[3]);
    s32 duration = evtGetValue(event, args[4]);
    f32 height = evtGetValue(event, args[5]);
    s32 elapsed;
    s32 el;
    u32 uel;
    f32 t;
    if (isFirstCall) {
        npc->startTime = gp->renderTime;
        npc->ipos[0] = npc->pos.x;
        npc->ipos[1] = npc->pos.y;
        npc->ipos[2] = npc->pos.z;
        event->userdataf[1] = -4.0f * height;
        event->userdataf[2] = y - (f32)npc->ipos[1] - event->userdataf[1];
    }
    el = ((u32)gp->renderTime - (u32)npc->startTime) / (OS_TIMER_CLOCK / 1000);
    uel = el;
    if (el < duration) {
        elapsed = uel;
        t = (f32)elapsed / (f32)duration;
        npc->pos.x = intplGetValue(0, elapsed, duration, npc->ipos[0], x);
        npc->pos.z = intplGetValue(0, uel, duration, npc->ipos[2], z);
        npc->pos.y = t * (event->userdataf[1] * t + event->userdataf[2]) + (f32)npc->ipos[1];
        return 0;
    }
    npc->pos.x = x;
    npc->pos.y = y;
    npc->pos.z = z;
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_flag_onoff) {
    s32* args = event->args;
    s32 name = evtGetValue(event, args[0]);
    s32 onoff = evtGetValue(event, args[1]);
    NanNPC* npc = nanNPCSearch((char*)name);
    u16 flag = evtGetValue(event, args[2]);
    if (onoff) {
        npc->flags &= ~flag;
    } else {
        npc->flags |= flag;
    }
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_ppflag_onoff) {
    s32* args = event->args;
    s32 name = evtGetValue(event, args[0]);
    s32 onoff = evtGetValue(event, args[1]);
    NanNPC* npc = nanNPCSearch((char*)name);
    u16 flag = evtGetValue(event, args[2]);
    if (onoff) {
        npc->pose->flags &= ~flag;
    } else {
        npc->pose->flags |= flag;
    }
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_func) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->func = (void (*)(NanNPC*))evtGetValue(event, args[1]);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_shadow_position) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->pose->flags |= 0x10;
    npc->pose->shadowY = evtGetFloat(event, args[1]);
    return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_color) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->color.r = evtGetValue(event, args[1]);
    npc->color.g = evtGetValue(event, args[2]);
    npc->color.b = evtGetValue(event, args[3]);
    npc->color.a = evtGetValue(event, args[4]);
    return 2;
}
#endif

#pragma force_active on
#pragma explicit_zero_data on
#ifdef NONMATCHING
USER_FUNC(evt_nannpcwork_flag_onoff) {
    s32* args = event->args;
    s32 onoff = evtGetValue(event, args[0]);
    NanNPCWork* w = nanNPCWork;
    u16 flag = evtGetValue(event, args[1]);
    if (onoff) {
        w->flags &= ~flag;
    } else {
        w->flags |= flag;
    }
    return 2;
}
#endif
#pragma explicit_zero_data reset
#pragma force_active reset

#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset
#pragma force_active reset

#ifndef NONMATCHING
// ASM-STOPGAP: nanNPCOption (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off

asm s32 evt_nannpcwork_flag_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r29, nanNPCWork(r0)
	mr r31, r3
	lwz r4, 0x4(r30)
	mr r3, r28
	bl evtGetValue
	cmpwi r31, 0x0
	clrlwi r4, r3, 16
	beq @1
	lwz r3, 0x10(r29)
	andc r0, r3, r4
	stw r0, 0x10(r29)
	b @2
	@1:
	lwz r0, 0x10(r29)
	or r0, r0, r4
	stw r0, 0x10(r29)
	@2:
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_nannpc_set_color(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetValue
	stb r3, 0xbc(r30)
	mr r3, r25
	lwz r4, 0x8(r26)
	bl evtGetValue
	stb r3, 0xbd(r30)
	mr r3, r25
	lwz r4, 0xc(r26)
	bl evtGetValue
	stb r3, 0xbe(r30)
	mr r3, r25
	lwz r4, 0x10(r26)
	bl evtGetValue
	stb r3, 0xbf(r30)
	li r3, 0x2
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_shadow_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x10(r30)
	mr r3, r25
	lwz r0, 0x0(r4)
	ori r0, r0, 0x10
	stw r0, 0x0(r4)
	lwz r4, 0x4(r26)
	bl evtGetFloat
	lwz r4, 0x10(r30)
	li r3, 0x2
	stfs f1, 0x8(r4)
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_func(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetValue
	stw r3, 0x64(r30)
	li r3, 0x2
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_ppflag_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r24, 0x10(r1)
	mr r24, r3
	lwz r25, 0x18(r3)
	lwz r4, 0x0(r25)
	bl evtGetValue
	lwz r4, 0x4(r25)
	mr r26, r3
	mr r3, r24
	bl evtGetValue
	li r28, 0x0
	lwz r30, nanNPCWork(r0)
	mr r31, r3
	mr r27, r26
	mr r26, r28
	b @1
	@2:
	lwz r3, 0x0(r30)
	clrrwi. r0, r27, 31
	add r29, r3, r26
	bne @3
	mr r5, r27
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r27, makestring(r0)
	@3:
	mr r3, r29
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r26, r26, 0xc0
	addi r28, r28, 0x1
	@1:
	lwz r0, 0xc(r30)
	cmpw r28, r0
	blt @2
	li r29, 0x0
	@5:
	lwz r4, 0x8(r25)
	mr r3, r24
	bl evtGetValue
	cmpwi r31, 0x0
	clrlwi r5, r3, 16
	beq @6
	lwz r4, 0x10(r29)
	lwz r3, 0x0(r4)
	andc r0, r3, r5
	stw r0, 0x0(r4)
	b @7
	@6:
	lwz r3, 0x10(r29)
	lwz r0, 0x0(r3)
	or r0, r0, r5
	stw r0, 0x0(r3)
	@7:
	lmw r24, 0x10(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_flag_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r24, 0x10(r1)
	mr r24, r3
	lwz r25, 0x18(r3)
	lwz r4, 0x0(r25)
	bl evtGetValue
	lwz r4, 0x4(r25)
	mr r26, r3
	mr r3, r24
	bl evtGetValue
	li r28, 0x0
	lwz r30, nanNPCWork(r0)
	mr r31, r3
	mr r27, r26
	mr r26, r28
	b @1
	@2:
	lwz r3, 0x0(r30)
	clrrwi. r0, r27, 31
	add r29, r3, r26
	bne @3
	mr r5, r27
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r27, makestring(r0)
	@3:
	mr r3, r29
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r26, r26, 0xc0
	addi r28, r28, 0x1
	@1:
	lwz r0, 0xc(r30)
	cmpw r28, r0
	blt @2
	li r29, 0x0
	@5:
	lwz r4, 0x8(r25)
	mr r3, r24
	bl evtGetValue
	cmpwi r31, 0x0
	clrlwi r3, r3, 16
	beq @6
	lhz r0, 0x14(r29)
	andc r0, r0, r3
	sth r0, 0x14(r29)
	b @7
	@6:
	lhz r0, 0x14(r29)
	or r0, r0, r3
	sth r0, 0x14(r29)
	@7:
	lmw r24, 0x10(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_jump_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stmw r24, 0x30(r1)
	mr r28, r3
	mr r29, r4
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	li r26, 0x0
	lwz r27, nanNPCWork(r0)
	mr r25, r3
	mr r24, r26
	b @1
	@2:
	lwz r3, 0x0(r27)
	clrrwi. r0, r25, 31
	add r31, r3, r24
	bne @3
	mr r5, r25
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r25, makestring(r0)
	@3:
	mr r3, r31
	mr r4, r25
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r24, r24, 0xc0
	addi r26, r26, 0x1
	@1:
	lwz r0, 0xc(r27)
	cmpw r26, r0
	blt @2
	li r31, 0x0
	@5:
	lwz r4, 0x4(r30)
	mr r3, r28
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802f3040@ha
	stw r3, 0xc(r1)
	addi r5, r4, double_to_int_802f3040@l
	lwz r4, 0x8(r30)
	stw r0, 0x8(r1)
	mr r3, r28
	lfd f1, 0x0(r5)
	lfd f0, 0x8(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802f3040@ha
	stw r3, 0x14(r1)
	addi r5, r4, double_to_int_802f3040@l
	lwz r4, 0xc(r30)
	stw r0, 0x10(r1)
	mr r3, r28
	lfd f1, 0x0(r5)
	lfd f0, 0x10(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802f3040@ha
	stw r3, 0x1c(r1)
	addi r5, r4, double_to_int_802f3040@l
	lwz r4, 0x10(r30)
	stw r0, 0x18(r1)
	mr r3, r28
	lfd f1, 0x0(r5)
	lfd f0, 0x18(r1)
	fsubs f29, f0, f1
	bl evtGetValue
	lwz r4, 0x14(r30)
	mr r30, r3
	mr r3, r28
	bl evtGetValue
	xoris r0, r3, 0x8000
	lis r4, 0x4330
	stw r0, 0x24(r1)
	lis r3, double_to_int_802f3040@ha
	lfd f2, double_to_int_802f3040@l(r3)
	cmpwi r29, 0x0
	stw r4, 0x20(r1)
	lfd f0, 0x20(r1)
	fsubs f1, f0, f2
	beq @6
	lwz r3, gp(r0)
	lfs f0, float_neg4_8041c57c(r0)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	fmuls f0, f0, f1
	stw r4, 0x8(r1)
	stw r3, 0x54(r31)
	stw r0, 0x50(r31)
	lfs f1, 0x18(r31)
	fctiwz f1, f1
	stfd f1, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r0, 0x68(r31)
	lfs f1, 0x1c(r31)
	fctiwz f1, f1
	stfd f1, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x6c(r31)
	lfs f1, 0x20(r31)
	fctiwz f1, f1
	stfd f1, 0x10(r1)
	lwz r0, 0x14(r1)
	stw r0, 0x70(r31)
	stfs f0, 0x7c(r28)
	lwz r0, 0x6c(r31)
	lfs f0, 0x7c(r28)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fsubs f1, f30, f1
	fsubs f0, f1, f0
	stfs f0, 0x80(r28)
	@6:
	lis r3, 0x8000
	lwz r4, gp(r0)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	addi r3, r3, 0x4dd3
	lwz r5, 0x54(r31)
	srwi r0, r0, 2
	lwz r4, 0x3c(r4)
	mulhwu r0, r3, r0
	subf r3, r5, r4
	srwi r0, r0, 6
	divwu r4, r3, r0
	cmpw r4, r30
	bge @7
	lis r6, 0x4330
	xoris r0, r4, 0x8000
	stw r0, 0x24(r1)
	xoris r3, r30, 0x8000
	lis r5, double_to_int_802f3040@ha
	lwz r0, 0x68(r31)
	stw r6, 0x20(r1)
	fmr f2, f31
	lfd f3, double_to_int_802f3040@l(r5)
	xoris r0, r0, 0x8000
	lfd f0, 0x20(r1)
	mr r24, r4
	stw r3, 0x1c(r1)
	fsubs f1, f0, f3
	mr r5, r30
	stw r6, 0x18(r1)
	li r3, 0x0
	lfd f0, 0x18(r1)
	stw r0, 0x14(r1)
	fsubs f0, f0, f3
	stw r6, 0x10(r1)
	fdivs f30, f1, f0
	lfd f0, 0x10(r1)
	fsubs f1, f0, f3
	bl intplGetValue
	stfs f1, 0x18(r31)
	lis r0, 0x4330
	lis r3, double_to_int_802f3040@ha
	fmr f2, f29
	lwz r5, 0x70(r31)
	mr r4, r24
	stw r0, 0x8(r1)
	xoris r0, r5, 0x8000
	lfd f1, double_to_int_802f3040@l(r3)
	stw r0, 0xc(r1)
	mr r5, r30
	li r3, 0x0
	lfd f0, 0x8(r1)
	fsubs f1, f0, f1
	bl intplGetValue
	stfs f1, 0x20(r31)
	lis r0, 0x4330
	lis r4, double_to_int_802f3040@ha
	li r3, 0x0
	lwz r5, 0x6c(r31)
	stw r0, 0x28(r1)
	xoris r0, r5, 0x8000
	lfs f3, 0x7c(r28)
	stw r0, 0x2c(r1)
	lfs f2, 0x80(r28)
	lfd f1, double_to_int_802f3040@l(r4)
	lfd f0, 0x28(r1)
	fmadds f2, f3, f30, f2
	fsubs f0, f0, f1
	fmadds f0, f30, f2, f0
	stfs f0, 0x1c(r31)
	b @8
	@7:
	stfs f31, 0x18(r31)
	li r3, 0x2
	stfs f30, 0x1c(r31)
	stfs f29, 0x20(r31)
	@8:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	lmw r24, 0x30(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 evt_nannpc_move_position2(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stmw r24, 0x50(r1)
	mr r26, r3
	mr r27, r4
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	li r30, 0x0
	lwz r29, nanNPCWork(r0)
	mr r25, r3
	mr r24, r30
	b @1
	@2:
	lwz r3, 0x0(r29)
	clrrwi. r0, r25, 31
	add r31, r3, r24
	bne @3
	mr r5, r25
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r25, makestring(r0)
	@3:
	mr r3, r31
	mr r4, r25
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r24, r24, 0xc0
	addi r30, r30, 0x1
	@1:
	lwz r0, 0xc(r29)
	cmpw r30, r0
	blt @2
	li r31, 0x0
	@5:
	lwz r3, gp(r0)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @6
	lwz r30, 0x38(r3)
	lwz r29, 0x3c(r3)
	b @7
	@6:
	lwz r30, 0x40(r3)
	lwz r29, 0x44(r3)
	@7:
	lwz r4, 0x4(r28)
	mr r3, r26
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x34(r1)
	lis r4, double_to_int_802f3040@ha
	lfd f1, double_to_int_802f3040@l(r4)
	mr r3, r26
	stw r0, 0x30(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f1
	stfs f0, 0x20(r1)
	lwz r4, 0x8(r28)
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x3c(r1)
	lis r4, double_to_int_802f3040@ha
	lfd f1, double_to_int_802f3040@l(r4)
	mr r3, r26
	stw r0, 0x38(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f1
	stfs f0, 0x24(r1)
	lwz r4, 0xc(r28)
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x44(r1)
	lis r4, double_to_int_802f3040@ha
	lfd f1, double_to_int_802f3040@l(r4)
	mr r3, r26
	stw r0, 0x40(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f1
	stfs f0, 0x28(r1)
	lwz r4, 0x10(r28)
	bl evtGetFloat
	fmr f31, f1
	cmpwi r27, 0x0
	beq @8
	stw r29, 0x19c(r26)
	stw r30, 0x198(r26)
	lwz r3, 0x18(r31)
	lwz r0, 0x1c(r31)
	stw r3, 0x88(r31)
	stw r0, 0x8c(r31)
	lwz r0, 0x20(r31)
	stw r0, 0x90(r31)
	@8:
	addi r3, r1, 0x20
	addi r4, r31, 0x88
	addi r5, r1, 0x14
	bl PSVECSubtract
	addi r3, r1, 0x14
	bl PSVECMag
	lfs f0, float_1000_8041c580(r0)
	lis r3, 0x8000
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	fmuls f0, f0, f1
	lwz r4, 0x19c(r26)
	srwi r0, r0, 2
	addi r3, r3, 0x4dd3
	mulhwu r0, r3, r0
	subf r4, r4, r29
	fdivs f0, f0, f31
	srawi r3, r4, 31
	li r5, 0x0
	srwi r6, r0, 6
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r24, 0x44(r1)
	bl __div2u
	mr r26, r4
	lis r5, 0x4330
	xoris r3, r26, 0x8000
	xoris r0, r24, 0x8000
	lis r4, double_to_int_802f3040@ha
	stw r3, 0x3c(r1)
	addi r6, r4, double_to_int_802f3040@l
	addi r3, r1, 0x14
	stw r5, 0x38(r1)
	addi r4, r1, 0x8
	lfd f2, 0x0(r6)
	lfd f0, 0x38(r1)
	stw r0, 0x34(r1)
	fsubs f1, f0, f2
	stw r5, 0x30(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f2
	fdivs f1, f1, f0
	bl PSVECScale
	cmpw r26, r24
	bge @9
	addi r3, r31, 0x88
	addi r4, r1, 0x8
	addi r5, r31, 0x18
	bl PSVECAdd
	li r3, 0x0
	b @10
	@9:
	lwz r4, 0x20(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	stw r4, 0x18(r31)
	stw r0, 0x1c(r31)
	lwz r0, 0x28(r1)
	stw r0, 0x20(r31)
	@10:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	lmw r24, 0x50(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 evt_nannpc_get_work(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetValue
	slwi r0, r3, 2
	lwz r4, 0x8(r26)
	add r5, r30, r0
	mr r3, r25
	lwz r5, 0xa4(r5)
	bl evtSetValue
	lmw r25, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_work(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetValue
	lwz r4, 0x8(r26)
	mr r31, r3
	mr r3, r25
	bl evtGetValue
	slwi r0, r31, 2
	add r4, r30, r0
	stw r3, 0xa4(r4)
	li r3, 0x2
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_dir(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_802f3040@ha
	lfd f1, double_to_int_802f3040@l(r4)
	li r3, 0x2
	stw r0, 0x8(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	stfs f0, 0x60(r30)
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_animtbl(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetValue
	li r4, 0x0
	stw r3, 0x58(r30)
	@6:
	lha r0, 0x0(r3)
	cmpwi r0, -0x1
	beq @7
	addi r3, r3, 0x2
	addi r4, r4, 0x1
	b @6
	@7:
	sth r4, 0x5c(r30)
	lha r0, 0x5c(r30)
	cmpwi r0, 0x0
	bne @8
	li r0, 0x0
	stw r0, 0x58(r30)
	@8:
	lmw r25, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void evt_nannpc_set_animtbl_sub(NanNPC* npc, s16* tbl) {
	nofralloc
	li r5, 0x0
	stw r4, 0x58(r3)
	@1:
	lha r0, 0x0(r4)
	cmpwi r0, -0x1
	beq @2
	addi r4, r4, 0x2
	addi r5, r5, 0x1
	b @1
	@2:
	sth r5, 0x5c(r3)
	lha r0, 0x5c(r3)
	cmpwi r0, 0x0
	bnelr
	li r0, 0x0
	stw r0, 0x58(r3)
	blr
}

asm s32 evt_nannpc_set_size(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetFloat
	stfs f1, 0x48(r30)
	mr r3, r25
	lwz r4, 0x8(r26)
	bl evtGetFloat
	stfs f1, 0x4c(r30)
	li r3, 0x2
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_hosei_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetFloat
	stfs f1, 0x24(r30)
	mr r3, r25
	lwz r4, 0x8(r26)
	bl evtGetFloat
	stfs f1, 0x28(r30)
	mr r3, r25
	lwz r4, 0xc(r26)
	bl evtGetFloat
	stfs f1, 0x2c(r30)
	li r3, 0x2
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_get_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	lfs f1, 0x18(r30)
	bl evtSetFloat
	lwz r4, 0x8(r26)
	mr r3, r25
	lfs f1, 0x1c(r30)
	bl evtSetFloat
	lwz r4, 0xc(r26)
	mr r3, r25
	lfs f1, 0x20(r30)
	bl evtSetFloat
	lmw r25, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	li r29, 0x0
	lwz r31, nanNPCWork(r0)
	mr r28, r3
	mr r27, r29
	b @1
	@2:
	lwz r3, 0x0(r31)
	clrrwi. r0, r28, 31
	add r30, r3, r27
	bne @3
	mr r5, r28
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r28, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	b @5
	@4:
	addi r27, r27, 0xc0
	addi r29, r29, 0x1
	@1:
	lwz r0, 0xc(r31)
	cmpw r29, r0
	blt @2
	li r30, 0x0
	@5:
	lwz r4, 0x4(r26)
	mr r3, r25
	bl evtGetFloat
	stfs f1, 0x18(r30)
	mr r3, r25
	stfs f1, 0x30(r30)
	lwz r4, 0x8(r26)
	bl evtGetFloat
	stfs f1, 0x1c(r30)
	mr r3, r25
	stfs f1, 0x34(r30)
	lwz r4, 0xc(r26)
	bl evtGetFloat
	stfs f1, 0x20(r30)
	li r3, 0x2
	stfs f1, 0x38(r30)
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_entry(EventEntry *event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r23, 0xc(r1)
	mr r23, r3
	lis r3, vec3_802f2ff8@ha
	addi r31, r3, vec3_802f2ff8@l
	lwz r24, 0x18(r23)
	bl extGetPosePtr
	lwz r4, 0x0(r24)
	mr r28, r3
	mr r3, r23
	bl evtGetValue
	lwz r23, nanNPCWork(r0)
	mr r25, r3
	li r24, 0x0
	li r26, 0x0
	clrrwi r29, r3, 31
	b @1
	@2:
	lwz r0, 0x0(r23)
	cmplwi r29, 0x0
	mr r27, r25
	add r30, r0, r26
	bne @3
	mr r5, r25
	la r3, makestring(r0)
	la r4, str_8041C574(r0)
	crclr 6
	bl sprintf
	la r27, makestring(r0)
	@3:
	mr r3, r30
	mr r4, r27
	bl strcmp
	lwz r0, 0x10(r30)
	cmplwi r0, 0x0
	bne @4
	mr r3, r30
	mr r4, r27
	bl strcpy
	slwi r0, r24, 5
	li r4, 0x0
	add r0, r28, r0
	lfs f1, float_32_8041c584(r0)
	stw r0, 0x10(r30)
	lfs f0, float_0_8041c588(r0)
	sth r4, 0x14(r30)
	sth r4, 0x16(r30)
	lwz r3, 0x24(r31)
	lwz r0, 0x28(r31)
	stw r3, 0x18(r30)
	stw r0, 0x1c(r30)
	lwz r0, 0x2c(r31)
	stw r0, 0x20(r30)
	lwz r3, 0x30(r31)
	lwz r0, 0x34(r31)
	stw r3, 0x30(r30)
	stw r0, 0x34(r30)
	lwz r0, 0x38(r31)
	stw r0, 0x38(r30)
	lwz r3, 0x3c(r31)
	lwz r0, 0x40(r31)
	stw r3, 0x24(r30)
	stw r0, 0x28(r30)
	lwz r0, 0x44(r31)
	stw r0, 0x2c(r30)
	stfs f1, 0x48(r30)
	stfs f1, 0x4c(r30)
	stw r4, 0x54(r30)
	stw r4, 0x50(r30)
	sth r4, 0x5c(r30)
	stfs f0, 0x60(r30)
	lfs f0, 0x60(r30)
	lwz r3, 0x10(r30)
	fneg f0, f0
	stfs f0, 0x4(r3)
	lwz r0, dat_8041c570(r0)
	stw r0, 0xbc(r30)
	b @5
	@4:
	addi r26, r26, 0xc0
	addi r24, r24, 0x1
	@1:
	lwz r0, 0xc(r23)
	cmpw r24, r0
	blt @2
	@5:
	lmw r23, 0xc(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_nannpc_set_subfunc(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	cmpwi r3, 0x1
	lwz r30, nanNPCWork(r0)
	beq @1
	bge @2
	cmpwi r3, 0x0
	bge @3
	b @4
	@2:
	cmpwi r3, 0x3
	bge @4
	b @5
	@3:
	lwz r4, 0x4(r31)
	mr r3, r29
	bl evtGetValue
	stw r3, 0x14(r30)
	b @4
	@1:
	lwz r4, 0x4(r31)
	mr r3, r29
	bl evtGetValue
	stw r3, 0x18(r30)
	b @4
	@5:
	lwz r4, 0x4(r31)
	mr r3, r29
	bl evtGetValue
	stw r3, 0x1c(r30)
	@4:
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_nannpc_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r5, vec3_802f2ff8@ha
	stw r0, 0x34(r1)
	stmw r23, 0xc(r1)
	mr r25, r4
	mr r23, r3
	addi r30, r5, vec3_802f2ff8@l
	lwz r24, 0x18(r3)
	lwz r4, 0x0(r24)
	bl evtGetValue
	lwz r4, 0x4(r24)
	mr r28, r3
	mr r3, r23
	bl evtGetValue
	lwz r4, 0x8(r24)
	mr r31, r3
	mr r3, r23
	bl evtGetValue
	lwz r4, 0xc(r24)
	mr r27, r3
	mr r3, r23
	bl evtGetValue
	lis r4, nannpc_ext_dispent@ha
	cmpwi r25, 0x0
	addi r0, r4, nannpc_ext_dispent@l
	mr r26, r3
	mr r25, r0
	beq @1
	li r3, 0x0
	b @2
	@1:
	li r3, 0x20
	bl _mapAlloc
	stw r3, nanNPCWork(r0)
	li r4, 0x0
	li r5, 0x20
	bl memset
	lwz r29, nanNPCWork(r0)
	mr r3, r23
	lwz r4, 0x10(r24)
	bl evtGetValue
	stw r3, 0xc(r29)
	lwz r0, 0xc(r29)
	mulli r3, r0, 0xc0
	bl _mapAlloc
	stw r3, 0x0(r29)
	li r4, 0x0
	lwz r0, 0xc(r29)
	lwz r3, 0x0(r29)
	mulli r5, r0, 0xc0
	bl memset
	lwz r0, 0xc(r29)
	slwi r3, r0, 3
	bl _mapAlloc
	stw r3, 0x4(r29)
	li r4, 0x0
	lwz r0, 0xc(r29)
	lwz r3, 0x4(r29)
	slwi r5, r0, 3
	bl memset
	li r3, 0x14
	bl _mapAlloc
	stw r3, 0x8(r29)
	li r4, 0x0
	li r5, 0x14
	lwz r3, 0x8(r29)
	bl memset
	li r4, 0x0
	lis r3, nannpc_ext_main_sub@ha
	stw r4, 0x14(r29)
	addi r0, r3, nannpc_ext_main_sub@l
	cmplwi r27, 0x0
	lwz r3, nanNPCWork(r0)
	stw r0, 0x18(r3)
	stw r4, 0x1c(r29)
	bne @3
	lis r3, nannpc_ext_init@ha
	addi r0, r3, nannpc_ext_init@l
	mr r27, r0
	@3:
	cmplwi r26, 0x0
	bne @4
	lis r3, nannpc_ext_main@ha
	addi r0, r3, nannpc_ext_main@l
	mr r26, r0
	@4:
	lwz r3, 0xc(r29)
	mr r4, r28
	mr r5, r27
	mr r6, r26
	mr r7, r25
	bl extEntry
	lfs f1, float_32_8041c584(r0)
	li r6, 0x0
	lfs f0, float_0_8041c588(r0)
	li r5, 0x0
	b @5
	@6:
	lwz r0, 0x0(r29)
	li r4, 0x0
	addi r6, r6, 0x1
	add r7, r0, r5
	addi r5, r5, 0xc0
	stb r4, 0x0(r7)
	stw r4, 0x10(r7)
	sth r4, 0x14(r7)
	sth r4, 0x16(r7)
	lwz r3, 0x0(r30)
	lwz r0, 0x4(r30)
	stw r3, 0x18(r7)
	stw r0, 0x1c(r7)
	lwz r0, 0x8(r30)
	stw r0, 0x20(r7)
	lwz r3, 0xc(r30)
	lwz r0, 0x10(r30)
	stw r3, 0x30(r7)
	stw r0, 0x34(r7)
	lwz r0, 0x14(r30)
	stw r0, 0x38(r7)
	lwz r3, 0x18(r30)
	lwz r0, 0x1c(r30)
	stw r3, 0x24(r7)
	stw r0, 0x28(r7)
	lwz r0, 0x20(r30)
	stw r0, 0x2c(r7)
	stfs f1, 0x48(r7)
	stfs f1, 0x4c(r7)
	stw r4, 0x54(r7)
	stw r4, 0x50(r7)
	stw r4, 0x58(r7)
	sth r4, 0x5c(r7)
	sth r4, 0x5e(r7)
	stfs f0, 0x60(r7)
	stw r4, 0x64(r7)
	lwz r0, dat_8041c56c(r0)
	stw r0, 0xbc(r7)
	@5:
	lwz r0, 0xc(r29)
	cmpw r6, r0
	blt @6
	cmplwi r31, 0x0
	bne @7
	li r3, 0x2
	b @2
	@7:
	lha r0, 0x0(r31)
	cmpwi r0, -0x1
	beq @8
	lwz r3, 0x8(r29)
	sth r0, 0x0(r3)
	lha r0, 0x2(r31)
	lwz r3, 0x8(r29)
	sth r0, 0x2(r3)
	lha r0, 0x4(r31)
	cmpwi r0, -0x1
	beq @8
	lwz r3, 0x8(r29)
	sth r0, 0x4(r3)
	lha r0, 0x6(r31)
	lwz r3, 0x8(r29)
	sth r0, 0x6(r3)
	lha r0, 0x8(r31)
	cmpwi r0, -0x1
	beq @8
	lwz r3, 0x8(r29)
	sth r0, 0x8(r3)
	lha r0, 0xa(r31)
	lwz r3, 0x8(r29)
	sth r0, 0xa(r3)
	lha r0, 0xc(r31)
	cmpwi r0, -0x1
	beq @8
	lwz r3, 0x8(r29)
	sth r0, 0xc(r3)
	lha r0, 0xe(r31)
	lwz r3, 0x8(r29)
	sth r0, 0xe(r3)
	lha r0, 0x10(r31)
	cmpwi r0, -0x1
	beq @8
	lwz r3, 0x8(r29)
	sth r0, 0x10(r3)
	lha r0, 0x12(r31)
	lwz r3, 0x8(r29)
	sth r0, 0x12(r3)
	@8:
	li r3, 0x2
	@2:
	lmw r23, 0xc(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void nannpc_ext_dispent() {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, nanNPCWork(r0)
	lwz r0, 0x10(r3)
	clrlwi. r0, r0, 31
	bne @1
	lis r3, nannpc_ext_disp@ha
	lfs f1, float_0_8041c588(r0)
	addi r5, r3, nannpc_ext_disp@l
	li r4, 0x1
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	lis r3, nannpc_ext_shadow_disp@ha
	lfs f1, float_0_8041c588(r0)
	addi r5, r3, nannpc_ext_shadow_disp@l
	li r4, 0x2
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	b @2
	@1:
	lis r3, nannpc_ext_disp@ha
	lfs f1, float_0_8041c588(r0)
	addi r5, r3, nannpc_ext_disp@l
	li r4, 0x2
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	lis r3, nannpc_ext_shadow_disp@ha
	lfs f1, float_0_8041c588(r0)
	addi r5, r3, nannpc_ext_shadow_disp@l
	li r4, 0x2
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void nannpc_ext_main() {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r31, nanNPCWork(r0)
	lwz r12, 0x14(r31)
	cmplwi r12, 0x0
	beq @1
	mtctr r12
	bctrl
	@1:
	lwz r12, 0x18(r31)
	cmplwi r12, 0x0
	beq @2
	mtctr r12
	bctrl
	@2:
	lwz r12, 0x1c(r31)
	cmplwi r12, 0x0
	beq @3
	mtctr r12
	bctrl
	@3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void nannpc_ext_main_sub_fast() {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lwz r28, nanNPCWork(r0)
	bl extGetPoseNum
	subi r30, r3, 0x1
	mulli r31, r30, 0xc0
	b @1
	@2:
	lwz r0, 0x0(r28)
	add r29, r0, r31
	lbz r0, 0x0(r29)
	extsb. r0, r0
	beq @3
	lwz r12, 0x64(r29)
	cmplwi r12, 0x0
	beq @4
	mr r3, r29
	mtctr r12
	bctrl
	@4:
	lwz r5, 0x58(r29)
	cmplwi r5, 0x0
	beq @5
	mullw r0, r30, r30
	lwz r4, gp(r0)
	lha r3, 0x5c(r29)
	lwz r4, 0x1c(r4)
	add r4, r4, r0
	divwu r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	slwi r0, r0, 1
	lhax r0, r5, r0
	sth r0, 0x5e(r29)
	@5:
	lha r0, 0x5e(r29)
	lwz r3, 0x10(r29)
	stw r0, 0x10(r3)
	lfs f0, 0x60(r29)
	lwz r3, 0x10(r29)
	fneg f0, f0
	stfs f0, 0x4(r3)
	lhz r0, 0x14(r29)
	rlwinm. r0, r0, 0, 30, 30
	beq @6
	lwz r3, 0x10(r29)
	lfs f1, float_0_8041c588(r0)
	lwz r3, 0xc(r3)
	lfs f0, float_neg1000_8041c58c(r0)
	stfs f1, 0xc(r3)
	lwz r3, 0x10(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0x1c(r3)
	lwz r3, 0x10(r29)
	lwz r3, 0xc(r3)
	stfs f1, 0x2c(r3)
	b @3
	@6:
	lwz r3, 0x10(r29)
	lfs f0, 0x18(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0xc(r3)
	lwz r3, 0x10(r29)
	lfs f0, 0x1c(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0x1c(r3)
	lwz r3, 0x10(r29)
	lfs f0, 0x20(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0x2c(r3)
	@3:
	subi r31, r31, 0xc0
	subi r30, r30, 0x1
	@1:
	cmpwi r30, 0x0
	bge @2
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void nannpc_ext_main_sub() {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r29, nanNPCWork(r0)
	bl extGetPoseNum
	subi r30, r3, 0x1
	mulli r31, r30, 0xc0
	b @1
	@2:
	lwz r0, 0x0(r29)
	add r3, r0, r31
	lbz r0, 0x0(r3)
	extsb. r0, r0
	beq @3
	lwz r12, 0x64(r3)
	cmplwi r12, 0x0
	beq @3
	mtctr r12
	bctrl
	@3:
	subi r31, r31, 0xc0
	subi r30, r30, 0x1
	@1:
	cmpwi r30, 0x0
	bge @2
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void nannpc_ext_init() {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stfd f30, 0x20(r1)
	psq_st f30, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl extGetPosePtr
	mr r29, r3
	bl extGetPoseNum
	lfs f30, float_0_8041c588(r0)
	subi r30, r3, 0x1
	lfs f31, float_neg1000_8041c58c(r0)
	li r31, 0x3
	b @1
	@2:
	stw r31, 0x0(r29)
	stfs f30, 0x4(r29)
	lwz r3, 0xc(r29)
	bl PSMTXIdentity
	lwz r3, 0xc(r29)
	subi r30, r30, 0x1
	stfs f30, 0xc(r3)
	lwz r3, 0xc(r29)
	stfs f31, 0x1c(r3)
	lwz r3, 0xc(r29)
	addi r29, r29, 0x20
	stfs f30, 0x2c(r3)
	@1:
	cmpwi r30, 0x0
	bge @2
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	psq_l f30, 0x28(r1), 0, 0
	lfd f30, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x44(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void nannpc_ext_shadow_disp() {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	la r3, mt_544(r0)
	stw r0, 0x14(r1)
	bl extLoadShadowMtx
	bl extLoadShadowRenderMode
	bl extLoadShadowVertex
	bl extLoadShadowTev
	bl extDrawShadow
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void nannpc_ext_disp() {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lwz r31, nanNPCWork(r0)
	lwz r0, 0x10(r31)
	clrlwi. r0, r0, 31
	beq @1
	bl extLoadVertex
	bl extLoadTexture
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0x8
	li r6, 0x2
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x4
	li r6, 0x1
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	lfs f1, float_0_8041c588(r0)
	addi r4, r1, 0x8
	lwz r0, dat_8041c568(r0)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	stw r0, 0x8(r1)
	fmr f4, f1
	bl GXSetFog
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	bl extGetPoseNum
	subic. r7, r3, 0x1
	mulli r5, r7, 0xc0
	slwi r6, r7, 3
	addi r3, r7, 0x1
	blt @2
	srwi. r0, r3, 2
	mtctr r0
	beq @3
	@4:
	lwz r0, 0x4(r31)
	lwz r4, 0x0(r31)
	add r8, r0, r6
	subi r6, r6, 0x8
	stw r7, 0x0(r8)
	add r4, r4, r5
	subi r7, r7, 0x1
	subi r5, r5, 0xc0
	lfs f0, 0x20(r4)
	stfs f0, 0x4(r8)
	lwz r0, 0x4(r31)
	lwz r4, 0x0(r31)
	add r8, r0, r6
	subi r6, r6, 0x8
	stw r7, 0x0(r8)
	add r4, r4, r5
	subi r7, r7, 0x1
	subi r5, r5, 0xc0
	lfs f0, 0x20(r4)
	stfs f0, 0x4(r8)
	lwz r0, 0x4(r31)
	lwz r4, 0x0(r31)
	add r8, r0, r6
	subi r6, r6, 0x8
	stw r7, 0x0(r8)
	add r4, r4, r5
	subi r7, r7, 0x1
	subi r5, r5, 0xc0
	lfs f0, 0x20(r4)
	stfs f0, 0x4(r8)
	lwz r0, 0x4(r31)
	lwz r4, 0x0(r31)
	add r8, r0, r6
	subi r6, r6, 0x8
	stw r7, 0x0(r8)
	add r4, r4, r5
	subi r5, r5, 0xc0
	subi r7, r7, 0x1
	lfs f0, 0x20(r4)
	stfs f0, 0x4(r8)
	bdnz @4
	andi. r3, r3, 0x3
	beq @2
	@3:
	mtctr r3
	@5:
	lwz r0, 0x4(r31)
	lwz r4, 0x0(r31)
	add r8, r0, r6
	subi r6, r6, 0x8
	stw r7, 0x0(r8)
	add r4, r4, r5
	subi r5, r5, 0xc0
	subi r7, r7, 0x1
	lfs f0, 0x20(r4)
	stfs f0, 0x4(r8)
	bdnz @5
	@2:
	lis r4, nannpc_zcompare@ha
	lwz r3, 0x4(r31)
	addi r6, r4, nannpc_zcompare@l
	lwz r4, 0xc(r31)
	li r5, 0x8
	bl qqsort
	bl extGetPoseNum
	subi r29, r3, 0x1
	slwi r30, r29, 3
	b @6
	@7:
	lwz r5, 0x4(r31)
	addi r4, r1, 0xc
	lwz r6, 0x0(r31)
	li r3, 0x1
	lwzx r28, r5, r30
	mulli r5, r28, 0xc0
	addi r0, r5, 0xbc
	lwzx r0, r6, r0
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r28
	bl extPoseDraw
	subi r30, r30, 0x8
	subi r29, r29, 0x1
	@6:
	cmpwi r29, 0x0
	bge @7
	bl extLoadTextureExit
	b @8
	@1:
	bl extLoadRenderMode
	bl extLoadVertex
	bl extLoadTexture
	bl extLoadTev
	bl extDraw
	bl extLoadTextureExit
	@8:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 nannpc_zcompare(NanNPCSort* a, NanNPCSort* b) {
	nofralloc
	lfs f1, 0x4(r3)
	lfs f0, 0x4(r4)
	fcmpo cr0, f1, f0
	bge @1
	li r3, 0x1
	blr
	@1:
	ble @2
	li r3, -0x1
	blr
	@2:
	li r3, 0x0
	blr
}

asm void nanNPCOption(void) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stfd f31, 0xd0(r1)
	psq_st f31, 0xd8(r1), 0, 0
	stmw r23, 0xac(r1)
	lwz r26, nanNPCWork(r0)
	lwz r24, 0x0(r26)
	b @1
	@2:
	lhz r0, 0x14(r24)
	rlwinm. r0, r0, 0, 29, 29
	beq @3
	b @4
	@5:
	cmplw r24, r23
	beq @6
	lhz r0, 0x14(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq @6
	addi r3, r24, 0x18
	addi r4, r23, 0x18
	bl PSVECDistance
	fmr f31, f1
	addi r3, r24, 0x18
	addi r4, r23, 0x18
	addi r5, r1, 0x90
	bl PSVECSubtract
	lfs f0, 0x4c(r24)
	fcmpo cr0, f31, f0
	cror eq, lt, eq
	bne @6
	addi r3, r1, 0x90
	bl PSVECMag
	lfs f0, float_0_8041c588(r0)
	fcmpu cr0, f0, f1
	bne @7
	lfs f0, float_1_8041c590(r0)
	stfs f0, 0x90(r1)
	@7:
	addi r3, r1, 0x90
	mr r4, r3
	bl PSVECNormalize
	lfs f0, float_0_8041c588(r0)
	addi r3, r1, 0x90
	lfs f1, float_0p5_8041c594(r0)
	mr r4, r3
	stfs f0, 0x94(r1)
	bl PSVECScale
	addi r3, r24, 0x3c
	addi r4, r1, 0x90
	mr r5, r3
	bl PSVECAdd
	addi r3, r23, 0x3c
	addi r4, r1, 0x90
	mr r5, r3
	bl PSVECSubtract
	@6:
	addi r23, r23, 0xc0
	@4:
	lwz r0, 0xc(r26)
	lwz r3, 0x0(r26)
	mulli r0, r0, 0xc0
	add r0, r3, r0
	cmplw r23, r0
	blt @5
	@3:
	addi r24, r24, 0xc0
	@1:
	lwz r0, 0xc(r26)
	lwz r23, 0x0(r26)
	mulli r0, r0, 0xc0
	add r0, r23, r0
	cmplw r24, r0
	blt @2
	b @8
	@9:
	lhz r0, 0x14(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq @10
	addi r3, r23, 0x30
	addi r4, r23, 0x18
	addi r5, r1, 0x90
	bl PSVECSubtract
	addi r3, r1, 0x90
	bl PSVECMag
	lfs f2, float_0p8_8041c598(r0)
	lfs f0, 0x4c(r23)
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	ble @10
	addi r3, r1, 0x90
	mr r4, r3
	bl PSVECNormalize
	lfs f0, float_0_8041c588(r0)
	addi r3, r1, 0x90
	lfs f1, float_0p5_8041c594(r0)
	mr r4, r3
	stfs f0, 0x94(r1)
	bl PSVECScale
	addi r3, r23, 0x3c
	addi r4, r1, 0x90
	mr r5, r3
	bl PSVECAdd
	@10:
	addi r23, r23, 0xc0
	@8:
	lwz r0, 0xc(r26)
	lwz r25, 0x0(r26)
	mulli r0, r0, 0xc0
	add r0, r25, r0
	cmplw r23, r0
	blt @9
	addi r30, r1, 0x38
	addi r29, r1, 0x34
	addi r28, r1, 0x2c
	addi r27, r1, 0x28
	b @11
	@12:
	lhz r0, 0x14(r25)
	rlwinm. r0, r0, 0, 29, 29
	beq @13
	addi r3, r25, 0x3c
	bl PSVECMag
	fmr f31, f1
	lfs f0, float_0_8041c588(r0)
	fcmpu cr0, f31, f0
	beq @13
	lfs f0, float_10_8041c59c(r0)
	fcmpo cr0, f31, f0
	ble @14
	lfs f0, float_5_8041c5a0(r0)
	addi r3, r25, 0x3c
	mr r4, r3
	fdivs f1, f0, f31
	bl PSVECScale
	lfs f31, float_5_8041c5a0(r0)
	@14:
	lwz r0, 0x1c(r25)
	addi r3, r25, 0x3c
	lwz r5, 0x18(r25)
	addi r4, r1, 0x6c
	stw r0, 0x64(r1)
	lwz r0, 0x20(r25)
	lfs f1, 0x64(r1)
	lfs f0, float_1_8041c590(r0)
	stw r5, 0x60(r1)
	fadds f0, f1, f0
	stw r0, 0x68(r1)
	stfs f0, 0x64(r1)
	bl PSVECNormalize
	lhz r0, 0x14(r25)
	rlwinm. r0, r0, 0, 28, 28
	beq @15
	addi r3, r25, 0x18
	addi r4, r25, 0x3c
	mr r5, r3
	bl PSVECAdd
	addi r3, r25, 0x3c
	lfs f1, float_0p6_8041c5a4(r0)
	mr r4, r3
	bl PSVECScale
	b @13
	@15:
	lwz r3, 0x6c(r1)
	li r0, 0x0
	lwz r23, 0x70(r1)
	mr r5, r27
	lwz r24, 0x74(r1)
	mr r6, r28
	stw r3, 0x84(r1)
	mr r9, r29
	lwz r3, 0x60(r1)
	mr r10, r30
	lwz r12, 0x64(r1)
	addi r4, r1, 0x24
	lwz r11, 0x68(r1)
	addi r7, r1, 0x20
	stw r3, 0x78(r1)
	addi r8, r1, 0x30
	li r31, 0x1
	li r3, 0x0
	stw r12, 0x7c(r1)
	lfs f1, 0x78(r1)
	stw r11, 0x80(r1)
	lfs f2, 0x7c(r1)
	stw r23, 0x88(r1)
	lfs f3, 0x80(r1)
	stw r24, 0x8c(r1)
	stw r0, 0xb8(r25)
	stw r0, 0xb4(r25)
	stfs f31, 0x20(r1)
	lfs f4, 0x84(r1)
	lfs f5, 0x88(r1)
	lfs f6, 0x8c(r1)
	bl hitCheckFilter
	stw r3, 0xb4(r25)
	lwz r0, 0xb4(r25)
	cmplwi r0, 0x0
	bne @16
	addi r3, r25, 0x18
	addi r4, r25, 0x3c
	mr r5, r3
	bl PSVECAdd
	b @17
	@16:
	lwz r6, 0x18(r25)
	addi r3, r25, 0x18
	lwz r0, 0x1c(r25)
	mr r5, r3
	addi r4, r25, 0x3c
	stw r6, 0x48(r1)
	stw r0, 0x4c(r1)
	lwz r0, 0x20(r25)
	stw r0, 0x50(r1)
	bl PSVECAdd
	lfs f1, float_0_8041c588(r0)
	lfs f0, 0x40(r25)
	fcmpu cr0, f1, f0
	bne @18
	stfs f1, 0x34(r1)
	@18:
	addi r3, r1, 0x30
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x84
	addi r4, r1, 0x30
	addi r5, r1, 0x54
	bl C_VECReflect
	fmr f1, f31
	addi r3, r1, 0x54
	addi r4, r25, 0x3c
	bl PSVECScale
	addi r3, r1, 0x84
	addi r4, r1, 0x30
	li r31, 0x0
	bl PSVECDotProduct
	lfs f2, 0x20(r1)
	addi r3, r1, 0x30
	lfs f0, float_0p1_8041c5a8(r0)
	mr r4, r3
	fsubs f2, f31, f2
	fneg f2, f2
	fmadds f1, f1, f2, f0
	bl PSVECScale
	addi r3, r25, 0x18
	addi r4, r1, 0x30
	mr r5, r3
	bl PSVECAdd
	addi r3, r25, 0x18
	addi r4, r1, 0x48
	addi r5, r1, 0x3c
	bl PSVECSubtract
	addi r3, r1, 0x3c
	bl PSVECMag
	frsp f2, f1
	lfs f0, float_0_8041c588(r0)
	stfs f1, 0x20(r1)
	fcmpo cr0, f2, f0
	ble @17
	addi r3, r1, 0x3c
	mr r4, r3
	bl PSVECNormalize
	lfs f1, float_1_8041c590(r0)
	addi r4, r1, 0x8
	lfs f0, 0x4c(r1)
	addi r5, r1, 0xc
	lwz r8, 0x48(r1)
	addi r6, r1, 0x10
	lwz r3, 0x4c(r1)
	fadds f2, f1, f0
	lwz r0, 0x50(r1)
	addi r7, r1, 0x20
	stw r8, 0x78(r1)
	addi r8, r1, 0x14
	lfs f1, 0x48(r1)
	stw r3, 0x7c(r1)
	addi r9, r1, 0x18
	lfs f3, 0x50(r1)
	addi r10, r1, 0x1c
	stw r0, 0x80(r1)
	li r3, 0x0
	lfs f4, 0x3c(r1)
	lfs f5, 0x40(r1)
	lfs f6, 0x44(r1)
	bl hitCheckFilter
	stw r3, 0xb8(r25)
	lwz r0, 0xb8(r25)
	cmplwi r0, 0x0
	beq @17
	lwz r3, 0x48(r1)
	lwz r0, 0x4c(r1)
	stw r3, 0x18(r25)
	stw r0, 0x1c(r25)
	lwz r0, 0x50(r1)
	stw r0, 0x20(r25)
	@17:
	cmpwi r31, 0x0
	beq @13
	addi r3, r25, 0x3c
	lfs f1, float_0p6_8041c5a4(r0)
	mr r4, r3
	bl PSVECScale
	@13:
	addi r25, r25, 0xc0
	@11:
	lwz r0, 0xc(r26)
	lwz r3, 0x0(r26)
	mulli r0, r0, 0xc0
	add r0, r3, r0
	cmplw r25, r0
	blt @12
	psq_l f31, 0xd8(r1), 0, 0
	lfd f31, 0xd0(r1)
	lmw r23, 0xac(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}
// clang-format on
#endif
#pragma force_active reset
