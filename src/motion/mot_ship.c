#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_sbr.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

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

f32 shipData[6] = {-0.05f, -0.7f, 0.02f, 0.02f, 2.0f, 0.01f};
const char* paper_ship[4] = {"p_hune", "p_hune_g", "p_hune_y", "p_hune_v"};

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

#define HARBOR_PROBE(ANG, POS)                                                                                     	sincosf(&sn, &cs, toMovedir(ANG));                                                                             	dist = 40.0f;                                                                                                  	hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, dist * sn + m->position.x,                      	                     20.0f + m->position.y, dist * cs + m->position.z, 0.0f, -1.0f, 0.0f);                     	if (hit != NULL && harborKind(hit) != 0) {                                                                     		hitObjGetPos(hitGetName(hit), &POS);                                                                       		ix = (s32)((100.0f * POS.x + 0.5f) / 100.0f);                                                              		iy = (s32)((100.0f * POS.y + 0.5f) / 100.0f);                                                              		iz = (s32)((100.0f * POS.z + 0.5f) / 100.0f);                                                              		out->x = ix;                                                                                               		out->y = iy;                                                                                               		out->z = iz;                                                                                               		return TRUE;                                                                                               	}

BOOL checkHarbor(Vec* out) {
	s32 ix, iy, iz;
	f32 sn, cs, hx, hy, hz, dist, nx, ny, nz;
	Vec p1, p2, p3;
	HitEntry* hit;
	MarioWork* m = marioGetPtr();
	HARBOR_PROBE(m->unk1A8, p1)
	HARBOR_PROBE(90.0f + m->unk1A8, p2)
	HARBOR_PROBE(m->unk1A8 - 90.0f, p3)
	return FALSE;
}

#define MSF(m, o) (*(f32*)((u8*)(m) + (o)))
#define MSI(m, o) (*(s32*)((u8*)(m) + (o)))
#define MSP(m, o) (*(void**)((u8*)(m) + (o)))
#define MSO(o) (*(s32*)((u8*)marioGetPtr()->motStruct + (o)))
#define MSOF(o) (*(f32*)((u8*)marioGetPtr()->motStruct + (o)))

void allPartyRideOff(void);
void allPartyForceRideOn(void);
void* effFunemizuEntry(s32, f32, f32, f32, f32, f32);

void mot_ship_post(void) {
	MarioWork* m = marioGetPtr();
	s32 t;
	allPartyRideOff();
	if (m->dispFlags & 0x40000000) {
		marioPaperOff();
	}
	MSF(m, 0x1B4) = 20.0f;
	MSF(m, 0x1B8) = 37.0f;
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

void marioReInit_ship(void) {
	MarioWork* m = marioGetPtr();
	void* p;
	s32 t, u;
	f32 a, b;
	m->trigFlags &= ~1;
	p = __memAlloc(HEAP_DEFAULT, 0x48);
	marioGetPtr()->motStruct = p;
	memset(marioGetPtr()->motStruct, 0, 0x48);
	*(s16*)((u8*)m + 0x2E) = 0x19;
	MSF(m, 0x9C) = -15.0f;
	MSI(m, 0x44) = 0x32;
	MSF(m, 0x1B4) = 40.0f;
	MSF(m, 0x1B8) = 40.0f;
	marioPaperOn(paper_ship[marioGetColor()]);
	marioChgPaper("PM_H_1B");
	marioChgPose("M_J_1B");
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
	u = MSI(m, 0x134);
	*(s32*)((u8*)*(void**)((u8*)*(void**)((u8*)marioGetPtr()->motStruct + 0x24) + 0xC) + 0x48) = u;
	allPartyForceRideOn();
}

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
	if (m->currSubMotionId == 10) {
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

void marioShipForceStop(void) {
	f32 a = 0.0f;
	f32 b;
	marioGetPtr();
	b = 0.0f;
	((ShipDir*)marioGetPtr()->motStruct)->dispX = a;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = b;
}

void marioShipSetDispDir(void) {
	f32 a = 0.0f;
	f32 b;
	marioGetPtr();
	b = 0.0f;
	((ShipDir*)marioGetPtr()->motStruct)->dispX = a;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = b;
}

BOOL marioChkShipPlace(HitEntry* hit) {
	return (hitGetAttr(hit) & 0x3C000) != 0;
}

void marioForceShipAnime(void) {
	MarioWork* m = marioGetPtr();
	marioPaperOff();
	marioChgPaper(NULL);
	marioPaperOn(paper_ship[marioGetColor()]);
	marioChgPaper("PM_H_1B");
	marioChgPose("M_J_1B");
	m->trigFlags |= 8;
}

void marioShipChgFall(void) {
	MarioWork* m = marioGetPtr();
	if (!(m->flags & 0x20000)) {
		m->flags |= 0x20000;
		*(f32*)((u8*)m + 0x7C) = -0.1f;
		*(f32*)((u8*)m + 0x80) = -0.2f;
		*(f32*)((u8*)m + 0x84) = 0.024f;
		*(f32*)((u8*)m + 0x88) = -0.004f;
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
