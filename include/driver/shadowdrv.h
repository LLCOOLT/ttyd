#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "memory.h"

typedef struct DepthShadowWork {
    s32 unk0; //0x0, flags
    s32 unk4; //0x4, draw count
    s32 unk8; //0x8, config index
    union {
        u8 unkC[0xFC - 0xC]; //0xC
        struct {
            Mtx view; //0xC
            Mtx44 proj; //0x3C
            Mtx texMtx; //0x7C
            Mtx depthMtx; //0xAC
            GXTexObj texObj; //0xDC
        };
    };
    smartEntry* unkFC; //0xFC
    GXColor unk100; //0x100
} DepthShadowWork;

typedef struct ProjShadowWork {
    s32 unk0; //0x0, flags
    s32 unk4; //0x4, draw count
    s32 unk8; //0x8, config index
    union {
        u8 unkC[0xFC - 0xC]; //0xC
        struct {
            Mtx view; //0xC
            Mtx44 proj; //0x3C
            Mtx texMtx; //0x7C
            Mtx depthMtx; //0xAC
            GXTexObj texObj; //0xDC
        };
    };
    smartEntry* unkFC; //0xFC
    GXColor unk100; //0x100
} ProjShadowWork;

typedef struct ShadowEntry {
    u16 flags; //0x0
    u8 mode; //0x2
    u8 type; //0x3
    Vec pos; //0x4
    f32 size; //0x10
    f32 sizeY; //0x14
    s16 offscreenId; //0x18
    s16 camId; //0x1A
    f32 volume; //0x1C
    f32 decay; //0x20
    f32 decay2; //0x24
    u8 alpha; //0x28
    u8 pad_29[3]; //0x29
    Mtx mtx; //0x2C
} ShadowEntry;

typedef struct CharShadowWork {
    s32 unk0; //0x0, flags
    s32 unk4; //0x4, draw count
    s32 unk8; //0x8, config index
    union {
        u8 field_0xC[0xFC - 0xC]; //0xC
        struct {
            Mtx view; //0xC
            Mtx44 proj; //0x3C
            Mtx texMtx; //0x7C
            Mtx depthMtx; //0xAC
            GXTexObj texObj; //0xDC
        };
    };
    smartEntry* unkFC; //0xFC
    GXColor unk100; //0x100
    s32 unk104; //0x104
    ShadowEntry* entries; //0x108
    s32 unk10C; //0x10C
    s32 unk110; //0x110
    f32 unk114; //0x114
    s32 unk118; //0x118
} CharShadowWork;

typedef struct ShadowConfig {
    s32 follow; //0x0
    Vec pos; //0x4
    Vec up; //0x10
    Vec target; //0x1C
    f32 left; //0x28
    f32 top; //0x2C
    f32 near; //0x30
    f32 far; //0x34
    s32 projType; //0x38
    u32 format; //0x3C
    s32 sizeIdx; //0x40
    f32 offset; //0x44
} ShadowConfig;

void shadowInit(void);
void shadowMain(void);