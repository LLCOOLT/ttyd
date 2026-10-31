#include "version.h"
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


#define ST_CHG_MSG(i) ((StChgMsg*)_battleWorkPointer->announce.stChg.msg + (i)) /* cast keeps the 0x18D88 displacement folded into each access */

BOOL BattleStatusChangeAnnouceMain_Unit(BattleUnit* unit);
void BattleStatusChangeMsgSetAnnouce(BattleUnit* unit, s32 index, s32 changed);
void BattleStatusChangeInfoWorkInit(BattleUnit* unit);
void _st_chg_msg_disp(void);

typedef struct StChgMsgData {
	s8 type;
	const char* name;
	const char* msg1;
	const char* msg0;
} StChgMsgData;

// Status Type Priority Data. The demo defines it first; its .data follows that order (retail keeps it in .sdata).
#ifdef VERSION_G8ME01_DEMO
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
	-1,
};
#endif

StChgMsgData _st_chg_msg_data[] = {
	{ 4, "どく", "msg_st_chg_poison", "msg_st_chg_poison" },
	{ 16, "チャージ", "msg_st_chg_charge", "msg_st_chg_charge3" },
	{ 1, "ねむり", "msg_st_chg_sleep", "msg_st_chg_sleep" },
	{ 2, "ストップ", "msg_st_chg_stan", "msg_st_chg_stan" },
	{ 3, "グルグル", "msg_st_chg_guruguru", "msg_st_chg_guruguru" },
	{ 5, "こんらん", "msg_st_chg_confusion", "msg_st_chg_confusion" },
	{ 6, "ビリビリ", "msg_st_chg_biribiri", "msg_st_chg_biribiri" },
	{ 7, "ヨケヨケ", "msg_st_chg_dodge", "msg_st_chg_dodge" },
	{ 8, "ひだるま", "msg_st_chg_fire", "msg_st_chg_fire" },
	{ 9, "こおりづけ", "msg_st_chg_freeze", "msg_st_chg_freeze" },
	{ 10, "デカデカ", "msg_st_chg_big", "msg_st_chg_big" },
	{ 11, "ミニミニ", "msg_st_chg_small", "msg_st_chg_small" },
	{ 12, "つよつよ", "msg_st_chg_tuyotuyo", "msg_st_chg_tuyotuyo" },
	{ 13, "よわよわ", "msg_st_chg_yowayowa", "msg_st_chg_yowayowa" },
	{ 14, "カチカチ", "msg_st_chg_hard", "msg_st_chg_hard" },
	{ 15, "フニャフニャ", "msg_st_chg_soft", "msg_st_chg_soft" },
	{ 0, "アレルギー", "msg_st_chg_allergy", "msg_st_chg_allergy" },
	{ 18, "とうめい", "msg_st_chg_trans", "msg_st_chg_trans" },
	{ 19, "はやい", "msg_st_chg_quick", "msg_st_chg_quick" },
	{ 20, "のろい", "msg_st_chg_slow", "msg_st_chg_slow" },
	{ 21, "しかえし", "msg_st_chg_counter", "msg_st_chg_counter" },
	{ 22, "ボムカウンター", "msg_st_chg_bombcounter", "msg_st_chg_bombcounter" },
	{ 23, "じわじわＨＰ", "msg_st_chg_reg_hp", "msg_st_chg_reg_hp" },
	{ 24, "じわじわＦＰ", "msg_st_chg_reg_fp", "msg_st_chg_reg_fp" },
	{ -1, "", "", "" },
};


