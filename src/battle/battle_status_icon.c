#include "version.h"
#pragma optimize_for_size on
#include "battle/battle_status_icon.h"
#include "battle/battle.h"
#include <string.h>
#ifdef VERSION_G8ME01
#include "mario/mariost.h"
#endif

extern BattleWork* _battleWorkPointer;

typedef struct IconDispTableEntry IconDispTableEntry;
struct IconDispTableEntry {
	s32 id;
	BOOL (*callback)(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry); //0x4
	s32 something;
	s32 something2;
};

BOOL _bsi_default_turn(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry);
BOOL _bsi_guruguru(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry);
BOOL _bsi_biribiri(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry);
BOOL _bsi_allergy(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry);
BOOL _bsi_regeneration(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry);

#ifdef VERSION_G8ME01
__declspec(section ".data") u32 fd_bsi_0[2] = {0xBF800000, 0x3F800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_1[2] = {0xBF800000, 0x3F800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_2[2] = {0x3F800000, 0xBF800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_3[2] = {0x3F800000, 0xBF800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_4[2] = {0xBF800000, 0x3F800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_5[2] = {0xBF800000, 0x3F800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_6[2] = {0x3F800000, 0xBF800000}; // MWCC trig-pool pair (+-1.0f)
__declspec(section ".data") u32 fd_bsi_7[2] = {0x3F800000, 0xBF800000}; // MWCC trig-pool pair (+-1.0f)
IconDispTableEntry _disp_table[0x17] = {
		{1, _bsi_default_turn, 22, 1},
		{4, _bsi_default_turn, 20, 1},
		{21, _bsi_default_turn, 21, 1},
		{2, _bsi_default_turn, 23, 1},
		{8, _bsi_default_turn, 24, 1},
		{9, _bsi_default_turn, 25, 1},
		{19, _bsi_default_turn, 26, 1},
		{20, _bsi_default_turn, 27, 1},
		{14, _bsi_default_turn, 28, 1},
		{15, _bsi_default_turn, 29, 1},
		{7, _bsi_default_turn, 41, 1},
		{10, _bsi_default_turn, 42, 1},
		{11, _bsi_default_turn, 43, 1},
		{5, _bsi_default_turn, 44, 1},
		{12, _bsi_default_turn, 45, 1},
		{13, _bsi_default_turn, 46, 1},
		{18, _bsi_default_turn, 47, 1},
		{3, _bsi_guruguru, 39, 0},
		{6, _bsi_biribiri, 38, 0},
		{0, _bsi_allergy, 40, 0},
		{23, _bsi_regeneration, 30, 0},
		{24, _bsi_regeneration, 31, 0},
		{-1, NULL, 0, 0},
};
IconDispTableEntry _disp_table_1[0x17] = {
		{1, _bsi_default_turn, 22, 1},
		{4, _bsi_default_turn, 20, 1},
		{21, _bsi_default_turn, 21, 1},
		{2, _bsi_default_turn, 23, 1},
		{8, _bsi_default_turn, 24, 1},
		{9, _bsi_default_turn, 25, 1},
		{19, _bsi_default_turn, 26, 1},
		{20, _bsi_default_turn, 27, 1},
		{14, _bsi_default_turn, 28, 1},
		{15, _bsi_default_turn, 29, 1},
		{7, _bsi_default_turn, 41, 1},
		{10, _bsi_default_turn, 42, 1},
		{11, _bsi_default_turn, 43, 1},
		{5, _bsi_default_turn, 44, 1},
		{12, _bsi_default_turn, 45, 1},
		{13, _bsi_default_turn, 46, 1},
		{18, _bsi_default_turn, 47, 1},
		{3, _bsi_guruguru, 39, 0},
		{6, _bsi_biribiri, 38, 0},
		{0, _bsi_allergy, 40, 0},
		{23, _bsi_regeneration, 32, 0},
		{24, _bsi_regeneration, 33, 0},
		{-1, NULL, 0, 0},
};
IconDispTableEntry _disp_table_2[0x17] = {
		{1, _bsi_default_turn, 22, 1},
		{4, _bsi_default_turn, 20, 1},
		{21, _bsi_default_turn, 21, 1},
		{2, _bsi_default_turn, 23, 1},
		{8, _bsi_default_turn, 24, 1},
		{9, _bsi_default_turn, 25, 1},
		{19, _bsi_default_turn, 26, 1},
		{20, _bsi_default_turn, 27, 1},
		{14, _bsi_default_turn, 28, 1},
		{15, _bsi_default_turn, 29, 1},
		{7, _bsi_default_turn, 41, 1},
		{10, _bsi_default_turn, 42, 1},
		{11, _bsi_default_turn, 43, 1},
		{5, _bsi_default_turn, 44, 1},
		{12, _bsi_default_turn, 45, 1},
		{13, _bsi_default_turn, 46, 1},
		{18, _bsi_default_turn, 47, 1},
		{3, _bsi_guruguru, 39, 0},
		{6, _bsi_biribiri, 38, 0},
		{0, _bsi_allergy, 40, 0},
		{23, _bsi_regeneration, 34, 0},
		{24, _bsi_regeneration, 35, 0},
		{-1, NULL, 0, 0},
};
IconDispTableEntry _disp_table_3[0x17] = {
		{1, _bsi_default_turn, 22, 1},
		{4, _bsi_default_turn, 20, 1},
		{21, _bsi_default_turn, 21, 1},
		{2, _bsi_default_turn, 23, 1},
		{8, _bsi_default_turn, 24, 1},
		{9, _bsi_default_turn, 25, 1},
		{19, _bsi_default_turn, 26, 1},
		{20, _bsi_default_turn, 27, 1},
		{14, _bsi_default_turn, 28, 1},
		{15, _bsi_default_turn, 29, 1},
		{7, _bsi_default_turn, 41, 1},
		{10, _bsi_default_turn, 42, 1},
		{11, _bsi_default_turn, 43, 1},
		{5, _bsi_default_turn, 44, 1},
		{12, _bsi_default_turn, 45, 1},
		{13, _bsi_default_turn, 46, 1},
		{18, _bsi_default_turn, 47, 1},
		{3, _bsi_guruguru, 39, 0},
		{6, _bsi_biribiri, 38, 0},
		{0, _bsi_allergy, 40, 0},
		{23, _bsi_regeneration, 36, 0},
		{24, _bsi_regeneration, 37, 0},
		{-1, NULL, 0, 0},
};
#else
IconDispTableEntry _disp_table[0x17] = {
	{1, _bsi_default_turn, 15, 1},
	{4, _bsi_default_turn, 13, 1},
	{21, _bsi_default_turn, 14, 1},
	{2, _bsi_default_turn, 16, 1},
	{8, _bsi_default_turn, 17, 1},
	{9, _bsi_default_turn, 18, 1},
	{19, _bsi_default_turn, 19, 1},
	{20, _bsi_default_turn, 20, 1},
	{14, _bsi_default_turn, 21, 1},
	{15, _bsi_default_turn, 22, 1},
	{7, _bsi_default_turn, 28, 1},
	{10, _bsi_default_turn, 29, 1},
	{11, _bsi_default_turn, 30, 1},
	{5, _bsi_default_turn, 31, 1},
	{12, _bsi_default_turn, 32, 1},
	{13, _bsi_default_turn, 33, 1},
	{18, _bsi_default_turn, 34, 1},
	{3, _bsi_guruguru, 26, 0},
	{6, _bsi_biribiri, 25, 0},
	{0, _bsi_allergy, 27, 0},
	{23, _bsi_regeneration, 23, 0},
	{24, _bsi_regeneration, 24, 0},
	{-1, NULL, 0, 0},
};
#endif


__declspec(section ".sdata2") GXColor bsi_disp_color = {0xFF, 0xFF, 0xFF, 0xFF};
__declspec(section ".sdata2") GXColor bsi_turn_num_color = {0xFF, 0xFF, 0xFF, 0xFF};
__declspec(section ".sdata2") GXColor bsi_default_turn_color = {0xFF, 0xFF, 0xFF, 0xFF};
__declspec(section ".sdata2") GXColor bsi_guruguru_color = {0xFF, 0xFF, 0xFF, 0xFF};
__declspec(section ".sdata2") GXColor bsi_allergy_color = {0xFF, 0xFF, 0xFF, 0xFF};
__declspec(section ".sdata2") GXColor bsi_biribiri_color = {0xFF, 0xFF, 0xFF, 0xFF};
__declspec(section ".sdata2") GXColor bsi_hp_regen_color0 = {0xED, 0x14, 0x5B, 0xFF};
__declspec(section ".sdata2") GXColor bsi_hp_regen_color1 = {0xFF, 0xEA, 0x05, 0xFF};
__declspec(section ".sdata2") GXColor float_0p10207_80422208 = {0x3D, 0xD1, 0x09, 0xFF};
__declspec(section ".sdata2") GXColor bsi_fp_regen_color1 = {0x61, 0xE9, 0xE7, 0xFF};
__declspec(section ".sdata2") GXColor bsi_regen_color = {0x00, 0x00, 0x00, 0xFF};

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
#ifdef VERSION_G8ME01
			IconDispTableEntry* d;
			BattleWorkStatusIconEntry* e;
			switch (gp->language) {
				case 2:
					d = &_disp_table_1[i];
					break;
				case 3:
				case 4:
					d = &_disp_table_2[i];
					break;
				case 5:
					d = &_disp_table_3[i];
					break;
				default:
					d = &_disp_table[i];
					break;
			}
#else
			IconDispTableEntry* d = (IconDispTableEntry*)((u8*)_disp_table + i * 16);
#endif
#ifdef VERSION_G8ME01
			e = &icon->mIcons[icon->mNumStatusIcons];
#else
			BattleWorkStatusIconEntry* e = &icon->mIcons[icon->mNumStatusIcons];
#endif
			if (d->id == -1) break;
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

void btlDispTexPlane(u32 id, GXColor color, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY, s32 extra);
void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color, s32 extra);
#include "driver/icondrv.h"
extern void btlGetScreenPoint(Vec* in, Vec* out);

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
	GXColor col = bsi_disp_color;
	Vec screen, p, n;
	Mtx m, trans, scale, npivot, pivot, rx, ry, rz, nm;
	BsiDispEntry* e;
	s32 i;

	btlGetScreenPoint(&icon->mPosition, &screen);
	for (i = icon->mNumStatusIcons - 1; i >= 0; i--) {
		e = (BsiDispEntry*)&icon->mIcons[i];
		p = screen;
		p.y += icon->mDistanceBetweenIcons * (f32)i;
		p.y += icon->mScreenSpaceOffset.y;
		p.x += icon->mScreenSpaceOffset.x;
		p.z += icon->mScreenSpaceOffset.z;
		p.z -= (f32)(-(i * 2));
		if (!(e->flags & 1)) {
			if (!(icon->mFlags & 1)) {
				btlDispTexPlane(VERSION_PICK(0x23, 0x30), col, p.x, p.y, p.z, 0.8f, 0.8f, 0);
			} else {
				btlDispTexPlane(VERSION_PICK(0x23, 0x30), col, p.x, p.y, p.z, 0.8f, -0.8f, 0);
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
			btlDispTexPlane2(m, (u32)e->icon, e->color, 0);
		}
		if (e->turns != 0) {
			n = p;
			n.x += 21.6f;
			n.y -= 16.0f;
			PSMTXIdentity(nm);
			PSMTXTrans(trans, n.x, n.y, n.z);
			PSMTXConcat(trans, nm, nm);
			iconNumberDispGx(nm, e->turns, TRUE, bsi_turn_num_color);
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

#include "system.h"


#define BSI_S(u, o) (*(s16*)((u8*)(u) + BUOFF(o)))
#define BSI_F(u, o) (*(f32*)((u8*)(u) + BUOFF(o)))

BOOL _bsi_default_turn(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	s32 type = disp->id;
	s8 turns, strength;
	s32 kind;
	if (*(u32*)((u8*)_battleWorkPointer + 0xef4) & 0x10000) {
		if (type != 1 && !((BOOL(*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, disp->id)) return FALSE;
		kind = *(s32*)((u8*)unit + 8);
		if (!((kind >= 1 && kind < 0xd8) || (kind >= 0xde && kind < 0xe0) || (kind >= 0xe0 && kind < 0xe7))) return FALSE;
	} else if (!((BOOL(*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, disp->id)) {
		return FALSE;
	}
	((void(*)(BattleUnit*, s8, s8*, s8*))BtlUnit_GetStatus)(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = (Vec){1.0f,1.0f,1.0f};
	entry->v1 = (Vec){0.0f,0.0f,0.0f};
	entry->v2 = (Vec){0.0f,0.0f,0.0f};
	entry->color = *(u32*)&bsi_default_turn_color;
	entry->flags = disp->something2;
	entry->v3 = (Vec){0.0f,0.0f,0.0f};
	return TRUE;
}

BOOL _bsi_guruguru(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	int type = disp->id;
	s8 turns, strength;
	Vec v;
	if (!((BOOL(*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, type)) {
		BSI_F(unit, 0xad4) = 0.0f;
		return FALSE;
	}
	BSI_F(unit, 0xad4) += 4.0f;
	((void(*)(BattleUnit*, s8, s8*, s8*))BtlUnit_GetStatus)(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = (Vec){1.0f,1.0f,1.0f};
	entry->v1 = (Vec){0.0f,0.0f,0.0f};
	v = (Vec){0.0f,0.0f,0.0f};
	v.z = BSI_F(unit, 0xad4);
	entry->v2 = v;
	entry->color = *(u32*)&bsi_guruguru_color;
	entry->flags = disp->something2;
	entry->v3 = (Vec){0.0f,4.0f,0.0f};
	return TRUE;
}

BOOL _bsi_allergy(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	int type = disp->id;
	s8 turns, strength;
	if (!((BOOL(*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, type)) {
		BSI_S(unit, 0xada) = 0;
		return FALSE;
	}
	((void(*)(BattleUnit*, s8, s8*, s8*))BtlUnit_GetStatus)(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = (Vec){1.0f,1.0f,1.0f};
	entry->v1 = (Vec){0.0f,0.0f,0.0f};
	entry->v2 = (Vec){0.0f,0.0f,0.0f};
	entry->color = *(u32*)&bsi_allergy_color;
	entry->flags = disp->something2;
	entry->v3 = (Vec){0.0f,0.0f,0.0f};
	BSI_S(unit, 0xada)++;
	if (BSI_S(unit, 0xada) & 0x10) entry->flags |= 2;
	return TRUE;
}

BOOL _bsi_biribiri(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	s32 type = disp->id;
	s8 turns, strength;
	if (!((BOOL(*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, disp->id)) {
		BSI_S(unit, 0xae0) = 0;
		BSI_S(unit, 0xae2) = 0;
		return FALSE;
	}
	entry->v0 = (Vec){1.0f,1.0f,1.0f};
	switch (BSI_S(unit, 0xae0)) {
		case 0:
			BSI_S(unit, 0xae0)++;
			BSI_S(unit, 0xae2) = irand(6) + 4;
		case 1:
			entry->v0 = (Vec){1.0f,1.0f,1.0f};
			BSI_S(unit, 0xae2)--;
			if (BSI_S(unit, 0xae2) < 0) {
				BSI_S(unit, 0xae0)++;
				BSI_S(unit, 0xae2) = irand(100) + 30;
			}
			break;
		case 2:
			entry->v0 = (Vec){0.8f,0.8f,1.0f};
			BSI_S(unit, 0xae2)--;
			if (BSI_S(unit, 0xae2) < 0) {
				BSI_S(unit, 0xae2) = irand(6) + 4;
				BSI_S(unit, 0xae0) = 1;
			}
			break;
	}
	((void(*)(BattleUnit*, s8, s8*, s8*))BtlUnit_GetStatus)(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v1 = (Vec){0.0f,0.0f,0.0f};
	entry->v2 = (Vec){0.0f,0.0f,0.0f};
	entry->color = *(u32*)&bsi_biribiri_color;
	entry->flags = disp->something2;
	entry->v3 = (Vec){0.0f,0.0f,0.0f};
	return TRUE;
}


BOOL _bsi_regeneration(BattleUnit* unit, IconDispTableEntry* disp, BattleWorkStatusIconEntry* entry_) {
	BsiEntry* entry = (BsiEntry*)entry_;
	s32 type = disp->id;
	s16* ctr;
	GXColor c0, c1, col;
	s32 t;
	s8 turns, strength;
	if (type == 0x17) {
		ctr = &BSI_S(unit, 0xadc);
		c0 = bsi_hp_regen_color0;
		c1 = bsi_hp_regen_color1;
	} else if (type == 0x18) {
		ctr = &BSI_S(unit, 0xade);
		c0 = float_0p10207_80422208;
		c1 = bsi_fp_regen_color1;
	} else {
		return FALSE;
	}
	if (!((BOOL(*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, disp->id)) {
		*ctr = 0;
		return FALSE;
	}
	(*ctr)++; t = (*ctr * 12) % 720;
	if (t >= 360) t = 720 - t;
	((void(*)(BattleUnit*, s8, s8*, s8*))BtlUnit_GetStatus)(unit, type, &turns, &strength);
	entry->type = type;
	entry->turns = turns >= 0 ? turns : -turns;
	entry->icon = disp->something;
	entry->v0 = (Vec){1.0f,1.0f,1.0f};
	entry->v1 = (Vec){0.0f,0.0f,0.0f};
	entry->v2 = (Vec){0.0f,0.0f,0.0f};
	col = bsi_regen_color;
	col.r = intplGetValue(11, t, 360, c0.r, c1.r);
	col.g = intplGetValue(11, t, 360, c0.g, c1.g);
	col.b = intplGetValue(11, t, 360, c0.b, c1.b);
	*(GXColor*)&entry->color = col;
	entry->flags = disp->something2;
	entry->v3 = (Vec){0.0f,0.0f,0.0f};
	return TRUE;
}
