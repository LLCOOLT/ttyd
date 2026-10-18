#include "driver/effdrv.h"
#include "driver/arcdrv.h"
#include "eff/eff_n64.h"
#include "manager/dvdmgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <string.h>

extern int sprintf(char* str, const char* format, ...);

extern GlobalWork* gp;

//.data
EffectSet eff_set_table[] = {
	{0, "kemuri"},
	{1, "confetti"},
	{2, "fukidashi"},
	{3, "butterfly"},
	{4, "hit"},
	{5, "damage_star"},
	{6, "small_star"},
	{7, "mario_balloon"},
	{8, "mugi"},
	{9, "stardust"},
	{10, "recovery"},
	{11, "miss_star"},
	{12, "nice"},
	{13, "breath_fire"},
	{14, "torch"},
	{15, "confusion"},
	{16, "spark"},
	{17, "updown"},
	{18, "charge"},
	{19, "toge_flush"},
	{20, "ice"},
	{21, "fire"},
	{22, "bomb"},
	{23, "ripple"},
	{24, "coin_fukidashi"},
	{25, "star_point"},
	{26, "puni_balloon"},
	{27, "p_fukidashi"},
	{28, "kemuri_test"},
	{29, "starstone"},
	{30, "itemget"},
	{31, "status"},
	{32, "pointget"},
	{33, "levelup"},
	{34, "stageclear"},
	{35, "fall"},
	{36, "fpdamage"},
	{37, "break"},
	{38, "mobj_broken"},
	{39, "mahojin"},
	{40, "nozle"},
	{41, "mizutama"},
	{42, "minigame"},
	{43, "splash"},
	{44, "treasure_map"},
	{45, "kiss"},
	{46, "funemizu"},
	{47, "mist"},
	{48, "teresa"},
	{49, "batten"},
	{50, "sheep"},
	{51, "naniga"},
	{52, "sandars"},
	{53, "boomerang"},
	{54, "irekae"},
	{55, "rankup"},
	{56, "scanning"},
	{57, "toiki"},
	{58, "mist2"},
	{59, "particle"},
	{60, "ibuki"},
	{61, "mahorn"},
	{62, "spirit"},
	{63, "indirect"},
	{64, "syuryou"},
	{65, "uranoko"},
	{66, "hibashira"},
	{67, "number"},
	{68, "laser"},
	{69, "machingegun"},
	{70, "las_mon"},
	{71, "sleep"},
	{72, "energy"},
	{73, "biribirikinoko"},
	{74, "nokotarou"},
	{75, "queen"},
	{76, "queen2"},
	{77, "gonbaba_breath"},
	{78, "majinai"},
	{79, "mahorn2"},
	{80, "ultra_hammer"},
	{-1, NULL}
};

//.sbss
static EffectWork work;

//.sdata
static EffectWork* wp = &work;
const char* prefix_tbl[2] = {"jp", "us"};

//local prototypes
static void _callback_tpl(s32 error, DVDFileInfo* info);

#ifdef NONMATCHING
static void _callback_tpl(s32 error, DVDFileInfo* info) {
	DVDEntry* entry = info->cb.userData;
	UnpackTexPalette(wp->texture);
	DVDMgrClose(entry);
	wp->texLoaded = TRUE;
}
#endif

#ifdef NONMATCHING
void effInit(void) {
	wp->count = 0x100;
	wp->entries = __memAlloc(HEAP_DEFAULT, wp->count * sizeof(EffectEntry));
	memset(wp->entries, 0, wp->count * sizeof(EffectEntry));
	wp->handle = NULL;
	wp->language = -1;
	wp->texture = NULL;
	wp->texLoaded = FALSE;
	effInit64();
}
#endif

#ifdef NONMATCHING
void effTexSetup(void) {
	DVDEntry* entry;
	char path[128];
	u32 size;

	wp->texture = NULL;
	wp->texLoaded = FALSE;
	wp->texture = arcOpen("effect.tpl", 0, 0);
	if (!wp->texture) {
		sprintf(path, "%s/e/jp/effect.tpl\0", getMarioStDvdRoot());
		entry = DVDMgrOpen(path, 2, 0);
		size = OSRoundUp32B(DVDMgrGetLength(entry));
		wp->texture = __memAlloc(HEAP_DEFAULT, size);
		entry->info.cb.userData = entry;
		DVDMgrReadAsync(entry, wp->texture, size, 0, _callback_tpl);
	}
	else {
		UnpackTexPalette(wp->texture);
		wp->texLoaded = TRUE;
	}
	effTexSetupN64();
}
#endif

