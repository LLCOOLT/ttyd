// Camera that circles a target ("kaiten", rotation): the cam_kaiten_* functions that gor_00, tik_05 and
// win_06 each carry.
#pragma once

#include <dolphin/mtx.h>
#include <dolphin/types.h>

// A camera position on the circle around target (ckp0 = start, ckp1 = end, ckpw = current).
typedef struct KaitenParam {
    Vec pos;    // 0x00, camera position
    Vec target; // 0x0C, camera look-at, centre of the circle
    f32 angle;  // 0x18, degrees around target in the xz plane
    f32 dist;   // 0x1C, xz distance from target
} KaitenParam;
