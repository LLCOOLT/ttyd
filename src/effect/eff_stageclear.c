#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "eff/eff_confetti.h"
#include "manager/evtmgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

double tan(double);
int rand(void);
extern s32 evt_cam_shake[];
EffectEntry* effMiniGameEntry(s32);

typedef struct StageClearWork {
    s32 type;     // 0x0
    Vec position; // 0xC
    f32 pad10;    // 0x10
    f32 scale;    // 0x14
    s32 delay;    // 0x18
    s32 frame;    // 0x1C
    u32 shake;    // 0x20
    s32 confetti; // 0x24
    s32 done;     // 0x28
} StageClearWork;

#define EV_W(e, off) (*(s32*)((u8*)(e) + (off)))

void effStageClearMain(EffectEntry* effect);
void effStageClearDisp(CameraId cameraId, EffectEntry* effect);

static s32 tex_us[] = {0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA0, 0x9E, 0xA3, 0xA0, 0xA4, 0xA5};
s32 tex_shadow_us[] = {0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAA, 0xA8, 0xAD, 0xAA, 0xAE, 0xAF};
static s32 evt_shake[] = {
    0x00020018, 0xFE363C81, 0x00000000, 0x0005005B, (s32)evt_cam_shake, 0x00000005, 0xF24A7A8A, 0xF24A7A8A, 0x00000032,
    0x00000020, 0x0005005B, (s32)evt_cam_shake, 0x00000005, 0xF24A7A94, 0xF24A7A94, 0x00000064, 0x00000021, 0x00000002,
    0x00000001,
};

static s32 tex_jp[] = {0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3};
s32 tex_shadow_jp[] = {0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB};
static s32* texid_tbl[] = {tex_jp, tex_shadow_jp, tex_us, tex_shadow_us};
static s32 niji_tbl[] = {0xAC, 0xB0};
s32 shake_dt[] = {2, 6, 2, 0, -1};
s32 shake_dt2[] = {12, 36, 12, 0, -1};
static u8 scale_dt[] = {0x00, 0x00, 0x16, 0x2E, 0x47, 0x5D, 0x6E, 0x78, 0x77, 0x6E, 0x66, 0x00};

EffectEntry* effStageClearEntry(s32 type, f32 x, f32 y, f32 z) {
    EffectEntry* effect;
    StageClearWork* work;
    StageClearWork* p;
    s32 i;
    s32 n = 9;

    if (type == 1 && gp->language != 0U) {
        return effMiniGameEntry(1);
    }
    effect = effEntry();
    if (gp->language != 0U) {
        n = 14;
    }
    if (type % 10 == 1) {
        n = 7;
    }
    effect->type = "StageClear\0";
    effect->count = n;
    work = __memAlloc(HEAP_EFFECT, effect->count * sizeof(StageClearWork));
    effect->userdata = work;
    effect->callback = (EffectCallback)effStageClearMain;
    work->type = type;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale = 1.0f;
    work->delay = 0;
    work->frame = 0;
    work->confetti = irand(5) + 1;
    work->done = 0;
    for (i = 1, p = work + 1; i < effect->count; i++, p++) {
        p->position.x = (f32)((i - 1) * 38 - (effect->count - 1) * 38 / 2 + 20);
        p->position.y = 0.0f;
        p->position.z = 0.0f;
        p->scale = 0.0f;
        p->delay = (s32)((f32)i * (0.2f * (f32)gp->framerate));
        p->frame = 0;
        p->shake = 0;
    }
    return effect;
}

void effStageClearMain(EffectEntry* effect) {
    StageClearWork* work = effect->userdata;
    Vec pos;
    Vec tmp;
    s32 i;
    s32 type;
    s32 n;
    StageClearWork* p;

    tmp = (Vec){0.0f, 0.0f, 0.0f};
    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    pos = tmp;
    type = work->type;
    n = 0;
    work->frame++;
    for (i = 1, work++; i < effect->count; i++, work++) {
        p = work;
        if (p->delay != 0) {
            p->delay--;
            if (p->delay == 0) {
                psndSFXOn((const char*)(type == 0 ? 0x29b : 0x82e));
            }
        } else {
            if ((u32)p->frame < 11) {
                p->scale = (f32)scale_dt[p->frame] / 100.0f;
            }
            p->frame++;
            if (p->scale > 0.9f) {
                if (p->shake == 0U) {
                    s32* d;
                    p->shake = (s32)evtEntry(evt_shake, 0, 0);
                    d = shake_dt;
                    if (i == effect->count - 1) {
                        d = shake_dt2;
                    }
                    EV_W(p->shake, 0x9C) = (s32)d;
                    EV_W(p->shake, 0xA0) = (effect->count - 1 - i) == 0;
                }
                n++;
            }
        }
    }
    if (n >= effect->count - 1) {
        ((StageClearWork*)effect->userdata)->done = 1;
    }
    if (type % 10 == 1 && n >= effect->count - 1 && gp->retraceCount % 60 == 0) {
        work = effect->userdata;
        if (work->confetti > 0) {
            f32 b;
            f32 a;
            a = pos.y + (f32)(100 - irand(200));
            b = pos.x + (f32)(200 - irand(400));
            effConfettiEntry(rand() % 3 + 24, 60, b, a, pos.z);
            psndSFXOn((const char*)0x82f);
            work->confetti--;
        }
    }
    if (type < 10) {
        dispEntry(CAMERA_3D, dispCalcZ(&pos), 2, (DispCallback)effStageClearDisp, effect);
    } else {
        dispEntry((CameraId)5, dispCalcZ(&pos), 8, (DispCallback)effStageClearDisp, effect);
    }
}

