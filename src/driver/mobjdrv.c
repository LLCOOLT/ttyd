// Map object (mobj) driver: blocks, item boxes, switches and the other interactive map objects:
// their update, hit checks and drawing.
#include "driver/mobjdrv.h"
#include "driver/mapdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario_party.h"
#include "party.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/hitdrv.h"
#include "driver/offscreendrv.h"
#include "driver/itemdrv.h"
#include "manager/evtmgr.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <string.h>
#include "koopa.h"
#include "driver/shadowdrv.h"
#include "manager/evtmgr_cmd.h"
#include "version.h"
#include <dolphin/pad.h>
#include "mot/mot_hip.h"
#include "koopa_hit.h"

/* static map-file joint data for the mobj cube models (same layout as a loaded map file) */
typedef struct CubeDrawMode {
    MapJointDrawMode mode;
    u32 reserved_10;
} CubeDrawMode; /* reserved_10: never accessed */
typedef struct CubeMesh {
    u8 reserved_00;       // 0x0, map file byte, not read (MapFileMesh)
    u8 padding[2];        // 0x1
    u8 isPackedDisplay;   // 0x3
    s32 displayListCount; // 0x4
    u32 elementMask;      // 0x8
    void* vcdTable;       // 0xC, cubeDDT
    u32* lists[15];       // 0x10, display lists in cubeDN
} CubeMesh;
typedef struct CubeJoint {
    MapFileJoint joint;
    MapFileJointPart part;
} CubeJoint;

#if VERSION >= VERSION_JP // small data in retail; in the demo's .data each sits before its joint
CubeDrawMode cubeMSJ = {{0, 1, 0, 0, 0, (s32)0x80000000}, 0};

CubeDrawMode front2MSJ = {{0, 1, 0, 0, 0, 0}, 0};
#endif

// static data from inlined header functions

typedef struct CubeVtxData34 {
    s32 count;
    Vec v[34];
} CubeVtxData34;
typedef struct CubeVtxData18 {
    s32 count;
    Vec v[18];
} CubeVtxData18;
CubeVtxData34 cubeDVP = {
    8,
    {
        { -0.5f, 0.0f, 0.5f },
        { 0.5f, 0.0f, 0.5f },
        { -0.5f, 1.0f, 0.5f },
        { 0.5f, 1.0f, 0.5f },
        { -0.5f, 1.0f, -0.5f },
        { 0.5f, 1.0f, -0.5f },
        { -0.5f, 0.0f, -0.5f },
        { 0.5f, 0.0f, -0.5f },
    },
};

CubeVtxData18 cubeDVN = {
    6,
    {
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, -1.0f },
        { 0.0f, -1.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { -1.0f, 0.0f, 0.0f },
    },
};

void* cubeDDT[26] = {
    &cubeDVP, &cubeDVN, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000,
    (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000,
    (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000, (void*)0x00000000,
    (void*)0x00000000, (void*)0x00000000
};

/* GX display list data: six unpacked index lists of 205 words (count, then one index record per vertex) */
u32 cubeDN[1230] = {
    0x00000004, 0x00000005, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00060005,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00020005, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00040005, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x00070004, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010004, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00050004, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00030004, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000004, 0x00070003, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00060003, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010003,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000003, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000004,
    0x00050002, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00040002, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00070002, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00060002, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x00030001, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00020001, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00050001, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00040001,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000004, 0x00010000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00030000, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00020000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

CubeMesh cubeDP = {0, {0}, 0, 6, 0, cubeDDT, {cubeDN, &cubeDN[205], &cubeDN[410], &cubeDN[615], &cubeDN[820], &cubeDN[1025]}};

#if VERSION <= VERSION_DEMO_US
CubeDrawMode cubeMSJ = {{0, 1, 0, 0, 0, (s32)0x80000000}, 0};
#endif
CubeJoint cubeDJ = {
    { NULL, NULL, NULL, NULL, NULL, NULL, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.5f, 0.0f, -0.5f }, { 0.5f, 1.0f, 0.5f }, { 0 }, &cubeMSJ.mode, 1 },
    { NULL, (MapFileMesh*)&cubeDP },
};

CubeMesh headDP = {0, {0}, 0, 1, 0, cubeDDT, {&cubeDN[410]}};

CubeJoint headDJ = {
    { NULL, NULL, NULL, NULL, NULL, NULL, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.5f, 0.0f, -0.5f }, { 0.5f, 0.0f, 0.5f }, { 0 }, &cubeMSJ.mode, 1 },
    { NULL, (MapFileMesh*)&headDP },
};

CubeMesh frontDP = {0, {0}, 0, 1, 0, cubeDDT, {&cubeDN[1025]}};

CubeJoint frontDJ = {
    { NULL, NULL, NULL, NULL, NULL, NULL, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.5f, 0.0f, -0.5f }, { 0.5f, 1.0f, 0.5f }, { 0 }, &cubeMSJ.mode, 1 },
    { NULL, (MapFileMesh*)&frontDP },
};

#if VERSION <= VERSION_DEMO_US
CubeDrawMode front2MSJ = {{0, 1, 0, 0, 0, 0}, 0};
#endif
CubeMesh front2DP = {0, {0}, 0, 5, 0, cubeDDT, {cubeDN, &cubeDN[205], &cubeDN[410], &cubeDN[615], &cubeDN[820]}};

CubeJoint front2DJ = {
    { NULL, NULL, NULL, NULL, NULL, NULL, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -0.5f, 0.0f, -0.5f }, { 0.5f, 1.0f, 0.5f }, { 0 }, &front2MSJ.mode, 1 },
    { NULL, (MapFileMesh*)&front2DP },
};

