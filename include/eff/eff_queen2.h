#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effQueen2Entry(s32 type, f32 x, f32 y, f32 z);
void effQueen2Main(EffectEntry* effect);
void effQueen2Disp(CameraId cameraId, EffectEntry* effect);
