#pragma once

#include "driver/effdrv.h"
#include "dolphin/types.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

typedef struct EffStarStoneWork {
    s32 type;        // 0x0
    u16 flags;       // 0x4
    Vec position;    // 0x8
    f32 scale;       // 0x14
    f32 f18;         // 0x18
    f32 rotY;        // 0x1C, degrees (stone_ry)
    f32 f20;         // 0x20
    f32 f24;         // 0x24
    f32 f28;         // 0x28
    s32 timer;       // 0x2C
    GXColor color;   // 0x30
    EffectEntry* dust; // 0x34
    s32 cam;         // 0x38
    s32 state;       // 0x3C
    f32 f40;         // 0x40
    f32 f44;         // 0x44
    f32 f48;         // 0x48
    f32 f4c;         // 0x4C
    f32 f50;         // 0x50
    f32 f54;         // 0x54
    f32 f58;         // 0x58
    u8 r, g, b, a;   // 0x5C
    s32 sfx;         // 0x60
} EffStarStoneWork;

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
