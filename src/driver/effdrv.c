#include "driver/effdrv.h"
#include "driver/arcdrv.h"
#include "eff/eff_n64.h"
#include "manager/dvdmgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <string.h>
#ifndef NONMATCHING
#include "sdk/texPalette.h"
__declspec(section ".rodata") extern const f64 double_to_int_802c3c88;
__declspec(section ".rodata") extern const char str_802C3C90[];
__declspec(section ".rodata") extern const char str_802C3CA8[];
__declspec(section ".rodata") extern const char str_802C3CB4[];
__declspec(section ".sdata2") extern const f32 float_1000_8041a0a8;
__declspec(section ".sdata2") extern const f32 float_0_8041a0ac;
__declspec(section ".sdata2") extern const f32 dat_8041a0b0;
__declspec(section ".sdata2") extern const f32 float_3_8041a0b4;
__declspec(section ".sdata2") extern const f32 float_neg2_8041a0b8;
__declspec(section ".sdata2") extern const f32 float_1_8041a0bc;
__declspec(section ".sdata2") extern const f32 float_2_8041a0c0;
__declspec(section ".sdata2") extern const u32 gap_09_8041A0C4_sdata2;
#define EXT_LIT(sym, val) (sym)

#endif

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

static void _callback_tpl(s32 error, DVDFileInfo* info) {
	DVDEntry* entry = info->cb.userData;
	UnpackTexPalette(wp->texture);
	DVDMgrClose(entry);
	wp->texLoaded = TRUE;
}

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

#ifndef NONMATCHING
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
int __cvt_ull_flt();
int __div2i();
void effCalcMayaAnimMatrix(struct MayaAnim* anim, struct MayaKeyList* list, f32* mtx, f32* alpha);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void effTexSetup(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		lis r3, str_802C3CA8@ha
		opword 0x38800000
		opword 0x90010094
		opword 0x38000000
		addi r3, r3, str_802C3CA8@l
		opword 0x93E1008C
		opword 0x93C10088
		lwz r5, wp(r13)
		opword 0x90050008
		opword 0x38A00000
		lwz r6, wp(r13)
		opword 0x9006000C
		bl arcOpen
		lwz r4, wp(r13)
		opword 0x90640008
		lwz r3, wp(r13)
		opword 0x80630008
		opword 0x28030000
		opword 0x4082007C
		bl getMarioStDvdRoot
		lis r4, str_802C3CB4@ha
		opword 0x7C651B78
		addi r4, r4, str_802C3CB4@l
		opword 0x38610008
		opword 0x4CC63182
		bl sprintf
		opword 0x38610008
		opword 0x38800002
		opword 0x38A00000
		bl DVDMgrOpen
		opword 0x7C7F1B78
		bl DVDMgrGetLength
		opword 0x3803001F
		opword 0x38600000
		opword 0x541E0034
		opword 0x7FC4F378
		bl __memAlloc
		lwz r6, wp(r13)
		lis r4, _callback_tpl@ha
		addi r7, r4, _callback_tpl@l
		opword 0x7FC5F378
		opword 0x90660008
		opword 0x7FE3FB78
		opword 0x38C00000
		opword 0x93FF006C
		lwz r4, wp(r13)
		opword 0x80840008
		bl DVDMgrReadAsync
		opword 0x48000014
		bl UnpackTexPalette
		lwz r3, wp(r13)
		opword 0x38000001
		opword 0x9003000C
		bl effTexSetupN64
		opword 0x80010094
		opword 0x83E1008C
		opword 0x83C10088
		opword 0x7C0803A6
		opword 0x38210090
#endif
	}
