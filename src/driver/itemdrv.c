#include "driver/itemdrv.h"
#include "driver/swdrv.h"
#define iconEntry iconEntry_hidden
#define iconChange iconChange_hidden
#include "driver/icondrv.h"
#undef iconEntry
#undef iconChange
#include "driver/windowdrv.h"
#include "manager/evtmgr.h"
#include "driver/camdrv.h"
#include "driver/mobjdrv.h"
#include "eff/eff_stardust.h"
#include "pmario_sound.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/msgdrv.h"
#include "driver/seqdrv.h"
#include "data/item_data.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "party.h"
#include "party/party_vivian.h"
#include "memory.h"
#include "system.h"
#include <string.h>
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_802cabe0[3];
__declspec(section ".rodata") extern const f32 vec3_802cabec[3];
__declspec(section ".rodata") extern const f32 vec3_802cabf8[3];
__declspec(section ".rodata") extern const f32 vec3_802cac04[3];
__declspec(section ".rodata") extern const f32 vec3_802cac10[3];
__declspec(section ".rodata") extern const f32 vec3_802cac1c[3];
__declspec(section ".rodata") extern const f64 double_20_802cac28;
__declspec(section ".rodata") extern const f64 double_0p5_802cac30;
__declspec(section ".rodata") extern const f64 double_3_802cac38;
__declspec(section ".rodata") extern const f64 double_0_802cac40;
__declspec(section ".rodata") extern const f64 double_to_int_802cac48;
__declspec(section ".rodata") extern const char str_802CAC50[];
__declspec(section ".rodata") extern const char str_802CAC60[];
__declspec(section ".rodata") extern const char str_802CAC7C[];
__declspec(section ".rodata") extern const char str_802CAC8C[];
__declspec(section ".rodata") extern const char str_802CAC9C[];
__declspec(section ".rodata") extern const char str_802CACB0[];
__declspec(section ".rodata") extern const char str_802CACCC[];
__declspec(section ".rodata") extern const char str_802CACE0[];
__declspec(section ".rodata") extern const char str_802CACF4[];
__declspec(section ".rodata") extern const char str_802CAD0C[];
__declspec(section ".rodata") extern const char str_802CAD24[];
__declspec(section ".rodata") extern const char str_802CAD38[];
__declspec(section ".rodata") extern const char str_802CAD4C[];
__declspec(section ".rodata") extern const char str_802CAD60[];
__declspec(section ".rodata") extern const char str_802CAD78[];
__declspec(section ".rodata") extern const char str_802CAD8C[];
__declspec(section ".rodata") extern const char str_802CADA0[];
__declspec(section ".rodata") extern const char str_802CADBC[];
__declspec(section ".rodata") extern const char str_802CADD0[];
__declspec(section ".rodata") extern const char str_802CADE0[];
__declspec(section ".rodata") extern const char str_802CADE8[];
__declspec(section ".rodata") extern const char str_802CAE00[];
__declspec(section ".rodata") extern const char str_802CAE18[];
__declspec(section ".rodata") extern const char str_802CAE30[];
__declspec(section ".rodata") extern const char str_802CAE48[];
__declspec(section ".rodata") extern const f64 double_neg1_802cae60;
__declspec(section ".sdata2") extern const u32 dat_8041af90;
__declspec(section ".sdata2") extern const u32 dat_8041af94;
__declspec(section ".sdata2") extern const u32 dat_8041af98;
__declspec(section ".sdata2") extern const f32 float_0_8041af9c;
__declspec(section ".sdata2") extern const f32 float_20_8041afa0;
__declspec(section ".sdata2") extern const f32 float_1_8041afa4;
__declspec(section ".sdata2") extern const f32 float_4_8041afa8;
__declspec(section ".sdata2") extern const f32 float_neg1_8041afac;
__declspec(section ".sdata2") extern const f32 float_10_8041afb0;
__declspec(section ".sdata2") extern const f32 float_15_8041afb4;
__declspec(section ".sdata2") extern const f32 float_0p5_8041afb8;
__declspec(section ".sdata2") extern const f32 float_180_8041afbc;
__declspec(section ".sdata2") extern const f32 float_100_8041afc0;
__declspec(section ".sdata2") extern const f32 float_35_8041afc4;
__declspec(section ".sdata2") extern const f32 float_16_8041afc8;
__declspec(section ".sdata2") extern const f32 float_500_8041afcc;
__declspec(section ".sdata2") extern const f32 float_90_8041afd0;
__declspec(section ".sdata2") extern const f32 float_30_8041afd4;
__declspec(section ".sdata2") extern const f32 float_0p67_8041afd8;
__declspec(section ".sdata2") extern const f32 float_1E06_8041afdc;
__declspec(section ".sdata2") extern const f32 float_6p2832_8041afe0;
__declspec(section ".sdata2") extern const f32 float_360_8041afe4;
__declspec(section ".sdata2") extern const f32 float_neg980_8041afe8;
__declspec(section ".sdata2") extern const f32 float_0p25_8041afec;
__declspec(section ".sdata2") extern const f32 float_neg1000_8041aff0;
__declspec(section ".sdata2") extern const f32 float_0p7_8041aff4;
__declspec(section ".sdata2") extern const f32 float_8_8041aff8;
__declspec(section ".sdata2") extern const f32 float_1024_8041affc;
__declspec(section ".sdata2") extern const f32 float_50_8041b000;
__declspec(section ".sdata2") extern const f32 float_62_8041b004;
__declspec(section ".sdata2") extern const f32 float_85_8041b008;
__declspec(section ".sdata2") extern const f32 float_120_8041b00c;
__declspec(section ".sdata2") extern const f32 float_12_8041b010;
__declspec(section ".sdata2") extern const f32 float_1000_8041b014;
#define EXT_LIT(sym, val) (sym)
#endif


#ifdef NONMATCHING
inline Vec unknownVec0(void) {
    return (Vec){ 0.0f, 0.0f, 0.0f };
}
#endif

#ifdef NONMATCHING
inline Vec makeVecByValue2(f32 x, f32 y, f32 z) {
    Vec v = (Vec){ 0.0f, 0.0f, 0.0f };
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
#endif

#ifdef NONMATCHING
inline Vec makeVecByValue(f32 x, f32 y, f32 z) {
    Vec v = (Vec){ 0.0f, 0.0f, 0.0f };
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
#endif
#ifndef NONMATCHING

#endif

extern int __float_nan[];
#ifdef NONMATCHING
static inline s32 item_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 item_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (item_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern ItemData itemDataTable[];
void iconEntry(const char* name, u16 iconId);
void iconChange(const char* name, u16 iconId);
BOOL marioChkItemGetMotion(void);
void marioChgGetItemMotion(void);
void marioChgStayMotion(void);
void marioSetCamId(s32 camId);
EffectEntry* effItemGetEntry(s32 type, f32 x, f32 y, f32 z);
u32 psndBGMChkSilent(s32 a1);
BOOL psndBGMChk(s32 a1);
BOOL psndBGMOff(u32 flags);
s32 msgWindow_Entry(const char* msg, s32 a2, s32 a3);
extern s32 all_juyoitem_lecture[];
BOOL nokonoko_holdItem(void);
BOOL N_fbatPreventMarioEventChk(void);
s32 marioGetJabaraState(void);
EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
EffectEntry* effSplashEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);
double sin(double);
double cos(double);
EffectEntry* effHagetakaFlushN64Entry(s32 a1, s32 a2, f32 x, f32 y, f32 z, f32 scale);

BOOL itemGetNokoCheck(ItemEntry* entry);
void winNameDisp(WinMgrEntry* win);
void winNameDisp2(WinMgrEntry* win);
void winHelpMain(WinMgrEntry* win);
void winHelpDisp(WinMgrEntry* win);
void winFullDisp(WinMgrEntry* win);
BOOL N_itemPickUpFromFieldCheck(void);

ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);
HitEntry* itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy);
HitEntry* itemHitCheckUp(ItemEntry* entry, f32 vy);


HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);
void itemseq_GetItem(ItemEntry* entry);
void itemDelete(const char* name);
void itemModeChange(ItemEntry* entry, s32 mode);
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);

//.bss
static ItemWork work[2];



//.data
WinMgrDesc itemdrv_window_desc[4] = {
	{0, 0, 8, -175, 120, 350, 42, {0xE1, 0xD7, 0x9B, 0xFF}, NULL, winNameDisp},
	{0, 0, 8, -240, -130, 500, 80, {0xF0, 0xF0, 0xF0, 0xFF}, winHelpMain, winHelpDisp},
	{0, 0, 8, -175, 200, 350, 75, {0x2B, 0xA4, 0xFF, 0xFF}, NULL, winFullDisp},
	{0, 0, 8, -175, 120, 350, 42, {0xE1, 0xD7, 0x9B, 0xFF}, NULL, winNameDisp2},
};

//TODO: inline function? I see nothing in the symbol map
#define itemGetWork() (gp->inBattle ? &work[1] : &work[0])

inline void itemCheckBadge(ItemEntry* entry) {
    if (!gp->inBattle) {
        if (BADGE_MIN <= entry->itemId && entry->itemId < BADGE_MAX) {
            if (entry->flags & 0x100) {
                pouchArriveBadge(entry->itemId);
            }
        }
    }
}

void itemseq_Bound(ItemEntry* entry);
#ifdef NONMATCHING
static inline BOOL itemGetPouch(ItemEntry* entry) {
	EventEntry* evt;
#endif

#ifdef NONMATCHING
	if (!pouchGetItem(entry->itemId)) {
		return FALSE;
#endif
#ifndef NONMATCHING

void itemGetSound(ItemEntry* entry);

void itemInit(void);

void itemReInit(void);

void itemCoinDrop(Vec* position);

BOOL itemGetCheck(ItemEntry* entry);

BOOL itemGetNokoCheck(ItemEntry* entry);

BOOL N_itemPickUpFromFieldCheck(void);

typedef struct ItemEffPos {
	u8 pad[8];
	Vec position;
} ItemEffPos;


void itemMain(void);
int FontDrawEdge();
int FontDrawEdgeOff();
f32 PSVECMag(const Vec* v);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
int __cvt_dbl_usll();
int __cvt_sll_flt();
int __div2i();
void *memset(void *dest, int ch, size_t count);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
extern void* jumptable_80312488[];
extern void* jumptable_80312440[];
void itemMain(void);

void itemModeChange(ItemEntry* entry, s32 mode);

ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);

void itemDelete(const char* name);

ItemEntry* itemNameToPtr(char* name);

ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);

ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range);

void winNameDisp(WinMgrEntry* win);

void winNameDisp2(WinMgrEntry* win);

void winHelpMain(WinMgrEntry* win);

void winHelpDisp(WinMgrEntry* win);

void winFullDisp(WinMgrEntry* win);


__declspec(section ".data") static void* jumptable_80312418[] = {
    (char*)itemseq_GetItem + 0x64,
    (char*)itemseq_GetItem + 0x3D8,
    (char*)itemseq_GetItem + 0x938,
    (char*)itemseq_GetItem + 0x95C,
    (char*)itemseq_GetItem + 0xC5C,
    (char*)itemseq_GetItem + 0xD8C,
    (char*)itemseq_GetItem + 0xFA8,
    (char*)itemseq_GetItem + 0xFEC,
    (char*)itemseq_GetItem + 0x1200,
    (char*)itemseq_GetItem + 0x1104,
};
__declspec(section ".data") void* jumptable_80312440[] = {
    (char*)itemEntry + 0x628,
    (char*)itemEntry + 0x63C,
    (char*)itemEntry + 0x7BC,
    (char*)itemEntry + 0x670,
    (char*)itemEntry + 0x65C,
    (char*)itemEntry + 0x770,
    (char*)itemEntry + 0x790,
    (char*)itemEntry + 0x764,
    (char*)itemEntry + 0x700,
    (char*)itemEntry + 0x6F4,
    (char*)itemEntry + 0x72C,
    (char*)itemEntry + 0x690,
    (char*)itemEntry + 0x6BC,
    (char*)itemEntry + 0x7D0,
    (char*)itemEntry + 0x7E4,
    (char*)itemEntry + 0x7F8,
    (char*)itemEntry + 0x614,
    (char*)itemEntry + 0x608,
};
__declspec(section ".data") void* jumptable_80312488[] = {
    (char*)itemMain + 0x47C,
    (char*)itemMain + 0x29C,
    (char*)itemMain + 0x35C,
    (char*)itemMain + 0x290,
    (char*)itemMain + 0x290,
    (char*)itemMain + 0x284,
    (char*)itemMain + 0x284,
    (char*)itemMain + 0x47C,
    (char*)itemMain + 0x368,
    (char*)itemMain + 0x3BC,
    (char*)itemMain + 0x284,
};
void itemseq_GetItem(ItemEntry* entry);

static s32 _move_dir_1090;
void itemseq_Bound(ItemEntry* entry);

void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z);






HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);

HitEntry*
itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy) {
	HitEntry* hit;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;

	hitDist = EXT_LIT(float_20_8041afa0, 20.0f) + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, EXT_LIT(float_0_8041af9c, 0.0f), EXT_LIT(float_neg1_8041afac, -1.0f), EXT_LIT(float_0_8041af9c, 0.0f))) {
		entry->position.y = hitY;
#endif
	}
#ifdef NONMATCHING
	if (entry->flags & 0x20) {
		swSet(entry->evtId);
#endif
#ifndef NONMATCHING
	else {
		hit = NULL;
		entry->position.y += vy;
#endif
	}
#ifdef NONMATCHING
	else if (entry->flags & 0x40) {
		_swSet(entry->evtId);
	}
	if ((u32)entry->evtCode != 0) {
		evt = evtEntry((void*)entry->evtCode, 0, 0x20);
		evt->lwData[0] = FLOAT(entry->position.x);
		evt->lwData[1] = FLOAT(entry->position.y);
		evt->lwData[2] = FLOAT(entry->position.z);
	}
	entry->flags2 |= 1;
	return TRUE;
#endif
#ifndef NONMATCHING
	return hit;
#endif
}

#ifdef NONMATCHING
static inline void itemGetEnd(ItemEntry* entry) {
	marioStSystemLevel(0);
	psndClearFlag(0x80);
	if (entry->flags2 & 0x1000000) {
		entry->flags2 &= ~0x1000000;
		marioCtrlOn();
#endif
#ifndef NONMATCHING
HitEntry*
itemHitCheckUp(ItemEntry* entry, f32 vy) {
	HitEntry* hit;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	f32 x, y, z;

	if (vy <= EXT_LIT(float_0_8041af9c, 0.0f)) {
		return NULL;
#endif
	}
#ifdef NONMATCHING
	marioKeyOn();
	marioChgStayMotion();
	camGetPtr(8)->flags &= ~0x200;
#endif
#ifndef NONMATCHING
	x = entry->position.x; y = EXT_LIT(float_20_8041afa0, 20.0f) + entry->position.y; z = entry->position.z;
	hitDist = EXT_LIT(float_20_8041afa0, 20.0f) + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, EXT_LIT(float_0_8041af9c, 0.0f), EXT_LIT(float_1_8041afa4, 1.0f), EXT_LIT(float_0_8041af9c, 0.0f))) {
		entry->position.y = hitY - 20.0f - 4.0f;
		return hit;
	}
	x = entry->position.x; y = entry->position.y; z = entry->position.z;
	hitDist = EXT_LIT(float_20_8041afa0, 20.0f) + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, EXT_LIT(float_0_8041af9c, 0.0f), EXT_LIT(float_1_8041afa4, 1.0f), EXT_LIT(float_0_8041af9c, 0.0f))) {
		entry->position.y = hitY - 20.0f;
		return hit;
	}
	return NULL;
#endif
}

#ifdef NONMATCHING
void itemGetSound(ItemEntry* entry);
#endif
#ifndef NONMATCHING
void itemForceGet(ItemEntry* entry);

void itemNokoForceGet(ItemEntry* entry);

void itemFlagOn(ItemEntry* entry, u16 flags);

void itemFlagOff(ItemEntry* entry, u16 flags);

u16 itemFlag(ItemEntry* entry, u16 flags);

void itemStatusOn(ItemEntry* entry, u32 flags);

u32 itemStatus(ItemEntry* entry, u32 flags);

void itemPickUp(ItemEntry* entry);


// prototypes for asm stopgap forward references
void itemPickUp(ItemEntry* entry);
u32 itemStatus(ItemEntry* entry, u32 flags);
void itemStatusOn(ItemEntry* entry, u32 flags);
u16 itemFlag(ItemEntry* entry, u16 flags);
void itemFlagOff(ItemEntry* entry, u16 flags);
void itemFlagOn(ItemEntry* entry, u16 flags);
void itemNokoForceGet(ItemEntry* entry);
void itemForceGet(ItemEntry* entry);
HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);
void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z);
void itemseq_Bound(ItemEntry* entry);
void itemseq_GetItem(ItemEntry* entry);
void winFullDisp(WinMgrEntry* win);
void winHelpDisp(WinMgrEntry* win);
void winHelpMain(WinMgrEntry* win);
void winNameDisp2(WinMgrEntry* win);
void winNameDisp(WinMgrEntry* win);
ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemNameToPtr(char* name);
void itemDelete(const char* name);
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);
void itemModeChange(ItemEntry* entry, s32 mode);
void itemMain(void);
BOOL N_itemPickUpFromFieldCheck(void);
BOOL itemGetNokoCheck(ItemEntry* entry);
BOOL itemGetCheck(ItemEntry* entry);
void itemCoinDrop(Vec* position);
void itemReInit(void);
void itemInit(void);

