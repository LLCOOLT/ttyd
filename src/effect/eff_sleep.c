#include "eff/eff_sleep.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "memory.h"
#include "mario/mariost.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern double sin(double x);
extern double cos(double x);

//local prototypes
void effSleepDisp(CameraId camId, EffectEntry* effect);

EffectEntry* effSleepEntry(s32 a1, s32 a2, f32 x, f32 y, f32 z, f32 scale, f32 rotation) {
	EffectEntry* effect;
	effSleepData* data;
	f32 radians;
	s32 smth;
	int i;
	
	effect = effEntry();
	effect->type = "Sleep";
	effect->count = 4;
	data = __memAlloc(HEAP_EFFECT, effect->count * sizeof(effSleepData));
	effect->userdata = data;
	effect->callback = effSleepMain;
	effect->flags |= 2;
	data->field_0x0 = a1;
	data->position.x = x;
	data->position.y = y;
	data->position.z = z;
	data->scale = scale;
	data->field_0x14 = 0;
	if (a2 <= 0) {
		data->field_0x18 = 1000;
	}
	else {
		data->field_0x18 = a2;
	}
	data->field_0x1C = 0;

	radians = (6.2831855f * rotation) / 360.0f; //TODO: get radians to f26
	for (data++, smth = 16, i = 1; i < effect->count; data++, smth += 16, i++) {
		data->position.x = (16.0f * (f32)i) * (f32)cos(radians);
		data->position.y = (16.0f * (f32)i) * (f32)sin(radians);
		data->position.z = 0.0f;
		data->scale = (0.2f * (f32)i) + 1.0f;
		data->field_0x14 = 0;
		data->field_0x20 = smth;
	}
	return effect;
}

void effSleepMain(EffectEntry* effect) {
	effSleepData* data = effect->userdata;
	Vec position;
	int i;

	position = (Vec){ data->position.x, data->position.y, data->position.z };
	if (effect->flags & 4) {
		effect->flags &= ~4;
		data->field_0x18 = 16;
	}
	if (data->field_0x18 < 1000) {
		data->field_0x18--;
	}
	if (data->field_0x18 < 32) {
		data->field_0x14 = data->field_0x18 * 8;
	}
	if (data->field_0x18 < 0) {
		effDelete(effect);
		return;
	}
	data->field_0x1C++;
	if (data->field_0x1C < 32) {
		data->field_0x14 = data->field_0x1C * 8 + 7;
	}
	for (i = 1, data++; i < effect->count; i++, data++) {
		if (data->field_0x20 != 0) {
			data->field_0x20--;
		}
		else {
			data->field_0x14 += 8;
			if (data->field_0x14 > 255) {
				data->field_0x14 = 255;
			}
		}
	}
	dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effSleepDisp, effect);
}

#pragma push
#pragma opt_propagation off
#pragma opt_lifetimes off
void effSleepDisp(CameraId camId, EffectEntry* effect) {
	effSleepData* data = effect->userdata;
	CameraEntry* cam;
	s32 alpha;
	Mtx mtx;
	Mtx scale;
	Mtx rot;
	Mtx res;
	GXTexObj texObj;
	f32 w;
	f32 x0;
	f32 tau;
	f32 k;
	f32 half;
	f32 one;
	f32 s0, s1;
	s32 base;
	s32 off;
	s32 j;
	int i;

	cam = camGetPtr(camId);
	alpha = data->field_0x14;

	PSMTXTrans(mtx, data->position.x, data->position.y, data->position.z);
	PSMTXScale(scale, data->scale, data->scale, data->scale);
	PSMTXRotRad(rot, 'y', MTXDegToRad(-camGetPtr(camId)->viewYaw));
	PSMTXConcat(mtx, rot, mtx);
	PSMTXConcat(mtx, scale, res);
	PSMTXConcat(cam->view, res, res);

	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	effGetTexObj(0x8C, &texObj);
	GXLoadTexObj(&texObj, GX_TEXMAP0);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	w = 8.0f;
	x0 = -w;
	base = 50;
	for (i = 1, data++; i < effect->count; i++, data++, base += 50) {
		if (data->field_0x20 == 0) {
			GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 0xFF, 0xFF, 0xFF, data->field_0x14 * alpha / 255 });
			PSMTXTrans(mtx, data->position.x, data->position.y, data->position.z);
			PSMTXScale(scale, data->scale, data->scale, data->scale);
			PSMTXConcat(mtx, scale, mtx);
			PSMTXConcat(res, mtx, mtx);
			GXLoadPosMtxImm(mtx, GX_PNMTX0);
			GXSetCurrentMtx(GX_PNMTX0);
			tau = 6.2831855f;
			k = 0.015625f;
			half = 0.5f;
			one = 1.0f;
			j = 0;
			off = 0;
			do {
				s0 = half * (f32)sin((tau * (f32)(gp->retraceCount + (base + off))) * k);
				s1 = half * (f32)sin((tau * (f32)(gp->retraceCount + (base + (j + 1) * 10))) * k);
				GXBegin(GX_QUADS, GX_VTXFMT0, 4);
				GXPosition3f32(x0 * half + s1, one * (f32)(j + 1), 0.0f);
				GXTexCoord2f32(0.0f, 0.125f * (f32)(7 - j));
				GXPosition3f32(4.0f + s1, one * (f32)(j + 1), 0.0f);
				GXTexCoord2f32(1.0f, 0.125f * (f32)(7 - j));
				GXPosition3f32(4.0f + s0, one * (f32)j, 0.0f);
				GXTexCoord2f32(1.0f, 0.125f * (f32)(8 - j));
				GXPosition3f32(x0 * half + s0, one * (f32)j, 0.0f);
				GXTexCoord2f32(0.0f, 0.125f * (f32)(8 - j));
				j++;
				off += 10;
			} while (j < 8);
		}
	}
}
#pragma pop
