// eff_scanning.c: scanning effect entry (effScanningEntry) and its work data (effScanningData).
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"
#include <dolphin/mtx.h>

typedef struct effScanningData {
    s32 type;     // 0x0
    Vec position; // 0x4
    f32 scale;    // 0x10
    s32 animId;   // 0x14
    s32 state;    // 0x18
    s32 timer;    // 0x1C, only cleared at entry
    s32 alpha;    // 0x20, set to 255 at entry
} effScanningData;

EffectEntry* effScanningEntry(s32 int2, f32 float3, f32 float4, f32 float5);
