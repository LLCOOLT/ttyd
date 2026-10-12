#include "battle/battle_ac.h"
#include "battle/battle.h"
#include "battle/ac/ac_table.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "battle/battle_disp.h"
#include "battle/battle_unit.h"

extern ActionCommandEntry ActionCommandList[];
extern BattleWork* _battleWorkPointer;

s32 psndSFXOn(const char* name);
void psndSFXOff(s32 id);
void psndSFX_pit(s32 id, s32 pitch);
void BattleAudience_Case_ActionCommandBad(BattleWeapon* weapon);
void BattleAudience_Case_ActionCommandGood(BattleWeapon* weapon);

#define AC_SE_ID(wp) (*(u32*)((u8*)(wp) + 0x1F18))
#define AC_SE_VAL(wp) (*(f32*)((u8*)(wp) + 0x1F1C))
#define AC_GUARD_TIMER(wp) (*(s16*)((u8*)(wp) + 0x1D18))

//local prototypes
u32 BattleACPadCheckRecordTrigger(s32 chan, s32 mask);


void BattleActionCommandManagerInit(BattleWork* wp) {
	BtlPad_WorkInit(&wp->actionCommands.pad);
	wp->actionCommands.maincb = NULL;
	wp->actionCommands.resultcb = NULL;
	wp->actionCommands.dispcb = NULL;
	wp->actionCommands.deletecb = NULL;
	wp->actionCommands.field_0x288 = -1;
}

void BattleActionCommandManager(BattleWork* wp) {
	BattleACMainCallback main;
	DispCallback disp;

	BtlPad_WorkUpdate(&wp->actionCommands.pad, 0);
	main = wp->actionCommands.maincb;
	if (main) {
		if (!main(wp)) {
			wp->actionCommands.maincb = NULL;
		}

		disp = wp->actionCommands.dispcb;
		if (disp) {
			dispEntry(CAMERA_2D, 900.0f, 1, disp, wp);
		}
	}
}

s32 BattleActionCommandResult(BattleWork* wp) {
	BattleACResultCallback result;

	result = wp->actionCommands.resultcb;
	if (result) {
		return result(wp);
	}
	else {
		return wp->actionCommands.result & 2;
	}
}

void BattleActionCommandDeclareACResult(BattleWork* work, BattleWeapon* weapon, s32 result) {
	switch (result) {
	case -1:
		BattleAudience_Case_ActionCommandBad(weapon);
		break;
	default:
		work->impendingBonuses.mWeapon = weapon;
		work->impendingBonuses.mSpAcSuccessMultiplier = 0.25f * (f32)result + 0.5f;
		work->impendingBonuses.field_0x9 = weapon->field_0x19;
		work->impendingBonuses.mBingoSlotChance = weapon->mBingoSlotChance;
		BattleAudience_Case_ActionCommandGood(weapon);
		break;
	}
}

void BattleActionCommandSetup(BattleWork* work, s32 id, BattleUnit* unit, s32 a4, s32 a5) {
	ActionCommandEntry* entry; // r6

	work->actionCommands.mAcUnit = unit;
	work->actionCommands.field_0x4 = a4;
	work->actionCommands.mAcState = 0;
	work->actionCommands.mResultCount = 0;
	work->actionCommands.result = 1;
	work->actionCommands.maincb = NULL;
	work->actionCommands.dispcb = NULL;
	work->actionCommands.resultcb = NULL;
	work->actionCommands.deletecb = NULL;
	work->actionCommands.field_0x8 = a5;
	work->actionCommands.field_0x30 = 0;
	for (entry = ActionCommandList; entry->id; entry++) {
		if (entry->id == id) {
			work->actionCommands.maincb = entry->main;
			if (!(work->actionCommands.mAcUnit->mTokenFlags & 0x10)){
				work->actionCommands.dispcb = entry->disp;
			}
			work->actionCommands.resultcb = entry->result;
			work->actionCommands.deletecb = entry->delete;
			return;
		}
	}
}

void BattleActionCommandStart(BattleWork* work) {
	work->actionCommands.mAcState = 100;
}

