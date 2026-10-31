// envdrv.c: the environment driver (EnvironmentGlare and filter types): glare, blur and depth-of-field screen effects.
#pragma once

#include <dolphin/gx.h>
#include "memory.h"
#include <dolphin/mtx.h>
#include "driver/mapdrv.h"

typedef struct EnvironmentGlareTexCoord {
    f32 x; // 0x0, screen pixels, scaled by coordScale / fbWidth
    f32 y; // 0x4
} EnvironmentGlareTexCoord;

typedef struct EnvironmentGlare {
    GXBlendMode mode;                  // 0x0
    GXBlendFactor srcFactor;           // 0x4
    GXBlendFactor dstFactor;           // 0x8
    GXTevKColorSel kcolorSel0;         // 0xC
    GXTevKColorSel kcolorSel1;         // 0x10
    f32 coordScale;                    // 0x14
    s32 count;                         // 0x18, number of coords that follors
    EnvironmentGlareTexCoord coords[]; // 0x1C
} EnvironmentGlare;

// EnvironmentGlareFilter.flags
#define ENV_GLARE_FLAG_DEPTH 0x1 // depth-dependent: zscale applies (envGlareFilterZ)
typedef struct EnvironmentGlareFilter {
    u16 flags;  // 0x0
    u16 type;   // 0x2
    u16 y0;     // 0x4
    u16 y1;     // 0x6
    u16 x0;     // 0x8
    u16 x1;     // 0xA
    f32 zscale; // 0xC
} EnvironmentGlareFilter;

// EnvironmentDof.flags
#define ENV_DOF_PASS1 0x1 // pass 1 drawn (level1, radius1)
#define ENV_DOF_PASS2 0x2 // pass 2 drawn (level2, radius2)
typedef struct EnvironmentDof {
    u16 flags;    // 0x0, ENV_DOF_*
    u8 level1;    // 0x2, pass 1 konst color
    u8 level2;    // 0x3, pass 2 konst color
    f32 radius1;  // 0x4, pass 1 sample offset (4 taps)
    f32 radius2;  // 0x8, pass 2 sample offset
} EnvironmentDof; // two-pass depth-of-field style screen blur

// EnvironmentWork.flags. Bits 0x1, 0x2, 0x10000000 and 0x80000000 have no setter in this tree.
#define ENV_FLAG_CAPTURE_COLOR 0x1   // envCapture copies the frame colour to capture
#define ENV_FLAG_CAPTURE_DEPTH 0x2   // envCapture copies the frame depth to capture2
#define ENV_FLAG_BLUR_CAPTURE 0x4    // envCapture2 copies the frame to the blur texture
#define ENV_FLAG_BLUR_READY 0x8      // the blur texture holds a frame: envDisp_Blur draws it
#define ENV_FLAG_FF_LINES 0x10000000 // envDisp_FF draws its radial lines
#define ENV_FLAG_GLARE 0x20000000    // the glare filter is on (envGlareFilter)
#define ENV_FLAG_BLUR 0x40000000     // the motion blur is on (envBlurOn)
#define ENV_FLAG_DOF 0x80000000      // the depth of field is drawn (envDisp_DepthOfField)
typedef struct EnvironmentWork {
    s32 flags;                     // 0x0
    smartEntry* capture;           // 0x4
    smartEntry* capture2;          // 0x8
    GXTexObj captureObj;           // 0xC
    GXTexObj captureObj2;          // 0x2C
    void* envBlur;                 // 0x4C, see envBlurOn
    GXTexObj envBlurObj;           // 0x50
    u8 texMtxWork[0x88 - 0x70];    // 0x70, EnvTexMtxWork view (view, mtx, model, scale, rotY, rotX)
    EnvironmentDof dof;            // 0x88
    u8 pad_94[0x98 - 0x94];        // 0x94, never accessed
    u16 blurWork;                  // 0x98, start of the EnvBlurWork view; bit 1 = blur on
    u8 blurWorkRest[0xB0 - 0x9A];  // 0x9A, rest of the EnvBlurWork view
    EnvironmentGlareFilter filter; // 0xB0
    u8 yamiView[0xF0 - 0xC0];      // 0xC0, Mtx set by envSetYamiView
} EnvironmentWork;

void envInit(void);
void envReInit(void);
void envTexSetup(void);
void envMain(void);
void envBlurOn(s32 type, s32 msec);
void envBlurOff(void);
struct MapTevCallbackInfo;
void envSetWater(struct MapTevCallbackInfo* info);

void envGlareFilter(s32 type, s32 y0, s32 x0, s32 y1, s32 x1);
void envGlareFilterZ(f32 zscale);
void envAddTev(s32 type, MapTevCallbackInfo* info);
void envSetYamiView(Mtx view);
void envSetYami(MapTevCallbackInfo* info);
