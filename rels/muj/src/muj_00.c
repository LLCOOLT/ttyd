// muj_00 (無人島, Keelhaul Key): the beach: the shipwreck landing (mujinto_hyochaku) and the crew,
// and later the battle between Lord Crump's X-Nauts and Cortez's pirates (kaizoku_vs_dai3).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "driver/mapdrv.h"
#include "dolphin/gx.h"
#include "memory.h"
#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "system.h"
#include "mario/mariost.h"
#include "mario/mario.h"
#include "party.h"
#include "dolphin/mtx.h"
#include "evt/evt_bero.h"
#include "evt/evt_damage.h"
#include "evt/evt_hit.h"
#include "evt/evt_light.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_memcard.h"
#include "evt/evt_mobj.h"
#include "evt/evt_npc.h"
#include "evt/evt_paper.h"
#include "evt/evt_pouch.h"
#include "evt/evt_nannpc.h"
#include "muj.h"
#include "driver/hitdrv.h"
#include "evt/evt_cam.h"
#include "eff/eff_kemu_test.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "evt/evt_msg.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_telop.h"
#include "data_tables.h"
#include "libc_decls.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/camdrv.h"

static u8 muj_00_bss_0C[4];
static u8* _ap;
typedef struct TobiWork {
    Vec pos;
    s32 type;
} TobiWork;
static void suifu_kyorokyoro(NanNPC* npc);
typedef struct OrbitData {
    f32 angle;
    f32 dist;
} OrbitData;
OrbitData* _op;
#define ORBIT(i, p)           \
    op[i].angle += d;         \
    t = op[i].angle;          \
    rad = orbit_update(t);    \
    r = op[i].dist;           \
    x = r * sinf_l(rad) + cx; \
    t = r * cosf_l(rad) + cz; \
    p.x = x;                  \
    p.z = t;                  \
    (void)0
static NanNPC* random_choice_target(s32 type);
TobiWork* Tobidat;
static void tobikakari_seq00(NanNPC* npc);
static inline f32 sinf_l(f32 x) {
    f32 v = sin(x);
    return v;
}
static inline f32 cosf_l(f32 x) {
    return cos(x);
}
static inline f32 orbit_update(f32 x) {
    return x * 3.141592f / 180.0f;
}

static USER_FUNC(alpha_init_func);
static USER_FUNC(alpha_set_func);
#if VERSION == VERSION_EU
USER_FUNC(evt_sub_get_framerate); // evt_sub.c (PAL only): writes gp->framerate (50 or 60) to arg 0
#endif
static USER_FUNC(scale_func);
#if VERSION >= VERSION_US
USER_FUNC(N_evt_sub_status_gauge_force_update);
#endif
static void tobikakari_seq00(NanNPC* npc);
static NanNPC* random_choice_target(s32 type);
static void suifu_kyorokyoro_init(NanNPC* npc);
static void suifu_kyorokyoro(NanNPC* npc);
static void alpha_tev(MapTevCallbackInfo* info);

static ExtTexInfo ext_entry_data[59];
#if VERSION <= VERSION_DEMO_US
static s16 suifu_animtbl[41];
#else
static s16 suifu_animtbl[42];
#endif
#if VERSION <= VERSION_DEMO_US
s16 suifu_animtbl_run[21];
#else
s16 suifu_animtbl_run[22];
#endif
#if VERSION <= VERSION_DEMO_US
static s16 elmos_animtbl[21];
#else
static s16 elmos_animtbl[22];
#endif
#if VERSION <= VERSION_DEMO_US
static s16 dai3_animtbl[41];
#else
static s16 dai3_animtbl[42];
#endif
#if VERSION <= VERSION_DEMO_US
s16 dai3_animtbl_run[21];
#else
s16 dai3_animtbl_run[22];
#endif
extern EvtWord suifu_dark[];
extern EvtWord nannpc_light[];
extern EvtWord koburon_init[];
extern EvtWord koburon_regp[];
extern EvtWord koburon_talk[];
extern EvtWord koburon_dead[];
extern EvtWord koburon_evt[];
static NpcSetupInfo npcEnt[15];
static BeroEntry bero_entry_data[4];
extern EvtWord mujinto_hyochaku[];
s32 suifu_random_setup[380];
extern EvtWord suifu_random_sub[];
extern EvtWord tama_shoot[];
extern EvtWord npc_kyorokyoro[];
extern EvtWord dai3_shurai_sub[];
extern EvtWord dai3_shurai[];
static EvtWord dai3_shurai_after[68];
s32 kaizoku_vs_dai3_suifupos[380];
s32 kaizoku_vs_dai3_elmospos[400];
extern EvtWord iwapera_offscreen[];
extern EvtWord iwapera_offscreen_end[];
extern EvtWord dai3_kurukuru[];
s32 kaizoku_vs_dai3_dai3pos[300];
extern EvtWord dai3_butai_setup[];
extern EvtWord dai3_butai_main[];
extern EvtWord dai3_kanbu_setup[];
extern EvtWord dai3_kanbu_main[];
extern EvtWord kaizoku_setup[];
extern EvtWord kaizoku_main[];
extern EvtWord mario_main_init[];
extern EvtWord mario_main[];
extern EvtWord mario_main2[];
extern EvtWord kaizoku_move_every[];
extern EvtWord dai3_move_every[];
f32 dai3_spline_dt[27];
f32 kaizoku_spline_dt[30];
extern EvtWord kaizoku_move_trace_se[];
extern EvtWord kaizoku_move_trace[];
extern EvtWord dai3_move_trace_se[];
extern EvtWord dai3_move_trace[];
extern EvtWord tobikakari_kemuri[];
extern EvtWord cam_dai3_vs_kaizoku[];
extern EvtWord kaizoku_vs_dai3[];
extern EvtWord senin_kansei[];
f32 dai3_taisan_spline_dt00[9];
f32 dai3_taisan_spline_dt01[9];
extern EvtWord nameraka_rotate[];
extern EvtWord dai3_taisan_move_trace00[];
extern EvtWord dai3_taisan_move_trace01[];
extern EvtWord dai3_beat_back[];
s32 leave_island_suifupos[380];
extern EvtWord move_ship_se00[];
extern EvtWord move_ship_se01[];
extern EvtWord option_ship_npc[];
extern EvtWord option_ship_korutesu[];
extern EvtWord option_ship_marco[];
extern EvtWord option_ship_main[];
extern EvtWord leave_island[];
extern EvtWord muj_gor_ship_sub[];
extern EvtWord muj_gor_ship_start[];
extern EvtWord into_muj_ship[];
extern EvtWord mony_peton_boarding_sub[];
extern EvtWord mony_peton_boarding[];
static HitDamageReturn hitDmgRetPoints[8];

static void alpha_tev(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    u8* alpha = _ap;

    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, *alpha});
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
    info->tevStage++;
}

static USER_FUNC(alpha_init_func) {
    _ap = _mapAlloc(1);
    *_ap = 255;
    return EVT_RETURN_DONE;
}

static USER_FUNC(alpha_set_func) {
    *_ap = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(koburon_get_encount_info) {
    s32 arg = event->args[0];
    FieldBattleData* fbat = fbatGetPointer();

    evtSetValue(event, arg, fbat->hitKind);
    return EVT_RETURN_DONE;
}

static void suifu_kyorokyoro(NanNPC* npc) {
    switch (npc->state) {
        case 0:
            npc->startTime = gp->renderTime;
            npc->state = 1;
            npc->duration = irand(1000) + 100;
            if (npc->dir == 90.0f) {
                npc->dir = 270.0f;
            } else {
                npc->dir = 90.0f;
            }
            break;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->startTime) > npc->duration) {
                npc->startTime = gp->renderTime;
                npc->state = 2;
                npc->duration = irand(350) + 350;
                if (npc->dir == 90.0f) {
                    npc->dir = 270.0f;
                } else {
                    npc->dir = 90.0f;
                }
            }
            break;
        case 2:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->startTime) > npc->duration) {
                npc->startTime = gp->renderTime;
                npc->state = 3;
                npc->duration = irand(350) + 350;
                if (npc->dir == 90.0f) {
                    npc->dir = 270.0f;
                } else {
                    npc->dir = 90.0f;
                }
            }
            break;
        case 3:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->startTime) > npc->duration) {
                npc->func = NULL;
                if (npc->dir == 90.0f) {
                    npc->dir = 270.0f;
                }
            }
            break;
    }
}

static void suifu_kyorokyoro_init(NanNPC* npc) {
    npc->state = 0;
    npc->func = suifu_kyorokyoro;
}

#if VERSION <= VERSION_DEMO_US
// The demo's cannonball smoke (tama_shoot): a kemu_test burst at (x, y, z), its effect returned in arg 3.
static USER_FUNC(tama_shoot_kemuri_entry) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    evtSetValue(event, args[3], (s32)effKemuTestEntry(11, x, y, z, 1.0f));
    return EVT_RETURN_DONE;
}

// Turns the smoke from tama_shoot_kemuri_entry; the effect pointer goes through effNameToPtr as is.
static USER_FUNC(tama_shoot_kemuri) {
    EvtWord* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 rx = evtGetFloat(event, args[1]);
    f32 rz = evtGetFloat(event, args[2]);

    effKemuTestSetRxRz(effNameToPtr(name), rx, rz);
    return EVT_RETURN_DONE;
}
#endif

static USER_FUNC(dai3_butai_main_func) {
    s32 d;
    EvtWord* args = event->args;
    f32 a = evtGetValue(event, args[0]);
    f32 b = evtGetValue(event, args[1]);
    f32 cx = evtGetValue(event, args[2]);
    f32 cz = evtGetValue(event, args[3]);
    s32 i;
    NanNPC* npc;
    f32 s;
    f32 rad;
    f32 r;
    f32 c;
    NanNPCWork* wp = nanNPCWork;

    d = b - a;

    for (i = 0; i < 100; i++) {
        npc = &wp->npc[i + 205];
        npc->angle += d;
        r = npc->radius;
        rad = npc->angle;
        rad = 3.141592f * rad / 180.0f;
        s = sinf_l(rad);
        c = cosf_l(rad);
        npc->pos.x = r * s + cx;
        npc->pos.z = r * c + cz;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(kaizoku_main_func) {
    EvtWord* args = event->args;
    f32 a = evtGetValue(event, args[0]);
    f32 b = evtGetValue(event, args[1]);
    f32 cx = evtGetValue(event, args[2]);
    f32 cz = evtGetValue(event, args[3]);
    s32 d = b - a;
    s32 i;
    NanNPC* npc;
    f32 r;
    f32 rad;
    f32 s;
    f32 c;
    NanNPCWork* wp = nanNPCWork;

    for (i = 0; i < 95; i++) {
        npc = &wp->npc[i + 10];
        npc->angle += d;
        r = npc->radius;
        rad = npc->angle;
        rad = 3.141592f * rad / 180.0f;
        s = sin(rad);
        c = cos(rad);
        npc->pos.x = r * s + cx;
        npc->pos.z = r * c + cz;
    }
    for (i = 0; i < 100; i++) {
        npc = &wp->npc[i + 105];
        npc->angle += d;
        s = npc->radius;
        rad = npc->angle;
        rad = 3.141592f * rad / 180.0f;
        r = sin(rad);
        c = cos(rad);
        npc->pos.x = s * r + cx;
        npc->pos.z = s * c + cz;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_main_init_func) {
    _op = _mapAlloc(0x40);
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_main_setup_func) {
    EvtWord* args = event->args;
    f32 cx = evtGetValue(event, args[0]);
    f32 cz = evtGetValue(event, args[1]);
    OrbitData* op = _op;
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    NpcEntry* npc1 = evtNpcNameToPtr(event, "マルコ");
    NpcEntry* npc2 = evtNpcNameToPtr(event, "コルテス");
    NpcEntry* npc3 = evtNpcNameToPtr(event, "モニー");
    NpcEntry* npc4 = evtNpcNameToPtr(event, "ガラの悪い水夫");
    NpcEntry* npc5 = evtNpcNameToPtr(event, "ピートン");
    NpcEntry* npc6 = evtNpcNameToPtr(event, "オドオド水夫");

    op[0].dist = distABf(cx, -cz, cx + mario->position.x, -(cz + mario->position.z));
    op[0].angle = angleABf(cx, -cz, cx + mario->position.x, -(cz + mario->position.z));
    op[1].dist = distABf(cx, -cz, cx + party->position.x, -(cz + party->position.z));
    op[1].angle = angleABf(cx, -cz, cx + party->position.x, -(cz + party->position.z));
    op[2].dist = distABf(cx, -cz, cx + npc1->position.x, -(cz + npc1->position.z));
    op[2].angle = angleABf(cx, -cz, cx + npc1->position.x, -(cz + npc1->position.z));
    op[3].dist = distABf(cx, -cz, cx + npc2->position.x, -(cz + npc2->position.z));
    op[3].angle = angleABf(cx, -cz, cx + npc2->position.x, -(cz + npc2->position.z));
    op[4].dist = distABf(cx, -cz, cx + npc3->position.x, -(cz + npc3->position.z));
    op[4].angle = angleABf(cx, -cz, cx + npc3->position.x, -(cz + npc3->position.z));
    op[5].dist = distABf(cx, -cz, cx + npc4->position.x, -(cz + npc4->position.z));
    op[5].angle = angleABf(cx, -cz, cx + npc4->position.x, -(cz + npc4->position.z));
    op[6].dist = distABf(cx, -cz, cx + npc5->position.x, -(cz + npc5->position.z));
    op[6].angle = angleABf(cx, -cz, cx + npc5->position.x, -(cz + npc5->position.z));
    op[7].dist = distABf(cx, -cz, cx + npc6->position.x, -(cz + npc6->position.z));
    op[7].angle = angleABf(cx, -cz, cx + npc6->position.x, -(cz + npc6->position.z));
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_main_func) {
    EvtWord* args;
    OrbitData* op;
    MarioWork* mario;
    PartyEntry* party;
    NpcEntry* npc1;
    NpcEntry* npc2;
    NpcEntry* npc3;
    NpcEntry* npc4;
    NpcEntry* npc5;
    NpcEntry* npc6;
    f32 a;
    f32 b;
    f32 cx;
    f32 cz;
    f32 d;
    f32 t;
    f32 r;
    f32 rad;
    f32 x;

    args = event->args;
    a = evtGetValue(event, args[0]);
    b = evtGetValue(event, args[1]);
    cx = evtGetValue(event, args[2]);
    cz = evtGetValue(event, args[3]);
    op = _op;
    mario = marioGetPtr();
    party = partyGetPtr(0);
    npc1 = evtNpcNameToPtr(event, "マルコ");
    npc2 = evtNpcNameToPtr(event, "コルテス");
    npc3 = evtNpcNameToPtr(event, "モニー");
    npc4 = evtNpcNameToPtr(event, "ガラの悪い水夫");
    npc5 = evtNpcNameToPtr(event, "ピートン");
    npc6 = evtNpcNameToPtr(event, "オドオド水夫");
    d = b - a;
    ORBIT(0, mario->position);
    ORBIT(1, party->position);
    ORBIT(2, npc1->position);
    ORBIT(3, npc2->position);
    ORBIT(4, npc3->position);
    ORBIT(5, npc4->position);
    ORBIT(6, npc5->position);
    ORBIT(7, npc6->position);
    npc1->prevPosition = npc1->position;
    npc2->prevPosition = npc2->position;
    npc3->prevPosition = npc3->position;
    npc4->prevPosition = npc4->position;
    npc5->prevPosition = npc5->position;
    npc6->prevPosition = npc6->position;
    return EVT_RETURN_DONE;
}

static NanNPC* random_choice_target(s32 type) {
    NanNPCWork* wp = nanNPCWork;
    s32 idx;

    switch (type) {
        case 0:
        case 1:
            idx = irand(100) + 205;
            break;
        case 2:
        default:
            if (irand(2)) {
                idx = irand(95) + 10;
            } else {
                idx = irand(100) + 105;
            }
            break;
    }
    return &wp->npc[idx];
}

static void tobikakari_seq00(NanNPC* npc) {
    TobiWork* work = npc->tobi;
    NanNPC* target;
    s32 r;
    s32 elapsed;
    f32 t;

    switch (npc->state) {
        case 0:
            r = irand(1000);
            if (r < 100) {
                npc->state = 10;
            } else if (r < 200) {
                npc->startTime = (s32)gp->renderTime;
                npc->duration = irand(500) + 1;
                npc->state = 21;
            } else {
                npc->startTime = (s32)gp->renderTime;
                npc->duration = irand(2000) + 500;
                npc->state = 22;
            }
            break;
        case 10:
            npc->startTime = (s32)gp->renderTime;
            npc->start = npc->pos;
            target = random_choice_target(work->type);
            npc->target = target->tobi->pos;
            npc->target.z += 2.0f;
            npc->vy = -4.0f * (f32)(irand(30) + 100);
            npc->dy = npc->target.y - npc->start.y - npc->vy;
            npc->duration = irand(500) + 400;
            if (npc->start.x < npc->target.x) {
                npc->dir = 90.0f;
            } else {
                npc->dir = 270.0f;
            }
            npc->state = 20;
            npc->nextState = 21;
            break;
        case 11:
            npc->startTime = (s32)gp->renderTime;
            npc->start = npc->pos;
            npc->target = work->pos;
            npc->vy = -4.0f * (f32)(irand(30) + 100);
            npc->dy = npc->target.y - npc->start.y - npc->vy;
            npc->duration = irand(500) + 400;
            npc->state = 20;
            npc->nextState = 22;
            break;
        case 20:
            elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->startTime);
            if (elapsed < npc->duration) {
                t = (f32)elapsed / (f32)npc->duration;
                npc->pos.x = intplGetValue(0, npc->start.x, npc->target.x, elapsed, npc->duration);
                npc->pos.z = intplGetValue(0, npc->start.z, npc->target.z, elapsed, npc->duration);
                npc->pos.y = npc->start.y + t * (npc->vy * t + npc->dy);
            } else {
                npc->pos = npc->target;
                npc->startTime = (s32)gp->renderTime;
                npc->duration = irand(2000) + 500;
                npc->state = npc->nextState;
            }
            break;
        case 21:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->startTime) > npc->duration) {
                npc->state = 11;
            }
            break;
        case 22:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->startTime) > npc->duration) {
                npc->state = 10;
            }
            break;
    }
}