static inline void itemModeChange__af_inl(ItemEntry* entry, s32 mode) {
	entry->mode = mode;
	entry->subState = 0;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void winNameDisp(WinMgrEntry* win) {
	asm volatile {
		opword 0x9421FBE0
		opword 0x7C0802A6
		opword 0x90010424
		opword 0x93E1041C
		opword 0x93C10418
		opword 0x7C7E1B78
		lis r3, itemDataTable@ha
		opword 0x93A10414
		addi r3, r3, itemDataTable@l
		opword 0x83FE002C
		opword 0x801F0004
		opword 0x1C000028
		opword 0x7C630214
		opword 0x80630004
		bl msgSearch
		opword 0x801F0004
		opword 0x7C7D1B78
		opword 0x2C0000F0
		opword 0x41800030
		opword 0x2C000153
		opword 0x40800028
		lis r3, str_802CAE30@ha
		addi r3, r3, str_802CAE30@l
		bl msgSearch
		opword 0x7C641B78
		opword 0x7FA5EB78
		opword 0x3861000C
		opword 0x4CC63182
		bl sprintf
		opword 0x48000024
		lis r3, str_802CAE48@ha
		addi r3, r3, str_802CAE48@l
		bl msgSearch
		opword 0x7C641B78
		opword 0x7FA5EB78
		opword 0x3861000C
		opword 0x4CC63182
		bl sprintf
		opword 0x3861000C
		bl FontGetMessageWidth
		opword 0x547D043E
		opword 0x801E0020
		opword 0x387D0014
		opword 0x7C030000
		opword 0x40810020
		opword 0x907E0020
		opword 0x801E0020
		opword 0x7C6000D0
		opword 0x54600FFE
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x901E0018
		opword 0x807F0028
		bl winMgrAction
		opword 0x2C030000
		opword 0x40820038
		bl FontDrawStart
		lwz r0, dat_8041af90(r2)
		opword 0x38610008
		opword 0x90010008
		bl FontDrawColor
		opword 0x7C9D00D0
		opword 0x807E001C
		opword 0x54800FFE
		opword 0x38A1000C
		opword 0x7C002214
		opword 0x3883FFF8
		opword 0x7C030E70
		bl FontDrawMessage
		opword 0x80010424
		opword 0x83E1041C
		opword 0x83C10418
		opword 0x83A10414
		opword 0x7C0803A6
		opword 0x38210420
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void winNameDisp2(WinMgrEntry* win) {
	asm volatile {
		opword 0x9421FBE0
		opword 0x7C0802A6
		opword 0x90010424
		opword 0x93E1041C
		opword 0x93C10418
		opword 0x7C7E1B78
		lis r3, itemDataTable@ha
		opword 0x93A10414
		addi r3, r3, itemDataTable@l
		opword 0x83FE002C
		opword 0x801F0004
		opword 0x1C000028
		opword 0x7C630214
		opword 0x80630004
		bl msgSearch
		lis r4, str_802CAE18@ha
		opword 0x7C7D1B78
		addi r0, r4, str_802CAE18@l
		opword 0x7C030378
		bl msgSearch
		opword 0x7C641B78
		opword 0x7FA5EB78
		opword 0x3861000C
		opword 0x4CC63182
		bl sprintf
		opword 0x3861000C
		bl FontGetMessageWidth
		opword 0x547D043E
		opword 0x801E0020
		opword 0x387D0014
		opword 0x7C030000
		opword 0x40810020
		opword 0x907E0020
		opword 0x801E0020
		opword 0x7C6000D0
		opword 0x54600FFE
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x901E0018
		opword 0x807F0028
		bl winMgrAction
		opword 0x2C030000
		opword 0x40820038
		bl FontDrawStart
		lwz r0, dat_8041af94(r2)
		opword 0x38610008
		opword 0x90010008
		bl FontDrawColor
		opword 0x7C9D00D0
		opword 0x807E001C
		opword 0x54800FFE
		opword 0x38A1000C
		opword 0x7C002214
		opword 0x3883FFF8
		opword 0x7C030E70
		bl FontDrawMessage
		opword 0x80010424
		opword 0x83E1041C
		opword 0x83C10418
		opword 0x83A10414
		opword 0x7C0803A6
		opword 0x38210420
	}
}
#pragma pop

void winHelpMain(WinMgrEntry* win) {
	winMgrHelpMain(win);
}

void winHelpDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;

	if (!winMgrAction(entry->winId[1])) {
		win->msg = msgSearch(itemDataTable[entry->itemId].description);
		winMgrHelpDraw(win);
	}
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void winFullDisp(WinMgrEntry* win) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x38000000
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x7C7E1B78
		opword 0x93A10014
		opword 0x93810010
		opword 0x83E3002C
		opword 0x807F0004
		opword 0x2C0300F0
		opword 0x41800010
		opword 0x2C030153
		opword 0x40800008
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820014
		lis r3, str_802CADE8@ha
		addi r3, r3, str_802CADE8@l
		bl msgSearch
		opword 0x48000010
		lis r3, str_802CAE00@ha
		addi r3, r3, str_802CAE00@l
		bl msgSearch
		opword 0x7C7D1B78
		bl FontGetMessageWidth
		opword 0x547C043E
		opword 0x801E0020
		opword 0x387C0014
		opword 0x7C030000
		opword 0x40810020
		opword 0x907E0020
		opword 0x801E0020
		opword 0x7C6000D0
		opword 0x54600FFE
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x901E0018
		opword 0x807F0030
		bl winMgrAction
		opword 0x2C030000
		opword 0x40820040
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041af98(r2)
		opword 0x38610008
		opword 0x90010008
		bl FontDrawColor
		opword 0x7C9C00D0
		opword 0x807E001C
		opword 0x54800FFE
		opword 0x7FA5EB78
		opword 0x7C002214
		opword 0x3883FFF6
		opword 0x7C030E70
		bl FontDrawMessage
		bl FontDrawEdgeOff
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x83810010
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void itemseq_GetItem(ItemEntry* entry) {
	char _af_pad[72];
	asm {
		lis r4, work@ha
	}
	asm volatile {
		addi r29, r4, work@l
		lis r4, vec3_802cabe0@ha
		opword 0x7C7F1B78
		addi r28, r4, vec3_802cabe0@l
		lwz r5, gp(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BBD001C
		bl marioGetPtr
		opword 0xA01F0026
		opword 0x7C7E1B78
		opword 0x28000009
		opword 0x418112C8
		lis r3, jumptable_80312418@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80312418@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x801F0038
		opword 0x5400041C
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x540005EF
		opword 0x41820014
		opword 0x801F0038
		opword 0x64000400
		opword 0x901F0038
		opword 0x48000010
		opword 0x801F0038
		opword 0x54000188
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x5400062C
		opword 0xB01F0000
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x418202AC
		opword 0x807F0004
		bl pouchGetItem
		opword 0x2C030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480000B8
		opword 0xA07F0000
		opword 0x546006B5
		opword 0x41820010
		opword 0x807F0008
		bl swSet
		opword 0x48000014
		opword 0x54600673
		opword 0x4182000C
		opword 0x807F0008
		bl _swSet
		opword 0x807F0020
		opword 0x28030000
		opword 0x41820074
		opword 0x38800000
		opword 0x38A00020
		bl evtEntry
		lfs f1, float_1024_8041affc(r2)
		opword 0xC01F003C
		opword 0xEC010032
		opword 0xFC00001E
		stfd f0, _af_pad+48(r1)
		opword 0x8081003C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x9003009C
		opword 0xC01F0040
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010040
		opword 0x80810044
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A0
		opword 0xC01F0044
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8081004C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A4
		opword 0x801F0038
		opword 0x38600001
		opword 0x60000001
		opword 0x901F0038
		opword 0x2C030000
		opword 0x418201C4
		opword 0x38000000
		opword 0x901F007C
		opword 0x901F0078
		opword 0x809C003C
		opword 0x807C0040
		opword 0x801C0044
		opword 0x9081002C
		opword 0xC03F003C
		opword 0x90610030
		opword 0xC05F0040
		opword 0xD021002C
		opword 0xC07F0044
		opword 0x90010034
		opword 0x8081002C
		opword 0xD0410030
		opword 0xD0610034
		opword 0x80610030
		opword 0x80010034
		opword 0x90810020
		opword 0x90610024
		opword 0x90010028
		opword 0x801F0004
		opword 0x2C00007B
		opword 0x41820088
		opword 0x40800014
		opword 0x2C000079
		opword 0x4182001C
		opword 0x40800048
		opword 0x48000090
		opword 0x2C00007D
		opword 0x41820088
		opword 0x40800084
		opword 0x48000074
		lfs f0, float_35_8041afc4(r2)
		opword 0x38600001
		lfs f4, float_16_8041afc8(r2)
		opword 0x38800003
		opword 0xEC40102A
		opword 0x38A0001E
		opword 0xFCA02090
		bl effStardustEntry
		opword 0x387C0070
		opword 0x38810020
		bl psndSFXOn_3D
		opword 0x48000050
		lfs f0, float_35_8041afc4(r2)
		opword 0x38600001
		lfs f4, float_16_8041afc8(r2)
		opword 0x38800003
		opword 0xEC40102A
		opword 0x38A0001E
		opword 0xFCA02090
		bl effStardustEntry
		opword 0x387C0080
		opword 0x38810020
		bl psndSFXOn_3D
		opword 0x48000020
		opword 0x387C009C
		opword 0x38810020
		bl psndSFXOn_3D
		opword 0x48000010
		opword 0x387C00AC
		opword 0x38810020
		bl psndSFXOn_3D
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r26, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B5A001C
		opword 0x839A0004
		opword 0x3B600000
		opword 0x4800008C
		opword 0x387C000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x807C0004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA01C0000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x801C0004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x807C001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x387C000C
		bl iconDelete
		opword 0xA01C0000
		opword 0x5400043C
		opword 0xB01C0000
		opword 0x3B7B0001
		opword 0x3B9C0098
		opword 0x801A0000
		opword 0x7C1B0000
		opword 0x4180FF70
		opword 0x48000FD0
		opword 0x38600004
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x48000FBC
		opword 0x38600001
		opword 0x38000000
		opword 0xB07F0026
		opword 0x38600008
		opword 0x901F007C
		opword 0x901F0078
		bl camGetPtr
		opword 0xA0030000
		opword 0x60000200
		opword 0xB0030000
		bl marioKeyOff
		opword 0x38600002
		bl marioStSystemLevel
		opword 0x38600080
		bl psndSetFlag
		lfs f0, float_0_8041af9c(r2)
		opword 0xD01E0174
		opword 0xD01E017C
		opword 0xD01E0180
		opword 0xD01E018C
		opword 0x801F0004
		opword 0x2C000007
		opword 0x4182001C
		opword 0x2C000008
		opword 0x41820014
		opword 0x2C00000A
		opword 0x4182000C
		opword 0x2C00000B
		opword 0x40820010
		opword 0x801F0038
		opword 0x60002000
		opword 0x901F0038
		opword 0xA07F0000
		opword 0x546004E7
		opword 0x4182000C
		opword 0x54600463
		opword 0x41820048
		bl marioChkItemGetMotion
		opword 0x2C030000
		opword 0x4082003C
		opword 0xA07E002E
		opword 0x28030005
		opword 0x41820024
		opword 0x3803FFFA
		opword 0x5400043E
		opword 0x28000002
		opword 0x40810014
		opword 0x2803000F
		opword 0x4182000C
		opword 0x2803000E
		opword 0x40820EF0
		opword 0x38000008
		opword 0xB01F0026
		opword 0x48000EE4
		opword 0x38000002
		opword 0xB01F0026
		bl marioChgGetItemMotion
		lfs f2, float_50_8041b000(r2)
		opword 0x3B600007
		opword 0xC03E0090
		opword 0x3B40FFFF
		opword 0xC07E0094
		opword 0xC01E008C
		opword 0xEC22082A
		opword 0xD01F003C
		opword 0xD03F0040
		opword 0xD07F0044
		opword 0x801F0004
		opword 0x2C000057
		opword 0x40820010
		opword 0x3B600004
		opword 0x3B40FFFF
		opword 0x48000078
		opword 0x2C00007D
		opword 0x40820010
		opword 0x3B600008
		opword 0x3B400000
		opword 0x48000064
		opword 0x2C00000C
		opword 0x40800010
		opword 0x3B600003
		opword 0x3B400003
		opword 0x48000050
		opword 0x2C000072
		opword 0x40800010
		opword 0x3B600006
		opword 0x3B400001
		opword 0x4800003C
		opword 0x2C000079
		opword 0x40800010
		opword 0x3B600000
		opword 0x3B40FFFF
		opword 0x48000028
		opword 0x2C0000EC
		opword 0x40800010
		opword 0x3B600007
		opword 0x3B40FFFF
		opword 0x48000014
		opword 0x2C000153
		opword 0x4080000C
		opword 0x3B600005
		opword 0x3B400002
		lfs f2, float_62_8041b004(r2)
		opword 0x7F63DB78
		opword 0xC01E0090
		opword 0xC03E008C
		opword 0xEC42002A
		opword 0xC07E0094
		bl effItemGetEntry
		opword 0x907D000C
		opword 0x801F0038
		opword 0x540004A5
		opword 0x4182002C
		opword 0x80BD000C
		opword 0x38000005
		opword 0x387F000C
		opword 0x38800200
		opword 0x80A5000C
		opword 0x90050038
		bl iconFlagOn
		opword 0x38600007
		bl marioSetCamId
		opword 0x48000038
		opword 0x80BD000C
		opword 0x38000005
		opword 0x387F000C
		opword 0x38800100
		opword 0x80A5000C
		opword 0x90050038
		bl iconFlagOn
		opword 0x2C1B0000
		opword 0x4182000C
		opword 0x2C1B0003
		opword 0x4082000C
		opword 0x38600005
		bl marioSetCamId
		opword 0xA01F0000
		opword 0x54000421
		opword 0x408200F8
		opword 0x38600000
		bl psndBGMChkSilent
		opword 0x28030000
		opword 0x41820010
		opword 0xA01F0000
		opword 0x60000008
		opword 0xB01F0000
		opword 0x2C1A0002
		opword 0x4182006C
		opword 0x40800014
		opword 0x2C1A0000
		opword 0x41820018
		opword 0x40800038
		opword 0x480000A0
		opword 0x2C1A0004
		opword 0x40800098
		opword 0x48000070
		opword 0xA01F0000
		opword 0x54000739
		opword 0x4082000C
		opword 0x38603800
		bl psndBGMOff
		opword 0x389C0180
		opword 0x38600211
		bl psndBGMOn
		opword 0x48000090
		opword 0xA01F0000
		opword 0x54000739
		opword 0x4082000C
		opword 0x38603800
		bl psndBGMOff
		opword 0x389C0198
		opword 0x38600211
		bl psndBGMOn
		opword 0x4800006C
		opword 0xA01F0000
		opword 0x54000739
		opword 0x4082000C
		opword 0x38603800
		bl psndBGMOff
		opword 0x389C01AC
		opword 0x38600211
		bl psndBGMOn
		opword 0x48000048
		opword 0xA01F0000
		opword 0x54000739
		opword 0x4082000C
		opword 0x38603800
		bl psndBGMOff
		opword 0x389C01C0
		opword 0x38600211
		bl psndBGMOn
		opword 0x48000024
		opword 0xA01F0000
		opword 0x54000739
		opword 0x4082000C
		opword 0x38603800
		bl psndBGMOff
		opword 0x389C01DC
		opword 0x38600211
		bl psndBGMOn
		opword 0x2C1B0008
		opword 0x4082002C
		opword 0x3C80F5DE
		opword 0x38600000
		opword 0x388401A2
		bl evtGetValue
		opword 0x7C651B78
		opword 0x3C60F5DE
		opword 0x388301A2
		opword 0x38600000
		opword 0x38A50001
		bl evtSetValue
		opword 0xA01F0000
		opword 0x540004E2
		opword 0xB01F0000
		opword 0x809C003C
		opword 0x807C0040
		opword 0x801C0044
		opword 0x90810014
		opword 0xC03F003C
		opword 0x90610018
		opword 0xC05F0040
		opword 0xD0210014
		opword 0xC07F0044
		opword 0x9001001C
		opword 0x80810014
		opword 0xD0410018
		opword 0xD061001C
		opword 0x80610018
		opword 0x8001001C
		opword 0x90810008
		opword 0x9061000C
		opword 0x90010010
		opword 0x801F0004
		opword 0x2C00007B
		opword 0x41820088
		opword 0x40800014
		opword 0x2C000079
		opword 0x4182001C
		opword 0x40800048
		opword 0x48000090
		opword 0x2C00007D
		opword 0x41820088
		opword 0x40800084
		opword 0x48000074
		lfs f0, float_35_8041afc4(r2)
		opword 0x38600001
		lfs f4, float_16_8041afc8(r2)
		opword 0x38800003
		opword 0xEC40102A
		opword 0x38A0001E
		opword 0xFCA02090
		bl effStardustEntry
		opword 0x387C0070
		opword 0x38810008
		bl psndSFXOn_3D
		opword 0x48000050
		lfs f0, float_35_8041afc4(r2)
		opword 0x38600001
		lfs f4, float_16_8041afc8(r2)
		opword 0x38800003
		opword 0xEC40102A
		opword 0x38A0001E
		opword 0xFCA02090
		bl effStardustEntry
		opword 0x387C0080
		opword 0x38810008
		bl psndSFXOn_3D
		opword 0x48000020
		opword 0x387C009C
		opword 0x38810008
		bl psndSFXOn_3D
		opword 0x48000010
		opword 0x387C00AC
		opword 0x38810008
		bl psndSFXOn_3D
		lis r3, itemdrv_window_desc@ha
		addi r3, r3, itemdrv_window_desc@l
		bl winMgrEntry
		opword 0x907F0028
		opword 0x807F0028
		bl winMgrOpen
		opword 0x807F0028
		opword 0x7FE4FB78
		bl winMgrSetParam
		opword 0x801F0038
		opword 0x540004A5
		opword 0x4082002C
		lis r3, itemdrv_window_desc@ha
		addi r3, r3, itemdrv_window_desc@l
		opword 0x38630028
		bl winMgrEntry
		opword 0x907F002C
		opword 0x807F002C
		bl winMgrOpen
		opword 0x807F002C
		opword 0x7FE4FB78
		bl winMgrSetParam
		opword 0x807F0004
		bl pouchGetItem
		opword 0x2C030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480000B8
		opword 0xA07F0000
		opword 0x546006B5
		opword 0x41820010
		opword 0x807F0008
		bl swSet
		opword 0x48000014
		opword 0x54600673
		opword 0x4182000C
		opword 0x807F0008
		bl _swSet
		opword 0x807F0020
		opword 0x28030000
		opword 0x41820074
		opword 0x38800000
		opword 0x38A00020
		bl evtEntry
		lfs f1, float_1024_8041affc(r2)
		opword 0xC01F003C
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8081004C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x9003009C
		opword 0xC01F0040
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010040
		opword 0x80810044
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A0
		opword 0xC01F0044
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010038
		opword 0x8081003C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A4
		opword 0x801F0038
		opword 0x38600001
		opword 0x60000001
		opword 0x901F0038
		opword 0x2C030000
		opword 0x4082002C
		lis r3, itemdrv_window_desc@ha
		addi r3, r3, itemdrv_window_desc@l
		opword 0x38630050
		bl winMgrEntry
		opword 0x907F0030
		opword 0x807F0030
		bl winMgrOpen
		opword 0x807F0030
		opword 0x7FE4FB78
		bl winMgrSetParam
		opword 0x801F0004
		opword 0x2C000049
		opword 0x40820010
		opword 0x387F000C
		opword 0x38800114
		bl iconChange
		opword 0x801F001C
		opword 0x28000000
		opword 0x408209F4
		opword 0x387F000C
		bl iconNameToPtr
		opword 0xA0030000
		opword 0x60000080
		opword 0xB0030000
		opword 0x480009DC
		opword 0x801F0038
		opword 0x540004A5
		opword 0x40820014
		bl marioCtrlOff
		opword 0x801F0038
		opword 0x64000100
		opword 0x901F0038
		opword 0x38000003
		opword 0xB01F0026
		opword 0xA07F0000
		opword 0x54600421
		opword 0x40820048
		opword 0x546004A5
		opword 0x40820040
		opword 0x38600001
		bl psndBGMChk
		opword 0x2C030000
		opword 0x41820030
		opword 0xA01F0000
		opword 0x38600201
		opword 0x60002000
		opword 0xB01F0000
		bl psndBGMOff
		opword 0xA01F0000
		opword 0x54000739
		opword 0x40820010
		opword 0x386000A0
		opword 0x38800000
		bl psndBGMOn
		opword 0x807F0028
		bl winMgrAction
		opword 0x2C030000
		opword 0x40820958
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546005AF
		opword 0x41820948
		opword 0x807F0028
		bl winMgrCloseAutoDelete
		opword 0x801F0038
		opword 0x540004A5
		opword 0x4082000C
		opword 0x807F002C
		bl winMgrCloseAutoDelete
		opword 0xA07F0000
		opword 0x54600421
		opword 0x4082002C
		opword 0x546004A5
		opword 0x40820024
		opword 0x38600201
		bl psndBGMOff
		opword 0xA01F0000
		opword 0x54000739
		opword 0x40820010
		opword 0x386000A0
		opword 0x38800000
		bl psndBGMOn
		opword 0x801F0038
		opword 0x540004A5
		opword 0x41820010
		opword 0x38000006
		opword 0xB01F0026
		opword 0x480008E0
		opword 0x801F0004
		opword 0x2C000079
		opword 0x41800060
		opword 0x2C0000EC
		opword 0x40800058
		opword 0x2C00007D
		opword 0x41820050
		opword 0x386000EB
		bl swGet
		opword 0x2C030000
		opword 0x40820040
		lwz r3, gp(r13)
		opword 0x80030000
		opword 0x540004E7
		opword 0x40820030
		opword 0x386000EB
		bl swSet
		opword 0x38000004
		opword 0x387C01F0
		opword 0xB01F0026
		bl msgSearch
		opword 0x38800000
		opword 0x38A00000
		bl msgWindow_Entry
		opword 0x907D0018
		opword 0x48000878
		opword 0x807D000C
		bl effSoftDelete
		opword 0x38600004
		bl marioSetCamId
		opword 0x387F000C
		opword 0x38800100
		bl iconFlagOff
		opword 0x801F0004
		opword 0x2C000049
		opword 0x40820010
		opword 0x387F000C
		opword 0x38800115
		bl iconChange
		opword 0x801F001C
		opword 0x28000000
		opword 0x40820018
		opword 0x387F000C
		bl iconNameToPtr
		opword 0xA0030000
		opword 0x5400066E
		opword 0xB0030000
		opword 0x801F0038
		opword 0x540007FF
		opword 0x41820108
		opword 0x38600000
		bl marioStSystemLevel
		opword 0x38600080
		bl psndClearFlag
		opword 0x807F0038
		opword 0x546001CF
		opword 0x41820010
		opword 0x5460020C
		opword 0x901F0038
		bl marioCtrlOn
		bl marioKeyOn
		bl marioChgStayMotion
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		lis r4, work@ha
		addi r26, r4, work@l
		opword 0x540005EA
		opword 0xB0030000
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B5A001C
		opword 0x839A0004
		opword 0x3B600000
		opword 0x4800008C
		opword 0x387C000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x807C0004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA01C0000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x801C0004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x807C001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x387C000C
		bl iconDelete
		opword 0xA01C0000
		opword 0x5400043C
		opword 0xB01C0000
		opword 0x3B7B0001
		opword 0x3B9C0098
		opword 0x801A0000
		opword 0x7C1B0000
		opword 0x4180FF70
		opword 0x48000714
		opword 0x38000005
		opword 0xB01F0026
		opword 0x807F0030
		bl winMgrCloseAutoDelete
		bl marioChgStayMotion
		opword 0x387F000C
		opword 0x38800002
		bl iconFlagOn
		opword 0x809F0004
		opword 0x2C0400F0
		opword 0x41800020
		opword 0x2C040153
		opword 0x40800018
		opword 0x38600002
		opword 0x38A00001
		bl winMgrSelectEntry
		opword 0x907D0010
		opword 0x480006CC
		opword 0x38600001
		opword 0x38A00001
		bl winMgrSelectEntry
		opword 0x907D0010
		opword 0x480006B8
		opword 0x807D0018
		bl windowCheckID
		opword 0x2C030000
		opword 0x408206A8
		opword 0x807D000C
		bl effSoftDelete
		opword 0x38600004
		bl marioSetCamId
		opword 0x387F000C
		opword 0x38800100
		bl iconFlagOff
		opword 0x38600000
		bl marioStSystemLevel
		opword 0x38600080
		bl psndClearFlag
		opword 0x807F0038
		opword 0x546001CF
		opword 0x41820010
		opword 0x5460020C
		opword 0x901F0038
		bl marioCtrlOn
		bl marioKeyOn
		bl marioChgStayMotion
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		lis r4, work@ha
		addi r26, r4, work@l
		opword 0x540005EA
		opword 0xB0030000
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B5A001C
		opword 0x839A0004
		opword 0x3B600000
		opword 0x4800008C
		opword 0x387C000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x807C0004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA01C0000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x801C0004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x807C001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x387C000C
		bl iconDelete
		opword 0xA01C0000
		opword 0x5400043C
		opword 0xB01C0000
		opword 0x3B7B0001
		opword 0x3B9C0098
		opword 0x801A0000
		opword 0x7C1B0000
		opword 0x4180FF70
		opword 0x48000588
		opword 0x807D0010
		bl winMgrSelect
		opword 0x7C7A1B79
		opword 0x41820578
		opword 0x807D0010
		bl winMgrSelectDelete
		opword 0x2C1A0000
		opword 0x40800020
		opword 0x801F0038
		opword 0x5400014B
		opword 0x4182016C
		opword 0xA01F0000
		opword 0x60000100
		opword 0xB01F0000
		opword 0x4800015C
		opword 0x7F43D378
		bl pouchRemoveItem
		opword 0x807F0004
		bl pouchGetItem
		opword 0x2C030000
		opword 0x418200B4
		opword 0xA07F0000
		opword 0x546006B5
		opword 0x41820010
		opword 0x807F0008
		bl swSet
		opword 0x48000014
		opword 0x54600673
		opword 0x4182000C
		opword 0x807F0008
		bl _swSet
		opword 0x807F0020
		opword 0x28030000
		opword 0x41820074
		opword 0x38800000
		opword 0x38A00020
		bl evtEntry
		lfs f1, float_1024_8041affc(r2)
		opword 0xC01F003C
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8081004C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x9003009C
		opword 0xC01F0040
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010040
		opword 0x80810044
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A0
		opword 0xC01F0044
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010038
		opword 0x8081003C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A4
		opword 0x801F0038
		opword 0x60000001
		opword 0x901F0038
		opword 0x80BF0038
		lis r4, itemDataTable@ha
		opword 0x38000000
		opword 0x387F000C
		opword 0x54A5003C
		addi r4, r4, itemDataTable@l
		opword 0x90BF0038
		opword 0x935F0004
		opword 0x901F0020
		opword 0x901F0008
		opword 0xA01F0000
		opword 0x540006F0
		opword 0xB01F0000
		opword 0x801F0004
		opword 0x1C000028
		opword 0x7C840214
		opword 0xA0840020
		bl iconChange
		opword 0x809D0008
		opword 0x387F000C
		opword 0x38040001
		opword 0x901D0008
		bl iconNameToPtr
		opword 0x80BD0008
		opword 0x389C0200
		opword 0x4CC63182
		opword 0x38630018
		bl sprintf
		opword 0x80BD0008
		opword 0x387F000C
		opword 0x389C0200
		opword 0x4CC63182
		bl sprintf
		opword 0xA01F0000
		opword 0x60000100
		opword 0xB01F0000
		opword 0xA01F0000
		lis r3, itemdrv_window_desc@ha
		addi r3, r3, itemdrv_window_desc@l
		lfs f0, float_85_8041b008(r2)
		opword 0x54000524
		lfs f2, float_120_8041b00c(r2)
		opword 0xB01F0000
		opword 0x38630078
		lfs f1, float_0p7_8041aff4(r2)
		opword 0xD01F0050
		lfs f0, float_1_8041afa4(r2)
		opword 0xD05F0058
		opword 0xD03F0080
		opword 0xD01F0084
		bl winMgrEntry
		opword 0x907F0028
		opword 0x807F0028
		bl winMgrOpen
		opword 0x807F0028
		opword 0x7FE4FB78
		bl winMgrSetParam
		bl marioChgGetItemMotion
		opword 0x387F000C
		opword 0x38800002
		bl iconFlagOff
		opword 0x801E0000
		opword 0x5400018D
		opword 0x41820010
		opword 0x801F0038
		opword 0x60008000
		opword 0x901F0038
		opword 0x38000009
		opword 0xB01F0026
		opword 0x4800036C
		lis r3, all_juyoitem_lecture@ha
		opword 0x38800000
		addi r3, r3, all_juyoitem_lecture@l
		opword 0x38A00000
		opword 0x38C00000
		bl evtEntryType
		opword 0x907D0014
		opword 0x38600080
		opword 0x809D0014
		opword 0x93E400BC
		opword 0x801D000C
		opword 0x809D0014
		opword 0x900400C0
		bl psndClearFlag
		opword 0x38000007
		opword 0xB01F0026
		opword 0x48000328
		opword 0x807D0014
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x40820314
		opword 0x38600000
		bl marioStSystemLevel
		opword 0x38600080
		bl psndClearFlag
		opword 0x807F0038
		opword 0x546001CF
		opword 0x41820010
		opword 0x5460020C
		opword 0x901F0038
		bl marioCtrlOn
		bl marioKeyOn
		bl marioChgStayMotion
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		lis r4, work@ha
		addi r26, r4, work@l
		opword 0x540005EA
		opword 0xB0030000
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B5A001C
		opword 0x839A0004
		opword 0x3B600000
		opword 0x4800008C
		opword 0x387C000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x807C0004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA01C0000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x801C0004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x807C001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x387C000C
		bl iconDelete
		opword 0xA01C0000
		opword 0x5400043C
		opword 0xB01C0000
		opword 0x3B7B0001
		opword 0x3B9C0098
		opword 0x801A0000
		opword 0x7C1B0000
		opword 0x4180FF70
		opword 0x48000210
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546005EF
		opword 0x41820200
		opword 0x807F0028
		bl winMgrCloseAutoDelete
		opword 0x809F0038
		opword 0x38000006
		opword 0x38600000
		opword 0x60840008
		opword 0x909F0038
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0xA01F0000
		opword 0x54000734
		opword 0xB01F0000
		opword 0x801F0004
		opword 0x2C000001
		opword 0x41800018
		opword 0x2C000079
		opword 0x40800010
		opword 0x907F007C
		opword 0x907F0078
		opword 0x48000034
		opword 0x2C0000F0
		opword 0x4180001C
		opword 0x2C000153
		opword 0x40800014
		opword 0x38000000
		opword 0x901F007C
		opword 0x901F0078
		opword 0x48000014
		opword 0x38604E20
		opword 0x38000000
		opword 0x907F007C
		opword 0x901F0078
		opword 0x801F0038
		opword 0x38600000
		opword 0x64000001
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000524
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x540007FA
		opword 0xB01F0000
		bl marioStSystemLevel
		opword 0x38600080
		bl psndClearFlag
		opword 0x807F0038
		opword 0x546001CF
		opword 0x41820010
		opword 0x5460020C
		opword 0x901F0038
		bl marioCtrlOn
		bl marioKeyOn
		bl marioChgStayMotion
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x540005EA
		opword 0xB0030000
		opword 0x48000114
		opword 0x801E0000
		opword 0x5400018D
		opword 0x41820010
		opword 0x801F0038
		opword 0x60008000
		opword 0x901F0038
		opword 0x38800000
		opword 0x909F007C
		opword 0x909F0078
		opword 0x801F0038
		opword 0x540004E7
		opword 0x41820050
		opword 0x38000001
		opword 0xB01F0024
		opword 0xB09F0026
		opword 0x801F0038
		opword 0x540007B8
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000776
		opword 0x901F0038
		opword 0x801F0038
		opword 0x540004A0
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000524
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x54000524
		opword 0xB01F0000
		opword 0x4800006C
		lfs f1, float_85_8041b008(r2)
		opword 0x38000006
		lfs f0, float_120_8041b00c(r2)
		opword 0xD03F0050
		lfs f1, float_0p7_8041aff4(r2)
		opword 0xD01F0058
		lfs f0, float_1_8041afa4(r2)
		opword 0xD03F0080
		opword 0xD01F0084
		opword 0x807F0038
		opword 0x60630008
		opword 0x907F0038
		opword 0xB01F0024
		opword 0xB09F0026
		opword 0xA01F0000
		opword 0x54000734
		opword 0xB01F0000
		opword 0x801F0038
		opword 0x54000524
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x540007FA
		opword 0xB01F0000
		opword 0xA01F0000
		opword 0x54000524
		opword 0xB01F0000
		opword 0x38600000
		bl marioStSystemLevel
		opword 0x38600080
		bl psndClearFlag
		opword 0x807F0038
		opword 0x546001CF
		opword 0x41820010
		opword 0x5460020C
		opword 0x901F0038
		bl marioCtrlOn
		bl marioKeyOn
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void itemseq_Bound(ItemEntry* entry) {
	char _af_pad[112];
	asm volatile {
		lis r4, vec3_802cabe0@ha
		opword 0x7C7F1B78
		addi r30, r4, vec3_802cabe0@l
		bl marioGetPtr
		opword 0x7C7B1B78
		opword 0x38600004
		bl camGetPtr
		opword 0xA01F0026
		opword 0x7C7C1B78
		opword 0x2C000001
		opword 0x41820364
		opword 0x40800D2C
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000D20
		opword 0x38000001
		opword 0x38800000
		opword 0xB01F0026
		opword 0x909F0064
		opword 0x909F0060
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F006C
		opword 0x901F0068
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0074
		opword 0x901F0070
		opword 0x909F008C
		opword 0x807F0038
		opword 0x546006F7
		opword 0x40820CD4
		opword 0xA01F0024
		opword 0x2C000006
		opword 0x4182002C
		opword 0x4080001C
		opword 0x2C000004
		opword 0x41820270
		opword 0x40800024
		opword 0x2C000003
		opword 0x4080026C
		opword 0x48000CAC
		opword 0x2C00000A
		opword 0x41820298
		opword 0x48000CA0
		opword 0x60600004
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x40820020
		lfs f1, float_1_8041afa4(r2)
		opword 0x38000000
		lfs f0, float_500_8041afcc(r2)
		opword 0xD03F0080
		opword 0xD03F0084
		opword 0x901F0088
		opword 0xD01F0058
		opword 0x801F0038
		opword 0x54000673
		opword 0x408201BC
		opword 0x801F0004
		opword 0x2C00007A
		opword 0x418200F8
		opword 0x40800010
		opword 0x2C000079
		opword 0x40800010
		opword 0x480000E8
		opword 0x2C00007D
		opword 0x408000E0
		opword 0x3860001E
		bl irand
		opword 0x3863002D
		opword 0x3C004330
		opword 0x6C648000
		stw r0, _af_pad+104(r1)
		opword 0xC83E0068
		opword 0x38600064
		opword 0x90810074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xD01F0050
		bl irand
		opword 0x2C030032
		opword 0x40800054
		opword 0x3860003C
		bl irand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610074
		opword 0xC87E0068
		opword 0x90010070
		lfs f2, float_90_8041afd0(r2)
		opword 0xC8010070
		opword 0xC03C0114
		opword 0xEC601828
		lfs f0, float_30_8041afd4(r2)
		opword 0xEC22082A
		opword 0xEC21182A
		opword 0xEC010028
		opword 0xFC00001E
		opword 0xD8010078
		opword 0x8001007C
		opword 0x901F0054
		opword 0x48000BB4
		opword 0x3860003C
		bl irand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061007C
		opword 0xC87E0068
		opword 0x90010078
		opword 0xC05C0114
		opword 0xC8010078
		lfs f1, float_90_8041afd0(r2)
		opword 0xEC601828
		lfs f0, float_30_8041afd4(r2)
		opword 0xEC220828
		opword 0xEC21182A
		opword 0xEC010028
		opword 0xFC00001E
		opword 0xD8010070
		opword 0x80010074
		opword 0x901F0054
		opword 0x48000B64
		lfs f0, float_100_8041afc0(r2)
		opword 0x38600064
		opword 0xD01F0050
		bl irand
		opword 0x2C030032
		opword 0x40800054
		opword 0x3860001E
		bl irand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061007C
		opword 0xC87E0068
		opword 0x90010078
		lfs f2, float_90_8041afd0(r2)
		opword 0xC8010078
		opword 0xC03C0114
		opword 0xEC601828
		lfs f0, float_15_8041afb4(r2)
		opword 0xEC22082A
		opword 0xEC21182A
		opword 0xEC010028
		opword 0xFC00001E
		opword 0xD8010070
		opword 0x80010074
		opword 0x901F0054
		opword 0x48000AFC
		opword 0x3860001E
		bl irand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061007C
		opword 0xC87E0068
		opword 0x90010078
		opword 0xC05C0114
		opword 0xC8010078
		lfs f1, float_90_8041afd0(r2)
		opword 0xEC601828
		lfs f0, float_15_8041afb4(r2)
		opword 0xEC220828
		opword 0xEC21182A
		opword 0xEC010028
		opword 0xFC00001E
		opword 0xD8010070
		opword 0x80010074
		opword 0x901F0054
		opword 0x48000AAC
		lwz r0, _move_dir_1090(r13)
		opword 0x901F0054
		lwz r3, _move_dir_1090(r13)
		opword 0x38630084
		opword 0x2C030168
		stw r3, _move_dir_1090(r13)
		opword 0x4180000C
		opword 0x3803FE98
		stw r0, _move_dir_1090(r13)
		opword 0x3860001E
		bl irand
		opword 0x38630041
		opword 0x3C004330
		opword 0x6C638000
		opword 0x90010078
		opword 0xC85E0068
		opword 0x9061007C
		lfs f0, float_0p67_8041afd8(r2)
		opword 0xC8210078
		opword 0xEC211028
		opword 0xEC000072
		opword 0xD01F0050
		opword 0x48000A50
		opword 0x60600008
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x40820018
		lfs f0, float_1_8041afa4(r2)
		opword 0x38000000
		opword 0xD01F0080
		opword 0xD01F0084
		opword 0x901F0088
		lfs f0, float_0_8041af9c(r2)
		opword 0x38000000
		opword 0xD01F0050
		opword 0x901F0054
		opword 0xD01F0058
		opword 0x48000A10
		lfs f2, float_1_8041afa4(r2)
		lfs f1, float_500_8041afcc(r2)
		opword 0xD05F0080
		lfs f0, float_0_8041af9c(r2)
		opword 0xD05F0084
		opword 0x909F0088
		opword 0xD03F0058
		opword 0xD01F0050
		opword 0x909F0054
		opword 0x801F0038
		opword 0x60000020
		opword 0x901F0038
		opword 0x801F0038
		opword 0x60000004
		opword 0x901F0038
		opword 0x480009D0
		lwz r6, gp(r13)
		opword 0x3C60431C
		opword 0x3C808000
		opword 0x38A00000
		opword 0x80060038
		opword 0x3863DE83
		opword 0x80C6003C
		opword 0x90DF0074
		opword 0x901F0070
		opword 0x800400F8
		opword 0x80FF0074
		opword 0x5400F0BE
		opword 0x809F006C
		opword 0x7C030016
		opword 0x80DF0070
		opword 0x7FA43810
		opword 0x807F0068
		opword 0x7F833110
		opword 0x57A41838
		opword 0x541A8BFE
		opword 0x57831838
		opword 0x53A31F7E
		opword 0x7F46D378
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1E06_8041afdc(r2)
		opword 0x7F46D378
		opword 0x833F0060
		opword 0x38A00000
		opword 0xEFC10024
		lwz r24, 0x64(r31)
		opword 0x57231838
		opword 0x57041838
		opword 0x53031F7E
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1E06_8041afdc(r2)
		opword 0x7CF8E814
		opword 0x7C19E114
		opword 0x7F46D378
		opword 0xEFA10024
		opword 0x54031838
		opword 0x54E41838
		opword 0x38A00000
		opword 0x50E31F7E
		bl __div2i
		bl __cvt_sll_flt
		opword 0x807F0054
		opword 0x3C004330
		lfs f0, float_1E06_8041afdc(r2)
		opword 0x6C638000
		opword 0x90010078
		opword 0xC85E0068
		opword 0xEF810024
		opword 0x9061007C
		lfs f3, float_6p2832_8041afe0(r2)
		opword 0xC8210078
		lfs f0, float_360_8041afe4(r2)
		opword 0xEC211028
		opword 0xEC230072
		opword 0xEC210024
		bl sin
		opword 0x807F0054
		opword 0x3C004330
		opword 0x90010070
		opword 0xFC200818
		opword 0x6C608000
		opword 0xC01F0050
		opword 0x90010074
		opword 0xEC600072
		opword 0xC83E0068
		opword 0xC8010070
		lfs f2, float_6p2832_8041afe0(r2)
		opword 0xEC200828
		lfs f0, float_360_8041afe4(r2)
		fmuls f27, f30, f3
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		opword 0xFC000818
		opword 0x807F0038
		opword 0xC03F0050
		opword 0x54600421
		opword 0xFC000050
		opword 0xEC010032
		opword 0xEC5E0032
		opword 0x41820008
		lfs f2, float_0_8041af9c(r2)
		opword 0xEFFC0732
		lfs f3, float_neg980_8041afe8(r2)
		opword 0xC03F0084
		opword 0x5460077B
		opword 0xEC230072
		opword 0xC07F0058
		opword 0xEC1DFF7C
		opword 0xEC010032
		opword 0xEFA307BA
		opword 0x41820028
		opword 0x801F008C
		opword 0x2C000000
		opword 0x40820010
		lfs f0, float_0_8041af9c(r2)
		opword 0xFC1D0040
		opword 0x40800010
		opword 0x801F0038
		opword 0x540007B8
		opword 0x901F0038
		opword 0x807F0038
		opword 0x54600739
		opword 0x41820018
		opword 0x801F008C
		opword 0x2C000000
		opword 0x4182000C
		opword 0x54600776
		opword 0x901F0038
		opword 0x801F0038
		opword 0x540006B5
		opword 0x418200F4
		lfs f0, float_0_8041af9c(r2)
		opword 0xFC1D0040
		opword 0x408000E8
		lfs f4, float_16_8041afc8(r2)
		opword 0x38600001
		opword 0xC03F003C
		opword 0x38800003
		opword 0xFCA02090
		opword 0xC05F0040
		opword 0xC07F0044
		opword 0x38A0001E
		bl effStardustEntry
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r26, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B5A001C
		opword 0x839A0004
		opword 0x3B600000
		opword 0x4800008C
		opword 0x387C000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x807C0004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA01C0000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x801C0004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x807C001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x387C000C
		bl iconDelete
		opword 0xA01C0000
		opword 0x5400043C
		opword 0xB01C0000
		opword 0x3B7B0001
		opword 0x3B9C0098
		opword 0x801A0000
		opword 0x7C1B0000
		opword 0x4180FF70
		opword 0x48000714
		opword 0x801F0054
		opword 0xFC20D890
		opword 0x7FE3FB78
		opword 0x38810048
		opword 0x90010040
		opword 0x38A10044
		opword 0x38C10040
		bl itemHitCheckSide
		opword 0xC0010048
		opword 0x28030000
		opword 0xD01F003C
		opword 0xC0010044
		opword 0xD01F0044
		opword 0x80010040
		opword 0x901F0054
		opword 0x41820014
		opword 0xC03F0050
		lfs f0, float_0p25_8041afec(r2)
		opword 0xEC010032
		opword 0xD01F0050
		opword 0x801F0038
		opword 0x540006B5
		opword 0x4082014C
		opword 0xA01F0000
		opword 0x54000529
		opword 0x40820140
		lfs f4, float_0_8041af9c(r2)
		opword 0xFC1D2040
		opword 0x4C401382
		opword 0x4082000C
		opword 0x38600000
		opword 0x480000EC
		opword 0xFC40EA10
		opword 0xC81E0048
		lfs f7, float_20_8041afa0(r2)
		opword 0xFCC02090
		opword 0xC03F003C
		opword 0x38810024
		opword 0xFC00102A
		opword 0xC05F0040
		opword 0xC07F0044
		opword 0x38A10028
		opword 0xEC47102A
		lfs f5, float_1_8041afa4(r2)
		opword 0xFC000018
		opword 0x38C1002C
		opword 0x38E10030
		opword 0x39010034
		opword 0x39210038
		opword 0x3941003C
		opword 0xD0010030
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820020
		opword 0xC0410028
		lfs f1, float_20_8041afa0(r2)
		lfs f0, float_4_8041afa8(r2)
		opword 0xEC220828
		opword 0xEC010028
		opword 0xD01F0040
		opword 0x48000074
		opword 0xFC60EA10
		opword 0xC81E0048
		lfs f4, float_0_8041af9c(r2)
		opword 0x38810024
		opword 0xC03F003C
		opword 0x38A10028
		opword 0xFC00182A
		opword 0xC05F0040
		opword 0xC07F0044
		opword 0xFCC02090
		lfs f5, float_1_8041afa4(r2)
		opword 0x38C1002C
		opword 0xFC000018
		opword 0x38E10030
		opword 0x39010034
		opword 0x39210038
		opword 0x3941003C
		opword 0x38600000
		opword 0xD0010030
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820018
		opword 0xC0210028
		lfs f0, float_20_8041afa0(r2)
		opword 0xEC010028
		opword 0xD01F0040
		opword 0x48000008
		opword 0x38600000
		opword 0x28030000
		opword 0x41820038
		opword 0xC03F0058
		opword 0x38000000
		lfs f0, float_0p25_8041afec(r2)
		opword 0xFC200850
		lfs f29, float_0_8041af9c(r2)
		opword 0xEC010032
		opword 0xD01F0058
		opword 0x901F0064
		opword 0x901F0060
		opword 0x801F0070
		opword 0x807F0074
		opword 0x907F006C
		opword 0x901F0068
		opword 0x801F0038
		opword 0x540002D7
		opword 0x418200C4
		opword 0xC03F0040
		lfs f0, float_neg1000_8041aff0(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408200B0
		opword 0x38000007
		opword 0x38600000
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0x801F0038
		opword 0x540007B8
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000776
		opword 0x901F0038
		opword 0x801F0038
		opword 0x540004A0
		opword 0x901F0038
		opword 0x801F0004
		opword 0x2C000001
		opword 0x41800018
		opword 0x2C000079
		opword 0x40800010
		opword 0x907F007C
		opword 0x907F0078
		opword 0x48000034
		opword 0x2C0000F0
		opword 0x4180001C
		opword 0x2C000153
		opword 0x40800014
		opword 0x38000000
		opword 0x901F007C
		opword 0x901F0078
		opword 0x48000014
		opword 0x38604E20
		opword 0x38000000
		opword 0x907F007C
		opword 0x901F0078
		opword 0x801F0038
		opword 0x64000001
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000524
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x60000100
		opword 0xB01F0000
		opword 0x48000498
		lfs f4, float_0_8041af9c(r2)
		opword 0xFC1D2040
		opword 0x4C411382
		opword 0x40820018
		opword 0xC01F0040
		opword 0x3B400000
		opword 0xEC00E82A
		opword 0xD01F0040
		opword 0x480000A0
		opword 0x801F0038
		opword 0x540002D7
		opword 0x41820018
		opword 0xC01F0040
		opword 0x3B400000
		opword 0xEC00E82A
		opword 0xD01F0040
		opword 0x48000080
		opword 0xFC40EA10
		opword 0xC81E0048
		lfs f7, float_20_8041afa0(r2)
		opword 0xFCC02090
		opword 0xC03F003C
		opword 0x38810008
		opword 0xFC00102A
		opword 0xC05F0040
		opword 0xC07F0044
		opword 0x38A1000C
		opword 0xEC47102A
		lfs f5, float_neg1_8041afac(r2)
		opword 0xFC000018
		opword 0x38C10010
		opword 0x38E10014
		opword 0x39010018
		opword 0x3921001C
		opword 0x39410020
		opword 0xD0010014
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xC001000C
		opword 0x7C7A1B78
		opword 0xD01F0040
		opword 0x48000014
		opword 0xC01F0040
		opword 0x3B400000
		opword 0xEC00E82A
		opword 0xD01F0040
		opword 0x281A0000
		opword 0x418203A8
		opword 0x7F43D378
		bl hitGetAttr
		opword 0x5460056D
		opword 0x41820074
		opword 0x801F0038
		opword 0x38810058
		opword 0x38600194
		opword 0x64000010
		opword 0x901F0038
		opword 0x80DE0024
		opword 0x80BE0028
		opword 0x801E002C
		opword 0x90C10058
		opword 0x90A1005C
		opword 0x90010060
		opword 0xC01F003C
		opword 0xD0010058
		opword 0xC01F0040
		opword 0xD001005C
		opword 0xC01F0044
		opword 0xD0010060
		bl psndSFXOn_3D
		opword 0xC03F003C
		opword 0x38600000
		opword 0xC05F0040
		opword 0xC07F0044
		lfs f4, float_0p7_8041aff4(r2)
		bl effSplashEntry
		opword 0xA01F0000
		opword 0x60000002
		opword 0xB01F0000
		opword 0x48000328
		opword 0x809F008C
		opword 0x7F43D378
		opword 0x38040001
		opword 0x901F008C
		bl hitGetAttr
		opword 0x54600001
		opword 0x40820054
		opword 0x807F0088
		opword 0x2C030000
		opword 0x41820048
		opword 0x801F008C
		opword 0x7C001800
		opword 0x4180003C
		opword 0x38600001
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x801F0038
		opword 0x540007B8
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000776
		opword 0x901F0038
		opword 0x801F0038
		opword 0x540004A0
		opword 0x901F0038
		opword 0x480002E4
		opword 0x809E0030
		opword 0x807E0034
		opword 0x801E0038
		opword 0x9081004C
		opword 0xC01F003C
		opword 0x90610050
		opword 0xC03F0040
		opword 0xD001004C
		opword 0xC01F0044
		opword 0x90010054
		opword 0x8081004C
		opword 0xD0210050
		opword 0xD0010054
		opword 0x80610050
		opword 0x80010054
		opword 0x90810064
		opword 0x90610068
		opword 0x9001006C
		opword 0x801F0004
		opword 0x2C00007B
		opword 0x41820050
		opword 0x4080001C
		opword 0x2C000079
		opword 0x41820024
		opword 0x40800030
		opword 0x2C000072
		opword 0x40800068
		opword 0x48000074
		opword 0x2C00007D
		opword 0x4182004C
		opword 0x40800068
		opword 0x48000034
		opword 0x387E00BC
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000080
		opword 0x387E00D0
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000070
		opword 0x387E00EC
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000060
		opword 0x387E0100
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000050
		opword 0x387E0114
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000040
		opword 0x387E012C
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000030
		opword 0x2C0000F0
		opword 0x4180001C
		opword 0x2C000153
		opword 0x40800014
		opword 0x387E0144
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0x48000010
		opword 0x387E0158
		opword 0x38810064
		bl psndSFXOn_3D
		opword 0xA01F0000
		opword 0x3B000000
		opword 0x54000631
		opword 0x4182001C
		lfs f1, float_0_8041af9c(r2)
		opword 0xC01F0058
		opword 0xFC010000
		opword 0x4182000C
		opword 0x38000001
		opword 0x4800006C
		opword 0x7F43D378
		bl hitGetAttr
		opword 0x54600001
		opword 0x41820058
		lfs f1, float_0_8041af9c(r2)
		opword 0xC01F0058
		opword 0xFC010000
		opword 0x41820048
		opword 0x7F43D378
		bl mobjHitObjPtrToPtr
		opword 0x881B003C
		opword 0x2C000002
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000030
		opword 0x28030000
		opword 0x41820024
		opword 0x38630015
		opword 0x389E016C
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x38000001
		opword 0x3B000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x40820044
		opword 0xEC1CF02A
		lfs f2, float_neg980_8041afe8(r2)
		opword 0xC03F0084
		opword 0xC07F0058
		opword 0xEC000032
		opword 0xC09F0080
		opword 0xEC220072
		lfs f2, float_0p7_8041aff4(r2)
		opword 0xEC00F828
		opword 0xEC010032
		opword 0xEC0307BA
		opword 0xFC000050
		opword 0xEC00F024
		opword 0xEC040032
		opword 0xEC020032
		opword 0xD01F0058
		lfs f1, float_neg980_8041afe8(r2)
		opword 0x2C180000
		opword 0xC01F0084
		opword 0xC05F0058
		opword 0xEC210032
		lfs f3, float_0p5_8041afb8(r2)
		opword 0xEC020824
		opword 0xEC030032
		opword 0xFC000210
		opword 0xFC600018
		opword 0xEC0100F2
		opword 0xEC030032
		opword 0xEC2200FA
		opword 0x40820048
		lfs f0, float_8_8041aff8(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820038
		opword 0x38600001
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x801F0038
		opword 0x540007B8
		opword 0x901F0038
		opword 0x801F0038
		opword 0x54000776
		opword 0x901F0038
		opword 0x801F0038
		opword 0x540004A0
		opword 0x901F0038
		opword 0xA01F0000
		opword 0x540005AD
		opword 0x4182002C
		opword 0x801F008C
		opword 0x2C000001
		opword 0x41810020
		opword 0x801F0090
		opword 0x901F0054
		opword 0xC01F0094
		opword 0xD01F0050
		opword 0xA01F0000
		opword 0x540005EA
		opword 0xB01F0000
		opword 0x38000000
		opword 0x901F0064
		opword 0x901F0060
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F006C
		opword 0x901F0068
		opword 0x4800002C
		opword 0x801F0064
		opword 0x807F0060
		opword 0x7C00E814
		opword 0x901F0064
		opword 0x7C03E114
		opword 0x901F0060
		opword 0x801F0070
		opword 0x807F0074
		opword 0x907F006C
		opword 0x901F0068
		opword 0x801F0038
		opword 0x54000734
		opword 0x901F0038
	}
}
#pragma pop

void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z) {
	entry->position.x = x;
	entry->position.y = y;
	entry->position.z = z;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle) {
	char _af_pad[56];
	asm volatile {
		opword 0x7C7B1B78
		lis r3, vec3_802cabe0@ha
		opword 0xC07B003C
		opword 0x7C9C2378
		fmr f29, f1
		lfs f0, float_0_8041af9c(r2)
		opword 0xD0640000
		opword 0x7CBD2B78
		opword 0xFFC01090
		opword 0x7CDE3378
		opword 0xC03B0044
		opword 0xFC00E800
		addi r31, r3, vec3_802cabe0@l
		opword 0xD0250000
		opword 0x40820014
		opword 0xFC00F000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000428
		lfs f1, float_0_8041af9c(r2)
		opword 0xFC60E890
		opword 0xFC80F090
		opword 0xFC400890
		bl angleABf
		la r3, _af_pad+12
		opword 0x38810010
		bl sincosf
		opword 0xEC3E07B2
		lfs f0, float_0_8041af9c(r2)
		opword 0xEFFD0F7A
		opword 0xFC1F0040
		opword 0x4081004C
		opword 0xFC20F834
		opword 0xC87F0050
		opword 0xC85F0058
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC010032
		opword 0xFC5F0032
		opword 0xFC401018
		opword 0x48000090
		opword 0xC81F0060
		opword 0xFC1F0040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f2, __float_nan@l(r3)
		opword 0x48000078
		opword 0xD3E1000C
		opword 0x3C007F80
		opword 0x8081000C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x40820010
		lis r3, __float_nan@ha
		lfs f2, __float_nan@l(r3)
		opword 0x48000008
		opword 0xFC40F890
		lfs f1, float_10_8041afb0(r2)
		opword 0x38810030
		lfs f0, float_15_8041afb4(r2)
		opword 0x38A1002C
		opword 0xEC21102A
		opword 0xC0810014
		lfs f5, float_0_8041af9c(r2)
		opword 0x38C10028
		opword 0xC0C10010
		opword 0x38E10024
		opword 0xD0210024
		opword 0x39010020
		opword 0x3921001C
		opword 0x39410018
		opword 0xC05B0040
		opword 0x38600000
		opword 0xC03B003C
		opword 0xEC42002A
		opword 0xC07B0044
		bl hitCheckFilter
		mr. r26, r3
		opword 0x418200C0
		opword 0xC0C10018
		opword 0x3C004330
		opword 0xC0610020
		opword 0xEC1E01B2
		lfs f4, float_0p5_8041afb8(r2)
		opword 0xC0BC0000
		opword 0x90010038
		opword 0xEC1D00FA
		opword 0xC83F0068
		lfs f2, float_180_8041afbc(r2)
		opword 0xEC60E8FC
		opword 0xEC00F1BC
		opword 0xEC6400F2
		opword 0xEC040032
		opword 0xEC65182A
		opword 0xD07C0000
		opword 0xC07D0000
		opword 0xEC03002A
		opword 0xD01D0000
		opword 0x801E0000
		opword 0x6C008000
		opword 0x9001003C
		opword 0xC8010038
		opword 0xEC000828
		opword 0xEC22002A
		bl reviseAngle
		opword 0xFFC00890
		lfs f1, float_0_8041af9c(r2)
		lfs f4, float_100_8041afc0(r2)
		opword 0xC0610020
		opword 0xFC400890
		opword 0xC0010018
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		bl reviseAngle
		opword 0xFFA00890
		opword 0xEC3DF028
		bl reviseAngle
		opword 0xEC3D082A
		bl reviseAngle
		opword 0xFC00081E
		opword 0x7F43D378
		opword 0xD8010040
		opword 0x80010044
		opword 0x901E0000
		opword 0x4800020C
		lfs f0, float_0_8041af9c(r2)
		opword 0xFC1F0040
		opword 0x4081004C
		opword 0xFC20F834
		opword 0xC87F0050
		opword 0xC85F0058
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC010032
		opword 0xFFFF0032
		opword 0xFFE0F818
		opword 0x48000088
		opword 0xC81F0060
		opword 0xFC1F0040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f31, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD3E10008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f31, __float_nan@l(r3)
		lfs f1, float_10_8041afb0(r2)
		opword 0x38810030
		lfs f0, float_15_8041afb4(r2)
		opword 0x38A1002C
		opword 0xEC21F82A
		opword 0xC0810014
		lfs f5, float_0_8041af9c(r2)
		opword 0x38C10028
		opword 0xC0C10010
		opword 0x38E10024
		opword 0xD0210024
		opword 0x39010020
		opword 0x3921001C
		opword 0x39410018
		opword 0xC05B0040
		opword 0x38600000
		opword 0xC03B003C
		opword 0xEC42002A
		opword 0xC07B0044
		bl hitCheckFilter
		opword 0x7C7B1B79
		opword 0x418200C0
		opword 0xC0C10018
		opword 0x3C004330
		opword 0xC0610020
		opword 0xEC1E01B2
		lfs f4, float_0p5_8041afb8(r2)
		opword 0xC0BC0000
		opword 0x90010040
		opword 0xEC1D00FA
		opword 0xC83F0068
		lfs f2, float_180_8041afbc(r2)
		opword 0xEC60E8FC
		opword 0xEC00F1BC
		opword 0xEC6400F2
		opword 0xEC040032
		opword 0xEC65182A
		opword 0xD07C0000
		opword 0xC07D0000
		opword 0xEC03002A
		opword 0xD01D0000
		opword 0x801E0000
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC000828
		opword 0xEC22002A
		bl reviseAngle
		opword 0xFFC00890
		lfs f1, float_0_8041af9c(r2)
		lfs f4, float_100_8041afc0(r2)
		opword 0xC0610020
		opword 0xFC400890
		opword 0xC0010018
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		bl reviseAngle
		opword 0xFFA00890
		opword 0xEC3DF028
		bl reviseAngle
		opword 0xEC3D082A
		bl reviseAngle
		opword 0xFC00081E
		opword 0x7F63DB78
		opword 0xD8010038
		opword 0x8001003C
		opword 0x901E0000
		opword 0x48000020
		opword 0xC01C0000
		opword 0x38600000
		opword 0xEC00E82A
		opword 0xD01C0000
		opword 0xC01D0000
		opword 0xEC00F02A
		opword 0xD01D0000
	}
}
#pragma pop

#define itemModeChange itemModeChange__af_inl
void itemForceGet(ItemEntry* entry) {
	entry->timer = 0;
	itemModeChange(entry, 2);
	entry->flags |= 0x1000;
	entry->flags2 &= ~0x10000;
}

#undef itemModeChange

#define itemModeChange itemModeChange__af_inl
void itemNokoForceGet(ItemEntry* entry) {
	if (itemGetNokoCheck(entry)) {
		entry->timer = 0;
		itemModeChange(entry, 2);
		entry->flags |= 0x5000;
		entry->flags2 &= ~0x10000;
	}
	else {
		entry->timer = 0;
		itemModeChange(entry, 1);
		entry->flags2 &= ~4;
		entry->flags2 &= ~8;
		entry->flags2 &= ~0x4000;
		entry->flags2 &= ~0x1000;
	}
}

#undef itemModeChange

void itemFlagOn(ItemEntry* entry, u16 flags) {
	entry->flags |= flags;
}

void itemFlagOff(ItemEntry* entry, u16 flags) {
	entry->flags &= ~flags;
}

u16 itemFlag(ItemEntry* entry, u16 flags) {
	return entry->flags & flags;
}

void itemStatusOn(ItemEntry* entry, u32 flags) {
	entry->flags2 |= flags;
}

u32 itemStatus(ItemEntry* entry, u32 flags) {
	return entry->flags2 & flags;
}

#define itemModeChange itemModeChange__af_inl
#pragma defer_codegen off
void itemPickUp(ItemEntry* entry) {
	entry->flags2 |= 0x1000;
	itemModeChange(entry, 8);
	entry->timer = 0;
	entry->flags2 &= ~0x100;
}

#pragma defer_codegen reset

#undef itemModeChange

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	fmr f28, f1
	fmr f29, f2
	fmr f30, f3
	fmr f31, f4
	bl marioGetPtr
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r31, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq L_af_1
	addi r31, r31, 0x1c
L_af_1:
	lis r3, vec3_802cabec@ha
	lwz r30, 0x4(r31)
	addi r5, r3, vec3_802cabec@l
	li r29, 0x0
	lwz r4, 0x0(r5)
	li r28, 0x0
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	stfs f28, 0x14(r1)
	stfs f29, 0x18(r1)
	lwz r4, 0x14(r1)
	stfs f30, 0x1c(r1)
	lwz r3, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r4, 0x20(r1)
	stw r3, 0x24(r1)
	stw r0, 0x28(r1)
	b L_af_2
L_af_3:
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq L_af_4
	lwz r3, 0x38(r30)
	rlwinm. r0, r3, 0, 19, 19
	bne L_af_4
	rlwinm. r0, r3, 0, 11, 11
	bne L_af_4
	lhz r0, 0x24(r30)
	cmplwi r0, 0x2
	beq L_af_4
	rlwinm. r0, r3, 0, 6, 6
	bne L_af_4
	lis r3, vec3_802cabf8@ha
	lfs f2, 0x3c(r30)
	addi r5, r3, vec3_802cabf8@l
	lfs f1, 0x40(r30)
	lwz r7, 0x0(r5)
	addi r3, r1, 0x38
	lwz r6, 0x4(r5)
	addi r4, r1, 0x20
	lwz r0, 0x8(r5)
	addi r5, r1, 0x2c
	stw r7, 0x8(r1)
	lfs f0, 0x44(r30)
	stw r6, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f2, 0x8(r1)
	stfs f1, 0xc(r1)
	lwz r7, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r6, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r7, 0x38(r1)
	stw r6, 0x3c(r1)
	stw r0, 0x40(r1)
	bl PSVECSubtract
	addi r3, r1, 0x2c
	bl PSVECMag
	fcmpo cr0, f1, f31
	bge L_af_4
	mr r29, r30
	fmr f31, f1
L_af_4:
	addi r28, r28, 0x1
	addi r30, r30, 0x98
L_af_2:
	lwz r0, 0x0(r31)
	cmpw r28, r0
	blt L_af_3
	mr r3, r29
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r0, 0xa4(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}
#endif

void itemInit(void) { // 1:1
    ItemWork* wp;

    wp = &work[0];
    wp->count = 32;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->currId = 0;

    wp = &work[1];
    wp->count = 32;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->currId = 0;
}

void itemReInit(void) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;

    if (!gp->inBattle) {
        for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
            if (entry->flags & 1) { //flush all current badges
                itemCheckBadge(entry);
            }
        }
    }

    //clear all existing entries
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        iconDelete(entry->name);
        entry->flags &= ~1;
        memset(entry->name, 0, sizeof(entry->name));
    }
}

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void itemCoinDrop(Vec* position) {
	ItemEntry* entry;

	if (pouchGetCoin() > 0) {
		pouchAddCoin(-1);
		entry = itemEntry(NULL, 0x79, 8, -1, 0, position->x, position->y, position->z);
		if (entry) {
			entry->flags2 |= 0x40;
		}
	}
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

BOOL itemGetCheck(ItemEntry* entry) {
	MarioWork* mario = marioGetPtr();

	if (!entry) return FALSE;
	if (entry->flags2 & 0x100000) return FALSE;
	if (mario->characterId == 2) {
		if (!(*(s32*)mario->field_0x14 & 1)) {
			if (marioStGetSystemLevel() != 0U) return FALSE;
			if (mario->flags & 0xA) return FALSE;
		}
	}
	else {
		if (marioStGetSystemLevel() != 0U) return FALSE;
		if (mario->flags & 0xA) return FALSE;
	}
	if (*(s32*)&gp->mapEventId) return FALSE;
	if (seqGetSeq() != 2) return FALSE;
	if (mario->currMotionId == 0x19) return FALSE;
	if (mario->currMotionId == 0x18) return FALSE;
	if (vivianGetStatus()) return FALSE;
	if (mario->currMotionId == 0x1F || mario->currMotionId == 0x20) return FALSE;
	if (nokonoko_holdItem()) return FALSE;
	{
		ItemWork* wp = itemGetWork();
		ItemEntry* item;
		int i;
		for (item = wp->entries, i = 0; i < wp->count; i++, item++) {
			if (item->flags & 1 && item->mode == 2) {
				return FALSE;
			}
		}
	}
	if (N_fbatPreventMarioEventChk()) return FALSE;
	switch (entry->mode) {
		case 5:
		case 6:
			if (!entry->subState) break;
			if (entry->flags2 & 4) break;
			if (entry->flags2 & 8) break;
			return TRUE;
		case 3:
		case 4:
			if (entry->flags2 & 8) break;
			return TRUE;
		case 1:
		case 7:
			return TRUE;
	}
	return FALSE;
}

#pragma dont_inline on
#ifndef NONMATCHING
#pragma dont_inline on
#endif
BOOL itemGetNokoCheck(ItemEntry* entry) {
	MarioWork* mario = marioGetPtr();

	if (!entry) return FALSE;
	if (entry->flags2 & 0x100000) return FALSE;
	if (marioStGetSystemLevel() != 0U) return FALSE;
	if (mario->flags & 0xA) return FALSE;
	if (entry->flags2 & 0x2000000) return FALSE;
	if (*(s32*)&gp->mapEventId) return FALSE;
	if (seqGetSeq() != 2) return FALSE;
	if (mario->currMotionId == 0x19) return FALSE;
	if (vivianGetStatus()) return FALSE;
	if (mario->currMotionId == 0x1F || mario->currMotionId == 0x20) return FALSE;
	if ((u16)(mario->currMotionId - 5) <= 3 || mario->currMotionId == 0xF || mario->currMotionId == 0xE) return FALSE;
	{
		ItemWork* wp = itemGetWork();
		ItemEntry* item;
		int i;
		for (item = wp->entries, i = 0; i < wp->count; i++, item++) {
			if (item->flags & 1 && item->mode == 2) {
				return FALSE;
			}
		}
	}
	return !N_fbatPreventMarioEventChk();
}
#pragma dont_inline reset

#ifndef NONMATCHING
#pragma dont_inline reset

#endif
BOOL N_itemPickUpFromFieldCheck(void) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (entry->flags & 1 && entry->mode == 2) {
			return TRUE;
		}
	}
	return FALSE;
}

#ifdef NONMATCHING
typedef struct ItemEffPos {
	u8 pad[8];
	Vec position;
} ItemEffPos;


#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void itemMain(void) {
#ifdef NONMATCHING
	ItemWork* wp = itemGetWork();
	MarioWork* mario;
	ItemEntry* entry;
	PartyEntry* party;
	HitEntry* hit;
	BOOL active;
	u16 mode;
	int i;
	f32 newY;
	f32 y;
	s32 dx, dy;

	mario = marioGetPtr();
	entry = itemHitCheck(mario->position.x, mario->position.y, mario->position.z, mario->wPlayerCollisionBox.x * 0.5f + 12.0f);
	if (itemGetCheck(entry)) {
		itemModeChange(entry, 2);
	}

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) continue;
		mode = entry->mode;
		active = TRUE;
		switch (mode) {
			case 2:
			case 7:
			case 8:
			case 10:
				break;
			default:
				if (gp->systemLevelFlags & 0xF) {
					active = FALSE;
				}
				break;
		}
		if (!active) {
			entry->baseTime = gp->renderTime;
			continue;
		}
		if (mode != 2) {
			if (entry->timer == 0) {
				entry->flags2 &= ~0x100;
			}
			else if (entry->flags2 & 0x4000) {
				entry->flags2 &= ~0x100;
			}
			else {
				entry->timer -= (f32)OSTicksToMicroseconds(gp->renderTime - entry->baseTime) / 1000.0f;
				if (entry->timer <= 0) {
					itemModeChange(entry, 9);
				}
				else if (entry->timer <= 3000) {
					if ((entry->timer >> 4) & 1) {
						entry->flags2 ^= 0x100;
					}
				}
			}
		}
		else {
			entry->flags2 &= ~0x100;
		}

		switch (entry->mode) {
			case 5:
			case 6:
			case 10:
				itemseq_Bound(entry);
				break;
			case 3:
			case 4:
				itemseq_Bound(entry);
				break;
			case 1:
				y = entry->position.y; { f32 dirY = -1.0f;
				if (entry->flags2 & 0x100000) {
					hit = NULL;
					newY = y + dirY;
				}
				else {
					f32 hitNZ, hitNY, hitNX, hitDist, hitZ, hitY, hitX;
					f32 px = entry->position.x, py = entry->position.y + 20.0f, pz = entry->position.z;
					{ f64 d = __fabs(-1.0); hitDist = 20.0 + d; }
					hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, px, py, pz, 0.0f, -1.0f, 0.0f);
					if (hit) {
						newY = hitY;
					}
					else {
						hit = NULL;
						newY = y + dirY;
					}
				} }
				if (!hit) {
					itemModeChange(entry, 3);
				}
				else {
					entry->position.y = newY;
				}
				break;
			case 2:
				itemseq_GetItem(entry);
				break;
			case 8:
				party = partyGetPtr(marioGetPartyId());
				if (party) {
					f32 px = party->position.x, py = 15.0f + party->position.y, pz = party->position.z;
					entry->position.x = px;
					entry->position.y = py;
					entry->position.z = pz;
				}
				else {
					itemModeChange(entry, 3);
					entry->flags2 &= ~0x1000;
				}
				break;
			case 9:
				itemDelete(entry->name);
				break;
		}

		if (entry->flags & 1) {
			switch (entry->itemId) {
				case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
					if (!(entry->flags2 & 0x100)) {
						((ItemEffPos*)entry->effect->userdata)->position.x = entry->position.x;
						((ItemEffPos*)entry->effect->userdata)->position.y = 16.0f + entry->position.y;
						((ItemEffPos*)entry->effect->userdata)->position.z = entry->position.z;
					}
					else {
						((ItemEffPos*)entry->effect->userdata)->position.x = entry->position.x;
						((ItemEffPos*)entry->effect->userdata)->position.y = -1000.0f;
						((ItemEffPos*)entry->effect->userdata)->position.z = entry->position.z;
					}
					break;
				default:
					if (!(entry->flags2 & 0x100)) {
						iconSetPos(entry->name, entry->position.x, entry->position.y, entry->position.z);
						iconSetScale(entry->name, entry->scale);
						iconSetAlpha(entry->name, entry->alpha);
					}
					else {
						iconSetPos(entry->name, entry->position.x, -1000.0f, entry->position.z);
					}
					break;
			}
			entry->baseTime = gp->renderTime;
			if (entry->itemId == 0x79 || entry->itemId == 0x7A) {
				if (irand(1000) < 30) {
					dx = 10 - irand(20);
					dy = irand(20) + 10;
					effHagetakaFlushN64Entry(0, 10, entry->position.x + dx, entry->position.y + dy, entry->position.z, 1.0f);
				}
			}
		}
	}

	wp = gp->inBattle ? &work[0] : &work[1];
	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (entry->flags & 1) {
			entry->baseTime = gp->renderTime;
		}
