#include "battle/battle_status_effect.h"
#include "battle/battle_unit.h"
#include "battle/battle.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "battle/battle_pad.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include <stdio.h>
#include <string.h>
#include "driver/icondrv.h"

extern BattleWork* _battleWorkPointer;

typedef struct StChgMsg {
	s8 type; // 0x0
	u8 flags; // 0x1
	s8 field_0x2; // 0x2
	u8 pad_3; // 0x3
	s32 unitId; // 0x4
	s32 field_0x8; // 0x8
} StChgMsg;

#define ST_CHG_MSG(i) (((StChgMsg*)((u8*)_battleWorkPointer + 0x18D88)) + (i))
#define ST_CHG_TEXT ((const char*)((u8*)_battleWorkPointer + 0x18ED8))

BOOL BattleStatusChangeAnnouceMain_Unit(BattleUnit* unit);
void BattleStatusChangeMsgSetAnnouce(s32* data, s32 index, s32 arg2);
void BattleStatusChangeInfoWorkInit(BattleUnit* unit);
void _st_chg_msg_disp(void);

typedef struct StChgInfo {
	s8 type;
	s8 field_0x1;
	u8 field_0x2;
	u8 field_0x3;
	s32 field_0x4;
	s32 field_0x8;
} StChgInfo;

typedef struct StChgMsgData {
	s8 type;
	const char* name;
	const char* msg1;
	const char* msg0;
} StChgMsgData;

extern StChgMsgData _st_chg_msg_data[];
extern s8 _st_pri_data[];


//.sdata
//Status Type Priority Data
s8 _st_pri_data[] = {
	STATUS_CHARGE, //charge is elevated
	STATUS_POISON, //poison is elevated
	STATUS_SLEEP,
	STATUS_STOP,
	STATUS_DIZZY,
	STATUS_CONFUSE,
	STATUS_ELECTRIC,
	STATUS_DODGY,
	STATUS_BURN,
	STATUS_FREEZE,
	STATUS_HUGE,
	STATUS_TINY,
	STATUS_ATTACK_UP,
	STATUS_ATTACK_DOWN,
	STATUS_DEFENSE_UP,
	STATUS_DEFENSE_DOWN,
	STATUS_ALLERGIC,
	STATUS_INVISIBLE,
	STATUS_FAST,
	STATUS_SLOW,
	STATUS_PAYBACK,
	STATUS_HOLD_FAST,
	STATUS_HP_REGEN,
	STATUS_FP_REGEN,
	-1
};

//local prototypes
void BSE_Sleep(BattleUnit* unit);
void BSE_SleepDelete(BattleUnit* unit);
void BSE_Biribiri(BattleUnit* unit);
void BSE_BiribiriDelete(BattleUnit* unit);
void BSE_Fire(BattleUnit* unit);
void BSE_FireDelete(BattleUnit* unit);
void BSE_Freeze(BattleUnit* unit);
void BSE_FreezeDelete(BattleUnit* unit);
void BSE_Kagegakure(BattleUnit* unit);
void BSE_KagegakureDelete(BattleUnit* unit);
s32 _get_pri(s8 type);

void BattleStatusEffectInit(BattleUnit* unit) {
	; //stubbed in retail
}

void BattleStatusEffectMain(BattleUnit* unit) {
	BSE_Sleep(unit);
	BSE_Biribiri(unit);
	BSE_Fire(unit);
	BSE_Freeze(unit);
	BSE_Kagegakure(unit);
}

void BattleStatusEffectDelete(BattleUnit* unit) {
	BSE_SleepDelete(unit);
	BSE_BiribiriDelete(unit);
	BSE_FireDelete(unit);
	BSE_FreezeDelete(unit);
	BSE_KagegakureDelete(unit);
}

#include "driver/effdrv.h"
EffectEntry* effSparkEntry(s32, s32, f32, f32, f32, f32);
EffectEntry* effSleepEntry(s32, s32, f32, f32, f32, f32, f32);
#define EFF_SLEEP(u) (*(EffectEntry**)((u8*)(u) + 0x320))
#define EFF_SPARK(u) (*(EffectEntry**)((u8*)(u) + 0x32C))