#define MAX_MOBJ_WORK 3

//.sbss
BOOL koopaRunFlag;

//.bss
static MapObjectWork work[MAX_MOBJ_WORK];

#define mobjGetWorkFlag(flag) (flag ? &work[1] : &work[0])

#if VERSION <= VERSION_DEMO_US
int mobjCheckKururingFloorItem(MapObjectEntry* entry);
#else
static inline int mobjCheckKururingFloorItem(MapObjectEntry* entry);
#endif

/**
 * Switches to a separate 128-entry map object table (in map memory) for Bowser's side-scrolling stages
 * and marks them running; nothing in the main program calls it, so it comes from the map code.
 * mobjReset turns it off again.
 */
void mobjKoopaOn(void) {
    if (!koopaRunFlag) {
        MapObjectWork* wp = &work[2];

        koopaRunFlag = TRUE;
        wp->count = 128;
        wp->entries = _mapAlloc(sizeof(MapObjectEntry) * wp->count);
        memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);
    }
}

/** Returns the map object table in use: Bowser's stage table while it runs, else the field or battle one. */
inline MapObjectWork* mobjGetWork(void) {
    if (koopaRunFlag) {
        return &work[2];
    } else {
        return mobjGetWorkFlag(gp->inBattle);
    }
}

/**
 * Draw callback for a translucent map object: draws its pose's opaque and translucent parts in one go,
 * with its paper texture if it has one.
 */
static void mobjDispXLU(CameraId camId, void* param) {
    MapObjectEntry* entry = param; // cast to correct type

    if (entry->flags & MOBJ_FLAG_PAPER_TEX) {
        animSetPaperTexMtx(entry->paperTexMtx, NULL, NULL);
        animSetPaperTexObj(&entry->paperTexObj, NULL, NULL, entry->paperTexData, NULL, NULL, 1, 1);
    }
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 1);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 2);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 3);
    if (entry->flags & MOBJ_FLAG_PAPER_TEX) {
        animSetPaperTexMtx(NULL, NULL, NULL);
        animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
    }
}

/**
 * Draw callback for a map object, called once per render pass (opaque, alpha-tested, translucent);
 * draws its pose with its paper texture if it has one.
 */
static void mobjDisp(CameraId camId, void* param) {
    MapObjectEntry* entry = param; // cast to correct type
    DispEntry* disp;

    if (entry->flags & MOBJ_FLAG_PAPER_TEX) {
        animSetPaperTexMtx(entry->paperTexMtx, NULL, NULL);
        animSetPaperTexObj(&entry->paperTexObj, NULL, NULL, entry->paperTexData, NULL, NULL, 1, 1);
    }
    disp = dispGetCurWork();
    switch (disp->renderMode) {
        case 0:
            animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                         10.0f * entry->scale.x, 1);
            break;
        case 1:
            animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                         10.0f * entry->scale.x, 2);
            break;
        case 2:
        default:
            animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                         10.0f * entry->scale.x, 3);
            break;
    }
    if (entry->flags & MOBJ_FLAG_PAPER_TEX) {
        animSetPaperTexMtx(NULL, NULL, NULL);
        animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
    }
}

/**
 * Draw callback on the offscreen camera for a map object with an offscreen region:
 * draws its pose and grows the region by the screen box it covered.
 */
static void mobjDisp_OffscreenXLU(CameraId camId, void* param) {
    MapObjectEntry* entry = param; // cast to correct type
    u16 left, top, right, bottom;

    sysWaitDrawSync();
    GXClearBoundingBox();
    if (entry->flags & MOBJ_FLAG_PAPER_TEX) {
        animSetPaperTexMtx(entry->paperTexMtx, NULL, NULL);
        animSetPaperTexObj(&entry->paperTexObj, NULL, NULL, entry->paperTexData, NULL, NULL, 1, 1);
    }
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 1);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 2);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 3);
    if (entry->flags & MOBJ_FLAG_PAPER_TEX) {
        animSetPaperTexMtx(NULL, NULL, NULL);
        animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->offscreenId, left, top, right, bottom);
}

/** Allocates the field (16) and battle (8) map object tables; called once at boot. */
void mobjInit(void) {
    MapObjectWork* wp = &work[0];

    wp->count = 16;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(MapObjectEntry) * wp->count);
    memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);

    wp = &work[1];
    wp->count = 8;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(MapObjectEntry) * wp->count);
    memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);

    koopaRunFlag = FALSE;
}

/** Clears the field or battle map object table and leaves Bowser's stage mode; run when a map or battle starts. */
void mobjReset(BOOL inBattle) {
    MapObjectWork* wp = mobjGetWorkFlag(inBattle);
    memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);
    koopaRunFlag = FALSE;
}

/**
 * Creates the collision for a map object from its pose's bounding box, replacing any it had:
 * type 0 a solid cube (MOBJ_<name>), 1 a cube shaped for head hits,
 * 2 a front cube plus a second part (MOBJ~<name>) for objects with two hit parts.
 */