#endif
#ifndef NONMATCHING
	char _af_pad[52];
	asm volatile {
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r31, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BFF001C
		bl marioGetPtr
		lfs f3, float_0p5_8041afb8(r2)
		opword 0xC04301B4
		lfs f0, float_12_8041b010(r2)
		opword 0xC023008C
		opword 0xEC8300BA
		opword 0xC0430090
		opword 0xC0630094
		bl itemHitCheck
		opword 0x7C7C1B78
		bl itemGetCheck
		opword 0x2C030000
		opword 0x41820014
		opword 0x38600002
		opword 0x38000000
		opword 0xB07C0024
		opword 0xB01C0026
		lis r3, work@ha
		opword 0x83BF0004
		addi r3, r3, work@l
		opword 0x3B800000
		opword 0x3BC3001C
		opword 0x48000590
		opword 0xA01D0000
		opword 0x540007FF
		opword 0x4182057C
		opword 0xA0BD0024
		opword 0x38800001
		opword 0x2C050009
		opword 0x4182002C
		opword 0x4080001C
		opword 0x2C050002
		opword 0x41820034
		opword 0x4180001C
		opword 0x2C050007
		opword 0x40800028
		opword 0x48000010
		opword 0x2C05000B
		opword 0x40800008
		opword 0x48000018
		lwz r3, gp(r13)
		opword 0x80030018
		opword 0x5400073F
		opword 0x41820008
		opword 0x38800000
		opword 0x2C040000
		opword 0x4082001C
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907D006C
		opword 0x901D0068
		opword 0x48000510
		opword 0x28050002
		opword 0x41820148
		opword 0x801D0078
		opword 0x38600000
		opword 0x809D007C
		opword 0x7C001A78
		opword 0x7C831A78
		opword 0x7C600379
		opword 0x40820014
		opword 0x801D0038
		opword 0x5400062C
		opword 0x901D0038
		opword 0x48000128
		opword 0x807D0038
		opword 0x54600463
		opword 0x41820010
		opword 0x5460062C
		opword 0x901D0038
		opword 0x48000110
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C60431C
		opword 0x3863DE83
		opword 0x80A6003C
		opword 0x5400F0BE
		opword 0x809D006C
		opword 0x7C030016
		opword 0x80E60038
		opword 0x7CC42810
		opword 0x807D0068
		opword 0x38A00000
		opword 0x7C633910
		opword 0x54631838
		opword 0x54C41838
		opword 0x50C31F7E
		opword 0x54068BFE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1000_8041b014(r2)
		opword 0x807D0078
		fdivs f31, f1, f0
		opword 0x809D007C
		bl __cvt_sll_flt
		opword 0xEC21F828
		bl __cvt_dbl_usll
		opword 0x909D007C
		opword 0x38A00000
		opword 0x6CA48000
		opword 0x907D0078
		opword 0x80DD0078
		opword 0x80FD007C
		opword 0x6CC38000
		opword 0x7C072810
		opword 0x7C632110
		opword 0x7C642110
		opword 0x7C6300D1
		opword 0x40820014
		opword 0x38000009
		opword 0xB01D0024
		opword 0xB0BD0026
		opword 0x48000064
		opword 0x38000BB8
		opword 0x6CC38000
		opword 0x7C070010
		opword 0x7C632110
		opword 0x7C642110
		opword 0x7C6300D1
		opword 0x40820048
		opword 0x54E4E03E
		opword 0x7CC02670
		opword 0x7C002838
		opword 0x38600001
		opword 0x50C4E006
		opword 0x7C831838
		opword 0x7C002A78
		opword 0x7C632A78
		opword 0x7C600379
		opword 0x41820020
		opword 0x801D0038
		opword 0x68000100
		opword 0x901D0038
		opword 0x48000010
		opword 0x801D0038
		opword 0x5400062C
		opword 0x901D0038
		opword 0xA01D0024
		opword 0x2800000A
		opword 0x41810214
		lis r3, jumptable_80312488@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80312488@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7FA3EB78
		bl itemseq_Bound
		opword 0x480001F0
		opword 0x7FA3EB78
		bl itemseq_Bound
		opword 0x480001E4
		opword 0x801D0038
		opword 0xC3FD0040
		opword 0x540002D7
		opword 0x41820014
		lfs f0, float_neg1_8041afac(r2)
		opword 0x38600000
		opword 0xEC1F002A
		opword 0x48000080
		lis r4, double_neg1_802cae60@ha
		lis r3, double_20_802cac28@ha
		lfd f0, double_neg1_802cae60@l(r4)
		la r4, _af_pad+0
		lfd f2, double_20_802cac28@l(r3)
		opword 0x38A1000C
		opword 0xFCA00210
		lfs f4, float_0_8041af9c(r2)
		lfs f0, float_20_8041afa0(r2)
		opword 0x38C10010
		opword 0xC03D003C
		opword 0xFCC02090
		opword 0xFCE2282A
		opword 0xC07D0044
		opword 0xEC40F82A
		lfs f5, float_neg1_8041afac(r2)
		opword 0x38E10014
		opword 0x39010018
		opword 0xFC003818
		opword 0x3921001C
		opword 0x39410020
		opword 0x38600000
		opword 0xD0010014
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4182000C
		opword 0xC001000C
		opword 0x48000010
		lfs f0, float_neg1_8041afac(r2)
		opword 0x38600000
		opword 0xEC1F002A
		opword 0x28030000
		opword 0x40820018
		opword 0x38600003
		opword 0x38000000
		opword 0xB07D0024
		opword 0xB01D0026
		opword 0x4800012C
		opword 0xD01D0040
		opword 0x48000124
		opword 0x7FA3EB78
		bl itemseq_GetItem
		opword 0x48000118
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820028
		lfs f2, float_15_8041afb4(r2)
		opword 0xC023005C
		opword 0xC0630060
		opword 0xC0030058
		opword 0xEC22082A
		opword 0xD01D003C
		opword 0xD03D0040
		opword 0xD07D0044
		opword 0x480000E4
		opword 0x38600003
		opword 0x38000000
		opword 0xB07D0024
		opword 0xB01D0026
		opword 0x801D0038
		opword 0x54000524
		opword 0x901D0038
		opword 0x480000C4
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x4182000C
		opword 0x7FD9F378
		opword 0x4800000C
		lis r3, work@ha
		addi r25, r3, work@l
		opword 0x83590004
		opword 0x3B600000
		opword 0x4800008C
		opword 0x387A000C
		opword 0x389D000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x807A0004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA01A0000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x801A0004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x807A001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x387A000C
		bl iconDelete
		opword 0xA01A0000
		opword 0x5400043C
		opword 0xB01A0000
		opword 0x3B7B0001
		opword 0x3B5A0098
		opword 0x80190000
		opword 0x7C1B0000
		opword 0x4180FF70
		opword 0xA01D0000
		opword 0x540007FF
		opword 0x41820190
		opword 0x801D0004
		opword 0x2C000079
		opword 0x4080008C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000080
		opword 0x801D0038
		opword 0x540005EF
		opword 0x40820040
		opword 0x807D001C
		opword 0xC01D003C
		opword 0x8063000C
		lfs f1, float_16_8041afc8(r2)
		opword 0xD0030008
		opword 0xC01D0040
		opword 0x807D001C
		opword 0xEC01002A
		opword 0x8063000C
		opword 0xD003000C
		opword 0x807D001C
		opword 0xC01D0044
		opword 0x8063000C
		opword 0xD0030010
		opword 0x48000088
		opword 0x807D001C
		opword 0xC03D003C
		opword 0x8063000C
		lfs f0, float_neg1000_8041aff0(r2)
		opword 0xD0230008
		opword 0x807D001C
		opword 0x8063000C
		opword 0xD003000C
		opword 0x807D001C
		opword 0xC01D0044
		opword 0x8063000C
		opword 0xD0030010
		opword 0x48000054
		opword 0x801D0038
		opword 0x540005EF
		opword 0x40820034
		opword 0xC03D003C
		opword 0x387D000C
		opword 0xC05D0040
		opword 0xC07D0044
		bl iconSetPos
		opword 0xC03D0048
		opword 0x387D000C
		bl iconSetScale
		opword 0x889D004C
		opword 0x387D000C
		bl iconSetAlpha
		opword 0x48000018
		opword 0xC03D003C
		opword 0x387D000C
		lfs f2, float_neg1000_8041aff0(r2)
		opword 0xC07D0044
		bl iconSetPos
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907D006C
		opword 0x901D0068
		opword 0x801D0004
		opword 0x2C000079
		opword 0x4182000C
		opword 0x2C00007A
		opword 0x40820084
		opword 0x386003E8
		bl irand
		opword 0x2C03001E
		opword 0x40800074
		opword 0x38600014
		bl irand
		opword 0x2323000A
		opword 0x38600014
		bl irand
		opword 0x3803000A
		opword 0x3CA04330
		opword 0x6F238000
		opword 0x90A10028
		lis r4, double_to_int_802cac48@ha
		opword 0x6C008000
		opword 0x9061002C
		opword 0x38600000
		lfd f5, double_to_int_802cac48@l(r4)
		opword 0x3880000A
		opword 0xC8010028
		opword 0x90010034
		opword 0xEC202828
		opword 0xC09D003C
		opword 0x90A10030
		opword 0xC05D0040
		opword 0xC8010030
		opword 0xEC24082A
		opword 0xC07D0044
		opword 0xEC002828
		lfs f4, float_1_8041afa4(r2)
		opword 0xEC42002A
		bl effHagetakaFlushN64Entry
		opword 0x3B9C0001
		opword 0x3BBD0098
		opword 0x801F0000
		opword 0x7C1C0000
		opword 0x4180FA6C
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x4182000C
		lis r3, work@ha
		addi r30, r3, work@l
		opword 0x809E0004
		opword 0x38A00000
		opword 0x4800002C
		opword 0xA0040000
		opword 0x540007FF
		opword 0x41820018
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x9064006C
		opword 0x90040068
		opword 0x38A50001
		opword 0x38840098
		opword 0x801E0000
		opword 0x7C050000
		opword 0x4180FFD0
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

void itemModeChange(ItemEntry* entry, s32 mode) {
	entry->mode = mode;
	entry->subState = 0;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z) {
#ifdef NONMATCHING
	ItemWork* wp = itemGetWork();
	int i;
	ItemEntry* entry;
	BOOL isGswf, isLswf;
	char itemName[8];

	isGswf = FALSE;
	isLswf = FALSE;
	if (evtId != -1) {
		if (evtId >= GSWF(0) && evtId <= EVTDAT_GSWF_MAX) {
			evtId += EVTDAT_GSWF_BASE;
			isGswf = TRUE;
			if (swGet(evtId)) {
				return NULL;
			}
		}
		else if (evtId >= LSWF(0) && evtId <= EVTDAT_LSWF_MAX) {
			evtId += EVTDAT_LSWF_BASE;
			isLswf = TRUE;
			if (_swGet(evtId)) {
				return NULL;
			}
		}
#endif
#ifndef NONMATCHING
	char _af_pad[4];
	asm volatile {
		lwz r9, gp(r13)
		lis r8, work@ha
		fmr f29, f1
		addi r23, r8, work@l
		opword 0x80090014
		opword 0xFFC01090
		opword 0xFFE01890
		opword 0x7C781B78
		opword 0x2C000000
		opword 0x7C992378
		opword 0x7CBA2B78
		opword 0x7CDB3378
		opword 0x7CFC3B78
		opword 0x41820008
		opword 0x3AF7001C
		opword 0x2C1BFFFF
		opword 0x3BC00000
		opword 0x3BA00000
		opword 0x4182008C
		opword 0x3C60F840
		opword 0x38035B80
		opword 0x7C1B0000
		opword 0x41800038
		opword 0x3C60F8D9
		opword 0x3803F200
		opword 0x7C1B0000
		opword 0x41810028
		opword 0x3F7B07C0
		opword 0x3BC00001
		opword 0x3B7BA480
		opword 0x7F63DB78
		bl swGet
		opword 0x2C030000
		opword 0x41820050
		opword 0x38600000
		opword 0x48000758
		opword 0x3C60F972
		opword 0x38038880
		opword 0x7C1B0000
		opword 0x41800038
		opword 0x3C60FA0A
		opword 0x38031F00
		opword 0x7C1B0000
		opword 0x41810028
		opword 0x3F7B068E
		opword 0x3BA00001
		opword 0x3B7B7780
		opword 0x7F63DB78
		bl _swGet
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000714
		opword 0x28180000
		opword 0x40820048
		opword 0x80970008
		opword 0x3C600010
		opword 0x3803FFFF
		opword 0x38640001
		opword 0x90770008
		opword 0x80770008
		opword 0x7C030040
		opword 0x4180000C
		opword 0x38000001
		opword 0x90170008
		lis r3, str_802CADE0@ha
		opword 0x80B70008
		addi r4, r3, str_802CADE0@l
		la r3, _af_pad+0
		opword 0x4CC63182
		bl sprintf
		opword 0x3B010008
		opword 0x82D70004
		li r21, 0x0
		opword 0x4800002C
		opword 0xA0160000
		opword 0x540007FF
		opword 0x41820018
		opword 0x7F04C378
		opword 0x3876000C
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x3AB50001
		opword 0x3AD60098
		opword 0x80170000
		opword 0x7C150000
		opword 0x4180FFD0
		opword 0x80970004
		opword 0x38A00000
		opword 0x80770000
		opword 0x7C9F2378
		opword 0x7C6903A6
		opword 0x2C030000
		opword 0x4081001C
		opword 0xA01F0000
		opword 0x540007FF
		opword 0x41820010
		opword 0x38A50001
		opword 0x3BFF0098
		opword 0x4200FFEC
		opword 0x7C051800
		opword 0x418002BC
		opword 0xA0640000
		opword 0x7C9F2378
		opword 0x546007FF
		opword 0x418200D8
		opword 0x80040004
		opword 0x2C000079
		opword 0x408200CC
		opword 0x5460056B
		opword 0x418200C4
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r23, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3AF7001C
		opword 0x82B70004
		opword 0x3AC00000
		opword 0x4800008C
		opword 0x3875000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x80750004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA0150000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x80150004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x8075001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x3875000C
		bl iconDelete
		opword 0xA0150000
		opword 0x5400043C
		opword 0xB0150000
		opword 0x3AD60001
		opword 0x3AB50098
		opword 0x80170000
		opword 0x7C160000
		opword 0x4180FF70
		opword 0x480001C8
		opword 0x546007FF
		opword 0x7C9F2378
		opword 0x418200D8
		opword 0x80040004
		opword 0x2C00007C
		opword 0x408200CC
		opword 0x5460056B
		opword 0x418200C4
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r23, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3AF7001C
		opword 0x82D70004
		opword 0x3AA00000
		opword 0x4800008C
		opword 0x3876000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x80760004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA0160000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x80160004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x8076001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x3876000C
		bl iconDelete
		opword 0xA0160000
		opword 0x5400043C
		opword 0xB0160000
		opword 0x3AB50001
		opword 0x3AD60098
		opword 0x80170000
		opword 0x7C150000
		opword 0x4180FF70
		opword 0x480000E8
		opword 0x546007FF
		opword 0x7C9F2378
		opword 0x418200D8
		opword 0x80040004
		opword 0x2C00007B
		opword 0x408200CC
		opword 0x5460056B
		opword 0x418200C4
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r23, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3AF7001C
		opword 0x82D70004
		opword 0x3AA00000
		opword 0x4800008C
		opword 0x3876000C
		opword 0x389F000C
		bl strcmp
		opword 0x2C030000
		opword 0x40820070
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820028
		opword 0x80760004
		opword 0x2C0300F0
		opword 0x4180001C
		opword 0x2C030153
		opword 0x40800014
		opword 0xA0160000
		opword 0x540005EF
		opword 0x41820008
		bl pouchArriveBadge
		opword 0x80160004
		opword 0x2C000079
		opword 0x4080001C
		opword 0x2C000072
		opword 0x40800008
		opword 0x48000010
		opword 0x8076001C
		bl effSoftDelete
		opword 0x4800000C
		opword 0x3876000C
		bl iconDelete
		opword 0xA0160000
		opword 0x5400043C
		opword 0xB0160000
		opword 0x3AB50001
		opword 0x3AD60098
		opword 0x80170000
		opword 0x7C150000
		opword 0x4180FF70
		opword 0x48000008
		opword 0x3BE00000
		opword 0x281F0000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000394
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00098
		bl memset
		opword 0x7F04C378
		opword 0x387F000C
		bl strcpy
		opword 0xD3BF003C
		opword 0x2C1BFFFF
		lfs f0, float_1_8041afa4(r2)
		opword 0x380000FF
		opword 0xD3DF0040
		opword 0xD3FF0044
		opword 0x933F0004
		opword 0xB35F0002
		opword 0x939F0020
		opword 0xA07F0000
		opword 0x60630001
		opword 0xB07F0000
		opword 0xD01F0048
		opword 0x981F004C
		opword 0x4182003C
		opword 0x2C1E0000
		opword 0x41820018
		opword 0x937F0008
		opword 0xA01F0000
		opword 0x60000020
		opword 0xB01F0000
		opword 0x48000028
		opword 0x2C1D0000
		opword 0x41820020
		opword 0x937F0008
		opword 0xA01F0000
		opword 0x60000040
		opword 0xB01F0000
		opword 0x4800000C
		opword 0x3800FFFF
		opword 0x901F0008
		opword 0x807F0004
		opword 0x2C030079
		opword 0x40800034
		opword 0x2C030072
		opword 0x40800008
		opword 0x48000028
		lfs f0, float_16_8041afc8(r2)
		opword 0xFC20E890
		opword 0xFC60F890
		lfs f4, float_1_8041afa4(r2)
		opword 0xEC40F02A
		opword 0x3863FF8E
		bl effStarStoneEntry
		opword 0x907F001C
		opword 0x48000054
		opword 0x1C190028
		opword 0x38600000
		lis r4, itemDataTable@ha
		opword 0x907F001C
		opword 0x387F000C
		addi r4, r4, itemDataTable@l
		opword 0x7C840214
		opword 0xA0840020
		bl iconEntry
		opword 0xFC20E890
		opword 0x387F000C
		opword 0xFC40F090
		opword 0xFC60F890
		bl iconSetPos
		opword 0xC03F0048
		opword 0x387F000C
		bl iconSetScale
		opword 0x889F004C
		opword 0x387F000C
		bl iconSetAlpha
		lfs f0, float_1_8041afa4(r2)
		opword 0xD01F0084
		opword 0xD01F0080
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F006C
		opword 0x901F0068
		opword 0x801F0004
		opword 0x2C00007D
		opword 0x4080001C
		opword 0x2C000079
		opword 0x40800008
		opword 0x48000010
		opword 0xA01F0000
		opword 0x60000004
		opword 0xB01F0000
		opword 0x5740043E
		opword 0x28000011
		opword 0x4181021C
		lis r3, jumptable_80312440@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80312440@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xA01F0000
		opword 0x60000002
		opword 0xB01F0000
		opword 0x38600007
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x480001E4
		opword 0x38600001
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x480001D0
		opword 0x38600001
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0xA01F0000
		opword 0x60000002
		opword 0xB01F0000
		opword 0x480001B0
		opword 0x38600006
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x4800019C
		opword 0x38001388
		opword 0x38600000
		opword 0x901F007C
		opword 0x38000005
		opword 0x907F0078
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0x4800017C
		opword 0x80BF0038
		opword 0x38804E20
		opword 0x38600000
		opword 0x38000006
		opword 0x60A54000
		opword 0x90BF0038
		opword 0x909F007C
		opword 0x907F0078
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0x48000150
		opword 0x80BF0038
		opword 0x38804E20
		opword 0x38600000
		opword 0x38000006
		opword 0x60A54000
		opword 0x90BF0038
		opword 0x909F007C
		opword 0x907F0078
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0xA01F0000
		opword 0x60000400
		opword 0xB01F0000
		opword 0x48000118
		opword 0xA01F0000
		opword 0x60000100
		opword 0xB01F0000
		opword 0x80BF0038
		opword 0x38801F40
		opword 0x38600000
		opword 0x38000006
		opword 0x60A54000
		opword 0x90BF0038
		opword 0x909F007C
		opword 0x907F0078
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0x480000E0
		opword 0x80BF0038
		opword 0x38801F40
		opword 0x38600000
		opword 0x38000006
		opword 0x60A54000
		opword 0x90BF0038
		opword 0x909F007C
		opword 0x907F0078
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0xA01F0000
		opword 0x60000400
		opword 0xB01F0000
		opword 0x480000A8
		opword 0x801F0038
		opword 0x60004000
		opword 0x901F0038
		opword 0x38001388
		opword 0x38600000
		opword 0x901F007C
		opword 0x38000006
		opword 0x907F0078
		opword 0xB01F0024
		opword 0xB07F0026
		opword 0x4800007C
		opword 0x38001388
		opword 0x38800000
		opword 0x901F007C
		opword 0x38000006
		opword 0x909F0078
		opword 0x807F0038
		opword 0x60630040
		opword 0x907F0038
		opword 0xB01F0024
		opword 0xB09F0026
		opword 0x48000050
		opword 0x38600005
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x4800003C
		opword 0x38600003
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x48000028
		opword 0x38600004
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x48000014
		opword 0x3860000A
		opword 0x38000000
		opword 0xB07F0024
		opword 0xB01F0026
		opword 0x7FE3FB78
#endif
	}
#ifdef NONMATCHING

	if (name == NULL) {
		wp->currId++;
		if (wp->currId >= 0xFFFFF) {
			wp->currId = 1;
		}
		sprintf(itemName, "_i%05x", wp->currId);
		name = itemName;
	}

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (entry->flags & 1 && !strcmp(entry->name, name)) {
			break;
		}
	}

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) {
			break;
		}
	}

	if (i >= wp->count) {
		entry = wp->entries;
		if (entry->flags & 1 && entry->itemId == 0x79 && entry->flags & 0x400) {
			itemDelete(entry->name);
		}
		else {
			entry = wp->entries;
			if (entry->flags & 1 && entry->itemId == 0x7C && entry->flags & 0x400) {
				itemDelete(entry->name);
			}
			else {
				entry = wp->entries;
				if (entry->flags & 1 && entry->itemId == 0x7B && entry->flags & 0x400) {
					itemDelete(entry->name);
				}
				else {
					entry = NULL;
				}
			}
		}
		if (entry == NULL) {
			return NULL;
		}
	}

	memset(entry, 0, sizeof(ItemEntry));
	strcpy(entry->name, name);
	entry->position.x = x;
	entry->position.y = y;
	entry->position.z = z;
	entry->itemId = itemId;
	entry->type = type;
	entry->evtCode = a5;
	entry->flags |= 1;
	entry->scale = 1.0f;
	entry->alpha = 0xFF;
	if (evtId != -1) {
		if (isGswf) {
			entry->evtId = evtId;
			entry->flags |= 0x20;
		}
		else if (isLswf) {
			entry->evtId = evtId;
			entry->flags |= 0x40;
		}
	}
	else {
		entry->evtId = -1;
	}

	switch (entry->itemId) {
	case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
		entry->effect = effStarStoneEntry(entry->itemId - 0x72, x, 16.0f + y, z, 1.0f);
		break;
	default:
		entry->effect = NULL;
		iconEntry(entry->name, itemDataTable[itemId].icon_id);
		{ char* nm = ((ItemEntry*)entry)->name; iconSetPos(nm, x, y, z); }
		iconSetScale(entry->name, entry->scale);
		iconSetAlpha(entry->name, entry->alpha);
		break;
	}
	entry->bounceFactor = entry->gravityScale = 1.0f;
	entry->baseTime = gp->renderTime;
	switch (entry->itemId) {
	case 0x79: case 0x7A: case 0x7B: case 0x7C:
		entry->flags |= 4;
		break;
	}

	switch ((u16)type) {
		case 17:
			entry->flags |= 2;
		case 16:
			itemModeChange(entry, 7);
			break;
		case 0:
			itemModeChange(entry, 1);
			break;
		case 1:
			itemModeChange(entry, 1);
			entry->flags |= 2;
			break;
		case 4:
			itemModeChange(entry, 6);
			break;
		case 3:
			entry->timer = 5000;
			itemModeChange(entry, 5);
			break;
		case 11:
			entry->flags2 |= 0x4000;
			entry->timer = 20000;
			itemModeChange(entry, 6);
			break;
		case 12:
			entry->flags2 |= 0x4000;
			entry->timer = 20000;
			itemModeChange(entry, 6);
			entry->flags |= 0x400;
			break;
		case 9:
			entry->flags |= 0x100;
		case 8:
			entry->flags2 |= 0x4000;
			entry->timer = 8000;
			itemModeChange(entry, 6);
			break;
		case 10:
			entry->flags2 |= 0x4000;
			entry->timer = 8000;
			itemModeChange(entry, 6);
			entry->flags |= 0x400;
			break;
		case 7:
			entry->flags2 |= 0x4000;
		case 5:
			entry->timer = 5000;
			itemModeChange(entry, 6);
			break;
		case 6:
			entry->timer = 5000;
			entry->flags2 |= 0x40;
			itemModeChange(entry, 6);
			break;
		case 2:
			itemModeChange(entry, 5);
			break;
		case 13:
			itemModeChange(entry, 3);
			break;
		case 14:
			itemModeChange(entry, 4);
			break;
		case 15:
			itemModeChange(entry, 10);
			break;
	}
	return entry;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void itemDelete(const char* name) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!strcmp(entry->name, name)) {
			itemCheckBadge(entry);
			switch (entry->itemId) {
				case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
					effSoftDelete(entry->effect);
					break;
				default:
					iconDelete(entry->name);
					break;
			}
			entry->flags &= ~1;
		}
	}
}

