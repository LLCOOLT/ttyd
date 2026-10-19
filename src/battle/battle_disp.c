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
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802eddd0[3];
__declspec(section ".rodata") extern const f32 vec3_802edddc[3];
__declspec(section ".rodata") extern const f32 vec3_802edde8[3];
__declspec(section ".rodata") extern const f32 vec3_802eddf4[3];
__declspec(section ".rodata") extern const f32 vec3_802ede00[3];
__declspec(section ".rodata") extern const f32 vec3_802ede0c[3];
__declspec(section ".rodata") extern const f32 vec3_802ede18[3];
__declspec(section ".rodata") extern const f64 double_to_int_802ede28;
__declspec(section ".rodata") extern const f64 double_to_int_mask_802ede30;
__declspec(section ".rodata") extern const char str_802EDE38[8];
__declspec(section ".rodata") extern const char str_802EDE40[8];
__declspec(section ".rodata") extern const char str_802EDE48[8];
__declspec(section ".rodata") extern const char str_802EDE50[8];
__declspec(section ".rodata") extern const char str_802EDE58[8];
__declspec(section ".rodata") extern const char str_802EDE60[8];
__declspec(section ".rodata") extern const char str_802EDE68[8];
__declspec(section ".rodata") extern const char str_802EDE70[8];
__declspec(section ".rodata") extern const f64 double_10_802ede78;
__declspec(section ".rodata") extern const f64 double_1_802ede80;
__declspec(section ".sdata2") extern const f32 float_308_8041bf28;
__declspec(section ".sdata2") extern const f32 float_3p5_8041bf2c;
__declspec(section ".sdata2") extern const f32 float_13_8041bf30;
__declspec(section ".sdata2") extern const f32 float_220_8041bf34;
__declspec(section ".sdata2") extern const f32 float_0p35_8041bf38;
__declspec(section ".sdata2") extern const f32 float_4_8041bf3c;
__declspec(section ".sdata2") extern const f32 float_10_8041bf40;
__declspec(section ".sdata2") extern const f32 float_20_8041bf44;
__declspec(section ".sdata2") extern const f32 float_16_8041bf48;
__declspec(section ".sdata2") extern const f32 float_0p5_8041bf4c;
__declspec(section ".sdata2") extern const f32 float_901_8041bf50;
__declspec(section ".sdata2") extern const f32 float_deg2rad_8041bf54;
__declspec(section ".sdata2") extern const f32 float_0_8041bf58;
__declspec(section ".sdata2") extern const f32 float_304_8041bf5c;
__declspec(section ".sdata2") extern const f32 float_240_8041bf60;
__declspec(section ".sdata2") extern const f32 float_1_8041bf64;
__declspec(section ".sdata2") extern const f32 float_2_8041bf68;
__declspec(section ".sdata2") extern const f32 float_5_8041bf6c;
__declspec(section ".sdata2") extern const f32 float_270_8041bf70;
__declspec(section ".sdata2") extern const f32 float_90_8041bf74;
__declspec(section ".sdata2") extern const f32 float_neg1_8041bf78;
__declspec(section ".sdata2") extern const f32 float_180_8041bf7c;
__declspec(section ".sdata2") extern const f32 float_neg5_8041bf80;
__declspec(section ".sdata2") extern const f32 float_7_8041bf84;
__declspec(section ".sdata2") extern const f32 float_100_8041bf88;
__declspec(section ".sdata2") extern const f32 float_0p1_8041bf8c;
__declspec(section ".sdata2") extern const f32 float_8_8041bf90;
#endif
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