void mobjHitEntry(MapObjectEntry* entry, s32 type) {
    AnimationPoseData* pose;
    Mtx mtx;
    Vec min;
    Vec max;
    Vec position;
    s32 i;

    pose = animPoseGetAnimBaseDataPtr(entry->poseId);
    min = (Vec){pose->bboxMin.x, pose->bboxMin.y, pose->bboxMin.z};
    max = (Vec){pose->bboxMax.x, pose->bboxMax.y, pose->bboxMax.z};
    for (i = 0; i < 2; i++) {
        if (entry->hitObj[i].hitObject != NULL)
            hitDelete(entry->hitObj[i].name);
    }
    PSVECAdd(&max, &min, &entry->translation);
    PSVECScale(&entry->translation, &entry->translation, 0.5f);
    PSVECScale(&entry->translation, &entry->translation, 10.0f);
    entry->translation.y = 0.0f;
    // FAKE: the `(0, x)` comma expressions change MWCC's expression tree so the |max - min| loads get the
    // target float registers; the values are the same
    entry->scale2.x = 10.0f * (entry->scale.x * (f32)(0, __fabs((0, max.x - min.x))));
    entry->scale2.y = 10.0f * (entry->scale.y * (f32)__fabs(max.y));
    entry->scale2.z = 10.0f * (entry->scale.z * (f32)(0, __fabs((0, max.z - min.z))));
    if (strncmp(pose->fileName, "HOBJ_", strlen("HOBJ_")) == 0) {
        entry->translation.z = 0.0f;
        entry->scale2.z = 10.0f * (2.5f * entry->scale.z);
    }
    switch (type) {
        case 0:
            PSVECAdd(&entry->position, &entry->translation, &position);
            {
                Mtx zrot, yrot, xrot, scale, trans;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
            memcpy(entry->hitObj[0].jointData + 8, &cubeDJ, sizeof(CubeJoint));
            strcpy(entry->hitObj[0].name, "MOBJ_");
            strcat(entry->hitObj[0].name, entry->name);
            *(char**)(entry->hitObj[0].jointData + 8) = entry->hitObj[0].name;
            entry->hitObj[0].hitObject = hitEntryMOBJ((MapFileJoint*)(entry->hitObj[0].jointData + 8), mtx);
#if VERSION >= VERSION_JP // the demo hit objects have no mobj back pointer
            entry->hitObj[0].hitObject->mobj = entry;
#endif
            break;
        case 1:
            PSVECAdd(&entry->position, &entry->translation, &position);
            {
                Mtx zrot, yrot, xrot, scale, trans;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
            memcpy(entry->hitObj[0].jointData + 8, &headDJ, sizeof(CubeJoint));
            strcpy(entry->hitObj[0].name, "MOBJ_");
            strcat(entry->hitObj[0].name, entry->name);
            *(char**)(entry->hitObj[0].jointData + 8) = entry->hitObj[0].name;
            entry->hitObj[0].hitObject = hitEntryMOBJ((MapFileJoint*)(entry->hitObj[0].jointData + 8), mtx);
#if VERSION >= VERSION_JP // the demo hit objects have no mobj back pointer
            entry->hitObj[0].hitObject->mobj = entry;
#endif
            break;
        case 2:
            PSVECAdd(&entry->position, &entry->translation, &position);
            {
                Mtx zrot, yrot, xrot, scale, trans;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
            memcpy(entry->hitObj[0].jointData + 8, &frontDJ, sizeof(CubeJoint));
            strcpy(entry->hitObj[0].name, "MOBJ_");
            strcat(entry->hitObj[0].name, entry->name);
            *(char**)(entry->hitObj[0].jointData + 8) = entry->hitObj[0].name;
            entry->hitObj[0].hitObject = hitEntryMOBJ((MapFileJoint*)(entry->hitObj[0].jointData + 8), mtx);
#if VERSION >= VERSION_JP // the demo hit objects have no mobj back pointer
            entry->hitObj[0].hitObject->mobj = entry;
#endif
            memcpy(entry->hitObj[1].jointData + 8, &front2DJ, sizeof(CubeJoint));
            strcpy(entry->hitObj[1].name, "MOBJ~");
            strcat(entry->hitObj[1].name, entry->name);
            *(char**)(entry->hitObj[1].jointData + 8) = entry->hitObj[1].name;
            entry->hitObj[1].hitObject = hitEntryMOBJ((MapFileJoint*)(entry->hitObj[1].jointData + 8), mtx);
#if VERSION >= VERSION_JP // the demo hit objects have no mobj back pointer
            entry->hitObj[1].hitObject->mobj = entry;
#endif
            break;
    }
}

/**
 * Creates a named map object (blocks, switches, boxes, save blocks, ...) drawing animation pose animPoseName,
 * reusing the slot if the name exists; returns its index. Called by the evt_mobj entry commands.
 */
s32 mobjEntry(const char* name, const char* animPoseName) {
    MapObjectWork* wp = mobjGetWork();
    s32 entryCount;
    s32 idx;
    MapObjectEntry* entry;

    entryCount = wp->count;
    for (idx = 0, entry = wp->entries; idx < entryCount; idx++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) && (strcmp(entry->name, name) == 0))
            break;
    }
    // SPM uses this to assert the name isn't duplicate, here it's just pointless

    for (idx = 0, entry = wp->entries; idx < entryCount; idx++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) == 0)
            break;
    }

    memset(entry, 0, sizeof(*entry));
    entry->flags |= MOBJ_FLAG_USED;
    strcpy(entry->name, name);

    entry->position = (Vec){0.0f, 0.0f, 0.0f};
    entry->scale = (Vec){1.0f, 1.0f, 1.0f};
    entry->rotation = (Vec){0.0f, 0.0f, 0.0f};
    entry->velocity = (Vec){0.0f, 0.0f, 0.0f};
    entry->gravity = 1.0f;
    entry->bounce = 1.0f;
    entry->camId = CAMERA_3D;
    entry->poseId = animPoseEntry(animPoseName, gp->inBattle != 0);
    animPosePeraOff(entry->poseId);
    strcpy(entry->animName, animPoseName);
    animPoseSetAnim(entry->poseId, "S_1", 1);
    animPoseSetMaterialLightFlagOn(entry->poseId, ANIM_MATERIAL_LIGHT_CHARA);
    mobjHitEntry(entry, 0);
    entry->offscreenId = -1;
    return idx;
}

