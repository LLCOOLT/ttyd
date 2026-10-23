#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

extern double sin(double x);

// sin of an angle given in degrees
static inline f32 effMagic1SinDeg(f32 deg) { return sin(6.2831855f * deg / 360.0f); }

// color pulse between two channel values: from + (to - from) * (1 + sin(deg)) / 2
static inline f32 effMagic1Blend(s32 from, s32 to, f32 deg) {
    return 0.5f * ((f32)(to - from) * (1.0f + effMagic1SinDeg(deg))) + (f32)from;
}

EffectEntry* effMagic1N64Entry(s32 type, s32 life, f32 x, f32 y, f32 z, f32 tx, f32 ty, f32 tz);

extern GXColor magic1_zero_color;
