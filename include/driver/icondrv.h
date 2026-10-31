// icondrv.c: the icon driver (IconEntry flags, icon.bin layout, iconEntry/iconDispGx): the button and item icons drawn on screen.
#pragma once

/*
icon.bin structure:
s16 numEntries
s16 entryOffset[numEntries]
s16 IconBinEntry[6][numEntries] (?, width override? height override? numImages, tplId, iconDelay?)
2 extra bytes for some reason
*/

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "version.h"

#define numBinEntries 0x218

typedef struct IconBinaryEntry {
    u16 type;       // 0x0, 1 if animated
    u16 width;      // 0x2, overrides tpl size
    u16 height;     // 0x4, overrides tpl size
    u16 numIcons;   // 0x6, for simple anims like button press
    u16 tplId;      // 0x8, for tpl lookup
    u16 frameDelay; // 0xA, if animated, number of frames until next
} IconBinaryEntry;

typedef struct IconBinary {
    u16 count;                           // 0x0, numBinEntries
    u16 offset[numBinEntries];           // 0x2
    IconBinaryEntry data[numBinEntries]; // 0x432
} IconBinary;

// IconEntry flags (the same in every version; the version-dependent ones follow)
#define ICON_FLAG_USED 0x1
#define ICON_FLAG_HIDDEN 0x2         // not drawn (iconMain skips the display entry)
#define ICON_FLAG_GRAYSCALE 0x20     // drawn desaturated (luminance through TEV swap tables), then tinted by the entry colour;
                                     // also accepted in the iconDispGx* flags argument
#define ICON_FLAG_ANIMATED 0x1000    // the icon has several frames; iconMain steps them
#define ICON_FLAG_PENDING_BIN 0x2000 // made before icon.bin had loaded; iconMain finishes the set-up

// IconEntry flags that the demo numbers differently
#if VERSION <= VERSION_DEMO_US
#define ICON_FLAG_2D 0x4
#define ICON_FLAG_FLIP_X 0x8
#define ICON_FLAG_FLIP_Y 0x10
#define ICON_FLAG_EFFECT_A 0x40
#define ICON_FLAG_NO_MAP_BLEND 0x80
#define ICON_FLAG_EFFECT_B 0x100
#define ICON_FLAG_CULL_BACK 0x200
#define ICON_FLAG_CULL_FRONT 0x400
#else
#define ICON_FLAG_FLIP_X 0x4
#define ICON_FLAG_FLIP_Y 0x8
#define ICON_FLAG_2D 0x10
#define ICON_FLAG_NO_MAP_BLEND 0x40 // the map's blend colour is not applied
#define ICON_FLAG_EFFECT_A 0x100    // drawn by the 3deff_A camera
#define ICON_FLAG_EFFECT_B 0x200    // drawn by the 3deff_B camera
#define ICON_FLAG_CULL_BACK 0x400
#define ICON_FLAG_CULL_FRONT 0x800
#endif
// Set on field item icons (itemdrv): the map's blend colour is not applied. The demo has it as ICON_FLAG_NO_MAP_BLEND;
// the later versions test it beside their own ICON_FLAG_NO_MAP_BLEND.
#define ICON_FLAG_ITEM_NO_BLEND 0x80

typedef struct IconEntry {
    union {
        s16 flags;  // 0x0
        u16 uflags; // 0x0, unsigned view (icondrv uses lhz)
    };
    u8 pad_02;      // 0x2, never accessed
    Vec position;   // 0x4
    f32 scale;      // 0x10
    GXColor color;  // 0x14
    char name[16];  // 0x18
    u16 iconId;     // 0x28
    u16 width;      // 0x2A
    u16 height;     // 0x2C
    u16 numIcons;   // 0x2E
    u16 currIcon;   // 0x30, if animated, currently displayed icon (starts at 0)
    u16 tplId;      // 0x32
    u16 frameDelay; // 0x34
    u8 pad_36[2];   // 0x36, never accessed
} IconEntry;

typedef struct IconWork {
    s32 count;          // 0x0
    IconEntry* entries; // 0x4
} IconWork;

void iconInit(void);
void iconTexSetup(void);
void iconReInit(void);
void iconMain(void);
void iconEntry(const char* name, u16 iconId);
void iconEntry2D(const char* name, s16 iconId);
void iconDelete(const char* name);
void iconChange(const char* name, u16 iconId);
// iconDispGx flag bits: drawn with the 2D camera, mirrored in x. The demo's 2D bit is 4, with the flips after it
// (x 8, y 0x10); retail moved the flips to 4 and 8 and the 2D bit to 0x10.
#if VERSION <= VERSION_DEMO_US
#define ICON_DISP_2D 4
#define ICON_DISP_FLIP_X 8
#else
#define ICON_DISP_2D 0x10
#define ICON_DISP_FLIP_X 4
#endif

void iconDispGxAlpha(Vec* position, s16 flags, u16 iconId, u8 alpha, f32 scale);
void iconDispGx(Vec* position, s16 flags, u16 iconId, f32 scale);
void iconDispGx2(Mtx mtx, s16 flags, u16 iconId);
void iconDispGxCol(Mtx pos, s16 flags, u16 iconId, GXColor color);
#if VERSION >= VERSION_US
void iconGetTexObj(GXTexObj* texObj, s32 iconId);
#else
void iconGetTexObj(GXTexObj* texObj, s16 iconId);
#endif
void iconGetWidthHeight(u16* width, u16* height, s16 iconId);
#if VERSION >= VERSION_US
void iconGetWidthHight(u16* width, u16* height, s32 iconId);
#else
void iconGetWidthHight(u16* width, u16* height, s16 iconId);
#endif
IconEntry* iconNameToPtr(const char* name);
void iconSetPos(const char* name, f32 x, f32 y, f32 z);
void iconFlagOn(const char* name, s16 flags);
void iconFlagOff(const char* name, s16 mask);
void iconSetScale(const char* name, f32 scale);
void iconSetAlpha(const char* name, u8 alpha);
s32 iconNumberDispGx(Mtx mtx, s32 number, BOOL small, GXColor color);
s32 iconNumberDispGx3D(Mtx mtx, s32 number, BOOL small, GXColor color);
