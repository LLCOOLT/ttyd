// eff_timestamp_n64.c: timestamp digit effect entry (effTimestampN64Entry).
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

EffectEntry* effTimestampN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
