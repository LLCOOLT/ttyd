#include "eff/eff_nice.h"
#include "driver/animdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include <string.h>
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/gx.h>

extern GlobalWork* gp;

//.sdata
const char* anim_jp[] = {
	"EFF_nice",
	"EFF_good",
	"EFF_great",
	"EFF_wonderful",
	"EFF_excellent",
	NULL,
	"EFF_lucky"
};
const char* anim_us[] = {
	"EFF_nice_us",
	"EFF_good_us",
	"EFF_great_us",
	"EFF_wonderful_us",
	"EFF_excellent_us",
	NULL,
	"EFF_lucky_us"
};
const char** anim_tbl[2] = { anim_jp, anim_us };
s32 acrobat_jp[] = {179, 180, 181, 182, 183, 184, 185};
s32 acrobat_us[] = {183, 184, 185, 186, 187, 188}; //includes nonexistant textures
s32* acrobat_tbl[2] = { acrobat_jp, acrobat_us };

//forward declarations
static void rendermodeFunc(s32 wXluStage);
void effNiceMain(EffectEntry* effect);

BOOL effNiceAsync(s32 group) {
	int i;
	BOOL valid;
	const char* name;

	valid = TRUE;
	for (i = 0; i < 7; i++) {
		name = anim_tbl[gp->language][i];
		if (name && !animGroupBaseAsync(name, group, NULL)) {
			valid = FALSE;
		}
	}
	return valid;
}

static void rendermodeFunc(s32 wXluStage) {
	AnimationWork* wp = animGetPtr();

	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
	wp->currDispMode = wXluStage;
}

EffectEntry* effNiceEntry(s32 type, f32 x, f32 y, f32 z) {
	NiceEffectWork *userdata, *ptr;
	EffectEntry* effect;
	u32 size, count;
	int i;

	effect = effEntry();
	if (type == 5) { //guard for unused slot
		type = 0 & 0xFFu;
	}
	switch (type) {
		case 7:
			if ((u32)gp->language == 0) {
				count = 8;
			} else {
				count = 7;
			}
			break;
		default:
			count = 1;
			break;
	}
	effect->type = "Nice";
	size = count * sizeof(NiceEffectWork);
	effect->count = count;
	userdata = __memAlloc(HEAP_EFFECT, size);
	effect->userdata = userdata;
	memset(userdata, 0, size);
	effect->callback = effNiceMain;
	effect->flags |= 2;
	userdata->type = type;
	userdata->position.x = x;
	userdata->position.y = y;
	userdata->position.z = z;
	userdata->field_0x10 = 1.0f;
	userdata->field_0x14 = 1.0f;
	userdata->field_0x18 = 1.0f;
	userdata->field_0x1C = 1.0f;
	userdata->poseId = -1;
	switch (type) {
	case 7:
		ptr = userdata + 1;
		for (i = 1; i < effect->count; i++, ptr++) {
			ptr->position.x = 1000.0f;
			ptr->position.y = 0.0f;
			ptr->position.z = 0.0f;
			ptr->field_0x10 = 1.0f;
			ptr->field_0x14 = 1.0f;
			ptr->field_0x18 = 1.0f;
			ptr->field_0x28 = 0;
			ptr->field_0x20 = 0;
		}
		break;
	default:
		size = gp->inBattle != 0;
		userdata->poseId = animPoseEntry(anim_tbl[gp->language][type], size);
		animPoseSetAnim(userdata->poseId, "A_1", TRUE);
		animPoseSetMaterialFlagOn(userdata->poseId, 0x1800);
		animPoseSetGXFunc(userdata->poseId, rendermodeFunc, FALSE);
		break;
	}
	return effect;
}

void effNiceMain(EffectEntry* effect) {

}

void effNiceDisp(CameraId cameraId, void* param) {
	EffectEntry* effect = param;
	NiceEffectWork* wp = effect->userdata;
	Mtx trans, rot, scale, mtx;

	PSMTXTrans(trans, wp->position.x, wp->position.y, wp->position.z);
	PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
	PSMTXScale(scale, wp->field_0x1C, wp->field_0x1C, wp->field_0x1C);
	PSMTXConcat(trans, rot, mtx);
	PSMTXConcat(mtx, scale, mtx);
	PSMTXScale(scale, 8.0f, 8.0f, 8.0f);
	PSMTXConcat(mtx, scale, mtx);
	animPoseDrawMtx(wp->poseId, mtx, 1, 0.0f, 1.0f);
	animPoseDrawMtx(wp->poseId, mtx, 2, 0.0f, 1.0f);
	animPoseDrawMtx(wp->poseId, mtx, 3, 0.0f, 1.0f);
}

void effAcrobatDisp(CameraId cameraId, void* param);

