// eff_mahojin.c: magic-circle effect entry (effMahojinEntry) and its work struct (EffMahojinWork).
#pragma once

#include "driver/effdrv.h"
#include "dolphin/types.h"
#include <dolphin/mtx.h>
#include "driver/camdrv.h"

typedef struct EffMahojinWork {
    s32 type;                             // 0x0
    Vec position;                         // 0x4
    s32 timer;                            // 0x10
    s32 counter;                          // 0x14, only cleared at entry
    s32 poseId[2];                        // 0x18
    s32 alpha;                            // 0x20
    s32 state;                            // 0x24
    EffectEntry* arg;                     // 0x28, star-stone effect drawn in pass 1
    void (*func)(CameraId, EffectEntry*); // 0x2C, effStarStoneDraw
} EffMahojinWork;

EffectEntry* effMahojinEntry(s32 type, f32 x, f32 y, f32 z);
