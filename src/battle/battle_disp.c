#pragma optimize_for_size on
#pragma auto_inline off
#include "battle/battle_disp.h"
#include "battle/battle.h"
#include "battle/battle_menu_disp.h"
#include "battle/battle_unit.h"
#include "sdk/texPalette.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "data/item_data.h"
#include "system.h"
#include <string.h>
// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on

f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);

extern ItemData itemDataTable[];
f32 sinfd(f32 degrees);
s32 BtlUnit_EnemyItemCanUseCheck(s32 item);

#define PART_FIELD(p, T, o) (*(T*)((u8*)(p) + (o)))
#define PART_GRAVITY(p) ((p)->gravityTimer)
#define PART_FLOAT(p) ((p)->floatTimer)
#define PART_POSENAME(p) ((p)->poseName)
#define PART_ANIMFLAGS(p) ((p)->animFlags)
#define PART_ANIMSPEED(p) ((p)->animSpeed)
#define PART_ANIMSPEED2(p) ((p)->animSpeed2)
#define PART_POSESTATE(p) ((p)->poseState)
#define PART_POSETYPE(p) ((p)->poseType)
#define PART_POSETIMER(p) ((p)->poseTimer)

extern BattleWork* _battleWorkPointer;

//.sdata
s32 _status_pose_table[] = {
	STATUS_INSTANT_KILL,
	STATUS_STOP,
	STATUS_FREEZE,
	STATUS_SLEEP,
	STATUS_POISON,
	STATUS_CONFUSE,
	STATUS_DIZZY,
	-1
};

//local prototypes
const char* searchPoseTbl(BattleDispPose* table, s32 poseId);
void btlDispGXInit2DSub(void);
void btlDispTexPlaneInit(void);
void btlDispTexPlainGX(u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3);
void btlDispGetTexSize(u32 id, u16* width, u16* height);
void _partsBlurControl(BattleUnitPart* part, s32 flags, Mtx orientation, GXColor color, f32 rotation);
void btlUnitItemDisp(CameraId camId, BattleUnit* unit);
void _pose_def(BattleUnitPart* part);
void _pose_one_pattern(BattleUnitPart* part);
void _pose_two_pattern(BattleUnitPart* part);
void btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, GXColor color);
void _btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, Vec pos2, Vec scale2, GXColor color);
void _btlStockExpDisp(CameraId camId, void* param);

