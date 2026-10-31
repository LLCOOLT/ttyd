// effN64Vtx: N64-style vertex (position, texture coordinates, colour) used by the Paper Mario 64 effect display code.
#pragma once

#include <dolphin/types.h>

// N64-style vertex used by the effN64 display code: position, texture coordinates and colour (stride 0xE).
typedef struct effN64Vtx {
    s16 x, y, z;   // 0x0
    s16 s, t;      // 0x6
    u8 r, g, b, a; // 0xA
} effN64Vtx;
