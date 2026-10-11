#pragma once

#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effSmallStarEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6,
                               f32 arg7);
void effSmallStarCamChg(EffectEntry* effect, s32 cameraId);
