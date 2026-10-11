#pragma once

#include <dolphin/types.h>
#include "battle/battle_stage_object.h"
#include "battle/battle_database_common.h"

typedef struct BattleSpotEntry {
	u16 flags; // 0x0
	u8 field_0x2[0x4 - 0x2]; // 0x2
	Vec field_4; // 0x4
	Vec field_10; // 0x10
	Vec field_1C; // 0x1C
	s32 field_28; // 0x28, unknown, unused and set by an sbss2 var, TODO?
} BattleSpotEntry;

typedef struct BattleSpotWork {
	s32 count; //0x0
	BattleSpotEntry* entries; //0x4
	BOOL skipRender; //0x8
} BattleSpotWork;

typedef struct BattleStageData {
	char* mGlobalStageDataDir; //0x0
	char* mSpecificStageDataDir; //0x4
	u32 mNumObjects; //0x8
	BattleStageObjectData* mObjects; //0xC, TODO extern?
	BattleWeapon bgAWeapon; //0x10, background A1/A2 falling
	BattleWeapon bgBWeapon; //0xD0, background B falling
	void* initEvt; //0x190
	void* destroyBgA1Evt; //0x194
	void* destroyBgA2Evt; //0x198
	void* destroyBgBEvt; //0x19C
	void* bgA1Evt; //0x1A0
	void* bgA2Evt; //0x1A4
	void* bgBEvt; //0x1A8
	void* bgCEvt; //0x1AC
	s8 field_0x1B0; //0x1B0
	s8 disableBgA1Destroy; //0x1B1
	s8 disableBgA2Destroy; //0x1B2
	s8 disableBgBDestroy; //0x1B3
} BattleStageData;

typedef struct BattleWorkStage {
	u8 field_0x0[0xB24 - 0x0]; //0x0
	f32 field_0xB24; //0xB24, stage edge X?
	f32 field_0xB28; //0xB28, escape wall height
	u8 field_0xB2C[0xB34 - 0xB2C]; //0xB2C
	f32 field_0xB34; //0xB34, ceiling height
	u8 field_0xB38[0xB3C - 0xB38]; //0xB38
} BattleStage;

BattleStage* BattleStageGetPtr(void);



void BattleStageInit(void);
void BattleStageMain(void);
void BattleStageEnd(void);
