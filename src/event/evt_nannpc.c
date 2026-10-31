// Script commands for crowd NPCs (nannpc): many simple sprite NPCs drawn through extdrv.
#include "evt/evt_cmd.h"
#include "evt/evt_nannpc.h"
#include "driver/extdrv.h"
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
#include "libc_decls.h"
#include "version.h"

static s32 nannpc_zcompare(const void* a, const void* b);

NanNPCWork* nanNPCWork;
char makestring[16];

#if VERSION <= VERSION_DEMO_US
/**
 * The demo turns the name into a string in a helper (same code, other register order).
 * Demo only: in the other versions the helper's "%06x" literal would move ahead in the string pool even unused.
 */
static inline char* nanNPCEntryName(char* name) {
    if (!((EvtWord)name & 0x80000000)) {
        sprintf(makestring, "%06x", name);
        name = makestring;
    }
    return name;
}

/** the demo search through that helper */
static inline NanNPC* nanNPCSearch2(char* name) {
    s32 i;
    NanNPC* p;
    NanNPCWork* w = nanNPCWork;
    for (i = 0; i < w->num; i++) {
        p = &w->npc[i];
        name = nanNPCEntryName(name);
        if (!strcmp((char*)p->name, name)) {
            return p;
        }
    }
    return NULL;
}
#endif

/**
 * Finds the crowd NPC with the given name.
 * Names are strings; a value without the top address bit is treated as a number
 * and looked up by its six-digit hex form, so scripts can name crowd NPCs by index. NULL if none matches.
 */
static inline NanNPC* nanNPCSearch(char* name) {
    s32 i;
    NanNPC* p;
    NanNPCWork* w = nanNPCWork;
    for (i = 0; i < w->num; i++) {
        p = &w->npc[i];
        if (!((EvtWord)name & 0x80000000)) {
            sprintf(makestring, "%06x", name);
            name = makestring;
        }
        if (!strcmp((char*)p->name, name)) {
            return p;
        }
    }
    return NULL;
}

/**
 * Moves crowd NPC r by its move vector, sliding off map collision:
 * a hit reflects the motion off the wall and pushes the NPC clear, and the move vector decays by 0.6 per frame.
 * NPCs with flag 0x8 move without collision.
 */
static inline void nanNPCHitMove(NanNPC* r, f32 mag) {
    s32 clear;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 d20;
    Vec h;
    Vec n;
    Vec v3c;
    Vec v48;
    Vec v54;
    Vec v60;
    Vec v6c;
    Vec v78;
    Vec v84;
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
            {
                f32 dot = PSVECDotProduct(&v84, &n);
                PSVECScale(&n, &n, dot * -(mag - d20) + 0.1f);
            }
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
                    r->pos = v48; // v78 == v48 here; the target reads v48 and keeps the dead v78 copy
                }
            }
        }
        if (clear) {
            PSVECScale(&r->move, &r->move, 0.6f);
        }
    }
}

// FAKE: opt_dead_assignments off keeps the dead v78 = v48 struct copy in the inlined nanNPCHitMove (the target stores it, never reads it)
#pragma push
// FAKE: keeps the dead stores that the target has; removing it changes the code
#pragma opt_dead_assignments off
/**
 * Crowd behaviour pass, installed by map rels (Rogueport plaza gor_00, dou_11) as sub function 2:
 * NPCs with flag 0x4 push each other apart when closer than their size,
 * are pulled back towards their target position, and then move with collision (speed capped).
 */
void nanNPCOption(void) {
    NanNPC* q;
    void* w;
    NanNPC* p;
    NanNPC* r;
    Vec diff;
    f32 mag;
    f32 dist;

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
    // FAKE: r (loop 3 start) assigned in loop 2's exit test, as the target loads it there (no mr copy); w->npc is not changed by loop 2
    for (p = ((NanNPCWork*)w)->npc; p < (r = ((NanNPCWork*)w)->npc) + ((NanNPCWork*)w)->num; p++) {
        if (p->flags & 4) {
            PSVECSubtract(&p->target, &p->pos, &diff);
            mag = PSVECMag(&diff);
            if (mag > 0.8f * p->sizeY) {
                PSVECNormalize(&diff, &diff);
                diff.y = 0.0f;
                PSVECScale(&diff, &diff, 0.5f);
                PSVECAdd(&p->move, &diff, &p->move);
            }
        }
    }
    for (; r < ((NanNPCWork*)w)->npc + ((NanNPCWork*)w)->num; r++) {
        if (r->flags & 4) {
            mag = PSVECMag(&r->move);
            if (mag) {
                if (mag > 10.0f) {
                    PSVECScale(&r->move, &r->move, 5.0f / mag);
                    mag = 5.0f;
                }
                nanNPCHitMove(r, mag);
            }
        }
    }
}
#pragma pop