#ifdef NONMATCHING
	else {
		UnpackTexPalette(wp->texture);
		wp->texLoaded = TRUE;
	}
	effTexSetupN64();
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void effGetTexObj(u32 id, GXTexObj* obj) {
#ifdef __MWERKS__
#ifndef NONMATCHING
#pragma explicit_zero_data on
#endif
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
#ifndef NONMATCHING
#pragma explicit_zero_data reset
#endif
#endif
}

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
#ifdef NONMATCHING
		if (fileAsyncf(4, 0, "%s/e/%s/effect_%s.tpl", dvdroot, prefix, prefix) != 0U) {
#endif
#ifndef NONMATCHING
		if (fileAsyncf(4, 0, EXT_LIT((char*)str_802C3C90, "%s/e/%s/effect_%s.tpl"), dvdroot, prefix, prefix) != 0U) {
#endif
			prefix = prefix_tbl[gp->language];
#ifdef NONMATCHING
			wp->handle = fileAllocf(4, "%s/e/%s/effect_%s.tpl", getMarioStDvdRoot(), prefix, prefix);
#endif
#ifndef NONMATCHING
			wp->handle = fileAllocf(4, EXT_LIT((char*)str_802C3C90, "%s/e/%s/effect_%s.tpl"), getMarioStDvdRoot(), prefix, prefix);
#endif
			wp->language = gp->language;
		}
	}
}

void effDelete(EffectEntry* effect) {
	if (effect && effect->flags) {
		__memFree(HEAP_EFFECT, effect->userdata);
		effect->flags = 0;
	}
}

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

