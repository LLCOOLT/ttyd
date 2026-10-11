#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effRankupEntry(s32 type, f32 x, f32 y, f32 z);
void effRankupMain(EffectEntry* effect);
void effRankupDisp(CameraId cameraId, EffectEntry* effect);