/** qsort comparator ordering crowd NPCs from far to near (larger Z first) so they draw back to front. */
static s32 nannpc_zcompare(const void* a, const void* b) {
    if (((const NanNPCSort*)a)->z < ((const NanNPCSort*)b)->z) {
        return 1;
    }
    if (((const NanNPCSort*)a)->z > ((const NanNPCSort*)b)->z) {
        return -1;
    }
    return 0;
}

/**
 * Sets the TEV, channel and fog state for drawing crowd sprites tinted by each NPC's colour (TEV colour register
 * 1).
 */
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
/**
 * Draws the crowd.
 * With work flag 0x1 each NPC's sprite is drawn separately, sorted by Z and tinted by its colour;
 * otherwise extdrv draws all the poses in one batch.
 */
static void nannpc_ext_disp(CameraId camera, void* param) {
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
        qqsort(w->sort, w->num, 8, nannpc_zcompare);
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

/** Draws the crowd's shadows through extdrv with a fixed 10x scale matrix. */
static void nannpc_ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {{10.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 10.0f, 0.0f, 0.1f}, {0.0f, 0.0f, 10.0f, 0.0f}};
    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}

/** Default extdrv init for the crowd: hides every pose 1000 units below the map with no rotation. */
static void nannpc_ext_init(void) {
    s32 i;
    ExtdrvPose* pose = extGetPosePtr();
    for (i = extGetPoseNum() - 1; i >= 0; i--, pose++) {
        pose->flags = 3;
        pose->dir = 0.0f;
        PSMTXIdentity(*pose->mtx);
        (*pose->mtx)[0][3] = 0.0f;
        (*pose->mtx)[1][3] = -1000.0f;
        (*pose->mtx)[2][3] = 0.0f;
    }
}

/** Default per-frame update (sub function 1): calls each active crowd NPC's own func. */
void nannpc_ext_main_sub(void) {
    s32 i;
    NanNPCWork* w = nanNPCWork;
    for (i = extGetPoseNum() - 1; i >= 0; i--) {
        NanNPC* p = &w->npc[i];
        if (p->name[0] && p->func) {
            p->func(p);
        }
    }
}

/**
 * Fuller per-frame update maps install as sub function 1:
 * runs each NPC's func, steps its animation table (offset per NPC so the crowd does not animate in step),
 * and copies texture, direction and position to its extdrv pose;
 * flag 0x2 hides the NPC by moving it 1000 units down.
 */
