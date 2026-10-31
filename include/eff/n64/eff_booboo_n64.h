// eff_booboo_n64.c: Paper Mario 64 Booboo effect entry (effBoobooN64Entry).
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

// evt_eff64 passes the usual N64 effect arguments; the effect reads none of them
EffectEntry* effBoobooN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
