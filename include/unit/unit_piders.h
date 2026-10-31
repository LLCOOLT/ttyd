#pragma once

// Piders / Churantalar (spiders): the thread drawn from the ceiling to the spider, shared by every copy
// of the units (jon, mri, tou2 and tst).

#include <dolphin/types.h>

// Kept in the unit's countersetWeapon slot (BTL_ALLOC'd); drawn as a quad from (x0, y0, z0) to (x1, y1, z1).
typedef struct PidersYarn {
    f32 x0, y0, z0; // 0x00, top end, y0 = 400 (above the stage)
    f32 x1, y1, z1; // 0x0C, bottom end at the spider (y1 = unit->work[2])
    u8 alpha;       // 0x18
} PidersYarn;
