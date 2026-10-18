#pragma once

#include "driver/imgdrv.h"
#include "sdk/texPalette.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef void (*OffscreenCallback)(CameraId cameraId, void* param);

typedef enum FadeType {
	FADE_IN_BLACK = 9,
	FADE_OUT_BLACK = 10,






	FADE_OUT_WHITE = 17,
	FADE_IN_WHITE2 = 18,





	TITLE_SCREEN_CURTAIN_LEAVE_GRADUAL2 = 39,

	MARIO_HEAD_FADE_IN = 52,
	MARIO_HEAD_FADE_OUT = 53,
} FadeType;

typedef struct FadeEntry {
	u16 flags; //0x0, 4 = use virtual pos
	u8 pad_2[2]; //0x2
	FadeType type; //0x4
	s32 state; //0x8, step within the fade type
	u8 field_0xC[0x10 - 0xC]; //0xC
	s32 field_0x10; //0x10
	s32 field_0x14; //0x14
	GXColor color; //0x18
	f32 fadeSpotX; //0x1C
	f32 fadeSpotY; //0x20
	f32 progress; //0x24, 0..1 (1 - elapsed/duration when fading in)
	f32 field_0x28; //0x28
	union {
		u8 field_0x2C[0x5C - 0x2C]; //0x2C
		Mtx texMtx; //0x2C
	};
	f32 elapsed; //0x5C, ms, +16.67 per frame
	const char* animFile; //0x60, e.g. "OFF_d_dokan_down"
	const char* animName; //0x64, e.g. "A_1"
	s32 imageType; //0x68
	s32 poseId; //0x6C, animPoseEntry handle, -1 = none
	s32 paperPoseId; //0x70, animPaperPoseEntry handle, -1 = none
	union {
		u8 field_0x74[0x78 - 0x74]; //0x74
		GXColor animColor; //0x74
	};
	f32 animOffsetX; //0x78
	f32 animOffsetY; //0x7C
	Vec VirtualPos; //0x80
	ImageEntry* image; //0x8C
	f32 field_0x90; //0x90
	s32 field_0x94; //0x94
	s32 field_0x98; //0x98, sfx id
	OffscreenCallback callback; //0x9C
	void* offparam; //0xA0
	u32 delayFrames; //0xA4, frames to wait before the fade advances
} FadeEntry;

typedef struct FadeWork {
	u16 flags; //0x0
	u8 pad_2[2]; //0x2
	u32 field_0x4; //0x4
	FadeEntry entries[5]; //0x8
	s32 lastEntryId; //0x350, entry index used by the last fadeEntry
	f32 softness; //0x354, 0 after fadeTecSoftOn, 1 after fadeTecSoftOff
	TEXPalette* texture; //0x358
	BOOL loaded; //0x35C
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