void BattleAudience_Disp(void);
void BattleStatusEffectMain(struct BattleUnit* unit);
void BattleStatusIconMain(struct BattleUnit* unit);
int BtlUnit_CanActStatus();
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
GXTexFmt GXGetTexObjFmt(const GXTexObj* to);
u16 GXGetTexObjHeight(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetNumTevStages(u8 nStages);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
int animPoseVivianMain();
BOOL evtCheckID(s32 eventId);
void BattleBreakSlot_Disp(void);
void BattleCommandDisplay(BattleWork* wp);
void BattleStageDisp(void);
void BattleStockExpDisp(void);
void BtlUnit_ControlPoseSoundMain(BattleUnitPart* part);
void BtlUnit_HpGaugeMain(BattleUnit* unit);
BOOL animPoseTestXLU(s32 poseId);
void btlDispAnimeSpeed(BattleUnitPart* part, f32 speed);
void btlUnitPartsBlurControl(BattleUnitPart* part, s32 unused, Mtx orientation, GXColor color, f32 rotation);
void floatOffsetControl(BattleUnitPart* part);
f32 getFloatDispOffset(BattleUnitPart* part);
f32 getGravityDispOffset(BattleUnitPart* part);
void gravityOffsetControl(BattleUnitPart* part);
void shadowEntry(f32 x, f32 y, f32 z, f32 s);
void statusPoseControl(BattleUnitPart* part);
#ifdef NONMATCHING
void btlDispGXPoint2DRasta(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a) {
	GXPosition3f32(x, y, 0.0f);
	GXColor4u8(r, g, b, a);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void btlDispGXPoint2DRasta(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a) {
	asm volatile {
		opword 0x3CE0CC01
		opword 0xD0278000
		opword 0xD0478000
		lfs f0, float_0_8041bf58(r2)
		opword 0xD0078000
		opword 0x98678000
		opword 0x98878000
		opword 0x98A78000
		opword 0x98C78000
	}
}
#pragma pop
#endif

void btlDispGXQuads2DRasta(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	btlDispGXPoint2DRasta(x0, y0, r, g, b, a);
	btlDispGXPoint2DRasta(x1, y0, r, g, b, a);
	btlDispGXPoint2DRasta(x1, y1, r, g, b, a);
	btlDispGXPoint2DRasta(x0, y1, r, g, b, a);
}

#ifdef NONMATCHING
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t) {
	GXPosition3f32(x, y, 0.0f);
	GXColor4u8(r, g, b, a);
	GXTexCoord2f32(s, t);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t) {
	asm volatile {
		opword 0x3CE0CC01
		opword 0xD0278000
		opword 0xD0478000
		lfs f0, float_0_8041bf58(r2)
		opword 0xD0078000
		opword 0x98678000
		opword 0x98878000
		opword 0x98A78000
		opword 0x98C78000
		opword 0xD0678000
		opword 0xD0878000
	}
}
#pragma pop
#endif

void btlDispGXQuads2D(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a) {
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	btlDispGXPoint2D(x0, y0, r, g, b, a, EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_0_8041bf58, 0.0f));
	btlDispGXPoint2D(x1, y0, r, g, b, a, EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_0_8041bf58, 0.0f));
	btlDispGXPoint2D(x1, y1, r, g, b, a, EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_1_8041bf64, 1.0f));
	btlDispGXPoint2D(x0, y1, r, g, b, a, EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_1_8041bf64, 1.0f));
}
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

	x = EXT_LIT(float_0p5_8041bf4c, 0.5f) * (f32)GXGetTexObjWidth(&texobj);
	y = EXT_LIT(float_0p5_8041bf4c, 0.5f) * (f32)GXGetTexObjHeight(&texobj);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);

	GXPosition3f32(-x, y, EXT_LIT(float_0_8041bf58, 0.0f));
	GXWGFifo.u8 = color0.r; GXWGFifo.u8 = color0.g; GXWGFifo.u8 = color0.b; GXWGFifo.u8 = color0.a;
	GXTexCoord2f32(EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_0_8041bf58, 0.0f));

	GXPosition3f32(x, y, EXT_LIT(float_0_8041bf58, 0.0f));
	GXWGFifo.u8 = color1.r; GXWGFifo.u8 = color1.g; GXWGFifo.u8 = color1.b; GXWGFifo.u8 = color1.a;
	GXTexCoord2f32(EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_0_8041bf58, 0.0f));

	GXPosition3f32(x, -y, EXT_LIT(float_0_8041bf58, 0.0f));
	GXWGFifo.u8 = color2.r; GXWGFifo.u8 = color2.g; GXWGFifo.u8 = color2.b; GXWGFifo.u8 = color2.a;
	GXTexCoord2f32(EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_1_8041bf64, 1.0f));

	GXPosition3f32(-x, -y, EXT_LIT(float_0_8041bf58, 0.0f));
	GXWGFifo.u8 = color3.r; GXWGFifo.u8 = color3.g; GXWGFifo.u8 = color3.b; GXWGFifo.u8 = color3.a;
	GXTexCoord2f32(EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_1_8041bf64, 1.0f));
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void btlDispTexPlainGX(u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xDBE10060
		opword 0xF3E10068
		opword 0xDBC10050
		opword 0xF3C10058
		opword 0xBF810040
		lwz r8, _battleWorkPointer(r13)
		opword 0x7C9C2378
		opword 0x7CBD2B78
		opword 0x7CDE3378
		opword 0x3C880001
		opword 0x7C651B78
		opword 0x80C463DC
		opword 0x7CFF3B78
		opword 0x38810008
		opword 0x806600A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38610008
		bl GXGetTexObjFmt
		opword 0x2C030000
		opword 0x41820008
		opword 0x4800008C
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000A
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00005
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x48000064
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		bl GXSetTevOp
		opword 0x38610008
		bl GXGetTexObjWidth
		opword 0x5464043E
		opword 0x3C004330
		lis r3, double_to_int_mask_802ede30@ha
		opword 0x9081002C
		addi r4, r3, double_to_int_mask_802ede30@l
		lfs f0, float_0p5_8041bf4c(r2)
		opword 0x90010028
		opword 0x38610008
		opword 0xC8440000
		opword 0xC8210028
		opword 0xEC211028
		opword 0xEFE00072
		bl GXGetTexObjHeight
		opword 0x5464043E
		opword 0x3C004330
		lis r3, double_to_int_mask_802ede30@ha
		opword 0x90810034
		addi r4, r3, double_to_int_mask_802ede30@l
		lfs f0, float_0p5_8041bf4c(r2)
		opword 0x90010030
		opword 0x38600080
		opword 0xC8440000
		opword 0x38800000
		opword 0xC8210030
		opword 0x38A00004
		opword 0xEC211028
		opword 0xEFC00072
		bl GXBegin
		opword 0xFC20F850
		opword 0x3D80CC01
		opword 0x881C0000
		opword 0xFC40F050
		opword 0x887C0001
		opword 0xD02C8000
		opword 0x88DC0002
		opword 0xD3CC8000
		lfs f0, float_0_8041bf58(r2)
		opword 0x88FC0003
		opword 0xD00C8000
		opword 0x889D0000
		opword 0x980C8000
		opword 0x88BD0001
		opword 0x986C8000
		opword 0x895D0002
		opword 0x98CC8000
		opword 0x897D0003
		opword 0x98EC8000
		lfs f0, float_0_8041bf58(r2)
		opword 0x88DE0000
		opword 0xD00C8000
		lfs f0, float_0_8041bf58(r2)
		opword 0x88FE0001
		opword 0xD00C8000
		opword 0x891E0002
		opword 0xD3EC8000
		opword 0x893E0003
		opword 0xD3CC8000
		lfs f0, float_0_8041bf58(r2)
		opword 0x881F0000
		opword 0xD00C8000
		opword 0x887F0001
		opword 0x988C8000
		opword 0x889F0002
		opword 0x98AC8000
		opword 0x88BF0003
		opword 0x994C8000
		opword 0x996C8000
		lfs f0, float_1_8041bf64(r2)
		opword 0xD00C8000
		lfs f0, float_0_8041bf58(r2)
		opword 0xD00C8000
		opword 0xD3EC8000
		opword 0xD04C8000
		lfs f0, float_0_8041bf58(r2)
		opword 0xD00C8000
		opword 0x98CC8000
		opword 0x98EC8000
		opword 0x990C8000
		opword 0x992C8000
		lfs f0, float_1_8041bf64(r2)
		opword 0xD00C8000
		lfs f0, float_1_8041bf64(r2)
		opword 0xD00C8000
		opword 0xD02C8000
		opword 0xD04C8000
		lfs f0, float_0_8041bf58(r2)
		opword 0xD00C8000
		opword 0x980C8000
		opword 0x986C8000
		opword 0x988C8000
		opword 0x98AC8000
		lfs f0, float_0_8041bf58(r2)
		opword 0xD00C8000
		lfs f0, float_1_8041bf64(r2)
		opword 0xD00C8000
		opword 0xE3E10068
		opword 0xCBE10060
		opword 0xE3C10058
		opword 0xCBC10050
		opword 0xBB810040
		opword 0x80010074
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop
#endif

void btlDispTexPlane(u32 id, GXColor color, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY) {
	CameraEntry* camera;
	Mtx scale, trans, mtx;

	btlDispTexPlaneInit();
	camera = camGetCurPtr();
	PSMTXScale(scale, sX, sY, EXT_LIT(float_1_8041bf64, 1.0f));
	PSMTXTrans(trans, tX, tY, tZ);
	PSMTXConcat(trans, scale, mtx);
	PSMTXConcat(camera->view, mtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	btlDispTexPlainGX(id, color, color, color, color);
}

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

void btlDispGetTexSize(u32 id, u16* width, u16* height) {
	GXTexObj texobj;

	TEXGetGXTexObjFromPalette(*_battleWorkPointer->menuTex->data, &texobj, id);
	*width = GXGetTexObjWidth(&texobj);
	*height = GXGetTexObjHeight(&texobj);
}

void btlDispInit(void) {
	BattleWork* wp = _battleWorkPointer;
	
	battleCameraInit();
	battleMenuDispInit();
	wp->dispFlags |= 2;
}

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
				tpos.z += EXT_LIT(float_7_8041bf84, 7.0f);
				h = BattleGetFloorHeight(wp, tpos.x, tpos.y, tpos.z);
				switch (unit->work[2]) {
					case 2:
						if (__fabs(pos.x - tpos.x) > EXT_LIT(double_10_802ede78, 10.0)) {
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
						if (__fabs(pos.x - tpos.x) < EXT_LIT(double_1_802ede80, 1.0)) {
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
		unit->mSizeMultiplier = EXT_LIT(float_1_8041bf64, 1.0f);
		BtlUnit_GetStatus(unit, 0xB, &turns, &strength);
		if (turns > 0 && strength < 0) {
			scale = 0.5f * strength + 1.0f;
			if (scale < EXT_LIT(float_0p5_8041bf4c, 0.5f)) scale = EXT_LIT(float_0p5_8041bf4c, 0.5f);
			unit->mSizeMultiplier *= scale;
		}
		BtlUnit_GetStatus(unit, 0xA, &turns, &strength);
		if (turns > 0 && strength > 0) {
			scale = 1.0f + strength;
			if (scale > EXT_LIT(float_2_8041bf68, 2.0f)) scale = EXT_LIT(float_2_8041bf68, 2.0f);
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
					spos.x *= EXT_LIT(float_0p5_8041bf4c, 0.5f);
					spos.y += vpos.y;
					spos.z += vpos.z;
					spos.y *= EXT_LIT(float_0p5_8041bf4c, 0.5f);
					spos.z *= EXT_LIT(float_0p5_8041bf4c, 0.5f);
				}
				spos.y = BattleGetFloorHeight(wp, spos.x, spos.y, spos.z); h = spos.y;
				if (ppos.y <= h) {
					scale = 1.0f;
				}
				else {
					scale = (100.0f - (ppos.y - h)) / 100.0f;
				}
				if (scale > EXT_LIT(double_1_802ede80, 1.0)) scale = EXT_LIT(float_1_8041bf64, 1.0f);
				if (scale < EXT_LIT(float_0p1_8041bf8c, 0.1f)) scale = EXT_LIT(float_0p1_8041bf8c, 0.1f);
				scale = scale * ((f32)part->shadowSize * unit->mScale.x * part->mScale.x * unit->mSizeMultiplier) ;
				scale = scale * part->shadowScale;
				if ((unit->flags & 0x10000) && scale < EXT_LIT(float_16_8041bf48, 16.0f)) scale = EXT_LIT(float_16_8041bf48, 16.0f);
				if (scale < EXT_LIT(float_10_8041bf40, 10.0f)) scale = EXT_LIT(float_8_8041bf90, 8.0f);
				shadowEntry(spos.x, EXT_LIT(float_10_8041bf40, 10.0f) + h, spos.z, scale);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void btlDispMain(void) {
	char _af_pad[132];
	asm {
		lis r3, vec3_802eddd0@ha
	}
	asm volatile {
		addi r28, r3, vec3_802eddd0@l
		la r17, _af_pad+96
		opword 0x3A410064
		opword 0x3AA10074
		opword 0x3AC10070
		opword 0x3AE10050
		opword 0x3B01004C
		opword 0x3B210038
		opword 0x3B410034
		opword 0x3B600000
		lwz r29, _battleWorkPointer(r13)
		lwz r3, _battleWorkPointer(r13)
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x7C7F1B79
		opword 0x41820AE4
		opword 0x801F0008
		opword 0x2C0000DF
		opword 0x408201B0
		opword 0x801F021C
		opword 0x2C000000
		opword 0x418201A4
		opword 0x809F0214
		opword 0x7FA3EB78
		bl BattleGetUnitPtr
		opword 0x7C731B79
		opword 0x41820190
		opword 0x807302A4
		opword 0x2C030000
		opword 0x4182001C
		bl evtCheckID
		opword 0x2C030000
		opword 0x41820010
		opword 0x801302A8
		opword 0x5400077B
		opword 0x4182016C
		opword 0x807302B0
		opword 0x2C030000
		opword 0x41820010
		bl evtCheckID
		opword 0x2C030000
		opword 0x40820154
		opword 0x7FE3FB78
		opword 0x7E459378
		opword 0x7E268B78
		opword 0x38810060
		bl BtlUnit_GetPos
		opword 0x7E639B78
		opword 0x7EC5B378
		opword 0x7EA6AB78
		opword 0x3881006C
		bl BtlUnit_GetPos
		opword 0xC0410074
		opword 0x7FA3EB78
		lfs f0, float_7_8041bf84(r2)
		opword 0xC021006C
		opword 0xEC62002A
		opword 0xC0410070
		opword 0xD0610074
		bl BattleGetFloorHeight
		opword 0x801F021C
		opword 0xFC400890
		opword 0x2C000003
		opword 0x41820078
		opword 0x408000E8
		opword 0x2C000002
		opword 0x40800008
		opword 0x480000DC
		opword 0xC0610060
		opword 0xC041006C
		opword 0xC81C00A8
		opword 0xEC231028
		opword 0xFC800A10
		opword 0xFC040040
		opword 0x40810034
		opword 0xFC021840
		opword 0x4081001C
		opword 0xEC221828
		lfs f0, float_10_8041bf40(r2)
		opword 0xEC010028
		opword 0xEC03002A
		opword 0xD0010060
		opword 0x48000014
		lfs f0, float_10_8041bf40(r2)
		opword 0xEC010028
		opword 0xEC030028
		opword 0xD0010060
		opword 0xC0210060
		opword 0x7FE3FB78
		opword 0xC0410070
		opword 0xC0610074
		bl BtlUnit_SetPos
		opword 0x48000088
		opword 0xC0810060
		opword 0xC021006C
		opword 0xC81C00B0
		opword 0xEC640828
		opword 0xFC601A10
		opword 0xFC030040
		opword 0x4080001C
		opword 0xC0610074
		opword 0x7FE3FB78
		bl BtlUnit_SetPos
		opword 0x38000001
		opword 0x901F021C
		opword 0x48000054
		opword 0xFC012040
		opword 0x40810020
		lfs f0, float_1_8041bf64(r2)
		opword 0x7FE3FB78
		opword 0xC0610074
		opword 0xEC24002A
		opword 0xD0210060
		bl BtlUnit_SetPos
		opword 0x48000030
		lfs f0, float_1_8041bf64(r2)
		opword 0x7FE3FB78
		opword 0xC0610074
		opword 0xEC240028
		opword 0xD0210060
		bl BtlUnit_SetPos
		opword 0x48000014
		opword 0xC021006C
		opword 0x7FE3FB78
		opword 0xC0610074
		bl BtlUnit_SetPos
		opword 0x8A7F030E
		opword 0x7FE3FB78
		opword 0x38800002
		bl BtlUnit_OffUnitFlag
		opword 0x881F030D
		opword 0x7C130000
		opword 0x41820040
		opword 0x7FE3FB78
		opword 0x38800002
		bl BtlUnit_OnUnitFlag
		opword 0x881F030D
		opword 0x7C009800
		opword 0x40810018
		opword 0x3A73000C
		opword 0x7C130000
		opword 0x4081001C
		opword 0x7C130378
		opword 0x48000014
		opword 0x3A73FFFE
		opword 0x7C130000
		opword 0x40800008
		opword 0x7C130378
		opword 0x9A7F030E
		opword 0x7FE3FB78
		bl BtlUnit_HpGaugeMain
		lfs f0, float_1_8041bf64(r2)
		opword 0x7FE3FB78
		opword 0x38A10009
		opword 0x38C10008
		opword 0xD01F0114
		opword 0x3880000B
		bl BtlUnit_GetStatus
		opword 0x88010009
		opword 0x7C000775
		opword 0x40810054
		opword 0x88610008
		opword 0x7C600775
		opword 0x40800048
		opword 0x7C630774
		opword 0x3C004330
		opword 0x6C638000
		opword 0x90010078
		opword 0xC85C0058
		opword 0x9061007C
		lfs f3, float_0p5_8041bf4c(r2)
		opword 0xC8210078
		lfs f0, float_1_8041bf64(r2)
		opword 0xEC211028
		opword 0xEC23007A
		opword 0xFC011840
		opword 0x40800008
		opword 0xFC201890
		opword 0xC01F0114
		opword 0xEC000072
		opword 0xD01F0114
		opword 0x7FE3FB78
		opword 0x38A10009
		opword 0x38C10008
		opword 0x3880000A
		bl BtlUnit_GetStatus
		opword 0x88010009
		opword 0x7C000775
		opword 0x40810054
		opword 0x88610008
		opword 0x7C600775
		opword 0x40810048
		opword 0x7C630774
		opword 0x3C004330
		opword 0x6C638000
		opword 0x90010078
		opword 0xC85C0058
		opword 0x9061007C
		lfs f3, float_1_8041bf64(r2)
		opword 0xC8210078
		lfs f0, float_2_8041bf68(r2)
		opword 0xEC211028
		opword 0xEC23082A
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		opword 0xC01F0114
		opword 0xEC000072
		opword 0xD01F0114
		opword 0x7FE3FB78
		bl BattleStatusEffectMain
		opword 0x7FE3FB78
		bl BattleStatusIconMain
		opword 0x83DF0014
		opword 0x48000720
		opword 0x801E01C0
		opword 0x2C00FFFF
		opword 0x41820710
		opword 0x801E0204
		opword 0x3A9E01C4
		opword 0x540007BD
		opword 0x40820174
		opword 0x7FE3FB78
		bl _GetStatusPoseType
		opword 0x801F0008
		opword 0x7C731B78
		opword 0x2C000001
		opword 0x41800020
		opword 0x2C0000D8
		opword 0x40800018
		opword 0x807E01BC
		opword 0x7E649B78
		bl searchPoseTbl
		opword 0x7C741B78
		opword 0x480000E8
		opword 0x2C13001C
		opword 0x4082004C
		opword 0x7FE3FB78
		opword 0x38800016
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820038
		opword 0x801F0138
		opword 0x54000085
		opword 0x4182002C
		opword 0x7FC3F378
		opword 0x38800039
		bl BtlUnit_GetPoseNameFromType
		opword 0x7C741B79
		opword 0x40820078
		opword 0x807E01BC
		opword 0x3880001C
		bl searchPoseTbl
		opword 0x7C741B78
		opword 0x48000064
		opword 0x2C13001C
		opword 0x4082004C
		opword 0x7FE3FB78
		opword 0x38800016
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820038
		opword 0x801F0138
		opword 0x540000C7
		opword 0x4182002C
		opword 0x7FC3F378
		opword 0x38800038
		bl BtlUnit_GetPoseNameFromType
		opword 0x7C741B79
		opword 0x40820028
		opword 0x807E01BC
		opword 0x3880001C
		bl searchPoseTbl
		opword 0x7C741B78
		opword 0x48000014
		opword 0x807E01BC
		opword 0x7E649B78
		bl searchPoseTbl
		opword 0x7C741B78
		opword 0x7FE3FB78
		opword 0x3C800100
		bl BtlUnit_CheckStatusFlag
		opword 0x2C030000
		opword 0x41820024
		opword 0x7FE3FB78
		bl BtlUnit_CanActStatus
		opword 0x2C030000
		opword 0x41820014
		opword 0x7FC3F378
		opword 0x3880002D
		bl BtlUnit_GetPoseNameFromType
		opword 0x7C741B78
		opword 0x7FE3FB78
		opword 0x38800013
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x41820014
		lfs f1, float_2_8041bf68(r2)
		opword 0x7FC3F378
		bl btlDispAnimeSpeed
		opword 0x48000044
		opword 0x7FE3FB78
		opword 0x38800014
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x41820014
		lfs f1, float_0p5_8041bf4c(r2)
		opword 0x7FC3F378
		bl btlDispAnimeSpeed
		opword 0x48000020
		lfs f1, float_1_8041bf64(r2)
		opword 0x7FC3F378
		bl btlDispAnimeSpeed
		opword 0x48000010
		lfs f1, float_1_8041bf64(r2)
		opword 0x7FC3F378
		bl btlDispAnimeSpeed
		opword 0x807E0204
		opword 0x546007FF
		opword 0x41820168
		opword 0x5460003C
		opword 0x3A600000
		opword 0x901E0204
		opword 0x801E0204
		opword 0x540005EB
		opword 0x901E0204
		opword 0x41820018
		opword 0x807E01C0
		opword 0x7E84A378
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0x48000014
		opword 0x807E01C0
		opword 0x7E84A378
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x38600000
		opword 0x987E0214
		opword 0x801E0204
		opword 0x5400077B
		opword 0x4182000C
		opword 0x987E0215
		opword 0x48000038
		opword 0x38000001
		opword 0x7FE3FB78
		opword 0x981E0215
		opword 0x38800012
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820010
		opword 0x881E04F3
		opword 0x280000FF
		opword 0x41820010
		opword 0x38000007
		opword 0x3A600001
		opword 0x981E0215
		opword 0x807E0204
		opword 0x546007BD
		opword 0x41820014
		opword 0x54600739
		opword 0x4082000C
		opword 0x54600631
		opword 0x41820058
		opword 0x38000001
		opword 0x7FE3FB78
		opword 0x981E0215
		opword 0x38800012
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820010
		opword 0x881E04F3
		opword 0x280000FF
		opword 0x41820010
		opword 0x38000007
		opword 0x3A600001
		opword 0x981E0215
		opword 0x7FE3FB78
		opword 0x38800007
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x41820010
		opword 0x38000004
		opword 0x3A600001
		opword 0x981E0215
		opword 0x2C130000
		opword 0x4182001C
		opword 0x801E01AC
		opword 0x54000421
		opword 0x41820010
		opword 0x38000000
		opword 0x3A600000
		opword 0x981E0215
		opword 0x807E0204
		opword 0x5460077B
		opword 0x4082003C
		opword 0x2C130000
		opword 0x41820018
		opword 0x54600673
		opword 0x40820010
		opword 0x60600040
		opword 0x901E0204
		opword 0x48000020
		opword 0x2C130000
		opword 0x40820018
		opword 0x54600673
		opword 0x41820010
		opword 0x801E0204
		opword 0x540006B0
		opword 0x901E0204
		opword 0x7FC3F378
		bl gravityOffsetControl
		opword 0x7FC3F378
		bl floatOffsetControl
		opword 0x7FC3F378
		bl statusPoseControl
		opword 0x7FC3F378
		opword 0x38810014
		opword 0x38A10010
		opword 0x38C1000C
		bl BtlUnit_GetPartsWorldPos
		opword 0x807E01C0
		bl animPoseMain
		opword 0xC021000C
		opword 0x7FE3FB78
		opword 0xC01E04F8
		opword 0x38800012
		opword 0x80DC0000
		opword 0x80BC0004
		opword 0xEC01002A
		opword 0x801C0008
		opword 0x90C10018
		opword 0xC0410014
		opword 0x90010020
		opword 0xC0210010
		opword 0x90A1001C
		opword 0xD0410018
		opword 0xD021001C
		opword 0x80C10018
		opword 0xD0010020
		opword 0x80A1001C
		opword 0x80010020
		opword 0x90C10054
		opword 0x90A10058
		opword 0x9001005C
		opword 0x80BE0004
		opword 0xA8050034
		opword 0x981E04F7
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820010
		opword 0x801F0104
		opword 0x54000739
		opword 0x41820018
		opword 0x887E04F7
		opword 0x380000FF
		opword 0x54633830
		opword 0x7C0303D6
		opword 0x981E04F7
		opword 0x889E04F7
		opword 0x380000FF
		opword 0x887E04F3
		opword 0x7C6419D6
		opword 0x7C0303D6
		opword 0x981E04F7
		opword 0x881E04F0
		opword 0x981E04F4
		opword 0x881E04F1
		opword 0x981E04F5
		opword 0x881E04F2
		opword 0x981E04F6
		opword 0x809F0104
		opword 0x548001CF
		opword 0x408200C0
		opword 0x807E01AC
		opword 0x546001CF
		opword 0x408200B4
		opword 0x546007FF
		opword 0x4182000C
		opword 0x548006F7
		opword 0x4082007C
		opword 0x881E04F7
		opword 0x280000FF
		opword 0x41800014
		opword 0x807E01C0
		bl animPoseTestXLU
		opword 0x2C030000
		opword 0x41820034
		opword 0x801E0204
		opword 0x540005EF
		opword 0x40820054
		opword 0x38610054
		bl dispCalcZ
		lis r3, btlUnitPartsDisp@ha
		opword 0x7FC6F378
		addi r5, r3, btlUnitPartsDisp@l
		opword 0x38800002
		opword 0x38600004
		bl dispEntry
		opword 0x48000030
		opword 0x801E0204
		opword 0x540005EF
		opword 0x40820024
		opword 0x38610054
		bl dispCalcZ
		lis r3, btlUnitPartsDisp@ha
		opword 0x7FC6F378
		addi r5, r3, btlUnitPartsDisp@l
		opword 0x38800001
		opword 0x38600004
		bl dispEntry
		opword 0x801E01AC
		opword 0x5400014B
		opword 0x41820020
		lis r3, btlUnitPartsBlurDisp@ha
		opword 0xC021000C
		addi r5, r3, btlUnitPartsBlurDisp@l
		opword 0x7FC6F378
		opword 0x38600004
		opword 0x38800002
		bl dispEntry
		opword 0x801F0104
		opword 0x54000085
		opword 0x408201A0
		opword 0x801E01AC
		opword 0x5400018D
		opword 0x40820194
		opword 0x7FC3F378
		opword 0x7F05C378
		opword 0x7EE6BB78
		opword 0x38810048
		bl BtlUnit_GetPartsWorldPos
		opword 0x801F001C
		opword 0x80A10048
		opword 0x8081004C
		opword 0x540003DF
		opword 0x80610050
		opword 0x90A1003C
		opword 0x90810040
		opword 0x90610044
		opword 0x41820074
		opword 0x7FA3EB78
		opword 0x7FE4FB78
		bl BattleGetPartnerPtr
		opword 0x28030000
		opword 0x41820060
		opword 0x7F45D378
		opword 0x7F26CB78
		opword 0x38810030
		bl BtlUnit_GetPos
		opword 0xC061003C
		opword 0xC0410030
		opword 0xC0210040
		opword 0xC01A0000
		opword 0xEC43102A
		lfs f5, float_0p5_8041bf4c(r2)
		opword 0xEC61002A
		opword 0xC0210044
		opword 0xC0190000
		opword 0xEC820172
		opword 0xD041003C
		opword 0xEC21002A
		opword 0xEC430172
		opword 0xD0610040
		opword 0xEC010172
		opword 0xD0210044
		opword 0xD081003C
		opword 0xD0410040
		opword 0xD0010044
		opword 0xC021003C
		opword 0x7FA3EB78
		opword 0xC0410040
		opword 0xC0610044
		bl BattleGetFloorHeight
		opword 0xFCC00818
		opword 0xC0180000
		opword 0xD0210040
		opword 0xFC003040
		opword 0x4C401382
		opword 0x4082000C
		lfs f4, float_1_8041bf64(r2)
		opword 0x48000014
		opword 0xEC003028
		lfs f1, float_100_8041bf88(r2)
		opword 0xEC010028
		opword 0xEC800824
		opword 0xC81C00B0
		opword 0xFC040040
		opword 0x40810008
		lfs f4, float_1_8041bf64(r2)
		lfs f0, float_0p1_8041bf8c(r2)
		opword 0xFC040040
		opword 0x40800008
		opword 0xFC800090
		opword 0xA89E01A2
		opword 0x3C604330
		opword 0x801F001C
		opword 0x6C848000
		opword 0x90610078
		opword 0xC85C0058
		opword 0x540003DF
		opword 0x9081007C
		opword 0xC03F0090
		opword 0xC8010078
		opword 0xC07E0060
		opword 0xEC401028
		opword 0xC0BF0114
		opword 0xC01E0078
		opword 0xEC220072
		opword 0xEC230072
		opword 0xEC250072
		opword 0xEC840072
		opword 0xEC840032
		opword 0x41820014
		lfs f0, float_16_8041bf48(r2)
		opword 0xFC040040
		opword 0x40800008
		opword 0xFC800090
		lfs f0, float_10_8041bf40(r2)
		opword 0xFC040040
		opword 0x40800008
		lfs f4, float_8_8041bf90(r2)
		lfs f0, float_10_8041bf40(r2)
		opword 0xC021003C
		opword 0xEC40302A
		opword 0xC0610044
		bl shadowEntry
		opword 0x807F0008
		opword 0x2C0300E4
		opword 0x41820034
		opword 0x2C03008D
		opword 0x4182002C
		opword 0x2C030086
		opword 0x41820024
		opword 0x3803FFE1
		opword 0x28000002
		opword 0x40810018
		opword 0x3803FF43
		opword 0x28000004
		opword 0x4081000C
		opword 0x2C030085
		opword 0x4082006C
		opword 0x807F0214
		opword 0x3C004330
		opword 0x90010078
		opword 0x38810024
		opword 0x6C638000
		opword 0xC83C0058
		opword 0x9061007C
		opword 0xC8010078
		opword 0x90010080
		opword 0xEC000828
		opword 0x90010088
		opword 0xD0010024
		opword 0x801F0218
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8010080
		opword 0xEC000828
		opword 0xD0010028
		opword 0x801F021C
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xD001002C
		opword 0x807E01C0
		bl animPoseVivianMain
		opword 0x7FC3F378
		bl BtlUnit_ControlPoseSoundMain
		opword 0x83DE0000
		opword 0x281E0000
		opword 0x4082F8E0
		opword 0x801F0304
		opword 0x2C000000
		opword 0x41820070
		opword 0x807F001C
		opword 0x54600043
		opword 0x4182002C
		opword 0x54600109
		opword 0x40820024
		lis r3, btlUnitStolenItemDisp@ha
		lfs f1, float_0_8041bf58(r2)
		addi r5, r3, btlUnitStolenItemDisp@l
		opword 0x7FE6FB78
		opword 0x38600004
		opword 0x38800002
		bl dispEntry
		opword 0x48000064
		opword 0x5460014B
		opword 0x4182000C
		opword 0x5460018D
		opword 0x41820054
		opword 0x54600109
		opword 0x4082004C
		lis r3, btlUnitItemDisp@ha
		lfs f1, float_0_8041bf58(r2)
		addi r5, r3, btlUnitItemDisp@l
		opword 0x7FE6FB78
		opword 0x38600004
		opword 0x38800002
		bl dispEntry
		opword 0x4800002C
		opword 0x801D0EF4
		opword 0x5400039D
		opword 0x41820020
		lis r3, btlUnitItemDisp2@ha
		lfs f1, float_0_8041bf58(r2)
		addi r5, r3, btlUnitItemDisp2@l
		opword 0x7FE6FB78
		opword 0x38600004
		opword 0x38800002
		bl dispEntry
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180F504
		bl BattleStockExpDisp
		bl BattleStageDisp
		opword 0x7FA3EB78
		bl BattleCommandDisplay
		bl BattleAudience_Disp
		bl BattleBreakSlot_Disp
		opword 0x807D0EF4
		opword 0x546003DF
		opword 0x4182000C
		opword 0x5460041C
		opword 0x901D0EF4
		opword 0x807D0EF4
		opword 0x5460039D
		opword 0x4182000C
		opword 0x546003DA
		opword 0x901D0EF4
	}
}
#pragma pop
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
	f32 zscale = EXT_LIT(float_1_8041bf64, 1.0f);
	GXColor* color;
	wp = _battleWorkPointer;
	unit = part->mOwner;
	if (part->poseId < 0) return;

	MTX_TRANS_NEG(uTN, unit->mRotationOffset);
	MTX_TRANS(uT, unit->mRotationOffset);
	MTX_TRANS(uDisp, unit->mDisplayOffset);
	MTX_TRANS(uPos, unit->mPosition);
	PSMTXRotRad(uRx, 'x', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (unit->mRotation.x + unit->mBaseRotation.x));
	PSMTXRotRad(uRy, 'y', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (unit->mRotation.y + unit->mBaseRotation.y));
	PSMTXRotRad(uRz, 'z', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (unit->mRotation.z + unit->mBaseRotation.z));
	PSMTXScale(uS, unit->mSizeMultiplier * (unit->mBaseScale.x * unit->mScale.x), unit->mSizeMultiplier * (unit->mBaseScale.y * unit->mScale.y), unit->mBaseScale.z * unit->mScale.z);
	PSMTXIdentity(uM);
	PSMTXConcat(uS, uM, uM);
	PSMTXConcat(uTN, uM, uM);
	PSMTXConcat(uRy, uM, uM);
	PSMTXConcat(uRz, uM, uM);
	PSMTXConcat(uRx, uM, uM);
	PSMTXConcat(uT, uM, uMtx);
	PSMTXConcat(uDisp, uMtx, uMtx);

	angle = EXT_LIT(float_270_8041bf70, 270.0f);
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
		PSMTXRotRad(pRx2, 'x', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (part->mRotation.x + part->mBaseRotation.x));
		PSMTXRotRad(pRy2, 'y', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (dir + (part->mRotation.y + part->mBaseRotation.y)));
		PSMTXRotRad(pRz2, 'z', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (part->mRotation.z + part->mBaseRotation.z));
		PSMTXTrans(pPos2, x, y, z);
		rotY = reviseAngle(EXT_LIT(float_neg1_8041bf78, -1.0f) * angle - 90.0f);
		z = reviseAngle(part->mBaseRotation.y + (rotY + part->mRotation.y));
		cam = camGetCurPtr();
		camAngle = CAMDIR(cam);
		a = reviseAngle(z + camAngle);
		if (a >= EXT_LIT(float_90_8041bf74, 90.0f) && a <= EXT_LIT(float_270_8041bf70, 270.0f)) {
			zscale *= -1.0f;
			PSMTXRotRad(pRy2, 'y', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * ((dir + (part->mRotation.y + part->mBaseRotation.y)) - 2.0f * (EXT_LIT(float_180_8041bf7c, 180.0f) - (a - camAngle))));
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
		PSMTXTrans(mT5, EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_neg5_8041bf80, -5.0f));
		PSMTXConcat(mT5, blurMtx, blurMtx);
	}
	else {
		if (unit->faceDirection >= 0) angle = 90.0f;
		dir = part->faceDirection;
		if (dir > EXT_LIT(float_0_8041bf58, 0.0f)) {
			dir = 1.0f;
		}
		else if (dir < EXT_LIT(float_0_8041bf58, 0.0f)) {
			dir = -1.0f;
		}
		else {
			dir = wp->alliances[unit->mAlliance].attackDirection;
		}
		x = part->mPositionOffset.x * dir + unit->mPosition.x;
		y = unit->mPosition.y + part->mPositionOffset.y + getGravityDispOffset(part) + getFloatDispOffset(part);
		z = unit->mPosition.z + part->mPositionOffset.z;
		dir = EXT_LIT(float_0_8041bf58, 0.0f);
		if (part->mOwner->mAttributeFlags & 0x4000000) {
			cam = camGetCurPtr();
			a = CAMDIR(cam);
			dir = reviseAngle(a - angleABf(cam->cameraPos.x, cam->cameraPos.z, x, z));
		}
		MTX_TRANS_NEG(pTN, part->mRotationOffset);
		MTX_TRANS(pT, part->mRotationOffset);
		PSMTXRotRad(pRx, 'x', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (part->mRotation.x + part->mBaseRotation.x));
		PSMTXRotRad(pRy, 'y', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (dir + (part->mRotation.y + part->mBaseRotation.y)));
		PSMTXRotRad(pRz, 'z', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * (part->mRotation.z + part->mBaseRotation.z));
		PSMTXTrans(pPos, x, y, z);
		MTX_TRANS(pDisp, part->mDisplayOffset);
		rotY = reviseAngle(EXT_LIT(float_neg1_8041bf78, -1.0f) * angle - 90.0f);
		if (!(part->mOwner->flags & 0x1000000)) {
			a = reviseAngle(rotY + unit->mRotation.y + part->mRotation.y + unit->mBaseRotation.y + part->mBaseRotation.y);
			cam = camGetCurPtr();
			a = reviseAngle(a + CAMDIR(cam));
			if (a >= EXT_LIT(float_90_8041bf74, 90.0f) && a <= EXT_LIT(float_270_8041bf70, 270.0f)) {
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
		PSMTXTrans(mT5, EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_0_8041bf58, 0.0f), EXT_LIT(float_neg5_8041bf80, -5.0f));
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
	animPoseDrawMtx(part->poseId, drawMtx, 1, rotY, EXT_LIT(float_2_8041bf68, 2.0f));
	animPoseDrawMtx(part->poseId, drawMtx, 2, rotY, EXT_LIT(float_2_8041bf68, 2.0f));
	animPoseDrawMtx(part->poseId, drawMtx, 3, rotY, EXT_LIT(float_2_8041bf68, 2.0f));
	if (part->dispCallback) {
		part->dispCallback(part, 1);
	}
	btlUnitPartsBlurControl(part, 0, blurMtx, *color, rotY);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void btlUnitPartsDisp(CameraId camId, BattleUnitPart* part) {
	char _af_pad[1412];
	asm volatile {
		opword 0x800401C0
		opword 0x7C9E2378
		lwz r31, _battleWorkPointer(r13)
		opword 0x2C000000
		lfs f26, float_1_8041bf64(r2)
		lwz r29, 0x4ec(r4)
		opword 0x41800CE0
		opword 0xC03D0078
		la r3, _af_pad+536
		opword 0xC05D007C
		opword 0xC01D0080
		opword 0xFC200850
		opword 0xFC401050
		opword 0xFC600050
		bl PSMTXTrans
		opword 0xC03D0078
		opword 0x386101F0
		opword 0xC05D007C
		opword 0xC07D0080
		bl PSMTXTrans
		opword 0xC03D0054
		opword 0x386102E0
		opword 0xC05D0058
		opword 0xC07D005C
		bl PSMTXTrans
		opword 0xC03D003C
		opword 0x38610310
		opword 0xC05D0040
		opword 0xC07D0044
		bl PSMTXTrans
		opword 0xC03D006C
		opword 0x386102B0
		opword 0xC01D0060
		opword 0x38800078
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC03D0070
		opword 0x38610280
		opword 0xC01D0064
		opword 0x38800079
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC03D0074
		opword 0x38610250
		opword 0xC01D0068
		opword 0x3880007A
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC07D009C
		opword 0x386101C0
		opword 0xC05D0090
		opword 0xC03D00A0
		opword 0xC01D0094
		opword 0xEC8300B2
		opword 0xC0BD0114
		opword 0xEC410032
		opword 0xC07D00A4
		opword 0xC01D0098
		opword 0xEC250132
		opword 0xEC4500B2
		opword 0xEC630032
		bl PSMTXScale
		opword 0x38610490
		bl PSMTXIdentity
		opword 0x38810490
		opword 0x386101C0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610220
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386101F0
		opword 0x38810490
		opword 0x38A10550
		bl PSMTXConcat
		opword 0x38810550
		opword 0x386102E0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x801E01AC
		lfs f27, float_270_8041bf70(r2)
		opword 0x540000C7
		opword 0x41820300
		opword 0x881E00BD
		opword 0x7C000775
		opword 0x41800008
		lfs f27, float_90_8041bf74(r2)
		opword 0xC3BE0018
		opword 0x7FC3F378
		bl getFloatDispOffset
		opword 0xFFC00890
		opword 0x7FC3F378
		bl getGravityDispOffset
		opword 0xC01E001C
		opword 0xC39E0020
		opword 0xEC00082A
		opword 0xEFC0F02A
		bl camGetCurPtr
		opword 0x7C7F1B78
		opword 0xC023000C
		opword 0xC0430014
		opword 0xC0630018
		opword 0xC0830020
		bl angleABf
		opword 0xFFE00890
		opword 0xC03F000C
		opword 0xFC60E890
		opword 0xC05F0014
		opword 0xFC80E090
		bl angleABf
		opword 0xEC3F0828
		bl reviseAngle
		opword 0xC05E0058
		opword 0xFFE00890
		opword 0xC03E0054
		opword 0x38610430
		opword 0xC01E005C
		opword 0xFC401050
		opword 0xFC200850
		opword 0xFC600050
		bl PSMTXTrans
		opword 0xC03E0054
		opword 0x38610400
		opword 0xC05E0058
		opword 0xC07E005C
		bl PSMTXTrans
		opword 0xC03E0048
		opword 0x386103D0
		opword 0xC01E003C
		opword 0x38800078
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC03E004C
		opword 0x386103A0
		opword 0xC01E0040
		opword 0x38800079
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC1F002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC03E0050
		opword 0x38610370
		opword 0xC01E0044
		opword 0x3880007A
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xFC20E890
		opword 0x38610460
		opword 0xFC40F090
		opword 0xFC60E090
		bl PSMTXTrans
		lfs f1, float_neg1_8041bf78(r2)
		lfs f0, float_90_8041bf74(r2)
		opword 0xEC2106F8
		bl reviseAngle
		opword 0xFFC00890
		opword 0xC01E004C
		opword 0xC05E0040
		opword 0xEC1E002A
		opword 0xEC22002A
		bl reviseAngle
		opword 0xFF800890
		bl camGetCurPtr
		opword 0xC023000C
		opword 0xC0430014
		opword 0xC0630018
		opword 0xC0830020
		bl angleABf
		opword 0xFF600890
		opword 0xEC3CD82A
		bl reviseAngle
		lfs f0, float_90_8041bf74(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820054
		lfs f0, float_270_8041bf70(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820044
		opword 0xC05E004C
		opword 0xEC21D828
		opword 0xC01E0040
		opword 0x386103A0
		lfs f3, float_180_8041bf7c(r2)
		opword 0x38800079
		opword 0xEC02002A
		lfs f4, float_neg1_8041bf78(r2)
		opword 0xEC230828
		lfs f2, float_2_8041bf68(r2)
		opword 0xEC1F002A
		lfs f3, float_deg2rad_8041bf54(r2)
		opword 0xEF5A0132
		opword 0xEC02007C
		opword 0xEC230032
		bl PSMTXRotRad
		opword 0x801E01AC
		opword 0x54000109
		opword 0x41820038
		opword 0xC03E0074
		opword 0x386104F0
		opword 0xC01E0068
		opword 0xC07E006C
		opword 0xEC010032
		opword 0xC03E0060
		opword 0xC09E0070
		opword 0xC05E0064
		opword 0xEC230072
		opword 0xEC7A0032
		opword 0xEC4400B2
		bl PSMTXScale
		opword 0x48000040
		opword 0xC07E006C
		opword 0x386104F0
		opword 0xC05E0060
		opword 0xC03E0070
		opword 0xC01E0064
		opword 0xEC8300B2
		opword 0xC0BD0114
		opword 0xEC610032
		opword 0xC05E0074
		opword 0xC01E0068
		opword 0xEC250132
		opword 0xEC020032
		opword 0xEC4500F2
		opword 0xEC7A0032
		bl PSMTXScale
		opword 0x38610340
		bl PSMTXIdentity
		opword 0x38810340
		opword 0x386104F0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810340
		opword 0x38610430
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810340
		opword 0x38610370
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810340
		opword 0x386103D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810340
		opword 0x386103A0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810340
		opword 0x38610400
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610460
		opword 0x38810340
		opword 0x38A10520
		bl PSMTXConcat
		opword 0x38610520
		opword 0x388104C0
		bl PSMTXCopy
		lfs f1, float_0_8041bf58(r2)
		opword 0x38610010
		lfs f3, float_neg5_8041bf80(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x388104C0
		opword 0x38610010
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x4800069C
		opword 0x881D0185
		opword 0x7C000775
		opword 0x41800008
		lfs f27, float_90_8041bf74(r2)
		opword 0x881E00BD
		opword 0x3C604330
		lis r4, double_to_int_802ede28@ha
		opword 0x90610580
		opword 0x7C000774
		lfd f2, double_to_int_802ede28@l(r4)
		opword 0x6C008000
		lfs f0, float_0_8041bf58(r2)
		opword 0x90010584
		opword 0xC8210580
		opword 0xEC211028
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041bf64(r2)
		opword 0x4800003C
		opword 0x4080000C
		lfs f2, float_neg1_8041bf78(r2)
		opword 0x48000030
		opword 0x881D000C
		opword 0x90610580
		opword 0x7C000774
		opword 0x54001838
		opword 0x7C7F0214
		opword 0x8803000A
		opword 0x7C000774
		opword 0x6C008000
		opword 0x90010584
		opword 0xC8010580
		opword 0xEC401028
		opword 0xC03E0024
		opword 0x7FC3F378
		opword 0xC01D003C
		opword 0xEFC100BA
		bl getFloatDispOffset
		opword 0xFF400890
		opword 0x7FC3F378
		bl getGravityDispOffset
		opword 0xC05D0040
		opword 0xC01E0028
		opword 0x807E04EC
		opword 0xEC62002A
		opword 0xC05D0044
		opword 0x80030104
		opword 0xC01E002C
		opword 0xEC23082A
		opword 0x5400014B
		opword 0xEFA2002A
		lfs f28, float_0_8041bf58(r2)
		opword 0xEFE1D02A
		opword 0x41820044
		bl camGetCurPtr
		opword 0x7C7F1B78
		opword 0xC023000C
		opword 0xC0430014
		opword 0xC0630018
		opword 0xC0830020
		bl angleABf
		opword 0xFF400890
		opword 0xC03F000C
		opword 0xFC60F090
		opword 0xC05F0014
		opword 0xFC80E890
		bl angleABf
		opword 0xEC3A0828
		bl reviseAngle
		opword 0xFF800890
		opword 0xC03E0054
		opword 0x386100A0
		opword 0xC05E0058
		opword 0xC01E005C
		opword 0xFC200850
		opword 0xFC401050
		opword 0xFC600050
		bl PSMTXTrans
		opword 0xC03E0054
		opword 0x38610070
		opword 0xC05E0058
		opword 0xC07E005C
		bl PSMTXTrans
		opword 0xC03E0048
		opword 0x38610130
		opword 0xC01E003C
		opword 0x38800078
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC03E004C
		opword 0x38610100
		opword 0xC01E0040
		opword 0x38800079
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC1C002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xC03E0050
		opword 0x386100D0
		opword 0xC01E0044
		opword 0x3880007A
		lfs f2, float_deg2rad_8041bf54(r2)
		opword 0xEC01002A
		opword 0xEC220032
		bl PSMTXRotRad
		opword 0xFC20F090
		opword 0x38610190
		opword 0xFC40F890
		opword 0xFC60E890
		bl PSMTXTrans
		opword 0xC03E0030
		opword 0x38610160
		opword 0xC05E0034
		opword 0xC07E0038
		bl PSMTXTrans
		lfs f1, float_neg1_8041bf78(r2)
		lfs f0, float_90_8041bf74(r2)
		opword 0xEC2106F8
		bl reviseAngle
		opword 0x807E04EC
		opword 0xFFC00890
		opword 0x8003001C
		opword 0x540001CF
		opword 0x40820264
		opword 0xC01D0070
		opword 0xC03E004C
		opword 0xEC1E002A
		opword 0xC05D0064
		opword 0xC07E0040
		opword 0xEC01002A
		opword 0xEC02002A
		opword 0xEC23002A
		bl reviseAngle
		opword 0xFF400890
		bl camGetCurPtr
		opword 0xC023000C
		opword 0xC0430014
		opword 0xC0630018
		opword 0xC0830020
		bl angleABf
		opword 0xEC3A082A
		bl reviseAngle
		lfs f0, float_90_8041bf74(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082020C
		lfs f0, float_270_8041bf70(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408201FC
		opword 0xC07D009C
		opword 0x386101C0
		opword 0xC05D0090
		opword 0xC03D00A0
		opword 0xC01D0094
		opword 0xEC6300B2
		opword 0xC0BD0114
		opword 0xEC810032
		opword 0xC05D00A4
		opword 0xC01D0098
		opword 0xEC2500F2
		lfs f3, float_neg1_8041bf78(r2)
		opword 0xEC020032
		opword 0xEC450132
		opword 0xEC630032
		bl PSMTXScale
		opword 0x38610490
		bl PSMTXIdentity
		opword 0x38810490
		opword 0x386101C0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610220
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x881E04FC
		opword 0x7C000774
		opword 0x2C000003
		opword 0x418200CC
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820058
		opword 0x40800088
		opword 0x2C000000
		opword 0x40800018
		opword 0x48000148
		opword 0x2C000005
		opword 0x41820110
		opword 0x4080013C
		opword 0x480000D4
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000104
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x480000D0
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x4800009C
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000068
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000034
		opword 0x38810490
		opword 0x38610250
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610280
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386102B0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386101F0
		opword 0x38810490
		opword 0x38A10550
		bl PSMTXConcat
		opword 0x38810550
		opword 0x386102E0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0xC03E0074
		opword 0x38610040
		opword 0xC01E0068
		opword 0xC09E006C
		opword 0xC07E0060
		opword 0xEC010032
		lfs f2, float_1_8041bf64(r2)
		opword 0xC0BE0070
		opword 0xEC2400F2
		opword 0xC09E0064
		opword 0xEC620032
		opword 0xEC450132
		bl PSMTXScale
		opword 0x38610490
		bl PSMTXIdentity
		opword 0x38810490
		opword 0x38610550
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610040
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386100A0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x881E04FC
		opword 0x7C000774
		opword 0x2C000003
		opword 0x418200CC
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820058
		opword 0x40800088
		opword 0x2C000000
		opword 0x40800018
		opword 0x48000148
		opword 0x2C000005
		opword 0x41820110
		opword 0x4080013C
		opword 0x480000D4
		opword 0x38810490
		opword 0x38610100
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386100D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610130
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000104
		opword 0x38810490
		opword 0x38610100
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610130
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386100D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x480000D0
		opword 0x38810490
		opword 0x38610130
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610100
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386100D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x4800009C
		opword 0x38810490
		opword 0x38610130
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x386100D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610100
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000068
		opword 0x38810490
		opword 0x386100D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610130
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610100
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000034
		opword 0x38810490
		opword 0x386100D0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610100
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610130
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810490
		opword 0x38610070
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610190
		opword 0x38810490
		opword 0x38A10520
		bl PSMTXConcat
		opword 0x38810520
		opword 0x38610160
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610520
		opword 0x388104C0
		bl PSMTXCopy
		lfs f1, float_0_8041bf58(r2)
		opword 0x38610010
		lfs f3, float_neg5_8041bf80(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x388104C0
		opword 0x38610010
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x801E04F4
		opword 0x901E0218
		opword 0x801E0204
		opword 0x540006F7
		opword 0x41820014
		opword 0x38000000
		opword 0x981E0218
		opword 0x981E0219
		opword 0x981E021A
		opword 0x801E0204
		opword 0x540006B5
		opword 0x41820014
		opword 0x38000000
		opword 0x981E0218
		opword 0x981E0219
		opword 0x981E021A
		opword 0x881E0218
		opword 0x280000FF
		opword 0x40820094
		opword 0x881E0219
		opword 0x280000FF
		opword 0x40820088
		opword 0x881E021A
		opword 0x280000FF
		opword 0x4082007C
		opword 0x7FA3EB78
		opword 0x38800004
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x41820028
		opword 0x881E0218
		opword 0x386000FF
		opword 0x1C0000A0
		opword 0x7C001BD6
		opword 0x981E0218
		opword 0x881E0218
		opword 0x1C0000A0
		opword 0x7C001BD6
		opword 0x981E021A
		opword 0x887E0218
		opword 0x388000FF
		opword 0x881D030E
		opword 0x7C0301D6
		opword 0x7C0023D6
		opword 0x981E0218
		opword 0x887E0219
		opword 0x881D030E
		opword 0x7C0301D6
		opword 0x7C0023D6
		opword 0x981E0219
		opword 0x887E021A
		opword 0x881D030E
		opword 0x7C0301D6
		opword 0x7C0023D6
		opword 0x981E021A
		opword 0x801E0218
		opword 0x3881000C
		opword 0x9001000C
		opword 0x807E01C0
		bl animPoseSetMaterialEvtColor
		opword 0x807E01C0
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		opword 0x819E0210
		opword 0x280C0000
		opword 0x41820014
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x7FA3EB78
		opword 0x38800010
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x41820014
		opword 0x807E01C0
		opword 0x3C800080
		bl animPoseSetMaterialFlagOn
		opword 0x48000010
		opword 0x807E01C0
		opword 0x3C800080
		bl animPoseSetMaterialFlagOff
		opword 0xFC20F090
		opword 0x807E01C0
		lfs f2, float_2_8041bf68(r2)
		opword 0x38810520
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0xFC20F090
		opword 0x807E01C0
		lfs f2, float_2_8041bf68(r2)
		opword 0x38810520
		opword 0x38A00002
		bl animPoseDrawMtx
		opword 0xFC20F090
		opword 0x807E01C0
		lfs f2, float_2_8041bf68(r2)
		opword 0x38810520
		opword 0x38A00003
		bl animPoseDrawMtx
		opword 0x819E0210
		opword 0x280C0000
		opword 0x41820014
		opword 0x7FC3F378
		opword 0x38800001
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x801E0218
		opword 0xFC20F090
		opword 0x7FC3F378
		opword 0x38A104C0
		opword 0x90010008
		opword 0x38C10008
		opword 0x38800000
		bl btlUnitPartsBlurControl
	}
}
#pragma pop
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
		((void (*)(f32, Vec*, s16, u16))iconDispGx)(EXT_LIT(float_1_8041bf64, 1.0f), &pos, 0, itemDataTable[item].icon_id);
	}
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void btlUnitItemDisp(CameraId camId, BattleUnit* unit) {
	char _af_pad[24];
	asm volatile {
		mr r30, r4
		opword 0x7FC3F378
		lwz r31, _battleWorkPointer(r13)
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		stw r3, _af_pad+20(r1)
		opword 0x807E0304
		opword 0x90010018
		bl BtlUnit_EnemyItemCanUseCheck
		opword 0x801F0EF4
		opword 0x7C7F1B78
		opword 0x5400039D
		opword 0x41820010
		opword 0x2C1F0000
		opword 0x40820008
		opword 0x3BE00094
		opword 0x2C1F0000
		opword 0x41820090
		opword 0x38A1000C
		opword 0x38C10010
		opword 0x7FC3F378
		opword 0x38810008
		bl BtlUnit_GetPos
		opword 0xC0210008
		lis r3, itemDataTable@ha
		opword 0xC01E00B4
		opword 0x1C1F0028
		addi r3, r3, itemDataTable@l
		opword 0xC061000C
		opword 0xEC81002A
		opword 0xC0410010
		opword 0x7C830214
		lfs f1, float_1_8041bf64(r2)
		opword 0x38610008
		opword 0xD0810008
		opword 0xA0A40020
		opword 0x38800000
		opword 0xC01E00B8
		opword 0xEC63002A
		opword 0xD061000C
		opword 0xC01E00BC
		opword 0xEC42002A
		opword 0xD0410010
		opword 0xC01E00C0
		opword 0xEC04002A
		opword 0xD0010008
		opword 0xC01E00C4
		opword 0xEC03002A
		opword 0xD001000C
		opword 0xC01E00C8
		opword 0xEC02002A
		opword 0xD0010010
		bl iconDispGx
	}
}
#pragma pop
#endif
#pragma pop

#pragma dont_inline on
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
#pragma dont_inline reset

#ifdef NONMATCHING
void btlUnitStolenItemDisp(CameraId camId, void* param) {
	BattleUnit* unit = param;
	Vec pos;
	s32 item = unit->heldItem;

	BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
	pos.y += EXT_LIT(float_5_8041bf6c, 5.0f) + unit->mSizeMultiplier * (f32)BtlUnit_GetHeight(unit);
	((void (*)(f32, Vec*, s16, u16))iconDispGx)(EXT_LIT(float_1_8041bf64, 1.0f), &pos, 0, itemDataTable[item].icon_id);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void btlUnitStolenItemDisp(CameraId camId, void* param) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0x38A1000C
		opword 0x38C10010
		opword 0xBFC10028
		opword 0x7C9F2378
		opword 0x38810008
		opword 0x7FE3FB78
		opword 0x83DF0304
		bl BtlUnit_GetPos
		opword 0x7FE3FB78
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061001C
		lis r4, double_to_int_802ede28@ha
		lfd f1, double_to_int_802ede28@l(r4)
		lis r3, itemDataTable@ha
		opword 0x90010018
		addi r4, r3, itemDataTable@l
		opword 0x1C1E0028
		opword 0xC07F0114
		opword 0xC8010018
		opword 0x38610008
		lfs f2, float_5_8041bf6c(r2)
		opword 0xEC800828
		opword 0x7CA40214
		opword 0xC001000C
		lfs f1, float_1_8041bf64(r2)
		opword 0x38800000
		opword 0xEC43113A
		opword 0xA0A50020
		opword 0xEC00102A
		opword 0xD001000C
		bl iconDispGx
		opword 0xBBC10028
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif

#pragma dont_inline on
void btlUnitPartsBlurControl(BattleUnitPart* part, s32 unused, Mtx orientation, GXColor color, f32 rotation) {

	if (part->attributes & 0x4000000) {
		_partsBlurControl(part, 1, orientation, color, rotation);
	}
	else {
		_partsBlurControl(part, 0, orientation, color, rotation);
	}
}
#pragma dont_inline reset

//TODO: probably needs Entry* pointer to make offsets relative and then it should match
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
				animPoseDrawMtx(part->poseId, entry->orientation, 1, entry->rotation, EXT_LIT(float_2_8041bf68, 2.0f));
				animPoseDrawMtx(part->poseId, entry->orientation, 2, entry->rotation, EXT_LIT(float_2_8041bf68, 2.0f));
				animPoseDrawMtx(part->poseId, entry->orientation, 3, entry->rotation, EXT_LIT(float_2_8041bf68, 2.0f));
			}
		}
	}
}

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

void btlDispChangePeraAnime(BattleUnitPart* part, const char* name) {
	PART_ANIMFLAGS(part) |= 4;
	PART_POSETYPE(part) = 0;
	animPoseSetEffectAnim(part->poseId, name, 1);
}

void btlDispPoseAnime(BattleUnitPart* part) {
	PART_ANIMFLAGS(part) &= ~0x12;
	PART_ANIMFLAGS(part) |= 1;
	PART_ANIMFLAGS(part) &= ~0x80;
	PART_ANIMFLAGS(part) &= ~0x4;
}

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

#ifdef NONMATCHING
f32 getGravityDispOffset(BattleUnitPart* part) {
	return 4.0f * sinfd((PART_GRAVITY(part) * 3 + 270) % 360) + 4.0f;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
f32 getGravityDispOffset(BattleUnitPart* part) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x38800168
		opword 0x90010014
		opword 0x3C004330
		opword 0xA0A301A6
		lis r3, double_to_int_802ede28@ha
		lfd f1, double_to_int_802ede28@l(r3)
		opword 0x1CA50003
		opword 0x90010008
		opword 0x3865010E
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7C001850
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC200828
		bl sinfd
		lfs f0, float_4_8041bf3c(r2)
		opword 0x80010014
		opword 0xEC20007A
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

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

#ifdef NONMATCHING
f32 getFloatDispOffset(BattleUnitPart* part) {
	return 2.0f * sinfd((PART_FLOAT(part) * 4 + 270) % 360) + 2.0f;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
f32 getFloatDispOffset(BattleUnitPart* part) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x38800168
		opword 0x90010014
		opword 0x3C004330
		opword 0xA0A301A8
		lis r3, double_to_int_802ede28@ha
		opword 0x90010008
		opword 0x54A5103A
		lfd f1, double_to_int_802ede28@l(r3)
		opword 0x38A5010E
		opword 0x7C0523D6
		opword 0x7C0021D6
		opword 0x7C002850
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC200828
		bl sinfd
		lfs f0, float_2_8041bf68(r2)
		opword 0x80010014
		opword 0xEC20007A
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

#pragma dont_inline on
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
#pragma dont_inline reset

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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void _pose_one_pattern(BattleUnitPart* part) {
	asm volatile {
		mr r30, r3
		lis r3, vec3_802eddd0@ha
		addi r31, r3, vec3_802eddd0@l
		opword 0x881E0214
		opword 0x2C000000
		opword 0x41820008
		opword 0x4800009C
		opword 0x38000001
		opword 0x981E0214
		opword 0x881E0215
		opword 0x2C000003
		opword 0x41820044
		opword 0x40800010
		opword 0x2C000002
		opword 0x40800014
		opword 0x48000078
		opword 0x2C000007
		opword 0x41820050
		opword 0x4800006C
		opword 0x807E01C0
		opword 0x389F0068
		opword 0x38A00001
		bl animPoseSetEffect
		opword 0x807E01C0
		opword 0x389F0078
		opword 0x38A00001
		bl animPoseSetEffectAnim
		opword 0x48000048
		opword 0x807E01C0
		opword 0x389F0068
		opword 0x38A00001
		bl animPoseSetEffect
		opword 0x807E01C0
		opword 0x389F0098
		opword 0x38A00001
		bl animPoseSetEffectAnim
		opword 0x48000024
		opword 0x807E01C0
		opword 0x389F0068
		opword 0x38A00001
		bl animPoseSetEffect
		opword 0x807E01C0
		opword 0x389F00A0
		opword 0x38A00001
		bl animPoseSetEffectAnim
	}
}
#pragma pop
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void _pose_two_pattern(BattleUnitPart* part) {
	asm {
		lis r4, vec3_802eddd0@ha
	}
	asm volatile {
		opword 0x7C7F1B78
		addi r30, r4, vec3_802eddd0@l
		opword 0x88030214
		opword 0x2C000001
		opword 0x418200FC
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000260
		opword 0x2C000003
		opword 0x40800258
		opword 0x480001B8
		opword 0x38000001
		opword 0x981F0214
		opword 0x881F0215
		opword 0x2C000005
		opword 0x41820050
		opword 0x40800010
		opword 0x2C000004
		opword 0x40800014
		opword 0x48000230
		opword 0x2C000007
		opword 0x40800228
		opword 0x48000078
		opword 0x807F01C0
		opword 0x389E0068
		opword 0x38A00001
		bl animPoseSetEffect
		opword 0x807F01C0
		opword 0x389E0070
		opword 0x38A00001
		bl animPoseSetEffectAnim
		opword 0x38600898
		bl sysMsec2Frame
		opword 0xB07F0216
		opword 0x480001F4
		opword 0x807F01C0
		opword 0x389E0068
		opword 0x38A00001
		bl animPoseSetEffect
		opword 0x807F01C0
		opword 0x389E0078
		opword 0x38A00001
		bl animPoseSetEffectAnim
		opword 0x38600898
		bl sysMsec2Frame
		opword 0x7C7E1B78
		opword 0x38600004
		bl irand
		opword 0x38030006
		opword 0x7C00F1D6
		opword 0xB01F0216
		opword 0x480001B0
		opword 0x807F01C0
		opword 0x389E0068
		opword 0x38A00001
		bl animPoseSetEffect
		opword 0x807F01C0
		opword 0x389E0080
		opword 0x38A00001
		bl animPoseSetEffectAnim
		opword 0x38600004
		bl irand
		opword 0x38030007
		opword 0x1C000016
		opword 0xB01F0216
		opword 0x48000178
		opword 0x881F0215
		opword 0x2C000005
		opword 0x41820058
		opword 0x40800010
		opword 0x2C000004
		opword 0x40800014
		opword 0x4800015C
		opword 0x2C000007
		opword 0x40800154
		opword 0x48000078
		opword 0xA07F0216
		opword 0x3803FFFF
		opword 0xB01F0216
		opword 0xA01F0216
		opword 0x28000000
		opword 0x40820138
		opword 0x807F01C0
		opword 0x389E0070
		opword 0x38A00001
		bl animPoseSetEffectAnim
		opword 0x38600898
		bl sysMsec2Frame
		opword 0xB07F0216
		opword 0x48000118
		opword 0xA07F0216
		opword 0x3803FFFF
		opword 0xB01F0216
		opword 0xA01F0216
		opword 0x28000000
		opword 0x40820100
		opword 0x38000002
		opword 0x389E0088
		opword 0x981F0214
		opword 0x38A00001
		opword 0x807F01C0
		bl animPoseSetEffectAnim
		opword 0x38000016
		opword 0xB01F0216
		opword 0x480000DC
		opword 0xA07F0216
		opword 0x3803FFFF
		opword 0xB01F0216
		opword 0xA01F0216
		opword 0x28000000
		opword 0x408200C4
		opword 0x38000002
		opword 0x389E0090
		opword 0x981F0214
		opword 0x38A00001
		opword 0x807F01C0
		bl animPoseSetEffectAnim
		opword 0x38000016
		opword 0xB01F0216
		opword 0x480000A0
		opword 0x881F0215
		opword 0x2C000005
		opword 0x41820048
		opword 0x40800010
		opword 0x2C000004
		opword 0x40800014
		opword 0x48000084
		opword 0x2C000007
		opword 0x4080007C
		opword 0x48000054
		opword 0xA09F0216
		opword 0x3804FFFF
		opword 0xB01F0216
		opword 0xA01F0216
		opword 0x28000000
		opword 0x40820060
		opword 0x38000000
		opword 0x981F0214
		bl _pose_two_pattern
		opword 0x48000050
		opword 0xA09F0216
		opword 0x3804FFFF
		opword 0xB01F0216
		opword 0xA01F0216
		opword 0x28000000
		opword 0x40820038
		opword 0x38000000
		opword 0x981F0214
		bl _pose_two_pattern
		opword 0x48000028
		opword 0xA09F0216
		opword 0x3804FFFF
		opword 0xB01F0216
		opword 0xA01F0216
		opword 0x28000000
		opword 0x40820010
		opword 0x38000000
		opword 0x981F0214
		bl _pose_two_pattern
	}
}
#pragma pop
#endif

#pragma push
#pragma opt_dead_assignments off
void btlDispAnimeSpeed(BattleUnitPart* part, f32 speed) {
#ifdef NONMATCHING
	f32 unusedOne = 1.0f;
#endif // FAKE: the target's unreferenced 1.0f is gap_09_8041BF94_sdata2
	PART_ANIMSPEED(part) = speed;
	animPoseSetLocalTimeRate(part->poseId, PART_ANIMSPEED(part) * PART_ANIMSPEED2(part));
}
#pragma pop

void btlGetScreenPoint(Vec* in, Vec* out) {
	CameraEntry* camera = camGetPtr(CAMERA_3D);
	Vec v;

	v.x = in->x;
	v.y = in->y;
	v.z = in->z;

	PSMTXMultVec(camera->view, &v, &v);
	PSMTX44MultVec(camera->projection, &v, &v);
	out->x = EXT_LIT(float_304_8041bf5c, 304.0f) * v.x;
	out->y = EXT_LIT(float_240_8041bf60, 240.0f) * v.y;
	out->z = EXT_LIT(float_0_8041bf58, 0.0f);
}

#pragma dont_inline on
#ifdef NONMATCHING
void btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, GXColor color) {
	u16 width, height;
	f32 hw, hh;
	Vec off;
	Vec unused; unused.x = EXT_LIT(float_0_8041bf58, 0.0f); unused.y = EXT_LIT(float_0_8041bf58, 0.0f); unused.z = EXT_LIT(float_0_8041bf58, 0.0f);

	off.z = EXT_LIT(float_0_8041bf58, 0.0f);

	btlDispGetTexSize(id, &width, &height);
	hw = EXT_LIT(float_0p5_8041bf4c, 0.5f) * ((f32)width * scale.x);
	hh = EXT_LIT(float_0p5_8041bf4c, 0.5f) * ((f32)height * scale.y);
	off.x = -hw;
	off.y = hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_1_8041bf64, 1.0f)}, color);
	off.x = hw;
	off.y = hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){EXT_LIT(float_neg1_8041bf78, -1.0f), EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_1_8041bf64, 1.0f)}, color);
	off.x = hw;
	off.y = -hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){EXT_LIT(float_neg1_8041bf78, -1.0f), EXT_LIT(float_neg1_8041bf78, -1.0f), EXT_LIT(float_1_8041bf64, 1.0f)}, color);
	off.x = -hw;
	off.y = -hh;
	_btlDispTex4(id, pos, scale, rot, off, (Vec){EXT_LIT(float_1_8041bf64, 1.0f), EXT_LIT(float_neg1_8041bf78, -1.0f), EXT_LIT(float_1_8041bf64, 1.0f)}, color);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, GXColor color) {
	char _af_pad[280];
	asm volatile {
		lfs f0, float_0_8041bf58(r2)
		lis r8, vec3_802eddd0@ha
		opword 0x7C9B2378
		opword 0x7CBC2B78
		stfs f0, _af_pad+268(r1)
		opword 0x7C7A1B78
		opword 0x7CDD3378
		opword 0x7CFE3B78
		addi r31, r8, vec3_802eddd0@l
		opword 0x3881000A
		opword 0x38A10008
		bl btlDispGetTexSize
		opword 0xA081000A
		opword 0x3D404330
		opword 0xA0010008
		opword 0x7F43D378
		opword 0x9081011C
		opword 0x38810100
		opword 0x81FE0000
		opword 0x38A100F4
		opword 0x91410118
		opword 0x38C100E8
		opword 0xC87F0060
		opword 0x38E100DC
		opword 0xC8010118
		opword 0x390100D0
		opword 0x90010124
		opword 0x39210018
		opword 0xEC401828
		opword 0xC01C0000
		opword 0x91410120
		lfs f4, float_0p5_8041bf4c(r2)
		opword 0xC8210120
		opword 0xEC420032
		opword 0xC01C0004
		opword 0xEC211828
		opword 0x821F000C
		fmuls f29, f4, f2
		opword 0x823F0010
		opword 0x825F0014
		opword 0xEC010032
		opword 0xFFE0E850
		opword 0x82A10114
		opword 0x82DD0000
		opword 0xEFC40032
		opword 0x82FD0004
		opword 0xD3E1010C
		opword 0x831D0008
		opword 0xD3C10110
		opword 0x8261010C
		opword 0x82810110
		opword 0x833C0000
		opword 0x819C0004
		opword 0x817C0008
		opword 0x815B0000
		opword 0x801B0004
		lwz r14, 0x8(r27)
		opword 0x91E10018
		opword 0x920100D0
		opword 0x922100D4
		opword 0x924100D8
		opword 0x926100DC
		opword 0x928100E0
		opword 0x92A100E4
		opword 0x92C100E8
		opword 0x92E100EC
		opword 0x930100F0
		opword 0x932100F4
		opword 0x918100F8
		opword 0x916100FC
		opword 0x91410100
		opword 0x90010104
		opword 0x91C10108
		bl _btlDispTex4
		opword 0xD3A1010C
		opword 0x7F43D378
		opword 0x831E0000
		opword 0x388100C4
		opword 0xD3C10110
		opword 0x38A100B8
		opword 0x82FF0018
		opword 0x38C100AC
		opword 0x82DF001C
		opword 0x38E100A0
		opword 0x82BF0020
		opword 0x39010094
		opword 0x8281010C
		opword 0x39210014
		opword 0x82610110
		opword 0x82410114
		opword 0x823D0000
		opword 0x821D0004
		opword 0x81FD0008
		opword 0x81DC0000
		opword 0x819C0004
		opword 0x817C0008
		opword 0x815B0000
		opword 0x801B0004
		opword 0x833B0008
		opword 0x93010014
		opword 0x92E10094
		opword 0x92C10098
		opword 0x92A1009C
		opword 0x928100A0
		opword 0x926100A4
		opword 0x924100A8
		opword 0x922100AC
		opword 0x920100B0
		opword 0x91E100B4
		opword 0x91C100B8
		opword 0x918100BC
		opword 0x916100C0
		opword 0x914100C4
		opword 0x900100C8
		opword 0x932100CC
		bl _btlDispTex4
		opword 0xFFC0F050
		opword 0x831E0000
		opword 0x82FF0024
		opword 0x7F43D378
		opword 0x82DF0028
		opword 0x38810088
		opword 0xD3C10110
		opword 0x38A1007C
		opword 0x82BF002C
		opword 0x38C10070
		opword 0x82610110
		opword 0x38E10064
		opword 0x823D0000
		opword 0x39010058
		opword 0x821D0004
		opword 0x39210010
		opword 0x81FD0008
		opword 0x81DC0000
		opword 0x819C0004
		opword 0x817C0008
		opword 0x815B0000
		opword 0x801B0004
		opword 0x833B0008
		opword 0xD3A1010C
		opword 0x93010010
		opword 0x92E10058
		opword 0x92C1005C
		opword 0x92A10060
		opword 0x92810064
		opword 0x92610068
		opword 0x9241006C
		opword 0x92210070
		opword 0x92010074
		opword 0x91E10078
		opword 0x91C1007C
		opword 0x91810080
		opword 0x91610084
		opword 0x91410088
		opword 0x9001008C
		opword 0x93210090
		bl _btlDispTex4
		opword 0xD3E1010C
		opword 0x7E749B78
		opword 0x7E539378
		opword 0x833E0000
		opword 0x831F0030
		opword 0x7F43D378
		opword 0x82FF0034
		opword 0x3881004C
		opword 0x82DF0038
		opword 0x38A10040
		opword 0x82A1010C
		opword 0x38C10034
		opword 0x825D0000
		opword 0x38E10028
		opword 0x823D0004
		opword 0x3901001C
		opword 0x821D0008
		opword 0x3921000C
		opword 0x81FC0000
		opword 0x81DC0004
		opword 0x819C0008
		opword 0x817B0000
		opword 0x815B0004
		opword 0x801B0008
		opword 0xD3C10110
		opword 0x9321000C
		opword 0x9301001C
		opword 0x92E10020
		opword 0x92C10024
		opword 0x92A10028
		opword 0x9281002C
		opword 0x92610030
		opword 0x92410034
		opword 0x92210038
		opword 0x9201003C
		opword 0x91E10040
		opword 0x91C10044
		opword 0x91810048
		opword 0x9161004C
		opword 0x91410050
		opword 0x90010054
		bl _btlDispTex4
	}
}
#pragma pop
#endif
#pragma dont_inline reset

void _btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, Vec pos2, Vec scale2, GXColor color) {
	Mtx mtx, trans, scl, rotX, rotY, rotZ, trans2, scl2;

	PSMTXIdentity(mtx);
	PSMTXTrans(trans, pos.x, pos.y, pos.z);
	PSMTXTrans(trans2, pos2.x, pos2.y, pos2.z);
	PSMTXScale(scl, scale.x, scale.y, scale.z);
	PSMTXScale(scl2, scale2.x, scale2.y, scale2.z);
	PSMTXRotRad(rotX, 'x', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * rot.x);
	PSMTXRotRad(rotY, 'y', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * rot.y);
	PSMTXRotRad(rotZ, 'z', EXT_LIT(float_deg2rad_8041bf54, 0.017453292f) * rot.z);
	PSMTXConcat(scl, mtx, mtx);
	PSMTXConcat(scl2, mtx, mtx);
	PSMTXConcat(trans2, mtx, mtx);
	PSMTXConcat(rotZ, mtx, mtx);
	PSMTXConcat(rotX, mtx, mtx);
	PSMTXConcat(rotY, mtx, mtx);
	PSMTXConcat(trans, mtx, mtx);
	((void (*)(Mtx, u32, GXColor, s32))btlDispTexPlane2)(mtx, id, color, 0);
}

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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void BattleStockExpDisp(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		lwz r4, _battleWorkPointer(r13)
		opword 0x80640F00
		opword 0x80040F04
		opword 0x7C030000
		opword 0x40810028
		opword 0x80640F08
		opword 0x38030001
		opword 0x90040F08
		opword 0x80040F08
		opword 0x2C000004
		opword 0x41800010
		opword 0x80640F04
		opword 0x38030001
		opword 0x90040F04
		opword 0x80040EF8
		opword 0x540007BD
		opword 0x41820020
		lis r3, _btlStockExpDisp@ha
		lfs f1, float_901_8041bf50(r2)
		addi r5, r3, _btlStockExpDisp@l
		opword 0x38800001
		opword 0x38600008
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif
#pragma dont_inline reset

__declspec(section ".sdata") u32 g5_y_s1185;
__declspec(section ".sdata") u32 g5_x_s1184;
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
			pos.x = EXT_LIT(float_308_8041bf28, 308.0f) + x - 3.5f - 13.0f * i;
			pos.y = y - 220.0f;
			iconDispGx(&pos, 0x10, 0x18C, EXT_LIT(float_0p35_8041bf38, 0.35f));
		}
		for (i = 0; i < tens; i++) {
			Vec pos = {0.0f, 0.0f, -100.0f};
			pos.x = EXT_LIT(float_4_8041bf3c, 4.0f) + (EXT_LIT(float_308_8041bf28, 308.0f) + x - 10.0f - 20.0f * i);
			pos.y = EXT_LIT(float_16_8041bf48, 16.0f) + (y - 220.0f);
			iconDispGx(&pos, 0x10, 0x18C, EXT_LIT(float_0p5_8041bf4c, 0.5f));
		}
	}
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void _btlStockExpDisp(CameraId camId, void* param) {
	char _af_pad[28];
	asm volatile {
		lwz r3, _battleWorkPointer(r13)
		opword 0x80030F04
		opword 0x2C000000
		opword 0x40810164
		opword 0x2C000064
		opword 0x7C050378
		opword 0x40810008
		opword 0x38A00064
		opword 0x3800000A
		lis r3, double_to_int_802ede28@ha
		opword 0x7FE503D6
		lis r4, vec3_802ede0c@ha
		lfs f29, float_13_8041bf30(r2)
		li r27, 0x0
		lfd f28, double_to_int_802ede28@l(r3)
		addi r30, r4, vec3_802ede0c@l
		opword 0x1C1F000A
		lfs f27, float_308_8041bf28(r2)
		lfs f26, float_3p5_8041bf2c(r2)
		opword 0x3FA04330
		lfs f25, float_220_8041bf34(r2)
		opword 0x7F802850
		opword 0x48000068
		opword 0x6F608000
		lfs f0, g5_x_s1184(r13)
		opword 0x90010024
		la r3, _af_pad+12
		opword 0xEC3B002A
		lfs f0, g5_y_s1185(r13)
		opword 0x93A10020
		opword 0x38800010
		opword 0x80FE0000
		opword 0xEC00C828
		opword 0xC8610020
		opword 0xEC41D028
		opword 0x80DE0004
		opword 0x38A0018C
		opword 0xEC63E028
		opword 0x801E0008
		opword 0x90C10018
		lfs f1, float_0p35_8041bf38(r2)
		opword 0xEC5D10FC
		opword 0x90E10014
		opword 0x9001001C
		opword 0xD0410014
		opword 0xD0010018
		bl iconDispGx
		opword 0x3B7B0001
		opword 0x7C1BE000
		opword 0x4180FF98
		lis r3, double_to_int_802ede28@ha
		lis r4, vec3_802ede18@ha
		lfs f25, float_4_8041bf3c(r2)
		addi r29, r4, vec3_802ede18@l
		lfs f26, float_20_8041bf44(r2)
		opword 0x3B800000
		lfd f27, double_to_int_802ede28@l(r3)
		opword 0x3FC04330
		lfs f28, float_308_8041bf28(r2)
		lfs f29, float_10_8041bf40(r2)
		lfs f30, float_16_8041bf48(r2)
		lfs f31, float_220_8041bf34(r2)
		opword 0x48000070
		opword 0x6F808000
		lfs f0, g5_x_s1184(r13)
		opword 0x90010024
		opword 0x38610008
		opword 0xEC3C002A
		lfs f0, g5_y_s1185(r13)
		opword 0x93C10020
		opword 0x38800010
		opword 0xEC00F828
		opword 0x80DD0000
		opword 0xC8610020
		opword 0xEC41E828
		opword 0x80BD0004
		opword 0xEC1E002A
		opword 0xEC63D828
		opword 0x801D0008
		opword 0x90A1000C
		lfs f1, float_0p5_8041bf4c(r2)
		opword 0x38A0018C
		opword 0xEC5A10FC
		opword 0x90C10008
		opword 0xEC59102A
		opword 0x90010010
		opword 0xD001000C
		opword 0xD0410008
		bl iconDispGx
		opword 0x3B9C0001
		opword 0x7C1CF800
		opword 0x4180FF90
	}
}
#pragma pop
#endif


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset
#pragma force_active reset

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802eddd0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802edddc[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802edde8[3] = {-1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802eddf4[3] = {-1.0f, -1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ede00[3] = {1.0f, -1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ede0c[3] = {0.0f, 0.0f, -100.0f};
__declspec(section ".rodata") const f32 vec3_802ede18[3] = {0.0f, 0.0f, -100.0f};
__declspec(section ".rodata") const f64 double_to_int_802ede28 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_to_int_mask_802ede30 = 4503599627370496.0;
__declspec(section ".rodata") const char str_802EDE38[8] = "p_b_st\0";
__declspec(section ".rodata") const char str_802EDE40[8] = "PM_Y_1B";
__declspec(section ".rodata") const char str_802EDE48[8] = "PM_C_1A";
__declspec(section ".rodata") const char str_802EDE50[8] = "PM_F_2\0";
__declspec(section ".rodata") const char str_802EDE58[8] = "PM_C_1B";
__declspec(section ".rodata") const char str_802EDE60[8] = "PM_F_1B";
__declspec(section ".rodata") const char str_802EDE68[8] = "PM_F_1A";
__declspec(section ".rodata") const char str_802EDE70[8] = "PM_Y_1A";
__declspec(section ".rodata") const f64 double_10_802ede78 = 10.0;
__declspec(section ".rodata") const f64 double_1_802ede80 = 1.0;
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
__declspec(section ".sdata2") const u32 gap_09_8041BF94_sdata2[1] = {0};
#endif
