#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effSparkEntry(s32 type, f32 x, f32 y, f32 z);
void effSparkMain(EffectEntry* effect);
void effSparkDisp(CameraId cameraId, EffectEntry* effect);
