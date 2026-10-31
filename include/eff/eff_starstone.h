// Crystal Star effect: entry (effStarStoneEntry), draw function (effStarStoneDraw), flags (StarStoneFlags)
// and per-effect work data (EffStarStoneWork).
#pragma once

#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include "dolphin/types.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

// EffStarStoneWork.flags
typedef enum StarStoneFlags {
    STARSTONE_FLAG_DROPPED = 0x1,      // set when dropped (state 1): from then on list 0 of each half is drawn too
    STARSTONE_FLAG_NO_DUST = 0x2,      // type >= 7 at entry: no snow dust, sparkles or shadow
    STARSTONE_FLAG_SHINE_SFX = 0x4,    // play the shine loop (off in battle and for type >= 7)
    STARSTONE_FLAG_SFX_ON = 0x8,       // the shine loop is playing (sfx holds its id)
    STARSTONE_FLAG_NO_JUMP_SFX = 0x10, // no bounce sound when it lands
    STARSTONE_FLAG_NO_DRAW = 0x20,     // the caller draws it (effStarStoneDraw)
} StarStoneFlags;

typedef struct EffStarStoneWork {
    s32 type;          // 0x0, 0-6 (entry takes it modulo 7)
    u16 flags;         // 0x4, StarStoneFlags
    Vec position;      // 0x8
    f32 scale;         // 0x14
    f32 spinY;         // 0x18, degrees, applied last; eases to -90 while the halves fall apart
    f32 rotY;          // 0x1C, degrees (stone_ry)
    f32 tiltZ;         // 0x20, degrees; eases to 90 while the halves fall apart
    f32 texScrollU;    // 0x24, shine texture scroll
    f32 texScrollV;    // 0x28
    s32 timer;         // 0x2C, 0-59
    GXColor color;     // 0x30, edge colour (edge_color[type])
    EffectEntry* dust; // 0x34, snow dust under the stone
    s32 cam;           // 0x38, camera id (4 unless the caller changes it)
    s32 state;         // 0x3C, 0 idle; set 1 to drop it: 2-5 bounce and split
    f32 gravity;       // 0x40
    f32 velY;          // 0x44
    f32 half1X;        // 0x48, offset of the first half
    f32 half1Z;        // 0x4C
    f32 half2X;        // 0x50, offset of the second half
    f32 half2Z;        // 0x54
    f32 angle;         // 0x58, set to 90 at entry; never read
    u8 r, g, b, a;     // 0x5C
    s32 sfx;           // 0x60, shine loop sound id
} EffStarStoneWork;

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// Draws the stone into the given camera, for callers that set STARSTONE_FLAG_NO_DRAW and draw it themselves.
void effStarStoneDraw(CameraId cameraId, EffectEntry* effect);
