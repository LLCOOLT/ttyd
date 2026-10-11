#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effToikiEntry(s32 type, s32 duration, f32 x, f32 y, f32 z);
void effToikiMain(EffectEntry* effect);
void effToikiDisp(CameraId cameraId, EffectEntry* effect);