#pragma optimize_for_size on
void BSE_Sleep(BattleUnit* unit) {
	f32 x, y, z;
	f32* wk;
	f32 dx, dy;
	BOOL on = FALSE;

	if (BtlUnit_CheckStatus(unit, 1)) {
		on = TRUE;
	}
	if (on) {
		if (EFF_SLEEP(unit) == NULL) {
			EFF_SLEEP(unit) = effSleepEntry(0, 0, -1000.0f, -1000.0f, -1000.0f, 1.0f, 60.0f);
		}
		wk = (f32*)EFF_SLEEP(unit)->userdata;
		BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
		dx = 0.5f * (unit->mSizeMultiplier * BtlUnit_GetWidth(unit));
		dy = 0.95f * (unit->mSizeMultiplier * BtlUnit_GetHeight(unit));
		if (*(u32*)&unit->mAttributeFlags & 2) {
			dy = 0.0f;
		}
		x += dx;
		y += dy;
		wk[1] = x;
		wk[2] = y;
		wk[3] = z;
	}
	else {
		BSE_SleepDelete(unit);
	}
}

void BSE_SleepDelete(BattleUnit* unit) {
	if (EFF_SLEEP(unit) != NULL) {
		effDelete(EFF_SLEEP(unit));
		EFF_SLEEP(unit) = NULL;
	}
}

void BSE_Biribiri(BattleUnit* unit) {
	f32 x, y, z;
	f32* wk;
	f32 dy;
	BOOL on = FALSE;

	if (BtlUnit_CheckStatus(unit, 6)) {
		on = TRUE;
	}
	if (on) {
		if (EFF_SPARK(unit) == NULL) {
			EFF_SPARK(unit) = effSparkEntry(0, 10, -1000.0f, -1000.0f, -1000.0f, BtlUnit_GetWidth(unit) / 2);
		}
		wk = (f32*)EFF_SPARK(unit)->userdata;
		BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
		dy = unit->mSizeMultiplier * (BtlUnit_GetHeight(unit) / 2);
		if (*(u32*)&unit->mAttributeFlags & 2) {
			dy = 0.0f;
		}
		y += dy;
		wk[1] = x;
		wk[2] = y;
		wk[3] = 10.0f + z;
	}
	else {
		BSE_BiribiriDelete(unit);
	}
}

void BSE_BiribiriDelete(BattleUnit* unit) {
	if (EFF_SPARK(unit) != NULL) {
		effDelete(EFF_SPARK(unit));
		EFF_SPARK(unit) = NULL;
	}
}
#pragma optimize_for_size reset

EffectEntry* effFireEntry(s32, s32, f32, f32, f32, f32);
EffectEntry* effIceEntry(s32, s32, f32, f32, f32, f32);
#define EFF_FIRE(u) (*(EffectEntry**)((u8*)(u) + 0x324))
#define EFF_ICE(u) (*(EffectEntry**)((u8*)(u) + 0x328))
#define KIND_F(u, o) (*(f32*)((u8*)(u)->mKindParams + (o)))

#pragma optimize_for_size on
void BSE_Fire(BattleUnit* unit) {
	f32 x, y, z;
	f32* wk;
	BOOL on = FALSE;

	if (BtlUnit_CheckStatus(unit, 8)) {
		on = TRUE;
	}
	if (on) {
		if (EFF_FIRE(unit) == NULL) {
			EFF_FIRE(unit) = effFireEntry(0, 0, -1000.0f, -1000.0f, -1000.0f, 1.0f);
		}
		wk = (f32*)EFF_FIRE(unit)->userdata;
		BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
		x += unit->mSizeMultiplier * (KIND_F(unit, 0x48) * (unit->faceDirection >= 0 ? 1.0f : -1.0f));
		y += KIND_F(unit, 0x4C) * unit->mSizeMultiplier;
		z += KIND_F(unit, 0x50) * unit->mSizeMultiplier;
		wk[1] = x;
		wk[2] = y;
		wk[3] = z + 5.0f;
	}
	else {
		BSE_FireDelete(unit);
	}
}

