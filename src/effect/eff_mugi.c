#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
double sin(double);
double cos(double);
s32 rand(void);

typedef struct EffMugiWork {
    s32 active;    // 0x0
    s32 type;      // 0x4
    Vec position;  // 0x8
    Vec rotation;  // 0x14
    Vec scale;     // 0x20
    f32 speedA;    // 0x2C
    f32 speedB;    // 0x30
    f32 alpha;     // 0x34
    f32 vel0;      // 0x38
    f32 vel1;      // 0x3C
    f32 vel2;      // 0x40
    f32 vel3;      // 0x44
    f32 vel4;      // 0x48
    f32 dirX;      // 0x4C
    f32 dirZ;      // 0x50
    s32 timer;     // 0x54
    s32 fade;      // 0x58
    f32 extra;     // 0x5C
    s32 poseId;    // 0x60
} EffMugiWork;

void effMugiKemuriMain(EffectEntry* effect);
void effMugiKemuriDisp(CameraId cameraId, EffectEntry* effect);
void effMugiKemuri2Main(EffectEntry* effect);
void effMugiKemuri2Disp(CameraId cameraId, EffectEntry* effect);

EffectEntry* effMugiKemuriEntry(f32 x, f32 y, f32 z, f32 yaw) {
    EffectEntry* effect;
    EffMugiWork* work;
    EffMugiWork* p;
    s32 i;
    f32 a;

    effect = effEntry();
    effect->type = "MugiKemuri\0";
    effect->count = 5;
    work = __memAlloc(HEAP_EFFECT, 5 * sizeof(EffMugiWork));
    effect->userdata = work;
    memset(work, 0, 5 * sizeof(EffMugiWork));
    effect->callback = effMugiKemuriMain;
    effect->flags |= 2;
    for (i = 0, p = work; i < 5; i++, p++) {
        p->active = 1;
        p->speedB = 0.29999998f;
        p->alpha = 0.0f;
        p->vel0 = 0.0f;
        p->position.x = x;
        p->position.y = y;
        p->position.z = z;
        p->scale.x = p->scale.y = p->scale.z = 0.7f;
        p->fade = 255;
        p->timer = 60;
        p->rotation.x = 0.0f;
        p->rotation.y = yaw + (f32)(i * 72);
        p->rotation.z = 0.0f;
        p->vel1 = 1.75f;
        p->vel2 = -0.08f;
        p->vel3 = 0.0f;
        p->vel4 = 0.0f;
        p->speedA = -3.9f;
        a = 2.0f * 3.1415927f * reviseAngle(p->rotation.y) / 360.0f;
        p->dirX = sin(a);
        p->dirZ = cos(a);
        p->poseId = -1;
    }
    return effect;
}

EffectEntry* effMugiKemuri2Entry(s32 type, f32 x, f32 y, f32 z, f32 yaw, f32 flip) {
    EffectEntry* effect;
    EffMugiWork* work;
    EffMugiWork* p;
    s32 i;
    f32 a;

    effect = effEntry();
    effect->type = "MugiKemuri2";
    effect->count = 5;
    work = __memAlloc(HEAP_EFFECT, 5 * sizeof(EffMugiWork));
    effect->userdata = work;
    memset(work, 0, 5 * sizeof(EffMugiWork));
    effect->callback = effMugiKemuri2Main;
    effect->flags |= 2;
    for (i = 0, p = work; i < 5; i++, p++) {
        p->active = 1;
        p->type = type;
        p->vel0 = 0.0f;
        p->position.x = x;
        p->position.y = y;
        p->position.z = z;
        p->scale.x = p->scale.y = p->scale.z = 0.7f;
        p->fade = 255;
        p->alpha = 1.0f;
        p->speedB = 5.4f;
        p->speedA = flip != 0.0f ? -10 : 10;
        p->vel1 = 0.5f;
        p->vel2 = -0.07f;
        p->vel3 = 0.003f;
        p->vel4 = 0.0f;
        p->timer = 15;
        p->rotation.y = yaw;
        p->rotation.x = 0.0f;
        p->rotation.z = 0.0f;
        p->extra = (rand() % 100) >> 4 & 1;
        a = 2.0f * 3.1415927f * reviseAngle(yaw + (flip != 0.0f ? -90 : 90)) / 360.0f;
        p->dirX = sin(a);
        p->dirZ = cos(a);
        p->poseId = -1;
    }
    return effect;
}