#ifndef VERSION_G8ME01_DEMO
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
	-1,
};
#endif

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
#define EFF_SLEEP(u) ((u)->sleepEff)
#define EFF_SPARK(u) ((u)->sparkEff)

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
		if (unit->mAttributeFlags & 2) {
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
		if (unit->mAttributeFlags & 2) {
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
#define EFF_FIRE(u) ((u)->fireEff)
#define EFF_ICE(u) ((u)->iceEff)

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
		x += unit->mSizeMultiplier * (unit->mKindParams->burnFlameOffset.x * (unit->faceDirection >= 0 ? 1.0f : -1.0f));
		y += unit->mKindParams->burnFlameOffset.y * unit->mSizeMultiplier;
		z += unit->mKindParams->burnFlameOffset.z * unit->mSizeMultiplier;
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


void BSE_Kagegakure(BattleUnit* unit) {
	char name[0x10];
	f32 x, y, z;
	BOOL on = FALSE;

	if ((_battleWorkPointer->dispFlags & 1) && (unit->mAttributeFlags & 0x10)) {
		on = TRUE;
	}
	if (on) {
		if (unit->kageIcon == NULL) {
			sprintf(name, "_biK_%02x", *(s32*)unit);
#ifdef VERSION_G8ME01
			iconEntry(name, 0xA1);
#else
			iconEntry(name, 0x99);
#endif
			unit->kageIcon = iconNameToPtr(name);
		}
		BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
		iconSetPos(unit->kageIcon->name, x, y, z + 5.0f);
	}
	else {
		BSE_KagegakureDelete(unit);
	}
}

void BSE_KagegakureDelete(BattleUnit* unit) {
	if (unit->kageIcon != NULL) {
		iconDelete(unit->kageIcon->name);
		unit->kageIcon = NULL;
	}
}

void BSE_TurnFirstProcessEffectEntry(BattleUnit* unit, s16 active) {
	unit->mBurnDamageFlameState = 1;
	unit->mbBurnDamageFlameActive = active;
}

void BattleDamageDirect(s32 unitId, BattleUnit* target, BattleUnitPart* part, s32 damage, s32 fpDamage, u32 result, u32 pattern, s32 flag);
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);
f32 sinfd(f32 degrees);

#pragma optimize_for_size on
BOOL BSE_TurnFirstProcessEffectMain(BattleUnit* unit) {
	BattleUnitPart* part;
	f32 x, y, z;
	f32* work;
	u16 ac;
	u16 st;

	part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
	st = unit->mBurnDamageFlameState;
	if (st == 0) {
		return FALSE;
	}
	ac = unit->mbBurnDamageFlameActive;
	if (ac == 0) {
		return FALSE;
	}
	switch (ac) {
	case 1:
	switch (st) {
	case 1:
		unit->mBurnDamageFlameState = st + 1;
		unit->mBurnDamageFlameScale = 1.0f;
		BtlUnit_GetPartsWorldPos(part, &x, &y, &z);
		z += 5.0f;
		unit->mBurnDamageFlameEff = effFireEntry(0, 0, x, y, z, unit->mBurnDamageFlameScale);
		unit->mBurnDamageFlameAnimTimer = 0;
		break;
	case 2:
		work = (f32*)unit->mBurnDamageFlameEff->userdata;
		unit->mBurnDamageFlameAnimTimer++;
		unit->mBurnDamageFlameScale = 1.6f * sinfd(unit->mBurnDamageFlameAnimTimer * 3) + 0.4f;
		work[9] = unit->mBurnDamageFlameScale;
		if (unit->mBurnDamageFlameAnimTimer >= 60) {
			unit->mBurnDamageFlameState++;
		}
		break;
	case 3:
		effDelete(unit->mBurnDamageFlameEff);
		unit->mBurnDamageFlameEff = NULL;
		unit->mBurnDamageFlameState = 0;
		if (!BtlUnit_CheckShadowGuard(unit)) {
			BattleDamageDirect(-5, unit, NULL, 1, 0, 0x118, 0, 1);
		}
	case 0:
	default:
		return FALSE;
	}
	break;
	default:
		return FALSE;
	}
	return TRUE;
}
#pragma optimize_for_size reset

#pragma optimize_for_size on
void BattleStatusChangeInfoWorkInit(BattleUnit* unit) {
	s32 i;
	StChgInfo* e = &unit->statusChangeInfo[0];

	for (i = 0; i < 6; i++) {
		StChgInfo* p = &e[i];
		p->type = -1;
		p->strength = 0;
		p->stagger = 0;
		p->stackOffset = 0;
		p->reserved_04 = 0;
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
void BattleStatusChangeInfoSetAnnouce(BattleUnit* unit, s32 type, s32 strength, s32 changed) {
	StChgInfo* e = &unit->statusChangeInfo[0];
	StChgInfo tmp, swap;
	s8 pri = _get_pri(type);
	s32 i, j, n;
	u8 u, t;

	for (i = 0; i < 6; i++) {
		s32 cur = e[i].type;

		n = _get_pri(cur);
		if (pri >= (s8)n) break;
	}
	if (i >= 6) return;
	tmp.type = type;
	tmp.strength = strength;
	tmp.changed = changed;
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
	j = 0;
	n = j;
	t = 0;
	for (i = 0; i < 6; i++) {
		if (e[i].type == -1) break;
		e[i].stagger = t;
		e[i].reserved_04 = j;
		t += 10;
		n++;
	}
if (t == 0) goto L3;
	u = 0x50;
	goto Ld;
L3:
	u = 0x3C;
Ld:;
	for (j = n; j >= 0; j--) {
		if (e[j].type != -1) {
			e[j].stackOffset = u;
			u += 10;
		}
	}
}

#pragma optimize_for_size reset
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

void BattleStatusChangeMsgSetAnnouce(BattleUnit* unit, s32 index, s32 changed) {
	StChgMsg* msg = ST_CHG_MSG(index);
	s32 id;

	msg->unitId = unit->unitId;
	msg->type = index;
	msg->timer = 0;
	msg->changed = changed;
	id = unit->currentKind;
	if (id == 0xDE) {
		msg->flags |= 1;
	}
	else if (id >= 0xE0 && id < 0xE7 && unit->mAlliance == 0) {
		msg->flags |= 2;
	}
	else {
		msg->flags |= 4;
	}
}

#pragma optimize_for_size on
void BattleStatusChangeMsgAdjust(BattleWork* wp) {
	s32 t;
	StChgWork* base;
	s8 i;
	StChgMsg* msg;
	s32 j;
	BattleUnit* unit;
	s32 n, found, k;
	StChgInfo* e;

	base = &wp->announce.stChg;

	for (i = 0; i < 28; i++) {
		t = i;
		msg = &base->msg[t];
		if (msg->type == -1) continue;
		msg->flags = 0;
		for (j = 0; j < 64; j++) {
			unit = BattleGetUnitPtr(wp, j);
			if (unit && !BtlUnit_CheckStatus(unit, 0x1B)) {
				e = &unit->statusChangeInfo[0];
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
					BattleStatusChangeMsgSetAnnouce(unit, t, e[k].changed);
				}
			}
		}
		if (!msg->flags) {
			msg->unitId = -1;
			msg->type = -1;
		}
		else if (*(s64*)&base->maskHi & (s64)(1 << t)) {
			msg->unitId = -1;
			msg->type = -1;
		}
	}
}

BOOL BattleStatusChangeMsgMain(BattleWork* wp) {
	StChgWork* base = &wp->announce.stChg;
	StChgMsg* msg;
	s8* p;
	BOOL ret = FALSE;
	s32 i;

	for (i = 0; _st_pri_data[i] != -1; i++) {
		msg = &base->msg[_st_pri_data[i]];
		if (msg->type == -1) continue;
		ret = TRUE;
		BattleGetUnitPtr(wp, msg->unitId);
		if (msg->timer) {
			msg->timer--;
			if (BattlePadCheckTrigger(0x300)) {
				msg->timer = 0;
			}
			if (!msg->timer) {
				msg->type = -1;
			}
		}
		else {
			sprintf(base->text, "");
			for (i = 0; i < 28; i++) {
				if (msg->type == _st_chg_msg_data[i].type || _st_chg_msg_data[i].type == -1) {
					if (msg->changed) {
						sprintf(base->text, msgSearch(_st_chg_msg_data[i].msg1));
					}
					else {
						sprintf(base->text, msgSearch(_st_chg_msg_data[i].msg0));
					}
					break;
				}
			}
			msg->timer = 90;
		}
		dispEntry(8, 900.0f, 1, (DispCallback)_st_chg_msg_disp, 0);
		break;
	}
#ifndef VERSION_G8ME01_DEMO
	if (ret) {
		for (i = 0; i < 64; i++) {
			BattleUnit* unit = BattleGetUnitPtr(wp, i);
			if (unit) BattleStatusChangeInfoWorkInit(unit);
		}
	}
#endif
	return ret;
}



typedef void (*WakuColByRefFunc)(u16, GXColor*, f32, f32, f32, f32, f32);

void _st_chg_msg_disp(void) {
	StChgWork* st = &_battleWorkPointer->announce.stChg;
	f32 y; f32 x; u16 width; u16 lines;
	GXColor col0;
	width = FontGetMessageWidthLine((const char*)st->text, &lines);
	lines++;
	col0 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	y = 0.0f; x = y - (width / 2); y = -120.0f;
	// the color is passed by address here (same ABI as by-value GXColor)
	((WakuColByRefFunc)windowDispGX_Waku_col)(0, &col0, x - 20.0f, ((lines - 1) * 29) + -117.0f, (f32)(width + 40), (f32)(lines * 29 + 1), 10.0f);
	FontDrawStart();
	FontDrawMessage(x, (s32)y + (lines - 1) * 29, (const char*)st->text);
}

