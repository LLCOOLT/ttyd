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

f32 shipData[6] = {-0.05f, -0.7f, 0.02f, 0.02f, 2.0f, 0.01f};
const char* paper_ship[4] = {(char*)str_802C5E24, (char*)str_802C5E2C, (char*)str_802C5E38, (char*)str_802C5E44};

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

#ifdef NONMATCHING
s32 N_marioShipGetDir(void) {
	marioGetPtr();
	if (marioGetPtr()->motStruct != NULL) {
		return (((ShipDir*)marioGetPtr()->motStruct)->flags >> 1) & 1;
	}
	return 0;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void marioSetSwirlPower(s32 msec, f32 a, f32 b) {
	s32 t;
	marioGetPtr();
	t = sysMsec2Frame(msec);
	((ShipWork*)marioGetPtr()->motStruct)->swirlTime = t;
	((ShipWork*)marioGetPtr()->motStruct)->swirlX = a;
	((ShipWork*)marioGetPtr()->motStruct)->swirlY = b;
}
#endif

#ifdef NONMATCHING
BOOL marioChkSwirlPower(void) {
	marioGetPtr();
	return ((ShipWork*)marioGetPtr()->motStruct)->swirlTime != 0;
}
#endif

#ifdef NONMATCHING
void marioShipForceStop(void) {
	f32 a = 0.0f;
	f32 b;
	marioGetPtr();
	b = 0.0f;
	((ShipDir*)marioGetPtr()->motStruct)->dispX = a;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = b;
}
#endif

#ifdef NONMATCHING
void marioShipSetDispDir(void) {
	f32 a = 0.0f;
	f32 b;
	marioGetPtr();
	b = 0.0f;
	((ShipDir*)marioGetPtr()->motStruct)->dispX = a;
	((ShipDir*)marioGetPtr()->motStruct)->dispY = b;
}
#endif

#ifdef NONMATCHING
BOOL marioChkShipPlace(HitEntry* hit) {
	return (hitGetAttr(hit) & 0x3C000) != 0;
}
#endif

#ifdef NONMATCHING
void marioForceShipAnime(void) {
	MarioWork* m = marioGetPtr();
	marioPaperOff();
	marioChgPaper(NULL);
	marioPaperOn(paper_ship[marioGetColor()]);
	marioChgPaper((char*)str_802C5E70);
	marioChgPose("M_Z_1");
	m->dispFlags |= 8;
}
#endif

#ifdef NONMATCHING
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
}
#endif

#ifdef NONMATCHING
void mot_ship_post(void) {
	MarioWork* m = marioGetPtr();
	s32 t;
	allPartyRideOff();
	if (m->dispFlags & 0x40000000) {
		marioPaperOff();
	}
	m->wPlayerCollisionBox.x = 20.0f;
	m->wPlayerCollisionBox.y = 37.0f;
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
#endif

#ifdef NONMATCHING
void mot_ship(void) {
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
	}
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

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
}
#endif
#ifdef NONMATCHING
void shipStrippedPool(f32* p) { p[0] = 15.0f; p[1] = 50.0f; p[2] = 30.30303f; p[3] = 180.0f; p[4] = 3.1415927f; }
#endif


#ifdef NONMATCHING
BOOL checkHarbor(Vec* out) {
	f32 ix, iy, iz;
	f32 tx, ty, tz, sn, cs, hx, hy, hz, dist, nx, ny, nz;
	Vec p1, p2, p3;
	HitEntry* hit;
	MarioWork* m = marioGetPtr();
	HARBOR_PROBE(m->displayDirection, p1)
	HARBOR_PROBE(90.0f + m->displayDirection, p2)
	HARBOR_PROBE(m->displayDirection - 90.0f, p3)
	return FALSE;
}
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
// ASM-STOPGAP: N_marioShipGetDir (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const char str_802C5E00[] = "SFX_MARIO_SHIP1_1\000\000";
#pragma force_active on
__declspec(section ".rodata") const char str_802C5E14[] = "SFX_MARIO_SHIP2";
__declspec(section ".rodata") const char str_802C5E24[] = "p_hune\000";
__declspec(section ".rodata") const char str_802C5E2C[] = "p_hune_g\000\000\000";
__declspec(section ".rodata") const char str_802C5E38[] = "p_hune_y\000\000\000";
__declspec(section ".rodata") const char str_802C5E44[] = "p_hune_v\000\000\000";
__declspec(section ".rodata") const f64 double_to_int_802c5e50 = 4503601774854144;
__declspec(section ".rodata") const char str_802C5E58[] = "M_J_1B\000";
__declspec(section ".rodata") const char str_802C5E60[] = "PM_H_1A";
__declspec(section ".rodata") const char str_802C5E68[] = "dou_03\000";
__declspec(section ".rodata") const char str_802C5E70[] = "PM_H_1B";
#pragma force_active reset
#pragma force_active on
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
__declspec(section ".sdata2") const char str_8041ADFC[8] = "M_Z_1\0\0";
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