void BSE_FireDelete(BattleUnit* unit) {
	if (EFF_FIRE(unit) != NULL) {
		effDelete(EFF_FIRE(unit));
		EFF_FIRE(unit) = NULL;
	}
}

void BSE_Freeze(BattleUnit* unit) {
	f32 x, y, z;
	f32* wk;
	f32 a, b, sc;
	BOOL on = FALSE;

	if (BtlUnit_CheckStatus(unit, 9)) {
		on = TRUE;
	}
	if (on) {
		if (EFF_ICE(unit) == NULL) {
			EFF_ICE(unit) = effIceEntry(0, -1, -1000.0f, -1000.0f, -1000.0f, 1.0f);
		}
		wk = (f32*)EFF_ICE(unit)->userdata;
		{
			BattleUnitPart* parts = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
			a = unit->mWidth / 20.0f;
			b = unit->mHeight / 36.0f;
			sc = a <= b ? a : b;
			sc *= unit->mSizeMultiplier;
			wk[4] = sc;
			BtlUnit_GetPartsWorldPos(parts, &x, &y, &z);
		}
		wk[1] = x;
		wk[2] = 20.0f * sc + y;
		wk[3] = 10.0f + z;
	}
	else {
		BSE_FreezeDelete(unit);
	}
}

void BSE_FreezeDelete(BattleUnit* unit) {
	if (EFF_ICE(unit) != NULL) {
		effSoftDelete(EFF_ICE(unit));
		EFF_ICE(unit) = NULL;
	}
}

#pragma optimize_for_size reset

#define KAGE_ICON(u) (*(u8**)((u8*)(u) + 0x330))

void BSE_Kagegakure(BattleUnit* unit) {
	char name[0x10];
	f32 x, y, z;
	BOOL on = FALSE;

	if ((_battleWorkPointer->dispFlags & 1) && (unit->mAttributeFlags & 0x10)) {
		on = TRUE;
	}
	if (on) {
		if (KAGE_ICON(unit) == NULL) {
			sprintf(name, "_biK_%02x", *(s32*)unit);
			iconEntry(name, 0x99);
			KAGE_ICON(unit) = (u8*)iconNameToPtr(name);
		}
		BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
		iconSetPos((char*)KAGE_ICON(unit) + 0x18, x, y, z + 5.0f);
	}
	else {
		BSE_KagegakureDelete(unit);
	}
}

void BSE_KagegakureDelete(BattleUnit* unit) {
	if (KAGE_ICON(unit) != NULL) {
		iconDelete((char*)KAGE_ICON(unit) + 0x18);
		KAGE_ICON(unit) = NULL;
	}
}

void BSE_TurnFirstProcessEffectEntry(BattleUnit* unit, s16 active) {
	unit->mBurnDamageFlameState = 1;
	unit->mbBurnDamageFlameActive = active;
}

void BattleDamageDirect(s32 unitId, BattleUnit* target, BattleUnitPart* part, s32 damage, s32 fpDamage, u32 result, u32 pattern, s32 flag);
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);
f32 sinfd(f32 degrees);

BOOL BSE_TurnFirstProcessEffectMain(BattleUnit* unit) {
	BattleUnitPart* part;
	f32 x, y, z;
	f32* work;
	u16 st;
	u16 ac;

	part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
	st = *(u16*)&unit->mBurnDamageFlameState;
	if (st == 0) {
		return FALSE;
	}
	ac = *(u16*)&unit->mbBurnDamageFlameActive;
	if (ac == 0) {
		return FALSE;
	}
	if ((s32)ac != 1) {
		return FALSE;
	}
	switch (unit->mBurnDamageFlameState) {
	case 0:
		return FALSE;
	case 1:
		unit->mBurnDamageFlameState++;
		unit->mBurnDamageFlameScale = 1.0f;
		BtlUnit_GetPartsWorldPos(part, &x, &y, &z);
		z += 5.0f;
		unit->mBurnDamageFlameEff = effFireEntry(0, 0, x, y, z, unit->mBurnDamageFlameScale);
		unit->mBurnDamageFlameAnimTimer = 0;
		return TRUE;
	case 2:
		work = (f32*)unit->mBurnDamageFlameEff->userdata;
		unit->mBurnDamageFlameAnimTimer++;
		unit->mBurnDamageFlameScale = 1.6f * sinfd(unit->mBurnDamageFlameAnimTimer * 3) + 0.4f;
		work[9] = unit->mBurnDamageFlameScale;
		if (unit->mBurnDamageFlameAnimTimer >= 60) {
			unit->mBurnDamageFlameState++;
		}
		return TRUE;
	case 3:
		effDelete(unit->mBurnDamageFlameEff);
		unit->mBurnDamageFlameEff = NULL;
		unit->mBurnDamageFlameState = 0;
		if (!BtlUnit_CheckShadowGuard(unit)) {
			BattleDamageDirect(-5, unit, NULL, 1, 0, 0x118, 0, 1);
		}
		return FALSE;
	}
	return FALSE;
}

