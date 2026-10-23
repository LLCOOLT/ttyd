#pragma once

#include "driver/camdrv.h"
#include "memory.h"
#include <dolphin/mtx.h>

typedef struct ImageShadow {
	s32 flags; //0x0
	u16 x; //0x4
	u16 y; //0x6
	u8 field_0x8[0x10 - 0x8]; //0x8
	s32 field_0x10; //0x10
	s32 field_0x14; //0x14
	s32 field_0x18; //0x18
	u8 field_0x1C[0x3C - 0x1C]; //0x1C
	smartEntry* data; //0x3C
	s32 field_0x40; //0x40, TODO: "hasData" or smth?
} ImageShadow;

typedef struct ImageEntry {
	ImageShadow shadows[3]; //0x0
	u32 flags; //0xCC
	s32 type; //0xD0
	char name[16]; //0xD4
	u16 width; //0xE4
	u16 height; //0xE6
	f32 offsetX; //0xE8, screen offset (evt_img_set_position)
	f32 offsetY; //0xEC
	Vec point; //0xF0, virtual point
	f32 order; //0xFC
	s32 shadowId; //0x100
	s32 poseId; //0x104
	s32 animName; //0x108, const char* anim to play, 0 = none
	u8 field_0x10C[0x110 - 0x10C]; //0x10C
	OSTime animTime; //0x110, animTimeGetTime() at anim start
	f32 loopTimes; //0x118, animPoseGetLoopTimes result
	f32 offsetZ; //0x11C
	Mtx mtx; //0x120, extra transform
	CameraId camId; //0x150
	s32 dispCamId; //0x154, camera drawn on (default 4)
} ImageEntry;

typedef struct ImageWork {
	s32 count; //0x0
	ImageEntry* entries; //0x4
} ImageWork;

void imgInit(void);
void imgAutoRelease(s32 type);
s32 imgEntry(const char* name, s32 type);
void imgMain(void);
ImageEntry* imgNameToPtr(const char* name, s32 type);
void imgFreeCapture(ImageEntry* entry, s32 shadowId);
void imgSetVirtualPoint(ImageEntry* entry, const Vec* point);
void imgClearVirtualPoint(ImageEntry* entry);
void imgRelease(ImageEntry* entry, s32 type);
void imgSetShadow(ImageEntry* entry, s32 shadowId);
