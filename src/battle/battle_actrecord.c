#include "battle/battle_actrecord.h"

extern BattleWork* _battleWorkPointer;
#pragma optimize_for_size on
#pragma dont_inline on
#ifdef VERSION_G8ME01
#define R(o) (hi[0x6f1c + (o)])
#else
#define R(o) (hi[0x6f00 + (o)])
#endif
s32 _check_turn_count_0_end(s32 n);
s32 _check_turn_count_0_turn(s32 n);
s32 _check_use(s32 n);
s32 _check_no_use(s32 n);

void BtlActRec_AddCount(u8* count) {
	if (*count < 100) {
		*count = *count + 1;
	}
}

void BtlActRec_AddPoint(u8* point, s32 amount) {
	*point += amount;
	if (*point > 100) {
		*point = 100;
	}
}

void BtlActRec_JudgeTurnRuleKeep(void) {
	s32 v;
	BattleWork* wp = _battleWorkPointer;
	u8* rec = *(u8**)((u8*)wp + 0x2738);
	u8* hi = (u8*)wp + 0x10000;
	switch (rec[0x18]) {
	case 60:
	case 61:
	case 62:
		if (rec[0x18] == 62) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x1f) + R(0x25) + R(0x26) + R(0x29) + R(0x33) + R(0x35) + R(0x37) + R(0x39) + R(0x3a) + R(0x27) + R(0x28) + R(0x2a) + R(0x34) + R(0x36) + R(0x38);
		} else if (rec[0x18] == 60) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x1f) + R(0x25) + R(0x26) + R(0x29) + R(0x33) + R(0x35) + R(0x37);
		} else {
			v = R(0x39) + R(0x3a) + R(0x27) + R(0x28) + R(0x2a) + R(0x34) + R(0x36) + R(0x38);
		}
		_check_turn_count_0_turn(v);
		break;
	case 63:
	case 64:
	case 65:
		if (rec[0x18] == 65) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x25) + R(0x39) + R(0x27);
		} else if (rec[0x18] == 63) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x25);
		} else {
			v = R(0x39) + R(0x27);
		}
		_check_turn_count_0_turn(v);
		break;
	}
}

