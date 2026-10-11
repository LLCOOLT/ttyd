#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effTogeFlushEntry(s32 type, f32 x, f32 y, f32 z, s32 life);
void effTogeFlushMain(EffectEntry* effect);
void effTogeFlushDisp(CameraId cameraId, EffectEntry* effect);
