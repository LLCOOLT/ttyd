#pragma once

// Senkaron ("a thousand bones"): the swarm of up to 1000 Dull Bones drawn as ext poses in gon_03
// (Hooktail Castle) and las_05 (Palace of Shadow).

#include <dolphin/types.h>

typedef struct Senkaron {
    s8 state;  // 0x00
    u16 area;  // 0x02, las_05: floor cell (x + z * 29.5), bones in the same cell are pushed together
    s32 timer; // 0x04
    f32 vx;    // 0x08
    f32 vy;    // 0x0C
    f32 vz;    // 0x10
    u32 flags; // 0x14, las_05 only
} Senkaron;