#ifdef NONMATCHING
const char* searchPoseTbl(BattleDispPose* table, s32 poseId) {
	int i;

	if (!table) return NULL;
	for (i = 0; i < 0x1C; i++, table++) {
		if ((s32)table->poseId == poseId || (s32)table->poseId == 0x1C) {
			return table->poseName;
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
void btlDispGXInit2DSub(void) {
	GXSetCullMode(GX_CULL_NONE);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
	GXClearVtxDesc();
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
}
#endif

#ifdef NONMATCHING
void btlDispGXInit2DRasta(void) {
	btlDispGXInit2DSub();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
}
#endif

#ifdef NONMATCHING
void btlDispGXInit2D(void) {
	btlDispGXInit2DSub();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXSetNumTexGens(1);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}
#endif

#ifdef NONMATCHING
void btlDispGXPoint2DRasta(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a) {
	GXPosition3f32(x, y, 0.0f);
	GXColor4u8(r, g, b, a);
}
#endif

#ifdef NONMATCHING
void btlDispGXQuads2DRasta(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	btlDispGXPoint2DRasta(x0, y0, r, g, b, a);
	btlDispGXPoint2DRasta(x1, y0, r, g, b, a);
	btlDispGXPoint2DRasta(x1, y1, r, g, b, a);
	btlDispGXPoint2DRasta(x0, y1, r, g, b, a);
}
#endif

#ifdef NONMATCHING
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t) {
	GXPosition3f32(x, y, 0.0f);
	GXColor4u8(r, g, b, a);
	GXTexCoord2f32(s, t);
}
#endif

#ifdef NONMATCHING
void btlDispGXQuads2D(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	btlDispGXPoint2D(x0, y0, r, g, b, a, 0.0f, 0.0f);
	btlDispGXPoint2D(x1, y0, r, g, b, a, 1.0f, 0.0f);
	btlDispGXPoint2D(x1, y1, r, g, b, a, 1.0f, 1.0f);
	btlDispGXPoint2D(x0, y1, r, g, b, a, 0.0f, 1.0f);
}
#endif
#ifdef NONMATCHING
void btlDispTexPlaneInit(void) {
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetNumTexGens(1);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
}
#endif

#ifdef NONMATCHING
void btlDispTexPlainGX(u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3) {
	GXTexObj texobj;
	f32 x, y;
	
	TEXGetGXTexObjFromPalette(*_battleWorkPointer->menuTex->data, &texobj, id);
	GXLoadTexObj(&texobj, GX_TEXMAP0);
	switch (GXGetTexObjFmt(&texobj)) {
	case GX_TF_I4:
		GXSetNumTevStages(1);
		GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
		GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		break;
	default:
		GXSetNumTevStages(1);
		GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		break;
	}

	x = 0.5f * (f32)GXGetTexObjWidth(&texobj);
	y = 0.5f * (f32)GXGetTexObjHeight(&texobj);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);

	GXPosition3f32(-x, y, 0.0f);
	GXWGFifo.u8 = color0.r; GXWGFifo.u8 = color0.g; GXWGFifo.u8 = color0.b; GXWGFifo.u8 = color0.a;
	GXTexCoord2f32(0.0f, 0.0f);

	GXPosition3f32(x, y, 0.0f);
	GXWGFifo.u8 = color1.r; GXWGFifo.u8 = color1.g; GXWGFifo.u8 = color1.b; GXWGFifo.u8 = color1.a;
	GXTexCoord2f32(1.0f, 0.0f);

	GXPosition3f32(x, -y, 0.0f);
	GXWGFifo.u8 = color2.r; GXWGFifo.u8 = color2.g; GXWGFifo.u8 = color2.b; GXWGFifo.u8 = color2.a;
	GXTexCoord2f32(1.0f, 1.0f);

	GXPosition3f32(-x, -y, 0.0f);
	GXWGFifo.u8 = color3.r; GXWGFifo.u8 = color3.g; GXWGFifo.u8 = color3.b; GXWGFifo.u8 = color3.a;
	GXTexCoord2f32(0.0f, 1.0f);
}
#endif

#ifdef NONMATCHING
void btlDispTexPlane(u32 id, GXColor color, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY) {
	CameraEntry* camera;
	Mtx scale, trans, mtx;

	btlDispTexPlaneInit();
	camera = camGetCurPtr();
	PSMTXScale(scale, sX, sY, 1.0f);
	PSMTXTrans(trans, tX, tY, tZ);
	PSMTXConcat(trans, scale, mtx);
	PSMTXConcat(camera->view, mtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	btlDispTexPlainGX(id, color, color, color, color);
}
#endif

#ifdef NONMATCHING
void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color) {
	CameraEntry* camera;
	Mtx mtx2;

	btlDispTexPlaneInit();
	MTXCopy(mtx, mtx2);
	camera = camGetCurPtr();
	MTXConcat(camera->view, mtx2, mtx2);
	GXLoadPosMtxImm(mtx2, 0);
	btlDispTexPlainGX(id, color, color, color, color);
}
#endif

#ifdef NONMATCHING
void btlDispTexPlane3(Mtx mtx, u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3) {
	CameraEntry* camera;
	Mtx mtx2;

	btlDispTexPlaneInit();
	PSMTXCopy(mtx, mtx2);
	camera = camGetCurPtr();
	PSMTXConcat(camera->view, mtx2, mtx2);
	GXLoadPosMtxImm(mtx2, 0);
	btlDispTexPlainGX(id, color0, color1, color2, color3);
}
#endif

#ifdef NONMATCHING
void btlDispGetTexSize(u32 id, u16* width, u16* height) {
	GXTexObj texobj;

	TEXGetGXTexObjFromPalette(*_battleWorkPointer->menuTex->data, &texobj, id);
	*width = GXGetTexObjWidth(&texobj);
	*height = GXGetTexObjHeight(&texobj);
}
#endif

#ifdef NONMATCHING
void btlDispInit(void) {
	BattleWork* wp = _battleWorkPointer;
	
	battleCameraInit();
	battleMenuDispInit();
	wp->dispFlags |= 2;
}
#endif

#ifdef NONMATCHING
StatusEffectType _GetStatusPoseType(BattleUnit* unit) { //TODO: extsb
	s32* table = _status_pose_table;
	StatusEffectType type;

	if (unit->mAttributeFlags & 0x20000) {
		return STATUS_INSTANT_KILL;
	}
	while (1) {
		type = *table;
		if (*table == -1) break;
		if (((BOOL (*)(BattleUnit*, s8))BtlUnit_CheckStatus)(unit, type)) {
			return type;
		}
		table++;
	}
	return STATUS_INVALID;
}
#endif

#define UNF(u, T, o) (*(T*)((u8*)(u) + (o)))
typedef void (*PartsDispCb)(BattleUnitPart*, s32);
void shadowEntry(f32 x, f32 y, f32 z, f32 s);
void BtlUnit_HpGaugeMain(BattleUnit* unit);
void BtlUnit_ControlPoseSoundMain(BattleUnitPart* part);
BOOL animPoseTestXLU(s32 poseId);
void BattleStageDisp(void);
void BattleCommandDisplay(BattleWork* wp);
void BattleBreakSlot_Disp(void);
void BattleStockExpDisp(void);
void btlDispAnimeSpeed(BattleUnitPart* part, f32 speed);
void gravityOffsetControl(BattleUnitPart* part);
void floatOffsetControl(BattleUnitPart* part);
void statusPoseControl(BattleUnitPart* part);
f32 getGravityDispOffset(BattleUnitPart* part);
f32 getFloatDispOffset(BattleUnitPart* part);
void btlUnitPartsBlurDisp(CameraId camId, BattleUnitPart* part);
void btlUnitItemDisp2(CameraId camId, BattleUnit* unit);
void btlUnitStolenItemDisp(CameraId camId, void* param);
void btlUnitPartsBlurControl(BattleUnitPart* part, s32 unused, Mtx orientation, GXColor color, f32 rotation);
void btlUnitPartsDisp(CameraId camId, BattleUnitPart* part);
StatusEffectType _GetStatusPoseType(BattleUnit* unit);

#ifdef NONMATCHING
void btlDispMain(void) {
	BattleUnit* unit;
	BattleUnitPart* part;
	BattleWork* wp = _battleWorkPointer;
	s32 i;
	const char* poseName;
	BattleUnit* target;
	s32 loop;
	s32 type;
	BattleUnit* partner;
	f32 h;
	f32 scale;
	Vec tpos;
	s32 xlu;
	Vec pos;
	Vec zpos;
	Vec ppos;
	Vec spos;
	Vec vpos;
	Vec viv;
	f32 wx;
	f32 wy;
	f32 wz;
	s8 turns;
	s8 strength;

	for (i = 0; i < 0x40; i++) {
		unit = BattleGetUnitPtr(_battleWorkPointer, i);
		if (!unit) continue;
		if (unit->currentKind == UNIT_SHELL_SHIELD && unit->work[2] != 0) {
			target = BattleGetUnitPtr(wp, unit->work[0]);
			if (target) {
				if (target->attackEventId && evtCheckID(target->attackEventId)) {
					if (!(UNF(target, u32, 0x2A8) & 4)) goto next;
				}
				if (target->damageEventId && evtCheckID(target->damageEventId)) goto next;
				BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
				BtlUnit_GetPos(target, &tpos.x, &tpos.y, &tpos.z);
				tpos.z += 7.0f;
				h = BattleGetFloorHeight(wp, tpos.x, tpos.y, tpos.z);
				switch (unit->work[2]) {
					case 2:
						if (__fabs(pos.x - tpos.x) > 10.0) {
							if (tpos.x > pos.x) {
								pos.x = pos.x + ((tpos.x - pos.x) - 10.0f);
							}
							else {
								pos.x = pos.x - ((pos.x - tpos.x) - 10.0f);
							}
						}
						BtlUnit_SetPos(unit, pos.x, tpos.y, tpos.z);
						break;
					case 3:
						if (__fabs(pos.x - tpos.x) < 1.0) {
							BtlUnit_SetPos(unit, tpos.x, h, tpos.z);
							unit->work[2] = 1;
						}
						else if (tpos.x > pos.x) {
							pos.x += 1.0f;
							BtlUnit_SetPos(unit, pos.x, h, tpos.z);
						}
						else {
							pos.x -= 1.0f;
							BtlUnit_SetPos(unit, pos.x, h, tpos.z);
						}
						break;
					default:
						BtlUnit_SetPos(unit, tpos.x, h, tpos.z);
						break;
				}
			}
		}
next:
		loop = unit->moveColorLvDisp;
		BtlUnit_OffUnitFlag(unit, 2);
		if (loop != unit->mMoveColorLv) {
			BtlUnit_OnUnitFlag(unit, 2);
			if (unit->mMoveColorLv > loop) {
				loop += 12;
				if (loop > unit->mMoveColorLv) loop = unit->mMoveColorLv;
			}
			else {
				loop -= 2;
				if (loop < unit->mMoveColorLv) loop = unit->mMoveColorLv;
			}
		}
		unit->moveColorLvDisp = loop;
		BtlUnit_HpGaugeMain(unit);
		unit->mSizeMultiplier = 1.0f;
		BtlUnit_GetStatus(unit, 0xB, &turns, &strength);
		if (turns > 0 && strength < 0) {
			scale = 0.5f * strength + 1.0f;
			if (scale < 0.5f) scale = 0.5f;
			unit->mSizeMultiplier *= scale;
		}
		BtlUnit_GetStatus(unit, 0xA, &turns, &strength);
		if (turns > 0 && strength > 0) {
			scale = 1.0f + strength;
			if (scale > 2.0f) scale = 2.0f;
			unit->mSizeMultiplier *= scale;
		}
		BattleStatusEffectMain(unit);
		BattleStatusIconMain(unit);

		for (part = unit->mParts; part; part = part->mNextPart) {
			if (part->poseId == -1) continue;
			poseName = PART_POSENAME(part);
			if (!(PART_ANIMFLAGS(part) & 2)) {
				type = _GetStatusPoseType(unit);
				if (unit->currentKind >= 1 && unit->currentKind < 0xD8) {
					poseName = searchPoseTbl(part->poseTable, type);
				}
				else {
					if (type == 0x1C && !BtlUnit_CheckStatus(unit, 0x16) && (unit->mStatusFlags & 0x20000000)) {
						poseName = BtlUnit_GetPoseNameFromType(part, 0x39);
						if (!poseName) poseName = searchPoseTbl(part->poseTable, 0x1C);
					}
					else if (type == 0x1C && !BtlUnit_CheckStatus(unit, 0x16) && (unit->mStatusFlags & 0x10000000)) {
						poseName = BtlUnit_GetPoseNameFromType(part, 0x38);
						if (!poseName) poseName = searchPoseTbl(part->poseTable, 0x1C);
					}
					else {
						poseName = searchPoseTbl(part->poseTable, type);
					}
					if (BtlUnit_CheckStatusFlag(unit, 0x1000000) && BtlUnit_CanActStatus(unit)) {
						poseName = BtlUnit_GetPoseNameFromType(part, 0x2D);
					}
				}
				if (BtlUnit_CheckStatus(unit, 0x13)) {
					btlDispAnimeSpeed(part, 2.0f);
				}
				else if (BtlUnit_CheckStatus(unit, 0x14)) {
					btlDispAnimeSpeed(part, 0.5f);
				}
				else {
					btlDispAnimeSpeed(part, 1.0f);
				}
			}
			else {
				btlDispAnimeSpeed(part, 1.0f);
			}
			if (PART_ANIMFLAGS(part) & 1) {
				xlu = 0;
				PART_ANIMFLAGS(part) &= ~1;
				if (PART_ANIMFLAGS(part) &= ~0x200) {
					animPoseSetAnim(part->poseId, poseName, TRUE);
				}
				else {
					animPoseSetAnim(part->poseId, poseName, FALSE);
				}
				PART_POSESTATE(part) = 0;
				if (PART_ANIMFLAGS(part) & 4) {
					PART_POSETYPE(part) = 0;
				}
				else {
					PART_POSETYPE(part) = 1;
					if (BtlUnit_CheckStatus(unit, 0x12) || part->color.a != 0xFF) {
						PART_POSETYPE(part) = 7;
						xlu = 1;
					}
				}
				if (!(PART_ANIMFLAGS(part) & 2) || (PART_ANIMFLAGS(part) & 8) || (PART_ANIMFLAGS(part) & 0x80)) {
					PART_POSETYPE(part) = 1;
					if (BtlUnit_CheckStatus(unit, 0x12) || part->color.a != 0xFF) {
						PART_POSETYPE(part) = 7;
						xlu = 1;
					}
					if (BtlUnit_CheckStatus(unit, 7)) {
						PART_POSETYPE(part) = 4;
						xlu = 1;
					}
				}
				if (xlu && (part->attributes & 0x8000)) {
					xlu = 0;
					PART_POSETYPE(part) = 0;
				}
				if (!(PART_ANIMFLAGS(part) & 4)) {
					if (xlu && !(PART_ANIMFLAGS(part) & 0x40)) {
						PART_ANIMFLAGS(part) |= 0x40;
					}
					else if (!xlu && (PART_ANIMFLAGS(part) & 0x40)) {
						PART_ANIMFLAGS(part) &= ~0x40;
					}
				}
			}
			gravityOffsetControl(part);
			floatOffsetControl(part);
			statusPoseControl(part);
			BtlUnit_GetPartsWorldPos(part, &wx, &wy, &wz);
			animPoseMain(part->poseId);
			zpos = (Vec){wx, wy, wz + part->dispZOffset};
			part->dispColor.a = part->mKindPartParams->baseAlpha;
			if (BtlUnit_CheckStatus(unit, 0x12) || (unit->mAttributeFlags & 8)) {
				part->dispColor.a = (part->dispColor.a << 7) / 255;
			}
			part->dispColor.a = part->dispColor.a * part->color.a / 255;
			part->dispColor.r = part->color.r;
			part->dispColor.g = part->color.g;
			part->dispColor.b = part->color.b;
			if (!(unit->mAttributeFlags & 0x1000000) && !(part->attributes & 0x1000000)) {
				if (!(part->attributes & 1) || !(unit->mAttributeFlags & 0x10)) {
					if (part->dispColor.a < 0xFF || animPoseTestXLU(part->poseId)) {
						if (!(PART_ANIMFLAGS(part) & 0x100)) {
							dispEntry(CAMERA_3D, dispCalcZ(&zpos), 2, (DispCallback)btlUnitPartsDisp, part);
						}
					}
					else {
						if (!(PART_ANIMFLAGS(part) & 0x100)) {
							dispEntry(CAMERA_3D, dispCalcZ(&zpos), 1, (DispCallback)btlUnitPartsDisp, part);
						}
					}
				}
				if (part->attributes & 0x4000000) {
					dispEntry(CAMERA_3D, wz, 2, (DispCallback)btlUnitPartsBlurDisp, part);
				}
			}
			if (!(unit->mAttributeFlags & 0x20000000) && !(part->attributes & 0x2000000)) {
				BtlUnit_GetPartsWorldPos(part, &ppos.x, &ppos.y, &ppos.z);
				spos = ppos;
				if ((unit->flags & 0x10000) && (partner = BattleGetPartnerPtr(wp, unit)) != NULL) {
					BtlUnit_GetPos(partner, &vpos.x, &vpos.y, &vpos.z);
					spos.x += vpos.x;
					spos.x *= 0.5f;
					spos.y += vpos.y;
					spos.z += vpos.z;
					spos.y *= 0.5f;
					spos.z *= 0.5f;
				}
				spos.y = BattleGetFloorHeight(wp, spos.x, spos.y, spos.z); h = spos.y;
				if (ppos.y <= h) {
					scale = 1.0f;
				}
				else {
					scale = (100.0f - (ppos.y - h)) / 100.0f;
				}
				if (scale > 1.0) scale = 1.0f;
				if (scale < 0.1f) scale = 0.1f;
				scale = scale * ((f32)part->shadowSize * unit->mScale.x * part->mScale.x * unit->mSizeMultiplier) ;
				scale = scale * part->shadowScale;
				if ((unit->flags & 0x10000) && scale < 16.0f) scale = 16.0f;
				if (scale < 10.0f) scale = 8.0f;
				shadowEntry(spos.x, 10.0f + h, spos.z, scale);
			}
			{ s32 k = unit->currentKind;
			if (k == 0xE4 || k == 0x8D || k == 0x86 || (u32)(k - 0x1F) <= 2 || (u32)(k - 0xBD) <= 4 || k == 0x85) {
					viv.x = unit->work[0];
					viv.y = unit->work[1];
					viv.z = unit->work[2];
					animPoseVivianMain(part->poseId, &viv);
			} }
			BtlUnit_ControlPoseSoundMain(part);
		}
		if (unit->heldItem) {
			if ((unit->flags & 0x40000000) && !(unit->flags & 0x8000000)) {
				dispEntry(CAMERA_3D, 0.0f, 2, (DispCallback)btlUnitStolenItemDisp, unit);
			}
			else if ((!(unit->flags & 0x4000000) || (unit->flags & 0x2000000)) && !(unit->flags & 0x8000000)) {
				dispEntry(CAMERA_3D, 0.0f, 2, (DispCallback)btlUnitItemDisp, unit);
			}
		}
		else if (wp->flags & 0x20000) {
			dispEntry(CAMERA_3D, 0.0f, 2, (DispCallback)btlUnitItemDisp2, unit);
		}
	}
	BattleStockExpDisp();
	BattleStageDisp();
	BattleCommandDisplay(wp);
	BattleAudience_Disp();
	BattleBreakSlot_Disp();
	if (wp->flags & 0x10000) wp->flags &= ~0x10000;
	if (wp->flags & 0x20000) wp->flags &= ~0x20000;
}
#endif

#define MTX_TRANS_NEG(m, v) PSMTXTrans(m, -(v).x, -(v).y, -(v).z)
#define MTX_TRANS(m, v) PSMTXTrans(m, (v).x, (v).y, (v).z)
#define CAMDIR(c) angleABf((c)->cameraPos.x, (c)->cameraPos.z, (c)->cameraAt.x, (c)->cameraAt.z)

#ifdef NONMATCHING
void btlUnitPartsDisp(CameraId camId, BattleUnitPart* part) {
	Mtx uMtx;
	Mtx drawMtx;
	Mtx pS2;
	Mtx blurMtx;
	Mtx uM;
	Mtx pPos2;
	Mtx pTN2;
	Mtx pT2;
	Mtx pRx2;
	Mtx pRy2;
	Mtx pRz2;
	Mtx pM;
	Mtx uPos;
	Mtx uDisp;
	Mtx uRx;
	Mtx uRy;
	Mtx uRz;
	Mtx uTN;
	Mtx uT;
	Mtx uS;
	Mtx pPos;
	Mtx pDisp;
	Mtx pRx;
	Mtx pRy;
	Mtx pRz;
	Mtx pTN;
	Mtx pT;
	Mtx pS;
	Mtx mT5;
	BattleWork* wp;
	BattleUnit* unit;
	CameraEntry* cam;
	f32 rotY;
	f32 x, y, z;
	f32 angle;
	f32 dir;
	f32 camAngle;
	f32 a;
	f32 zscale = 1.0f;
	GXColor* color;
	wp = _battleWorkPointer;
	unit = part->mOwner;
	if (part->poseId < 0) return;

	MTX_TRANS_NEG(uTN, unit->mRotationOffset);
	MTX_TRANS(uT, unit->mRotationOffset);
	MTX_TRANS(uDisp, unit->mDisplayOffset);
	MTX_TRANS(uPos, unit->mPosition);
	PSMTXRotRad(uRx, 'x', 0.017453292f * (unit->mRotation.x + unit->mBaseRotation.x));
	PSMTXRotRad(uRy, 'y', 0.017453292f * (unit->mRotation.y + unit->mBaseRotation.y));
	PSMTXRotRad(uRz, 'z', 0.017453292f * (unit->mRotation.z + unit->mBaseRotation.z));
	PSMTXScale(uS, unit->mSizeMultiplier * (unit->mBaseScale.x * unit->mScale.x), unit->mSizeMultiplier * (unit->mBaseScale.y * unit->mScale.y), unit->mBaseScale.z * unit->mScale.z);
	PSMTXIdentity(uM);
	PSMTXConcat(uS, uM, uM);
	PSMTXConcat(uTN, uM, uM);
	PSMTXConcat(uRy, uM, uM);
	PSMTXConcat(uRz, uM, uM);
	PSMTXConcat(uRx, uM, uM);
	PSMTXConcat(uT, uM, uMtx);
	PSMTXConcat(uDisp, uMtx, uMtx);

	angle = 270.0f;
	if (part->attributes & 0x10000000) {
		if (part->faceDirection >= 0) angle = 90.0f;
		x = part->mPosition.x;
		y = part->mPosition.y + getGravityDispOffset(part) + getFloatDispOffset(part);
		z = part->mPosition.z;
		cam = camGetCurPtr();
		a = CAMDIR(cam);
		dir = reviseAngle(a - angleABf(cam->cameraPos.x, cam->cameraPos.z, x, z));
		MTX_TRANS_NEG(pTN2, part->mRotationOffset);
		MTX_TRANS(pT2, part->mRotationOffset);
		PSMTXRotRad(pRx2, 'x', 0.017453292f * (part->mRotation.x + part->mBaseRotation.x));
		PSMTXRotRad(pRy2, 'y', 0.017453292f * (dir + (part->mRotation.y + part->mBaseRotation.y)));
		PSMTXRotRad(pRz2, 'z', 0.017453292f * (part->mRotation.z + part->mBaseRotation.z));
		PSMTXTrans(pPos2, x, y, z);
		rotY = reviseAngle(-1.0f * angle - 90.0f);
		z = reviseAngle(part->mBaseRotation.y + (rotY + part->mRotation.y));
		cam = camGetCurPtr();
		camAngle = CAMDIR(cam);
		a = reviseAngle(z + camAngle);
		if (a >= 90.0f && a <= 270.0f) {
			zscale *= -1.0f;
			PSMTXRotRad(pRy2, 'y', 0.017453292f * ((dir + (part->mRotation.y + part->mBaseRotation.y)) - 2.0f * (180.0f - (a - camAngle))));
		}
		if (part->attributes & 0x8000000) {
			PSMTXScale(pS2, part->mBaseScale.x * part->mScale.x, part->mBaseScale.y * part->mScale.y, zscale * (part->mBaseScale.z * part->mScale.z));
		}
		else {
			PSMTXScale(pS2, unit->mSizeMultiplier * (part->mBaseScale.x * part->mScale.x), unit->mSizeMultiplier * (part->mBaseScale.y * part->mScale.y), zscale * (part->mBaseScale.z * part->mScale.z));
		}
		PSMTXIdentity(pM);
		PSMTXConcat(pS2, pM, pM);
		PSMTXConcat(pTN2, pM, pM);
		PSMTXConcat(pRz2, pM, pM);
		PSMTXConcat(pRx2, pM, pM);
		PSMTXConcat(pRy2, pM, pM);
		PSMTXConcat(pT2, pM, pM);
		PSMTXConcat(pPos2, pM, drawMtx);
		PSMTXCopy(drawMtx, blurMtx);
		PSMTXTrans(mT5, 0.0f, 0.0f, -5.0f);
		PSMTXConcat(mT5, blurMtx, blurMtx);
	}
	else {
		if (unit->faceDirection >= 0) angle = 90.0f;
		dir = part->faceDirection;
		if (dir > 0.0f) {
			dir = 1.0f;
		}
		else if (dir < 0.0f) {
			dir = -1.0f;
		}
		else {
			dir = wp->alliances[unit->mAlliance].attackDirection;
		}
		x = part->mPositionOffset.x * dir + unit->mPosition.x;
		y = unit->mPosition.y + part->mPositionOffset.y + getGravityDispOffset(part) + getFloatDispOffset(part);
		z = unit->mPosition.z + part->mPositionOffset.z;
		dir = 0.0f;
		if (part->mOwner->mAttributeFlags & 0x4000000) {
			cam = camGetCurPtr();
			a = CAMDIR(cam);
			dir = reviseAngle(a - angleABf(cam->cameraPos.x, cam->cameraPos.z, x, z));
		}
		MTX_TRANS_NEG(pTN, part->mRotationOffset);
		MTX_TRANS(pT, part->mRotationOffset);
		PSMTXRotRad(pRx, 'x', 0.017453292f * (part->mRotation.x + part->mBaseRotation.x));
		PSMTXRotRad(pRy, 'y', 0.017453292f * (dir + (part->mRotation.y + part->mBaseRotation.y)));
		PSMTXRotRad(pRz, 'z', 0.017453292f * (part->mRotation.z + part->mBaseRotation.z));
		PSMTXTrans(pPos, x, y, z);
		MTX_TRANS(pDisp, part->mDisplayOffset);
		rotY = reviseAngle(-1.0f * angle - 90.0f);
		if (!(part->mOwner->flags & 0x1000000)) {
			a = reviseAngle(rotY + unit->mRotation.y + part->mRotation.y + unit->mBaseRotation.y + part->mBaseRotation.y);
			cam = camGetCurPtr();
			a = reviseAngle(a + CAMDIR(cam));
			if (a >= 90.0f && a <= 270.0f) {
				PSMTXScale(uS, unit->mSizeMultiplier * (unit->mBaseScale.x * unit->mScale.x), unit->mSizeMultiplier * (unit->mBaseScale.y * unit->mScale.y), -1.0f * (unit->mBaseScale.z * unit->mScale.z));
				PSMTXIdentity(uM);
				PSMTXConcat(uS, uM, uM);
				PSMTXConcat(uTN, uM, uM);
				switch (part->rotationOrder) {
					case 0:
						PSMTXConcat(uRy, uM, uM);
						PSMTXConcat(uRz, uM, uM);
						PSMTXConcat(uRx, uM, uM);
						break;
					case 1:
						PSMTXConcat(uRy, uM, uM);
						PSMTXConcat(uRx, uM, uM);
						PSMTXConcat(uRz, uM, uM);
						break;
					case 2:
						PSMTXConcat(uRx, uM, uM);
						PSMTXConcat(uRy, uM, uM);
						PSMTXConcat(uRz, uM, uM);
						break;
					case 3:
						PSMTXConcat(uRx, uM, uM);
						PSMTXConcat(uRz, uM, uM);
						PSMTXConcat(uRy, uM, uM);
						break;
					case 4:
						PSMTXConcat(uRz, uM, uM);
						PSMTXConcat(uRx, uM, uM);
						PSMTXConcat(uRy, uM, uM);
						break;
					case 5:
						PSMTXConcat(uRz, uM, uM);
						PSMTXConcat(uRy, uM, uM);
						PSMTXConcat(uRx, uM, uM);
						break;
				}
				PSMTXConcat(uT, uM, uMtx);
				PSMTXConcat(uDisp, uMtx, uMtx);
			}
		}
		PSMTXScale(pS, part->mBaseScale.x * part->mScale.x, part->mBaseScale.y * part->mScale.y, zscale * (part->mBaseScale.z * part->mScale.z));
		PSMTXIdentity(uM);
		PSMTXConcat(uMtx, uM, uM);
		PSMTXConcat(pS, uM, uM);
		PSMTXConcat(pTN, uM, uM);
		switch (part->rotationOrder) {
			case 0:
				PSMTXConcat(pRy, uM, uM);
				PSMTXConcat(pRz, uM, uM);
				PSMTXConcat(pRx, uM, uM);
				break;
			case 1:
				PSMTXConcat(pRy, uM, uM);
				PSMTXConcat(pRx, uM, uM);
				PSMTXConcat(pRz, uM, uM);
				break;
			case 2:
				PSMTXConcat(pRx, uM, uM);
				PSMTXConcat(pRy, uM, uM);
				PSMTXConcat(pRz, uM, uM);
				break;
			case 3:
				PSMTXConcat(pRx, uM, uM);
				PSMTXConcat(pRz, uM, uM);
				PSMTXConcat(pRy, uM, uM);
				break;
			case 4:
				PSMTXConcat(pRz, uM, uM);
				PSMTXConcat(pRx, uM, uM);
				PSMTXConcat(pRy, uM, uM);
				break;
			case 5:
				PSMTXConcat(pRz, uM, uM);
				PSMTXConcat(pRy, uM, uM);
				PSMTXConcat(pRx, uM, uM);
				break;
		}
		PSMTXConcat(pT, uM, uM);
		PSMTXConcat(pPos, uM, drawMtx);
		PSMTXConcat(pDisp, drawMtx, drawMtx);
		PSMTXCopy(drawMtx, blurMtx);
		PSMTXTrans(mT5, 0.0f, 0.0f, -5.0f);
		PSMTXConcat(mT5, blurMtx, blurMtx);
	}

	color = &part->drawColor;
	*color = part->dispColor;
	if (PART_ANIMFLAGS(part) & 0x10) {
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	if (PART_ANIMFLAGS(part) & 0x20) {
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	if (color->r == 0xFF && color->g == 0xFF && color->b == 0xFF) {
		if (BtlUnit_CheckStatus(unit, 4)) {
			color->r = color->r * 160 / 255;
			color->b = color->r * 160 / 255;
		}
		color->r = color->r * unit->moveColorLvDisp / 255;
		color->g = color->g * unit->moveColorLvDisp / 255;
		color->b = color->b * unit->moveColorLvDisp / 255;
	}
	animPoseSetMaterialEvtColor(part->poseId, *color);
	animPoseSetMaterialFlagOn(part->poseId, 0x40);
	if (part->dispCallback) {
		part->dispCallback(part, 0);
	}
	if (BtlUnit_CheckStatus(unit, 0x10)) {
		animPoseSetMaterialFlagOn(part->poseId, 0x800000);
	}
	else {
		animPoseSetMaterialFlagOff(part->poseId, 0x800000);
	}
	animPoseDrawMtx(part->poseId, drawMtx, 1, rotY, 2.0f);
	animPoseDrawMtx(part->poseId, drawMtx, 2, rotY, 2.0f);
	animPoseDrawMtx(part->poseId, drawMtx, 3, rotY, 2.0f);
	if (part->dispCallback) {
		part->dispCallback(part, 1);
	}
	btlUnitPartsBlurControl(part, 0, blurMtx, *color, rotY);
}
#endif

#pragma push
#pragma opt_dead_assignments off
#ifdef NONMATCHING
void btlUnitItemDisp(CameraId camId, BattleUnit* unit) {
	BattleWork* wp = _battleWorkPointer;
	s32 item;
	f32 height;
	Vec pos;

	height = BtlUnit_GetHeight(unit);

	item = BtlUnit_EnemyItemCanUseCheck(unit->heldItem);
	if (wp->flags & 0x20000 && !item) {
		item = 0x94;
	}
	if (item) {
		BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
		pos.x += ((Vec*)unit->field_0xB4)->x;
		pos.y += ((Vec*)unit->field_0xB4)->y;
		pos.z += ((Vec*)unit->field_0xB4)->z;
		pos.x += unit->heldItemOffset.x;
		pos.y += unit->heldItemOffset.y;
		pos.z += unit->heldItemOffset.z;
		((void (*)(f32, Vec*, s16, u16))iconDispGx)(1.0f, &pos, 0, itemDataTable[item].icon_id);
	}
}
#endif
#pragma pop

#pragma dont_inline on
#ifdef NONMATCHING
void btlUnitItemDisp2(CameraId camId, BattleUnit* unit) {
	BattleWork* wp = _battleWorkPointer;
	s32 kind = unit->currentKind;

	if (kind >= 1 && kind < 0xD8) goto disp;
	if (kind >= 0xDE && kind < 0xE0) goto disp;
	if (kind < 0xE0 || kind >= 0xE7) return;
disp:
	if (wp->flags & 0x20000) {
		btlUnitItemDisp(camId, unit);
	}
	else {
		wp->flags |= 0x20000;
		btlUnitItemDisp(camId, unit);
		wp->flags &= ~0x20000;
	}
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void btlUnitStolenItemDisp(CameraId camId, void* param) {
	BattleUnit* unit = param;
	Vec pos;
	s32 item = unit->heldItem;

	BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
	pos.y += 5.0f + unit->mSizeMultiplier * (f32)BtlUnit_GetHeight(unit);
	((void (*)(f32, Vec*, s16, u16))iconDispGx)(1.0f, &pos, 0, itemDataTable[item].icon_id);
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void btlUnitPartsBlurControl(BattleUnitPart* part, s32 unused, Mtx orientation, GXColor color, f32 rotation) {

	if (part->attributes & 0x4000000) {
		_partsBlurControl(part, 1, orientation, color, rotation);
	}
	else {
		_partsBlurControl(part, 0, orientation, color, rotation);
	}
}
#endif
#pragma dont_inline reset

//TODO: probably needs Entry* pointer to make offsets relative and then it should match
#ifdef NONMATCHING
void _partsBlurControl(BattleUnitPart* part, s32 flags, Mtx orientation, GXColor color, f32 rotation) {
	BattleWorkUnitPartBlur* blur;
	int i;

	blur = &part->blurWork;
	for (i = 9; i > 0; i--) { //shift all slots forward one
		blur->work[i] = blur->work[i - 1];
	}
	blur->work[0].flags = flags;
	MTXCopy(orientation, blur->work[0].orientation);
	blur->work[0].rotation = rotation;
	blur->work[0].base = color;
	((u32*)blur->work[0].blurColor)[0] = ((u32*)blur->color)[0];
	((u32*)blur->work[0].blurColor)[1] = ((u32*)blur->color)[1];
	if (blur->flags & 1 && blur->work[1].flags & 1) {
		blur->work[0].flags &= ~1;
	}
}
#endif

#ifdef NONMATCHING
void btlUnitPartsBlurDisp(CameraId camId, BattleUnitPart* part) {
	BattleWorkUnitPartBlur* blur;
	BattleWorkUnitPartBlurEntry* entry;
	GXColor color;
	u8* c;
	s32 i;

	blur = &part->blurWork;
	for (i = 0; i < 10; i++) {
		entry = &blur->work[i];
		color = entry->base;
		if (entry->flags & 1) {
			c = (u8*)entry->blurColor;
			color.r = color.r * (u8)((c[0] * (10 - i)) / 10 + (c[4] * i) / 10) / 255;
			color.g = color.g * (u8)((c[1] * (10 - i)) / 10 + (c[5] * i) / 10) / 255;
			color.b = color.b * (u8)((c[2] * (10 - i)) / 10 + (c[6] * i) / 10) / 255;
			color.a = color.a * (u8)((c[3] * (10 - i)) / 10 + (c[7] * i) / 10) / 255;
			if (color.a) {
				animPoseSetMaterialEvtColor(part->poseId, color);
				animPoseSetMaterialFlagOn(part->poseId, 0x40);
				animPoseDrawMtx(part->poseId, entry->orientation, 1, entry->rotation, 2.0f);
				animPoseDrawMtx(part->poseId, entry->orientation, 2, entry->rotation, 2.0f);
				animPoseDrawMtx(part->poseId, entry->orientation, 3, entry->rotation, 2.0f);
			}
		}
	}
}
#endif

#ifdef NONMATCHING
void btlDispEntAnime(BattleUnit* unit) {
	BattleUnitPart* part;
	const char* name;

	for (part = unit->mParts; part; part = part->mNextPart) {
		if (!part->poseTable) {
			part->poseId = -1;
		}
		else {
			name = part->mKindPartParams->modelName;
			if (!name) {
				part->poseId = -1;
			}
			else {
				strcpy(PART_POSENAME(part), searchPoseTbl(part->poseTable, 0x1C));
				part->poseId = animPoseEntry(name, 1);
			}
		}
	}
}
#endif

#ifdef NONMATCHING
void btlDispChangeAnime(BattleUnitPart* part, const char* name, BOOL flag) {
	strcpy(PART_POSENAME(part), name);
	PART_ANIMFLAGS(part) |= 2;
	PART_ANIMFLAGS(part) |= 1;
	PART_ANIMFLAGS(part) &= ~0x80;
	PART_ANIMFLAGS(part) &= ~0x200;
	PART_ANIMFLAGS(part) &= ~0x10;
	if (flag) {
		PART_ANIMFLAGS(part) |= 8;
	}
	else {
		PART_ANIMFLAGS(part) &= ~8;
	}
}
#endif

#ifdef NONMATCHING
void btlDispChangePeraAnime(BattleUnitPart* part, const char* name) {
	PART_ANIMFLAGS(part) |= 4;
	PART_POSETYPE(part) = 0;
	animPoseSetEffectAnim(part->poseId, name, 1);
}
#endif

#ifdef NONMATCHING
void btlDispPoseAnime(BattleUnitPart* part) {
	PART_ANIMFLAGS(part) &= ~0x12;
	PART_ANIMFLAGS(part) |= 1;
	PART_ANIMFLAGS(part) &= ~0x80;
	PART_ANIMFLAGS(part) &= ~0x4;
}
#endif

#ifdef NONMATCHING
void gravityOffsetControl(BattleUnitPart* part) {
	BOOL active = TRUE;
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* unit = part->mOwner;

	if (!(wp->flags & 0x40000000)) {
		active = FALSE;
	}
	else if (unit->mAttributeFlags & 0x1004) {
		active = FALSE;
	}
	if (active) {
		PART_GRAVITY(part)++;
	}
	else if (PART_GRAVITY(part)) {
		PART_GRAVITY(part) %= 120;
		if (PART_GRAVITY(part) >= 60) {
			PART_GRAVITY(part)++;
		}
		else if (PART_GRAVITY(part)) {
			PART_GRAVITY(part)--;
		}
	}
}
#endif

#ifdef NONMATCHING
f32 getGravityDispOffset(BattleUnitPart* part) {
	return 4.0f * sinfd((PART_GRAVITY(part) * 3 + 270) % 360) + 4.0f;
}
#endif

#ifdef NONMATCHING
void floatOffsetControl(BattleUnitPart* part) {
	BOOL active = TRUE;
	BattleUnit* unit = part->mOwner;

	if (!(unit->flags & 0x100000)) {
		active = FALSE;
	}
	else if (!(unit->flags & 0x200000)) {
		active = FALSE;
	}
	else if (BtlUnit_CheckStatus(unit, 0x1B)) {
		active = FALSE;
	}
	if (active) {
		PART_FLOAT(part)++;
	}
	else if (PART_FLOAT(part)) {
		PART_FLOAT(part) %= 90;
		if (PART_FLOAT(part) >= 45) {
			PART_FLOAT(part)++;
		}
		else if (PART_FLOAT(part)) {
			PART_FLOAT(part)--;
		}
	}
}
#endif

#ifdef NONMATCHING
f32 getFloatDispOffset(BattleUnitPart* part) {
	return 2.0f * sinfd((PART_FLOAT(part) * 4 + 270) % 360) + 2.0f;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void statusPoseControl(BattleUnitPart* part) {
	switch (PART_POSETYPE(part)) {
		case 0:
			break;
		case 2:
		case 3:
		case 7:
			_pose_one_pattern(part);
			break;
		case 4:
		case 5:
		case 6:
			_pose_two_pattern(part);
			break;
		default:
			_pose_def(part);
			break;
	}
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void _pose_def(BattleUnitPart* part) {
	switch (PART_POSESTATE(part)) {
		case 0:
			PART_POSESTATE(part) = 1;
			animPoseSetEffect(part->poseId, NULL, 0);
			if (part->mOwner->flags & 0x1000000) {
				animPoseSetMaterialLightFlagOn(part->poseId, 8);
			}
			break;
	}
}
#endif

#ifdef NONMATCHING
void _pose_one_pattern(BattleUnitPart* part) {
	switch (PART_POSESTATE(part)) {
	case 0:
		PART_POSESTATE(part) = 1;
		switch (PART_POSETYPE(part)) {
			case 2:
				animPoseSetEffect(part->poseId, "p_b_st", 1);
				animPoseSetEffectAnim(part->poseId, "PM_C_1A", 1);
				break;
			case 3:
				animPoseSetEffect(part->poseId, "p_b_st", 1);
				animPoseSetEffectAnim(part->poseId, "PM_F_1A", 1);
				break;
			case 7:
				animPoseSetEffect(part->poseId, "p_b_st", 1);
				animPoseSetEffectAnim(part->poseId, "PM_Y_1A", 1);
				break;
		}
		break;
	}
}
#endif

#ifdef NONMATCHING
void _pose_two_pattern(BattleUnitPart* part) {
	switch (PART_POSESTATE(part)) {
		case 0:
			PART_POSESTATE(part) = 1;
			switch (PART_POSETYPE(part)) {
				case 4:
					animPoseSetEffect(part->poseId, "p_b_st", 1);
					animPoseSetEffectAnim(part->poseId, "PM_Y_1B", 1);
					PART_POSETIMER(part) = sysMsec2Frame(2200);
					break;
				case 5:
					animPoseSetEffect(part->poseId, "p_b_st", 1);
					animPoseSetEffectAnim(part->poseId, "PM_C_1A", 1);
					PART_POSETIMER(part) = (irand(4) + 6) * sysMsec2Frame(2200);
					break;
				case 6:
					animPoseSetEffect(part->poseId, "p_b_st", 1);
					animPoseSetEffectAnim(part->poseId, "PM_F_2", 1);
					PART_POSETIMER(part) = (irand(4) + 7) * 22;
					break;
			}
			break;
		case 1:
			switch (PART_POSETYPE(part)) {
				case 4:
					PART_POSETIMER(part)--;
					if (PART_POSETIMER(part) == 0) {
						animPoseSetEffectAnim(part->poseId, "PM_Y_1B", 1);
						PART_POSETIMER(part) = sysMsec2Frame(2200);
					}
					break;
				case 5:
					PART_POSETIMER(part)--;
					if (PART_POSETIMER(part) == 0) {
						PART_POSESTATE(part) = 2;
						animPoseSetEffectAnim(part->poseId, "PM_C_1B", 1);
						PART_POSETIMER(part) = 22;
					}
					break;
				case 6:
					PART_POSETIMER(part)--;
					if (PART_POSETIMER(part) == 0) {
						PART_POSESTATE(part) = 2;
						animPoseSetEffectAnim(part->poseId, "PM_F_1B", 1);
						PART_POSETIMER(part) = 22;
					}
					break;
			}
			break;
		case 2:
			switch (PART_POSETYPE(part)) {
				case 4:
					PART_POSETIMER(part)--;
					if (PART_POSETIMER(part) == 0) {
						PART_POSESTATE(part) = 0;
						_pose_two_pattern(part);
					}
					break;
				case 5:
					PART_POSETIMER(part)--;
					if (PART_POSETIMER(part) == 0) {
						PART_POSESTATE(part) = 0;
						_pose_two_pattern(part);
					}
					break;
				case 6:
					PART_POSETIMER(part)--;
					if (PART_POSETIMER(part) == 0) {
						PART_POSESTATE(part) = 0;
						_pose_two_pattern(part);
					}
					break;
			}
			break;
	}
}
#endif

#pragma push
#pragma opt_dead_assignments off
#ifdef NONMATCHING
void btlDispAnimeSpeed(BattleUnitPart* part, f32 speed) {
	f32 unusedOne = 1.0f;
	PART_ANIMSPEED(part) = speed;
	animPoseSetLocalTimeRate(part->poseId, PART_ANIMSPEED(part) * PART_ANIMSPEED2(part));
}
#endif
#pragma pop

#ifdef NONMATCHING
void btlGetScreenPoint(Vec* in, Vec* out) {
	CameraEntry* camera = camGetPtr(CAMERA_3D);
	Vec v;

	v.x = in->x;
	v.y = in->y;
	v.z = in->z;

	PSMTXMultVec(camera->view, &v, &v);
	PSMTX44MultVec(camera->projection, &v, &v);
	out->x = 304.0f * v.x;
	out->y = 240.0f * v.y;
	out->z = 0.0f;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, GXColor color) {
	u16 width, height;
	f32 hw, hh;
	Vec off;
	Vec unused; unused.x = 0.0f; unused.y = 0.0f; unused.z = 0.0f;

	off.z = 0.0f;

	btlDispGetTexSize(id, &width, &height);
	hw = 0.5f * ((f32)width * scale.x);
	hh = 0.5f * ((f32)height * scale.y);
	off.x = -hw;
	off.y = hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){1.0f, 1.0f, 1.0f}, color);
	off.x = hw;
	off.y = hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){-1.0f, 1.0f, 1.0f}, color);
	off.x = hw;
	off.y = -hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){-1.0f, -1.0f, 1.0f}, color);
	off.x = -hw;
	off.y = -hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){1.0f, -1.0f, 1.0f}, color);
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void _btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, Vec pos2, Vec scale2, GXColor color) {
	Mtx mtx, trans, scl, rotX, rotY, rotZ, trans2, scl2;

	PSMTXIdentity(mtx);
	PSMTXTrans(trans, pos.x, pos.y, pos.z);
	PSMTXTrans(trans2, pos2.x, pos2.y, pos2.z);
	PSMTXScale(scl, scale.x, scale.y, scale.z);
	PSMTXScale(scl2, scale2.x, scale2.y, scale2.z);
	PSMTXRotRad(rotX, 'x', 0.017453292f * rot.x);
	PSMTXRotRad(rotY, 'y', 0.017453292f * rot.y);
	PSMTXRotRad(rotZ, 'z', 0.017453292f * rot.z);
	PSMTXConcat(scl, mtx, mtx);
	PSMTXConcat(scl2, mtx, mtx);
	PSMTXConcat(trans2, mtx, mtx);
	PSMTXConcat(rotZ, mtx, mtx);
	PSMTXConcat(rotX, mtx, mtx);
	PSMTXConcat(rotY, mtx, mtx);
	PSMTXConcat(trans, mtx, mtx);
	((void (*)(Mtx, u32, GXColor, s32))btlDispTexPlane2)(mtx, id, color, 0);
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void BattleStockExpDisp(void) {
	BattleWork* wp = _battleWorkPointer;

	if (wp->stockExp > wp->stockExpDisp) {
		wp->stockExpTimer++;
		if (wp->stockExpTimer >= 4) {
			wp->stockExpDisp++;
		}
	}
	if (wp->dispFlags & 2) {
		dispEntry(CAMERA_2D, 901.0f, 1, _btlStockExpDisp, NULL);
	}
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void _btlStockExpDisp(CameraId camId, void* param) {
	static f32 x;
	static f32 y;
	s32 exp;
	s32 tens;
	s32 ones;
	s32 i;
	s32 n;

	exp = _battleWorkPointer->stockExpDisp;
	if (exp > 0) {
		n = exp;
		if (exp > 100) {
			n = 100;
		}
		tens = n / 10;
		ones = n - tens * 10;
		for (i = 0; i < ones; i++) {
			Vec pos = {0.0f, 0.0f, -100.0f};
			pos.x = 308.0f + x - 3.5f - 13.0f * i;
			pos.y = y - 220.0f;
			iconDispGx(&pos, 0x10, 0x18C, 0.35f);
		}
		for (i = 0; i < tens; i++) {
			Vec pos = {0.0f, 0.0f, -100.0f};
			pos.x = 4.0f + (308.0f + x - 10.0f - 20.0f * i);
			pos.y = 16.0f + (y - 220.0f);
			iconDispGx(&pos, 0x10, 0x18C, 0.5f);
		}
	}
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): searchPoseTbl (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802eddd0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802edddc[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802edde8[3] = { -1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802eddf4[3] = { -1.0f, -1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ede00[3] = { 1.0f, -1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ede0c[3] = { 0.0f, 0.0f, -100.0f };
__declspec(section ".rodata") const f32 vec3_802ede18[3] = { 0.0f, 0.0f, -100.0f };
__declspec(section ".rodata") const f64 double_to_int_802ede28 = 4503601774854144;
__declspec(section ".rodata") const f64 double_to_int_mask_802ede30 = 4503599627370496;
__declspec(section ".rodata") const char str_802EDE38[] = "p_b_st\000";
__declspec(section ".rodata") const char str_802EDE40[] = "PM_Y_1B";
__declspec(section ".rodata") const char str_802EDE48[] = "PM_C_1A";
__declspec(section ".rodata") const char str_802EDE50[] = "PM_F_2\000";
__declspec(section ".rodata") const char str_802EDE58[] = "PM_C_1B";
__declspec(section ".rodata") const char str_802EDE60[] = "PM_F_1B";
__declspec(section ".rodata") const char str_802EDE68[] = "PM_F_1A";
__declspec(section ".rodata") const char str_802EDE70[] = "PM_Y_1A";
__declspec(section ".rodata") const f64 double_10_802ede78 = 10;
__declspec(section ".rodata") const f64 double_1_802ede80 = 1;
#pragma force_active reset
__declspec(section ".sdata2") const f32 float_308_8041bf28 = 308.0f;
__declspec(section ".sdata2") const f32 float_3p5_8041bf2c = 3.5f;
__declspec(section ".sdata2") const f32 float_13_8041bf30 = 13.0f;
__declspec(section ".sdata2") const f32 float_220_8041bf34 = 220.0f;
__declspec(section ".sdata2") const f32 float_0p35_8041bf38 = 0.35f;
__declspec(section ".sdata2") const f32 float_4_8041bf3c = 4.0f;
__declspec(section ".sdata2") const f32 float_10_8041bf40 = 10.0f;
__declspec(section ".sdata2") const f32 float_20_8041bf44 = 20.0f;
__declspec(section ".sdata2") const f32 float_16_8041bf48 = 16.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041bf4c = 0.5f;
__declspec(section ".sdata2") const f32 float_901_8041bf50 = 901.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041bf54 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_0_8041bf58 = 0.0f;
__declspec(section ".sdata2") const f32 float_304_8041bf5c = 304.0f;
__declspec(section ".sdata2") const f32 float_240_8041bf60 = 240.0f;
__declspec(section ".sdata2") const f32 float_1_8041bf64 = 1.0f;
__declspec(section ".sdata2") const f32 float_2_8041bf68 = 2.0f;
__declspec(section ".sdata2") const f32 float_5_8041bf6c = 5.0f;
__declspec(section ".sdata2") const f32 float_270_8041bf70 = 270.0f;
__declspec(section ".sdata2") const f32 float_90_8041bf74 = 90.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041bf78 = -1.0f;
__declspec(section ".sdata2") const f32 float_180_8041bf7c = 180.0f;
__declspec(section ".sdata2") const f32 float_neg5_8041bf80 = -5.0f;
__declspec(section ".sdata2") const f32 float_7_8041bf84 = 7.0f;
__declspec(section ".sdata2") const f32 float_100_8041bf88 = 100.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041bf8c = 0.1f;
__declspec(section ".sdata2") const f32 float_8_8041bf90 = 8.0f;

void BattleAudience_Disp(void);
BattleUnit* BattleGetPartnerPtr(BattleWork* work, BattleUnit* unit);
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
void BattleStatusEffectMain(struct BattleUnit* unit);
void BattleStatusIconMain(struct BattleUnit* unit);
void BtlUnit_CanActStatus();
BOOL BtlUnit_CheckStatus(BattleUnit* unit, StatusEffectType type);
s32 BtlUnit_CheckStatusFlag(BattleUnit* unit, s32 flags);
s32 BtlUnit_GetHeight(BattleUnit* unit);
void BtlUnit_GetPartsWorldPos(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_GetPos(BattleUnit* unit, f32* x, f32* y, f32* z);
char* BtlUnit_GetPoseNameFromType(BattleUnitPart* part, s32 type);
void BtlUnit_GetStatus(BattleUnit* unit, StatusEffectType type, s8* turns, s8* strength);
void BtlUnit_OffUnitFlag(BattleUnit* unit, s32 flags);
void BtlUnit_OnUnitFlag(BattleUnit* unit, s32 flags);
void BtlUnit_SetPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
GXTexFmt GXGetTexObjFmt(const GXTexObj* to);
u16 GXGetTexObjHeight(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetCullMode(GXCullMode mode);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id);
void _restfpr_28();
void _savefpr_28();
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
s32 animPoseEntry(const char* animName, s32 type);
void animPoseMain(s32 poseId);
void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetEffect(s32 poseId, const char* animName, BOOL someflag);
void animPoseSetEffectAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate);
void animPoseSetMaterialEvtColor(s32 poseId, GXColor color);
void animPoseSetMaterialFlagOff(s32 poseId, u32 mask);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask);
void animPoseVivianMain();
void battleCameraInit(void);
void battleMenuDispInit(void);
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t);
void btlDispGXPoint2DRasta(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a);
void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color);
CameraEntry* camGetCurPtr(void);
CameraEntry* camGetPtr(CameraId cameraId);
f32 dispCalcZ(Vec* input);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
BOOL evtCheckID(s32 eventId);
void iconDispGx(Vec* position, s16 flags, u16 iconId, f32 scale);
s32 irand(s32 scalar);
f32 reviseAngle(f32 angle);
char *strcpy(char *dest, const char *src);
s32 sysMsec2Frame(s32 msec);
/* G5 TODO init y$1185 in None */ static u32 g5_y_s1185[1];
/* G5 TODO init x$1184 in None */ static u32 g5_x_s1184[1];
asm void _btlStockExpDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stfd f29, 0x80(r1)
	psq_st f29, 0x88(r1), 0, 0
	stfd f28, 0x70(r1)
	psq_st f28, 0x78(r1), 0, 0
	stfd f27, 0x60(r1)
	psq_st f27, 0x68(r1), 0, 0
	stfd f26, 0x50(r1)
	psq_st f26, 0x58(r1), 0, 0
	stfd f25, 0x40(r1)
	psq_st f25, 0x48(r1), 0, 0
	stmw r27, 0x2c(r1)
	lwz r3, _battleWorkPointer(r13)
	lwz r0, 0xf04(r3)
	cmpwi r0, 0x0
	ble L_g5_1
	cmpwi r0, 0x64
	mr r5, r0
	ble L_g5_2
	li r5, 0x64
	L_g5_2:
	li r0, 0xa
	lis r3, double_to_int_802ede28@ha
	divw r31, r5, r0
	lis r4, vec3_802ede0c@ha
	lfs f29, float_13_8041bf30(r2)
	li r27, 0x0
	lfd f28, double_to_int_802ede28@l(r3)
	addi r30, r4, vec3_802ede0c@l
	mulli r0, r31, 0xa
	lfs f27, float_308_8041bf28(r2)
	lfs f26, float_3p5_8041bf2c(r2)
	lis r29, 0x4330
	lfs f25, float_220_8041bf34(r2)
	subf r28, r0, r5
	b L_g5_3
	L_g5_4:
	xoris r0, r27, 0x8000
	lfs f0, g5_x_s1184(r13)
	stw r0, 0x24(r1)
	addi r3, r1, 0x14
	fadds f1, f27, f0
	lfs f0, g5_y_s1185(r13)
	stw r29, 0x20(r1)
	li r4, 0x10
	lwz r7, 0x0(r30)
	fsubs f0, f0, f25
	lfd f3, 0x20(r1)
	fsubs f2, f1, f26
	lwz r6, 0x4(r30)
	li r5, 0x18c
	fsubs f3, f3, f28
	lwz r0, 0x8(r30)
	stw r6, 0x18(r1)
	lfs f1, float_0p35_8041bf38(r2)
	fnmsubs f2, f29, f3, f2
	stw r7, 0x14(r1)
	stw r0, 0x1c(r1)
	stfs f2, 0x14(r1)
	stfs f0, 0x18(r1)
	bl iconDispGx
	addi r27, r27, 0x1
	L_g5_3:
	cmpw r27, r28
	blt L_g5_4
	lis r3, double_to_int_802ede28@ha
	lis r4, vec3_802ede18@ha
	lfs f25, float_4_8041bf3c(r2)
	addi r29, r4, vec3_802ede18@l
	lfs f26, float_20_8041bf44(r2)
	li r28, 0x0
	lfd f27, double_to_int_802ede28@l(r3)
	lis r30, 0x4330
	lfs f28, float_308_8041bf28(r2)
	lfs f29, float_10_8041bf40(r2)
	lfs f30, float_16_8041bf48(r2)
	lfs f31, float_220_8041bf34(r2)
	b L_g5_5
	L_g5_6:
	xoris r0, r28, 0x8000
	lfs f0, g5_x_s1184(r13)
	stw r0, 0x24(r1)
	addi r3, r1, 0x8
	fadds f1, f28, f0
	lfs f0, g5_y_s1185(r13)
	stw r30, 0x20(r1)
	li r4, 0x10
	fsubs f0, f0, f31
	lwz r6, 0x0(r29)
	lfd f3, 0x20(r1)
	fsubs f2, f1, f29
	lwz r5, 0x4(r29)
	fadds f0, f30, f0
	fsubs f3, f3, f27
	lwz r0, 0x8(r29)
	stw r5, 0xc(r1)
	lfs f1, float_0p5_8041bf4c(r2)
	li r5, 0x18c
	fnmsubs f2, f26, f3, f2
	stw r6, 0x8(r1)
	fadds f2, f25, f2
	stw r0, 0x10(r1)
	stfs f0, 0xc(r1)
	stfs f2, 0x8(r1)
	bl iconDispGx
	addi r28, r28, 0x1
	L_g5_5:
	cmpw r28, r31
	blt L_g5_6
	L_g5_1:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	psq_l f28, 0x78(r1), 0, 0
	lfd f28, 0x70(r1)
	psq_l f27, 0x68(r1), 0, 0
	lfd f27, 0x60(r1)
	psq_l f26, 0x58(r1), 0, 0
	lfd f26, 0x50(r1)
	psq_l f25, 0x48(r1), 0, 0
	lfd f25, 0x40(r1)
	lmw r27, 0x2c(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm void BattleStockExpDisp(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, _battleWorkPointer(r13)
	lwz r3, 0xf00(r4)
	lwz r0, 0xf04(r4)
	cmpw r3, r0
	ble L_g5_1
	lwz r3, 0xf08(r4)
	addi r0, r3, 0x1
	stw r0, 0xf08(r4)
	lwz r0, 0xf08(r4)
	cmpwi r0, 0x4
	blt L_g5_1
	lwz r3, 0xf04(r4)
	addi r0, r3, 0x1
	stw r0, 0xf04(r4)
	L_g5_1:
	lwz r0, 0xef8(r4)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_2
	lis r3, _btlStockExpDisp@ha
	lfs f1, float_901_8041bf50(r2)
	addi r5, r3, _btlStockExpDisp@l
	li r4, 0x1
	li r3, 0x8
	li r6, 0x0
	bl dispEntry
	L_g5_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, Vec pos2, Vec scale2, GXColor color) {
	nofralloc
	stwu r1, -0x1b0(r1)
	mflr r0
	stw r0, 0x1b4(r1)
	stmw r25, 0x194(r1)
	mr r25, r3
	mr r26, r4
	mr r27, r5
	mr r28, r6
	mr r29, r7
	mr r30, r8
	mr r31, r9
	addi r3, r1, 0x15c
	bl PSMTXIdentity
	lfs f1, 0x0(r26)
	addi r3, r1, 0x12c
	lfs f2, 0x4(r26)
	lfs f3, 0x8(r26)
	bl PSMTXTrans
	lfs f1, 0x0(r29)
	addi r3, r1, 0x3c
	lfs f2, 0x4(r29)
	lfs f3, 0x8(r29)
	bl PSMTXTrans
	lfs f1, 0x0(r27)
	addi r3, r1, 0xfc
	lfs f2, 0x4(r27)
	lfs f3, 0x8(r27)
	bl PSMTXScale
	lfs f1, 0x0(r30)
	addi r3, r1, 0xc
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl PSMTXScale
	lfs f1, float_deg2rad_8041bf54(r2)
	addi r3, r1, 0xcc
	lfs f0, 0x0(r28)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_8041bf54(r2)
	addi r3, r1, 0x9c
	lfs f0, 0x4(r28)
	li r4, 0x79
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_8041bf54(r2)
	addi r3, r1, 0x6c
	lfs f0, 0x8(r28)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x15c
	addi r3, r1, 0xfc
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x15c
	addi r3, r1, 0xc
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x15c
	addi r3, r1, 0x3c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x15c
	addi r3, r1, 0x6c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x15c
	addi r3, r1, 0xcc
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x15c
	addi r3, r1, 0x9c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x15c
	addi r3, r1, 0x12c
	mr r5, r4
	bl PSMTXConcat
	lwz r0, 0x0(r31)
	mr r4, r25
	addi r3, r1, 0x15c
	addi r5, r1, 0x8
	stw r0, 0x8(r1)
	li r6, 0x0
	bl btlDispTexPlane2
	lmw r25, 0x194(r1)
	lwz r0, 0x1b4(r1)
	mtlr r0
	addi r1, r1, 0x1b0
	blr
}

asm void btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, GXColor color) {
	nofralloc
	stwu r1, -0x1a0(r1)
	mflr r0
	stw r0, 0x1a4(r1)
	stfd f31, 0x190(r1)
	psq_st f31, 0x198(r1), 0, 0
	stfd f30, 0x180(r1)
	psq_st f30, 0x188(r1), 0, 0
	stfd f29, 0x170(r1)
	psq_st f29, 0x178(r1), 0, 0
	stmw r14, 0x128(r1)
	lfs f0, float_0_8041bf58(r2)
	lis r8, vec3_802eddd0@ha
	mr r27, r4
	mr r28, r5
	stfs f0, 0x114(r1)
	mr r26, r3
	mr r29, r6
	mr r30, r7
	addi r31, r8, vec3_802eddd0@l
	addi r4, r1, 0xa
	addi r5, r1, 0x8
	bl btlDispGetTexSize
	lhz r4, 0xa(r1)
	lis r10, 0x4330
	lhz r0, 0x8(r1)
	mr r3, r26
	stw r4, 0x11c(r1)
	addi r4, r1, 0x100
	lwz r15, 0x0(r30)
	addi r5, r1, 0xf4
	stw r10, 0x118(r1)
	addi r6, r1, 0xe8
	lfd f3, 0x60(r31)
	addi r7, r1, 0xdc
	lfd f0, 0x118(r1)
	addi r8, r1, 0xd0
	stw r0, 0x124(r1)
	addi r9, r1, 0x18
	fsubs f2, f0, f3
	lfs f0, 0x0(r28)
	stw r10, 0x120(r1)
	lfs f4, float_0p5_8041bf4c(r2)
	lfd f1, 0x120(r1)
	fmuls f2, f2, f0
	lfs f0, 0x4(r28)
	fsubs f1, f1, f3
	lwz r16, 0xc(r31)
	fmuls f29, f4, f2
	lwz r17, 0x10(r31)
	lwz r18, 0x14(r31)
	fmuls f0, f1, f0
	fneg f31, f29
	lwz r21, 0x114(r1)
	lwz r22, 0x0(r29)
	fmuls f30, f4, f0
	lwz r23, 0x4(r29)
	stfs f31, 0x10c(r1)
	lwz r24, 0x8(r29)
	stfs f30, 0x110(r1)
	lwz r19, 0x10c(r1)
	lwz r20, 0x110(r1)
	lwz r25, 0x0(r28)
	lwz r12, 0x4(r28)
	lwz r11, 0x8(r28)
	lwz r10, 0x0(r27)
	lwz r0, 0x4(r27)
	lwz r14, 0x8(r27)
	stw r15, 0x18(r1)
	stw r16, 0xd0(r1)
	stw r17, 0xd4(r1)
	stw r18, 0xd8(r1)
	stw r19, 0xdc(r1)
	stw r20, 0xe0(r1)
	stw r21, 0xe4(r1)
	stw r22, 0xe8(r1)
	stw r23, 0xec(r1)
	stw r24, 0xf0(r1)
	stw r25, 0xf4(r1)
	stw r12, 0xf8(r1)
	stw r11, 0xfc(r1)
	stw r10, 0x100(r1)
	stw r0, 0x104(r1)
	stw r14, 0x108(r1)
	bl _btlDispTex4
	stfs f29, 0x10c(r1)
	mr r3, r26
	lwz r24, 0x0(r30)
	addi r4, r1, 0xc4
	stfs f30, 0x110(r1)
	addi r5, r1, 0xb8
	lwz r23, 0x18(r31)
	addi r6, r1, 0xac
	lwz r22, 0x1c(r31)
	addi r7, r1, 0xa0
	lwz r21, 0x20(r31)
	addi r8, r1, 0x94
	lwz r20, 0x10c(r1)
	addi r9, r1, 0x14
	lwz r19, 0x110(r1)
	lwz r18, 0x114(r1)
	lwz r17, 0x0(r29)
	lwz r16, 0x4(r29)
	lwz r15, 0x8(r29)
	lwz r14, 0x0(r28)
	lwz r12, 0x4(r28)
	lwz r11, 0x8(r28)
	lwz r10, 0x0(r27)
	lwz r0, 0x4(r27)
	lwz r25, 0x8(r27)
	stw r24, 0x14(r1)
	stw r23, 0x94(r1)
	stw r22, 0x98(r1)
	stw r21, 0x9c(r1)
	stw r20, 0xa0(r1)
	stw r19, 0xa4(r1)
	stw r18, 0xa8(r1)
	stw r17, 0xac(r1)
	stw r16, 0xb0(r1)
	stw r15, 0xb4(r1)
	stw r14, 0xb8(r1)
	stw r12, 0xbc(r1)
	stw r11, 0xc0(r1)
	stw r10, 0xc4(r1)
	stw r0, 0xc8(r1)
	stw r25, 0xcc(r1)
	bl _btlDispTex4
	fneg f30, f30
	lwz r24, 0x0(r30)
	lwz r23, 0x24(r31)
	mr r3, r26
	lwz r22, 0x28(r31)
	addi r4, r1, 0x88
	stfs f30, 0x110(r1)
	addi r5, r1, 0x7c
	lwz r21, 0x2c(r31)
	addi r6, r1, 0x70
	lwz r19, 0x110(r1)
	addi r7, r1, 0x64
	lwz r17, 0x0(r29)
	addi r8, r1, 0x58
	lwz r16, 0x4(r29)
	addi r9, r1, 0x10
	lwz r15, 0x8(r29)
	lwz r14, 0x0(r28)
	lwz r12, 0x4(r28)
	lwz r11, 0x8(r28)
	lwz r10, 0x0(r27)
	lwz r0, 0x4(r27)
	lwz r25, 0x8(r27)
	stfs f29, 0x10c(r1)
	stw r24, 0x10(r1)
	stw r23, 0x58(r1)
	stw r22, 0x5c(r1)
	stw r21, 0x60(r1)
	stw r20, 0x64(r1)
	stw r19, 0x68(r1)
	stw r18, 0x6c(r1)
	stw r17, 0x70(r1)
	stw r16, 0x74(r1)
	stw r15, 0x78(r1)
	stw r14, 0x7c(r1)
	stw r12, 0x80(r1)
	stw r11, 0x84(r1)
	stw r10, 0x88(r1)
	stw r0, 0x8c(r1)
	stw r25, 0x90(r1)
	bl _btlDispTex4
	stfs f31, 0x10c(r1)
	mr r20, r19
	mr r19, r18
	lwz r25, 0x0(r30)
	lwz r24, 0x30(r31)
	mr r3, r26
	lwz r23, 0x34(r31)
	addi r4, r1, 0x4c
	lwz r22, 0x38(r31)
	addi r5, r1, 0x40
	lwz r21, 0x10c(r1)
	addi r6, r1, 0x34
	lwz r18, 0x0(r29)
	addi r7, r1, 0x28
	lwz r17, 0x4(r29)
	addi r8, r1, 0x1c
	lwz r16, 0x8(r29)
	addi r9, r1, 0xc
	lwz r15, 0x0(r28)
	lwz r14, 0x4(r28)
	lwz r12, 0x8(r28)
	lwz r11, 0x0(r27)
	lwz r10, 0x4(r27)
	lwz r0, 0x8(r27)
	stfs f30, 0x110(r1)
	stw r25, 0xc(r1)
	stw r24, 0x1c(r1)
	stw r23, 0x20(r1)
	stw r22, 0x24(r1)
	stw r21, 0x28(r1)
	stw r20, 0x2c(r1)
	stw r19, 0x30(r1)
	stw r18, 0x34(r1)
	stw r17, 0x38(r1)
	stw r16, 0x3c(r1)
	stw r15, 0x40(r1)
	stw r14, 0x44(r1)
	stw r12, 0x48(r1)
	stw r11, 0x4c(r1)
	stw r10, 0x50(r1)
	stw r0, 0x54(r1)
	bl _btlDispTex4
	psq_l f31, 0x198(r1), 0, 0
	lfd f31, 0x190(r1)
	psq_l f30, 0x188(r1), 0, 0
	lfd f30, 0x180(r1)
	psq_l f29, 0x178(r1), 0, 0
	lfd f29, 0x170(r1)
	lmw r14, 0x128(r1)
	lwz r0, 0x1a4(r1)
	mtlr r0
	addi r1, r1, 0x1a0
	blr
}

asm void btlGetScreenPoint(Vec* in, Vec* out) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r29, 0x24(r1)
	mr r29, r3
	mr r30, r4
	li r3, 0x4
	bl camGetPtr
	lfs f0, 0x0(r29)
	mr r31, r3
	addi r4, r1, 0x8
	stfs f0, 0x8(r1)
	mr r5, r4
	addi r3, r31, 0x11c
	lfs f0, 0x4(r29)
	stfs f0, 0xc(r1)
	lfs f0, 0x8(r29)
	stfs f0, 0x10(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x8
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f1, float_304_8041bf5c(r2)
	lfs f0, 0x8(r1)
	lfs f2, float_240_8041bf60(r2)
	fmuls f1, f1, f0
	lfs f0, float_0_8041bf58(r2)
	stfs f1, 0x0(r30)
	lfs f1, 0xc(r1)
	fmuls f1, f2, f1
	stfs f1, 0x4(r30)
	stfs f0, 0x8(r30)
	lmw r29, 0x24(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void btlDispAnimeSpeed(BattleUnitPart* part, f32 speed) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stfs f1, 0x208(r3)
	lfs f1, 0x208(r3)
	lfs f0, 0x20c(r3)
	lwz r3, 0x1c0(r3)
	fmuls f1, f1, f0
	bl animPoseSetLocalTimeRate
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _pose_two_pattern(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, vec3_802eddd0@ha
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r31, r3
	addi r30, r4, vec3_802eddd0@l
	lbz r0, 0x214(r3)
	cmpwi r0, 0x1
	beq L_g5_1
	bge L_g5_2
	cmpwi r0, 0x0
	bge L_g5_3
	b L_g5_4
	L_g5_2:
	cmpwi r0, 0x3
	bge L_g5_4
	b L_g5_5
	L_g5_3:
	li r0, 0x1
	stb r0, 0x214(r31)
	lbz r0, 0x215(r31)
	cmpwi r0, 0x5
	beq L_g5_6
	bge L_g5_7
	cmpwi r0, 0x4
	bge L_g5_8
	b L_g5_4
	L_g5_7:
	cmpwi r0, 0x7
	bge L_g5_4
	b L_g5_9
	L_g5_8:
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x68
	li r5, 0x1
	bl animPoseSetEffect
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x70
	li r5, 0x1
	bl animPoseSetEffectAnim
	li r3, 0x898
	bl sysMsec2Frame
	sth r3, 0x216(r31)
	b L_g5_4
	L_g5_6:
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x68
	li r5, 0x1
	bl animPoseSetEffect
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x78
	li r5, 0x1
	bl animPoseSetEffectAnim
	li r3, 0x898
	bl sysMsec2Frame
	mr r30, r3
	li r3, 0x4
	bl irand
	addi r0, r3, 0x6
	mullw r0, r0, r30
	sth r0, 0x216(r31)
	b L_g5_4
	L_g5_9:
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x68
	li r5, 0x1
	bl animPoseSetEffect
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x80
	li r5, 0x1
	bl animPoseSetEffectAnim
	li r3, 0x4
	bl irand
	addi r0, r3, 0x7
	mulli r0, r0, 0x16
	sth r0, 0x216(r31)
	b L_g5_4
	L_g5_1:
	lbz r0, 0x215(r31)
	cmpwi r0, 0x5
	beq L_g5_10
	bge L_g5_11
	cmpwi r0, 0x4
	bge L_g5_12
	b L_g5_4
	L_g5_11:
	cmpwi r0, 0x7
	bge L_g5_4
	b L_g5_13
	L_g5_12:
	lhz r3, 0x216(r31)
	subi r0, r3, 0x1
	sth r0, 0x216(r31)
	lhz r0, 0x216(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	lwz r3, 0x1c0(r31)
	addi r4, r30, 0x70
	li r5, 0x1
	bl animPoseSetEffectAnim
	li r3, 0x898
	bl sysMsec2Frame
	sth r3, 0x216(r31)
	b L_g5_4
	L_g5_10:
	lhz r3, 0x216(r31)
	subi r0, r3, 0x1
	sth r0, 0x216(r31)
	lhz r0, 0x216(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	li r0, 0x2
	addi r4, r30, 0x88
	stb r0, 0x214(r31)
	li r5, 0x1
	lwz r3, 0x1c0(r31)
	bl animPoseSetEffectAnim
	li r0, 0x16
	sth r0, 0x216(r31)
	b L_g5_4
	L_g5_13:
	lhz r3, 0x216(r31)
	subi r0, r3, 0x1
	sth r0, 0x216(r31)
	lhz r0, 0x216(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	li r0, 0x2
	addi r4, r30, 0x90
	stb r0, 0x214(r31)
	li r5, 0x1
	lwz r3, 0x1c0(r31)
	bl animPoseSetEffectAnim
	li r0, 0x16
	sth r0, 0x216(r31)
	b L_g5_4
	L_g5_5:
	lbz r0, 0x215(r31)
	cmpwi r0, 0x5
	beq L_g5_14
	bge L_g5_15
	cmpwi r0, 0x4
	bge L_g5_16
	b L_g5_4
	L_g5_15:
	cmpwi r0, 0x7
	bge L_g5_4
	b L_g5_17
	L_g5_16:
	lhz r4, 0x216(r31)
	subi r0, r4, 0x1
	sth r0, 0x216(r31)
	lhz r0, 0x216(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	li r0, 0x0
	stb r0, 0x214(r31)
	bl _pose_two_pattern
	b L_g5_4
	L_g5_14:
	lhz r4, 0x216(r31)
	subi r0, r4, 0x1
	sth r0, 0x216(r31)
	lhz r0, 0x216(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	li r0, 0x0
	stb r0, 0x214(r31)
	bl _pose_two_pattern
	b L_g5_4
	L_g5_17:
	lhz r4, 0x216(r31)
	subi r0, r4, 0x1
	sth r0, 0x216(r31)
	lhz r0, 0x216(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	li r0, 0x0
	stb r0, 0x214(r31)
	bl _pose_two_pattern
	L_g5_4:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _pose_one_pattern(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	lis r3, vec3_802eddd0@ha
	addi r31, r3, vec3_802eddd0@l
	lbz r0, 0x214(r30)
	cmpwi r0, 0x0
	beq L_g5_1
	b L_g5_2
	L_g5_1:
	li r0, 0x1
	stb r0, 0x214(r30)
	lbz r0, 0x215(r30)
	cmpwi r0, 0x3
	beq L_g5_3
	bge L_g5_4
	cmpwi r0, 0x2
	bge L_g5_5
	b L_g5_2
	L_g5_4:
	cmpwi r0, 0x7
	beq L_g5_6
	b L_g5_2
	L_g5_5:
	lwz r3, 0x1c0(r30)
	addi r4, r31, 0x68
	li r5, 0x1
	bl animPoseSetEffect
	lwz r3, 0x1c0(r30)
	addi r4, r31, 0x78
	li r5, 0x1
	bl animPoseSetEffectAnim
	b L_g5_2
	L_g5_3:
	lwz r3, 0x1c0(r30)
	addi r4, r31, 0x68
	li r5, 0x1
	bl animPoseSetEffect
	lwz r3, 0x1c0(r30)
	addi r4, r31, 0x98
	li r5, 0x1
	bl animPoseSetEffectAnim
	b L_g5_2
	L_g5_6:
	lwz r3, 0x1c0(r30)
	addi r4, r31, 0x68
	li r5, 0x1
	bl animPoseSetEffect
	lwz r3, 0x1c0(r30)
	addi r4, r31, 0xa0
	li r5, 0x1
	bl animPoseSetEffectAnim
	L_g5_2:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _pose_def(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lbz r0, 0x214(r3)
	cmpwi r0, 0x0
	beq L_g5_1
	b L_g5_2
	L_g5_1:
	li r0, 0x1
	li r4, 0x0
	stb r0, 0x214(r31)
	li r5, 0x0
	lwz r3, 0x1c0(r31)
	bl animPoseSetEffect
	lwz r3, 0x4ec(r31)
	lwz r0, 0x1c(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq L_g5_2
	lwz r3, 0x1c0(r31)
	li r4, 0x8
	bl animPoseSetMaterialLightFlagOn
	L_g5_2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void statusPoseControl(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lbz r0, 0x215(r3)
	cmpwi r0, 0x4
	bge L_g5_1
	cmpwi r0, 0x1
	beq L_g5_2
	bge L_g5_3
	cmpwi r0, 0x0
	bge L_g5_4
	b L_g5_2
	L_g5_1:
	cmpwi r0, 0x7
	beq L_g5_3
	bge L_g5_2
	b L_g5_5
	L_g5_3:
	bl _pose_one_pattern
	b L_g5_4
	L_g5_5:
	bl _pose_two_pattern
	b L_g5_4
	L_g5_2:
	bl _pose_def
	L_g5_4:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm f32 getFloatDispOffset(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x168
	stw r0, 0x14(r1)
	lis r0, 0x4330
	lhz r5, 0x1a8(r3)
	lis r3, double_to_int_802ede28@ha
	stw r0, 0x8(r1)
	slwi r5, r5, 2
	lfd f1, double_to_int_802ede28@l(r3)
	addi r5, r5, 0x10e
	divw r0, r5, r4
	mullw r0, r0, r4
	subf r0, r0, r5
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f1, f0, f1
	bl sinfd
	lfs f0, float_2_8041bf68(r2)
	lwz r0, 0x14(r1)
	fmadds f1, f0, f1, f0
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void floatOffsetControl(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	li r31, 0x1
	lwz r3, 0x4ec(r3)
	lwz r4, 0x1c(r3)
	rlwinm. r0, r4, 0, 11, 11
	bne L_g5_1
	li r31, 0x0
	b L_g5_2
	L_g5_1:
	rlwinm. r0, r4, 0, 10, 10
	bne L_g5_3
	li r31, 0x0
	b L_g5_2
	L_g5_3:
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_2
	li r31, 0x0
	L_g5_2:
	cmpwi r31, 0x0
	beq L_g5_4
	lhz r3, 0x1a8(r30)
	addi r0, r3, 0x1
	sth r0, 0x1a8(r30)
	b L_g5_5
	L_g5_4:
	lhz r4, 0x1a8(r30)
	cmplwi r4, 0x0
	beq L_g5_5
	li r3, 0x5a
	divw r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	sth r0, 0x1a8(r30)
	lhz r3, 0x1a8(r30)
	cmplwi r3, 0x2d
	blt L_g5_6
	addi r0, r3, 0x1
	sth r0, 0x1a8(r30)
	b L_g5_5
	L_g5_6:
	cmplwi r3, 0x0
	beq L_g5_5
	subi r0, r3, 0x1
	sth r0, 0x1a8(r30)
	L_g5_5:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm f32 getGravityDispOffset(BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x168
	stw r0, 0x14(r1)
	lis r0, 0x4330
	lhz r5, 0x1a6(r3)
	lis r3, double_to_int_802ede28@ha
	lfd f1, double_to_int_802ede28@l(r3)
	mulli r5, r5, 0x3
	stw r0, 0x8(r1)
	addi r3, r5, 0x10e
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f1, f0, f1
	bl sinfd
	lfs f0, float_4_8041bf3c(r2)
	lwz r0, 0x14(r1)
	fmadds f1, f0, f1, f0
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void gravityOffsetControl(BattleUnitPart* part) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	li r5, 0x1
	lwz r6, 0x4ec(r3)
	lwz r0, 0xef4(r4)
	rlwinm. r0, r0, 0, 1, 1
	bne L_g5_1
	li r5, 0x0
	b L_g5_2
	L_g5_1:
	lwz r0, 0x104(r6)
	andi. r0, r0, 0x1004
	beq L_g5_2
	li r5, 0x0
	L_g5_2:
	cmpwi r5, 0x0
	beq L_g5_3
	lhz r4, 0x1a6(r3)
	addi r0, r4, 0x1
	sth r0, 0x1a6(r3)
	blr
	L_g5_3:
	lhz r5, 0x1a6(r3)
	cmplwi r5, 0x0
	beqlr
	li r4, 0x78
	divw r0, r5, r4
	mullw r0, r0, r4
	subf r0, r0, r5
	sth r0, 0x1a6(r3)
	lhz r4, 0x1a6(r3)
	cmplwi r4, 0x3c
	blt L_g5_4
	addi r0, r4, 0x1
	sth r0, 0x1a6(r3)
	blr
	L_g5_4:
	cmplwi r4, 0x0
	beqlr
	subi r0, r4, 0x1
	sth r0, 0x1a6(r3)
	blr
}

asm void btlDispPoseAnime(BattleUnitPart* part) {
	nofralloc
	lwz r4, 0x204(r3)
	li r0, -0x13
	and r0, r4, r0
	stw r0, 0x204(r3)
	lwz r0, 0x204(r3)
	ori r0, r0, 0x1
	stw r0, 0x204(r3)
	lwz r0, 0x204(r3)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x204(r3)
	lwz r0, 0x204(r3)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x204(r3)
	blr
}

asm void btlDispChangePeraAnime(BattleUnitPart* part, const char* name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x1
	stw r0, 0x14(r1)
	li r0, 0x0
	lwz r6, 0x204(r3)
	ori r6, r6, 0x4
	stw r6, 0x204(r3)
	stb r0, 0x215(r3)
	lwz r3, 0x1c0(r3)
	bl animPoseSetEffectAnim
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlDispChangeAnime(BattleUnitPart* part, const char* name, BOOL flag) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	mr r31, r5
	addi r3, r30, 0x1c4
	bl strcpy
	lwz r0, 0x204(r30)
	cmpwi r31, 0x0
	ori r0, r0, 0x2
	stw r0, 0x204(r30)
	lwz r0, 0x204(r30)
	ori r0, r0, 0x1
	stw r0, 0x204(r30)
	lwz r0, 0x204(r30)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x204(r30)
	lwz r0, 0x204(r30)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x204(r30)
	lwz r0, 0x204(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x204(r30)
	beq L_g5_1
	lwz r0, 0x204(r30)
	ori r0, r0, 0x8
	stw r0, 0x204(r30)
	b L_g5_2
	L_g5_1:
	lwz r0, 0x204(r30)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x204(r30)
	L_g5_2:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlDispEntAnime(BattleUnit* unit) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r31, 0x14(r3)
	b L_g5_1
	L_g5_2:
	lwz r3, 0x1bc(r31)
	cmplwi r3, 0x0
	bne L_g5_3
	li r0, -0x1
	stw r0, 0x1c0(r31)
	b L_g5_4
	L_g5_3:
	lwz r4, 0x4(r31)
	lwz r30, 0x8(r4)
	cmplwi r30, 0x0
	bne L_g5_5
	li r0, -0x1
	stw r0, 0x1c0(r31)
	b L_g5_4
	L_g5_5:
	li r4, 0x1c
	bl searchPoseTbl
	mr r4, r3
	addi r3, r31, 0x1c4
	bl strcpy
	mr r3, r30
	li r4, 0x1
	bl animPoseEntry
	stw r3, 0x1c0(r31)
	L_g5_4:
	lwz r31, 0x0(r31)
	L_g5_1:
	cmplwi r31, 0x0
	bne L_g5_2
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlUnitPartsBlurDisp(CameraId camId, BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r22, 0x18(r1)
	mr r28, r4
	li r29, 0x0
	li r27, 0x0
	addi r31, r28, 0x21c
	L_g5_1:
	addi r30, r27, 0xc
	add r30, r31, r30
	lwz r0, 0x0(r30)
	lwz r3, 0x38(r30)
	clrlwi. r0, r0, 31
	stw r3, 0xc(r1)
	beq L_g5_2
	lbz r0, 0x43(r30)
	subfic r22, r29, 0xa
	lbz r6, 0x40(r30)
	li r7, 0xa
	mullw r10, r0, r29
	lbz r0, 0x3c(r30)
	lbz r3, 0x3f(r30)
	li r5, 0xff
	lbz r24, 0x41(r30)
	lbz r25, 0x3e(r30)
	mullw r8, r0, r22
	lbz r26, 0x42(r30)
	lbz r23, 0x3d(r30)
	lbz r9, 0xc(r1)
	lbz r4, 0xd(r1)
	lbz r12, 0xf(r1)
	mullw r6, r6, r29
	lbz r0, 0xe(r1)
	divw r8, r8, r7
	mullw r11, r3, r22
	divw r6, r6, r7
	add r6, r8, r6
	clrlwi r6, r6, 24
	mullw r6, r9, r6
	divw r8, r6, r5
	mullw r3, r23, r22
	stb r8, 0xc(r1)
	mullw r24, r24, r29
	divw r6, r3, r7
	divw r3, r24, r7
	add r3, r6, r3
	clrlwi r3, r3, 24
	mullw r3, r4, r3
	divw r3, r3, r5
	mullw r25, r25, r22
	stb r3, 0xd(r1)
	mullw r26, r26, r29
	divw r11, r11, r7
	divw r10, r10, r7
	add r10, r11, r10
	clrlwi r10, r10, 24
	mullw r10, r12, r10
	divw r11, r10, r5
	divw r4, r25, r7
	stb r11, 0xf(r1)
	clrlwi. r10, r11, 24
	divw r3, r26, r7
	add r3, r4, r3
	clrlwi r3, r3, 24
	mullw r0, r0, r3
	divw r0, r0, r5
	stb r0, 0xe(r1)
	beq L_g5_2
	lwz r0, 0xc(r1)
	addi r4, r1, 0x8
	stw r0, 0x8(r1)
	lwz r3, 0x1c0(r28)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x1c0(r28)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r3, 0x1c0(r28)
	addi r4, r30, 0x4
	lfs f1, 0x34(r30)
	li r5, 0x1
	lfs f2, float_2_8041bf68(r2)
	bl animPoseDrawMtx
	lwz r3, 0x1c0(r28)
	addi r4, r30, 0x4
	lfs f1, 0x34(r30)
	li r5, 0x2
	lfs f2, float_2_8041bf68(r2)
	bl animPoseDrawMtx
	lwz r3, 0x1c0(r28)
	addi r4, r30, 0x4
	lfs f1, 0x34(r30)
	li r5, 0x3
	lfs f2, float_2_8041bf68(r2)
	bl animPoseDrawMtx
	L_g5_2:
	addi r29, r29, 0x1
	addi r27, r27, 0x44
	cmpwi r29, 0xa
	blt L_g5_1
	lmw r22, 0x18(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void _partsBlurControl(BattleUnitPart* part, s32 flags, Mtx orientation, GXColor color, f32 rotation) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	li r10, 0x9
	li r7, 0x8
	stw r0, 0x24(r1)
	stfd f31, 0x18(r1)
	fmr f31, f1
	stmw r30, 0x10(r1)
	addi r31, r3, 0x21c
	mr r30, r6
	li r3, 0x264
	L_g5_1:
	add r6, r31, r3
	addi r9, r6, 0x8
	subi r8, r6, 0x3c
	mtctr r7
	L_g5_2:
	lwz r6, 0x4(r8)
	lwzu r0, 0x8(r8)
	stw r6, 0x4(r9)
	stwu r0, 0x8(r9)
	bdnz L_g5_2
	lwz r0, 0x4(r8)
	subic. r10, r10, 0x1
	subi r3, r3, 0x44
	stw r0, 0x4(r9)
	bgt L_g5_1
	stw r4, 0xc(r31)
	mr r3, r5
	addi r4, r31, 0x10
	bl PSMTXCopy
	stfs f31, 0x40(r31)
	lwz r0, 0x0(r30)
	stw r0, 0x44(r31)
	lwz r0, 0x4(r31)
	stw r0, 0x48(r31)
	lwz r0, 0x8(r31)
	stw r0, 0x4c(r31)
	lwz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq L_g5_3
	lwz r0, 0x50(r31)
	clrlwi. r0, r0, 31
	beq L_g5_3
	lwz r0, 0xc(r31)
	clrrwi r0, r0, 1
	stw r0, 0xc(r31)
	L_g5_3:
	lfd f31, 0x18(r1)
	lmw r30, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void btlUnitPartsBlurControl(BattleUnitPart* part, s32 unused, Mtx orientation, GXColor color, f32 rotation) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r0, 0x1ac(r3)
	rlwinm. r0, r0, 0, 5, 5
	beq L_g5_1
	lwz r0, 0x0(r6)
	addi r6, r1, 0xc
	li r4, 0x1
	stw r0, 0xc(r1)
	bl _partsBlurControl
	b L_g5_2
	L_g5_1:
	lwz r0, 0x0(r6)
	addi r6, r1, 0x8
	li r4, 0x0
	stw r0, 0x8(r1)
	bl _partsBlurControl
	L_g5_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlUnitStolenItemDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	addi r5, r1, 0xc
	addi r6, r1, 0x10
	stmw r30, 0x28(r1)
	mr r31, r4
	addi r4, r1, 0x8
	mr r3, r31
	lwz r30, 0x304(r31)
	bl BtlUnit_GetPos
	mr r3, r31
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x1c(r1)
	lis r4, double_to_int_802ede28@ha
	lfd f1, double_to_int_802ede28@l(r4)
	lis r3, itemDataTable@ha
	stw r0, 0x18(r1)
	addi r4, r3, itemDataTable@l
	mulli r0, r30, 0x28
	lfs f3, 0x114(r31)
	lfd f0, 0x18(r1)
	addi r3, r1, 0x8
	lfs f2, float_5_8041bf6c(r2)
	fsubs f4, f0, f1
	add r5, r4, r0
	lfs f0, 0xc(r1)
	lfs f1, float_1_8041bf64(r2)
	li r4, 0x0
	fmadds f2, f3, f4, f2
	lhz r5, 0x20(r5)
	fadds f0, f0, f2
	stfs f0, 0xc(r1)
	bl iconDispGx
	lmw r30, 0x28(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void btlUnitItemDisp2(CameraId camId, BattleUnit* unit) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r0, 0x8(r4)
	lwz r31, _battleWorkPointer(r13)
	cmpwi r0, 0x1
	blt L_g5_1
	cmpwi r0, 0xd8
	blt L_g5_2
	L_g5_1:
	cmpwi r0, 0xde
	blt L_g5_3
	cmpwi r0, 0xe0
	blt L_g5_2
	L_g5_3:
	cmpwi r0, 0xe0
	blt L_g5_4
	cmpwi r0, 0xe7
	blt L_g5_2
	b L_g5_4
	L_g5_2:
	lwz r5, 0xef4(r31)
	rlwinm. r0, r5, 0, 14, 14
	beq L_g5_5
	bl btlUnitItemDisp
	b L_g5_4
	L_g5_5:
	oris r0, r5, 0x2
	stw r0, 0xef4(r31)
	bl btlUnitItemDisp
	lwz r0, 0xef4(r31)
	rlwinm r0, r0, 0, 15, 13
	stw r0, 0xef4(r31)
	L_g5_4:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlUnitItemDisp(CameraId camId, BattleUnit* unit) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r30, 0x28(r1)
	mr r30, r4
	mr r3, r30
	lwz r31, _battleWorkPointer(r13)
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x1c(r1)
	lwz r3, 0x304(r30)
	stw r0, 0x18(r1)
	bl BtlUnit_EnemyItemCanUseCheck
	lwz r0, 0xef4(r31)
	mr r31, r3
	rlwinm. r0, r0, 0, 14, 14
	beq L_g5_1
	cmpwi r31, 0x0
	bne L_g5_1
	li r31, 0x94
	L_g5_1:
	cmpwi r31, 0x0
	beq L_g5_2
	addi r5, r1, 0xc
	addi r6, r1, 0x10
	mr r3, r30
	addi r4, r1, 0x8
	bl BtlUnit_GetPos
	lfs f1, 0x8(r1)
	lis r3, itemDataTable@ha
	lfs f0, 0xb4(r30)
	mulli r0, r31, 0x28
	addi r3, r3, itemDataTable@l
	lfs f3, 0xc(r1)
	fadds f4, f1, f0
	lfs f2, 0x10(r1)
	add r4, r3, r0
	lfs f1, float_1_8041bf64(r2)
	addi r3, r1, 0x8
	stfs f4, 0x8(r1)
	lhz r5, 0x20(r4)
	li r4, 0x0
	lfs f0, 0xb8(r30)
	fadds f3, f3, f0
	stfs f3, 0xc(r1)
	lfs f0, 0xbc(r30)
	fadds f2, f2, f0
	stfs f2, 0x10(r1)
	lfs f0, 0xc0(r30)
	fadds f0, f4, f0
	stfs f0, 0x8(r1)
	lfs f0, 0xc4(r30)
	fadds f0, f3, f0
	stfs f0, 0xc(r1)
	lfs f0, 0xc8(r30)
	fadds f0, f2, f0
	stfs f0, 0x10(r1)
	bl iconDispGx
	L_g5_2:
	lmw r30, 0x28(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void btlUnitPartsDisp(CameraId camId, BattleUnitPart* part) {
	nofralloc
	stwu r1, -0x600(r1)
	mflr r0
	stw r0, 0x604(r1)
	stfd f31, 0x5f0(r1)
	psq_st f31, 0x5f8(r1), 0, 0
	stfd f30, 0x5e0(r1)
	psq_st f30, 0x5e8(r1), 0, 0
	stfd f29, 0x5d0(r1)
	psq_st f29, 0x5d8(r1), 0, 0
	stfd f28, 0x5c0(r1)
	psq_st f28, 0x5c8(r1), 0, 0
	stfd f27, 0x5b0(r1)
	psq_st f27, 0x5b8(r1), 0, 0
	stfd f26, 0x5a0(r1)
	psq_st f26, 0x5a8(r1), 0, 0
	stmw r29, 0x594(r1)
	lwz r0, 0x1c0(r4)
	mr r30, r4
	lwz r31, _battleWorkPointer(r13)
	cmpwi r0, 0x0
	lfs f26, float_1_8041bf64(r2)
	lwz r29, 0x4ec(r4)
	blt L_g5_1
	lfs f1, 0x78(r29)
	addi r3, r1, 0x220
	lfs f2, 0x7c(r29)
	lfs f0, 0x80(r29)
	fneg f1, f1
	fneg f2, f2
	fneg f3, f0
	bl PSMTXTrans
	lfs f1, 0x78(r29)
	addi r3, r1, 0x1f0
	lfs f2, 0x7c(r29)
	lfs f3, 0x80(r29)
	bl PSMTXTrans
	lfs f1, 0x54(r29)
	addi r3, r1, 0x2e0
	lfs f2, 0x58(r29)
	lfs f3, 0x5c(r29)
	bl PSMTXTrans
	lfs f1, 0x3c(r29)
	addi r3, r1, 0x310
	lfs f2, 0x40(r29)
	lfs f3, 0x44(r29)
	bl PSMTXTrans
	lfs f1, 0x6c(r29)
	addi r3, r1, 0x2b0
	lfs f0, 0x60(r29)
	li r4, 0x78
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f1, 0x70(r29)
	addi r3, r1, 0x280
	lfs f0, 0x64(r29)
	li r4, 0x79
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f1, 0x74(r29)
	addi r3, r1, 0x250
	lfs f0, 0x68(r29)
	li r4, 0x7a
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f3, 0x9c(r29)
	addi r3, r1, 0x1c0
	lfs f2, 0x90(r29)
	lfs f1, 0xa0(r29)
	lfs f0, 0x94(r29)
	fmuls f4, f3, f2
	lfs f5, 0x114(r29)
	fmuls f2, f1, f0
	lfs f3, 0xa4(r29)
	lfs f0, 0x98(r29)
	fmuls f1, f5, f4
	fmuls f2, f5, f2
	fmuls f3, f3, f0
	bl PSMTXScale
	addi r3, r1, 0x490
	bl PSMTXIdentity
	addi r4, r1, 0x490
	addi r3, r1, 0x1c0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x220
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x1f0
	addi r4, r1, 0x490
	addi r5, r1, 0x550
	bl PSMTXConcat
	addi r4, r1, 0x550
	addi r3, r1, 0x2e0
	mr r5, r4
	bl PSMTXConcat
	lwz r0, 0x1ac(r30)
	lfs f27, float_270_8041bf70(r2)
	rlwinm. r0, r0, 0, 3, 3
	beq L_g5_2
	lbz r0, 0xbd(r30)
	extsb. r0, r0
	blt L_g5_3
	lfs f27, float_90_8041bf74(r2)
	L_g5_3:
	lfs f29, 0x18(r30)
	mr r3, r30
	bl getFloatDispOffset
	fmr f30, f1
	mr r3, r30
	bl getGravityDispOffset
	lfs f0, 0x1c(r30)
	lfs f28, 0x20(r30)
	fadds f0, f0, f1
	fadds f30, f0, f30
	bl camGetCurPtr
	mr r31, r3
	lfs f1, 0xc(r3)
	lfs f2, 0x14(r3)
	lfs f3, 0x18(r3)
	lfs f4, 0x20(r3)
	bl angleABf
	fmr f31, f1
	lfs f1, 0xc(r31)
	fmr f3, f29
	lfs f2, 0x14(r31)
	fmr f4, f28
	bl angleABf
	fsubs f1, f31, f1
	bl reviseAngle
	lfs f2, 0x58(r30)
	fmr f31, f1
	lfs f1, 0x54(r30)
	addi r3, r1, 0x430
	lfs f0, 0x5c(r30)
	fneg f2, f2
	fneg f1, f1
	fneg f3, f0
	bl PSMTXTrans
	lfs f1, 0x54(r30)
	addi r3, r1, 0x400
	lfs f2, 0x58(r30)
	lfs f3, 0x5c(r30)
	bl PSMTXTrans
	lfs f1, 0x48(r30)
	addi r3, r1, 0x3d0
	lfs f0, 0x3c(r30)
	li r4, 0x78
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f1, 0x4c(r30)
	addi r3, r1, 0x3a0
	lfs f0, 0x40(r30)
	li r4, 0x79
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fadds f0, f31, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f1, 0x50(r30)
	addi r3, r1, 0x370
	lfs f0, 0x44(r30)
	li r4, 0x7a
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	fmr f1, f29
	addi r3, r1, 0x460
	fmr f2, f30
	fmr f3, f28
	bl PSMTXTrans
	lfs f1, float_neg1_8041bf78(r2)
	lfs f0, float_90_8041bf74(r2)
	fmsubs f1, f1, f27, f0
	bl reviseAngle
	fmr f30, f1
	lfs f0, 0x4c(r30)
	lfs f2, 0x40(r30)
	fadds f0, f30, f0
	fadds f1, f2, f0
	bl reviseAngle
	fmr f28, f1
	bl camGetCurPtr
	lfs f1, 0xc(r3)
	lfs f2, 0x14(r3)
	lfs f3, 0x18(r3)
	lfs f4, 0x20(r3)
	bl angleABf
	fmr f27, f1
	fadds f1, f28, f27
	bl reviseAngle
	lfs f0, float_90_8041bf74(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_g5_4
	lfs f0, float_270_8041bf70(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne L_g5_4
	lfs f2, 0x4c(r30)
	fsubs f1, f1, f27
	lfs f0, 0x40(r30)
	addi r3, r1, 0x3a0
	lfs f3, float_180_8041bf7c(r2)
	li r4, 0x79
	fadds f0, f2, f0
	lfs f4, float_neg1_8041bf78(r2)
	fsubs f1, f3, f1
	lfs f2, float_2_8041bf68(r2)
	fadds f0, f31, f0
	lfs f3, float_deg2rad_8041bf54(r2)
	fmuls f26, f26, f4
	fnmsubs f0, f2, f1, f0
	fmuls f1, f3, f0
	bl PSMTXRotRad
	L_g5_4:
	lwz r0, 0x1ac(r30)
	rlwinm. r0, r0, 0, 4, 4
	beq L_g5_5
	lfs f1, 0x74(r30)
	addi r3, r1, 0x4f0
	lfs f0, 0x68(r30)
	lfs f3, 0x6c(r30)
	fmuls f0, f1, f0
	lfs f1, 0x60(r30)
	lfs f4, 0x70(r30)
	lfs f2, 0x64(r30)
	fmuls f1, f3, f1
	fmuls f3, f26, f0
	fmuls f2, f4, f2
	bl PSMTXScale
	b L_g5_6
	L_g5_5:
	lfs f3, 0x6c(r30)
	addi r3, r1, 0x4f0
	lfs f2, 0x60(r30)
	lfs f1, 0x70(r30)
	lfs f0, 0x64(r30)
	fmuls f4, f3, f2
	lfs f5, 0x114(r29)
	fmuls f3, f1, f0
	lfs f2, 0x74(r30)
	lfs f0, 0x68(r30)
	fmuls f1, f5, f4
	fmuls f0, f2, f0
	fmuls f2, f5, f3
	fmuls f3, f26, f0
	bl PSMTXScale
	L_g5_6:
	addi r3, r1, 0x340
	bl PSMTXIdentity
	addi r4, r1, 0x340
	addi r3, r1, 0x4f0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x340
	addi r3, r1, 0x430
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x340
	addi r3, r1, 0x370
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x340
	addi r3, r1, 0x3d0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x340
	addi r3, r1, 0x3a0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x340
	addi r3, r1, 0x400
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x460
	addi r4, r1, 0x340
	addi r5, r1, 0x520
	bl PSMTXConcat
	addi r3, r1, 0x520
	addi r4, r1, 0x4c0
	bl PSMTXCopy
	lfs f1, float_0_8041bf58(r2)
	addi r3, r1, 0x10
	lfs f3, float_neg5_8041bf80(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r4, r1, 0x4c0
	addi r3, r1, 0x10
	mr r5, r4
	bl PSMTXConcat
	b L_g5_7
	L_g5_2:
	lbz r0, 0x185(r29)
	extsb. r0, r0
	blt L_g5_8
	lfs f27, float_90_8041bf74(r2)
	L_g5_8:
	lbz r0, 0xbd(r30)
	lis r3, 0x4330
	lis r4, double_to_int_802ede28@ha
	stw r3, 0x580(r1)
	extsb r0, r0
	lfd f2, double_to_int_802ede28@l(r4)
	xoris r0, r0, 0x8000
	lfs f0, float_0_8041bf58(r2)
	stw r0, 0x584(r1)
	lfd f1, 0x580(r1)
	fsubs f1, f1, f2
	fcmpo cr0, f1, f0
	ble L_g5_9
	lfs f2, float_1_8041bf64(r2)
	b L_g5_10
	L_g5_9:
	bge L_g5_11
	lfs f2, float_neg1_8041bf78(r2)
	b L_g5_10
	L_g5_11:
	lbz r0, 0xc(r29)
	stw r3, 0x580(r1)
	extsb r0, r0
	slwi r0, r0, 3
	add r3, r31, r0
	lbz r0, 0xa(r3)
	extsb r0, r0
	xoris r0, r0, 0x8000
	stw r0, 0x584(r1)
	lfd f0, 0x580(r1)
	fsubs f2, f0, f2
	L_g5_10:
	lfs f1, 0x24(r30)
	mr r3, r30
	lfs f0, 0x3c(r29)
	fmadds f30, f1, f2, f0
	bl getFloatDispOffset
	fmr f26, f1
	mr r3, r30
	bl getGravityDispOffset
	lfs f2, 0x40(r29)
	lfs f0, 0x28(r30)
	lwz r3, 0x4ec(r30)
	fadds f3, f2, f0
	lfs f2, 0x44(r29)
	lwz r0, 0x104(r3)
	lfs f0, 0x2c(r30)
	fadds f1, f3, f1
	rlwinm. r0, r0, 0, 5, 5
	fadds f29, f2, f0
	lfs f28, float_0_8041bf58(r2)
	fadds f31, f1, f26
	beq L_g5_12
	bl camGetCurPtr
	mr r31, r3
	lfs f1, 0xc(r3)
	lfs f2, 0x14(r3)
	lfs f3, 0x18(r3)
	lfs f4, 0x20(r3)
	bl angleABf
	fmr f26, f1
	lfs f1, 0xc(r31)
	fmr f3, f30
	lfs f2, 0x14(r31)
	fmr f4, f29
	bl angleABf
	fsubs f1, f26, f1
	bl reviseAngle
	fmr f28, f1
	L_g5_12:
	lfs f1, 0x54(r30)
	addi r3, r1, 0xa0
	lfs f2, 0x58(r30)
	lfs f0, 0x5c(r30)
	fneg f1, f1
	fneg f2, f2
	fneg f3, f0
	bl PSMTXTrans
	lfs f1, 0x54(r30)
	addi r3, r1, 0x70
	lfs f2, 0x58(r30)
	lfs f3, 0x5c(r30)
	bl PSMTXTrans
	lfs f1, 0x48(r30)
	addi r3, r1, 0x130
	lfs f0, 0x3c(r30)
	li r4, 0x78
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f1, 0x4c(r30)
	addi r3, r1, 0x100
	lfs f0, 0x40(r30)
	li r4, 0x79
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fadds f0, f28, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	lfs f1, 0x50(r30)
	addi r3, r1, 0xd0
	lfs f0, 0x44(r30)
	li r4, 0x7a
	lfs f2, float_deg2rad_8041bf54(r2)
	fadds f0, f1, f0
	fmuls f1, f2, f0
	bl PSMTXRotRad
	fmr f1, f30
	addi r3, r1, 0x190
	fmr f2, f31
	fmr f3, f29
	bl PSMTXTrans
	lfs f1, 0x30(r30)
	addi r3, r1, 0x160
	lfs f2, 0x34(r30)
	lfs f3, 0x38(r30)
	bl PSMTXTrans
	lfs f1, float_neg1_8041bf78(r2)
	lfs f0, float_90_8041bf74(r2)
	fmsubs f1, f1, f27, f0
	bl reviseAngle
	lwz r3, 0x4ec(r30)
	fmr f30, f1
	lwz r0, 0x1c(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne L_g5_13
	lfs f0, 0x70(r29)
	lfs f1, 0x4c(r30)
	fadds f0, f30, f0
	lfs f2, 0x64(r29)
	lfs f3, 0x40(r30)
	fadds f0, f1, f0
	fadds f0, f2, f0
	fadds f1, f3, f0
	bl reviseAngle
	fmr f26, f1
	bl camGetCurPtr
	lfs f1, 0xc(r3)
	lfs f2, 0x14(r3)
	lfs f3, 0x18(r3)
	lfs f4, 0x20(r3)
	bl angleABf
	fadds f1, f26, f1
	bl reviseAngle
	lfs f0, float_90_8041bf74(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_g5_13
	lfs f0, float_270_8041bf70(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne L_g5_13
	lfs f3, 0x9c(r29)
	addi r3, r1, 0x1c0
	lfs f2, 0x90(r29)
	lfs f1, 0xa0(r29)
	lfs f0, 0x94(r29)
	fmuls f3, f3, f2
	lfs f5, 0x114(r29)
	fmuls f4, f1, f0
	lfs f2, 0xa4(r29)
	lfs f0, 0x98(r29)
	fmuls f1, f5, f3
	lfs f3, float_neg1_8041bf78(r2)
	fmuls f0, f2, f0
	fmuls f2, f5, f4
	fmuls f3, f3, f0
	bl PSMTXScale
	addi r3, r1, 0x490
	bl PSMTXIdentity
	addi r4, r1, 0x490
	addi r3, r1, 0x1c0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x220
	mr r5, r4
	bl PSMTXConcat
	lbz r0, 0x4fc(r30)
	extsb r0, r0
	cmpwi r0, 0x3
	beq L_g5_14
	bge L_g5_15
	cmpwi r0, 0x1
	beq L_g5_16
	bge L_g5_17
	cmpwi r0, 0x0
	bge L_g5_18
	b L_g5_19
	L_g5_15:
	cmpwi r0, 0x5
	beq L_g5_20
	bge L_g5_19
	b L_g5_21
	L_g5_18:
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	b L_g5_19
	L_g5_16:
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	b L_g5_19
	L_g5_17:
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	b L_g5_19
	L_g5_14:
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	b L_g5_19
	L_g5_21:
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	b L_g5_19
	L_g5_20:
	addi r4, r1, 0x490
	addi r3, r1, 0x250
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x280
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x2b0
	mr r5, r4
	bl PSMTXConcat
	L_g5_19:
	addi r3, r1, 0x1f0
	addi r4, r1, 0x490
	addi r5, r1, 0x550
	bl PSMTXConcat
	addi r4, r1, 0x550
	addi r3, r1, 0x2e0
	mr r5, r4
	bl PSMTXConcat
	L_g5_13:
	lfs f1, 0x74(r30)
	addi r3, r1, 0x40
	lfs f0, 0x68(r30)
	lfs f4, 0x6c(r30)
	lfs f3, 0x60(r30)
	fmuls f0, f1, f0
	lfs f2, float_1_8041bf64(r2)
	lfs f5, 0x70(r30)
	fmuls f1, f4, f3
	lfs f4, 0x64(r30)
	fmuls f3, f2, f0
	fmuls f2, f5, f4
	bl PSMTXScale
	addi r3, r1, 0x490
	bl PSMTXIdentity
	addi r4, r1, 0x490
	addi r3, r1, 0x550
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x40
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0xa0
	mr r5, r4
	bl PSMTXConcat
	lbz r0, 0x4fc(r30)
	extsb r0, r0
	cmpwi r0, 0x3
	beq L_g5_22
	bge L_g5_23
	cmpwi r0, 0x1
	beq L_g5_24
	bge L_g5_25
	cmpwi r0, 0x0
	bge L_g5_26
	b L_g5_27
	L_g5_23:
	cmpwi r0, 0x5
	beq L_g5_28
	bge L_g5_27
	b L_g5_29
	L_g5_26:
	addi r4, r1, 0x490
	addi r3, r1, 0x100
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0xd0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x130
	mr r5, r4
	bl PSMTXConcat
	b L_g5_27
	L_g5_24:
	addi r4, r1, 0x490
	addi r3, r1, 0x100
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x130
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0xd0
	mr r5, r4
	bl PSMTXConcat
	b L_g5_27
	L_g5_25:
	addi r4, r1, 0x490
	addi r3, r1, 0x130
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x100
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0xd0
	mr r5, r4
	bl PSMTXConcat
	b L_g5_27
	L_g5_22:
	addi r4, r1, 0x490
	addi r3, r1, 0x130
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0xd0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x100
	mr r5, r4
	bl PSMTXConcat
	b L_g5_27
	L_g5_29:
	addi r4, r1, 0x490
	addi r3, r1, 0xd0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x130
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x100
	mr r5, r4
	bl PSMTXConcat
	b L_g5_27
	L_g5_28:
	addi r4, r1, 0x490
	addi r3, r1, 0xd0
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x100
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x490
	addi r3, r1, 0x130
	mr r5, r4
	bl PSMTXConcat
	L_g5_27:
	addi r4, r1, 0x490
	addi r3, r1, 0x70
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x190
	addi r4, r1, 0x490
	addi r5, r1, 0x520
	bl PSMTXConcat
	addi r4, r1, 0x520
	addi r3, r1, 0x160
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x520
	addi r4, r1, 0x4c0
	bl PSMTXCopy
	lfs f1, float_0_8041bf58(r2)
	addi r3, r1, 0x10
	lfs f3, float_neg5_8041bf80(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r4, r1, 0x4c0
	addi r3, r1, 0x10
	mr r5, r4
	bl PSMTXConcat
	L_g5_7:
	lwz r0, 0x4f4(r30)
	stw r0, 0x218(r30)
	lwz r0, 0x204(r30)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_30
	li r0, 0x0
	stb r0, 0x218(r30)
	stb r0, 0x219(r30)
	stb r0, 0x21a(r30)
	L_g5_30:
	lwz r0, 0x204(r30)
	rlwinm. r0, r0, 0, 26, 26
	beq L_g5_31
	li r0, 0x0
	stb r0, 0x218(r30)
	stb r0, 0x219(r30)
	stb r0, 0x21a(r30)
	L_g5_31:
	lbz r0, 0x218(r30)
	cmplwi r0, 0xff
	bne L_g5_32
	lbz r0, 0x219(r30)
	cmplwi r0, 0xff
	bne L_g5_32
	lbz r0, 0x21a(r30)
	cmplwi r0, 0xff
	bne L_g5_32
	mr r3, r29
	li r4, 0x4
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_33
	lbz r0, 0x218(r30)
	li r3, 0xff
	mulli r0, r0, 0xa0
	divw r0, r0, r3
	stb r0, 0x218(r30)
	lbz r0, 0x218(r30)
	mulli r0, r0, 0xa0
	divw r0, r0, r3
	stb r0, 0x21a(r30)
	L_g5_33:
	lbz r3, 0x218(r30)
	li r4, 0xff
	lbz r0, 0x30e(r29)
	mullw r0, r3, r0
	divw r0, r0, r4
	stb r0, 0x218(r30)
	lbz r3, 0x219(r30)
	lbz r0, 0x30e(r29)
	mullw r0, r3, r0
	divw r0, r0, r4
	stb r0, 0x219(r30)
	lbz r3, 0x21a(r30)
	lbz r0, 0x30e(r29)
	mullw r0, r3, r0
	divw r0, r0, r4
	stb r0, 0x21a(r30)
	L_g5_32:
	lwz r0, 0x218(r30)
	addi r4, r1, 0xc
	stw r0, 0xc(r1)
	lwz r3, 0x1c0(r30)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x1c0(r30)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r12, 0x210(r30)
	cmplwi r12, 0x0
	beq L_g5_34
	mr r3, r30
	li r4, 0x0
	mtctr r12
	bctrl
	L_g5_34:
	mr r3, r29
	li r4, 0x10
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_35
	lwz r3, 0x1c0(r30)
	lis r4, 0x80
	bl animPoseSetMaterialFlagOn
	b L_g5_36
	L_g5_35:
	lwz r3, 0x1c0(r30)
	lis r4, 0x80
	bl animPoseSetMaterialFlagOff
	L_g5_36:
	fmr f1, f30
	lwz r3, 0x1c0(r30)
	lfs f2, float_2_8041bf68(r2)
	addi r4, r1, 0x520
	li r5, 0x1
	bl animPoseDrawMtx
	fmr f1, f30
	lwz r3, 0x1c0(r30)
	lfs f2, float_2_8041bf68(r2)
	addi r4, r1, 0x520
	li r5, 0x2
	bl animPoseDrawMtx
	fmr f1, f30
	lwz r3, 0x1c0(r30)
	lfs f2, float_2_8041bf68(r2)
	addi r4, r1, 0x520
	li r5, 0x3
	bl animPoseDrawMtx
	lwz r12, 0x210(r30)
	cmplwi r12, 0x0
	beq L_g5_37
	mr r3, r30
	li r4, 0x1
	mtctr r12
	bctrl
	L_g5_37:
	lwz r0, 0x218(r30)
	fmr f1, f30
	mr r3, r30
	addi r5, r1, 0x4c0
	stw r0, 0x8(r1)
	addi r6, r1, 0x8
	li r4, 0x0
	bl btlUnitPartsBlurControl
	L_g5_1:
	psq_l f31, 0x5f8(r1), 0, 0
	lfd f31, 0x5f0(r1)
	psq_l f30, 0x5e8(r1), 0, 0
	lfd f30, 0x5e0(r1)
	psq_l f29, 0x5d8(r1), 0, 0
	lfd f29, 0x5d0(r1)
	psq_l f28, 0x5c8(r1), 0, 0
	lfd f28, 0x5c0(r1)
	psq_l f27, 0x5b8(r1), 0, 0
	lfd f27, 0x5b0(r1)
	psq_l f26, 0x5a8(r1), 0, 0
	lfd f26, 0x5a0(r1)
	lmw r29, 0x594(r1)
	lwz r0, 0x604(r1)
	mtlr r0
	addi r1, r1, 0x600
	blr
}

asm void btlDispMain(void) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	lis r3, vec3_802eddd0@ha
	stw r0, 0xd4(r1)
	stmw r17, 0x94(r1)
	addi r28, r3, vec3_802eddd0@l
	addi r17, r1, 0x68
	addi r18, r1, 0x64
	addi r21, r1, 0x74
	addi r22, r1, 0x70
	addi r23, r1, 0x50
	addi r24, r1, 0x4c
	addi r25, r1, 0x38
	addi r26, r1, 0x34
	li r27, 0x0
	lwz r29, _battleWorkPointer(r13)
	L_g5_1:
	lwz r3, _battleWorkPointer(r13)
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_2
	lwz r0, 0x8(r31)
	cmpwi r0, 0xdf
	bne L_g5_3
	lwz r0, 0x21c(r31)
	cmpwi r0, 0x0
	beq L_g5_3
	lwz r4, 0x214(r31)
	mr r3, r29
	bl BattleGetUnitPtr
	mr. r19, r3
	beq L_g5_3
	lwz r3, 0x2a4(r19)
	cmpwi r3, 0x0
	beq L_g5_4
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_4
	lwz r0, 0x2a8(r19)
	rlwinm. r0, r0, 0, 29, 29
	beq L_g5_3
	L_g5_4:
	lwz r3, 0x2b0(r19)
	cmpwi r3, 0x0
	beq L_g5_5
	bl evtCheckID
	cmpwi r3, 0x0
	bne L_g5_3
	L_g5_5:
	mr r3, r31
	mr r5, r18
	mr r6, r17
	addi r4, r1, 0x60
	bl BtlUnit_GetPos
	mr r3, r19
	mr r5, r22
	mr r6, r21
	addi r4, r1, 0x6c
	bl BtlUnit_GetPos
	lfs f2, 0x74(r1)
	mr r3, r29
	lfs f0, float_7_8041bf84(r2)
	lfs f1, 0x6c(r1)
	fadds f3, f2, f0
	lfs f2, 0x70(r1)
	stfs f3, 0x74(r1)
	bl BattleGetFloorHeight
	lwz r0, 0x21c(r31)
	fmr f2, f1
	cmpwi r0, 0x3
	beq L_g5_6
	bge L_g5_7
	cmpwi r0, 0x2
	bge L_g5_8
	b L_g5_7
	L_g5_8:
	lfs f3, 0x60(r1)
	lfs f2, 0x6c(r1)
	lfd f0, 0xa8(r28)
	fsubs f1, f3, f2
	fabs f4, f1
	fcmpo cr0, f4, f0
	ble L_g5_9
	fcmpo cr0, f2, f3
	ble L_g5_10
	fsubs f1, f2, f3
	lfs f0, float_10_8041bf40(r2)
	fsubs f0, f1, f0
	fadds f0, f3, f0
	stfs f0, 0x60(r1)
	b L_g5_9
	L_g5_10:
	lfs f0, float_10_8041bf40(r2)
	fsubs f0, f1, f0
	fsubs f0, f3, f0
	stfs f0, 0x60(r1)
	L_g5_9:
	lfs f1, 0x60(r1)
	mr r3, r31
	lfs f2, 0x70(r1)
	lfs f3, 0x74(r1)
	bl BtlUnit_SetPos
	b L_g5_3
	L_g5_6:
	lfs f4, 0x60(r1)
	lfs f1, 0x6c(r1)
	lfd f0, 0xb0(r28)
	fsubs f3, f4, f1
	fabs f3, f3
	fcmpo cr0, f3, f0
	bge L_g5_11
	lfs f3, 0x74(r1)
	mr r3, r31
	bl BtlUnit_SetPos
	li r0, 0x1
	stw r0, 0x21c(r31)
	b L_g5_3
	L_g5_11:
	fcmpo cr0, f1, f4
	ble L_g5_12
	lfs f0, float_1_8041bf64(r2)
	mr r3, r31
	lfs f3, 0x74(r1)
	fadds f1, f4, f0
	stfs f1, 0x60(r1)
	bl BtlUnit_SetPos
	b L_g5_3
	L_g5_12:
	lfs f0, float_1_8041bf64(r2)
	mr r3, r31
	lfs f3, 0x74(r1)
	fsubs f1, f4, f0
	stfs f1, 0x60(r1)
	bl BtlUnit_SetPos
	b L_g5_3
	L_g5_7:
	lfs f1, 0x6c(r1)
	mr r3, r31
	lfs f3, 0x74(r1)
	bl BtlUnit_SetPos
	L_g5_3:
	lbz r19, 0x30e(r31)
	mr r3, r31
	li r4, 0x2
	bl BtlUnit_OffUnitFlag
	lbz r0, 0x30d(r31)
	cmpw r19, r0
	beq L_g5_13
	mr r3, r31
	li r4, 0x2
	bl BtlUnit_OnUnitFlag
	lbz r0, 0x30d(r31)
	cmpw r0, r19
	ble L_g5_14
	addi r19, r19, 0xc
	cmpw r19, r0
	ble L_g5_13
	mr r19, r0
	b L_g5_13
	L_g5_14:
	subi r19, r19, 0x2
	cmpw r19, r0
	bge L_g5_13
	mr r19, r0
	L_g5_13:
	stb r19, 0x30e(r31)
	mr r3, r31
	bl BtlUnit_HpGaugeMain
	lfs f0, float_1_8041bf64(r2)
	mr r3, r31
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	stfs f0, 0x114(r31)
	li r4, 0xb
	bl BtlUnit_GetStatus
	lbz r0, 0x9(r1)
	extsb. r0, r0
	ble L_g5_15
	lbz r3, 0x8(r1)
	extsb. r0, r3
	bge L_g5_15
	extsb r3, r3
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	stw r0, 0x78(r1)
	lfd f2, 0x58(r28)
	stw r3, 0x7c(r1)
	lfs f3, float_0p5_8041bf4c(r2)
	lfd f1, 0x78(r1)
	lfs f0, float_1_8041bf64(r2)
	fsubs f1, f1, f2
	fmadds f1, f3, f1, f0
	fcmpo cr0, f1, f3
	bge L_g5_16
	fmr f1, f3
	L_g5_16:
	lfs f0, 0x114(r31)
	fmuls f0, f0, f1
	stfs f0, 0x114(r31)
	L_g5_15:
	mr r3, r31
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	li r4, 0xa
	bl BtlUnit_GetStatus
	lbz r0, 0x9(r1)
	extsb. r0, r0
	ble L_g5_17
	lbz r3, 0x8(r1)
	extsb. r0, r3
	ble L_g5_17
	extsb r3, r3
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	stw r0, 0x78(r1)
	lfd f2, 0x58(r28)
	stw r3, 0x7c(r1)
	lfs f3, float_1_8041bf64(r2)
	lfd f1, 0x78(r1)
	lfs f0, float_2_8041bf68(r2)
	fsubs f1, f1, f2
	fadds f1, f3, f1
	fcmpo cr0, f1, f0
	ble L_g5_18
	fmr f1, f0
	L_g5_18:
	lfs f0, 0x114(r31)
	fmuls f0, f0, f1
	stfs f0, 0x114(r31)
	L_g5_17:
	mr r3, r31
	bl BattleStatusEffectMain
	mr r3, r31
	bl BattleStatusIconMain
	lwz r30, 0x14(r31)
	b L_g5_19
	L_g5_20:
	lwz r0, 0x1c0(r30)
	cmpwi r0, -0x1
	beq L_g5_21
	lwz r0, 0x204(r30)
	addi r20, r30, 0x1c4
	rlwinm. r0, r0, 0, 30, 30
	bne L_g5_22
	mr r3, r31
	bl _GetStatusPoseType
	lwz r0, 0x8(r31)
	mr r19, r3
	cmpwi r0, 0x1
	blt L_g5_23
	cmpwi r0, 0xd8
	bge L_g5_23
	lwz r3, 0x1bc(r30)
	mr r4, r19
	bl searchPoseTbl
	mr r20, r3
	b L_g5_24
	L_g5_23:
	cmpwi r19, 0x1c
	bne L_g5_25
	mr r3, r31
	li r4, 0x16
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_25
	lwz r0, 0x138(r31)
	rlwinm. r0, r0, 0, 2, 2
	beq L_g5_25
	mr r3, r30
	li r4, 0x39
	bl BtlUnit_GetPoseNameFromType
	mr. r20, r3
	bne L_g5_26
	lwz r3, 0x1bc(r30)
	li r4, 0x1c
	bl searchPoseTbl
	mr r20, r3
	b L_g5_26
	L_g5_25:
	cmpwi r19, 0x1c
	bne L_g5_27
	mr r3, r31
	li r4, 0x16
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_27
	lwz r0, 0x138(r31)
	rlwinm. r0, r0, 0, 3, 3
	beq L_g5_27
	mr r3, r30
	li r4, 0x38
	bl BtlUnit_GetPoseNameFromType
	mr. r20, r3
	bne L_g5_26
	lwz r3, 0x1bc(r30)
	li r4, 0x1c
	bl searchPoseTbl
	mr r20, r3
	b L_g5_26
	L_g5_27:
	lwz r3, 0x1bc(r30)
	mr r4, r19
	bl searchPoseTbl
	mr r20, r3
	L_g5_26:
	mr r3, r31
	lis r4, 0x100
	bl BtlUnit_CheckStatusFlag
	cmpwi r3, 0x0
	beq L_g5_24
	mr r3, r31
	bl BtlUnit_CanActStatus
	cmpwi r3, 0x0
	beq L_g5_24
	mr r3, r30
	li r4, 0x2d
	bl BtlUnit_GetPoseNameFromType
	mr r20, r3
	L_g5_24:
	mr r3, r31
	li r4, 0x13
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_28
	lfs f1, float_2_8041bf68(r2)
	mr r3, r30
	bl btlDispAnimeSpeed
	b L_g5_29
	L_g5_28:
	mr r3, r31
	li r4, 0x14
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_30
	lfs f1, float_0p5_8041bf4c(r2)
	mr r3, r30
	bl btlDispAnimeSpeed
	b L_g5_29
	L_g5_30:
	lfs f1, float_1_8041bf64(r2)
	mr r3, r30
	bl btlDispAnimeSpeed
	b L_g5_29
	L_g5_22:
	lfs f1, float_1_8041bf64(r2)
	mr r3, r30
	bl btlDispAnimeSpeed
	L_g5_29:
	lwz r3, 0x204(r30)
	clrlwi. r0, r3, 31
	beq L_g5_31
	clrrwi r0, r3, 1
	li r19, 0x0
	stw r0, 0x204(r30)
	lwz r0, 0x204(r30)
	rlwinm. r0, r0, 0, 23, 21
	stw r0, 0x204(r30)
	beq L_g5_32
	lwz r3, 0x1c0(r30)
	mr r4, r20
	li r5, 0x1
	bl animPoseSetAnim
	b L_g5_33
	L_g5_32:
	lwz r3, 0x1c0(r30)
	mr r4, r20
	li r5, 0x0
	bl animPoseSetAnim
	L_g5_33:
	li r3, 0x0
	stb r3, 0x214(r30)
	lwz r0, 0x204(r30)
	rlwinm. r0, r0, 0, 29, 29
	beq L_g5_34
	stb r3, 0x215(r30)
	b L_g5_35
	L_g5_34:
	li r0, 0x1
	mr r3, r31
	stb r0, 0x215(r30)
	li r4, 0x12
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_36
	lbz r0, 0x4f3(r30)
	cmplwi r0, 0xff
	beq L_g5_35
	L_g5_36:
	li r0, 0x7
	li r19, 0x1
	stb r0, 0x215(r30)
	L_g5_35:
	lwz r3, 0x204(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_37
	rlwinm. r0, r3, 0, 28, 28
	bne L_g5_37
	rlwinm. r0, r3, 0, 24, 24
	beq L_g5_38
	L_g5_37:
	li r0, 0x1
	mr r3, r31
	stb r0, 0x215(r30)
	li r4, 0x12
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_39
	lbz r0, 0x4f3(r30)
	cmplwi r0, 0xff
	beq L_g5_40
	L_g5_39:
	li r0, 0x7
	li r19, 0x1
	stb r0, 0x215(r30)
	L_g5_40:
	mr r3, r31
	li r4, 0x7
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_38
	li r0, 0x4
	li r19, 0x1
	stb r0, 0x215(r30)
	L_g5_38:
	cmpwi r19, 0x0
	beq L_g5_41
	lwz r0, 0x1ac(r30)
	rlwinm. r0, r0, 0, 16, 16
	beq L_g5_41
	li r0, 0x0
	li r19, 0x0
	stb r0, 0x215(r30)
	L_g5_41:
	lwz r3, 0x204(r30)
	rlwinm. r0, r3, 0, 29, 29
	bne L_g5_31
	cmpwi r19, 0x0
	beq L_g5_42
	rlwinm. r0, r3, 0, 25, 25
	bne L_g5_42
	ori r0, r3, 0x40
	stw r0, 0x204(r30)
	b L_g5_31
	L_g5_42:
	cmpwi r19, 0x0
	bne L_g5_31
	rlwinm. r0, r3, 0, 25, 25
	beq L_g5_31
	lwz r0, 0x204(r30)
	rlwinm r0, r0, 0, 26, 24
	stw r0, 0x204(r30)
	L_g5_31:
	mr r3, r30
	bl gravityOffsetControl
	mr r3, r30
	bl floatOffsetControl
	mr r3, r30
	bl statusPoseControl
	mr r3, r30
	addi r4, r1, 0x14
	addi r5, r1, 0x10
	addi r6, r1, 0xc
	bl BtlUnit_GetPartsWorldPos
	lwz r3, 0x1c0(r30)
	bl animPoseMain
	lfs f1, 0xc(r1)
	mr r3, r31
	lfs f0, 0x4f8(r30)
	li r4, 0x12
	lwz r6, 0x0(r28)
	lwz r5, 0x4(r28)
	fadds f0, f1, f0
	lwz r0, 0x8(r28)
	stw r6, 0x18(r1)
	lfs f2, 0x14(r1)
	stw r0, 0x20(r1)
	lfs f1, 0x10(r1)
	stw r5, 0x1c(r1)
	stfs f2, 0x18(r1)
	stfs f1, 0x1c(r1)
	lwz r6, 0x18(r1)
	stfs f0, 0x20(r1)
	lwz r5, 0x1c(r1)
	lwz r0, 0x20(r1)
	stw r6, 0x54(r1)
	stw r5, 0x58(r1)
	stw r0, 0x5c(r1)
	lwz r5, 0x4(r30)
	lha r0, 0x34(r5)
	stb r0, 0x4f7(r30)
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_43
	lwz r0, 0x104(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_44
	L_g5_43:
	lbz r3, 0x4f7(r30)
	li r0, 0xff
	slwi r3, r3, 7
	divw r0, r3, r0
	stb r0, 0x4f7(r30)
	L_g5_44:
	lbz r4, 0x4f7(r30)
	li r0, 0xff
	lbz r3, 0x4f3(r30)
	mullw r3, r4, r3
	divw r0, r3, r0
	stb r0, 0x4f7(r30)
	lbz r0, 0x4f0(r30)
	stb r0, 0x4f4(r30)
	lbz r0, 0x4f1(r30)
	stb r0, 0x4f5(r30)
	lbz r0, 0x4f2(r30)
	stb r0, 0x4f6(r30)
	lwz r4, 0x104(r31)
	rlwinm. r0, r4, 0, 7, 7
	bne L_g5_45
	lwz r3, 0x1ac(r30)
	rlwinm. r0, r3, 0, 7, 7
	bne L_g5_45
	clrlwi. r0, r3, 31
	beq L_g5_46
	rlwinm. r0, r4, 0, 27, 27
	bne L_g5_47
	L_g5_46:
	lbz r0, 0x4f7(r30)
	cmplwi r0, 0xff
	blt L_g5_48
	lwz r3, 0x1c0(r30)
	bl animPoseTestXLU
	cmpwi r3, 0x0
	beq L_g5_49
	L_g5_48:
	lwz r0, 0x204(r30)
	rlwinm. r0, r0, 0, 23, 23
	bne L_g5_47
	addi r3, r1, 0x54
	bl dispCalcZ
	lis r3, btlUnitPartsDisp@ha
	mr r6, r30
	addi r5, r3, btlUnitPartsDisp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	b L_g5_47
	L_g5_49:
	lwz r0, 0x204(r30)
	rlwinm. r0, r0, 0, 23, 23
	bne L_g5_47
	addi r3, r1, 0x54
	bl dispCalcZ
	lis r3, btlUnitPartsDisp@ha
	mr r6, r30
	addi r5, r3, btlUnitPartsDisp@l
	li r4, 0x1
	li r3, 0x4
	bl dispEntry
	L_g5_47:
	lwz r0, 0x1ac(r30)
	rlwinm. r0, r0, 0, 5, 5
	beq L_g5_45
	lis r3, btlUnitPartsBlurDisp@ha
	lfs f1, 0xc(r1)
	addi r5, r3, btlUnitPartsBlurDisp@l
	mr r6, r30
	li r3, 0x4
	li r4, 0x2
	bl dispEntry
	L_g5_45:
	lwz r0, 0x104(r31)
	rlwinm. r0, r0, 0, 2, 2
	bne L_g5_50
	lwz r0, 0x1ac(r30)
	rlwinm. r0, r0, 0, 6, 6
	bne L_g5_50
	mr r3, r30
	mr r5, r24
	mr r6, r23
	addi r4, r1, 0x48
	bl BtlUnit_GetPartsWorldPos
	lwz r0, 0x1c(r31)
	lwz r5, 0x48(r1)
	lwz r4, 0x4c(r1)
	rlwinm. r0, r0, 0, 15, 15
	lwz r3, 0x50(r1)
	stw r5, 0x3c(r1)
	stw r4, 0x40(r1)
	stw r3, 0x44(r1)
	beq L_g5_51
	mr r3, r29
	mr r4, r31
	bl BattleGetPartnerPtr
	cmplwi r3, 0x0
	beq L_g5_51
	mr r5, r26
	mr r6, r25
	addi r4, r1, 0x30
	bl BtlUnit_GetPos
	lfs f3, 0x3c(r1)
	lfs f2, 0x30(r1)
	lfs f1, 0x40(r1)
	lfs f0, 0x0(r26)
	fadds f2, f3, f2
	lfs f5, float_0p5_8041bf4c(r2)
	fadds f3, f1, f0
	lfs f1, 0x44(r1)
	lfs f0, 0x0(r25)
	fmuls f4, f2, f5
	stfs f2, 0x3c(r1)
	fadds f1, f1, f0
	fmuls f2, f3, f5
	stfs f3, 0x40(r1)
	fmuls f0, f1, f5
	stfs f1, 0x44(r1)
	stfs f4, 0x3c(r1)
	stfs f2, 0x40(r1)
	stfs f0, 0x44(r1)
	L_g5_51:
	lfs f1, 0x3c(r1)
	mr r3, r29
	lfs f2, 0x40(r1)
	lfs f3, 0x44(r1)
	bl BattleGetFloorHeight
	frsp f6, f1
	lfs f0, 0x0(r24)
	stfs f1, 0x40(r1)
	fcmpo cr0, f0, f6
	cror eq, lt, eq
	bne L_g5_52
	lfs f4, float_1_8041bf64(r2)
	b L_g5_53
	L_g5_52:
	fsubs f0, f0, f6
	lfs f1, float_100_8041bf88(r2)
	fsubs f0, f1, f0
	fdivs f4, f0, f1
	L_g5_53:
	lfd f0, 0xb0(r28)
	fcmpo cr0, f4, f0
	ble L_g5_54
	lfs f4, float_1_8041bf64(r2)
	L_g5_54:
	lfs f0, float_0p1_8041bf8c(r2)
	fcmpo cr0, f4, f0
	bge L_g5_55
	fmr f4, f0
	L_g5_55:
	lha r4, 0x1a2(r30)
	lis r3, 0x4330
	lwz r0, 0x1c(r31)
	xoris r4, r4, 0x8000
	stw r3, 0x78(r1)
	lfd f2, 0x58(r28)
	rlwinm. r0, r0, 0, 15, 15
	stw r4, 0x7c(r1)
	lfs f1, 0x90(r31)
	lfd f0, 0x78(r1)
	lfs f3, 0x60(r30)
	fsubs f2, f0, f2
	lfs f5, 0x114(r31)
	lfs f0, 0x78(r30)
	fmuls f1, f2, f1
	fmuls f1, f3, f1
	fmuls f1, f5, f1
	fmuls f4, f4, f1
	fmuls f4, f4, f0
	beq L_g5_56
	lfs f0, float_16_8041bf48(r2)
	fcmpo cr0, f4, f0
	bge L_g5_56
	fmr f4, f0
	L_g5_56:
	lfs f0, float_10_8041bf40(r2)
	fcmpo cr0, f4, f0
	bge L_g5_57
	lfs f4, float_8_8041bf90(r2)
	L_g5_57:
	lfs f0, float_10_8041bf40(r2)
	lfs f1, 0x3c(r1)
	fadds f2, f0, f6
	lfs f3, 0x44(r1)
	bl shadowEntry
	L_g5_50:
	lwz r3, 0x8(r31)
	cmpwi r3, 0xe4
	beq L_g5_58
	cmpwi r3, 0x8d
	beq L_g5_58
	cmpwi r3, 0x86
	beq L_g5_58
	subi r0, r3, 0x1f
	cmplwi r0, 0x2
	ble L_g5_58
	subi r0, r3, 0xbd
	cmplwi r0, 0x4
	ble L_g5_58
	cmpwi r3, 0x85
	bne L_g5_59
	L_g5_58:
	lwz r3, 0x214(r31)
	lis r0, 0x4330
	stw r0, 0x78(r1)
	addi r4, r1, 0x24
	xoris r3, r3, 0x8000
	lfd f1, 0x58(r28)
	stw r3, 0x7c(r1)
	lfd f0, 0x78(r1)
	stw r0, 0x80(r1)
	fsubs f0, f0, f1
	stw r0, 0x88(r1)
	stfs f0, 0x24(r1)
	lwz r0, 0x218(r31)
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f0, 0x80(r1)
	fsubs f0, f0, f1
	stfs f0, 0x28(r1)
	lwz r0, 0x21c(r31)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	stfs f0, 0x2c(r1)
	lwz r3, 0x1c0(r30)
	bl animPoseVivianMain
	L_g5_59:
	mr r3, r30
	bl BtlUnit_ControlPoseSoundMain
	L_g5_21:
	lwz r30, 0x0(r30)
	L_g5_19:
	cmplwi r30, 0x0
	bne L_g5_20
	lwz r0, 0x304(r31)
	cmpwi r0, 0x0
	beq L_g5_60
	lwz r3, 0x1c(r31)
	rlwinm. r0, r3, 0, 1, 1
	beq L_g5_61
	rlwinm. r0, r3, 0, 4, 4
	bne L_g5_61
	lis r3, btlUnitStolenItemDisp@ha
	lfs f1, float_0_8041bf58(r2)
	addi r5, r3, btlUnitStolenItemDisp@l
	mr r6, r31
	li r3, 0x4
	li r4, 0x2
	bl dispEntry
	b L_g5_2
	L_g5_61:
	rlwinm. r0, r3, 0, 5, 5
	beq L_g5_62
	rlwinm. r0, r3, 0, 6, 6
	beq L_g5_2
	L_g5_62:
	rlwinm. r0, r3, 0, 4, 4
	bne L_g5_2
	lis r3, btlUnitItemDisp@ha
	lfs f1, float_0_8041bf58(r2)
	addi r5, r3, btlUnitItemDisp@l
	mr r6, r31
	li r3, 0x4
	li r4, 0x2
	bl dispEntry
	b L_g5_2
	L_g5_60:
	lwz r0, 0xef4(r29)
	rlwinm. r0, r0, 0, 14, 14
	beq L_g5_2
	lis r3, btlUnitItemDisp2@ha
	lfs f1, float_0_8041bf58(r2)
	addi r5, r3, btlUnitItemDisp2@l
	mr r6, r31
	li r3, 0x4
	li r4, 0x2
	bl dispEntry
	L_g5_2:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_1
	bl BattleStockExpDisp
	bl BattleStageDisp
	mr r3, r29
	bl BattleCommandDisplay
	bl BattleAudience_Disp
	bl BattleBreakSlot_Disp
	lwz r3, 0xef4(r29)
	rlwinm. r0, r3, 0, 15, 15
	beq L_g5_63
	rlwinm r0, r3, 0, 16, 14
	stw r0, 0xef4(r29)
	L_g5_63:
	lwz r3, 0xef4(r29)
	rlwinm. r0, r3, 0, 14, 14
	beq L_g5_64
	rlwinm r0, r3, 0, 15, 13
	stw r0, 0xef4(r29)
	L_g5_64:
	lmw r17, 0x94(r1)
	lwz r0, 0xd4(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm StatusEffectType _GetStatusPoseType(BattleUnit* unit) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	la r31, _status_pose_table(r13)
	lwz r0, 0x104(r3)
	rlwinm. r0, r0, 0, 14, 14
	beq L_g5_1
	li r3, 0x1b
	b L_g5_2
	L_g5_1:
	lwz r30, 0x0(r31)
	cmpwi r30, -0x1
	beq L_g5_3
	mr r3, r29
	extsb r4, r30
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_4
	mr r3, r30
	b L_g5_2
	L_g5_4:
	addi r31, r31, 0x4
	b L_g5_1
	L_g5_3:
	li r3, 0x1c
	L_g5_2:
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void btlDispInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r31, _battleWorkPointer(r13)
	bl battleCameraInit
	bl battleMenuDispInit
	lwz r0, 0xef8(r31)
	ori r0, r0, 0x2
	stw r0, 0xef8(r31)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlDispGetTexSize(u32 id, u16* width, u16* height) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r30, 0x28(r1)
	mr r30, r4
	mr r31, r5
	addi r4, r1, 0x8
	lwz r6, _battleWorkPointer(r13)
	addis r5, r6, 0x1
	lwz r6, 0x63dc(r5)
	mr r5, r3
	lwz r3, 0xa0(r6)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x8
	bl GXGetTexObjWidth
	sth r3, 0x0(r30)
	addi r3, r1, 0x8
	bl GXGetTexObjHeight
	sth r3, 0x0(r31)
	lmw r30, 0x28(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void btlDispTexPlane3(Mtx mtx, u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r26, 0x48(r1)
	mr r26, r3
	mr r27, r4
	mr r28, r5
	mr r29, r6
	mr r30, r7
	mr r31, r8
	bl btlDispTexPlaneInit
	mr r3, r26
	addi r4, r1, 0x18
	bl PSMTXCopy
	bl camGetCurPtr
	addi r4, r1, 0x18
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r7, 0x0(r31)
	mr r3, r27
	lwz r9, 0x0(r30)
	addi r4, r1, 0x14
	lwz r8, 0x0(r29)
	addi r5, r1, 0x10
	lwz r0, 0x0(r28)
	addi r6, r1, 0xc
	stw r7, 0x8(r1)
	addi r7, r1, 0x8
	stw r9, 0xc(r1)
	stw r8, 0x10(r1)
	stw r0, 0x14(r1)
	bl btlDispTexPlainGX
	lmw r26, 0x48(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r29, 0x54(r1)
	mr r29, r3
	mr r30, r4
	mr r31, r5
	bl btlDispTexPlaneInit
	mr r3, r29
	addi r4, r1, 0x18
	bl PSMTXCopy
	bl camGetCurPtr
	addi r4, r1, 0x18
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, 0x0(r31)
	mr r3, r30
	addi r4, r1, 0x14
	addi r5, r1, 0x10
	stw r0, 0x8(r1)
	addi r6, r1, 0xc
	addi r7, r1, 0x8
	stw r0, 0xc(r1)
	stw r0, 0x10(r1)
	stw r0, 0x14(r1)
	bl btlDispTexPlainGX
	lmw r29, 0x54(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void btlDispTexPlane(u32 id, GXColor color, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stfd f27, 0xc0(r1)
	psq_st f27, 0xc8(r1), 0, 0
	stmw r29, 0xb4(r1)
	fmr f27, f1
	mr r29, r3
	fmr f28, f2
	mr r30, r4
	fmr f29, f3
	fmr f30, f4
	fmr f31, f5
	bl btlDispTexPlaneInit
	bl camGetCurPtr
	fmr f1, f30
	mr r31, r3
	fmr f2, f31
	lfs f3, float_1_8041bf64(r2)
	addi r3, r1, 0x78
	bl PSMTXScale
	fmr f1, f27
	addi r3, r1, 0x48
	fmr f2, f28
	fmr f3, f29
	bl PSMTXTrans
	addi r3, r1, 0x48
	addi r4, r1, 0x78
	addi r5, r1, 0x18
	bl PSMTXConcat
	addi r4, r1, 0x18
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, 0x0(r30)
	mr r3, r29
	addi r4, r1, 0x14
	addi r5, r1, 0x10
	stw r0, 0x8(r1)
	addi r6, r1, 0xc
	addi r7, r1, 0x8
	stw r0, 0xc(r1)
	stw r0, 0x10(r1)
	stw r0, 0x14(r1)
	bl btlDispTexPlainGX
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	psq_l f27, 0xc8(r1), 0, 0
	lfd f27, 0xc0(r1)
	lmw r29, 0xb4(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm void btlDispTexPlainGX(u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stmw r28, 0x40(r1)
	lwz r8, _battleWorkPointer(r13)
	mr r28, r4
	mr r29, r5
	mr r30, r6
	addis r4, r8, 0x1
	mr r5, r3
	lwz r6, 0x63dc(r4)
	mr r31, r7
	addi r4, r1, 0x8
	lwz r3, 0xa0(r6)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
	addi r3, r1, 0x8
	bl GXGetTexObjFmt
	cmpwi r3, 0x0
	beq L_g5_1
	b L_g5_2
	L_g5_1:
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	b L_g5_3
	L_g5_2:
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	bl GXSetTevOp
	L_g5_3:
	addi r3, r1, 0x8
	bl GXGetTexObjWidth
	clrlwi r4, r3, 16
	lis r0, 0x4330
	lis r3, double_to_int_mask_802ede30@ha
	stw r4, 0x2c(r1)
	addi r4, r3, double_to_int_mask_802ede30@l
	lfs f0, float_0p5_8041bf4c(r2)
	stw r0, 0x28(r1)
	addi r3, r1, 0x8
	lfd f2, 0x0(r4)
	lfd f1, 0x28(r1)
	fsubs f1, f1, f2
	fmuls f31, f0, f1
	bl GXGetTexObjHeight
	clrlwi r4, r3, 16
	lis r0, 0x4330
	lis r3, double_to_int_mask_802ede30@ha
	stw r4, 0x34(r1)
	addi r4, r3, double_to_int_mask_802ede30@l
	lfs f0, float_0p5_8041bf4c(r2)
	stw r0, 0x30(r1)
	li r3, 0x80
	lfd f2, 0x0(r4)
	li r4, 0x0
	lfd f1, 0x30(r1)
	li r5, 0x4
	fsubs f1, f1, f2
	fmuls f30, f0, f1
	bl GXBegin
	fneg f1, f31
	lis r12, 0xcc01
	lbz r0, 0x0(r28)
	fneg f2, f30
	lbz r3, 0x1(r28)
	stfs f1, -0x8000(r12)
	lbz r6, 0x2(r28)
	stfs f30, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	lbz r7, 0x3(r28)
	stfs f0, -0x8000(r12)
	lbz r4, 0x0(r29)
	stb r0, -0x8000(r12)
	lbz r5, 0x1(r29)
	stb r3, -0x8000(r12)
	lbz r10, 0x2(r29)
	stb r6, -0x8000(r12)
	lbz r11, 0x3(r29)
	stb r7, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	lbz r6, 0x0(r30)
	stfs f0, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	lbz r7, 0x1(r30)
	stfs f0, -0x8000(r12)
	lbz r8, 0x2(r30)
	stfs f31, -0x8000(r12)
	lbz r9, 0x3(r30)
	stfs f30, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	lbz r0, 0x0(r31)
	stfs f0, -0x8000(r12)
	lbz r3, 0x1(r31)
	stb r4, -0x8000(r12)
	lbz r4, 0x2(r31)
	stb r5, -0x8000(r12)
	lbz r5, 0x3(r31)
	stb r10, -0x8000(r12)
	stb r11, -0x8000(r12)
	lfs f0, float_1_8041bf64(r2)
	stfs f0, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	stfs f0, -0x8000(r12)
	stfs f31, -0x8000(r12)
	stfs f2, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	stfs f0, -0x8000(r12)
	stb r6, -0x8000(r12)
	stb r7, -0x8000(r12)
	stb r8, -0x8000(r12)
	stb r9, -0x8000(r12)
	lfs f0, float_1_8041bf64(r2)
	stfs f0, -0x8000(r12)
	lfs f0, float_1_8041bf64(r2)
	stfs f0, -0x8000(r12)
	stfs f1, -0x8000(r12)
	stfs f2, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	stfs f0, -0x8000(r12)
	stb r0, -0x8000(r12)
	stb r3, -0x8000(r12)
	stb r4, -0x8000(r12)
	stb r5, -0x8000(r12)
	lfs f0, float_0_8041bf58(r2)
	stfs f0, -0x8000(r12)
	lfs f0, float_1_8041bf64(r2)
	stfs f0, -0x8000(r12)
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	lmw r28, 0x40(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void btlDispTexPlaneInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	stw r0, 0x14(r1)
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlDispGXQuads2D(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
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
	stfd f28, 0x20(r1)
	psq_st f28, 0x28(r1), 0, 0
	stmw r28, 0x10(r1)
	fmr f28, f1
	mr r28, r3
	fmr f29, f2
	mr r29, r4
	mr r30, r5
	fmr f30, f3
	fmr f31, f4
	mr r31, r6
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lfs f3, float_0_8041bf58(r2)
	fmr f1, f28
	fmr f2, f29
	mr r3, r28
	fmr f4, f3
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2D
	fmr f1, f30
	lfs f3, float_1_8041bf64(r2)
	fmr f2, f29
	lfs f4, float_0_8041bf58(r2)
	mr r3, r28
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2D
	lfs f3, float_1_8041bf64(r2)
	fmr f1, f30
	fmr f2, f31
	mr r3, r28
	fmr f4, f3
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2D
	fmr f1, f28
	lfs f3, float_0_8041bf58(r2)
	fmr f2, f31
	lfs f4, float_1_8041bf64(r2)
	mr r3, r28
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2D
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	psq_l f28, 0x28(r1), 0, 0
	lfd f28, 0x20(r1)
	lmw r28, 0x10(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t) {
	nofralloc
	lis r7, 0xcc01
	stfs f1, -0x8000(r7)
	stfs f2, -0x8000(r7)
	lfs f0, float_0_8041bf58(r2)
	stfs f0, -0x8000(r7)
	stb r3, -0x8000(r7)
	stb r4, -0x8000(r7)
	stb r5, -0x8000(r7)
	stb r6, -0x8000(r7)
	stfs f3, -0x8000(r7)
	stfs f4, -0x8000(r7)
	blr
}

asm void btlDispGXQuads2DRasta(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	addi r11, r1, 0x40
	bl _savefpr_28
	stmw r28, 0x10(r1)
	fmr f28, f1
	mr r28, r3
	fmr f29, f2
	mr r29, r4
	mr r30, r5
	fmr f30, f3
	fmr f31, f4
	mr r31, r6
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	fmr f1, f28
	mr r3, r28
	fmr f2, f29
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2DRasta
	fmr f1, f30
	mr r3, r28
	fmr f2, f29
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2DRasta
	fmr f1, f30
	mr r3, r28
	fmr f2, f31
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2DRasta
	fmr f1, f28
	mr r3, r28
	fmr f2, f31
	mr r4, r29
	mr r5, r30
	mr r6, r31
	bl btlDispGXPoint2DRasta
	addi r11, r1, 0x40
	bl _restfpr_28
	lmw r28, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void btlDispGXPoint2DRasta(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a) {
	nofralloc
	lis r7, 0xcc01
	stfs f1, -0x8000(r7)
	stfs f2, -0x8000(r7)
	lfs f0, float_0_8041bf58(r2)
	stfs f0, -0x8000(r7)
	stb r3, -0x8000(r7)
	stb r4, -0x8000(r7)
	stb r5, -0x8000(r7)
	stb r6, -0x8000(r7)
	blr
}

asm void btlDispGXInit2D(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl btlDispGXInit2DSub
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xa
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlDispGXInit2DRasta(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl btlDispGXInit2DSub
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x5
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btlDispGXInit2DSub(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	stw r0, 0x14(r1)
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x5
	bl GXSetBlendMode
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	bl GXSetZMode
	bl GXClearVtxDesc
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x1
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm const char* searchPoseTbl(BattleDispPose* table, s32 poseId) {
	nofralloc
	cmplwi r3, 0x0
	bne L_g5_1
	li r3, 0x0
	blr
	L_g5_1:
	li r0, 0x1c
	mtctr r0
	L_g5_2:
	lwz r0, 0x0(r3)
	cmpw r0, r4
	beq L_g5_3
	cmpwi r0, 0x1c
	bne L_g5_4
	L_g5_3:
	lwz r3, 0x4(r3)
	blr
	L_g5_4:
	addi r3, r3, 0x8
	bdnz L_g5_2
	li r3, 0x0
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8041BF94_sdata2[1] = {0};
#pragma force_active reset
#pragma force_active reset