void effMugiKemuriMain(EffectEntry* effect) {
    EffMugiWork* work = effect->userdata;
    const char* name;
    EffMugiWork* p;
    s32 i;
    BOOL inBattle;
    BOOL moved;
    Vec position;

    position = (Vec){ work->position.x, work->position.y, work->position.z };
    inBattle = gp->inBattle != 0 ? TRUE : FALSE;

    if (effect->flags & 4) {
        effect->flags &= ~4;
        for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
            if (p->poseId != -1) {
                animPoseRelease(p->poseId);
            }
        }
        effDelete(effect);
        return;
    }
    for (i = 0, p = work; i < effect->count; i++, p++) {
        if (p->poseId == -1) {
            name = strncmp(gp->currentMapName, "win", 3) == 0 ? "EFF_Hana" : "EFF_Mugi";
            if (!animGroupBaseAsync(name, inBattle, NULL)) {
                return;
            }
            p->poseId = animPoseEntry(name, inBattle);
            animPoseSetAnim(p->poseId, "Z_1", TRUE);
        }
    }
    moved = FALSE;
    for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
        if (p->active == 0) {
            continue;
        }
        if (--p->timer <= 0) {
            p->active = 0;
            continue;
        }
        moved = TRUE;
        p->speedA *= 0.85f;
        p->position.x += p->speedA * p->dirX;
        p->position.z += p->speedA * p->dirZ;
        p->vel3 += p->vel4;
        p->vel2 += p->vel3;
        p->vel1 += p->vel2;
        p->position.y += p->vel1;
        if (p->vel1 < 0.0f) {
            p->vel3 = 0.004f;
        }
        p->rotation.x -= 1.0f;
        if (p->rotation.x < -100.0f) {
            p->rotation.x = -100.0f;
        }
    }
    if (!moved) {
        for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
            if (p->poseId != -1) {
                animPoseRelease(p->poseId);
            }
        }
        effDelete(effect);
        return;
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effMugiKemuriDisp, effect);
}

void effMugiKemuri2Main(EffectEntry* effect) {
    EffMugiWork* work = effect->userdata;
    const char* name;
    EffMugiWork* p;
    s32 i;
    BOOL inBattle;
    BOOL moved;
    BOOL alive;
    Vec position;

    position = (Vec){ work->position.x, work->position.y, work->position.z };
    inBattle = gp->inBattle != 0 ? TRUE : FALSE;

    if (effect->flags & 4) {
        effect->flags &= ~4;
        for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
            if (p->poseId != -1) {
                animPoseRelease(p->poseId);
            }
        }
        effDelete(effect);
        return;
    }
    for (i = 0, p = work; i < effect->count; i++, p++) {
        if (p->poseId == -1) {
            name = strncmp(gp->currentMapName, "win", 3) == 0 ? "EFF_Hana" : "EFF_Mugi";
            if (!animGroupBaseAsync(name, inBattle, NULL)) {
                return;
            }
            p->poseId = animPoseEntry(name, inBattle);
            animPoseSetAnim(p->poseId, "Z_1", TRUE);
        }
    }
    moved = FALSE;
    for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
        if (p->active == 0) {
            continue;
        }
        if (--p->timer <= 0) {
            p->active = 0;
            continue;
        }
        moved = TRUE;
        if (p->type == 0 && p->alpha != 0.0f && marioGetPtr()->currMotionId == 0) {
            p->timer++;
            continue;
        }
        p->vel3 += p->vel4;
        p->vel2 += p->vel3;
        p->vel1 += p->vel2;
        p->rotation.z += p->vel1 * p->speedA;
        p->position.x -= p->dirX * (p->vel1 * p->speedB);
        p->position.z -= p->dirZ * (p->vel1 * p->speedB);
        p->fade -= 12;
        if (p->vel1 < 0.0f) {
            p->alpha = 0.0f;
        }
    }
    if (!moved) {
        alive = FALSE;
        for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
            p->fade -= 10;
            if (p->fade > 0) {
                alive = TRUE;
            } else {
                p->fade = 0;
            }
        }
        if (!alive) {
            for (i = 0, p = effect->userdata; i < effect->count; i++, p++) {
                if (p->poseId != -1) {
                    animPoseRelease(p->poseId);
                }
            }
            effDelete(effect);
            return;
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effMugiKemuri2Disp, effect);
}

