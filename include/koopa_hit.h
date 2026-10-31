#pragma once

#include "driver/hitdrv.h"

HitEntry* kpaChkHitobjRide(void);
long kpaClearHitobjRide(void);
#ifdef VERSION_G8ME01_DEMO
HitEntry* kpaSearchWallFront(Vec* pos, f32* h, f32 dx, f32 dz);
#endif