void BattleActionCommandStop(BattleWork* work) {
	if (work->actionCommands.deletecb) {
		work->actionCommands.deletecb(work);
	}
}

#pragma dont_inline on
s32 BattleActionCommandCheckDefence(BattleUnit* unit, BattleWeapon* weapon) {
	BattleWork* wp = _battleWorkPointer;
	s32 i;
	s32 count;
	s32 done;
	s32 diff;
	s32 normal;
	s32 superguard;
	u8 normal_frames[7] = {10, 9, 8, 8, 7, 6, 5};
	u8 super_frames[7] = {5, 4, 3, 3, 2, 1, 1};

	done = 0;
	wp->actionCommands.mDefenseResult = 0;
	diff = 3 + unit->badgesEquipped.Unsimplifier - unit->badgesEquipped.Simplifier;
	if (diff < 0) {
		diff = 0;
	}
	if (diff > 6) {
		diff = 6;
	}
	superguard = super_frames[diff];
	normal = normal_frames[diff];

	if ((u8)weapon->superguardsAllowed && unit->currentHp > 0) {
		if (AC_GUARD_TIMER(wp) > 0) {
			AC_GUARD_TIMER(wp)--;
			done = 1;
			wp->actionCommands.mDefenseResult = 5;
		}
		else if (unit->badgesEquipped.AutoCommand) {
			done = 1;
			wp->actionCommands.mDefenseResult = 5;
		}
		else {
			for (i = 0; i < superguard; i++) {
				if (BattleACPadCheckRecordTrigger(i, 0x200)) {
					break;
				}
			}
			if (i < superguard) {
				count = 0;
				for (i = 0; i < 15; i++) {
					if (BattleACPadCheckRecordTrigger(i, 0x100)) {
						count++;
					}
					if (BattleACPadCheckRecordTrigger(i, 0x200)) {
						count++;
					}
				}
				if (count < 2) {
					done = 1;
					wp->actionCommands.mDefenseResult = 5;
				}
			}
		}
	}

	if (!done) {
		if (AC_GUARD_TIMER(wp) > 0) {
			AC_GUARD_TIMER(wp)--;
			wp->actionCommands.mDefenseResult = 4;
		}
		else {
			count = 0;
			for (i = 0; i < 15; i++) {
				if (BattleACPadCheckRecordTrigger(i, 0x100)) {
					count++;
				}
				if (BattleACPadCheckRecordTrigger(i, 0x200)) {
					count++;
				}
			}
			if (count >= 2) {
				wp->actionCommands.mDefenseResult = 1;
			}
			else {
				for (i = 0; i < normal; i++) {
					if (BattleACPadCheckRecordTrigger(i, 0x100)) {
						break;
					}
				}
				if (i >= normal) {
					if (count > 0) {
						wp->actionCommands.mDefenseResult = 1;
					}
					else {
						wp->actionCommands.mDefenseResult = 2;
					}
				}
				else {
					wp->actionCommands.mDefenseResult = 4;
				}
			}
		}
	}
	BtlPad_WorkInit(&wp->actionCommands.pad);
	return wp->actionCommands.mDefenseResult;
}
#pragma dont_inline reset

u32 BattleACPadCheckRecordTrigger(s32 chan, s32 mask) {
	return _battleWorkPointer->actionCommands.pad.mButtonsPressedHistory[chan] & mask;
}

s32 BattleActionCommandGetDefenceResult(void) {
	return _battleWorkPointer->actionCommands.mDefenseResult;
}

void BattleActionCommandResetDefenceResult(void) {
	BattleWork* wp = _battleWorkPointer;
	wp->actionCommands.mDefenseResult = 0;
	BtlPad_WorkInit(&wp->actionCommands.pad);
}

s8 BattleActionCommandGetDifficulty(BattleWork* work) {
	return work->actionCommands.mAcDifficulty;
}