#ifdef NONMATCHING
void effGetTexObj(u32 id, GXTexObj* obj) {
#ifdef __MWERKS__
#pragma explicit_zero_data on
	if ((s32)id < 146) { //number of images in effect.tpl
		if (!wp->texLoaded) {
			static char dummy ATTRIBUTE_ALIGN(32) = '\0';
			GXInitTexObj(obj, &dummy, 1, 1, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
		}
		else {
			TEXGetGXTexObjFromPalette(wp->texture, obj, id);
		}
	}
	else {
		static char dummy ATTRIBUTE_ALIGN(32) = '\0';
		if (!wp->handle) {
			GXInitTexObj(obj, &dummy, 1, 1, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
		}
		else {
			TEXGetGXTexObjFromPalette(*wp->handle->data, obj, id - 146);
		}
	}
#pragma explicit_zero_data reset
#endif
}
#endif

#ifdef NONMATCHING
void effAutoRelease(BOOL inBattle) {
	int i;
	int count = wp->count;
	EffectEntry* entry = wp->entries;

	for (i = 0; i < count; i++, entry++) {
		if (entry->flags & 1 && (s32)entry->inBattle == inBattle && entry && entry->flags) {
			__memFree(HEAP_EFFECT, entry->userdata);
			entry->flags = 0;
		}
	}
}
#endif

#ifdef NONMATCHING
EffectEntry* effEntry(void) {
	EffectEntry* entry = wp->entries;
	int i;

	for (i = 0; i < wp->count; i++, entry++) {
		if (!entry->flags) {
			break;
		}
	}
	entry->flags = 1;
	entry->inBattle = gp->inBattle != 0;
	entry->type = 0;
	entry->count = 0;
	entry->userdata = NULL;
	entry->callback = NULL;
	entry->name[0] = '\0';
	return entry;
}
#endif

#ifdef NONMATCHING
void effSetName(EffectEntry* effect, const char* name) {
	int i;
	int count = wp->count;
	EffectEntry* entry = wp->entries;

	for (i = 0; i < count; i++, entry++) {
		if (entry->flags && !strcmp(entry->name, name)) {
			break;
		}
	}
	strcpy(effect->name, name);
}
#endif

#ifdef NONMATCHING
void effMain(void) {
	const char *dvdroot, *prefix;
	int i;
	int count = wp->count;
	EffectEntry* entry = wp->entries;

	for (i = 0; i < count; i++, entry++) {
		if (gp->inBattle) {
			if ((s32)entry->inBattle != 1) {
				continue;
			}
		}
		else if ((s32)entry->inBattle != 0) {
			continue;
		}
		if (entry->flags & 1) {
			if (entry->callback) {
				entry->callback(entry);
			}
		}
	}
	if ((u32)wp->language != (u32)gp->language) {
		if (wp->handle) {
			fileFree(wp->handle);
			wp->handle = NULL;
		}
		prefix = prefix_tbl[gp->language];
		dvdroot = getMarioStDvdRoot();
		if (fileAsyncf(4, 0, "%s/e/%s/effect_%s.tpl", dvdroot, prefix, prefix) != 0U) {
			prefix = prefix_tbl[gp->language];
			wp->handle = fileAllocf(4, "%s/e/%s/effect_%s.tpl", getMarioStDvdRoot(), prefix, prefix);
			wp->language = gp->language;
		}
	}
}
#endif

#ifdef NONMATCHING
void effDelete(EffectEntry* effect) {
	if (effect && effect->flags) {
		__memFree(HEAP_EFFECT, effect->userdata);
		effect->flags = 0;
	}
}
#endif

#ifdef NONMATCHING
void effSoftDelete(EffectEntry* effect) {
	if (effect && effect->flags) {
		if (effect->flags & 2) {
			effect->flags |= 4; // "deleted"
		}
		else {
			effDelete(effect); //inlined
		}
	}
}
#endif

#ifdef NONMATCHING
EffectEntry* effNameToPtr(const char* name) {
	int i;
	int count = wp->count;
	EffectEntry* entry = wp->entries;

	for (i = 0; i < count; i++, entry++) {
		if (entry->flags && !strcmp(entry->name, name)) {
			break;
		}
	}
	if (i >= count) {
		return NULL;
	}
	else {
		return entry; //found a match
	}
}
#endif

#ifdef NONMATCHING
EffectSet* effGetSet(const char* name) {
	s32 i;

	for (i = 0; eff_set_table[i].id != -1; i++) { //run until end of table
		if (!strcmp(eff_set_table[i].name, name)) {
			return &eff_set_table[i];
		}
	}
	return NULL;
}
#endif

typedef struct MayaKey {
	s16 time;
	u8 data[0xb0];
} MayaKey;

typedef struct MayaKeyList {
	s32 count;
	MayaKey* keys;
	s32 pad[2];
} MayaKeyList;

typedef struct MayaListHdr {
	s32 count;
	MayaKeyList* entries;
} MayaListHdr;

typedef struct MayaAnimData {
	u8 pad0[4];
	f32 endTime;
	MayaListHdr* lists;
} MayaAnimData;

typedef struct MayaJoint {
	Mtx mtx;
	f32 alpha;
} MayaJoint;

typedef struct MayaAnim {
	u16 flags;
	f32 time;
	OSTime startTime;
	MayaAnimData* data;
	MayaJoint joints[1];
} MayaAnim;

typedef struct MayaPoly {
	s32 pad0[2];
	s32 count;
	s16** strips;
} MayaPoly;

#ifdef NONMATCHING
void effCalcMayaAnimMatrix(MayaAnim* anim, MayaKeyList* list, f32* mtx, f32* alpha) {
	f32 buf[22];
	Mtx trans; Mtx scale; Mtx tmp2; Mtx pivot2; Mtx pivot2Inv; Mtx trans3; Mtx pivot1; Mtx pivot1Inv; Mtx trans2; Mtx rotX; Mtx rotY; Mtx rotZ; Mtx tmp;


	register u32 gqr;
	s32 n = list->count;
	s32 k;
	f32 t;

	for (k = 1; k < n; k++) {
		MayaKey* prev;
		MayaKey* curr;
		s32 i;
		register s8* pb;
		f32* out;
		register s8* pa;
		curr = &list->keys[k];
		prev = &list->keys[k - 1];
		gqr = 0x06070607;
		asm { mtspr GQR5, gqr }
		if (anim->time <= curr->time) {
			t = anim->time;
		}
		else if (k != ( n - 1) ) {
			continue;
		}
		else {
			t = curr->time;
		}
		pa = (s8*)prev;
		pb = (s8*)curr;
		out = buf;
		for (i = 0; i < 22; i++) {
			f32 u; f32 dt; f32 s; f32 s2; f32 s3; f32 div;
			register f32 qm0; register f32 qd0; register f32 qv1; register f32 qv0; register f32 qm1;
			asm {
				psq_l qv0, 2(pa), 1, 5
				} asm { psq_l qd0, 4(pa), 1, 5
				} asm { psq_l qm0, 6(pa), 1, 5
				} asm { psq_l qv1, 2(pb), 1, 5
				} asm { psq_l qm1, 4(pb), 1, 5
				} asm { psq_l qd0, 6(pb), 1, 5
			}
			if (pa[9] != 0) {
				*out = qv0;
			}
			else {
				u = t - prev->time;
				dt = curr->time - prev->time;
				div = (!dt) ? ( 0.00000001f ) : ( dt) ;
				s = u / div;
				s2 = s * s;
				s3 = s2 * s;
				*out = ((( qv0 * (1.0f + (( 2.0f * s3 ) - ( 3.0f * s2)) )) + ( qm0 * (dt * (s + (s3 - ( 2.0f * s2))) ))) + ( qv1 * ((( -2.0f ) * s3 ) + ( 3.0f * s2) ))) + ( qm1 * (dt * (s3 - s2) ));
			}
			pa += 8;
			pb += 8;
			out++;
		}
		PSMTXTrans(trans, buf[0], buf[1], buf[2]);
		PSMTXRotRad(rotX, 'x', buf[3]);
		PSMTXRotRad(rotY, 'y', buf[4]);
		PSMTXRotRad(rotZ, 'z', buf[5]);
		PSMTXScale(scale, buf[6], buf[7], buf[8]);
		PSMTXTrans(pivot1, buf[9], buf[10], buf[11]);
		PSMTXTrans(pivot1Inv, -buf[9], -buf[10], -buf[11]);
		PSMTXTrans(trans2, buf[12], buf[13], buf[14]);
		PSMTXTrans(pivot2, buf[15], buf[16], buf[17]);
		PSMTXTrans(pivot2Inv, -buf[15], -buf[16], -buf[17]);
		PSMTXTrans(trans3, buf[18], buf[19], buf[20]);
		PSMTXConcat(trans3, pivot2, tmp);
		PSMTXConcat(tmp, scale, tmp);
		PSMTXConcat(tmp, pivot2Inv, scale);
		PSMTXConcat(trans2, pivot1, tmp);
		PSMTXConcat(tmp, rotZ, tmp);
		PSMTXConcat(tmp, rotY, tmp);
		PSMTXConcat(tmp, rotX, tmp);
		PSMTXConcat(tmp, pivot1Inv, tmp2);
		PSMTXConcat(trans, tmp2, tmp);
		PSMTXConcat(tmp, scale, (MtxPtr)mtx);
		*alpha = ( buf[21] > 1.0f ) ? ( 1.0f ) : ((buf [21] < ( (buf[21] < 0.0f ) * 0.0f)) ? ( 0.0f ) : ( buf[21]) );
		return;
	}
}
#endif

#ifdef NONMATCHING
MayaAnim* effMayaAnimAlloc(MayaAnimData* data) {
	s32 size = data->lists->count * sizeof(MayaJoint) + 0x18;
	MayaAnim* anim = __memAlloc(HEAP_EFFECT, size);
	memset(anim, 0, size);
	anim->data = data;
	return anim;
}
#endif

#ifdef NONMATCHING
void effDeleteMayaAnim(MayaAnim* anim) {
	__memFree(HEAP_EFFECT, anim);
}
#endif

#ifdef NONMATCHING
void effPlayMayaAnim(MayaAnim* anim) {
	OSTime now = gp->inBattle ? gp->renderTime : gp->renderFieldTime;
	anim->startTime = now / (OS_TIMER_CLOCK / 1000);
	anim->time = 0.0f;
	anim->flags |= 1;
}
#endif

#ifdef NONMATCHING
void effCalcMayaAnim(MayaAnim* anim) {
	if ((anim->flags & 1) && !(anim->flags & 2)) {
		OSTime now = gp->inBattle ? gp->renderTime : gp->renderFieldTime;
		s32 i;
		now = now / (OS_TIMER_CLOCK / 1000);
		anim->time = (f32)(u64)(now - anim->startTime) * gp->framerate / 1000.0f;
		if (anim->time >= anim->data->endTime) {
			anim->time = anim->data->endTime;
			anim->flags |= 2;
		}
		for (i = 0; i < anim->data->lists->count; i++) {
			effCalcMayaAnimMatrix(anim, &anim->data->lists->entries[i], (f32*)anim->joints[i].mtx, &anim->joints[i].alpha);
		}
	}
}
#endif

#ifdef NONMATCHING
void effDrawMayaPoly(MayaPoly* poly) {
	s32 i;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 9);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 9);
	GXSetCullMode(GX_CULL_NONE);
	for (i = 0; i < poly->count; i++) {
		s16* strip = poly->strips[i];
		u16 n = strip[0];
		s16* v;
		s32 j;
		GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, n);
		v = strip + 1;
		for (j = 0; j < n; j++, v += 5) {
			GXPosition3s16(v[0], v[1], v[2]);
			GXTexCoord2s16(v[3], v[4]);
		}
	}
}
#endif


