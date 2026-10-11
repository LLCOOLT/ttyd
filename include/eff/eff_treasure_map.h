#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effTreasureMapEntry(s32 type, f32 x, f32 y, f32 z);
void effTreasureMapMain(EffectEntry* effect);
void effTreasureMapDisp(CameraId cameraId, EffectEntry* effect);
