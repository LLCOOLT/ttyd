#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effMachinegunEntry(s32 type, f32 x, f32 y, f32 z, f32 angle, f32 speed, f32 scale);
void effMachinegunMain(EffectEntry* effect);
void effMachinegunDisp(CameraId cameraId, EffectEntry* effect);