void BtlActRec_JudgeRuleKeep(void) {
	s32 v;
	BattleWork* wp = _battleWorkPointer;
	u8* hi;
	u8* rec;
	void* mario;
	rec = *(u8**)((u8*)wp + 0x2738);
	hi = (u8*)wp + 0x10000;
	mario = BattleGetMarioPtr(wp);
	BattleGetPartyPtr(wp);
	switch (rec[0x18]) {
	case 0:
		rec[0x19] = 6;
		break;
	case 1:
		rec[0x19] = _check_no_use(R(0x1c));
		break;
	case 2:
		rec[0x19] = _check_use(R(0x1c));
		break;
	case 3:
		rec[0x19] = _check_no_use(R(0x1d));
		break;
	case 4:
		rec[0x19] = _check_use(R(0x1d));
		break;
	case 5:
		rec[0x19] = _check_no_use(R(0x1e) + R(0x1f));
		break;
	case 6:
		rec[0x19] = _check_use(R(0x1e) + R(0x1f));
		break;
	case 7:
		rec[0x19] = _check_no_use(R(0x20));
		break;
	case 8:
		rec[0x19] = _check_use(R(0x20));
		break;
	case 9:
		rec[0x19] = _check_no_use(R(0x21));
		break;
	case 10:
		rec[0x19] = _check_use(R(0x21));
		break;
	case 11:
		rec[0x19] = _check_no_use(R(0x20) + R(0x21));
		break;
	case 12:
		rec[0x19] = _check_use(R(0x20) + R(0x21));
		break;
	case 13:
		rec[0x19] = _check_no_use(R(0x22));
		break;
	case 14:
		rec[0x19] = _check_use(R(0x22));
		break;
	case 15:
		rec[0x19] = _check_no_use(R(0x23));
		break;
	case 16:
		rec[0x19] = _check_use(R(0x23));
		break;
	case 17:
		rec[0x19] = _check_no_use(R(0x22) + R(0x23));
		break;
	case 18:
		rec[0x19] = _check_use(R(0x22) + R(0x23));
		break;
	case 19:
		if (mario != NULL) {
			rec[0x19] = _check_use(*(s16*)((u8*)mario + 0x10c));
		} else {
			rec[0x19] = 1;
		}
		break;
	case 20:
		if (mario != NULL) {
			rec[0x19] = _check_no_use(*(s16*)((u8*)mario + 0x10c));
		} else {
			rec[0x19] = 1;
		}
		break;
	case 21:
		rec[0x19] = _check_use(R(0x24));
		break;
	case 22:
		rec[0x19] = _check_no_use(R(0x25) + R(0x26));
		break;
	case 23:
		rec[0x19] = _check_use(R(0x25) + R(0x26));
		break;
	case 24:
		rec[0x19] = _check_no_use(R(0x27) + R(0x28));
		break;
	case 25:
		rec[0x19] = _check_use(R(0x27) + R(0x28));
		break;
	case 26:
		rec[0x19] = _check_no_use(R(0x25) + R(0x26) + R(0x27) + R(0x28));
		break;
	case 27:
		rec[0x19] = _check_use(R(0x25) + R(0x26) + R(0x27) + R(0x28));
		break;
	case 28:
		rec[0x19] = _check_no_use(R(0x29));
		break;
	case 29:
		rec[0x19] = _check_use(R(0x29));
		break;
	case 30:
		rec[0x19] = _check_no_use(R(0x2a));
		break;
	case 31:
		rec[0x19] = _check_use(R(0x2a));
		break;
	case 32:
		rec[0x19] = _check_no_use(R(0x29) + R(0x2a));
		break;
	case 33:
		rec[0x19] = _check_use(R(0x29) + R(0x2a));
		break;
	case 34:
		rec[0x19] = _check_no_use(R(0x2b));
		break;
	case 35:
		rec[0x19] = _check_use(R(0x2b));
		break;
	case 36:
		rec[0x19] = _check_no_use(R(0x2c));
		break;
	case 37:
		rec[0x19] = _check_use(R(0x2c));
		break;
	case 38:
		rec[0x19] = _check_no_use(R(0x2d));
		break;
	case 39:
		rec[0x19] = _check_use(R(0x2d));
		break;
	case 40:
		rec[0x19] = _check_no_use(R(0x2e));
		break;
	case 41:
		rec[0x19] = _check_use(R(0x2e));
		break;
	case 42:
		rec[0x19] = _check_no_use(R(0x2d) + R(0x2e));
		break;
	case 43:
		rec[0x19] = _check_use(R(0x2d) + R(0x2e));
		break;
	case 44:
		rec[0x19] = _check_no_use(R(0x2f));
		break;
	case 45:
		rec[0x19] = _check_use(R(0x2f));
		break;
	case 46:
		rec[0x19] = _check_no_use(R(0x31));
		break;
	case 47:
		rec[0x19] = _check_use(R(0x31));
		break;
	case 48:
		rec[0x19] = _check_no_use(R(0x2f) + R(0x31));
		break;
	case 49:
		rec[0x19] = _check_use(R(0x2f) + R(0x31));
		break;
	case 50:
		rec[0x19] = _check_no_use(R(0x30));
		break;
	case 51:
		rec[0x19] = _check_use(R(0x30));
		break;
	case 52:
		rec[0x19] = _check_no_use(R(0x32));
		break;
	case 53:
		rec[0x19] = _check_use(R(0x32));
		break;
	case 54:
		rec[0x19] = _check_no_use(R(0x2f) + R(0x31));
		break;
	case 55:
		rec[0x19] = _check_use(R(0x2f) + R(0x31));
		break;
	case 56:
		rec[0x19] = _check_no_use(R(0x30) + R(0x32));
		break;
	case 57:
		rec[0x19] = _check_use(R(0x30) + R(0x32));
		break;
	case 58:
		if (R(0x3b) > rec[0x1a]) {
			rec[0x19] = 6;
		} else if (R(0x3b) > rec[0x1b]) {
			rec[0x19] = 2;
		} else {
			rec[0x19] = 1;
		}
		break;
	case 59:
		if (R(0x3b) <= rec[0x1a]) {
			rec[0x19] = 6;
		} else if (R(0x3b) <= rec[0x1b]) {
			rec[0x19] = 2;
		} else {
			rec[0x19] = 1;
		}
		break;
	case 60:
	case 61:
	case 62:
		if (rec[0x18] == 62) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x1f) + R(0x25) + R(0x26) + R(0x29) + R(0x33) + R(0x35) + R(0x37) + R(0x39) + R(0x3a) + R(0x27) + R(0x28) + R(0x2a) + R(0x34) + R(0x36) + R(0x38);
		} else if (rec[0x18] == 60) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x1f) + R(0x25) + R(0x26) + R(0x29) + R(0x33) + R(0x35) + R(0x37);
		} else {
			v = R(0x39) + R(0x3a) + R(0x27) + R(0x28) + R(0x2a) + R(0x34) + R(0x36) + R(0x38);
		}
		_check_turn_count_0_end(v);
		break;
	case 63:
	case 64:
	case 65:
		if (rec[0x18] == 65) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x25) + R(0x39) + R(0x27);
		} else if (rec[0x18] == 63) {
			v = R(0x1c) + R(0x1d) + R(0x1e) + R(0x25);
		} else {
			v = R(0x39) + R(0x27);
		}
		_check_turn_count_0_end(v);
		break;
	case 66:
		if (R(0x1d) + R(0x1e) + R(0x1f) + R(0x25) + R(0x26) + R(0x29) + R(0x33) + R(0x35) + R(0x2d) + R(0x37) == 0) {
			rec[0x19] = 6;
		} else {
			rec[0x19] = 1;
		}
		break;
	case 67:
		if (R(0x1c) + R(0x1e) + R(0x1f) + R(0x25) + R(0x26) + R(0x29) + R(0x33) + R(0x35) + R(0x2d) + R(0x37) == 0) {
			rec[0x19] = 6;
		} else {
			rec[0x19] = 1;
		}
		break;
	}
}


