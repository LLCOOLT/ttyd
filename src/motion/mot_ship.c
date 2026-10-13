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

#define HARBOR_PROBE(ANG, POS)                                                                                     	sincosf(&sn, &cs, toMovedir(ANG));                                                                             	tz = 40.0f * cs + m->position.z; dist = 40.0f; hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, 40.0f * sn + m->position.x,                      	                     20.0f + m->position.y, tz, 0.0f, -1.0f, 0.0f);                     	if (hit != NULL && harborKind(hit) != 0) {                                                                     		hitObjGetPos(hitGetName(hit), &POS);                                                                       		ix = (s32)((100.0f * POS.x + 0.5f) / 100.0f);                                                              		iy = (s32)((100.0f * POS.y + 0.5f) / 100.0f);                                                              		iz = (s32)((100.0f * POS.z + 0.5f) / 100.0f);                                                              		out->x = ix;                                                                                               		out->y = iy;                                                                                               		out->z = iz;                                                                                               		return TRUE;                                                                                               	}

__declspec(section ".sdata2") static const char s_MJ1B[] = "M_J_1B";
BOOL checkHarbor(Vec* out) {
	s32 ix, iy, iz;
	f32 tx, tz, sn, cs, hx, hy, hz, dist, nx, ny, nz;
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
	marioChgPose(s_MJ1B);
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
	marioChgPose(s_MJ1B);
	m->dispFlags |= 8;
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

f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
void movePos(float* ret_sin, float* ret_cos, f32 a3, f32 degree);
double sin(double);
double cos(double);

void shipMove(void) {
	MarioWork* m = marioGetPtr();
	f32 spd = MSF(m, 0x190);
	f32 dx, dz, vx, vz, tx, tz, max, len, fr;
	s32 snd;
	dx = 0.0f;
	dx = 0.0f;
	if (((ShipWork*)marioGetPtr()->motStruct)->swirlTime != 0) {
		((ShipWork*)marioGetPtr()->motStruct)->swirlTime--;
		movePos(&dx, &dz, ((ShipWork*)marioGetPtr()->motStruct)->swirlX, ((ShipWork*)marioGetPtr()->motStruct)->swirlY);
		((ShipDir*)marioGetPtr()->motStruct)->dispX += dx;
		((ShipDir*)marioGetPtr()->motStruct)->dispY += dz;
		if (((ShipDir*)marioGetPtr()->motStruct)->dispX > shipData[4]) {
			((ShipDir*)marioGetPtr()->motStruct)->dispX = shipData[4];
		}
		if (((ShipDir*)marioGetPtr()->motStruct)->dispX < -shipData[4]) {
			((ShipDir*)marioGetPtr()->motStruct)->dispX = -shipData[4];
		}
		if (((ShipDir*)marioGetPtr()->motStruct)->dispY > shipData[4]) {
			((ShipDir*)marioGetPtr()->motStruct)->dispY = shipData[4];
		}
		if (((ShipDir*)marioGetPtr()->motStruct)->dispY < -shipData[4]) {
			((ShipDir*)marioGetPtr()->motStruct)->dispY = -shipData[4];
		}
	}
	vx = ((ShipDir*)marioGetPtr()->motStruct)->dispX;
	vz = ((ShipDir*)marioGetPtr()->motStruct)->dispY;
	if (MSF(m, 0x190) != 0.0f) {
		tx = spd * (f32)sin(3.1416f * MSF(m, 0x194) / 180.0f);
		tz = spd * -(f32)cos(3.1416f * MSF(m, 0x194) / 180.0f);
	} else {
		tx = vx;
		tz = vz;
	}
	max = shipData[4];
	if (spd != 0.0f || ((ShipWork*)marioGetPtr()->motStruct)->swirlTime != 0) {
		if (tx > vx) {
			vx += (1.0f + tx - vx) * shipData[3];
			if (vx >= max) vx = max;
		} else {
			vx += (tx - 1.0f - vx) * shipData[3];
			if (vx <= -max) vx = -max;
		}
		if (tz > vz) {
			vz += (1.0f + tz - vz) * shipData[3];
			if (vz >= max) vz = max;
		} else {
			vz += (tz - 1.0f - vz) * shipData[3];
			if (vz <= -max) vz = -max;
		}
	}
	if (spd == 0.0f) {
		fr = shipData[0];
		if (MSI(m, 0x1F0) != 0) fr = shipData[1];
		fr = __fabs(fr);
		vx += -vx * fr;
		vz += -vz * fr;
		if (__fabs(vx) < 0.01f) vx = 0.0f;
		if (__fabs(vz) < 0.01f) vz = 0.0f;
	}
	((ShipDir*)marioGetPtr()->motStruct)->dispX = vx;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = vz;
	len = distABf(0.0f, 0.0f, vx, vz);
	if (spd != 0.0f) {
		if (len >= max) len = max;
	} else if (len < shipData[5]) {
		len = 0.0f;
		((ShipDir*)marioGetPtr()->motStruct)->dispX = 0.0f;
		((ShipDir*)marioGetPtr()->motStruct)->dispY = 0.0f;
	}
	MSF(m, 0x180) = len;
	if (len != 0.0f) {
		MSF(m, 0x1A0) = angleABf(0.0f, 0.0f, ((ShipDir*)marioGetPtr()->motStruct)->dispX, ((ShipDir*)marioGetPtr()->motStruct)->dispY);
	}
	if (len >= 1.0f) {
		MarioWork* mm = marioGetPtr();
		if (marioGetPtr()->motStruct != NULL && (u32)MSO(0x38) == 0xFFFFFFFFU) {
			snd = psndSFXOn_3D((const char*)0x190, (Vec*)((u8*)mm + 0x8C));
			MSO(0x38) = snd;
		}
	} else if (len <= 0.2f) {
		marioGetPtr();
		if (marioGetPtr()->motStruct != NULL && (u32)MSO(0x38) != 0xFFFFFFFFU) {
			psndSFXOff(MSO(0x38));
			snd = -1;
			MSO(0x38) = snd;
		}
	}
	if ((u32)MSO(0x38) != 0xFFFFFFFFU) {
		psndSFX_pos(MSO(0x38), (Vec*)((u8*)m + 0x8C));
	}
	MSF(m, 0x18C) = len;
}