void effMugiKemuriDisp(CameraId cameraId, EffectEntry* effect) {
    EffMugiWork* p = effect->userdata;
    s32 i;
    Mtx sc, tr, rx, ry, rz;
    GXColor color;

    for (i = 0; i < effect->count; i++, p++) {
        if (p->active == 0 && p->fade == 0) {
            continue;
        }
        PSMTXRotRad(rx, 'x', 0.017453292f * p->rotation.x);
        PSMTXRotRad(ry, 'y', 0.017453292f * p->rotation.y);
        PSMTXRotRad(rz, 'z', 0.017453292f * p->rotation.z);
        PSMTXTrans(tr, p->position.x, p->position.y, p->position.z);
        PSMTXScale(sc, p->scale.x, p->scale.y, p->scale.z);
        PSMTXConcat(rx, rz, rz);
        PSMTXConcat(ry, rz, rz);
        PSMTXConcat(rz, sc, sc);
        PSMTXConcat(tr, sc, tr);
        if (p->poseId == -1) {
            continue;
        }
        animPoseSetMaterialFlagOn(p->poseId, 0x40);
        color = (GXColor){ 0xFF, 0xFF, 0xFF, 0 };
        color.a = p->fade;
        animPoseSetMaterialEvtColor(p->poseId, color);
        animPoseMain(p->poseId);
        animPoseDrawMtx(p->poseId, tr, 1, 0.0f, 15.0f);
        animPoseDrawMtx(p->poseId, tr, 2, 0.0f, 15.0f);
        animPoseDrawMtx(p->poseId, tr, 3, 0.0f, 15.0f);
    }
}

void effMugiKemuri2Disp(CameraId cameraId, EffectEntry* effect) {
    EffMugiWork* p = effect->userdata;
    s32 i;
    Mtx sc, tr, rx, ry, rz;
    GXColor color;

    for (i = 0; i < effect->count; i++, p++) {
        if (p->active == 0 && p->fade == 0) {
            continue;
        }
        PSMTXRotRad(rx, 'x', 0.017453292f * p->rotation.x);
        PSMTXRotRad(ry, 'y', 0.017453292f * p->rotation.y);
        PSMTXRotRad(rz, 'z', 0.017453292f * p->rotation.z);
        PSMTXTrans(tr, p->position.x, p->position.y, p->position.z);
        PSMTXScale(sc, p->scale.x, p->scale.y, p->scale.z);
        PSMTXConcat(rx, rz, rz);
        PSMTXConcat(ry, rz, rz);
        PSMTXConcat(rz, sc, sc);
        PSMTXConcat(tr, sc, tr);
        if (p->poseId == -1) {
            continue;
        }
        animPoseSetMaterialFlagOn(p->poseId, 0x40);
        color = (GXColor){ 0xFF, 0xFF, 0xFF, 0 };
        color.a = p->fade;
        animPoseSetMaterialEvtColor(p->poseId, color);
        animPoseMain(p->poseId);
        animPoseDrawMtx(p->poseId, tr, 1, 0.0f, 15.0f);
        animPoseDrawMtx(p->poseId, tr, 2, 0.0f, 15.0f);
        animPoseDrawMtx(p->poseId, tr, 3, 0.0f, 15.0f);
    }
}
