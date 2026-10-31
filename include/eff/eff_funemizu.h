// eff_funemizu.c: boat-water effect: effFunemizuEntry, effFunemizuGetMapColor and the work data (EffFunemizuWork).
#pragma once

#include "dolphin/gx/GXStruct.h"
#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include "driver/camdrv.h"
#include "driver/effdrv.h"

typedef struct EffFunemizuWork {
    s32 type;         // 0x0
    Vec position;     // 0x4
    f32 speed;        // 0x10, wake: boat speed (set by the caller each frame); spray: sideways speed
    f32 yaw;          // 0x14, heading in degrees
    f32 layer1Width;  // 0x18, wake: first layer scale, eases to speed (0-1)
    f32 layer2Width;  // 0x1C, second layer scale, eases to speed - 1 (0-1)
    f32 layer1Height; // 0x20
    f32 layer2Height; // 0x24
    f32 layer1Scroll; // 0x28, texture scroll
    f32 layer2Scroll; // 0x2C
    s32 timer;        // 0x30
    f32 velY;         // 0x34, spray: vertical speed
    f32 gravity;      // 0x38, spray: taken off velY each frame
    s32 delay;        // 0x3C
    s32 alpha;        // 0x40
    f32 scale;        // 0x44
    CameraId cam;     // 0x48
} EffFunemizuWork;

GXColor effFunemizuGetMapColor(void);
EffectEntry* effFunemizuEntry(s32 type, f32 x, f32 y, f32 z, f32 size, f32 yaw);
