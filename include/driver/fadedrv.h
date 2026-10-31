// fadedrv.c: the fade driver (FadeType, fadeEntry): screen transitions and overlays.
#pragma once

#include "driver/imgdrv.h"
#include "sdk/texPalette.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "version.h"

typedef void (*OffscreenCallback)(CameraId cameraId, void* param);

// Fade types for fadeEntry. Each type runs in one of the five FadeWork entries (slot in brackets) and draws on
// the camera named last. Animated types play an OFF_* animation group (file, animation name); the A_n/Z_n
// animation names are the game's own and their direction is not named here where the effect was not checked.
// The demo has no FADE_IN_SPOT2/FADE_OUT_SPOT2, so every later value is 2 lower there.
typedef enum FadeType {
    FADE_NONE = 0,
    FADE_IN_IRIS = 1,     // [0] fade.tpl texture 0 opening from the centre, CAMERA_FADE
    FADE_OUT_IRIS = 2,    // [0] fade.tpl texture 0 closing to the centre, CAMERA_FADE
    FADE_IN_SPOT = 3,     // [0] fade.tpl texture 1, spinning, opening on fadeSetSpotPos, CAMERA_FADE
    FADE_OUT_SPOT = 4,    // [0] as FADE_IN_SPOT, closing
    FADE_IN_SPOT_3D = 5,  // [0] as FADE_IN_SPOT on CAMERA_3D
    FADE_OUT_SPOT_3D = 6, // [0] as FADE_OUT_SPOT on CAMERA_3D
#if VERSION >= VERSION_JP
    FADE_IN_SPOT2 = 7,  // fadeEntry turns it into FADE_IN_SPOT
    FADE_OUT_SPOT2 = 8, // fadeEntry turns it into FADE_OUT_SPOT
#endif
    FADE_IN_BLACK,               // [0] colour fade from the fadeEntry colour, CAMERA_FADE
    FADE_OUT_BLACK,              // [0] colour fade to the fadeEntry colour, CAMERA_FADE
    FADE_IN_BLACK_2D,            // [0] as FADE_IN_BLACK on CAMERA_2D
    FADE_OUT_BLACK_2D,           // [0] as FADE_OUT_BLACK on CAMERA_2D
    FADE_COVER_BLACK_2D,         // [0] the fadeEntry colour at its own alpha at once, CAMERA_2D
    FADE_IN_BLACK_3D,            // [0] as FADE_IN_BLACK on CAMERA_3D
    FADE_OUT_BLACK_3D,           // [0] as FADE_OUT_BLACK on CAMERA_3D
    FADE_IN_WHITE,               // FADE_IN_BLACK in white (240, 240, 240)
    FADE_OUT_WHITE,              // FADE_OUT_BLACK in white
    FADE_IN_WHITE_2D,            // FADE_IN_BLACK_2D in white
    FADE_OUT_WHITE_2D,           // FADE_OUT_BLACK_2D in white
    FADE_IN_WHITE_3D,            // FADE_IN_BLACK_3D in white
    FADE_OUT_WHITE_3D,           // FADE_OUT_BLACK_3D in white
    FADE_CURTAIN_VERTICAL_A1,    // [1] OFF_d_maku_up_down A_1, held at the end, CAMERA_FADE
    FADE_CURTAIN_VERTICAL_A2,    // [1] OFF_d_maku_up_down A_2, darkens from half way, CAMERA_FADE
    FADE_CURTAIN_SIDES_A1_3D,    // [1] OFF_d_maku_left_right A_1, CAMERA_3D_IMAGE
    FADE_CURTAIN_SIDES_A2_3D,    // [1] OFF_d_maku_left_right A_2, released at the end, CAMERA_3D_IMAGE
    FADE_CURTAIN_SIDES_Z1_3D,    // [1] OFF_d_maku_left_right Z_1, CAMERA_3D_IMAGE
    FADE_CURTAIN_SIDES_A1,       // [1] OFF_d_maku_left_right A_1, CAMERA_FADE2
    FADE_CURTAIN_SIDES_A2,       // [1] OFF_d_maku_left_right A_2, released at the end, CAMERA_FADE2
    FADE_CURTAIN_CENTER_A1_3D,   // [1] OFF_d_maku_center A_1 (curtain-up sound), CAMERA_3D_IMAGE
    FADE_CURTAIN_CENTER_A2_3D,   // [1] OFF_d_maku_center A_2 (curtain-down sound), CAMERA_3D_IMAGE
    FADE_CURTAIN_CENTER_Z2_3D,   // [1] OFF_d_maku_center Z_2, CAMERA_3D_IMAGE
    FADE_CURTAIN_CENTER_Z1_3D,   // [1] OFF_d_maku_center Z_1, CAMERA_3D_IMAGE
    FADE_CURTAIN_LEAVE_3D,       // [1] the current curtain grows from 1x to 3x over 2 s, then is released, CAMERA_3D_IMAGE
    FADE_CURTAIN_ENTER_3D,       // [1] OFF_d_maku_center Z_2 shrinking from 3x to 1x over 3 s (1.5 s after fadeSetNarrowFast)
    FADE_CURTAIN_CENTER_A1,      // [1] as FADE_CURTAIN_CENTER_A1_3D on CAMERA_FADE
    FADE_CURTAIN_CENTER_A2,      // [1] as FADE_CURTAIN_CENTER_A2_3D on CAMERA_FADE
    FADE_CURTAIN_CENTER_Z2,      // [1] as FADE_CURTAIN_CENTER_Z2_3D on CAMERA_FADE
    FADE_CURTAIN_CENTER_Z1,      // [1] as FADE_CURTAIN_CENTER_Z1_3D on CAMERA_FADE
    FADE_CURTAIN_LEAVE,          // [1] as FADE_CURTAIN_LEAVE_3D on CAMERA_FADE
    FADE_CURTAIN_ENTER,          // [1] as FADE_CURTAIN_ENTER_3D on CAMERA_FADE
    FADE_PIPE_UP_A1,             // [2] OFF_d_dokan_up A_1 over a screen capture
    FADE_PIPE_UP_A2,             // [2] OFF_d_dokan_up A_2 (black screen while loading, released at the end)
    FADE_PIPE_DOWN_A1,           // [2] OFF_d_dokan_down A_1
    FADE_PIPE_DOWN_A2,           // [2] OFF_d_dokan_down A_2
    FADE_PIPE_LEFT_A1,           // [2] OFF_d_dokan_left A_1
    FADE_PIPE_LEFT_A2,           // [2] OFF_d_dokan_left A_2
    FADE_PIPE_RIGHT_A1,          // [2] OFF_d_dokan_right A_1
    FADE_PIPE_RIGHT_A2,          // [2] OFF_d_dokan_right A_2
    FADE_PAGE_FLIP_Z1,           // [3] OFF_d_meku Z_1 over a screen capture
    FADE_PAGE_FLIP_A1,           // [3] OFF_d_meku A_1 on the captured page (needs fadeSetOffscreenCallback)
    FADE_PAGE_FLIP_FOUR,         // [1] OFF_d_four_meku_5sec A_1, CAMERA_3D_IMAGE
    FADE_PAGE_FLIP_Z1_OFFSCREEN, // [3] FADE_PAGE_FLIP_Z1 captured through the "fOff_peron" offscreen
    FADE_PAGE_FLIP_A1_OFFSCREEN, // [3] FADE_PAGE_FLIP_A1, deletes "fOff_peron" at the end
    FADE_STORY_MARIO_A3,         // [3] OFF_f_in_out_mario A_3 (story change sound 2)
    FADE_STORY_MARIO_A1,         // [3] OFF_f_in_out_mario A_1 then A_2 (story change sound 1), camera 10
    FADE_STORY_PEACH_A3,         // [3] OFF_f_in_out_peach A_3
    FADE_STORY_PEACH_A1,         // [3] OFF_f_in_out_peach A_1 then A_2, camera 10
    FADE_STORY_BOWSER_A3,        // [3] OFF_f_in_out_kuppa A_3
    FADE_STORY_BOWSER_A1,        // [3] OFF_f_in_out_kuppa A_1 then A_2, camera 10
    FADE_STORY_MARIO_A2,         // [3] OFF_f_in_out_mario A_2 then A_2 again, camera 9
    FADE_STORY_PEACH_A2,         // [3] OFF_f_in_out_peach A_2 then A_2 again, camera 9
    FADE_STORY_BOWSER_A2,        // [3] OFF_f_in_out_kuppa A_2 then A_2 again, camera 9
    FADE_CURTAIN_SIDES_A1_TOP,   // [4] as FADE_CURTAIN_SIDES_A1 in its own slot, CAMERA_FADE2
    FADE_CURTAIN_SIDES_A2_TOP,   // [4] as FADE_CURTAIN_SIDES_A2 in its own slot, CAMERA_FADE2

} FadeType;

