#pragma once

// Magnum Battender (Magnus von Grapple) and Magnum Battender mkII: types shared between the mri and
// aji units.

#include "driver/effdrv.h"
#include <dolphin/mtx.h>
#include <dolphin/types.h>

// One rocket arm (work[0] / work[1], BattleAlloc'd).
typedef struct ArmWork {
    Vec prevPos;      // 0x00
    Vec pos;          // 0x0C
    f32 rot;          // 0x18
    f32 targetRot;    // 0x1C
    EffectEntry* eff; // 0x20, effBattenEntry
} ArmWork;