ItemEntry* itemNameToPtr(char* name) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!strcmp(entry->name, name)) {
			return entry;
		}
	}
	return NULL;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range) {
#ifdef NONMATCHING
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;
	MarioWork* mario;
	ItemEntry* found;
	f32 dx, dy, dz, xzdist, dist;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	HitEntry* hit;

	mario = marioGetPtr();
	found = NULL;
	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) continue;
			if (entry->flags & 2) { do { } while (0); continue; }
		if (entry->flags2 & 0x1000) continue;
		if (entry->mode == 2) continue;
		dx = x - entry->position.x; dy = y - entry->position.y;
		dz = z - entry->position.z;
		xzdist = item_sqrtf(dx * dx + dz * dz);
		dist = item_sqrtf(dx * dx + dy * dy + dz * dz);
		if (xzdist < range && marioItemGetOk() && marioGetJabaraState() != 1 &&
			marioGetJabaraState() != 4 && marioGetJabaraState() != 5)
		{
			if (__fabs((y + mario->wPlayerCollisionBox.y * 0.5f) - entry->position.y) < mario->wPlayerCollisionBox.y * 0.5f + 10.0f) {
				hit = NULL;
				if (y < entry->position.y) {
					hitDist = 10.0f + (entry->position.y - y);
					if (hitDist > 0.0f) {
						hit = hitCheckAttr(0x80000000, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f);
					}
				}
				if (!hit) {
					found = entry;
					range = dist;
				}
			}
		}
	}
	return found;
}

ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
	MarioWork* mario = marioGetPtr();
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	ItemEntry* found;
	int i;
	Vec itemPos, diff, pos;
	f32 dist;

	entry = wp->entries;
	found = NULL;
	i = 0;
	pos = makeVecByValue2(x, y, z);
	for (; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) continue;
		if (entry->flags2 & 0x1000) continue;
		if (entry->flags2 & 0x100000) continue;
		if (entry->mode == 2) continue;
		if (entry->flags2 & 0x2000000) continue;
		{ f32 iz, iy, ix; ix = entry->position.x; iy = entry->position.y; iz = entry->position.z; itemPos = makeVecByValue(ix, iy, iz); }
		PSVECSubtract(&itemPos, &pos, &diff);
		dist = PSVECMag(&diff);
		if (dist < range) {
			found = entry;
			range = dist;
		}
	}
	return found;
}

void winNameDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;
	const char* name;
	u16 width;
	char buffer[1024];

	name = msgSearch(itemDataTable[entry->itemId].name);
	if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
		sprintf(buffer, msgSearch("msg_window_badge_get"), name);
	}
	else {
		sprintf(buffer, msgSearch("msg_window_item_get"), name);
	}
	width = FontGetMessageWidth(buffer);
	if (width + 20 > win->width) {
		win->width = width + 20;
		win->x = -win->width / 2;
	}
	if (!winMgrAction(entry->winId[0])) {
		FontDrawStart();
		FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
		FontDrawMessage(-width / 2, win->y - 8, buffer);
#endif
#ifndef NONMATCHING
	char _af_pad[40];
	asm volatile {
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r30, r3, work@l
		fmr f27, f1
		opword 0x80040014
		lis r3, vec3_802cabe0@ha
		opword 0xFF801090
		addi r29, r3, vec3_802cabe0@l
		opword 0xFFA01890
		opword 0x2C000000
		opword 0xFFC02090
		opword 0x41820008
		opword 0x3BDE001C
		bl marioGetPtr
		opword 0x839E0004
		opword 0x7C7F1B78
		li r26, 0x0
		opword 0x3B600000
		opword 0x480002E0
		opword 0xA07C0000
		opword 0x546007FF
		opword 0x418202CC
		opword 0x546007BD
		opword 0x408202C4
		opword 0x801C0038
		opword 0x540004E7
		opword 0x408202B8
		opword 0xA01C0024
		opword 0x28000002
		opword 0x418202AC
		opword 0xC03C003C
		opword 0xC01C0044
		opword 0xEC7B0828
		opword 0xC05C0040
		opword 0xEC1D0028
		lfs f1, float_0_8041af9c(r2)
		opword 0xECFC1028
		opword 0xECA300F2
		opword 0xECC00032
		opword 0xEC05302A
		opword 0xFC000840
		opword 0x4081004C
		opword 0xFC400034
		opword 0xC89D0050
		opword 0xC87D0058
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC20187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC20187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC20187C
		opword 0xFC220072
		opword 0xFC000072
		opword 0xFC000018
		opword 0x48000088
		opword 0xC83D0060
		opword 0xFC000840
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f0, __float_nan@l(r3)
		opword 0x48000070
		stfs f0, _af_pad+4(r1)
		opword 0x3C007F80
		opword 0x8081000C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f0, __float_nan@l(r3)
		opword 0xEC4729FA
		lfs f1, float_0_8041af9c(r2)
		opword 0xEFE6102A
		opword 0xFC1F0840
		opword 0x4081004C
		opword 0xFC40F834
		opword 0xC89D0050
		opword 0xC87D0058
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC3F187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC3F187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC3F187C
		opword 0xFC220072
		opword 0xFFFF0072
		opword 0xFFE0F818
		opword 0x48000088
		opword 0xC83D0060
		opword 0xFC1F0840
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f31, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD3E10008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f31, __float_nan@l(r3)
		opword 0xFC00F040
		opword 0x408000C8
		bl marioItemGetOk
		opword 0x2C030000
		opword 0x418200BC
		bl marioGetJabaraState
		opword 0x2C030001
		opword 0x418200B0
		bl marioGetJabaraState
		opword 0x2C030004
		opword 0x418200A4
		bl marioGetJabaraState
		opword 0x2C030005
		opword 0x41820098
		lfs f4, float_0p5_8041afb8(r2)
		opword 0xC01F01B8
		lfs f1, float_10_8041afb0(r2)
		opword 0xEC44E03A
		opword 0xC07C0040
		opword 0xEC04083A
		opword 0xEC421828
		opword 0xFC401210
		opword 0xFC020040
		opword 0x40800070
		opword 0xFC1C1840
		opword 0x38600000
		opword 0x40800054
		opword 0xEC03E028
		lfs f4, float_0_8041af9c(r2)
		opword 0xEC01002A
		opword 0xFC002040
		opword 0xD001001C
		opword 0x4081003C
		opword 0xFC20D890
		lfs f5, float_1_8041afa4(r2)
		opword 0xFC40E090
		opword 0x38810028
		opword 0xFC60E890
		opword 0x38A10024
		opword 0xFCC02090
		opword 0x38C10020
		opword 0x38E1001C
		opword 0x39010018
		opword 0x39210014
		opword 0x39410010
		opword 0x3C608000
		bl hitCheckAttr
		opword 0x28030000
		opword 0x4082000C
		opword 0x7F9AE378
		opword 0xFFC0F890
		opword 0x3B7B0001
		opword 0x3B9C0098
		opword 0x801E0000
		opword 0x7C1B0000
		opword 0x4180FD1C
		opword 0x7F43D378
#endif
	}
}
#ifdef NONMATCHING