void BattleActionCommandSetDifficulty(BattleWork* work, BattleUnit* unit, s32 difficulty) {
	s32 adjusted;

	work->actionCommands.mBaseAcDifficulty = difficulty;
	adjusted = difficulty - unit->badgesEquipped.Simplifier + unit->badgesEquipped.Unsimplifier;
	if (adjusted < 0) {
		adjusted = 0;
	}
	if (adjusted > 6) {
		adjusted = 6;
	}
	work->actionCommands.mAcDifficulty = adjusted;
}

s32 BattleActionCommandGetPrizeLv(BattleWork* work, BattleUnit* unit, s32 lv) {
	if (unit != NULL && (u8)unit->damageCode == 0x1E) {
		return -1;
	}
	lv += (u8)work->actionCommands.mAcDifficulty;
	lv--;
	if (lv < 0) {
		lv = 0;
	}
	if (lv >= 7) {
		lv = 6;
	}
	return lv;
}

u16 BattleACGetButtonIcon(s32 button, s32 pressed) {
	u16 icon = 0;

	switch (button) {
	case 0x100:
		if (pressed) icon = 0x65; else icon = 0x64;
		break;
	case 0x200:
		if (pressed) icon = 0x67; else icon = 0x66;
		break;
	case 0x400:
		if (pressed) icon = 0x69; else icon = 0x68;
		break;
	case 0x800:
		if (pressed) icon = 0x6B; else icon = 0x6A;
		break;
	case 0x20:
		if (pressed) icon = 0x81; else icon = 0x80;
		break;
	case 0x40:
		if (pressed) icon = 0x7F; else icon = 0x7E;
		break;
	case 0x10:
		if (pressed) icon = 0x83; else icon = 0x82;
		break;
	case 0x10000:
		if (pressed) icon = 0x7C; else icon = 0x79;
		break;
	case 0x20000:
		if (pressed) icon = 0x76; else icon = 0x79;
		break;
	case 0x40000:
		if (pressed) icon = 0x78; else icon = 0x79;
		break;
	case 0x80000:
		if (pressed) icon = 0x7A; else icon = 0x79;
		break;
	case 0x90000:
		if (pressed) icon = 0x7D; else icon = 0x79;
		break;
	case 0xA0000:
		if (pressed) icon = 0x77; else icon = 0x79;
		break;
	case 0x50000:
		if (pressed) icon = 0x7B; else icon = 0x79;
		break;
	case 0x60000:
		if (pressed) icon = 0x75; else icon = 0x79;
		break;
	}
	return icon;
}

static inline s32 gaugeMax(void) {
	return 100;
}

static inline void gaugeQuad(CameraEntry* cam, f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
	if (x1 >= x0) {
		btlDispGXInit2DRasta();
		GXLoadPosMtxImm(cam->view, 0);
		btlDispGXQuads2DRasta(x0, y0, x1, y1, r, g, b, a);
	}
}

