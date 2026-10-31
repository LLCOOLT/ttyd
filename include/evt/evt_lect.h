#pragma once

// Types shared by the per-area lecture (tutorial) scripts, rels/<area>/src/event/evt_lect_<area>.c.
// Each copy keeps its own two on-screen button icons, `static LectButton lbtn[2]`.

#include <dolphin/mtx.h>
#include <dolphin/types.h>

// Where a lecture button icon is drawn.
typedef struct LectButtonDisp {
    s32 dispFlags; // 0x0, cleared with the button and never read
    Vec pos;       // 0x4, screen position of the icon (CAMERA_2D)
} LectButtonDisp;

// LectButton.flags
#define LECT_BUTTON_FLAG_HIDDEN 0x1 // not drawn; set when the button reaches seq 4

// One lecture button icon.
// seq: 0 = initialise (icon ICON_068), 1 = idle, 2 = fade in, 3 = fade out, 4 = finished (hidden).
typedef struct LectButton {
    u8 flags;               // 0x0, LECT_BUTTON_FLAG_*
    u8 seq;                 // 0x1
    u8 pad_2[0x8 - 0x2];    // 0x2
    LectButtonDisp disp;    // 0x8
    u8 pad_18[0x40 - 0x18]; // 0x18
    s16 iconId;             // 0x40, IconType
    s16 alpha;              // 0x42, 0-255, stepped by 7 while fading
} LectButton;
