#include "eff/n64/eff_kemuri1_n64.h"
#include "memory.h"
#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct effKemuri1Data {
	u16 type; //0x0
	u8 align_2[2]; //0x2, TODO: verify align
	Vec position; //0x4
	u8 field_0x10[0x38 - 0x10]; //0x10
	s32 field_0x38; //0x38
	s32 field_0x3C; //0x3C
	u8 field_0x40[0x4C - 0x40]; //0x40
	s32 field_0x4C; //0x4C
} effKemuri1Data;

//local prototypes
void effKemuri1Main(EffectEntry* effect);

EffectEntry* effKemuri1N64Entry(s32 type, f32 x, f32 y, f32 z, f32 a5) {
	EffectEntry* effect;
	s32 effCount;
	effKemuri1Data* data;

	effect = effEntry();
	switch (type) {
		case 2:
			effCount = 1;
			break;
		case 3:
			effCount = 4;
			break;
		case 4: //TODO: -strict off, case 4 ... 7:?
		case 5:
		case 6:
		case 7:
			effCount = 9;
			break;
		default:
			effCount = 3;
			break;
	}

	effect->type = "Kemuri1N64";
	effect->count = effCount;
	data = __memAlloc(HEAP_EFFECT, sizeof(effKemuri1Data) * effCount);
	effect->userdata = data;
	effect->callback = effKemuri1Main;
	switch (type) {
		case 0:
		case 1:
			data->field_0x38 = 0;
			data->field_0x4C = 15;
			break;
		case 2:
			data->field_0x38 = 3;
			data->field_0x4C = 65;
			break;
		case 3:
			data->field_0x38 = 2;
			data->field_0x4C = 129;
		case 4: //TODO: -strict off, case 4 ... 7:?
		case 5:
		case 6:
		case 7:
			data->field_0x38 = 3;
			data->field_0x4C = 65;
			break;
		default:
			break;
	}
}

void effKemuri1Main(EffectEntry* effect) {

}

typedef struct effKemuri1Work {
	u16 type; //0x0
	u8 pad_2[2];
	Vec position; //0x4
	u8 field_0x10[0x40 - 0x10];
	s32 timer; //0x40
	u8 r, g, b; //0x44
	u8 pad_47;
	s32 field_0x48;
	u8 pad_4C[4];
} effKemuri1Work;

void effKemuri1Disp(CameraId cameraId, EffectEntry* effect) {
	Mtx mtx, scale, rot, view;
	GXTexObj tex;
	effKemuri1Work* work;
	CameraEntry* camera;
	s32 type;
	s32 i, j;
	f32 s, ofsS, ofsT;
	s32 a, b;

	work = effect->userdata;
	camera = camGetPtr(cameraId);
	type = work->type;
	a = work->timer;
	b = work->field_0x48;
	s = 1.0f;
	switch (type) {
		case 5:
		case 6:
		case 7:
			s = 0.5f;
			break;
	}
	PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
	PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
	PSMTXScale(scale, s, s, s);
	PSMTXConcat(mtx, rot, mtx);
	PSMTXConcat(mtx, scale, mtx);
	PSMTXConcat(camera->view, mtx, view);
	effGetTexObj(0x28, &tex);
	GXLoadTexObj(&tex, GX_TEXMAP0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTexGens(2);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
	GXSetNumTevStages(3);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
	GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
	GXSetTevColor(GX_TEVREG0, (GXColor){0x80, 0x80, 0x80, 0x80});
	GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	ofsS = 0.0625f * a;
	ofsT = 0.0625f * b;
	for (i = 1, work++; i < effect->count; i++, work++) {
		f32 h;
		f32 w;
		if (work->timer > 15) {
			continue;
		}
		PSMTXTrans(mtx, ofsS, 0.0f, 0.0f);
		PSMTXScale(scale, 0.0625f, 1.0f, 1.0f);
		PSMTXConcat(mtx, scale, mtx);
		GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
		PSMTXTrans(mtx, ofsT, 0.0f, 0.0f);
		PSMTXScale(scale, 0.0625f, 1.0f, 1.0f);
		PSMTXConcat(mtx, scale, mtx);
		GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX2x4);
		s = 0.5f;
		for (j = 0; j < 2; j++) {
			if (j == 0) {
				GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0x60});
				PSMTXTrans(mtx, work->position.x + 2.0f, work->position.y - 2.0f, work->position.z);
				PSMTXConcat(view, mtx, mtx);
				GXLoadPosMtxImm(mtx, GX_PNMTX0);
			} else {
				GXSetChanMatColor(GX_COLOR0A0, (GXColor){work->r, work->g, work->b, 0xFF});
				PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
				PSMTXConcat(view, mtx, mtx);
				GXLoadPosMtxImm(mtx, GX_PNMTX0);
			}
			GXBegin(GX_QUADS, GX_VTXFMT0, 4);
			switch (type) {
				case 0:
					w = h = 16.0f;
					break;
				case 1:
					w = h = 24.0f;
					break;
				default:
					w = h = 32.0f;
					break;
			}
			GXPosition3f32(-w * s, h * s, 0.0f);
			GXTexCoord2f32(0.0f, 0.0f);
			GXPosition3f32(w * s, h * s, 0.0f);
			GXTexCoord2f32(1.0f, 0.0f);
			GXPosition3f32(w * s, -h * s, 0.0f);
			GXTexCoord2f32(1.0f, 1.0f);
			GXPosition3f32(-w * s, -h * s, 0.0f);
			GXTexCoord2f32(0.0f, 1.0f);
		}
	}
}
