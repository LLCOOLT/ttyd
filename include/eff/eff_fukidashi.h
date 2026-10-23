#pragma once

#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include "driver/npcdrv.h"

typedef struct EffFukidashiWork {
    s32 type;        // 0x0
    Vec position;    // 0x4
    Vec base;        // 0x10
    f32 angle;       // 0x1C
    f32 size;        // 0x20
    f32 rot;         // 0x24
    f32 zRot;        // 0x28
    f32 scale;       // 0x2C
    s32 timer;       // 0x30
    s32 frame;       // 0x34
    s32 animVal;     // 0x38
    s32 number;      // 0x3C
    s32 duration;    // 0x40
    NpcEntry* npc;   // 0x44
    s32 alpha;       // 0x48
    CameraId camera; // 0x4C
    s32 pad_50;       // 0x50, never accessed
    s32 stage;       // 0x54
} EffFukidashiWork;