// FadeEntry.flags
enum FadeEntryFlags {
    FADE_ENTRY_ACTIVE = 0x1,      // set by fadeEntry; fadeMain skips entries without it
    FADE_ENTRY_FINISHED = 0x2,    // the fade has reached its end (fadeIsFinish)
    FADE_ENTRY_VIRTUAL_POS = 0x4, // draw at VirtualPos (fadeSetAnimVirtualPos)
    FADE_ENTRY_FAST = 0x8,        // fadeSetNarrowFast: the curtain zoom takes 90 frames instead of 180
};

// FadeWork.flags
enum FadeWorkFlags {
    FADE_WORK_TEC_SOFT_IN = 0x10,    // the tec overlay is easing in (softness 0 -> 1)
    FADE_WORK_TEC_SOFT_OUT = 0x20,   // the tec overlay is easing out (softness 1 -> 0), then the tec flags clear
    FADE_WORK_TEC = 0x1000,          // disp_tec draws the dark overlay (fadeTecOn)
    FADE_WORK_SOFT_FOCUS = 0x2000,   // disp_tec draws the light overlay (fadeSoftFocusOn)
    FADE_WORK_WHITE_OUT = 0x4000,    // fill the 3D camera with white (fadeWhiteOutOn)
    FADE_WORK_BLACK_SCREEN = 0x8000, // a pipe fade's animation is still loading: cover the screen in black
};

