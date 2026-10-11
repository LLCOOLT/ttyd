#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effMajinaiEntry(s32 type, f32 x, f32 y, f32 z);
void effMajinaiMain(EffectEntry* effect);
void effMajinaiDisp(CameraId cameraId, EffectEntry* effect);