// prototypes for asm stopgap forward references
void effDrawMayaPoly(MayaPoly* poly);
void effCalcMayaAnim(MayaAnim* anim);
void effPlayMayaAnim(MayaAnim* anim);
void effDeleteMayaAnim(MayaAnim* anim);
MayaAnim* effMayaAnimAlloc(MayaAnimData* data);
void effCalcMayaAnimMatrix(MayaAnim* anim, MayaKeyList* list, f32* mtx, f32* alpha);
EffectSet* effGetSet(const char* name);
EffectEntry* effNameToPtr(const char* name);
void effSoftDelete(EffectEntry* effect);
void effDelete(EffectEntry* effect);
void effMain(void);
void effSetName(EffectEntry* effect, const char* name);
EffectEntry* effEntry(void);
void effAutoRelease(BOOL inBattle);
void effGetTexObj(u32 id, GXTexObj* obj);
void effTexSetup(void);
void effInit(void);
#pragma explicit_zero_data on
static char effDummy820 ATTRIBUTE_ALIGN(32) = 0;
static char effDummy824 ATTRIBUTE_ALIGN(32) = 0;
#pragma explicit_zero_data reset
#ifndef NONMATCHING
// ASM-STOPGAP: _callback_tpl (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".rodata") const f64 double_to_int_802c3c88 = 4503601774854144;
__declspec(section ".rodata") const char str_802C3C90[] = "%s/e/%s/effect_%s.tpl\000\000";
__declspec(section ".rodata") const char str_802C3CA8[] = "effect.tpl\000";
__declspec(section ".rodata") const char str_802C3CB4[] = "%s/e/jp/effect.tpl\000";
__declspec(section ".sdata2") const f32 float_1000_8041a0a8 = 1000.0f;
__declspec(section ".sdata2") const f32 float_0_8041a0ac = 0.0f;
__declspec(section ".sdata2") const f32 dat_8041a0b0 = 0.00000001f;
__declspec(section ".sdata2") const f32 float_3_8041a0b4 = 3.0f;
__declspec(section ".sdata2") const f32 float_neg2_8041a0b8 = -2.0f;
__declspec(section ".sdata2") const f32 float_1_8041a0bc = 1.0f;
__declspec(section ".sdata2") const f32 float_2_8041a0c0 = 2.0f;