/** Removes the named map object and its collision and frees its pose. */
void mobjDelete(const char* name) {
    MapObjectWork* wp = mobjGetWork();
    s32 entryCount;
    int i;
    MapObjectEntry* entry;

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) && strcmp(entry->name, name) == 0) {
            for (i = 0; i < 2; i++) {
                if ((entry->hitObj[i].name) != NULL) {
                    if (!gp->inBattle) {
                        marioResetHitObj(entry->hitObj[i].name);
                    }
                    hitDelete(entry->hitObj[i].name);
                }
            }
            entry->flags &= ~MOBJ_FLAG_USED;
            break;
        }
    }
}

/** Moves the named map object to (x, y, z) and updates its collision. */
void mobjSetPosition(const char* name, f32 x, f32 y, f32 z) {
    MapObjectWork* wp = mobjGetWork();
    MapObjectEntry* entry;
    s32 entryCount;
    int i;

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) && strcmp(entry->name, name) == 0) {
            break;
        }
    }

    entry->position.x = x;
    entry->position.y = y + 0.1f;
    entry->position.z = z;
}

typedef struct MobjWorkHit {
    s32 count;
    MapObjectEntry* entries;
    HitEntry* hit[5];
} MobjWorkHit;
#define WH(k) (wp->hit[k])

/**
 * Per-frame update of all map objects: works out which one Mario hammered, hit from below, stood on,
 * spun on or touched with an action, which one a partner, a Bobbery bomb or Bowser hit,
 * and reports it to the object; runs each object's main function, drops falling ones,
 * keeps their shadows and colours, and queues their drawing (offscreen if they have a region).
 */