#pragma optimize_for_size on
void BattleStatusChangeInfoWorkInit(BattleUnit* unit) {
	s32 i;
	StChgInfo* e = (StChgInfo*)((u8*)unit + 0xAE4);

	for (i = 0; i < 6; i++) {
		StChgInfo* p = &e[i];
		p->type = -1;
		p->field_0x1 = 0;
		p->field_0x2 = 0;
		p->field_0x3 = 0;
		p->field_0x4 = 0;
	}
}
#pragma optimize_for_size reset

#pragma dont_inline on
//should be StatusEffectType, TODO fix for s8
s32 _get_pri(s8 type) {
	s8* val;
	s32 priority = 24; //TODO: #define?

	for (val = _st_pri_data;; priority--, val++) {
		if (*val == -1) {
			return -1; //reached end of list
		}
		if (*val == type) {
			return priority;
		}
	}
	return -1;
}

#pragma optimize_for_size on
void BattleStatusChangeInfoSetAnnouce(BattleUnit* unit, s8 type, s8 arg2, s32 arg3) {
	StChgInfo* e = (StChgInfo*)((u8*)unit + 0xAE4);
	StChgInfo tmp, swap;
	s8 pri = _get_pri(type);
	s32 i, j, n;
	u8 t, v;

	for (i = 0; i < 6; i++) {
		if (pri >= (s8)_get_pri(e[i].type)) break;
	}
	if (i >= 6) return;
	tmp.type = type;
	tmp.field_0x1 = arg2;
	tmp.field_0x8 = arg3;
	if (type == e[i].type) {
		e[i] = tmp;
	}
	else {
		for (; i < 6; i++) {
			swap = e[i];
			e[i] = tmp;
			tmp = swap;
		}
	}
	n = 0;
	t = 0;
	for (j = 0; j < 6; j++) {
		if (e[j].type == -1) break;
		e[j].field_0x2 = t;
		t += 10;
		e[j].field_0x4 = 0;
		n++;
	}
	v = t ? 0x50 : 0x3C;
	for (j = n; j >= 0; j--) {
		if (e[j].type != -1) {
			e[j].field_0x3 = v;
			v += 10;
		}
	}
}

#pragma optimize_for_size reset
#pragma dont_inline on
#pragma optimize_for_size on
BOOL BattleStatusChangeAnnouceMain(BattleWork* wp) {
	s32 i;
	BOOL ret;
	BattleUnit* unit;

	ret = FALSE;
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit && BattleStatusChangeAnnouceMain_Unit(unit)) {
			ret = TRUE;
		}
	}
	return ret;
}

BOOL BattleStatusChangeAnnouceMain_Unit(BattleUnit* unit) {
	return FALSE;
}
#pragma optimize_for_size reset
#pragma dont_inline reset

#pragma optimize_for_size on
void BattleStatusChangeMsgWorkInit(void) {
	StChgMsg* msg = ST_CHG_MSG(0);
	s32 i;

	memset(msg, 0, 0x258);
	for (i = 0; i < 28; i++) {
		msg[i].type = -1;
	}
}
#pragma optimize_for_size reset