static USER_FUNC(tobikakaru_init) {
    NanNPCWork* wp = nanNPCWork;
    TobiWork* p;
    s32 i;
    NanNPC* npc;

    p = _mapAlloc(0x1310);
    Tobidat = p;
    for (i = 0; i < 95; i++) {
        npc = &wp->npc[i + 10];
        npc->func = tobikakari_seq00;
        npc->state = 0;
        npc->tobi = p;
        evt_nannpc_set_animtbl_sub(npc, suifu_animtbl_run);
        p->pos = npc->pos;
        p->type = 0;
        p++;
    }
    for (i = 0; i < 100; i++) {
        npc = &wp->npc[i + 105];
        npc->func = tobikakari_seq00;
        npc->state = 0;
        npc->tobi = p;
        p->pos = npc->pos;
        p->type = 1;
        p++;
    }
    for (i = 0; i < 100; i++) {
        npc = &wp->npc[i + 205];
        npc->func = tobikakari_seq00;
        npc->state = 0;
        npc->tobi = p;
        evt_nannpc_set_animtbl_sub(npc, dai3_animtbl_run);
        p->pos = npc->pos;
        p->type = 2;
        p++;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(tobikakaru_end) {
    NanNPCWork* wp = nanNPCWork;
    NanNPC* npc;
    s32 i;

    for (i = 0; i < 95; i++) {
        npc = &wp->npc[i + 10];
        npc->func = NULL;
        evt_nannpc_set_animtbl_sub(npc, suifu_animtbl);
    }
    for (i = 0; i < 100; i++) {
        npc = &wp->npc[i + 105];
        npc->func = NULL;
    }
    for (i = 0; i < 100; i++) {
        npc = &wp->npc[i + 205];
        npc->func = NULL;
        evt_nannpc_set_animtbl_sub(npc, dai3_animtbl);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(ship_rotate) {
    EvtWord* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);

    f32 angle = angleABf(x1, -z1, x2, -z2);

    evtSetFloat(event, args[4], angle - 90.0f);
    return EVT_RETURN_DONE;
}

static USER_FUNC(ship_rotate_rev) {
    EvtWord* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);

    f32 angle;

    angle = angleABf(x1, -z1, x2, -z2);
    evtSetFloat(event, args[4], 180.0f + (angle - 90.0f));
    return EVT_RETURN_DONE;
}

static USER_FUNC(cam_test_init_func) {
    EvtWord* args = event->args;
    Vec b;
    Vec a;
    f32 dist;

    a.x = evtGetValue(event, args[0]);
    a.y = 110.0f;
    a.z = evtGetValue(event, args[1]);
    b.x = 70.0f;
    b.y = 110.0f;
    b.z = 0.0f;
    dist = PSVECDistance(&a, &b);
    evtSetFloat(event, args[2], 57.29579f * (f32)atan2(-(b.x - a.x), b.z - a.z));
    evtSetFloat(event, args[3], dist);
    return EVT_RETURN_DONE;
}

static USER_FUNC(cam_test_func) {
    EvtWord* args = event->args;
    s32* p0 = args++;
    s32* p1 = args++;
    f32 angle = evtGetFloat(event, *args++);
    f32 dist = evtGetFloat(event, *args++);
    f32 rad, s, c;
    Vec center;
    rad = 6.2831855f * angle / 360.0f;
    s = sinf_l(rad);
    c = cosf_l(rad);
    center.x = 70.0f;
    center.y = 110.0f;
    center.z = 0.0f;
    evtSetValue(event, *p0, center.x + dist * s);
    evtSetValue(event, *p1, center.z - dist * c);
    return EVT_RETURN_DONE;
}

static ExtTexInfo ext_entry_data[] = {
    {"c_boro_k", "S_1", 0.0f},
    {"c_boro_k", "S_1", 3.0f},
    {"c_boro_k", "S_1", 6.0f},
    {"c_boro_k", "S_1", 9.0f},
    {"c_boro_k", "S_1", 12.0f},
    {"c_boro_k", "S_1", 15.0f},
    {"c_boro_k", "S_1", 18.0f},
    {"c_boro_k", "S_1", 21.0f},
    {"c_boro_k", "S_1", 24.0f},
    {"c_boro_k", "S_1", 27.0f},
    {"c_boro_k", "S_1", 30.0f},
    {"c_boro_k", "S_1", 33.0f},
    {"c_boro_k", "S_1", 36.0f},
    {"c_boro_k", "S_1", 39.0f},
    {"c_boro_k", "R_1", 0.0f},
    {"c_boro_k", "R_1", 2.0f},
    {"c_boro_k", "R_1", 4.0f},
    {"c_boro_k", "R_1", 6.0f},
    {"c_boro_k", "R_1", 8.0f},
    {"c_boro_k", "R_1", 10.0f},
    {"c_boro_k", "R_1", 12.0f},
    {"c_boro_k", "R_1", 14.0f},
    {"c_boro_k", "R_1", 16.0f},
    {"c_boro_k", "R_1", 18.0f},
    {"c_elmos", "S_1", 0.0f},
    {"c_elmos", "S_1", 2.0f},
    {"c_elmos", "S_1", 4.0f},
    {"c_elmos", "S_1", 6.0f},
    {"c_elmos", "S_1", 8.0f},
    {"c_elmos", "S_1", 10.0f},
    {"c_elmos", "S_1", 12.0f},
    {"c_elmos", "S_1", 14.0f},
    {"c_elmos", "S_1", 16.0f},
    {"c_elmos", "S_1", 18.0f},
    {"c_zako_n", "S_1", 0.0f},
    {"c_zako_n", "S_1", 3.0f},
    {"c_zako_n", "S_1", 6.0f},
    {"c_zako_n", "S_1", 9.0f},
    {"c_zako_n", "S_1", 12.0f},
    {"c_zako_n", "S_1", 15.0f},
    {"c_zako_n", "S_1", 18.0f},
    {"c_zako_n", "S_1", 21.0f},
    {"c_zako_n", "S_1", 24.0f},
    {"c_zako_n", "S_1", 27.0f},
    {"c_zako_n", "S_1", 30.0f},
    {"c_zako_n", "S_1", 33.0f},
    {"c_zako_n", "S_1", 36.0f},
    {"c_zako_n", "S_1", 39.0f},
    {"c_zako_n", "R_1", 0.0f},
    {"c_zako_n", "R_1", 2.0f},
    {"c_zako_n", "R_1", 4.0f},
    {"c_zako_n", "R_1", 6.0f},
    {"c_zako_n", "R_1", 8.0f},
    {"c_zako_n", "R_1", 10.0f},
    {"c_zako_n", "R_1", 12.0f},
    {"c_zako_n", "R_1", 14.0f},
    {"c_zako_n", "R_1", 16.0f},
    {"c_zako_n", "R_1", 18.0f},
    {0},
};

static s16 suifu_animtbl[] = {
    0, 0, 0, 1, 1, 1, 2, 2,
    2, 3, 3, 3, 4, 4, 4, 5,
    5, 5, 6, 6, 6, 7, 7, 7,
    8, 8, 8, 9, 9, 9, 10, 10,
    10, 11, 11, 11, 12, 12, 12, 13,
#if VERSION <= VERSION_DEMO_US
    -1,
#else
    -1, 0,
#endif
};

s16 suifu_animtbl_run[] = {
    14, 14, 15, 15, 16, 16, 17, 17,
    18, 18, 19, 19, 20, 20, 21, 21,
#if VERSION <= VERSION_DEMO_US
    22, 22, 23, 23, -1,
#else
    22, 22, 23, 23, -1, 0,
#endif
};

static s16 elmos_animtbl[] = {
    24, 24, 25, 25, 26, 26, 27, 27,
    28, 28, 29, 29, 30, 30, 31, 31,
#if VERSION <= VERSION_DEMO_US
    32, 32, 33, 33, -1,
#else
    32, 32, 33, 33, -1, 0,
#endif
};

static s16 dai3_animtbl[] = {
    34, 34, 34, 35, 35, 35, 36, 36,
    36, 37, 37, 37, 38, 38, 38, 39,
    39, 39, 40, 40, 40, 41, 41, 41,
    42, 42, 42, 43, 43, 43, 44, 44,
    44, 45, 45, 45, 46, 46, 46, 47,
#if VERSION <= VERSION_DEMO_US
    -1,
#else
    -1, 0,
#endif
};

s16 dai3_animtbl_run[] = {
    48, 48, 49, 49, 50, 50, 51, 51,
    52, 52, 53, 53, 54, 54, 55, 55,
#if VERSION <= VERSION_DEMO_US
    56, 56, 57, 57, -1,
#else
    56, 56, 57, 57, -1, 0,
#endif
};

static EVT_BEGIN(nannpc_mode_setup)
    CALL(evt_nannpc_init, PTR(ext_entry_data), 0, 0, 0, 305)
    CALL(evt_nannpc_set_subfunc, 1, PTR(nannpc_ext_main_sub_fast))
    SET_VALUE(LW(0), 0)
    LOOP(10)
        CALL(evt_nannpc_entry, LW(0))
        CALL(evt_nannpc_set_func, LW(0), 0)
        CALL(evt_nannpc_set_animtbl, LW(0), PTR(suifu_animtbl))
        CALL(evt_nannpc_flag_onoff, LW(0), 0, 2)
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(0), 10)
    LOOP(95)
        CALL(evt_nannpc_entry, LW(0))
        CALL(evt_nannpc_set_func, LW(0), 0)
        CALL(evt_nannpc_set_animtbl, LW(0), PTR(suifu_animtbl))
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(0), 105)
    LOOP(100)
        CALL(evt_nannpc_entry, LW(0))
        CALL(evt_nannpc_set_func, LW(0), 0)
        CALL(evt_nannpc_set_animtbl, LW(0), PTR(elmos_animtbl))
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(0), 205)
    LOOP(100)
        CALL(evt_nannpc_entry, LW(0))
        CALL(evt_nannpc_set_func, LW(0), 0)
        CALL(evt_nannpc_set_animtbl, LW(0), PTR(dai3_animtbl))
        ADD(LW(0), 1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(back_dark)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, LW(10))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(back_light)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, LW(10))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(suifu_dark)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, LW(10))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(LW(2), 10)
        LOOP(95)
            CALL(evt_nannpc_set_color, LW(2), LW(0), LW(0), LW(0), 255)
            ADD(LW(2), 1)
        END_LOOP
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(nannpc_light)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, LW(10))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(LW(2), 0)
        LOOP(305)
            CALL(evt_nannpc_set_color, LW(2), LW(0), LW(0), LW(0), 255)
            ADD(LW(2), 1)
        END_LOOP
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(garawaru_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_npc_set_position, STRING("me"), 1386, 35, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(garawaru_talk)
    CALL(evt_msg_print, 0, STRING("stg5_muj_117_01"), 0, STRING("me"))
    RETURN
EVT_END()

static EVT_BEGIN(marco_init)
    RETURN
EVT_END()

static EVT_BEGIN(marco_talk)
    RETURN
EVT_END()

static EVT_BEGIN(odoodo_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_npc_set_position, STRING("me"), 1400, 35, -100)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(odoodo_talk)
    CALL(evt_msg_print, 0, STRING("stg5_muj_117_00"), 0, STRING("me"))
    RETURN
EVT_END()

static EVT_BEGIN(suifu_a_init)
    RETURN
EVT_END()

static EVT_BEGIN(suifu_a_talk)
    RETURN
EVT_END()

static EVT_BEGIN(suifu_bomb_init)
    RETURN
EVT_END()

static EVT_BEGIN(suifu_bomb_talk)
    RETURN
EVT_END()

static EVT_BEGIN(suifu_c_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_npc_set_position, STRING("me"), 1325, 35, -225)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(suifu_c_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG5_36_HOLE_IN_THE_WALL)
        CALL(evt_msg_print, 0, STRING("stg5_muj_94_01"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_msg_print, 0, STRING("stg5_muj_117_04"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(suifu_d_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_npc_set_position, STRING("me"), 1350, 35, -150)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(suifu_d_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG5_36_HOLE_IN_THE_WALL)
        CALL(evt_msg_print, 0, STRING("stg5_muj_94_02"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_msg_print, 0, STRING("stg5_muj_117_05"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(suifu_e_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_npc_set_position, STRING("me"), 1250, 35, -175)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(suifu_e_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG5_36_HOLE_IN_THE_WALL)
        CALL(evt_msg_print, 0, STRING("stg5_muj_94_03"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_msg_print, 0, STRING("stg5_muj_117_06"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(korutesu_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_GREATER_OR_EQUAL(STORY_STG5_49_BOWSER_TWILIGHT_TOWN_2)
        CALL(evt_npc_set_ry, STRING("me"), 90)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(korutesu_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_GREATER_OR_EQUAL(STORY_STG5_58_FAIR_WINDS)
        CALL(evt_msg_print, 0, STRING("hune_00"), 0, STRING("me"))
        CALL(evt_msg_select, 0, STRING("hune_00_yesno"))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("hune_02"))
            SET_VALUE(GSWF(GSWF_GOR00_SHIP_ARRIVAL_PENDING), 1)
            CALL_CHILD(muj_gor_ship_start)
        ELSE
            CALL(evt_msg_print_add, 0, STRING("hune_01"))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(mony_init)
    RETURN
EVT_END()

static EVT_BEGIN(mony_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG5_36_HOLE_IN_THE_WALL)
        CALL(evt_msg_print, 0, STRING("stg5_muj_94_04"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_msg_print, 0, STRING("stg5_muj_117_07"), 0, STRING("me"))
        CASE_EQUAL(STORY_STG5_64_02_F_AND_F_SAIL_OFF)
        CALL(evt_msg_print, 0, STRING("stg5_muj_146_02"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(peton_init)
    RETURN
EVT_END()

static EVT_BEGIN(peton_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG5_36_HOLE_IN_THE_WALL)
        CALL(evt_msg_print, 0, STRING("stg5_muj_94_05"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG5_40_TRUE_IDENTITY, STORY_STG5_41_RETURN_TO_THE_GROTTO)
        CALL(evt_msg_print, 0, STRING("stg5_muj_117_08"), 0, STRING("me"))
        CASE_EQUAL(STORY_STG5_64_02_F_AND_F_SAIL_OFF)
        CALL(evt_msg_print, 0, STRING("stg5_muj_146_01"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(koburon_init)
    CALL(evt_npc_reaction_flag_onoff, 0, STRING("me"), 15)
    CALL(evt_npc_set_anim, STRING("me"), STRING("A_2"))
    CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
    CALL(evt_npc_set_position, STRING("me"), LW(3), -1000, LW(5))
#if VERSION >= VERSION_JP
    CALL(evt_npc_change_interrupt, STRING("me"), 6, 0)
#endif
    SET_VALUE(LSWF(1), 0)
    RETURN
EVT_END()

EVT_BEGIN(koburon_regp)
#if VERSION >= VERSION_JP
    CALL(L_evt_mario_keyon_wait)
#endif
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(1))
    IF_INT_GREATER(LW(1), 100)
        IF_INT_EQUAL(LSWF(1), 1)
#if VERSION >= VERSION_JP
            CALL(evt_npc_change_interrupt, STRING("me"), 6, 0)
#endif
            CALL(evt_npc_reaction_flag_onoff, 0, STRING("me"), 15)
            CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_KOBURON_IN1"), LW(3), LW(4), LW(5), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("A_2"))
            WAIT_MS(300)
            CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
            CALL(evt_npc_set_position, STRING("me"), LW(3), -1000, LW(5))
            SET_VALUE(LSWF(1), 0)
        END_IF
#if VERSION >= VERSION_JP
        CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
        CALL(evt_npc_set_position, STRING("me"), LW(3), -1000, LW(5))
#endif
    ELSE
        IF_INT_EQUAL(LSWF(1), 0)
            CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
            CALL(evt_npc_set_position, STRING("me"), LW(3), 35, LW(5))
            CALL(evt_npc_set_anim, STRING("me"), STRING("A_1"))
#if VERSION <= VERSION_DEMO_US
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_KOBURON_OUT1"), LW(3), -29999996, LW(5), 0)
#else
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_KOBURON_OUT1"), LW(3), 35, LW(5), 0)
#endif
            SET_VALUE(LSWF(1), 1)
            WAIT_MS(500)
            CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
            CALL(evt_npc_reaction_flag_onoff, 1, STRING("me"), 15)
#if VERSION >= VERSION_JP
            CALL(evt_npc_change_interrupt, STRING("me"), 6, PTR(koburon_talk))
#endif
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(koburon_talk)
    IF_INT_EQUAL(GSWF(GSWF_MUJ00_KOBURON_FIRST_TALK), 0)
        CALL(evt_msg_print, 0, STRING("koburon_01"), 0, STRING("me"))
        SET_VALUE(GSWF(GSWF_MUJ00_KOBURON_FIRST_TALK), 1)
    ELSE
        SWITCH(GSW(GSW_MUJ00_WHACKA_BUMPS))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 0, STRING("koburon_02"), 0, STRING("me"))
            CASE_EQUAL(1)
            CALL(evt_msg_print, 0, STRING("koburon_03"), 0, STRING("me"))
            CASE_EQUAL(2)
            CALL(evt_msg_print, 0, STRING("koburon_04"), 0, STRING("me"))
            CASE_EQUAL(3)
            CALL(evt_msg_print, 0, STRING("koburon_05"), 0, STRING("me"))
            CASE_EQUAL(4)
            CALL(evt_msg_print, 0, STRING("koburon_06"), 0, STRING("me"))
            CASE_EQUAL(5)
            CALL(evt_msg_print, 0, STRING("koburon_07"), 0, STRING("me"))
            CASE_EQUAL(6)
            CALL(evt_msg_print, 0, STRING("koburon_08"), 0, STRING("me"))
            CASE_EQUAL(7)
            CALL(evt_msg_print, 0, STRING("koburon_09"), 0, STRING("me"))
        END_SWITCH
    END_IF
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    RETURN
EVT_END()

EVT_BEGIN(koburon_dead)
#if VERSION >= VERSION_JP
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_DAMAGED_PLIABLE1"), LW(0), LW(1), LW(2), 0)
#endif
    CALL(evt_npc_set_damage_anim, STRING("me"))
    WAIT_MS(200)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
#endif
    ADD(LW(1), 30)
    ADD(LW(2), 10)
    CALL(evt_item_entry, STRING("item_99"), ITEM_WHACKA_BUMP, LW(0), LW(1), LW(2), ITEM_ENTRY_FALL_THROWN, -1, 0)
    WAIT_MS(400)
    IF_INT_EQUAL(GSW(GSW_MUJ00_WHACKA_BUMPS), 7)
        CALL(evt_msg_print, 0, STRING("koburon_14"), 0, STRING("me"))
        GOTO(99)
    END_IF
    CALL(koburon_get_encount_info, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(131072)
        CASE_OR_EQUAL(262144)
        CASE_OR_EQUAL(524288)
        CALL(evt_msg_print, 0, STRING("koburon_10"), 0, STRING("me"))
        CASE_END
        CASE_OR_EQUAL(1048576)
        CASE_OR_EQUAL(2097152)
        CASE_OR_EQUAL(4194304)
        CALL(evt_msg_print, 0, STRING("koburon_10"), 0, STRING("me"))
        CASE_END
        CASE_OR_EQUAL(8388608)
        CALL(evt_msg_print, 0, STRING("koburon_11"), 0, STRING("me"))
        CASE_END
        CASE_OR_EQUAL(16777216)
        CALL(evt_msg_print, 0, STRING("koburon_13"), 0, STRING("me"))
        CASE_END
    END_SWITCH
    LABEL(99)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    WAIT_MS(100)
    ADD(GSW(GSW_MUJ00_WHACKA_BUMPS), 1)
    SET_VALUE(LSWF(2), 1)
    CALL(evt_npc_reaction_flag_onoff, 0, STRING("me"), 15)
    CALL(evt_npc_set_anim, STRING("me"), STRING("A_2"))
    WAIT_MS(500)
    CALL(evt_npc_change_interrupt, STRING("me"), 1, 0)
    CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    SET_VALUE(GSWF(GSWF_MUJ00_KOBURON_FIRST_TALK), 1)
    RETURN
EVT_END()

EVT_BEGIN(koburon_evt)
    IF_INT_EQUAL(GSW(GSW_MUJ00_WHACKA_BUMPS), 8)
        CALL(evt_npc_delete, STRING("コブロン"))
        RETURN
    END_IF
    CALL(evt_npc_set_position, STRING("コブロン"), 562, 35, -1226)
    CALL(evt_npc_set_width, STRING("コブロン"), 15)
    CALL(evt_npc_set_height, STRING("コブロン"), 22)
    RETURN
EVT_END()

static EVT_BEGIN(kiza_talk)
    CALL(evt_msg_print, 0, STRING("stg5_muj_146_02_01"), 0, STRING("me"))
    RETURN
EVT_END()

static EVT_BEGIN(kiza_entry)
    CALL(evt_npc_entry, STRING("キザ野郎"), STRING("c_kiza"))
    CALL(evt_npc_set_tribe, STRING("キザ野郎"), STRING("キザ野郎"))
    CALL(evt_npc_set_position, STRING("キザ野郎"), 575, 25, -420)
    CALL(evt_npc_set_ry, STRING("キザ野郎"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("キザ野郎"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_change_interrupt, STRING("キザ野郎"), 6, PTR(kiza_talk))
    RETURN
EVT_END()

static NpcSetupInfo npcEnt[] = {
    {
        "ガラの悪い水夫", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        garawaru_init, // initEvent
        NULL, // regularEvent
        garawaru_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マルコ", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        marco_init, // initEvent
        NULL, // regularEvent
        marco_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "めがね水夫", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        npc_init_evt, // initEvent
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, // regularEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "第三勢力幹部", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        npc_init_evt, // initEvent
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, // regularEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "オドオド水夫", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        odoodo_init, // initEvent
        NULL, // regularEvent
        odoodo_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "水夫A", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        suifu_a_init, // initEvent
        NULL, // regularEvent
        suifu_a_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "水夫ボム兵", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        suifu_bomb_init, // initEvent
        NULL, // regularEvent
        suifu_bomb_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "水夫C", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        suifu_c_init, // initEvent
        NULL, // regularEvent
        suifu_c_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "水夫D", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        suifu_d_init, // initEvent
        NULL, // regularEvent
        suifu_d_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "水夫E", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        suifu_e_init, // initEvent
        NULL, // regularEvent
        suifu_e_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "コルテス", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        korutesu_init, // initEvent
        NULL, // regularEvent
        korutesu_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "モニー", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        mony_init, // initEvent
        NULL, // regularEvent
        mony_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ピートン", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        peton_init, // initEvent
        NULL, // regularEvent
        peton_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "コブロン", // name
        NPC_FLAG_TALK_ANIM, // flags
        7, // reactionFlags
        koburon_init, // initEvent
        koburon_regp, // regularEvent
        koburon_talk, // talkEvent
        koburon_dead, // deadEvent
        NULL, NULL, NULL, NULL, 0, // findEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

static BeroEntry bero_entry_data[] = {
    {
        "e_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "muj_01", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "n_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "muj_10", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "n_bero_02", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "dou_11", // nextMapName
        "n_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(mujinto_hyochaku)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_eff_delete, STRING("sunlight"))
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    WAIT_MS(2000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_00"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_01"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_02"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_03"), 0, 0)
    WAIT_MS(500)
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_party_cont_onoff, 0, 1)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_pos, 1185, -15, 0)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_pos, 0, 1220, -15, 30)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_pose, STRING("M_W_4B"))
    CALL(evt_cam3d_evt_set, 1250, 141, 535, 1250, 45, -7, 0, 11)
    WAIT_MS(1500)
    SET_VALUE(LW(10), 300)
    CALL(evt_eff64, STRING("sunlight"), STRING("sunlight_n64"), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    SPAWN_EVENT(back_light)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG5_MUJ1"))
        CALL(evt_snd_bgm_scope, 0, 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_telop_entry, 9)
    END_INLINE_EVENT
    WAIT_MS(1800)
    CALL(evt_npc_set_position, STRING("ガラの悪い水夫"), 1485, 35, 15)
    CALL(evt_npc_flag_onoff, 1, STRING("ガラの悪い水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_msg_print, 0, STRING("stg5_muj_03_00"), 0, STRING("ガラの悪い水夫"))
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_npc_move_position, STRING("ガラの悪い水夫"), 1342, 37, 0, FLOAT(60.0f), 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_04"), 0, STRING("ガラの悪い水夫"))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(1000)
    CALL(evt_npc_set_ry, STRING("ガラの悪い水夫"), 90)
    CALL(evt_npc_move_position, STRING("ガラの悪い水夫"), 1485, 15, 0, FLOAT(60.0f), 0)
    CALL(evt_npc_set_position, STRING("ガラの悪い水夫"), 0, -1000, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_11_DESERTED_ISLAND)
    CALL(evt_mario_dispflag_onoff, 0, 2)
#if VERSION >= VERSION_JP
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
#endif
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

s32 suifu_random_setup[] = {
    1289, 35, -419, 270, 1214, 35, -335, 90,
    1264, 35, -358, 270, 1306, 35, -462, 90,
    1273, 35, -431, 270, 1153, 35, -500, 90,
    1327, 35, -369, 270, 1201, 35, -468, 90,
    1364, 35, -494, 270, 1190, 35, -443, 90,
    1275, 35, -455, 270, 1215, 35, -425, 90,
    1185, 35, -388, 270, 1167, 35, -399, 90,
    1162, 35, -468, 270, 1208, 35, -441, 90,
    1219, 35, -350, 270, 1261, 35, -415, 90,
    1306, 35, -416, 270, 1160, 35, -341, 90,
    1209, 35, -486, 270, 1348, 35, -468, 90,
    1215, 35, -397, 270, 1202, 35, -404, 90,
    1143, 35, -347, 270, 1246, 35, -435, 90,
    1163, 35, -321, 270, 1251, 33, -458, 99,
    1203, 35, -346, 270, 1371, 35, -356, 90,
    1231, 35, -400, 270, 1366, 35, -472, 90,
    1285, 35, -357, 270, 1145, 35, -375, 90,
    1234, 35, -483, 270, 1133, 35, -469, 90,
    1325, 35, -419, 270, 1230, 35, -368, 90,
    1279, 35, -337, 270, 1133, 35, -454, 90,
    1232, 35, -424, 270, 1136, 35, -436, 90,
    1132, 35, -403, 270, 1203, 35, -386, 90,
    1333, 35, -392, 270, 1238, 35, -323, 90,
    1234, 35, -452, 270, 1278, 35, -470, 90,
    1131, 35, -360, 270, 1300, 35, -434, 90,
    1317, 35, -399, 270, 1219, 35, -382, 90,
    1289, 35, -482, 270, 1341, 35, -410, 90,
    1354, 35, -426, 270, 1150, 35, -397, 90,
    1313, 35, -321, 270, 1130, 35, -388, 90,
    1268, 35, -401, 270, 1183, 35, -320, 90,
    1208, 35, -366, 270, 1237, 35, -386, 90,
    1319, 35, -433, 270, 1314, 35, -479, 90,
    1147, 35, -329, 270, 1361, 35, -455, 90,
    1144, 35, -487, 270, 1164, 35, -484, 90,
    1330, 35, -496, 270, 1352, 35, -383, 90,
    1290, 35, -449, 270, 1119, 35, -372, 90,
    1245, 35, -414, 270, 1306, 35, -351, 90,
    1169, 35, -366, 270, 1313, 35, -378, 90,
    1256, 35, -385, 270, 1362, 35, -370, 90,
    1333, 35, -480, 270, 1183, 35, -346, 90,
    1120, 35, -484, 270, 1193, 35, -427, 90,
    1269, 35, -496, 270, 1129, 35, -328, 90,
    1370, 35, -437, 270, 1249, 35, -340, 90,
    1326, 35, -350, 270, 1298, 35, -330, 90,
    1246, 35, -369, 270, 1178, 35, -473, 90,
    1327, 35, -461, 270, 1335, 35, -447, 90,
    1343, 35, -367, 270, 1293, 35, -370, 90,
    1356, 35, -338, 270,
};

EVT_BEGIN(suifu_random_sub)
    CALL(evt_nannpc_set_subfunc, 2, PTR(nanNPCOption))
    SET_VALUE(LW(0), 10)
    SET_INT_READ_ADDR(PTR(suifu_random_setup))
    LOOP(95)
        READ_INT3(LW(1), LW(2), LW(3))
        READ_INT(LW(4))
        CALL(evt_nannpc_set_position, LW(0), LW(1), LW(2), LW(3))
        CALL(evt_nannpc_set_dir, LW(0), LW(4))
        CALL(evt_nannpc_ppflag_onoff, LW(0), 0, 1)
        CALL(evt_nannpc_flag_onoff, LW(0), 0, 4)
        CALL(evt_nannpc_set_shadow_position, LW(0), 35)
        CALL(evt_nannpc_set_size, LW(0), 30, 15)
        ADD(LW(0), 1)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_nannpc_flag_onoff, 0, 0, 4)
        CALL(evt_nannpc_set_size, 0, 30, 15)
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_nannpc_set_position, 0, LW(0), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_set_position, STRING("水夫C"), 1330, 35, -200)
    CALL(evt_npc_set_position, STRING("水夫D"), 1295, 35, -225)
    CALL(evt_npc_set_position, STRING("水夫E"), 1250, 35, -190)
    CALL(evt_npc_set_position, STRING("モニー"), 1180, 35, -275)
    CALL(evt_npc_set_position, STRING("ピートン"), 1235, 35, -275)
    CALL(evt_npc_set_ry, STRING("水夫E"), 90)
    CALL(evt_npc_set_ry, STRING("モニー"), 90)
    CALL(evt_npc_set_ry, STRING("ピートン"), 90)
    RETURN
EVT_END()

EVT_BEGIN(tama_shoot)
    CALL(evt_snd_sfxon, STRING("SFX_STG5_CANNON_FIRING1"), 0)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), GW(13))
        ADD(LW(0), 320)
        SET_VALUE(LW(1), GW(14))
        ADD(LW(1), 130)
        SET_VALUE(LW(2), GW(15))
#if VERSION <= VERSION_DEMO_US
        CALL(tama_shoot_kemuri_entry, LW(0), LW(1), LW(2), LW(10))
        CALL(tama_shoot_kemuri, LW(10), FLOAT(90.0f), FLOAT(90.0f))
#else
        CALL(evt_eff, 0, STRING("kemuri_test"), 16, LW(0), LW(1), LW(2), FLOAT(3.0f), 0, 0, 0, 0, 0, 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.0068359375f), FLOAT(0.0f), 500)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_STG5_CANNON_SEA1"), 0)
    CALL(evt_eff, 0, STRING("splash"), 0, LW(0), -20, LW(2), FLOAT(3.0f), 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(npc_kyorokyoro)
    CALL(evt_sub_random, 1000, LW(10))
    ADD(LW(10), 100)
    WAIT_MS(LW(10))
    CALL(evt_npc_reverse_ry, LW(0))
    CALL(evt_sub_random, 350, LW(10))
    ADD(LW(10), 350)
    WAIT_MS(LW(10))
    CALL(evt_npc_reverse_ry, LW(0))
    CALL(evt_sub_random, 350, LW(10))
    ADD(LW(10), 350)
    WAIT_MS(LW(10))
    CALL(evt_npc_set_ry, LW(0), 270)
    RETURN
EVT_END()

EVT_BEGIN(dai3_shurai_sub)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    LOOP(0)
        CALL(evt_mario_party_use_check, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_stop, 0)
    CALL(evt_npc_set_position, STRING("マルコ"), 1500, 35, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("マルコ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_set_position, STRING("ガラの悪い水夫"), 1500, 35, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ガラの悪い水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_set_position, STRING("オドオド水夫"), 1500, 35, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("オドオド水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("めがね水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力幹部"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_cam3d_evt_set, 1335, 145, 312, 1335, 75, -82, 1000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("マルコ"), 1370, -50, 0, FLOAT(100.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("ガラの悪い水夫"), 1385, 0, 0, FLOAT(110.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING("オドオド水夫"), 1400, -100, 0, FLOAT(80.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 1255, -100, FLOAT(120.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 1285, -80, FLOAT(120.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_95"), 0, STRING("マルコ"))
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_MS(500)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_msg_print, 0, STRING("stg5_muj_96"), 0, STRING("ガラの悪い水夫"))
    CALL(evt_set_dir_to_target, STRING("オドオド水夫"), STRING("水夫E"))
    CALL(evt_npc_get_position, STRING("オドオド水夫"), LW(0), LW(1), LW(2))
    ADD(LW(0), -10)
    CALL(evt_npc_move_position, STRING("オドオド水夫"), LW(0), LW(2), 0, FLOAT(60.0f), 0)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("オドオド水夫"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 1290, 143, 213, 1290, 90, -82, 500, 11)
    CALL(evt_npc_move_position, STRING("オドオド水夫"), 1325, -150, 0, FLOAT(180.0f), 0)
    WAIT_MS(500)
    CALL(evt_set_dir_to_target, STRING("水夫E"), STRING("オドオド水夫"))
    CALL(evt_msg_print, 0, STRING("stg5_muj_99"), 0, STRING("オドオド水夫"))
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("水夫E"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_100"), 0, STRING("水夫E"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_101"), 0, STRING("オドオド水夫"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_102"), 0, STRING("水夫C"))
    CALL(evt_cam3d_evt_set, 1335, 145, 312, 1335, 75, -82, 500, 11)
    WAIT_MS(1000)
    CALL(evt_npc_flag_onoff, 0, STRING("マルコ"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("ガラの悪い水夫"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("オドオド水夫"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("モニー"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("ピートン"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("水夫C"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("水夫D"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("水夫E"), NPC_FLAG_TALK_ANIM)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg5_muj_103"), 0, STRING("マルコ"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg5_muj_103"), 0, STRING("ガラの悪い水夫"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg5_muj_103"), 0, STRING("オドオド水夫"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg5_muj_103"), 0, STRING("ピートン"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg5_muj_103"), 0, STRING("水夫E"))
    END_INLINE_EVENT
    WAIT_MS(2000)
    CALL(evt_npc_flag_onoff, 1, STRING("マルコ"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("ガラの悪い水夫"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("オドオド水夫"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("モニー"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("ピートン"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("水夫C"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("水夫D"), NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("水夫E"), NPC_FLAG_TALK_ANIM)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_sfxon, STRING("SFX_STG5_CANNON_FIRING1"), 0)
    CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.009765625f), FLOAT(0.0f), 1000)
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_party_set_dir, 0, 270, 200)
    CALL(evt_npc_set_ry, STRING("ピートン"), 270)
    WAIT_MS(500)
    SET_VALUE(LW(0), 10)
    LOOP(95)
        CALL(evt_nannpc_set_func, LW(0), PTR(suifu_kyorokyoro_init))
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(0), STRING("モニー"))
    SPAWN_EVENT(npc_kyorokyoro)
    SET_VALUE(LW(0), STRING("水夫C"))
    SPAWN_EVENT(npc_kyorokyoro)
    SET_VALUE(LW(0), STRING("水夫D"))
    SPAWN_EVENT(npc_kyorokyoro)
    SET_VALUE(LW(0), STRING("水夫E"))
    SPAWN_EVENT(npc_kyorokyoro)
    SET_VALUE(LW(0), STRING("オドオド水夫"))
    SPAWN_EVENT(npc_kyorokyoro)
    SET_VALUE(LW(0), STRING("ガラの悪い水夫"))
    SPAWN_EVENT(npc_kyorokyoro)
    SET_VALUE(LW(0), STRING("マルコ"))
    SPAWN_EVENT(npc_kyorokyoro)
    WAIT_MS(3000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_104"), 0, STRING("オドオド水夫"))
    WAIT_MS(1000)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
    CALL(evt_cam3d_evt_set, 60, 180, 369, 1289, 10, -184, 0, 11)
    SET_VALUE(LW(0), 741)
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 48)
    SET_FLOAT_VALUE(LW(3), FLOAT(4.0f))
    CALL_CHILD(tama_shoot)
    WAIT_MS(1000)
    SET_VALUE(LW(0), 872)
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), -155)
    SET_FLOAT_VALUE(LW(3), FLOAT(2.0f))
    CALL_CHILD(tama_shoot)
    WAIT_MS(1000)
    SET_VALUE(LW(0), 991)
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 77)
    SET_FLOAT_VALUE(LW(3), FLOAT(3.0f))
    CALL_CHILD(tama_shoot)
    WAIT_MS(3000)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ガラの悪い水夫"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_124"), 0, STRING("ガラの悪い水夫"))
    CALL(evt_cam3d_evt_set, 350, 150, 654, -865, 200, 82, 1000, 11)
    CALL(evt_mapobj_trans, 1, STRING("S_c"), -1100, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_c"), 0, 0, 0)
    SET_FLOAT_VALUE(GW(13), -1100)
    SET_FLOAT_VALUE(GW(14), 0)
    SET_FLOAT_VALUE(GW(15), 0)
    CALL(evt_hit_bind_update, STRING("A_c"))
    WAIT_MS(2000)
    SET_VALUE(LW(0), 991)
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 77)
    SET_FLOAT_VALUE(LW(3), FLOAT(3.0f))
    CALL_CHILD(tama_shoot)
    WAIT_MS(2000)
    CALL(evt_npc_set_position, STRING("めがね水夫"), -991, 58, -16)
    CALL(evt_npc_set_ry, STRING("めがね水夫"), 90)
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), 0, -100, 0)
    CALL(evt_npc_set_ry, STRING("第三勢力幹部"), 90)
    CALL(evt_msg_print, 0, STRING("stg5_muj_105"), 0, STRING("めがね水夫"))
    WAIT_MS(1000)
    CALL(evt_npc_jump_position_nohit, STRING("めがね水夫"), -802, 162, 0, 500, 120)
    CALL(evt_cam3d_evt_set, -370, 192, 203, -821, 210, -11, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_106"), 0, STRING("めがね水夫"))
    CALL(evt_cam3d_evt_set, -404, 360, 514, 119, 260, 216, 0, 11)
    CALL(evt_npc_set_position, STRING("めがね水夫"), 261, 155, 8)
    CALL(evt_mapobj_trans, 1, STRING("S_c"), 0, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_c"), 0, 0, 0)
    SET_FLOAT_VALUE(GW(13), 0)
    SET_FLOAT_VALUE(GW(14), 0)
    SET_FLOAT_VALUE(GW(15), 0)
    CALL(evt_hit_bind_update, STRING("A_c"))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_107"), 0, STRING("ガラの悪い水夫"))
    CALL(evt_msg_print, 0, STRING("stg5_muj_108"), 0, STRING("オドオド水夫"))
    CALL(evt_cam3d_evt_set, 700, 145, 178, 202, 210, -46, 0, 11)
    WAIT_MS(1000)
    SET_VALUE(LW(0), 991)
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 77)
    SET_FLOAT_VALUE(LW(3), FLOAT(3.0f))
    CALL_CHILD(tama_shoot)
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_109"), 0, STRING("めがね水夫"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("めがね水夫"), LW(0), LW(1), LW(2))
        WAIT_MS(400)
        CALL(evt_npc_set_position, STRING("めがね水夫"), 0, -1000, 0)
        CALL(evt_npc_set_position, STRING("第三勢力幹部"), LW(0), LW(1), LW(2))
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 0, 0, 720, 800)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MODULO(LW(0), 360)
        CALL(evt_npc_set_rotate, STRING("めがね水夫"), 0, LW(0), 0)
        CALL(evt_npc_set_rotate, STRING("第三勢力幹部"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SURPRISED1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_110"), 0, STRING("第三勢力幹部"))
    CALL(evt_npc_set_ry, STRING("マルコ"), 180)
    CALL(evt_cam3d_evt_set, 1195, 50, 405, 200, 180, -43, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_111"), 0, STRING("第三勢力幹部"))
    SET_VALUE(LW(0), 991)
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 77)
    SET_FLOAT_VALUE(LW(3), FLOAT(3.0f))
    CALL_CHILD(tama_shoot)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, 1975, 128, 0, -623, 128, 0, 0, 11)
    CALL(evt_npc_set_ry_lr, STRING("オドオド水夫"), 0)
    CALL(evt_mapobj_trans, 1, STRING("S_c"), -1000, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_c"), 0, 0, 0)
    SET_FLOAT_VALUE(GW(13), -1000)
    SET_FLOAT_VALUE(GW(14), 0)
    SET_FLOAT_VALUE(GW(15), 0)
    CALL(evt_hit_bind_update, STRING("A_c"))
    CALL(evt_mario_dispflag_onoff, 1, 4)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), -707, 162, 9)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg5_muj_112"), 0, STRING("第三勢力幹部"))
    SPAWN_EVENT_GET_ID(PTR(dai3_shurai_after), GW(8))
    CALL(evt_msg_print, 0, STRING("stg5_muj_113"), 0, STRING("マルコ"))
    CALL(evt_msg_print, 0, STRING("stg5_muj_114"), 0, STRING("ガラの悪い水夫"))
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("マルコ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_115"), 0, STRING("マルコ"))
    CALL(evt_msg_print, 0, STRING("stg5_muj_116"), 0, STRING("オドオド水夫"))
    CALL(evt_npc_set_ry_lr, STRING("マルコ"), 1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_117"), 0, STRING("マルコ"))
    CALL(evt_npc_set_ry_lr, STRING("マルコ"), 0)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("マルコ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("マルコ"), 0, -1000, 0)
    CALL(evt_party_stop, 1)
    CALL(evt_mario_set_party_pos, 1, 9, LW(0), LW(1), LW(2))
    WAIT_MS(1000)
    CALL(evt_party_run, 1)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 0, STRING("オドオド水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("ガラの悪い水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("マルコ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("水夫C"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("水夫D"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("水夫E"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_40_TRUE_IDENTITY)
    CALL(evt_mario_adjust_dir)
    CALL(evt_mario_dispflag_onoff, 0, 4)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(dai3_shurai)
    CALL(evt_mapobj_trans, 1, STRING("S_c"), 0, -1000, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_c"), 0, 0, 0)
    SET_FLOAT_VALUE(GW(13), 0)
    SET_FLOAT_VALUE(GW(14), -1000)
    SET_FLOAT_VALUE(GW(15), 0)
    CALL(evt_hit_bind_update, STRING("A_c"))
    LOOP(0)
        CALL(evt_mario_get_name_hitobj_ride, LW(10))
        IF_STR_EQUAL(LW(10), STRING("A_yuka01"))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(2), -125)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SPAWN_EVENT(dai3_shurai_sub)
    RETURN
EVT_END()

static EVT_BEGIN(dai3_shurai_after)
    LOOP(0)
        CALL(evt_sub_random, 2500, LW(10))
        WAIT_MS(LW(10))
        WAIT_MS(500)
        CALL(evt_sub_random, 2, LW(11))
        SWITCH(LW(11))
            CASE_EQUAL(0)
            SET_VALUE(LW(0), 1086)
            SET_VALUE(LW(1), -60)
            SET_VALUE(LW(2), -247)
            SET_FLOAT_VALUE(LW(3), FLOAT(4.0f))
            CALL_CHILD(tama_shoot)
            CASE_EQUAL(1)
            SET_VALUE(LW(0), 1135)
            SET_VALUE(LW(1), -60)
            SET_VALUE(LW(2), 51)
            SET_FLOAT_VALUE(LW(3), FLOAT(2.0f))
            CALL_CHILD(tama_shoot)
            CASE_EQUAL(2)
            SET_VALUE(LW(0), 1251)
            SET_VALUE(LW(1), -60)
            SET_VALUE(LW(2), 153)
            SET_FLOAT_VALUE(LW(3), FLOAT(3.0f))
            CALL_CHILD(tama_shoot)
        END_SWITCH
    END_LOOP
    RETURN
EVT_END()

s32 kaizoku_vs_dai3_suifupos[] = {
    -88, 115, -6, 270, -87, 115, 15, 270,
    -92, 115, 34, 270, -104, 115, 76, 270,
    -110, 115, 66, 270, -84, 115, 75, 270,
    -110, 115, 66, 270, -129, 115, 34, 270,
    -129, 115, 11, 270, -139, 115, -8, 270,
    -153, 115, -6, 270, -123, 115, -18, 270,
    -104, 115, -27, 270, -156, 115, 26, 270,
    -156, 115, 51, 270, -153, 115, 53, 270,
    -135, 115, 53, 270, -108, 115, 57, 270,
    -95, 115, 67, 270, -84, 115, 67, 270,
    -102, 115, -50, 270, -112, 115, -49, 270,
    -132, 115, -39, 270, -147, 115, -29, 270,
    -153, 115, -41, 270, -153, 115, -2, 270,
    -138, 115, 14, 270, -121, 115, 31, 270,
    -105, 115, 35, 270, -105, 115, 53, 270,
    -118, 115, 62, 270, -127, 115, 44, 270,
    -142, 115, 56, 270, -155, 115, 27, 270,
    -137, 115, 8, 270, -137, 115, -28, 270,
    -124, 115, -37, 270, -107, 115, -55, 270,
    -91, 115, -47, 270, -86, 115, -37, 270,
    -86, 115, -72, 270, -108, 115, -58, 270,
    -131, 115, -53, 270, -153, 115, -52, 270,
    -155, 115, -44, 270, -32, 40, -66, 270,
    -64, 40, -19, 270, -52, 40, -35, 270,
    -12, 40, 59, 270, -39, 40, 56, 270,
    -52, 40, 51, 270, -54, 40, 76, 270,
    -43, 40, 66, 270, -19, 40, 53, 270,
    -32, 40, 85, 270, -26, 40, 71, 270,
    -45, 40, 40, 270, -52, 40, 8, 270,
    -50, 40, -9, 270, -21, 40, -52, 270,
    -27, 40, -42, 270, -37, 40, -81, 270,
    -52, 40, -78, 270, -37, 40, -46, 270,
    -62, 40, -70, 270, -62, 40, -57, 270,
    -62, 40, 11, 270, -61, 40, -38, 270,
    -42, 40, -27, 270, -22, 40, -24, 270,
    -22, 40, -5, 270, -22, 40, 22, 270,
    -41, 40, 22, 270, -61, 40, 22, 270,
    -53, 40, 41, 270, -60, 40, 28, 270,
    -53, 40, -1, 270, -36, 40, -3, 270,
    -32, 40, 13, 270, -27, 40, 31, 270,
    -27, 40, 31, 270, -10, 40, 39, 270,
    -29, 40, -12, 270, -14, 40, -37, 270,
    -12, 40, -66, 270, -59, 40, 60, 270,
    -32, 40, -27, 270, -17, 40, -84, 270,
    -26, 40, -78, 270, -47, 40, -65, 270,
    -47, 40, -45, 270, -60, 40, -42, 270,
    -60, 40, 34, 270, -55, 40, 81, 270,
    -61, 40, 65, 270,
};

s32 kaizoku_vs_dai3_elmospos[] = {
    51, 165, 25, 270, 34, 112, -63, 270,
    37, 158, 67, 270, 24, 191, 69, 270,
    28, 228, -49, 270, 33, 201, -32, 270,
    30, 195, -5, 270, 31, 166, 1, 270,
    38, 144, 47, 270, 36, 192, 43, 270,
    41, 164, 35, 247, 0, 244, 17, 270,
    39, 185, 31, 270, 33, 183, -100, 270,
    7, 108, -53, 270, 36, 249, 20, 270,
    36, 164, -73, 270, 39, 148, 93, 270,
    6, 102, -76, 270, 41, 138, -31, 270,
    7, 235, 58, 270, 30, 241, -93, 270,
    31, 214, 91, 270, 32, 132, 6, 270,
    34, 185, 14, 270, 41, 148, -13, 270,
    38, 141, -72, 270, 35, 209, -53, 270,
    38, 152, 7, 270, 33, 108, -17, 270,
    14, 230, -11, 270, 35, 117, 115, 270,
    9, 247, 30, 270, 40, 161, -58, 270,
    10, 100, 65, 270, 37, 113, 80, 270,
    7, 206, 119, 270, 28, 247, 107, 270,
    36, 188, -72, 270, 37, 176, -24, 270,
    14, 181, -73, 270, 34, 176, -53, 270,
    41, 133, 26, 270, 23, 207, 61, 270,
    30, 201, 25, 270, 10, 237, 57, 270,
    30, 239, 97, 270, 19, 241, 13, 270,
    32, 187, 79, 270, 32, 184, 125, 270,
    8, 192, 19, 270, 25, 214, 38, 270,
    24, 145, 37, 270, 18, 232, -86, 270,
    12, 223, 38, 270, 21, 212, 16, 270,
    39, 119, 45, 270, 34, 198, 107, 270,
    34, 109, -113, 270, 29, 205, -83, 270,
    32, 214, 116, 270, 15, 223, 0, 270,
    3, 126, 31, 270, 37, 199, -45, 270,
    33, 217, -18, 270, 7, 101, -13, 270,
    36, 126, -88, 270, 21, 232, -113, 270,
    36, 141, 125, 270, 25, 100, -33, 270,
    2, 210, 47, 270, 41, 166, 125, 270,
    39, 176, 100, 270, 42, 138, 70, 238,
    8, 226, 2, 270, 40, 164, 85, 270,
    34, 172, 57, 270, 28, 228, 74, 270,
    15, 229, -68, 270, 38, 108, 107, 270,
    19, 239, -37, 270, 24, 115, 112, 270,
    35, 209, -96, 270, 16, 125, 5, 270,
    7, 166, 116, 270, 38, 121, 90, 270,
    36, 150, -105, 270, 36, 163, -113, 270,
    29, 167, -111, 270, 35, 206, -118, 270,
    14, 247, 37, 270, 8, 249, 67, 270,
    3, 184, -6, 270, 7, 182, 124, 270,
    19, 115, -50, 270, 36, 160, -90, 270,
    12, 103, 24, 270, 6, 167, 71, 270,
    29, 186, 68, 270, 0, 179, -38, 270,
};

EVT_BEGIN(iwapera_offscreen)
    CALL(evt_img_entry, STRING("capture_img"))
    CALL(evt_img_set_paper, STRING("capture_img"), STRING("OFF_d_yabu"))
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_iwa_before"), STRING("offscreen"))
    CALL(evt_offscreen_get_boundingbox, STRING("offscreen"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, STRING("capture_img"), 0, 0, 1, LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, STRING("capture_img"), 2, STRING("offscreen"), 1, LW(10), LW(11), LW(12), LW(13))
    WAIT_MS(1500)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_before"), MAPOBJ_FLAG_HIDE)
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_1"))
    RETURN
EVT_END()

EVT_BEGIN(iwapera_offscreen_end)
    CALL(evt_img_wait_animend, STRING("capture_img"))
    CALL(evt_img_free_capture, STRING("capture_img"), 0)
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_release, STRING("capture_img"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_iwa_before"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_iwa_after"), MAPOBJ_FLAG_HIDE)
    RETURN
EVT_END()

EVT_BEGIN(dai3_kurukuru)
    CALL(evt_snd_sfxon, STRING("SFX_STG5_SHIP_IMPACT1"), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.01953125f), FLOAT(0.0f), 500)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), GW(1))
        SET_VALUE(LW(1), LW(0))
        ADD(LW(1), 15)
        CALL(evt_sub_intpl_msec_init, 4, LW(0), LW(1), 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(GW(1), LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), GW(2))
        SET_VALUE(LW(1), LW(0))
        ADD(LW(1), -80)
        CALL(evt_sub_intpl_msec_init, 4, LW(0), LW(1), 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(GW(2), LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

s32 kaizoku_vs_dai3_dai3pos[] = {
    107, 159, -120, 10, 245, -57, 8, 152,
    40, 100, 164, -87, 3, 121, -28, -13,
    130, -5, 106, 212, -59, -14, 186, -87,
    -2, 196, 66, 109, 214, 54, -11, 156,
    59, 93, 227, -109, 104, 227, -86, 99,
    134, -24, 0, 200, -139, 102, 105, -37,
    91, 122, -35, 101, 159, -42, -18, 207,
    -90, -15, 231, -146, -16, 132, -39, 106,
    123, -8, 96, 123, -94, -19, 141, 94,
    -18, 261, -8, -18, 137, 61, -2, 109,
    -5, 94, 195, -99, -13, 209, -133, -2,
    228, -10, 97, 188, -120, -18, 211, -25,
    -3, 224, -65, -2, 153, 85, 95, 191,
    -117, 107, 220, 33, 8, 129, -47, 2,
    153, 132, -13, 119, 33, 99, 127, -63,
    -8, 209, -67, -9, 195, 93, -7, 198,
    127, 7, 123, -89, 85, 175, 101, 110,
    175, -101, 1, 155, -140, 7, 152, -61,
    102, 107, -69, 98, 134, 96, 110, 136,
    35, 4, 139, 49, -3, 131, 40, 102,
    182, -47, 5, 247, 90, -3, 179, -19,
    -3, 120, -88, 102, 167, -15, 6, 223,
    139, 95, 195, -20, 91, 170, 6, 10,
    217, 41, -19, 145, 121, -7, 133, 56,
    5, 237, -28, -4, 209, -92, 96, 220,
    94, 99, 182, 75, 101, 223, 85, 91,
    125, -46, 6, 250, 51, 4, 213, 90,
    101, 179, 41, -10, 244, 16, 1, 134,
    20, 104, 143, 14, 103, 203, -73, -1,
    249, 134, 7, 200, -49, -2, 238, -58,
    -6, 245, -110, 103, 129, 69, 93, 162,
    89, 0, 122, -44, 1, 112, 71, 107,
    163, 55, -15, 169, 18, 5, 183, 107,
    84, 201, 10, -9, 124, -138, 108, 177,
    -75, 7, 234, -26, 2, 170, 55, -12,
    124, 92, 109, 208, -74, -10, 132, -79,
    -15, 135, 79, -2, 264, 112, -13, 130,
    2, -18, 217, -94,
};

EVT_BEGIN(dai3_butai_setup)
    SET_VALUE(LW(0), 205)
    SET_INT_READ_ADDR(PTR(kaizoku_vs_dai3_dai3pos))
    LOOP(100)
        CALL(evt_nannpc_set_dir, LW(0), 90)
        READ_INT3(LW(1), LW(2), LW(3))
        ADD(LW(1), GW(2))
        ADD(LW(3), GW(3))
        CALL(evt_nannpc_set_position, LW(0), LW(1), LW(2), LW(3))
        SET_VALUE(LW(12), 0)
        SUBTRACT(LW(12), GW(3))
        SET_VALUE(LW(13), 0)
        SUBTRACT(LW(13), LW(3))
        CALL(evt_sub_get_dir, GW(2), LW(12), LW(1), LW(13), LW(10))
        CALL(evt_sub_get_dist, GW(2), LW(12), LW(1), LW(13), LW(11))
        CALL(evt_nannpc_set_work, LW(0), 0, LW(10))
        CALL(evt_nannpc_set_work, LW(0), 1, LW(11))
        ADD(LW(0), 1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dai3_butai_main)
    SET_VALUE(LW(10), GW(1))
    LOOP(0)
        CALL(dai3_butai_main_func, LW(10), GW(1), GW(2), GW(3))
        SET_VALUE(LW(10), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dai3_kanbu_setup)
    RETURN
EVT_END()

EVT_BEGIN(dai3_kanbu_main)
    CALL(evt_npc_get_position, STRING("第三勢力幹部"), LW(1), LW(2), LW(3))
    CALL(evt_sub_get_dir, GW(2), GW(3), LW(1), LW(3), GW(10))
    CALL(evt_sub_get_dist, GW(2), GW(3), LW(1), LW(3), GW(11))
    SET_VALUE(LW(10), GW(1))
    LOOP(0)
        SET_VALUE(LW(11), GW(1))
        SUBTRACT(LW(11), LW(10))
        SUBTRACT(GW(10), LW(11))
        SET_VALUE(LW(0), 0)
        SUBTRACT(LW(0), GW(10))
        ADD(LW(0), 180)
        CALL(evt_sub_get_sincos, LW(0), LW(14), LW(15))
        MULTIPLY_FLOAT(LW(14), GW(11))
        MULTIPLY_FLOAT(LW(15), GW(11))
        ADD_FLOAT(LW(14), GW(2))
        ADD_FLOAT(LW(15), GW(3))
        CALL(evt_npc_get_position, STRING("第三勢力幹部"), LW(1), LW(2), LW(3))
        CALL(evt_npc_set_position, STRING("第三勢力幹部"), LW(14), LW(2), LW(15))
        SET_VALUE(LW(10), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(kaizoku_setup)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, -1)
    CALL(evt_party_set_dir, 1, 270, -1)
    SET_VALUE(LW(0), 10)
    SET_INT_READ_ADDR(PTR(kaizoku_vs_dai3_suifupos))
    LOOP(95)
        READ_INT3(LW(1), LW(2), LW(3))
        ADD(LW(1), GW(5))
        ADD(LW(3), GW(6))
        CALL(evt_nannpc_set_position, LW(0), LW(1), LW(2), LW(3))
        READ_INT(LW(4))
        CALL(evt_nannpc_set_dir, LW(0), LW(4))
        SET_VALUE(LW(12), 0)
        SUBTRACT(LW(12), GW(6))
        SET_VALUE(LW(13), 0)
        SUBTRACT(LW(13), LW(3))
        CALL(evt_sub_get_dir, GW(5), LW(12), LW(1), LW(13), LW(10))
        CALL(evt_sub_get_dist, GW(5), LW(12), LW(1), LW(13), LW(11))
        CALL(evt_nannpc_set_work, LW(0), 0, LW(10))
        CALL(evt_nannpc_set_work, LW(0), 1, LW(11))
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(0), 105)
    SET_INT_READ_ADDR(PTR(kaizoku_vs_dai3_elmospos))
    LOOP(100)
        READ_INT3(LW(1), LW(2), LW(3))
        ADD(LW(1), GW(5))
        ADD(LW(3), GW(6))
        CALL(evt_nannpc_set_position, LW(0), LW(1), LW(2), LW(3))
        READ_INT(LW(4))
        CALL(evt_nannpc_set_dir, LW(0), LW(4))
        SET_VALUE(LW(12), 0)
        SUBTRACT(LW(12), GW(6))
        SET_VALUE(LW(13), 0)
        SUBTRACT(LW(13), LW(3))
        CALL(evt_sub_get_dir, GW(5), LW(12), LW(1), LW(13), LW(10))
        CALL(evt_sub_get_dist, GW(5), LW(12), LW(1), LW(13), LW(11))
        CALL(evt_nannpc_set_work, LW(0), 0, LW(10))
        CALL(evt_nannpc_set_work, LW(0), 1, LW(11))
        CALL(evt_nannpc_ppflag_onoff, LW(0), 0, 4)
        ADD(LW(0), 1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(kaizoku_main)
    SET_VALUE(LW(10), GW(4))
    LOOP(0)
        CALL(kaizoku_main_func, LW(10), GW(4), GW(5), GW(6))
        SET_VALUE(LW(10), GW(4))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mario_main_init)
    CALL(mario_main_init_func)
    RETURN
EVT_END()

EVT_BEGIN(mario_main)
    CALL(evt_mario_set_pos, 20, 40, 10)
    CALL(evt_party_set_pos, 0, 10, 40, -65)
    CALL(evt_npc_set_position, STRING("マルコ"), 20, 40, -35)
    CALL(evt_npc_set_position, STRING("コルテス"), 126, 75, -30)
    CALL(evt_npc_set_position, STRING("ガラの悪い水夫"), 32, 40, 35)
    CALL(evt_npc_set_position, STRING("モニー"), 10, 40, 36)
    CALL(evt_npc_set_ry, STRING("モニー"), 270)
    CALL(evt_npc_set_position, STRING("ピートン"), 15, 40, 72)
    CALL(evt_npc_set_ry, STRING("ピートン"), 270)
    CALL(evt_npc_set_position, STRING("オドオド水夫"), -6, 40, -88)
    CALL(evt_npc_set_ry, STRING("オドオド水夫"), 270)
    CALL(mario_main_setup_func, GW(5), GW(6))
    SET_VALUE(LW(10), GW(4))
    LOOP(0)
        CALL(mario_main_func, LW(10), GW(4), GW(5), GW(6))
        SET_VALUE(LW(10), GW(4))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mario_main2)
    CALL(evt_mario_set_pos, 20, 40, 10)
    CALL(evt_party_set_pos, 0, 10, 40, -25)
    CALL(evt_npc_set_position, STRING("マルコ"), -3, 40, -69)
    CALL(evt_npc_set_position, STRING("コルテス"), 126, 75, -30)
    CALL(evt_npc_set_position, STRING("ガラの悪い水夫"), 32, 40, 35)
    CALL(evt_npc_set_position, STRING("モニー"), 10, 40, 36)
    CALL(evt_npc_set_ry, STRING("モニー"), 270)
    CALL(evt_npc_set_position, STRING("ピートン"), 15, 40, 72)
    CALL(evt_npc_set_ry, STRING("ピートン"), 270)
    CALL(evt_npc_set_position, STRING("オドオド水夫"), -6, 40, -88)
    CALL(evt_npc_set_ry, STRING("オドオド水夫"), 270)
    CALL(mario_main_setup_func, GW(5), GW(6))
    SET_VALUE(LW(10), GW(4))
    LOOP(0)
        CALL(mario_main_func, LW(10), GW(4), GW(5), GW(6))
        SET_VALUE(LW(10), GW(4))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(kaizoku_move_every)
    LOOP(0)
        CALL(evt_mapobj_trans, 1, STRING("S_b"), GW(5), 0, GW(6))
        CALL(evt_mapobj_rotate, 1, STRING("S_b"), 0, GW(4), 0)
        CALL(evt_hit_bind_update, STRING("A_b"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dai3_move_every)
    LOOP(0)
        CALL(evt_mapobj_trans, 1, STRING("S_c"), GW(2), 0, GW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_c"), 0, GW(1), 0)
        SET_FLOAT_VALUE(GW(13), GW(2))
        SET_FLOAT_VALUE(GW(14), 0)
        SET_FLOAT_VALUE(GW(15), GW(3))
        CALL(evt_hit_bind_update, STRING("A_c"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

f32 dai3_spline_dt[] = {
    -1200.0f, 0.0f, -0.0f, -1100.5623f, 0.0f, -8.453464f, -293.84833f, 0.0f,
    399.23074f, 34.78095f, 0.0f, 432.56693f, 421.29593f, 0.0f, 248.42857f, 461.67648f,
    0.0f, 165.65f, 415.21323f, 0.0f, -397.27994f, -330.27072f, 0.0f, -496.12314f,
    -362.64764f, 0.0f, -332.12228f,
};

f32 kaizoku_spline_dt[] = {
    -35.35443f, 0.0f, -1842.3301f, -144.56525f, 0.0f, -833.1615f, -259.41003f, 0.0f,
    -703.04047f, -643.16766f, 0.0f, -279.92737f, -441.1687f, 0.0f, 463.3269f, 122.979614f,
    0.0f, 678.0878f, 398.20316f, 0.0f, 594.73975f, 606.0688f, 0.0f, 63.382736f,
    199.88821f, 0.0f, -403.68475f, -80.28505f, 0.0f, -265.78485f,
};

EVT_BEGIN(kaizoku_move_trace_se)
    CALL(evt_mapobj_get_position, STRING("S_b"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_KOR_SHIP_MOVE1"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_snd_sfx_dist, LW(13), 30)
    BEGIN_INLINE_EVENT_GET_ID(LW(14))
        LOOP(0)
            CALL(evt_mapobj_get_position, STRING("S_b"), LW(10), LW(11), LW(12))
            CALL(evt_snd_sfx_pos, LW(13), LW(10), LW(11), LW(12))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_WHILE(GF(10))
    CALL(evt_snd_sfxoff, LW(13))
    DELETE_EVENT(LW(14))
    RETURN
EVT_END()

EVT_BEGIN(kaizoku_move_trace)
    SET_FLOAT_VALUE(LW(5), GW(5))
    SET_FLOAT_VALUE(LW(6), GW(6))
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), LW(0))
    MULTIPLY(LW(9), 100)
    CALL(evt_sub_spline_init, 1, 0, PTR(kaizoku_spline_dt), 10, 0, LW(0))
    LOOP(0)
        SET_VALUE(LW(10), LW(8))
        DIVIDE(LW(10), 100)
        CALL(evt_sub_spline_get_value_manual, LW(10), LW(0), LW(1), LW(2))
        SWITCH(LW(8))
            CASE_LESS(200000)
            SET_VALUE(LW(7), 600)
            CASE_LESS(300000)
            SET_VALUE(LW(7), 1000)
            CASE_LESS(400000)
            SET_VALUE(LW(7), 1300)
            CASE_LESS(600000)
            SET_VALUE(LW(7), 1600)
            CASE_LESS(800000)
            SET_VALUE(LW(7), 2000)
        END_SWITCH
        ADD(LW(8), LW(7))
        SET_VALUE(LW(3), 1)
        IF_INT_GREATER_OR_EQUAL(LW(8), LW(9))
            SET_VALUE(LW(3), 0)
        END_IF
        SET_FLOAT_VALUE(GW(5), LW(0))
        SET_FLOAT_VALUE(GW(6), LW(2))
        SET_VALUE(LF(0), 1)
        IF_FLOAT_EQUAL(GW(5), LW(5))
            IF_FLOAT_EQUAL(GW(6), LW(6))
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            CALL(ship_rotate, LW(5), LW(6), GW(5), GW(6), GW(4))
        END_IF
        IF_INT_EQUAL(LW(3), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
        SET_FLOAT_VALUE(LW(5), GW(5))
        SET_FLOAT_VALUE(LW(6), GW(6))
    END_LOOP
    CALL(evt_sub_spline_free)
    SET_VALUE(GF(10), 0)
    RETURN
EVT_END()

EVT_BEGIN(dai3_move_trace_se)
    CALL(evt_mapobj_get_position, STRING("S_c"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_3RD_SHIP_MOVE1"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_snd_sfx_dist, LW(13), 30)
    BEGIN_INLINE_EVENT_GET_ID(LW(14))
        LOOP(0)
            CALL(evt_mapobj_get_position, STRING("S_b"), LW(10), LW(11), LW(12))
            CALL(evt_snd_sfx_pos, LW(13), LW(10), LW(11), LW(12))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_WHILE(GF(11))
    CALL(evt_snd_sfxoff, LW(13))
    DELETE_EVENT(LW(14))
    RETURN
EVT_END()

EVT_BEGIN(dai3_move_trace)
    SET_FLOAT_VALUE(LW(5), GW(2))
    SET_FLOAT_VALUE(LW(6), GW(3))
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), LW(0))
    MULTIPLY(LW(9), 100)
    CALL(evt_sub_spline_init, 1, 0, PTR(dai3_spline_dt), 9, 0, LW(0))
    LOOP(0)
        SET_VALUE(LW(10), LW(8))
        DIVIDE(LW(10), 100)
        CALL(evt_sub_spline_get_value_manual, LW(10), LW(0), LW(1), LW(2))
        ADD(LW(8), 1115)
        SET_VALUE(LW(3), 1)
        IF_INT_GREATER_OR_EQUAL(LW(8), LW(9))
            SET_VALUE(LW(3), 0)
        END_IF
        SET_FLOAT_VALUE(GW(2), LW(0))
        SET_FLOAT_VALUE(GW(3), LW(2))
        SET_VALUE(LF(0), 1)
        IF_FLOAT_EQUAL(GW(2), LW(5))
            IF_FLOAT_EQUAL(GW(3), LW(6))
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            CALL(ship_rotate, LW(5), LW(6), GW(2), GW(3), GW(1))
        END_IF
        IF_INT_EQUAL(LW(3), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
        SET_FLOAT_VALUE(LW(5), GW(2))
        SET_FLOAT_VALUE(LW(6), GW(3))
    END_LOOP
    CALL(evt_sub_spline_free)
    RETURN
EVT_END()

static EVT_BEGIN(_kemuri_sub)
    CALL(evt_sub_random, 300, LW(0))
    ADD(LW(0), -400)
    CALL(evt_sub_random, 150, LW(1))
    ADD(LW(1), 150)
    CALL(evt_sub_random, 50, LW(2))
    ADD(LW(2), -300)
    CALL(evt_sub_random, 100, LW(3))
    ADD_FLOAT(LW(3), FLOAT(50.0f))
    DIVIDE_FLOAT(LW(3), FLOAT(100.0f))
    CALL(evt_eff, 0, STRING("kemuri_test"), 2, LW(0), LW(1), LW(2), LW(3), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG0_3RD_ATTACK3"), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(tobikakari_kemuri)
    LOOP(0)
        SPAWN_EVENT(_kemuri_sub)
        SPAWN_EVENT(_kemuri_sub)
        CALL(evt_sub_random, 200, LW(0))
        ADD(LW(0), 200)
        WAIT_MS(LW(0))
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(cam_dai3_vs_kaizoku)
    SET_VALUE(LW(0), 70)
    SET_VALUE(LW(1), 1400)
    CALL(cam_test_init_func, LW(0), LW(1), LW(2), LW(3))
    ADD_FLOAT(LW(2), FLOAT(-120.0f))
    CALL(evt_cam3d_evt_set, LW(0), 110, LW(1), 70, 90, 0, 0, 11)
    LOOP(0)
        CALL(cam_test_func, LW(0), LW(1), LW(2), LW(3))
        CALL(evt_cam3d_evt_set, LW(0), 110, LW(1), 70, 90, 0, 0, 11)
        ADD_FLOAT(LW(2), FLOAT(0.26953125f))
        IF_INT_GREATER_OR_EQUAL(LW(2), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(2), FLOAT(360.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(kaizoku_vs_dai3)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_clear_party, 1)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("コルテス"), 20, 40, -1800)
    CALL(evt_npc_set_ry, STRING("コルテス"), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("コルテス"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), -945, 150, -5)
    CALL(evt_npc_set_ry, STRING("第三勢力幹部"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力幹部"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INSTANT_TURN | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("第三勢力幹部"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("モニー"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("ピートン"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("ガラの悪い水夫"), NPC_FLAG_MOVE_ANIM)
    SET_VALUE(GW(1), 0)
    SET_VALUE(GW(2), -1200)
    SET_VALUE(GW(3), 0)
    SPAWN_EVENT_GET_ID(PTR(dai3_move_every), LW(10))
    SET_VALUE(GW(4), 0)
    SET_VALUE(GW(5), 0)
    SET_VALUE(GW(6), -2000)
    SPAWN_EVENT_GET_ID(PTR(kaizoku_move_every), LW(11))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hai"), MAPOBJ_FLAG_HIDE)
    CALL(evt_cam3d_evt_set, -847, 334, 977, -847, 78, -475, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_msg_print, 0, STRING("stg5_muj_118"), 0, STRING("第三勢力幹部"))
    DELETE_EVENT(GW(8))
    CALL(evt_cam3d_evt_set, 0, 470, -91, 0, 400, -383, 500, 11)
    WAIT_MS(600)
    CALL(evt_npc_flag_onoff, 0, STRING("第三勢力幹部"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), -1105, 60, 30)
    SPAWN_EVENT(dai3_butai_setup)
    WAIT_FRAMES(2)
    SPAWN_EVENT_GET_ID(PTR(dai3_butai_main), LW(12))
    SPAWN_EVENT_GET_ID(PTR(dai3_kanbu_main), LW(13))
    SPAWN_EVENT(kaizoku_setup)
    WAIT_FRAMES(2)
    SPAWN_EVENT_GET_ID(PTR(kaizoku_main), LW(14))
    SPAWN_EVENT_GET_ID(PTR(mario_main), LW(15))
    WAIT_MS(400)
    CALL(evt_npc_flag_onoff, 1, STRING("コルテス"), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_pera_onoff, STRING("コルテス"), 0)
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_119"), 0, STRING("コルテス"))
    CALL(evt_msg_continue)
    SET_VALUE(GF(0), 1)
    SET_VALUE(GF(1), 1)
    BEGIN_INLINE_EVENT
        SET_VALUE(GF(10), 1)
        SPAWN_EVENT(kaizoku_move_trace_se)
        SET_VALUE(LW(0), 20000)
        CALL_CHILD(kaizoku_move_trace)
        SET_VALUE(GF(10), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(GF(11), 1)
        SPAWN_EVENT(dai3_move_trace_se)
        SET_VALUE(LW(0), 15000)
        CALL_CHILD(dai3_move_trace)
        SET_VALUE(GF(11), 0)
        CALL_CHILD(dai3_kurukuru)
        SET_VALUE(GF(1), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_print, 0, STRING("stg5_muj_120"), 0, STRING("第三勢力幹部"))
        CALL(evt_msg_continue)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL_CHILD(iwapera_offscreen)
        CALL(evt_mapobj_get_position, STRING("S_iwa_before"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon, STRING("SFX_OFF5_SHIP_APPEAR1"), 0)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_BOSS_STG5_KORTESS1"))
        WAIT_MS(3500)
        CALL(evt_cam3d_evt_set, 0, 2650, 2025, 0, 250, 225, 500, 11)
        CALL_CHILD(iwapera_offscreen_end)
        WAIT_MS(4000)
        SPAWN_EVENT_GET_ID(PTR(cam_dai3_vs_kaizoku), LW(10))
#if VERSION == VERSION_EU
        CALL(evt_sub_get_framerate, LW(0))
        IF_INT_EQUAL(LW(0), 60)
            WAIT_MS(9500)
            DELETE_EVENT(LW(10))
            CALL(evt_cam3d_evt_set, -205, 528, 672, -205, 108, -278, 0, 11)
            WAIT_MS(1400)
            CALL(evt_cam3d_evt_set, -700, 290, 74, -374, 80, -316, 0, 11)
            WAIT_MS(200)
        ELSE
            WAIT_MS(11400)
            DELETE_EVENT(LW(10))
            CALL(evt_cam3d_evt_set, -205, 528, 672, -205, 108, -278, 0, 11)
            WAIT_MS(1680)
            CALL(evt_cam3d_evt_set, -700, 290, 74, -374, 80, -316, 0, 11)
            WAIT_MS(240)
        END_IF
#else
        WAIT_MS(9500)
        DELETE_EVENT(LW(10))
        CALL(evt_cam3d_evt_set, -205, 528, 672, -205, 108, -278, 0, 11)
        WAIT_MS(1400)
        CALL(evt_cam3d_evt_set, -700, 290, 74, -374, 80, -316, 0, 11)
        WAIT_MS(200)
#endif
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    WAIT_WHILE(GF(0))
    WAIT_WHILE(GF(1))
    DELETE_EVENT(LW(10))
    DELETE_EVENT(LW(11))
    DELETE_EVENT(LW(12))
    DELETE_EVENT(LW(13))
    DELETE_EVENT(LW(14))
    DELETE_EVENT(LW(15))
    CALL(evt_msg_print, 0, STRING("stg5_muj_121"), 0, STRING("第三勢力幹部"))
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_party_cont_onoff, 0, 1)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, -120, 320, 259, -163, 115, -249, 0, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_122"), 0, STRING("コルテス"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -436, 595, 725, -226, 120, -460, 500, 11)
    WAIT_MS(1000)
    CALL(tobikakaru_init)
    SPAWN_EVENT_GET_ID(PTR(tobikakari_kemuri), LW(15))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_ELM_VS_3RD1"), -226, 120, -460, LW(9))
    CALL(evt_snd_sfx_dist, LW(9), 30)
    WAIT_MS(2500)
    CALL(evt_cam3d_evt_set, -369, 245, -37, 0, 67, -303, 0, 11)
    CALL(evt_npc_flag_onoff, 1, STRING("コルテス"), NPC_FLAG_HIDDEN)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_123"), 0, STRING("マルコ"))
    CALL(evt_cam3d_evt_set, -436, 595, 725, -226, 120, -460, 0, 11)
    CALL(evt_npc_flag_onoff, 0, STRING("コルテス"), NPC_FLAG_HIDDEN)
    WAIT_MS(500)
#if VERSION <= VERSION_DEMO_US
    BEGIN_INLINE_EVENT
#else
    CALL(evt_party_run, 0)
    BEGIN_INLINE_EVENT_GET_ID(LW(3))
#endif
        CALL(evt_party_set_dir, 0, 270, 200)
        CALL(evt_party_jump_pos, 0, -405, 60, -237, 1000, 0, 80)
    END_INLINE_EVENT
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FLD_JUMP3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, -430, 60, -212, 1000, 0, 80)
    CALL(evt_snd_sfxoff, LW(9))
#if VERSION >= VERSION_JP
    LOOP(0)
        IS_EVENT_RUNNING(LW(3), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#endif
    CALL(evt_npc_release_filednpc, 1)
    CALL(evt_npc_set_battle_info, STRING("第三勢力幹部"), 5)
    CALL(evt_npc_battle_start, STRING("第三勢力幹部"))
    CALL(evt_npc_wait_battle_end)
    DELETE_EVENT(LW(15))
    CALL(tobikakaru_end)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_42_PIRATES_VS_X_NAUTS)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(dai3_beat_back)
    RETURN
EVT_END()

EVT_BEGIN(senin_kansei)
    LOOP(0)
        WAIT_MS(400)
        SET_VALUE(LW(0), GW(5))
        SET_VALUE(LW(2), GW(6))
        BEGIN_INLINE_EVENT
            ADD(LW(0), -30)
            CALL(evt_msg_toge, 2, LW(0), 200, LW(2))
            CALL(evt_msg_print, 0, STRING("stg5_muj_127"), 0, 0)
        END_INLINE_EVENT
        WAIT_MS(300)
        BEGIN_INLINE_EVENT
            ADD(LW(0), -32)
            CALL(evt_msg_toge, 2, LW(0), 100, LW(2))
            CALL(evt_msg_print, 0, STRING("stg5_muj_128"), 0, 0)
        END_INLINE_EVENT
        WAIT_MS(200)
        BEGIN_INLINE_EVENT
            ADD(LW(0), 100)
            CALL(evt_msg_toge, 2, LW(0), 155, LW(2))
            CALL(evt_msg_print, 0, STRING("stg5_muj_129"), 0, 0)
        END_INLINE_EVENT
        WAIT_MS(300)
        BEGIN_INLINE_EVENT
            ADD(LW(0), -40)
            CALL(evt_msg_toge, 2, LW(0), 150, LW(2))
            CALL(evt_msg_print, 0, STRING("stg5_muj_130"), 0, 0)
        END_INLINE_EVENT
        WAIT_MS(400)
        BEGIN_INLINE_EVENT
            ADD(LW(0), 80)
            CALL(evt_msg_toge, 2, LW(0), 107, LW(2))
            CALL(evt_msg_print, 0, STRING("stg5_muj_131"), 0, 0)
        END_INLINE_EVENT
        WAIT_MS(200)
        BEGIN_INLINE_EVENT
            ADD(LW(0), 65)
            CALL(evt_msg_toge, 2, LW(0), 205, LW(2))
            CALL(evt_msg_print, 0, STRING("stg5_muj_132"), 0, 0)
        END_INLINE_EVENT
    END_LOOP
    RETURN
EVT_END()

f32 dai3_taisan_spline_dt00[] = {
    -416.0f, 0.0f, -334.0f, -413.67612f, 0.0f, -365.46518f, -411.63168f, 0.0f,
    -404.80673f,
};

f32 dai3_taisan_spline_dt01[] = {
    -416.0f, 0.0f, -334.0f, -839.007f, 0.0f, -339.86542f, -1018.9882f, 0.0f,
    -346.33777f,
};

EVT_BEGIN(nameraka_rotate)
    LOOP(0)
        IF_FLOAT_NOT_EQUAL(GW(1), GW(7))
            IF_FLOAT_GREATER_OR_EQUAL(GW(1), GW(7))
                SET_FLOAT_VALUE(LW(0), GW(1))
                SUBTRACT_FLOAT(LW(0), FLOAT(1.0f))
                SET_FLOAT_VALUE(GW(1), LW(0))
                IF_FLOAT_LESS_OR_EQUAL(GW(1), GW(7))
                    SET_FLOAT_VALUE(GW(1), GW(7))
                END_IF
            ELSE
                SET_FLOAT_VALUE(LW(0), GW(1))
                ADD_FLOAT(LW(0), FLOAT(1.0f))
                SET_FLOAT_VALUE(GW(1), LW(0))
                IF_FLOAT_GREATER_OR_EQUAL(GW(1), GW(7))
                    SET_FLOAT_VALUE(GW(1), GW(7))
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dai3_taisan_move_trace00)
    SET_FLOAT_VALUE(LW(5), GW(2))
    SET_FLOAT_VALUE(LW(6), GW(3))
    CALL(evt_sub_spline_init, 1, 0, PTR(dai3_taisan_spline_dt00), 3, 0, LW(0))
    LOOP(0)
        CALL(evt_sub_spline_get_value, LW(0), LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(GW(2), LW(0))
        SET_FLOAT_VALUE(GW(3), LW(2))
        SET_VALUE(LF(0), 1)
        IF_FLOAT_EQUAL(GW(2), LW(5))
            IF_FLOAT_EQUAL(GW(3), LW(6))
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            CALL(ship_rotate_rev, LW(5), LW(6), GW(2), GW(3), GW(7))
        END_IF
        SET_FLOAT_VALUE(LW(5), GW(2))
        SET_FLOAT_VALUE(LW(6), GW(3))
        IF_INT_EQUAL(LW(3), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dai3_taisan_move_trace01)
    SET_FLOAT_VALUE(LW(5), GW(2))
    SET_FLOAT_VALUE(LW(6), GW(3))
    CALL(evt_sub_spline_init, 1, 0, PTR(dai3_taisan_spline_dt01), 3, 0, LW(0))
    LOOP(0)
        CALL(evt_sub_spline_get_value, LW(0), LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(GW(2), LW(0))
        SET_FLOAT_VALUE(GW(3), LW(2))
        SET_VALUE(LF(0), 1)
        IF_FLOAT_EQUAL(GW(2), LW(5))
            IF_FLOAT_EQUAL(GW(3), LW(6))
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            CALL(ship_rotate, LW(5), LW(6), GW(2), GW(3), GW(7))
        END_IF
        SET_FLOAT_VALUE(LW(5), GW(2))
        SET_FLOAT_VALUE(LW(6), GW(3))
        IF_INT_EQUAL(LW(3), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dai3_beat_back)
    CALL(evt_mario_key_onoff, 0)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_party_cont_onoff, 0, 1)
#endif
    CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
#else
    CALL(evt_party_stop, 0)
    CALL(evt_party_set_pos, 0, -71, 45, -240)
#endif
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), -448, 60, -236)
    CALL(evt_cam3d_evt_set, -436, 595, 725, -226, 120, -460, 0, 11)
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SET_VALUE(GW(2), -416)
    SET_VALUE(GW(3), -334)
    SET_FLOAT_VALUE(GW(4), FLOAT(0.0f))
    SET_VALUE(GW(5), -78)
    SET_VALUE(GW(6), -267)
    SPAWN_EVENT_GET_ID(PTR(dai3_move_every), LW(10))
    SPAWN_EVENT_GET_ID(PTR(kaizoku_move_every), LW(11))
    SPAWN_EVENT(dai3_butai_setup)
    SPAWN_EVENT(kaizoku_setup)
    WAIT_FRAMES(1)
    SPAWN_EVENT_GET_ID(PTR(dai3_butai_main), LW(12))
    SPAWN_EVENT_GET_ID(PTR(dai3_kanbu_main), LW(13))
    SPAWN_EVENT_GET_ID(PTR(kaizoku_main), LW(14))
    SPAWN_EVENT_GET_ID(PTR(mario_main2), LW(15))
    WAIT_FRAMES(2)
    SET_VALUE(GW(1), 273)
    SET_VALUE(GW(4), 215)
    IF_INT_EQUAL(LW(0), 0)
    ELSE
        CALL(evt_seq_wait, 2)
    END_IF
    SET_FLOAT_VALUE(GW(7), GW(1))
    SPAWN_EVENT_GET_ID(PTR(nameraka_rotate), LW(9))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_125"), 0, STRING("第三勢力幹部"))
    SET_VALUE(GF(11), 1)
    SPAWN_EVENT(dai3_move_trace_se)
    SET_VALUE(LW(0), 3500)
    SPAWN_EVENT(dai3_taisan_move_trace01)
    WAIT_MS(3500)
    SET_VALUE(GF(11), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_cam3d_evt_set, -141, 262, 147, -45, 43, -397, 500, 11)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print_party, STRING("stg5_muj_126"))
    SPAWN_EVENT_GET_ID(PTR(senin_kansei), LW(10))
    WAIT_MS(3000)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_43_X_NAUTS_RETREAT)
    DELETE_EVENT(LW(10))
    CALL(evt_fade_entry, FADE_OUT_SPOT_3D, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1500)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 24)
#if VERSION >= VERSION_US
    CALL_CHILD(evt_memcard_save_wrapper)
#else
    CALL_CHILD(evt_memcard_save)
#endif
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
    CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
    CALL(evt_bero_mapchange, STRING("aji_10"), STRING(""))
    RETURN
EVT_END()

s32 leave_island_suifupos[] = {
    565, 77, -606, 90, 574, 77, -612, 90,
    590, 77, -618, 90, 590, 77, -605, 90,
    592, 77, -585, 90, 607, 77, -584, 90,
    623, 77, -580, 90, 632, 77, -568, 90,
    655, 77, -564, 90, 655, 77, -577, 90,
    643, 77, -600, 90, 625, 77, -605, 90,
    632, 77, -622, 90, 648, 77, -627, 90,
    659, 77, -637, 90, 664, 77, -617, 90,
    646, 77, -554, 90, 612, 77, -615, 90,
    615, 77, -594, 90, 659, 77, -597, 90,
    613, 77, -636, 90, 634, 77, -651, 90,
    664, 77, -665, 90, 661, 77, -651, 90,
    639, 77, -584, 90, 684, 65, -567, 90,
    668, 65, -570, 90, 675, 65, -641, 90,
    678, 65, -583, 90, 681, 65, -597, 90,
    672, 65, -553, 90, 727, 40, -619, 90,
    693, 42, -640, 90, 688, 42, -626, 90,
    695, 42, -614, 90, 701, 42, -677, 90,
    701, 42, -665, 90, 725, 42, -665, 270,
    746, 42, -665, 270, 818, 42, -685, 270,
    695, 42, -654, 270, 710, 42, -606, 270,
    707, 42, -629, 270, 818, 42, -631, 270,
    714, 42, -644, 270, 732, 42, -648, 270,
    754, 42, -646, 270, 769, 42, -650, 270,
    784, 42, -648, 270, 807, 42, -648, 270,
    820, 42, -653, 270, 738, 42, -660, 270,
    793, 42, -661, 270, 784, 42, -695, 270,
    786, 42, -700, 270, 800, 42, -683, 270,
    746, 42, -690, 270, 777, 42, -674, 270,
    758, 42, -675, 270, 737, 42, -680, 270,
    720, 42, -681, 270, 770, 42, -691, 270,
    846, 115, -672, 270, 846, 115, -646, 270,
    861, 115, -646, 270, 869, 115, -647, 270,
    886, 115, -639, 270, 887, 115, -618, 270,
    898, 115, -649, 270, 907, 115, -631, 270,
    873, 115, -626, 270, 909, 115, -610, 270,
    909, 115, -599, 270, 874, 115, -582, 270,
    861, 115, -590, 270, 852, 115, -596, 270,
    852, 115, -632, 270, 843, 115, -631, 270,
    843, 115, -603, 270, 855, 115, -588, 270,
    852, 115, -578, 270, 866, 115, -561, 270,
    910, 115, -582, 270, 856, 115, -560, 270,
    856, 115, -544, 270, 848, 115, -541, 270,
    869, 115, -540, 270, 887, 115, -559, 270,
    892, 115, -544, 270, 903, 115, -548, 270,
    915, 115, -551, 270, 915, 115, -567, 270,
    899, 115, -572, 270, 884, 115, -582, 270,
    896, 115, -592, 270,
};

EVT_BEGIN(move_ship_se00)
    LOOP(5)
        WAIT_MS(2000)
        CALL(evt_mapobj_get_position, STRING("S_b"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_SHIP_KOL_MOVE1"), LW(0), LW(1), LW(2), 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(move_ship_se01)
    LOOP(7)
        WAIT_MS(1400)
        CALL(evt_mapobj_get_position, STRING("S_b"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_SHIP_KOL_MAST1"), LW(0), LW(1), LW(2), 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(option_ship_npc)
    SET_FLOAT_VALUE(LW(10), GW(0))
    SET_FLOAT_VALUE(LW(11), GW(1))
    LOOP(0)
        SET_FLOAT_VALUE(LW(4), GW(0))
        SUBTRACT_FLOAT(LW(4), LW(10))
        SET_FLOAT_VALUE(LW(5), GW(1))
        SUBTRACT_FLOAT(LW(5), LW(11))
        SET_VALUE(LW(0), 10)
        LOOP(95)
            CALL(evt_nannpc_get_position, LW(0), LW(1), LW(2), LW(3))
            ADD_FLOAT(LW(1), LW(4))
            ADD_FLOAT(LW(2), LW(5))
            CALL(evt_nannpc_set_position, LW(0), LW(1), LW(2), LW(3))
            ADD(LW(0), 1)
        END_LOOP
        CALL(evt_npc_get_position, STRING("水夫A"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("水夫A"), LW(1), LW(2), LW(3))
        CALL(evt_npc_get_position, STRING("水夫ボム兵"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("水夫ボム兵"), LW(1), LW(2), LW(3))
        CALL(evt_npc_get_position, STRING("水夫C"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("水夫C"), LW(1), LW(2), LW(3))
        CALL(evt_npc_get_position, STRING("オドオド水夫"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("オドオド水夫"), LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(LW(10), GW(0))
        SET_FLOAT_VALUE(LW(11), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(option_ship_korutesu)
    SET_FLOAT_VALUE(LW(10), GW(0))
    SET_FLOAT_VALUE(LW(11), GW(1))
    LOOP(0)
        SET_FLOAT_VALUE(LW(4), GW(0))
        SUBTRACT_FLOAT(LW(4), LW(10))
        SET_FLOAT_VALUE(LW(5), GW(1))
        SUBTRACT_FLOAT(LW(5), LW(11))
        CALL(evt_npc_get_position, STRING("コルテス"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        CALL(evt_npc_set_position, STRING("コルテス"), LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(LW(10), GW(0))
        SET_FLOAT_VALUE(LW(11), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(option_ship_marco)
    SET_FLOAT_VALUE(LW(10), GW(0))
    SET_FLOAT_VALUE(LW(11), GW(1))
    LOOP(0)
        SET_FLOAT_VALUE(LW(4), GW(0))
        SUBTRACT_FLOAT(LW(4), LW(10))
        SET_FLOAT_VALUE(LW(5), GW(1))
        SUBTRACT_FLOAT(LW(5), LW(11))
        CALL(evt_npc_get_position, STRING("マルコ"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("マルコ"), LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(LW(10), GW(0))
        SET_FLOAT_VALUE(LW(11), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(option_ship_mario)
    SET_FLOAT_VALUE(LW(10), GW(0))
    SET_FLOAT_VALUE(LW(11), GW(1))
    LOOP(0)
        SET_FLOAT_VALUE(LW(4), GW(0))
        SUBTRACT_FLOAT(LW(4), LW(10))
        SET_FLOAT_VALUE(LW(5), GW(1))
        SUBTRACT_FLOAT(LW(5), LW(11))
        CALL(evt_mario_get_pos, 0, LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_mario_set_pos, LW(1), LW(2), LW(3))
        CALL(evt_party_get_pos, 0, LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_party_set_pos, 0, LW(1), LW(2), LW(3))
        CALL(evt_party_get_pos, 1, LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_party_set_pos, 1, LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(LW(10), GW(0))
        SET_FLOAT_VALUE(LW(11), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(option_ship_main)
    LOOP(0)
        SET_VALUE(LW(0), GW(0))
        SET_VALUE(LW(1), GW(1))
        CALL(evt_mapobj_trans, 1, STRING("S_b"), LW(0), LW(1), -605)
        CALL(evt_mapobj_rotate, 1, STRING("S_b"), 0, 180, 0)
        CALL(evt_hit_bind_update, STRING("A_b"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(leave_island)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("コルテス"), 640, 125, -603)
    CALL(evt_npc_set_ry, STRING("コルテス"), 90)
    CALL(evt_npc_set_position, STRING("オドオド水夫"), 706, 40, -566)
    CALL(evt_npc_set_ry, STRING("オドオド水夫"), 90)
    CALL(evt_npc_set_position, STRING("水夫A"), 720, 40, -589)
    CALL(evt_npc_set_ry, STRING("水夫A"), 90)
    CALL(evt_npc_set_position, STRING("水夫C"), 779, 40, -548)
    CALL(evt_npc_set_ry, STRING("水夫C"), 270)
    CALL(evt_npc_set_position, STRING("水夫ボム兵"), 751, 40, -590)
    CALL(evt_npc_set_ry, STRING("水夫ボム兵"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("コルテス"), NPC_FLAG_USED)
    CALL(evt_npc_flag_onoff, 1, STRING("オドオド水夫"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_TALK_ANIM | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("水夫A"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_TALK_ANIM | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("水夫C"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_TALK_ANIM | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("水夫ボム兵"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_TALK_ANIM | NPC_FLAG_INTANGIBLE)
    SET_VALUE(LW(0), 10)
    SET_INT_READ_ADDR(PTR(leave_island_suifupos))
    LOOP(95)
        READ_INT3(LW(1), LW(2), LW(3))
        READ_INT(LW(4))
        ADD(LW(2), 2)
        CALL(evt_nannpc_set_position, LW(0), LW(1), LW(2), LW(3))
        CALL(evt_nannpc_set_dir, LW(0), LW(4))
        ADD(LW(0), 1)
    END_LOOP
    CALL(evt_npc_set_position, STRING("ガラの悪い水夫"), 920, 25, -423)
    CALL(evt_npc_set_ry, STRING("ガラの悪い水夫"), 270)
    CALL(evt_npc_set_position, STRING("モニー"), 950, 25, -383)
    CALL(evt_npc_set_ry, STRING("モニー"), 270)
    CALL(evt_npc_set_position, STRING("ピートン"), 980, 25, -423)
    CALL(evt_npc_set_ry, STRING("ピートン"), 270)
    CALL(evt_npc_set_position, STRING("水夫D"), 1010, 25, -383)
    CALL(evt_npc_set_ry, STRING("水夫D"), 270)
    CALL(evt_npc_set_position, STRING("ボロ水夫A"), 1040, 25, -423)
    CALL(evt_npc_set_ry, STRING("ボロ水夫A"), 270)
    CALL(evt_npc_set_position, STRING("ボロ水夫B"), 1060, 25, -383)
    CALL(evt_npc_set_ry, STRING("ボロ水夫B"), 270)
    CALL(evt_npc_set_position, STRING("店員"), 1090, 35, -423)
    CALL(evt_npc_set_ry, STRING("店員"), 270)
    CALL(evt_npc_set_position, STRING("宿店員"), 1110, 35, -383)
    CALL(evt_npc_set_ry, STRING("宿店員"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("ボロ水夫A"), NPC_FLAG_USED)
    CALL(evt_npc_flag_onoff, 1, STRING("ボロ水夫B"), NPC_FLAG_USED)
    CALL(evt_npc_flag_onoff, 1, STRING("店員"), NPC_FLAG_USED)
    CALL(evt_npc_flag_onoff, 1, STRING("宿店員"), NPC_FLAG_USED)
    SET_VALUE(GW(0), 770)
    SET_VALUE(GW(1), 0)
    SET_RAW_VALUE(LW(0), GW(1))
    SET_FLOAT_VALUE(LW(1), FLOAT(1.5f))
    SPAWN_EVENT(option_ship_npc)
    SPAWN_EVENT(option_ship_korutesu)
    SPAWN_EVENT(option_ship_main)
    SPAWN_EVENT(muj_ship_puka)
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_mario_set_pos, 800, 25, -415)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_pos, 0, 835, 25, -425)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_npc_set_position, STRING("マルコ"), 750, 25, -415)
    CALL(evt_npc_set_ry, STRING("マルコ"), 270)
    CALL(evt_cam3d_evt_set, 750, 438, 999, 750, 225, -233, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, 660, 267, -170, 660, 190, -603, 0, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_133"), 0, STRING("コルテス"))
    CALL(evt_cam3d_evt_set, 775, 133, -36, 775, 45, -550, 0, 11)
    WAIT_MS(500)
    CALL(evt_npc_set_ry, STRING("マルコ"), 90)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg5_muj_134"), 0, STRING("マルコ"))
    CALL(evt_cam3d_evt_set, 750, 151, -218, 750, 55, -759, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_135"), 0, STRING("水夫A"))
    CALL(evt_cam3d_evt_set, 787, 151, -218, 787, 55, -759, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_136"), 0, STRING("水夫C"))
    CALL(evt_cam3d_evt_set, 775, 133, -36, 775, 45, -550, 0, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_137"), 0, STRING("マルコ"))
    CALL(evt_npc_jump_position_nohit, STRING("マルコ"), 745, 40, -555, 500, 30)
    CALL(evt_npc_set_ry, STRING("マルコ"), 90)
    SPAWN_EVENT(option_ship_marco)
    CALL(evt_msg_print, 0, STRING("stg5_muj_138"), 0, STRING("モニー"))
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 950, 133, -36, 950, 45, -550, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_139"), 0, STRING("モニー"))
    CALL(evt_msg_print, 0, STRING("stg5_muj_140"), 0, STRING("ピートン"))
    CALL(evt_npc_get_position, STRING("ガラの悪い水夫"), LW(0), LW(1), LW(2))
    ADD(LW(0), -10)
    CALL(evt_npc_move_position, STRING("ガラの悪い水夫"), LW(0), LW(2), 0, FLOAT(60.0f), 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_141"), 0, STRING("ガラの悪い水夫"))
    CALL(evt_cam3d_evt_set, 820, 133, -36, 820, 45, -550, 500, 11)
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg5_muj_142"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 200)
        CALL(evt_party_jump_pos, 0, 765, 40, -535, 500, 0, -1000)
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(200)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FLD_JUMP5"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, 730, 40, -535, 500, 0, -1000)
    CALL(evt_mario_set_dir, 90, 200, 0)
    SPAWN_EVENT(option_ship_mario)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 640, 270, -110, 640, 185, -603, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_143"), 0, STRING("コルテス"))
    CALL(evt_npc_set_ry, STRING("コルテス"), 270)
    SET_VALUE(LW(0), 10)
    LOOP(95)
        CALL(evt_nannpc_get_position, LW(0), LW(10), LW(11), LW(12))
        IF_FLOAT_GREATER_OR_EQUAL(LW(11), 60)
            IF_FLOAT_LESS_OR_EQUAL(LW(11), 80)
                BEGIN_INLINE_EVENT
                    CALL(evt_sub_random, 300, LW(13))
                    ADD(LW(13), 100)
                    WAIT_MS(LW(13))
                    CALL(evt_nannpc_set_dir, LW(0), 270)
                END_INLINE_EVENT
            END_IF
        END_IF
        ADD(LW(0), 1)
    END_LOOP
    CALL(evt_cam3d_evt_set, 770, 317, 411, 770, 149, -559, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_mario_cont_onoff, 0)
    SPAWN_EVENT(move_ship_se00)
    SPAWN_EVENT(move_ship_se01)
    CALL(evt_mapobj_get_position, STRING("S_b"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_WAVE1"), LW(0), LW(1), LW(2), LW(9))
    CALL(evt_snd_sfxon, STRING("SFX_STG5_SHIP_STARTING1_2"), 0)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG5_GHOST_SHIP1"))
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, 944, 164, -240, 33, 155, -611, 13000, 11)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 1, 770, -770, 18000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(GW(0), LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(17000)
    CALL(evt_snd_sfxoff, LW(9))
    CALL(evt_nannpcwork_flag_onoff, 0, 1)
    SET_VALUE(LW(0), 10)
    LOOP(95)
        CALL(evt_nannpc_ppflag_onoff, LW(0), 0, 4)
        ADD(LW(0), 1)
    END_LOOP
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
    CALL(evt_eff_softdelete, STRING("sunlight"))
    SET_VALUE(LW(10), 600)
    SPAWN_EVENT(back_dark)
    CALL_CHILD(suifu_dark)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_muj_144"), 0, 0)
    WAIT_MS(2000)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_58_FAIR_WINDS)
    CALL(evt_bero_mapchange, STRING("gor_00"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(muj_gor_ship_sub)
    LOOP(0)
        SET_FLOAT_VALUE(LW(0), GW(0))
        SET_FLOAT_VALUE(LW(1), GW(1))
        SET_FLOAT_VALUE(LW(2), GW(2))
        CALL(evt_mapobj_trans, 1, STRING("S_b"), LW(0), LW(1), -605)
        CALL(evt_mapobj_rotate, 1, STRING("S_b"), 0, LW(2), 0)
        CALL(evt_hit_bind_update, STRING("A_b"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(muj_gor_ship)
    CALL(evt_npc_set_position, STRING("コルテス"), 655, 40, -542)
    CALL(evt_npc_set_ry, STRING("コルテス"), 90)
    CALL(alpha_init_func)
    CALL(evt_map_set_tevcallback, 1, PTR(alpha_tev))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("S_mizu_06"), MAPOBJ_TEV_CALLBACK(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_mizu_06"), MAPOBJ_FLAG_DISPLAY_LIST)
    CALL(alpha_set_func, 0)
    SET_FLOAT_VALUE(GW(0), FLOAT(685.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SET_VALUE(GW(2), 0)
    SPAWN_EVENT(muj_gor_ship_sub)
    SET_RAW_VALUE(LW(0), GW(1))
    SET_FLOAT_VALUE(LW(1), FLOAT(1.5f))
    SPAWN_EVENT_GET_ID(PTR(muj_ship_puka), GW(10))
    RETURN
EVT_END()

static EVT_BEGIN(ship_pera)
    CALL(evt_img_entry, STRING("capture_img"))
    CALL(evt_img_set_paper, STRING("capture_img"), STRING("OFF_d_kaiten"))
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_offscreen_set_texture_fmt, STRING("offscreen"), 6, 6)
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_b"), STRING("offscreen"))
    CALL(evt_img_alloc_capture, STRING("capture_img"), 0, STRING("offscreen"), 0, 0, 0, 608, 480)
    CALL(evt_img_alloc_capture, STRING("capture_img"), 1, STRING("offscreen"), 0, 0, 0, 608, 480)
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_set_virtual_point, STRING("capture_img"), 685, 0, -605)
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("Z_1"))
    CALL(evt_img_onoff, STRING("capture_img"), 1)
    CALL(evt_snd_sfxon, STRING("SFX_OFF_SHIP_REVERSE1"), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_b"), MAPOBJ_FLAG_HIDE)
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_1"))
    CALL(evt_img_wait_animend, STRING("capture_img"))
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_b"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(GW(2), 180)
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_b"))
    CALL(evt_img_free_capture, STRING("capture_img"), 0)
    CALL(evt_img_free_capture, STRING("capture_img"), 1)
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_release, STRING("capture_img"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_paper_delete, STRING("OFF_d_kaiten"))
    RETURN
EVT_END()

static USER_FUNC(scale_func) {
    f32 s = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    PartyEntry* party2 = partyGetPtr(1);

    mario->scale = (Vec){s, s, s};
    if (party != NULL) {
        party->scale = (Vec){s, s, s};
    }
    if (party2 != NULL) {
        party2->scale = (Vec){s, s, s};
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(muj_gor_ship_start)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG5_GHOST_SHIP1"))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 0, 100, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(scale_func, LW(0))
            CALL(evt_npc_set_scale, STRING("コルテス"), LW(0), LW(0), LW(0))
            CALL(evt_npc_set_scale, STRING("モニー"), LW(0), LW(0), LW(0))
            CALL(evt_npc_set_scale, STRING("ピートン"), LW(0), LW(0), LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mario_cont_onoff, 0)
        CALL(evt_party_cont_onoff, 0, 0)
        CALL(evt_party_cont_onoff, 1, 0)
        CALL(evt_mario_set_pos, 0, -1000, 0)
        CALL(evt_party_set_pos, 0, 0, -1000, 0)
        CALL(evt_party_set_pos, 1, 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 685, 278, 455, 685, 158, -537, 500, 11)
    WAIT_MS(1000)
    DELETE_EVENT(GW(10))
    SET_VALUE(GF(10), 1)
    CALL(evt_npc_set_position, STRING("船ダミー"), 0, GW(1), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL_CHILD(ship_pera)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_get_position, STRING("船ダミー"), LW(0), LW(1), LW(2))
            SET_FLOAT_VALUE(GW(1), LW(1))
            IF_INT_EQUAL(GF(10), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mapobj_get_position, STRING("S_b"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG0_SHIP_JUMP1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_jump_position_nohit, STRING("船ダミー"), 0, GW(1), 0, 1800, 150)
    CALL(evt_mapobj_get_position, STRING("S_b"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG0_SHIP_LANDING1"), LW(0), LW(1), LW(2), 0)
    SET_VALUE(GF(10), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_06"), MAPOBJ_FLAG_HIDE)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 0, 0, 255, 2000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(alpha_set_func, LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    SET_RAW_VALUE(LW(0), GW(1))
    SET_FLOAT_VALUE(LW(1), FLOAT(1.5f))
    SPAWN_EVENT_GET_ID(PTR(muj_ship_puka), GW(10))
    CALL(evt_snd_sfxon, STRING("SFX_STG5_SHIP_STARTING1_4"), 0)
    SET_FLOAT_VALUE(LW(0), GW(0))
    SET_FLOAT_VALUE(LW(1), GW(0))
    ADD_FLOAT(LW(1), FLOAT(-800.0f))
    CALL(evt_sub_intpl_msec_init, 1, LW(0), LW(1), 10000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        SET_FLOAT_VALUE(GW(0), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_bero_mapchange, STRING("muj_20"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(into_muj_ship)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    ADD_FLOAT(GW(0), FLOAT(-600.0f))
    SET_FLOAT_VALUE(LW(10), FLOAT(-600.0f))
    SET_FLOAT_VALUE(LW(0), FLOAT(730.0f))
    ADD_FLOAT(LW(0), LW(10))
    SET_FLOAT_VALUE(LW(1), FLOAT(705.0f))
    ADD_FLOAT(LW(1), LW(10))
    SET_FLOAT_VALUE(LW(2), FLOAT(710.0f))
    ADD_FLOAT(LW(2), LW(10))
    SET_FLOAT_VALUE(LW(3), FLOAT(655.0f))
    ADD_FLOAT(LW(3), LW(10))
    CALL(evt_mario_set_pos, LW(0), 40, -550)
    CALL(evt_party_set_pos, 0, LW(1), 40, -570)
    CALL(evt_party_set_pos, 1, LW(2), 40, -590)
    CALL(evt_npc_set_position, STRING("コルテス"), LW(3), 40, -542)
    CALL(evt_cam3d_evt_set, 682, 199, 75, 682, 78, -614, 0, 11)
    SPAWN_EVENT_GET_ID(PTR(option_ship_korutesu), LW(8))
    SPAWN_EVENT_GET_ID(PTR(option_ship_mario), LW(9))
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_sfxon, STRING("SFX_STG5_SHIP_ARRIVAL1_4"), 0)
    SET_FLOAT_VALUE(LW(0), GW(0))
    SET_FLOAT_VALUE(LW(1), GW(0))
    ADD_FLOAT(LW(1), FLOAT(600.0f))
    CALL(evt_sub_intpl_msec_init, 11, LW(0), LW(1), 6000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        SET_FLOAT_VALUE(GW(0), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_party_cont_onoff, 0, 1)
    CALL(evt_party_cont_onoff, 1, 1)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    DELETE_EVENT(LW(8))
    DELETE_EVENT(LW(9))
    CALL(evt_cam3d_evt_off, 500, 11)
#if VERSION >= VERSION_JP
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
#endif
    CALL(evt_mario_key_onoff, 1)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_62_AN_ILL_DON_PIANTA)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_63_KEELHAUL_ANYTIME)
    END_IF
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG5_MUJ1"))
    RETURN
EVT_END()

EVT_BEGIN(mony_peton_boarding_sub)
    SET_FLOAT_VALUE(LW(10), GW(0))
    SET_FLOAT_VALUE(LW(11), GW(1))
    LOOP(0)
        SET_FLOAT_VALUE(LW(4), GW(0))
        SUBTRACT_FLOAT(LW(4), LW(10))
        SET_FLOAT_VALUE(LW(5), GW(1))
        SUBTRACT_FLOAT(LW(5), LW(11))
        CALL(evt_npc_get_position, STRING("モニー"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("モニー"), LW(1), LW(2), LW(3))
        CALL(evt_npc_get_position, STRING("ピートン"), LW(1), LW(2), LW(3))
        ADD_FLOAT(LW(1), LW(4))
        ADD_FLOAT(LW(2), LW(5))
        CALL(evt_npc_set_position, STRING("ピートン"), LW(1), LW(2), LW(3))
        SET_FLOAT_VALUE(LW(10), GW(0))
        SET_FLOAT_VALUE(LW(11), GW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mony_peton_boarding)
    SET_VALUE(LW(0), 0)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_64_01_WEDDING_RING_DELIVERY)
        SET_VALUE(LW(0), 1)
    END_IF
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_64_02_F_AND_F_SAIL_OFF)
        SET_VALUE(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_npc_set_position, STRING("モニー"), 710, 40, -590)
    CALL(evt_npc_set_ry, STRING("モニー"), 90)
    CALL(evt_npc_set_position, STRING("ピートン"), 745, 40, -575)
    CALL(evt_npc_set_ry, STRING("ピートン"), 90)
    SPAWN_EVENT(mony_peton_boarding_sub)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_64_02_F_AND_F_SAIL_OFF)
        RETURN
    END_IF
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_mario_get_name_hitobj_ride, LW(10))
        IF_INT_LESS_OR_EQUAL(LW(0), 790)
            IF_STR_EQUAL(LW(10), STRING("A_hasi_hon"))
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_cam3d_evt_set, 727, 170, -204, 727, 127, -415, 500, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg5_muj_145"), 0, STRING("ピートン"))
    CALL(evt_msg_print, 0, STRING("stg5_muj_146"), 0, STRING("モニー"))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_64_02_F_AND_F_SAIL_OFF)
    RETURN
EVT_END()

static HitDamageReturn hitDmgRetPoints[] = {
    {"A_yuka01", {1083.0f, 35.0f, -738.0f}},
    {"A_yuka06", {582.0f, 35.0f, -1173.0f}},
    {"A_yuka03", {1083.0f, 35.0f, -738.0f}},
    {"A_yuka04", {1083.0f, 35.0f, -738.0f}},
    {"A_yuka02", {1240.0f, 14.0f, 40.0f}},
    {"A_yuka05", {1240.0f, 14.0f, 40.0f}},
    {"A_hasi_hon", {1048.0f, 24.0f, -423.0f}},
    {0},
};

EVT_BEGIN(muj_00_init_evt)
    BEGIN_INLINE_EVENT
        CALL(evt_light_bind_mapobj, STRING("pointLight1"), STRING("S_b"), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_light_bind_mapobj, STRING("pointLight2"), STRING("S_b"), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_light_bind_mapobj, STRING("pointLight3"), STRING("S_b"), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_light_bind_mapobj, STRING("pointLight4"), STRING("S_b"), 0)
    END_INLINE_EVENT
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_58_FAIR_WINDS)
        IF_INT_EQUAL(GSWF(GSWF_GOR00_SAIL_TO_KEELHAUL), 1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG5_GHOST_SHIP1"))
        ELSE
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG5_MUJ1"))
        END_IF
    ELSE
        IF_INT_NOT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_10_HAUNTED)
            IF_INT_NOT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_49_BOWSER_TWILIGHT_TOWN_2)
                IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_42_PIRATES_VS_X_NAUTS)
                    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_BOSS_STG5_KORTESS1"))
                ELSE
                    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG5_MUJ1"))
                END_IF
            END_IF
        END_IF
    END_IF
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG5_MUJ2"))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_npc_set_tribe, STRING("モニー"), STRING("モニー（指輪）"))
    CALL(evt_npc_set_tribe, STRING("ピートン"), STRING("ピートン（指輪）"))
    CALL(evt_npc_sound_data_set, STRING("マルコ"), STRING("SFX_STG5_MARCO_MOVE1L"), STRING("SFX_STG5_MARCO_MOVE1R"), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG8_00_START)
        CALL_CHILD(kiza_entry)
    END_IF
    CALL_CHILD(koburon_evt)
    CALL(evt_npc_entry, STRING("船ダミー"), STRING("c_suifu_b"))
    CALL(evt_npc_flag_onoff, 1, STRING("船ダミー"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_HIDDEN | NPC_FLAG_INTANGIBLE)
    CALL(evt_eff64, STRING("sunlight"), STRING("sunlight_n64"), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 1375, 35, -430, STRING("S_ground"), 125, GSWF(GSWF_MUJ00_STAR_PIECE_PANEL))
    CALL(evt_paper_entry, STRING("OFF_d_yabu"))
    CALL(evt_paper_entry, STRING("OFF_d_kaiten"))
    CALL(evt_map_playanim, STRING("S_mizu"), 1, 0)
    CALL(evt_map_playanim, STRING("fune_c_01"), 1, 0)
    CALL(evt_map_playanim, STRING("fune_c_02"), 1, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_b"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_b"), 1, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_c"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_c"), 1, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hasi"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_01"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_04"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_hasi1"), 1, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_before"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_after"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_s011"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_ana_after"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_ana_before"), MAPOBJ_FLAG_HIDE)
    IF_INT_LESS_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_35_ESCAPE_ROUTE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ana_before"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_iwa_s011"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ana_after"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_iwa_09"), 1, 0)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_iwa_before"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_iwa_after"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_40_TRUE_IDENTITY)
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG5_41_RETURN_TO_THE_GROTTO)
            SPAWN_EVENT_GET_ID(PTR(dai3_shurai_after), GW(8))
        END_IF
    END_IF
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(evt_gazigazi_entry)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG5_10_HAUNTED)
        SPAWN_EVENT(mujinto_hyochaku)
        CASE_EQUAL(STORY_STG5_36_HOLE_IN_THE_WALL)
        CALL_CHILD(nannpc_mode_setup)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_c"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_c"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_c"), STRING("S_c"))
        SPAWN_EVENT(dai3_shurai)
        SPAWN_EVENT(suifu_random_sub)
        CASE_EQUAL(STORY_STG5_40_TRUE_IDENTITY)
        CALL_CHILD(nannpc_mode_setup)
        SPAWN_EVENT(suifu_random_sub)
        CASE_EQUAL(STORY_STG5_41_01_ALL_ABOARD)
        CALL_CHILD(nannpc_mode_setup)
        CALL_CHILD(mario_main_init)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_b"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_b"), STRING("S_b"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_c"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_c"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_c"), STRING("S_c"))
        SPAWN_EVENT(kaizoku_vs_dai3)
        CASE_EQUAL(STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CALL_CHILD(nannpc_mode_setup)
        CALL_CHILD(mario_main_init)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_b"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_b"), STRING("S_b"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_c"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_c"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_c"), STRING("S_c"))
        SET_VALUE(LW(0), 1)
        SPAWN_EVENT(dai3_beat_back)
        CASE_EQUAL(STORY_STG5_49_BOWSER_TWILIGHT_TOWN_2)
        CALL(evt_mario_get_party, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
#if VERSION >= VERSION_US
        END_IF
        CALL(evt_pouch_mario_recovery)
        CALL(evt_pouch_all_party_recovery)
        CALL(N_evt_sub_status_gauge_force_update)
#else
            CALL(evt_pouch_mario_recovery)
            CALL(evt_pouch_all_party_recovery)
        END_IF
#endif
        CALL_CHILD(nannpc_mode_setup)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_b"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_b"), STRING("S_b"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_hasi"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_01"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_04"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_00"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_hasi1"), 1, 1)
        SPAWN_EVENT(leave_island)
        CASE_GREATER_OR_EQUAL(STORY_STG5_58_FAIR_WINDS)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_b"), 1, 1)
        CALL(evt_hit_bind_mapobj, STRING("A_b"), STRING("S_b"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_hasi"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_01"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_04"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_00"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_hasi1"), 1, 1)
        CALL_CHILD(muj_gor_ship)
        IF_INT_EQUAL(GSWF(GSWF_GOR00_SAIL_TO_KEELHAUL), 1)
            SET_VALUE(GSWF(GSWF_GOR00_SAIL_TO_KEELHAUL), 0)
            SET_VALUE(GSWF(GSWF_SHIP_TRAVEL_ACTIVE), 1)
            SPAWN_EVENT(into_muj_ship)
        END_IF
        SPAWN_EVENT(mony_peton_boarding)
    END_SWITCH
    CALL(evt_hitobj_onoff, STRING("A_b_bero01"), 1, 0)
    RETURN
EVT_END()