void acrobatMain(EffectEntry* effect) {
	NiceEffectWork* wp = effect->userdata;
	int done = 0;
	Vec pos;
	Vec tmp = {0.0f, 0.0f, 0.0f};
	int i;

	tmp.x = wp->position.x;
	tmp.y = wp->position.y;
	tmp.z = wp->position.z;
	pos = tmp;
	wp++;
	for (i = 1; i < effect->count; i++, wp++) {
		switch (wp->field_0x28) {
		case 0:
			wp->field_0x20 = i * 4;
			wp->field_0x28++;
			if (i == 1) {
				psndSFXOn("SFX_SYSTEM_ACROBAT1");
			}
			break;
		case 1:
			wp->field_0x20--;
			if (wp->field_0x20 < 0) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 2:
			wp->field_0x20++;
			wp->position.x = intplGetValue(12, wp->field_0x20, 30, 500.0f, i * 4);
			if (wp->field_0x20 >= 30) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 3:
			wp->field_0x20++;
			wp->field_0x10 = intplGetValue(12, wp->field_0x20, 8, 1.0f, 0.4f);
			wp->field_0x14 = intplGetValue(12, wp->field_0x20, 8, 1.0f, 1.5f);
			if (wp->field_0x20 >= 8) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 4:
			wp->field_0x20++;
			if (wp->field_0x20 > (effect->count - i - 1) * 4) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 5:
			wp->field_0x20++;
			wp->position.x = intplGetValue(8, wp->field_0x20, 30, i * 4, i * 12);
			wp->field_0x10 = intplGetValue(12, wp->field_0x20, 30, 0.2f, 1.0f);
			wp->field_0x14 = intplGetValue(12, wp->field_0x20, 30, 1.5f, 1.0f);
			if (wp->field_0x20 >= 30) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 6:
			wp->field_0x20++;
			if (wp->field_0x20 > 16) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 7:
			wp->field_0x20++;
			wp->field_0x10 = intplGetValue(12, wp->field_0x20, 15, 1.0f, 1.5f);
			wp->field_0x14 = intplGetValue(12, wp->field_0x20, 15, 1.0f, 0.1f);
			if (wp->field_0x20 >= 15) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 8:
			wp->field_0x20++;
			wp->field_0x10 = intplGetValue(12, wp->field_0x20, 15, 1.5f, 0.1f);
			wp->field_0x14 = intplGetValue(12, wp->field_0x20, 15, 0.1f, 2.0f);
			if (wp->field_0x20 >= 15) {
				wp->field_0x20 = 0;
				wp->field_0x28++;
			}
			break;
		case 9:
			done++;
			wp->field_0x10 = wp->field_0x14 = wp->field_0x18 = 0.0f;
			break;
		}
	}
	if (done >= effect->count - 1) {
		effDelete(effect);
	} else {
		dispEntry(CAMERA_3D, dispCalcZ(&pos), 8, effAcrobatDisp, effect);
	}
}

void effAcrobatDisp(CameraId cameraId, void* param) {
	EffectEntry* effect = param;
	NiceEffectWork* wp = effect->userdata;
	CameraEntry* camera = camGetPtr(cameraId);
	Mtx trans, rot, scale, mtx;
	GXTexObj tex;
	f32 size, half, ofsX, ofsY;
	int i;

	PSMTXTrans(trans, wp->position.x, wp->position.y, wp->position.z);
	PSMTXScale(scale, wp->field_0x1C, wp->field_0x1C, wp->field_0x1C);
	PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
	PSMTXConcat(trans, rot, mtx);
	PSMTXConcat(mtx, scale, mtx);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	{
		GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
		GXSetChanMatColor(GX_COLOR0A0, color);
	}
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	size = 20.0f;
	size = -size;
	half = size * 0.5f;
	wp++;
	for (i = 1; i < effect->count; i++, wp++) {
		if (wp->field_0x28 < 6) {
			ofsX = size * 0.5f;
			ofsY = 0.0f;
		} else {
			ofsX = 0.0f;
			ofsY = size * 0.5f;
		}
		PSMTXTrans(trans, wp->position.x, wp->position.y, wp->position.z);
		PSMTXTrans(rot, ofsX, ofsY, 0.0f);
		PSMTXScale(scale, wp->field_0x10, wp->field_0x14, wp->field_0x18);
		PSMTXConcat(rot, scale, scale);
		PSMTXTrans(rot, -ofsX, -ofsY, 0.0f);
		PSMTXConcat(scale, rot, scale);
		PSMTXConcat(trans, scale, scale);
		PSMTXConcat(mtx, scale, scale);
		PSMTXConcat(camera->view, scale, scale);
		GXLoadPosMtxImm(scale, 0);
		GXSetCurrentMtx(0);
		effGetTexObj(acrobat_tbl[gp->language][i - 1], &tex);
		GXLoadTexObj(&tex, GX_TEXMAP0);
		GXBegin(GX_QUADS, GX_VTXFMT0, 4);
		GXPosition3f32(half, 10.0f, 0.0f);
		GXTexCoord2f32(0.0f, 0.0f);
		GXPosition3f32(10.0f, 10.0f, 0.0f);
		GXTexCoord2f32(1.0f, 0.0f);
		GXPosition3f32(10.0f, half, 0.0f);
		GXTexCoord2f32(1.0f, 1.0f);
		GXPosition3f32(half, half, 0.0f);
		GXTexCoord2f32(0.0f, 1.0f);
	}
}