void winNameDisp2(WinMgrEntry* win) {
	ItemEntry* entry = win->param;
	const char* name;
	u16 width;
	char buffer[1024];

	name = msgSearch(itemDataTable[entry->itemId].name);
	sprintf(buffer, msgSearch("msg_window_item_release"), name);
	width = FontGetMessageWidth(buffer);
	if (width + 20 > win->width) {
		win->width = width + 20;
		win->x = -win->width / 2;
	}
	if (!winMgrAction(entry->winId[0])) {
		FontDrawStart();
		FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
		FontDrawMessage(-width / 2, win->y - 8, buffer);
	}
}

void winHelpMain(WinMgrEntry* win) {
	winMgrHelpMain(win);
}

void winHelpDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;

	if (!winMgrAction(entry->winId[1])) {
		win->msg = msgSearch(itemDataTable[entry->itemId].description);
		winMgrHelpDraw(win);
	}
}

void winFullDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;
	BOOL isBadge = FALSE;
	u16 width;
	const char* msg;
#endif
#ifndef NONMATCHING
#pragma pop
#endif


#ifdef NONMATCHING
	if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
		isBadge = TRUE;
	}
	msg = isBadge ? msgSearch("msg_window_badge_full") : msgSearch("msg_window_item_full");
	width = FontGetMessageWidth(msg);
	if (width + 20 > win->width) {
		win->width = width + 20;
		win->x = -win->width / 2;
	}
	if (!winMgrAction(entry->winId[2])) {
		FontDrawStart();
		FontDrawEdge();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawMessage(-width / 2, win->y - 10, msg);
		FontDrawEdgeOff();
	}
}
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802cabe0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cabec[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cabf8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cac04[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cac10[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cac1c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_20_802cac28 = 20.0;
__declspec(section ".rodata") const f64 double_0p5_802cac30 = 0.5;
__declspec(section ".rodata") const f64 double_3_802cac38 = 3.0;
__declspec(section ".rodata") const f64 double_0_802cac40 = 0.0;
__declspec(section ".rodata") const f64 double_to_int_802cac48 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802CAC50[] = "SFX_COIN_GET1\0\0";
__declspec(section ".rodata") const char str_802CAC60[] = "SFX_EVT_GAME_MONTE_COUNT1\0\0";
__declspec(section ".rodata") const char str_802CAC7C[] = "SFX_HEART_GET1\0";
__declspec(section ".rodata") const char str_802CAC8C[] = "SFX_FLOWER_GET1";
__declspec(section ".rodata") const char str_802CAC9C[] = "SFX_COIN_LEAPED1\0\0\0";
__declspec(section ".rodata") const char str_802CACB0[] = "SFX_EVT_GAME_MONTE_LEAPED1\0";
__declspec(section ".rodata") const char str_802CACCC[] = "SFX_HEART_LEAPED1\0\0";
__declspec(section ".rodata") const char str_802CACE0[] = "SFX_FLOWER_LEAPED1\0";
__declspec(section ".rodata") const char str_802CACF4[] = "SFX_STAR_PIECE_LEAPED1\0";
__declspec(section ".rodata") const char str_802CAD0C[] = "SFX_EVT_STARSTONE_JUMP1";
__declspec(section ".rodata") const char str_802CAD24[] = "SFX_BADGE_LEAPED1\0\0";
__declspec(section ".rodata") const char str_802CAD38[] = "SFX_ITEM_LEAPED1\0\0\0";
__declspec(section ".rodata") const char str_802CAD4C[] = "MOBJ_KururinFloor\0\0";
__declspec(section ".rodata") const char str_802CAD60[] = "BGM_FF_GET_STARPIECE1\0\0";
__declspec(section ".rodata") const char str_802CAD78[] = "BGM_FF_GET_KEYITEM1";
__declspec(section ".rodata") const char str_802CAD8C[] = "BGM_FF_GET_BADGE1\0\0";
__declspec(section ".rodata") const char str_802CADA0[] = "BGM_FF_GET_IMPORTANT_ITEM1\0";
__declspec(section ".rodata") const char str_802CADBC[] = "BGM_FF_GET_ITEM1\0\0\0";
__declspec(section ".rodata") const char str_802CADD0[] = "item_first_hit\0";
__declspec(section ".rodata") const char str_802CADE0[] = "_i%05x\0";
__declspec(section ".rodata") const char str_802CADE8[] = "msg_window_badge_full\0\0";
__declspec(section ".rodata") const char str_802CAE00[] = "msg_window_item_full\0\0\0";
__declspec(section ".rodata") const char str_802CAE18[] = "msg_window_item_release";
__declspec(section ".rodata") const char str_802CAE30[] = "msg_window_badge_get\0\0\0";
__declspec(section ".rodata") const char str_802CAE48[] = "msg_window_item_get";
__declspec(section ".rodata") const f64 double_neg1_802cae60 = -1.0;
__declspec(section ".rodata") extern const u32 gap_04_802CAE68_rodata[6];
__declspec(section ".rodata") const u32 gap_04_802CAE68_rodata[6] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".sdata2") const u32 dat_8041af90 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041af94 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041af98 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0_8041af9c = 0.0f;
__declspec(section ".sdata2") const f32 float_20_8041afa0 = 20.0f;
__declspec(section ".sdata2") const f32 float_1_8041afa4 = 1.0f;
__declspec(section ".sdata2") const f32 float_4_8041afa8 = 4.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041afac = -1.0f;
__declspec(section ".sdata2") const f32 float_10_8041afb0 = 10.0f;
__declspec(section ".sdata2") const f32 float_15_8041afb4 = 15.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041afb8 = 0.5f;
__declspec(section ".sdata2") const f32 float_180_8041afbc = 180.0f;
__declspec(section ".sdata2") const f32 float_100_8041afc0 = 100.0f;
__declspec(section ".sdata2") const f32 float_35_8041afc4 = 35.0f;
__declspec(section ".sdata2") const f32 float_16_8041afc8 = 16.0f;
__declspec(section ".sdata2") const f32 float_500_8041afcc = 500.0f;
__declspec(section ".sdata2") const f32 float_90_8041afd0 = 90.0f;
__declspec(section ".sdata2") const f32 float_30_8041afd4 = 30.0f;
__declspec(section ".sdata2") const f32 float_0p67_8041afd8 = 0.67f;
__declspec(section ".sdata2") const f32 float_1E06_8041afdc = 1000000.0f;
__declspec(section ".sdata2") const f32 float_6p2832_8041afe0 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041afe4 = 360.0f;
__declspec(section ".sdata2") const f32 float_neg980_8041afe8 = -980.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041afec = 0.25f;
__declspec(section ".sdata2") const f32 float_neg1000_8041aff0 = -1000.0f;
__declspec(section ".sdata2") const f32 float_0p7_8041aff4 = 0.7f;
__declspec(section ".sdata2") const f32 float_8_8041aff8 = 8.0f;
__declspec(section ".sdata2") const f32 float_1024_8041affc = 1024.0f;
__declspec(section ".sdata2") const f32 float_50_8041b000 = 50.0f;
__declspec(section ".sdata2") const f32 float_62_8041b004 = 62.0f;
__declspec(section ".sdata2") const f32 float_85_8041b008 = 85.0f;
__declspec(section ".sdata2") const f32 float_120_8041b00c = 120.0f;
__declspec(section ".sdata2") const f32 float_12_8041b010 = 12.0f;
__declspec(section ".sdata2") const f32 float_1000_8041b014 = 1000.0f;
#endif


#ifdef NONMATCHING
void itemseq_GetItem(ItemEntry* entry) {
	ItemWork* wp = itemGetWork();
	MarioWork* mario;
	s32 type, bgm;
	s32 select;

	mario = marioGetPtr();
	switch (entry->subState) {
		case 0:
			entry->flags2 &= ~0x10000;
			if (entry->flags & 0x100) {
				entry->flags2 |= 0x4000000;
			}
			else {
				entry->flags2 &= ~0x4000000;
			}
			entry->flags &= ~0x100;
			if (entry->flags & 4) {
				if (itemGetPouch(entry)) {
					entry->timer = 0;
					itemGetSound(entry);
					itemDelete(entry->name);
				}
				else {
					itemModeChange(entry, 4);
				}
				break;
			}
			entry->subState = 1;
			entry->timer = 0;
			camGetPtr(8)->flags |= 0x200;
			marioKeyOff();
			marioStSystemLevel(2);
			psndSetFlag(0x80);
			mario->unk174.x = 0.0f;
			mario->unk174.z = 0.0f;
			mario->baseSpeed = 0.0f;
			*(f32*)mario->unk18C = 0.0f;
			if (entry->itemId == 7 || entry->itemId == 8 || entry->itemId == 10 || entry->itemId == 11) {
				entry->flags2 |= 0x2000;
			}
		case 1:
			if (!(entry->flags & 0x1000) || entry->flags & 0x4000) {
				if (!marioChkItemGetMotion()) {
					if (mario->currMotionId == 5 || (u16)(mario->currMotionId - 6) <= 2 ||
						mario->currMotionId == 0xF || mario->currMotionId == 0xE)
					{
						entry->subState = 8;
					}
					break;
				}
			}
			entry->subState = 2;
			marioChgGetItemMotion();
			{
				f32 y = 50.0f + mario->position.y, z = mario->position.z;
				entry->position.x = mario->position.x;
				entry->position.y = y;
				entry->position.z = z;
			}
			type = 7;
			bgm = -1;
			if (entry->itemId == 0x57) {
				type = 4;
				bgm = -1;
			}
			else if (entry->itemId == 0x7D) {
				type = 8;
				bgm = 0;
			}
			else if (entry->itemId < 0xC) {
				type = 3;
				bgm = 3;
			}
			else if (entry->itemId < 0x72) {
				type = 6;
				bgm = 1;
			}
			else if (entry->itemId < 0x79) {
				type = 0;
				bgm = -1;
			}
			else if (entry->itemId < 0xEC) {
				type = 7;
				bgm = -1;
			}
			else if (entry->itemId < 0x153) {
				type = 5;
				bgm = 2;
			}
			wp->effect = effItemGetEntry(type, mario->position.x, 62.0f + mario->position.y, mario->position.z);
			if (entry->flags2 & 0x2000) {
				((s32*)wp->effect->userdata)[14] = 5;
				iconFlagOn(entry->name, 0x200);
				marioSetCamId(7);
			}
			else {
				((s32*)wp->effect->userdata)[14] = 5;
				iconFlagOn(entry->name, 0x100);
				if (type == 0 || type == 3) {
					marioSetCamId(5);
				}
			}
			if (!(entry->flags & 0x8000)) {
				if (psndBGMChkSilent(0)) {
					entry->flags |= 8;
				}
				switch (bgm) {
					case 0:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_STARPIECE1");
						break;
					case 1:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_KEYITEM1");
						break;
					case 2:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_BADGE1");
						break;
					case 3:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_IMPORTANT_ITEM1");
						break;
					default:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_ITEM1");
						break;
				}
			}
			if (type == 8) {
				evtSetValue(NULL, 0xF5DE01A2, evtGetValue(NULL, 0xF5DE01A2) + 1);
			}
			entry->flags &= ~0x2000;
			itemGetSound(entry);
			entry->winId[0] = winMgrEntry(&itemdrv_window_desc[0]);
			winMgrOpen(entry->winId[0]);
			winMgrSetParam(entry->winId[0], entry);
			if (!(entry->flags2 & 0x2000)) {
				entry->winId[1] = winMgrEntry(&itemdrv_window_desc[1]);
				winMgrOpen(entry->winId[1]);
				winMgrSetParam(entry->winId[1], entry);
			}
			if (!itemGetPouch(entry)) {
				entry->winId[2] = winMgrEntry(&itemdrv_window_desc[2]);
				winMgrOpen(entry->winId[2]);
				winMgrSetParam(entry->winId[2], entry);
			}
			if (entry->itemId == 0x49) {
				iconChange(entry->name, 0x114);
			}
			if (!entry->effect) {
				iconNameToPtr(entry->name)->uflags |= 0x80;
			}
			break;
		case 2:
			if (!(entry->flags2 & 0x2000)) {
				marioCtrlOff();
				entry->flags2 |= 0x1000000;
			}
			entry->subState = 3;
		case 3:
			if (!(entry->flags & 0x8000) && !(entry->flags & 0x2000)) {
				if (psndBGMChk(1)) {
					entry->flags |= 0x2000;
					psndBGMOff(0x201);
					if (!(entry->flags & 8)) {
						psndBGMOn(0xA0, NULL);
					}
				}
			}
			if (winMgrAction(entry->winId[0])) {
				break;
			}
			if (!(keyGetButtonTrg(0) & 0x300)) {
				break;
			}
			winMgrCloseAutoDelete(entry->winId[0]);
			if (!(entry->flags2 & 0x2000)) {
				winMgrCloseAutoDelete(entry->winId[1]);
			}
			if (!(entry->flags & 0x8000) && !(entry->flags & 0x2000)) {
				psndBGMOff(0x201);
				if (!(entry->flags & 8)) {
					psndBGMOn(0xA0, NULL);
				}
			}
			if (entry->flags2 & 0x2000) {
				entry->subState = 6;
				break;
			}
			if (entry->itemId >= 0x79 && entry->itemId < 0xEC && entry->itemId != 0x7D && !swGet(0xEB) && !(gp->flags & 0x1000)) {
				swSet(0xEB);
				entry->subState = 4;
				wp->msgWindowId = msgWindow_Entry(msgSearch("item_first_hit"), 0, 0);
				break;
			}
			effSoftDelete(wp->effect);
			marioSetCamId(4);
			iconFlagOff(entry->name, 0x100);
			if (entry->itemId == 0x49) {
				iconChange(entry->name, 0x115);
			}
			if (!entry->effect) {
				iconNameToPtr(entry->name)->uflags &= ~0x80;
			}
			if (entry->flags2 & 1) {
				itemGetEnd(entry);
				itemDelete(entry->name);
				break;
			}
			entry->subState = 5;
			winMgrCloseAutoDelete(entry->winId[2]);
			marioChgStayMotion();
			iconFlagOn(entry->name, 2);
			{
				s32 id = entry->itemId;
				if (id >= 0xF0 && id < 0x153) {
					wp->select = winMgrSelectEntry(2, id, 1);
				}
				else {
					wp->select = winMgrSelectEntry(1, id, 1);
				}
			}
			break;
		case 4:
			if (windowCheckID(wp->msgWindowId)) {
				break;
			}
			effSoftDelete(wp->effect);
			marioSetCamId(4);
			iconFlagOff(entry->name, 0x100);
			itemGetEnd(entry);
			itemDelete(entry->name);
			break;
		case 5:
			select = winMgrSelect(wp->select);
			if (!select) {
				break;
			}
			winMgrSelectDelete(wp->select);
			if (select < 0) {
				if (entry->flags2 & 0x4000000) {
					entry->flags |= 0x100;
				}
			}
			else {
				pouchRemoveItem(select);
				itemGetPouch(entry);
				entry->flags2 &= ~1;
				entry->itemId = select;
				entry->evtCode = 0;
				entry->evtId = 0;
				entry->flags &= ~0x60;
				iconChange(entry->name, itemDataTable[entry->itemId].icon_id);
				wp->currId++;
				sprintf(iconNameToPtr(entry->name)->name, "_i%05x", wp->currId);
				sprintf(entry->name, "_i%05x", wp->currId);
				entry->flags |= 0x100;
			}
			entry->flags &= ~0x1000;
			entry->speed = 85.0f;
			entry->velocityY = 120.0f;
			entry->bounceFactor = 0.7f;
			entry->gravityScale = 1.0f;
			entry->winId[0] = winMgrEntry(&itemdrv_window_desc[3]);
			winMgrOpen(entry->winId[0]);
			winMgrSetParam(entry->winId[0], entry);
			marioChgGetItemMotion();
			iconFlagOff(entry->name, 2);
			if (mario->flags & 0x2000000) {
				entry->flags2 |= 0x8000;
			}
			entry->subState = 9;
			break;
		case 6:
			wp->lectureEvt = evtEntryType(all_juyoitem_lecture, 0, 0, 0);
			wp->lectureEvt->lwData[8] = (s32)entry;
			wp->lectureEvt->lwData[9] = (s32)wp->effect;
			psndClearFlag(0x80);
			entry->subState = 7;
			break;
		case 7:
			if (evtCheckID(wp->lectureEvt->eventId)) {
				break;
			}
			itemGetEnd(entry);
			itemDelete(entry->name);
			break;
		case 9:
			if (!(keyGetButtonTrg(0) & 0x100)) {
				break;
			}
			winMgrCloseAutoDelete(entry->winId[0]);
			entry->flags2 |= 8;
			itemModeChange(entry, 6);
			entry->flags &= ~0x10;
			if (entry->itemId >= 1 && entry->itemId < 0x79) {
				entry->timer = 0;
			}
			else if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
				entry->timer = 0;
			}
			else {
				entry->timer = 20000;
			}
			entry->flags2 |= 0x10000;
			entry->flags2 &= ~0x1000;
			entry->flags &= ~2;
			itemGetEnd(entry);
			break;
		case 8:
			if (mario->flags & 0x2000000) {
				entry->flags2 |= 0x8000;
			}
			entry->timer = 0;
			if (entry->flags2 & 0x1000) {
				itemModeChange(entry, 1);
				entry->flags2 &= ~4;
				entry->flags2 &= ~8;
				entry->flags2 &= ~0x4000;
				entry->flags2 &= ~0x1000;
				entry->flags &= ~0x1000;
			}
			else {
				entry->speed = 85.0f;
				entry->velocityY = 120.0f;
				entry->bounceFactor = 0.7f;
				entry->gravityScale = 1.0f;
				entry->flags2 |= 8;
				itemModeChange(entry, 6);
				entry->flags &= ~0x10;
				entry->flags2 &= ~0x1000;
				entry->flags &= ~2;
				entry->flags &= ~0x1000;
			}
			marioStSystemLevel(0);
			psndClearFlag(0x80);
			if (entry->flags2 & 0x1000000) {
				entry->flags2 &= ~0x1000000;
				marioCtrlOn();
			}
			marioKeyOn();
			break;
	}
}

static s32 _move_dir_1090;
void itemseq_Bound(ItemEntry* entry) {
	static s32 _move_dir;
	MarioWork* mario;
	CameraEntry* camera;
	HitEntry* hit;
	MapObjectEntry* mobj;
	BOOL isFloor, bounce;
	s64 delta;
	f32 t2sq, dt, dy, t2, dx, t1;
	f32 dz, v, peak, height;
	f32 newX, newZ;
	s32 newDir;
	Vec pos;
	s32 itemId;

	mario = marioGetPtr();
	camera = camGetPtr(4);
	switch (entry->subState) {
		case 0:
			entry->subState = 1;
			entry->airTime = 0;
			entry->baseTime = gp->renderTime;
			entry->curTime = gp->renderTime;
			entry->bounceCount = 0;
			if (entry->flags2 & 0x10) {
				break;
			}
			switch (entry->mode) {
				case 6:
					entry->flags2 |= 4;
				case 5:
					if (!(entry->flags & 0x10)) {
						entry->bounceFactor = 1.0f;
						entry->gravityScale = 1.0f;
						entry->maxBounces = 0;
						entry->velocityY = 500.0f;
					}
					if (!(entry->flags2 & 0x40)) {
						switch (entry->itemId) {
							case 0x79:
							case 0x7B:
							case 0x7C:
								entry->speed = irand(30) + 45;
								if (irand(100) < 50) {
									entry->direction = 90.0f + camera->viewYaw + irand(60) - 30.0f;
								}
								else {
									entry->direction = camera->viewYaw - 90.0f + irand(60) - 30.0f;
								}
								break;
							default:
								entry->speed = 100.0f;
								if (irand(100) < 50) {
									entry->direction = 90.0f + camera->viewYaw + irand(30) - 15.0f;
								}
								else {
									entry->direction = camera->viewYaw - 90.0f + irand(30) - 15.0f;
								}
								break;
						}
					}
					else {
						entry->direction = _move_dir;
						_move_dir += 132;
						if (_move_dir >= 360) {
							_move_dir -= 360;
						}
						entry->speed = 0.67f * (irand(30) + 65);
					}
					break;
				case 4:
					entry->flags2 |= 8;
				case 3:
					if (!(entry->flags & 0x10)) {
						entry->bounceFactor = 1.0f;
						entry->gravityScale = 1.0f;
						entry->maxBounces = 0;
					}
					entry->speed = 0.0f;
					entry->direction = 0;
					entry->velocityY = 0.0f;
					break;
				case 10:
					entry->bounceFactor = 1.0f;
					entry->gravityScale = 1.0f;
					entry->maxBounces = 0;
					entry->velocityY = 500.0f;
					entry->speed = 0.0f;
					entry->direction = 0;
					entry->flags2 |= 0x20;
					entry->flags2 |= 4;
					break;
			}
			break;
		case 1:
			entry->curTime = gp->renderTime;
			delta = entry->curTime - entry->baseTime;
			dt = OSTicksToMicroseconds(delta) / 1000000.0f;
			t1 = OSTicksToMicroseconds(entry->airTime) / 1000000.0f;
			t2 = OSTicksToMicroseconds(entry->airTime + delta) / 1000000.0f;
			dx = dt * (entry->speed * (f32)sin(6.2831855f * entry->direction / 360.0f));
			dz = dt * (entry->speed * -(f32)cos(6.2831855f * entry->direction / 360.0f));
			if (entry->flags2 & 0x8000) {
				dz = 0.0f;
			}
			t2sq = t2 * t2;
			dy = entry->velocityY * dt + (-980.0f * entry->gravityScale) * (t2sq - t1 * t1);
			if (entry->flags2 & 4) {
				if (entry->bounceCount != 0 || dy < 0.0f) {
					entry->flags2 &= ~4;
				}
			}
			if (entry->flags2 & 8 && entry->bounceCount != 0) {
				entry->flags2 &= ~8;
			}
			if (entry->flags2 & 0x20 && dy < 0.0f) {
				effStardustEntry(1, 3, 30, entry->position.x, entry->position.y, entry->position.z, 16.0f, 16.0f);
				itemDelete(entry->name);
				return;
			}
			newDir = entry->direction;
			hit = itemHitCheckSide(entry, &newX, dx, &newZ, dz, &newDir);
			entry->position.x = newX;
			entry->position.z = newZ;
			entry->direction = newDir;
			if (hit) {
				entry->speed *= 0.25f;
			}
			if (!(entry->flags2 & 0x20) && !(entry->flags & 0x800)) {
				hit = itemHitCheckUp(entry, dy);
				if (hit) {
					entry->velocityY = -entry->velocityY * 0.25f;
					dy = 0.0f;
					entry->airTime = 0;
					entry->baseTime = entry->curTime;
				}
			}
			if (entry->flags2 & 0x100000 && entry->position.y <= -1000.0f) {
				itemModeChange(entry, 7);
				entry->flags2 &= ~4;
				entry->flags2 &= ~8;
				entry->flags2 &= ~0x4000;
				if (entry->itemId >= 1 && entry->itemId < 0x79) {
					entry->timer = 0;
				}
				else if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
					entry->timer = 0;
				}
				else {
					entry->timer = 20000;
				}
				entry->flags2 |= 0x10000;
				entry->flags2 &= ~0x1000;
				entry->flags |= 0x100;
				break;
			}
			if (dy >= 0.0f) {
				hit = NULL;
				entry->position.y += dy;
			}
			else if (entry->flags2 & 0x100000) {
				hit = NULL;
				entry->position.y += dy;
			}
			else {
				hit = itemHitCheckY(entry, entry->position.z, 20.0f + entry->position.y, entry->position.x, dy);
			}
			if (hit) {
				if (hitGetAttr(hit) & 0x600) {
					entry->flags2 |= 0x100000;
					{
						Vec sndPos = (Vec){0.0f, 0.0f, 0.0f};
						sndPos.x = entry->position.x;
						sndPos.y = entry->position.y;
						sndPos.z = entry->position.z;
						psndSFXOn_3D((const char*)0x194, &sndPos);
					}
					effSplashEntry(0, entry->position.x, entry->position.y, entry->position.z, 0.7f);
					entry->flags |= 2;
				}
				else {
					entry->bounceCount++;
					if (!(hitGetAttr(hit) & 0x80000000) && entry->maxBounces != 0 && entry->bounceCount >= entry->maxBounces) {
						itemModeChange(entry, 1);
						entry->flags2 &= ~4;
						entry->flags2 &= ~8;
						entry->flags2 &= ~0x4000;
						break;
					}
					{
					pos = (Vec){entry->position.x, entry->position.y, entry->position.z};
					switch (itemId = entry->itemId) {
						case 0x79:
							psndSFXOn_3D("SFX_COIN_LEAPED1", &pos);
							break;
						case 0x7A:
							psndSFXOn_3D("SFX_EVT_GAME_MONTE_LEAPED1", &pos);
							break;
						case 0x7B:
							psndSFXOn_3D("SFX_HEART_LEAPED1", &pos);
							break;
						case 0x7C:
							psndSFXOn_3D("SFX_FLOWER_LEAPED1", &pos);
							break;
						case 0x7D:
							psndSFXOn_3D("SFX_STAR_PIECE_LEAPED1", &pos);
							break;
						case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
							psndSFXOn_3D("SFX_EVT_STARSTONE_JUMP1", &pos);
							break;
						default:
							if (itemId >= 0xF0 && itemId < 0x153) {
								psndSFXOn_3D("SFX_BADGE_LEAPED1", &pos);
							}
							else {
								psndSFXOn_3D("SFX_ITEM_LEAPED1", &pos);
							}
							break;
					}
					}
					isFloor = FALSE;
					if (entry->flags & 0x80 && entry->velocityY != 0.0f) {
						bounce = TRUE;
					}
					else if (hitGetAttr(hit) & 0x80000000 && entry->velocityY != 0.0f) {
						mobj = mobjHitObjPtrToPtr(hit);
						if (mario->characterId == 2) {
							bounce = FALSE;
						}
						else if (mobj && strcmp(mobj->animName, "MOBJ_KururinFloor")) {
							bounce = TRUE;
							isFloor = TRUE;
						}
						else {
							goto no_bounce;
						}
					}
					else {
					no_bounce:
						bounce = FALSE;
					}
					if (!bounce) {
						v = entry->velocityY * dt + (-980.0f * entry->gravityScale) * ((t2 + dt) * (t2 + dt) - t2sq);
						entry->velocityY = 0.7f * (entry->bounceFactor * (-v / dt));
					}
					peak = __fabs(0.5f * (entry->velocityY / (-980.0f * entry->gravityScale)));
					height = entry->velocityY * peak + peak * ((-980.0f * entry->gravityScale) * peak);
					if (!isFloor && height <= 8.0f) {
						itemModeChange(entry, 1);
						entry->flags2 &= ~4;
						entry->flags2 &= ~8;
						entry->flags2 &= ~0x4000;
					}
					if (entry->flags & 0x200 && entry->bounceCount <= 1) {
						entry->direction = entry->savedDirection;
						entry->speed = entry->savedSpeed;
						entry->flags &= ~0x200;
					}
					entry->airTime = 0;
					entry->baseTime = gp->renderTime;
					break;
				}
			}
			entry->airTime += delta;
			entry->baseTime = entry->curTime;
			break;
	}
	entry->flags2 &= ~0x10;
}

