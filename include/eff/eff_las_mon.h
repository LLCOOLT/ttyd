#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effLasMonEntry(s32 type, f32 x, f32 y, f32 z);
void effLasMonMain(EffectEntry* effect);
void effLasMonDisp(CameraId cameraId, EffectEntry* effect);