void mobjMain(void) {
    MobjWorkHit* wp;
    MapObjectEntry* entry;
    MarioWork* mario;
    PartyEntry* party;
    s16 fbat;
    s32 count;
    s32 i;
    s32 hit;
    HitEntry* hitJump;
    s32 partyFlag;
    HitEntry* hitPtr;
    s32 k;
    GXColor blend1;
    GXColor blend2;
    GXColor evt;
    Vec camPos;
    f32 nz, ny, nx, dist, hz, hy, hx;

    {
        MapObjectWork* w = mobjGetWork();
        wp = (MobjWorkHit*)w;
    }
    count = wp->count;
    entry = wp->entries;
    mario = marioGetPtr();
    party = partyGetPtr(marioGetPartyId());
    fbat = *(s16*)fbatGetPointer();
    hitJump = NULL;
    partyFlag = 0;
    if (party != NULL && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        partyFlag = 1;
    }

    if (gp->inBattle == 0) {
        if (mario->hitobjHammer != NULL) {
            if (WH(0) == NULL || strcmp(hitGetName(WH(0)), hitGetName(mario->hitobjHammer)) != 0) {
                WH(0) = mario->hitobjHammer;
            }
        } else {
            WH(0) = NULL;
        }
        if (mario->hitobjHead != NULL) {
            if (WH(1) == NULL || strcmp(hitGetName(WH(1)), hitGetName(mario->hitobjHead)) != 0) {
                hitJump = WH(1) = mario->hitobjHead;
            }
        } else {
            WH(1) = NULL;
        }
        if (mario->hitobjStandOn != NULL) {
            if (WH(2) == NULL || strcmp(hitGetName(WH(2)), hitGetName(mario->hitobjStandOn)) != 0) {
                WH(2) = mario->hitobjStandOn;
            }
        } else {
            WH(2) = NULL;
        }
        if (mario->hitobjFront != NULL) {
            if (WH(3) == NULL || strcmp(hitGetName(WH(3)), hitGetName(mario->hitobjFront)) != 0) {
                WH(3) = mario->hitobjFront;
            }
        } else {
            WH(3) = NULL;
        }
        if (party != NULL && party->hitobjAction != NULL) {
            if (WH(4) == NULL || strcmp(hitGetName(WH(4)), hitGetName(party->hitobjAction)) != 0) {
                WH(4) = party->hitobjAction;
            }
        } else {
            WH(4) = NULL;
        }
    }

    for (i = 0; i < count; i++, entry++) {
        if (!(entry->flags & MOBJ_FLAG_USED)) {
            continue;
        }
#if VERSION >= VERSION_US
        if (!(gp->inBattle == 0 && (gp->inBattle != 0 || ((u32)fbat > 1 && fbat != 8)) &&
              !(entry->flags & MOBJ_FLAG_PAPER_TEX))) {
#else
        if (!(gp->inBattle == 0 && (gp->inBattle != 0 || ((u32)fbat > 1 && fbat != 8)))) {
#endif
            if (entry->flags & MOBJ_FLAG_CALC_MTX) {
                if (mobjCheckItemboxOpen(entry) == 2) {
                    mobjCalcMtx2(entry);
                } else {
                    mobjCalcMtx(entry);
                }
                entry->flags &= ~MOBJ_FLAG_CALC_MTX;
            }
            if (entry->flags & MOBJ_FLAG_FALL) {
                if (entry->velocity.y >= 0.0f) {
                    entry->position.y += entry->velocity.y;
                    entry->velocity.y -= entry->gravity;
                } else {
#if VERSION <= VERSION_DEMO_US
                    dist = 1.0f + (f32)__fabs(entry->velocity.y);
                    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, entry->position.x,
                                       10.0f + entry->position.y, entry->position.z, 0.0f, -10.0f, 0.0f) != NULL) {
#else
                    dist = 10.0f + (1.0f + (f32)__fabs(entry->velocity.y));
                    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, entry->position.x,
                                       10.0f + entry->position.y, entry->position.z, 0.0f, -1.0f, 0.0f) != NULL) {
#endif
                        entry->position.y = hy;
                        entry->velocity.y = (-0.5f * entry->bounce) * entry->velocity.y;
                        if (__fabs(entry->velocity.y) <= 2.0) {
                            entry->velocity.y = 0.0f;
                        }
                    } else {
                        entry->position.y += entry->velocity.y;
                        entry->velocity.y -= entry->gravity;
                    }
                }
                mobjCalcMtx(entry);
            }
            if (!(entry->flags & MOBJ_FLAG_HIT)) {
                hit = 0;
                hitPtr = entry->hitObj[0].hitObject;
                if ((s32)(u8)mario->characterId != 2) {
                    // The first hit kind that applies wins. The goto is kept: the hammer and partner checks
                    // fall through to the next kind when their inner test fails, and no if/else-if form of
                    // that gives the same code (the partner blocks merge or re-test the flag).
                    if ((entry->flags & MOBJ_HIT_HAMMER) && mario->hitobjHammer == hitPtr) {
                        if (marioGetPtr()->position.y <= 5.0f + entry->position.y) {
                            entry->hitFlag = MOBJ_HIT_HAMMER;
                            hit = 1;
                            goto hitDone;
                        }
                    }
                    if ((entry->flags & MOBJ_HIT_FROM_BELOW) && hitJump == hitPtr) {
                        entry->hitFlag = MOBJ_HIT_FROM_BELOW;
                        hit = 1;
                        goto hitDone;
                    }
                    if ((entry->flags & MOBJ_HIT_STAND_ON) && mario->hitobjStandOn == hitPtr) {
                        entry->hitFlag = MOBJ_HIT_STAND_ON;
                        hit = 1;
                        goto hitDone;
                    }
                    if ((entry->flags & MOBJ_HIT_SPIN_JUMP) && mario->hitobjStandOn == hitPtr && marioChkHipBump()) {
                        entry->hitFlag = MOBJ_HIT_SPIN_JUMP;
                        hit = 1;
                        goto hitDone;
                    }
#if VERSION <= VERSION_DEMO_US
                    if ((entry->flags & MOBJ_HIT_FRONT_ACTION) && mario->hitobjFront == hitPtr &&
                        (mario->buttonTrg & PAD_BUTTON_A) && !partyFlag) {
#else
                    if (marioFrontActionValidChk() && (entry->flags & MOBJ_HIT_FRONT_ACTION) &&
                        mario->hitobjFront == hitPtr && (mario->buttonTrg & PAD_BUTTON_A) && !partyFlag) {
#endif
                        entry->hitFlag = MOBJ_HIT_FRONT_ACTION;
                        hit = 1;
                        goto hitDone;
                    }
                    if ((entry->flags & MOBJ_HIT_PARTY_ACTION) && party != NULL) {
                        if (party->hitobjAction == hitPtr) {
                            entry->hitFlag = MOBJ_HIT_PARTY_ACTION;
                            hit = 1;
                            goto hitDone;
                        } else if (party->hitobjAction != NULL && (s32)(u8)party->currentMemberId == PARTY_MEMBER_BOBBERY) {
                            if (PSVECDistance(&party->position, &entry->position) <
                                entry->hitObj[0].hitObject->radius + party->width) {
                                entry->hitFlag = MOBJ_HIT_PARTY_ACTION;
                                hit = 1;
                                goto hitDone;
                            }
                        }
                    }
                    if ((entry->flags & MOBJ_HIT_BOMB) && party != NULL && (s32)(u8)party->currentMemberId == PARTY_MEMBER_BOBBERY) {
                        if (party->hitobjAction == hitPtr) {
                            entry->hitFlag = MOBJ_HIT_BOMB;
                            hit = 1;
                            goto hitDone;
                        } else if (party->hitobjAction != NULL) {
                            if (PSVECDistance(&party->position, &entry->position) <
                                entry->hitObj[0].hitObject->radius + party->width) {
                                entry->hitFlag = MOBJ_HIT_PARTY_ACTION;
                                hit = 1;
                                goto hitDone;
                            }
                        }
                    }
                } else {
                    if (entry->flags & MOBJ_HIT_KOOPA_HEAD) {
                        for (k = 0; k < 10; k++) {
                            if (kpaGetHitobjHead(k) == hitPtr) {
                                entry->hitFlag = MOBJ_HIT_KOOPA_HEAD;
                                hit = 1;
                                break;
                            }
                        }
                    }
                    if (entry->flags & MOBJ_HIT_KOOPA_HIP_DROP) {
                        for (k = 0; k < 10 && hit == 0; k++) {
                            if (kpaGetHitobjRide(k) == hitPtr && kpaHipAttackCheck()) {
                                entry->hitFlag = MOBJ_HIT_KOOPA_HIP_DROP;
                                hit = 1;
                                break;
                            }
                        }
                    }
                    if ((entry->flags & MOBJ_HIT_KOOPA_LEVEL3) && kpaGetHitobj() == hitPtr && kpaGetLevel() == 3) {
                        entry->hitFlag = MOBJ_HIT_KOOPA_LEVEL3;
                        hit = 1;
                    } else if ((entry->flags & MOBJ_HIT_KOOPA_FLAME) && kpaGetHitFlame() == hitPtr) {
                        entry->hitFlag = MOBJ_HIT_KOOPA_FLAME;
                        hit = 1;
                    } else if ((entry->flags & MOBJ_HIT_KOOPA_FRONT) && mario->hitobjFront == hitPtr) {
                        entry->hitFlag = MOBJ_HIT_KOOPA_FRONT;
                        hit = 1;
                    } else if ((entry->flags & MOBJ_HIT_STAND_ON) && mario->hitobjStandOn == hitPtr) {
                        entry->hitFlag = MOBJ_HIT_STAND_ON;
                        hit = 1;
                    }
                }
            hitDone:
                if (hit != 0) {
                    entry->flags |= MOBJ_FLAG_HIT;
                }
            }
            if (entry->flags & MOBJ_FLAG_NO_HIT) {
                entry->flags &= ~MOBJ_FLAG_HIT;
            }
            if ((u32)marioStGetSystemLevel() != 0) {
                entry->flags &= ~MOBJ_FLAG_HIT;
            }
#if VERSION >= VERSION_JP
            {
                MarioMotion motion = marioGetPtr()->currMotionId;
                if (motion == 0x1f || motion == 0x20) {
                    entry->flags &= ~MOBJ_FLAG_HIT;
                }
            }
#endif
            if (entry->mainFunc != NULL) {
                if (entry->mainFunc(entry) == -1) {
                    continue;
                }
            }
        }
        if (!(entry->flags & MOBJ_FLAG_USED)) {
            continue;
        }
        if (!koopaRunFlag && !(entry->flags & (MOBJ_FLAG_NO_SHADOW | MOBJ_FLAG_HIDDEN))) {
            MapWork* mw = mapGetWork();
            s32 shadowId;
            mapGetBlend(&blend1);
            mapGetBlend2(&blend2);
            if ((mw->entries[0].flags & 2) && !(animPoseGetMaterialFlag(entry->poseId) & 0x800) && blend1.a != 0xff) {
            } else if ((mw->entries[0].flags & 4) && !(animPoseGetMaterialFlag(entry->poseId) & 0x1000) &&
                       blend2.a != 0xff) {
            } else {
                shadowId = shadowEntry(entry->position.x, entry->position.y, entry->position.z,
                                       10.0f * entry->scale.x * entry->scale2.x / 25.0f);
                if (entry->flags & MOBJ_HIT_FROM_BELOW) {
                    shadowSetType(shadowId, 1);
                    shadowSetSize(shadowId, 10.0f * entry->scale.x * entry->scale2.x / 20.0f);
                }
            }
        }
        animPoseMain(entry->poseId);
        evt = animPoseGetMaterialEvtColor(entry->poseId);
        if (entry->flags & MOBJ_FLAG_INVISIBLE) {
            continue;
        }
        if (!(entry->flags & MOBJ_FLAG_NO_CULL)) {
            PSMTXMultVec(camGetPtr(CAMERA_3D)->view, &entry->position, &camPos);
            PSMTX44MultVec(camGetPtr(CAMERA_3D)->projection, &camPos, &camPos);
            if (__fabs(camPos.x) > 1.5 || __fabs(camPos.y) > 1.5 || __fabs(camPos.z) > 1.0) {
                continue;
            }
        }
        if ((entry->flags & MOBJ_FLAG_BLINK) && ((gp->retraceCount >> 3) & 1)) {
            continue;
        }
        if (entry->offscreenId == -1) {
            if ((animPoseGetMaterialFlag(entry->poseId) & 0x40) && evt.a != 0xff) {
                dispEntry(entry->camId, dispCalcZ(&entry->position), 2, mobjDispXLU, entry);
            } else {
                dispEntry(entry->camId, dispCalcZ(&entry->position), 0, mobjDisp, entry);
                dispEntry(entry->camId, dispCalcZ(&entry->position), 1, mobjDisp, entry);
                dispEntry(entry->camId, dispCalcZ(&entry->position), 2, mobjDisp, entry);
            }
        } else {
            if ((animPoseGetMaterialFlag(entry->poseId) & 0x40) && evt.a != 0xff) {
                dispEntry(CAMERA_OFFSCREEN2, dispCalcZ(&entry->position), 2, mobjDisp_OffscreenXLU, entry);
            } else {
                dispEntry(CAMERA_OFFSCREEN2, dispCalcZ(&entry->position), 0, mobjDisp_OffscreenXLU, entry);
                dispEntry(CAMERA_OFFSCREEN2, dispCalcZ(&entry->position), 1, mobjDisp_OffscreenXLU, entry);
                dispEntry(CAMERA_OFFSCREEN2, dispCalcZ(&entry->position), 2, mobjDisp_OffscreenXLU, entry);
            }
        }
    }
}