void nannpc_ext_main_sub_fast(void) {
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
            p->pose->texId = p->anim;
            p->pose->dir = -p->dir;
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

/** Default extdrv main callback: runs the three crowd sub functions (set by evt_nannpc_set_subfunc) in order. */
static void nannpc_ext_main(void) {
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

/**
 * Registers the crowd's draw and shadow callbacks with dispdrv each frame;
 * the sprites go in render mode 1, or 2 with work flag 0x1.
 */
static void nannpc_ext_dispent(void) {
    if (!(nanNPCWork->flags & 1)) {
        dispEntry(4, 0.0f, 1, nannpc_ext_disp, 0);
        dispEntry(4, 0.0f, 2, nannpc_ext_shadow_disp, 0);
    } else {
        dispEntry(4, 0.0f, 2, nannpc_ext_disp, 0);
        dispEntry(4, 0.0f, 2, nannpc_ext_shadow_disp, 0);
    }
}

/**
 * Sets up the crowd NPC system for a map (Rogueport plaza, Keelhaul Key, dou_11):
 * args[0] the extdrv texture info, args[1] an optional table of up to five pairs ended by -1,
 * args[2]/args[3] optional extdrv init and main callbacks and args[4] the number of NPCs.
 * Allocates the work on the map heap and starts extdrv; yields once first.
 */
USER_FUNC(evt_nannpc_init) {
    EvtWord* args = event->args;
    NanNPCWork* w;
    s32 i;
    ExtdrvTexInfo* texInfo = (ExtdrvTexInfo*)evtGetValue(event, args[0]);
    s16* tbl = (s16*)evtGetValue(event, args[1]);
    void (*initf)(void) = (void (*)(void))evtGetValue(event, args[2]);
    void (*mainf)(void) = (void (*)(void))evtGetValue(event, args[3]);
    void (*dispf)(void) = nannpc_ext_dispent;
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
    extEntry(w->num, texInfo, initf, mainf, dispf);
    for (i = 0; i < w->num; i++) {
        NanNPC* p = &w->npc[i];
        p->name[0] = 0;
        p->pose = NULL;
        p->flags = 0;
        p->flags2 = 0;
        p->pos = (Vec){0.0f, -1000.0f, 0.0f};
        p->target = (Vec){0.0f, -1000.0f, 0.0f};
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

/**
 * Installs a crowd sub function: args[0] picks the slot (0-2, run in that order every frame)
 * and args[1] is the function, e.g. nannpc_ext_main_sub_fast or nanNPCOption.
 */
USER_FUNC(evt_nannpc_set_subfunc) {
    EvtWord* args = event->args;
    s32 kind = evtGetValue(event, args[0]);
    NanNPCWork* w = nanNPCWork;
    switch (kind) {
        case 0:
            w->func14 = (void (*)(void))evtGetValue(event, args[1]);
            break;
        case 1:
            w->func18 = (void (*)(void))evtGetValue(event, args[1]);
            break;
        case 2:
            w->func1c = (void (*)(void))evtGetValue(event, args[1]);
            break;
    }
    return 2;
}

/**
 * Claims the first free crowd NPC slot for name args[0] (a string, or a number used as its hex form)
 * and resets it to defaults: hidden below the map, size 32x32, white colour.
 */
USER_FUNC(evt_nannpc_entry) {
    NanNPC* p;
    ExtdrvPose* pose;
    char* str;
    s32 off;
    EvtWord name;
    s32 i;
    EvtWord* args;
    NanNPCWork* w;
    args = event->args;
    pose = extGetPosePtr();
    name = (long long)evtGetValue(event, args[0]); // FAKE: the 64-bit cast keeps the target register order
    w = nanNPCWork;
    for (i = 0, off = 0; i < w->num; off += sizeof(NanNPC), i++) {
        p = (NanNPC*)((u8*)w->npc + off); // FAKE: byte offset; &w->npc[i] reorders the loop
#if VERSION <= VERSION_DEMO_US
        str = nanNPCEntryName((char*)name);
#else
        str = (char*)name;
        if (!(((EvtWord)str) & 0x80000000)) {
            sprintf(makestring, "%06x", name);
            str = makestring;
        }
#endif
        strcmp((char*)p->name, str);
        if (!p->pose) {
            strcpy((char*)p->name, str);
            p->pose = &pose[i];
            p->flags = 0;
            p->flags2 = 0;
            p->pos = (Vec){0.0f, -1000.0f, 0.0f};
            p->target = (Vec){0.0f, -1000.0f, 0.0f};
            p->hosei = (Vec){0.0f, 0.0f, 0.0f};
            p->sizeX = 32.0f;
            p->sizeY = 32.0f;
            p->startTime = 0;
            p->animnum = 0;
            p->dir = 0.0f;
            p->pose->dir = -p->dir;
            p->color = (GXColor){255, 255, 255, 255};
            break;
        }
    }

    return 2;
}

/** Places crowd NPC args[0] at X, Y, Z args[1]-args[3] and makes that its target position too. */
USER_FUNC(evt_nannpc_set_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    f32 x = evtGetFloat(event, args[1]);
    npc->pos.x = x;
    npc->target.x = x;
    x = evtGetFloat(event, args[2]);
    npc->pos.y = x;
    npc->target.y = x;
    x = evtGetFloat(event, args[3]);
    npc->pos.z = x;
    npc->target.z = x;
    return 2;
}

/** Returns crowd NPC args[0]'s position in args[1]-args[3]. */
USER_FUNC(evt_nannpc_get_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    evtSetFloat(event, args[1], npc->pos.x);
    evtSetFloat(event, args[2], npc->pos.y);
    evtSetFloat(event, args[3], npc->pos.z);
    return 2;
}

/** Sets crowd NPC args[0]'s display offset (hosei) to args[1]-args[3]. */
USER_FUNC(evt_nannpc_set_hosei_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    npc->hosei.x = evtGetFloat(event, args[1]);
    npc->hosei.y = evtGetFloat(event, args[2]);
    npc->hosei.z = evtGetFloat(event, args[3]);
    return 2;
}

/**
 * Sets crowd NPC args[0]'s width and height (args[1], args[2]);
 * the height is also the push-apart distance in nanNPCOption.
 */
USER_FUNC(evt_nannpc_set_size) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    npc->sizeX = evtGetFloat(event, args[1]);
    npc->sizeY = evtGetFloat(event, args[2]);
    return 2;
}

/** Gives a crowd NPC an animation table of texture ids ended by -1 (the C version of evt_nannpc_set_animtbl). */
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

/** Gives crowd NPC args[0] the animation table args[1] (texture ids ended by -1); an empty table clears it. */
USER_FUNC(evt_nannpc_set_animtbl) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
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

/** Sets crowd NPC args[0]'s facing to args[1] degrees. */
USER_FUNC(evt_nannpc_set_dir) {
    EvtWord* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->dir = evtGetValue(event, args[1]);
    return 2;
}

/** Stores args[2] in work slot args[1] of crowd NPC args[0], for the map's own NPC functions. */
USER_FUNC(evt_nannpc_set_work) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    s32 idx = evtGetValue(event, args[1]);
    npc->work[idx] = evtGetValue(event, args[2]);
    return 2;
}

/** Reads work slot args[1] of crowd NPC args[0] into args[2]. */
USER_FUNC(evt_nannpc_get_work) {
    EvtWord* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[2], npc->work[evtGetValue(event, args[1])]);
    return 2;
}

/**
 * Walks crowd NPC args[0] in a straight line to X, Y, Z args[1]-args[3] at args[4] units per second,
 * blocking until it arrives. Uses battle or field time so it pauses with the game.
 */
USER_FUNC(evt_nannpc_move_position2) {
    NanNPC* npc;
    OSTime now;
    EvtWord* args;
    f32 speed;
    s32 total;
    s32 elapsed;
    Vec target;
    Vec diff;
    Vec step;
    args = event->args;
#if VERSION <= VERSION_DEMO_US
    npc = nanNPCSearch2((char*)evtGetValue(event, args[0]));
    now = gp->inBattle ? gp->renderTime : gp->renderFieldTime;
#else
    npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    if (gp->inBattle) {
        now = gp->renderTime;
    } else {
        now = gp->renderFieldTime;
    }
#endif
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

/**
 * Makes crowd NPC args[0] jump to X, Y, Z args[1]-args[3] in args[4] ms with an arc args[5] units high,
 * blocking until it lands.
 */
USER_FUNC(evt_nannpc_jump_position) {
    EvtWord* args = event->args;
#if VERSION <= VERSION_DEMO_US
    NanNPC* npc = nanNPCSearch2((char*)evtGetValue(event, args[0]));
#else
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
#endif
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
        npc->pos.x = intplGetValue(0, npc->ipos[0], x, elapsed, duration);
        npc->pos.z = intplGetValue(0, npc->ipos[2], z, uel, duration);
        npc->pos.y = t * (event->userdataf[1] * t + event->userdataf[2]) + (f32)npc->ipos[1];
        return 0;
    }
    npc->pos.x = x;
    npc->pos.y = y;
    npc->pos.z = z;
    return 2;
}

/**
 * Changes the flags of crowd NPC args[0]: args[1] nonzero clears the bits in args[2],
 * zero sets them (inverted from the usual on/off).
 * Flag 0x2 hides the NPC, 0x4 joins it to nanNPCOption's crowd movement, 0x8 skips collision.
 */
USER_FUNC(evt_nannpc_flag_onoff) {
    EvtWord* args = event->args;
    EvtWord name = evtGetValue(event, args[0]);
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

/** Changes crowd NPC args[0]'s extdrv pose flags: args[1] nonzero clears the bits in args[2], zero sets them. */
USER_FUNC(evt_nannpc_ppflag_onoff) {
    EvtWord* args = event->args;
    EvtWord name = evtGetValue(event, args[0]);
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

/** Sets crowd NPC args[0]'s per-frame function to args[1]; map rels use it to run each NPC's own behaviour. */
USER_FUNC(evt_nannpc_set_func) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    npc->func = (void (*)(NanNPC*))evtGetValue(event, args[1]);
    return 2;
}

/** Pins crowd NPC args[0]'s shadow to height args[1] (pose flag 0x10). */
USER_FUNC(evt_nannpc_set_shadow_position) {
    EvtWord* args = event->args;
    NanNPC* npc = nanNPCSearch((char*)evtGetValue(event, args[0]));
    npc->pose->flags |= 0x10;
    npc->pose->shadowY = evtGetFloat(event, args[1]);
    return 2;
}

/** Tints crowd NPC args[0] with RGBA args[1]-args[4] (used when the crowd draws NPCs one by one). */
USER_FUNC(evt_nannpc_set_color) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    NanNPC* npc = nanNPCSearch(name);
    npc->color.r = evtGetValue(event, args[1]);
    npc->color.g = evtGetValue(event, args[2]);
    npc->color.b = evtGetValue(event, args[3]);
    npc->color.a = evtGetValue(event, args[4]);
    return 2;
}

/**
 * Changes the crowd work flags: args[0] nonzero clears the bits in args[1], zero sets them.
 * Flag 0x1 switches to per- NPC drawing with tint and depth sorting.
 */
USER_FUNC(evt_nannpcwork_flag_onoff) {
    EvtWord* args = event->args;
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

#pragma force_active reset
