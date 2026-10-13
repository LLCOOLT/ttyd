#include "battle/battle_status_icon.h"
#include "battle/battle.h"
#include <string.h>

extern BattleWork* _battleWorkPointer;

typedef struct IconDispTableEntry IconDispTableEntry;
struct IconDispTableEntry {
	s32 id;
	BOOL (*callback)(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry); //0x4
	s32 something;
	s32 something2;
};

IconDispTableEntry _disp_table[0x17] = {
	{1, NULL, 15, 1}
};

//local prototypes
void BattleStatusIconDisp(CameraId camId, void* param);

void BattleStatusIconInit(BattleUnit* unit) {
	memset(&unit->mStatusIconWork, 0, sizeof(BattleWorkStatusIcon));
}

void BattleStatusIconMain(BattleUnit* unit) {
	BattleWorkStatusIcon* icon = &unit->mStatusIconWork;
	BattleWork* work = _battleWorkPointer;
	u32 i;

	icon->mNumStatusIcons = 0;
	if (work->flags & 0x10000 || work->dispFlags & 1) {
		BtlUnit_GetPos(unit, &icon->mPosition.x, &icon->mPosition.y, &icon->mPosition.z);
		icon->mPosition.x += ((f32)(unit->mStatusIconOffset[0]) * unit->mSizeMultiplier);
		icon->mPosition.y += ((f32)(unit->mStatusIconOffset[1]) * unit->mSizeMultiplier);
		icon->mScreenSpaceOffset.x = 13.440001f;
		icon->mScreenSpaceOffset.z = 0.0f;
		icon->mFlags = 0;
		if (!(unit->mAttributeFlags & kCeiling)) {
			icon->mDistanceBetweenIcons = 25.6f;
			icon->mScreenSpaceOffset.y = 19.200001f;
		}
		else {
			icon->mDistanceBetweenIcons = 25.6f;
			icon->mScreenSpaceOffset.y = 0.0f;
		}

		for (i = 0; i < 0x17; i++) {
			IconDispTableEntry* d = (IconDispTableEntry*)((u8*)_disp_table + i * 16);
			BattleWorkStatusIconEntry* e = &icon->mIcons[icon->mNumStatusIcons];
			if (_disp_table[i].id == -1) break;
			if (d->callback(unit, d, e)) {
				icon->mNumStatusIcons++;
			}
		}
		if (icon->mNumStatusIcons > 0) {
			dispEntry(CAMERA_2D, 901.0f, 1, BattleStatusIconDisp, unit);
		}
	}
}

void BattleStatusIconDelete(BattleUnit* unit) {
	; //stubbed in retail
}

#include "battle/battle_disp.h"
#include "driver/icondrv.h"
extern void btlGetScreenPoint(Vec* in, Vec* out);
extern GXColor dat_804221e8, dat_804221ec;

typedef struct BsiDispEntry {
	s32 type; //0x0
	s32 turns; //0x4
	u32 icon; //0x8
	Vec scale; //0xC
	Vec pivot; //0x18
	Vec rot; //0x24
	Vec trans; //0x30
	GXColor color; //0x3C
	s32 flags; //0x40
} BsiDispEntry;