void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z) {
	entry->position.x = x;
	entry->position.y = y;
	entry->position.z = z;
}





void itemGetSound(ItemEntry* entry) {
	Vec pos;

	pos = (Vec){entry->position.x, entry->position.y, entry->position.z};
	switch (entry->itemId) {
		case 0x79:
			effStardustEntry(1, 3, 30, entry->position.x, 35.0f + entry->position.y, entry->position.z, 16.0f, 16.0f);
			psndSFXOn_3D("SFX_COIN_GET1", &pos);
			break;
		case 0x7A:
			effStardustEntry(1, 3, 30, entry->position.x, 35.0f + entry->position.y, entry->position.z, 16.0f, 16.0f);
			psndSFXOn_3D("SFX_EVT_GAME_MONTE_COUNT1", &pos);
			break;
		case 0x7B:
			psndSFXOn_3D("SFX_HEART_GET1", &pos);
			break;
		case 0x7C:
			psndSFXOn_3D("SFX_FLOWER_GET1", &pos);
			break;
		case 0x7D:
			break;
	}
}

HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle) {
	HitEntry* hit;
	f32 a, b;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	f32 sin, cos;
	f32 dot, ox, oz;

	*outX = entry->position.x;
	*outZ = entry->position.z;
	if (dx == 0.0f && dz == 0.0f) {
		return NULL;
	}
	sincosf(&sin, &cos, angleABf(0.0f, 0.0f, dx, dz));
	hitDist = 10.0f + item_sqrtf(dx * dx + dz * dz);
	hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ,
		entry->position.x, 15.0f + entry->position.y, entry->position.z, sin, 0.0f, cos);
	if (hit) {
		dot = dx * hitNX + dz * hitNZ;
		ox = 0.5f * (dx - dot * hitNX);
		oz = 0.5f * (dz - dot * hitNZ);
		*outX += ox;
		*outZ += oz;
		a = reviseAngle(180.0f + *angle);
		b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * hitNX, 100.0f * hitNZ));
		*angle = reviseAngle(b + reviseAngle(b - a));
		return hit;
	}
	hitDist = 10.0f + item_sqrtf(dx * dx + dz * dz);
	hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ,
		entry->position.x, 15.0f + entry->position.y, entry->position.z, sin, 0.0f, cos);
	if (hit) {
		dot = dx * hitNX + dz * hitNZ;
		ox = 0.5f * (dx - dot * hitNX);
		oz = 0.5f * (dz - dot * hitNZ);
		*outX += ox;
		*outZ += oz;
		a = reviseAngle(180.0f + *angle);
		b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * hitNX, 100.0f * hitNZ));
		*angle = reviseAngle(b + reviseAngle(b - a));
		return hit;
	}
	*outX += dx;
	*outZ += dz;
	return NULL;
}

