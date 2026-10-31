// eff_hagetaka_flush_n64.c: Paper Mario 64 HagetakaFlush effect entry (effHagetakaFlushN64Entry).
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

// lifetime: both callers pass one (itemdrv 10); the effect does not read it
EffectEntry* effHagetakaFlushN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale);
