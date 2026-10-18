// FAKE: whole-unit ASM-STOPGAP (C3b 2026-10-18): asm_inline.py + C3b aifix/rodatagen, .data/.sdata tail pads declared, force_active. C kept under NONMATCHING. See docs/FAKES.md.
#include "battle/battle_stage_object.h"
#include "battle/battle.h"
#include "battle/battle_audience.h"
#include "battle/battle_damage.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_unit.h"
#include "battle/battle_unit_event.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/mapdrv.h"
#include "driver/msgdrv.h"
#include "driver/npcdrv.h"
#include "driver/windowdrv.h"
#include "eff/eff_nice.h"
#include "eff/n64/eff_confetti_n64.h"
#include "eff/n64/eff_kemuri1_n64.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "mario/mario_pouch.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#pragma force_active on
__declspec(section ".rodata") const u32 vec3_802f3ac8[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3ad4[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3ae0[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3aec[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3af8[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b04[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b10[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b1c[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b28[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b34[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b40[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b4c[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b58[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b64[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b70[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 vec3_802f3b7c[3] = {0x4479C000, 0x4479C000, 0x4479C000};
__declspec(section ".rodata") const u32 str_802F3B88[3] = {0x6E6F7A7A, 0x6C655F6C, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3B94[3] = {0x6E6F7A7A, 0x6C655F63, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3BA0[3] = {0x6E6F7A7A, 0x6C655F72, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3BAC[3] = {0x65736361, 0x70655F77, 0x616C6C00};
__declspec(section ".rodata") const u32 str_802F3BB8[3] = {0x73706F74, 0x6C696768, 0x74000000};
__declspec(section ".rodata") const u32 vec3_802f3bc4[3] = {0x00000000, 0x00000000, 0xC2C80000};
__declspec(section ".rodata") const u32 vec3_802f3bd0[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3BDC[7] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F4441, 0x4D414745, 0x5F545542, 0x31000000};
__declspec(section ".rodata") const u32 str_802F3BF8[8] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F4441, 0x4D414745, 0x5F4E4F52, 0x4D414C31, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3C18[5] = {0x5346585F, 0x52455354, 0x5F434F4E, 0x44495449, 0x4F4E3100};
__declspec(section ".rodata") const u32 gap_rodata_164[1] = {0x00000000};
__declspec(section ".rodata") const u32 double_to_int_802f3c30[2] = {0x43300000, 0x80000000};
__declspec(section ".rodata") const u32 str_802F3C38[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F534D, 0x4F4B4531, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3C50[5] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F4649, 0x52453100};
__declspec(section ".rodata") const u32 str_802F3C64[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F4452, 0x59494345, 0x31000000};
__declspec(section ".rodata") const u32 str_802F3C7C[2] = {0x69665F62, 0x6F647900};
__declspec(section ".rodata") const u32 str_802F3C84[7] = {0x62746C5F, 0x6D73675F, 0x65736361, 0x70655F77, 0x616C6C5F, 0x636C6F73, 0x65320000};
__declspec(section ".rodata") const u32 str_802F3CA0[3] = {0x6E5F6865, 0x61645F6C, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3CAC[3] = {0x6E5F6865, 0x61645F63, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3CB8[3] = {0x6E5F6865, 0x61645F72, 0x00000000};
__declspec(section ".rodata") const u32 str_802F3CC4[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F5345, 0x545F444F, 0x574E3100};
__declspec(section ".rodata") const u32 str_802F3CDC[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F5345, 0x545F444F, 0x574E3300};
__declspec(section ".rodata") const u32 str_802F3CF4[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F5345, 0x545F444F, 0x574E3200};
__declspec(section ".rodata") const u32 str_802F3D0C[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F5345, 0x545F4641, 0x4C4C3100};
__declspec(section ".rodata") const u32 str_802F3D24[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F5345, 0x545F4641, 0x4C4C3300};
__declspec(section ".rodata") const u32 str_802F3D3C[6] = {0x5346585F, 0x42544C5F, 0x53544147, 0x455F5345, 0x545F4641, 0x4C4C3200};
__declspec(section ".rodata") const u32 str_802F3D54[2] = {0x69665F77, 0x69726500};
__declspec(section ".rodata") const u32 gap_rodata_294[1] = {0x00000000};
__declspec(section ".sdata2") const u32 dat_8041cce8[1] = {0xFFFFFF00};
__declspec(section ".sdata2") const u32 dat_8041ccec[1] = {0xFFFFFF00};
__declspec(section ".sdata2") const u32 dat_8041ccf0[1] = {0xFFFFFF00};
__declspec(section ".sdata2") const u32 dat_8041ccf4[1] = {0xFFFFFF00};
__declspec(section ".sdata2") const u32 dat_8041ccf8[1] = {0xFFFFFFFF};
__declspec(section ".sdata2") const u32 dat_8041ccfc[1] = {0xFFFFFF00};
__declspec(section ".sdata2") const u32 float_0p1_8041cd00[1] = {0x3DCCCCCD};
__declspec(section ".sdata2") const u32 float_0_8041cd04[1] = {0x00000000};
__declspec(section ".sdata2") const u32 float_90_8041cd08[1] = {0x42B40000};
__declspec(section ".sdata2") const u32 float_270_8041cd0c[1] = {0x43870000};
__declspec(section ".sdata2") const u32 float_5_8041cd10[1] = {0x40A00000};
__declspec(section ".sdata2") const u32 float_neg300_8041cd14[1] = {0xC3960000};
__declspec(section ".sdata2") const u32 float_15_8041cd18[1] = {0x41700000};
__declspec(section ".sdata2") const u32 float_300_8041cd1c[1] = {0x43960000};
__declspec(section ".sdata2") const u32 float_85_8041cd20[1] = {0x42AA0000};
__declspec(section ".sdata2") const u32 float_50_8041cd24[1] = {0x42480000};
__declspec(section ".sdata2") const u32 float_neg50_8041cd28[1] = {0xC2480000};
__declspec(section ".sdata2") const u32 float_45_8041cd2c[1] = {0x42340000};
__declspec(section ".sdata2") const u32 float_0p75_8041cd30[1] = {0x3F400000};
__declspec(section ".sdata2") const u32 float_10_8041cd34[1] = {0x41200000};
__declspec(section ".sdata2") const u32 float_12_8041cd38[1] = {0x41400000};
__declspec(section ".sdata2") const u32 float_neg80_8041cd3c[1] = {0xC2A00000};
__declspec(section ".sdata2") const u32 float_20_8041cd40[1] = {0x41A00000};
__declspec(section ".sdata2") const u32 float_8_8041cd44[1] = {0x41000000};
__declspec(section ".sdata2") const u32 float_1_8041cd48[1] = {0x3F800000};
__declspec(section ".sdata2") const u32 float_neg45_8041cd4c[1] = {0xC2340000};
__declspec(section ".sdata2") const u32 float_neg135_8041cd50[1] = {0xC3070000};
__declspec(section ".sdata2") const u32 float_neg90_8041cd54[1] = {0xC2B40000};
__declspec(section ".sdata2") const u32 float_neg117_8041cd58[1] = {0xC2EA0000};
__declspec(section ".sdata2") const u32 float_30_8041cd5c[1] = {0x41F00000};
__declspec(section ".sdata2") const u32 float_neg120_8041cd60[1] = {0xC2F00000};
__declspec(section ".sdata2") const u32 float_900_8041cd64[1] = {0x44610000};
__declspec(section ".sdata2") const u32 str_8041CD68[1] = {0x41310000};
__declspec(section ".sdata2") const u32 str_8041CD6C[1] = {0x41320000};
__declspec(section ".sdata2") const u32 str_8041CD70[1] = {0x42000000};
__declspec(section ".sdata2") const u32 str_8041CD74[1] = {0x43000000};
__declspec(section ".sdata2") const u32 str_8041CD78[1] = {0x64656E00};
__declspec(section ".sdata2") const u32 gap_sdata2_94[1] = {0x00000000};

#pragma optimize_for_size on
#pragma dont_inline on

// raw words, so the tables don't depend on how much of BattleWeapon is named
typedef union BattleWeaponData {
	u32 raw[0xC0 / 4];
	BattleWeapon weapon;
} BattleWeaponData;

typedef struct BattleStageNozzleData {
	u8 dirRate[3][4]; //0x0, weights for each nozzle's next direction
	u8 typeRate[4]; //0xC
	BattleWeaponData weapons[4]; //0x10, per nozzle type
} BattleStageNozzleData;

typedef struct BattleStageFallObjectData {
	BattleWeaponData frameWeapon; //0x0, falling iron frame
	u8 rates[9]; //0xC0
	BattleWeaponData weapons[9]; //0xCC
} BattleStageFallObjectData;

// lives in BattleWork at 0x180C0
typedef struct BattleStageObjectWork {
	u8 field_0x0[0x4 - 0x0]; //0x0
	Vec bgRotation; //0x4
	Vec bgRotationPrev; //0x10
	u8 flags; //0x1C
	s32 bgDestroyEvtId; //0x20
	s32 bgEvtId[4]; //0x24
	BattleStageNozzleData* nozzleData; //0x34
	BattleStageFallObjectData* fallObjectData; //0x38
	BattleWeapon* nozzleWeapons[2]; //0x3C
	BattleWeapon nozzleWeaponWork[2]; //0x44
	u8 nozzleDir[3]; //0x1C4
	u8 nozzleNextDir[3]; //0x1C7
	s8 nozzleType; //0x1CA
	s32 nozzleTurnEvtId[3]; //0x1CC
	s32 nozzleWorkEvtId; //0x1D8
	s32 fogTimer; //0x1DC
	EffectEntry* fogEffect; //0x1E0
	s32 closeWallEvtId; //0x1E4
	s32 fallFrameEvtId; //0x1E8
	s32 objectFallEvtId; //0x1EC
} BattleStageObjectWork;

#define STAGE_WORK(wp) ((BattleStageObjectWork*)(wp)->field_180C0)
#define EVT_UW(evt, n) (((s32*)(evt)->userdata)[n])
#define UNIT_FIELD(unit, type, off) (*(type*)((u8*)(unit) + (off)))

extern BattleWork* _battleWorkPointer;
extern s32 weaponGetPowerDefault[];
extern BattleUnitKind unit_object_tree;
extern BattleUnitKind unit_object_switch;

void mapGrpFlagOn(const char* name, u32 flags);
void mapGrpFlagOff(const char* name, u32 flags);
void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
void mapGrpSetColor(const char* name, GXColor color);
void mapPlayAnimationLv(const char* name, s32 a, s32 b);
f32 intpl_sub(s32 type, f32 start, f32 end, s32 cur, s32 max);
f32 sinfd(f32 degrees);
f32 cosfd(f32 degrees);
void FontDrawString(f32 x, f32 y, const char* str);
BOOL BattleCheckConcluded(BattleWork* wp);
BOOL BattleWaitAllActiveEvtEnd_NoBgSetEndWait(BattleWork* wp);
void BattleAudience_Case_HaikeiSet(void);
void BattleAudience_Case_FallObject_Aud(s32 index, u8 type);
void BattleAudience_Case_FallObject_Stage(void);
EffectEntry* effNozleEntry(s32 type, f32 x, f32 y, f32 z, f32 rx, f32 ry, s32 lifetime);
EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8);
BOOL effFallCheckHit(EffectEntry* effect);
void BattleSamplingEnemy(BattleWorkWeaponTargets* targets, BattleWeapon* weapon, s32 unitId, s8 belong, u32 classFlags, u32 propFlags, s8 direction);
void BattleChoiceSamplingEnemy(BattleWorkWeaponTargets* targets, u32 flags, s32* unitId, s32* partId);
s32 BattlePreCheckDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32 flags);
BOOL BtlUnit_GetACPossibility(BattleUnit* unit);
s32 BattleActionCommandCheckDefence(BattleUnit* unit, BattleWeapon* weapon);
f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);
void btl_camera_set_mode(s32 a, s32 b);
void btl_camera_set_moveSpeedLv(s32 a, s32 b);

//local prototypes
void BattleObjectConfig(void);
void _mobj_shake_main(BattleStageObject* obj);
void _Nozzle_Change_Check(u8 index, u8* rate);
void _disp_escape_wall_message(CameraId camera, void* param);
void _nozzle_type_init(void);
f32 _get_nozzle_dir(s32 index);
s32 _get_nozzle_attack_index(u8 index);
void _rate_mix(s8* dstChance, s8* dstTime, s8* srcChance, s8* srcTime);
void _rate_mix_3(s8* dstChance, s8* dstTime, s8* dstStrength, s8* srcChance, s8* srcTime, s8* srcStrength);
void _combine_nozzle_weapon(BOOL copy, BattleWeapon* dst, BattleWeapon* src);
USER_FUNC(_object_fall_attack);
USER_FUNC(_object_fall_wait);
USER_FUNC(_nozzle_work_get_weapon_address);
USER_FUNC(_nozzle_work_attack_set);
USER_FUNC(_nozzle_work_effect);
USER_FUNC(_nozzle_work_wait);
USER_FUNC(_fall_frame_delete);
USER_FUNC(_fall_frame);
USER_FUNC(_fall_frame_wait_unit_ready);
USER_FUNC(_fall_frame_wait);
USER_FUNC(_announce_wall_message);
USER_FUNC(_nozzle_turn);
USER_FUNC(_set_mobj_shake);
USER_FUNC(_bgset_audience_bgset_access);
USER_FUNC(_bgset_audience_bgset_access);
USER_FUNC(_bgset_kemuri_effect);
USER_FUNC(_get_bgset_attack_data);
USER_FUNC(_mobj_destroy);
USER_FUNC(_mobj_set_alpha);
USER_FUNC(_set_mobj_rotate_x);

USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_GetACPossibility);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetSelectEnemy);
USER_FUNC(btlevtcmd_GetSelectNextEnemy);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_shake_h);

extern BattleWeaponData _nozzle_at_base_mario;
extern BattleWeaponData _nozzle_at_base_monster;
extern BattleStageNozzleData battle_stage_nozzle_data[];
extern BattleStageFallObjectData battle_stage_fall_object_data[];
extern BattleStageObjectData _object_nozzle_data[];
extern s32 _object_turn_event_core[];
extern s32 _fall_frame_event[];
extern s32 _nozzle_work_event_core[];
extern s32 _object_fall_event[];
extern BattleStageObjectData _object_wall_data;
extern BattleStageObjectData _object_spot_light_data[];
extern s32 _entry_tree_data[];
extern s32 _entry_switch_data[];
extern s32 _object_turn_event_A1[];
extern s32 _object_turn_event_A2[];
extern s32 _object_turn_event_B[];
extern s32 _nozzle_turn_event[];
extern s32 _close_wall_event[];
extern s32 _nozzle_work_event_0[];
extern s32 _nozzle_work_event_1[];

#ifdef NONMATCHING
BattleStageObject* BattleGetObjectPtr(s32 id) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	int i;

	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id == id) {
			return obj;
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
BattleStageObject* BattleSearchObjectPtr(const char* name) {
	BattleWork* wp = _battleWorkPointer;
	int i;
	BattleStageObject* obj;

	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id && !strcmp(obj->data->name, name)) {
			return obj;
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
void BattleStageObjectInit(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageData* stage = wp->fbatInfo->setup->stageData;
	s32 numObjects = stage->mNumObjects;
	BattleStageObjectData* data = stage->mObjects;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	s32 countA1 = 0;
	s32 countA2 = 0;
	s32 countB = 0;
	s32 countC = 0;
	BOOL hasIronFrame = FALSE;
	s32 id;
	BattleStageObject* obj;
	BattleUnit* unit;
	int i;
	int j;

	memset(wp->stageObjects, 0, sizeof(wp->stageObjects));
	switch (pouchGetPtr()->rank) {
		case 1:
		case 2:
		case 3:
			mapPlayAnimationLv("den", 1, 0);
			break;
	}
	switch (pouchGetPtr()->rank) {
		case 1:
		case 2:
		case 3:
			sw->nozzleData = &battle_stage_nozzle_data[pouchGetPtr()->rank];
			break;
		default:
			sw->nozzleData = NULL;
			break;
	}
	sw->fallObjectData = &battle_stage_fall_object_data[pouchGetPtr()->rank];
	sw->nozzleType = -1;
	sw->fogTimer = 0;
	sw->fogEffect = NULL;
	mapGrpFlagOff(mapGetWork()->entries[0].rootMapObj->joints->name, 2);
	if (mapGetMapObj("A1")) {
		mapGrpFlagOn("A1", 1);
		mapGrpFlagOff("A1", 2);
	}
	if (mapGetMapObj("A2")) {
		mapGrpFlagOn("A2", 1);
		mapGrpFlagOff("A2", 2);
	}
	if (mapGetMapObj("B")) {
		mapGrpFlagOn("B", 1);
		mapGrpFlagOff("B", 2);
	}
	if (mapGetMapObj("C")) {
		mapGrpFlagOn("C", 1);
		mapGrpFlagOff("C", 2);
	}
	mapGrpFlagOn("escape_wall", 1);

	id = 1;
	if (data) {
		for (; numObjects != 0; id++, numObjects--, data++) {
			for (i = 0; i < 32; i++) {
				obj = &wp->stageObjects[i];
				if (obj->id <= 0) {
					break;
				}
			}
			if (i >= 32) {
				break;
			}
			obj->data = data;
			obj->id = id;
			obj->mBattleUnitIdx = -1;
			switch (obj->data->mLayer) {
				case 0:
					countA1++;
					break;
				case 1:
					countA2++;
					break;
				case 2:
					countB++;
					break;
				case 3:
					countC++;
					break;
				case 6:
					hasIronFrame = TRUE;
					break;
			}
			switch (obj->data->mLayer) {
				case 0:
				case 1:
				case 6:
				case 7:
					obj->mPosition = data->mPosition;
					break;
				case 2:
				case 3:
					obj->mPosition = data->mPosition;
					break;
			}
			obj->mRotation.x = obj->mRotation.y = obj->mRotation.z = 0.0f;
			obj->prevPosition = (Vec){999.0f, 999.0f, 999.0f};
			obj->prevPositionOffset = (Vec){999.0f, 999.0f, 999.0f};
			obj->prevRotation = (Vec){999.0f, 999.0f, 999.0f};
			obj->prevPositionOffset2 = (Vec){999.0f, 999.0f, 999.0f};
			mapGrpFlagOff(obj->data->name, 1);
			switch (data->mSpawnSpecialUnitType) {
				case 0:
					unit = BtlUnit_Entry((BattleUnitSetup*)_entry_tree_data);
					unit->stageObjectId = obj->id;
					obj->mBattleUnitIdx = unit->unitId;
					BtlUnit_SetPos(unit, obj->mPosition.x, obj->mPosition.y, obj->mPosition.z);
					BtlUnit_SetHomePos(unit, obj->mPosition.x, obj->mPosition.y, obj->mPosition.z);
					break;
				case 1:
					unit = BtlUnit_Entry((BattleUnitSetup*)_entry_switch_data);
					unit->stageObjectId = obj->id;
					obj->mBattleUnitIdx = unit->unitId;
					BtlUnit_SetPos(unit, obj->mPosition.x, obj->mPosition.y, obj->mPosition.z);
					BtlUnit_SetHomePos(unit, obj->mPosition.x, obj->mPosition.y, obj->mPosition.z);
					break;
				case 2:
					break;
			}
		}
	}

	if (pouchGetPtr()->rank > 0) {
		data = _object_nozzle_data;
		for (j = 0; j < 3; j++, id++, data++) {
			for (i = 0; i < 32; i++) {
				obj = &wp->stageObjects[i];
				if (obj->id <= 0) {
					break;
				}
			}
			if (i >= 32) {
				break;
			}
			obj->data = data;
			obj->id = id;
			obj->mBattleUnitIdx = -1;
			obj->mPosition = data->mPosition;
			obj->mRotation.x = obj->mRotation.y = obj->mRotation.z = 0.0f;
			obj->prevPosition = (Vec){999.0f, 999.0f, 999.0f};
			obj->prevPositionOffset = (Vec){999.0f, 999.0f, 999.0f};
			obj->prevRotation = (Vec){999.0f, 999.0f, 999.0f};
			obj->prevPositionOffset2 = (Vec){999.0f, 999.0f, 999.0f};
			mapGrpFlagOff(obj->data->name, 1);
		}
	}

	data = &_object_wall_data;
	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id <= 0) {
			break;
		}
	}
	obj->data = data;
	obj->id = id;
	obj->mBattleUnitIdx = -1;
	obj->mPosition = data->mPosition;
	obj->mPosition.y = BattleStageGetPtr()->stageSizeY;
	obj->mRotation.x = obj->mRotation.y = obj->mRotation.z = 0.0f;
	obj->prevPosition = (Vec){999.0f, 999.0f, 999.0f};
	obj->prevPositionOffset = (Vec){999.0f, 999.0f, 999.0f};
	obj->prevRotation = (Vec){999.0f, 999.0f, 999.0f};
	obj->prevPositionOffset2 = (Vec){999.0f, 999.0f, 999.0f};
	mapGrpFlagOn(obj->data->name, 1);
	obj->mFlags |= 1;
	id++;

	j = 0;
	while (TRUE) {
		data = &_object_spot_light_data[j];
		if (!data->name) {
			break;
		}
		for (i = 0; i < 32; i++) {
			obj = &wp->stageObjects[i];
			if (obj->id <= 0) {
				break;
			}
		}
		obj->data = data;
		obj->id = id;
		obj->mBattleUnitIdx = -1;
		obj->mPosition = data->mPosition;
		obj->mRotation.x = obj->mRotation.y = obj->mRotation.z = 0.0f;
		obj->prevPosition = (Vec){999.0f, 999.0f, 999.0f};
		obj->prevPositionOffset = (Vec){999.0f, 999.0f, 999.0f};
		obj->prevRotation = (Vec){999.0f, 999.0f, 999.0f};
		obj->prevPositionOffset2 = (Vec){999.0f, 999.0f, 999.0f};
		mapGrpFlagOn(obj->data->name, 1);
		obj->mFlags |= 1;
		id++;
		j++;
	}

	if (stage->initEvt) {
		evtEntry(stage->initEvt, 10, 0);
	}
	if (countA1 && stage->bgA1Evt) {
		STAGE_WORK(wp)->bgEvtId[0] = evtEntry(stage->bgA1Evt, 10, 0)->eventId;
	}
	if (countA2 && stage->bgA2Evt) {
		STAGE_WORK(wp)->bgEvtId[1] = evtEntry(stage->bgA2Evt, 10, 0)->eventId;
	}
	if (countB && stage->bgBEvt) {
		STAGE_WORK(wp)->bgEvtId[2] = evtEntry(stage->bgBEvt, 10, 0)->eventId;
	}
	if (countC && stage->bgCEvt) {
		STAGE_WORK(wp)->bgEvtId[3] = evtEntry(stage->bgCEvt, 10, 0)->eventId;
	}
	if (!countA1) {
		STAGE_WORK(wp)->flags |= 2;
	}
	if (!countA2) {
		STAGE_WORK(wp)->flags |= 4;
	}
	if (!countB) {
		STAGE_WORK(wp)->flags |= 8;
	}
	if (stage->disableBgA1Destroy) {
		STAGE_WORK(wp)->flags |= 2;
	}
	if (stage->disableBgA2Destroy) {
		STAGE_WORK(wp)->flags |= 4;
	}
	if (stage->disableBgBDestroy) {
		STAGE_WORK(wp)->flags |= 8;
	}
	if (!hasIronFrame) {
		STAGE_WORK(wp)->flags |= 0x20;
		mapGrpFlagOn("if_body", 1);
		mapGrpFlagOn("if_wire", 1);
	}
}
#endif

#ifdef NONMATCHING
void BattleStageObjectMain(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	BattleStageObject* obj;
	BOOL changed;
	int i;

	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id <= 0) {
			continue;
		}
		changed = FALSE;
		if (obj->mPosition.x != obj->prevPosition.x || obj->mPosition.y != obj->prevPosition.y || obj->mPosition.z != obj->prevPosition.z) {
			obj->prevPosition = obj->mPosition;
			changed = TRUE;
		}
		if (obj->positionOffset.x != obj->prevPositionOffset.x || obj->positionOffset.y != obj->prevPositionOffset.y || obj->positionOffset.z != obj->prevPositionOffset.z) {
			obj->prevPositionOffset = obj->positionOffset;
			changed = TRUE;
		}
		if (obj->positionOffset2.x != obj->prevPositionOffset2.x || obj->positionOffset2.y != obj->prevPositionOffset2.y || obj->positionOffset2.z != obj->prevPositionOffset2.z) {
			obj->prevPositionOffset2 = obj->positionOffset2;
			changed = TRUE;
		}
		if (obj->mRotation.x != obj->prevRotation.x || obj->mRotation.y != obj->prevRotation.y || obj->mRotation.z != obj->prevRotation.z) {
			obj->prevRotation = obj->mRotation;
			changed = TRUE;
		}
		if (obj->mFlags & 2) {
			obj->mFlags &= ~2;
			changed = TRUE;
		}
		switch (obj->data->mLayer) {
			case 2:
				if (sw->bgRotation.x != sw->bgRotationPrev.x ||
					sw->bgRotation.y != sw->bgRotationPrev.y ||
					sw->bgRotation.z != sw->bgRotationPrev.z) {
					sw->bgRotationPrev = sw->bgRotation;
					changed = TRUE;
				}
				break;
		}
		switch (obj->data->mLayer) {
			case 0:
			case 1:
			case 4:
			case 5:
			case 6:
			case 7:
				if (changed) {
					mapObjTranslate(obj->data->name,
						obj->positionOffset2.x + (obj->mPosition.x + obj->positionOffset.x),
						obj->positionOffset2.y + (obj->mPosition.y + obj->positionOffset.y),
						obj->positionOffset2.z + (obj->mPosition.z + obj->positionOffset.z));
					mapObjRotate(obj->data->name, obj->mRotation.x, obj->mRotation.y, obj->mRotation.z);
				}
				break;
			case 2:
				if (changed) {
					mapObjTranslate(obj->data->name,
						obj->positionOffset2.x + (obj->mPosition.x + obj->positionOffset.x),
						obj->positionOffset2.y + (obj->mPosition.y + obj->positionOffset.y),
						obj->positionOffset2.z + (obj->mPosition.z + obj->positionOffset.z));
					mapObjTranslate(obj->data->name, 0.0f, -obj->positionOffset.y, 0.0f);
					mapObjRotate(obj->data->name, sw->bgRotation.x, sw->bgRotation.y, sw->bgRotation.z);
					mapObjTranslate(obj->data->name, 0.0f, obj->positionOffset.y, 0.0f);
				}
				break;
			case 3:
				if (changed) {
					mapObjTranslate(obj->data->name,
						obj->positionOffset2.x + (obj->mPosition.x + obj->positionOffset.x),
						obj->positionOffset2.y + (obj->mPosition.y + obj->positionOffset.y),
						obj->positionOffset2.z + (obj->mPosition.z + obj->positionOffset.z));
					mapObjTranslate(obj->data->name, 0.0f, -obj->mPosition.y, 0.0f);
					mapObjRotate(obj->data->name, obj->mRotation.x, obj->mRotation.y, obj->mRotation.z);
					mapObjTranslate(obj->data->name, 0.0f, obj->mPosition.y, 0.0f);
				}
				break;
		}
		if (obj->mFlags & 1) {
			if (!(mapGetMapObj(obj->data->name)->flags & 1)) {
				mapGrpFlagOn(obj->data->name, 1);
			}
		}
		else {
			if (mapGetMapObj(obj->data->name)->flags & 1) {
				mapGrpFlagOff(obj->data->name, 1);
			}
		}
	}
	BattleObjectConfig();
}
#endif

#ifdef NONMATCHING
void BattleObjectConfig(void) {
	//stubbed in retail
}
#endif

#ifdef NONMATCHING
void BattleStage_DestroyA1(void) {
	BattleWork* wp = _battleWorkPointer;
	void* evt = wp->fbatInfo->setup->stageData->destroyBgA1Evt;
	EventEntry* entry;

	evtDeleteID(STAGE_WORK(wp)->bgEvtId[0]);
	STAGE_WORK(wp)->bgEvtId[0] = 0;
	if (STAGE_WORK(wp)->bgDestroyEvtId && evtCheckID(STAGE_WORK(wp)->bgDestroyEvtId)) {
		evtDeleteID(*(s32*)(wp->field_180C0 + 0x20));
	}
	if (!evt) {
		evt = _object_turn_event_A1;
	}
	entry = evtEntry(evt, 10, 0);
	if (entry) {
		*(s32*)(wp->field_180C0 + 0x20) = entry->eventId;
	}
}
#endif

#ifdef NONMATCHING
void BattleStage_DestroyA2(void) {
	BattleWork* wp = _battleWorkPointer;
	void* evt = wp->fbatInfo->setup->stageData->destroyBgA2Evt;

	evtDeleteID(STAGE_WORK(wp)->bgEvtId[1]);
	STAGE_WORK(wp)->bgEvtId[1] = 0;
	if (!evt) {
		evt = _object_turn_event_A2;
	}
	evtEntry(evt, 10, 0);
}
#endif

#ifdef NONMATCHING
void BattleStage_DestroyB(void) {
	BattleWork* wp = _battleWorkPointer;
	void* evt = wp->fbatInfo->setup->stageData->destroyBgBEvt;
	EventEntry* entry;

	evtDeleteID(STAGE_WORK(wp)->bgEvtId[2]);
	STAGE_WORK(wp)->bgEvtId[2] = 0;
	if (STAGE_WORK(wp)->bgDestroyEvtId && evtCheckID(STAGE_WORK(wp)->bgDestroyEvtId)) {
		evtDeleteID(*(s32*)(wp->field_180C0 + 0x20));
	}
	if (!evt) {
		evt = _object_turn_event_B;
	}
	entry = evtEntry(evt, 10, 0);
	if (entry) {
		*(s32*)(wp->field_180C0 + 0x20) = entry->eventId;
	}
}
#endif

__declspec(section ".data") u64 lbl_80371490 = 0xBF8000003F800000;
__declspec(section ".data") u64 fd_battle_stage_object_negone_one_374 = 0xBF8000003F800000;
__declspec(section ".data") u64 lbl_803714A0 = 0x3F800000BF800000;
__declspec(section ".data") u64 fd_battle_stage_object_one_negone_373 = 0x3F800000BF800000;
__declspec(section ".data") u64 lbl_803714B0 = 0xBF8000003F800000;
__declspec(section ".data") u64 fd_battle_stage_object_negone_one_360 = 0xBF8000003F800000;
__declspec(section ".data") u64 lbl_803714C0 = 0x3F800000BF800000;
__declspec(section ".data") u64 fd_battle_stage_object_one_negone_359 = 0x3F800000BF800000;

BattleWeaponData _nozzle_at_base_mario = {{
	0, 0, 0, 0, 0x64000002, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0x02000070, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0x00000064, 0, 0,
}};

BattleWeaponData _nozzle_at_base_monster = {{
	0, 0, 0, 0, 0x64000002, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0x0200006F, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0x00000064, 0, 0,
}};

BattleStageNozzleData battle_stage_nozzle_data[] = {
	{
		{{0, 0, 50, 50}, {0, 50, 0, 50}, {0, 50, 50, 0}}, {100, 0, 0, 0},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
	{
		{{0, 0, 50, 50}, {0, 50, 0, 50}, {0, 50, 50, 0}}, {60, 40, 0, 0},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x02000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0x00640100, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
	{
		{{0, 0, 50, 50}, {0, 50, 0, 50}, {0, 50, 50, 0}}, {40, 30, 30, 0},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x02000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0x00640100, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000002, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x03000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
	{
		{{0, 0, 50, 50}, {0, 50, 0, 50}, {0, 50, 50, 0}}, {20, 30, 30, 20},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x02000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0x00640100, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000002, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x03000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x01000302, 0, 0, 0x000007FF, 0,
				0, 0, 0, 0x00000064, 0x03000000, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
};

BattleStageFallObjectData battle_stage_fall_object_data[] = {
	{
		{{
			0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
			0x00000001, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0x00000064, 0, 0,
		}},
		{0, 10, 0, 0, 0, 0, 0, 0, 10},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00010302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000002, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0x64000000, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0x00000100, 0x000007FF, 0x80000000,
				0x64006400, 0x64006400, 0x00640064, 0x00000064, 0x00640000, 0, 0, 0x0000009D,
				0, 0x00009D00, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000005, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00640300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000003, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00000019, 0x03000000, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
	{
		{{
			0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
			0x00000001, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0x00000064, 0, 0,
		}},
		{10, 10, 0, 0, 0, 10, 0, 0, 10},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00010302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000002, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0x64000000, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0x00000100, 0x000007FF, 0x80000000,
				0x64006400, 0x64006400, 0x00640064, 0x00000064, 0x00640000, 0, 0, 0x0000009D,
				0, 0x00009D00, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000005, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00640300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000003, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00000019, 0x03000000, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
	{
		{{
			0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
			0x00000001, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0x00000064, 0, 0,
		}},
		{10, 10, 10, 10, 10, 10, 0, 0, 10},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00010302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000002, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0x64000000, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0x00000100, 0x000007FF, 0x80000000,
				0x64006400, 0x64006400, 0x00640064, 0x00000064, 0x00640000, 0, 0, 0x0000009D,
				0, 0x00009D00, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000005, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00640300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000003, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00000019, 0x03000000, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
	{
		{{
			0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
			0x00000001, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0x00000064, 0, 0,
		}},
		{10, 10, 10, 10, 10, 10, 10, 10, 10},
		{
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00010302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00320300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000002, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0, 0x000007FF, 0x80000000,
				0x64000000, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x00000302, 0, 0x00000100, 0x000007FF, 0x80000000,
				0x64006400, 0x64006400, 0x00640064, 0x00000064, 0x00640000, 0, 0, 0x0000009D,
				0, 0x00009D00, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000005, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00640300, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000003, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x02100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0x32030000, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
			{{
				0, 0, 0, 0, 0x64000002, 0, 0, (u32)weaponGetPowerDefault,
				0x00000001, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0x01100060, 0x20000000, 0x000A0302, 0, 0, 0x000007FF, 0x80000000,
				0, 0, 0x00000019, 0x03000000, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0x00000064, 0, 0,
			}},
		},
	},
};

BattleStageObjectData _object_nozzle_data[] = {
	{(char*)str_802F3B88, 3, 4, {-120.0f, 0.0f, 90.0f}, 0, 0},
	{(char*)str_802F3B94, 3, 4, {0.0f, 0.0f, 90.0f}, 0, 0},
	{(char*)str_802F3BA0, 3, 4, {120.0f, 0.0f, 90.0f}, 0, 0},
};

EVT_BEGIN(_object_turn_event_core)
    CALL(_set_mobj_shake_init, LW(9))
    CALL(_set_mobj_shake, LW(9))
    CALL(_set_mobj_rotate_x, LW(9))
    IF_INT_NOT_EQUAL(LW(9), 1)
        CALL(evt_btl_camera_shake_h, 0, 4, 0, 30, 13)
    END_IF
    CALL(_bgset_kemuri_effect, LW(9))
    IF_INT_NOT_EQUAL(LW(9), 1)
        CALL(_bgset_audience_bgset_access)
    END_IF
    CALL(btlevtcmd_check_battleflag, LW(0), 256)
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(20)
    END_IF
    CALL(_get_bgset_attack_data, LW(9), LW(12))
    IF_INT_EQUAL(LW(12), 0)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, -5, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -5, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    SET_VALUE(LW(15), 0)
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(20)
    END_IF
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_GetACPossibility, LW(10), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            ADD(LW(15), 1)
            CALL(btlevtcmd_ResultACDefence, LW(10), LW(12))
        END_IF
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(4)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
        CASE_DEFAULT
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    LABEL(20)
    WAIT_FRAMES(50)
    SET_VALUE(LW(0), 255)
    SET_VALUE(LW(1), 51)
    LABEL(50)
    SUBTRACT(LW(0), 5)
    CALL(_mobj_set_alpha, LW(9), LW(0))
    SUBTRACT(LW(1), 1)
    IF_INT_GREATER(LW(1), 0)
        WAIT_FRAMES(1)
        GOTO(50)
    END_IF
    CALL(_mobj_destroy, LW(9))
    RETURN
EVT_END()

EVT_BEGIN(_fall_frame_event)
    CALL(_fall_frame_wait)
    CALL(_fall_frame_wait_unit_ready)
    CALL(_fall_frame, LW(12))
    CALL(btlevtcmd_GetEnemyBelong, -5, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -5, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    SET_VALUE(LW(15), 0)
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(20)
    END_IF
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_GetACPossibility, LW(10), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            ADD(LW(15), 1)
            CALL(btlevtcmd_ResultACDefence, LW(10), LW(12))
        END_IF
    END_IF
    CALL(btlevtcmd_CheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    LABEL(20)
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 20, 13)
    CALL(_fall_frame_delete)
    RETURN
EVT_END()

EVT_BEGIN(_nozzle_work_event_core)
    CALL(_nozzle_work_wait)
    CALL(_nozzle_work_effect, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(_nozzle_work_attack_set)
    CALL(_nozzle_work_get_weapon_address, 0, LW(12))
    IF_INT_EQUAL(LW(12), 0)
        GOTO(19)
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, -5, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -5, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    SET_VALUE(LW(15), 0)
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(19)
    END_IF
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_GetACPossibility, LW(10), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            ADD(LW(15), 1)
            CALL(btlevtcmd_ResultACDefence, LW(10), LW(12))
        END_IF
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(4)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
        CASE_DEFAULT
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    LABEL(19)
    CALL(_nozzle_work_get_weapon_address, 1, LW(12))
    IF_INT_EQUAL(LW(12), 0)
        GOTO(29)
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, -5, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -5, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(20)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(29)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(4)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -5, LW(10), LW(11), LW(12), 256, LW(5))
        CASE_DEFAULT
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(20)
    LABEL(29)
    RETURN
EVT_END()

EVT_BEGIN(_object_fall_event)
    CALL(_object_fall_wait)
    CALL(_object_fall_attack, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    RETURN
EVT_END()

BattleStageObjectData _object_wall_data = {(char*)str_802F3BAC, 4, 5, {-175.0f, 0.0f, 0.0f}, 0, 0};

BattleStageObjectData _object_spot_light_data[] = {
	{(char*)str_802F3BB8, 6, 7, {0.0f, 240.0f, 0.0f}, 0, 0},
	{NULL, 6, 7, {0.0f, 0.0f, 0.0f}, 0, 0},
};

s32 _entry_tree_data[] = {
	(s32)&unit_object_tree, 0x02000000, 0x04000005, 0xC47A0000, 0xC47A0000, 0xC47A0000, 0, 0,
	0, 0, 0, 0,
};

s32 _entry_switch_data[] = {
	(s32)&unit_object_switch, 0x02000000, 0x04000005, 0xC47A0000, 0xC47A0000, 0xC47A0000, 0, 0,
	0, 0, 0, 0,
};

EVT_BEGIN(_object_turn_event_A1)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(_object_turn_event_core))
    RETURN
EVT_END()

EVT_BEGIN(_object_turn_event_A2)
    SET_VALUE(LW(9), 1)
    CALL_CHILD(PTR(_object_turn_event_core))
    RETURN
EVT_END()

EVT_BEGIN(_object_turn_event_B)
    SET_VALUE(LW(9), 2)
    CALL_CHILD(PTR(_object_turn_event_core))
    RETURN
EVT_END()

EVT_BEGIN(_nozzle_turn_event)
    CALL(_nozzle_turn)
    RETURN
EVT_END()

EVT_BEGIN(_close_wall_event)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(_announce_wall_message)
    RETURN
EVT_END()

EVT_BEGIN(_nozzle_work_event_0)
    SET_VALUE(LW(10), 0)
    CALL_CHILD(PTR(_nozzle_work_event_core))
    RETURN
EVT_END()

EVT_BEGIN(_nozzle_work_event_1)
    SET_VALUE(LW(10), 1)
    CALL_CHILD(PTR(_nozzle_work_event_core))
    RETURN
EVT_END()
#ifdef NONMATCHING
USER_FUNC(_set_mobj_rotate_x) {
	const char* fall1;
	const char* fall3;
	BattleWork* wp;
	int j;
	int i;
	BOOL busy;
	const char* fall2;
	s32 layer;
	BattleStageObjectWork* sw;
	BattleStageObject* obj;

	s32* args = event->args;
	busy = FALSE;
	sw = STAGE_WORK(wp = _battleWorkPointer);
	layer = evtGetValue(event, *args++);
	if (isFirstCall) {
		switch (layer) {
			case 0:
			case 1:
				for (j = 0; j < 32; j++) {
					obj = &wp->stageObjects[j];
					if (obj->id > 0 && obj->data->mLayer == layer) {
						obj->mNumFramesToStartFalling = obj->data->mNumFramesToStartFalling;
						obj->mNumFramesFalling = 0;
					}
				}
				break;
			case 2:
				EVT_UW(event, 1) = 0;
				EVT_UW(event, 2) = 60;
				EVT_UW(event, 3) = 0;
				break;
		}
	}
	switch (layer) {
		case 0:
		case 1:
			fall1 = (char*)str_802F3D0C;
			fall3 = (char*)str_802F3D24;
			for (i = 0; i < 32; i++) {
				obj = &wp->stageObjects[i];
				if (obj->id > 0 && obj->data->mLayer == layer) {
					if (obj->mNumFramesToStartFalling) {
						obj->mNumFramesToStartFalling--;
						busy = TRUE;
						_mobj_shake_main(obj);
					}
					else {
						if (obj->mNumFramesFalling == 0) {
							if (layer == 0) {
								psndSFXOn_3D(fall1, &obj->mPosition);
							}
							else {
								psndSFXOn_3D(fall3, &obj->mPosition);
							}
						}
						obj->mNumFramesFalling++;
						obj->mRotation.x = intpl_sub(2, obj->mShakeAngle, 90.0f, obj->mNumFramesFalling, obj->data->mNumFramesToFall);
						if (obj->mNumFramesFalling < obj->data->mNumFramesToFall) {
							busy = TRUE;
						}
					}
				}
			}
			break;
		case 2:
			if (EVT_UW(event, 1)) {
				EVT_UW(event, 1)--;
				busy = TRUE;
			}
			else {
				if (EVT_UW(event, 3) == 0) {
					fall2 = (char*)str_802F3D3C;
					psndSFXOn_3D(fall2, &(Vec){0.0f, 0.0f, -100.0f});
				}
				EVT_UW(event, 3)++;
				sw->bgRotation.x = (s32)intpl_sub(2, 0.0f, 90.0f, EVT_UW(event, 3), EVT_UW(event, 2));
				if (EVT_UW(event, 3) < EVT_UW(event, 2)) {
					busy = TRUE;
				}
			}
			break;
	}
	return busy ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_mobj_set_alpha) {
	s32* args = event->args;
	s32 layer = evtGetValue(event, args[0]);
	u8 alpha = evtGetValue(event, args[1]);

	switch (layer) {
		case 0:
			if (mapGetMapObj("A1")) {
				mapGrpSetColor("A1", (GXColor){255, 255, 255, alpha});
			}
			break;
		case 1:
			if (mapGetMapObj("A2")) {
				mapGrpSetColor("A2", (GXColor){255, 255, 255, alpha});
			}
			break;
		case 2:
			if (mapGetMapObj("B")) {
				mapGrpSetColor("B", (GXColor){255, 255, 255, alpha});
			}
			break;
		case 3:
			if (mapGetMapObj("C")) {
				mapGrpSetColor("C", (GXColor){255, 255, 255, alpha});
			}
			break;
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_mobj_destroy) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	BattleUnit* unit;
	BattleUnitPart* part;
	s32 layer;
	int i;

	layer = evtGetValue(event, event->args[0]);
	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id > 0 && obj->data->mLayer == layer) {
			obj->mFlags |= 1;
			unit = BattleGetUnitPtr(wp, obj->mBattleUnitIdx);
			if (unit) {
				for (part = unit->mParts; part; part = part->mNextPart) {
					part->attributes |= 0x10000;
				}
			}
		}
	}
	switch (layer) {
		case 0:
			STAGE_WORK(wp)->flags |= 2;
			break;
		case 1:
			STAGE_WORK(wp)->flags |= 4;
			break;
		case 2:
			STAGE_WORK(wp)->flags |= 8;
			break;
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_get_bgset_attack_data) {
	BattleWork* wp = _battleWorkPointer;
	s32* args = event->args;
	s32 type = evtGetValue(event, args[0]);
	s32 out = args[1];
	BattleWeapon* weapon;

	switch (type) {
		case 0:
			weapon = &wp->fbatInfo->setup->stageData->bgAWeapon;
			break;
		case 2:
			weapon = &wp->fbatInfo->setup->stageData->bgBWeapon;
			break;
		case 1:
		default:
			weapon = NULL;
			break;
	}
	if (weapon && !weapon->hpDamageFn) {
		weapon = NULL;
	}
	evtSetValue(event, out, (s32)weapon);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_bgset_kemuri_effect) {
	s32 layer;
	const char* sfxA1;
	const char* sfxA2;
	const char* sfxB;
	BattleWork* wp;
	s32* args = event->args;
	int i;
	BattleStageObject* obj;
	f32 x, y, z;
	wp = _battleWorkPointer;
	layer = evtGetValue(event, args[0]);
	sfxA1 = "SFX_BTL_STAGE_SET_DOWN1";
	sfxA2 = "SFX_BTL_STAGE_SET_DOWN3";
	sfxB = "SFX_BTL_STAGE_SET_DOWN2";
	for (i = 0; i < 32; i++) {
		args++;
		args--;
		obj = &wp->stageObjects[i];
		if (obj->id > 0 && obj->data->mLayer == layer) {
			x = obj->mPosition.x;
			y = obj->mPosition.y;
			z = obj->mPosition.z;
			switch (layer) {
				case 0:
					z += 30.0f;
					effKemuri1N64Entry(3, x, y, z, 0.0f);
					psndSFXOn_3D(sfxA1, &obj->mPosition);
					break;
				case 1:
					z += 15.0f;
					effKemuri1N64Entry(0, x, y, z, 0.0f);
					psndSFXOn_3D(sfxA2, &obj->mPosition);
					break;
				case 2:
					z += 30.0f;
					effKemuri1N64Entry(3, x, y, z, 0.0f);
					effKemuri1N64Entry(4, x, y, z, 0.0f);
					psndSFXOn_3D(sfxB, &obj->mPosition);
					break;
			}
		}
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_bgset_audience_bgset_access) {
	BattleAudience_Case_HaikeiSet();
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_set_mobj_shake_init) {
	BattleWork* wp = _battleWorkPointer;
	s32 layer;
	int i;
	BattleStageObject* obj;
	u8 position;

	layer = evtGetValue(event, event->args[0]);
	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id > 0 && obj->data->mLayer == layer) {
			obj->field_0x72 = 0;
			obj->mShakePeriodLength = irand(10) + 60;
			if (irand(100) & 1) {
				position = 0;
			}
			else {
				position = obj->mShakePeriodLength / 2;
			}
			obj->mShakePeriodPosition = position;
			obj->mShakeAngle = 0.0f;
		}
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_set_mobj_shake) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	s32 layer;
	int i;

	layer = evtGetValue(event, event->args[0]);
	if (BattleWaitAllActiveEvtEnd_NoBgSetEndWait(wp)) {
		if (!sw->nozzleWorkEvtId || !evtCheckID(sw->nozzleWorkEvtId)) {
			if (!sw->fallFrameEvtId || !evtCheckID(sw->fallFrameEvtId)) {
				return EVT_RETURN_DONE;
			}
		}
	}
	switch (layer) {
		case 0:
		case 1:
			for (i = 0; i < 32; i++) {
				obj = &wp->stageObjects[i];
				if (obj->id > 0 && obj->data->mLayer == layer) {
					_mobj_shake_main(obj);
				}
			}
			break;
		case 2:
			break;
	}
	return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
void _mobj_shake_main(BattleStageObject* obj) {
	obj->mShakePeriodPosition++;
	if (obj->mShakePeriodPosition >= obj->mShakePeriodLength) {
		obj->mShakePeriodPosition = 0;
	}
	obj->mShakeAngle = 5.0f * sinfd(obj->mShakePeriodPosition * 360 / obj->mShakePeriodLength);
	obj->mRotation.x = obj->mShakeAngle;
}
#endif

#ifdef NONMATCHING
void BattleStage_NozzleDirChangeCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	u8 i;

	if (sw->nozzleData) {
		for (i = 0; i < 3; i++) {
			_Nozzle_Change_Check(i, sw->nozzleData->dirRate[i]);
		}
	}
}
#endif

#ifdef NONMATCHING
void _Nozzle_Change_Check(u8 index, u8* rate) {
	BattleStageObjectWork* sw = STAGE_WORK(_battleWorkPointer);
	u8* cur = &sw->nozzleDir[index];
	EventEntry* evt;
	s32 total = 0;
	u8* p;
	u8 dir;
	int i;

	for (i = 0; i < 4; i++) {
		total += rate[i];
	}
	total = irand(total);
	for (dir = 0, p = rate; dir < 4; p++, dir++) {
		total -= *p;
		if (total < 0) {
			break;
		}
	}
	if (dir != *cur) {
		if (sw->nozzleTurnEvtId[index] && !evtCheckID(sw->nozzleTurnEvtId[index])) {
			sw->nozzleTurnEvtId[index] = 0;
		}
		if (sw->nozzleTurnEvtId[index] == 0) {
			sw->nozzleNextDir[index] = dir;
			evt = evtEntry(_nozzle_turn_event, 10, 0);
			sw->nozzleTurnEvtId[index] = evt->eventId;
			if (evt) {
				evt->unitId = index;
			}
		}
	}
}
#endif

#ifdef NONMATCHING
USER_FUNC(_nozzle_turn) {
	BattleStageObjectWork* sw = STAGE_WORK(_battleWorkPointer);
	s32 index = event->unitId;
	const char* name;
	f32 rotX, rotY, from, to;

	if (isFirstCall) {
		EVT_UW(event, 2) = 0;
		EVT_UW(event, 3) = 0;
		if (sw->nozzleDir[index]) {
			EVT_UW(event, 2) = 30;
		}
	}
	switch (index) {
		case 0:
			name = "nozzle_l";
			break;
		case 1:
			name = "nozzle_c";
			break;
		case 2:
			name = "nozzle_r";
			break;
		default:
			return EVT_RETURN_DONE;
	}
	BattleSearchObjectPtr(name);
	if (EVT_UW(event, 2) < 30) {
		EVT_UW(event, 2)++;
		rotX = intpl_sub(2, 0.0f, -80.0f, EVT_UW(event, 2), 30);
	}
	else {
		rotX = -80.0f;
	}
	if (EVT_UW(event, 3) < 30) {
		EVT_UW(event, 3)++;
		switch (sw->nozzleDir[index]) {
			case 1:
				from = 45.0f;
				break;
			case 2:
				from = 0.0f;
				break;
			case 3:
				from = -45.0f;
				break;
			case 0:
			default:
				from = 0.0f;
				break;
		}
		switch (sw->nozzleNextDir[index]) {
			case 1:
				to = 45.0f;
				break;
			case 2:
				to = 0.0f;
				break;
			case 3:
				to = -45.0f;
				break;
			case 0:
			default:
				to = 0.0f;
				break;
		}
		rotY = intpl_sub(12, from, to, EVT_UW(event, 3), 30);
	}
	switch (index) {
		case 0:
			mapObjRotate("n_head_l", rotX, rotY, 0.0f);
			break;
		case 1:
			mapObjRotate("n_head_c", rotX, rotY, 0.0f);
			break;
		case 2:
			mapObjRotate("n_head_r", rotX, rotY, 0.0f);
			break;
	}
	if (EVT_UW(event, 2) >= 30 && EVT_UW(event, 3) >= 30) {
		sw->nozzleDir[index] = sw->nozzleNextDir[index];
		sw->nozzleTurnEvtId[index] = 0;
		return EVT_RETURN_DONE;
	}
	return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
void BattleStage_WallCloseCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (!(sw->flags & 0x10)) {
		sw->flags |= 0x10;
		sw->closeWallEvtId = evtEntry(_close_wall_event, 10, 0)->eventId;
	}
}
#endif

#ifdef NONMATCHING
USER_FUNC(_announce_wall_message) {
	if (isFirstCall) {
		event->userdata[0] = 60;
	}
	if (event->userdata[0] < 0) {
		return EVT_RETURN_DONE;
	}
	event->userdata[0]--;
	dispEntry(CAMERA_2D, 900.0f, 1, _disp_escape_wall_message, NULL);
	return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
void _disp_escape_wall_message(CameraId camera, void* param) {
	const char* msg = msgSearch("btl_msg_escape_wall_close2");
	s32 width = FontGetMessageWidth(msg);
	f32 x;
	f32 zero = 0.0f;

	x = zero - width / 2;
	windowDispGX_Waku_col(0, (GXColor){255, 255, 255, 255}, x - 20.0f, -117.0f, width + 40, 30.0f, 10.0f);
	FontDrawStart();
	FontDrawString(zero - (width / 2), -120.0f, msg);
}
#endif

#ifdef NONMATCHING
void BattleStage_IronFrameFallCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (!(sw->flags & 0x40) && !(sw->flags & 0x20)) {
		sw->flags |= 0x20;
		sw->fallFrameEvtId = evtEntry(_fall_frame_event, 10, 0)->eventId;
	}
}
#endif

#ifdef NONMATCHING
USER_FUNC(_fall_frame_wait) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (!BattleWaitAllActiveEvtEnd_NoBgSetEndWait(wp)) {
		return EVT_RETURN_BLOCK;
	}
	if (sw->nozzleWorkEvtId) {
		if (evtCheckID(sw->nozzleWorkEvtId)) {
			return EVT_RETURN_BLOCK;
		}
		sw->nozzleWorkEvtId = 0;
	}
	return EVT_RETURN_YIELD;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_fall_frame_wait_unit_ready) {
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* unit;
	EventEntry* evt;
	int i;

	if (isFirstCall) {
		for (i = 0; i < 64; i++) {
			unit = BattleGetUnitPtr(wp, i);
			if (unit && !(unit->flags & 0x80000000) && !BtlUnit_CheckStatus(unit, 0x1B) && UNIT_FIELD(unit, void*, 0x2BC)) {
				evt = evtEntry(UNIT_FIELD(unit, void*, 0x2BC), 10, 0);
				if (evt) {
					evt->unitId = unit->unitId;
				}
				UNIT_FIELD(unit, s32, 0x2C0) = evt->eventId;
			}
		}
	}
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit && !(unit->flags & 0x80000000)) {
			if (UNIT_FIELD(unit, s32, 0x2C0) && !evtCheckID(UNIT_FIELD(unit, s32, 0x2C0))) {
				UNIT_FIELD(unit, s32, 0x2C0) = 0;
			}
			if (UNIT_FIELD(unit, s32, 0x2C0)) {
				return EVT_RETURN_BLOCK;
			}
		}
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_fall_frame) {
	BattleWork* wp;
	s32 arg = event->args[0];
	BattleStageObject* body;
	BattleStageObjectWork* sw;

	wp = _battleWorkPointer;
	sw = STAGE_WORK(wp);
	body = BattleSearchObjectPtr("if_body");
	if (isFirstCall) {
		EVT_UW(event, 2) = 0;
		EVT_UW(event, 3) = body->mPosition.y;
	}
	EVT_UW(event, 2)++;
	body->mPosition.y = intpl_sub(2, EVT_UW(event, 3), 0.0f, EVT_UW(event, 2) * EVT_UW(event, 2) / 60, 60);
	if (EVT_UW(event, 2) < 60) {
		return EVT_RETURN_BLOCK;
	}
	evtSetValue(event, arg, (s32)sw->fallObjectData);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_fall_frame_delete) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (isFirstCall) {
		EVT_UW(event, 2) = 255;
	}
	EVT_UW(event, 2) -= 5;
	mapGrpSetColor("if_body", (GXColor){255, 255, 255, EVT_UW(event, 2)});
	if (EVT_UW(event, 2) > 0) {
		return EVT_RETURN_BLOCK;
	}
	sw->fallFrameEvtId = 0;
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
void BattleStage_NozzleWorkCheck(s32 type) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	EventEntry* evt;

	if (pouchGetPtr()->rank > 0) {
		_nozzle_type_init();
		if (type || sw->nozzleType) {
			if (sw->nozzleWorkEvtId && !evtCheckID(sw->nozzleWorkEvtId)) {
				sw->nozzleWorkEvtId = 0;
			}
			if (sw->nozzleWorkEvtId == 0) {
				if (type) {
					evt = evtEntry(_nozzle_work_event_1, 10, 0);
				}
				else {
					evt = evtEntry(_nozzle_work_event_0, 10, 0);
				}
				sw->nozzleWorkEvtId = evt->eventId;
			}
		}
	}
}
#endif

#ifdef NONMATCHING
void _nozzle_type_init(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	BattleStageNozzleData* data = sw->nozzleData;
	s32 total;
	s8 i;

	if (sw->nozzleType == -1) {
		total = 0;
		for (i = 0; i < 4; i++) {
			total += data->typeRate[i];
		}
		total = irand(total);
		for (i = 0; i < 4; i++) {
			total -= data->typeRate[i];
			if (total < 0) {
				break;
			}
		}
		sw->nozzleType = i;
	}
}
#endif

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_wait) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	int i;

	if (!BattleWaitAllActiveEvtEnd_NoBgSetEndWait(wp)) {
		return EVT_RETURN_BLOCK;
	}
	for (i = 0; i < 3; i++) {
		if (sw->nozzleTurnEvtId[i]) {
			if (evtCheckID(sw->nozzleTurnEvtId[i])) {
				return EVT_RETURN_BLOCK;
			}
			sw->nozzleTurnEvtId[i] = 0;
		}
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
f32 _get_nozzle_dir(s32 index) {
	switch (STAGE_WORK(_battleWorkPointer)->nozzleDir[index]) {
		case 1:
			return -45.0f;
		case 3:
			return -135.0f;
		case 2:
		default:
			return -90.0f;
	}
}
#endif

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_effect) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	s32* args = event->args;
	const char* sfx;
	s32 effType = 0;
	BOOL started;
	BattleStageObject* obj;
	f32 z, rot, angle1, angle2, angle3;
	s32 fog;
	s32 out;

	fog = evtGetValue(event, args[0]);
	out = args[1];
	started = FALSE;
	if (isFirstCall) {
		if (BattleCheckConcluded(wp)) {
			evtSetValue(event, out, 0);
			return EVT_RETURN_DONE;
		}
		EVT_UW(event, 0) = 90;
		switch (sw->nozzleType) {
			case 1:
				sfx = "SFX_BTL_STAGE_SMOKE1";
				effType = 0;
				break;
			case 2:
				sfx = NULL;
				effType = 1;
				break;
			case 3:
				sfx = "SFX_BTL_STAGE_FIRE1";
				effType = 2;
				break;
		}
		switch (sw->nozzleType) {
			case 1:
			case 2:
			case 3:
				obj = BattleSearchObjectPtr("nozzle_l");
				angle1 = _get_nozzle_dir(0);
				if (sw->nozzleDir[0]) {
					if (sfx) {
						EVT_UW(event, 5) = psndSFXOn_3D(sfx, &obj->mPosition);
					}
					else {
						EVT_UW(event, 5) = -1;
					}
					rot = 90.0f + angle1;
					rot = reviseAngle(rot);
					z = 10.0f * sinfd(angle1) + obj->mPosition.z;
					EVT_UW(event, 1) = (s32)effNozleEntry(effType, obj->mPosition.x - 10.0f * cosfd(angle1), 12.0f + obj->mPosition.y, z, -80.0f, rot, 90);
				}
				else {
					if (sfx) {
						EVT_UW(event, 5) = psndSFXOn_3D(sfx, &obj->mPosition);
					}
					else {
						EVT_UW(event, 5) = -1;
					}
					EVT_UW(event, 1) = (s32)effNozleEntry(effType, obj->mPosition.x, 20.0f + obj->mPosition.y, 8.0f + obj->mPosition.z, 0.0f, 0.0f, 90);
					if (fog == 0) {
						effConfettiN64Entry(4, 90, obj->mPosition.x, 20.0f + obj->mPosition.y, 8.0f + obj->mPosition.z, 1.0f);
					}
				}
				obj = BattleSearchObjectPtr("nozzle_c");
				angle2 = _get_nozzle_dir(1);
				if (sw->nozzleDir[1]) {
					if (sfx) {
						EVT_UW(event, 6) = psndSFXOn_3D(sfx, &obj->mPosition);
					}
					else {
						EVT_UW(event, 6) = -1;
					}
					rot = reviseAngle(90.0f + angle2);
					z = 10.0f * sinfd(angle2) + obj->mPosition.z;
					EVT_UW(event, 2) = (s32)effNozleEntry(effType, obj->mPosition.x - 10.0f * cosfd(angle2), 12.0f + obj->mPosition.y, z, -80.0f, rot, 90);
				}
				else {
					if (sfx) {
						EVT_UW(event, 6) = psndSFXOn_3D(sfx, &obj->mPosition);
					}
					else {
						EVT_UW(event, 6) = -1;
					}
					EVT_UW(event, 2) = (s32)effNozleEntry(effType, obj->mPosition.x, 20.0f + obj->mPosition.y, 8.0f + obj->mPosition.z, 0.0f, 0.0f, 90);
					if (fog == 0) {
						effConfettiN64Entry(4, 90, obj->mPosition.x, 20.0f + obj->mPosition.y, 8.0f + obj->mPosition.z, 1.0f);
					}
				}
				obj = BattleSearchObjectPtr("nozzle_r");
				angle3 = _get_nozzle_dir(2);
				if (sw->nozzleDir[2]) {
					if (sfx) {
						EVT_UW(event, 7) = psndSFXOn_3D(sfx, &obj->mPosition);
					}
					else {
						EVT_UW(event, 7) = -1;
					}
					z = reviseAngle(90.0f + angle3);
					rot = 10.0f * sinfd(angle3) + obj->mPosition.z;
					EVT_UW(event, 3) = (s32)effNozleEntry(effType, obj->mPosition.x - 10.0f * cosfd(angle3), 12.0f + obj->mPosition.y, rot, -80.0f, z, 90);
				}
				else {
					if (sfx) {
						EVT_UW(event, 7) = psndSFXOn_3D(sfx, &obj->mPosition);
					}
					else {
						EVT_UW(event, 7) = -1;
					}
					EVT_UW(event, 3) = (s32)effNozleEntry(effType, obj->mPosition.x, 20.0f + obj->mPosition.y, 8.0f + obj->mPosition.z, 0.0f, 0.0f, 90);
					if (fog == 0) {
						effConfettiN64Entry(4, 90, obj->mPosition.x, 20.0f + obj->mPosition.y, 8.0f + obj->mPosition.z, 1.0f);
					}
				}
				started = TRUE;
				break;
			default:
				if (fog && !sw->fogEffect) {
					EVT_UW(event, 0) = 120;
					EVT_UW(event, 1) = 0;
					EVT_UW(event, 3) = 0;
					EVT_UW(event, 2) = 0;
					sw->fogEffect = effNozleEntry(3, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1000);
					EVT_UW(event, 3) = (s32)sw->fogEffect;
					sw->fogTimer = 2;
					EVT_UW(event, 5) = psndSFXOn_3D("SFX_BTL_STAGE_DRYICE1", &BattleSearchObjectPtr("nozzle_c")->mPosition);
					started = TRUE;
					EVT_UW(event, 6) = -1;
					EVT_UW(event, 7) = -1;
				}
				break;
		}
		if (!started) {
			evtSetValue(event, out, 0);
			return EVT_RETURN_DONE;
		}
	}
	if (EVT_UW(event, 0) > 0) {
		EVT_UW(event, 0)--;
		if (EVT_UW(event, 0) <= 0) {
			if ((u32)EVT_UW(event, 5) != 0xFFFFFFFF) {
				psndSFXOff(EVT_UW(event, 5));
			}
			if ((u32)EVT_UW(event, 6) != 0xFFFFFFFF) {
				psndSFXOff(EVT_UW(event, 6));
			}
			if ((u32)EVT_UW(event, 7) != 0xFFFFFFFF) {
				psndSFXOff(EVT_UW(event, 7));
			}
		}
		return EVT_RETURN_BLOCK;
	}
	evtSetValue(event, out, 1);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
BOOL BattleFogEndCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (sw->fogTimer == 0) {
		return TRUE;
	}
	sw->fogTimer--;
	if (sw->fogTimer > 0) {
		return FALSE;
	}
	if (sw->fogEffect) {
		effSoftDelete(sw->fogEffect);
		sw->fogEffect = NULL;
	}
	return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL BattleFogForceStop(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (sw->fogTimer == 0) {
		return FALSE;
	}
	if (sw->fogEffect) {
		effSoftDelete(sw->fogEffect);
		sw->fogEffect = NULL;
	}
	return TRUE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_attack_set) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	s32 index;
	int i;

	sw->nozzleWeapons[0] = NULL;
	sw->nozzleWeapons[1] = NULL;
	memset(&sw->nozzleWeaponWork[0], 0, sizeof(BattleWeapon));
	memset(&sw->nozzleWeaponWork[1], 0, sizeof(BattleWeapon));
	_combine_nozzle_weapon(TRUE, &sw->nozzleWeaponWork[0], &_nozzle_at_base_mario.weapon);
	_combine_nozzle_weapon(TRUE, &sw->nozzleWeaponWork[1], &_nozzle_at_base_monster.weapon);
	for (i = 0; i < 3; i++) {
		index = _get_nozzle_attack_index(i);
		if (index >= 0) {
			if (!sw->nozzleWeapons[index]) {
				sw->nozzleWeapons[index] = &sw->nozzleWeaponWork[index];
			}
			_combine_nozzle_weapon(FALSE, sw->nozzleWeapons[index], &sw->nozzleData->weapons[sw->nozzleType].weapon);
		}
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 _get_nozzle_attack_index(u8 index) {
	BattleStageObjectWork* sw = STAGE_WORK(_battleWorkPointer);

	switch (index) {
		case 0:
			switch (sw->nozzleDir[index]) {
				case 1:
					return -1;
				case 2:
					return 0;
				case 3:
					return 1;
			}
		case 2:
			switch (sw->nozzleDir[index]) {
				case 1:
					return 0;
				case 2:
					return 1;
				case 3:
					return -1;
			}
		case 1:
			switch (sw->nozzleDir[index]) {
				case 1:
					return 0;
				case 2:
					return -1;
				case 3:
					return 1;
			}
	}
	return -1;
}
#endif

#ifdef NONMATCHING
void _rate_mix(s8* dstChance, s8* dstTime, s8* srcChance, s8* srcTime) {
	if (*srcChance <= 0) {
		return;
	}
	if (*srcChance > *dstChance) {
		*dstChance = *srcChance;
	}
	*dstTime += *srcTime;
}
#endif

#ifdef NONMATCHING
void _rate_mix_3(s8* dstChance, s8* dstTime, s8* dstStrength, s8* srcChance, s8* srcTime, s8* srcStrength) {
	if (*srcChance <= 0) {
		return;
	}
	if (*srcChance > *dstChance) {
		*dstChance = *srcChance;
	}
	*dstTime += *srcTime;
	*dstStrength += *srcStrength;
	if (*dstStrength == 0) {
		*dstChance = 0;
		*dstTime = 0;
	}
}
#endif

#ifdef NONMATCHING
void _combine_nozzle_weapon(BOOL copy, BattleWeapon* dst, BattleWeapon* src) {
	s8* d;
	s8* s;
	int i;

	if (copy) {
		*dst = *src;
		return;
	}
	dst->baseFpCost += src->baseFpCost;
	dst->baseSpCost += src->baseSpCost;
	if (!dst->hpDamageFn) {
		dst->hpDamageFn = src->hpDamageFn;
	}
	for (i = 0; i < 8; i++) {
		dst->hpDamageWork[i] += src->hpDamageWork[i];
	}
	dst->element = src->element;
	s = (s8*)src + 0x80;
	d = (s8*)dst + 0x80;
	_rate_mix(&d[0x0], &d[0x1], &s[0x0], &s[0x1]);
	_rate_mix(&d[0x2], &d[0x3], &s[0x2], &s[0x3]);
	_rate_mix(&d[0x4], &d[0x5], &s[0x4], &s[0x5]);
	_rate_mix(&d[0x6], &d[0x7], &s[0x6], &s[0x8]);
	_rate_mix(&d[0x9], &d[0xA], &s[0x9], &s[0xA]);
	_rate_mix(&d[0xB], &d[0xC], &s[0xB], &s[0xC]);
	_rate_mix(&d[0xD], &d[0xE], &s[0xD], &s[0xE]);
	_rate_mix(&d[0xF], &d[0x10], &s[0xF], &s[0x10]);
	_rate_mix(&d[0x11], &d[0x12], &s[0x11], &s[0x12]);
	_rate_mix_3(&d[0x13], &d[0x14], &d[0x15], &s[0x13], &s[0x14], &s[0x15]);
	_rate_mix_3(&d[0x19], &d[0x1A], &d[0x1B], &s[0x19], &s[0x1A], &s[0x1B]);
	_rate_mix(&d[0x1C], &d[0x1D], &s[0x1C], &s[0x1D]);
	d[0x1F] += s[0x1F];
	_rate_mix(&d[0x20], &d[0x21], &s[0x20], &s[0x21]);
	_rate_mix(&d[0x22], &d[0x23], &s[0x22], &s[0x23]);
	d[0x2A] += s[0x2A];
	d[0x2B] += s[0x2B];
	d[0x2C] += s[0x2C];
	d[0x2D] += s[0x2D];
}
#endif

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_get_weapon_address) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	s32* args = event->args;
	s32 index = evtGetValue(event, args[0]);

	evtSetValue(event, args[1], (s32)sw->nozzleWeapons[index]);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 BattleStage_ObjectFallCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	EventEntry* evt;

	if (wp->flags & 0x1000) {
		return 0;
	}
	evt = evtEntry(_object_fall_event, 10, 0);
	sw->objectFallEvtId = evt->eventId;
	return evt->eventId;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_object_fall_wait) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (!BattleWaitAllActiveEvtEnd_NoBgSetEndWait(wp)) {
		return EVT_RETURN_BLOCK;
	}
	if (sw->nozzleWorkEvtId) {
		if (evtCheckID(sw->nozzleWorkEvtId)) {
			return EVT_RETURN_BLOCK;
		}
		sw->nozzleWorkEvtId = 0;
	}
	if (sw->fallFrameEvtId) {
		if (evtCheckID(sw->fallFrameEvtId)) {
			return EVT_RETURN_BLOCK;
		}
		sw->fallFrameEvtId = 0;
	}
	if (sw->bgDestroyEvtId) {
		if (evtCheckID(sw->bgDestroyEvtId)) {
			return EVT_RETURN_BLOCK;
		}
		sw->bgDestroyEvtId = 0;
	}
	return EVT_RETURN_DONE;
}
#endif


typedef struct FallObjectEntry {
	s8 index; //0x0
	s8 type; //0x1
	u8 field_0x2[0x4 - 0x2]; //0x2
	s32 kind; //0x4, 0 = unit, 1 = audience
	s32 unitId; //0x8
	s32 partId; //0xC
	s16 delay; //0x10
	s16 field_0x12; //0x12
	u8 noAc; //0x14
	u8 field_0x15; //0x15
	u8 field_0x16[0x1C - 0x16]; //0x16
	s32 preCheck; //0x1C
	s32 sfxId; //0x20
	EffectEntry* effect; //0x24
	BattleWeaponData weapon; //0x28
} FallObjectEntry;

typedef struct FallObjectWork {
	u8 count; //0x0
	s8 prevTypes[3]; //0x1
	FallObjectEntry entries[1]; //0x4
} FallObjectWork;
extern void* jumptable_80374848[];
s32 _object_fall_attack(EventEntry *event, BOOL isFirstCall);
s32 BattleStage_ObjectFallCheck(void);
void _combine_nozzle_weapon(BOOL copy, BattleWeapon* dst, BattleWeapon* src);
void _rate_mix_3(s8* dstChance, s8* dstTime, s8* dstStrength, s8* srcChance, s8* srcTime, s8* srcStrength);
void _rate_mix(s8* dstChance, s8* dstTime, s8* srcChance, s8* srcTime);
s32 _get_nozzle_attack_index(u8 index);
BOOL BattleFogForceStop(void);
BOOL BattleFogEndCheck(void);
f32 _get_nozzle_dir(s32 index);
void _nozzle_type_init(void);
void BattleStage_NozzleWorkCheck(s32 type);
void BattleStage_IronFrameFallCheck(void);
void _disp_escape_wall_message(CameraId camera, void* param);
void BattleStage_WallCloseCheck(void);
void _Nozzle_Change_Check(u8 index, u8* rate);
void BattleStage_NozzleDirChangeCheck(void);
void _mobj_shake_main(BattleStageObject* obj);
void BattleStage_DestroyB(void);
void BattleStage_DestroyA2(void);
void BattleStage_DestroyA1(void);
void BattleObjectConfig(void);
void BattleStageObjectMain(void);
void BattleStageObjectInit(void);
BattleStageObject* BattleSearchObjectPtr(const char* name);
BattleStageObject* BattleGetObjectPtr(s32 id);
USER_FUNC(_object_fall_wait);
USER_FUNC(_nozzle_work_get_weapon_address);
USER_FUNC(_nozzle_work_attack_set);
USER_FUNC(_nozzle_work_effect);
USER_FUNC(_nozzle_work_wait);
USER_FUNC(_fall_frame_delete);
USER_FUNC(_fall_frame);
USER_FUNC(_fall_frame_wait_unit_ready);
USER_FUNC(_fall_frame_wait);
USER_FUNC(_announce_wall_message);
USER_FUNC(_nozzle_turn);
USER_FUNC(_set_mobj_shake);
USER_FUNC(_set_mobj_shake_init);
USER_FUNC(_bgset_audience_bgset_access);
USER_FUNC(_bgset_kemuri_effect);
USER_FUNC(_get_bgset_attack_data);
USER_FUNC(_mobj_destroy);
USER_FUNC(_mobj_set_alpha);
USER_FUNC(_set_mobj_rotate_x);

#ifdef NONMATCHING
s32 _object_fall_attack(EventEntry *event, BOOL isFirstCall)
{
  BOOL found = 0;
  s32 j;
  BattleWeapon *weapon;
  BattleWork *wp = _battleWorkPointer;
  const char *sfxNormal;
  const char *sfxTub;
  BattleStageFallObjectData *fd = ((BattleStageObjectWork *) wp->field_180C0)->fallObjectData;
  s32 *ud = event->userdata;
  s32 *args = event->args;
  s32 arg0 = *(args++);
  FallObjectWork *w;
  FallObjectEntry *e;
  FallObjectEntry *o;
  BattleUnit *unit2;
  s32 k;
  BattleUnit *unit;
  const char *sfxTub2;
  const char *sfxRest;
  s32 i;
  BattleUnitPart *part;
  s32 sum;
  s32 r;
  u32 flags;
  s16 delay;
  BOOL done;
  s32 acCount;
  f32 width;
  f32 dir;
  BattleWorkWeaponTargets targets;
  BattleWorkWeaponTargets targets2;
  Vec pos;
  Vec hit;
  Vec sfxPos;
  Vec p;
  s32 unitId;
  s32 partId;
  if (isFirstCall)
  {
    w = BattleAlloc(sizeof(FallObjectWork));
    ud[0] = (s32) w;
    ud[1] = 0;
    memset(w, 0, sizeof(FallObjectWork));
    w->entries[0].index = -1;
    for (i = 0; i < 3; i++)
    {
      w->prevTypes[i] = -1;
    }

    if (BattleCheckConcluded(wp))
    {
      evtSetValue(event, arg0, ud[1]);
      return 2;
    }
    w->count = 1;
    for (i = 0; i < w->count; i++)
    {
      e = &w->entries[i];
      e->index = i;
      for (j = 0; j < 3; j++)
      {
        if (w->prevTypes[j] == (-1))
        {
          break;
        }
      }

      if (j >= 3)
      {
        e->type = w->prevTypes[irand(3)];
      }
      else
      {
        sum = 0;
        for (k = 0; k < 9; k++)
        {
          sum += fd->rates[k];
        }

        r = irand(sum);
        for (e->type = 0; e->type < 8; e->type++)
        {
          if ((r -= fd->rates[e->type]) < 0)
          {
            break;
          }
        }

        w->prevTypes[j] = e->type;
      }
      e->weapon = fd->weapons[e->type];
      if (e->type == 6)
      {
        if (irand(100) < 50)
        {
          e->weapon.weapon.targetClassFlags |= 0x100;
          e->weapon.weapon.targetClassFlags &= ~0x200;
        }
        else
        {
          e->weapon.weapon.targetClassFlags &= ~0x100;
          e->weapon.weapon.targetClassFlags |= 0x200;
        }
      }
      weapon = &e->weapon.weapon;
      e->kind = 0;
      if ((((*((u16 *) (&pouchGetPtr()->mStarPowersObtained))) && (!(BattleAudienceBaseGetPtr()->flags & 0x4000))) && (e->type != 6)) && (e->type != 7))
      {
        if (((*((u32 *) (&wp->field_19064[4]))) & 2) || (irand(100) < 10))
        {
          e->kind = 1;
          e->partId = -1;
          e->unitId = BattleAudience_HaitiRandForFallObject();
          found = 1;
          ud[1] = 1;
        }
      }
      if (e->kind == 0)
      {
        BattleSamplingEnemy(&targets, weapon, BattleGetSystemPtr(wp)->unitId, 1, weapon->targetClassFlags, weapon->targetPropertyFlags, -wp->alliances[1].attackDirection);
        if (targets.numTargets <= 0)
        {
          evtSetValue(event, arg0, ud[1]);
          return 2;
        }
        found = 1;
        BattleChoiceSamplingEnemy(&targets, weapon->targetWeightFlags, &unitId, &partId);
        e->unitId = unitId;
        e->partId = partId;
        e->noAc = 1;
        for (k = i; k >= 0; k--)
        {
          o = &w->entries[k];
          if (((e != o) && (o->kind == 0)) && (e->unitId == o->unitId))
          {
            o->noAc = 0;
          }
        }

      }
    }

    if (!found)
    {
      evtSetValue(event, arg0, ud[1]);
      return 2;
    }
    for (i = 0; i < w->count; i++)
    {
      e = &w->entries[i];
      weapon = &e->weapon.weapon;
      if (e->kind == 0)
      {
        flags = 0;
        if (e->noAc)
        {
          flags |= 0x100;
        }
        if (e->field_0x15)
        {
          flags |= 0x100000;
        }
        e->preCheck = BattlePreCheckDamage(BattleGetSystemPtr(wp), BattleGetUnitPtr(wp, e->unitId), BattleGetUnitPartsPtr(e->unitId, e->partId), weapon, flags);
        if ((e->preCheck == 1) && (!e->noAc))
        {
          delay = irand(0);
          for (k = 0; k < i; k++)
          {
            o = &w->entries[k];
            if (e->unitId == o->unitId)
            {
              o->delay = delay;
              delay += irand(22) + 20;
              if (o->noAc)
              {
                o->field_0x15 = 1;
              }
            }
          }

        }
      }
    }

  }
  sfxTub = "SFX_BTL_STAGE_DAMAGE_TUB1";
  sfxNormal = "SFX_BTL_STAGE_DAMAGE_NORMAL1";
  sfxRest = "SFX_REST_CONDITION1";
  sfxTub2 = sfxTub;
  w = (FallObjectWork *) ud[0];
  done = 1;
  for (i = 0; i < w->count; i++)
  {
    e = &w->entries[i];
    if (e->index == (-1))
    {
      continue;
    }
    acCount = 0;
    done = 0;
    if (e->kind == 0)
    {
      unit = BattleGetUnitPtr(wp, e->unitId);
      part = BattleGetUnitPartsPtr(e->unitId, e->partId);
    }
    if ((e->effect == ((void *) 0)) || (e->delay > 0))
    {
      e->delay--;
      if (e->delay > 0)
      {
        continue;
      }
      switch (e->kind)
      {
        case 0:
          BtlUnit_GetHitPos(unit, part, &hit.x, &hit.y, &hit.z);
          width = BtlUnit_GetWidth(unit);
          break;

        case 1:
          hit.x = ((e->unitId % 20) * 25) - 230;
          hit.y = BattleStageGetPtr()->audienceSizeY;
          hit.z = (0.1f * (e->unitId % 20)) + (((e->unitId / 20) * 30) + 115);
          btl_camera_set_mode(0, 6);
          btl_camera_set_moveSpeedLv(0, 2);
          width = 0.0f;
          break;

        default:
          hit = (Vec){0.0f, 0.0f, 0.0f};
          width = 0.0f;
          break;

      }

      pos = hit;
      pos.y = BattleGetFloorHeight(wp, pos.x, pos.y, pos.z);
      if (hit.x >= 0.0f)
      {
        dir = 90.0f;
      }
      else
      {
        dir = 270.0f;
      }
      switch (e->preCheck)
      {
        case 2:

        case 3:

        case 4:

        case 6:
          hit.y = pos.y;
          break;

      }

      e->sfxId = -1;
      e->field_0x12 = 0;
      sfxTub = "SFX_BTL_STAGE_DAMAGE_TUB1";
      switch (e->type)
      {
        case 0:
          e->effect = effFallEntry(4, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;

        case 1:
          e->effect = effFallEntry(5, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;

        case 2:
          e->effect = effFallEntry(0, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 100, 90);
          break;

        case 3:
          e->effect = effFallEntry(1, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;

        case 4:
          e->effect = effFallEntry(2, pos.x, pos.y, 5.0f + pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;

        case 8:
          e->effect = effFallEntry(8, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;

        case 5:
          e->effect = effFallEntry(3, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;

        case 6:
          if (BtlUnit_GetBelong(unit) == 0)
        {
          e->effect = effFallEntry(6, -300.0f, pos.y, 15.0f + pos.z, 0.0f, 0.0f, dir, 1, 180);
        }
        else
        {
          e->effect = effFallEntry(6, 300.0f, pos.y, 15.0f + pos.z, 0.0f, 0.0f, dir, 1, 180);
        }
          break;

        case 7:
          e->effect = effFallEntry(7, pos.x, pos.y, 5.0f + pos.z, width, hit.y - pos.y, dir, 1, 180);
          break;

      }

    }
    else
    {
      if ((e->effect != ((void *) 0)) && (!effFallCheckHit(e->effect)))
      {
        continue;
      }
      weapon = &e->weapon.weapon;
      if (e->kind == 1)
      {
        BattleAudience_Case_FallObject_Aud(e->unitId, e->type);
        psndSFXOff(e->sfxId);
        BattleAudience_GetHomePosition(e->unitId, &sfxPos.x, &sfxPos.y, &sfxPos.z);
        switch (e->type)
        {
          case 5:
            break;

          case 0:

          case 1:
            psndSFXOn_3D(sfxTub, &sfxPos);
            break;

          default:
            psndSFXOn_3D(sfxNormal, &sfxPos);
            break;

        }

      }
      else
      {
        BattleAudience_Case_FallObject_Stage();
        if (weapon->targetClassFlags & 0x1000000)
        {
          BtlUnit_GetHitPos(unit, part, &sfxPos.x, &sfxPos.y, &sfxPos.z);
          flags = 0;
          if (e->noAc)
          {
            flags |= 0x100;
          }
          psndSFXOff(e->sfxId);
          switch (e->preCheck)
          {
            case 2:

            case 3:

            case 4:

            case 6:
              switch (e->type)
            {
              case 5:
                break;

              case 0:

              case 1:
                psndSFXOn_3D(sfxTub, &sfxPos);
                break;

            }

              break;

            case 1:
              switch (e->type)
            {
              case 0:

              case 1:
                psndSFXOn_3D(sfxTub2, &sfxPos);
                break;

              case 5:
                psndSFXOn_3D(sfxRest, &sfxPos);
                break;

              default:
                psndSFXOn_3D(sfxNormal, &sfxPos);
                break;

            }

              if (BtlUnit_GetACPossibility(unit))
            {
              BattleActionCommandCheckDefence(unit, weapon);
            }
              BattleCheckDamage(BattleGetSystemPtr(wp), unit, part, weapon, flags);
              break;

          }

        }
        else
        {
          psndSFXOff(e->sfxId);
          BattleSamplingEnemy(&targets2, weapon, BattleGetSystemPtr(wp)->unitId, 1, weapon->targetClassFlags, weapon->targetPropertyFlags, -wp->alliances[1].attackDirection);
          if (targets2.numTargets > 0)
          {
            while (targets2.currentTarget < targets2.numTargets)
            {
              BattleWorkTarget *tg;
              tg = &targets2.targets[targets2.targetIndices[targets2.currentTarget]];
              unit2 = BattleGetUnitPtr(wp, tg->unitIdx);
              switch (BattlePreCheckDamage(BattleGetSystemPtr(wp), unit2, BattleGetUnitPartsPtr(tg->unitIdx, tg->partIdx), weapon, 0x100))
              {
                case 2:

                case 4:
                  break;

                case 3:
                {
                  EffectEntry *eff;
                  BtlUnit_GetPos(unit2, &p.x, &p.y, &p.z);
                  if (p.y < 85.0f)
                  {
                    p.y += 50.0f;
                  }
                  else
                  {
                    p.y += -50.0f;
                  }
                  p.x -= 45.0f;
                  eff = effNiceEntry(6, p.x, p.y, p.z);
                  ((f32 *) eff->userdata)[7] = 0.75f;
                  unit2->damagePattern = 0;
                  BattleRunHitEvent(unit2, 0x126);
                  break;
                }

                case 6:
                  unit2->damagePattern = 0;
                  BattleRunHitEvent(unit2, 0x127);
                  break;

                case 1:
                  if (BtlUnit_GetACPossibility(unit2) && (acCount <= 0))
                {
                  BattleActionCommandCheckDefence(unit2, weapon);
                  acCount++;
                }
                  BattleCheckDamage(BattleGetSystemPtr(wp), unit2, BattleGetUnitPartsPtr(tg->unitIdx, tg->partIdx), weapon, 0x100);
                  break;

              }

              targets2.currentTarget++;
            }

          }
        }
      }
      e->index = -1;
    }
  }

  if (!done)
  {
    return 0;
  }
  BattleFree((void *) ud[0]);
  evtSetValue(event, arg0, ud[1]);
  return 2;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: BattleGetObjectPtr (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off

asm s32 _object_fall_attack(EventEntry *event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x1670(r1)
	mflr r0
	stw r0, 0x1674(r1)
	li r0, 0x1668
	stfd f31, 0x1660(r1)
	psq_stx f31, r1, r0, 0, 0
	li r0, 0x1658
	stfd f30, 0x1650(r1)
	psq_stx f30, r1, r0, 0, 0
	stmw r14, 0x1608(r1)
	lwz r6, _battleWorkPointer(r0)
	mr r15, r3
	lwz r7, 0x18(r3)
	lis r5, vec3_802f3ac8@ha
	addis r3, r6, 0x2
	cmpwi r4, 0x0
	lwz r17, -0x7f08(r3)
	mr r25, r6
	lwz r22, 0x0(r7)
	addi r30, r5, vec3_802f3ac8@l
	li r21, 0x0
	beq @1
	li r3, 0xec
	bl BattleAlloc
	mr r14, r3
	li r0, 0x0
	stw r14, 0x78(r15)
	li r4, 0x0
	li r5, 0xec
	stw r0, 0x7c(r15)
	bl memset
	li r3, -0x1
	li r0, 0x3
	stb r3, 0x4(r14)
	li r4, 0x0
	mtctr r0
	@2:
	addi r0, r4, 0x1
	addi r4, r4, 0x1
	stbx r3, r14, r0
	bdnz @2
	mr r3, r25
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq @3
	lwz r5, 0x7c(r15)
	mr r3, r15
	mr r4, r22
	bl evtSetValue
	li r3, 0x2
	b @4
	@3:
	li r0, 0x1
	li r16, 0x0
	stb r0, 0x0(r14)
	li r24, 0x0
	b @5
	@6:
	addi r23, r24, 0x4
	li r0, 0x3
	add r23, r14, r23
	li r18, 0x0
	stb r16, 0x0(r23)
	mtctr r0
	@7:
	addi r0, r18, 0x1
	lbzx r0, r14, r0
	extsb r0, r0
	cmpwi r0, -0x1
	beq @8
	addi r18, r18, 0x1
	bdnz @7
	@8:
	cmpwi r18, 0x3
	blt @9
	li r3, 0x3
	bl irand
	addi r0, r3, 0x1
	lbzx r0, r14, r0
	stb r0, 0x1(r23)
	b @10
	@9:
	li r0, 0x9
	li r3, 0x0
	li r4, 0x0
	mtctr r0
	@11:
	addi r0, r4, 0xc0
	addi r4, r4, 0x1
	lbzx r0, r17, r0
	add r3, r3, r0
	bdnz @11
	bl irand
	li r0, 0x0
	stb r0, 0x1(r23)
	b @12
	@13:
	extsb r4, r5
	addi r0, r4, 0xc0
	lbzx r0, r17, r0
	subf. r3, r0, r3
	blt @14
	lbz r4, 0x1(r23)
	addi r0, r4, 0x1
	stb r0, 0x1(r23)
	@12:
	lbz r5, 0x1(r23)
	extsb r0, r5
	cmpwi r0, 0x8
	blt @13
	@14:
	addi r0, r18, 0x1
	stbx r5, r14, r0
	@10:
	lbz r3, 0x1(r23)
	li r0, 0x18
	addi r5, r23, 0x24
	extsb r3, r3
	mulli r3, r3, 0xc0
	addi r3, r3, 0xcc
	add r4, r17, r3
	mtctr r0
	subi r4, r4, 0x4
	@15:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @15
	lbz r0, 0x1(r23)
	cmpwi r0, 0x6
	bne @16
	li r3, 0x64
	bl irand
	cmpwi r3, 0x32
	bge @17
	lwz r0, 0x8c(r23)
	ori r0, r0, 0x100
	stw r0, 0x8c(r23)
	lwz r0, 0x8c(r23)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x8c(r23)
	b @16
	@17:
	lwz r0, 0x8c(r23)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x8c(r23)
	lwz r0, 0x8c(r23)
	ori r0, r0, 0x200
	stw r0, 0x8c(r23)
	@16:
	li r0, 0x0
	addi r18, r23, 0x28
	stw r0, 0x4(r23)
	bl pouchGetPtr
	lhz r0, 0x8c(r3)
	cmplwi r0, 0x0
	beq @18
	bl BattleAudienceBaseGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 17, 17
	bne @18
	lbz r0, 0x1(r23)
	extsb r0, r0
	cmpwi r0, 0x6
	beq @18
	cmpwi r0, 0x7
	beq @18
	addis r3, r25, 0x2
	lwz r0, -0x6f98(r3)
	rlwinm. r0, r0, 0, 30, 30
	bne @19
	li r3, 0x64
	bl irand
	cmpwi r3, 0xa
	bge @18
	@19:
	li r3, 0x1
	li r0, -0x1
	stw r3, 0x4(r23)
	stw r0, 0xc(r23)
	bl BattleAudience_HaitiRandForFallObject
	stw r3, 0x8(r23)
	li r0, 0x1
	li r21, 0x1
	stw r0, 0x7c(r15)
	@18:
	lwz r0, 0x4(r23)
	cmpwi r0, 0x0
	bne @20
	mr r3, r25
	bl BattleGetSystemPtr
	lbz r0, 0x12(r25)
	mr r4, r18
	lwz r5, 0x0(r3)
	addi r3, r1, 0xb0c
	neg r0, r0
	lwz r7, 0x64(r18)
	lwz r8, 0x68(r18)
	extsb r9, r0
	li r6, 0x1
	bl BattleSamplingEnemy
	lbz r0, 0x1578(r1)
	extsb. r0, r0
	bgt @21
	lwz r5, 0x7c(r15)
	mr r3, r15
	mr r4, r22
	bl evtSetValue
	li r3, 0x2
	b @4
	@21:
	lwz r4, 0x7c(r18)
	addi r3, r1, 0xb0c
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	li r21, 0x1
	bl BattleChoiceSamplingEnemy
	lwz r3, 0xc(r1)
	addi r0, r16, 0x1
	li r5, 0x1
	mr r7, r16
	stw r3, 0x8(r23)
	mulli r3, r16, 0xe8
	li r4, 0x0
	lwz r6, 0x8(r1)
	stw r6, 0xc(r23)
	stb r5, 0x14(r23)
	mtctr r0
	cmpwi r16, 0x0
	blt @20
	@22:
	addi r6, r3, 0x4
	add r6, r14, r6
	cmplw r23, r6
	beq @23
	lwz r0, 0x4(r6)
	cmpwi r0, 0x0
	bne @23
	lwz r5, 0x8(r23)
	lwz r0, 0x8(r6)
	cmpw r5, r0
	bne @23
	stb r4, 0x14(r6)
	@23:
	subi r7, r7, 0x1
	subi r3, r3, 0xe8
	bdnz @22
	@20:
	addi r16, r16, 0x1
	addi r24, r24, 0xe8
	@5:
	lbz r0, 0x0(r14)
	cmpw r16, r0
	blt @6
	cmpwi r21, 0x0
	bne @24
	lwz r5, 0x7c(r15)
	mr r3, r15
	mr r4, r22
	bl evtSetValue
	li r3, 0x2
	b @4
	@24:
	li r16, 0x0
	li r24, 0x0
	b @25
	@26:
	addi r17, r24, 0x4
	add r17, r14, r17
	lwz r0, 0x4(r17)
	addi r23, r17, 0x28
	cmpwi r0, 0x0
	bne @27
	lbz r0, 0x14(r17)
	li r26, 0x0
	cmplwi r0, 0x0
	beq @28
	ori r26, r26, 0x100
	@28:
	lbz r0, 0x15(r17)
	cmplwi r0, 0x0
	beq @29
	oris r26, r26, 0x10
	@29:
	lwz r3, 0x8(r17)
	lwz r4, 0xc(r17)
	bl BattleGetUnitPartsPtr
	lwz r4, 0x8(r17)
	mr r21, r3
	mr r3, r25
	bl BattleGetUnitPtr
	mr r18, r3
	mr r3, r25
	bl BattleGetSystemPtr
	mr r4, r18
	mr r5, r21
	mr r6, r23
	mr r7, r26
	bl BattlePreCheckDamage
	stw r3, 0x1c(r17)
	lwz r0, 0x1c(r17)
	cmpwi r0, 0x1
	bne @27
	lbz r0, 0x14(r17)
	cmplwi r0, 0x0
	bne @27
	li r3, 0x0
	bl irand
	extsh r18, r3
	li r21, 0x0
	li r26, 0x0
	li r27, 0x1
	b @30
	@31:
	addi r23, r26, 0x4
	lwz r3, 0x8(r17)
	add r23, r14, r23
	lwz r0, 0x8(r23)
	cmpw r3, r0
	bne @32
	sth r18, 0x10(r23)
	li r3, 0x16
	bl irand
	lbz r0, 0x14(r23)
	add r3, r3, r18
	addi r3, r3, 0x14
	cmplwi r0, 0x0
	extsh r18, r3
	beq @32
	stb r27, 0x15(r23)
	@32:
	addi r21, r21, 0x1
	addi r26, r26, 0xe8
	@30:
	cmpw r21, r16
	blt @31
	@27:
	addi r16, r16, 0x1
	addi r24, r24, 0xe8
	@25:
	lbz r0, 0x0(r14)
	cmpw r16, r0
	blt @26
	@1:
	addi r29, r30, 0x114
	addi r0, r30, 0x150
	lwz r27, 0x78(r15)
	addi r14, r30, 0x130
	stw r29, 0x15f4(r1)
	addi r28, r1, 0x14
	li r24, 0x1
	li r26, 0x0
	stw r0, 0x15f0(r1)
	li r31, 0x0
	b @33
	@34:
	addi r21, r31, 0x4
	add r21, r27, r21
	lbz r0, 0x0(r21)
	extsb r0, r0
	cmpwi r0, -0x1
	beq @35
	lwz r0, 0x4(r21)
	li r23, 0x0
	li r24, 0x0
	cmpwi r0, 0x0
	bne @36
	lwz r4, 0x8(r21)
	mr r3, r25
	bl BattleGetUnitPtr
	mr r0, r3
	lwz r3, 0x8(r21)
	lwz r4, 0xc(r21)
	mr r20, r0
	bl BattleGetUnitPartsPtr
	mr r19, r3
	@36:
	lwz r3, 0x24(r21)
	cmplwi r3, 0x0
	beq @37
	lha r0, 0x10(r21)
	cmpwi r0, 0x0
	ble @38
	@37:
	lha r3, 0x10(r21)
	subi r0, r3, 0x1
	sth r0, 0x10(r21)
	lha r0, 0x10(r21)
	cmpwi r0, 0x0
	bgt @35
	lwz r0, 0x4(r21)
	cmpwi r0, 0x1
	beq @39
	bge @40
	cmpwi r0, 0x0
	bge @41
	b @40
	@41:
	mr r3, r20
	mr r4, r19
	addi r6, r1, 0x2c
	addi r7, r1, 0x30
	addi r5, r1, 0x28
	bl BtlUnit_GetHitPos
	mr r3, r20
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x15dc(r1)
	lfd f1, 0x168(r30)
	stw r0, 0x15d8(r1)
	lfd f0, 0x15d8(r1)
	fsubs f30, f0, f1
	b @42
	@39:
	lwz r5, 0x8(r21)
	li r4, 0x14
	lis r0, 0x4330
	lfd f1, 0x168(r30)
	divw r3, r5, r4
	stw r0, 0x15d8(r1)
	mullw r0, r3, r4
	subf r0, r0, r5
	mulli r3, r0, 0x19
	subi r0, r3, 0xe6
	xoris r0, r0, 0x8000
	stw r0, 0x15dc(r1)
	lfd f0, 0x15d8(r1)
	fsubs f0, f0, f1
	stfs f0, 0x28(r1)
	bl BattleStageGetPtr
	lfs f0, 0xb34(r3)
	lis r0, 0x4330
	li r6, 0x14
	stw r0, 0x15e0(r1)
	lfd f2, 0x168(r30)
	li r3, 0x0
	stfs f0, 0x2c(r1)
	li r4, 0x6
	lfs f3, float_0p1_8041cd00(r0)
	lwz r7, 0x8(r21)
	stw r0, 0x15e8(r1)
	divw r5, r7, r6
	mullw r0, r5, r6
	mulli r5, r5, 0x1e
	subf r6, r0, r7
	addi r0, r5, 0x73
	xoris r5, r6, 0x8000
	xoris r0, r0, 0x8000
	stw r5, 0x15e4(r1)
	stw r0, 0x15ec(r1)
	lfd f1, 0x15e0(r1)
	lfd f0, 0x15e8(r1)
	fsubs f1, f1, f2
	fsubs f0, f0, f2
	fmadds f0, f3, f1, f0
	stfs f0, 0x30(r1)
	bl btl_camera_set_mode
	li r3, 0x0
	li r4, 0x2
	bl btl_camera_set_moveSpeedLv
	lfs f30, float_0_8041cd04(r0)
	b @42
	@40:
	lwz r4, 0x108(r30)
	lwz r3, 0x10c(r30)
	lwz r0, 0x110(r30)
	stw r4, 0x28(r1)
	lfs f30, float_0_8041cd04(r0)
	stw r3, 0x2c(r1)
	stw r0, 0x30(r1)
	@42:
	lwz r5, 0x28(r1)
	mr r3, r25
	lwz r4, 0x2c(r1)
	lwz r0, 0x30(r1)
	stw r5, 0x34(r1)
	stw r4, 0x38(r1)
	lfs f1, 0x34(r1)
	stw r0, 0x3c(r1)
	lfs f2, 0x38(r1)
	lfs f3, 0x3c(r1)
	bl BattleGetFloorHeight
	lfs f2, 0x28(r1)
	lfs f0, float_0_8041cd04(r0)
	stfs f1, 0x38(r1)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @43
	lfs f31, float_90_8041cd08(r0)
	b @44
	@43:
	lfs f31, float_270_8041cd0c(r0)
	@44:
	lwz r0, 0x1c(r21)
	cmpwi r0, 0x5
	beq @45
	bge @46
	cmpwi r0, 0x2
	bge @47
	b @45
	@46:
	cmpwi r0, 0x7
	bge @45
	@47:
	lfs f0, 0x38(r1)
	stfs f0, 0x2c(r1)
	@45:
	li r3, -0x1
	li r0, 0x0
	stw r3, 0x20(r21)
	sth r0, 0x12(r21)
	lbz r0, 0x1(r21)
	extsb r0, r0
	cmplwi r0, 0x8
	bgt @35
	lis r3, jumptable_80374848@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80374848@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@48:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f1, 0x34(r1)
	li r3, 0x4
	fsubs f5, f0, f2
	lfs f3, 0x3c(r1)
	li r4, 0x1
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@49:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f1, 0x34(r1)
	li r3, 0x5
	fsubs f5, f0, f2
	lfs f3, 0x3c(r1)
	li r4, 0x1
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@50:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f1, 0x34(r1)
	li r3, 0x0
	fsubs f5, f0, f2
	lfs f3, 0x3c(r1)
	li r4, 0x64
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@51:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f1, 0x34(r1)
	li r3, 0x1
	fsubs f5, f0, f2
	lfs f3, 0x3c(r1)
	li r4, 0x1
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@52:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f7, float_5_8041cd10(r0)
	li r3, 0x2
	lfs f3, 0x3c(r1)
	fsubs f5, f0, f2
	lfs f1, 0x34(r1)
	fadds f3, f7, f3
	li r4, 0x1
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@53:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f1, 0x34(r1)
	li r3, 0x8
	fsubs f5, f0, f2
	lfs f3, 0x3c(r1)
	li r4, 0x1
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@54:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f1, 0x34(r1)
	li r3, 0x3
	fsubs f5, f0, f2
	lfs f3, 0x3c(r1)
	li r4, 0x1
	li r5, 0x5a
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@55:
	mr r3, r20
	bl BtlUnit_GetBelong
	extsb. r0, r3
	bne @56
	lfs f4, float_0_8041cd04(r0)
	fmr f6, f31
	lfs f2, float_15_8041cd18(r0)
	li r3, 0x6
	lfs f0, 0x3c(r1)
	fmr f5, f4
	lfs f1, float_neg300_8041cd14(r0)
	fadds f3, f2, f0
	lfs f2, 0x38(r1)
	li r4, 0x1
	li r5, 0xb4
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@56:
	lfs f4, float_0_8041cd04(r0)
	fmr f6, f31
	lfs f2, float_15_8041cd18(r0)
	li r3, 0x6
	lfs f0, 0x3c(r1)
	fmr f5, f4
	lfs f1, float_300_8041cd1c(r0)
	fadds f3, f2, f0
	lfs f2, 0x38(r1)
	li r4, 0x1
	li r5, 0xb4
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@57:
	lfs f2, 0x38(r1)
	fmr f4, f30
	lfs f0, 0x2c(r1)
	fmr f6, f31
	lfs f7, float_5_8041cd10(r0)
	li r3, 0x7
	lfs f3, 0x3c(r1)
	fsubs f5, f0, f2
	lfs f1, 0x34(r1)
	fadds f3, f7, f3
	li r4, 0x1
	li r5, 0xb4
	bl effFallEntry
	stw r3, 0x24(r21)
	b @35
	@38:
	cmplwi r3, 0x0
	beq @58
	bl effFallCheckHit
	cmpwi r3, 0x0
	beq @35
	@58:
	lwz r0, 0x4(r21)
	addi r18, r21, 0x28
	cmpwi r0, 0x1
	bne @59
	lbz r4, 0x1(r21)
	lwz r3, 0x8(r21)
	bl BattleAudience_Case_FallObject_Aud
	lwz r3, 0x20(r21)
	bl psndSFXOff
	lwz r3, 0x8(r21)
	addi r5, r1, 0x20
	addi r6, r1, 0x24
	addi r4, r1, 0x1c
	bl BattleAudience_GetHomePosition
	lbz r0, 0x1(r21)
	extsb r0, r0
	cmpwi r0, 0x5
	beq @60
	bge @61
	cmpwi r0, 0x2
	bge @61
	cmpwi r0, 0x0
	bge @62
	b @61
	@62:
	mr r3, r29
	addi r4, r1, 0x1c
	bl psndSFXOn_3D
	b @60
	@61:
	mr r3, r14
	addi r4, r1, 0x1c
	bl psndSFXOn_3D
	b @60
	@59:
	bl BattleAudience_Case_FallObject_Stage
	lwz r0, 0x64(r18)
	rlwinm. r0, r0, 0, 7, 7
	beq @63
	mr r3, r20
	mr r4, r19
	addi r6, r1, 0x20
	addi r7, r1, 0x24
	addi r5, r1, 0x1c
	bl BtlUnit_GetHitPos
	lbz r0, 0x14(r21)
	li r16, 0x0
	cmplwi r0, 0x0
	beq @64
	ori r16, r16, 0x100
	@64:
	lwz r3, 0x20(r21)
	bl psndSFXOff
	lwz r0, 0x1c(r21)
	cmpwi r0, 0x5
	beq @60
	bge @65
	cmpwi r0, 0x1
	beq @66
	bge @67
	b @60
	@65:
	cmpwi r0, 0x7
	bge @60
	@67:
	lbz r0, 0x1(r21)
	extsb r0, r0
	cmpwi r0, 0x5
	beq @60
	bge @60
	cmpwi r0, 0x2
	bge @60
	cmpwi r0, 0x0
	bge @68
	b @60
	@68:
	mr r3, r29
	addi r4, r1, 0x1c
	bl psndSFXOn_3D
	b @60
	@66:
	lbz r0, 0x1(r21)
	extsb r0, r0
	cmpwi r0, 0x5
	beq @69
	bge @70
	cmpwi r0, 0x2
	bge @70
	cmpwi r0, 0x0
	bge @71
	b @70
	@71:
	lwz r3, 0x15f4(r1)
	addi r4, r1, 0x1c
	bl psndSFXOn_3D
	b @72
	@69:
	lwz r3, 0x15f0(r1)
	addi r4, r1, 0x1c
	bl psndSFXOn_3D
	b @72
	@70:
	mr r3, r14
	addi r4, r1, 0x1c
	bl psndSFXOn_3D
	@72:
	mr r3, r20
	bl BtlUnit_GetACPossibility
	cmpwi r3, 0x0
	beq @73
	mr r3, r20
	mr r4, r18
	bl BattleActionCommandCheckDefence
	@73:
	mr r3, r25
	bl BattleGetSystemPtr
	mr r4, r20
	mr r5, r19
	mr r6, r18
	mr r7, r16
	bl BattleCheckDamage
	b @60
	@63:
	lwz r3, 0x20(r21)
	bl psndSFXOff
	mr r3, r25
	bl BattleGetSystemPtr
	lbz r0, 0x12(r25)
	mr r4, r18
	lwz r5, 0x0(r3)
	addi r3, r1, 0x40
	neg r0, r0
	lwz r7, 0x64(r18)
	lwz r8, 0x68(r18)
	extsb r9, r0
	li r6, 0x1
	bl BattleSamplingEnemy
	lbz r0, 0xaac(r1)
	extsb. r0, r0
	ble @60
	@74:
	lbz r3, 0xaf7(r1)
	lbz r0, 0xaac(r1)
	extsb r3, r3
	extsb r0, r0
	cmpw r3, r0
	bge @60
	addi r0, r3, 0xa6d
	addi r4, r1, 0x40
	lbzx r0, r4, r0
	mr r3, r25
	extsb r0, r0
	mulli r4, r0, 0x24
	addi r0, r1, 0x40
	addi r17, r4, 0x4
	add r17, r0, r17
	lha r4, 0x0(r17)
	bl BattleGetUnitPtr
	mr r0, r3
	lha r3, 0x0(r17)
	lha r4, 0x2(r17)
	mr r16, r0
	bl BattleGetUnitPartsPtr
	stw r3, 0x15f8(r1)
	mr r3, r25
	bl BattleGetSystemPtr
	lwz r5, 0x15f8(r1)
	mr r4, r16
	mr r6, r18
	li r7, 0x100
	bl BattlePreCheckDamage
	cmpwi r3, 0x4
	beq @75
	bge @76
	cmpwi r3, 0x2
	beq @75
	bge @77
	cmpwi r3, 0x1
	bge @78
	b @75
	@76:
	cmpwi r3, 0x6
	beq @79
	b @75
	@77:
	mr r3, r16
	mr r5, r28
	addi r6, r1, 0x18
	addi r4, r1, 0x10
	bl BtlUnit_GetPos
	lfs f1, 0x0(r28)
	lfs f0, float_85_8041cd20(r0)
	fcmpo cr0, f1, f0
	bge @80
	lfs f0, float_50_8041cd24(r0)
	fadds f0, f1, f0
	stfs f0, 0x0(r28)
	b @81
	@80:
	lfs f0, float_neg50_8041cd28(r0)
	fadds f0, f1, f0
	stfs f0, 0x0(r28)
	@81:
	lfs f1, 0x10(r1)
	li r3, 0x6
	lfs f0, float_45_8041cd2c(r0)
	lfs f2, 0x0(r28)
	fsubs f1, f1, f0
	lfs f3, 0x18(r1)
	stfs f1, 0x10(r1)
	bl effNiceEntry
	lwz r5, 0xc(r3)
	li r0, 0x0
	lfs f0, float_0p75_8041cd30(r0)
	mr r3, r16
	li r4, 0x126
	stfs f0, 0x1c(r5)
	stw r0, 0x270(r16)
	bl BattleRunHitEvent
	b @75
	@79:
	li r0, 0x0
	mr r3, r16
	stw r0, 0x270(r16)
	li r4, 0x127
	bl BattleRunHitEvent
	b @75
	@78:
	mr r3, r16
	bl BtlUnit_GetACPossibility
	cmpwi r3, 0x0
	beq @82
	cmpwi r23, 0x0
	bgt @82
	mr r3, r16
	mr r4, r18
	bl BattleActionCommandCheckDefence
	addi r23, r23, 0x1
	@82:
	lha r3, 0x0(r17)
	lha r4, 0x2(r17)
	bl BattleGetUnitPartsPtr
	mr r17, r3
	mr r3, r25
	bl BattleGetSystemPtr
	mr r4, r16
	mr r5, r17
	mr r6, r18
	li r7, 0x100
	bl BattleCheckDamage
	@75:
	lbz r3, 0xaf7(r1)
	addi r0, r3, 0x1
	stb r0, 0xaf7(r1)
	b @74
	@60:
	li r0, -0x1
	stb r0, 0x0(r21)
	@35:
	addi r26, r26, 0x1
	addi r31, r31, 0xe8
	@33:
	lbz r0, 0x0(r27)
	cmpw r26, r0
	blt @34
	cmpwi r24, 0x0
	bne @83
	li r3, 0x0
	b @4
	@83:
	lwz r3, 0x78(r15)
	bl BattleFree
	lwz r5, 0x7c(r15)
	mr r3, r15
	mr r4, r22
	bl evtSetValue
	li r3, 0x2
	@4:
	li r0, 0x1668
	psq_lx f31, r1, r0, 0, 0
	lfd f31, 0x1660(r1)
	li r0, 0x1658
	psq_lx f30, r1, r0, 0, 0
	lfd f30, 0x1650(r1)
	lmw r14, 0x1608(r1)
	lwz r0, 0x1674(r1)
	mtlr r0
	addi r1, r1, 0x1670
	blr
}

asm s32 _object_fall_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	bl BattleWaitAllActiveEvtEnd_NoBgSetEndWait
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, -0x7d68(r31)
	cmpwi r3, 0x0
	beq @3
	bl evtCheckID
	cmpwi r3, 0x0
	beq @4
	li r3, 0x0
	b @2
	@4:
	li r0, 0x0
	stw r0, -0x7d68(r31)
	@3:
	lwz r3, -0x7d58(r31)
	cmpwi r3, 0x0
	beq @5
	bl evtCheckID
	cmpwi r3, 0x0
	beq @6
	li r3, 0x0
	b @2
	@6:
	li r0, 0x0
	stw r0, -0x7d58(r31)
	@5:
	lwz r3, -0x7f20(r31)
	cmpwi r3, 0x0
	beq @7
	bl evtCheckID
	cmpwi r3, 0x0
	beq @8
	li r3, 0x0
	b @2
	@8:
	li r0, 0x0
	stw r0, -0x7f20(r31)
	@7:
	li r3, 0x2
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 BattleStage_ObjectFallCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	lwz r0, 0xef4(r3)
	addis r31, r3, 0x2
	rlwinm. r0, r0, 0, 19, 19
	beq @1
	li r3, 0x0
	b @2
	@1:
	lis r3, _object_fall_event@ha
	li r4, 0xa
	addi r3, r3, _object_fall_event@l
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, -0x7d54(r31)
	lwz r3, 0x15c(r3)
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 _nozzle_work_get_weapon_address(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	lwz r4, _battleWorkPointer(r0)
	lwz r30, 0x18(r3)
	addis r31, r4, 0x2
	lwz r4, 0x0(r30)
	subi r31, r31, 0x7f40
	bl evtGetValue
	slwi r0, r3, 2
	lwz r4, 0x4(r30)
	add r5, r31, r0
	mr r3, r29
	lwz r5, 0x3c(r5)
	bl evtSetValue
	lmw r29, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void _combine_nozzle_weapon(BOOL copy, BattleWeapon* dst, BattleWeapon* src) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r3, 0x0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	beq @1
	li r0, 0x18
	subi r6, r4, 0x4
	subi r4, r5, 0x4
	mtctr r0
	@2:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r6)
	stwu r0, 0x8(r6)
	bdnz @2
	b @3
	@1:
	lbz r3, 0x11(r4)
	lbz r0, 0x11(r5)
	add r0, r3, r0
	stb r0, 0x11(r4)
	lbz r3, 0x12(r4)
	lbz r0, 0x12(r5)
	add r0, r3, r0
	stb r0, 0x12(r4)
	lwz r0, 0x1c(r4)
	cmplwi r0, 0x0
	bne @4
	lwz r0, 0x1c(r5)
	stw r0, 0x1c(r4)
	@4:
	li r0, 0x8
	li r3, 0x0
	mtctr r0
	@5:
	addi r7, r3, 0x20
	addi r3, r3, 0x4
	lwzx r6, r4, r7
	lwzx r0, r5, r7
	add r0, r6, r0
	stwx r0, r4, r7
	bdnz @5
	lbz r0, 0x6c(r5)
	addi r30, r5, 0x80
	addi r31, r4, 0x80
	stb r0, 0x6c(r4)
	mr r3, r31
	mr r5, r30
	addi r4, r31, 0x1
	addi r6, r30, 0x1
	bl _rate_mix
	addi r3, r31, 0x2
	addi r4, r31, 0x3
	addi r5, r30, 0x2
	addi r6, r30, 0x3
	bl _rate_mix
	addi r3, r31, 0x4
	addi r4, r31, 0x5
	addi r5, r30, 0x4
	addi r6, r30, 0x5
	bl _rate_mix
	addi r3, r31, 0x6
	addi r4, r31, 0x7
	addi r5, r30, 0x6
	addi r6, r30, 0x8
	bl _rate_mix
	addi r3, r31, 0x9
	addi r4, r31, 0xa
	addi r5, r30, 0x9
	addi r6, r30, 0xa
	bl _rate_mix
	addi r3, r31, 0xb
	addi r4, r31, 0xc
	addi r5, r30, 0xb
	addi r6, r30, 0xc
	bl _rate_mix
	addi r3, r31, 0xd
	addi r4, r31, 0xe
	addi r5, r30, 0xd
	addi r6, r30, 0xe
	bl _rate_mix
	addi r3, r31, 0xf
	addi r4, r31, 0x10
	addi r5, r30, 0xf
	addi r6, r30, 0x10
	bl _rate_mix
	addi r3, r31, 0x11
	addi r4, r31, 0x12
	addi r5, r30, 0x11
	addi r6, r30, 0x12
	bl _rate_mix
	addi r3, r31, 0x13
	addi r4, r31, 0x14
	addi r5, r31, 0x15
	addi r6, r30, 0x13
	addi r7, r30, 0x14
	addi r8, r30, 0x15
	bl _rate_mix_3
	addi r3, r31, 0x19
	addi r4, r31, 0x1a
	addi r5, r31, 0x1b
	addi r6, r30, 0x19
	addi r7, r30, 0x1a
	addi r8, r30, 0x1b
	bl _rate_mix_3
	addi r3, r31, 0x1c
	addi r4, r31, 0x1d
	addi r5, r30, 0x1c
	addi r6, r30, 0x1d
	bl _rate_mix
	lbz r7, 0x1f(r31)
	addi r3, r31, 0x20
	lbz r0, 0x1f(r30)
	addi r4, r31, 0x21
	addi r5, r30, 0x20
	addi r6, r30, 0x21
	add r0, r7, r0
	stb r0, 0x1f(r31)
	bl _rate_mix
	addi r3, r31, 0x22
	addi r4, r31, 0x23
	addi r5, r30, 0x22
	addi r6, r30, 0x23
	bl _rate_mix
	lbz r3, 0x2a(r31)
	lbz r0, 0x2a(r30)
	add r0, r3, r0
	stb r0, 0x2a(r31)
	lbz r3, 0x2b(r31)
	lbz r0, 0x2b(r30)
	add r0, r3, r0
	stb r0, 0x2b(r31)
	lbz r3, 0x2c(r31)
	lbz r0, 0x2c(r30)
	add r0, r3, r0
	stb r0, 0x2c(r31)
	lbz r3, 0x2d(r31)
	lbz r0, 0x2d(r30)
	add r0, r3, r0
	stb r0, 0x2d(r31)
	@3:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _rate_mix_3(s8* dstChance, s8* dstTime, s8* dstStrength, s8* srcChance, s8* srcTime, s8* srcStrength) {
	nofralloc
	lbz r9, 0x0(r6)
	extsb. r0, r9
	blelr
	lbz r0, 0x0(r3)
	extsb r6, r9
	extsb r0, r0
	cmpw r6, r0
	ble @1
	stb r9, 0x0(r3)
	@1:
	lbz r6, 0x0(r4)
	lbz r0, 0x0(r7)
	add r0, r6, r0
	stb r0, 0x0(r4)
	lbz r6, 0x0(r5)
	lbz r0, 0x0(r8)
	add r0, r6, r0
	stb r0, 0x0(r5)
	lbz r0, 0x0(r5)
	extsb. r0, r0
	bnelr
	li r0, 0x0
	stb r0, 0x0(r3)
	stb r0, 0x0(r4)
	blr
}

asm void _rate_mix(s8* dstChance, s8* dstTime, s8* srcChance, s8* srcTime) {
	nofralloc
	lbz r7, 0x0(r5)
	extsb. r0, r7
	blelr
	lbz r0, 0x0(r3)
	extsb r5, r7
	extsb r0, r0
	cmpw r5, r0
	ble @1
	stb r7, 0x0(r3)
	@1:
	lbz r3, 0x0(r4)
	lbz r0, 0x0(r6)
	add r0, r3, r0
	stb r0, 0x0(r4)
	blr
}

asm s32 _get_nozzle_attack_index(u8 index) {
	nofralloc
	clrlwi r0, r3, 24
	lwz r4, _battleWorkPointer(r0)
	cmpwi r0, 0x1
	addis r5, r4, 0x2
	subi r5, r5, 0x7f40
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @4
	@2:
	cmpwi r0, 0x3
	bge @4
	b @5
	@3:
	add r4, r5, r0
	lbz r0, 0x1c4(r4)
	cmpwi r0, 0x2
	beq @6
	bge @7
	cmpwi r0, 0x1
	bge @8
	b @5
	@7:
	cmpwi r0, 0x4
	bge @5
	b @9
	@8:
	li r3, -0x1
	blr
	@6:
	li r3, 0x0
	blr
	@9:
	li r3, 0x1
	blr
	@5:
	clrlwi r0, r3, 24
	add r4, r5, r0
	lbz r0, 0x1c4(r4)
	cmpwi r0, 0x2
	beq @10
	bge @11
	cmpwi r0, 0x1
	bge @12
	b @1
	@11:
	cmpwi r0, 0x4
	bge @1
	b @13
	@12:
	li r3, 0x0
	blr
	@10:
	li r3, 0x1
	blr
	@13:
	li r3, -0x1
	blr
	@1:
	clrlwi r0, r3, 24
	add r3, r5, r0
	lbz r0, 0x1c4(r3)
	cmpwi r0, 0x2
	beq @14
	bge @15
	cmpwi r0, 0x1
	bge @16
	b @4
	@15:
	cmpwi r0, 0x4
	bge @4
	b @17
	@16:
	li r3, 0x0
	blr
	@14:
	li r3, -0x1
	blr
	@17:
	li r3, 0x1
	blr
	@4:
	li r3, -0x1
	blr
}

asm s32 _nozzle_work_attack_set(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	li r5, 0xc0
	stw r0, 0x14(r1)
	li r0, 0x0
	stmw r30, 0x8(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	stw r0, -0x7f04(r31)
	subi r3, r31, 0x7efc
	stw r0, -0x7f00(r31)
	subi r31, r31, 0x7f40
	bl memset
	addi r3, r31, 0x104
	li r4, 0x0
	li r5, 0xc0
	bl memset
	lis r3, _nozzle_at_base_mario@ha
	addi r4, r31, 0x44
	addi r5, r3, _nozzle_at_base_mario@l
	li r3, 0x1
	bl _combine_nozzle_weapon
	lis r3, _nozzle_at_base_monster@ha
	addi r4, r31, 0x104
	addi r5, r3, _nozzle_at_base_monster@l
	li r3, 0x1
	bl _combine_nozzle_weapon
	li r30, 0x0
	@1:
	clrlwi r3, r30, 24
	bl _get_nozzle_attack_index
	cmpwi r3, 0x0
	blt @2
	slwi r4, r3, 2
	addi r4, r4, 0x3c
	lwzx r0, r31, r4
	cmplwi r0, 0x0
	bne @3
	mulli r3, r3, 0xc0
	addi r0, r3, 0x44
	add r0, r31, r0
	stwx r0, r31, r4
	@3:
	lbz r0, 0x1ca(r31)
	li r3, 0x0
	lwz r6, 0x34(r31)
	extsb r0, r0
	lwzx r4, r31, r4
	mulli r5, r0, 0xc0
	addi r5, r5, 0x10
	add r5, r6, r5
	bl _combine_nozzle_weapon
	@2:
	addi r30, r30, 0x1
	cmpwi r30, 0x3
	blt @1
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL BattleFogForceStop(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	lwz r0, -0x7d64(r31)
	cmpwi r0, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, -0x7d60(r31)
	cmplwi r3, 0x0
	beq @3
	bl effSoftDelete
	li r0, 0x0
	stw r0, -0x7d60(r31)
	@3:
	li r3, 0x1
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL BattleFogEndCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	lwz r3, -0x7d64(r31)
	cmpwi r3, 0x0
	bne @1
	li r3, 0x1
	b @2
	@1:
	subi r0, r3, 0x1
	stw r0, -0x7d64(r31)
	lwz r0, -0x7d64(r31)
	cmpwi r0, 0x0
	ble @3
	li r3, 0x0
	b @2
	@3:
	lwz r3, -0x7d60(r31)
	cmplwi r3, 0x0
	beq @4
	bl effSoftDelete
	li r0, 0x0
	stw r0, -0x7d60(r31)
	@4:
	li r3, 0x1
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 _nozzle_work_effect(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stmw r23, 0xc(r1)
	mr r25, r3
	lwz r6, _battleWorkPointer(r0)
	lwz r26, 0x18(r3)
	mr r23, r4
	lis r5, vec3_802f3ac8@ha
	mr r24, r6
	lwz r4, 0x0(r26)
	addi r30, r5, vec3_802f3ac8@l
	addis r29, r6, 0x2
	li r27, 0x0
	bl evtGetValue
	cmpwi r23, 0x0
	lwz r26, 0x4(r26)
	mr r31, r3
	li r23, 0x0
	beq @1
	mr r3, r24
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq @2
	mr r3, r25
	mr r4, r26
	li r5, 0x0
	bl evtSetValue
	li r3, 0x2
	b @3
	@2:
	li r0, 0x5a
	stw r0, 0x78(r25)
	lbz r0, -0x7d76(r29)
	extsb r0, r0
	cmpwi r0, 0x2
	beq @4
	bge @5
	cmpwi r0, 0x1
	bge @6
	b @7
	@5:
	cmpwi r0, 0x4
	bge @7
	b @8
	@6:
	addi r28, r30, 0x170
	li r27, 0x0
	b @7
	@4:
	li r28, 0x0
	li r27, 0x1
	b @7
	@8:
	addi r28, r30, 0x188
	li r27, 0x2
	@7:
	cmpwi r0, 0x4
	bge @9
	cmpwi r0, 0x1
	bge @10
	b @9
	@10:
	addi r3, r30, 0xc0
	bl BattleSearchObjectPtr
	mr r24, r3
	li r3, 0x0
	bl _get_nozzle_dir
	lbz r0, -0x7d7c(r29)
	fmr f29, f1
	cmplwi r0, 0x0
	beq @11
	cmplwi r28, 0x0
	beq @12
	mr r3, r28
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	stw r3, 0x8c(r25)
	b @13
	@12:
	li r0, -0x1
	stw r0, 0x8c(r25)
	@13:
	lfs f0, float_90_8041cd08(r0)
	fadds f1, f0, f29
	bl reviseAngle
	fmr f31, f1
	fmr f1, f29
	bl sinfd
	lfs f2, float_10_8041cd34(r0)
	lfs f0, 0xc(r24)
	fmadds f30, f2, f1, f0
	fmr f1, f29
	bl cosfd
	lfs f4, float_10_8041cd34(r0)
	fmr f3, f30
	lfs f0, 0x4(r24)
	fmr f5, f31
	lfs f2, float_12_8041cd38(r0)
	mr r3, r27
	fnmsubs f1, f4, f1, f0
	lfs f0, 0x8(r24)
	li r4, 0x5a
	lfs f4, float_neg80_8041cd3c(r0)
	fadds f2, f2, f0
	bl effNozleEntry
	stw r3, 0x7c(r25)
	b @14
	@11:
	cmplwi r28, 0x0
	beq @15
	mr r3, r28
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	stw r3, 0x8c(r25)
	b @16
	@15:
	li r0, -0x1
	stw r0, 0x8c(r25)
	@16:
	lfs f4, float_0_8041cd04(r0)
	mr r3, r27
	lfs f2, float_20_8041cd40(r0)
	li r4, 0x5a
	lfs f1, 0x8(r24)
	fmr f5, f4
	lfs f3, float_8_8041cd44(r0)
	lfs f0, 0xc(r24)
	fadds f2, f2, f1
	lfs f1, 0x4(r24)
	fadds f3, f3, f0
	bl effNozleEntry
	cmpwi r31, 0x0
	stw r3, 0x7c(r25)
	bne @14
	lfs f2, float_20_8041cd40(r0)
	li r3, 0x4
	lfs f1, 0x8(r24)
	li r4, 0x5a
	lfs f3, float_8_8041cd44(r0)
	lfs f0, 0xc(r24)
	fadds f2, f2, f1
	lfs f1, 0x4(r24)
	fadds f3, f3, f0
	lfs f4, float_1_8041cd48(r0)
	bl effConfettiN64Entry
	@14:
	addi r3, r30, 0xcc
	bl BattleSearchObjectPtr
	mr r24, r3
	li r3, 0x1
	bl _get_nozzle_dir
	lbz r0, -0x7d7b(r29)
	fmr f29, f1
	cmplwi r0, 0x0
	beq @17
	cmplwi r28, 0x0
	beq @18
	mr r3, r28
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	stw r3, 0x90(r25)
	b @19
	@18:
	li r0, -0x1
	stw r0, 0x90(r25)
	@19:
	lfs f0, float_90_8041cd08(r0)
	fadds f1, f0, f29
	bl reviseAngle
	fmr f31, f1
	fmr f1, f29
	bl sinfd
	lfs f2, float_10_8041cd34(r0)
	lfs f0, 0xc(r24)
	fmadds f30, f2, f1, f0
	fmr f1, f29
	bl cosfd
	lfs f4, float_10_8041cd34(r0)
	fmr f3, f30
	lfs f0, 0x4(r24)
	fmr f5, f31
	lfs f2, float_12_8041cd38(r0)
	mr r3, r27
	fnmsubs f1, f4, f1, f0
	lfs f0, 0x8(r24)
	li r4, 0x5a
	lfs f4, float_neg80_8041cd3c(r0)
	fadds f2, f2, f0
	bl effNozleEntry
	stw r3, 0x80(r25)
	b @20
	@17:
	cmplwi r28, 0x0
	beq @21
	mr r3, r28
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	stw r3, 0x90(r25)
	b @22
	@21:
	li r0, -0x1
	stw r0, 0x90(r25)
	@22:
	lfs f4, float_0_8041cd04(r0)
	mr r3, r27
	lfs f2, float_20_8041cd40(r0)
	li r4, 0x5a
	lfs f1, 0x8(r24)
	fmr f5, f4
	lfs f3, float_8_8041cd44(r0)
	lfs f0, 0xc(r24)
	fadds f2, f2, f1
	lfs f1, 0x4(r24)
	fadds f3, f3, f0
	bl effNozleEntry
	cmpwi r31, 0x0
	stw r3, 0x80(r25)
	bne @20
	lfs f2, float_20_8041cd40(r0)
	li r3, 0x4
	lfs f1, 0x8(r24)
	li r4, 0x5a
	lfs f3, float_8_8041cd44(r0)
	lfs f0, 0xc(r24)
	fadds f2, f2, f1
	lfs f1, 0x4(r24)
	fadds f3, f3, f0
	lfs f4, float_1_8041cd48(r0)
	bl effConfettiN64Entry
	@20:
	addi r3, r30, 0xd8
	bl BattleSearchObjectPtr
	mr r30, r3
	li r3, 0x2
	bl _get_nozzle_dir
	lbz r0, -0x7d7a(r29)
	fmr f29, f1
	cmplwi r0, 0x0
	beq @23
	cmplwi r28, 0x0
	beq @24
	mr r3, r28
	addi r4, r30, 0x4
	bl psndSFXOn_3D
	stw r3, 0x94(r25)
	b @25
	@24:
	li r0, -0x1
	stw r0, 0x94(r25)
	@25:
	lfs f0, float_90_8041cd08(r0)
	fadds f1, f0, f29
	bl reviseAngle
	fmr f30, f1
	fmr f1, f29
	bl sinfd
	lfs f2, float_10_8041cd34(r0)
	lfs f0, 0xc(r30)
	fmadds f31, f2, f1, f0
	fmr f1, f29
	bl cosfd
	lfs f4, float_10_8041cd34(r0)
	fmr f3, f31
	lfs f0, 0x4(r30)
	fmr f5, f30
	lfs f2, float_12_8041cd38(r0)
	mr r3, r27
	fnmsubs f1, f4, f1, f0
	lfs f0, 0x8(r30)
	li r4, 0x5a
	lfs f4, float_neg80_8041cd3c(r0)
	fadds f2, f2, f0
	bl effNozleEntry
	stw r3, 0x84(r25)
	b @26
	@23:
	cmplwi r28, 0x0
	beq @27
	mr r3, r28
	addi r4, r30, 0x4
	bl psndSFXOn_3D
	stw r3, 0x94(r25)
	b @28
	@27:
	li r0, -0x1
	stw r0, 0x94(r25)
	@28:
	lfs f4, float_0_8041cd04(r0)
	mr r3, r27
	lfs f2, float_20_8041cd40(r0)
	li r4, 0x5a
	lfs f1, 0x8(r30)
	fmr f5, f4
	lfs f3, float_8_8041cd44(r0)
	lfs f0, 0xc(r30)
	fadds f2, f2, f1
	lfs f1, 0x4(r30)
	fadds f3, f3, f0
	bl effNozleEntry
	cmpwi r31, 0x0
	stw r3, 0x84(r25)
	bne @26
	lfs f2, float_20_8041cd40(r0)
	li r3, 0x4
	lfs f1, 0x8(r30)
	li r4, 0x5a
	lfs f3, float_8_8041cd44(r0)
	lfs f0, 0xc(r30)
	fadds f2, f2, f1
	lfs f1, 0x4(r30)
	fadds f3, f3, f0
	lfs f4, float_1_8041cd48(r0)
	bl effConfettiN64Entry
	@26:
	li r23, 0x1
	b @29
	@9:
	cmpwi r31, 0x0
	beq @29
	lwz r0, -0x7d60(r29)
	cmplwi r0, 0x0
	bne @29
	li r0, 0x78
	lfs f1, float_0_8041cd04(r0)
	stw r0, 0x78(r25)
	li r0, 0x0
	fmr f2, f1
	li r3, 0x3
	stw r0, 0x7c(r25)
	fmr f3, f1
	fmr f4, f1
	li r4, 0x3e8
	stw r0, 0x84(r25)
	fmr f5, f1
	stw r0, 0x80(r25)
	bl effNozleEntry
	stw r3, -0x7d60(r29)
	li r0, 0x2
	addi r3, r30, 0xcc
	lwz r4, -0x7d60(r29)
	stw r4, 0x84(r25)
	stw r0, -0x7d64(r29)
	bl BattleSearchObjectPtr
	mr r4, r3
	addi r3, r30, 0x19c
	addi r4, r4, 0x4
	bl psndSFXOn_3D
	stw r3, 0x8c(r25)
	li r0, -0x1
	li r23, 0x1
	stw r0, 0x90(r25)
	stw r0, 0x94(r25)
	@29:
	cmpwi r23, 0x0
	bne @1
	mr r3, r25
	mr r4, r26
	li r5, 0x0
	bl evtSetValue
	li r3, 0x2
	b @3
	@1:
	lwz r3, 0x78(r25)
	cmpwi r3, 0x0
	ble @30
	subi r0, r3, 0x1
	stw r0, 0x78(r25)
	lwz r0, 0x78(r25)
	cmpwi r0, 0x0
	bgt @31
	lwz r3, 0x8c(r25)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @32
	bl psndSFXOff
	@32:
	lwz r3, 0x90(r25)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @33
	bl psndSFXOff
	@33:
	lwz r3, 0x94(r25)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @31
	bl psndSFXOff
	@31:
	li r3, 0x0
	b @3
	@30:
	mr r3, r25
	mr r4, r26
	li r5, 0x1
	bl evtSetValue
	li r3, 0x2
	@3:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lmw r23, 0xc(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm f32 _get_nozzle_dir(s32 index) {
	nofralloc
	lwz r4, _battleWorkPointer(r0)
	addis r0, r4, 0x2
	add r3, r0, r3
	lbz r0, -0x7d7c(r3)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x1
	bge @3
	b @1
	@2:
	cmpwi r0, 0x4
	bge @1
	b @4
	@3:
	lfs f1, float_neg45_8041cd4c(r0)
	blr
	@4:
	lfs f1, float_neg135_8041cd50(r0)
	blr
	@1:
	lfs f1, float_neg90_8041cd54(r0)
	blr
}

asm s32 _nozzle_work_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r28, r3, 0x2
	subi r28, r28, 0x7f40
	bl BattleWaitAllActiveEvtEnd_NoBgSetEndWait
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	li r31, 0x0
	li r27, 0x0
	mr r30, r31
	@3:
	addi r29, r31, 0x1cc
	lwzx r3, r28, r29
	cmpwi r3, 0x0
	beq @4
	bl evtCheckID
	cmpwi r3, 0x0
	beq @5
	li r3, 0x0
	b @2
	@5:
	stwx r30, r28, r29
	@4:
	addi r27, r27, 0x1
	addi r31, r31, 0x4
	cmpwi r27, 0x3
	blt @3
	li r3, 0x2
	@2:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void _nozzle_type_init(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	lbz r0, -0x7d76(r31)
	lwz r30, -0x7f0c(r31)
	extsb r0, r0
	cmpwi r0, -0x1
	bne @1
	li r3, 0x0
	li r5, 0x0
	b @2
	@3:
	extsb r4, r5
	addi r5, r5, 0x1
	addi r0, r4, 0xc
	lbzx r0, r30, r0
	add r3, r3, r0
	@2:
	extsb r0, r5
	cmpwi r0, 0x4
	blt @3
	bl irand
	li r5, 0x0
	b @4
	@5:
	extsb r4, r5
	addi r0, r4, 0xc
	lbzx r0, r30, r0
	subf. r3, r0, r3
	blt @6
	addi r5, r5, 0x1
	@4:
	extsb r0, r5
	cmpwi r0, 0x4
	blt @5
	@6:
	stb r5, -0x7d76(r31)
	@1:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStage_NozzleWorkCheck(s32 type) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	lwz r4, _battleWorkPointer(r0)
	addis r31, r4, 0x2
	bl pouchGetPtr
	lha r0, 0x88(r3)
	cmpwi r0, 0x0
	ble @1
	bl _nozzle_type_init
	cmpwi r30, 0x0
	bne @2
	lbz r0, -0x7d76(r31)
	extsb. r0, r0
	beq @1
	@2:
	lwz r3, -0x7d68(r31)
	cmpwi r3, 0x0
	beq @3
	bl evtCheckID
	cmpwi r3, 0x0
	bne @3
	li r0, 0x0
	stw r0, -0x7d68(r31)
	@3:
	lwz r0, -0x7d68(r31)
	cmpwi r0, 0x0
	bne @1
	cmpwi r30, 0x0
	beq @4
	la r3, _nozzle_work_event_1(r0)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	b @5
	@4:
	la r3, _nozzle_work_event_0(r0)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	@5:
	lwz r0, 0x15c(r3)
	stw r0, -0x7d68(r31)
	@1:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 _fall_frame_delete(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	cmpwi r4, 0x0
	stw r0, 0x24(r1)
	stmw r30, 0x18(r1)
	mr r30, r3
	lwz r5, _battleWorkPointer(r0)
	addis r31, r5, 0x2
	beq @1
	li r0, 0xff
	stw r0, 0x80(r30)
	@1:
	lwz r5, 0x80(r30)
	lis r3, str_802F3C7C@ha
	addi r3, r3, str_802F3C7C@l
	addi r4, r1, 0xc
	subi r0, r5, 0x5
	stw r0, 0x80(r30)
	lwz r5, dat_8041ccfc(r0)
	lwz r0, 0x80(r30)
	stw r5, 0x8(r1)
	stb r0, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl mapGrpSetColor
	lwz r0, 0x80(r30)
	cmpwi r0, 0x0
	ble @2
	li r3, 0x0
	b @3
	@2:
	li r0, 0x0
	li r3, 0x2
	stw r0, -0x7d58(r31)
	@3:
	lmw r30, 0x18(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _fall_frame(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r30, r3
	mr r29, r4
	lwz r6, 0x18(r3)
	lis r3, str_802F3C7C@ha
	lwz r5, _battleWorkPointer(r0)
	addi r3, r3, str_802F3C7C@l
	lwz r31, 0x0(r6)
	addis r28, r5, 0x2
	bl BattleSearchObjectPtr
	cmpwi r29, 0x0
	mr r29, r3
	beq @1
	li r0, 0x0
	stw r0, 0x80(r30)
	lfs f0, 0x8(r29)
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x84(r30)
	@1:
	lwz r5, 0x80(r30)
	lis r4, double_to_int_802f3c30@ha
	lis r3, 0x4330
	lfd f1, double_to_int_802f3c30@l(r4)
	addi r5, r5, 0x1
	stw r3, 0x8(r1)
	li r0, 0x3c
	lfs f2, float_0_8041cd04(r0)
	stw r5, 0x80(r30)
	li r3, 0x2
	li r5, 0x3c
	lwz r4, 0x80(r30)
	lwz r6, 0x84(r30)
	mullw r4, r4, r4
	xoris r6, r6, 0x8000
	stw r6, 0xc(r1)
	lfd f0, 0x8(r1)
	divw r4, r4, r0
	fsubs f1, f0, f1
	bl intpl_sub
	stfs f1, 0x8(r29)
	lwz r0, 0x80(r30)
	cmpwi r0, 0x3c
	bge @2
	li r3, 0x0
	b @3
	@2:
	lwz r5, -0x7f08(r28)
	mr r3, r30
	mr r4, r31
	bl evtSetValue
	li r3, 0x2
	@3:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _fall_frame_wait_unit_ready(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	cmpwi r4, 0x0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	lwz r28, _battleWorkPointer(r0)
	beq @1
	li r29, 0x0
	@2:
	mr r3, r28
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r30, r3
	beq @3
	lwz r0, 0x1c(r30)
	clrrwi. r0, r0, 31
	bne @3
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne @3
	lwz r3, 0x2bc(r30)
	cmplwi r3, 0x0
	beq @3
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq @4
	lwz r0, 0x0(r30)
	stw r0, 0x160(r3)
	@4:
	lwz r0, 0x15c(r3)
	stw r0, 0x2c0(r30)
	@3:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt @2
	@1:
	li r29, 0x0
	mr r31, r29
	@5:
	mr r3, r28
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r30, r3
	beq @6
	lwz r0, 0x1c(r30)
	clrrwi. r0, r0, 31
	bne @6
	lwz r3, 0x2c0(r30)
	cmpwi r3, 0x0
	beq @7
	bl evtCheckID
	cmpwi r3, 0x0
	bne @7
	stw r31, 0x2c0(r30)
	@7:
	lwz r0, 0x2c0(r30)
	cmpwi r0, 0x0
	beq @6
	li r3, 0x0
	b @8
	@6:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt @5
	li r3, 0x2
	@8:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _fall_frame_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	bl BattleWaitAllActiveEvtEnd_NoBgSetEndWait
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, -0x7d68(r31)
	cmpwi r3, 0x0
	beq @3
	bl evtCheckID
	cmpwi r3, 0x0
	beq @4
	li r3, 0x0
	b @2
	@4:
	li r0, 0x0
	stw r0, -0x7d68(r31)
	@3:
	li r3, 0x1
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStage_IronFrameFallCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	lbz r3, -0x7f24(r31)
	rlwinm. r0, r3, 0, 25, 25
	bne @1
	rlwinm. r0, r3, 0, 26, 26
	bne @1
	ori r0, r3, 0x20
	lis r3, _fall_frame_event@ha
	stb r0, -0x7f24(r31)
	addi r3, r3, _fall_frame_event@l
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, -0x7d58(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _disp_escape_wall_message(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	lis r3, str_802F3C84@ha
	addi r3, r3, str_802F3C84@l
	bl msgSearch
	mr r31, r3
	bl FontGetMessageWidth
	clrlwi r6, r3, 16
	lis r5, 0x4330
	srawi r0, r6, 1
	lis r4, double_to_int_802f3c30@ha
	addze r3, r0
	addi r0, r6, 0x28
	xoris r3, r3, 0x8000
	addi r6, r4, double_to_int_802f3c30@l
	stw r3, 0x14(r1)
	xoris r0, r0, 0x8000
	lwz r7, dat_8041ccf8(r0)
	addi r4, r1, 0x8
	stw r5, 0x10(r1)
	li r3, 0x0
	lfd f3, 0x0(r6)
	lfd f0, 0x10(r1)
	lfs f2, float_0_8041cd04(r0)
	fsubs f0, f0, f3
	stw r0, 0x1c(r1)
	lfs f1, float_20_8041cd40(r0)
	stw r5, 0x18(r1)
	fsubs f31, f2, f0
	lfs f2, float_neg117_8041cd58(r0)
	lfd f0, 0x18(r1)
	stw r7, 0x8(r1)
	fsubs f1, f31, f1
	lfs f4, float_30_8041cd5c(r0)
	fsubs f3, f0, f3
	lfs f5, float_10_8041cd34(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	fmr f1, f31
	lfs f2, float_neg120_8041cd60(r0)
	mr r3, r31
	bl FontDrawString
	psq_l f31, 0x38(r1), 0, 0
	lwz r0, 0x44(r1)
	lfd f31, 0x30(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 _announce_wall_message(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r4, 0x0
	stw r0, 0x14(r1)
	beq @1
	li r0, 0x3c
	stw r0, 0x78(r3)
	@1:
	lwz r4, 0x78(r3)
	cmpwi r4, 0x0
	bge @2
	li r3, 0x2
	b @3
	@2:
	subi r0, r4, 0x1
	lis r4, _disp_escape_wall_message@ha
	stw r0, 0x78(r3)
	addi r5, r4, _disp_escape_wall_message@l
	lfs f1, float_900_8041cd64(r0)
	li r3, 0x8
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	li r3, 0x0
	@3:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStage_WallCloseCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	lbz r3, -0x7f24(r31)
	rlwinm. r0, r3, 0, 27, 27
	bne @1
	ori r0, r3, 0x10
	la r3, _close_wall_event(r0)
	stb r0, -0x7f24(r31)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, -0x7d5c(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 _nozzle_turn(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stfd f30, 0x20(r1)
	psq_st f30, 0x28(r1), 0, 0
	stmw r28, 0x10(r1)
	lwz r5, _battleWorkPointer(r0)
	mr r29, r3
	cmpwi r4, 0x0
	lis r3, vec3_802f3ac8@ha
	addis r31, r5, 0x2
	lwz r30, 0x160(r29)
	addi r28, r3, vec3_802f3ac8@l
	subi r31, r31, 0x7f40
	beq @1
	li r0, 0x0
	add r3, r31, r30
	stw r0, 0x80(r29)
	stw r0, 0x84(r29)
	lbz r0, 0x1c4(r3)
	cmplwi r0, 0x0
	beq @1
	li r0, 0x1e
	stw r0, 0x80(r29)
	@1:
	cmpwi r30, 0x1
	beq @2
	bge @3
	cmpwi r30, 0x0
	bge @4
	b @5
	@3:
	cmpwi r30, 0x3
	bge @5
	b @6
	@4:
	addi r3, r28, 0xc0
	b @7
	@2:
	addi r3, r28, 0xcc
	b @7
	@6:
	addi r3, r28, 0xd8
	b @7
	@5:
	li r3, 0x2
	b @8
	@7:
	bl BattleSearchObjectPtr
	lwz r3, 0x80(r29)
	cmpwi r3, 0x1e
	bge @9
	addi r0, r3, 0x1
	lfs f1, float_0_8041cd04(r0)
	stw r0, 0x80(r29)
	li r3, 0x2
	lfs f2, float_neg80_8041cd3c(r0)
	li r5, 0x1e
	lwz r4, 0x80(r29)
	bl intpl_sub
	fmr f31, f1
	b @10
	@9:
	lfs f31, float_neg80_8041cd3c(r0)
	@10:
	lwz r3, 0x84(r29)
	cmpwi r3, 0x1e
	bge @11
	addi r0, r3, 0x1
	add r3, r31, r30
	stw r0, 0x84(r29)
	lbz r0, 0x1c4(r3)
	cmpwi r0, 0x2
	beq @12
	bge @13
	cmpwi r0, 0x0
	beq @14
	bge @15
	b @14
	@13:
	cmpwi r0, 0x4
	bge @14
	b @16
	@15:
	lfs f1, float_45_8041cd2c(r0)
	b @17
	@12:
	lfs f1, float_0_8041cd04(r0)
	b @17
	@16:
	lfs f1, float_neg45_8041cd4c(r0)
	b @17
	@14:
	lfs f1, float_0_8041cd04(r0)
	@17:
	add r3, r31, r30
	lbz r0, 0x1c7(r3)
	cmpwi r0, 0x2
	beq @18
	bge @19
	cmpwi r0, 0x0
	beq @20
	bge @21
	b @20
	@19:
	cmpwi r0, 0x4
	bge @20
	b @22
	@21:
	lfs f2, float_45_8041cd2c(r0)
	b @23
	@18:
	lfs f2, float_0_8041cd04(r0)
	b @23
	@22:
	lfs f2, float_neg45_8041cd4c(r0)
	b @23
	@20:
	lfs f2, float_0_8041cd04(r0)
	@23:
	lwz r4, 0x84(r29)
	li r3, 0xc
	li r5, 0x1e
	bl intpl_sub
	fmr f30, f1
	@11:
	cmpwi r30, 0x1
	beq @24
	bge @25
	cmpwi r30, 0x0
	bge @26
	b @27
	@25:
	cmpwi r30, 0x3
	bge @27
	b @28
	@26:
	fmr f1, f31
	lfs f3, float_0_8041cd04(r0)
	fmr f2, f30
	addi r3, r28, 0x1d8
	bl mapObjRotate
	b @27
	@24:
	fmr f1, f31
	lfs f3, float_0_8041cd04(r0)
	fmr f2, f30
	addi r3, r28, 0x1e4
	bl mapObjRotate
	b @27
	@28:
	fmr f1, f31
	lfs f3, float_0_8041cd04(r0)
	fmr f2, f30
	addi r3, r28, 0x1f0
	bl mapObjRotate
	@27:
	lwz r0, 0x80(r29)
	cmpwi r0, 0x1e
	blt @29
	lwz r0, 0x84(r29)
	cmpwi r0, 0x1e
	blt @29
	add r6, r31, r30
	slwi r0, r30, 2
	lbz r5, 0x1c7(r6)
	add r4, r31, r0
	li r0, 0x0
	li r3, 0x2
	stb r5, 0x1c4(r6)
	stw r0, 0x1cc(r4)
	b @8
	@29:
	li r3, 0x0
	@8:
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	psq_l f30, 0x28(r1), 0, 0
	lfd f30, 0x20(r1)
	lmw r28, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void _Nozzle_Change_Check(u8 index, u8* rate) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	li r0, 0x4
	stmw r27, 0xc(r1)
	clrlwi r30, r3, 24
	mr r31, r3
	mr r27, r4
	li r3, 0x0
	addi r29, r30, 0x1c4
	lwz r5, _battleWorkPointer(r0)
	addis r28, r5, 0x2
	mtctr r0
	subi r28, r28, 0x7f40
	@1:
	lbz r0, 0x0(r4)
	addi r4, r4, 0x1
	add r3, r3, r0
	bdnz @1
	bl irand
	mr r4, r27
	li r27, 0x0
	b @2
	@3:
	lbz r0, 0x0(r4)
	subf. r3, r0, r3
	blt @4
	addi r4, r4, 0x1
	addi r27, r27, 0x1
	@2:
	clrlwi r0, r27, 24
	cmplwi r0, 0x4
	blt @3
	@4:
	lbzx r0, r28, r29
	clrlwi r3, r27, 24
	cmplw r3, r0
	beq @5
	slwi r0, r30, 2
	add r29, r28, r0
	lwz r3, 0x1cc(r29)
	cmpwi r3, 0x0
	beq @6
	bl evtCheckID
	cmpwi r3, 0x0
	bne @6
	li r0, 0x0
	stw r0, 0x1cc(r29)
	@6:
	lwz r0, 0x1cc(r29)
	cmpwi r0, 0x0
	bne @5
	add r4, r28, r30
	la r3, _nozzle_turn_event(r0)
	stb r27, 0x1c7(r4)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	cmplwi r3, 0x0
	stw r0, 0x1cc(r29)
	beq @5
	clrlwi r0, r31, 24
	stw r0, 0x160(r3)
	@5:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void BattleStage_NozzleDirChangeCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r3, _battleWorkPointer(r0)
	addis r31, r3, 0x2
	lwz r0, -0x7f0c(r31)
	cmplwi r0, 0x0
	beq @1
	li r30, 0x0
	b @2
	@3:
	lwz r4, -0x7f0c(r31)
	clrlslwi r0, r30, 24, 2
	mr r3, r30
	add r4, r4, r0
	bl _Nozzle_Change_Check
	addi r30, r30, 0x1
	@2:
	clrlwi r0, r30, 24
	cmplwi r0, 0x3
	blt @3
	@1:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _mobj_shake_main(BattleStageObject* obj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	lbz r3, 0x74(r3)
	addi r0, r3, 0x1
	stb r0, 0x74(r31)
	lbz r3, 0x74(r31)
	lbz r0, 0x73(r31)
	cmplw r3, r0
	blt @1
	li r0, 0x0
	stb r0, 0x74(r31)
	@1:
	lbz r5, 0x74(r31)
	lis r0, 0x4330
	lis r3, double_to_int_802f3c30@ha
	lbz r4, 0x73(r31)
	mulli r5, r5, 0x168
	stw r0, 0x8(r1)
	lfd f1, double_to_int_802f3c30@l(r3)
	divw r0, r5, r4
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f1, f0, f1
	bl sinfd
	lfs f0, float_5_8041cd10(r0)
	fmuls f0, f0, f1
	stfs f0, 0x78(r31)
	lfs f0, 0x78(r31)
	stfs f0, 0x1c(r31)
	lwz r31, 0x1c(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _set_mobj_shake(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	lwz r4, 0x18(r3)
	lwz r5, _battleWorkPointer(r0)
	lwz r4, 0x0(r4)
	mr r29, r5
	addis r31, r5, 0x2
	bl evtGetValue
	mr r30, r3
	mr r3, r29
	bl BattleWaitAllActiveEvtEnd_NoBgSetEndWait
	cmpwi r3, 0x0
	beq @1
	lwz r3, -0x7d68(r31)
	cmpwi r3, 0x0
	beq @2
	bl evtCheckID
	cmpwi r3, 0x0
	bne @1
	@2:
	lwz r3, -0x7d58(r31)
	cmpwi r3, 0x0
	beq @3
	bl evtCheckID
	cmpwi r3, 0x0
	bne @1
	@3:
	li r3, 0x2
	b @4
	@1:
	cmpwi r30, 0x2
	beq @5
	bge @5
	cmpwi r30, 0x0
	bge @6
	b @5
	@6:
	li r28, 0x0
	li r31, 0x0
	@7:
	addis r3, r31, 0x1
	addi r3, r3, 0x7140
	add r3, r29, r3
	lwz r0, 0x0(r3)
	cmpwi r0, 0x0
	ble @8
	lwz r4, 0x64(r3)
	lhz r0, 0x6(r4)
	cmpw r0, r30
	bne @8
	bl _mobj_shake_main
	@8:
	addi r28, r28, 0x1
	addi r31, r31, 0x7c
	cmpwi r28, 0x20
	blt @7
	@5:
	li r3, 0x0
	@4:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _set_mobj_shake_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r29, _battleWorkPointer(r0)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r30, r3
	li r28, 0x0
	li r31, 0x0
	@1:
	addis r27, r31, 0x1
	addi r27, r27, 0x7140
	add r27, r29, r27
	lwz r0, 0x0(r27)
	cmpwi r0, 0x0
	ble @2
	lwz r3, 0x64(r27)
	lhz r0, 0x6(r3)
	cmpw r0, r30
	bne @2
	li r0, 0x0
	li r3, 0xa
	stb r0, 0x72(r27)
	bl irand
	addi r0, r3, 0x3c
	li r3, 0x64
	stb r0, 0x73(r27)
	bl irand
	clrlwi. r0, r3, 31
	beq @3
	li r0, 0x0
	b @4
	@3:
	lbz r0, 0x73(r27)
	extrwi r0, r0, 8, 23
	@4:
	stb r0, 0x74(r27)
	lfs f0, float_0_8041cd04(r0)
	stfs f0, 0x78(r27)
	@2:
	addi r28, r28, 0x1
	addi r31, r31, 0x7c
	cmpwi r28, 0x20
	blt @1
	lmw r27, 0xc(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _bgset_audience_bgset_access(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl BattleAudience_Case_HaikeiSet
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 _bgset_kemuri_effect(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stmw r24, 0x10(r1)
	lwz r5, 0x18(r3)
	lis r4, vec3_802f3ac8@ha
	lwz r26, _battleWorkPointer(r0)
	addi r31, r4, vec3_802f3ac8@l
	lwz r4, 0x0(r5)
	bl evtGetValue
	mr r30, r3
	addi r29, r31, 0x1fc
	addi r28, r31, 0x214
	addi r27, r31, 0x22c
	li r25, 0x0
	li r31, 0x0
	@1:
	addis r24, r31, 0x1
	addi r24, r24, 0x7140
	add r24, r26, r24
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	ble @2
	lwz r3, 0x64(r24)
	lhz r0, 0x6(r3)
	cmpw r0, r30
	bne @2
	cmpwi r30, 0x1
	lfs f31, 0x4(r24)
	lfs f30, 0x8(r24)
	lfs f29, 0xc(r24)
	beq @3
	bge @4
	cmpwi r30, 0x0
	bge @5
	b @2
	@4:
	cmpwi r30, 0x3
	bge @2
	b @6
	@5:
	lfs f0, float_30_8041cd5c(r0)
	fmr f1, f31
	fmr f2, f30
	lfs f4, float_0_8041cd04(r0)
	fadds f29, f29, f0
	li r3, 0x3
	fmr f3, f29
	bl effKemuri1N64Entry
	mr r3, r29
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	b @2
	@3:
	lfs f0, float_15_8041cd18(r0)
	fmr f1, f31
	fmr f2, f30
	lfs f4, float_0_8041cd04(r0)
	fadds f29, f29, f0
	li r3, 0x0
	fmr f3, f29
	bl effKemuri1N64Entry
	mr r3, r28
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	b @2
	@6:
	lfs f0, float_30_8041cd5c(r0)
	fmr f1, f31
	fmr f2, f30
	lfs f4, float_0_8041cd04(r0)
	fadds f29, f29, f0
	li r3, 0x3
	fmr f3, f29
	bl effKemuri1N64Entry
	fmr f1, f31
	lfs f4, float_0_8041cd04(r0)
	fmr f2, f30
	li r3, 0x4
	fmr f3, f29
	bl effKemuri1N64Entry
	mr r3, r27
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	@2:
	addi r25, r25, 0x1
	addi r31, r31, 0x7c
	cmpwi r25, 0x20
	blt @1
	li r3, 0x2
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lmw r24, 0x10(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 _get_bgset_attack_data(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r31, _battleWorkPointer(r0)
	lwz r4, 0x0(r30)
	bl evtGetValue
	cmpwi r3, 0x1
	lwz r4, 0x4(r30)
	beq @1
	bge @2
	cmpwi r3, 0x0
	bge @3
	b @1
	@2:
	cmpwi r3, 0x3
	bge @1
	b @4
	@3:
	lwz r3, 0x2738(r31)
	lwz r3, 0xc(r3)
	lwz r3, 0x0(r3)
	addi r5, r3, 0x10
	b @5
	@4:
	lwz r3, 0x2738(r31)
	lwz r3, 0xc(r3)
	lwz r3, 0x0(r3)
	addi r5, r3, 0xd0
	b @5
	@1:
	li r5, 0x0
	@5:
	cmplwi r5, 0x0
	beq @6
	lwz r0, 0x1c(r5)
	cmplwi r0, 0x0
	bne @6
	li r5, 0x0
	@6:
	mr r3, r29
	bl evtSetValue
	lmw r29, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _mobj_destroy(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	lwz r4, 0x18(r3)
	lwz r29, _battleWorkPointer(r0)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r30, r3
	li r28, 0x0
	li r31, 0x0
	@1:
	addis r4, r31, 0x1
	addi r4, r4, 0x7140
	add r4, r29, r4
	lwz r0, 0x0(r4)
	cmpwi r0, 0x0
	ble @2
	lwz r3, 0x64(r4)
	lhz r0, 0x6(r3)
	cmpw r0, r30
	bne @2
	lwz r0, 0x68(r4)
	mr r3, r29
	ori r0, r0, 0x1
	stw r0, 0x68(r4)
	lwz r4, 0x6c(r4)
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq @2
	lwz r3, 0x14(r3)
	b @3
	@4:
	lwz r0, 0x1ac(r3)
	oris r0, r0, 0x1
	stw r0, 0x1ac(r3)
	lwz r3, 0x0(r3)
	@3:
	cmplwi r3, 0x0
	bne @4
	@2:
	addi r28, r28, 0x1
	addi r31, r31, 0x7c
	cmpwi r28, 0x20
	blt @1
	cmpwi r30, 0x1
	beq @5
	bge @6
	cmpwi r30, 0x0
	bge @7
	b @8
	@6:
	cmpwi r30, 0x3
	bge @8
	b @9
	@7:
	addis r3, r29, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x2
	stb r0, -0x7f24(r3)
	b @8
	@5:
	addis r3, r29, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x4
	stb r0, -0x7f24(r3)
	b @8
	@9:
	addis r3, r29, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x8
	stb r0, -0x7f24(r3)
	@8:
	lmw r28, 0x10(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _mobj_set_alpha(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r30, 0x28(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	cmpwi r31, 0x2
	clrlwi r30, r3, 24
	beq @1
	bge @2
	cmpwi r31, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r31, 0x4
	bge @5
	b @6
	@3:
	la r3, str_8041CD68(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @5
	lwz r0, dat_8041cce8(r0)
	addi r4, r1, 0x24
	la r3, str_8041CD68(r0)
	stw r0, 0x20(r1)
	stb r30, 0x23(r1)
	lwz r0, 0x20(r1)
	stw r0, 0x24(r1)
	bl mapGrpSetColor
	b @5
	@4:
	la r3, str_8041CD6C(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @5
	lwz r0, dat_8041ccec(r0)
	addi r4, r1, 0x1c
	la r3, str_8041CD6C(r0)
	stw r0, 0x18(r1)
	stb r30, 0x1b(r1)
	lwz r0, 0x18(r1)
	stw r0, 0x1c(r1)
	bl mapGrpSetColor
	b @5
	@1:
	la r3, str_8041CD70(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @5
	lwz r0, dat_8041ccf0(r0)
	addi r4, r1, 0x14
	la r3, str_8041CD70(r0)
	stw r0, 0x10(r1)
	stb r30, 0x13(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	bl mapGrpSetColor
	b @5
	@6:
	la r3, str_8041CD74(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @5
	lwz r0, dat_8041ccf4(r0)
	addi r4, r1, 0xc
	la r3, str_8041CD74(r0)
	stw r0, 0x8(r1)
	stb r30, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl mapGrpSetColor
	@5:
	lmw r30, 0x28(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 _set_mobj_rotate_x(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r5, vec3_802f3ac8@ha
	stw r0, 0x54(r1)
	stmw r24, 0x30(r1)
	mr r24, r4
	mr r29, r3
	addi r30, r5, vec3_802f3ac8@l
	li r26, 0x0
	lwz r6, 0x18(r3)
	lwz r28, _battleWorkPointer(r0)
	lwz r4, 0x0(r6)
	addis r27, r28, 0x2
	bl evtGetValue
	cmpwi r24, 0x0
	mr r31, r3
	beq @1
	cmpwi r31, 0x2
	beq @2
	bge @1
	cmpwi r31, 0x0
	bge @3
	b @1
	@3:
	li r3, 0x0
	li r0, 0x20
	mr r4, r3
	mtctr r0
	@4:
	addis r6, r3, 0x1
	addi r6, r6, 0x7140
	add r6, r28, r6
	lwz r0, 0x0(r6)
	cmpwi r0, 0x0
	ble @5
	lwz r5, 0x64(r6)
	lhz r0, 0x6(r5)
	cmpw r0, r31
	bne @5
	lbz r0, 0x14(r5)
	stb r0, 0x70(r6)
	stb r4, 0x71(r6)
	@5:
	addi r3, r3, 0x7c
	bdnz @4
	b @1
	@2:
	li r3, 0x0
	li r0, 0x3c
	stw r3, 0x7c(r29)
	stw r0, 0x80(r29)
	stw r3, 0x84(r29)
	@1:
	cmpwi r31, 0x2
	beq @6
	bge @7
	cmpwi r31, 0x0
	bge @8
	b @7
	@8:
	addi r29, r30, 0x244
	addi r30, r30, 0x25c
	li r27, 0x0
	li r25, 0x0
	@9:
	addis r24, r25, 0x1
	addi r24, r24, 0x7140
	add r24, r28, r24
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	ble @10
	lwz r3, 0x64(r24)
	lhz r0, 0x6(r3)
	cmpw r0, r31
	bne @10
	lbz r3, 0x70(r24)
	cmplwi r3, 0x0
	beq @11
	subi r0, r3, 0x1
	mr r3, r24
	stb r0, 0x70(r24)
	li r26, 0x1
	bl _mobj_shake_main
	b @10
	@11:
	lbz r0, 0x71(r24)
	cmplwi r0, 0x0
	bne @12
	cmpwi r31, 0x0
	bne @13
	mr r3, r29
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	b @12
	@13:
	mr r3, r30
	addi r4, r24, 0x4
	bl psndSFXOn_3D
	@12:
	lbz r4, 0x71(r24)
	li r3, 0x2
	lfs f2, float_90_8041cd08(r0)
	addi r0, r4, 0x1
	stb r0, 0x71(r24)
	lwz r5, 0x64(r24)
	lfs f1, 0x78(r24)
	lbz r4, 0x71(r24)
	lbz r5, 0x15(r5)
	bl intpl_sub
	stfs f1, 0x1c(r24)
	lwz r3, 0x64(r24)
	lbz r4, 0x71(r24)
	lbz r0, 0x15(r3)
	cmplw r4, r0
	bge @10
	li r26, 0x1
	@10:
	addi r27, r27, 0x1
	addi r25, r25, 0x7c
	cmpwi r27, 0x20
	blt @9
	b @7
	@6:
	lwz r3, 0x7c(r29)
	cmpwi r3, 0x0
	beq @14
	subi r0, r3, 0x1
	li r26, 0x1
	stw r0, 0x7c(r29)
	b @7
	@14:
	lwz r0, 0x84(r29)
	cmpwi r0, 0x0
	bne @15
	lwz r6, 0xfc(r30)
	addi r3, r30, 0x274
	lwz r5, 0x100(r30)
	addi r4, r1, 0x8
	lwz r0, 0x104(r30)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl psndSFXOn_3D
	@15:
	lwz r4, 0x84(r29)
	li r3, 0x2
	lfs f1, float_0_8041cd04(r0)
	addi r0, r4, 0x1
	lfs f2, float_90_8041cd08(r0)
	stw r0, 0x84(r29)
	lwz r4, 0x84(r29)
	lwz r5, 0x80(r29)
	bl intpl_sub
	fctiwz f0, f1
	lis r0, 0x4330
	stw r0, 0x20(r1)
	lfd f1, 0x168(r30)
	stfd f0, 0x18(r1)
	lwz r0, 0x1c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x24(r1)
	lfd f0, 0x20(r1)
	fsubs f0, f0, f1
	stfs f0, -0x7f3c(r27)
	lwz r3, 0x84(r29)
	lwz r0, 0x80(r29)
	cmpw r3, r0
	bge @7
	li r26, 0x1
	@7:
	subfic r3, r26, 0x0
	li r0, 0x2
	subfe r3, r3, r3
	andc r3, r0, r3
	lmw r24, 0x30(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void BattleStage_DestroyB(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r31, _battleWorkPointer(r0)
	lwz r4, 0x2738(r31)
	addis r3, r31, 0x2
	lwz r3, -0x7f14(r3)
	lwz r4, 0xc(r4)
	lwz r4, 0x0(r4)
	lwz r30, 0x19c(r4)
	bl evtDeleteID
	addis r3, r31, 0x2
	li r0, 0x0
	stw r0, -0x7f14(r3)
	lwz r3, -0x7f20(r3)
	cmpwi r3, 0x0
	beq @1
	bl evtCheckID
	cmpwi r3, 0x0
	beq @1
	addis r3, r31, 0x2
	lwz r3, -0x7f20(r3)
	bl evtDeleteID
	@1:
	cmplwi r30, 0x0
	bne @2
	la r30, _object_turn_event_B(r0)
	@2:
	mr r3, r30
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq @3
	lwz r0, 0x15c(r3)
	addis r3, r31, 0x2
	stw r0, -0x7f20(r3)
	@3:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStage_DestroyA2(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r31, _battleWorkPointer(r0)
	lwz r4, 0x2738(r31)
	addis r3, r31, 0x2
	lwz r3, -0x7f18(r3)
	lwz r4, 0xc(r4)
	lwz r4, 0x0(r4)
	lwz r30, 0x198(r4)
	bl evtDeleteID
	cmplwi r30, 0x0
	addis r3, r31, 0x2
	li r0, 0x0
	stw r0, -0x7f18(r3)
	bne @1
	la r30, _object_turn_event_A2(r0)
	@1:
	mr r3, r30
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStage_DestroyA1(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r31, _battleWorkPointer(r0)
	lwz r4, 0x2738(r31)
	addis r3, r31, 0x2
	lwz r3, -0x7f1c(r3)
	lwz r4, 0xc(r4)
	lwz r4, 0x0(r4)
	lwz r30, 0x194(r4)
	bl evtDeleteID
	addis r3, r31, 0x2
	li r0, 0x0
	stw r0, -0x7f1c(r3)
	lwz r3, -0x7f20(r3)
	cmpwi r3, 0x0
	beq @1
	bl evtCheckID
	cmpwi r3, 0x0
	beq @1
	addis r3, r31, 0x2
	lwz r3, -0x7f20(r3)
	bl evtDeleteID
	@1:
	cmplwi r30, 0x0
	bne @2
	la r30, _object_turn_event_A1(r0)
	@2:
	mr r3, r30
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq @3
	lwz r0, 0x15c(r3)
	addis r3, r31, 0x2
	stw r0, -0x7f20(r3)
	@3:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleObjectConfig(void) {
	nofralloc
	blr
}

asm void BattleStageObjectMain(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	li r28, 0x0
	li r27, 0x0
	lwz r31, _battleWorkPointer(r0)
	addis r30, r31, 0x2
	@1:
	addis r29, r27, 0x1
	addi r29, r29, 0x7140
	add r29, r31, r29
	lwz r0, 0x0(r29)
	cmpwi r0, 0x0
	ble @2
	lfs f1, 0x4(r29)
	li r4, 0x0
	lfs f0, 0x34(r29)
	fcmpu cr0, f1, f0
	bne @3
	lfs f1, 0x8(r29)
	lfs f0, 0x38(r29)
	fcmpu cr0, f1, f0
	bne @3
	lfs f1, 0xc(r29)
	lfs f0, 0x3c(r29)
	fcmpu cr0, f1, f0
	beq @4
	@3:
	lwz r3, 0x4(r29)
	li r4, 0x1
	lwz r0, 0x8(r29)
	stw r3, 0x34(r29)
	stw r0, 0x38(r29)
	lwz r0, 0xc(r29)
	stw r0, 0x3c(r29)
	@4:
	lfs f1, 0x10(r29)
	lfs f0, 0x40(r29)
	fcmpu cr0, f1, f0
	bne @5
	lfs f1, 0x14(r29)
	lfs f0, 0x44(r29)
	fcmpu cr0, f1, f0
	bne @5
	lfs f1, 0x18(r29)
	lfs f0, 0x48(r29)
	fcmpu cr0, f1, f0
	beq @6
	@5:
	lwz r3, 0x10(r29)
	li r4, 0x1
	lwz r0, 0x14(r29)
	stw r3, 0x40(r29)
	stw r0, 0x44(r29)
	lwz r0, 0x18(r29)
	stw r0, 0x48(r29)
	@6:
	lfs f1, 0x28(r29)
	lfs f0, 0x58(r29)
	fcmpu cr0, f1, f0
	bne @7
	lfs f1, 0x2c(r29)
	lfs f0, 0x5c(r29)
	fcmpu cr0, f1, f0
	bne @7
	lfs f1, 0x30(r29)
	lfs f0, 0x60(r29)
	fcmpu cr0, f1, f0
	beq @8
	@7:
	lwz r3, 0x28(r29)
	li r4, 0x1
	lwz r0, 0x2c(r29)
	stw r3, 0x58(r29)
	stw r0, 0x5c(r29)
	lwz r0, 0x30(r29)
	stw r0, 0x60(r29)
	@8:
	lfs f1, 0x1c(r29)
	lfs f0, 0x4c(r29)
	fcmpu cr0, f1, f0
	bne @9
	lfs f1, 0x20(r29)
	lfs f0, 0x50(r29)
	fcmpu cr0, f1, f0
	bne @9
	lfs f1, 0x24(r29)
	lfs f0, 0x54(r29)
	fcmpu cr0, f1, f0
	beq @10
	@9:
	lwz r3, 0x1c(r29)
	li r4, 0x1
	lwz r0, 0x20(r29)
	stw r3, 0x4c(r29)
	stw r0, 0x50(r29)
	lwz r0, 0x24(r29)
	stw r0, 0x54(r29)
	@10:
	lwz r3, 0x68(r29)
	rlwinm. r0, r3, 0, 30, 30
	beq @11
	rlwinm r0, r3, 0, 31, 29
	li r4, 0x1
	stw r0, 0x68(r29)
	@11:
	lwz r3, 0x64(r29)
	lhz r0, 0x6(r3)
	cmpwi r0, 0x2
	beq @12
	b @13
	@12:
	lfs f1, -0x7f3c(r30)
	lfs f0, -0x7f30(r30)
	fcmpu cr0, f1, f0
	bne @14
	lfs f1, -0x7f38(r30)
	lfs f0, -0x7f2c(r30)
	fcmpu cr0, f1, f0
	bne @14
	lfs f1, -0x7f34(r30)
	lfs f0, -0x7f28(r30)
	fcmpu cr0, f1, f0
	beq @13
	@14:
	lwz r3, -0x7f3c(r30)
	li r4, 0x1
	lwz r0, -0x7f38(r30)
	stw r3, -0x7f30(r30)
	stw r0, -0x7f2c(r30)
	lwz r0, -0x7f34(r30)
	stw r0, -0x7f28(r30)
	@13:
	lwz r3, 0x64(r29)
	lhz r0, 0x6(r3)
	cmpwi r0, 0x3
	beq @15
	bge @16
	cmpwi r0, 0x2
	bge @17
	cmpwi r0, 0x0
	bge @18
	b @19
	@16:
	cmpwi r0, 0x8
	bge @19
	@18:
	cmpwi r4, 0x0
	beq @19
	lfs f3, 0x4(r29)
	lfs f2, 0x10(r29)
	lfs f1, 0x8(r29)
	lfs f0, 0x14(r29)
	fadds f3, f3, f2
	lfs f5, 0x28(r29)
	lfs f2, 0xc(r29)
	fadds f4, f1, f0
	lfs f0, 0x18(r29)
	fadds f1, f5, f3
	lfs f5, 0x2c(r29)
	fadds f0, f2, f0
	lfs f3, 0x30(r29)
	fadds f2, f5, f4
	lwz r3, 0x0(r3)
	fadds f3, f3, f0
	bl mapObjTranslate
	lwz r3, 0x64(r29)
	lfs f1, 0x1c(r29)
	lwz r3, 0x0(r3)
	lfs f2, 0x20(r29)
	lfs f3, 0x24(r29)
	bl mapObjRotate
	b @19
	@17:
	cmpwi r4, 0x0
	beq @19
	lfs f3, 0x4(r29)
	lfs f2, 0x10(r29)
	lfs f1, 0x8(r29)
	lfs f0, 0x14(r29)
	fadds f3, f3, f2
	lfs f5, 0x28(r29)
	lfs f2, 0xc(r29)
	fadds f4, f1, f0
	lfs f0, 0x18(r29)
	fadds f1, f5, f3
	lfs f5, 0x2c(r29)
	fadds f0, f2, f0
	lfs f3, 0x30(r29)
	fadds f2, f5, f4
	lwz r3, 0x0(r3)
	fadds f3, f3, f0
	bl mapObjTranslate
	lfs f1, float_0_8041cd04(r0)
	lfs f0, 0x14(r29)
	lwz r3, 0x64(r29)
	fmr f3, f1
	fneg f2, f0
	lwz r3, 0x0(r3)
	bl mapObjTranslate
	lwz r3, 0x64(r29)
	lfs f1, -0x7f3c(r30)
	lwz r3, 0x0(r3)
	lfs f2, -0x7f38(r30)
	lfs f3, -0x7f34(r30)
	bl mapObjRotate
	lfs f1, float_0_8041cd04(r0)
	lwz r3, 0x64(r29)
	fmr f3, f1
	lfs f2, 0x14(r29)
	lwz r3, 0x0(r3)
	bl mapObjTranslate
	b @19
	@15:
	cmpwi r4, 0x0
	beq @19
	lfs f3, 0x4(r29)
	lfs f2, 0x10(r29)
	lfs f1, 0x8(r29)
	lfs f0, 0x14(r29)
	fadds f3, f3, f2
	lfs f5, 0x28(r29)
	lfs f2, 0xc(r29)
	fadds f4, f1, f0
	lfs f0, 0x18(r29)
	fadds f1, f5, f3
	lfs f5, 0x2c(r29)
	fadds f0, f2, f0
	lfs f3, 0x30(r29)
	fadds f2, f5, f4
	lwz r3, 0x0(r3)
	fadds f3, f3, f0
	bl mapObjTranslate
	lfs f1, float_0_8041cd04(r0)
	lfs f0, 0x8(r29)
	lwz r3, 0x64(r29)
	fmr f3, f1
	fneg f2, f0
	lwz r3, 0x0(r3)
	bl mapObjTranslate
	lwz r3, 0x64(r29)
	lfs f1, 0x1c(r29)
	lwz r3, 0x0(r3)
	lfs f2, 0x20(r29)
	lfs f3, 0x24(r29)
	bl mapObjRotate
	lfs f1, float_0_8041cd04(r0)
	lwz r3, 0x64(r29)
	fmr f3, f1
	lfs f2, 0x8(r29)
	lwz r3, 0x0(r3)
	bl mapObjTranslate
	@19:
	lwz r0, 0x68(r29)
	clrlwi. r0, r0, 31
	beq @20
	lwz r3, 0x64(r29)
	lwz r3, 0x0(r3)
	bl mapGetMapObj
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	bne @2
	lwz r3, 0x64(r29)
	li r4, 0x1
	lwz r3, 0x0(r3)
	bl mapGrpFlagOn
	b @2
	@20:
	lwz r3, 0x64(r29)
	lwz r3, 0x0(r3)
	bl mapGetMapObj
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @2
	lwz r3, 0x64(r29)
	li r4, 0x1
	lwz r3, 0x0(r3)
	bl mapGrpFlagOff
	@2:
	addi r28, r28, 0x1
	addi r27, r27, 0x7c
	cmpwi r28, 0x20
	blt @1
	bl BattleObjectConfig
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void BattleStageObjectInit(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stmw r18, 0x8(r1)
	lwz r24, _battleWorkPointer(r0)
	lis r6, lbl_80371490@ha
	lis r5, vec3_802f3ac8@ha
	li r31, 0x0
	lwz r4, 0x2738(r24)
	addis r3, r24, 0x1
	addi r26, r5, vec3_802f3ac8@l
	addi r25, r6, lbl_80371490@l
	lwz r4, 0xc(r4)
	addis r20, r24, 0x2
	li r30, 0x0
	li r29, 0x0
	lwz r23, 0x0(r4)
	li r28, 0x0
	li r27, 0x0
	li r4, 0x0
	lwz r22, 0x8(r23)
	li r5, 0xf80
	lwz r21, 0xc(r23)
	addi r3, r3, 0x7140
	bl memset
	bl pouchGetPtr
	lha r0, 0x88(r3)
	cmpwi r0, 0x4
	bge @1
	cmpwi r0, 0x1
	bge @2
	b @1
	@2:
	la r3, str_8041CD78(r0)
	li r4, 0x1
	li r5, 0x0
	bl mapPlayAnimationLv
	@1:
	bl pouchGetPtr
	lha r0, 0x88(r3)
	cmpwi r0, 0x4
	bge @3
	cmpwi r0, 0x1
	bge @4
	b @3
	@4:
	bl pouchGetPtr
	lha r3, 0x88(r3)
	addi r0, r25, 0x1c0
	mulli r3, r3, 0x310
	add r0, r0, r3
	stw r0, -0x7f0c(r20)
	b @5
	@3:
	li r0, 0x0
	stw r0, -0x7f0c(r20)
	@5:
	bl pouchGetPtr
	lha r5, 0x88(r3)
	addi r4, r25, 0xe00
	li r3, -0x1
	li r0, 0x0
	mulli r5, r5, 0x78c
	add r4, r4, r5
	stw r4, -0x7f08(r20)
	stb r3, -0x7d76(r20)
	stw r0, -0x7d64(r20)
	stw r0, -0x7d60(r20)
	bl mapGetWork
	lwz r3, 0xa8(r3)
	li r4, 0x2
	lwz r3, 0x8(r3)
	lwz r3, 0x0(r3)
	bl mapGrpFlagOff
	la r3, str_8041CD68(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @6
	la r3, str_8041CD68(r0)
	li r4, 0x1
	bl mapGrpFlagOn
	la r3, str_8041CD68(r0)
	li r4, 0x2
	bl mapGrpFlagOff
	@6:
	la r3, str_8041CD6C(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @7
	la r3, str_8041CD6C(r0)
	li r4, 0x1
	bl mapGrpFlagOn
	la r3, str_8041CD6C(r0)
	li r4, 0x2
	bl mapGrpFlagOff
	@7:
	la r3, str_8041CD70(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @8
	la r3, str_8041CD70(r0)
	li r4, 0x1
	bl mapGrpFlagOn
	la r3, str_8041CD70(r0)
	li r4, 0x2
	bl mapGrpFlagOff
	@8:
	la r3, str_8041CD74(r0)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq @9
	la r3, str_8041CD74(r0)
	li r4, 0x1
	bl mapGrpFlagOn
	la r3, str_8041CD74(r0)
	li r4, 0x2
	bl mapGrpFlagOff
	@9:
	addi r3, r26, 0xe4
	li r4, 0x1
	bl mapGrpFlagOn
	cmplwi r21, 0x0
	li r20, 0x1
	beq @10
	lfs f31, float_0_8041cd04(r0)
	b @11
	@12:
	li r0, 0x20
	li r4, 0x0
	li r3, 0x0
	mtctr r0
	@13:
	addis r19, r3, 0x1
	addi r19, r19, 0x7140
	add r19, r24, r19
	lwz r0, 0x0(r19)
	cmpwi r0, 0x0
	ble @14
	addi r4, r4, 0x1
	addi r3, r3, 0x7c
	bdnz @13
	@14:
	cmpwi r4, 0x20
	bge @10
	stw r21, 0x64(r19)
	li r0, -0x1
	stw r20, 0x0(r19)
	stw r0, 0x6c(r19)
	lwz r3, 0x64(r19)
	lhz r0, 0x6(r3)
	cmpwi r0, 0x3
	beq @15
	bge @16
	cmpwi r0, 0x1
	beq @17
	bge @18
	cmpwi r0, 0x0
	bge @19
	b @20
	@16:
	cmpwi r0, 0x6
	beq @21
	b @20
	@19:
	addi r31, r31, 0x1
	b @20
	@17:
	addi r30, r30, 0x1
	b @20
	@18:
	addi r29, r29, 0x1
	b @20
	@15:
	addi r28, r28, 0x1
	b @20
	@21:
	li r27, 0x1
	@20:
	cmpwi r0, 0x4
	bge @22
	cmpwi r0, 0x2
	bge @23
	cmpwi r0, 0x0
	bge @24
	b @25
	@22:
	cmpwi r0, 0x8
	bge @25
	cmpwi r0, 0x6
	bge @24
	b @25
	@24:
	lwz r3, 0x8(r21)
	lwz r0, 0xc(r21)
	stw r3, 0x4(r19)
	stw r0, 0x8(r19)
	lwz r0, 0x10(r21)
	stw r0, 0xc(r19)
	b @25
	@23:
	lwz r3, 0x8(r21)
	lwz r0, 0xc(r21)
	stw r3, 0x4(r19)
	stw r0, 0x8(r19)
	lwz r0, 0x10(r21)
	stw r0, 0xc(r19)
	@25:
	stfs f31, 0x24(r19)
	li r4, 0x1
	stfs f31, 0x20(r19)
	stfs f31, 0x1c(r19)
	lwz r3, 0x0(r26)
	lwz r0, 0x4(r26)
	stw r3, 0x34(r19)
	stw r0, 0x38(r19)
	lwz r0, 0x8(r26)
	stw r0, 0x3c(r19)
	lwz r3, 0xc(r26)
	lwz r0, 0x10(r26)
	stw r3, 0x40(r19)
	stw r0, 0x44(r19)
	lwz r0, 0x14(r26)
	stw r0, 0x48(r19)
	lwz r3, 0x18(r26)
	lwz r0, 0x1c(r26)
	stw r3, 0x4c(r19)
	stw r0, 0x50(r19)
	lwz r0, 0x20(r26)
	stw r0, 0x54(r19)
	lwz r3, 0x24(r26)
	lwz r0, 0x28(r26)
	stw r3, 0x58(r19)
	stw r0, 0x5c(r19)
	lwz r0, 0x2c(r26)
	stw r0, 0x60(r19)
	lwz r3, 0x64(r19)
	lwz r3, 0x0(r3)
	bl mapGrpFlagOff
	lhz r0, 0x4(r21)
	cmpwi r0, 0x1
	beq @26
	bge @27
	cmpwi r0, 0x0
	bge @28
	b @27
	b @27
	@28:
	la r3, _entry_tree_data(r0)
	bl BtlUnit_Entry
	lwz r0, 0x0(r19)
	mr r18, r3
	stw r0, 0xb2c(r3)
	lwz r0, 0x0(r3)
	stw r0, 0x6c(r19)
	lfs f1, 0x4(r19)
	lfs f2, 0x8(r19)
	lfs f3, 0xc(r19)
	bl BtlUnit_SetPos
	lfs f1, 0x4(r19)
	mr r3, r18
	lfs f2, 0x8(r19)
	lfs f3, 0xc(r19)
	bl BtlUnit_SetHomePos
	b @27
	@26:
	la r3, _entry_switch_data(r0)
	bl BtlUnit_Entry
	lwz r0, 0x0(r19)
	mr r18, r3
	stw r0, 0xb2c(r3)
	lwz r0, 0x0(r3)
	stw r0, 0x6c(r19)
	lfs f1, 0x4(r19)
	lfs f2, 0x8(r19)
	lfs f3, 0xc(r19)
	bl BtlUnit_SetPos
	lfs f1, 0x4(r19)
	mr r3, r18
	lfs f2, 0x8(r19)
	lfs f3, 0xc(r19)
	bl BtlUnit_SetHomePos
	@27:
	addi r20, r20, 0x1
	subi r22, r22, 0x1
	addi r21, r21, 0x18
	@11:
	cmpwi r22, 0x0
	bne @12
	@10:
	bl pouchGetPtr
	lha r0, 0x88(r3)
	cmpwi r0, 0x0
	ble @29
	lfs f31, float_0_8041cd04(r0)
	addi r25, r25, 0x2c30
	li r21, 0x0
	@30:
	li r0, 0x20
	li r4, 0x0
	li r3, 0x0
	mtctr r0
	@31:
	addis r19, r3, 0x1
	addi r19, r19, 0x7140
	add r19, r24, r19
	lwz r0, 0x0(r19)
	cmpwi r0, 0x0
	ble @32
	addi r4, r4, 0x1
	addi r3, r3, 0x7c
	bdnz @31
	@32:
	cmpwi r4, 0x20
	bge @29
	stw r25, 0x64(r19)
	li r0, -0x1
	li r4, 0x1
	stw r20, 0x0(r19)
	stw r0, 0x6c(r19)
	lwz r3, 0x8(r25)
	lwz r0, 0xc(r25)
	stw r3, 0x4(r19)
	stw r0, 0x8(r19)
	lwz r0, 0x10(r25)
	stw r0, 0xc(r19)
	stfs f31, 0x24(r19)
	stfs f31, 0x20(r19)
	stfs f31, 0x1c(r19)
	lwz r3, 0x30(r26)
	lwz r0, 0x34(r26)
	stw r3, 0x34(r19)
	stw r0, 0x38(r19)
	lwz r0, 0x38(r26)
	stw r0, 0x3c(r19)
	lwz r3, 0x3c(r26)
	lwz r0, 0x40(r26)
	stw r3, 0x40(r19)
	stw r0, 0x44(r19)
	lwz r0, 0x44(r26)
	stw r0, 0x48(r19)
	lwz r3, 0x48(r26)
	lwz r0, 0x4c(r26)
	stw r3, 0x4c(r19)
	stw r0, 0x50(r19)
	lwz r0, 0x50(r26)
	stw r0, 0x54(r19)
	lwz r3, 0x54(r26)
	lwz r0, 0x58(r26)
	stw r3, 0x58(r19)
	stw r0, 0x5c(r19)
	lwz r0, 0x5c(r26)
	stw r0, 0x60(r19)
	lwz r3, 0x64(r19)
	lwz r3, 0x0(r3)
	bl mapGrpFlagOff
	addi r21, r21, 0x1
	addi r25, r25, 0x18
	cmpwi r21, 0x3
	addi r20, r20, 0x1
	blt @30
	@29:
	li r0, 0x20
	la r4, _object_wall_data(r0)
	li r3, 0x0
	mtctr r0
	@33:
	addis r19, r3, 0x1
	addi r19, r19, 0x7140
	add r19, r24, r19
	lwz r0, 0x0(r19)
	cmpwi r0, 0x0
	ble @34
	addi r3, r3, 0x7c
	bdnz @33
	@34:
	stw r4, 0x64(r19)
	li r0, -0x1
	stw r20, 0x0(r19)
	stw r0, 0x6c(r19)
	lwz r3, 0x8(r4)
	lwz r0, 0xc(r4)
	stw r3, 0x4(r19)
	stw r0, 0x8(r19)
	lwz r0, 0x10(r4)
	stw r0, 0xc(r19)
	bl BattleStageGetPtr
	lfs f1, 0xb28(r3)
	li r4, 0x1
	lfs f0, float_0_8041cd04(r0)
	stfs f1, 0x8(r19)
	stfs f0, 0x24(r19)
	stfs f0, 0x20(r19)
	stfs f0, 0x1c(r19)
	lwz r3, 0x60(r26)
	lwz r0, 0x64(r26)
	stw r3, 0x34(r19)
	stw r0, 0x38(r19)
	lwz r0, 0x68(r26)
	stw r0, 0x3c(r19)
	lwz r3, 0x6c(r26)
	lwz r0, 0x70(r26)
	stw r3, 0x40(r19)
	stw r0, 0x44(r19)
	lwz r0, 0x74(r26)
	stw r0, 0x48(r19)
	lwz r3, 0x78(r26)
	lwz r0, 0x7c(r26)
	stw r3, 0x4c(r19)
	stw r0, 0x50(r19)
	lwz r0, 0x80(r26)
	stw r0, 0x54(r19)
	lwz r3, 0x84(r26)
	lwz r0, 0x88(r26)
	stw r3, 0x58(r19)
	stw r0, 0x5c(r19)
	lwz r0, 0x8c(r26)
	stw r0, 0x60(r19)
	lwz r3, 0x64(r19)
	lwz r3, 0x0(r3)
	bl mapGrpFlagOn
	lwz r0, 0x68(r19)
	li r21, 0x0
	lfs f31, float_0_8041cd04(r0)
	addi r20, r20, 0x1
	ori r0, r0, 0x1
	stw r0, 0x68(r19)
	@35:
	la r5, _object_spot_light_data(r0)
	add r5, r5, r21
	lwz r0, 0x0(r5)
	cmplwi r0, 0x0
	beq @36
	li r0, 0x20
	li r3, 0x0
	mtctr r0
	@37:
	addis r19, r3, 0x1
	addi r19, r19, 0x7140
	add r19, r24, r19
	lwz r0, 0x0(r19)
	cmpwi r0, 0x0
	ble @38
	addi r3, r3, 0x7c
	bdnz @37
	@38:
	stw r5, 0x64(r19)
	li r0, -0x1
	li r4, 0x1
	stw r20, 0x0(r19)
	stw r0, 0x6c(r19)
	lwz r3, 0x8(r5)
	lwz r0, 0xc(r5)
	stw r3, 0x4(r19)
	stw r0, 0x8(r19)
	lwz r0, 0x10(r5)
	stw r0, 0xc(r19)
	stfs f31, 0x24(r19)
	stfs f31, 0x20(r19)
	stfs f31, 0x1c(r19)
	lwz r3, 0x90(r26)
	lwz r0, 0x94(r26)
	stw r3, 0x34(r19)
	stw r0, 0x38(r19)
	lwz r0, 0x98(r26)
	stw r0, 0x3c(r19)
	lwz r3, 0x9c(r26)
	lwz r0, 0xa0(r26)
	stw r3, 0x40(r19)
	stw r0, 0x44(r19)
	lwz r0, 0xa4(r26)
	stw r0, 0x48(r19)
	lwz r3, 0xa8(r26)
	lwz r0, 0xac(r26)
	stw r3, 0x4c(r19)
	stw r0, 0x50(r19)
	lwz r0, 0xb0(r26)
	stw r0, 0x54(r19)
	lwz r3, 0xb4(r26)
	lwz r0, 0xb8(r26)
	stw r3, 0x58(r19)
	stw r0, 0x5c(r19)
	lwz r0, 0xbc(r26)
	stw r0, 0x60(r19)
	lwz r3, 0x64(r19)
	lwz r3, 0x0(r3)
	bl mapGrpFlagOn
	lwz r0, 0x68(r19)
	addi r20, r20, 0x1
	addi r21, r21, 0x18
	ori r0, r0, 0x1
	stw r0, 0x68(r19)
	b @35
	@36:
	lwz r3, 0x190(r23)
	cmplwi r3, 0x0
	beq @39
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	@39:
	cmpwi r31, 0x0
	beq @40
	lwz r3, 0x1a0(r23)
	cmplwi r3, 0x0
	beq @40
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	addis r3, r24, 0x2
	stw r0, -0x7f1c(r3)
	@40:
	cmpwi r30, 0x0
	beq @41
	lwz r3, 0x1a4(r23)
	cmplwi r3, 0x0
	beq @41
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	addis r3, r24, 0x2
	stw r0, -0x7f18(r3)
	@41:
	cmpwi r29, 0x0
	beq @42
	lwz r3, 0x1a8(r23)
	cmplwi r3, 0x0
	beq @42
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	addis r3, r24, 0x2
	stw r0, -0x7f14(r3)
	@42:
	cmpwi r28, 0x0
	beq @43
	lwz r3, 0x1ac(r23)
	cmplwi r3, 0x0
	beq @43
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	addis r3, r24, 0x2
	stw r0, -0x7f10(r3)
	@43:
	cmpwi r31, 0x0
	bne @44
	addis r3, r24, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x2
	stb r0, -0x7f24(r3)
	@44:
	cmpwi r30, 0x0
	bne @45
	addis r3, r24, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x4
	stb r0, -0x7f24(r3)
	@45:
	cmpwi r29, 0x0
	bne @46
	addis r3, r24, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x8
	stb r0, -0x7f24(r3)
	@46:
	lbz r0, 0x1b1(r23)
	extsb. r0, r0
	beq @47
	addis r3, r24, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x2
	stb r0, -0x7f24(r3)
	@47:
	lbz r0, 0x1b2(r23)
	extsb. r0, r0
	beq @48
	addis r3, r24, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x4
	stb r0, -0x7f24(r3)
	@48:
	lbz r0, 0x1b3(r23)
	extsb. r0, r0
	beq @49
	addis r3, r24, 0x2
	lbz r0, -0x7f24(r3)
	ori r0, r0, 0x8
	stb r0, -0x7f24(r3)
	@49:
	cmpwi r27, 0x0
	bne @50
	addis r5, r24, 0x2
	addi r3, r26, 0x1b4
	lbz r0, -0x7f24(r5)
	li r4, 0x1
	ori r0, r0, 0x20
	stb r0, -0x7f24(r5)
	bl mapGrpFlagOn
	addi r3, r26, 0x28c
	li r4, 0x1
	bl mapGrpFlagOn
	@50:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	lmw r18, 0x8(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm BattleStageObject* BattleSearchObjectPtr(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	li r29, 0x0
	li r31, 0x0
	lwz r30, _battleWorkPointer(r0)
	@1:
	addis r28, r31, 0x1
	addi r28, r28, 0x7140
	add r28, r30, r28
	lwz r0, 0x0(r28)
	cmpwi r0, 0x0
	beq @2
	lwz r3, 0x64(r28)
	mr r4, r27
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @2
	mr r3, r28
	b @3
	@2:
	addi r29, r29, 0x1
	addi r31, r31, 0x7c
	cmpwi r29, 0x20
	blt @1
	li r3, 0x0
	@3:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BattleStageObject* BattleGetObjectPtr(s32 id) {
	nofralloc
	li r0, 0x20
	lwz r5, _battleWorkPointer(r0)
	li r4, 0x0
	mtctr r0
	@1:
	addis r6, r4, 0x1
	addi r6, r6, 0x7140
	add r6, r5, r6
	lwz r0, 0x0(r6)
	cmpw r0, r3
	bne @2
	mr r3, r6
	blr
	@2:
	addi r4, r4, 0x7c
	bdnz @1
	li r3, 0x0
	blr
}
// clang-format on
#endif

__declspec(section ".data") void* jumptable_80374848[9] = {
    (void*)((char*)_object_fall_attack + 0x780),
    (void*)((char*)_object_fall_attack + 0x7b4),
    (void*)((char*)_object_fall_attack + 0x7e8),
    (void*)((char*)_object_fall_attack + 0x81c),
    (void*)((char*)_object_fall_attack + 0x850),
    (void*)((char*)_object_fall_attack + 0x8c0),
    (void*)((char*)_object_fall_attack + 0x8f4),
    (void*)((char*)_object_fall_attack + 0x974),
    (void*)((char*)_object_fall_attack + 0x88c)
};
__declspec(section ".data") u32 gap_05_8037486C_data[1] = {0};
__declspec(section ".sdata") u32 gap_07_80411F3C_sdata[1] = {0};
#pragma force_active reset
