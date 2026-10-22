#include "eff/eff_rankup.h"
#include "driver/animdrv.h"
#include "driver/dispdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include <dolphin/mtx.h>

typedef struct EffRankupWork {
    s32 type;       // 0x0
    Vec position;   // 0x4
    f32 scale;      // 0x10
    s32 poseId;     // 0x14
    s32 state;      // 0x18
    s32 field_0x1C; // 0x1C
    s32 alpha;      // 0x20
} EffRankupWork;

EffectEntry* effRankupEntry(s32 type, f32 x, f32 y, f32 z) {
    EffectEntry* effect;
    EffRankupWork* work;

    effect = effEntry();
    effect->type = "Rankup\0";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffRankupWork) * effect->count);
    effect->userdata = work;
    effect->callback = effRankupMain;
    effect->flags |= 2;
    work->type = type;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale = 1.0f;
    work->poseId = -1;
    work->state = 0;
    work->field_0x1C = 0;
    work->alpha = 255;
    return effect;
}

void effRankupMain(EffectEntry* effect) {
    EffRankupWork* work = effect->userdata;
    Vec position;
    BOOL inBattle;

    position = (Vec){ work->position.x, work->position.y, work->position.z };
    inBattle = gp->inBattle != 0;

    // soft delete
    if (effect->flags & 4) {
        effect->flags &= ~4;
        if (work->poseId != -1) {
            animPoseRelease(work->poseId);
        }
        effDelete(effect);
        return;
    }
    switch (work->state) {
        case 0:
            if (!animGroupBaseAsync("EFF_TekiKyouka", inBattle, NULL)) {
                return;
            }
            work->poseId = animPoseEntry("EFF_TekiKyouka", (u32)inBattle);
            animPoseSetAnim(work->poseId, "Z_1", TRUE);
            work->state++;
            break;
        case 1:
            if (animPoseGetLoopTimes(work->poseId) > 1.0f) {
                animPoseRelease(work->poseId);
                effDelete(effect);
                return;
            }
            break;
    }
    // fade out over the last part of the animation
    if (!(animPoseGetLoopTimes(work->poseId) < 0.61538464f)) {
        work->alpha -= 20;
        if (work->alpha < 0) {
            work->alpha = 0;
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effRankupDisp, effect);
}

void effRankupDisp(CameraId cameraId, EffectEntry* effect) {
    EffRankupWork* work = effect->userdata;
    Mtx mtx;
    Mtx scale;
    Mtx rot;

    if (work->poseId != -1) {
        PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
        PSMTXScale(scale, work->scale, work->scale, work->scale);
        PSMTXRotRad(rot, 'y', MTXDegToRad(-camGetPtr(cameraId)->viewYaw));
        PSMTXConcat(mtx, rot, mtx);
        PSMTXConcat(mtx, scale, mtx);
        animPoseSetMaterialFlagOn(work->poseId, 0x40);
        animPoseSetMaterialEvtColor(work->poseId, (GXColor){ 0xFF, 0xFF, 0xFF, work->alpha });
        animPoseMain(work->poseId);
        animPoseDrawMtx(work->poseId, mtx, 1, 0.0f, 6.0f);
        animPoseDrawMtx(work->poseId, mtx, 2, 0.0f, 6.0f);
        animPoseDrawMtx(work->poseId, mtx, 3, 0.0f, 6.0f);
    }
}