typedef struct FadeEntry {
    u16 flags;                  // 0x0, FadeEntryFlags
    u8 pad_2[2];                // 0x2
    FadeType type;              // 0x4
    s32 state;                  // 0x8, step within the fade type
    u8 pad_0C[0x10 - 0xC];      // 0xC, never accessed
    s64 duration;               // 0x10, ms
    GXColor color;              // 0x18
    f32 fadeSpotX;              // 0x1C
    f32 fadeSpotY;              // 0x20
    f32 progress;               // 0x24, 0..1 (1 - elapsed/duration when fading in)
    f32 rotation;               // 0x28, degrees (z rotation of the fade texture)
    Mtx texMtx;                 // 0x2C, built in the fade draw (entries[0] only), loaded as GX_TEXMTX0
    f32 elapsed;                // 0x5C, ms, +16.67 per frame
    const char* animFile;       // 0x60, e.g. "OFF_d_dokan_down"
    const char* animName;       // 0x64, e.g. "A_1"
    s32 imageType;              // 0x68
    s32 poseId;                 // 0x6C, animPoseEntry handle, -1 = none
    s32 paperPoseId;            // 0x70, animPaperPoseEntry handle, -1 = none
    GXColor animColor;          // 0x74
    f32 animOffsetX;            // 0x78
    f32 animOffsetY;            // 0x7C
    Vec VirtualPos;             // 0x80
    ImageEntry* image;          // 0x8C
    f32 scale;                  // 0x90, fade texture scale
    s32 scaleTimer;             // 0x94, frames into the scale interpolation
    s32 sfxId;                  // 0x98, SFX started by the fade, psndSFXOff on finish
    OffscreenCallback callback; // 0x9C
    void* offparam;             // 0xA0
    u32 delayFrames;            // 0xA4, frames to wait before the fade advances
} FadeEntry;

typedef struct FadeWork {
    u16 flags;            // 0x0, FadeWorkFlags
    u8 pad_2[2];          // 0x2
    u32 pad_04;           // 0x4, never accessed
    FadeEntry entries[5]; // 0x8
    s32 lastEntryId;      // 0x350, entry index used by the last fadeEntry
    f32 softness;         // 0x354, 0 after fadeTecSoftOn, 1 after fadeTecSoftOff
    TEXPalette* texture;  // 0x358
    BOOL loaded;          // 0x35C
} FadeWork;

void fadeInit(void);
void fadeTexSetup(void);
void fadeEntry(s32 type, s32 duration, GXColor color);
void fadeTecOn(void);
void fadeTecOff(void);
void fadeTecSoftOn(void);
void fadeTecSoftOff(void);
void fadeSoftFocusOn(void);
void fadeSoftFocusOff(void);
void fadeWhiteOutOn(void);
void fadeWhiteOutOff(void);
void fadeSetSpotPos(f32 x, f32 y);
void fadeSetAnimOfsPos(f32 x, f32 y);
void fadeSetOffscreenCallback(OffscreenCallback callback, void* param);
void fadeMain(void);
BOOL fadeIsFinish(void);
void fadeReset(s32 id);
TEXPalette* fadeGetTpl(void);
void fadeSetNarrowFast(void);
void fadeSetAnimVirtualPos(f32 x, f32 y, f32 z);

#if VERSION >= VERSION_US
extern const f32 fadeConstOne;
#endif
