// eff_lensflare_n64.c: lens-flare effect entry (effLensflareN64Entry).
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

EffectEntry* effLensflareN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale); // scale is not read