/** Returns the map object with this name; one past the table when there is none (the name is expected to exist). */
MapObjectEntry* mobjNameToPtr(const char* name) {
    int i;
    s32 entryCount;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) && strcmp(entry->name, name) == 0) {
            break;
        }
    }

    return entry;
}

/** Returns the map object with this name, or NULL if there is none. */
MapObjectEntry* mobjNameToPtrNoAssert(const char* name) {
    int i;
    s32 entryCount;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) && strcmp(entry->name, name) == 0) {
            break;
        }
    }

    if (i >= entryCount) {
        return NULL;
    }

    return entry;
}

#if VERSION <= VERSION_DEMO_US
/** the demo searches the mobj list for the entry whose first hit object is hitObj */
MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hitObj) {
    int i;
    s32 entryCount;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) && hitObj == entry->hitObj[0].hitObject) {
            break;
        }
    }

    return entry;
}
#else
/**
 * Returns the map object that owns collision hitObj,
 * or NULL if it is not map-object collision (attribute bit 31). The demo searches the table instead.
 */
MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hitObj) {
    if (hitObj->attributes & (1 << 31)) {
        return hitObj->mobj;
    }

    return NULL;
}
#endif

/**
 * Starts script eventCode for a map object (its this-object is set),
 * unless the object's previous script is still running; returns the event or NULL.
 */
