#ifdef NONMATCHING
// FAKE: whole-unit ASM-STOPGAP (C3b 2026-10-18): asm_inline.py + C3b aifix/rodatagen (.rodata/.sdata2/.sdata in target order, mt$544 as file-scope mt_544), unused inlines under NONMATCHING, force_active. C kept under NONMATCHING. See docs/FAKES.md.
#endif
#ifndef NONMATCHING
// FAKE: whole-unit ASM-STOPGAP (C3b 2026-10-18): asm_inline.py + C3b aifix/rodatagen (.rodata/.sdata2/.sdata in target order, mt_544 as file-scope mt_544), unused inlines under NONMATCHING, force_active. C kept under NONMATCHING. See docs/FAKES.md.
#endif
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
#ifndef NONMATCHING
#define EXT_LIT(sym, val) (sym)

#endif
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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 evt_nannpcwork_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_color(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_shadow_position(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_func(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_ppflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_jump_position(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_move_position2(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_get_work(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_work(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_animtbl(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_size(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_hosei_position(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_set_subfunc(EventEntry* event, BOOL isFirstCall);
s32 evt_nannpc_init(EventEntry* event, BOOL isFirstCall);
#endif

s32 gap_08_8041899C_sbss;
NanNPCWork* nanNPCWork;
char makestring[16];

void nannpc_ext_disp();
void nannpc_ext_shadow_disp();
void nannpc_ext_dispent();
void nannpc_ext_main();
void nannpc_ext_main_sub();
void nannpc_ext_init();

static inline NanNPC* nanNPCSearch(char* name) {
    s32 i;
    NanNPC* p;
    NanNPCWork* w = nanNPCWork;
    for (i = 0; i < w->num; i++) {
        p = &w->npc[i];
        if (!((u32)name & 0x80000000)) {
#ifdef NONMATCHING
            sprintf(makestring, "%06x", name);
#endif
#ifndef NONMATCHING
            sprintf(makestring, EXT_LIT((char*)str_8041C574, "%06x"), name);
#endif
            name = makestring;
        }
        if (!strcmp((char*)p->name, name)) {
            return p;
        }
    }
    return NULL;
}

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
#ifndef NONMATCHING
void C_VECReflect(const Vec* src, const Vec* normal, Vec* dst);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void PSMTXIdentity(Mtx m);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDistance(const Vec* a, const Vec* b);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECNormalize(const Vec* src, Vec* dst);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void *memset(void *dest, int ch, size_t count);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
void nanNPCOption(void);
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
#ifndef NONMATCHING
s32 nannpc_zcompare(NanNPCSort* a, NanNPCSort* b);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
void nannpc_ext_disp();
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
#ifndef NONMATCHING
void nannpc_ext_shadow_disp();
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
#ifndef NONMATCHING
void nannpc_ext_init();
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
#ifndef NONMATCHING
void nannpc_ext_main_sub();
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
#ifndef NONMATCHING
void nannpc_ext_main_sub_fast();
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
#ifndef NONMATCHING
void nannpc_ext_main();
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
#ifndef NONMATCHING
void nannpc_ext_dispent();
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
#ifndef NONMATCHING
s32 evt_nannpc_init(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_nannpc_set_subfunc(EventEntry* event, BOOL isFirstCall);
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
#endif
#ifndef NONMATCHING
s32 evt_nannpc_entry(EventEntry *event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
  return 2;
}
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_position(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_position) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_get_position(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_hosei_position(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_size(EventEntry* event, BOOL isFirstCall);

void evt_nannpc_set_animtbl_sub(NanNPC* npc, s16* tbl);

s32 evt_nannpc_set_animtbl(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_dir(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_work(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_get_work(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_move_position2(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_jump_position(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_flag_onoff(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_ppflag_onoff(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_func(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_shadow_position(EventEntry* event, BOOL isFirstCall);

s32 evt_nannpc_set_color(EventEntry* event, BOOL isFirstCall);

#pragma force_active on
#pragma explicit_zero_data on
s32 evt_nannpcwork_flag_onoff(EventEntry* event, BOOL isFirstCall);
#pragma explicit_zero_data reset
#pragma force_active reset

#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset
#pragma force_active reset

#pragma force_active reset

s32 evt_nannpc_set_position(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_get_position) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_get_position(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    evtSetFloat(event, args[1], npc->pos.x);
    evtSetFloat(event, args[2], npc->pos.y);
    evtSetFloat(event, args[3], npc->pos.z);
    return 2;
}

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_hosei_position) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_hosei_position(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->hosei.x = evtGetFloat(event, args[1]);
    npc->hosei.y = evtGetFloat(event, args[2]);
    npc->hosei.z = evtGetFloat(event, args[3]);
    return 2;
}

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_size) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_size(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->sizeX = evtGetFloat(event, args[1]);
    npc->sizeY = evtGetFloat(event, args[2]);
    return 2;
}

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

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_animtbl) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_animtbl(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_dir) {
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->dir = evtGetValue(event, args[1]);
    return 2;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_nannpc_set_dir(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[4];
	asm volatile {
		mr r25, r3
		opword 0x83430018
		opword 0x809A0000
		bl evtGetValue
		opword 0x3BA00000
		lwz r31, nanNPCWork(r13)
		opword 0x7C7C1B78
		opword 0x7FBBEB78
		opword 0x4800004C
		opword 0x807F0000
		opword 0x57800001
		opword 0x7FC3DA14
		opword 0x4082001C
		opword 0x7F85E378
		la r3, makestring(r13)
		la r4, str_8041C574(r2)
		opword 0x4CC63182
		bl sprintf
		la r28, makestring(r13)
		opword 0x7FC3F378
		opword 0x7F84E378
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x3B7B00C0
		opword 0x3BBD0001
		opword 0x801F000C
		opword 0x7C1D0000
		opword 0x4180FFB0
		opword 0x3BC00000
		opword 0x809A0004
		opword 0x7F23CB78
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061000C
		lis r4, double_to_int_802f3040@ha
		lfd f1, double_to_int_802f3040@l(r4)
		opword 0x38600002
		stw r0, _af_pad+0(r1)
		opword 0xC8010008
		opword 0xEC000828
		opword 0xD01E0060
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_work) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_work(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    s32 idx = evtGetValue(event, args[1]);
    npc->work[idx] = evtGetValue(event, args[2]);
    return 2;
}

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_get_work) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_get_work(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[2], npc->work[evtGetValue(event, args[1])]);
    return 2;
}

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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_nannpc_move_position2(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[64];
	asm volatile {
		opword 0x7C7A1B78
		opword 0x7C9B2378
		opword 0x83830018
		opword 0x809C0000
		bl evtGetValue
		opword 0x3BC00000
		lwz r29, nanNPCWork(r13)
		opword 0x7C791B78
		opword 0x7FD8F378
		opword 0x4800004C
		opword 0x807D0000
		opword 0x57200001
		opword 0x7FE3C214
		opword 0x4082001C
		opword 0x7F25CB78
		la r3, makestring(r13)
		la r4, str_8041C574(r2)
		opword 0x4CC63182
		bl sprintf
		la r25, makestring(r13)
		opword 0x7FE3FB78
		opword 0x7F24CB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x3B1800C0
		opword 0x3BDE0001
		opword 0x801D000C
		opword 0x7C1E0000
		opword 0x4180FFB0
		opword 0x3BE00000
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820010
		opword 0x83C30038
		opword 0x83A3003C
		opword 0x4800000C
		opword 0x83C30040
		opword 0x83A30044
		opword 0x809C0004
		opword 0x7F43D378
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		stw r3, _af_pad+44(r1)
		lis r4, double_to_int_802f3040@ha
		lfd f1, double_to_int_802f3040@l(r4)
		opword 0x7F43D378
		opword 0x90010030
		opword 0xC8010030
		opword 0xEC000828
		opword 0xD0010020
		opword 0x809C0008
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061003C
		lis r4, double_to_int_802f3040@ha
		lfd f1, double_to_int_802f3040@l(r4)
		opword 0x7F43D378
		opword 0x90010038
		opword 0xC8010038
		opword 0xEC000828
		opword 0xD0010024
		opword 0x809C000C
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610044
		lis r4, double_to_int_802f3040@ha
		lfd f1, double_to_int_802f3040@l(r4)
		opword 0x7F43D378
		opword 0x90010040
		opword 0xC8010040
		opword 0xEC000828
		opword 0xD0010028
		opword 0x809C0010
		bl evtGetFloat
		fmr f31, f1
		opword 0x2C1B0000
		opword 0x41820024
		opword 0x93BA019C
		opword 0x93DA0198
		opword 0x807F0018
		opword 0x801F001C
		opword 0x907F0088
		opword 0x901F008C
		opword 0x801F0020
		opword 0x901F0090
		opword 0x38610020
		opword 0x389F0088
		opword 0x38A10014
		bl PSVECSubtract
		opword 0x38610014
		bl PSVECMag
		lfs f0, float_1000_8041c580(r2)
		opword 0x3C608000
		opword 0x800300F8
		opword 0x3C601062
		opword 0xEC000072
		opword 0x809A019C
		opword 0x5400F0BE
		opword 0x38634DD3
		opword 0x7C030016
		opword 0x7C84E850
		opword 0xEC00F824
		opword 0x7C83FE70
		opword 0x38A00000
		opword 0x5406D1BE
		opword 0xFC00001E
		opword 0xD8010040
		lwz r24, 0x44(r1)
		bl __div2u
		opword 0x7C9A2378
		opword 0x3CA04330
		opword 0x6F438000
		opword 0x6F008000
		lis r4, double_to_int_802f3040@ha
		opword 0x9061003C
		addi r6, r4, double_to_int_802f3040@l
		opword 0x38610014
		opword 0x90A10038
		opword 0x38810008
		opword 0xC8460000
		opword 0xC8010038
		opword 0x90010034
		opword 0xEC201028
		opword 0x90A10030
		opword 0xC8010030
		opword 0xEC001028
		opword 0xEC210024
		bl PSVECScale
		opword 0x7C1AC000
		opword 0x4080001C
		opword 0x387F0088
		opword 0x38810008
		opword 0x38BF0018
		bl PSVECAdd
		opword 0x38600000
		opword 0x48000020
		opword 0x80810020
		opword 0x38600002
		opword 0x80010024
		opword 0x909F0018
		opword 0x901F001C
		opword 0x80010028
		opword 0x901F0020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_nannpc_jump_position(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[32];
	asm volatile {
		opword 0x7C7C1B78
		opword 0x7C9D2378
		opword 0x83C30018
		opword 0x809E0000
		bl evtGetValue
		opword 0x3B400000
		lwz r27, nanNPCWork(r13)
		opword 0x7C791B78
		mr r24, r26
		opword 0x4800004C
		opword 0x807B0000
		opword 0x57200001
		opword 0x7FE3C214
		opword 0x4082001C
		opword 0x7F25CB78
		la r3, makestring(r13)
		la r4, str_8041C574(r2)
		opword 0x4CC63182
		bl sprintf
		la r25, makestring(r13)
		opword 0x7FE3FB78
		opword 0x7F24CB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x3B1800C0
		opword 0x3B5A0001
		opword 0x801B000C
		opword 0x7C1A0000
		opword 0x4180FFB0
		opword 0x3BE00000
		opword 0x809E0004
		opword 0x7F83E378
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802f3040@ha
		stw r3, _af_pad+4(r1)
		addi r5, r4, double_to_int_802f3040@l
		opword 0x809E0008
		opword 0x90010008
		opword 0x7F83E378
		opword 0xC8250000
		opword 0xC8010008
		opword 0xEFE00828
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802f3040@ha
		opword 0x90610014
		addi r5, r4, double_to_int_802f3040@l
		opword 0x809E000C
		opword 0x90010010
		opword 0x7F83E378
		opword 0xC8250000
		opword 0xC8010010
		opword 0xEFC00828
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802f3040@ha
		opword 0x9061001C
		addi r5, r4, double_to_int_802f3040@l
		opword 0x809E0010
		opword 0x90010018
		opword 0x7F83E378
		opword 0xC8250000
		opword 0xC8010018
		fsubs f29, f0, f1
		bl evtGetValue
		opword 0x809E0014
		opword 0x7C7E1B78
		opword 0x7F83E378
		bl evtGetValue
		opword 0x6C608000
		opword 0x3C804330
		opword 0x90010024
		lis r3, double_to_int_802f3040@ha
		lfd f2, double_to_int_802f3040@l(r3)
		opword 0x2C1D0000
		opword 0x90810020
		opword 0xC8010020
		opword 0xEC201028
		opword 0x41820088
		lwz r3, gp(r13)
		lfs f0, float_neg4_8041c57c(r2)
		opword 0x80030038
		opword 0x8063003C
		opword 0xEC000072
		opword 0x90810008
		opword 0x907F0054
		opword 0x901F0050
		opword 0xC03F0018
		opword 0xFC20081E
		opword 0xD8210020
		opword 0x80010024
		opword 0x901F0068
		opword 0xC03F001C
		opword 0xFC20081E
		opword 0xD8210018
		opword 0x8001001C
		opword 0x901F006C
		opword 0xC03F0020
		opword 0xFC20081E
		opword 0xD8210010
		opword 0x80010014
		opword 0x901F0070
		opword 0xD01C007C
		opword 0x801F006C
		opword 0xC01C007C
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC3E0828
		opword 0xEC010028
		opword 0xD01C0080
		opword 0x3C608000
		lwz r4, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x38634DD3
		opword 0x80BF0054
		opword 0x5400F0BE
		opword 0x8084003C
		opword 0x7C030016
		opword 0x7C652050
		opword 0x5400D1BE
		opword 0x7C830396
		opword 0x7C04F000
		opword 0x408000E8
		opword 0x3CC04330
		opword 0x6C808000
		opword 0x90010024
		opword 0x6FC38000
		lis r5, double_to_int_802f3040@ha
		opword 0x801F0068
		opword 0x90C10020
		opword 0xFC40F890
		lfd f3, double_to_int_802f3040@l(r5)
		opword 0x6C008000
		opword 0xC8010020
		opword 0x7C982378
		opword 0x9061001C
		opword 0xEC201828
		opword 0x7FC5F378
		opword 0x90C10018
		opword 0x38600000
		opword 0xC8010018
		opword 0x90010014
		opword 0xEC001828
		opword 0x90C10010
		opword 0xEFC10024
		opword 0xC8010010
		opword 0xEC201828
		bl intplGetValue
		opword 0xD03F0018
		opword 0x3C004330
		lis r3, double_to_int_802f3040@ha
		opword 0xFC40E890
		opword 0x80BF0070
		opword 0x7F04C378
		opword 0x90010008
		opword 0x6CA08000
		lfd f1, double_to_int_802f3040@l(r3)
		opword 0x9001000C
		opword 0x7FC5F378
		opword 0x38600000
		opword 0xC8010008
		opword 0xEC200828
		bl intplGetValue
		opword 0xD03F0020
		opword 0x3C004330
		lis r4, double_to_int_802f3040@ha
		opword 0x38600000
		opword 0x80BF006C
		opword 0x90010028
		opword 0x6CA08000
		opword 0xC07C007C
		opword 0x9001002C
		opword 0xC05C0080
		lfd f1, double_to_int_802f3040@l(r4)
		opword 0xC8010028
		opword 0xEC4317BA
		opword 0xEC000828
		opword 0xEC1E00BA
		opword 0xD01F001C
		opword 0x48000014
		opword 0xD3FF0018
		opword 0x38600002
		opword 0xD3DF001C
		opword 0xD3BF0020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_flag_onoff) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_flag_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_ppflag_onoff) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_ppflag_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_func) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_func(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->func = (void (*)(NanNPC*))evtGetValue(event, args[1]);
    return 2;
}

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_shadow_position) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_shadow_position(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->pose->flags |= 0x10;
    npc->pose->shadowY = evtGetFloat(event, args[1]);
    return 2;
}

#ifdef NONMATCHING
USER_FUNC(evt_nannpc_set_color) {
#endif
#ifndef NONMATCHING
s32 evt_nannpc_set_color(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->color.r = evtGetValue(event, args[1]);
    npc->color.g = evtGetValue(event, args[2]);
    npc->color.b = evtGetValue(event, args[3]);
    npc->color.a = evtGetValue(event, args[4]);
    return 2;
}

#ifdef NONMATCHING
#pragma force_active on
#pragma explicit_zero_data on
USER_FUNC(evt_nannpcwork_flag_onoff) {
#endif
#ifndef NONMATCHING
#pragma defer_codegen off
s32 evt_nannpcwork_flag_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
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
#ifdef NONMATCHING
#pragma explicit_zero_data reset
#pragma force_active reset
#endif

#ifndef NONMATCHING
#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
	lwz r23, nanNPCWork(r13)
	mr r25, r3
	li r24, 0x0
	li r26, 0x0
	clrrwi r29, r3, 31
	b L_af_1
L_af_2:
	lwz r0, 0x0(r23)
	cmplwi r29, 0x0
	mr r27, r25
	add r30, r0, r26
	bne L_af_3
	mr r5, r25
	la r3, makestring(r13)
	la r4, str_8041C574(r2)
	crclr 6
	bl sprintf
	la r27, makestring(r13)
L_af_3:
	mr r3, r30
	mr r4, r27
	bl strcmp
	lwz r0, 0x10(r30)
	cmplwi r0, 0x0
	bne L_af_4
	mr r3, r30
	mr r4, r27
	bl strcpy
	slwi r0, r24, 5
	li r4, 0x0
	add r0, r28, r0
	lfs f1, float_32_8041c584(r2)
	stw r0, 0x10(r30)
	lfs f0, float_0_8041c588(r2)
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
	lwz r0, dat_8041c570(r2)
	stw r0, 0xbc(r30)
	b L_af_5
L_af_4:
	addi r26, r26, 0xc0
	addi r24, r24, 0x1
L_af_1:
	lwz r0, 0xc(r23)
	cmpw r24, r0
	blt L_af_2
L_af_5:
	lmw r23, 0xc(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void nanNPCOption(void) {
	char _af_pad[156];
	asm volatile {
		lwz r26, nanNPCWork(r13)
		opword 0x831A0000
		opword 0x480000D8
		opword 0xA0180014
		opword 0x5400077B
		opword 0x418200C8
		opword 0x480000AC
		opword 0x7C18B840
		opword 0x418200A0
		opword 0xA0170014
		opword 0x5400077B
		opword 0x41820094
		opword 0x38780018
		opword 0x38970018
		bl PSVECDistance
		opword 0xFFE00890
		opword 0x38780018
		opword 0x38970018
		la r5, _af_pad+136
		bl PSVECSubtract
		opword 0xC018004C
		opword 0xFC1F0040
		opword 0x4C401382
		opword 0x40820064
		opword 0x38610090
		bl PSVECMag
		lfs f0, float_0_8041c588(r2)
		opword 0xFC000800
		opword 0x4082000C
		lfs f0, float_1_8041c590(r2)
		opword 0xD0010090
		opword 0x38610090
		opword 0x7C641B78
		bl PSVECNormalize
		lfs f0, float_0_8041c588(r2)
		opword 0x38610090
		lfs f1, float_0p5_8041c594(r2)
		opword 0x7C641B78
		opword 0xD0010094
		bl PSVECScale
		opword 0x3878003C
		opword 0x38810090
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x3877003C
		opword 0x38810090
		opword 0x7C651B78
		bl PSVECSubtract
		opword 0x3AF700C0
		opword 0x801A000C
		opword 0x807A0000
		opword 0x1C0000C0
		opword 0x7C030214
		opword 0x7C170040
		opword 0x4180FF44
		opword 0x3B1800C0
		opword 0x801A000C
		lwz r23, 0x0(r26)
		opword 0x1C0000C0
		opword 0x7C170214
		opword 0x7C180040
		opword 0x4180FF18
		opword 0x48000074
		opword 0xA0170014
		opword 0x5400077B
		opword 0x41820064
		opword 0x38770030
		opword 0x38970018
		opword 0x38A10090
		bl PSVECSubtract
		opword 0x38610090
		bl PSVECMag
		lfs f2, float_0p8_8041c598(r2)
		opword 0xC017004C
		opword 0xEC020032
		opword 0xFC010040
		opword 0x40810038
		opword 0x38610090
		opword 0x7C641B78
		bl PSVECNormalize
		lfs f0, float_0_8041c588(r2)
		opword 0x38610090
		lfs f1, float_0p5_8041c594(r2)
		opword 0x7C641B78
		opword 0xD0010094
		bl PSVECScale
		opword 0x3877003C
		opword 0x38810090
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x3AF700C0
		opword 0x801A000C
		opword 0x833A0000
		opword 0x1C0000C0
		opword 0x7C190214
		opword 0x7C170040
		opword 0x4180FF7C
		opword 0x3BC10038
		opword 0x3BA10034
		opword 0x3B81002C
		opword 0x3B610028
		opword 0x480002D4
		opword 0xA0190014
		opword 0x5400077B
		opword 0x418202C4
		opword 0x3879003C
		bl PSVECMag
		opword 0xFFE00890
		lfs f0, float_0_8041c588(r2)
		opword 0xFC1F0000
		opword 0x418202AC
		lfs f0, float_10_8041c59c(r2)
		opword 0xFC1F0040
		opword 0x4081001C
		lfs f0, float_5_8041c5a0(r2)
		opword 0x3879003C
		opword 0x7C641B78
		opword 0xEC20F824
		bl PSVECScale
		lfs f31, float_5_8041c5a0(r2)
		opword 0x8019001C
		opword 0x3879003C
		opword 0x80B90018
		opword 0x3881006C
		opword 0x90010064
		opword 0x80190020
		opword 0xC0210064
		lfs f0, float_1_8041c590(r2)
		opword 0x90A10060
		opword 0xEC01002A
		opword 0x90010068
		opword 0xD0010064
		bl PSVECNormalize
		opword 0xA0190014
		opword 0x54000739
		opword 0x41820028
		opword 0x38790018
		opword 0x3899003C
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x3879003C
		lfs f1, float_0p6_8041c5a4(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x48000224
		opword 0x8061006C
		opword 0x38000000
		opword 0x82E10070
		opword 0x7F65DB78
		opword 0x83010074
		opword 0x7F86E378
		opword 0x90610084
		opword 0x7FA9EB78
		opword 0x80610060
		opword 0x7FCAF378
		opword 0x81810064
		opword 0x38810024
		opword 0x81610068
		opword 0x38E10020
		opword 0x90610078
		opword 0x39010030
		opword 0x3BE00001
		opword 0x38600000
		opword 0x9181007C
		opword 0xC0210078
		opword 0x91610080
		opword 0xC041007C
		opword 0x92E10088
		opword 0xC0610080
		opword 0x9301008C
		opword 0x901900B8
		opword 0x901900B4
		opword 0xD3E10020
		opword 0xC0810084
		opword 0xC0A10088
		opword 0xC0C1008C
		bl hitCheckFilter
		opword 0x907900B4
		opword 0x801900B4
		opword 0x28000000
		opword 0x40820018
		opword 0x38790018
		opword 0x3899003C
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x48000168
		opword 0x80D90018
		opword 0x38790018
		opword 0x8019001C
		opword 0x7C651B78
		opword 0x3899003C
		opword 0x90C10048
		opword 0x9001004C
		opword 0x80190020
		opword 0x90010050
		bl PSVECAdd
		lfs f1, float_0_8041c588(r2)
		opword 0xC0190040
		opword 0xFC010000
		opword 0x40820008
		opword 0xD0210034
		opword 0x38610030
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x38610084
		opword 0x38810030
		opword 0x38A10054
		bl C_VECReflect
		opword 0xFC20F890
		opword 0x38610054
		opword 0x3899003C
		bl PSVECScale
		opword 0x38610084
		opword 0x38810030
		opword 0x3BE00000
		bl PSVECDotProduct
		opword 0xC0410020
		opword 0x38610030
		lfs f0, float_0p1_8041c5a8(r2)
		opword 0x7C641B78
		opword 0xEC5F1028
		opword 0xFC401050
		opword 0xEC2100BA
		bl PSVECScale
		opword 0x38790018
		opword 0x38810030
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x38790018
		opword 0x38810048
		opword 0x38A1003C
		bl PSVECSubtract
		opword 0x3861003C
		bl PSVECMag
		opword 0xFC400818
		lfs f0, float_0_8041c588(r2)
		opword 0xD0210020
		opword 0xFC020040
		opword 0x40810094
		opword 0x3861003C
		opword 0x7C641B78
		bl PSVECNormalize
		lfs f1, float_1_8041c590(r2)
		opword 0x38810008
		opword 0xC001004C
		opword 0x38A1000C
		opword 0x81010048
		opword 0x38C10010
		opword 0x8061004C
		opword 0xEC41002A
		opword 0x80010050
		opword 0x38E10020
		opword 0x91010078
		opword 0x39010014
		opword 0xC0210048
		opword 0x9061007C
		opword 0x39210018
		opword 0xC0610050
		opword 0x3941001C
		opword 0x90010080
		opword 0x38600000
		opword 0xC081003C
		opword 0xC0A10040
		opword 0xC0C10044
		bl hitCheckFilter
		opword 0x907900B8
		opword 0x801900B8
		opword 0x28000000
		opword 0x4182001C
		opword 0x80610048
		opword 0x8001004C
		opword 0x90790018
		opword 0x9019001C
		opword 0x80010050
		opword 0x90190020
		opword 0x2C1F0000
		opword 0x41820014
		opword 0x3879003C
		lfs f1, float_0p6_8041c5a4(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x3B3900C0
		opword 0x801A000C
		opword 0x807A0000
		opword 0x1C0000C0
		opword 0x7C030214
		opword 0x7C190040
		opword 0x4180FD1C
	}
}
#pragma pop

s32 nannpc_zcompare(NanNPCSort* a, NanNPCSort* b) {
    if (a->z < b->z) {
        return 1;
    }
    if (a->z > b->z) {
        return -1;
    }
    return 0;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void nannpc_ext_disp() {
	asm volatile {
		lwz r31, nanNPCWork(r13)
		opword 0x801F0010
		opword 0x540007FF
		opword 0x41820254
		bl extLoadVertex
		bl extLoadTexture
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C00002
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00004
		opword 0x38C00001
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		lfs f1, float_0_8041c588(r2)
		opword 0x38810008
		lwz r0, dat_8041c568(r2)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFC600890
		opword 0x90010008
		opword 0xFC800890
		bl GXSetFog
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600001
		bl GXSetNumTevStages
		bl extGetPoseNum
		opword 0x34E3FFFF
		opword 0x1CA700C0
		opword 0x54E61838
		opword 0x38670001
		opword 0x418000EC
		opword 0x5460F0BF
		opword 0x7C0903A6
		opword 0x418200B0
		opword 0x801F0004
		opword 0x809F0000
		opword 0x7D003214
		opword 0x38C6FFF8
		opword 0x90E80000
		opword 0x7C842A14
		opword 0x38E7FFFF
		opword 0x38A5FF40
		opword 0xC0040020
		opword 0xD0080004
		opword 0x801F0004
		opword 0x809F0000
		opword 0x7D003214
		opword 0x38C6FFF8
		opword 0x90E80000
		opword 0x7C842A14
		opword 0x38E7FFFF
		opword 0x38A5FF40
		opword 0xC0040020
		opword 0xD0080004
		opword 0x801F0004
		opword 0x809F0000
		opword 0x7D003214
		opword 0x38C6FFF8
		opword 0x90E80000
		opword 0x7C842A14
		opword 0x38E7FFFF
		opword 0x38A5FF40
		opword 0xC0040020
		opword 0xD0080004
		opword 0x801F0004
		opword 0x809F0000
		opword 0x7D003214
		opword 0x38C6FFF8
		opword 0x90E80000
		opword 0x7C842A14
		opword 0x38A5FF40
		opword 0x38E7FFFF
		opword 0xC0040020
		opword 0xD0080004
		opword 0x4200FF60
		opword 0x70630003
		opword 0x41820034
		opword 0x7C6903A6
		opword 0x801F0004
		opword 0x809F0000
		opword 0x7D003214
		opword 0x38C6FFF8
		opword 0x90E80000
		opword 0x7C842A14
		opword 0x38A5FF40
		opword 0x38E7FFFF
		opword 0xC0040020
		opword 0xD0080004
		opword 0x4200FFD8
		lis r4, nannpc_zcompare@ha
		opword 0x807F0004
		addi r6, r4, nannpc_zcompare@l
		opword 0x809F000C
		opword 0x38A00008
		bl qqsort
		bl extGetPoseNum
		opword 0x3BA3FFFF
		opword 0x57BE1838
		opword 0x4800003C
		opword 0x80BF0004
		opword 0x3881000C
		opword 0x80DF0000
		opword 0x38600001
		lwzx r28, r5, r30
		opword 0x1CBC00C0
		opword 0x380500BC
		opword 0x7C06002E
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x7F83E378
		bl extPoseDraw
		opword 0x3BDEFFF8
		opword 0x3BBDFFFF
		opword 0x2C1D0000
		opword 0x4080FFC4
		bl extLoadTextureExit
		opword 0x4800001C
		bl extLoadRenderMode
		bl extLoadVertex
		bl extLoadTexture
		bl extLoadTev
		bl extDraw
		bl extLoadTextureExit
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void nannpc_ext_shadow_disp() {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		la r3, mt_544(r13)
		opword 0x90010014
		bl extLoadShadowMtx
		bl extLoadShadowRenderMode
		bl extLoadShadowVertex
		bl extLoadShadowTev
		bl extDrawShadow
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void nannpc_ext_init() {
	asm volatile {
		bl extGetPosePtr
		mr r29, r3
		bl extGetPoseNum
		lfs f30, float_0_8041c588(r2)
		opword 0x3BC3FFFF
		lfs f31, float_neg1000_8041c58c(r2)
		opword 0x3BE00003
		opword 0x48000034
		opword 0x93FD0000
		opword 0xD3DD0004
		opword 0x807D000C
		bl PSMTXIdentity
		opword 0x807D000C
		opword 0x3BDEFFFF
		opword 0xD3C3000C
		opword 0x807D000C
		opword 0xD3E3001C
		opword 0x807D000C
		opword 0x3BBD0020
		opword 0xD3C3002C
		opword 0x2C1E0000
		opword 0x4080FFCC
	}
}
#pragma pop

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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void nannpc_ext_main_sub_fast() {
	asm volatile {
		lwz r28, nanNPCWork(r13)
		bl extGetPoseNum
		opword 0x3BC3FFFF
		opword 0x1FFE00C0
		opword 0x480000F8
		opword 0x801C0000
		opword 0x7FA0FA14
		opword 0x881D0000
		opword 0x7C000775
		opword 0x418200DC
		opword 0x819D0064
		opword 0x280C0000
		opword 0x41820010
		opword 0x7FA3EB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x80BD0058
		opword 0x28050000
		opword 0x41820030
		opword 0x7C1EF1D6
		lwz r4, gp(r13)
		opword 0xA87D005C
		opword 0x8084001C
		opword 0x7C840214
		opword 0x7C041B96
		opword 0x7C0019D6
		opword 0x7C002050
		opword 0x5400083C
		opword 0x7C0502AE
		opword 0xB01D005E
		opword 0xA81D005E
		opword 0x807D0010
		opword 0x90030010
		opword 0xC01D0060
		opword 0x807D0010
		opword 0xFC000050
		opword 0xD0030004
		opword 0xA01D0014
		opword 0x540007BD
		opword 0x41820034
		opword 0x807D0010
		lfs f1, float_0_8041c588(r2)
		opword 0x8063000C
		lfs f0, float_neg1000_8041c58c(r2)
		opword 0xD023000C
		opword 0x807D0010
		opword 0x8063000C
		opword 0xD003001C
		opword 0x807D0010
		opword 0x8063000C
		opword 0xD023002C
		opword 0x48000034
		opword 0x807D0010
		opword 0xC01D0018
		opword 0x8063000C
		opword 0xD003000C
		opword 0x807D0010
		opword 0xC01D001C
		opword 0x8063000C
		opword 0xD003001C
		opword 0x807D0010
		opword 0xC01D0020
		opword 0x8063000C
		opword 0xD003002C
		opword 0x3BFFFF40
		opword 0x3BDEFFFF
		opword 0x2C1E0000
		opword 0x4080FF08
	}
}
#pragma pop

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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void nannpc_ext_dispent() {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		lwz r3, nanNPCWork(r13)
		opword 0x80030010
		opword 0x540007FF
		opword 0x40820040
		lis r3, nannpc_ext_disp@ha
		lfs f1, float_0_8041c588(r2)
		addi r5, r3, nannpc_ext_disp@l
		opword 0x38800001
		opword 0x38600004
		opword 0x38C00000
		bl dispEntry
		lis r3, nannpc_ext_shadow_disp@ha
		lfs f1, float_0_8041c588(r2)
		addi r5, r3, nannpc_ext_shadow_disp@l
		opword 0x38800002
		opword 0x38600004
		opword 0x38C00000
		bl dispEntry
		opword 0x4800003C
		lis r3, nannpc_ext_disp@ha
		lfs f1, float_0_8041c588(r2)
		addi r5, r3, nannpc_ext_disp@l
		opword 0x38800002
		opword 0x38600004
		opword 0x38C00000
		bl dispEntry
		lis r3, nannpc_ext_shadow_disp@ha
		lfs f1, float_0_8041c588(r2)
		addi r5, r3, nannpc_ext_shadow_disp@l
		opword 0x38800002
		opword 0x38600004
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
s32 evt_nannpc_init(EventEntry* event, BOOL isFirstCall) {
	asm {
		lis r5, vec3_802f2ff8@ha
	}
	asm volatile {
		opword 0x7C992378
		mr r23, r3
		addi r30, r5, vec3_802f2ff8@l
		opword 0x83030018
		opword 0x80980000
		bl evtGetValue
		opword 0x80980004
		opword 0x7C7C1B78
		opword 0x7EE3BB78
		bl evtGetValue
		opword 0x80980008
		opword 0x7C7F1B78
		opword 0x7EE3BB78
		bl evtGetValue
		opword 0x8098000C
		opword 0x7C7B1B78
		opword 0x7EE3BB78
		bl evtGetValue
		lis r4, nannpc_ext_dispent@ha
		opword 0x2C190000
		addi r0, r4, nannpc_ext_dispent@l
		opword 0x7C7A1B78
		opword 0x7C190378
		opword 0x4182000C
		opword 0x38600000
		opword 0x4800025C
		opword 0x38600020
		bl _mapAlloc
		stw r3, nanNPCWork(r13)
		opword 0x38800000
		opword 0x38A00020
		bl memset
		lwz r29, nanNPCWork(r13)
		opword 0x7EE3BB78
		opword 0x80980010
		bl evtGetValue
		opword 0x907D000C
		opword 0x801D000C
		opword 0x1C6000C0
		bl _mapAlloc
		opword 0x907D0000
		opword 0x38800000
		opword 0x801D000C
		opword 0x807D0000
		opword 0x1CA000C0
		bl memset
		opword 0x801D000C
		opword 0x54031838
		bl _mapAlloc
		opword 0x907D0004
		opword 0x38800000
		opword 0x801D000C
		opword 0x807D0004
		opword 0x54051838
		bl memset
		opword 0x38600014
		bl _mapAlloc
		opword 0x907D0008
		opword 0x38800000
		opword 0x38A00014
		opword 0x807D0008
		bl memset
		opword 0x38800000
		lis r3, nannpc_ext_main_sub@ha
		opword 0x909D0014
		addi r0, r3, nannpc_ext_main_sub@l
		opword 0x281B0000
		lwz r3, nanNPCWork(r13)
		opword 0x90030018
		opword 0x909D001C
		opword 0x40820010
		lis r3, nannpc_ext_init@ha
		addi r0, r3, nannpc_ext_init@l
		opword 0x7C1B0378
		opword 0x281A0000
		opword 0x40820010
		lis r3, nannpc_ext_main@ha
		addi r0, r3, nannpc_ext_main@l
		opword 0x7C1A0378
		opword 0x807D000C
		opword 0x7F84E378
		opword 0x7F65DB78
		opword 0x7F46D378
		opword 0x7F27CB78
		bl extEntry
		lfs f1, float_32_8041c584(r2)
		opword 0x38C00000
		lfs f0, float_0_8041c588(r2)
		opword 0x38A00000
		opword 0x4800009C
		opword 0x801D0000
		opword 0x38800000
		opword 0x38C60001
		opword 0x7CE02A14
		opword 0x38A500C0
		opword 0x98870000
		opword 0x90870010
		opword 0xB0870014
		opword 0xB0870016
		opword 0x807E0000
		opword 0x801E0004
		opword 0x90670018
		opword 0x9007001C
		opword 0x801E0008
		opword 0x90070020
		opword 0x807E000C
		opword 0x801E0010
		opword 0x90670030
		opword 0x90070034
		opword 0x801E0014
		opword 0x90070038
		opword 0x807E0018
		opword 0x801E001C
		opword 0x90670024
		opword 0x90070028
		opword 0x801E0020
		opword 0x9007002C
		opword 0xD0270048
		opword 0xD027004C
		opword 0x90870054
		opword 0x90870050
		opword 0x90870058
		opword 0xB087005C
		opword 0xB087005E
		opword 0xD0070060
		opword 0x90870064
		lwz r0, dat_8041c56c(r2)
		opword 0x900700BC
		opword 0x801D000C
		opword 0x7C060000
		opword 0x4180FF60
		opword 0x281F0000
		opword 0x4082000C
		opword 0x38600002
		opword 0x480000A8
		opword 0xA81F0000
		opword 0x2C00FFFF
		opword 0x41820098
		opword 0x807D0008
		opword 0xB0030000
		opword 0xA81F0002
		opword 0x807D0008
		opword 0xB0030002
		opword 0xA81F0004
		opword 0x2C00FFFF
		opword 0x41820078
		opword 0x807D0008
		opword 0xB0030004
		opword 0xA81F0006
		opword 0x807D0008
		opword 0xB0030006
		opword 0xA81F0008
		opword 0x2C00FFFF
		opword 0x41820058
		opword 0x807D0008
		opword 0xB0030008
		opword 0xA81F000A
		opword 0x807D0008
		opword 0xB003000A
		opword 0xA81F000C
		opword 0x2C00FFFF
		opword 0x41820038
		opword 0x807D0008
		opword 0xB003000C
		opword 0xA81F000E
		opword 0x807D0008
		opword 0xB003000E
		opword 0xA81F0010
		opword 0x2C00FFFF
		opword 0x41820018
		opword 0x807D0008
		opword 0xB0030010
		opword 0xA81F0012
		opword 0x807D0008
		opword 0xB0030012
		opword 0x38600002
	}
}
#pragma pop

s32 evt_nannpc_set_subfunc(EventEntry* event, BOOL isFirstCall) {
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


// literal pool in target order (asmfake --minimal)
#endif
#pragma force_active on
#ifdef NONMATCHING
#pragma explicit_zero_data on
#pragma explicit_zero_data reset
#pragma force_active reset
#endif

#ifdef NONMATCHING
#pragma force_active reset
#endif
