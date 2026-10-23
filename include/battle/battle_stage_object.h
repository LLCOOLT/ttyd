#pragma once

#include <dolphin/mtx.h>
#include "evt/evt_cmd.h"

typedef struct BattleStageObjectData {
	char* name; //0x0
	u16 mSpawnSpecialUnitType; //0x4
	u16 mLayer; //0x8
	Vec mPosition; //0xC
	u8 mNumFramesToStartFalling; //0x14
	u8 mNumFramesToFall; //0x15
	u8 pad_16[2]; //0x16, TODO remove cuz compiler auto-pads
} BattleStageObjectData;

typedef struct BattleStageObject {
	s32 id; //0x0
	Vec mPosition; //0x4
	Vec positionOffset; //0x10, added to mPosition for mapObjTranslate
	Vec mRotation; //0x1C
	Vec positionOffset2; //0x28, second offset (btlevtcmd stage-object position)
	Vec prevPosition; //0x34, change detection
	Vec prevPositionOffset; //0x40
	Vec prevRotation; //0x4C
	Vec prevPositionOffset2; //0x58
	BattleStageObjectData* data; //0x64
	u32 mFlags; //0x68
	u32 mBattleUnitIdx; //0x6C
	u8 mNumFramesToStartFalling; //0x70
	u8 mNumFramesFalling; //0x71
	u8 field_0x72; //0x72
	u8 mShakePeriodLength; //0x73
	u8 mShakePeriodPosition; //0x74
	u8 field_0x75[3]; //0x75
	f32 mShakeAngle; //0x78
} BattleStageObject;

BattleStageObject* BattleGetObjectPtr(s32 id);
BattleStageObject* BattleSearchObjectPtr(const char* name);

void BattleStageObjectMain(void);





USER_FUNC(_set_mobj_shake_init);


void BattleStageObjectInit(void);

extern s32 _close_wall_event[];
extern s32 _entry_switch_data[];
extern s32 _entry_tree_data[];
extern s32 _fall_frame_event[];
extern s32 _nozzle_turn_event[];
extern s32 _nozzle_work_event_0[];
extern s32 _nozzle_work_event_1[];
extern s32 _nozzle_work_event_core[];
extern s32 _object_fall_event[];
extern BattleStageObjectData _object_nozzle_data[];
extern BattleStageObjectData _object_spot_light_data[];
extern s32 _object_turn_event_A1[];
extern s32 _object_turn_event_A2[];
extern s32 _object_turn_event_B[];
extern s32 _object_turn_event_core[];
extern BattleStageObjectData _object_wall_data;
extern void* jumptable_80374848[];