void effStageClearDisp(CameraId cameraId, EffectEntry* effect) {
    StageClearWork* work = effect->userdata;
    CameraEntry* cam;
    f32 scale;
    f32 size, half, dx, dy;
    StageClearWork* p;
    s32 i;
    s32 s;
    s32 frame;
    s32 type;
    Mtx m154;
    Mtx m124;
    Mtx mf4;
    Mtx mc4;
    Mtx m94;
    GXTexObj tex;
    f32 proj[7];
    f32 vp[6];
    Vec eye;
    Vec up;
    Vec target;
    Vec eyeInit;

    camGetPtr(cameraId);
    scale = 0.9f * (1.7f * work->scale);
    frame = work->frame;
    type = work->type;
    if (gp->language != 0U) {
        scale *= 0.6f;
    }
    GXGetProjectionv(proj);
    GXGetViewportv(vp);
    cam = camGetPtr(8);
    GXSetProjection(cam->projection, cam->projType);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    PSMTXTrans(m154, work->position.x, work->position.y, work->position.z);
    PSMTXScale(m124, scale, scale, scale);
    PSMTXConcat(m154, m124, mf4);
    GXSetNumChans(0);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    size = 48.0f;
    half = 24.0f;
    for (s = 1; s >= 0; s--) {
        p = effect->userdata;
        for (i = 1, p++; i < effect->count; i++, p++) {
            dx = (f32)(4 * s);
            dy = (f32)(-s * 4);
            if (s != 0) {
                if (type % 10 == 0) {
                    effGetTexObj(texid_tbl[gp->language * 2 + 1][i - 1], &tex);
                    GXLoadTexObj(&tex, GX_TEXMAP0);
                } else {
                    effGetTexObj(i + 0x4F, &tex);
                    GXLoadTexObj(&tex, GX_TEXMAP0);
                }
                GXSetNumTevStages(1);
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
                GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, 0x80});
            } else if (type % 10 == 0) {
                effGetTexObj(texid_tbl[gp->language * 2][i - 1], &tex);
                GXLoadTexObj(&tex, GX_TEXMAP0);
                effGetTexObj(niji_tbl[gp->language != 0], &tex);
                GXLoadTexObj(&tex, GX_TEXMAP1);
                GXSetNumTevStages(3);
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp(GX_TEVSTAGE0, (GXTevOp)14, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(GX_TEVSTAGE0, (GXTevOp)14, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
                GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
                GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);
                GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
                GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
                GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevColor(GX_TEVREG0, (GXColor){0x36, 0x36, 0x36, 0xFF});
            } else {
                effGetTexObj(i + 0x49 - 1 + 1, &tex);
                GXLoadTexObj(&tex, GX_TEXMAP0);
                GXSetNumTevStages(1);
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
            }
            PSMTXTrans(m154, p->position.x + dx, p->position.y + dy, 0.0f);
            PSMTXScale(m124, p->scale, p->scale, p->scale);
            PSMTXConcat(mf4, m154, m154);
            PSMTXConcat(m154, m124, m154);
            PSMTXConcat(cam->view, m154, m124);
            GXLoadPosMtxImm(m124, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            eyeInit = (Vec){0.0f, 0.0f, 0.0f};
            eyeInit.z = 1.0f / (f32)tan(0.21816615760326385);
            eye = eyeInit;
            up = (Vec){0.0f, 1.0f, 0.0f};
            target = (Vec){0.0f, 0.0f, 0.0f};
            C_MTXLightPerspective(mc4, 25.0f, 640.0f, 0.5f, 0.5f, 0.5f, 0.5f);
            C_MTXLookAt(m94, &eye, &up, &target);
            PSMTXConcat(mc4, m94, mc4);
            PSMTXConcat(mc4, m154, m154);
            PSMTXTrans(m124, (f32)(-frame), 0.0f, 0.0f);
            PSMTXConcat(m154, m124, m154);
            GXLoadTexMtxImm(m154, GX_TEXMTX0, GX_MTX2x4);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(-size / 2.0f, half, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(half, half, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(half, -size / 2.0f, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(-size / 2.0f, -size / 2.0f, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetProjectionv(proj);
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
}

s32 effStageClearEndChk(EffectEntry* effect) {
    return ((StageClearWork*)effect->userdata)->done != 0;
}


#pragma force_active on
#pragma force_active on
__declspec(section ".data") u32 gap_05_803ADD14_data[3] = {0, 0, 0};
__declspec(section ".sdata") u32 gap_07_80415C34_sdata[3] = {0, 0, 0};
#pragma force_active reset
#pragma force_active reset