void __cvt_ull_flt();
void __div2i();
asm void effDrawMayaPoly(MayaPoly* poly) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
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
	li r6, 0x3
	li r7, 0x9
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x3
	li r7, 0x9
	bl GXSetVtxAttrFmt
	li r3, 0x0
	bl GXSetCullMode
	li r29, 0x0
	li r30, 0x0
	lis r31, 0xcc01
	b @1
	@2:
	lwz r5, 0xc(r26)
	li r3, 0xa0
	li r4, 0x0
	lwzx r28, r5, r30
	lha r0, 0x0(r28)
	clrlwi r27, r0, 16
	mr r5, r27
	bl GXBegin
	cmpwi r27, 0x0
	mr r3, r27
	addi r6, r28, 0x2
	ble @3
	srwi. r0, r27, 2
	mtctr r0
	beq @4
	@5:
	lha r5, 0x4(r6)
	lha r4, 0x2(r6)
	lha r0, 0x0(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	sth r5, -0x8000(r31)
	lha r4, 0x8(r6)
	lha r0, 0x6(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	lha r5, 0xe(r6)
	lha r4, 0xc(r6)
	lha r0, 0xa(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	sth r5, -0x8000(r31)
	lha r4, 0x12(r6)
	lha r0, 0x10(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	lha r5, 0x18(r6)
	lha r4, 0x16(r6)
	lha r0, 0x14(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	sth r5, -0x8000(r31)
	lha r4, 0x1c(r6)
	lha r0, 0x1a(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	lha r5, 0x22(r6)
	lha r4, 0x20(r6)
	lha r0, 0x1e(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	sth r5, -0x8000(r31)
	lha r4, 0x26(r6)
	lha r0, 0x24(r6)
	addi r6, r6, 0x28
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	bdnz @5
	andi. r3, r3, 0x3
	beq @3
	@4:
	mtctr r3
	@6:
	lha r5, 0x4(r6)
	lha r4, 0x2(r6)
	lha r0, 0x0(r6)
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	sth r5, -0x8000(r31)
	lha r4, 0x8(r6)
	lha r0, 0x6(r6)
	addi r6, r6, 0xa
	sth r0, -0x8000(r31)
	sth r4, -0x8000(r31)
	bdnz @6
	@3:
	addi r30, r30, 0x4
	addi r29, r29, 0x1
	@1:
	lwz r0, 0x8(r26)
	cmpw r29, r0
	blt @2
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void effCalcMayaAnim(MayaAnim* anim) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lhz r3, 0x0(r3)
	clrlwi. r0, r3, 31
	beq @1
	rlwinm. r0, r3, 0, 30, 30
	bne @1
	lwz r29, gp(r13)
	lwz r0, 0x14(r29)
	cmpwi r0, 0x0
	beq @2
	lwz r3, 0x38(r29)
	lwz r4, 0x3c(r29)
	b @3
	@2:
	lwz r3, 0x40(r29)
	lwz r4, 0x44(r29)
	@3:
	lis r6, 0x8000
	lis r5, 0x1062
	lwz r0, 0xf8(r6)
	addi r6, r5, 0x4dd3
	li r5, 0x0
	srwi r0, r0, 2
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	lwz r5, 0xc(r31)
	lwz r0, 0x8(r31)
	subfc r4, r5, r4
	subfe r3, r0, r3
	bl __cvt_ull_flt
	lwz r4, 0x4(r29)
	lis r0, 0x4330
	stw r0, 0x8(r1)
	lis r3, double_to_int_802c3c88@ha
	xoris r0, r4, 0x8000
	lfd f3, double_to_int_802c3c88@l(r3)
	stw r0, 0xc(r1)
	lfs f0, float_1000_8041a0a8(r2)
	lfd f2, 0x8(r1)
	fsubs f2, f2, f3
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x4(r31)
	lwz r3, 0x10(r31)
	lfs f0, 0x4(r31)
	lfs f1, 0x4(r3)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @4
	stfs f1, 0x4(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x2
	sth r0, 0x0(r31)
	@4:
	mr r30, r31
	li r28, 0x0
	li r29, 0x0
	b @5
	@6:
	lwz r0, 0x4(r3)
	mr r3, r31
	addi r5, r30, 0x14
	addi r6, r30, 0x44
	add r4, r0, r29
	bl effCalcMayaAnimMatrix
	addi r30, r30, 0x34
	addi r29, r29, 0x10
	addi r28, r28, 0x1
	@5:
	lwz r3, 0x10(r31)
	lwz r3, 0x8(r3)
	lwz r0, 0x0(r3)
	cmpw r28, r0
	blt @6
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void effPlayMayaAnim(MayaAnim* anim) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	b @2
	@1:
	lwz r3, 0x40(r4)
	lwz r4, 0x44(r4)
	@2:
	lis r6, 0x8000
	lis r5, 0x1062
	lwz r0, 0xf8(r6)
	addi r6, r5, 0x4dd3
	li r5, 0x0
	srwi r0, r0, 2
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	stw r4, 0xc(r31)
	lfs f0, float_0_8041a0ac(r2)
	stw r3, 0x8(r31)
	stfs f0, 0x4(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x1
	sth r0, 0x0(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void effDeleteMayaAnim(MayaAnim* anim) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r4, r3
	li r3, 0x3
	stw r0, 0x14(r1)
	bl __memFree
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm MayaAnim* effMayaAnimAlloc(MayaAnimData* data) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	li r3, 0x3
	lwz r4, 0x8(r30)
	lwz r0, 0x0(r4)
	mulli r4, r0, 0x34
	addi r31, r4, 0x18
	mr r4, r31
	bl __memAlloc
	mr r5, r31
	mr r31, r3
	li r4, 0x0
	bl memset
	stw r30, 0x10(r31)
	mr r3, r31
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void effCalcMayaAnimMatrix(MayaAnim* anim, MayaKeyList* list, f32* mtx, f32* alpha) {
	nofralloc
	stwu r1, -0x2f0(r1)
	mflr r0
	lis r7, double_to_int_802c3c88@ha
	lis r8, 0x607
	stw r0, 0x2f4(r1)
	addi r9, r8, 0x607
	lfd f1, double_to_int_802c3c88@l(r7)
	li r12, 0x1
	stw r31, 0x2ec(r1)
	mr r31, r6
	li r10, 0xb2
	lis r7, 0x4330
	stw r30, 0x2e8(r1)
	mr r30, r5
	lwz r11, 0x0(r4)
	subi r0, r11, 0x1
	mtctr r0
	cmpwi r11, 0x1
	ble @1
	@2:
	subi r5, r12, 0x1
	lwz r8, 0x4(r4)
	mulli r5, r5, 0xb2
	add r6, r8, r10
	add r5, r8, r5
	mtspr GQR5, r9
	lha r8, 0x0(r6)
	stw r7, 0x2d0(r1)
	xoris r8, r8, 0x8000
	lfs f2, 0x4(r3)
	stw r8, 0x2d4(r1)
	lfd f0, 0x2d0(r1)
	fsubs f0, f0, f1
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne @3
	fmr f0, f2
	b @4
	@3:
	cmpw r12, r0
	bne @5
	lis r0, 0x4330
	lis r3, double_to_int_802c3c88@ha
	stw r8, 0x2d4(r1)
	lfd f1, double_to_int_802c3c88@l(r3)
	stw r0, 0x2d0(r1)
	lfd f0, 0x2d0(r1)
	fsubs f0, f0, f1
	@4:
	li r0, 0x16
	mr r8, r5
	mr r9, r6
	addi r10, r1, 0x278
	mtctr r0
	@6:
	psq_l f9, 0x2(r8), 1, 5
	psq_l f1, 0x4(r8), 1, 5
	psq_l f10, 0x6(r8), 1, 5
	psq_l f11, 0x2(r9), 1, 5
	psq_l f12, 0x4(r9), 1, 5
	psq_l f1, 0x6(r9), 1, 5
	lbz r0, 0x9(r8)
	extsb. r0, r0
	beq @7
	stfs f9, 0x0(r10)
	b @8
	@7:
	lha r11, 0x0(r5)
	lis r3, 0x4330
	lha r0, 0x0(r6)
	lis r4, double_to_int_802c3c88@ha
	addi r7, r4, double_to_int_802c3c88@l
	stw r3, 0x2d8(r1)
	subf r0, r11, r0
	xoris r4, r11, 0x8000
	xoris r0, r0, 0x8000
	lfd f3, 0x0(r7)
	stw r0, 0x2dc(r1)
	lfs f1, float_0_8041a0ac(r2)
	lfd f2, 0x2d8(r1)
	stw r4, 0x2d4(r1)
	fsubs f8, f2, f3
	stw r3, 0x2d0(r1)
	lfd f2, 0x2d0(r1)
	fcmpu cr0, f8, f1
	fsubs f1, f2, f3
	fsubs f2, f0, f1
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq @9
	lfs f1, dat_8041a0b0(r2)
	b @10
	@9:
	fmr f1, f8
	@10:
	fdivs f7, f2, f1
	lfs f2, float_2_8041a0c0(r2)
	lfs f1, float_3_8041a0b4(r2)
	lfs f3, float_1_8041a0bc(r2)
	lfs f4, float_neg2_8041a0b8(r2)
	fmuls f5, f7, f7
	fmuls f6, f5, f7
	fmuls f13, f1, f5
	fnmsubs f1, f2, f5, f6
	fmsubs f2, f2, f6, f13
	fsubs f5, f6, f5
	fadds f1, f7, f1
	fadds f2, f3, f2
	fmadds f3, f4, f6, f13
	fmuls f1, f8, f1
	fmuls f4, f8, f5
	fmuls f1, f10, f1
	fmadds f1, f9, f2, f1
	fmadds f1, f11, f3, f1
	fmadds f1, f12, f4, f1
	stfs f1, 0x0(r10)
	@8:
	addi r8, r8, 0x8
	addi r9, r9, 0x8
	addi r10, r10, 0x4
	bdnz @6
	lfs f1, 0x278(r1)
	addi r3, r1, 0x248
	lfs f2, 0x27c(r1)
	lfs f3, 0x280(r1)
	bl PSMTXTrans
	lfs f1, 0x284(r1)
	addi r3, r1, 0x98
	li r4, 0x78
	bl PSMTXRotRad
	lfs f1, 0x288(r1)
	addi r3, r1, 0x68
	li r4, 0x79
	bl PSMTXRotRad
	lfs f1, 0x28c(r1)
	addi r3, r1, 0x38
	li r4, 0x7a
	bl PSMTXRotRad
	lfs f1, 0x290(r1)
	addi r3, r1, 0x218
	lfs f2, 0x294(r1)
	lfs f3, 0x298(r1)
	bl PSMTXScale
	lfs f1, 0x29c(r1)
	addi r3, r1, 0x128
	lfs f2, 0x2a0(r1)
	lfs f3, 0x2a4(r1)
	bl PSMTXTrans
	lfs f1, 0x29c(r1)
	addi r3, r1, 0xf8
	lfs f2, 0x2a0(r1)
	lfs f0, 0x2a4(r1)
	fneg f1, f1
	fneg f2, f2
	fneg f3, f0
	bl PSMTXTrans
	lfs f1, 0x2a8(r1)
	addi r3, r1, 0xc8
	lfs f2, 0x2ac(r1)
	lfs f3, 0x2b0(r1)
	bl PSMTXTrans
	lfs f1, 0x2b4(r1)
	addi r3, r1, 0x1b8
	lfs f2, 0x2b8(r1)
	lfs f3, 0x2bc(r1)
	bl PSMTXTrans
	lfs f1, 0x2b4(r1)
	addi r3, r1, 0x188
	lfs f2, 0x2b8(r1)
	lfs f0, 0x2bc(r1)
	fneg f1, f1
	fneg f2, f2
	fneg f3, f0
	bl PSMTXTrans
	lfs f1, 0x2c0(r1)
	addi r3, r1, 0x158
	lfs f2, 0x2c4(r1)
	lfs f3, 0x2c8(r1)
	bl PSMTXTrans
	addi r3, r1, 0x158
	addi r4, r1, 0x1b8
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x218
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x188
	addi r5, r1, 0x218
	bl PSMTXConcat
	addi r3, r1, 0xc8
	addi r4, r1, 0x128
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x68
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0xf8
	addi r5, r1, 0x1e8
	bl PSMTXConcat
	addi r3, r1, 0x248
	addi r4, r1, 0x1e8
	addi r5, r1, 0x8
	bl PSMTXConcat
	mr r5, r30
	addi r3, r1, 0x8
	addi r4, r1, 0x218
	bl PSMTXConcat
	lfs f1, 0x2cc(r1)
	lfs f0, float_1_8041a0bc(r2)
	fcmpo cr0, f1, f0
	ble @11
	b @12
	@11:
	lfs f0, float_0_8041a0ac(r2)
	fcmpo cr0, f1, f0
	bge @13
	b @12
	@13:
	fmr f0, f1
	@12:
	stfs f0, 0x0(r31)
	b @1
	@5:
	addi r10, r10, 0xb2
	addi r12, r12, 0x1
	bdnz @2
	@1:
	lwz r0, 0x2f4(r1)
	lwz r31, 0x2ec(r1)
	lwz r30, 0x2e8(r1)
	mtlr r0
	addi r1, r1, 0x2f0
	blr
}

asm EffectSet* effGetSet(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, eff_set_table@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r4, eff_set_table@l
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	mr r29, r3
	b @1
	@2:
	lwz r3, 0x4(r31)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @3
	lis r3, eff_set_table@ha
	slwi r4, r30, 3
	addi r0, r3, eff_set_table@l
	add r3, r0, r4
	b @4
	@3:
	addi r31, r31, 0x8
	addi r30, r30, 0x1
	@1:
	lha r0, 0x0(r31)
	cmpwi r0, -0x1
	bne @2
	li r3, 0x0
	@4:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm EffectEntry* effNameToPtr(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r4, wp(r13)
	lwz r30, 0x0(r4)
	lwz r29, 0x4(r4)
	b @1
	@2:
	lwz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq @3
	mr r4, r28
	addi r3, r29, 0x18
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	@3:
	addi r31, r31, 0x1
	addi r29, r29, 0x28
	@1:
	cmpw r31, r30
	blt @2
	@4:
	cmpw r31, r30
	blt @5
	li r3, 0x0
	b @6
	@5:
	mr r3, r29
	@6:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void effSoftDelete(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr. r31, r3
	beq @1
	lwz r3, 0x0(r31)
	cmplwi r3, 0x0
	beq @1
	rlwinm. r0, r3, 0, 30, 30
	beq @2
	ori r0, r3, 0x4
	stw r0, 0x0(r31)
	b @1
	@2:
	cmplwi r31, 0x0
	beq @1
	cmplwi r3, 0x0
	beq @1
	lwz r4, 0xc(r31)
	li r3, 0x3
	bl __memFree
	li r0, 0x0
	stw r0, 0x0(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void effDelete(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr. r31, r3
	beq @1
	lwz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq @1
	lwz r4, 0xc(r31)
	li r3, 0x3
	bl __memFree
	li r0, 0x0
	stw r0, 0x0(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void effMain(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, wp(r13)
	lwz r30, 0x0(r3)
	lwz r29, 0x4(r3)
	b @1
	@2:
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @3
	lwz r0, 0x4(r29)
	cmpwi r0, 0x1
	bne @4
	b @5
	@3:
	lwz r0, 0x4(r29)
	cmpwi r0, 0x0
	bne @4
	@5:
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq @4
	lwz r12, 0x10(r29)
	cmplwi r12, 0x0
	beq @4
	mr r3, r29
	mtctr r12
	bctrl
	@4:
	addi r31, r31, 0x1
	addi r29, r29, 0x28
	@1:
	cmpw r31, r30
	blt @2
	lwz r5, wp(r13)
	lwz r3, gp(r13)
	lwz r4, 0x14(r5)
	lwz r0, 0x16c(r3)
	cmplw r4, r0
	beq @6
	lwz r3, 0x10(r5)
	cmplwi r3, 0x0
	beq @7
	bl fileFree
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0x10(r3)
	@7:
	lwz r4, gp(r13)
	la r3, prefix_tbl(r13)
	lwz r0, 0x16c(r4)
	slwi r0, r0, 2
	lwzx r31, r3, r0
	bl getMarioStDvdRoot
	lis r4, str_802C3C90@ha
	mr r6, r3
	addi r5, r4, str_802C3C90@l
	mr r7, r31
	mr r8, r31
	li r3, 0x4
	li r4, 0x0
	crclr 6
	bl fileAsyncf
	cmplwi r3, 0x0
	beq @6
	lwz r4, gp(r13)
	la r3, prefix_tbl(r13)
	lwz r0, 0x16c(r4)
	slwi r0, r0, 2
	lwzx r31, r3, r0
	bl getMarioStDvdRoot
	lis r4, str_802C3C90@ha
	mr r5, r3
	addi r4, r4, str_802C3C90@l
	mr r6, r31
	mr r7, r31
	li r3, 0x4
	crclr 6
	bl fileAllocf
	lwz r4, wp(r13)
	stw r3, 0x10(r4)
	lwz r4, gp(r13)
	lwz r3, wp(r13)
	lwz r0, 0x16c(r4)
	stw r0, 0x14(r3)
	@6:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void effSetName(EffectEntry* effect, const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	mr r28, r4
	li r31, 0x0
	lwz r5, wp(r13)
	lwz r30, 0x0(r5)
	lwz r29, 0x4(r5)
	b @1
	@2:
	lwz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq @3
	mr r4, r28
	addi r3, r29, 0x18
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	@3:
	addi r31, r31, 0x1
	addi r29, r29, 0x28
	@1:
	cmpw r31, r30
	blt @2
	@4:
	mr r4, r28
	addi r3, r27, 0x18
	bl strcpy
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm EffectEntry* effEntry(void) {
	nofralloc
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @1
	@2:
	lwz r0, 0x0(r3)
	cmplwi r0, 0x0
	beq @1
	addi r3, r3, 0x28
	bdnz @2
	@1:
	li r4, 0x1
	li r0, 0x0
	stw r4, 0x0(r3)
	lwz r4, gp(r13)
	lwz r5, 0x14(r4)
	neg r4, r5
	or r4, r4, r5
	srwi r4, r4, 31
	stw r4, 0x4(r3)
	stw r0, 0x14(r3)
	stw r0, 0x8(r3)
	stw r0, 0xc(r3)
	stw r0, 0x10(r3)
	stb r0, 0x18(r3)
	blr
}

asm void effAutoRelease(BOOL inBattle) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	li r30, 0x0
	li r31, 0x0
	lwz r4, wp(r13)
	lwz r29, 0x0(r4)
	lwz r28, 0x4(r4)
	b @1
	@2:
	lwz r3, 0x0(r28)
	clrlwi. r0, r3, 31
	beq @3
	lwz r0, 0x4(r28)
	cmpw r0, r27
	bne @3
	cmplwi r28, 0x0
	beq @3
	cmplwi r3, 0x0
	beq @3
	lwz r4, 0xc(r28)
	li r3, 0x3
	bl __memFree
	stw r31, 0x0(r28)
	@3:
	addi r30, r30, 0x1
	addi r28, r28, 0x28
	@1:
	cmpw r30, r29
	blt @2
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void effGetTexObj(u32 id, GXTexObj* obj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r5, r3
	cmpwi r5, 0x92
	stw r0, 0x14(r1)
	bge @1
	lwz r3, wp(r13)
	lwz r0, 0xc(r3)
	cmpwi r0, 0x0
	bne @2
	mr r3, r4
	la r4, effDummy820(r13)
	li r5, 0x1
	li r6, 0x1
	li r7, 0x0
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	b @3
	@2:
	lwz r3, 0x8(r3)
	bl TEXGetGXTexObjFromPalette
	b @3
	@1:
	lwz r3, wp(r13)
	lwz r3, 0x10(r3)
	cmplwi r3, 0x0
	bne @4
	mr r3, r4
	la r4, effDummy824(r13)
	li r5, 0x1
	li r6, 0x1
	li r7, 0x0
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	b @3
	@4:
	lwz r3, 0xa0(r3)
	subi r5, r5, 0x92
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	@3:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void effTexSetup(void) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	lis r3, str_802C3CA8@ha
	li r4, 0x0
	stw r0, 0x94(r1)
	li r0, 0x0
	addi r3, r3, str_802C3CA8@l
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	lwz r5, wp(r13)
	stw r0, 0x8(r5)
	li r5, 0x0
	lwz r6, wp(r13)
	stw r0, 0xc(r6)
	bl arcOpen
	lwz r4, wp(r13)
	stw r3, 0x8(r4)
	lwz r3, wp(r13)
	lwz r3, 0x8(r3)
	cmplwi r3, 0x0
	bne @1
	bl getMarioStDvdRoot
	lis r4, str_802C3CB4@ha
	mr r5, r3
	addi r4, r4, str_802C3CB4@l
	addi r3, r1, 0x8
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	li r4, 0x2
	li r5, 0x0
	bl DVDMgrOpen
	mr r31, r3
	bl DVDMgrGetLength
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r30, r0, 5
	mr r4, r30
	bl __memAlloc
	lwz r6, wp(r13)
	lis r4, _callback_tpl@ha
	addi r7, r4, _callback_tpl@l
	mr r5, r30
	stw r3, 0x8(r6)
	mr r3, r31
	li r6, 0x0
	stw r31, 0x6c(r31)
	lwz r4, wp(r13)
	lwz r4, 0x8(r4)
	bl DVDMgrReadAsync
	b @2
	@1:
	bl UnpackTexPalette
	lwz r3, wp(r13)
	li r0, 0x1
	stw r0, 0xc(r3)
	@2:
	bl effTexSetupN64
	lwz r0, 0x94(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void effInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	stw r0, 0x14(r1)
	li r0, 0x100
	lwz r4, wp(r13)
	stw r0, 0x0(r4)
	lwz r4, wp(r13)
	lwz r0, 0x0(r4)
	mulli r4, r0, 0x28
	bl __memAlloc
	lwz r5, wp(r13)
	li r4, 0x0
	stw r3, 0x4(r5)
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mulli r5, r0, 0x28
	bl memset
	lwz r3, wp(r13)
	li r4, 0x0
	li r0, -0x1
	stw r4, 0x10(r3)
	lwz r3, wp(r13)
	stw r0, 0x14(r3)
	lwz r3, wp(r13)
	stw r4, 0x8(r3)
	lwz r3, wp(r13)
	stw r4, 0xc(r3)
	bl effInit64
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void _callback_tpl(s32 error, DVDFileInfo* info) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, wp(r13)
	lwz r31, 0x2c(r4)
	lwz r3, 0x8(r3)
	bl UnpackTexPalette
	mr r3, r31
	bl DVDMgrClose
	lwz r3, wp(r13)
	li r0, 0x1
	stw r0, 0xc(r3)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