void BattleStatusIconDisp(CameraId camId, void* param) {
	BattleWorkStatusIcon* icon = &((BattleUnit*)param)->mStatusIconWork;
	GXColor col = dat_804221e8;
	Vec screen, p, n;
	Mtx m, trans, scale, npivot, pivot, rx, ry, rz, nm;
	s32 i;
	BsiDispEntry* e;

	btlGetScreenPoint(&icon->mPosition, &screen);
	for (i = icon->mNumStatusIcons - 1; i >= 0; i--) {
		e = (BsiDispEntry*)((u8*)icon + (i * 0x44 + 0x20));
		p = screen;
		p.y += icon->mDistanceBetweenIcons * (f32)i;
		p.y += icon->mScreenSpaceOffset.y;
		p.z += icon->mScreenSpaceOffset.z;
		p.x += icon->mScreenSpaceOffset.x;
		p.z -= (f32)(-(i * 2));
		if (!(e->flags & 1)) {
			if (!(icon->mFlags & 1)) {
				btlDispTexPlane(0x23, col, p.x, p.y, p.z, 0.8f, 0.8f);
			} else {
				btlDispTexPlane(0x23, col, p.x, p.y, p.z, 0.8f, -0.8f);
			}
		}
		if (e->icon == 0) continue;
		if (!(e->flags & 2)) {
			PSMTXTrans(trans, p.x + e->trans.x, p.y + e->trans.y, p.z + e->trans.z);
			PSMTXScale(scale, 0.8f * e->scale.x, 0.8f * e->scale.y, e->scale.z);
			PSMTXTrans(npivot, -e->pivot.x, -e->pivot.y, -e->pivot.z);
			PSMTXTrans(pivot, e->pivot.x, e->pivot.y, e->pivot.z);
			PSMTXRotRad(rx, 'x', 0.017453292f * e->rot.x);
			PSMTXRotRad(ry, 'y', 0.017453292f * e->rot.y);
			PSMTXRotRad(rz, 'z', 0.017453292f * e->rot.z);
			PSMTXIdentity(m);
			PSMTXConcat(rz, scale, m);
			PSMTXConcat(npivot, m, m);
			PSMTXConcat(rz, m, m);
			PSMTXConcat(ry, m, m);
			PSMTXConcat(rx, m, m);
			PSMTXConcat(pivot, m, m);
			PSMTXConcat(trans, m, m);
			btlDispTexPlane2(m, (u32)e->icon, e->color);
		}
		if (e->turns != 0) {
			n = p;
			n.x += 21.6f;
			n.y -= 16.0f;
			PSMTXIdentity(nm);
			PSMTXTrans(trans, n.x, n.y, n.z);
			PSMTXConcat(trans, nm, nm);
			iconNumberDispGx(nm, e->turns, TRUE, dat_804221ec);
		}
	}
}

typedef struct BsiEntry {
	s32 type; //0x0
	s32 turns; //0x4
	s32 icon; //0x8
	Vec v0; //0xC
	Vec v1; //0x18
	Vec v2; //0x24
	Vec v3; //0x30
	u32 color; //0x3C
	s32 flags; //0x40
} BsiEntry;

extern const Vec vec3_803011e8[];
extern u32 dat_804221f0, dat_804221f4, dat_804221f8, dat_804221fc;
#include "system.h"


#define BSI_S(u, o) (*(s16*)((u8*)(u) + (o)))
#define BSI_F(u, o) (*(f32*)((u8*)(u) + (o)))

BOOL _bsi_default_turn(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	const Vec* tbl = vec3_803011e8;
	s32 type = disp->id;
	s8 turns, strength;
	s32 kind;
	if (*(u32*)((u8*)_battleWorkPointer + 0xef4) & 0x10000) {
		if (type != 1 && !BtlUnit_CheckStatus(unit, (s8)disp->id)) return FALSE;
		kind = *(s32*)((u8*)unit + 8);
		if (!((kind >= 1 && kind < 0xd8) || (kind >= 0xde && kind < 0xe0) || (kind >= 0xe0 && kind < 0xe7))) return FALSE;
	} else if (!BtlUnit_CheckStatus(unit, (s8)disp->id)) {
		return FALSE;
	}
	BtlUnit_GetStatus(unit, (s8)type, &turns, &strength);
	entry->type = type;
	entry->turns = turns < 0 ? -turns : turns;
	entry->icon = disp->something;
	entry->v0 = tbl[0];
	entry->v1 = tbl[1];
	entry->v2 = tbl[2];
	entry->color = dat_804221f0;
	entry->flags = disp->something2;
	entry->v3 = tbl[3];
	return TRUE;
}