EventEntry* mobjRunEvent(MapObjectEntry* entry, EvtWord* eventCode) {
    EventEntry* event;

    if (eventCode == NULL) {
        return NULL;
    }
    if (evtCheckID(entry->eventId)) {
        return NULL;
    }

    entry->eventId = 0;
    event = evtEntryType(eventCode, 0x1E, 0, 0x1A);
    event->thisMapObj = entry;
    entry->eventId = event->eventId;

    return event;
}

/** Builds a scale, x/y/z rotation (degrees) and translation matrix. */
static inline void calcMtx(Mtx mtx, Vec* pos, Vec* sc, Vec* rot) {
    Mtx trans;
    Mtx scale;
    Mtx xrot;
    Mtx yrot;
    Mtx zrot;
    MTXTrans(trans, pos->x, pos->y, pos->z);
    MTXScale(scale, sc->x, sc->y, sc->z);
    MTXRotRad(xrot, 'x', MTXDegToRad(rot->x));
    MTXRotRad(yrot, 'y', MTXDegToRad(rot->y));
    MTXRotRad(zrot, 'z', MTXDegToRad(rot->z));
    MTXConcat(trans, zrot, trans);
    MTXConcat(trans, yrot, trans);
    MTXConcat(trans, xrot, trans);
    MTXConcat(trans, scale, mtx);
}

/**
 * Recomputes a map object's collision matrices from its position, scale and rotation,
 * sizing the hit cube from its pose's bounding box (HOBJ_ poses get a thin fixed depth).
 */
void mobjCalcMtx(MapObjectEntry* entry) {
    AnimationPoseData* pose;
    Mtx mtx;
    Vec position;
    Vec min;
    Vec max;
    s32 i;

    PSVECAdd(&entry->position, &entry->translation, &position);
    pose = animPoseGetAnimBaseDataPtr(entry->poseId);
    min = (Vec){pose->bboxMin.x, pose->bboxMin.y, pose->bboxMin.z};
    max = (Vec){pose->bboxMax.x, pose->bboxMax.y, pose->bboxMax.z};
    entry->scale2.x = 10.0f * (entry->scale.x * (f32)__fabs(max.x - min.x));
    entry->scale2.y = 10.0f * (entry->scale.y * (f32)__fabs(max.y));
    entry->scale2.z = 10.0f * (entry->scale.z * (f32)__fabs(max.z - min.z));
    if (strncmp(pose->fileName, "HOBJ_", strlen("HOBJ_")) == 0) {
        entry->translation.z = 0.0f;
        entry->scale2.z = 10.0f * (2.5f * entry->scale.z);
    }
    calcMtx(mtx, &position, &entry->scale2, &entry->rotation);
    for (i = 0; i < 2; i++) {
        if (entry->hitObj[i].hitObject != NULL) {
            if (1) {
            }
            hitReCalcMatrix(entry->hitObj[i].hitObject, mtx);
        }
    }
}

/**
 * Recomputes a map object's collision matrices from its position, rotation and the already-computed hit size;
 * evt_mobj calls it as objects move.
 */
void mobjCalcMtx2(MapObjectEntry* entry) {
    Mtx mtx;
    Vec position;
    s32 i;

    PSVECAdd(&entry->position, &entry->translation, &position);

    calcMtx(mtx, &position, &entry->scale2, &entry->rotation);

    for (i = 0; i < 2; i++) {
        if (entry->hitObj[i].hitObject != 0)
            hitReCalcMatrix(entry->hitObj[i].hitObject, mtx);
    }
}

/**
 * Returns whether a map object shows the "!" hint balloon over Mario when he is near (MOBJ_FLAG_HINT).
 * Later versions accept NULL.
 */
BOOL mobjGetHint(MapObjectEntry* entry) {
#if VERSION >= VERSION_JP
    if (entry == NULL) {
        return 0;
    }
#endif
    return (entry->flags & MOBJ_FLAG_HINT) != 0;
}

/** Returns TRUE while any map object is busy (MOBJ_FLAG_BUSY); the pause menu does not open then. */
BOOL mobjCheckExec() {
    MapObjectWork* wp = mobjGetWork();
    int i;
    MapObjectEntry* entry;

    for (i = 0, entry = wp->entries; i < wp->count; entry++, i++) {
        if (entry->flags & MOBJ_FLAG_BUSY)
            return TRUE;
    }
    return FALSE;
}

/**
 * For treasure chests (normal, big, gray, black) returns 2 once opened (state 99) and 1 while closed;
 * 0 for any other object.
 */
