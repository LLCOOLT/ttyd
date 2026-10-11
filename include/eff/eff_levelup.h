#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effLevelupEntry(s32 type, f32 x, f32 y, f32 z, s32 limit);
void effLevelupMain(EffectEntry* effect);
void effLevelupDisp(CameraId cameraId, EffectEntry* effect);
