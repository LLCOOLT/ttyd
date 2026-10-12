#include "battle/battle.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <string.h>

extern BattleWork* _battleWorkPointer;

typedef struct ZSObj {
	s32 a;
	s32 n;
	Vec* v;
	Vec pos;
	u8 pad[0x30];
	s32 f48;
	s32 f4c;
} ZSObj;

typedef struct ZubaStarWork {
	/* 0x000 */ u8 pad0[0x10];
	/* 0x010 */ s32 level;
	/* 0x014 */ s32 count;
	/* 0x018 */ u8 pad18[0x90];
	/* 0x0A8 */ ZSObj* ptrs[200];
	/* 0x3C8 */ u8 pad3c8[0x1C0];
	/* 0x588 */ smartEntry* capture;
	/* 0x58C */ s32 stone_state;
	/* 0x590 */ u8 pad590[0x4C];
	/* 0x5DC */ EffectEntry* eff;
} ZubaStarWork;

ZubaStarWork* GetZubaStarPtr(void);

s32 star_stone_appear(void) {
	ZubaStarWork* w = GetZubaStarPtr();
	w->stone_state = 1;
	return 2;
}

s32 wait_star_stone_up(void) {
	return GetZubaStarPtr()->stone_state == 4 ? 2 : 0;
}

void zubaStarDispStar(void) {
}

#pragma dont_inline on
ZubaStarWork* GetZubaStarPtr(void) {
	return (ZubaStarWork*)((u8*)_battleWorkPointer + 0x1f4c);
}

#pragma dont_inline reset
s32 weaponGetPower_ZubaStar(void* a, s32* tbl) {
	return tbl[GetZubaStarPtr()->level + 8];
}

const Vec vec3_802ff6b0 = {0.0f, 0.0f, 0.0f};

void zubastar_create_takaku(s32 n, Vec* pts) {
	ZubaStarWork* w = GetZubaStarPtr();
	ZSObj* t;
	s32 i;
	s32 off;
	w->ptrs[w->count] = BattleAlloc(0x50);
	t = w->ptrs[w->count];
	t->v = BattleAlloc(n * 0xc);
	t->a = 0;
	t->n = n;
	t->pos = vec3_802ff6b0;
	t->f48 = 0;
	t->f4c = 1;
	off = 0;
	for (i = 0; i < n; i++, off += 0xc) {
		*(Vec*)((u8*)t->v + off) = *(Vec*)((u8*)pts + off);
	}
	w->count++;
}

s32 zubastar_get_kouten(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, f32* ox, f32* oy) {
	f32 dx1 = x2 - x1;
	f32 dx2;
	f32 a, b, d, t, e1, e2;
	if (dx1 == 0.0f && (dx2 = x4 - x3) == 0.0f) return 0;
	e1 = dx1 != 0.0f ? dx1 : 1e-5f;
	dx2 = x4 - x3;
	e2 = dx2 != 0.0f ? dx2 : 1e-5f;
	a = (y2 - y1) / e1;
	b = (y4 - y3) / e2;
	d = a - b;
	if (d == 0.0f) return 0;
	*ox = ((y3 - y1) + (a * x1 - b * x3)) / d;
	if (dx1 != 0.0f) *oy = a * (*ox - x1) + y1;
	else *oy = b * (*ox - x3) + y3;
	t = (*ox - x3) / e2;
	if (t >= 0.0f && t <= 1.0f) return 1;
	return 0;
}

s32 zubastar_init(void) {
	memset(GetZubaStarPtr(), 0, 0x5E0);
	return 2;
}

s32 zubastar_end(void) {
	s32 off = 0;
	s32 i;
	ZubaStarWork* w = GetZubaStarPtr();
	effDelete(*(EffectEntry**)((u8*)*(void**)((u8*)w->eff + 0xc) + 0x34));
	effDelete(w->eff);
	for (i = 0; i < 200; i++, off += 4) {
		typedef struct { u8 pad[8]; void* buf; } E;
		s32 o = off + 0xa8;
		if (*(E**)((u8*)w + o) != NULL) {
			if ((*(E**)((u8*)w + o))->buf != NULL) {
				BattleFree((*(E**)((u8*)w + o))->buf);
				(*(E**)((u8*)w + o))->buf = NULL;
			}
			BattleFree(*(E**)((u8*)w + o));
			*(E**)((u8*)w + o) = NULL;
		}
	}
	smartFree(w->capture);
	return 2;
}

void zubastar_capture(void) {
	ZubaStarWork* w = GetZubaStarPtr();
	GXSetTexCopySrc(0xd0, 0, 400, 480);
	GXSetTexCopyDst(400, 480, GX_TF_RGB565, GX_FALSE);
	GXCopyTex(*(void**)w->capture, GX_FALSE);
	GXPixModeSync();
}
