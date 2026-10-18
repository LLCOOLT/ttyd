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
	f32 stageSizeX; //0xB24, btlevtcmd_GetStageSize (init 290)
	f32 stageSizeY; //0xB28 (init 200)
	f32 stageSizeZ; //0xB2C (init 90)
	f32 audienceSizeX; //0xB30, btlevtcmd_GetStageAudienceAreaSize (init = stageSizeX)
	f32 audienceSizeY; //0xB34, also the floor height past stageSizeZ (init -50)
	f32 audienceSizeZ; //0xB38 (init 200)
} BattleStage;

BattleStage* BattleStageGetPtr(void);



void BattleStageInit(void);
void BattleStageMain(void);
void BattleStageEnd(void);