EffectSet* effGetSet(const char* name) {
	s32 i;

	for (i = 0; eff_set_table[i].id != -1; i++) { //run until end of table
		if (!strcmp(eff_set_table[i].name, name)) {
			return &eff_set_table[i];
		}
	}
	return NULL;
}

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void effCalcMayaAnimMatrix(MayaAnim* anim, MayaKeyList* list, f32* mtx, f32* alpha) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FD10
		opword 0x7C0802A6
		lis r7, double_to_int_802c3c88@ha
		opword 0x3D000607
		opword 0x900102F4
		opword 0x39280607
		lfd f1, double_to_int_802c3c88@l(r7)
		opword 0x39800001
		opword 0x93E102EC
		opword 0x7CDF3378
		opword 0x394000B2
		opword 0x3CE04330
		opword 0x93C102E8
		opword 0x7CBE2B78
		opword 0x81640000
		opword 0x380BFFFF
		opword 0x7C0903A6
		opword 0x2C0B0001
		opword 0x4081034C
		opword 0x38ACFFFF
		opword 0x81040004
		opword 0x1CA500B2
		opword 0x7CC85214
		opword 0x7CA82A14
		opword 0x7D35E3A6
		opword 0xA9060000
		opword 0x90E102D0
		opword 0x6D088000
		opword 0xC0430004
		opword 0x910102D4
		opword 0xC80102D0
		opword 0xEC000828
		opword 0xFC020040
		opword 0x4C401382
		opword 0x4082000C
		opword 0xFC001090
		opword 0x48000028
		opword 0x7C0C0000
		opword 0x408202F0
		opword 0x3C004330
		lis r3, double_to_int_802c3c88@ha
		opword 0x910102D4
		lfd f1, double_to_int_802c3c88@l(r3)
		opword 0x900102D0
		opword 0xC80102D0
		opword 0xEC000828
		opword 0x38000016
		opword 0x7CA82B78
		opword 0x7CC93378
		opword 0x39410278
		opword 0x7C0903A6
		opword 0xE128D002
		opword 0xE028D004
		opword 0xE148D006
		opword 0xE169D002
		opword 0xE189D004
		opword 0xE029D006
		opword 0x88080009
		opword 0x7C000775
		opword 0x4182000C
		opword 0xD12A0000
		opword 0x480000CC
		opword 0xA9650000
		opword 0x3C604330
		opword 0xA8060000
		lis r4, double_to_int_802c3c88@ha
		addi r7, r4, double_to_int_802c3c88@l
		opword 0x906102D8
		opword 0x7C0B0050
		opword 0x6D648000
		opword 0x6C008000
		opword 0xC8670000
		opword 0x900102DC
		lfs f1, float_0_8041a0ac(r2)
		opword 0xC84102D8
		opword 0x908102D4
		opword 0xED021828
		opword 0x906102D0
		opword 0xC84102D0
		opword 0xFC080800
		opword 0xEC221828
		opword 0xEC400828
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f1, dat_8041a0b0(r2)
		opword 0x48000008
		opword 0xFC204090
		opword 0xECE20824
		lfs f2, float_2_8041a0c0(r2)
		lfs f1, float_3_8041a0b4(r2)
		lfs f3, float_1_8041a0bc(r2)
		lfs f4, float_neg2_8041a0b8(r2)
		opword 0xECA701F2
		opword 0xECC501F2
		opword 0xEDA10172
		opword 0xEC22317C
		opword 0xEC4269B8
		opword 0xECA62828
		opword 0xEC27082A
		opword 0xEC43102A
		opword 0xEC6469BA
		opword 0xEC280072
		opword 0xEC880172
		opword 0xEC2A0072
		opword 0xEC2908BA
		opword 0xEC2B08FA
		opword 0xEC2C093A
		opword 0xD02A0000
		opword 0x39080008
		opword 0x39290008
		opword 0x394A0004
		opword 0x4200FF00
		opword 0xC0210278
		opword 0x38610248
		opword 0xC041027C
		opword 0xC0610280
		bl PSMTXTrans
		opword 0xC0210284
		opword 0x38610098
		opword 0x38800078
		bl PSMTXRotRad
		opword 0xC0210288
		opword 0x38610068
		opword 0x38800079
		bl PSMTXRotRad
		opword 0xC021028C
		opword 0x38610038
		opword 0x3880007A
		bl PSMTXRotRad
		opword 0xC0210290
		opword 0x38610218
		opword 0xC0410294
		opword 0xC0610298
		bl PSMTXScale
		opword 0xC021029C
		opword 0x38610128
		opword 0xC04102A0
		opword 0xC06102A4
		bl PSMTXTrans
		opword 0xC021029C
		opword 0x386100F8
		opword 0xC04102A0
		opword 0xC00102A4
		opword 0xFC200850
		opword 0xFC401050
		opword 0xFC600050
		bl PSMTXTrans
		opword 0xC02102A8
		opword 0x386100C8
		opword 0xC04102AC
		opword 0xC06102B0
		bl PSMTXTrans
		opword 0xC02102B4
		opword 0x386101B8
		opword 0xC04102B8
		opword 0xC06102BC
		bl PSMTXTrans
		opword 0xC02102B4
		opword 0x38610188
		opword 0xC04102B8
		opword 0xC00102BC
		opword 0xFC200850
		opword 0xFC401050
		opword 0xFC600050
		bl PSMTXTrans
		opword 0xC02102C0
		opword 0x38610158
		opword 0xC04102C4
		opword 0xC06102C8
		bl PSMTXTrans
		opword 0x38610158
		opword 0x388101B8
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810218
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810188
		opword 0x38A10218
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38810128
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810038
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810068
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610008
		opword 0x388100F8
		opword 0x38A101E8
		bl PSMTXConcat
		opword 0x38610248
		opword 0x388101E8
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x7FC5F378
		opword 0x38610008
		opword 0x38810218
		bl PSMTXConcat
		opword 0xC02102CC
		lfs f0, float_1_8041a0bc(r2)
		opword 0xFC010040
		opword 0x40810008
		opword 0x48000018
		lfs f0, float_0_8041a0ac(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0x48000008
		opword 0xFC000890
		opword 0xD01F0000
		opword 0x48000010
		opword 0x394A00B2
		opword 0x398C0001
		opword 0x4200FCBC
		opword 0x800102F4
		opword 0x83E102EC
		opword 0x83C102E8
		opword 0x7C0803A6
		opword 0x382102F0
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

MayaAnim* effMayaAnimAlloc(MayaAnimData* data) {
	s32 size = data->lists->count * sizeof(MayaJoint) + 0x18;
	MayaAnim* anim = __memAlloc(HEAP_EFFECT, size);
	memset(anim, 0, size);
	anim->data = data;
	return anim;
}

void effDeleteMayaAnim(MayaAnim* anim) {
	__memFree(HEAP_EFFECT, anim);
}

void effPlayMayaAnim(MayaAnim* anim) {
	OSTime now = gp->inBattle ? gp->renderTime : gp->renderFieldTime;
	anim->startTime = now / (OS_TIMER_CLOCK / 1000);
#ifdef NONMATCHING
	anim->time = 0.0f;
#endif
#ifndef NONMATCHING
	anim->time = EXT_LIT(float_0_8041a0ac, 0.0f);
#endif
	anim->flags |= 1;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void effCalcMayaAnim(MayaAnim* anim) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm {
		mr r31, r3
	}
	asm volatile {
		opword 0xA0630000
		opword 0x546007FF
		opword 0x4182010C
		opword 0x546007BD
		opword 0x40820104
		lwz r29, gp(r13)
		opword 0x801D0014
		opword 0x2C000000
		opword 0x41820010
		opword 0x807D0038
		opword 0x809D003C
		opword 0x4800000C
		opword 0x807D0040
		opword 0x809D0044
		opword 0x3CC08000
		opword 0x3CA01062
		opword 0x800600F8
		opword 0x38C54DD3
		opword 0x38A00000
		opword 0x5400F0BE
		opword 0x7C060016
		opword 0x5406D1BE
		bl __div2i
		opword 0x80BF000C
		opword 0x801F0008
		opword 0x7C852010
		opword 0x7C601910
		bl __cvt_ull_flt
		opword 0x809D0004
		opword 0x3C004330
		opword 0x90010008
		lis r3, double_to_int_802c3c88@ha
		opword 0x6C808000
		lfd f3, double_to_int_802c3c88@l(r3)
		opword 0x9001000C
		lfs f0, float_1000_8041a0a8(r2)
		opword 0xC8410008
		opword 0xEC421828
		opword 0xEC220072
		opword 0xEC010024
		opword 0xD01F0004
		opword 0x807F0010
		opword 0xC01F0004
		opword 0xC0230004
		opword 0xFC000840
		opword 0x4C411382
		opword 0x40820014
		opword 0xD03F0004
		opword 0xA01F0000
		opword 0x60000002
		opword 0xB01F0000
		opword 0x7FFEFB78
		li r28, 0x0
		opword 0x3BA00000
		opword 0x48000028
		opword 0x80030004
		opword 0x7FE3FB78
		opword 0x38BE0014
		opword 0x38DE0044
		opword 0x7C80EA14
		bl effCalcMayaAnimMatrix
		opword 0x3BDE0034
		opword 0x3BBD0010
		opword 0x3B9C0001
		opword 0x807F0010
		opword 0x80630008
		opword 0x80030000
		opword 0x7C1C0000
		opword 0x4180FFCC
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

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
#ifndef NONMATCHING
#pragma explicit_zero_data on
#endif
static char effDummy820 ATTRIBUTE_ALIGN(32) = 0;
static char effDummy824 ATTRIBUTE_ALIGN(32) = 0;
#ifndef NONMATCHING
#pragma explicit_zero_data reset
#endif

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f64 double_to_int_802c3c88 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802C3C90[] = "%s/e/%s/effect_%s.tpl\0\0";
__declspec(section ".rodata") const char str_802C3CA8[] = "effect.tpl\0";
__declspec(section ".rodata") const char str_802C3CB4[] = "%s/e/jp/effect.tpl\0";
__declspec(section ".sdata2") const f32 float_1000_8041a0a8 = 1000.0f;
__declspec(section ".sdata2") const f32 float_0_8041a0ac = 0.0f;
__declspec(section ".sdata2") const f32 dat_8041a0b0 = 0.00000001f;
__declspec(section ".sdata2") const f32 float_3_8041a0b4 = 3.0f;
__declspec(section ".sdata2") const f32 float_neg2_8041a0b8 = -2.0f;
__declspec(section ".sdata2") const f32 float_1_8041a0bc = 1.0f;
__declspec(section ".sdata2") const f32 float_2_8041a0c0 = 2.0f;
__declspec(section ".sdata2") const u32 gap_09_8041A0C4_sdata2 = 0x00000000;

#endif