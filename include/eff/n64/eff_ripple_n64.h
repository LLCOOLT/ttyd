#pragma once

#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effRippleN64Entry(s32 type, f32 x, f32 y, f32 z, f32 arg4);
void effRippleN64SetRxRz(EffectEntry* effect, f32 rx, f32 rz);