void BattleAcDrawGauge(s32 x, s32 y, s32 width, f32 ratio, s32 level, s32 a, s32 b, s32 c, s32 flags) {
	BattleWork* wp = _battleWorkPointer;
	s32 max = gaugeMax();
	Vec pos;
	GXColor color = {0x00, 0xE4, 0x86, 0xFF};
	CameraEntry* cam;
	f32 r;

	cam = camGetPtr(CAMERA_2D);
	pos = (Vec){0.0f, 0.0f, 0.0f};
	pos.x = x - 200;
	pos.y = y + 25;
	iconDispGx(&pos, 0x10, 0x8C, 1.0f);

	if (level >= 2) {
		gaugeQuad(cam, x - 289, y + 50, x + width * a / max - 289, y + 32, 0x21, 0x21, 0x75, 0xFF);
		if (b - a > 0) {
			gaugeQuad(cam, x + width * a / max - 289, y + 50, x + width * b / max - 289, y + 32, 0x1D, 0x23, 0xA3, 0xFF);
		}
		if (c - b > 0) {
			gaugeQuad(cam, x + width * b / max - 289, y + 50, x + width * c / max - 289, y + 32, 0x46, 0x0C, 0xB4, 0xFF);
		}
		if (100 - c > 0) {
			gaugeQuad(cam, x + width * c / max - 289, y + 50, x + width * 100 / max - 289, y + 32, 0x73, 0x0D, 0x13, 0xFF);
		}
	}

	if (level >= 2) {
		btlDispGXInit2DRasta();
		GXLoadPosMtxImm(cam->view, 0);
		btlDispGXQuads2DRasta(x - 289, y + 50, x - 289, y + 32, 0x2D, 0x38, 0xD2, 0xFF);
		if (a > 0) {
			r = x + width * a / max - 289;
			gaugeQuad(cam, r - 2.0f, y + 50, r, y + 32, 0x54, 0x28, 0xD1, 0xFF);
		}
		if (b - a > 0) {
			r = x + width * b / max - 289;
			gaugeQuad(cam, r - 2.0f, y + 50, r, y + 32, 0x7D, 0x2C, 0xB5, 0xFF);
		}
		if (c - b > 0) {
			r = x + width * c / max - 289;
			gaugeQuad(cam, r - 2.0f, y + 50, r, y + 32, 0xA1, 0x1B, 0x55, 0xFF);
		}
	}

	if (ratio < 0.0f) {
		return;
	}

	if (flags & 3) {
		if (flags & 1) {
			u8* mod = (u8*)wp + 0x1F2C;
			color.r = color.r * mod[0] / 255;
			color.g = color.g * mod[1] / 255;
			color.b = color.b * mod[2] / 255;
			color.a = color.a * mod[3] / 255;
		}
		else {
			color = (GXColor){0xFF, 0x00, 0x00, 0xFF};
		}
		if (ratio > 0.0f) {
			gaugeQuad(cam, x - 289, y + 50, (f32)(x - 289) + (f32)width * ratio, y + 32, color.r, color.g, color.b, color.a);
		}
		return;
	}

	if (ratio <= 0.0f) {
		return;
	}
	ratio = 100.0f * ratio;

	r = ratio;
	if (ratio > a) {
		r = a;
	}
	if (r > 0.0f) {
		gaugeQuad(cam, x - 289, y + 50, (f32)(x - 289) + width * r / 100.0f, y + 32, 0x00, 0xE4, 0x86, 0xFF);
	}

	r = ratio;
	if (ratio > b) {
		r = b;
	}
	if (r - a > 0.0f) {
		gaugeQuad(cam, x + width * a / max - 289, y + 50, (f32)(x - 289) + width * r / 100.0f, y + 32, 0x2E, 0xB4, 0xF2, 0xFF);
	}

	r = ratio;
	if (ratio > c) {
		r = c;
	}
	if (r - b > 0.0f) {
		gaugeQuad(cam, x + width * b / max - 289, y + 50, (f32)(x - 289) + width * r / 100.0f, y + 32, 0x75, 0x70, 0xFF, 0xFF);
	}

	if (ratio > 100.0f) {
		ratio = 100.0f;
	}
	if (ratio - c > 0.0f) {
		gaugeQuad(cam, x + width * c / max - 289, y + 50, (f32)(x - 289) + width * ratio / 100.0f, y + 32, 0xF3, 0x04, 0xBC, 0xFF);
	}
}

void BattleAcGaugeSeInit(void) {
	BattleWork* wp = _battleWorkPointer;

	AC_SE_ID(wp) = psndSFXOn("SFX_AC_POWER_GAUGE1");
	AC_SE_VAL(wp) = 0.0f;
}

void BattleAcGaugeSeUpdate(f32 value) {
	BattleWork* wp = _battleWorkPointer;

	if (value < 0.0f) {
		value = 0.0f;
	}
	if (value > 100.0f) {
		value = 100.0f;
	}
	AC_SE_VAL(wp) = value;
	if (AC_SE_ID(wp) != -1) {
		psndSFX_pit(AC_SE_ID(wp), 0.01f * (4092.0f * AC_SE_VAL(wp)));
	}
}

void BattleAcGaugeSeDelete(void) {
	BattleWork* wp = _battleWorkPointer;

	if (AC_SE_ID(wp) != -1) {
		psndSFXOff(AC_SE_ID(wp));
		AC_SE_ID(wp) = -1;
	}
}
