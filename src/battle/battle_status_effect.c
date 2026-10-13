#include "battle/battle_status_effect.h"
#include "battle/battle_unit.h"
#include "battle/battle.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "battle/battle_pad.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include <stdio.h>

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

void BSE_Sleep(BattleUnit* unit) {

}

void BSE_SleepDelete(BattleUnit* unit) {

}

void BSE_Biribiri(BattleUnit* unit) {

}

void BSE_BiribiriDelete(BattleUnit* unit) {

}

void BSE_Fire(BattleUnit* unit) {

}

void BSE_FireDelete(BattleUnit* unit) {

}

void BSE_Freeze(BattleUnit* unit) {

}

void BSE_FreezeDelete(BattleUnit* unit) {

}

void BSE_Kagegakure(BattleUnit* unit) {

}

void BSE_KagegakureDelete(BattleUnit* unit) {

}

void BSE_TurnFirstProcessEffectEntry(BattleUnit* unit, s16 active) {
	unit->mBurnDamageFlameState = 1;
	unit->mbBurnDamageFlameActive = active;
}

BOOL BSE_TurnFirstProcessEffectMain(BattleUnit* unit) {
	BattleUnitPart* part;

	part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
	if (!unit->mBurnDamageFlameState) {
		return FALSE;
	}
	if (!unit->mbBurnDamageFlameActive) {
		return FALSE;
	}
	if (unit->mbBurnDamageFlameActive != 1) {
		return FALSE;
	}
	//TODO: finish
	return FALSE;
}

void BattleStatusChangeInfoWorkInit(BattleUnit* unit) {

}

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

void BattleStatusChangeMsgWorkInit(void) {

}

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
