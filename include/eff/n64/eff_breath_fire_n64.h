#pragma once

#include "driver/effdrv.h"
#include <dolphin/types.h>
#include <dolphin/mtx.h>

typedef struct EffBreathFireN64Work {
    s32 type;       // 0x0
    s32 count;      // 0x4
    s32 unk8;       // 0x8
    Vec pos;        // 0xc
    Vec start;      // 0x18
    Vec end;        // 0x24
    f32 unk30;      // 0x30
    f32 unk34;      // 0x34
    f32 scale;      // 0x38
    f32 unk3c;      // 0x3c
    s32 alpha;      // 0x40
    s32 lifetime;   // 0x44
    s32 remaining;  // 0x48
    s32 frame;      // 0x4c
    Vec vel;        // 0x50
    f32 unk5c;      // 0x5c
    f32 velY;       // 0x60
    s32 color[6];   // 0x64
} EffBreathFireN64Work;

EffectEntry* effBreathFireN64Entry(s32 type, s32 arg1, s32 arg2, s32 arg3, f32 x, f32 y, f32 z,
                                   f32 arg7, f32 arg8, f32 arg9);