HitEntry*
itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy) {
	HitEntry* hit;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;

	hitDist = 20.0f + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, -1.0f, 0.0f)) {
		entry->position.y = hitY;
	}
	else {
		hit = NULL;
		entry->position.y += vy;
	}
	return hit;
}

HitEntry*
itemHitCheckUp(ItemEntry* entry, f32 vy) {
	HitEntry* hit;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	f32 x, y, z;

	if (vy <= 0.0f) {
		return NULL;
	}
	x = entry->position.x; y = 20.0f + entry->position.y; z = entry->position.z;
	hitDist = 20.0f + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
		entry->position.y = hitY - 20.0f - 4.0f;
		return hit;
	}
	x = entry->position.x; y = entry->position.y; z = entry->position.z;
	hitDist = 20.0f + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
		entry->position.y = hitY - 20.0f;
		return hit;
	}
	return NULL;
}

void itemForceGet(ItemEntry* entry) {
	entry->timer = 0;
	itemModeChange(entry, 2);
	entry->flags |= 0x1000;
	entry->flags2 &= ~0x10000;
}

void itemNokoForceGet(ItemEntry* entry) {
	if (itemGetNokoCheck(entry)) {
		entry->timer = 0;
		itemModeChange(entry, 2);
		entry->flags |= 0x5000;
		entry->flags2 &= ~0x10000;
	}
	else {
		entry->timer = 0;
		itemModeChange(entry, 1);
		entry->flags2 &= ~4;
		entry->flags2 &= ~8;
		entry->flags2 &= ~0x4000;
		entry->flags2 &= ~0x1000;
	}
}

void itemFlagOn(ItemEntry* entry, u16 flags) {
	entry->flags |= flags;
}

void itemFlagOff(ItemEntry* entry, u16 flags) {
	entry->flags &= ~flags;
}

u16 itemFlag(ItemEntry* entry, u16 flags) {
	return entry->flags & flags;
}

void itemStatusOn(ItemEntry* entry, u32 flags) {
	entry->flags2 |= flags;
}

u32 itemStatus(ItemEntry* entry, u32 flags) {
	return entry->flags2 & flags;
}

void itemPickUp(ItemEntry* entry) {
	entry->flags2 |= 0x1000;
	itemModeChange(entry, 8);
	entry->timer = 0;
	entry->flags2 &= ~0x100;
}


// prototypes for asm stopgap forward references
void itemPickUp(ItemEntry* entry);
u32 itemStatus(ItemEntry* entry, u32 flags);
void itemStatusOn(ItemEntry* entry, u32 flags);
u16 itemFlag(ItemEntry* entry, u16 flags);
void itemFlagOff(ItemEntry* entry, u16 flags);
void itemFlagOn(ItemEntry* entry, u16 flags);
void itemNokoForceGet(ItemEntry* entry);
void itemForceGet(ItemEntry* entry);
HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);
void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z);
void itemseq_Bound(ItemEntry* entry);
void itemseq_GetItem(ItemEntry* entry);
void winFullDisp(WinMgrEntry* win);
void winHelpDisp(WinMgrEntry* win);
void winHelpMain(WinMgrEntry* win);
void winNameDisp2(WinMgrEntry* win);
void winNameDisp(WinMgrEntry* win);
ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemNameToPtr(char* name);
void itemDelete(const char* name);
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);
void itemModeChange(ItemEntry* entry, s32 mode);
void itemMain(void);
BOOL N_itemPickUpFromFieldCheck(void);
BOOL itemGetNokoCheck(ItemEntry* entry);
BOOL itemGetCheck(ItemEntry* entry);
void itemCoinDrop(Vec* position);
void itemReInit(void);
void itemInit(void);

#endif