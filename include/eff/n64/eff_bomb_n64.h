#pragma once

#include "driver/effdrv.h"
#include <dolphin/types.h>

EffectEntry* effBombN64Entry(s32 type, f32 x, f32 y, f32 z);
void effBombN64SetCamId(EffectEntry* effect, s32 camId);
