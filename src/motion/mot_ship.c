#include "dolphin/types.h"
#include "evt/evt_cmd.h"
#include "evt/evt_snd.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_sbr.h"
#include "memory.h"
#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "manager/evtmgr.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#include "mario/mariost.h"
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f64 double_to_int_802c5e50;
__declspec(section ".sdata2") extern const f32 float_40_8041ad98;
__declspec(section ".sdata2") extern const f32 float_20_8041ad9c;
__declspec(section ".sdata2") extern const f32 float_0_8041ada0;
__declspec(section ".sdata2") extern const f32 float_neg1_8041ada4;
__declspec(section ".sdata2") extern const f32 float_0p5_8041ada8;
__declspec(section ".sdata2") extern const f32 float_100_8041adac;
__declspec(section ".sdata2") extern const f32 float_90_8041adb0;
__declspec(section ".sdata2") extern const f32 float_15_8041adb4;
__declspec(section ".sdata2") extern const f32 float_50_8041adb8;
__declspec(section ".sdata2") extern const f32 float_30p303_8041adbc;
__declspec(section ".sdata2") extern const f32 float_180_8041adc0;
__declspec(section ".sdata2") extern const f32 float_3p1416_8041adc4;
__declspec(section ".sdata2") extern const f32 float_1_8041adc8;
__declspec(section ".sdata2") extern const f32 float_0p01_8041adcc;
__declspec(section ".sdata2") extern const f32 float_0p2_8041add0;
__declspec(section ".sdata2") extern const f32 float_neg0p1_8041add4;
__declspec(section ".sdata2") extern const f32 float_neg0p2_8041add8;
__declspec(section ".sdata2") extern const f32 float_0p024_8041addc;
__declspec(section ".sdata2") extern const f32 float_neg0p004_8041ade0;
__declspec(section ".sdata2") extern const f32 float_4p25_8041ade4;
__declspec(section ".sdata2") extern const f32 float_30_8041ade8;
__declspec(section ".sdata2") extern const f32 float_neg30_8041adec;
__declspec(section ".sdata2") extern const f32 float_0p125_8041adf0;
__declspec(section ".sdata2") extern const f32 float_270_8041adf4;
__declspec(section ".sdata2") extern const f32 float_neg270_8041adf8;
__declspec(section ".sdata2") extern const char str_8041ADFC[];
__declspec(section ".sdata2") extern const f32 float_1024_8041ae04;
__declspec(section ".sdata2") extern const f32 float_1260_8041ae08;
__declspec(section ".sdata2") extern const f32 float_neg1080_8041ae0c;
__declspec(section ".sdata2") extern const f32 float_neg15_8041ae10;
__declspec(section ".sdata2") extern const f32 float_0p1_8041ae14;
__declspec(section ".sdata2") extern const f32 float_1620_8041ae18;
__declspec(section ".sdata2") extern const f32 float_neg1440_8041ae1c;
__declspec(section ".sdata2") extern const f32 float_36_8041ae20;
__declspec(section ".sdata2") extern const f32 float_306_8041ae24;
__declspec(section ".sdata2") extern const f32 float_neg0p4_8041ae28;
__declspec(section ".sdata2") extern const f32 float_neg18_8041ae2c;
__declspec(section ".sdata2") extern const f32 float_1p6_8041ae30;
__declspec(section ".sdata2") extern const f32 float_2p8_8041ae34;
__declspec(section ".sdata2") extern const f32 float_10_8041ae38;
__declspec(section ".sdata2") extern const f32 float_2_8041ae3c;
__declspec(section ".sdata2") extern const f32 float_80_8041ae40;
__declspec(section ".sdata2") extern const f32 float_neg20_8041ae44;
__declspec(section ".sdata2") extern const f32 float_360_8041ae48;
__declspec(section ".sdata2") extern const f32 float_0p05_8041ae4c;
__declspec(section ".sdata2") extern const f32 float_neg0p005_8041ae50;
__declspec(section ".sdata2") extern const f32 float_neg360_8041ae54;
__declspec(section ".sdata2") extern const f32 float_4_8041ae58;
__declspec(section ".sdata2") extern const f32 float_neg4_8041ae5c;
__declspec(section ".sdata2") extern const f32 float_540_8041ae60;
__declspec(section ".sdata2") extern const f32 float_37_8041ae64;
__declspec(section ".sdata2") extern const f32 float_neg13_8041ae68;
__declspec(section ".sdata2") extern const f32 float_3_8041ae6c;
__declspec(section ".sdata2") extern const f32 float_0p3_8041ae70;
__declspec(section ".sdata2") extern const f32 float_0p6_8041ae74;
__declspec(section ".sdata2") extern const f32 float_neg7_8041ae78;
__declspec(section ".sdata2") extern const f32 float_260_8041ae7c;
#define EXT_LIT(sym, val) (sym)

#endif
extern const char str_802C5E00[];
extern const char str_802C5E14[];
extern const char str_802C5E24[];
extern const char str_802C5E2C[];
extern const char str_802C5E38[];
extern const char str_802C5E44[];
extern const char str_802C5E58[];
extern const char str_802C5E60[];
extern const char str_802C5E68[];
extern const char str_802C5E70[];

typedef struct ShipWork {
	u32 flags; // 0x0
	u8 pad4[0x28 - 4];
	f32 swirlY; // 0x28
	f32 swirlX; // 0x2C
	s32 swirlTime; // 0x30
} ShipWork;

typedef struct ShipDir {
	u32 flags;
	u8 pad4[0x14 - 4];
	f32 dispX; // 0x14
	f32 dispY; // 0x18
} ShipDir;

static EVT_BEGIN(sound_evt)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E00), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E00), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E00), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E00), LW(0), LW(1), LW(2), 0)
RETURN
EVT_END()

EVT_BEGIN(sound_evt2)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E14), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E14), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E14), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING((char*)str_802C5E14), LW(0), LW(1), LW(2), 0)
RETURN
EVT_END()

#ifdef NONMATCHING
f32 shipData[6] = {-0.05f, -0.7f, 0.02f, 0.02f, 2.0f, 0.01f};
const char* paper_ship[4] = {(char*)str_802C5E24, (char*)str_802C5E2C, (char*)str_802C5E38, (char*)str_802C5E44};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") f32 shipData[6] = {-0.05f, -0.7f, 0.02f, 0.02f, 2.0f, 0.01f};
__declspec(section ".sdata") const char* paper_ship[4] = {(char*)str_802C5E24, (char*)str_802C5E2C, (char*)str_802C5E38, (char*)str_802C5E44};
#endif

void sincosf(f32* s, f32* c, f32 a);

static inline s32 harborKind(HitEntry* hit) {
	s32 k = 0;
	s32 attr = hitGetAttr(hit);
	if (attr & 0x4000) {
		k = 1;
	} else if (attr & 0x8000) {
		k = 2;
	} else if (attr & 0x10000) {
		k = 3;
	} else if (attr & 0x20000) {
		k = 4;
	}
	return k;
}

#define HARBOR_PROBE(ANG, POS)  sincosf(&sn, &cs, toMovedir(ANG)); tx = 40.0f * sn + m->position.x; tz = 40.0f * cs + m->position.z; ty = 20.0f + m->position.y; dist = 40.0f; hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, tx, ty, tz, 0.0f, -1.0f, 0.0f); if (hit != NULL && harborKind(hit) != 0) { hitObjGetPos(hitGetName(hit), &POS); ix = (s32)((100.0f * POS.x + 0.5f) / 100.0f); iy = (s32)((100.0f * POS.y + 0.5f) / 100.0f); iz = (s32)((100.0f * POS.z + 0.5f) / 100.0f); out->x = ix; out->y = iy; out->z = iz; return TRUE; }

BOOL checkHarbor(Vec* out);

#define MSF(m, o) (*(f32*)((u8*)(m) + (o)))
#define MSI(m, o) (*(s32*)((u8*)(m) + (o)))
#define MSP(m, o) (*(void**)((u8*)(m) + (o)))
#define MSO(o) (*(s32*)((u8*)marioGetPtr()->motStruct + (o)))
#define MSOF(o) (*(f32*)((u8*)marioGetPtr()->motStruct + (o)))

void allPartyRideOff(void);
void allPartyForceRideOn(void);
void* effFunemizuEntry(s32, f32, f32, f32, f32, f32);

void marioPreJump(void);
void allPartyRideShip(void);
void marioSetFallPara(void);
void marioClearJumpPara(void);
void N_marioReloadMapOnBottomlessOff(void);

f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
void movePos(float* ret_sin, float* ret_cos, f32 a3, f32 degree);
double __fabs(double);
void marioMakeJumpPara();
void N_marioSetBottomlessRespawnPosOnBeroEntry();
s32 marioChkLandon(f32, f32*);

#define MS_ARM() (*(f32*)((u8*)marioGetPtr()->motStruct + 0x1c))
#define SHIP_DIR (MSI(marioGetPtr()->motStruct, 0) & 1)

void marioCheckWallShip(f32, f32);
void marioPaperOff(void);
double sin(double);
double cos(double);
void shipMove(void);
#define EFFP() (*(void**)((u8*)*(void**)((u8*)marioGetPtr()->motStruct + 0x24) + 0xC))
#ifdef NONMATCHING
#define SHIP_EFF()                                                                                                 \
	{                                                                                                              \
		f30 = MSF(m, 0x180);                                                                                       \
		{                                                                                                          \
			MarioWork* mm = marioGetPtr();                                                                         \
			f32 zz = 0.0f;                                                                                         \
			if (0.0f == f30) {                                                                                     \
				s32 c;                                                                                             \
				marioGetPtr();                                                                                     \
				c = (MSOF(8) > 180.0f) ? 0 : 1;                                                                    \
				f30 = c ? 0.3f : 0.6f;                                                                             \
				{                                                                                                  \
					f32* ms = (f32*)marioGetPtr()->motStruct;                                                      \
					f32 old = ms[4];                                                                               \
					ms[4] = old + 0.1f * (f30 - MSOF(0x10));                                                       \
				}                                                                                                  \
				f30 = MSOF(0x10);                                                                                  \
			}                                                                                                      \
			f31 = mm->position.x;                                                                                  \
			MSF(EFFP(), 4) = f31;                                                                                  \
			f31 = mm->position.y + zz;                                                                           \
			MSF(EFFP(), 8) = f31;                                                                                  \
			f31 = mm->position.z;                                                                                  \
			MSF(EFFP(), 0xc) = f31;                                                                                \
			MSF(EFFP(), 0x10) = f30;                                                                               \
			f31 = MSF(mm, 0x1a8);                                                                                  \
			MSF(EFFP(), 0x14) = f31;                                                                               \
		}                                                                                                          \
	}
#endif
#ifndef NONMATCHING
#define SHIP_EFF()                                                                                                 \
	{                                                                                                              \
		f30 = MSF(m, 0x180);                                                                                       \
		{                                                                                                          \
			MarioWork* mm = marioGetPtr();                                                                         \
			f32 zz = EXT_LIT(float_0_8041ada0, 0.0f);                                                                                         \
			if (EXT_LIT(float_0_8041ada0, 0.0f) == f30) {                                                                                     \
				s32 c;                                                                                             \
				marioGetPtr();                                                                                     \
				c = (MSOF(8) > EXT_LIT(float_180_8041adc0, 180.0f)) ? 0 : 1;                                                                    \
				f30 = c ? EXT_LIT(float_0p3_8041ae70, 0.3f) : EXT_LIT(float_0p6_8041ae74, 0.6f);                                                                             \
				{                                                                                                  \
					f32* ms = (f32*)marioGetPtr()->motStruct;                                                      \
					f32 old = ms[4];                                                                               \
					ms[4] = old + EXT_LIT(float_0p1_8041ae14, 0.1f) * (f30 - MSOF(0x10));                                                       \
				}                                                                                                  \
				f30 = MSOF(0x10);                                                                                  \
			}                                                                                                      \
			f31 = mm->position.x;                                                                                  \
			MSF(EFFP(), 4) = f31;                                                                                  \
			f31 = mm->position.y + zz;                                                                           \
			MSF(EFFP(), 8) = f31;                                                                                  \
			f31 = mm->position.z;                                                                                  \
			MSF(EFFP(), 0xc) = f31;                                                                                \
			MSF(EFFP(), 0x10) = f30;                                                                               \
			f31 = MSF(mm, 0x1a8);                                                                                  \
			MSF(EFFP(), 0x14) = f31;                                                                               \
		}                                                                                                          \
	}
#endif

s32 N_marioShipGetDir(void) {
	marioGetPtr();
	if (marioGetPtr()->motStruct != NULL) {
		return (((ShipDir*)marioGetPtr()->motStruct)->flags >> 1) & 1;
	}
	return 0;
}

s32 marioShipChanging(void) {
	MarioWork* m = marioGetPtr();
	if (m->currMotionId != MARIO_MOTION_SHIP) {
		return 0;
	}
	if ((s32)m->currSubMotionId == 10) {
		return 2;
	}
	if ((s32)m->currSubMotionId >= 0 && (s32)m->currSubMotionId <= 12 || (s32)m->currSubMotionId >= 30 && (s32)m->currSubMotionId <= 48) {
		return 1;
	}
	if ((s32)m->currSubMotionId == 50 || (s32)m->currSubMotionId == 52) {
		return 3;
	}
	return 0;
}

void marioSetSwirlPower(s32 msec, f32 a, f32 b) {
	s32 t;
	marioGetPtr();
	t = sysMsec2Frame(msec);
	((ShipWork*)marioGetPtr()->motStruct)->swirlTime = t;
	((ShipWork*)marioGetPtr()->motStruct)->swirlX = a;
	((ShipWork*)marioGetPtr()->motStruct)->swirlY = b;
}

BOOL marioChkSwirlPower(void) {
	marioGetPtr();
	return ((ShipWork*)marioGetPtr()->motStruct)->swirlTime != 0;
}