void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);
void camFollowYOff(void);
void camFollowYOn(void);
CameraEntry* camGetPtr(CameraId cameraId);
void effDelete(EffectEntry* effect);
EventEntry* evtEntry(void* evtCode, u8 priority, u8 flags);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
s32 hitGetAttr(HitEntry* hit);
const char* hitGetName(HitEntry* hit);
void hitObjGetPos(const char* name, Vec* position);
void marioAdjustMoveDir(void);
void marioCamZoomOffReq2(s32);
BOOL marioCamZoomUp(void);
void marioChgMot(MarioMotion);
void marioChgPaper(const char* name);
void marioChgPose(const char* name);
s32 marioGetColor(void);
MarioWork* marioGetPtr(void);
void marioOfsRotReset(void);
BOOL marioPaperOn(const char* name);
void marioSetPaperAnimeLocalTime(s32 frames);
void *memset(void *dest, int ch, size_t count);
void psndSFXOff(s32 id);
s32 psndSFXOn_3D(const char* name, Vec* position);
void psndSFX_pos();
f32 revise360(f32 angle);
int strcmp(const char *s1, const char *s2);
s32 sysMsec2Frame(s32 msec);
f32 toMovedir(f32 angle);
asm BOOL checkHarbor(Vec* out) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stw r31, 0x8c(r1)
	mr r31, r3
	stw r30, 0x88(r1)
	stw r29, 0x84(r1)
	stw r28, 0x80(r1)
	bl marioGetPtr
	mr r30, r3
	lfs f1, 0x1a8(r3)
	bl toMovedir
	addi r3, r1, 0x28
	addi r4, r1, 0x24
	bl sincosf
	lfs f7, float_40_8041ad98(r2)
	addi r4, r1, 0x20
	lfs f1, 0x28(r1)
	addi r5, r1, 0x1c
	lfs f0, 0x8c(r30)
	addi r6, r1, 0x18
	lfs f4, float_0_8041ada0(r2)
	addi r7, r1, 0x14
	fmadds f1, f7, f1, f0
	lfs f5, 0x24(r1)
	lfs f3, 0x94(r30)
	fmr f6, f4
	lfs f0, 0x90(r30)
	addi r8, r1, 0x10
	lfs f2, float_20_8041ad9c(r2)
	fmadds f3, f7, f5, f3
	stfs f7, 0x14(r1)
	addi r9, r1, 0xc
	fadds f2, f2, f0
	lfs f5, float_neg1_8041ada4(r2)
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	mr. r28, r3
	beq @1
	li r29, 0x0
	bl hitGetAttr
	rlwinm. r0, r3, 0, 17, 17
	beq @2
	li r29, 0x1
	b @3
	@2:
	rlwinm. r0, r3, 0, 16, 16
	beq @4
	li r29, 0x2
	b @3
	@4:
	rlwinm. r0, r3, 0, 15, 15
	beq @5
	li r29, 0x3
	b @3
	@5:
	rlwinm. r0, r3, 0, 14, 14
	beq @3
	li r29, 0x4
	@3:
	cmpwi r29, 0x0
	beq @1
	mr r3, r28
	bl hitGetName
	addi r4, r1, 0x44
	bl hitObjGetPos
	lfs f4, float_100_8041adac(r2)
	lis r0, 0x4330
	lfs f3, float_0p5_8041ada8(r2)
	lis r3, double_to_int_802c5e50@ha
	lfs f0, 0x44(r1)
	addi r4, r3, double_to_int_802c5e50@l
	lfs f2, 0x48(r1)
	li r3, 0x1
	fmadds f0, f4, f0, f3
	lfs f1, 0x4c(r1)
	fmadds f2, f4, f2, f3
	stw r0, 0x78(r1)
	fmadds f1, f4, f1, f3
	lfd f3, 0x0(r4)
	fdivs f0, f0, f4
	stw r0, 0x58(r1)
	stw r0, 0x68(r1)
	fdivs f2, f2, f4
	fdivs f1, f1, f4
	fctiwz f0, f0
	fctiwz f2, f2
	fctiwz f1, f1
	stfd f0, 0x70(r1)
	stfd f2, 0x50(r1)
	lwz r0, 0x74(r1)
	stfd f1, 0x60(r1)
	xoris r0, r0, 0x8000
	lwz r4, 0x54(r1)
	stw r0, 0x7c(r1)
	xoris r4, r4, 0x8000
	lwz r0, 0x64(r1)
	stw r4, 0x5c(r1)
	lfd f0, 0x78(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x6c(r1)
	fsubs f0, f0, f3
	lfd f2, 0x58(r1)
	lfd f1, 0x68(r1)
	fsubs f2, f2, f3
	stfs f0, 0x0(r31)
	fsubs f0, f1, f3
	stfs f2, 0x4(r31)
	stfs f0, 0x8(r31)
	b @6
	@1:
	lfs f1, float_90_8041adb0(r2)
	lfs f0, 0x1a8(r30)
	fadds f1, f1, f0
	bl toMovedir
	addi r3, r1, 0x28
	addi r4, r1, 0x24
	bl sincosf
	lfs f7, float_40_8041ad98(r2)
	addi r4, r1, 0x20
	lfs f1, 0x28(r1)
	addi r5, r1, 0x1c
	lfs f0, 0x8c(r30)
	addi r6, r1, 0x18
	lfs f4, float_0_8041ada0(r2)
	addi r7, r1, 0x14
	fmadds f1, f7, f1, f0
	lfs f5, 0x24(r1)
	lfs f3, 0x94(r30)
	fmr f6, f4
	lfs f0, 0x90(r30)
	addi r8, r1, 0x10
	lfs f2, float_20_8041ad9c(r2)
	fmadds f3, f7, f5, f3
	stfs f7, 0x14(r1)
	addi r9, r1, 0xc
	fadds f2, f2, f0
	lfs f5, float_neg1_8041ada4(r2)
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	mr. r28, r3
	beq @7
	li r29, 0x0
	bl hitGetAttr
	rlwinm. r0, r3, 0, 17, 17
	beq @8
	li r29, 0x1
	b @9
	@8:
	rlwinm. r0, r3, 0, 16, 16
	beq @10
	li r29, 0x2
	b @9
	@10:
	rlwinm. r0, r3, 0, 15, 15
	beq @11
	li r29, 0x3
	b @9
	@11:
	rlwinm. r0, r3, 0, 14, 14
	beq @9
	li r29, 0x4
	@9:
	cmpwi r29, 0x0
	beq @7
	mr r3, r28
	bl hitGetName
	addi r4, r1, 0x38
	bl hitObjGetPos
	lfs f4, float_100_8041adac(r2)
	lis r0, 0x4330
	lfs f3, float_0p5_8041ada8(r2)
	lis r3, double_to_int_802c5e50@ha
	lfs f0, 0x38(r1)
	addi r4, r3, double_to_int_802c5e50@l
	lfs f2, 0x3c(r1)
	li r3, 0x1
	fmadds f0, f4, f0, f3
	lfs f1, 0x40(r1)
	fmadds f2, f4, f2, f3
	stw r0, 0x50(r1)
	fmadds f1, f4, f1, f3
	lfd f3, 0x0(r4)
	fdivs f0, f0, f4
	stw r0, 0x70(r1)
	stw r0, 0x60(r1)
	fdivs f2, f2, f4
	fdivs f1, f1, f4
	fctiwz f0, f0
	fctiwz f2, f2
	fctiwz f1, f1
	stfd f0, 0x58(r1)
	stfd f2, 0x78(r1)
	lwz r0, 0x5c(r1)
	stfd f1, 0x68(r1)
	xoris r0, r0, 0x8000
	lwz r4, 0x7c(r1)
	stw r0, 0x54(r1)
	xoris r4, r4, 0x8000
	lwz r0, 0x6c(r1)
	stw r4, 0x74(r1)
	lfd f0, 0x50(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	fsubs f0, f0, f3
	lfd f2, 0x70(r1)
	lfd f1, 0x60(r1)
	fsubs f2, f2, f3
	stfs f0, 0x0(r31)
	fsubs f0, f1, f3
	stfs f2, 0x4(r31)
	stfs f0, 0x8(r31)
	b @6
	@7:
	lfs f1, 0x1a8(r30)
	lfs f0, float_90_8041adb0(r2)
	fsubs f1, f1, f0
	bl toMovedir
	addi r3, r1, 0x28
	addi r4, r1, 0x24
	bl sincosf
	lfs f7, float_40_8041ad98(r2)
	addi r4, r1, 0x20
	lfs f1, 0x28(r1)
	addi r5, r1, 0x1c
	lfs f0, 0x8c(r30)
	addi r6, r1, 0x18
	lfs f4, float_0_8041ada0(r2)
	addi r7, r1, 0x14
	fmadds f1, f7, f1, f0
	lfs f5, 0x24(r1)
	lfs f3, 0x94(r30)
	fmr f6, f4
	lfs f0, 0x90(r30)
	addi r8, r1, 0x10
	lfs f2, float_20_8041ad9c(r2)
	fmadds f3, f7, f5, f3
	stfs f7, 0x14(r1)
	addi r9, r1, 0xc
	fadds f2, f2, f0
	lfs f5, float_neg1_8041ada4(r2)
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	mr. r30, r3
	beq @12
	li r29, 0x0
	bl hitGetAttr
	rlwinm. r0, r3, 0, 17, 17
	beq @13
	li r29, 0x1
	b @14
	@13:
	rlwinm. r0, r3, 0, 16, 16
	beq @15
	li r29, 0x2
	b @14
	@15:
	rlwinm. r0, r3, 0, 15, 15
	beq @16
	li r29, 0x3
	b @14
	@16:
	rlwinm. r0, r3, 0, 14, 14
	beq @14
	li r29, 0x4
	@14:
	cmpwi r29, 0x0
	beq @12
	mr r3, r30
	bl hitGetName
	addi r4, r1, 0x2c
	bl hitObjGetPos
	lfs f4, float_100_8041adac(r2)
	lis r0, 0x4330
	lfs f3, float_0p5_8041ada8(r2)
	lis r3, double_to_int_802c5e50@ha
	lfs f0, 0x2c(r1)
	addi r4, r3, double_to_int_802c5e50@l
	lfs f2, 0x30(r1)
	li r3, 0x1
	fmadds f0, f4, f0, f3
	lfs f1, 0x34(r1)
	fmadds f2, f4, f2, f3
	stw r0, 0x50(r1)
	fmadds f1, f4, f1, f3
	lfd f3, 0x0(r4)
	fdivs f0, f0, f4
	stw r0, 0x70(r1)
	stw r0, 0x60(r1)
	fdivs f2, f2, f4
	fdivs f1, f1, f4
	fctiwz f0, f0
	fctiwz f2, f2
	fctiwz f1, f1
	stfd f0, 0x58(r1)
	stfd f2, 0x78(r1)
	lwz r0, 0x5c(r1)
	stfd f1, 0x68(r1)
	xoris r0, r0, 0x8000
	lwz r4, 0x7c(r1)
	stw r0, 0x54(r1)
	xoris r4, r4, 0x8000
	lwz r0, 0x6c(r1)
	stw r4, 0x74(r1)
	lfd f0, 0x50(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	fsubs f0, f0, f3
	lfd f2, 0x70(r1)
	lfd f1, 0x60(r1)
	fsubs f2, f2, f3
	stfs f0, 0x0(r31)
	fsubs f0, f1, f3
	stfs f2, 0x4(r31)
	stfs f0, 0x8(r31)
	b @6
	@12:
	li r3, 0x0
	@6:
	lwz r0, 0x94(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	lwz r29, 0x84(r1)
	lwz r28, 0x80(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

void mot_ship(void);
#pragma force_active on
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
asm void shipMove(void) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stfd f28, 0x40(r1)
	psq_st f28, 0x48(r1), 0, 0
	stfd f27, 0x30(r1)
	psq_st f27, 0x38(r1), 0, 0
	stfd f26, 0x20(r1)
	psq_st f26, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	bl marioGetPtr
	mr r31, r3
	lfs f0, float_0_8041ada0(r2)
	lfs f30, 0x190(r3)
	stfs f0, 0xc(r1)
	stfs f0, 0xc(r1)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x30(r3)
	cmpwi r0, 0x0
	beq @1
	bl marioGetPtr
	lwz r4, 0x288(r3)
	lwz r3, 0x30(r4)
	subi r0, r3, 0x1
	stw r0, 0x30(r4)
	bl marioGetPtr
	lwz r30, 0x288(r3)
	bl marioGetPtr
	lwz r5, 0x288(r3)
	addi r3, r1, 0xc
	lfs f2, 0x28(r30)
	addi r4, r1, 0x8
	lfs f1, 0x2c(r5)
	bl movePos
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0xc(r1)
	lfs f1, 0x14(r3)
	fadds f0, f1, f0
	stfs f0, 0x14(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	la r30, shipData(r13)
	lfs f0, 0x8(r1)
	lfs f1, 0x18(r3)
	fadds f0, f1, f0
	stfs f0, 0x18(r3)
	lfs f27, 0x10(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x14(r3)
	fcmpo cr0, f0, f27
	ble @2
	lfs f27, 0x10(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f27, 0x14(r3)
	@2:
	bl marioGetPtr
	lfs f0, 0x10(r30)
	lwz r3, 0x288(r3)
	fneg f27, f0
	lfs f0, 0x14(r3)
	fcmpo cr0, f0, f27
	bge @3
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f27, 0x14(r3)
	@3:
	lfs f27, 0x10(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x18(r3)
	fcmpo cr0, f0, f27
	ble @4
	lfs f27, 0x10(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f27, 0x18(r3)
	@4:
	bl marioGetPtr
	lfs f0, 0x10(r30)
	lwz r3, 0x288(r3)
	fneg f27, f0
	lfs f0, 0x18(r3)
	fcmpo cr0, f0, f27
	bge @1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f27, 0x18(r3)
	@1:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f28, 0x14(r3)
	bl marioGetPtr
	lfs f1, 0x190(r31)
	lfs f0, float_0_8041ada0(r2)
	lwz r3, 0x288(r3)
	fcmpu cr0, f1, f0
	lfs f27, 0x18(r3)
	beq @5
	lfs f2, float_3p1416_8041adc4(r2)
	lfs f1, 0x194(r31)
	lfs f0, float_180_8041adc0(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, float_3p1416_8041adc4(r2)
	frsp f3, f1
	lfs f1, 0x194(r31)
	lfs f0, float_180_8041adc0(r2)
	fmuls f1, f2, f1
	fmuls f26, f30, f3
	fdivs f1, f1, f0
	bl cos
	frsp f0, f1
	fneg f0, f0
	fmuls f29, f30, f0
	b @6
	@5:
	fmr f26, f28
	fmr f29, f27
	@6:
	lfs f0, float_0_8041ada0(r2)
	la r30, shipData(r13)
	lfs f31, 0x10(r30)
	fcmpu cr0, f30, f0
	bne @7
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x30(r3)
	cmpwi r0, 0x0
	beq @8
	@7:
	fcmpo cr0, f26, f28
	ble @9
	lfs f1, float_1_8041adc8(r2)
	la r3, shipData(r13)
	lfs f0, 0xc(r3)
	fadds f1, f1, f26
	fsubs f1, f1, f28
	fmadds f28, f1, f0, f28
	fcmpo cr0, f28, f31
	cror eq, gt, eq
	bne @10
	fmr f28, f31
	b @10
	@9:
	lfs f1, float_1_8041adc8(r2)
	la r3, shipData(r13)
	lfs f0, 0xc(r3)
	fneg f2, f31
	fsubs f1, f26, f1
	fsubs f1, f1, f28
	fmadds f28, f1, f0, f28
	fcmpo cr0, f28, f2
	cror eq, lt, eq
	bne @10
	fmr f28, f2
	@10:
	fcmpo cr0, f29, f27
	ble @11
	lfs f1, float_1_8041adc8(r2)
	la r3, shipData(r13)
	lfs f0, 0xc(r3)
	fadds f1, f1, f29
	fsubs f1, f1, f27
	fmadds f27, f1, f0, f27
	fcmpo cr0, f27, f31
	cror eq, gt, eq
	bne @8
	fmr f27, f31
	b @8
	@11:
	lfs f1, float_1_8041adc8(r2)
	la r3, shipData(r13)
	lfs f0, 0xc(r3)
	fneg f2, f31
	fsubs f1, f29, f1
	fsubs f1, f1, f27
	fmadds f27, f1, f0, f27
	fcmpo cr0, f27, f2
	cror eq, lt, eq
	bne @8
	fmr f27, f2
	@8:
	lfs f0, float_0_8041ada0(r2)
	fcmpu cr0, f30, f0
	bne @12
	lwz r0, 0x1f0(r31)
	lfs f0, shipData(r13)
	cmplwi r0, 0x0
	beq @13
	la r3, shipData(r13)
	lfs f0, 0x4(r3)
	@13:
	fabs f3, f0
	lfs f0, float_0p01_8041adcc(r2)
	fneg f2, f28
	fneg f1, f27
	fmadds f28, f2, f3, f28
	fmadds f27, f1, f3, f27
	fabs f1, f28
	fcmpo cr0, f1, f0
	bge @14
	lfs f28, float_0_8041ada0(r2)
	@14:
	fabs f1, f27
	lfs f0, float_0p01_8041adcc(r2)
	fcmpo cr0, f1, f0
	bge @12
	lfs f27, float_0_8041ada0(r2)
	@12:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f28, 0x14(r3)
	bl marioGetPtr
	lfs f1, float_0_8041ada0(r2)
	fmr f3, f28
	lwz r3, 0x288(r3)
	fmr f4, f27
	fmr f2, f1
	stfs f27, 0x18(r3)
	bl distABf
	lfs f28, float_0_8041ada0(r2)
	fmr f29, f1
	fcmpu cr0, f30, f28
	beq @15
	lfs f0, 0x10(r30)
	fcmpo cr0, f29, f0
	cror eq, gt, eq
	bne @16
	fmr f29, f0
	b @16
	@15:
	la r3, shipData(r13)
	lfs f0, 0x14(r3)
	fcmpo cr0, f29, f0
	bge @16
	fmr f29, f28
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f27, float_0_8041ada0(r2)
	stfs f28, 0x14(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f27, 0x18(r3)
	@16:
	lfs f0, float_0_8041ada0(r2)
	stfs f29, 0x180(r31)
	fcmpu cr0, f29, f0
	beq @17
	bl marioGetPtr
	lwz r30, 0x288(r3)
	bl marioGetPtr
	lfs f1, float_0_8041ada0(r2)
	lwz r3, 0x288(r3)
	fmr f2, f1
	lfs f4, 0x18(r30)
	lfs f3, 0x14(r3)
	bl angleABf
	stfs f1, 0x1a0(r31)
	@17:
	lfs f0, float_1_8041adc8(r2)
	fcmpo cr0, f29, f0
	cror eq, gt, eq
	bne @18
	bl marioGetPtr
	mr r30, r3
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @19
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne @19
	addi r4, r30, 0x8c
	li r3, 0x190
	bl psndSFXOn_3D
	mr r30, r3
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r30, 0x38(r3)
	b @19
	@18:
	lfs f0, float_0p2_8041add0(r2)
	fcmpo cr0, f29, f0
	cror eq, lt, eq
	bne @19
	bl marioGetPtr
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @19
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @19
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	bl psndSFXOff
	li r30, -0x1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r30, 0x38(r3)
	@19:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @20
	bl marioGetPtr
	lwz r3, 0x288(r3)
	addi r4, r31, 0x8c
	lwz r3, 0x38(r3)
	bl psndSFX_pos
	@20:
	stfs f29, 0x18c(r31)
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	psq_l f27, 0x38(r1), 0, 0
	lfd f27, 0x30(r1)
	psq_l f26, 0x28(r1), 0, 0
	lfd f26, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r0, 0x84(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm BOOL marioChkShipMoveMode(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x19
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x44(r3)
	cmpwi r0, 0x32
	blt @3
	cmpwi r0, 0x34
	bgt @3
	li r3, 0x1
	b @2
	@3:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioShipChgFall(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r4, 0x0(r3)
	rlwinm. r0, r4, 0, 14, 14
	bne @1
	oris r0, r4, 0x2
	lfs f1, float_neg0p1_8041add4(r2)
	stw r0, 0x0(r3)
	lfs f0, float_neg0p2_8041add8(r2)
	stfs f1, 0x7c(r3)
	lfs f1, float_0p024_8041addc(r2)
	stfs f0, 0x80(r3)
	lfs f0, float_neg0p004_8041ade0(r2)
	stfs f1, 0x84(r3)
	stfs f0, 0x88(r3)
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mot_ship(void) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stmw r27, 0x5c(r1)
	lis r3, str_802C5E00@ha
	addi r30, r3, str_802C5E00@l
	bl marioGetPtr
	mr r31, r3
	lwz r3, 0xc(r3)
	clrlwi. r0, r3, 31
	beq @1
	clrrwi r0, r3, 1
	li r3, 0x0
	stw r0, 0xc(r31)
	li r4, 0x48
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r31)
	bl __memAlloc
	mr r28, r3
	bl marioGetPtr
	stw r28, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r4, 0x0
	li r5, 0x48
	bl memset
	li r28, -0x1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_0_8041ada0(r2)
	stw r28, 0x38(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041ada0(r2)
	stfs f30, 0x20(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_4p25_8041ade4(r2)
	stfs f31, 0x8(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r0, 0x0
	stfs f30, 0xc(r3)
	stw r0, 0x44(r31)
	lwz r0, 0xc(r31)
	rlwinm. r0, r0, 0, 29, 29
	bne @1
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	@1:
	lwz r0, 0x44(r31)
	cmplwi r0, 0x34
	bgt @2
	lis r3, jumptable_8030ECF8@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8030ECF8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@3:
	addi r4, r31, 0x8c
	li r3, 0x18d
	bl psndSFXOn_3D
	addi r4, r31, 0x8c
	li r3, 0xaf
	bl psndSFXOn_3D
	bl marioCamZoomUp
	bl marioPreJump
	addi r3, r30, 0x58
	bl marioChgPose
	bl camFollowYOff
	lwz r4, 0x4(r31)
	li r3, 0x0
	li r0, 0x1
	lfs f30, float_0_8041ada0(r2)
	ori r4, r4, 0x100
	stw r4, 0x4(r31)
	stw r3, 0x48(r31)
	stw r0, 0x44(r31)
	sth r3, 0x50(r31)
	sth r3, 0x52(r31)
	stfs f30, 0x180(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x1c(r3)
	lfs f1, 0x8c(r31)
	lfs f2, 0x90(r31)
	lfs f3, 0x94(r31)
	bl N_marioSetBottomlessRespawnPosOnBeroEntry
	lwz r29, 0x1e8(r31)
	bl marioGetPtr
	mr r28, r3
	mr r3, r29
	bl hitGetAttr
	rlwinm. r0, r3, 0, 17, 17
	li r29, 0x0
	beq @4
	lwz r3, 0x1e8(r28)
	bl hitGetName
	addi r4, r1, 0x1c
	bl hitObjGetPos
	lfs f1, 0x8c(r28)
	lfs f2, 0x94(r28)
	lfs f3, 0x1c(r1)
	lfs f4, 0x24(r1)
	bl angleABf
	lfs f0, 0x198(r28)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041adc0(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @5
	li r29, 0x2
	b @6
	@5:
	li r29, 0x1
	b @6
	@4:
	rlwinm. r0, r3, 0, 16, 16
	beq @7
	lwz r3, 0x1e8(r28)
	bl hitGetName
	addi r4, r1, 0x28
	bl hitObjGetPos
	lfs f1, 0x8c(r28)
	lfs f2, 0x94(r28)
	lfs f3, 0x28(r1)
	lfs f4, 0x30(r1)
	bl angleABf
	lfs f0, 0x198(r28)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041adc0(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @8
	li r29, 0x2
	b @6
	@8:
	li r29, 0x1
	b @6
	@7:
	rlwinm. r0, r3, 0, 15, 15
	beq @9
	li r29, 0x2
	b @6
	@9:
	rlwinm. r0, r3, 0, 14, 14
	beq @6
	li r29, 0x1
	@6:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r29, 0x0(r3)
	@10:
	bl marioMakeJumpPara
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @11
	lfs f31, float_30_8041ade8(r2)
	b @12
	@11:
	lfs f31, float_neg30_8041adec(r2)
	@12:
	bl marioGetPtr
	lwz r28, 0x288(r3)
	lfs f30, 0x1c(r28)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p125_8041adf0(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f31, f1
	fmadds f0, f0, f1, f30
	stfs f0, 0x1c(r28)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @13
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_30_8041ade8(r2)
	lfs f0, 0x1c(r3)
	fcmpo cr0, f0, f30
	cror eq, gt, eq
	bne @14
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x1c(r3)
	b @14
	@13:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_neg30_8041adec(r2)
	lfs f0, 0x1c(r3)
	fcmpo cr0, f0, f30
	cror eq, lt, eq
	bne @14
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x1c(r3)
	@14:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r27, 0x0
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @15
	lfs f1, 0x1a8(r31)
	lfs f0, float_270_8041adf4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @16
	li r27, 0x1
	b @16
	@15:
	lfs f1, 0x1a8(r31)
	lfs f0, float_neg270_8041adf8(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @16
	li r27, 0x1
	@16:
	cmpwi r27, 0x0
	beq @17
	li r3, 0x2
	li r0, 0x14
	stw r3, 0x44(r31)
	stw r0, 0x48(r31)
	bl marioGetColor
	slwi r0, r3, 2
	la r3, paper_ship(r13)
	lwzx r3, r3, r0
	bl marioPaperOn
	addi r3, r30, 0x60
	bl marioChgPaper
	la r3, str_8041ADFC(r2)
	bl marioChgPose
	lwz r0, 0x4(r31)
	lfs f30, float_15_8041adb4(r2)
	ori r0, r0, 0x8
	stw r0, 0x4(r31)
	bl marioGetPtr
	lwz r5, 0x288(r3)
	lis r3, sound_evt@ha
	addi r3, r3, sound_evt@l
	li r4, 0x0
	stfs f30, 0x20(r5)
	li r5, 0x0
	bl evtEntry
	lfs f1, float_1024_8041ae04(r2)
	lfs f0, 0x8c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x90(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x94(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	@17:
	lfs f1, 0x7c(r31)
	lfs f0, float_0_8041ada0(r2)
	fcmpo cr0, f1, f0
	ble @2
	lfs f0, 0x90(r31)
	fadds f0, f0, f1
	stfs f0, 0x90(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r31)
	b @2
	@18:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @19
	lfs f30, float_1_8041adc8(r2)
	b @20
	@19:
	lfs f30, float_neg1_8041ada4(r2)
	@20:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x20(r3)
	fmuls f31, f0, f30
	bl marioGetPtr
	lwz r28, 0x288(r3)
	lfs f30, 0x1c(r28)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p125_8041adf0(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f31, f1
	fmadds f0, f0, f1, f30
	stfs f0, 0x1c(r28)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r27, 0x0
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @21
	lfs f1, 0x1a8(r31)
	lfs f0, float_1260_8041ae08(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @22
	li r27, 0x1
	b @22
	@21:
	lfs f1, 0x1a8(r31)
	lfs f0, float_neg1080_8041ae0c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @22
	li r27, 0x1
	@22:
	cmpwi r27, 0x0
	beq @2
	li r3, 0x28
	li r0, 0x3
	stw r3, 0x48(r31)
	stw r0, 0x44(r31)
	b @2
	@23:
	lwz r0, 0x48(r31)
	cmpwi r0, 0xe
	bne @24
	bl allPartyRideShip
	@24:
	lwz r0, 0x48(r31)
	cmpwi r0, 0x14
	bne @25
	li r3, 0x384
	bl marioCamZoomOffReq2
	bl camFollowYOn
	@25:
	lwz r3, 0x48(r31)
	subic. r0, r3, 0x1
	stw r0, 0x48(r31)
	bgt @26
	li r0, 0x4
	stw r0, 0x44(r31)
	@26:
	lfs f2, 0x9c(r31)
	lfs f1, float_neg15_8041ae10(r2)
	fcmpo cr0, f2, f1
	ble @27
	lfs f0, float_1_8041adc8(r2)
	fsubs f0, f2, f0
	stfs f0, 0x9c(r31)
	lfs f0, 0x9c(r31)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @27
	stfs f1, 0x9c(r31)
	@27:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @28
	lfs f30, float_1_8041adc8(r2)
	b @29
	@28:
	lfs f30, float_neg1_8041ada4(r2)
	@29:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x20(r3)
	fmuls f31, f0, f30
	bl marioGetPtr
	lwz r28, 0x288(r3)
	lfs f30, 0x1c(r28)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p125_8041adf0(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f31, f1
	fmadds f0, f0, f1, f30
	stfs f0, 0x1c(r28)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p1_8041ae14(r2)
	lfs f1, 0x20(r3)
	fsubs f0, f1, f0
	stfs f0, 0x20(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_1_8041adc8(r2)
	lfs f0, 0x20(r3)
	fcmpo cr0, f0, f30
	cror eq, lt, eq
	bne @30
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x20(r3)
	@30:
	li r27, 0x0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @31
	lfs f1, 0x1a8(r31)
	lfs f0, float_1620_8041ae18(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @32
	stfs f0, 0x1a8(r31)
	li r27, 0x1
	b @32
	@31:
	lfs f1, 0x1a8(r31)
	lfs f0, float_neg1440_8041ae1c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @32
	stfs f0, 0x1a8(r31)
	li r27, 0x1
	@32:
	cmpwi r27, 0x0
	beq @2
	lwz r0, 0x44(r31)
	cmpwi r0, 0x4
	bne @2
	li r0, 0xa
	stw r0, 0x44(r31)
	b @2
	@33:
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r31)
	lfs f1, 0x1a8(r31)
	bl revise360
	stfs f1, 0x1a8(r31)
	lfs f0, float_40_8041ad98(r2)
	stfs f0, 0x1b4(r31)
	stfs f0, 0x1b8(r31)
	bl marioGetPtr
	lwz r28, 0x288(r3)
	lwz r27, 0x1e8(r31)
	bl marioGetPtr
	mr r29, r3
	mr r3, r27
	bl hitGetName
	addi r4, r1, 0x10
	bl hitObjGetPos
	lfs f5, float_100_8041adac(r2)
	lis r0, 0x4330
	lfs f1, 0x10(r1)
	li r27, 0x0
	lfs f2, float_0p5_8041ada8(r2)
	lfs f0, 0x18(r1)
	fmadds f3, f5, f1, f2
	lfs f1, 0x90(r29)
	fmadds f2, f5, f0, f2
	lfs f0, float_15_8041adb4(r2)
	stw r0, 0x40(r1)
	fdivs f4, f3, f5
	stw r0, 0x50(r1)
	lfd f3, 0x50(r30)
	fdivs f2, f2, f5
	fctiwz f4, f4
	fctiwz f2, f2
	fsubs f0, f1, f0
	stfd f4, 0x48(r1)
	stfd f2, 0x38(r1)
	lwz r3, 0x4c(r1)
	lwz r0, 0x3c(r1)
	xoris r3, r3, 0x8000
	stfs f0, 0x40(r28)
	xoris r0, r0, 0x8000
	stw r3, 0x44(r1)
	lwz r3, 0x1e8(r29)
	stw r0, 0x54(r1)
	lfd f1, 0x40(r1)
	lfd f0, 0x50(r1)
	fsubs f31, f1, f3
	fsubs f30, f0, f3
	bl hitGetAttr
	rlwinm. r0, r3, 0, 17, 17
	beq @34
	li r27, 0x1
	b @35
	@34:
	rlwinm. r0, r3, 0, 16, 16
	beq @36
	li r27, 0x2
	b @35
	@36:
	rlwinm. r0, r3, 0, 15, 15
	beq @37
	li r27, 0x3
	b @35
	@37:
	rlwinm. r0, r3, 0, 14, 14
	beq @35
	li r27, 0x4
	@35:
	cmpwi r27, 0x1
	bne @38
	lfs f1, float_50_8041adb8(r2)
	lfs f0, float_30p303_8041adbc(r2)
	fsubs f1, f30, f1
	stfs f31, 0x3c(r28)
	fsubs f0, f1, f0
	stfs f0, 0x44(r28)
	b @39
	@38:
	cmpwi r27, 0x2
	bne @40
	lfs f0, float_50_8041adb8(r2)
	lfs f1, float_30p303_8041adbc(r2)
	fadds f0, f0, f30
	stfs f31, 0x3c(r28)
	fadds f0, f1, f0
	stfs f0, 0x44(r28)
	b @39
	@40:
	cmpwi r27, 0x3
	bne @41
	lfs f1, float_50_8041adb8(r2)
	lfs f0, float_30p303_8041adbc(r2)
	fsubs f1, f31, f1
	fsubs f0, f1, f0
	stfs f0, 0x3c(r28)
	stfs f30, 0x44(r28)
	b @39
	@41:
	cmpwi r27, 0x4
	bne @42
	lfs f0, float_50_8041adb8(r2)
	lfs f1, float_30p303_8041adbc(r2)
	fadds f0, f0, f31
	fadds f0, f1, f0
	stfs f0, 0x3c(r28)
	stfs f30, 0x44(r28)
	b @39
	@42:
	stfs f31, 0x3c(r28)
	stfs f30, 0x44(r28)
	@39:
	bl marioGetPtr
	lwz r29, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f2, 0x44(r29)
	lfs f1, 0x3c(r3)
	lfs f3, 0x8c(r31)
	lfs f4, 0x94(r31)
	bl distABf
	lfs f0, float_0p1_8041ae14(r2)
	cmpwi r27, 0x3
	fmuls f30, f0, f1
	beq @43
	bge @44
	cmpwi r27, 0x1
	beq @45
	bge @46
	b @47
	@44:
	cmpwi r27, 0x5
	bge @47
	b @48
	@45:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x44(r3)
	fsubs f0, f0, f30
	stfs f0, 0x44(r3)
	b @47
	@46:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x44(r3)
	fadds f0, f0, f30
	stfs f0, 0x44(r3)
	b @47
	@43:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x3c(r3)
	fsubs f0, f0, f30
	stfs f0, 0x3c(r3)
	b @47
	@48:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x3c(r3)
	fadds f0, f0, f30
	stfs f0, 0x3c(r3)
	@47:
	bl marioGetPtr
	lwz r29, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x3c(r3)
	lfs f4, 0x44(r29)
	bl distABf
	lfs f0, float_36_8041ae20(r2)
	fdivs f0, f1, f0
	stfs f0, 0x180(r31)
	bl marioGetPtr
	lwz r29, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x3c(r3)
	lfs f4, 0x44(r29)
	bl angleABf
	stfs f1, 0x1a0(r31)
	lfs f0, 0x1a0(r31)
	stfs f0, 0x19c(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, 0x40(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x4(r3)
	bl marioGetPtr
	lwz r4, 0x288(r3)
	li r3, 0x24
	lfs f0, 0x90(r31)
	li r0, 0xb
	lfs f1, 0x40(r4)
	lfs f2, float_0_8041ada0(r2)
	fsubs f1, f1, f0
	lfs f0, float_306_8041ae24(r2)
	stfs f2, 0x7c(r31)
	fadds f1, f1, f1
	fdivs f0, f1, f0
	stfs f0, 0x80(r31)
	stfs f2, 0x84(r31)
	stfs f2, 0x88(r31)
	stw r3, 0x48(r31)
	stw r0, 0x44(r31)
	b @2
	@49:
	lfs f1, 0x180(r31)
	addi r3, r31, 0x8c
	lfs f2, 0x1a0(r31)
	addi r4, r31, 0x94
	bl movePos
	lfs f1, 0x90(r31)
	lfs f0, 0x7c(r31)
	fadds f0, f1, f0
	stfs f0, 0x90(r31)
	bl marioMakeJumpPara
	lfs f30, 0x7c(r31)
	bl marioGetPtr
	lfs f0, float_20_8041ad9c(r2)
	mr r29, r3
	fmr f1, f30
	addi r3, r1, 0xc
	stfs f0, 0x1b4(r29)
	bl marioChkLandon
	lfs f0, float_40_8041ad98(r2)
	cmplwi r3, 0x0
	stfs f0, 0x1b4(r29)
	beq @50
	lfs f2, 0x90(r29)
	lfs f0, 0xc(r1)
	lfs f1, float_0_8041ada0(r2)
	fsubs f0, f2, f0
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	beq @51
	fadds f0, f0, f30
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @50
	@51:
	stw r3, 0x1e4(r29)
	lfs f0, 0xc(r1)
	stfs f0, 0x90(r29)
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r29)
	lfs f1, 0x8c(r29)
	lfs f2, 0x94(r29)
	lfs f3, 0x11c(r29)
	lfs f4, 0x124(r29)
	bl distABf
	fabs f0, f1
	li r0, 0x0
	stfs f0, 0x128(r29)
	lwz r3, 0x0(r29)
	rlwinm r3, r3, 0, 25, 23
	stw r3, 0x0(r29)
	sth r0, 0x50(r29)
	sth r0, 0x52(r29)
	bl camFollowYOn
	li r0, 0x1
	b @52
	@50:
	li r0, 0x0
	@52:
	cmpwi r0, 0x0
	beq @2
	lfs f30, float_0_8041ada0(r2)
	stfs f30, 0x7c(r31)
	stfs f30, 0x80(r31)
	stfs f30, 0x84(r31)
	stfs f30, 0x88(r31)
	stfs f30, 0x180(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x1c(r3)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r31)
	lfs f1, 0x1a8(r31)
	bl revise360
	stfs f1, 0x1a8(r31)
	lfs f0, 0x1a8(r31)
	stfs f0, 0x1ac(r31)
	lfs f1, 0x1a8(r31)
	bl toMovedir
	stfs f1, 0x1a0(r31)
	addi r4, r31, 0x8c
	li r3, 0x18f
	lfs f0, 0x1a0(r31)
	stfs f0, 0x19c(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	ori r0, r0, 0x1000
	stw r0, 0x4(r31)
	bl psndSFXOn_3D
	lfs f1, float_0_8041ada0(r2)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	fmr f4, f1
	fmr f5, f1
	bl effFunemizuEntry
	mr r29, r3
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r29, 0x24(r3)
	lwz r29, 0x134(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_0_8041ada0(r2)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stw r29, 0x48(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_4p25_8041ade4(r2)
	stfs f30, 0x8(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r0, 0x32
	stfs f31, 0xc(r3)
	stw r0, 0x44(r31)
	lwz r0, 0xc(r31)
	rlwinm. r0, r0, 0, 29, 29
	bne @2
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	b @2
	@53:
	lwz r0, 0xc(r31)
	rlwinm. r0, r0, 0, 29, 29
	bne @54
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	@54:
	li r0, 0x1f
	stw r0, 0x44(r31)
	@55:
	lfs f2, 0x9c(r31)
	lfs f1, float_neg0p4_8041ae28(r2)
	lfs f0, float_neg18_8041ae2c(r2)
	fadds f1, f2, f1
	stfs f1, 0x9c(r31)
	lfs f1, 0x9c(r31)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @56
	li r3, 0x4
	li r0, 0x20
	stw r3, 0x48(r31)
	stw r0, 0x44(r31)
	@56:
	lfs f30, float_1p6_8041ae30(r2)
	bl marioGetPtr
	mr r29, r3
	lfs f31, 0x8c(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0_8041ada0(r2)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x4(r3)
	lfs f1, 0x90(r29)
	fadds f31, f1, f0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x8(r3)
	lfs f31, 0x94(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0xc(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f30, 0x10(r3)
	lfs f31, 0x1a8(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x14(r3)
	b @2
	@57:
	lwz r3, 0x48(r31)
	subic. r0, r3, 0x1
	stw r0, 0x48(r31)
	bgt @2
	li r0, 0x28
	stw r0, 0x44(r31)
	@58:
	bl marioGetPtr
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @59
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @59
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	bl psndSFXOff
	li r29, -0x1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r29, 0x38(r3)
	@59:
	bl camFollowYOff
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x4(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, 0x40(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_2p8_8041ae34(r2)
	stfs f31, 0x4(r3)
	stfs f0, 0x180(r31)
	bl marioGetPtr
	lwz r29, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x3c(r3)
	lfs f4, 0x44(r29)
	bl distABf
	lfs f0, float_2_8041ae3c(r2)
	lfs f2, 0x180(r31)
	fmuls f3, f0, f1
	lfs f1, float_10_8041ae38(r2)
	lfs f0, float_0p5_8041ada8(r2)
	fdivs f2, f3, f2
	fmadds f0, f1, f2, f0
	fdivs f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x50(r1)
	lwz r27, 0x54(r1)
	bl marioGetPtr
	lwz r29, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x3c(r3)
	lfs f4, 0x44(r29)
	bl angleABf
	stfs f1, 0x1a0(r31)
	lfs f0, 0x1a0(r31)
	stfs f0, 0x19c(r31)
	lwz r0, 0xc(r31)
	extrwi r3, r0, 1, 22
	addi r29, r3, 0x1
	bl marioGetPtr
	lis r4, 0x4330
	xoris r0, r27, 0x8000
	stw r0, 0x4c(r1)
	li r0, 0x29
	lwz r3, 0x288(r3)
	stw r4, 0x48(r1)
	lfd f4, 0x50(r30)
	lfd f0, 0x48(r1)
	lfs f5, float_0p5_8041ada8(r2)
	fsubs f0, f0, f4
	lfs f3, float_80_8041ae40(r2)
	stw r29, 0x0(r3)
	lfs f1, float_0_8041ada0(r2)
	fmuls f6, f5, f0
	stw r4, 0x38(r1)
	fmsubs f2, f6, f6, f6
	fadds f0, f5, f6
	fdivs f2, f3, f2
	fmuls f3, f2, f6
	fctiwz f0, f0
	fneg f2, f2
	stfs f3, 0x7c(r31)
	stfs f2, 0x80(r31)
	stfd f0, 0x40(r1)
	stfs f1, 0x84(r31)
	lwz r3, 0x44(r1)
	stfs f1, 0x88(r31)
	extsh r3, r3
	stw r3, 0x48(r31)
	stw r0, 0x44(r31)
	lwz r3, 0x48(r31)
	lfs f1, 0x9c(r31)
	addi r0, r3, 0x58
	xoris r0, r0, 0x8000
	stw r0, 0x3c(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f4
	fdivs f0, f1, f0
	fabs f0, f0
	stfs f0, 0x2b0(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	bl effDelete
	b @2
	@60:
	lfs f1, 0x180(r31)
	addi r3, r31, 0x8c
	lfs f2, 0x1a0(r31)
	addi r4, r31, 0x94
	bl movePos
	lfs f1, 0x90(r31)
	lfs f0, 0x7c(r31)
	fadds f0, f1, f0
	stfs f0, 0x90(r31)
	bl marioMakeJumpPara
	lfs f2, 0x9c(r31)
	lfs f1, 0x2b0(r31)
	lfs f0, float_0_8041ada0(r2)
	fadds f1, f2, f1
	stfs f1, 0x9c(r31)
	lfs f1, 0x9c(r31)
	fcmpo cr0, f1, f0
	ble @61
	stfs f0, 0x9c(r31)
	@61:
	lwz r3, 0x48(r31)
	subic. r0, r3, 0x1
	stw r0, 0x48(r31)
	bgt @2
	addi r3, r30, 0x60
	bl marioChgPaper
	la r3, str_8041ADFC(r2)
	bl marioChgPose
	li r0, 0x58
	stw r0, 0x2a4(r31)
	lwz r3, 0x2a4(r31)
	bl marioSetPaperAnimeLocalTime
	lfs f31, float_0_8041ada0(r2)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x1c(r3)
	lwz r0, 0x4(r31)
	ori r0, r0, 0x100
	stw r0, 0x4(r31)
	bl marioAdjustMoveDir
	li r0, 0x2b
	addi r4, r31, 0x8c
	stw r0, 0x44(r31)
	li r3, 0x192
	bl psndSFXOn_3D
	lis r3, sound_evt2@ha
	li r4, 0x0
	addi r3, r3, sound_evt2@l
	li r5, 0x0
	bl evtEntry
	lfs f1, float_1024_8041ae04(r2)
	lfs f0, 0x8c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x50(r1)
	lwz r4, 0x54(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x90(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x94(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	b @2
	@62:
	lfs f2, 0x9c(r31)
	lfs f1, 0x2b0(r31)
	lfs f0, float_0_8041ada0(r2)
	fadds f1, f2, f1
	stfs f1, 0x9c(r31)
	lfs f1, 0x9c(r31)
	fcmpo cr0, f1, f0
	ble @63
	stfs f0, 0x9c(r31)
	@63:
	lwz r3, 0x2a4(r31)
	bl marioSetPaperAnimeLocalTime
	lwz r3, 0x2a4(r31)
	subi r0, r3, 0x1
	cmpwi r0, 0x2c
	stw r0, 0x2a4(r31)
	blt @2
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @64
	lfs f30, float_20_8041ad9c(r2)
	b @65
	@64:
	lfs f30, float_neg20_8041ae44(r2)
	@65:
	bl marioGetPtr
	lwz r29, 0x288(r3)
	lfs f31, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p125_8041adf0(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f30, f1
	fmadds f0, f0, f1, f31
	stfs f0, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @66
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_20_8041ad9c(r2)
	lfs f0, 0x1c(r3)
	fcmpo cr0, f0, f31
	cror eq, gt, eq
	bne @67
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x1c(r3)
	b @67
	@66:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_neg20_8041ae44(r2)
	lfs f0, 0x1c(r3)
	fcmpo cr0, f0, f31
	cror eq, lt, eq
	bne @67
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x1c(r3)
	@67:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	lwz r0, 0x2a4(r31)
	cmpwi r0, 0x2c
	bne @2
	li r0, 0x2c
	stw r0, 0x44(r31)
	b @2
	@68:
	lfs f2, 0x9c(r31)
	lfs f1, 0x2b0(r31)
	lfs f0, float_0_8041ada0(r2)
	fadds f1, f2, f1
	stfs f1, 0x9c(r31)
	lfs f1, 0x9c(r31)
	fcmpo cr0, f1, f0
	ble @69
	stfs f0, 0x9c(r31)
	@69:
	lwz r3, 0x2a4(r31)
	bl marioSetPaperAnimeLocalTime
	lwz r3, 0x2a4(r31)
	subic. r0, r3, 0x1
	stw r0, 0x2a4(r31)
	bgt @70
	li r0, 0x0
	li r3, 0x2d
	stw r0, 0x2a4(r31)
	li r0, 0x6
	stw r3, 0x44(r31)
	stw r0, 0x48(r31)
	lfs f1, 0x1a8(r31)
	bl revise360
	stfs f1, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq @70
	lfs f1, 0x1a8(r31)
	lfs f0, float_360_8041ae48(r2)
	fsubs f0, f1, f0
	stfs f0, 0x1a8(r31)
	@70:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	b @2
	@71:
	lwz r3, 0x2a4(r31)
	bl marioSetPaperAnimeLocalTime
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @72
	lfs f30, float_1_8041adc8(r2)
	b @73
	@72:
	lfs f30, float_neg1_8041ada4(r2)
	@73:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x20(r3)
	fmuls f30, f0, f30
	bl marioGetPtr
	lwz r29, 0x288(r3)
	lfs f31, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p05_8041ae4c(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f30, f1
	fmadds f0, f0, f1, f31
	stfs f0, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_neg0p005_8041ae50(r2)
	lfs f1, 0x20(r3)
	fadds f0, f1, f0
	stfs f0, 0x20(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_10_8041ae38(r2)
	lfs f0, 0x20(r3)
	fcmpo cr0, f0, f31
	cror eq, lt, eq
	bne @74
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x20(r3)
	@74:
	lwz r3, 0x48(r31)
	subic. r0, r3, 0x1
	stw r0, 0x48(r31)
	bgt @2
	@75:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @76
	lfs f30, float_1_8041adc8(r2)
	b @77
	@76:
	lfs f30, float_neg1_8041ada4(r2)
	@77:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x20(r3)
	fmuls f30, f0, f30
	bl marioGetPtr
	lwz r29, 0x288(r3)
	lfs f31, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p05_8041ae4c(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f30, f1
	fmadds f0, f0, f1, f31
	stfs f0, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_neg0p005_8041ae50(r2)
	lfs f1, 0x20(r3)
	fadds f0, f1, f0
	stfs f0, 0x20(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_10_8041ae38(r2)
	lfs f0, 0x20(r3)
	fcmpo cr0, f0, f31
	cror eq, lt, eq
	bne @78
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x20(r3)
	@78:
	li r27, 0x0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @79
	lfs f1, 0x1a8(r31)
	lfs f0, float_360_8041ae48(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @80
	bl revise360
	stfs f1, 0x1a8(r31)
	li r27, 0x1
	b @80
	@79:
	lfs f1, 0x1a8(r31)
	lfs f0, float_neg360_8041ae54(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @80
	bl revise360
	stfs f1, 0x1a8(r31)
	li r27, 0x1
	@80:
	cmpwi r27, 0x0
	beq @2
	lfs f1, 0x1a8(r31)
	bl revise360
	stfs f1, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq @81
	lfs f1, 0x1a8(r31)
	lfs f0, float_360_8041ae48(r2)
	fsubs f0, f1, f0
	stfs f0, 0x1a8(r31)
	@81:
	bl marioPaperOff
	lwz r0, 0x4(r31)
	addi r3, r30, 0x58
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r31)
	bl marioChgPose
	li r0, 0x2f
	lfs f31, float_10_8041ae38(r2)
	stw r0, 0x44(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x20(r3)
	@82:
	li r27, 0x0
	bl marioGetPtr
	bl marioGetPtr
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @83
	lfs f30, float_4_8041ae58(r2)
	b @84
	@83:
	lfs f30, float_neg4_8041ae5c(r2)
	@84:
	bl marioGetPtr
	lwz r29, 0x288(r3)
	lfs f31, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p05_8041ae4c(r2)
	lfs f1, 0x1c(r3)
	fsubs f1, f30, f1
	fmadds f0, f0, f1, f31
	stfs f0, 0x1c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x1a8(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f0, f1
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @85
	lfs f1, 0x1a8(r31)
	lfs f0, float_540_8041ae60(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @86
	stfs f0, 0x1a8(r31)
	li r27, 0x1
	b @86
	@85:
	lfs f1, 0x1a8(r31)
	lfs f0, float_neg360_8041ae54(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @86
	stfs f0, 0x1a8(r31)
	li r27, 0x1
	@86:
	lwz r0, 0x44(r31)
	cmpwi r0, 0x2f
	bne @2
	cmpwi r27, 0x0
	beq @2
	lfs f1, 0x1a8(r31)
	bl revise360
	stfs f1, 0x1a8(r31)
	lfs f0, 0x1a8(r31)
	stfs f0, 0x1ac(r31)
	lfs f1, 0x1a8(r31)
	bl toMovedir
	stfs f1, 0x19c(r31)
	li r3, 0xa
	lfs f2, float_20_8041ad9c(r2)
	lfs f0, 0x19c(r31)
	lfs f1, float_37_8041ae64(r2)
	stfs f0, 0x1a0(r31)
	lfs f0, float_0_8041ada0(r2)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r31)
	stfs f2, 0x1b4(r31)
	stfs f1, 0x1b8(r31)
	stfs f0, 0x7c(r31)
	stfs f0, 0x80(r31)
	stfs f0, 0x84(r31)
	stfs f0, 0x88(r31)
	stfs f0, 0x180(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r31)
	stfs f0, 0x9c(r31)
	bl marioChgMot
	bl marioSetFallPara
	bl allPartyRideOff
	lfs f1, 0x8c(r31)
	lfs f2, 0x90(r31)
	lfs f3, 0x94(r31)
	bl N_marioSetBottomlessRespawnPosOnBeroEntry
	bl N_marioReloadMapOnBottomlessOff
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @87
	bl marioGetPtr
	mr r4, r3
	li r3, 0x0
	lwz r4, 0x288(r4)
	bl __memFree
	li r29, 0x0
	bl marioGetPtr
	stw r29, 0x288(r3)
	@87:
	lwz r0, 0xc(r31)
	rlwinm. r0, r0, 0, 29, 29
	bne @2
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	b @2
	@88:
	li r0, 0x34
	stw r0, 0x44(r31)
	@89:
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	beq @90
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, 0xc(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, 0x8(r3)
	fsubs f1, f0, f31
	bl revise360
	fmr f31, f1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x8(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f1, float_3p1416_8041adc4(r2)
	lfs f2, 0x8(r3)
	lfs f0, float_180_8041adc0(r2)
	fmuls f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	frsp f2, f1
	lfs f1, float_3_8041ae6c(r2)
	lfs f0, float_neg13_8041ae68(r2)
	fmadds f0, f1, f2, f0
	stfs f0, 0x9c(r31)
	@90:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 26, 26
	beq @91
	lfs f30, 0x180(r31)
	bl marioGetPtr
	lfs f0, float_0_8041ada0(r2)
	mr r30, r3
	fcmpu cr0, f30, f0
	bne @92
	bl marioGetPtr
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_180_8041adc0(r2)
	lfs f1, 0x8(r3)
	fcmpo cr0, f1, f0
	ble @93
	li r0, 0x0
	b @94
	@93:
	li r0, 0x1
	@94:
	cmpwi r0, 0x0
	beq @95
	lfs f30, float_0p3_8041ae70(r2)
	b @96
	@95:
	lfs f30, float_0p6_8041ae74(r2)
	@96:
	bl marioGetPtr
	lwz r29, 0x288(r3)
	lfs f31, 0x10(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p1_8041ae14(r2)
	lfs f1, 0x10(r3)
	fsubs f1, f30, f1
	fmadds f0, f0, f1, f31
	stfs f0, 0x10(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, 0x10(r3)
	@92:
	lfs f31, 0x8c(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0_8041ada0(r2)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x4(r3)
	lfs f1, 0x90(r30)
	fadds f31, f1, f0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x8(r3)
	lfs f31, 0x94(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0xc(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f30, 0x10(r3)
	lfs f31, 0x1a8(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x14(r3)
	b @2
	@91:
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	bne @97
	li r0, 0x0
	stb r0, 0x24e(r31)
	stb r0, 0x24f(r31)
	@97:
	bl shipMove
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 14
	beq @98
	bl marioMakeJumpPara
	lfs f1, 0x7c(r31)
	lfs f0, float_neg7_8041ae78(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @99
	stfs f0, 0x7c(r31)
	@99:
	lfs f30, 0x7c(r31)
	bl marioGetPtr
	lfs f0, float_20_8041ad9c(r2)
	mr r29, r3
	fmr f1, f30
	addi r3, r1, 0x8
	stfs f0, 0x1b4(r29)
	bl marioChkLandon
	lfs f0, float_40_8041ad98(r2)
	cmplwi r3, 0x0
	stfs f0, 0x1b4(r29)
	beq @100
	lfs f2, 0x90(r29)
	lfs f0, 0x8(r1)
	lfs f1, float_0_8041ada0(r2)
	fsubs f0, f2, f0
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	beq @101
	fadds f0, f0, f30
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @100
	@101:
	stw r3, 0x1e4(r29)
	lfs f0, 0x8(r1)
	stfs f0, 0x90(r29)
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r29)
	lfs f1, 0x8c(r29)
	lfs f2, 0x94(r29)
	lfs f3, 0x11c(r29)
	lfs f4, 0x124(r29)
	bl distABf
	fabs f0, f1
	li r0, 0x0
	stfs f0, 0x128(r29)
	lwz r3, 0x0(r29)
	rlwinm r3, r3, 0, 25, 23
	stw r3, 0x0(r29)
	sth r0, 0x50(r29)
	sth r0, 0x52(r29)
	bl camFollowYOn
	li r0, 0x1
	b @102
	@100:
	li r0, 0x0
	@102:
	cmpwi r0, 0x0
	bne @103
	lfs f1, 0x90(r31)
	lfs f0, 0x7c(r31)
	fadds f0, f1, f0
	stfs f0, 0x90(r31)
	b @103
	@98:
	bl marioClearJumpPara
	@103:
	lwz r3, gp(r13)
	addi r4, r30, 0x68
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @104
	lfs f1, 0x90(r31)
	lfs f0, float_260_8041ae7c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @104
	lfs f0, float_50_8041adb8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @104
	lfs f2, float_10_8041ae38(r2)
	lis r0, 0x4330
	lfs f4, 0x214(r31)
	lfs f0, float_0p5_8041ada8(r2)
	stw r0, 0x48(r1)
	fmadds f0, f2, f4, f0
	lfd f1, 0x50(r30)
	lfs f3, float_0_8041ada0(r2)
	fctiwz f0, f0
	stfd f0, 0x50(r1)
	lwz r0, 0x54(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x4c(r1)
	lfd f0, 0x48(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fcmpu cr0, f3, f0
	beq @104
	lfs f1, float_3p1416_8041adc4(r2)
	lfs f0, float_180_8041adc0(r2)
	fmuls f1, f1, f4
	fdivs f1, f1, f0
	bl sin
	frsp f3, f1
	lfs f1, float_2_8041ae3c(r2)
	lfs f0, 0x90(r31)
	lfs f2, float_3p1416_8041adc4(r2)
	fmadds f1, f1, f3, f0
	lfs f0, float_180_8041adc0(r2)
	stfs f1, 0x90(r31)
	lfs f1, 0x214(r31)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	frsp f1, f1
	lfs f2, float_2_8041ae3c(r2)
	lfs f0, 0x94(r31)
	fneg f1, f1
	fmadds f0, f2, f1, f0
	stfs f0, 0x94(r31)
	@104:
	li r0, 0x0
	stw r0, 0x1e0(r31)
	stw r0, 0x1dc(r31)
	stw r0, 0x1ec(r31)
	stw r0, 0x1f0(r31)
	lfs f1, 0x180(r31)
	lfs f2, 0x1a0(r31)
	bl marioCheckWallShip
	lfs f1, 0x180(r31)
	lfs f0, float_0p5_8041ada8(r2)
	fcmpo cr0, f1, f0
	bge @105
	lfs f0, float_0_8041ada0(r2)
	li r0, 0x32
	stfs f0, 0x180(r31)
	stw r0, 0x44(r31)
	@105:
	lfs f30, 0x180(r31)
	bl marioGetPtr
	lfs f0, float_0_8041ada0(r2)
	mr r29, r3
	fcmpu cr0, f30, f0
	bne @106
	bl marioGetPtr
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_180_8041adc0(r2)
	lfs f1, 0x8(r3)
	fcmpo cr0, f1, f0
	ble @107
	li r0, 0x0
	b @108
	@107:
	li r0, 0x1
	@108:
	cmpwi r0, 0x0
	beq @109
	lfs f30, float_0p3_8041ae70(r2)
	b @110
	@109:
	lfs f30, float_0p6_8041ae74(r2)
	@110:
	bl marioGetPtr
	lwz r30, 0x288(r3)
	lfs f31, 0x10(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0p1_8041ae14(r2)
	lfs f1, 0x10(r3)
	fsubs f1, f30, f1
	fmadds f0, f0, f1, f31
	stfs f0, 0x10(r30)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, 0x10(r3)
	@106:
	lfs f31, 0x8c(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_0_8041ada0(r2)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x4(r3)
	lfs f1, 0x90(r29)
	fadds f31, f1, f0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x8(r3)
	lfs f31, 0x94(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0xc(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f30, 0x10(r3)
	lfs f31, 0x1a8(r29)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stfs f31, 0x14(r3)
	lhz r0, 0x248(r31)
	andi. r0, r0, 0xa00
	beq @2
	bl marioGetPtr
	lwz r3, 0x288(r3)
	addi r3, r3, 0x3c
	bl checkHarbor
	cmpwi r3, 0x0
	beq @2
	li r0, 0x1e
	stw r0, 0x44(r31)
	@2:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	lmw r27, 0x5c(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void mot_ship_post(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	bl marioGetPtr
	mr r30, r3
	bl allPartyRideOff
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 1, 1
	beq @1
	bl marioPaperOff
	@1:
	lfs f1, float_20_8041ad9c(r2)
	lfs f0, float_37_8041ae64(r2)
	stfs f1, 0x1b4(r30)
	stfs f0, 0x1b8(r30)
	bl marioGetPtr
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @2
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @2
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x38(r3)
	bl psndSFXOff
	li r31, -0x1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r31, 0x38(r3)
	@2:
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x4(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r30)
	bl marioOfsRotReset
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @3
	bl marioGetPtr
	mr r4, r3
	li r3, 0x0
	lwz r4, 0x288(r4)
	bl __memFree
	li r31, 0x0
	bl marioGetPtr
	stw r31, 0x288(r3)
	@3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioReInit_ship(void) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stfd f30, 0x20(r1)
	psq_st f30, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl marioGetPtr
	mr r31, r3
	li r3, 0x0
	lwz r0, 0xc(r31)
	li r4, 0x48
	clrrwi r0, r0, 1
	stw r0, 0xc(r31)
	bl __memAlloc
	mr r29, r3
	bl marioGetPtr
	stw r29, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r4, 0x0
	li r5, 0x48
	bl memset
	li r0, 0x19
	lfs f1, float_neg15_8041ae10(r2)
	sth r0, 0x2e(r31)
	li r0, 0x32
	lfs f0, float_40_8041ad98(r2)
	stfs f1, 0x9c(r31)
	stw r0, 0x44(r31)
	stfs f0, 0x1b4(r31)
	stfs f0, 0x1b8(r31)
	bl marioGetColor
	slwi r0, r3, 2
	la r3, paper_ship(r13)
	lwzx r3, r3, r0
	bl marioPaperOn
	lis r3, str_802C5E60@ha
	addi r3, r3, str_802C5E60@l
	bl marioChgPaper
	la r3, str_8041ADFC(r2)
	bl marioChgPose
	lwz r3, 0x4(r31)
	li r0, 0x58
	ori r3, r3, 0x8
	stw r3, 0x4(r31)
	stw r0, 0x2a4(r31)
	lwz r3, 0x2a4(r31)
	bl marioSetPaperAnimeLocalTime
	li r29, -0x1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r30, 0x0
	stw r29, 0x38(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041ada0(r2)
	stw r30, 0x0(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_0_8041ada0(r2)
	stfs f31, 0x4(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041ada0(r2)
	stfs f30, 0x14(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_0_8041ada0(r2)
	stfs f31, 0x18(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041ada0(r2)
	stfs f30, 0x1c(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f30, float_0_8041ada0(r2)
	stfs f31, 0x20(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_4p25_8041ade4(r2)
	stfs f30, 0x8(r3)
	bl marioGetPtr
	lfs f1, float_0_8041ada0(r2)
	lwz r4, 0x288(r3)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	stfs f31, 0xc(r4)
	fmr f4, f1
	fmr f5, f1
	bl effFunemizuEntry
	mr r30, r3
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r30, 0x24(r3)
	lwz r31, 0x134(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x24(r3)
	lwz r3, 0xc(r3)
	stw r31, 0x48(r3)
	bl allPartyForceRideOn
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	psq_l f30, 0x28(r1), 0, 0
	lfd f30, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x44(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void marioForceShipAnime(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPtr
	mr r31, r3
	bl marioPaperOff
	li r3, 0x0
	bl marioChgPaper
	bl marioGetColor
	slwi r0, r3, 2
	la r3, paper_ship(r13)
	lwzx r3, r3, r0
	bl marioPaperOn
	lis r3, str_802C5E70@ha
	addi r3, r3, str_802C5E70@l
	bl marioChgPaper
	la r3, str_8041ADFC(r2)
	bl marioChgPose
	lwz r0, 0x4(r31)
	ori r0, r0, 0x8
	stw r0, 0x4(r31)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL marioChkShipPlace(HitEntry* hit) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl hitGetAttr
	rlwinm r3, r3, 0, 14, 17
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioShipSetDispDir(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	bl marioGetPtr
	lfs f30, float_0_8041ada0(r2)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041ada0(r2)
	stfs f30, 0x14(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x18(r3)
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f30, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void marioShipForceStop(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	bl marioGetPtr
	lfs f30, float_0_8041ada0(r2)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041ada0(r2)
	stfs f30, 0x14(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x18(r3)
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f30, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL marioChkSwirlPower(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r3, 0x30(r3)
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioSetSwirlPower(s32 msec, f32 a, f32 b) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x18(r1)
	fmr f31, f2
	stfd f30, 0x10(r1)
	fmr f30, f1
	stw r31, 0xc(r1)
	mr r31, r3
	bl marioGetPtr
	mr r3, r31
	bl sysMsec2Frame
	mr r31, r3
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r31, 0x30(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f30, 0x2c(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x28(r3)
	lwz r0, 0x24(r1)
	lfd f31, 0x18(r1)
	lfd f30, 0x10(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 marioShipChanging(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x19
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x44(r3)
	cmpwi r0, 0xa
	bne @3
	li r3, 0x2
	b @2
	@3:
	cmpwi r0, 0x0
	blt @4
	cmpwi r0, 0xc
	ble @5
	@4:
	cmpwi r0, 0x1e
	blt @6
	cmpwi r0, 0x30
	bgt @6
	@5:
	li r3, 0x1
	b @2
	@6:
	cmpwi r0, 0x32
	beq @7
	cmpwi r0, 0x34
	bne @8
	@7:
	li r3, 0x3
	b @2
	@8:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 N_marioShipGetDir(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @1
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x0(r3)
	extrwi r3, r0, 1, 30
	b @2
	@1:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