void BattleStatusChangeMsgSetAnnouce(s32* data, s32 index, s32 arg2) {
	StChgMsg* msg = ST_CHG_MSG(index);
	s32 id;

	msg->unitId = data[0];
	msg->type = index;
	msg->field_0x2 = 0;
	msg->field_0x8 = arg2;
	id = data[2];
	if (id == 0xDE) {
		msg->flags |= 1;
	}
	else if (id >= 0xE0 && id < 0xE7 && ((s8*)data)[0xC] == 0) {
		msg->flags |= 2;
	}
	else {
		msg->flags |= 4;
	}
}

#pragma dont_inline on
#pragma optimize_for_size on
void BattleStatusChangeMsgAdjust(BattleWork* wp) {
	StChgMsg* base = (StChgMsg*)((u8*)wp + 0x18D88);
	StChgMsg* msg;
	BattleUnit* unit;
	StChgInfo* e;
	s8 i;
	s32 j, n, k, found;

	for (i = 0; i < 28; i++) {
		msg = &base[i];
		if (msg->type == -1) continue;
		msg->flags = 0;
		for (j = 0; j < 64; j++) {
			unit = BattleGetUnitPtr(wp, j);
			if (unit && !BtlUnit_CheckStatus(unit, 0x1B)) {
				e = (StChgInfo*)((u8*)unit + 0xAE4);
				found = 0;
				k = 0;
				for (n = 0; n < 6; n++) {
					if (i == e[n].type) {
						found = 1;
						break;
					}
					k++;
				}
				if (found) {
					BattleStatusChangeMsgSetAnnouce((s32*)unit, i, e[k].field_0x8);
				}
			}
		}
		if (!msg->flags) {
			msg->unitId = -1;
			msg->type = -1;
		}
		else if (*(u64*)((u8*)base + 0x250) & (1ULL << i)) {
			msg->unitId = -1;
			msg->type = -1;
		}
	}
}

BOOL BattleStatusChangeMsgMain(BattleWork* wp) {
	StChgMsg* base = (StChgMsg*)((u8*)wp + 0x18D88);
	StChgMsg* msg;
	BOOL ret = FALSE;
	s8* p;
	s32 i;

	for (p = _st_pri_data; *p != -1; p++) {
		msg = &base[*p];
		if (msg->type == -1) continue;
		ret = TRUE;
		BattleGetUnitPtr(wp, msg->unitId);
		if (*(u8*)&msg->field_0x2) {
			msg->field_0x2--;
			if (BattlePadCheckTrigger(0x300)) {
				msg->field_0x2 = 0;
			}
			if (!*(u8*)&msg->field_0x2) {
				msg->type = -1;
			}
		}
		else {
			sprintf((char*)base + 0x150, "");
			for (i = 0; i < 28; i++) {
				if (msg->type == _st_chg_msg_data[i].type || _st_chg_msg_data[i].type == -1) {
					if (msg->field_0x8) {
						sprintf((char*)base + 0x150, msgSearch(_st_chg_msg_data[i].msg1));
					}
					else {
						sprintf((char*)base + 0x150, msgSearch(_st_chg_msg_data[i].msg0));
					}
					break;
				}
			}
			msg->field_0x2 = 90;
		}
		dispEntry(8, 1, 900.0f, (DispCallback)_st_chg_msg_disp, 0);
		break;
	}
	if (ret) {
		for (i = 0; i < 64; i++) {
			BattleUnit* unit = BattleGetUnitPtr(wp, i);
			if (unit) BattleStatusChangeInfoWorkInit(unit);
		}
	}
	return ret;
}

static const GXColor _st_chg_msg_col = {0xFF, 0xFF, 0xFF, 0xFF};
#pragma dont_inline reset


void _st_chg_msg_disp(void) {
	u8* wp = (u8*)_battleWorkPointer + 0x20000;
	u16 lines;
	u16 width;
	f32 x;
	f32 cx = 0.0f;
	f32 ty = -120.0f;

	width = FontGetMessageWidthLine((const char*)(wp - 0x7128), &lines);
	lines++;
	x = cx - (width / 2);
	windowDispGX_Waku_col(0, _st_chg_msg_col, x - 20.0f, -117.0f + ((lines - 1) * 29), width + 40, lines * 29 + 1, 10.0f);
	FontDrawStart();
	FontDrawMessage(x, (s32)ty + (lines - 1) * 29, (const char*)(wp - 0x7128));
}
