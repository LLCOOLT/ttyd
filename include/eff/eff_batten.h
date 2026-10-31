// eff_batten.c: Magnus von Grapple 2.0 effects (バッテンダーエックス): types 1-2 the target mark (EFF_batten_x), type 3 the rocket jets; effBattenEntry and EffBattenWork.
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"
#include <dolphin/mtx.h>

typedef struct EffBattenWork {
    s32 type;        // 0x0, 0: four layers (one work each), else one
    Vec position;    // 0x4
    f32 scale;       // 0x10
    u8 alpha;        // 0x14
    s32 state;       // 0x18
    s32 frame;       // 0x1C
    s32 reserved_20; // 0x20
    s32 poseId;      // 0x24
    Mtx mtx;         // 0x28
    s32 reserved_58; // 0x58
} EffBattenWork;

EffectEntry* effBattenEntry(s32 type, s32 duration, f32 x, f32 y, f32 z, f32 scale);
