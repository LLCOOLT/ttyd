#include "eff/eff_starpoint.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "memory.h"
#include <dolphin/mtx.h>
#include <stdlib.h>

#define PI 3.1415927f
#define HALF_PI 1.5707964f

typedef struct EffStarPointWork {
    s32 type;                // 0x0
    s32 timer;               // 0x4
    s32 frame;               // 0x8
    Vec position;            // 0xC
    f32 velX;                // 0x18
    f32 velZ;                // 0x1C
    f32 velY;                // 0x20
    f32 gravity;             // 0x24
    u8 field_0x28[4];        // 0x28
    s32 alpha;               // 0x2C
    s32 delay;               // 0x30
} EffStarPointWork;

// cheap polynomial approximations, valid for x in [0, 2pi]
static inline f32 _sinf(f32 x) {
    f32 y;

    if (x <= PI) {
        if (x <= HALF_PI) {
            return ((0.00761f * (x * x) - 0.16605f) * (x * x) + 1.0f) * x;
        }
        y = HALF_PI - (x - HALF_PI);
        return ((0.00761f * (y * y) - 0.16605f) * (y * y) + 1.0f) * y;
    }
    if (x < 4.712389f) {
        y = x - PI;
        return -(((0.00761f * (y * y) - 0.16605f) * (y * y) + 1.0f) * y);
    }
    y = HALF_PI - (x - 4.712389f);
    return -(((0.00761f * (y * y) - 0.16605f) * (y * y) + 1.0f) * y);
}

static inline f32 _cosf(f32 x) {
    f32 y;

    if (x <= PI) {
        if (x <= HALF_PI) {
            return (0.03705f * (x * x) - 0.4967f) * (x * x) + 1.0f;
        }
        y = HALF_PI - (x - HALF_PI);
        return -((0.03705f * (y * y) - 0.4967f) * (y * y) + 1.0f);
    }
    if (x < 4.712389f) {
        y = x - PI;
        return -((0.03705f * (y * y) - 0.4967f) * (y * y) + 1.0f);
    }
    y = HALF_PI - (x - 4.712389f);
    return (0.03705f * (y * y) - 0.4967f) * (y * y) + 1.0f;
}

EffectEntry* effStarPointEntry(s32 type, s32 count, f32 x, f32 y, f32 z) {
    EffectEntry* effect;
    EffStarPointWork* work;
    EffStarPointWork* star;
    s32 i, delay;
    f32 angle;

    effect = effEntry();
    effect->type = "StarPoint";
    effect->count = count + 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffStarPointWork) * effect->count);
    effect->userdata = work;
    effect->callback = effStarPointMain;
    work->type = type;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->timer = 60;
    work->frame = 0;

    star = work + 1;
    for (i = 1, delay = 4; i < effect->count; i++, delay += 3, star++) {
        star->position.x = 0.0f;
        star->position.y = 0.0f;
        star->position.z = 0.0f;
        angle = 6.2831855f * (rand() % 360) / 360.0f;
        star->velX = 2.0f * _sinf(angle);
        star->velZ = 2.0f * _cosf(angle);
        star->velY = 14.0f;
        star->gravity = 2.0f;
        star->alpha = 0;
        star->delay = delay;
    }
    return effect;
}

void effStarPointMain(EffectEntry* effect) {
    EffStarPointWork* work = effect->userdata;
    EffStarPointWork* star;
    Vec position;
    s32 i;

    position = (Vec){ work->position.x, work->position.y, work->position.z };
    work->timer--;
    work->frame++;
    if (work->timer < 0) {
        effDelete(effect);
        return;
    }
    star = work + 1;
    for (i = 1; i < effect->count; i++, star++) {
        if (star->delay) {
            star->delay--;
            star->alpha = 0;
        }
        else {
            star->velY -= star->gravity;
            star->position.x += star->velX;
            star->position.y += star->velY;
            star->position.z += star->velZ;
            if (star->velY < 0.0f) {
                star->alpha -= 2;
                if (star->alpha < 0) {
                    star->alpha = 0;
                }
            }
            else {
                star->alpha = 255;
            }
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 1, (DispCallback)effStarPointDisp, effect);
}

void effStarPointDisp(CameraId cameraId, EffectEntry* effect) {
    EffStarPointWork* work = effect->userdata;
    EffStarPointWork* star;
    Mtx mtx;
    Mtx rot;
    Mtx trans;
    s32 i;

    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rot, 'y', MTXDegToRad(-camGetPtr(CAMERA_3D)->viewYaw));
    PSMTXConcat(mtx, rot, mtx);
    star = work + 1;
    for (i = 1; i < effect->count; i++, star++) {
        if (star->alpha) {
            PSMTXTrans(trans, star->position.x, star->position.y, star->position.z);
            PSMTXConcat(mtx, trans, trans);
            iconDispGx2(trans, 0, 0x18C);
        }
    }
}
