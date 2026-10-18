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

#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 float_0_8041cbb0;
extern const f32 float_1_8041cbb8;
#endif

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
static const char** anim_tbl[2] = { anim_jp, anim_us };
s32 acrobat_jp[] = {179, 180, 181, 182, 183, 184, 185};
s32 acrobat_us[] = {183, 184, 185, 186, 187, 188}; //includes nonexistant textures
s32* acrobat_tbl[2] = { acrobat_jp, acrobat_us };
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80411CDC_sdata[1] = {0};
#pragma force_active reset
 // unreferenced zero word in target

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
	userdata->scaleX = EXT_LIT(float_1_8041cbb8, 1.0f);
	userdata->scaleY = EXT_LIT(float_1_8041cbb8, 1.0f);
	userdata->scaleZ = EXT_LIT(float_1_8041cbb8, 1.0f);
	userdata->field_0x1C = EXT_LIT(float_1_8041cbb8, 1.0f);
	userdata->poseId = -1;
	switch (type) {
	case 7:
		ptr = userdata + 1;
		for (i = 1; i < effect->count; i++, ptr++) {
			ptr->position.x = 1000.0f;
			ptr->position.y = EXT_LIT(float_0_8041cbb0, 0.0f);
			ptr->position.z = EXT_LIT(float_0_8041cbb0, 0.0f);
			ptr->scaleX = EXT_LIT(float_1_8041cbb8, 1.0f);
			ptr->scaleY = EXT_LIT(float_1_8041cbb8, 1.0f);
			ptr->scaleZ = EXT_LIT(float_1_8041cbb8, 1.0f);
			ptr->state = 0;
			ptr->timer = 0;
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

void effNiceDisp(CameraId cameraId, void* param);
void acrobatMain(EffectEntry* effect);

#ifdef NONMATCHING
void effNiceMain(EffectEntry* effect) {
	NiceEffectWork* wp = effect->userdata;
	Vec pos;
	Vec tmp = {0.0f, 0.0f, 0.0f};
	s32 type;
	AnimationPose* pose;
	AnimData* data;
	f32 start, len, t;

	tmp.x = wp->position.x;
	tmp.y = wp->position.y;
	tmp.z = wp->position.z;
	pos = tmp;
	type = wp->type;
	if (effect->flags & 4) {
		effect->flags &= ~4;
		if (wp->poseId != -1) {
			animPoseRelease(wp->poseId);
		}
		effDelete(effect);
		return;
	}
	if (wp->poseId != -1) {
		pose = animPoseGetAnimPosePtr(wp->poseId);
		data = animPoseGetAnimDataPtr(wp->poseId);
		animPoseMain(wp->poseId);
		switch (type) {
		case 0:
		case 1: {
			len = *(f32*)((u8*)*(void**)((u8*)data + 0x24) + 8);
			start = ((u32)gp->language == 0) ? 32.0f : 34.0f;
			if (pose->localFrame > start) {
				t = 1.0f - (pose->localFrame - start) / (len - start);
				if (t < 0.0f) t = 0.0f;
				animPoseSetMaterialFlagOn(wp->poseId, 0x40);
				animPoseSetMaterialEvtColor(wp->poseId, (GXColor){0xFF, 0xFF, 0xFF, 255.0f * t});
			}
			break;
		}
		case 2: {
			len = *(f32*)((u8*)*(void**)((u8*)data + 0x24) + 8);
			start = ((u32)gp->language == 0) ? 35.0f : 37.0f;
			if (pose->localFrame > start) {
				t = 1.0f - (pose->localFrame - start) / (len - start);
				if (t < 0.0f) t = 0.0f;
				animPoseSetMaterialFlagOn(wp->poseId, 0x40);
				animPoseSetMaterialEvtColor(wp->poseId, (GXColor){0xFF, 0xFF, 0xFF, 255.0f * t});
			}
			break;
		}
		case 3: {
			len = *(f32*)((u8*)*(void**)((u8*)data + 0x24) + 8);
			start = ((u32)gp->language == 0) ? 45.0f : 40.0f;
			if (pose->localFrame > start) {
				t = 1.0f - (pose->localFrame - start) / (len - start);
				if (t < 0.0f) t = 0.0f;
				animPoseSetMaterialFlagOn(wp->poseId, 0x40);
				animPoseSetMaterialEvtColor(wp->poseId, (GXColor){0xFF, 0xFF, 0xFF, 255.0f * t});
			}
			break;
		}
		case 4: {
			len = *(f32*)((u8*)*(void**)((u8*)data + 0x24) + 8);
			start = ((u32)gp->language == 0) ? 48.0f : 40.0f;
			if (pose->localFrame > start) {
				t = 1.0f - (pose->localFrame - start) / (len - start);
				if (t < 0.0f) t = 0.0f;
				animPoseSetMaterialFlagOn(wp->poseId, 0x40);
				animPoseSetMaterialEvtColor(wp->poseId, (GXColor){0xFF, 0xFF, 0xFF, 255.0f * t});
			}
			break;
		}
		case 6:
			break;
		}
		if (animPoseGetLoopTimes(wp->poseId) >= 1.0f) {
			animPoseRelease(wp->poseId);
			effDelete(effect);
			return;
		}
	}
	if (type == 7) {
		acrobatMain(effect);
	} else {
		dispEntry(CAMERA_3D, dispCalcZ(&pos), 8, effNiceDisp, effect);
	}
}
#endif

#ifdef NONMATCHING
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
#endif

void effAcrobatDisp(CameraId cameraId, void* param);

#ifdef NONMATCHING
void acrobatMain(EffectEntry* effect) {
	NiceEffectWork* wp = effect->userdata;
	int i;
	int done = 0;
	Vec pos;
	Vec tmp = {0.0f, 0.0f, 0.0f};

	tmp.x = wp->position.x;
	tmp.y = wp->position.y;
	tmp.z = wp->position.z;
	pos = tmp;
	for (i = 1, wp++; i < effect->count; i++, wp++) {
		char* sfx2 = "SFX_SYSTEM_ACROBAT1";
		switch (wp->state) {
		case 0:
			wp->timer = i * 4;
			wp->state++;
			if (i == 1) {
				psndSFXOn(sfx2);
			}
			break;
		case 1:
			wp->timer--;
			if (wp->timer < 0) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 2:
			wp->timer++;
			wp->position.x = intplGetValue(12, wp->timer, 30, 500.0f, i * 4);
			if (wp->timer >= 30) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 3:
			wp->timer++;
			wp->scaleX = intplGetValue(12, wp->timer, 8, 1.0f, 0.4f);
			wp->scaleY = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(12, 1.0f, 1.5f, wp->timer, 8);
			if (wp->timer >= 8) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 4:
			wp->timer++;
			if (wp->timer > (effect->count - i - 1) * 4) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 5:
			wp->timer++;
			wp->position.x = intplGetValue(8, wp->timer, 30, i * 4, i * 12);
			wp->scaleX = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(12, 0.2f, 1.0f, wp->timer, 30);
			wp->scaleY = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(12, 1.5f, 1.0f, wp->timer, 30);
			if (wp->timer >= 30) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 6:
			wp->timer++;
			if (wp->timer > 16) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 7:
			wp->timer++;
			wp->scaleX = intplGetValue(12, wp->timer, 15, 1.0f, 1.5f);
			wp->scaleY = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(12, 1.0f, 0.1f, wp->timer, 15);
			if (wp->timer >= 15) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 8:
			wp->timer++;
			wp->scaleX = intplGetValue(12, wp->timer, 15, 1.5f, 0.1f);
			wp->scaleY = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(12, 0.1f, 2.0f, wp->timer, 15);
			if (wp->timer >= 15) {
				wp->timer = 0;
				wp->state++;
			}
			break;
		case 9:
			done++;
			wp->scaleX = wp->scaleY = wp->scaleZ = 0.0f;
			break;
		}
	}
	if (done >= effect->count - 1) {
		effDelete(effect);
	} else {
		dispEntry(CAMERA_3D, dispCalcZ(&pos), 8, effAcrobatDisp, effect);
	}
}
#endif

#ifdef NONMATCHING
void effAcrobatDisp(CameraId cameraId, void* param) {
	EffectEntry* effect = param;
	NiceEffectWork* wp = effect->userdata;
	CameraEntry* camera = camGetPtr(cameraId);
	Mtx trans, rot, scale, mtx;
	GXTexObj tex;
	f32 size, half, ofsX, ofsY, ten;
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
	ten = 10.0f;
	size = -size;
	half = size; half *= 0.5f;
	wp++;
	for (i = 1; i < effect->count; i++, wp++) {
		if (wp->state < 6) {
			ofsX = size / 2.0f;
			ofsY = 0.0f;
		} else {
			ofsX = 0.0f;
			ofsY = size / 2.0f;
		}
		PSMTXTrans(trans, wp->position.x, wp->position.y, wp->position.z);
		PSMTXTrans(rot, ofsX, ofsY, 0.0f);
		PSMTXScale(scale, wp->scaleX, wp->scaleY, wp->scaleZ);
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
		GXPosition3f32(half, ten, 0.0f);
		GXTexCoord2f32(0.0f, 0.0f);
		GXPosition3f32(ten, ten, 0.0f);
		GXTexCoord2f32(1.0f, 0.0f);
		GXPosition3f32(ten, half, 0.0f);
		GXTexCoord2f32(1.0f, 1.0f);
		GXPosition3f32(half, half, 0.0f);
		GXTexCoord2f32(0.0f, 1.0f);
	}
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): effNiceMain (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".rodata") const f32 vec3_802f3748[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3754[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_802F3760[] = "SFX_SYSTEM_ACROBAT1";
__declspec(section ".rodata") const f64 double_to_int_802f3778 = 4503601774854144.0;
__declspec(section ".sdata2") const u32 dat_8041cb90 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_8041cb94 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_8041cb98 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_8041cb9c = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_8041cba0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0p017453_8041cba4 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_20_8041cba8 = 20.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041cbac = 0.5f;
__declspec(section ".sdata2") const f32 float_0_8041cbb0 = 0.0f;
__declspec(section ".sdata2") const f32 float_10_8041cbb4 = 10.0f;
__declspec(section ".sdata2") const f32 float_1_8041cbb8 = 1.0f;
__declspec(section ".sdata2") const f32 float_500_8041cbbc = 500.0f;
__declspec(section ".sdata2") const f32 float_0p4_8041cbc0 = 0.4f;
__declspec(section ".sdata2") const f32 float_1p5_8041cbc4 = 1.5f;
__declspec(section ".sdata2") const f32 float_0p2_8041cbc8 = 0.2f;
__declspec(section ".sdata2") const f32 float_0p1_8041cbcc = 0.1f;
__declspec(section ".sdata2") const f32 float_2_8041cbd0 = 2.0f;
__declspec(section ".sdata2") const f32 float_8_8041cbd4 = 8.0f;
__declspec(section ".sdata2") const f32 float_32_8041cbd8 = 32.0f;
__declspec(section ".sdata2") const f32 float_34_8041cbdc = 34.0f;
__declspec(section ".sdata2") const f32 float_255_8041cbe0 = 255.0f;
__declspec(section ".sdata2") const f32 float_35_8041cbe4 = 35.0f;
__declspec(section ".sdata2") const f32 float_37_8041cbe8 = 37.0f;
__declspec(section ".sdata2") const f32 float_45_8041cbec = 45.0f;
__declspec(section ".sdata2") const f32 float_40_8041cbf0 = 40.0f;
__declspec(section ".sdata2") const f32 float_48_8041cbf4 = 48.0f;

void acrobatMain(EffectEntry* effect);
__declspec(section ".data") static void* jumptable_8036FF10[] = {
    (char*)acrobatMain + 0xAC,
    (char*)acrobatMain + 0xD0,
    (char*)acrobatMain + 0x100,
    (char*)acrobatMain + 0x168,
    (char*)acrobatMain + 0x1D0,
    (char*)acrobatMain + 0x210,
    (char*)acrobatMain + 0x2C0,
    (char*)acrobatMain + 0x2F0,
    (char*)acrobatMain + 0x358,
    (char*)acrobatMain + 0x3C0,
};
asm void effAcrobatDisp(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0x160(r1)
	mflr r0
	stw r0, 0x164(r1)
	stfd f31, 0x150(r1)
	psq_st f31, 0x158(r1), 0, 0
	stfd f30, 0x140(r1)
	psq_st f30, 0x148(r1), 0, 0
	stfd f29, 0x130(r1)
	psq_st f29, 0x138(r1), 0, 0
	stfd f28, 0x120(r1)
	psq_st f28, 0x128(r1), 0, 0
	stfd f27, 0x110(r1)
	psq_st f27, 0x118(r1), 0, 0
	stmw r26, 0xf8(r1)
	mr r26, r4
	mr r27, r3
	lwz r28, 0xc(r4)
	bl camGetPtr
	lfs f1, 0x4(r28)
	mr r30, r3
	lfs f2, 0x8(r28)
	addi r3, r1, 0xbc
	lfs f3, 0xc(r28)
	bl PSMTXTrans
	lfs f1, 0x1c(r28)
	addi r3, r1, 0x5c
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r27
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x8c
	lfs f0, float_0p017453_8041cba4(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r3, r1, 0xbc
	addi r4, r1, 0x8c
	addi r5, r1, 0x2c
	bl PSMTXConcat
	addi r3, r1, 0x2c
	addi r4, r1, 0x5c
	mr r5, r3
	bl PSMTXConcat
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r0, dat_8041cba0(r2)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
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
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	bl GXSetTevOp
	li r3, 0x0
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
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
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	lfs f1, float_20_8041cba8(r2)
	li r27, 0x1
	lfs f0, float_0p5_8041cbac(r2)
	li r29, 0x4
	fneg f30, f1
	lfs f31, float_10_8041cbb4(r2)
	lis r31, 0xcc01
	addi r28, r28, 0x64
	fmuls f29, f30, f0
	b @1
	@2:
	lwz r0, 0x28(r28)
	cmpwi r0, 0x6
	bge @3
	lfs f0, float_0p5_8041cbac(r2)
	lfs f27, float_0_8041cbb0(r2)
	fmuls f28, f30, f0
	b @4
	@3:
	lfs f0, float_0p5_8041cbac(r2)
	lfs f28, float_0_8041cbb0(r2)
	fmuls f27, f30, f0
	@4:
	lfs f1, 0x4(r28)
	addi r3, r1, 0xbc
	lfs f2, 0x8(r28)
	lfs f3, 0xc(r28)
	bl PSMTXTrans
	fmr f1, f28
	lfs f3, float_0_8041cbb0(r2)
	fmr f2, f27
	addi r3, r1, 0x8c
	bl PSMTXTrans
	lfs f1, 0x10(r28)
	addi r3, r1, 0x5c
	lfs f2, 0x14(r28)
	lfs f3, 0x18(r28)
	bl PSMTXScale
	addi r4, r1, 0x5c
	addi r3, r1, 0x8c
	mr r5, r4
	bl PSMTXConcat
	fneg f1, f28
	lfs f3, float_0_8041cbb0(r2)
	fneg f2, f27
	addi r3, r1, 0x8c
	bl PSMTXTrans
	addi r3, r1, 0x5c
	addi r4, r1, 0x8c
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0x5c
	addi r3, r1, 0xbc
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x5c
	addi r3, r1, 0x2c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x5c
	addi r3, r30, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x5c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r5, gp(r13)
	la r3, acrobat_tbl(r13)
	subi r0, r29, 0x4
	addi r4, r1, 0xc
	lwz r5, 0x16c(r5)
	slwi r5, r5, 2
	lwzx r3, r3, r5
	lwzx r3, r3, r0
	bl effGetTexObj
	addi r3, r1, 0xc
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	stfs f29, -0x8000(r31)
	addi r27, r27, 0x1
	addi r29, r29, 0x4
	addi r28, r28, 0x64
	stfs f31, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	stfs f31, -0x8000(r31)
	stfs f31, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_1_8041cbb8(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	stfs f31, -0x8000(r31)
	stfs f29, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_1_8041cbb8(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_1_8041cbb8(r2)
	stfs f0, -0x8000(r31)
	stfs f29, -0x8000(r31)
	stfs f29, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041cbb0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_1_8041cbb8(r2)
	stfs f0, -0x8000(r31)
	@1:
	lwz r0, 0x8(r26)
	cmpw r27, r0
	blt @2
	psq_l f31, 0x158(r1), 0, 0
	lfd f31, 0x150(r1)
	psq_l f30, 0x148(r1), 0, 0
	lfd f30, 0x140(r1)
	psq_l f29, 0x138(r1), 0, 0
	lfd f29, 0x130(r1)
	psq_l f28, 0x128(r1), 0, 0
	lfd f28, 0x120(r1)
	psq_l f27, 0x118(r1), 0, 0
	lfd f27, 0x110(r1)
	lmw r26, 0xf8(r1)
	lwz r0, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x160
	blr
}

asm void acrobatMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r4, vec3_802f3754@ha
	stw r0, 0x54(r1)
	addi r6, r4, vec3_802f3754@l
	stmw r25, 0x34(r1)
	mr r25, r3
	li r26, 0x0
	li r27, 0x1
	li r31, 0x4
	li r30, 0xc
	lwz r28, 0xc(r3)
	lis r3, str_802F3760@ha
	lwz r5, 0x0(r6)
	addi r29, r3, str_802F3760@l
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x8(r1)
	lfs f2, 0x4(r28)
	stw r4, 0xc(r1)
	lfs f1, 0x8(r28)
	lfs f0, 0xc(r28)
	addi r28, r28, 0x64
	stw r0, 0x10(r1)
	stfs f2, 0x8(r1)
	stfs f1, 0xc(r1)
	lwz r4, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	b @1
	@2:
	lwz r0, 0x28(r28)
	cmplwi r0, 0x9
	bgt @3
	lis r3, jumptable_8036FF10@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8036FF10@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@4:
	stw r31, 0x20(r28)
	cmpwi r27, 0x1
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	bne @3
	mr r3, r29
	bl psndSFXOn
	b @3
	@5:
	lwz r3, 0x20(r28)
	subi r0, r3, 0x1
	stw r0, 0x20(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0x0
	bge @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@6:
	xoris r3, r31, 0x8000
	lis r0, 0x4330
	lwz r5, 0x20(r28)
	lis r4, double_to_int_802f3778@ha
	stw r3, 0x24(r1)
	li r3, 0xc
	addi r6, r5, 0x1
	lfd f2, double_to_int_802f3778@l(r4)
	stw r0, 0x20(r1)
	li r5, 0x1e
	lfs f1, float_500_8041cbbc(r2)
	lfd f0, 0x20(r1)
	stw r6, 0x20(r28)
	fsubs f2, f0, f2
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x4(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0x1e
	blt @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@7:
	lwz r4, 0x20(r28)
	li r3, 0xc
	lfs f1, float_1_8041cbb8(r2)
	li r5, 0x8
	addi r0, r4, 0x1
	lfs f2, float_0p4_8041cbc0(r2)
	stw r0, 0x20(r28)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x10(r28)
	li r3, 0xc
	lfs f1, float_1_8041cbb8(r2)
	li r5, 0x8
	lfs f2, float_1p5_8041cbc4(r2)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x14(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0x8
	blt @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@8:
	lwz r3, 0x20(r28)
	addi r0, r3, 0x1
	stw r0, 0x20(r28)
	lwz r0, 0x8(r25)
	lwz r4, 0x20(r28)
	subf r3, r27, r0
	subi r0, r3, 0x1
	slwi r0, r0, 2
	cmpw r4, r0
	ble @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@9:
	lis r6, 0x4330
	xoris r3, r31, 0x8000
	stw r3, 0x24(r1)
	xoris r0, r30, 0x8000
	lis r4, double_to_int_802f3778@ha
	lwz r5, 0x20(r28)
	stw r6, 0x20(r1)
	li r3, 0x8
	lfd f2, double_to_int_802f3778@l(r4)
	addi r7, r5, 0x1
	lfd f0, 0x20(r1)
	li r5, 0x1e
	stw r7, 0x20(r28)
	fsubs f1, f0, f2
	stw r0, 0x2c(r1)
	lwz r4, 0x20(r28)
	stw r6, 0x28(r1)
	lfd f0, 0x28(r1)
	fsubs f2, f0, f2
	bl intplGetValue
	stfs f1, 0x4(r28)
	li r3, 0xc
	lfs f1, float_0p2_8041cbc8(r2)
	li r5, 0x1e
	lfs f2, float_1_8041cbb8(r2)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x10(r28)
	li r3, 0xc
	lfs f1, float_1p5_8041cbc4(r2)
	li r5, 0x1e
	lfs f2, float_1_8041cbb8(r2)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x14(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0x1e
	blt @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@10:
	lwz r3, 0x20(r28)
	addi r0, r3, 0x1
	stw r0, 0x20(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0x10
	ble @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@11:
	lwz r4, 0x20(r28)
	li r3, 0xc
	lfs f1, float_1_8041cbb8(r2)
	li r5, 0xf
	addi r0, r4, 0x1
	lfs f2, float_1p5_8041cbc4(r2)
	stw r0, 0x20(r28)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x10(r28)
	li r3, 0xc
	lfs f1, float_1_8041cbb8(r2)
	li r5, 0xf
	lfs f2, float_0p1_8041cbcc(r2)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x14(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0xf
	blt @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@12:
	lwz r4, 0x20(r28)
	li r3, 0xc
	lfs f1, float_1p5_8041cbc4(r2)
	li r5, 0xf
	addi r0, r4, 0x1
	lfs f2, float_0p1_8041cbcc(r2)
	stw r0, 0x20(r28)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x10(r28)
	li r3, 0xc
	lfs f1, float_0p1_8041cbcc(r2)
	li r5, 0xf
	lfs f2, float_2_8041cbd0(r2)
	lwz r4, 0x20(r28)
	bl intplGetValue
	stfs f1, 0x14(r28)
	lwz r0, 0x20(r28)
	cmpwi r0, 0xf
	blt @3
	li r0, 0x0
	stw r0, 0x20(r28)
	lwz r3, 0x28(r28)
	addi r0, r3, 0x1
	stw r0, 0x28(r28)
	b @3
	@13:
	lfs f0, float_0_8041cbb0(r2)
	addi r26, r26, 0x1
	stfs f0, 0x18(r28)
	stfs f0, 0x14(r28)
	stfs f0, 0x10(r28)
	@3:
	addi r31, r31, 0x4
	addi r30, r30, 0xc
	addi r27, r27, 0x1
	addi r28, r28, 0x64
	@1:
	lwz r3, 0x8(r25)
	cmpw r27, r3
	blt @2
	subi r0, r3, 0x1
	cmpw r26, r0
	blt @14
	mr r3, r25
	bl effDelete
	b @15
	@14:
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effAcrobatDisp@ha
	mr r6, r25
	addi r5, r3, effAcrobatDisp@l
	li r4, 0x8
	li r3, 0x4
	bl dispEntry
	@15:
	lmw r25, 0x34(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void effNiceDisp(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stw r31, 0xcc(r1)
	stw r30, 0xc8(r1)
	mr r30, r3
	addi r3, r1, 0x98
	lwz r31, 0xc(r4)
	lfs f1, 0x4(r31)
	lfs f2, 0x8(r31)
	lfs f3, 0xc(r31)
	bl PSMTXTrans
	mr r3, r30
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x68
	lfs f0, float_0p017453_8041cba4(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	lfs f1, 0x1c(r31)
	addi r3, r1, 0x38
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x98
	addi r4, r1, 0x68
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	lfs f1, float_8_8041cbd4(r2)
	addi r3, r1, 0x38
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x8
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	lwz r3, 0x30(r31)
	addi r4, r1, 0x8
	lfs f1, float_0_8041cbb0(r2)
	li r5, 0x1
	lfs f2, float_1_8041cbb8(r2)
	bl animPoseDrawMtx
	lwz r3, 0x30(r31)
	addi r4, r1, 0x8
	lfs f1, float_0_8041cbb0(r2)
	li r5, 0x2
	lfs f2, float_1_8041cbb8(r2)
	bl animPoseDrawMtx
	lwz r3, 0x30(r31)
	addi r4, r1, 0x8
	lfs f1, float_0_8041cbb0(r2)
	li r5, 0x3
	lfs f2, float_1_8041cbb8(r2)
	bl animPoseDrawMtx
	lwz r0, 0xd4(r1)
	lwz r31, 0xcc(r1)
	lwz r30, 0xc8(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm void effNiceMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stmw r27, 0x4c(r1)
	lis r4, vec3_802f3748@ha
	lwz r31, 0xc(r3)
	addi r5, r4, vec3_802f3748@l
	mr r29, r3
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x28(r1)
	lfs f0, 0x4(r31)
	stw r3, 0x2c(r1)
	lfs f1, 0x8(r31)
	stfs f0, 0x28(r1)
	lfs f0, 0xc(r31)
	stw r0, 0x30(r1)
	lwz r4, 0x28(r1)
	stfs f1, 0x2c(r1)
	stfs f0, 0x30(r1)
	lwz r3, 0x2c(r1)
	lwz r0, 0x30(r1)
	stw r4, 0x34(r1)
	stw r3, 0x38(r1)
	stw r0, 0x3c(r1)
	lwz r3, 0x0(r29)
	lwz r30, 0x0(r31)
	rlwinm. r0, r3, 0, 29, 29
	beq @1
	rlwinm r0, r3, 0, 30, 28
	stw r0, 0x0(r29)
	lwz r3, 0x30(r31)
	cmpwi r3, -0x1
	beq @2
	bl animPoseRelease
	@2:
	mr r3, r29
	bl effDelete
	b @3
	@1:
	lwz r3, 0x30(r31)
	cmpwi r3, -0x1
	beq @4
	bl animPoseGetAnimPosePtr
	mr r27, r3
	lwz r3, 0x30(r31)
	bl animPoseGetAnimDataPtr
	mr r28, r3
	lwz r3, 0x30(r31)
	bl animPoseMain
	cmpwi r30, 0x4
	beq @5
	bge @6
	cmpwi r30, 0x2
	beq @7
	bge @8
	cmpwi r30, 0x0
	bge @9
	b @10
	@6:
	cmpwi r30, 0x6
	beq @10
	b @10
	@9:
	lwz r3, gp(r13)
	lwz r4, 0x24(r28)
	lwz r0, 0x16c(r3)
	lfs f4, 0x8(r4)
	cmplwi r0, 0x0
	bne @11
	lfs f0, float_32_8041cbd8(r2)
	b @12
	@11:
	lfs f0, float_34_8041cbdc(r2)
	@12:
	lfs f1, 0x24(r27)
	fcmpo cr0, f1, f0
	ble @10
	fsubs f2, f1, f0
	lfs f3, float_1_8041cbb8(r2)
	fsubs f1, f4, f0
	lfs f0, float_0_8041cbb0(r2)
	fdivs f1, f2, f1
	fsubs f31, f3, f1
	fcmpo cr0, f31, f0
	bge @13
	fmr f31, f0
	@13:
	lwz r3, 0x30(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lfs f0, float_255_8041cbe0(r2)
	addi r4, r1, 0x24
	lwz r0, dat_8041cb90(r2)
	fmuls f0, f0, f31
	stw r0, 0x20(r1)
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r0, 0x44(r1)
	stb r0, 0x23(r1)
	lwz r0, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r3, 0x30(r31)
	bl animPoseSetMaterialEvtColor
	b @10
	@7:
	lwz r3, gp(r13)
	lwz r4, 0x24(r28)
	lwz r0, 0x16c(r3)
	lfs f4, 0x8(r4)
	cmplwi r0, 0x0
	bne @14
	lfs f0, float_35_8041cbe4(r2)
	b @15
	@14:
	lfs f0, float_37_8041cbe8(r2)
	@15:
	lfs f1, 0x24(r27)
	fcmpo cr0, f1, f0
	ble @10
	fsubs f2, f1, f0
	lfs f3, float_1_8041cbb8(r2)
	fsubs f1, f4, f0
	lfs f0, float_0_8041cbb0(r2)
	fdivs f1, f2, f1
	fsubs f31, f3, f1
	fcmpo cr0, f31, f0
	bge @16
	fmr f31, f0
	@16:
	lwz r3, 0x30(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lfs f0, float_255_8041cbe0(r2)
	addi r4, r1, 0x1c
	lwz r0, dat_8041cb94(r2)
	fmuls f0, f0, f31
	stw r0, 0x18(r1)
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r0, 0x44(r1)
	stb r0, 0x1b(r1)
	lwz r0, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r3, 0x30(r31)
	bl animPoseSetMaterialEvtColor
	b @10
	@8:
	lwz r3, gp(r13)
	lwz r4, 0x24(r28)
	lwz r0, 0x16c(r3)
	lfs f4, 0x8(r4)
	cmplwi r0, 0x0
	bne @17
	lfs f0, float_45_8041cbec(r2)
	b @18
	@17:
	lfs f0, float_40_8041cbf0(r2)
	@18:
	lfs f1, 0x24(r27)
	fcmpo cr0, f1, f0
	ble @10
	fsubs f2, f1, f0
	lfs f3, float_1_8041cbb8(r2)
	fsubs f1, f4, f0
	lfs f0, float_0_8041cbb0(r2)
	fdivs f1, f2, f1
	fsubs f31, f3, f1
	fcmpo cr0, f31, f0
	bge @19
	fmr f31, f0
	@19:
	lwz r3, 0x30(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lfs f0, float_255_8041cbe0(r2)
	addi r4, r1, 0x14
	lwz r0, dat_8041cb98(r2)
	fmuls f0, f0, f31
	stw r0, 0x10(r1)
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r0, 0x44(r1)
	stb r0, 0x13(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r3, 0x30(r31)
	bl animPoseSetMaterialEvtColor
	b @10
	@5:
	lwz r3, gp(r13)
	lwz r4, 0x24(r28)
	lwz r0, 0x16c(r3)
	lfs f4, 0x8(r4)
	cmplwi r0, 0x0
	bne @20
	lfs f0, float_48_8041cbf4(r2)
	b @21
	@20:
	lfs f0, float_40_8041cbf0(r2)
	@21:
	lfs f1, 0x24(r27)
	fcmpo cr0, f1, f0
	ble @10
	fsubs f2, f1, f0
	lfs f3, float_1_8041cbb8(r2)
	fsubs f1, f4, f0
	lfs f0, float_0_8041cbb0(r2)
	fdivs f1, f2, f1
	fsubs f31, f3, f1
	fcmpo cr0, f31, f0
	bge @22
	fmr f31, f0
	@22:
	lwz r3, 0x30(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lfs f0, float_255_8041cbe0(r2)
	addi r4, r1, 0xc
	lwz r0, dat_8041cb9c(r2)
	fmuls f0, f0, f31
	stw r0, 0x8(r1)
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r0, 0x44(r1)
	stb r0, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	lwz r3, 0x30(r31)
	bl animPoseSetMaterialEvtColor
	@10:
	lwz r3, 0x30(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041cbb8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @4
	lwz r3, 0x30(r31)
	bl animPoseRelease
	mr r3, r29
	bl effDelete
	b @3
	@4:
	cmpwi r30, 0x7
	bne @23
	mr r3, r29
	bl acrobatMain
	b @3
	@23:
	addi r3, r1, 0x34
	bl dispCalcZ
	lis r3, effNiceDisp@ha
	mr r6, r29
	addi r5, r3, effNiceDisp@l
	li r4, 0x8
	li r3, 0x4
	bl dispEntry
	@3:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	lmw r27, 0x4c(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}
// clang-format on
#endif
