#pragma once

#include "driver/effdrv.h"
#include "mario/mario.h" /* MWOFF */
#include <dolphin/mtx.h>

/* the unit/mario the whirlwind follows: only position (0x8C) and size are read */
typedef struct WhirlwindTarget {
    u8 pad0[0x8C];
    Vec position; // 0x8C
    u8 pad1[MWOFF(0x1B8) - 0x98];
    f32 size; // 0x1B8
} WhirlwindTarget;

typedef struct EffWhirlwindN64Work {
    s32 type;                // 0x0
    WhirlwindTarget* target; // 0x4
    Vec position;            // 0x8
    f32 scale;               // 0x14
    f32 baseScale;           // 0x18
    s32 alpha;               // 0x1C
    s32 duration;            // 0x20
    s32 life;                // 0x24
    s32 frame;               // 0x28
    Vec rot;                 // 0x2C
    Vec vel;                 // 0x38
    u8 r, g, b, a;           // 0x44
} EffWhirlwindN64Work;

EffectEntry* effWhirlwindN64Entry(s32 type, WhirlwindTarget* target, f32 scale, s32 life);
