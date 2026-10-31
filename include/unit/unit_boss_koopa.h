#pragma once

// Koopa (Bowser) boss: types shared between the las battle and the tou2 (Glitz Pit) copy.

#include <dolphin/mtx.h>
#include <dolphin/types.h>

// An icon thrown in an arc from start to end (event->userdatap[0], BattleAlloc'd).
typedef struct IconJumpWork {
    Vec start;                   // 0x00
    Vec pos;                     // 0x0C
    Vec end;                     // 0x18
    s32 frames;                  // 0x24, frames left
    f32 speed;                   // 0x28, horizontal speed per frame
    f32 gravity;                 // 0x2C
    f32 vy;                      // 0x30
    u8 reserved_34[0x7C - 0x34]; // 0x34, never accessed (keeps the 0x7C-byte BattleAlloc)
} IconJumpWork;
