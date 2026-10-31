// Train wheel animation tables ("sharin", wheel; "clank", crank rods) read by the map scripts of the
// train scenes (gor_04, hom_10, pik_00, rsh_06) with READ_INT4/READ_INT. A NULL name ends a table.
#pragma once

#include "data_tables.h"
#include <dolphin/types.h>

// Map object rotated like a wheel.
typedef struct SharinData {
    const char* name;   // 0x0, map object
    s32 wheelSize;      // 0x4, 0 / 1 / 2: wheel radius 23.9 / 31.1 / 55.0
    s32 speedSource;    // 0x8, 0: GW(0), 1: GW(1) (distance travelled per frame)
    EvtFloat direction; // 0xC, 1.0 or -1.0, multiplies the angle
} SharinData;

// Map object (connecting rod) moved in a circle with its wheel.
typedef struct ClankData {
    const char* name;   // 0x00, map object
    s32 wheelSize;      // 0x04, as SharinData
    s32 speedSource;    // 0x08, as SharinData
    EvtFloat radius;    // 0x0C, crank radius
    EvtFloat direction; // 0x10, 1.0 or -1.0, multiplies the angle
} ClankData;
