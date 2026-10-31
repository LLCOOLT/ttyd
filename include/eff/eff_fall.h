// eff_fall.c: falling-object effect: effFallEntry and effFallCheckHit.
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 width, f32 drop, f32 dir, s32 num, s32 duration);
s32 effFallCheckHit(EffectEntry* effect);