#ifndef NONMATCHING
void *memset(void *dest, int ch, size_t count);
int psndSFX_pos();
int strcmp(const char *s1, const char *s2);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void marioShipForceStop(void) {
#ifdef NONMATCHING
	f32 a = 0.0f;
	f32 b;
	marioGetPtr();
	b = 0.0f;
	((ShipDir*)marioGetPtr()->motStruct)->dispX = a;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = b;
#endif
#ifndef NONMATCHING
	asm volatile {
		bl marioGetPtr
		lfs f30, float_0_8041ada0(r2)
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041ada0(r2)
		opword 0xD3C30014
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30018
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void marioShipSetDispDir(void) {
#ifdef NONMATCHING
	f32 a = 0.0f;
	f32 b;
	marioGetPtr();
	b = 0.0f;
	((ShipDir*)marioGetPtr()->motStruct)->dispX = a;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = b;
#endif
#ifndef NONMATCHING
	asm volatile {
		bl marioGetPtr
		lfs f30, float_0_8041ada0(r2)
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041ada0(r2)
		opword 0xD3C30014
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30018
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

BOOL marioChkShipPlace(HitEntry* hit) {
	return (hitGetAttr(hit) & 0x3C000) != 0;
}

void marioForceShipAnime(void) {
	MarioWork* m = marioGetPtr();
	marioPaperOff();
	marioChgPaper(NULL);
	marioPaperOn(paper_ship[marioGetColor()]);
	marioChgPaper((char*)str_802C5E70);
#ifdef NONMATCHING
	marioChgPose("M_Z_1");
#endif
#ifndef NONMATCHING
	marioChgPose(EXT_LIT((char*)str_8041ADFC, "M_Z_1"));
#endif
	m->dispFlags |= 8;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void marioReInit_ship(void) {
#ifdef NONMATCHING
	MarioWork* m = marioGetPtr();
	void* p;
	s32 t, u;
	f32 a, b;
	m->trigFlags &= ~1;
	p = __memAlloc(HEAP_DEFAULT, 0x48);
	marioGetPtr()->motStruct = p;
	memset(marioGetPtr()->motStruct, 0, 0x48);
	*(s16*)((u8*)m + 0x2E) = 0x19;
	m->dispOfs.y = -15.0f;
	MSI(m, 0x44) = 0x32;
	m->wPlayerCollisionBox.x = 40.0f;
	m->wPlayerCollisionBox.y = 40.0f;
	marioPaperOn(paper_ship[marioGetColor()]);
	marioChgPaper((char*)str_802C5E70);
	marioChgPose("M_Z_1");
	m->dispFlags |= 8;
	MSI(m, 0x2A4) = 0x58;
	marioSetPaperAnimeLocalTime(MSI(m, 0x2A4));
	t = -1;
	MSO(0x38) = t;
	u = 0;
	MSO(0) = u;
	a = 0.0f;
	MSOF(4) = a;
	b = 0.0f;
	MSOF(0x14) = b;
	a = 0.0f;
	MSOF(0x18) = a;
	b = 0.0f;
	MSOF(0x1C) = b;
	a = 0.0f;
	MSOF(0x20) = a;
	b = 0.0f;
	MSOF(8) = b;
	a = 4.25f;
	MSOF(0xC) = a;
	t = (s32)effFunemizuEntry(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	MSO(0x24) = t;
	u = m->camId;
	*(s32*)((u8*)*(void**)((u8*)*(void**)((u8*)marioGetPtr()->motStruct + 0x24) + 0xC) + 0x48) = u;
	allPartyForceRideOn();
#endif
#ifndef NONMATCHING
	asm volatile {
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0x38600000
		opword 0x801F000C
		opword 0x38800048
		opword 0x5400003C
		opword 0x901F000C
		bl __memAlloc
		opword 0x7C7D1B78
		bl marioGetPtr
		opword 0x93A30288
		bl marioGetPtr
		opword 0x80630288
		opword 0x38800000
		opword 0x38A00048
		bl memset
		opword 0x38000019
		lfs f1, float_neg15_8041ae10(r2)
		opword 0xB01F002E
		opword 0x38000032
		lfs f0, float_40_8041ad98(r2)
		opword 0xD03F009C
		opword 0x901F0044
		opword 0xD01F01B4
		opword 0xD01F01B8
		bl marioGetColor
		opword 0x5460103A
		la r3, paper_ship(r13)
		opword 0x7C63002E
		bl marioPaperOn
		lis r3, str_802C5E60@ha
		addi r3, r3, str_802C5E60@l
		bl marioChgPaper
		la r3, str_8041ADFC(r2)
		bl marioChgPose
		opword 0x807F0004
		opword 0x38000058
		opword 0x60630008
		opword 0x907F0004
		opword 0x901F02A4
		opword 0x807F02A4
		bl marioSetPaperAnimeLocalTime
		li r29, -0x1
		bl marioGetPtr
		opword 0x80630288
		opword 0x3BC00000
		opword 0x93A30038
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041ada0(r2)
		opword 0x93C30000
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_0_8041ada0(r2)
		opword 0xD3E30004
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041ada0(r2)
		opword 0xD3C30014
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_0_8041ada0(r2)
		opword 0xD3E30018
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041ada0(r2)
		opword 0xD3C3001C
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_0_8041ada0(r2)
		opword 0xD3E30020
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_4p25_8041ade4(r2)
		opword 0xD3C30008
		bl marioGetPtr
		lfs f1, float_0_8041ada0(r2)
		opword 0x80830288
		opword 0x38600000
		opword 0xFC400890
		opword 0xFC600890
		opword 0xD3E4000C
		opword 0xFC800890
		opword 0xFCA00890
		bl effFunemizuEntry
		opword 0x7C7E1B78
		bl marioGetPtr
		opword 0x80630288
		opword 0x93C30024
		opword 0x83FF0134
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0x93E30048
		bl allPartyForceRideOn
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void mot_ship_post(void) {
	MarioWork* m = marioGetPtr();
	s32 t;
	allPartyRideOff();
	if (m->dispFlags & 0x40000000) {
		marioPaperOff();
	}
#ifdef NONMATCHING
	m->wPlayerCollisionBox.x = 20.0f;
	m->wPlayerCollisionBox.y = 37.0f;
#endif
#ifndef NONMATCHING
	m->wPlayerCollisionBox.x = EXT_LIT(float_20_8041ad9c, 20.0f);
	m->wPlayerCollisionBox.y = EXT_LIT(float_37_8041ae64, 37.0f);
#endif
	marioGetPtr();
	if (marioGetPtr()->motStruct != NULL) {
		if ((u32)MSO(0x38) != 0xFFFFFFFFU) {
			psndSFXOff(MSO(0x38));
			t = -1;
			MSO(0x38) = t;
		}
	}
	m->dispFlags &= ~4;
	m->dispFlags &= ~0x100;
	m->dispFlags &= ~8;
	marioOfsRotReset();
	if (marioGetPtr()->motStruct != NULL) {
		__memFree(HEAP_DEFAULT, marioGetPtr()->motStruct);
		t = 0;
		marioGetPtr()->motStruct = (void*)t;
	}
}

#ifndef NONMATCHING
void mot_ship(void);
__declspec(section ".data") static void* jumptable_8030ECF8[] = {
    (char*)mot_ship + 0x108,
    (char*)mot_ship + 0x26C,
    (char*)mot_ship + 0x480,
    (char*)mot_ship + 0x558,
    (char*)mot_ship + 0x5C8,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x6EC,
    (char*)mot_ship + 0x9FC,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0xBF0,
    (char*)mot_ship + 0xC18,
    (char*)mot_ship + 0xCD8,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0xCF0,
    (char*)mot_ship + 0xEB0,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0xFDC,
    (char*)mot_ship + 0x10FC,
    (char*)mot_ship + 0x119C,
    (char*)mot_ship + 0x1264,
    (char*)mot_ship + 0x13D8,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x158C,
    (char*)mot_ship + 0x1A80,
    (char*)mot_ship + 0x1594,
};
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void mot_ship(void) {
#ifdef NONMATCHING
	MarioWork* m = marioGetPtr();
	MarioWork* m2;
	s32 r29, r27;
	f32 f30, f31;
	Vec pos;
	Vec p1, p2;

	if (m->trigFlags & 1) {
		m->trigFlags &= ~1;
		MSI(m, 0) &= ~0xF0000;
		m2 = (MarioWork*)__memAlloc(0, 0x48);
		marioGetPtr()->motStruct = m2;
		memset(marioGetPtr()->motStruct, 0, 0x48);
		m2 = (MarioWork*)-1;
		MSO(0x38) = (s32)m2;
		MSOF(0x20) = 0.0f;
		MSOF(8) = 0.0f;
		MSOF(0xC) = 4.25f;
		m->currSubMotionId = 0;
		if (!(m->trigFlags & 4)) {
			camGetPtr(8)->flags |= 0x200;
		}
	}
	switch (m->currSubMotionId) {
	case 0:
		psndSFXOn_3D((const char*)0x18d, &m->position);
		psndSFXOn_3D((const char*)0xaf, &m->position);
		marioCamZoomUp();
		marioPreJump();
		marioChgPose((char*)str_802C5E58);
		camFollowYOff();
		m->dispFlags |= 0x100;
		MSI(m, 0x48) = 0;
		m->currSubMotionId = 1;
		*(s16*)((u8*)m + 0x50) = 0;
		*(s16*)((u8*)m + 0x52) = 0;
		m->baseSpeed = 0.0f;
		MSOF(0x1c) = 0.0f;
		N_marioSetBottomlessRespawnPosOnBeroEntry(m->position.x, m->position.y, m->position.z);
		{
			HitEntry* hit = (HitEntry*)MSP(m, 0x1E8);
			s32 attr;
			m2 = marioGetPtr();
			attr = hitGetAttr(hit);
			r29 = 0;
			if (attr & 0x4000) {
				hitObjGetPos(hitGetName((HitEntry*)MSP(m2, 0x1E8)), &p1);
				f30 = revise360(angleABf(m2->position.x, m2->position.z, p1.x, p1.z) - m2->targetYaw);
				r29 = (f30 >= 180.0f) ? 2 : 1;
			} else if (attr & 0x8000) {
				hitObjGetPos(hitGetName((HitEntry*)MSP(m2, 0x1E8)), &p2);
				f30 = revise360(angleABf(m2->position.x, m2->position.z, p2.x, p2.z) - m2->targetYaw);
				r29 = (f30 >= 180.0f) ? 2 : 1;
			} else if (attr & 0x10000) {
				r29 = 2;
			} else if (attr & 0x20000) {
				r29 = 1;
			}
			MSO(0) = r29;
		}
		/* fallthrough */
	case 1:
		marioMakeJumpPara();
		f31 = SHIP_DIR ? 30.0f : -30.0f;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.125f * (f31 - MS_ARM());
		}
		if (SHIP_DIR) {
			f30 = 30.0f;
			if (MS_ARM() >= f30) {
				MS_ARM() = f30;
			}
		} else {
			f30 = -30.0f;
			if (MS_ARM() <= f30) {
				MS_ARM() = f30;
			}
		}
		m->displayDirection += MS_ARM();
		r27 = 0;
		if (SHIP_DIR) {
			if (m->displayDirection >= 270.0f) {
				r27 = 1;
			}
		} else {
			if (m->displayDirection <= -270.0f) {
				r27 = 1;
			}
		}
		if (r27) {
			m->currSubMotionId = 2;
			MSI(m, 0x48) = 20;
			marioPaperOn(paper_ship[marioGetColor()]);
			marioChgPaper((char*)str_802C5E60);
			marioChgPose("M_Z_1");
			f30 = 15.0f;
			m->dispFlags |= 8;
			MSOF(0x20) = f30;
			{
				void* e = evtEntry(sound_evt, 0, 0);
				MSI(e, 0x9c) = (s32)(1024.0f * m->position.x) - 230000000;
				MSI(e, 0xa0) = (s32)(1024.0f * m->position.y) - 230000000;
				MSI(e, 0xa4) = (s32)(1024.0f * m->position.z) - 230000000;
			}
		}
		if (m->jumpVelocityY > 0.0f) {
			m->position.y += m->jumpVelocityY;
			MSI(m, 0) &= ~0xF0000;
		}
		break;
	case 2:
		f30 = SHIP_DIR ? 1.0f : -1.0f;
		f31 = MSOF(0x20) * f30;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.125f * (f31 - MS_ARM());
		}
		m->displayDirection += MS_ARM();
		r27 = 0;
		if (SHIP_DIR) {
			if (m->displayDirection >= 1260.0f) {
				r27 = 1;
			}
		} else {
			if (m->displayDirection <= -1080.0f) {
				r27 = 1;
			}
		}
		if (r27) {
			MSI(m, 0x48) = 40;
			m->currSubMotionId = 3;
		}
		break;
	case 3:
		if (MSI(m, 0x48) == 14) {
			allPartyRideShip();
		}
		if (MSI(m, 0x48) == 20) {
			marioCamZoomOffReq2(900);
			camFollowYOn();
		}
		if (--MSI(m, 0x48) <= 0) {
			m->currSubMotionId = 4;
		}
		if (m->dispOfs.y > -15.0f) {
			m->dispOfs.y -= 1.0f;
			if (m->dispOfs.y <= -15.0f) {
				m->dispOfs.y = -15.0f;
			}
		}
	case 4:
		f30 = SHIP_DIR ? 1.0f : -1.0f;
		f31 = MSOF(0x20) * f30;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.125f * (f31 - MS_ARM());
		}
		m->displayDirection += MS_ARM();
		MSOF(0x20) -= 0.1f;
		f30 = 1.0f;
		if (MSOF(0x20) <= f30) {
			MSOF(0x20) = f30;
		}
		r27 = 0;
		if (SHIP_DIR) {
			if (m->displayDirection >= 1620.0f) {
				m->displayDirection = 1620.0f;
				r27 = 1;
			}
		} else {
			if (m->displayDirection <= -1440.0f) {
				m->displayDirection = -1440.0f;
				r27 = 1;
			}
		}
		if (r27) {
			if (MSI(m, 0x44) == 4) {
				m->currSubMotionId = 10;
			}
		}
		break;
	case 10: {
		MarioWork* mm;
		void* ms;
		f32 fz, fx;
		s32 ix, iz;
		HitEntry* hit;
		s32 attr;
		m->dispFlags &= ~0x100;
		m->displayDirection = revise360(m->displayDirection);
		m->wPlayerCollisionBox.x = 40.0f;
		m->wPlayerCollisionBox.y = 40.0f;
		ms = marioGetPtr()->motStruct;
		hit = (HitEntry*)MSP(m, 0x1E8);
		mm = marioGetPtr();
		hitObjGetPos(hitGetName(hit), &pos);
		fx = ix = (s32)((100.0f * pos.x + 0.5f) / 100.0f);
		iz = (s32)((100.0f * pos.z + 0.5f) / 100.0f);
		MSF(ms, 0x40) = m->position.y - 15.0f;
		fz = iz;
		r27 = harborKind((HitEntry*)MSP(mm, 0x1E8));
		if (r27 == 1) {
			MSF(ms, 0x3c) = fx;
			MSF(ms, 0x44) = fz - 50.0f - 30.30303f;
		} else if (r27 == 2) {
			MSF(ms, 0x3c) = fx;
			MSF(ms, 0x44) = 30.30303f + (50.0f + fz);
		} else if (r27 == 3) {
			MSF(ms, 0x3c) = fx - 50.0f - 30.30303f;
			MSF(ms, 0x44) = fz;
		} else if (r27 == 4) {
			MSF(ms, 0x3c) = 30.30303f + (50.0f + fx);
			MSF(ms, 0x44) = fz;
		} else {
			MSF(ms, 0x3c) = fx;
			MSF(ms, 0x44) = fz;
		}
		f30 = 0.1f * distABf(MSOF(0x3c), MSOF(0x44), m->position.x, m->position.z);
		switch (r27) {
		case 1: MSOF(0x44) -= f30; break;
		case 2: MSOF(0x44) += f30; break;
		case 3: MSOF(0x3c) -= f30; break;
		case 4: MSOF(0x3c) += f30; break;
		}
		m->baseSpeed = distABf(m->position.x, m->position.z, MSOF(0x3c), MSOF(0x44)) / 36.0f;
		m->directionView = angleABf(m->position.x, m->position.z, MSOF(0x3c), MSOF(0x44));
		m->moveDirection = m->directionView;
		MSOF(4) = MSOF(0x40);
		{
			f32 dd = MSOF(0x40) - m->position.y;
			m->jumpVelocityY = 0.0f;
			m->jumpAccelerationY = (dd + dd) / 306.0f;
		}
		m->jumpJerkY = 0.0f;
		m->jumpSnapY = 0.0f;
		MSI(m, 0x48) = 36;
		m->currSubMotionId = 11;
		break;
	}
	case 11: {
		s32 ok;
		u32 land;
		f32 ly;
		MarioWork* mm;
		movePos(&m->position.x, &m->position.z, m->baseSpeed, m->directionView);
		m->position.y += m->jumpVelocityY;
		marioMakeJumpPara();
		f30 = m->jumpVelocityY;
		mm = marioGetPtr();
		mm->wPlayerCollisionBox.x = 20.0f;
		land = marioChkLandon(f30, &ly);
		mm->wPlayerCollisionBox.x = 40.0f;
		{
			f32 d;
			if (land && ((d = mm->position.y - ly) <= 0.0f || d + f30 <= 0.0f)) {
				MSI(mm, 0x1e4) = land;
				mm->position.y = ly;
				MSI(mm, 0) &= ~0xF0000;
				mm->jumpDistance = __fabsf(distABf(mm->position.x, mm->position.z, mm->lastGroundPos.x, mm->lastGroundPos.z));
				MSI(mm, 0) &= ~0x80;
				*(s16*)((u8*)mm + 0x50) = 0;
				*(s16*)((u8*)mm + 0x52) = 0;
				camFollowYOn();
				ok = 1;
			} else {
				ok = 0;
			}
		}
		if (ok) {
			f30 = 0.0f;
			m->jumpVelocityY = f30;
			m->jumpAccelerationY = f30;
			m->jumpJerkY = f30;
			m->jumpSnapY = f30;
			m->baseSpeed = f30;
			MSOF(0x1c) = f30;
			MSI(m, 0) &= ~0xF0000;
			m->displayDirection = revise360(m->displayDirection);
			m->displayDirectionTarget = m->displayDirection;
			m->directionView = toMovedir(m->displayDirection);
			m->moveDirection = m->directionView;
			m->dispFlags &= ~0x100;
			m->dispFlags |= 0x1000;
			psndSFXOn_3D((const char*)0x18f, &m->position);
			MSO(0x24) = (s32)effFunemizuEntry(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			MSI(*(void**)((u8*)*(void**)((u8*)marioGetPtr()->motStruct + 0x24) + 0xC), 0x48) = m->camId;
			MSOF(8) = 0.0f;
			MSOF(0xC) = 4.25f;
			m->currSubMotionId = 50;
			if (!(m->trigFlags & 4)) {
				camGetPtr(8)->flags &= ~0x200;
			}
		}
		break;
	}
	case 30:
		if (!(m->trigFlags & 4)) {
			camGetPtr(8)->flags |= 0x200;
		}
		m->currSubMotionId = 31;
		/* fallthrough */
	case 31: {
		m->dispOfs.y += -0.4f;
		if (m->dispOfs.y <= -18.0f) {
			MSI(m, 0x48) = 4;
			m->currSubMotionId = 32;
		}
		f30 = 1.6f;
		{
			MarioWork* mm = marioGetPtr();
			f32 zz = 0.0f;
			f31 = mm->position.x;
			MSF(EFFP(), 4) = f31;
			f31 = mm->position.y + zz;
			MSF(EFFP(), 8) = f31;
			f31 = mm->position.z;
			MSF(EFFP(), 0xc) = f31;
			MSF(EFFP(), 0x10) = f30;
			f31 = mm->displayDirection;
			MSF(EFFP(), 0x14) = f31;
		}
		break;
	}
	case 32:
		if (--MSI(m, 0x48) > 0) {
			break;
		}
		m->currSubMotionId = 40;
		/* fallthrough */
	case 40: {
		f32 tt, qq, dd;
		s32 n;
		void* ms2;
		marioGetPtr();
		if (marioGetPtr()->motStruct != NULL) {
			if ((u32)MSO(0x38) != 0xFFFFFFFFU) {
				psndSFXOff(MSO(0x38));
				r29 = -1;
				MSO(0x38) = r29;
			}
		}
		camFollowYOff();
		m->dispFlags &= ~0x1000;
		f31 = MSOF(0x40);
		MSOF(4) = f31;
		m->baseSpeed = 2.8f;
		ms2 = marioGetPtr()->motStruct;
		dd = distABf(m->position.x, m->position.z, MSOF(0x3c), MSF(ms2, 0x44));
		n = (s32)((10.0f * (2.0f * dd / m->baseSpeed) + 0.5f) / 10.0f);
		ms2 = marioGetPtr()->motStruct;
		m->directionView = angleABf(m->position.x, m->position.z, MSOF(0x3c), MSF(ms2, 0x44));
		m->moveDirection = m->directionView;
		r29 = ((m->trigFlags >> 9) & 1) + 1;
		MSO(0) = r29;
		tt = 0.5f * (f32)n;
		qq = 80.0f / (tt * tt - tt);
		f30 = 0.0f;
		m->jumpVelocityY = qq * tt;
		m->jumpAccelerationY = -qq;
		m->jumpJerkY = f30;
		m->jumpSnapY = f30;
		MSI(m, 0x48) = (s16)(s32)(0.5f + tt);
		m->currSubMotionId = 0x29;
		MSF(m, 0x2b0) = __fabsf(m->dispOfs.y / (f32)(MSI(m, 0x48) + 0x58));
		effDelete((EffectEntry*)MSO(0x24));
		break;
	}
	case 41:
		movePos(&m->position.x, &m->position.z, m->baseSpeed, m->directionView);
		m->position.y += m->jumpVelocityY;
		marioMakeJumpPara();
		m->dispOfs.y += MSF(m, 0x2b0);
		f30 = 0.0f;
		if (m->dispOfs.y > f30) {
			m->dispOfs.y = f30;
		}
		if (--MSI(m, 0x48) > 0) {
			break;
		}
		marioChgPaper((char*)str_802C5E60);
		marioChgPose("M_Z_1");
		MSI(m, 0x2a4) = 0x58;
		marioSetPaperAnimeLocalTime(MSI(m, 0x2a4));
		f31 = 0.0f;
		MSOF(0x1c) = f31;
		m->dispFlags |= 0x100;
		marioAdjustMoveDir();
		m->currSubMotionId = 0x2b;
		psndSFXOn_3D((const char*)0x192, &m->position);
		{
			void* e = evtEntry(sound_evt2, 0, 0);
			MSI(e, 0x9c) = (s32)(1024.0f * m->position.x) - 230000000;
			MSI(e, 0xa0) = (s32)(1024.0f * m->position.y) - 230000000;
			MSI(e, 0xa4) = (s32)(1024.0f * m->position.z) - 230000000;
		}
		break;
	case 43:
		m->dispOfs.y += MSF(m, 0x2b0);
		f30 = 0.0f;
		if (m->dispOfs.y > f30) {
			m->dispOfs.y = f30;
		}
		marioSetPaperAnimeLocalTime(MSI(m, 0x2a4));
		if ((MSI(m, 0x2a4) = MSI(m, 0x2a4) - 1) < 0x2c) {
			break;
		}
		f30 = SHIP_DIR ? 20.0f : -20.0f;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.125f * (f30 - MS_ARM());
		}
		if (SHIP_DIR) {
			f31 = 20.0f;
			if (MS_ARM() >= f31) {
				MS_ARM() = f31;
			}
		} else {
			f31 = -20.0f;
			if (MS_ARM() <= f31) {
				MS_ARM() = f31;
			}
		}
		m->displayDirection += MS_ARM();
		if (MSI(m, 0x2a4) == 0x2c) {
			m->currSubMotionId = 0x2c;
		}
		break;
	case 44:
		m->dispOfs.y += MSF(m, 0x2b0);
		f30 = 0.0f;
		if (m->dispOfs.y > f30) {
			m->dispOfs.y = f30;
		}
		marioSetPaperAnimeLocalTime(MSI(m, 0x2a4));
		if ((MSI(m, 0x2a4) = MSI(m, 0x2a4) - 1) <= 0) {
			MSI(m, 0x2a4) = 0;
			m->currSubMotionId = 0x2d;
			MSI(m, 0x48) = 6;
			m->displayDirection = revise360(m->displayDirection);
			if (MSI(marioGetPtr()->motStruct, 0) & 2) {
				m->displayDirection = m->displayDirection - 360.0f;
			}
		}
		m->displayDirection += MS_ARM();
		break;
	case 45:
		marioSetPaperAnimeLocalTime(MSI(m, 0x2a4));
		f30 = SHIP_DIR ? 1.0f : -1.0f;
		f30 = MSOF(0x20) * f30;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.05f * (f30 - MS_ARM());
		}
		m->displayDirection += MS_ARM();
		MSOF(0x20) += -0.005f;
		f31 = 10.0f;
		if (MSOF(0x20) <= f31) {
			MSOF(0x20) = f31;
		}
		if (--MSI(m, 0x48) > 0) {
			break;
		}
	case 46:
		f30 = SHIP_DIR ? 1.0f : -1.0f;
		f30 = MSOF(0x20) * f30;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.05f * (f30 - MS_ARM());
		}
		m->displayDirection += MS_ARM();
		MSOF(0x20) += -0.005f;
		f31 = 10.0f;
		if (MSOF(0x20) <= f31) {
			MSOF(0x20) = f31;
		}
		r27 = 0;
		if (SHIP_DIR) {
			if (m->displayDirection >= 360.0f) {
				m->displayDirection = revise360(m->displayDirection);
				r27 = 1;
			}
		} else {
			if (m->displayDirection <= -360.0f) {
				m->displayDirection = revise360(m->displayDirection);
				r27 = 1;
			}
		}
		if (!r27) {
			break;
		}
		m->displayDirection = revise360(m->displayDirection);
		if (MSI(marioGetPtr()->motStruct, 0) & 2) {
			m->displayDirection = m->displayDirection - 360.0f;
		}
		marioPaperOff();
		m->dispFlags &= ~8;
		marioChgPose((char*)str_802C5E58);
		m->currSubMotionId = 0x2f;
		f31 = 10.0f;
		MSOF(0x20) = f31;
	case 47:
		r27 = 0;
		marioGetPtr();
		marioGetPtr();
		f30 = SHIP_DIR ? 4.0f : -4.0f;
		{
			f32* ms = (f32*)marioGetPtr()->motStruct;
			f32 old = ms[7];
			ms[7] = old + 0.05f * (f30 - MS_ARM());
		}
		m->displayDirection += MS_ARM();
		if (SHIP_DIR) {
			if (m->displayDirection >= 540.0f) {
				m->displayDirection = 540.0f;
				r27 = 1;
			}
		} else {
			if (m->displayDirection <= -360.0f) {
				m->displayDirection = -360.0f;
				r27 = 1;
			}
		}
		if (MSI(m, 0x44) != 0x2f || !r27) {
			break;
		}
		m->displayDirection = revise360(m->displayDirection);
		m->displayDirectionTarget = m->displayDirection;
		m->moveDirection = toMovedir(m->displayDirection);
		m->directionView = m->moveDirection;
		m->dispFlags &= ~0x100;
		m->wPlayerCollisionBox.x = 20.0f;
		m->wPlayerCollisionBox.y = 37.0f;
		f30 = 0.0f;
		m->jumpVelocityY = f30;
		m->jumpAccelerationY = f30;
		m->jumpJerkY = f30;
		m->jumpSnapY = f30;
		m->baseSpeed = f30;
		MSI(m, 0) &= ~0xF0000;
		m->dispOfs.y = f30;
		marioChgMot(10);
		marioSetFallPara();
		allPartyRideOff();
		N_marioSetBottomlessRespawnPosOnBeroEntry(m->position.x, m->position.y, m->position.z);
		N_marioReloadMapOnBottomlessOff();
		if (marioGetPtr()->motStruct != NULL) {
			__memFree(HEAP_DEFAULT, marioGetPtr()->motStruct);
			r29 = 0;
			marioGetPtr()->motStruct = (void*)r29;
		}
		if (!(m->trigFlags & 4)) {
			camGetPtr(8)->flags &= ~0x200;
		}
		break;
	case 50:
		m->currSubMotionId = 0x34;
	case 52:
		if ((u32)MSI(m, 0x1e4) != 0) {
			f31 = MSOF(0xC);
			f31 = revise360(MSOF(8) - f31);
			MSOF(8) = f31;
			m->dispOfs.y = 3.0f * (f32)sin(3.1415927f * MSOF(8) / 180.0f) + -13.0f;
		}
		if (MSI(m, 0) & 0x20) {
			SHIP_EFF()
			break;
		}
		if ((u32)MSI(m, 0x1e4) == 0) {
			*(u8*)((u8*)m + 0x24e) = 0;
			*(u8*)((u8*)m + 0x24f) = 0;
		}
		shipMove();
		if (MSI(m, 0) & 0x20000) {
			MarioWork* mm;
			s32 ok; u32 land;
			f32 ly;
			marioMakeJumpPara();
			if (m->jumpVelocityY <= -7.0f) {
				m->jumpVelocityY = -7.0f;
			}
			f30 = m->jumpVelocityY;
			mm = marioGetPtr();
			mm->wPlayerCollisionBox.x = 20.0f;
			land = marioChkLandon(f30, &ly);
			mm->wPlayerCollisionBox.x = 40.0f;
			{
				f32 d;
				if (land && ((d = mm->position.y - ly) <= 0.0f || d + f30 <= 0.0f)) {
					MSI(mm, 0x1e4) = land;
					mm->position.y = ly;
					MSI(mm, 0) &= ~0xF0000;
					mm->jumpDistance = __fabsf(distABf(mm->position.x, mm->position.z, mm->lastGroundPos.x, mm->lastGroundPos.z));
					MSI(mm, 0) &= ~0x80;
					*(s16*)((u8*)mm + 0x50) = 0;
					*(s16*)((u8*)mm + 0x52) = 0;
					camFollowYOn();
					ok = 1;
				} else {
					ok = 0;
				}
			}
			if (!ok) {
				m->position.y += m->jumpVelocityY;
			}
		} else {
			marioClearJumpPara();
		}
		if (strcmp((char*)gp + 0x12c, (char*)str_802C5E68) == 0) {
			if (m->position.y <= 260.0f && m->position.y >= 50.0f) {
				f32 ang = MSF(m, 0x214);
				if (0.0f != (f32)(s32)(10.0f * ang + 0.5f) / 10.0f) {
					m->position.y = 2.0f * (f32)sin(3.1415927f * ang / 180.0f) + m->position.y;
					m->position.z = 2.0f * -(f32)cos(3.1415927f * MSF(m, 0x214) / 180.0f) + m->position.z;
				}
			}
		}
		MSI(m, 0x1e0) = 0;
		MSI(m, 0x1dc) = 0;
		MSI(m, 0x1ec) = 0;
		MSI(m, 0x1f0) = 0;
		marioCheckWallShip(m->baseSpeed, m->directionView);
		if (m->baseSpeed < 0.5f) {
			m->baseSpeed = 0.0f;
			m->currSubMotionId = 0x32;
		}
		SHIP_EFF()
		if (*(u16*)((u8*)m + 0x248) & 0xa00) {
			if (checkHarbor((Vec*)((u8*)marioGetPtr()->motStruct + 0x3c))) {
				m->currSubMotionId = 0x1e;
			}
		}
		break;
#endif
#ifndef NONMATCHING
	char _af_pad[76];
	asm volatile {
		lis r3, str_802C5E00@ha
		addi r30, r3, str_802C5E00@l
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0x8063000C
		opword 0x546007FF
		opword 0x418200AC
		opword 0x5460003C
		opword 0x38600000
		opword 0x901F000C
		opword 0x38800048
		opword 0x801F0000
		opword 0x54000416
		opword 0x901F0000
		bl __memAlloc
		opword 0x7C7C1B78
		bl marioGetPtr
		opword 0x93830288
		bl marioGetPtr
		opword 0x80630288
		opword 0x38800000
		opword 0x38A00048
		bl memset
		opword 0x3B80FFFF
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_0_8041ada0(r2)
		opword 0x93830038
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041ada0(r2)
		opword 0xD3C30020
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_4p25_8041ade4(r2)
		opword 0xD3E30008
		bl marioGetPtr
		opword 0x80630288
		opword 0x38000000
		opword 0xD3C3000C
		opword 0x901F0044
		opword 0x801F000C
		opword 0x5400077B
		opword 0x40820018
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x60000200
		opword 0xB0030000
		opword 0x801F0044
		opword 0x28000034
		opword 0x41811994
		lis r3, jumptable_8030ECF8@ha
		opword 0x5400103A
		addi r3, r3, jumptable_8030ECF8@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x389F008C
		opword 0x3860018D
		bl psndSFXOn_3D
		opword 0x389F008C
		opword 0x386000AF
		bl psndSFXOn_3D
		bl marioCamZoomUp
		bl marioPreJump
		opword 0x387E0058
		bl marioChgPose
		bl camFollowYOff
		opword 0x809F0004
		opword 0x38600000
		opword 0x38000001
		lfs f30, float_0_8041ada0(r2)
		opword 0x60840100
		opword 0x909F0004
		opword 0x907F0048
		opword 0x901F0044
		opword 0xB07F0050
		opword 0xB07F0052
		opword 0xD3DF0180
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3C3001C
		opword 0xC03F008C
		opword 0xC05F0090
		opword 0xC07F0094
		bl N_marioSetBottomlessRespawnPosOnBeroEntry
		opword 0x83BF01E8
		bl marioGetPtr
		opword 0x7C7C1B78
		opword 0x7FA3EB78
		bl hitGetAttr
		opword 0x54600463
		opword 0x3BA00000
		opword 0x41820054
		opword 0x807C01E8
		bl hitGetName
		la r4, _af_pad+20
		bl hitObjGetPos
		opword 0xC03C008C
		opword 0xC05C0094
		opword 0xC061001C
		opword 0xC0810024
		bl angleABf
		opword 0xC01C0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041adc0(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x3BA00002
		opword 0x48000080
		opword 0x3BA00001
		opword 0x48000078
		opword 0x54600421
		opword 0x41820054
		opword 0x807C01E8
		bl hitGetName
		opword 0x38810028
		bl hitObjGetPos
		opword 0xC03C008C
		opword 0xC05C0094
		opword 0xC0610028
		opword 0xC0810030
		bl angleABf
		opword 0xC01C0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041adc0(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x3BA00002
		opword 0x48000028
		opword 0x3BA00001
		opword 0x48000020
		opword 0x546003DF
		opword 0x4182000C
		opword 0x3BA00002
		opword 0x48000010
		opword 0x5460039D
		opword 0x41820008
		opword 0x3BA00001
		bl marioGetPtr
		opword 0x80630288
		opword 0x93A30000
		bl marioMakeJumpPara
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f31, float_30_8041ade8(r2)
		opword 0x48000008
		lfs f31, float_neg30_8041adec(r2)
		bl marioGetPtr
		opword 0x83830288
		opword 0xC3DC001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p125_8041adf0(r2)
		opword 0xC023001C
		opword 0xEC3F0828
		opword 0xEC00F07A
		opword 0xD01C001C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820030
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_30_8041ade8(r2)
		opword 0xC003001C
		opword 0xFC00F040
		opword 0x4C411382
		opword 0x4082003C
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3C3001C
		opword 0x4800002C
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_neg30_8041adec(r2)
		opword 0xC003001C
		opword 0xFC00F040
		opword 0x4C401382
		opword 0x40820010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3C3001C
		bl marioGetPtr
		opword 0x80630288
		li r27, 0x0
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820020
		opword 0xC03F01A8
		lfs f0, float_270_8041adf4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820024
		opword 0x3B600001
		opword 0x4800001C
		opword 0xC03F01A8
		lfs f0, float_neg270_8041adf8(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0x3B600001
		opword 0x2C1B0000
		opword 0x418200CC
		opword 0x38600002
		opword 0x38000014
		opword 0x907F0044
		opword 0x901F0048
		bl marioGetColor
		opword 0x5460103A
		la r3, paper_ship(r13)
		opword 0x7C63002E
		bl marioPaperOn
		opword 0x387E0060
		bl marioChgPaper
		la r3, str_8041ADFC(r2)
		bl marioChgPose
		opword 0x801F0004
		lfs f30, float_15_8041adb4(r2)
		opword 0x60000008
		opword 0x901F0004
		bl marioGetPtr
		opword 0x80A30288
		lis r3, sound_evt@ha
		addi r3, r3, sound_evt@l
		opword 0x38800000
		opword 0xD3C50020
		opword 0x38A00000
		bl evtEntry
		lfs f1, float_1024_8041ae04(r2)
		opword 0xC01F008C
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010038
		opword 0x8081003C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x9003009C
		opword 0xC01F0090
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010040
		opword 0x80810044
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A0
		opword 0xC01F0094
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8081004C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A4
		opword 0xC03F007C
		lfs f0, float_0_8041ada0(r2)
		opword 0xFC010040
		opword 0x40811620
		opword 0xC01F0090
		opword 0xEC00082A
		opword 0xD01F0090
		opword 0x801F0000
		opword 0x54000416
		opword 0x901F0000
		opword 0x48001604
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f30, float_1_8041adc8(r2)
		opword 0x48000008
		lfs f30, float_neg1_8041ada4(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030020
		opword 0xEFE007B2
		bl marioGetPtr
		opword 0x83830288
		opword 0xC3DC001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p125_8041adf0(r2)
		opword 0xC023001C
		opword 0xEC3F0828
		opword 0xEC00F07A
		opword 0xD01C001C
		bl marioGetPtr
		opword 0x80630288
		opword 0x3B600000
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820020
		opword 0xC03F01A8
		lfs f0, float_1260_8041ae08(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820024
		opword 0x3B600001
		opword 0x4800001C
		opword 0xC03F01A8
		lfs f0, float_neg1080_8041ae0c(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0x3B600001
		opword 0x2C1B0000
		opword 0x41821540
		opword 0x38600028
		opword 0x38000003
		opword 0x907F0048
		opword 0x901F0044
		opword 0x4800152C
		opword 0x801F0048
		opword 0x2C00000E
		opword 0x40820008
		bl allPartyRideShip
		opword 0x801F0048
		opword 0x2C000014
		opword 0x40820010
		opword 0x38600384
		bl marioCamZoomOffReq2
		bl camFollowYOn
		opword 0x807F0048
		opword 0x3403FFFF
		opword 0x901F0048
		opword 0x4181000C
		opword 0x38000004
		opword 0x901F0044
		opword 0xC05F009C
		lfs f1, float_neg15_8041ae10(r2)
		opword 0xFC020840
		opword 0x40810024
		lfs f0, float_1_8041adc8(r2)
		opword 0xEC020028
		opword 0xD01F009C
		opword 0xC01F009C
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820008
		opword 0xD03F009C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f30, float_1_8041adc8(r2)
		opword 0x48000008
		lfs f30, float_neg1_8041ada4(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030020
		opword 0xEFE007B2
		bl marioGetPtr
		opword 0x83830288
		opword 0xC3DC001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p125_8041adf0(r2)
		opword 0xC023001C
		opword 0xEC3F0828
		opword 0xEC00F07A
		opword 0xD01C001C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p1_8041ae14(r2)
		opword 0xC0230020
		opword 0xEC010028
		opword 0xD0030020
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_1_8041adc8(r2)
		opword 0xC0030020
		opword 0xFC00F040
		opword 0x4C401382
		opword 0x40820010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3C30020
		opword 0x3B600000
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820024
		opword 0xC03F01A8
		lfs f0, float_1620_8041ae18(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082002C
		opword 0xD01F01A8
		opword 0x3B600001
		opword 0x48000020
		opword 0xC03F01A8
		lfs f0, float_neg1440_8041ae1c(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		opword 0xD01F01A8
		opword 0x3B600001
		opword 0x2C1B0000
		opword 0x418213B0
		opword 0x801F0044
		opword 0x2C000004
		opword 0x408213A4
		opword 0x3800000A
		opword 0x901F0044
		opword 0x48001398
		opword 0x801F0004
		opword 0x5400062C
		opword 0x901F0004
		opword 0xC03F01A8
		bl revise360
		opword 0xD03F01A8
		lfs f0, float_40_8041ad98(r2)
		opword 0xD01F01B4
		opword 0xD01F01B8
		bl marioGetPtr
		opword 0x83830288
		opword 0x837F01E8
		bl marioGetPtr
		opword 0x7C7D1B78
		opword 0x7F63DB78
		bl hitGetName
		opword 0x38810010
		bl hitObjGetPos
		lfs f5, float_100_8041adac(r2)
		opword 0x3C004330
		opword 0xC0210010
		opword 0x3B600000
		lfs f2, float_0p5_8041ada8(r2)
		opword 0xC0010018
		opword 0xEC65107A
		opword 0xC03D0090
		opword 0xEC45103A
		lfs f0, float_15_8041adb4(r2)
		opword 0x90010040
		opword 0xEC832824
		opword 0x90010050
		opword 0xC87E0050
		opword 0xEC422824
		opword 0xFC80201E
		opword 0xFC40101E
		opword 0xEC010028
		opword 0xD8810048
		opword 0xD8410038
		opword 0x8061004C
		opword 0x8001003C
		opword 0x6C638000
		opword 0xD01C0040
		opword 0x6C008000
		opword 0x90610044
		opword 0x807D01E8
		opword 0x90010054
		opword 0xC8210040
		opword 0xC8010050
		opword 0xEFE11828
		opword 0xEFC01828
		bl hitGetAttr
		opword 0x54600463
		opword 0x4182000C
		opword 0x3B600001
		opword 0x48000030
		opword 0x54600421
		opword 0x4182000C
		opword 0x3B600002
		opword 0x48000020
		opword 0x546003DF
		opword 0x4182000C
		opword 0x3B600003
		opword 0x48000010
		opword 0x5460039D
		opword 0x41820008
		opword 0x3B600004
		opword 0x2C1B0001
		opword 0x40820020
		lfs f1, float_50_8041adb8(r2)
		lfs f0, float_30p303_8041adbc(r2)
		opword 0xEC3E0828
		opword 0xD3FC003C
		opword 0xEC010028
		opword 0xD01C0044
		opword 0x48000078
		opword 0x2C1B0002
		opword 0x40820020
		lfs f0, float_50_8041adb8(r2)
		lfs f1, float_30p303_8041adbc(r2)
		opword 0xEC00F02A
		opword 0xD3FC003C
		opword 0xEC01002A
		opword 0xD01C0044
		opword 0x48000054
		opword 0x2C1B0003
		opword 0x40820020
		lfs f1, float_50_8041adb8(r2)
		lfs f0, float_30p303_8041adbc(r2)
		opword 0xEC3F0828
		opword 0xEC010028
		opword 0xD01C003C
		opword 0xD3DC0044
		opword 0x48000030
		opword 0x2C1B0004
		opword 0x40820020
		lfs f0, float_50_8041adb8(r2)
		lfs f1, float_30p303_8041adbc(r2)
		opword 0xEC00F82A
		opword 0xEC01002A
		opword 0xD01C003C
		opword 0xD3DC0044
		opword 0x4800000C
		opword 0xD3FC003C
		opword 0xD3DC0044
		bl marioGetPtr
		opword 0x83A30288
		bl marioGetPtr
		opword 0x80630288
		opword 0xC05D0044
		opword 0xC023003C
		opword 0xC07F008C
		opword 0xC09F0094
		bl distABf
		lfs f0, float_0p1_8041ae14(r2)
		opword 0x2C1B0003
		opword 0xEFC00072
		opword 0x41820054
		opword 0x40800014
		opword 0x2C1B0001
		opword 0x41820018
		opword 0x4080002C
		opword 0x4800006C
		opword 0x2C1B0005
		opword 0x40800064
		opword 0x4800004C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030044
		opword 0xEC00F028
		opword 0xD0030044
		opword 0x48000048
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030044
		opword 0xEC00F02A
		opword 0xD0030044
		opword 0x48000030
		bl marioGetPtr
		opword 0x80630288
		opword 0xC003003C
		opword 0xEC00F028
		opword 0xD003003C
		opword 0x48000018
		bl marioGetPtr
		opword 0x80630288
		opword 0xC003003C
		opword 0xEC00F02A
		opword 0xD003003C
		bl marioGetPtr
		opword 0x83A30288
		bl marioGetPtr
		opword 0x80630288
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC063003C
		opword 0xC09D0044
		bl distABf
		lfs f0, float_36_8041ae20(r2)
		opword 0xEC010024
		opword 0xD01F0180
		bl marioGetPtr
		opword 0x83A30288
		bl marioGetPtr
		opword 0x80630288
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC063003C
		opword 0xC09D0044
		bl angleABf
		opword 0xD03F01A0
		opword 0xC01F01A0
		opword 0xD01F019C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3C30040
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3C30004
		bl marioGetPtr
		opword 0x80830288
		opword 0x38600024
		opword 0xC01F0090
		opword 0x3800000B
		opword 0xC0240040
		lfs f2, float_0_8041ada0(r2)
		opword 0xEC210028
		lfs f0, float_306_8041ae24(r2)
		opword 0xD05F007C
		opword 0xEC21082A
		opword 0xEC010024
		opword 0xD01F0080
		opword 0xD05F0084
		opword 0xD05F0088
		opword 0x907F0048
		opword 0x901F0044
		opword 0x48001088
		opword 0xC03F0180
		opword 0x387F008C
		opword 0xC05F01A0
		opword 0x389F0094
		bl movePos
		opword 0xC03F0090
		opword 0xC01F007C
		opword 0xEC01002A
		opword 0xD01F0090
		bl marioMakeJumpPara
		opword 0xC3DF007C
		bl marioGetPtr
		lfs f0, float_20_8041ad9c(r2)
		opword 0x7C7D1B78
		opword 0xFC20F090
		opword 0x3861000C
		opword 0xD01D01B4
		bl marioChkLandon
		lfs f0, float_40_8041ad98(r2)
		opword 0x28030000
		opword 0xD01D01B4
		opword 0x41820088
		opword 0xC05D0090
		opword 0xC001000C
		lfs f1, float_0_8041ada0(r2)
		opword 0xEC020028
		opword 0xFC000840
		opword 0x4C401382
		opword 0x41820014
		opword 0xEC00F02A
		opword 0xFC000840
		opword 0x4C401382
		opword 0x4082005C
		opword 0x907D01E4
		opword 0xC001000C
		opword 0xD01D0090
		opword 0x801D0000
		opword 0x54000416
		opword 0x901D0000
		opword 0xC03D008C
		opword 0xC05D0094
		opword 0xC07D011C
		opword 0xC09D0124
		bl distABf
		opword 0xFC000A10
		opword 0x38000000
		opword 0xD01D0128
		opword 0x807D0000
		opword 0x5463066E
		opword 0x907D0000
		opword 0xB01D0050
		opword 0xB01D0052
		bl camFollowYOn
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820FA0
		lfs f30, float_0_8041ada0(r2)
		opword 0xD3DF007C
		opword 0xD3DF0080
		opword 0xD3DF0084
		opword 0xD3DF0088
		opword 0xD3DF0180
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3C3001C
		opword 0x801F0000
		opword 0x54000416
		opword 0x901F0000
		opword 0xC03F01A8
		bl revise360
		opword 0xD03F01A8
		opword 0xC01F01A8
		opword 0xD01F01AC
		opword 0xC03F01A8
		bl toMovedir
		opword 0xD03F01A0
		opword 0x389F008C
		opword 0x3860018F
		opword 0xC01F01A0
		opword 0xD01F019C
		opword 0x801F0004
		opword 0x5400062C
		opword 0x901F0004
		opword 0x801F0004
		opword 0x60001000
		opword 0x901F0004
		bl psndSFXOn_3D
		lfs f1, float_0_8041ada0(r2)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFC600890
		opword 0xFC800890
		opword 0xFCA00890
		bl effFunemizuEntry
		opword 0x7C7D1B78
		bl marioGetPtr
		opword 0x80630288
		opword 0x93A30024
		opword 0x83BF0134
		bl marioGetPtr
		opword 0x80630288
		lfs f30, float_0_8041ada0(r2)
		opword 0x80630024
		opword 0x8063000C
		opword 0x93A30048
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_4p25_8041ade4(r2)
		opword 0xD3C30008
		bl marioGetPtr
		opword 0x80630288
		opword 0x38000032
		opword 0xD3E3000C
		opword 0x901F0044
		opword 0x801F000C
		opword 0x5400077B
		opword 0x40820EAC
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x540005EA
		opword 0xB0030000
		opword 0x48000E94
		opword 0x801F000C
		opword 0x5400077B
		opword 0x40820018
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x60000200
		opword 0xB0030000
		opword 0x3800001F
		opword 0x901F0044
		opword 0xC05F009C
		lfs f1, float_neg0p4_8041ae28(r2)
		lfs f0, float_neg18_8041ae2c(r2)
		opword 0xEC22082A
		opword 0xD03F009C
		opword 0xC03F009C
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820014
		opword 0x38600004
		opword 0x38000020
		opword 0x907F0048
		opword 0x901F0044
		lfs f30, float_1p6_8041ae30(r2)
		bl marioGetPtr
		opword 0x7C7D1B78
		opword 0xC3E3008C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0_8041ada0(r2)
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30004
		opword 0xC03D0090
		opword 0xEFE1002A
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30008
		opword 0xC3FD0094
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E3000C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3C30010
		opword 0xC3FD01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30014
		opword 0x48000DAC
		opword 0x807F0048
		opword 0x3403FFFF
		opword 0x901F0048
		opword 0x41810D9C
		opword 0x38000028
		opword 0x901F0044
		bl marioGetPtr
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x4182003C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630038
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820024
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630038
		bl psndSFXOff
		opword 0x3BA0FFFF
		bl marioGetPtr
		opword 0x80630288
		opword 0x93A30038
		bl camFollowYOff
		opword 0x801F0004
		opword 0x54000524
		opword 0x901F0004
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3E30040
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_2p8_8041ae34(r2)
		opword 0xD3E30004
		opword 0xD01F0180
		bl marioGetPtr
		opword 0x83A30288
		bl marioGetPtr
		opword 0x80630288
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC063003C
		opword 0xC09D0044
		bl distABf
		lfs f0, float_2_8041ae3c(r2)
		opword 0xC05F0180
		opword 0xEC600072
		lfs f1, float_10_8041ae38(r2)
		lfs f0, float_0p5_8041ada8(r2)
		opword 0xEC431024
		opword 0xEC0100BA
		opword 0xEC000824
		opword 0xFC00001E
		opword 0xD8010050
		opword 0x83610054
		bl marioGetPtr
		opword 0x83A30288
		bl marioGetPtr
		opword 0x80630288
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC063003C
		opword 0xC09D0044
		bl angleABf
		opword 0xD03F01A0
		opword 0xC01F01A0
		opword 0xD01F019C
		opword 0x801F000C
		opword 0x5403BFFE
		opword 0x3BA30001
		bl marioGetPtr
		opword 0x3C804330
		opword 0x6F608000
		opword 0x9001004C
		opword 0x38000029
		opword 0x80630288
		opword 0x90810048
		opword 0xC89E0050
		opword 0xC8010048
		lfs f5, float_0p5_8041ada8(r2)
		opword 0xEC002028
		lfs f3, float_80_8041ae40(r2)
		opword 0x93A30000
		lfs f1, float_0_8041ada0(r2)
		opword 0xECC50032
		opword 0x90810038
		opword 0xEC4631B8
		opword 0xEC05302A
		opword 0xEC431024
		opword 0xEC6201B2
		opword 0xFC00001E
		opword 0xFC401050
		opword 0xD07F007C
		opword 0xD05F0080
		opword 0xD8010040
		opword 0xD03F0084
		opword 0x80610044
		opword 0xD03F0088
		opword 0x7C630734
		opword 0x907F0048
		opword 0x901F0044
		opword 0x807F0048
		opword 0xC03F009C
		opword 0x38030058
		opword 0x6C008000
		opword 0x9001003C
		opword 0xC8010038
		opword 0xEC002028
		opword 0xEC010024
		opword 0xFC000210
		opword 0xD01F02B0
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		bl effDelete
		opword 0x48000BD4
		opword 0xC03F0180
		opword 0x387F008C
		opword 0xC05F01A0
		opword 0x389F0094
		bl movePos
		opword 0xC03F0090
		opword 0xC01F007C
		opword 0xEC01002A
		opword 0xD01F0090
		bl marioMakeJumpPara
		opword 0xC05F009C
		opword 0xC03F02B0
		lfs f0, float_0_8041ada0(r2)
		opword 0xEC22082A
		opword 0xD03F009C
		opword 0xC03F009C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01F009C
		opword 0x807F0048
		opword 0x3403FFFF
		opword 0x901F0048
		opword 0x41810B78
		opword 0x387E0060
		bl marioChgPaper
		la r3, str_8041ADFC(r2)
		bl marioChgPose
		opword 0x38000058
		opword 0x901F02A4
		opword 0x807F02A4
		bl marioSetPaperAnimeLocalTime
		lfs f31, float_0_8041ada0(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E3001C
		opword 0x801F0004
		opword 0x60000100
		opword 0x901F0004
		bl marioAdjustMoveDir
		opword 0x3800002B
		opword 0x389F008C
		opword 0x901F0044
		opword 0x38600192
		bl psndSFXOn_3D
		lis r3, sound_evt2@ha
		opword 0x38800000
		addi r3, r3, sound_evt2@l
		opword 0x38A00000
		bl evtEntry
		lfs f1, float_1024_8041ae04(r2)
		opword 0xC01F008C
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010050
		opword 0x80810054
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x9003009C
		opword 0xC01F0090
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8081004C
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A0
		opword 0xC01F0094
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010040
		opword 0x80810044
		opword 0x3C84F24A
		opword 0x38047A80
		opword 0x900300A4
		opword 0x48000AA8
		opword 0xC05F009C
		opword 0xC03F02B0
		lfs f0, float_0_8041ada0(r2)
		opword 0xEC22082A
		opword 0xD03F009C
		opword 0xC03F009C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01F009C
		opword 0x807F02A4
		bl marioSetPaperAnimeLocalTime
		opword 0x807F02A4
		opword 0x3803FFFF
		opword 0x2C00002C
		opword 0x901F02A4
		opword 0x41800A68
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f30, float_20_8041ad9c(r2)
		opword 0x48000008
		lfs f30, float_neg20_8041ae44(r2)
		bl marioGetPtr
		opword 0x83A30288
		opword 0xC3FD001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p125_8041adf0(r2)
		opword 0xC023001C
		opword 0xEC3E0828
		opword 0xEC00F87A
		opword 0xD01D001C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820030
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_20_8041ad9c(r2)
		opword 0xC003001C
		opword 0xFC00F840
		opword 0x4C411382
		opword 0x4082003C
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E3001C
		opword 0x4800002C
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_neg20_8041ae44(r2)
		opword 0xC003001C
		opword 0xFC00F840
		opword 0x4C401382
		opword 0x40820010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E3001C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		opword 0x801F02A4
		opword 0x2C00002C
		opword 0x40820994
		opword 0x3800002C
		opword 0x901F0044
		opword 0x48000988
		opword 0xC05F009C
		opword 0xC03F02B0
		lfs f0, float_0_8041ada0(r2)
		opword 0xEC22082A
		opword 0xD03F009C
		opword 0xC03F009C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01F009C
		opword 0x807F02A4
		bl marioSetPaperAnimeLocalTime
		opword 0x807F02A4
		opword 0x3403FFFF
		opword 0x901F02A4
		opword 0x4181004C
		opword 0x38000000
		opword 0x3860002D
		opword 0x901F02A4
		opword 0x38000006
		opword 0x907F0044
		opword 0x901F0048
		opword 0xC03F01A8
		bl revise360
		opword 0xD03F01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007BD
		opword 0x41820014
		opword 0xC03F01A8
		lfs f0, float_360_8041ae48(r2)
		opword 0xEC010028
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		opword 0x480008E8
		opword 0x807F02A4
		bl marioSetPaperAnimeLocalTime
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f30, float_1_8041adc8(r2)
		opword 0x48000008
		lfs f30, float_neg1_8041ada4(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030020
		opword 0xEFC007B2
		bl marioGetPtr
		opword 0x83A30288
		opword 0xC3FD001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p05_8041ae4c(r2)
		opword 0xC023001C
		opword 0xEC3E0828
		opword 0xEC00F87A
		opword 0xD01D001C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_neg0p005_8041ae50(r2)
		opword 0xC0230020
		opword 0xEC01002A
		opword 0xD0030020
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_10_8041ae38(r2)
		opword 0xC0030020
		opword 0xFC00F840
		opword 0x4C401382
		opword 0x40820010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30020
		opword 0x807F0048
		opword 0x3403FFFF
		opword 0x901F0048
		opword 0x41810820
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f30, float_1_8041adc8(r2)
		opword 0x48000008
		lfs f30, float_neg1_8041ada4(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030020
		opword 0xEFC007B2
		bl marioGetPtr
		opword 0x83A30288
		opword 0xC3FD001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p05_8041ae4c(r2)
		opword 0xC023001C
		opword 0xEC3E0828
		opword 0xEC00F87A
		opword 0xD01D001C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_neg0p005_8041ae50(r2)
		opword 0xC0230020
		opword 0xEC01002A
		opword 0xD0030020
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_10_8041ae38(r2)
		opword 0xC0030020
		opword 0xFC00F840
		opword 0x4C401382
		opword 0x40820010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30020
		opword 0x3B600000
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820028
		opword 0xC03F01A8
		lfs f0, float_360_8041ae48(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820034
		bl revise360
		opword 0xD03F01A8
		opword 0x3B600001
		opword 0x48000024
		opword 0xC03F01A8
		lfs f0, float_neg360_8041ae54(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820010
		bl revise360
		opword 0xD03F01A8
		opword 0x3B600001
		opword 0x2C1B0000
		opword 0x4182070C
		opword 0xC03F01A8
		bl revise360
		opword 0xD03F01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007BD
		opword 0x41820014
		opword 0xC03F01A8
		lfs f0, float_360_8041ae48(r2)
		opword 0xEC010028
		opword 0xD01F01A8
		bl marioPaperOff
		opword 0x801F0004
		opword 0x387E0058
		opword 0x54000776
		opword 0x901F0004
		bl marioChgPose
		opword 0x3800002F
		lfs f31, float_10_8041ae38(r2)
		opword 0x901F0044
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30020
		opword 0x3B600000
		bl marioGetPtr
		bl marioGetPtr
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x4182000C
		lfs f30, float_4_8041ae58(r2)
		opword 0x48000008
		lfs f30, float_neg4_8041ae5c(r2)
		bl marioGetPtr
		opword 0x83A30288
		opword 0xC3FD001C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p05_8041ae4c(r2)
		opword 0xC023001C
		opword 0xEC3E0828
		opword 0xEC00F87A
		opword 0xD01D001C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC01F01A8
		opword 0xC023001C
		opword 0xEC00082A
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820024
		opword 0xC03F01A8
		lfs f0, float_540_8041ae60(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082002C
		opword 0xD01F01A8
		opword 0x3B600001
		opword 0x48000020
		opword 0xC03F01A8
		lfs f0, float_neg360_8041ae54(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		opword 0xD01F01A8
		opword 0x3B600001
		opword 0x801F0044
		opword 0x2C00002F
		opword 0x408205E4
		opword 0x2C1B0000
		opword 0x418205DC
		opword 0xC03F01A8
		bl revise360
		opword 0xD03F01A8
		opword 0xC01F01A8
		opword 0xD01F01AC
		opword 0xC03F01A8
		bl toMovedir
		opword 0xD03F019C
		opword 0x3860000A
		lfs f2, float_20_8041ad9c(r2)
		opword 0xC01F019C
		lfs f1, float_37_8041ae64(r2)
		opword 0xD01F01A0
		lfs f0, float_0_8041ada0(r2)
		opword 0x801F0004
		opword 0x5400062C
		opword 0x901F0004
		opword 0xD05F01B4
		opword 0xD03F01B8
		opword 0xD01F007C
		opword 0xD01F0080
		opword 0xD01F0084
		opword 0xD01F0088
		opword 0xD01F0180
		opword 0x801F0000
		opword 0x54000416
		opword 0x901F0000
		opword 0xD01F009C
		bl marioChgMot
		bl marioSetFallPara
		bl allPartyRideOff
		opword 0xC03F008C
		opword 0xC05F0090
		opword 0xC07F0094
		bl N_marioSetBottomlessRespawnPosOnBeroEntry
		bl N_marioReloadMapOnBottomlessOff
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x41820024
		bl marioGetPtr
		opword 0x7C641B78
		opword 0x38600000
		opword 0x80840288
		bl __memFree
		opword 0x3BA00000
		bl marioGetPtr
		opword 0x93A30288
		opword 0x801F000C
		opword 0x5400077B
		opword 0x40820510
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x540005EA
		opword 0xB0030000
		opword 0x480004F8
		opword 0x38000034
		opword 0x901F0044
		opword 0x801F01E4
		opword 0x28000000
		opword 0x41820068
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3E3000C
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030008
		opword 0xEC20F828
		bl revise360
		opword 0xFFE00890
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30008
		bl marioGetPtr
		opword 0x80630288
		lfs f1, float_3p1416_8041adc4(r2)
		opword 0xC0430008
		lfs f0, float_180_8041adc0(r2)
		opword 0xEC2100B2
		opword 0xEC210024
		bl sin
		opword 0xFC400818
		lfs f1, float_3_8041ae6c(r2)
		lfs f0, float_neg13_8041ae68(r2)
		opword 0xEC0100BA
		opword 0xD01F009C
		opword 0x801F0000
		opword 0x540006B5
		opword 0x4182010C
		opword 0xC3DF0180
		bl marioGetPtr
		lfs f0, float_0_8041ada0(r2)
		opword 0x7C7E1B78
		opword 0xFC1E0000
		opword 0x40820074
		bl marioGetPtr
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_180_8041adc0(r2)
		opword 0xC0230008
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182000C
		lfs f30, float_0p3_8041ae70(r2)
		opword 0x48000008
		lfs f30, float_0p6_8041ae74(r2)
		bl marioGetPtr
		opword 0x83A30288
		opword 0xC3FD0010
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p1_8041ae14(r2)
		opword 0xC0230010
		opword 0xEC3E0828
		opword 0xEC00F87A
		opword 0xD01D0010
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3C30010
		opword 0xC3FE008C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0_8041ada0(r2)
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30004
		opword 0xC03E0090
		opword 0xEFE1002A
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30008
		opword 0xC3FE0094
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E3000C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3C30010
		opword 0xC3FE01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30014
		opword 0x4800036C
		opword 0x801F01E4
		opword 0x28000000
		opword 0x40820010
		opword 0x38000000
		opword 0x981F024E
		opword 0x981F024F
		bl shipMove
		opword 0x801F0000
		opword 0x5400039D
		opword 0x418200F4
		bl marioMakeJumpPara
		opword 0xC03F007C
		lfs f0, float_neg7_8041ae78(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD01F007C
		opword 0xC3DF007C
		bl marioGetPtr
		lfs f0, float_20_8041ad9c(r2)
		opword 0x7C7D1B78
		opword 0xFC20F090
		opword 0x38610008
		opword 0xD01D01B4
		bl marioChkLandon
		lfs f0, float_40_8041ad98(r2)
		opword 0x28030000
		opword 0xD01D01B4
		opword 0x41820088
		opword 0xC05D0090
		opword 0xC0010008
		lfs f1, float_0_8041ada0(r2)
		opword 0xEC020028
		opword 0xFC000840
		opword 0x4C401382
		opword 0x41820014
		opword 0xEC00F02A
		opword 0xFC000840
		opword 0x4C401382
		opword 0x4082005C
		opword 0x907D01E4
		opword 0xC0010008
		opword 0xD01D0090
		opword 0x801D0000
		opword 0x54000416
		opword 0x901D0000
		opword 0xC03D008C
		opword 0xC05D0094
		opword 0xC07D011C
		opword 0xC09D0124
		bl distABf
		opword 0xFC000A10
		opword 0x38000000
		opword 0xD01D0128
		opword 0x807D0000
		opword 0x5463066E
		opword 0x907D0000
		opword 0xB01D0050
		opword 0xB01D0052
		bl camFollowYOn
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x4082001C
		opword 0xC03F0090
		opword 0xC01F007C
		opword 0xEC01002A
		opword 0xD01F0090
		opword 0x48000008
		bl marioClearJumpPara
		lwz r3, gp(r13)
		opword 0x389E0068
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x408200C8
		opword 0xC03F0090
		lfs f0, float_260_8041ae7c(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408200B4
		lfs f0, float_50_8041adb8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x408200A4
		lfs f2, float_10_8041ae38(r2)
		opword 0x3C004330
		opword 0xC09F0214
		lfs f0, float_0p5_8041ada8(r2)
		opword 0x90010048
		opword 0xEC02013A
		opword 0xC83E0050
		lfs f3, float_0_8041ada0(r2)
		opword 0xFC00001E
		opword 0xD8010050
		opword 0x80010054
		opword 0x6C008000
		opword 0x9001004C
		opword 0xC8010048
		opword 0xEC000828
		opword 0xEC001024
		opword 0xFC030000
		opword 0x4182005C
		lfs f1, float_3p1416_8041adc4(r2)
		lfs f0, float_180_8041adc0(r2)
		opword 0xEC210132
		opword 0xEC210024
		bl sin
		opword 0xFC600818
		lfs f1, float_2_8041ae3c(r2)
		opword 0xC01F0090
		lfs f2, float_3p1416_8041adc4(r2)
		opword 0xEC2100FA
		lfs f0, float_180_8041adc0(r2)
		opword 0xD03F0090
		opword 0xC03F0214
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		opword 0xFC200818
		lfs f2, float_2_8041ae3c(r2)
		opword 0xC01F0094
		opword 0xFC200850
		opword 0xEC02007A
		opword 0xD01F0094
		opword 0x38000000
		opword 0x901F01E0
		opword 0x901F01DC
		opword 0x901F01EC
		opword 0x901F01F0
		opword 0xC03F0180
		opword 0xC05F01A0
		bl marioCheckWallShip
		opword 0xC03F0180
		lfs f0, float_0p5_8041ada8(r2)
		opword 0xFC010040
		opword 0x40800014
		lfs f0, float_0_8041ada0(r2)
		opword 0x38000032
		opword 0xD01F0180
		opword 0x901F0044
		opword 0xC3DF0180
		bl marioGetPtr
		lfs f0, float_0_8041ada0(r2)
		opword 0x7C7D1B78
		opword 0xFC1E0000
		opword 0x40820074
		bl marioGetPtr
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_180_8041adc0(r2)
		opword 0xC0230008
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182000C
		lfs f30, float_0p3_8041ae70(r2)
		opword 0x48000008
		lfs f30, float_0p6_8041ae74(r2)
		bl marioGetPtr
		opword 0x83C30288
		opword 0xC3FE0010
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0p1_8041ae14(r2)
		opword 0xC0230010
		opword 0xEC3E0828
		opword 0xEC00F87A
		opword 0xD01E0010
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3C30010
		opword 0xC3FD008C
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_0_8041ada0(r2)
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30004
		opword 0xC03D0090
		opword 0xEFE1002A
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30008
		opword 0xC3FD0094
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E3000C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3C30010
		opword 0xC3FD01A8
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630024
		opword 0x8063000C
		opword 0xD3E30014
		opword 0xA01F0248
		opword 0x70000A00
		opword 0x41820024
		bl marioGetPtr
		opword 0x80630288
		opword 0x3863003C
		bl checkHarbor
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3800001E
		opword 0x901F0044
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

void marioShipChgFall(void) {
	MarioWork* m = marioGetPtr();
	if (!(m->flags & 0x20000)) {
		m->flags |= 0x20000;
#ifdef NONMATCHING
		*(f32*)((u8*)m + 0x7C) = -0.1f;
		*(f32*)((u8*)m + 0x80) = -0.2f;
		*(f32*)((u8*)m + 0x84) = 0.024f;
		*(f32*)((u8*)m + 0x88) = -0.004f;
#endif
#ifndef NONMATCHING
		*(f32*)((u8*)m + 0x7C) = EXT_LIT(float_neg0p1_8041add4, -0.1f);
		*(f32*)((u8*)m + 0x80) = EXT_LIT(float_neg0p2_8041add8, -0.2f);
		*(f32*)((u8*)m + 0x84) = EXT_LIT(float_0p024_8041addc, 0.024f);
		*(f32*)((u8*)m + 0x88) = EXT_LIT(float_neg0p004_8041ade0, -0.004f);
#endif
	}
}

BOOL marioChkShipMoveMode(void) {
	MarioWork* m = marioGetPtr();
	if (m->currMotionId != MARIO_MOTION_SHIP) {
		return FALSE;
	}
	if ((s32)m->currSubMotionId >= 50 && (s32)m->currSubMotionId <= 52) {
		return TRUE;
	}
	return FALSE;
}

double sin(double);
double cos(double);

#define SHIP_WORK ((ShipWork*)marioGetPtr()->motStruct)
#define SHIP_DISP ((ShipDir*)marioGetPtr()->motStruct)
#define SHIP_SFX (*(u32*)((u8*)marioGetPtr()->motStruct + 0x38))

#ifdef NONMATCHING
void shipMove(void)
{
  MarioWork *m = marioGetPtr();
  f32 len;
  unsigned long long new_var;
  f32 vz;
  f32 spd;
  f32 tz;
  f32 vx;
  f32 tx;
  f32 max;
  f32 dx;
  f32 dz;
  f32 fr;
  s32 snd;
  spd = *((f32 *) (((u8 *) m) + 0x190));
  dx = 0.0f;
  dx = 0.0f;
  if (((ShipWork *) marioGetPtr()->motStruct)->swirlTime != 0)
  {
    ((ShipWork *) marioGetPtr()->motStruct)->swirlTime--;
    movePos(&dx, &dz, ((ShipWork *) marioGetPtr()->motStruct)->swirlX, ((ShipWork *) marioGetPtr()->motStruct)->swirlY);
    ((ShipDir *) marioGetPtr()->motStruct)->dispX += dx;
    ((ShipDir *) marioGetPtr()->motStruct)->dispY += dz;
    vz = shipData[4];
    if (((ShipDir *) marioGetPtr()->motStruct)->dispX > vz)
    {
      vz = shipData[4];
      ((ShipDir *) marioGetPtr()->motStruct)->dispX = vz;
    }
    if (((ShipDir *) marioGetPtr()->motStruct)->dispX < (-shipData[4]))
    {
      ((ShipDir *) marioGetPtr()->motStruct)->dispX = -shipData[4];
    }
    vz = shipData[4];
    if (((ShipDir *) marioGetPtr()->motStruct)->dispY > vz)
    {
      vz = shipData[4];
      ((ShipDir *) marioGetPtr()->motStruct)->dispY = vz;
    }
    if (((ShipDir *) marioGetPtr()->motStruct)->dispY < (-shipData[4]))
    {
      ((ShipDir *) marioGetPtr()->motStruct)->dispY = -shipData[4];
    }
  }
  vx = ((ShipDir *) marioGetPtr()->motStruct)->dispX;
  vz = ((ShipDir *) marioGetPtr()->motStruct)->dispY;
  new_var = 3;
  if (*((f32 *) (((u8 *) m) + 0x190)))
  {
    tx = spd * ((f32) sin((3.1415927f * (*((f32 *) (((u8 *) m) + 0x194)))) / 180.0f));
    tz = spd * (-((f32) cos((3.1415927f * (*((f32 *) (((u8 *) m) + 0x194)))) / 180.0f)));
  }
  else
  {
    tx = vx;
    tz = vz;
  }
  max = shipData[4];
  if (spd || (((ShipWork *) marioGetPtr()->motStruct)->swirlTime != 0))
  {
    if (tx > vx)
    {
      vx += ((1.0f + tx) - vx) * shipData[new_var];
      if (vx >= max)
      {
        vx = max;
      }
    }
    else
    {
      vx += ((tx - 1.0f) - vx) * shipData[new_var];
      if (vx <= (-max))
      {
        vx = -max;
      }
    }
    if (tz > vz)
    {
      vz += ((1.0f + tz) - vz) * shipData[new_var];
      if (max <= vz)
      {
        vz = max;
      }
    }
    else
    {
      vz += ((tz - 1.0f) - vz) * shipData[new_var];
      if (vz <= (-max))
      {
        vz = -max;
      }
    }
  }
  if (!spd)
  {
    fr = shipData[0];
    if (((u32) (*((s32 *) (((u8 *) m) + 0x1F0)))) != 0)
    {
      fr = shipData[1];
    }
    fr = __fabsf(fr);
    vx += (-vx) * fr;
    vz += (-vz) * fr;
    if (__fabsf(vx) < 0.01f)
    {
      vx = 0.0f;
    }
    if (__fabsf(vz) < 0.01f)
    {
      vz = 0.0f;
    }
  }
  ((ShipDir *) marioGetPtr()->motStruct)->dispX = vx;
  ((ShipDir *) marioGetPtr()->motStruct)->dispY = vz;
  len = distABf(0.0f, 0.0f, vx, vz);
  if (spd)
  {
    if (len >= shipData[4])
    {
      len = shipData[4];
    }
  }
  else
    if (len < shipData[5])
  {
    len = 0.0f;
    ((ShipDir *) marioGetPtr()->motStruct)->dispX = 0.0f;
    ((ShipDir *) marioGetPtr()->motStruct)->dispY = 0.0f;
  }
  *((f32 *) (((u8 *) m) + 0x180)) = len;
  if (len)
  {
    *((f32 *) (((u8 *) m) + 0x1A0)) = angleABf(0.0f, 0.0f, ((ShipDir *) marioGetPtr()->motStruct)->dispX, ((ShipDir *) marioGetPtr()->motStruct)->dispY);
  }
  if (len >= 1.0f)
  {
    MarioWork *mm = marioGetPtr();
    if ((marioGetPtr()->motStruct != ((void *) 0)) && (((u32) (*((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)))) == 0xFFFFFFFFU))
    {
      snd = psndSFXOn_3D((const char *) 0x190, (Vec *) (((u8 *) mm) + 0x8C));
      *((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)) = snd;
    }
  }
  else
    if (len <= 0.2f)
  {
    marioGetPtr();
    if ((marioGetPtr()->motStruct != ((void *) 0)) && (((u32) (*((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)))) != 0xFFFFFFFFU))
    {
      psndSFXOff(*((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)));
      snd = -1;
      *((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)) = snd;
    }
  }
  if (((u32) (*((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)))) != 0xFFFFFFFFU)
  {
    psndSFX_pos(*((s32 *) (((u8 *) marioGetPtr()->motStruct) + 0x38)), (Vec *) (((u8 *) m) + 0x8C));
  }
  *((f32 *) (((u8 *) m) + 0x18C)) = len;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void shipMove(void) {
	char _af_pad[8];
	asm volatile {
		bl marioGetPtr
		opword 0x7C7F1B78
		lfs f0, float_0_8041ada0(r2)
		opword 0xC3C30190
		stfs f0, _af_pad+4(r1)
		opword 0xD001000C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030030
		opword 0x2C000000
		opword 0x41820110
		bl marioGetPtr
		opword 0x80830288
		opword 0x80640030
		opword 0x3803FFFF
		opword 0x90040030
		bl marioGetPtr
		opword 0x83C30288
		bl marioGetPtr
		opword 0x80A30288
		opword 0x3861000C
		opword 0xC05E0028
		opword 0x38810008
		opword 0xC025002C
		bl movePos
		bl marioGetPtr
		opword 0x80630288
		opword 0xC001000C
		opword 0xC0230014
		opword 0xEC01002A
		opword 0xD0030014
		bl marioGetPtr
		opword 0x80630288
		la r30, shipData(r13)
		opword 0xC0010008
		opword 0xC0230018
		opword 0xEC01002A
		opword 0xD0030018
		opword 0xC37E0010
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030014
		opword 0xFC00D840
		opword 0x40810014
		opword 0xC37E0010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3630014
		bl marioGetPtr
		opword 0xC01E0010
		opword 0x80630288
		opword 0xFF600050
		opword 0xC0030014
		opword 0xFC00D840
		opword 0x40800010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3630014
		opword 0xC37E0010
		bl marioGetPtr
		opword 0x80630288
		opword 0xC0030018
		opword 0xFC00D840
		opword 0x40810014
		opword 0xC37E0010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3630018
		bl marioGetPtr
		opword 0xC01E0010
		opword 0x80630288
		opword 0xFF600050
		opword 0xC0030018
		opword 0xFC00D840
		opword 0x40800010
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3630018
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3830014
		bl marioGetPtr
		opword 0xC03F0190
		lfs f0, float_0_8041ada0(r2)
		opword 0x80630288
		opword 0xFC010000
		opword 0xC3630018
		opword 0x4182004C
		lfs f2, float_3p1416_8041adc4(r2)
		opword 0xC03F0194
		lfs f0, float_180_8041adc0(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		lfs f2, float_3p1416_8041adc4(r2)
		opword 0xFC600818
		opword 0xC03F0194
		lfs f0, float_180_8041adc0(r2)
		opword 0xEC220072
		fmuls f26, f30, f3
		opword 0xEC210024
		bl cos
		opword 0xFC000818
		opword 0xFC000050
		opword 0xEFBE0032
		opword 0x4800000C
		opword 0xFF40E090
		opword 0xFFA0D890
		lfs f0, float_0_8041ada0(r2)
		la r30, shipData(r13)
		opword 0xC3FE0010
		opword 0xFC1E0000
		opword 0x40820018
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030030
		opword 0x2C000000
		opword 0x418200C4
		opword 0xFC1AE040
		opword 0x40810030
		lfs f1, float_1_8041adc8(r2)
		la r3, shipData(r13)
		opword 0xC003000C
		opword 0xEC21D02A
		opword 0xEC21E028
		opword 0xEF81E03A
		opword 0xFC1CF840
		opword 0x4C411382
		opword 0x40820038
		opword 0xFF80F890
		opword 0x48000030
		lfs f1, float_1_8041adc8(r2)
		la r3, shipData(r13)
		opword 0xC003000C
		opword 0xFC40F850
		opword 0xEC3A0828
		opword 0xEC21E028
		opword 0xEF81E03A
		opword 0xFC1C1040
		opword 0x4C401382
		opword 0x40820008
		opword 0xFF801090
		opword 0xFC1DD840
		opword 0x40810030
		lfs f1, float_1_8041adc8(r2)
		la r3, shipData(r13)
		opword 0xC003000C
		opword 0xEC21E82A
		opword 0xEC21D828
		opword 0xEF61D83A
		opword 0xFC1BF840
		opword 0x4C411382
		opword 0x40820038
		opword 0xFF60F890
		opword 0x48000030
		lfs f1, float_1_8041adc8(r2)
		la r3, shipData(r13)
		opword 0xC003000C
		opword 0xFC40F850
		opword 0xEC3D0828
		opword 0xEC21D828
		opword 0xEF61D83A
		opword 0xFC1B1040
		opword 0x4C401382
		opword 0x40820008
		opword 0xFF601090
		lfs f0, float_0_8041ada0(r2)
		opword 0xFC1E0000
		opword 0x40820058
		opword 0x801F01F0
		lfs f0, shipData(r13)
		opword 0x28000000
		opword 0x4182000C
		la r3, shipData(r13)
		opword 0xC0030004
		opword 0xFC600210
		lfs f0, float_0p01_8041adcc(r2)
		opword 0xFC40E050
		opword 0xFC20D850
		opword 0xEF82E0FA
		opword 0xEF61D8FA
		opword 0xFC20E210
		opword 0xFC010040
		opword 0x40800008
		lfs f28, float_0_8041ada0(r2)
		opword 0xFC20DA10
		lfs f0, float_0p01_8041adcc(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f27, float_0_8041ada0(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3830014
		bl marioGetPtr
		lfs f1, float_0_8041ada0(r2)
		opword 0xFC60E090
		opword 0x80630288
		opword 0xFC80D890
		opword 0xFC400890
		opword 0xD3630018
		bl distABf
		lfs f28, float_0_8041ada0(r2)
		opword 0xFFA00890
		opword 0xFC1EE000
		opword 0x4182001C
		opword 0xC01E0010
		opword 0xFC1D0040
		opword 0x4C411382
		opword 0x4082003C
		opword 0xFFA00090
		opword 0x48000034
		la r3, shipData(r13)
		opword 0xC0030014
		opword 0xFC1D0040
		opword 0x40800024
		opword 0xFFA0E090
		bl marioGetPtr
		opword 0x80630288
		lfs f27, float_0_8041ada0(r2)
		opword 0xD3830014
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3630018
		lfs f0, float_0_8041ada0(r2)
		opword 0xD3BF0180
		opword 0xFC1D0000
		opword 0x4182002C
		bl marioGetPtr
		opword 0x83C30288
		bl marioGetPtr
		lfs f1, float_0_8041ada0(r2)
		opword 0x80630288
		opword 0xFC400890
		opword 0xC09E0018
		opword 0xC0630014
		bl angleABf
		opword 0xD03F01A0
		lfs f0, float_1_8041adc8(r2)
		opword 0xFC1D0040
		opword 0x4C411382
		opword 0x40820054
		bl marioGetPtr
		opword 0x7C7E1B78
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x41820098
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630038
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x40820080
		opword 0x389E008C
		opword 0x38600190
		bl psndSFXOn_3D
		opword 0x7C7E1B78
		bl marioGetPtr
		opword 0x80630288
		opword 0x93C30038
		opword 0x48000060
		lfs f0, float_0p2_8041add0(r2)
		opword 0xFC1D0040
		opword 0x4C401382
		opword 0x40820050
		bl marioGetPtr
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x4182003C
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630038
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820024
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630038
		bl psndSFXOff
		opword 0x3BC0FFFF
		bl marioGetPtr
		opword 0x80630288
		opword 0x93C30038
		bl marioGetPtr
		opword 0x80630288
		opword 0x80630038
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820018
		bl marioGetPtr
		opword 0x80630288
		opword 0x389F008C
		opword 0x80630038
		bl psndSFX_pos
		opword 0xD3BF018C
	}
#endif
}
#ifdef NONMATCHING
void shipStrippedPool(f32* p) { p[0] = 15.0f; p[1] = 50.0f; p[2] = 30.30303f; p[3] = 180.0f; p[4] = 3.1415927f; }
#endif
#ifndef NONMATCHING
#pragma pop
#endif


#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
BOOL checkHarbor(Vec* out) {
#ifdef NONMATCHING
	f32 ix, iy, iz;
	f32 tx, ty, tz, sn, cs, hx, hy, hz, dist, nx, ny, nz;
	Vec p1, p2, p3;
	HitEntry* hit;
	MarioWork* m = marioGetPtr();
	HARBOR_PROBE(m->displayDirection, p1)
	HARBOR_PROBE(90.0f + m->displayDirection, p2)
	HARBOR_PROBE(m->displayDirection - 90.0f, p3)
	return FALSE;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0x93E1008C
		opword 0x7C7F1B78
		opword 0x93C10088
		opword 0x93A10084
		opword 0x93810080
		bl marioGetPtr
		opword 0x7C7E1B78
		opword 0xC02301A8
		bl toMovedir
		opword 0x38610028
		opword 0x38810024
		bl sincosf
		lfs f7, float_40_8041ad98(r2)
		opword 0x38810020
		opword 0xC0210028
		opword 0x38A1001C
		opword 0xC01E008C
		opword 0x38C10018
		lfs f4, float_0_8041ada0(r2)
		opword 0x38E10014
		opword 0xEC27007A
		opword 0xC0A10024
		opword 0xC07E0094
		opword 0xFCC02090
		opword 0xC01E0090
		opword 0x39010010
		lfs f2, float_20_8041ad9c(r2)
		opword 0xEC67197A
		opword 0xD0E10014
		opword 0x3921000C
		opword 0xEC42002A
		lfs f5, float_neg1_8041ada4(r2)
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7C1B79
		opword 0x41820110
		opword 0x3BA00000
		bl hitGetAttr
		opword 0x54600463
		opword 0x4182000C
		opword 0x3BA00001
		opword 0x48000030
		opword 0x54600421
		opword 0x4182000C
		opword 0x3BA00002
		opword 0x48000020
		opword 0x546003DF
		opword 0x4182000C
		opword 0x3BA00003
		opword 0x48000010
		opword 0x5460039D
		opword 0x41820008
		opword 0x3BA00004
		opword 0x2C1D0000
		opword 0x418200C4
		opword 0x7F83E378
		bl hitGetName
		opword 0x38810044
		bl hitObjGetPos
		lfs f4, float_100_8041adac(r2)
		opword 0x3C004330
		lfs f3, float_0p5_8041ada8(r2)
		lis r3, double_to_int_802c5e50@ha
		opword 0xC0010044
		addi r4, r3, double_to_int_802c5e50@l
		opword 0xC0410048
		opword 0x38600001
		opword 0xEC04183A
		opword 0xC021004C
		opword 0xEC4418BA
		opword 0x90010078
		opword 0xEC24187A
		opword 0xC8640000
		opword 0xEC002024
		opword 0x90010058
		opword 0x90010068
		opword 0xEC422024
		opword 0xEC212024
		opword 0xFC00001E
		opword 0xFC40101E
		opword 0xFC20081E
		opword 0xD8010070
		opword 0xD8410050
		opword 0x80010074
		opword 0xD8210060
		opword 0x6C008000
		opword 0x80810054
		opword 0x9001007C
		opword 0x6C848000
		opword 0x80010064
		opword 0x9081005C
		opword 0xC8010078
		opword 0x6C008000
		opword 0x9001006C
		opword 0xEC001828
		opword 0xC8410058
		opword 0xC8210068
		opword 0xEC421828
		opword 0xD01F0000
		opword 0xEC011828
		opword 0xD05F0004
		opword 0xD01F0008
		opword 0x48000320
		lfs f1, float_90_8041adb0(r2)
		opword 0xC01E01A8
		opword 0xEC21002A
		bl toMovedir
		opword 0x38610028
		opword 0x38810024
		bl sincosf
		lfs f7, float_40_8041ad98(r2)
		opword 0x38810020
		opword 0xC0210028
		opword 0x38A1001C
		opword 0xC01E008C
		opword 0x38C10018
		lfs f4, float_0_8041ada0(r2)
		opword 0x38E10014
		opword 0xEC27007A
		opword 0xC0A10024
		opword 0xC07E0094
		opword 0xFCC02090
		opword 0xC01E0090
		opword 0x39010010
		lfs f2, float_20_8041ad9c(r2)
		opword 0xEC67197A
		opword 0xD0E10014
		opword 0x3921000C
		opword 0xEC42002A
		lfs f5, float_neg1_8041ada4(r2)
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7C1B79
		opword 0x41820110
		opword 0x3BA00000
		bl hitGetAttr
		opword 0x54600463
		opword 0x4182000C
		opword 0x3BA00001
		opword 0x48000030
		opword 0x54600421
		opword 0x4182000C
		opword 0x3BA00002
		opword 0x48000020
		opword 0x546003DF
		opword 0x4182000C
		opword 0x3BA00003
		opword 0x48000010
		opword 0x5460039D
		opword 0x41820008
		opword 0x3BA00004
		opword 0x2C1D0000
		opword 0x418200C4
		opword 0x7F83E378
		bl hitGetName
		opword 0x38810038
		bl hitObjGetPos
		lfs f4, float_100_8041adac(r2)
		opword 0x3C004330
		lfs f3, float_0p5_8041ada8(r2)
		lis r3, double_to_int_802c5e50@ha
		opword 0xC0010038
		addi r4, r3, double_to_int_802c5e50@l
		opword 0xC041003C
		opword 0x38600001
		opword 0xEC04183A
		opword 0xC0210040
		opword 0xEC4418BA
		opword 0x90010050
		opword 0xEC24187A
		opword 0xC8640000
		opword 0xEC002024
		opword 0x90010070
		opword 0x90010060
		opword 0xEC422024
		opword 0xEC212024
		opword 0xFC00001E
		opword 0xFC40101E
		opword 0xFC20081E
		opword 0xD8010058
		opword 0xD8410078
		opword 0x8001005C
		opword 0xD8210068
		opword 0x6C008000
		opword 0x8081007C
		opword 0x90010054
		opword 0x6C848000
		opword 0x8001006C
		opword 0x90810074
		opword 0xC8010050
		opword 0x6C008000
		opword 0x90010064
		opword 0xEC001828
		opword 0xC8410070
		opword 0xC8210060
		opword 0xEC421828
		opword 0xD01F0000
		opword 0xEC011828
		opword 0xD05F0004
		opword 0xD01F0008
		opword 0x48000194
		opword 0xC03E01A8
		lfs f0, float_90_8041adb0(r2)
		opword 0xEC210028
		bl toMovedir
		opword 0x38610028
		opword 0x38810024
		bl sincosf
		lfs f7, float_40_8041ad98(r2)
		opword 0x38810020
		opword 0xC0210028
		opword 0x38A1001C
		opword 0xC01E008C
		opword 0x38C10018
		lfs f4, float_0_8041ada0(r2)
		opword 0x38E10014
		opword 0xEC27007A
		opword 0xC0A10024
		opword 0xC07E0094
		opword 0xFCC02090
		opword 0xC01E0090
		opword 0x39010010
		lfs f2, float_20_8041ad9c(r2)
		opword 0xEC67197A
		opword 0xD0E10014
		opword 0x3921000C
		opword 0xEC42002A
		lfs f5, float_neg1_8041ada4(r2)
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7E1B79
		opword 0x41820110
		opword 0x3BA00000
		bl hitGetAttr
		opword 0x54600463
		opword 0x4182000C
		opword 0x3BA00001
		opword 0x48000030
		opword 0x54600421
		opword 0x4182000C
		opword 0x3BA00002
		opword 0x48000020
		opword 0x546003DF
		opword 0x4182000C
		opword 0x3BA00003
		opword 0x48000010
		opword 0x5460039D
		opword 0x41820008
		opword 0x3BA00004
		opword 0x2C1D0000
		opword 0x418200C4
		opword 0x7FC3F378
		bl hitGetName
		opword 0x3881002C
		bl hitObjGetPos
		lfs f4, float_100_8041adac(r2)
		opword 0x3C004330
		lfs f3, float_0p5_8041ada8(r2)
		lis r3, double_to_int_802c5e50@ha
		opword 0xC001002C
		addi r4, r3, double_to_int_802c5e50@l
		opword 0xC0410030
		opword 0x38600001
		opword 0xEC04183A
		opword 0xC0210034
		opword 0xEC4418BA
		opword 0x90010050
		opword 0xEC24187A
		opword 0xC8640000
		opword 0xEC002024
		opword 0x90010070
		opword 0x90010060
		opword 0xEC422024
		opword 0xEC212024
		opword 0xFC00001E
		opword 0xFC40101E
		opword 0xFC20081E
		opword 0xD8010058
		opword 0xD8410078
		opword 0x8001005C
		opword 0xD8210068
		opword 0x6C008000
		opword 0x8081007C
		opword 0x90010054
		opword 0x6C848000
		opword 0x8001006C
		opword 0x90810074
		opword 0xC8010050
		opword 0x6C008000
		opword 0x90010064
		opword 0xEC001828
		opword 0xC8410070
		opword 0xC8210060
		opword 0xEC421828
		opword 0xD01F0000
		opword 0xEC011828
		opword 0xD05F0004
		opword 0xD01F0008
		opword 0x48000008
		opword 0x38600000
		opword 0x80010094
		opword 0x83E1008C
		opword 0x83C10088
		opword 0x83A10084
		opword 0x83810080
		opword 0x7C0803A6
		opword 0x38210090
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif


// prototypes for asm stopgap forward references
BOOL checkHarbor(Vec* out);
void shipMove(void);
BOOL marioChkShipMoveMode(void);
void marioShipChgFall(void);
void mot_ship(void);
void mot_ship_post(void);
void marioReInit_ship(void);
void marioForceShipAnime(void);
BOOL marioChkShipPlace(HitEntry* hit);
void marioShipSetDispDir(void);
void marioShipForceStop(void);
BOOL marioChkSwirlPower(void);
void marioSetSwirlPower(s32 msec, f32 a, f32 b);
s32 marioShipChanging(void);
s32 N_marioShipGetDir(void);

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char str_802C5E00[] = "SFX_MARIO_SHIP1_1\0\0";
__declspec(section ".rodata") const char str_802C5E14[] = "SFX_MARIO_SHIP2";
__declspec(section ".rodata") const char str_802C5E24[] = "p_hune\0";
__declspec(section ".rodata") const char str_802C5E2C[] = "p_hune_g\0\0\0";
__declspec(section ".rodata") const char str_802C5E38[] = "p_hune_y\0\0\0";
__declspec(section ".rodata") const char str_802C5E44[] = "p_hune_v\0\0\0";
__declspec(section ".rodata") const f64 double_to_int_802c5e50 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802C5E58[] = "M_J_1B\0";
__declspec(section ".rodata") const char str_802C5E60[] = "PM_H_1A";
__declspec(section ".rodata") const char str_802C5E68[] = "dou_03\0";
__declspec(section ".rodata") const char str_802C5E70[] = "PM_H_1B";
__declspec(section ".sdata2") const f32 float_40_8041ad98 = 40.0f;
__declspec(section ".sdata2") const f32 float_20_8041ad9c = 20.0f;
__declspec(section ".sdata2") const f32 float_0_8041ada0 = 0.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041ada4 = -1.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041ada8 = 0.5f;
__declspec(section ".sdata2") const f32 float_100_8041adac = 100.0f;
__declspec(section ".sdata2") const f32 float_90_8041adb0 = 90.0f;
__declspec(section ".sdata2") const f32 float_15_8041adb4 = 15.0f;
__declspec(section ".sdata2") const f32 float_50_8041adb8 = 50.0f;
__declspec(section ".sdata2") const f32 float_30p303_8041adbc = 30.30303f;
__declspec(section ".sdata2") const f32 float_180_8041adc0 = 180.0f;
__declspec(section ".sdata2") const f32 float_3p1416_8041adc4 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_1_8041adc8 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p01_8041adcc = 0.01f;
__declspec(section ".sdata2") const f32 float_0p2_8041add0 = 0.2f;
__declspec(section ".sdata2") const f32 float_neg0p1_8041add4 = -0.1f;
__declspec(section ".sdata2") const f32 float_neg0p2_8041add8 = -0.2f;
__declspec(section ".sdata2") const f32 float_0p024_8041addc = 0.024f;
__declspec(section ".sdata2") const f32 float_neg0p004_8041ade0 = -0.004f;
__declspec(section ".sdata2") const f32 float_4p25_8041ade4 = 4.25f;
__declspec(section ".sdata2") const f32 float_30_8041ade8 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg30_8041adec = -30.0f;
__declspec(section ".sdata2") const f32 float_0p125_8041adf0 = 0.125f;
__declspec(section ".sdata2") const f32 float_270_8041adf4 = 270.0f;
__declspec(section ".sdata2") const f32 float_neg270_8041adf8 = -270.0f;
__declspec(section ".sdata2") const char str_8041ADFC[] = "M_Z_1\0\0";
__declspec(section ".sdata2") const f32 float_1024_8041ae04 = 1024.0f;
__declspec(section ".sdata2") const f32 float_1260_8041ae08 = 1260.0f;
__declspec(section ".sdata2") const f32 float_neg1080_8041ae0c = -1080.0f;
__declspec(section ".sdata2") const f32 float_neg15_8041ae10 = -15.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041ae14 = 0.1f;
__declspec(section ".sdata2") const f32 float_1620_8041ae18 = 1620.0f;
__declspec(section ".sdata2") const f32 float_neg1440_8041ae1c = -1440.0f;
__declspec(section ".sdata2") const f32 float_36_8041ae20 = 36.0f;
__declspec(section ".sdata2") const f32 float_306_8041ae24 = 306.0f;
__declspec(section ".sdata2") const f32 float_neg0p4_8041ae28 = -0.4f;
__declspec(section ".sdata2") const f32 float_neg18_8041ae2c = -18.0f;
__declspec(section ".sdata2") const f32 float_1p6_8041ae30 = 1.6f;
__declspec(section ".sdata2") const f32 float_2p8_8041ae34 = 2.8f;
__declspec(section ".sdata2") const f32 float_10_8041ae38 = 10.0f;
__declspec(section ".sdata2") const f32 float_2_8041ae3c = 2.0f;
__declspec(section ".sdata2") const f32 float_80_8041ae40 = 80.0f;
__declspec(section ".sdata2") const f32 float_neg20_8041ae44 = -20.0f;
__declspec(section ".sdata2") const f32 float_360_8041ae48 = 360.0f;
__declspec(section ".sdata2") const f32 float_0p05_8041ae4c = 0.05f;
__declspec(section ".sdata2") const f32 float_neg0p005_8041ae50 = -0.005f;
__declspec(section ".sdata2") const f32 float_neg360_8041ae54 = -360.0f;
__declspec(section ".sdata2") const f32 float_4_8041ae58 = 4.0f;
__declspec(section ".sdata2") const f32 float_neg4_8041ae5c = -4.0f;
__declspec(section ".sdata2") const f32 float_540_8041ae60 = 540.0f;
__declspec(section ".sdata2") const f32 float_37_8041ae64 = 37.0f;
__declspec(section ".sdata2") const f32 float_neg13_8041ae68 = -13.0f;
__declspec(section ".sdata2") const f32 float_3_8041ae6c = 3.0f;
__declspec(section ".sdata2") const f32 float_0p3_8041ae70 = 0.3f;
__declspec(section ".sdata2") const f32 float_0p6_8041ae74 = 0.6f;
__declspec(section ".sdata2") const f32 float_neg7_8041ae78 = -7.0f;
__declspec(section ".sdata2") const f32 float_260_8041ae7c = 260.0f;

#endif