BOOL _bsi_guruguru(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	const Vec* tbl = vec3_803011e8;
	int type = disp->id;
	s8 turns, strength;
	Vec v;
	if (!BtlUnit_CheckStatus(unit, type)) {
		BSI_F(unit, 0xad4) = 0.0f;
		return FALSE;
	}
	BSI_F(unit, 0xad4) += 4.0f;
	BtlUnit_GetStatus(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = tbl[4];
	entry->v1 = tbl[5];
	v = tbl[6];
	v.z = BSI_F(unit, 0xad4);
	entry->v2 = v;
	entry->color = dat_804221f4;
	entry->flags = disp->something2;
	entry->v3 = tbl[7];
	return TRUE;
}

BOOL _bsi_allergy(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	const Vec* tbl = vec3_803011e8;
	int type = disp->id;
	s8 turns, strength;
	if (!BtlUnit_CheckStatus(unit, type)) {
		BSI_S(unit, 0xada) = 0;
		return FALSE;
	}
	BtlUnit_GetStatus(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = tbl[8];
	entry->v1 = tbl[9];
	entry->v2 = tbl[10];
	entry->color = dat_804221f8;
	entry->flags = disp->something2;
	entry->v3 = tbl[11];
	BSI_S(unit, 0xada)++;
	if (BSI_S(unit, 0xada) & 0x10) entry->flags |= 2;
	return TRUE;
}

BOOL _bsi_biribiri(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	const Vec* tbl = vec3_803011e8;
	s32 type = disp->id;
	s8 turns, strength;
	if (!BtlUnit_CheckStatus(unit, (s8)disp->id)) {
		BSI_S(unit, 0xae0) = 0;
		BSI_S(unit, 0xae2) = 0;
		return FALSE;
	}
	entry->v0 = tbl[12];
	switch (BSI_S(unit, 0xae0)) {
		case 0:
			BSI_S(unit, 0xae0)++;
			BSI_S(unit, 0xae2) = irand(6) + 4;
		case 1:
			entry->v0 = tbl[13];
			BSI_S(unit, 0xae2)--;
			if (BSI_S(unit, 0xae2) < 0) {
				BSI_S(unit, 0xae0)++;
				BSI_S(unit, 0xae2) = irand(100) + 30;
			}
			break;
		case 2:
			entry->v0 = tbl[14];
			BSI_S(unit, 0xae2)--;
			if (BSI_S(unit, 0xae2) < 0) {
				BSI_S(unit, 0xae2) = irand(6) + 4;
				BSI_S(unit, 0xae0) = 1;
			}
			break;
	}
	BtlUnit_GetStatus(unit, (s8)type, &turns, &strength);
	entry->type = type;
	entry->turns = turns < 0 ? -turns : turns;
	entry->icon = disp->something;
	entry->v1 = tbl[15];
	entry->v2 = tbl[16];
	entry->color = dat_804221fc;
	entry->flags = disp->something2;
	entry->v3 = tbl[17];
	return TRUE;
}

extern GXColor dat_80422200, dat_80422204, float_0p10207_80422208, dat_8042220c, dat_80422210;

BOOL _bsi_regeneration(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	const Vec* tbl = vec3_803011e8;
	s32 type = disp->id;
	s16* ctr;
	GXColor c0, c1, col;
	s32 t;
	s8 turns, strength;
	if (type == 0x17) {
		ctr = &BSI_S(unit, 0xadc);
		c0 = dat_80422200;
		c1 = dat_80422204;
	} else if (type == 0x18) {
		ctr = &BSI_S(unit, 0xade);
		c0 = float_0p10207_80422208;
		c1 = dat_8042220c;
	} else {
		return FALSE;
	}
	if (!BtlUnit_CheckStatus(unit, (s8)disp->id)) {
		*ctr = 0;
		return FALSE;
	}
	(*ctr)++; t = (*ctr * 12) % 720;
	if (t >= 360) t = 720 - t;
	BtlUnit_GetStatus(unit, (s8)type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = tbl[18];
	entry->v1 = tbl[19];
	entry->v2 = tbl[20];
	col = dat_80422210;
	col.r = intplGetValue(11, t, 360, c0.r, c1.r);
	col.g = intplGetValue(11, t, 360, c0.g, c1.g);
	col.b = intplGetValue(11, t, 360, c0.b, c1.b);
	*(GXColor*)&entry->color = col;
	entry->flags = disp->something2;
	entry->v3 = tbl[21];
	return TRUE;
}
