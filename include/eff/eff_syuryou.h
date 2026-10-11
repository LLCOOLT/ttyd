#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effSyuryouEntry(s32 type, s32 duration, f32 x, f32 y, f32 z);
void effSyuryouMain(EffectEntry* effect);
void effSyuryouDisp(CameraId cameraId, EffectEntry* effect);
