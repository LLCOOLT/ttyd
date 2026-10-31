// eff_thunderflare_n64.c: thunder flare entry (effThunderflareN64Entry) and element data (EffThunderflareN64Elem).
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"
#include <dolphin/mtx.h>

typedef struct EffThunderflareN64Elem {
    s32 flags;    // 0x0, only cleared at entry
    s32 type;     // 0x4
    Vec position; // 0x8
    s32 alpha;    // 0x14
    s32 lifetime; // 0x18
    s32 frame;    // 0x1C
    f32 rotA;     // 0x20
    f32 rotB;     // 0x24
    f32 scale;    // 0x28
    f32 dist;     // 0x2C
    s32 color[6]; // 0x30
} EffThunderflareN64Elem;

// scale: every caller passes one (1.0f); not read
EffectEntry* effThunderflareN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale);
