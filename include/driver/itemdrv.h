#pragma once

#include "driver/effdrv.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>

typedef struct ItemEntry {
	u16 flags; //0x0
	u16 field_0x2; //0x2, entry type
	s32 itemId; //0x4
	s32 evtId; //0x8, TODO: better name?
	char name[0x10]; //0xC
	EffectEntry* effect; //0x1C
	s32 field_0x20; //0x20
	u16 mode; //0x24
	u16 field_0x26; //0x26
	s32 winId[3]; //0x28
	u8 field_0x34[0x38 - 0x34]; //0x34
	u32 flags2; //0x38
	Vec position; //0x3C
	f32 scale; //0x48
	u8 alpha; //0x4C, TODO: "icon_alpha"?
	u8 field_0x4D[0x50 - 0x4D]; //0x4D
	f32 speed; //0x50
	s32 direction; //0x54
	f32 velocityY; //0x58
	u8 field_0x5C[0x60 - 0x5C]; //0x5C
	s64 airTime; //0x60
	OSTime field_0x68; //0x68
	OSTime field_0x70; //0x70
	s64 timer; //0x78
	f32 field_0x80; //0x80, bounce factor
	f32 field_0x84; //0x84, gravity scale
	s32 field_0x88; //0x88, max bounces
	s32 field_0x8C; //0x8C, bounce count
	s32 field_0x90; //0x90
	f32 field_0x94; //0x94
} ItemEntry;

typedef struct ItemWork {
	s32 count; //0x0
	ItemEntry* entries; //0x4
	u32 currId; //0x8, next available itemId
	EffectEntry* effect; //0xC
	struct WinMgrSelect* select; //0x10
	struct EventEntry* lectureEvt; //0x14
	s32 msgWindowId; //0x18
} ItemWork;

void itemInit(void);
void itemReInit(void);
void itemMain(void);
ItemEntry* itemNameToPtr(char*);
