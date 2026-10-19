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
#ifndef NONMATCHING
#define EXT_LIT(sym, val) (sym)

#endif
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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 _object_fall_attack(EventEntry* event, BOOL isFirstCall);
s32 _object_fall_wait(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_get_weapon_address(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_attack_set(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_effect(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_wait(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame_delete(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame_wait_unit_ready(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame_wait(EventEntry* event, BOOL isFirstCall);
s32 _announce_wall_message(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_turn(EventEntry* event, BOOL isFirstCall);
s32 _set_mobj_shake(EventEntry* event, BOOL isFirstCall);
s32 _bgset_audience_bgset_access(EventEntry* event, BOOL isFirstCall);
s32 _bgset_audience_bgset_access(EventEntry* event, BOOL isFirstCall);
s32 _bgset_kemuri_effect(EventEntry* event, BOOL isFirstCall);
s32 _get_bgset_attack_data(EventEntry* event, BOOL isFirstCall);
s32 _mobj_destroy(EventEntry* event, BOOL isFirstCall);
s32 _mobj_set_alpha(EventEntry* event, BOOL isFirstCall);
s32 _set_mobj_rotate_x(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 btlevtcmd_CheckDamage(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_GetACPossibility(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_GetEnemyBelong(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_GetSelectEnemy(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_GetSelectNextEnemy(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_PreCheckDamage(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_ResultACDefence(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_SamplingEnemy(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_StartAvoid(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_WaitAttackEnd(EventEntry* event, BOOL isFirstCall);
s32 btlevtcmd_check_battleflag(EventEntry* event, BOOL isFirstCall);
s32 evt_btl_camera_shake_h(EventEntry* event, BOOL isFirstCall);
#endif

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
#endif
#ifndef NONMATCHING
BattleStageObject* BattleGetObjectPtr(s32 id);
#endif

#ifdef NONMATCHING
	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id == id) {
			return obj;
		}
	}
	return NULL;
}
#endif
#ifndef NONMATCHING
BattleStageObject* BattleSearchObjectPtr(const char* name);
#endif

#ifdef NONMATCHING
BattleStageObject* BattleSearchObjectPtr(const char* name) {
	BattleWork* wp = _battleWorkPointer;
	int i;
	BattleStageObject* obj;
#endif
#ifndef NONMATCHING
void *memset(void *dest, int ch, size_t count);
extern u64 lbl_80371490;
void BattleStageObjectInit(void);
#endif

#ifdef NONMATCHING
	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id && !strcmp(obj->data->name, name)) {
			return obj;
		}
	}
	return NULL;
}
#endif
#ifndef NONMATCHING
void BattleStageObjectMain(void);
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
#endif
#ifndef NONMATCHING
void BattleObjectConfig(void);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
void BattleStage_DestroyA1(void);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
void BattleStage_DestroyA2(void);
#endif

#ifdef NONMATCHING
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

void BattleObjectConfig(void) {
	//stubbed in retail
}

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
#ifndef NONMATCHING
void BattleStage_DestroyB(void);
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

#ifdef NONMATCHING
BattleStageObjectData _object_spot_light_data[] = {
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") BattleStageObjectData _object_spot_light_data[] = {
#endif
	{(char*)str_802F3BB8, 6, 7, {0.0f, 240.0f, 0.0f}, 0, 0},
	{NULL, 6, 7, {0.0f, 0.0f, 0.0f}, 0, 0},
};

#ifdef NONMATCHING
s32 _entry_tree_data[] = {
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") s32 _entry_tree_data[] = {
#endif
	(s32)&unit_object_tree, 0x02000000, 0x04000005, 0xC47A0000, 0xC47A0000, 0xC47A0000, 0, 0,
	0, 0, 0, 0,
};

#ifdef NONMATCHING
s32 _entry_switch_data[] = {
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") s32 _entry_switch_data[] = {
#endif
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
#endif
#ifndef NONMATCHING
s32 _set_mobj_rotate_x(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 _mobj_set_alpha(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(_mobj_set_alpha) {
	s32* args = event->args;
	s32 layer = evtGetValue(event, args[0]);
	u8 alpha = evtGetValue(event, args[1]);
#endif
#ifndef NONMATCHING
s32 _mobj_destroy(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 _get_bgset_attack_data(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(_mobj_destroy) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	BattleUnit* unit;
	BattleUnitPart* part;
	s32 layer;
	int i;
#endif
#ifndef NONMATCHING
s32 _bgset_kemuri_effect(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 _bgset_audience_bgset_access(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(_get_bgset_attack_data) {
	BattleWork* wp = _battleWorkPointer;
	s32* args = event->args;
	s32 type = evtGetValue(event, args[0]);
	s32 out = args[1];
	BattleWeapon* weapon;
#endif
#ifndef NONMATCHING
s32 _set_mobj_shake_init(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 _set_mobj_shake(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
void _mobj_shake_main(BattleStageObject* obj);
#endif

#ifdef NONMATCHING
USER_FUNC(_bgset_audience_bgset_access) {
	BattleAudience_Case_HaikeiSet();
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
void BattleStage_NozzleDirChangeCheck(void);
#endif

#ifdef NONMATCHING
USER_FUNC(_set_mobj_shake_init) {
	BattleWork* wp = _battleWorkPointer;
	s32 layer;
	int i;
	BattleStageObject* obj;
	u8 position;
#endif
#ifndef NONMATCHING
void _Nozzle_Change_Check(u8 index, u8* rate);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 _nozzle_turn(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(_set_mobj_shake) {
#endif
#ifndef NONMATCHING
void BattleStage_WallCloseCheck(void);

s32 _announce_wall_message(EventEntry* event, BOOL isFirstCall);

void _disp_escape_wall_message(CameraId camera, void* param);

void BattleStage_IronFrameFallCheck(void);

s32 _fall_frame_wait(EventEntry* event, BOOL isFirstCall);

s32 _fall_frame_wait_unit_ready(EventEntry* event, BOOL isFirstCall);

s32 _fall_frame(EventEntry* event, BOOL isFirstCall);

s32 _fall_frame_delete(EventEntry* event, BOOL isFirstCall);

void BattleStage_NozzleWorkCheck(s32 type);

void _nozzle_type_init(void);

s32 _nozzle_work_wait(EventEntry* event, BOOL isFirstCall);

f32 _get_nozzle_dir(s32 index);

s32 _nozzle_work_effect(EventEntry* event, BOOL isFirstCall);

BOOL BattleFogEndCheck(void);

BOOL BattleFogForceStop(void);

s32 _nozzle_work_attack_set(EventEntry* event, BOOL isFirstCall);

s32 _get_nozzle_attack_index(u8 index);

void _rate_mix(s8* dstChance, s8* dstTime, s8* srcChance, s8* srcTime);

void _rate_mix_3(s8* dstChance, s8* dstTime, s8* dstStrength, s8* srcChance, s8* srcTime, s8* srcStrength);

void _combine_nozzle_weapon(BOOL copy, BattleWeapon* dst, BattleWeapon* src);

s32 _nozzle_work_get_weapon_address(EventEntry* event, BOOL isFirstCall);

s32 BattleStage_ObjectFallCheck(void);

s32 _object_fall_wait(EventEntry* event, BOOL isFirstCall);


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
s32 _object_fall_wait(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_get_weapon_address(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_attack_set(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_effect(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_work_wait(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame_delete(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame_wait_unit_ready(EventEntry* event, BOOL isFirstCall);
s32 _fall_frame_wait(EventEntry* event, BOOL isFirstCall);
s32 _announce_wall_message(EventEntry* event, BOOL isFirstCall);
s32 _nozzle_turn(EventEntry* event, BOOL isFirstCall);
s32 _set_mobj_shake(EventEntry* event, BOOL isFirstCall);
s32 _set_mobj_shake_init(EventEntry* event, BOOL isFirstCall);
s32 _bgset_audience_bgset_access(EventEntry* event, BOOL isFirstCall);
s32 _bgset_kemuri_effect(EventEntry* event, BOOL isFirstCall);
s32 _get_bgset_attack_data(EventEntry* event, BOOL isFirstCall);
s32 _mobj_destroy(EventEntry* event, BOOL isFirstCall);
s32 _mobj_set_alpha(EventEntry* event, BOOL isFirstCall);
s32 _set_mobj_rotate_x(EventEntry* event, BOOL isFirstCall);

s32 _object_fall_attack(EventEntry *event, BOOL isFirstCall);


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

#pragma dont_inline on
s32 _set_mobj_shake(EventEntry* event, BOOL isFirstCall) {
#endif
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
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void _mobj_shake_main(BattleStageObject* obj) {
#ifdef NONMATCHING
	obj->mShakePeriodPosition++;
	if (obj->mShakePeriodPosition >= obj->mShakePeriodLength) {
		obj->mShakePeriodPosition = 0;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x88630074
		opword 0x38030001
		opword 0x981F0074
		opword 0x887F0074
		opword 0x881F0073
		opword 0x7C030040
		opword 0x4180000C
		opword 0x38000000
		opword 0x981F0074
		opword 0x88BF0074
		opword 0x3C004330
		lis r3, double_to_int_802f3c30@ha
		opword 0x889F0073
		opword 0x1CA50168
		opword 0x90010008
		lfd f1, double_to_int_802f3c30@l(r3)
		opword 0x7C0523D6
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC200828
		bl sinfd
		lfs f0, float_5_8041cd10(r2)
		opword 0xEC000072
		opword 0xD01F0078
		opword 0xC01F0078
		opword 0xD01F001C
		opword 0x83E1001C
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
#endif
	}
#ifdef NONMATCHING
	obj->mShakeAngle = 5.0f * sinfd(obj->mShakePeriodPosition * 360 / obj->mShakePeriodLength);
	obj->mRotation.x = obj->mShakeAngle;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
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
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 _nozzle_turn(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		lwz r5, _battleWorkPointer(r13)
		opword 0x7C7D1B78
		opword 0x2C040000
		lis r3, vec3_802f3ac8@ha
		opword 0x3FE50002
		opword 0x83DD0160
		addi r28, r3, vec3_802f3ac8@l
		opword 0x3BFF80C0
		opword 0x41820028
		opword 0x38000000
		opword 0x7C7FF214
		opword 0x901D0080
		opword 0x901D0084
		opword 0x880301C4
		opword 0x28000000
		opword 0x4182000C
		opword 0x3800001E
		opword 0x901D0080
		opword 0x2C1E0001
		opword 0x41820028
		opword 0x40800010
		opword 0x2C1E0000
		opword 0x40800014
		opword 0x48000028
		opword 0x2C1E0003
		opword 0x40800020
		opword 0x48000014
		opword 0x387C00C0
		opword 0x4800001C
		opword 0x387C00CC
		opword 0x48000014
		opword 0x387C00D8
		opword 0x4800000C
		opword 0x38600002
		opword 0x480001A8
		bl BattleSearchObjectPtr
		opword 0x807D0080
		opword 0x2C03001E
		opword 0x4080002C
		opword 0x38030001
		lfs f1, float_0_8041cd04(r2)
		opword 0x901D0080
		opword 0x38600002
		lfs f2, float_neg80_8041cd3c(r2)
		opword 0x38A0001E
		opword 0x809D0080
		bl intpl_sub
		opword 0xFFE00890
		opword 0x48000008
		lfs f31, float_neg80_8041cd3c(r2)
		opword 0x807D0084
		opword 0x2C03001E
		opword 0x408000B8
		opword 0x38030001
		opword 0x7C7FF214
		opword 0x901D0084
		opword 0x880301C4
		opword 0x2C000002
		opword 0x4182002C
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820030
		opword 0x40800014
		opword 0x48000028
		opword 0x2C000004
		opword 0x40800020
		opword 0x48000014
		lfs f1, float_45_8041cd2c(r2)
		opword 0x48000018
		lfs f1, float_0_8041cd04(r2)
		opword 0x48000010
		lfs f1, float_neg45_8041cd4c(r2)
		opword 0x48000008
		lfs f1, float_0_8041cd04(r2)
		opword 0x7C7FF214
		opword 0x880301C7
		opword 0x2C000002
		opword 0x4182002C
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820030
		opword 0x40800014
		opword 0x48000028
		opword 0x2C000004
		opword 0x40800020
		opword 0x48000014
		lfs f2, float_45_8041cd2c(r2)
		opword 0x48000018
		lfs f2, float_0_8041cd04(r2)
		opword 0x48000010
		lfs f2, float_neg45_8041cd4c(r2)
		opword 0x48000008
		lfs f2, float_0_8041cd04(r2)
		opword 0x809D0084
		opword 0x3860000C
		opword 0x38A0001E
		bl intpl_sub
		fmr f30, f1
		opword 0x2C1E0001
		opword 0x41820038
		opword 0x40800010
		opword 0x2C1E0000
		opword 0x40800014
		opword 0x48000054
		opword 0x2C1E0003
		opword 0x4080004C
		opword 0x48000034
		opword 0xFC20F890
		lfs f3, float_0_8041cd04(r2)
		opword 0xFC40F090
		opword 0x387C01D8
		bl mapObjRotate
		opword 0x48000030
		opword 0xFC20F890
		lfs f3, float_0_8041cd04(r2)
		opword 0xFC40F090
		opword 0x387C01E4
		bl mapObjRotate
		opword 0x48000018
		opword 0xFC20F890
		lfs f3, float_0_8041cd04(r2)
		opword 0xFC40F090
		opword 0x387C01F0
		bl mapObjRotate
		opword 0x801D0080
		opword 0x2C00001E
		opword 0x41800034
		opword 0x801D0084
		opword 0x2C00001E
		opword 0x41800028
		opword 0x7CDFF214
		opword 0x57C0103A
		opword 0x88A601C7
		opword 0x7C9F0214
		opword 0x38000000
		opword 0x38600002
		opword 0x98A601C4
		opword 0x900401CC
		opword 0x48000008
		opword 0x38600000
#endif
	}
#ifdef NONMATCHING
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
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void BattleStage_WallCloseCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (!(sw->flags & 0x10)) {
		sw->flags |= 0x10;
		sw->closeWallEvtId = evtEntry(_close_wall_event, 10, 0)->eventId;
	}
}

#ifdef NONMATCHING
USER_FUNC(_announce_wall_message) {
	if (isFirstCall) {
		event->userdata[0] = 60;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 _announce_wall_message(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x2C040000
		opword 0x90010014
		opword 0x4182000C
		opword 0x3800003C
		opword 0x90030078
		opword 0x80830078
		opword 0x2C040000
		opword 0x4080000C
		opword 0x38600002
		opword 0x4800002C
		opword 0x3804FFFF
		lis r4, _disp_escape_wall_message@ha
		opword 0x90030078
		addi r5, r4, _disp_escape_wall_message@l
		lfs f1, float_900_8041cd64(r2)
		opword 0x38600008
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		opword 0x38600000
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
#endif
	}
#ifdef NONMATCHING
	if (event->userdata[0] < 0) {
		return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void _disp_escape_wall_message(CameraId camera, void* param) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0x93E1002C
		lis r3, str_802F3C84@ha
		addi r3, r3, str_802F3C84@l
		bl msgSearch
		opword 0x7C7F1B78
		bl FontGetMessageWidth
		opword 0x5466043E
		opword 0x3CA04330
		opword 0x7CC00E70
		lis r4, double_to_int_802f3c30@ha
		opword 0x7C600194
		opword 0x38060028
		opword 0x6C638000
		addi r6, r4, double_to_int_802f3c30@l
		opword 0x90610014
		opword 0x6C008000
		lwz r7, dat_8041ccf8(r2)
		opword 0x38810008
		opword 0x90A10010
		opword 0x38600000
		opword 0xC8660000
		opword 0xC8010010
		lfs f2, float_0_8041cd04(r2)
		opword 0xEC001828
		opword 0x9001001C
		lfs f1, float_20_8041cd40(r2)
		opword 0x90A10018
		opword 0xEFE20028
		lfs f2, float_neg117_8041cd58(r2)
		opword 0xC8010018
		opword 0x90E10008
		opword 0xEC3F0828
		lfs f4, float_30_8041cd5c(r2)
		opword 0xEC601828
		lfs f5, float_10_8041cd34(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0xFC20F890
		lfs f2, float_neg120_8041cd60(r2)
		opword 0x7FE3FB78
		bl FontDrawString
		opword 0xE3E10038
		opword 0x80010044
		opword 0xCBE10030
		opword 0x83E1002C
		opword 0x7C0803A6
		opword 0x38210040
#endif
	}
#ifdef NONMATCHING
	event->userdata[0]--;
	dispEntry(CAMERA_2D, 900.0f, 1, _disp_escape_wall_message, NULL);
	return EVT_RETURN_BLOCK;
#endif
}
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
#ifndef NONMATCHING
#pragma pop
#endif

void BattleStage_IronFrameFallCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);

	if (!(sw->flags & 0x40) && !(sw->flags & 0x20)) {
		sw->flags |= 0x20;
		sw->fallFrameEvtId = evtEntry(_fall_frame_event, 10, 0)->eventId;
	}
}

#ifdef NONMATCHING
USER_FUNC(_fall_frame_wait) {
#endif
#ifndef NONMATCHING
s32 _fall_frame_wait(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(_fall_frame_wait_unit_ready) {
#endif
#ifndef NONMATCHING
s32 _fall_frame_wait_unit_ready(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(_fall_frame) {
	BattleWork* wp;
	s32 arg = event->args[0];
	BattleStageObject* body;
	BattleStageObjectWork* sw;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 _fall_frame(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBF810010
		opword 0x7C7E1B78
		opword 0x7C9D2378
		opword 0x80C30018
		lis r3, str_802F3C7C@ha
		lwz r5, _battleWorkPointer(r13)
		addi r3, r3, str_802F3C7C@l
		opword 0x83E60000
		opword 0x3F850002
		bl BattleSearchObjectPtr
		opword 0x2C1D0000
		opword 0x7C7D1B78
		opword 0x41820020
		opword 0x38000000
		opword 0x901E0080
		opword 0xC01D0008
		opword 0xFC00001E
		opword 0xD8010008
		opword 0x8001000C
		opword 0x901E0084
		opword 0x80BE0080
		lis r4, double_to_int_802f3c30@ha
		opword 0x3C604330
		lfd f1, double_to_int_802f3c30@l(r4)
		opword 0x38A50001
		opword 0x90610008
		opword 0x3800003C
		lfs f2, float_0_8041cd04(r2)
		opword 0x90BE0080
		opword 0x38600002
		opword 0x38A0003C
		opword 0x809E0080
		opword 0x80DE0084
		opword 0x7C8421D6
		opword 0x6CC68000
		opword 0x90C1000C
		opword 0xC8010008
		opword 0x7C8403D6
		opword 0xEC200828
		bl intpl_sub
		opword 0xD03D0008
		opword 0x801E0080
		opword 0x2C00003C
		opword 0x4080000C
		opword 0x38600000
		opword 0x48000018
		opword 0x80BC80F8
		opword 0x7FC3F378
		opword 0x7FE4FB78
		bl evtSetValue
		opword 0x38600002
		opword 0xBB810010
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
	wp = _battleWorkPointer;
	sw = STAGE_WORK(wp);
	body = BattleSearchObjectPtr("if_body");
	if (isFirstCall) {
		EVT_UW(event, 2) = 0;
		EVT_UW(event, 3) = body->mPosition.y;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 _fall_frame_delete(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x2C040000
		opword 0x90010024
		opword 0xBFC10018
		opword 0x7C7E1B78
		lwz r5, _battleWorkPointer(r13)
		opword 0x3FE50002
		opword 0x4182000C
		opword 0x380000FF
		opword 0x901E0080
		opword 0x80BE0080
		lis r3, str_802F3C7C@ha
		addi r3, r3, str_802F3C7C@l
		opword 0x3881000C
		opword 0x3805FFFB
		opword 0x901E0080
		lwz r5, dat_8041ccfc(r2)
		opword 0x801E0080
		opword 0x90A10008
		opword 0x9801000B
		opword 0x80010008
		opword 0x9001000C
		bl mapGrpSetColor
		opword 0x801E0080
		opword 0x2C000000
		opword 0x4081000C
		opword 0x38600000
		opword 0x48000010
		opword 0x38000000
		opword 0x38600002
		opword 0x901F82A8
		opword 0xBBC10018
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
#endif
	}
#ifdef NONMATCHING
	EVT_UW(event, 2)++;
	body->mPosition.y = intpl_sub(2, EVT_UW(event, 3), 0.0f, EVT_UW(event, 2) * EVT_UW(event, 2) / 60, 60);
	if (EVT_UW(event, 2) < 60) {
		return EVT_RETURN_BLOCK;
	}
	evtSetValue(event, arg, (s32)sw->fallObjectData);
	return EVT_RETURN_DONE;
#endif
}
#ifndef NONMATCHING
#pragma pop
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
#ifndef NONMATCHING
#pragma dont_inline on
#endif
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
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

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

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_wait) {
#endif
#ifndef NONMATCHING
s32 _nozzle_work_wait(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
f32 _get_nozzle_dir(s32 index) {
#ifdef NONMATCHING
	switch (STAGE_WORK(_battleWorkPointer)->nozzleDir[index]) {
		case 1:
			return -45.0f;
		case 3:
			return -135.0f;
		case 2:
		default:
			return -90.0f;
#endif
#ifndef NONMATCHING
	asm volatile {
		lwz r4, _battleWorkPointer(r13)
		opword 0x3C040002
		opword 0x7C601A14
		opword 0x88038284
		opword 0x2C000002
		opword 0x41820030
		opword 0x40800010
		opword 0x2C000001
		opword 0x40800014
		opword 0x48000020
		opword 0x2C000004
		opword 0x40800018
		opword 0x4800000C
		lfs f1, float_neg45_8041cd4c(r2)
		opword 0x4E800020
		lfs f1, float_neg135_8041cd50(r2)
		opword 0x4E800020
		lfs f1, float_neg90_8041cd54(r2)
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 _nozzle_work_effect(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x7C791B78
		lwz r6, _battleWorkPointer(r13)
		opword 0x83430018
		opword 0x7C972378
		lis r5, vec3_802f3ac8@ha
		opword 0x7CD83378
		opword 0x809A0000
		addi r30, r5, vec3_802f3ac8@l
		opword 0x3FA60002
		opword 0x3B600000
		bl evtGetValue
		opword 0x2C170000
		opword 0x835A0004
		opword 0x7C7F1B78
		li r23, 0x0
		opword 0x418204F0
		opword 0x7F03C378
		bl BattleCheckConcluded
		opword 0x2C030000
		opword 0x4182001C
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x38A00000
		bl evtSetValue
		opword 0x38600002
		opword 0x48000540
		opword 0x3800005A
		opword 0x90190078
		opword 0x881D828A
		opword 0x7C000774
		opword 0x2C000002
		opword 0x4182002C
		opword 0x40800010
		opword 0x2C000001
		opword 0x40800014
		opword 0x48000030
		opword 0x2C000004
		opword 0x40800028
		opword 0x4800001C
		opword 0x3B9E0170
		opword 0x3B600000
		opword 0x48000018
		opword 0x3B800000
		opword 0x3B600001
		opword 0x4800000C
		opword 0x3B9E0188
		opword 0x3B600002
		opword 0x2C000004
		opword 0x408003C0
		opword 0x2C000001
		opword 0x40800008
		opword 0x480003B4
		opword 0x387E00C0
		bl BattleSearchObjectPtr
		opword 0x7C781B78
		opword 0x38600000
		bl _get_nozzle_dir
		opword 0x881D8284
		fmr f29, f1
		opword 0x28000000
		opword 0x4182008C
		opword 0x281C0000
		opword 0x41820018
		opword 0x7F83E378
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x9079008C
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x9019008C
		lfs f0, float_90_8041cd08(r2)
		opword 0xEC20E82A
		bl reviseAngle
		opword 0xFFE00890
		opword 0xFC20E890
		bl sinfd
		lfs f2, float_10_8041cd34(r2)
		opword 0xC018000C
		opword 0xEFC2007A
		opword 0xFC20E890
		bl cosfd
		lfs f4, float_10_8041cd34(r2)
		opword 0xFC60F090
		opword 0xC0180004
		opword 0xFCA0F890
		lfs f2, float_12_8041cd38(r2)
		opword 0x7F63DB78
		opword 0xEC24007C
		opword 0xC0180008
		opword 0x3880005A
		lfs f4, float_neg80_8041cd3c(r2)
		opword 0xEC42002A
		bl effNozleEntry
		opword 0x9079007C
		opword 0x48000090
		opword 0x281C0000
		opword 0x41820018
		opword 0x7F83E378
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x9079008C
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x9019008C
		lfs f4, float_0_8041cd04(r2)
		opword 0x7F63DB78
		lfs f2, float_20_8041cd40(r2)
		opword 0x3880005A
		opword 0xC0380008
		opword 0xFCA02090
		lfs f3, float_8_8041cd44(r2)
		opword 0xC018000C
		opword 0xEC42082A
		opword 0xC0380004
		opword 0xEC63002A
		bl effNozleEntry
		opword 0x2C1F0000
		opword 0x9079007C
		opword 0x40820030
		lfs f2, float_20_8041cd40(r2)
		opword 0x38600004
		opword 0xC0380008
		opword 0x3880005A
		lfs f3, float_8_8041cd44(r2)
		opword 0xC018000C
		opword 0xEC42082A
		opword 0xC0380004
		opword 0xEC63002A
		lfs f4, float_1_8041cd48(r2)
		bl effConfettiN64Entry
		opword 0x387E00CC
		bl BattleSearchObjectPtr
		opword 0x7C781B78
		opword 0x38600001
		bl _get_nozzle_dir
		opword 0x881D8285
		opword 0xFFA00890
		opword 0x28000000
		opword 0x4182008C
		opword 0x281C0000
		opword 0x41820018
		opword 0x7F83E378
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x90790090
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x90190090
		lfs f0, float_90_8041cd08(r2)
		opword 0xEC20E82A
		bl reviseAngle
		opword 0xFFE00890
		opword 0xFC20E890
		bl sinfd
		lfs f2, float_10_8041cd34(r2)
		opword 0xC018000C
		opword 0xEFC2007A
		opword 0xFC20E890
		bl cosfd
		lfs f4, float_10_8041cd34(r2)
		opword 0xFC60F090
		opword 0xC0180004
		opword 0xFCA0F890
		lfs f2, float_12_8041cd38(r2)
		opword 0x7F63DB78
		opword 0xEC24007C
		opword 0xC0180008
		opword 0x3880005A
		lfs f4, float_neg80_8041cd3c(r2)
		opword 0xEC42002A
		bl effNozleEntry
		opword 0x90790080
		opword 0x48000090
		opword 0x281C0000
		opword 0x41820018
		opword 0x7F83E378
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x90790090
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x90190090
		lfs f4, float_0_8041cd04(r2)
		opword 0x7F63DB78
		lfs f2, float_20_8041cd40(r2)
		opword 0x3880005A
		opword 0xC0380008
		opword 0xFCA02090
		lfs f3, float_8_8041cd44(r2)
		opword 0xC018000C
		opword 0xEC42082A
		opword 0xC0380004
		opword 0xEC63002A
		bl effNozleEntry
		opword 0x2C1F0000
		opword 0x90790080
		opword 0x40820030
		lfs f2, float_20_8041cd40(r2)
		opword 0x38600004
		opword 0xC0380008
		opword 0x3880005A
		lfs f3, float_8_8041cd44(r2)
		opword 0xC018000C
		opword 0xEC42082A
		opword 0xC0380004
		opword 0xEC63002A
		lfs f4, float_1_8041cd48(r2)
		bl effConfettiN64Entry
		opword 0x387E00D8
		bl BattleSearchObjectPtr
		opword 0x7C7E1B78
		opword 0x38600002
		bl _get_nozzle_dir
		opword 0x881D8286
		opword 0xFFA00890
		opword 0x28000000
		opword 0x4182008C
		opword 0x281C0000
		opword 0x41820018
		opword 0x7F83E378
		opword 0x389E0004
		bl psndSFXOn_3D
		opword 0x90790094
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x90190094
		lfs f0, float_90_8041cd08(r2)
		opword 0xEC20E82A
		bl reviseAngle
		opword 0xFFC00890
		opword 0xFC20E890
		bl sinfd
		lfs f2, float_10_8041cd34(r2)
		opword 0xC01E000C
		opword 0xEFE2007A
		opword 0xFC20E890
		bl cosfd
		lfs f4, float_10_8041cd34(r2)
		opword 0xFC60F890
		opword 0xC01E0004
		opword 0xFCA0F090
		lfs f2, float_12_8041cd38(r2)
		opword 0x7F63DB78
		opword 0xEC24007C
		opword 0xC01E0008
		opword 0x3880005A
		lfs f4, float_neg80_8041cd3c(r2)
		opword 0xEC42002A
		bl effNozleEntry
		opword 0x90790084
		opword 0x48000090
		opword 0x281C0000
		opword 0x41820018
		opword 0x7F83E378
		opword 0x389E0004
		bl psndSFXOn_3D
		opword 0x90790094
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x90190094
		lfs f4, float_0_8041cd04(r2)
		opword 0x7F63DB78
		lfs f2, float_20_8041cd40(r2)
		opword 0x3880005A
		opword 0xC03E0008
		opword 0xFCA02090
		lfs f3, float_8_8041cd44(r2)
		opword 0xC01E000C
		opword 0xEC42082A
		opword 0xC03E0004
		opword 0xEC63002A
		bl effNozleEntry
		opword 0x2C1F0000
		opword 0x90790084
		opword 0x40820030
		lfs f2, float_20_8041cd40(r2)
		opword 0x38600004
		opword 0xC03E0008
		opword 0x3880005A
		lfs f3, float_8_8041cd44(r2)
		opword 0xC01E000C
		opword 0xEC42082A
		opword 0xC03E0004
		opword 0xEC63002A
		lfs f4, float_1_8041cd48(r2)
		bl effConfettiN64Entry
		opword 0x3AE00001
		opword 0x48000090
		opword 0x2C1F0000
		opword 0x41820088
		opword 0x801D82A0
		opword 0x28000000
		opword 0x4082007C
		opword 0x38000078
		lfs f1, float_0_8041cd04(r2)
		opword 0x90190078
		opword 0x38000000
		opword 0xFC400890
		opword 0x38600003
		opword 0x9019007C
		opword 0xFC600890
		opword 0xFC800890
		opword 0x388003E8
		opword 0x90190084
		opword 0xFCA00890
		opword 0x90190080
		bl effNozleEntry
		opword 0x907D82A0
		opword 0x38000002
		opword 0x387E00CC
		opword 0x809D82A0
		opword 0x90990084
		opword 0x901D829C
		bl BattleSearchObjectPtr
		opword 0x7C641B78
		opword 0x387E019C
		opword 0x38840004
		bl psndSFXOn_3D
		opword 0x9079008C
		opword 0x3800FFFF
		opword 0x3AE00001
		opword 0x90190090
		opword 0x90190094
		opword 0x2C170000
		opword 0x4082001C
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x38A00000
		bl evtSetValue
		opword 0x38600002
		opword 0x4800007C
		opword 0x80790078
		opword 0x2C030000
		opword 0x4081005C
		opword 0x3803FFFF
		opword 0x90190078
		opword 0x80190078
		opword 0x2C000000
		opword 0x41810040
		opword 0x8079008C
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820008
		bl psndSFXOff
		opword 0x80790090
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820008
		bl psndSFXOff
		opword 0x80790094
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820008
		bl psndSFXOff
		opword 0x38600000
		opword 0x48000018
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x38A00001
		bl evtSetValue
		opword 0x38600002
#endif
	}
#ifdef NONMATCHING
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
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_attack_set) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 _nozzle_work_attack_set(EventEntry* event, BOOL isFirstCall) {
#endif
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
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

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

void _rate_mix(s8* dstChance, s8* dstTime, s8* srcChance, s8* srcTime) {
	if (*srcChance <= 0) {
		return;
	}
	if (*srcChance > *dstChance) {
		*dstChance = *srcChance;
	}
	*dstTime += *srcTime;
}

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

#ifndef NONMATCHING
#pragma dont_inline on
#endif
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
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
USER_FUNC(_nozzle_work_get_weapon_address) {
#endif
#ifndef NONMATCHING
s32 _nozzle_work_get_weapon_address(EventEntry* event, BOOL isFirstCall) {
#endif
	BattleWork* wp = _battleWorkPointer;
	BattleStageObjectWork* sw = STAGE_WORK(wp);
	s32* args = event->args;
	s32 index = evtGetValue(event, args[0]);

	evtSetValue(event, args[1], (s32)sw->nozzleWeapons[index]);
	return EVT_RETURN_DONE;
}

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

#ifdef NONMATCHING
USER_FUNC(_object_fall_wait) {
#endif
#ifndef NONMATCHING
s32 _object_fall_wait(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifndef NONMATCHING
#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 _object_fall_attack(EventEntry *event, BOOL isFirstCall) {
	char _af_pad[5624];
	asm volatile {
		lwz r6, _battleWorkPointer(r13)
		opword 0x7C6F1B78
		opword 0x80E30018
		lis r5, vec3_802f3ac8@ha
		opword 0x3C660002
		opword 0x2C040000
		opword 0x822380F8
		opword 0x7CD93378
		opword 0x82C70000
		addi r30, r5, vec3_802f3ac8@l
		opword 0x3AA00000
		opword 0x41820494
		opword 0x386000EC
		bl BattleAlloc
		opword 0x7C6E1B78
		opword 0x38000000
		opword 0x91CF0078
		opword 0x38800000
		opword 0x38A000EC
		opword 0x900F007C
		bl memset
		opword 0x3860FFFF
		opword 0x38000003
		opword 0x986E0004
		opword 0x38800000
		opword 0x7C0903A6
		opword 0x38040001
		opword 0x38840001
		opword 0x7C6E01AE
		opword 0x4200FFF4
		opword 0x7F23CB78
		bl BattleCheckConcluded
		opword 0x2C030000
		opword 0x4182001C
		opword 0x80AF007C
		opword 0x7DE37B78
		opword 0x7EC4B378
		bl evtSetValue
		opword 0x38600002
		opword 0x48000CE8
		opword 0x38000001
		opword 0x3A000000
		opword 0x980E0000
		opword 0x3B000000
		opword 0x480002C4
		opword 0x3AF80004
		opword 0x38000003
		opword 0x7EEEBA14
		opword 0x3A400000
		opword 0x9A170000
		opword 0x7C0903A6
		opword 0x38120001
		opword 0x7C0E00AE
		opword 0x7C000774
		opword 0x2C00FFFF
		opword 0x4182000C
		opword 0x3A520001
		opword 0x4200FFE8
		opword 0x2C120003
		opword 0x4180001C
		opword 0x38600003
		bl irand
		opword 0x38030001
		opword 0x7C0E00AE
		opword 0x98170001
		opword 0x48000070
		opword 0x38000009
		opword 0x38600000
		opword 0x38800000
		opword 0x7C0903A6
		opword 0x380400C0
		opword 0x38840001
		opword 0x7C1100AE
		opword 0x7C630214
		opword 0x4200FFF0
		bl irand
		opword 0x38000000
		opword 0x98170001
		opword 0x48000024
		opword 0x7CA40774
		opword 0x380400C0
		opword 0x7C1100AE
		opword 0x7C601851
		opword 0x41800020
		opword 0x88970001
		opword 0x38040001
		opword 0x98170001
		opword 0x88B70001
		opword 0x7CA00774
		opword 0x2C000008
		opword 0x4180FFD4
		opword 0x38120001
		opword 0x7CAE01AE
		opword 0x88770001
		opword 0x38000018
		opword 0x38B70024
		opword 0x7C630774
		opword 0x1C6300C0
		opword 0x386300CC
		opword 0x7C911A14
		opword 0x7C0903A6
		opword 0x3884FFFC
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		opword 0x88170001
		opword 0x2C000006
		opword 0x40820048
		opword 0x38600064
		bl irand
		opword 0x2C030032
		opword 0x40800020
		opword 0x8017008C
		opword 0x60000100
		opword 0x9017008C
		opword 0x8017008C
		opword 0x540005EA
		opword 0x9017008C
		opword 0x4800001C
		opword 0x8017008C
		opword 0x5400062C
		opword 0x9017008C
		opword 0x8017008C
		opword 0x60000200
		opword 0x9017008C
		opword 0x38000000
		opword 0x3A570028
		opword 0x90170004
		bl pouchGetPtr
		opword 0xA003008C
		opword 0x28000000
		opword 0x41820070
		bl BattleAudienceBaseGetPtr
		opword 0x80030000
		opword 0x54000463
		opword 0x40820060
		opword 0x88170001
		opword 0x7C000774
		opword 0x2C000006
		opword 0x41820050
		opword 0x2C000007
		opword 0x41820048
		opword 0x3C790002
		opword 0x80039068
		opword 0x540007BD
		opword 0x40820014
		opword 0x38600064
		bl irand
		opword 0x2C03000A
		opword 0x40800028
		opword 0x38600001
		opword 0x3800FFFF
		opword 0x90770004
		opword 0x9017000C
		bl BattleAudience_HaitiRandForFallObject
		opword 0x90770008
		opword 0x38000001
		opword 0x3AA00001
		opword 0x900F007C
		opword 0x80170004
		opword 0x2C000000
		opword 0x408200E0
		opword 0x7F23CB78
		bl BattleGetSystemPtr
		opword 0x88190012
		opword 0x7E449378
		opword 0x80A30000
		la r3, _af_pad+2820
		opword 0x7C0000D0
		opword 0x80F20064
		opword 0x81120068
		opword 0x7C090774
		opword 0x38C00001
		bl BattleSamplingEnemy
		opword 0x88011578
		opword 0x7C000775
		opword 0x4181001C
		opword 0x80AF007C
		opword 0x7DE37B78
		opword 0x7EC4B378
		bl evtSetValue
		opword 0x38600002
		opword 0x48000AA4
		opword 0x8092007C
		opword 0x38610B0C
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x3AA00001
		bl BattleChoiceSamplingEnemy
		opword 0x8061000C
		opword 0x38100001
		opword 0x38A00001
		opword 0x7E078378
		opword 0x90770008
		opword 0x1C7000E8
		opword 0x38800000
		opword 0x80C10008
		opword 0x90D7000C
		opword 0x98B70014
		opword 0x7C0903A6
		opword 0x2C100000
		opword 0x41800040
		opword 0x38C30004
		opword 0x7CCE3214
		opword 0x7C173040
		opword 0x41820024
		opword 0x80060004
		opword 0x2C000000
		opword 0x40820018
		opword 0x80B70008
		opword 0x80060008
		opword 0x7C050000
		opword 0x40820008
		opword 0x98860014
		opword 0x38E7FFFF
		opword 0x3863FF18
		opword 0x4200FFC8
		opword 0x3A100001
		opword 0x3B1800E8
		opword 0x880E0000
		opword 0x7C100000
		opword 0x4180FD38
		opword 0x2C150000
		opword 0x4082001C
		opword 0x80AF007C
		opword 0x7DE37B78
		opword 0x7EC4B378
		bl evtSetValue
		opword 0x38600002
		opword 0x480009E8
		opword 0x3A000000
		opword 0x3B000000
		opword 0x4800010C
		opword 0x3A380004
		opword 0x7E2E8A14
		opword 0x80110004
		opword 0x3AF10028
		opword 0x2C000000
		opword 0x408200EC
		opword 0x88110014
		opword 0x3B400000
		opword 0x28000000
		opword 0x41820008
		opword 0x635A0100
		opword 0x88110015
		opword 0x28000000
		opword 0x41820008
		opword 0x675A0010
		opword 0x80710008
		opword 0x8091000C
		bl BattleGetUnitPartsPtr
		opword 0x80910008
		opword 0x7C751B78
		opword 0x7F23CB78
		bl BattleGetUnitPtr
		opword 0x7C721B78
		opword 0x7F23CB78
		bl BattleGetSystemPtr
		opword 0x7E449378
		opword 0x7EA5AB78
		opword 0x7EE6BB78
		opword 0x7F47D378
		bl BattlePreCheckDamage
		opword 0x9071001C
		opword 0x8011001C
		opword 0x2C000001
		opword 0x4082007C
		opword 0x88110014
		opword 0x28000000
		opword 0x40820070
		opword 0x38600000
		bl irand
		opword 0x7C720734
		opword 0x3AA00000
		opword 0x3B400000
		opword 0x3B600001
		opword 0x4800004C
		opword 0x3AFA0004
		opword 0x80710008
		opword 0x7EEEBA14
		opword 0x80170008
		opword 0x7C030000
		opword 0x4082002C
		opword 0xB2570010
		opword 0x38600016
		bl irand
		opword 0x88170014
		opword 0x7C639214
		opword 0x38630014
		opword 0x28000000
		opword 0x7C720734
		opword 0x41820008
		opword 0x9B770015
		opword 0x3AB50001
		opword 0x3B5A00E8
		opword 0x7C158000
		opword 0x4180FFB4
		opword 0x3A100001
		opword 0x3B1800E8
		opword 0x880E0000
		opword 0x7C100000
		opword 0x4180FEF0
		opword 0x3BBE0114
		opword 0x381E0150
		opword 0x836F0078
		addi r14, r30, 0x130
		opword 0x93A115F4
		opword 0x3B810014
		opword 0x3B000001
		opword 0x3B400000
		opword 0x900115F0
		opword 0x3BE00000
		opword 0x48000864
		opword 0x3ABF0004
		opword 0x7EBBAA14
		opword 0x88150000
		opword 0x7C000774
		opword 0x2C00FFFF
		opword 0x41820844
		opword 0x80150004
		opword 0x3AE00000
		opword 0x3B000000
		opword 0x2C000000
		opword 0x40820028
		opword 0x80950008
		opword 0x7F23CB78
		bl BattleGetUnitPtr
		opword 0x7C601B78
		opword 0x80750008
		opword 0x8095000C
		opword 0x7C140378
		bl BattleGetUnitPartsPtr
		opword 0x7C731B78
		opword 0x80750024
		opword 0x28030000
		opword 0x41820010
		opword 0xA8150010
		opword 0x2C000000
		opword 0x40810438
		opword 0xA8750010
		opword 0x3803FFFF
		opword 0xB0150010
		opword 0xA8150010
		opword 0x2C000000
		opword 0x418107DC
		opword 0x80150004
		opword 0x2C000001
		opword 0x41820054
		opword 0x40800110
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000104
		opword 0x7E83A378
		opword 0x7E649B78
		opword 0x38C1002C
		opword 0x38E10030
		opword 0x38A10028
		bl BtlUnit_GetHitPos
		opword 0x7E83A378
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906115DC
		opword 0xC83E0168
		opword 0x900115D8
		opword 0xC80115D8
		opword 0xEFC00828
		opword 0x480000E0
		opword 0x80B50008
		opword 0x38800014
		opword 0x3C004330
		opword 0xC83E0168
		opword 0x7C6523D6
		opword 0x900115D8
		opword 0x7C0321D6
		opword 0x7C002850
		opword 0x1C600019
		opword 0x3803FF1A
		opword 0x6C008000
		opword 0x900115DC
		opword 0xC80115D8
		opword 0xEC000828
		opword 0xD0010028
		bl BattleStageGetPtr
		opword 0xC0030B34
		opword 0x3C004330
		opword 0x38C00014
		opword 0x900115E0
		opword 0xC85E0168
		opword 0x38600000
		opword 0xD001002C
		opword 0x38800006
		lfs f3, float_0p1_8041cd00(r2)
		opword 0x80F50008
		opword 0x900115E8
		opword 0x7CA733D6
		opword 0x7C0531D6
		opword 0x1CA5001E
		opword 0x7CC03850
		opword 0x38050073
		opword 0x6CC58000
		opword 0x6C008000
		opword 0x90A115E4
		opword 0x900115EC
		opword 0xC82115E0
		opword 0xC80115E8
		opword 0xEC211028
		opword 0xEC001028
		opword 0xEC03007A
		opword 0xD0010030
		bl btl_camera_set_mode
		opword 0x38600000
		opword 0x38800002
		bl btl_camera_set_moveSpeedLv
		lfs f30, float_0_8041cd04(r2)
		opword 0x48000020
		opword 0x809E0108
		opword 0x807E010C
		opword 0x801E0110
		opword 0x90810028
		lfs f30, float_0_8041cd04(r2)
		opword 0x9061002C
		opword 0x90010030
		opword 0x80A10028
		opword 0x7F23CB78
		opword 0x8081002C
		opword 0x80010030
		opword 0x90A10034
		opword 0x90810038
		opword 0xC0210034
		opword 0x9001003C
		opword 0xC0410038
		opword 0xC061003C
		bl BattleGetFloorHeight
		opword 0xC0410028
		lfs f0, float_0_8041cd04(r2)
		opword 0xD0210038
		opword 0xFC020040
		opword 0x4C411382
		opword 0x4082000C
		lfs f31, float_90_8041cd08(r2)
		opword 0x48000008
		lfs f31, float_270_8041cd0c(r2)
		opword 0x8015001C
		opword 0x2C000005
		opword 0x41820024
		opword 0x40800010
		opword 0x2C000002
		opword 0x40800010
		opword 0x48000014
		opword 0x2C000007
		opword 0x4080000C
		opword 0xC0010038
		opword 0xD001002C
		opword 0x3860FFFF
		opword 0x38000000
		opword 0x90750020
		opword 0xB0150012
		opword 0x88150001
		opword 0x7C000774
		opword 0x28000008
		opword 0x41810608
		lis r3, jumptable_80374848@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80374848@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		opword 0xC0210034
		opword 0x38600004
		opword 0xECA01028
		opword 0xC061003C
		opword 0x38800001
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x480005BC
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		opword 0xC0210034
		opword 0x38600005
		opword 0xECA01028
		opword 0xC061003C
		opword 0x38800001
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x48000588
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		opword 0xC0210034
		opword 0x38600000
		opword 0xECA01028
		opword 0xC061003C
		opword 0x38800064
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x48000554
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		opword 0xC0210034
		opword 0x38600001
		opword 0xECA01028
		opword 0xC061003C
		opword 0x38800001
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x48000520
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		lfs f7, float_5_8041cd10(r2)
		opword 0x38600002
		opword 0xC061003C
		opword 0xECA01028
		opword 0xC0210034
		opword 0xEC67182A
		opword 0x38800001
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x480004E4
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		opword 0xC0210034
		opword 0x38600008
		opword 0xECA01028
		opword 0xC061003C
		opword 0x38800001
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x480004B0
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		opword 0xC0210034
		opword 0x38600003
		opword 0xECA01028
		opword 0xC061003C
		opword 0x38800001
		opword 0x38A0005A
		bl effFallEntry
		opword 0x90750024
		opword 0x4800047C
		opword 0x7E83A378
		bl BtlUnit_GetBelong
		opword 0x7C600775
		opword 0x4082003C
		lfs f4, float_0_8041cd04(r2)
		opword 0xFCC0F890
		lfs f2, float_15_8041cd18(r2)
		opword 0x38600006
		opword 0xC001003C
		opword 0xFCA02090
		lfs f1, float_neg300_8041cd14(r2)
		opword 0xEC62002A
		opword 0xC0410038
		opword 0x38800001
		opword 0x38A000B4
		bl effFallEntry
		opword 0x90750024
		opword 0x48000434
		lfs f4, float_0_8041cd04(r2)
		opword 0xFCC0F890
		lfs f2, float_15_8041cd18(r2)
		opword 0x38600006
		opword 0xC001003C
		opword 0xFCA02090
		lfs f1, float_300_8041cd1c(r2)
		opword 0xEC62002A
		opword 0xC0410038
		opword 0x38800001
		opword 0x38A000B4
		bl effFallEntry
		opword 0x90750024
		opword 0x480003FC
		opword 0xC0410038
		opword 0xFC80F090
		opword 0xC001002C
		opword 0xFCC0F890
		lfs f7, float_5_8041cd10(r2)
		opword 0x38600007
		opword 0xC061003C
		opword 0xECA01028
		opword 0xC0210034
		opword 0xEC67182A
		opword 0x38800001
		opword 0x38A000B4
		bl effFallEntry
		opword 0x90750024
		opword 0x480003C0
		opword 0x28030000
		opword 0x41820010
		bl effFallCheckHit
		opword 0x2C030000
		opword 0x418203AC
		opword 0x80150004
		opword 0x3A550028
		opword 0x2C000001
		opword 0x40820074
		opword 0x88950001
		opword 0x80750008
		bl BattleAudience_Case_FallObject_Aud
		opword 0x80750020
		bl psndSFXOff
		opword 0x80750008
		opword 0x38A10020
		opword 0x38C10024
		opword 0x3881001C
		bl BattleAudience_GetHomePosition
		opword 0x88150001
		opword 0x7C000774
		opword 0x2C000005
		opword 0x4182035C
		opword 0x40800028
		opword 0x2C000002
		opword 0x40800020
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000014
		opword 0x7FA3EB78
		opword 0x3881001C
		bl psndSFXOn_3D
		opword 0x48000334
		opword 0x7DC37378
		opword 0x3881001C
		bl psndSFXOn_3D
		opword 0x48000324
		bl BattleAudience_Case_FallObject_Stage
		opword 0x80120064
		opword 0x540001CF
		opword 0x41820128
		opword 0x7E83A378
		opword 0x7E649B78
		opword 0x38C10020
		opword 0x38E10024
		opword 0x38A1001C
		bl BtlUnit_GetHitPos
		opword 0x88150014
		opword 0x3A000000
		opword 0x28000000
		opword 0x41820008
		opword 0x62100100
		opword 0x80750020
		bl psndSFXOff
		opword 0x8015001C
		opword 0x2C000005
		opword 0x418202D4
		opword 0x40800014
		opword 0x2C000001
		opword 0x4182004C
		opword 0x40800010
		opword 0x480002C0
		opword 0x2C000007
		opword 0x408002B8
		opword 0x88150001
		opword 0x7C000774
		opword 0x2C000005
		opword 0x418202A8
		opword 0x408002A4
		opword 0x2C000002
		opword 0x4080029C
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000290
		opword 0x7FA3EB78
		opword 0x3881001C
		bl psndSFXOn_3D
		opword 0x48000280
		opword 0x88150001
		opword 0x7C000774
		opword 0x2C000005
		opword 0x4182002C
		opword 0x40800038
		opword 0x2C000002
		opword 0x40800030
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000024
		opword 0x806115F4
		opword 0x3881001C
		bl psndSFXOn_3D
		opword 0x48000020
		opword 0x806115F0
		opword 0x3881001C
		bl psndSFXOn_3D
		opword 0x48000010
		opword 0x7DC37378
		opword 0x3881001C
		bl psndSFXOn_3D
		opword 0x7E83A378
		bl BtlUnit_GetACPossibility
		opword 0x2C030000
		opword 0x41820010
		opword 0x7E83A378
		opword 0x7E449378
		bl BattleActionCommandCheckDefence
		opword 0x7F23CB78
		bl BattleGetSystemPtr
		opword 0x7E84A378
		opword 0x7E659B78
		opword 0x7E469378
		opword 0x7E078378
		bl BattleCheckDamage
		opword 0x480001F0
		opword 0x80750020
		bl psndSFXOff
		opword 0x7F23CB78
		bl BattleGetSystemPtr
		opword 0x88190012
		opword 0x7E449378
		opword 0x80A30000
		opword 0x38610040
		opword 0x7C0000D0
		opword 0x80F20064
		opword 0x81120068
		opword 0x7C090774
		opword 0x38C00001
		bl BattleSamplingEnemy
		opword 0x88010AAC
		opword 0x7C000775
		opword 0x408101AC
		opword 0x88610AF7
		opword 0x88010AAC
		opword 0x7C630774
		opword 0x7C000774
		opword 0x7C030000
		opword 0x40800194
		opword 0x38030A6D
		opword 0x38810040
		opword 0x7C0400AE
		opword 0x7F23CB78
		opword 0x7C000774
		opword 0x1C800024
		opword 0x38010040
		opword 0x3A240004
		opword 0x7E208A14
		opword 0xA8910000
		bl BattleGetUnitPtr
		opword 0x7C601B78
		opword 0xA8710000
		opword 0xA8910002
		opword 0x7C100378
		bl BattleGetUnitPartsPtr
		opword 0x906115F8
		opword 0x7F23CB78
		bl BattleGetSystemPtr
		opword 0x80A115F8
		opword 0x7E048378
		opword 0x7E469378
		opword 0x38E00100
		bl BattlePreCheckDamage
		opword 0x2C030004
		opword 0x4182011C
		opword 0x4080001C
		opword 0x2C030002
		opword 0x41820110
		opword 0x4080001C
		opword 0x2C030001
		opword 0x408000B0
		opword 0x48000100
		opword 0x2C030006
		opword 0x4182008C
		opword 0x480000F4
		opword 0x7E038378
		opword 0x7F85E378
		opword 0x38C10018
		opword 0x38810010
		bl BtlUnit_GetPos
		opword 0xC03C0000
		lfs f0, float_85_8041cd20(r2)
		opword 0xFC010040
		opword 0x40800014
		lfs f0, float_50_8041cd24(r2)
		opword 0xEC01002A
		opword 0xD01C0000
		opword 0x48000010
		lfs f0, float_neg50_8041cd28(r2)
		opword 0xEC01002A
		opword 0xD01C0000
		opword 0xC0210010
		opword 0x38600006
		lfs f0, float_45_8041cd2c(r2)
		opword 0xC05C0000
		opword 0xEC210028
		opword 0xC0610018
		opword 0xD0210010
		bl effNiceEntry
		opword 0x80A3000C
		opword 0x38000000
		lfs f0, float_0p75_8041cd30(r2)
		opword 0x7E038378
		opword 0x38800126
		opword 0xD005001C
		opword 0x90100270
		bl BattleRunHitEvent
		opword 0x48000070
		opword 0x38000000
		opword 0x7E038378
		opword 0x90100270
		opword 0x38800127
		bl BattleRunHitEvent
		opword 0x48000058
		opword 0x7E038378
		bl BtlUnit_GetACPossibility
		opword 0x2C030000
		opword 0x4182001C
		opword 0x2C170000
		opword 0x41810014
		opword 0x7E038378
		opword 0x7E449378
		bl BattleActionCommandCheckDefence
		opword 0x3AF70001
		opword 0xA8710000
		opword 0xA8910002
		bl BattleGetUnitPartsPtr
		opword 0x7C711B78
		opword 0x7F23CB78
		bl BattleGetSystemPtr
		opword 0x7E048378
		opword 0x7E258B78
		opword 0x7E469378
		opword 0x38E00100
		bl BattleCheckDamage
		opword 0x88610AF7
		opword 0x38030001
		opword 0x98010AF7
		opword 0x4BFFFE5C
		opword 0x3800FFFF
		opword 0x98150000
		opword 0x3B5A0001
		opword 0x3BFF00E8
		opword 0x881B0000
		opword 0x7C1A0000
		opword 0x4180F798
		opword 0x2C180000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000020
		opword 0x806F0078
		bl BattleFree
		opword 0x80AF007C
		opword 0x7DE37B78
		opword 0x7EC4B378
		bl evtSetValue
		opword 0x38600002
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 _set_mobj_shake_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r29, _battleWorkPointer(r13)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r30, r3
	li r28, 0x0
	li r31, 0x0
L_af_1:
	addis r27, r31, 0x1
	addi r27, r27, 0x7140
	add r27, r29, r27
	lwz r0, 0x0(r27)
	cmpwi r0, 0x0
	ble L_af_2
	lwz r3, 0x64(r27)
	lhz r0, 0x6(r3)
	cmpw r0, r30
	bne L_af_2
	li r0, 0x0
	li r3, 0xa
	stb r0, 0x72(r27)
	bl irand
	addi r0, r3, 0x3c
	li r3, 0x64
	stb r0, 0x73(r27)
	bl irand
	clrlwi. r0, r3, 31
	beq L_af_3
	li r0, 0x0
	b L_af_4
L_af_3:
	lbz r0, 0x73(r27)
	extrwi r0, r0, 8, 23
L_af_4:
	stb r0, 0x74(r27)
	lfs f0, float_0_8041cd04(r2)
	stfs f0, 0x78(r27)
L_af_2:
	addi r28, r28, 0x1
	addi r31, r31, 0x7c
	cmpwi r28, 0x20
	blt L_af_1
	lmw r27, 0xc(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}
#endif

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
#endif
#ifndef NONMATCHING
BattleStageObject* BattleGetObjectPtr(s32 id) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	int i;
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
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
#endif
#ifndef NONMATCHING
BattleStageObject* BattleSearchObjectPtr(const char* name) {
	BattleWork* wp = _battleWorkPointer;
	int i;
	BattleStageObject* obj;
#endif

#ifdef NONMATCHING
        r = irand(sum);
        for (e->type = 0; e->type < 8; e->type++)
        {
          if ((r -= fd->rates[e->type]) < 0)
          {
            break;
          }
        }
#endif
#ifndef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void BattleStageObjectInit(void) {
	asm volatile {
		lwz r24, _battleWorkPointer(r13)
		lis r6, lbl_80371490@ha
		lis r5, vec3_802f3ac8@ha
		opword 0x3BE00000
		opword 0x80982738
		opword 0x3C780001
		addi r26, r5, vec3_802f3ac8@l
		addi r25, r6, lbl_80371490@l
		opword 0x8084000C
		opword 0x3E980002
		opword 0x3BC00000
		opword 0x3BA00000
		opword 0x82E40000
		opword 0x3B800000
		opword 0x3B600000
		opword 0x38800000
		opword 0x82D70008
		opword 0x38A00F80
		opword 0x82B7000C
		opword 0x38637140
		bl memset
		bl pouchGetPtr
		opword 0xA8030088
		opword 0x2C000004
		opword 0x40800020
		opword 0x2C000001
		opword 0x40800008
		opword 0x48000014
		la r3, str_8041CD78(r2)
		opword 0x38800001
		opword 0x38A00000
		bl mapPlayAnimationLv
		bl pouchGetPtr
		opword 0xA8030088
		opword 0x2C000004
		opword 0x4080002C
		opword 0x2C000001
		opword 0x40800008
		opword 0x48000020
		bl pouchGetPtr
		opword 0xA8630088
		opword 0x381901C0
		opword 0x1C630310
		opword 0x7C001A14
		opword 0x901480F4
		opword 0x4800000C
		opword 0x38000000
		opword 0x901480F4
		bl pouchGetPtr
		opword 0xA8A30088
		opword 0x38990E00
		opword 0x3860FFFF
		opword 0x38000000
		opword 0x1CA5078C
		opword 0x7C842A14
		opword 0x909480F8
		opword 0x9874828A
		opword 0x9014829C
		opword 0x901482A0
		bl mapGetWork
		opword 0x806300A8
		opword 0x38800002
		opword 0x80630008
		opword 0x80630000
		bl mapGrpFlagOff
		la r3, str_8041CD68(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x4182001C
		la r3, str_8041CD68(r2)
		opword 0x38800001
		bl mapGrpFlagOn
		la r3, str_8041CD68(r2)
		opword 0x38800002
		bl mapGrpFlagOff
		la r3, str_8041CD6C(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x4182001C
		la r3, str_8041CD6C(r2)
		opword 0x38800001
		bl mapGrpFlagOn
		la r3, str_8041CD6C(r2)
		opword 0x38800002
		bl mapGrpFlagOff
		la r3, str_8041CD70(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x4182001C
		la r3, str_8041CD70(r2)
		opword 0x38800001
		bl mapGrpFlagOn
		la r3, str_8041CD70(r2)
		opword 0x38800002
		bl mapGrpFlagOff
		la r3, str_8041CD74(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x4182001C
		la r3, str_8041CD74(r2)
		opword 0x38800001
		bl mapGrpFlagOn
		la r3, str_8041CD74(r2)
		opword 0x38800002
		bl mapGrpFlagOff
		opword 0x387A00E4
		opword 0x38800001
		bl mapGrpFlagOn
		opword 0x28150000
		opword 0x3A800001
		opword 0x4182024C
		lfs f31, float_0_8041cd04(r2)
		opword 0x4800023C
		opword 0x38000020
		opword 0x38800000
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x3E630001
		opword 0x3A737140
		opword 0x7E789A14
		opword 0x80130000
		opword 0x2C000000
		opword 0x40810010
		opword 0x38840001
		opword 0x3863007C
		opword 0x4200FFE0
		opword 0x2C040020
		opword 0x40800208
		opword 0x92B30064
		opword 0x3800FFFF
		opword 0x92930000
		opword 0x9013006C
		opword 0x80730064
		opword 0xA0030006
		opword 0x2C000003
		opword 0x41820044
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820028
		opword 0x4080002C
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000034
		opword 0x2C000006
		opword 0x41820028
		opword 0x48000028
		opword 0x3BFF0001
		opword 0x48000020
		opword 0x3BDE0001
		opword 0x48000018
		opword 0x3BBD0001
		opword 0x48000010
		opword 0x3B9C0001
		opword 0x48000008
		opword 0x3B600001
		opword 0x2C000004
		opword 0x40800018
		opword 0x2C000002
		opword 0x40800040
		opword 0x2C000000
		opword 0x4080001C
		opword 0x4800004C
		opword 0x2C000008
		opword 0x40800044
		opword 0x2C000006
		opword 0x40800008
		opword 0x48000038
		opword 0x80750008
		opword 0x8015000C
		opword 0x90730004
		opword 0x90130008
		opword 0x80150010
		opword 0x9013000C
		opword 0x4800001C
		opword 0x80750008
		opword 0x8015000C
		opword 0x90730004
		opword 0x90130008
		opword 0x80150010
		opword 0x9013000C
		opword 0xD3F30024
		opword 0x38800001
		opword 0xD3F30020
		opword 0xD3F3001C
		opword 0x807A0000
		opword 0x801A0004
		opword 0x90730034
		opword 0x90130038
		opword 0x801A0008
		opword 0x9013003C
		opword 0x807A000C
		opword 0x801A0010
		opword 0x90730040
		opword 0x90130044
		opword 0x801A0014
		opword 0x90130048
		opword 0x807A0018
		opword 0x801A001C
		opword 0x9073004C
		opword 0x90130050
		opword 0x801A0020
		opword 0x90130054
		opword 0x807A0024
		opword 0x801A0028
		opword 0x90730058
		opword 0x9013005C
		opword 0x801A002C
		opword 0x90130060
		opword 0x80730064
		opword 0x80630000
		bl mapGrpFlagOff
		opword 0xA0150004
		opword 0x2C000001
		opword 0x4182005C
		opword 0x40800098
		opword 0x2C000000
		opword 0x4080000C
		opword 0x4800008C
		opword 0x48000088
		la r3, _entry_tree_data(r13)
		bl BtlUnit_Entry
		opword 0x80130000
		mr r18, r3
		opword 0x90030B2C
		opword 0x80030000
		opword 0x9013006C
		opword 0xC0330004
		opword 0xC0530008
		opword 0xC073000C
		bl BtlUnit_SetPos
		opword 0xC0330004
		opword 0x7E439378
		opword 0xC0530008
		opword 0xC073000C
		bl BtlUnit_SetHomePos
		opword 0x48000044
		la r3, _entry_switch_data(r13)
		bl BtlUnit_Entry
		opword 0x80130000
		opword 0x7C721B78
		opword 0x90030B2C
		opword 0x80030000
		opword 0x9013006C
		opword 0xC0330004
		opword 0xC0530008
		opword 0xC073000C
		bl BtlUnit_SetPos
		opword 0xC0330004
		opword 0x7E439378
		opword 0xC0530008
		opword 0xC073000C
		bl BtlUnit_SetHomePos
		opword 0x3A940001
		opword 0x3AD6FFFF
		opword 0x3AB50018
		opword 0x2C160000
		opword 0x4082FDC4
		bl pouchGetPtr
		opword 0xA8030088
		opword 0x2C000000
		opword 0x40810104
		lfs f31, float_0_8041cd04(r2)
		opword 0x3B392C30
		opword 0x3AA00000
		opword 0x38000020
		opword 0x38800000
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x3E630001
		opword 0x3A737140
		opword 0x7E789A14
		opword 0x80130000
		opword 0x2C000000
		opword 0x40810010
		opword 0x38840001
		opword 0x3863007C
		opword 0x4200FFE0
		opword 0x2C040020
		opword 0x408000BC
		opword 0x93330064
		opword 0x3800FFFF
		opword 0x38800001
		opword 0x92930000
		opword 0x9013006C
		opword 0x80790008
		opword 0x8019000C
		opword 0x90730004
		opword 0x90130008
		opword 0x80190010
		opword 0x9013000C
		opword 0xD3F30024
		opword 0xD3F30020
		opword 0xD3F3001C
		opword 0x807A0030
		opword 0x801A0034
		opword 0x90730034
		opword 0x90130038
		opword 0x801A0038
		opword 0x9013003C
		opword 0x807A003C
		opword 0x801A0040
		opword 0x90730040
		opword 0x90130044
		opword 0x801A0044
		opword 0x90130048
		opword 0x807A0048
		opword 0x801A004C
		opword 0x9073004C
		opword 0x90130050
		opword 0x801A0050
		opword 0x90130054
		opword 0x807A0054
		opword 0x801A0058
		opword 0x90730058
		opword 0x9013005C
		opword 0x801A005C
		opword 0x90130060
		opword 0x80730064
		opword 0x80630000
		bl mapGrpFlagOff
		opword 0x3AB50001
		opword 0x3B390018
		opword 0x2C150003
		opword 0x3A940001
		opword 0x4180FF10
		opword 0x38000020
		la r4, _object_wall_data(r13)
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x3E630001
		opword 0x3A737140
		opword 0x7E789A14
		opword 0x80130000
		opword 0x2C000000
		opword 0x4081000C
		opword 0x3863007C
		opword 0x4200FFE4
		opword 0x90930064
		opword 0x3800FFFF
		opword 0x92930000
		opword 0x9013006C
		opword 0x80640008
		opword 0x8004000C
		opword 0x90730004
		opword 0x90130008
		opword 0x80040010
		opword 0x9013000C
		bl BattleStageGetPtr
		opword 0xC0230B28
		opword 0x38800001
		lfs f0, float_0_8041cd04(r2)
		opword 0xD0330008
		opword 0xD0130024
		opword 0xD0130020
		opword 0xD013001C
		opword 0x807A0060
		opword 0x801A0064
		opword 0x90730034
		opword 0x90130038
		opword 0x801A0068
		opword 0x9013003C
		opword 0x807A006C
		opword 0x801A0070
		opword 0x90730040
		opword 0x90130044
		opword 0x801A0074
		opword 0x90130048
		opword 0x807A0078
		opword 0x801A007C
		opword 0x9073004C
		opword 0x90130050
		opword 0x801A0080
		opword 0x90130054
		opword 0x807A0084
		opword 0x801A0088
		opword 0x90730058
		opword 0x9013005C
		opword 0x801A008C
		opword 0x90130060
		opword 0x80730064
		opword 0x80630000
		bl mapGrpFlagOn
		opword 0x80130068
		opword 0x3AA00000
		lfs f31, float_0_8041cd04(r2)
		opword 0x3A940001
		opword 0x60000001
		opword 0x90130068
		la r5, _object_spot_light_data(r13)
		opword 0x7CA5AA14
		opword 0x80050000
		opword 0x28000000
		opword 0x418200EC
		opword 0x38000020
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x3E630001
		opword 0x3A737140
		opword 0x7E789A14
		opword 0x80130000
		opword 0x2C000000
		opword 0x4081000C
		opword 0x3863007C
		opword 0x4200FFE4
		opword 0x90B30064
		opword 0x3800FFFF
		opword 0x38800001
		opword 0x92930000
		opword 0x9013006C
		opword 0x80650008
		opword 0x8005000C
		opword 0x90730004
		opword 0x90130008
		opword 0x80050010
		opword 0x9013000C
		opword 0xD3F30024
		opword 0xD3F30020
		opword 0xD3F3001C
		opword 0x807A0090
		opword 0x801A0094
		opword 0x90730034
		opword 0x90130038
		opword 0x801A0098
		opword 0x9013003C
		opword 0x807A009C
		opword 0x801A00A0
		opword 0x90730040
		opword 0x90130044
		opword 0x801A00A4
		opword 0x90130048
		opword 0x807A00A8
		opword 0x801A00AC
		opword 0x9073004C
		opword 0x90130050
		opword 0x801A00B0
		opword 0x90130054
		opword 0x807A00B4
		opword 0x801A00B8
		opword 0x90730058
		opword 0x9013005C
		opword 0x801A00BC
		opword 0x90130060
		opword 0x80730064
		opword 0x80630000
		bl mapGrpFlagOn
		opword 0x80130068
		opword 0x3A940001
		opword 0x3AB50018
		opword 0x60000001
		opword 0x90130068
		opword 0x4BFFFF08
		opword 0x80770190
		opword 0x28030000
		opword 0x41820010
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x2C1F0000
		opword 0x41820028
		opword 0x807701A0
		opword 0x28030000
		opword 0x4182001C
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x3C780002
		opword 0x900380E4
		opword 0x2C1E0000
		opword 0x41820028
		opword 0x807701A4
		opword 0x28030000
		opword 0x4182001C
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x3C780002
		opword 0x900380E8
		opword 0x2C1D0000
		opword 0x41820028
		opword 0x807701A8
		opword 0x28030000
		opword 0x4182001C
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x3C780002
		opword 0x900380EC
		opword 0x2C1C0000
		opword 0x41820028
		opword 0x807701AC
		opword 0x28030000
		opword 0x4182001C
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x3C780002
		opword 0x900380F0
		opword 0x2C1F0000
		opword 0x40820014
		opword 0x3C780002
		opword 0x880380DC
		opword 0x60000002
		opword 0x980380DC
		opword 0x2C1E0000
		opword 0x40820014
		opword 0x3C780002
		opword 0x880380DC
		opword 0x60000004
		opword 0x980380DC
		opword 0x2C1D0000
		opword 0x40820014
		opword 0x3C780002
		opword 0x880380DC
		opword 0x60000008
		opword 0x980380DC
		opword 0x881701B1
		opword 0x7C000775
		opword 0x41820014
		opword 0x3C780002
		opword 0x880380DC
		opword 0x60000002
		opword 0x980380DC
		opword 0x881701B2
		opword 0x7C000775
		opword 0x41820014
		opword 0x3C780002
		opword 0x880380DC
		opword 0x60000004
		opword 0x980380DC
		opword 0x881701B3
		opword 0x7C000775
		opword 0x41820014
		opword 0x3C780002
		opword 0x880380DC
		opword 0x60000008
		opword 0x980380DC
		opword 0x2C1B0000
		opword 0x4082002C
		opword 0x3CB80002
		opword 0x387A01B4
		opword 0x880580DC
		opword 0x38800001
		opword 0x60000020
		opword 0x980580DC
		bl mapGrpFlagOn
		opword 0x387A028C
		opword 0x38800001
		bl mapGrpFlagOn
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
      }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void BattleStageObjectMain(void) {
	asm volatile {
		opword 0x3B800000
		li r27, 0x0
		lwz r31, _battleWorkPointer(r13)
		opword 0x3FDF0002
		opword 0x3FBB0001
		opword 0x3BBD7140
		opword 0x7FBFEA14
		opword 0x801D0000
		opword 0x2C000000
		opword 0x408103DC
		opword 0xC03D0004
		opword 0x38800000
		opword 0xC01D0034
		opword 0xFC010000
		opword 0x40820024
		opword 0xC03D0008
		opword 0xC01D0038
		opword 0xFC010000
		opword 0x40820014
		opword 0xC03D000C
		opword 0xC01D003C
		opword 0xFC010000
		opword 0x41820020
		opword 0x807D0004
		opword 0x38800001
		opword 0x801D0008
		opword 0x907D0034
		opword 0x901D0038
		opword 0x801D000C
		opword 0x901D003C
		opword 0xC03D0010
		opword 0xC01D0040
		opword 0xFC010000
		opword 0x40820024
		opword 0xC03D0014
		opword 0xC01D0044
		opword 0xFC010000
		opword 0x40820014
		opword 0xC03D0018
		opword 0xC01D0048
		opword 0xFC010000
		opword 0x41820020
		opword 0x807D0010
		opword 0x38800001
		opword 0x801D0014
		opword 0x907D0040
		opword 0x901D0044
		opword 0x801D0018
		opword 0x901D0048
		opword 0xC03D0028
		opword 0xC01D0058
		opword 0xFC010000
		opword 0x40820024
		opword 0xC03D002C
		opword 0xC01D005C
		opword 0xFC010000
		opword 0x40820014
		opword 0xC03D0030
		opword 0xC01D0060
		opword 0xFC010000
		opword 0x41820020
		opword 0x807D0028
		opword 0x38800001
		opword 0x801D002C
		opword 0x907D0058
		opword 0x901D005C
		opword 0x801D0030
		opword 0x901D0060
		opword 0xC03D001C
		opword 0xC01D004C
		opword 0xFC010000
		opword 0x40820024
		opword 0xC03D0020
		opword 0xC01D0050
		opword 0xFC010000
		opword 0x40820014
		opword 0xC03D0024
		opword 0xC01D0054
		opword 0xFC010000
		opword 0x41820020
		opword 0x807D001C
		opword 0x38800001
		opword 0x801D0020
		opword 0x907D004C
		opword 0x901D0050
		opword 0x801D0024
		opword 0x901D0054
		opword 0x807D0068
		opword 0x546007BD
		opword 0x41820010
		opword 0x546007FA
		opword 0x38800001
		opword 0x901D0068
		opword 0x807D0064
		opword 0xA0030006
		opword 0x2C000002
		opword 0x41820008
		opword 0x48000050
		opword 0xC03E80C4
		opword 0xC01E80D0
		opword 0xFC010000
		opword 0x40820024
		opword 0xC03E80C8
		opword 0xC01E80D4
		opword 0xFC010000
		opword 0x40820014
		opword 0xC03E80CC
		opword 0xC01E80D8
		opword 0xFC010000
		opword 0x41820020
		opword 0x807E80C4
		opword 0x38800001
		opword 0x801E80C8
		opword 0x907E80D0
		opword 0x901E80D4
		opword 0x801E80CC
		opword 0x901E80D8
		opword 0x807D0064
		opword 0xA0030006
		opword 0x2C000003
		opword 0x41820128
		opword 0x40800018
		opword 0x2C000002
		opword 0x40800080
		opword 0x2C000000
		opword 0x40800010
		opword 0x480001A8
		opword 0x2C000008
		opword 0x408001A0
		opword 0x2C040000
		opword 0x41820198
		opword 0xC07D0004
		opword 0xC05D0010
		opword 0xC03D0008
		opword 0xC01D0014
		opword 0xEC63102A
		opword 0xC0BD0028
		opword 0xC05D000C
		opword 0xEC81002A
		opword 0xC01D0018
		opword 0xEC25182A
		opword 0xC0BD002C
		opword 0xEC02002A
		opword 0xC07D0030
		opword 0xEC45202A
		opword 0x80630000
		opword 0xEC63002A
		bl mapObjTranslate
		opword 0x807D0064
		opword 0xC03D001C
		opword 0x80630000
		opword 0xC05D0020
		opword 0xC07D0024
		bl mapObjRotate
		opword 0x48000138
		opword 0x2C040000
		opword 0x41820130
		opword 0xC07D0004
		opword 0xC05D0010
		opword 0xC03D0008
		opword 0xC01D0014
		opword 0xEC63102A
		opword 0xC0BD0028
		opword 0xC05D000C
		opword 0xEC81002A
		opword 0xC01D0018
		opword 0xEC25182A
		opword 0xC0BD002C
		opword 0xEC02002A
		opword 0xC07D0030
		opword 0xEC45202A
		opword 0x80630000
		opword 0xEC63002A
		bl mapObjTranslate
		lfs f1, float_0_8041cd04(r2)
		opword 0xC01D0014
		opword 0x807D0064
		opword 0xFC600890
		opword 0xFC400050
		opword 0x80630000
		bl mapObjTranslate
		opword 0x807D0064
		opword 0xC03E80C4
		opword 0x80630000
		opword 0xC05E80C8
		opword 0xC07E80CC
		bl mapObjRotate
		lfs f1, float_0_8041cd04(r2)
		opword 0x807D0064
		opword 0xFC600890
		opword 0xC05D0014
		opword 0x80630000
		bl mapObjTranslate
		opword 0x4800009C
		opword 0x2C040000
		opword 0x41820094
		opword 0xC07D0004
		opword 0xC05D0010
		opword 0xC03D0008
		opword 0xC01D0014
		opword 0xEC63102A
		opword 0xC0BD0028
		opword 0xC05D000C
		opword 0xEC81002A
		opword 0xC01D0018
		opword 0xEC25182A
		opword 0xC0BD002C
		opword 0xEC02002A
		opword 0xC07D0030
		opword 0xEC45202A
		opword 0x80630000
		opword 0xEC63002A
		bl mapObjTranslate
		lfs f1, float_0_8041cd04(r2)
		opword 0xC01D0008
		opword 0x807D0064
		opword 0xFC600890
		opword 0xFC400050
		opword 0x80630000
		bl mapObjTranslate
		opword 0x807D0064
		opword 0xC03D001C
		opword 0x80630000
		opword 0xC05D0020
		opword 0xC07D0024
		bl mapObjRotate
		lfs f1, float_0_8041cd04(r2)
		opword 0x807D0064
		opword 0xFC600890
		opword 0xC05D0008
		opword 0x80630000
		bl mapObjTranslate
		opword 0x801D0068
		opword 0x540007FF
		opword 0x41820030
		opword 0x807D0064
		opword 0x80630000
		bl mapGetMapObj
		opword 0x80030000
		opword 0x540007FF
		opword 0x40820040
		opword 0x807D0064
		opword 0x38800001
		opword 0x80630000
		bl mapGrpFlagOn
		opword 0x4800002C
		opword 0x807D0064
		opword 0x80630000
		bl mapGetMapObj
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820014
		opword 0x807D0064
		opword 0x38800001
		opword 0x80630000
		bl mapGrpFlagOff
		opword 0x3B9C0001
		opword 0x3B7B007C
		opword 0x2C1C0020
		opword 0x4180FC04
		bl BattleObjectConfig
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
void BattleObjectConfig(void) {
	//stubbed in retail
}
#endif

#ifdef NONMATCHING
        }
      }
    }
#endif
#ifndef NONMATCHING
void BattleStage_DestroyA1(void) {
	BattleWork* wp = _battleWorkPointer;
	void* evt = wp->fbatInfo->setup->stageData->destroyBgA1Evt;
	EventEntry* entry;
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
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
        case 1:
          hit.x = ((e->unitId % 20) * 25) - 230;
          hit.y = BattleStageGetPtr()->audienceSizeY;
          hit.z = (0.1f * (e->unitId % 20)) + (((e->unitId / 20) * 30) + 115);
          btl_camera_set_mode(0, 6);
          btl_camera_set_moveSpeedLv(0, 2);
          width = 0.0f;
          break;
#endif
#ifndef NONMATCHING
void BattleStage_DestroyA2(void) {
	BattleWork* wp = _battleWorkPointer;
	void* evt = wp->fbatInfo->setup->stageData->destroyBgA2Evt;
#endif

#ifdef NONMATCHING
        default:
          hit = (Vec){0.0f, 0.0f, 0.0f};
          width = 0.0f;
          break;
#endif
#ifndef NONMATCHING
	evtDeleteID(STAGE_WORK(wp)->bgEvtId[1]);
	STAGE_WORK(wp)->bgEvtId[1] = 0;
	if (!evt) {
		evt = _object_turn_event_A2;
	}
	evtEntry(evt, 10, 0);
}
#endif

#ifdef NONMATCHING
      }
#endif
#ifndef NONMATCHING
void BattleStage_DestroyB(void) {
	BattleWork* wp = _battleWorkPointer;
	void* evt = wp->fbatInfo->setup->stageData->destroyBgBEvt;
	EventEntry* entry;
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
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

#ifdef NONMATCHING
        case 3:
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
s32 _set_mobj_rotate_x(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[32];
	asm {
		lis r5, vec3_802f3ac8@ha
	}
	asm volatile {
		opword 0x7C982378
		opword 0x7C7D1B78
		addi r30, r5, vec3_802f3ac8@l
		opword 0x3B400000
		opword 0x80C30018
		lwz r28, _battleWorkPointer(r13)
		opword 0x80860000
		opword 0x3F7C0002
		bl evtGetValue
		opword 0x2C180000
		opword 0x7C7F1B78
		opword 0x41820080
		opword 0x2C1F0002
		opword 0x41820064
		opword 0x40800074
		opword 0x2C1F0000
		opword 0x40800008
		opword 0x48000068
		opword 0x38600000
		opword 0x38000020
		opword 0x7C641B78
		opword 0x7C0903A6
		opword 0x3CC30001
		opword 0x38C67140
		opword 0x7CDC3214
		opword 0x80060000
		opword 0x2C000000
		opword 0x40810020
		opword 0x80A60064
		opword 0xA0050006
		opword 0x7C00F800
		opword 0x40820010
		opword 0x88050014
		opword 0x98060070
		opword 0x98860071
		opword 0x3863007C
		opword 0x4200FFC8
		opword 0x48000018
		opword 0x38600000
		opword 0x3800003C
		opword 0x907D007C
		opword 0x901D0080
		opword 0x907D0084
		opword 0x2C1F0002
		opword 0x418200F8
		opword 0x408001A4
		opword 0x2C1F0000
		opword 0x40800008
		opword 0x48000198
		opword 0x3BBE0244
		opword 0x3BDE025C
		opword 0x3B600000
		opword 0x3B200000
		addis r24, r25, 0x1
		opword 0x3B187140
		opword 0x7F1CC214
		opword 0x80180000
		opword 0x2C000000
		opword 0x408100AC
		opword 0x80780064
		opword 0xA0030006
		opword 0x7C00F800
		opword 0x4082009C
		opword 0x88780070
		opword 0x28030000
		opword 0x4182001C
		opword 0x3803FFFF
		opword 0x7F03C378
		opword 0x98180070
		opword 0x3B400001
		bl _mobj_shake_main
		opword 0x48000078
		opword 0x88180071
		opword 0x28000000
		opword 0x40820028
		opword 0x2C1F0000
		opword 0x40820014
		opword 0x7FA3EB78
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x48000010
		opword 0x7FC3F378
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x88980071
		opword 0x38600002
		lfs f2, float_90_8041cd08(r2)
		opword 0x38040001
		opword 0x98180071
		opword 0x80B80064
		opword 0xC0380078
		opword 0x88980071
		opword 0x88A50015
		bl intpl_sub
		opword 0xD038001C
		opword 0x80780064
		opword 0x88980071
		opword 0x88030015
		opword 0x7C040040
		opword 0x40800008
		opword 0x3B400001
		opword 0x3B7B0001
		opword 0x3B39007C
		opword 0x2C1B0020
		opword 0x4180FF34
		opword 0x480000B4
		opword 0x807D007C
		opword 0x2C030000
		opword 0x41820014
		opword 0x3803FFFF
		opword 0x3B400001
		opword 0x901D007C
		opword 0x48000098
		opword 0x801D0084
		opword 0x2C000000
		opword 0x40820028
		opword 0x80DE00FC
		opword 0x387E0274
		opword 0x80BE0100
		la r4, _af_pad+0
		opword 0x801E0104
		opword 0x90C10008
		opword 0x90A1000C
		opword 0x90010010
		bl psndSFXOn_3D
		opword 0x809D0084
		opword 0x38600002
		lfs f1, float_0_8041cd04(r2)
		opword 0x38040001
		lfs f2, float_90_8041cd08(r2)
		opword 0x901D0084
		opword 0x809D0084
		opword 0x80BD0080
		bl intpl_sub
		opword 0xFC00081E
		opword 0x3C004330
		opword 0x90010020
		opword 0xC83E0168
		opword 0xD8010018
		opword 0x8001001C
		opword 0x6C008000
		opword 0x90010024
		opword 0xC8010020
		opword 0xEC000828
		opword 0xD01B80C4
		opword 0x807D0084
		opword 0x801D0080
		opword 0x7C030000
		opword 0x40800008
		opword 0x3B400001
		opword 0x207A0000
		opword 0x38000002
		opword 0x7C631910
		opword 0x7C031878
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
        case 4:
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 _mobj_set_alpha(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xBFC10028
		opword 0x7C7E1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x2C1F0002
		opword 0x547E063E
		opword 0x4182008C
		opword 0x40800014
		opword 0x2C1F0000
		opword 0x41820018
		opword 0x40800048
		opword 0x480000DC
		opword 0x2C1F0004
		opword 0x408000D4
		opword 0x480000A0
		la r3, str_8041CD68(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x418200C0
		lwz r0, dat_8041cce8(r2)
		opword 0x38810024
		la r3, str_8041CD68(r2)
		opword 0x90010020
		opword 0x9BC10023
		opword 0x80010020
		opword 0x90010024
		bl mapGrpSetColor
		opword 0x4800009C
		la r3, str_8041CD6C(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x4182008C
		lwz r0, dat_8041ccec(r2)
		opword 0x3881001C
		la r3, str_8041CD6C(r2)
		opword 0x90010018
		opword 0x9BC1001B
		opword 0x80010018
		opword 0x9001001C
		bl mapGrpSetColor
		opword 0x48000068
		la r3, str_8041CD70(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x41820058
		lwz r0, dat_8041ccf0(r2)
		opword 0x38810014
		la r3, str_8041CD70(r2)
		opword 0x90010010
		opword 0x9BC10013
		opword 0x80010010
		opword 0x90010014
		bl mapGrpSetColor
		opword 0x48000034
		la r3, str_8041CD74(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x41820024
		lwz r0, dat_8041ccf4(r2)
		opword 0x3881000C
		la r3, str_8041CD74(r2)
		opword 0x90010008
		opword 0x9BC1000B
		opword 0x80010008
		opword 0x9001000C
		bl mapGrpSetColor
		opword 0xBBC10028
		opword 0x38600002
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
        case 6:
          hit.y = pos.y;
          break;
#endif
#ifndef NONMATCHING
s32 _mobj_destroy(EventEntry* event, BOOL isFirstCall) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	BattleUnit* unit;
	BattleUnitPart* part;
	s32 layer;
	int i;
#endif

#ifdef NONMATCHING
      }
#endif
#ifndef NONMATCHING
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
      e->sfxId = -1;
      e->field_0x12 = 0;
      sfxTub = "SFX_BTL_STAGE_DAMAGE_TUB1";
      switch (e->type)
      {
        case 0:
          e->effect = effFallEntry(4, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;
#endif
#ifndef NONMATCHING
s32 _get_bgset_attack_data(EventEntry* event, BOOL isFirstCall) {
	BattleWork* wp = _battleWorkPointer;
	s32* args = event->args;
	s32 type = evtGetValue(event, args[0]);
	s32 out = args[1];
	BattleWeapon* weapon;
#endif

#ifdef NONMATCHING
        case 1:
          e->effect = effFallEntry(5, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 1, 90);
          break;
#endif
#ifndef NONMATCHING
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
        case 2:
          e->effect = effFallEntry(0, pos.x, pos.y, pos.z, width, hit.y - pos.y, dir, 100, 90);
          break;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 _bgset_kemuri_effect(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x80A30018
		lis r4, vec3_802f3ac8@ha
		lwz r26, _battleWorkPointer(r13)
		addi r31, r4, vec3_802f3ac8@l
		opword 0x80850000
		bl evtGetValue
		opword 0x7C7E1B78
		opword 0x3BBF01FC
		opword 0x3B9F0214
		opword 0x3B7F022C
		opword 0x3B200000
		opword 0x3BE00000
		addis r24, r31, 0x1
		opword 0x3B187140
		opword 0x7F1AC214
		opword 0x80180000
		opword 0x2C000000
		opword 0x408100E8
		opword 0x80780064
		opword 0xA0030006
		opword 0x7C00F000
		opword 0x408200D8
		opword 0x2C1E0001
		opword 0xC3F80004
		opword 0xC3D80008
		lfs f29, 0xc(r24)
		opword 0x41820050
		opword 0x40800010
		opword 0x2C1E0000
		opword 0x40800014
		opword 0x480000B4
		opword 0x2C1E0003
		opword 0x408000AC
		opword 0x48000064
		lfs f0, float_30_8041cd5c(r2)
		opword 0xFC20F890
		opword 0xFC40F090
		lfs f4, float_0_8041cd04(r2)
		opword 0xEFBD002A
		opword 0x38600003
		opword 0xFC60E890
		bl effKemuri1N64Entry
		opword 0x7FA3EB78
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x48000078
		lfs f0, float_15_8041cd18(r2)
		opword 0xFC20F890
		opword 0xFC40F090
		lfs f4, float_0_8041cd04(r2)
		opword 0xEFBD002A
		opword 0x38600000
		opword 0xFC60E890
		bl effKemuri1N64Entry
		opword 0x7F83E378
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x48000048
		lfs f0, float_30_8041cd5c(r2)
		opword 0xFC20F890
		opword 0xFC40F090
		lfs f4, float_0_8041cd04(r2)
		opword 0xEFBD002A
		opword 0x38600003
		opword 0xFC60E890
		bl effKemuri1N64Entry
		opword 0xFC20F890
		lfs f4, float_0_8041cd04(r2)
		opword 0xFC40F090
		opword 0x38600004
		opword 0xFC60E890
		bl effKemuri1N64Entry
		opword 0x7F63DB78
		opword 0x38980004
		bl psndSFXOn_3D
		opword 0x3B390001
		opword 0x3BFF007C
		opword 0x2C190020
		opword 0x4180FEF8
		opword 0x38600002
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 _bgset_audience_bgset_access(EventEntry* event, BOOL isFirstCall) {
	BattleAudience_Case_HaikeiSet();
	return EVT_RETURN_DONE;
#endif
}


#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
#endif

#ifndef NONMATCHING

#endif