s32 _check_use(s32 n) {
	u8* rec = *(u8**)((u8*)_battleWorkPointer + 0x2738);
	if (n >= rec[0x1a]) {
		return 6;
	}
	return (n >= rec[0x1b]) + 1;
}

s32 _check_no_use(s32 n) {
	u8* rec = *(u8**)((u8*)_battleWorkPointer + 0x2738);
	if (n >= rec[0x1b]) {
		return 1;
	}
	return n >= rec[0x1a] ? 2 : 6;
}

s32 _check_turn_count_0_turn(s32 n) {
	BattleWork* wp = _battleWorkPointer;
	u8* rec = *(u8**)((u8*)wp + 0x2738);
	u8* hi = (u8*)wp + 0x10000;
	if (R(0x3b) <= rec[0x1b] || rec[0x1b] == 0xff) {
		if (n == 0) {
			rec[0x19] = 2;
		} else {
			rec[0x19] = 1;
		}
	}
	if (R(0x3b) <= rec[0x1a] || rec[0x1a] == 0xff) {
		if (n == 0) {
			rec[0x19] = 6;
		} else if (!(rec[0x19] & 2)) {
			rec[0x19] = 1;
		}
	}
	return rec[0x19];
}

s32 _check_turn_count_0_end(s32 n) {
	BattleWork* wp = _battleWorkPointer;
	u8* rec = *(u8**)((u8*)wp + 0x2738);
	u8* hi = (u8*)wp + 0x10000;
	if (R(0x3b) <= rec[0x1b] || rec[0x1b] == 0xff) {
		if (n == 0) {
			rec[0x19] = 2;
		} else {
			rec[0x19] = 1;
		}
	}
	if (R(0x3b) <= rec[0x1a] || rec[0x1a] == 0xff) {
		if (n == 0) {
			rec[0x19] = 6;
		} else if (!(rec[0x19] & 2)) {
			rec[0x19] = 1;
		}
	}
	return rec[0x19];
}