s32 mobjCheckItemboxOpen(MapObjectEntry* entry) {
    if (strcmp(entry->animName, "MOBJ_TreasureBox") == 0 || strcmp(entry->animName, "MOBJ_BigTreasureBox") == 0 ||
        strcmp(entry->animName, "MOBJ_GrayTreasureBox") == 0 || strcmp(entry->animName, "MOBJ_BlackTreasureBox") == 0) {
        if (entry->state == 99)
            return 2;
        else
            return 1;
    } else {
        return 0;
    }
}

#if VERSION <= VERSION_DEMO_US
// FAKE: stand-in for the stripped function whose constants open the .sdata2 pool; the demo's fall code uses
// 1 + |vy| and a -10 ray, so its constants come in this order (and its 2.0 opens the .rodata doubles)
void mobjStrippedFallPool(MapObjectEntry* entry) {
    entry->velocity.y = 0.0f;
    entry->position.y = 1.0f;
    entry->position.x = 10.0f;
    entry->position.z = -10.0f;
    entry->velocity.x = -0.5f;
    if (__fabs(entry->velocity.y) <= 2.0) {
        entry->velocity.z = 0.0f;
    }
}

/** demo only: the nearest active mobj within minMagnitude of (x, y, z) */
MapObjectEntry* mobjNearDistCheck(f32 x, f32 y, f32 z, f32 minMagnitude) {
    int entryCount;
    Vec pos;
    Vec dist;
    Vec _pos;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();
    MapObjectEntry* ret;
    int i;
    float mag;

    entryCount = wp->count;
    entry = wp->entries;
    ret = NULL;

    _pos = (Vec){0.0f, 0.0f, 0.0f};
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
    pos = _pos;

    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) == 0)
            continue;

        VECSubtract(&entry->position, &pos, &dist);
        mag = VECMag(&dist);
        if (mag < minMagnitude) {
            minMagnitude = mag;
            ret = entry;
        }
    }

    return ret;
}
#endif

/**
 * Returns the nearest map object within minMagnitude of (x, y, z) whose pose is in the NULL-ended names list,
 * skipping opened chests and spent KururinFloor objects; Ms. Mowz uses it to sense hidden objects.
 */
MapObjectEntry* mobjNearDistCheck2(f32 x, f32 y, f32 z, f32 minMagnitude, char** names) {
    int entryCount;
    Vec pos;
    Vec dist;
    Vec _pos;
    Vec unusedVec;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();
    MapObjectEntry* ret;
    int i;
    float mag;
    char** animName;

    entryCount = wp->count;
    entry = wp->entries;
    ret = NULL;

#if VERSION >= VERSION_JP
    unusedVec = (Vec){0.0f, 0.0f, 0.0f};
#endif
    _pos = (Vec){0.0f, 0.0f, 0.0f};
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
    pos = _pos;

    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & MOBJ_FLAG_USED) == 0)
            continue;

        animName = names;
        while (*animName != NULL) {
            if (strcmp(entry->animName, *animName) == 0) {
                if (strcmp(entry->animName, "MOBJ_TreasureBox") == 0 ||
                    strcmp(entry->animName, "MOBJ_BigTreasureBox") == 0 ||
                    strcmp(entry->animName, "MOBJ_GrayTreasureBox") == 0 ||
                    strcmp(entry->animName, "MOBJ_BlackTreasureBox") == 0) {
                    if (mobjCheckItemboxOpen(entry) != 1) {
                        animName++;
                        continue;
                    }
                } else if (strcmp(entry->animName, kururinName) == 0) {
                    if (mobjCheckKururingFloorItem(entry) != 2) {
                        animName++;
                        continue;
                    }
                }

                VECSubtract(&entry->position, &pos, &dist);
                mag = VECMag(&dist);
                if (mag < minMagnitude) {
                    minMagnitude = mag;
                    ret = entry;
                    break;
                }
                break;
            }
            animName++;
        }
    }

    return ret;
}

const char kururinName[] = "MOBJ_KururinFloor";

#if VERSION <= VERSION_DEMO_US
/**
 * For a MOBJ_KururinFloor object returns 2 while its item is still there to find,
 * 1 once its item is out or its flag is set, and 0 for any other object. The demo keeps it as a real function.
 */
int mobjCheckKururingFloorItem(MapObjectEntry* entry) { // was always inlined in retail but not in demo
#else
/**
 * For a MOBJ_KururinFloor object returns 2 while its item is still there to find,
 * 1 once its item is out or its flag is set, and 0 for any other object. The demo keeps it as a real function.
 */
static inline int mobjCheckKururingFloorItem(MapObjectEntry* entry) { // was always inlined in retail but not in demo
#endif
    if (!strcmp(entry->animName, kururinName)) {
        ItemEntry* item = itemNameToPtr(entry->name);
        if ((item != NULL && (item->flags & ITEM_FLAG_USED) && evtGetValue(0, entry->flagVar) == 0))
            return 1;
        else if ((evtGetValue(0, entry->flagVar) != 0))
            return 1;
        else
            return 2;
    } else {
        return 0;
    }
}

#if VERSION >= VERSION_JP
// FAKE: retail stand-in for the stripped fall function (see the demo one above): its 0.0f, 10.0f, 1.0f,
// -1.0f and -0.5f open the .sdata2 pool in the target order. Dead-stripped at link.
void mobjStrippedFallPool(MapObjectEntry* entry) {
    entry->velocity.y = 0.0f;
    entry->position.y = 10.0f;
    entry->position.x = 1.0f;
    entry->position.z = -1.0f;
    entry->velocity.x = -0.5f;
}
#endif
