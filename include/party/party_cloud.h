#pragma once

#include <dolphin/mtx.h>

typedef struct PartyCloud {
    f32 unk0; //0x0
    f32 breathDir; //0x4, Gale Force breath direction (toMovedir)
    f32 breathDist; //0x8, Gale Force breath reach
    u8 field_0xC[0x20 - 0xC]; // 0xC
    s32 unk20; //0x20
    s32 unk24; //0x24
    s32 unk28; //0x28
    s32 unk2C; //0x2C
    u8 field_0x30[0x48 - 0xC];
} PartyCloud;

void cloudGetAt(Vec* position);
void cloudResetAt();
u8 cloudGetStatus();
f32 cloudGetBreathDir(void);
s32 cloudGetHitBreathout(s32 param_1);
