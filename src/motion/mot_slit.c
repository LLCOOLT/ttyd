#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "mot/mot_slit.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

#ifdef VERSION_G8ME01
void U_allPartySlitOffReq(void);
#endif

s32 pouchCheckItem(s32 itemId);
BOOL marioChkKey(void);
s32 marioKeyOffChk(void);
BOOL marioBgmodeChk(void);
BOOL marioChkJump(void);
BOOL marioRollChgChk(void);
BOOL marioPaperOn(const char* name);
void marioPaperOff(void);
void marioChgPaper(const char* name);
void marioChgPose(const char* name);
void marioAdjustMoveDir(void);
void marioChgMot(MarioMotion);
void marioChgMotSub(MarioMotion, s32);
void marioChgMot2(MarioMotion);
void marioSetFallPara(void);
BOOL marioSlitChkWallAround(void);
void allPartySlitOn(void);
void allPartySlitOff(void);
void allPartyForceSlitOff(void);
void mapSetPaperAmbColor(GXColor);
void mapResetPaperAmbColor(void);
f32 toMovedirSimple(f32);
f32 revise360(f32);
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
double fabs(double);
BOOL marioCreviceWallChk(const Vec* p);
CameraEntry* camGetPtr(CameraId);

int __abs(int);
#define abs __abs



#ifdef VERSION_G8ME01_DEMO
/* the demo keeps the slit state machine in the generic motion fields */
typedef s32 SlitState;
#define SLIT_STATE(m) ((m)->currSubMotionId)
#define SLIT_TIMER(m) ((m)->multiTimer)
#define SLIT_TIMER2(m) ((m)->mot.slit.timer2)
/* the exit states remember where they are, for marioSlitResume */
#define SLIT_SAVE(m) (m)->mot.slit.resumeState = SLIT_STATE(m);
#define SLIT_MARK(m) SLIT_SAVE(m) (m)->mot.slit.flags |= 0x10;
#else
typedef s16 SlitState;
#define SLIT_STATE(m) ((m)->slitState)
#define SLIT_TIMER(m) ((m)->slitTimer)
#define SLIT_TIMER2(m) ((m)->slitTimer2)
#define SLIT_SAVE(m)
#define SLIT_MARK(m)
#endif

#ifndef VERSION_G8ME01_DEMO
void marioSlitReenter(void) {
	MarioWork* mario = marioGetPtr();
	marioChgMot2(MARIO_MOTION_SLIT);
	SLIT_STATE(mario) = 10;
	mario->flags &= ~0xF0000;
}

void N_marioSlitSetAfterLand(void) {
	MarioWork* mario = marioGetPtr();
	marioChgMot2(MARIO_MOTION_SLIT);
	mario->flags &= ~0xF0000;
}
#endif

BOOL marioSlitAbilityChk(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x800000) {
		return FALSE;
	}
	if (!pouchCheckItem(2)) {
		return FALSE;
	}
	if (mario->flags & 0x80000000) {
		return FALSE;
	}
	return marioBgmodeChk() != 1;
}

s32 marioSlitButton(void) {
	MarioWork* mario = marioGetPtr();
#ifndef VERSION_G8ME01_DEMO
	if (mario->trigFlags & 2) {
		return 0;
	}
#endif
	if (marioKeyOffChk()) {
		return 0;
	}
	if (marioBgmodeChk() == 1) {
		return 0;
	}
#ifdef VERSION_G8ME01_DEMO
	if (!(mario->flags & 0x100000)) {
#else
	if (!(mario->dispFlags & 0x1000000)) {
#endif
		if (mario->buttonHold & 0x20) {
			return 1;
		}
	} else {
		if (mario->buttonHold & 0x20) {
			return 2;
		}
		if (mario->triggerR >= 50) {
			return 2;
		}
	}
	return 0;
}

BOOL marioSlitKeyDisable(void) {
	MarioWork* mario = marioGetPtr();
	SlitState st;
	if (!(mario->flags & 0x100000)) {
		return TRUE;
	}
	st = SLIT_STATE(mario);
	if (st >= 0x50 && st <= 0x52) {
		return FALSE;
	}
	if (st >= 0x5a && st <= 0x5e) {
		return FALSE;
	}
	return TRUE;
}

#ifndef VERSION_G8ME01_DEMO
BOOL U_marioSlitContinueChk(void) {
	MarioWork* mario = marioGetPtr();
	Vec pos;
	if (marioSlitButton()) {
		return TRUE;
	}
	if (marioSlitChkWallAround()) {
		return TRUE;
	}
	pos = mario->position;
	return marioCreviceWallChk(&pos) != 0;
}
#endif

BOOL marioCreviceWallChk(const Vec* p) {
	f32 offX;
	f32 offZ;
	f32 angA;
	f32 angB;
	HitEntry* hitA;
	HitEntry* hitB;
	f32 s;
	f32 c;
	f32 dist;
	f32 h = 10.0f;
	Vec pos;
	Vec dir;
	Vec outPos;
	Vec outNrm;

	marioGetPtr();
	sincosf(&s, &c, toMovedirSimple(270.0f));
	offX = 0.5f * (20.0f * s);
	offZ = 0.5f * (20.0f * c);
	angA = 0.0f;
	angB = angA;
	sincosf(&s, &c, toMovedirSimple(180.0f));
	dist = 20.0f;
	pos = *p;
	pos.y += 10.0f;
	{
		Vec t1 = {0, 0, 0};
		t1.x = s;
		t1.z = c;
		dir = t1;
	}
	hitA = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
	if (hitA) {
		angA = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
	}
	if (!hitA) {
		Vec t2 = {0, 0, 0};
		dist = 20.0f;
		t2.x = p->x + offX;
		t2.y = p->y + h;
		t2.z = p->z + offZ;
		pos = t2;
		hitA = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
		if (hitA) {
			angA = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
		}
	}
	if (!hitA) {
		Vec t3 = {0, 0, 0};
		dist = 20.0f;
		t3.x = p->x - offX;
		t3.y = p->y + h;
		t3.z = p->z - offZ;
		pos = t3;
		hitA = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
		if (hitA) {
			angA = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
		}
	}
	sincosf(&s, &c, toMovedirSimple(0.0f));
	dist = 20.0f;
	pos = *p;
	pos.y += 10.0f;
	{
		Vec u1 = {0, 0, 0};
		u1.x = s;
		u1.z = c;
		dir = u1;
	}
	hitB = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
	if (hitB) {
		angB = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
	}
	if (!hitB) {
		Vec u2 = {0, 0, 0};
		dist = 20.0f;
		u2.x = p->x + offX;
		u2.y = p->y + h;
		u2.z = p->z + offZ;
		pos = u2;
		hitB = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
		if (hitB) {
			angB = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
		}
	}
	if (!hitB) {
		Vec u3 = {0, 0, 0};
		dist = 20.0f;
		u3.x = p->x - offX;
		u3.y = p->y + h;
		u3.z = p->z - offZ;
		pos = u3;
		hitB = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
		if (hitB) {
			angB = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
		}
	}
	if (hitA && hitB && __fabsf(180.0f - 0.5f * (angA + angB)) <= 10.0f) {
		return TRUE;
	}
	return FALSE;
}

void marioClearSlitFloor(void) {
	MarioWork* mario = marioGetPtr();
	mario->slitPosSet = 0;
}

BOOL marioGetSlitFloorPos(Vec* out) {
	MarioWork* mario = marioGetPtr();
	if (mario->slitPosSet) {
		*out = mario->slitPos;
		return TRUE;
	}
	return FALSE;
}

BOOL marioChkSlitThrouh(void) {
	MarioWork* mario = marioGetPtr();
	SlitState st;
	if (mario->currMotionId != MARIO_MOTION_SLIT) {
		return FALSE;
	}
	st = SLIT_STATE(mario);
	if (st >= 0x50 && st <= 0x5e) {
		return TRUE;
	}
	return FALSE;
}

BOOL marioChkSlitThrouhEnd(void) {
	MarioWork* mario = marioGetPtr();
	SlitState st;
	if (mario->currMotionId != MARIO_MOTION_SLIT) {
		return FALSE;
	}
	st = SLIT_STATE(mario);
	if (st == 0x52 || st == 0x5e) {
		return TRUE;
	}
	return FALSE;
}

void motSlitContinue(void) {
	s16 v;
	v = 0x14;
	marioChgMot2(MARIO_MOTION_SLIT);
	SLIT_STATE(marioGetPtr()) = v;
}

#ifdef VERSION_G8ME01_DEMO
void marioSlitResume(void) {
	MarioWork* mario = marioGetPtr();
	marioChgMot2(MARIO_MOTION_SLIT);
	if (!(mario->mot.slit.flags & 0x10)) {
		SLIT_STATE(mario) = 0x64;
	} else {
		SLIT_STATE(mario) = mario->mot.slit.resumeState;
	}
}
#endif

BOOL marioChkSlitEnd(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->currMotionId != MARIO_MOTION_SLIT) {
		return FALSE;
	}
	return SLIT_STATE(mario) >= 0x64;
}

void motSlitCancel(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x100000) {
		SLIT_STATE(mario) = 0x64;
	}
}

void motSlitCancel2(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x100000) {
#ifndef VERSION_G8ME01_DEMO
		allPartyForceSlitOff();
#endif
		SLIT_STATE(mario) = 0x6e;
	}
}

void motSlitCancel3(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x100000) {
		SLIT_STATE(mario) = 0x78;
	}
}

BOOL marioGetMotSlitCancel3(void) {
	SlitState st;
	BOOL r = FALSE;
	MarioWork* mario = marioGetPtr();
	if (mario->currMotionId == MARIO_MOTION_SLIT) {
		st = SLIT_STATE(mario);
		if ((st >= 0x78 && st <= 0x7a) || (st >= 0x6e && st <= 0x70)) {
			r = TRUE;
		}
	}
	return r;
}

#define CLR_DISP 0xFEFFF3FF
#define CLR_SLITFLAGS(m) \
	(m)->flags &= ~0x400000; \
	(m)->flags &= ~0x200000; \
	(m)->dispFlags &= CLR_DISP; \
	(m)->dispFlags &= CLR_DISP;

static inline void slitSetDir(MarioWork* m, f32 a) {
	if (revise360(m->directionView - m->targetYaw) <= 180.0f) {
		m->displayDirection = 260.0f;
	} else {
		m->displayDirection = 280.0f;
	}
}

void marioSlitForceCancel(void) {
	MarioWork* m = marioGetPtr();
	if (m->flags & 0x100000) {
		m->flags &= ~0x100000;
		if (m->directionView >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
		}
		m->dispFlags &= CLR_DISP;
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
#ifdef VERSION_G8ME01_DEMO
		m->wPlayerCollisionBox.x = 20.0f;
#else
		m->wPlayerCollisionBox.x = 10.0f;
#endif
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		{
			MarioWork* p = marioGetPtr();
			p->camShiftTargetZ = 0.0f;
			p->camShiftRate.z = 0.004f;
		}
		allPartyForceSlitOff();
	}
}

void mot_slit_post(void) {
#ifdef VERSION_G8ME01_DEMO
	MarioWork* m = marioGetPtr();
	u16 id;
	if (!(m->flags & 0x100000)) {
		if (m->dispFlags & 0x1000000) {
			m->wPlayerCollisionBox.x = 20.0f;
			if (m->directionView >= 180.0f) {
				m->displayDirection = 0.0f;
				m->displayDirectionTarget = m->displayDirection;
			} else {
				m->displayDirection = 180.0f;
				m->displayDirectionTarget = m->displayDirection;
			}
			CLR_SLITFLAGS(m)
			marioPaperOff();
			mapResetPaperAmbColor();
			m->dispFlags &= ~4;
			marioAdjustMoveDir();
			allPartyForceSlitOff();
		}
	} else {
		id = m->currMotionId;
		if (id == 1 || (u16)(id - 2) <= 5 || m->currMotionId == 8) {
			return;
		}
		m->flags &= ~0x100000;
		m->wPlayerCollisionBox.x = 20.0f;
		if (m->directionView >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
		}
		CLR_SLITFLAGS(m)
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		allPartyForceSlitOff();
	}
}
#else
#ifdef VERSION_G8ME01
	MarioWork* m = marioGetPtr();
	u16 id;
	if (SLIT_STATE(m) >= 10) {
		id = m->currMotionId;
		if (id == 0x15 || (u16)(id - 0xb) <= 1 || m->currMotionId <= 7 || m->currMotionId == 8) {
			return;
		}
	}
#else
	MarioWork* m = marioGetPtr();
	u16 id = m->currMotionId;
	if (id == 0x15 || (u16)(id - 0xb) <= 1 || m->currMotionId <= 7 || m->currMotionId == 8) {
		return;
	}
#endif
	if (!(m->flags & 0x100000)) {
		if (m->dispFlags & 0x1000000) {
			m->wPlayerCollisionBox.x = 20.0f;
			if (m->directionView >= 180.0f) {
				m->displayDirection = 0.0f;
				m->displayDirectionTarget = m->displayDirection;
			} else {
				m->displayDirection = 180.0f;
				m->displayDirectionTarget = m->displayDirection;
			}
			CLR_SLITFLAGS(m)
			marioPaperOff();
			mapResetPaperAmbColor();
			m->dispFlags &= ~4;
#ifdef VERSION_G8MP01
			if (!(m->flags & 0x20)) {
				marioAdjustMoveDir();
			}
#else
			marioAdjustMoveDir();
#endif
			allPartyForceSlitOff();
		}
	} else if (m->currMotionId != 10) {
		m->flags &= ~0x100000;
		m->wPlayerCollisionBox.x = 20.0f;
		if (m->directionView >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
		}
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->dispFlags &= 0xFEFFF3FF;
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
#ifdef VERSION_G8ME01
		if (m->currMotionId != 0x16) {
			allPartyForceSlitOff();
		} else {
			U_allPartySlitOffReq();
		}
#else
		allPartyForceSlitOff();
#endif
	}
}
#endif

void marioForceSlitAnime(void) {
	MarioWork* m = marioGetPtr();
	marioPaperOff();
	marioChgPaper(NULL);
	marioPaperOn("p_slit");
	marioChgPose("M_S_1");
	marioChgPaper("PM_S_1A");
	m->dispFlags |= 4;
}

static inline void slitInit(void) {
	MarioWork* m = marioGetPtr();
	m->mot.slit.reserved_0 = 0.0f;
	m->mot.slit.counter = 0;
	m->mot.slit.count = 0;
	m->mot.slit.timer = 0;
	m->mot.slit.side = 0;
	m->trigFlags &= ~1;
	m->flags &= ~0xF0000;
	m->dispFlags |= 4;
	m->dispFlags |= 0x1000000;
	if (m->paperPoseId == -1) {
		GXColor tmp; GXColor col = {0, 0, 0, 255};
		col.r = 0xa8; col.g = 0xa8; col.b = 0xa8;
		tmp = col; ((void (*)(GXColor*))mapSetPaperAmbColor)(&tmp);
		marioPaperOn("p_slit");
	}
	if (!m->controlStickSensitivity) {
		marioChgPose("M_S_1");
	}
	marioChgPaper("PM_S_1A");
}

void marioReInit_slit(void) {
	MarioWork* m = marioGetPtr();
	slitInit();
	m->trigFlags &= ~1;
	m->currMotionId = MARIO_MOTION_SLIT;
	SLIT_STATE(m) = 10;
	m->displayDirection = 270.0f;
	m->displayDirectionTarget = m->displayDirection;
	marioChgPose("M_S_1");
	marioChgPaper("PM_S_1B");
	SLIT_STATE(m) = 10;
	m->mot.slit.count = 0;
	m->wPlayerCollisionBox.x = 6.0f;
	m->flags |= 0x100000;
	m->dispFlags |= 0x1000000;
	allPartySlitOn();
}

static inline BOOL slitContinueChk(void) {
	MarioWork* mario = marioGetPtr();
	Vec pos;
#ifdef VERSION_G8ME01_DEMO
	if (marioSlitButton() == 2) {
#else
	if (marioSlitButton()) {
#endif
		return TRUE;
	}
	if (marioSlitChkWallAround()) {
		return TRUE;
	}
	pos = mario->position;
	if (marioCreviceWallChk(&pos)) {
		return TRUE;
	}
	return FALSE;
}

#ifdef VERSION_G8ME01
#define SPEEDCHK_COND(m) ((m)->baseSpeed >= (m)->mBaseDashSpeed || (m)->controlStickSensitivity)
#else
#define SPEEDCHK_COND(m) ((m)->baseSpeed >= (m)->mBaseDashSpeed)
#endif
#define SPEEDCHK(m) SPEEDCHK_IF(m, (m)->baseSpeed >= (m)->mBaseDashSpeed)
#define SPEEDCHK_US(m) SPEEDCHK_IF(m, SPEEDCHK_COND(m))
#define SPEEDCHK_IF(m, c) \
	if (c) { \
		(m)->baseSpeed = (m)->mBaseWalkSpeed; \
		if (!((m)->trigFlags & 0x8000)) { \
			marioChgPose("M_R_1"); \
		} \
		m->mot.slit.flags |= 1; \
	}

static inline f32 slitWalkSpeed(void) {
	MarioWork* p = marioGetPtr();
	f32 spd = p->mBaseWalkSpeed;
	if (p->flags & 0x100000) {
		if (p->mot.slit.timer != 0) return spd; {
			int a = p->wStickDir1; int b = p->wStickDir2;
			if (a * a + b * b <= 0xbd1) {
				spd *= 0.5f;
			}

		}
	} else if (p->flags & 0x2000000) {
		spd *= 0.5f;
	}
	return spd;
}

#define SLITDIR(m) 	(m)->displayDirection = (revise360((m)->directionView - (m)->targetYaw) <= 180.0f) ? 260.0f : 280.0f;

#define SLITDIR2(m) 	if (revise360((m)->directionView - (m)->targetYaw) <= 180.0f) { 		m->mot.slit.side = 1; 		(m)->displayDirection = 260.0f; 	} else { 		m->mot.slit.side = 2; 		(m)->displayDirection = 280.0f; 	}

#define CAMFIX(m) \
	{ \
		MarioWork* p = marioGetPtr(); \
		p->camShiftTargetZ = 0.0f; \
		p->camShiftRate.z = 0.004f; \
	}

#ifdef VERSION_G8ME01
#define SLITSTOP(m) \
	if (!marioChkKey()) { \
		(m)->baseSpeed = 0.0f; \
		SLIT_STATE(m) = 10; \
		m->mot.slit.count = 0; \
		marioChgPose("M_S_1"); \
		marioChgPaper("PM_S_1B"); \
		break; \
	}
#define SLITSTOP2(m) \
	if (!marioChkKey()) { \
		m->mot.slit.timer = 0; \
		(m)->baseSpeed = 0.0f; \
		SLIT_STATE(m) = 10; \
		m->mot.slit.count = 0; \
		marioChgPose("M_S_1"); \
		marioChgPaper("PM_S_1B"); \
		break; \
	}
#else
#define SLITSTOP(m)
#define SLITSTOP2(m)
#endif

void mot_slit(void) {
	MarioWork* m = marioGetPtr();
	f32 d;
	SlitState st;
	if (!m->controlStickSensitivity) {
		m->trigFlags &= ~0x8000;
	}
	if (m->trigFlags & 1) {
		slitInit();
		SLIT_STATE(m) = 0;
		m->airTimer = 0;
	}
	if (marioRollChgChk()) {
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
		}
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		m->flags &= ~0x100000;
		return;
	}
	switch (SLIT_STATE(m)) {
	case 0:
		SLIT_TIMER(m) = 30;
		m->mot.slit.counter = 0;
		SLIT_STATE(m) = 2;
		m->mot.slit.lastY = m->position.y;
		SPEEDCHK_US(m)
		marioGetPtr();
		psndSFXOn_3D((char*)0x177, &m->position);
		break;
	case 2:
#ifdef VERSION_G8MP01
		if (m->flags & 0x20) {
			break;
		}
#endif
#ifdef VERSION_G8ME01
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		} else {
			SPEEDCHK_US(m)
			m->directionView = m->controlStickAngle;
		}
		if (--SLIT_TIMER(m) <= 0) {
#else
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		}
		if (--SLIT_TIMER(m) <= 0) {
#endif
			m->flags |= 0x100000;
			SLIT_STATE(m) = 4;
			m->wPlayerCollisionBox.x = 6.0f;
		}
		if (SLIT_TIMER(m) == 0x14) {
			allPartySlitOn();
		}
		break;
	case 4:
		if (marioChkKey()) {
			if (!m->controlStickSensitivity) {
				m->baseSpeed = 0.0f;
				marioChgPose("M_S_1");
			}
			m->directionView = toMovedirSimple(m->displayDirection);
		}
#ifdef VERSION_G8MP01
		if (!(m->flags & 0x20)) {
			SPEEDCHK(m)
		}
#else
		SPEEDCHK(m)
#endif
		m->displayDirection = 270.0f;
		m->displayDirectionTarget = m->displayDirection;
		if (!m->controlStickSensitivity) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1B");
		SLIT_STATE(m) = 10;
		m->mot.slit.count = 0;
	case 10:
		if (m->position.y != m->mot.slit.lastY) {
			CAMFIX(m)
		}
		m->mot.slit.lastY = m->position.y;
		if (m->forceMoveTimer != 0) {
			if (!(m->trigFlags & 0x8000)) {
				marioChgPose("M_W_1");
			}
			marioChgPaper("PM_S_1D");
			if (revise360(m->directionView - m->targetYaw) <= 180.0f) {
				m->mot.slit.side = 1;
				m->displayDirection = 260.0f;
			} else {
				m->mot.slit.side = 2;
				m->displayDirection = 280.0f;
			}
			break;
		}
		SPEEDCHK(m)
		if (marioChkKey()) {
			if (slitContinueChk() != TRUE) {
#ifndef VERSION_G8ME01_DEMO
				m->directionView = m->controlStickAngle;
#endif
				SLIT_STATE(m) = 0x64;
				break;
			}
		}
		if (marioChkJump()) {
			return;
		}
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			if (!m->mot.slit.counter) {
				marioChgPose("M_S_1");
				marioChgPaper("PM_S_1B");
			}
			break;
		}
		if (strcmp(m->animName, "M_I_Y") == 0) {
			marioChgPose("M_W_1");
		}
		if (!(m->mot.slit.flags & 1)) {
			CAMFIX(m)
		} else {
			m->mot.slit.flags &= ~1;
			CAMFIX(m)
		}
		m->baseSpeed = slitWalkSpeed();
		m->directionView = m->controlStickAngle;
		if (!(m->trigFlags & 0x8000)) {
			marioChgPose("M_W_1");
		}
		d = revise360(m->controlStickAngle - m->targetYaw);
		if (d >= 315.0f || d <= 45.0f || (d >= 135.0f && d <= 225.0f)) {
			marioChgPaper("PM_S_1E");
		} else {
			marioChgPaper("PM_S_1D");
			SLITDIR2(m)
		}
		SLIT_STATE(m) = 0x14;
		break;
	}
	switch (SLIT_STATE(m)) {
	case 0x14:
#ifndef VERSION_G8ME01_DEMO
		if (m->mot.slit.timer > 0) {
			m->mot.slit.timer = 0;
			marioChgPaper("PM_S_1D");
			SLITDIR(m)
			SLITSTOP(m)
		}
#endif
		if (marioChkKey()) {
			if (slitContinueChk() != TRUE) {
				SLIT_STATE(m) = 0x64;
			}
		}
		if (!(m->flags & 0x30000)) {
			marioChkJump();
		}
		if (marioChkKey()) {
			if (!m->controlStickSensitivity) {
				m->baseSpeed = 0.0f;
				if (++m->mot.slit.count < 6) {
					if (slitContinueChk() != TRUE) {
						SLIT_STATE(m) = 0x64;
					}
					break;
				} else {
					SLIT_STATE(m) = 4;
					break;
				}
			} else {
				s32 sum;
				m->mot.slit.count = 0;
				sum = abs((s8)m->wStickDir1) + abs((s8)m->wStickDir2);
				if (!(m->trigFlags & 0x8000)) {
					marioChgPose((sum < 0x44) ? "M_W_1" : "M_R_1");
				}
			}
		}
		if (marioChkKey()) {
			m->directionView = m->controlStickAngle;
			m->baseSpeed = slitWalkSpeed();
		}
		d = revise360(m->controlStickAngle - m->targetYaw);
		if (d >= 315.0f || d <= 45.0f || (d >= 135.0f && d <= 225.0f)) {
			marioChgPaper("PM_S_1E");
			m->mot.slit.count = 6;
			m->mot.slit.side = 0;
			SLITDIR(m)
			break;
		} else {
			marioChgPaper("PM_S_1D");
			d = revise360(m->directionView - m->targetYaw);
			if (m->mot.slit.side == 0) {
				m->mot.slit.side = (d >= 180.0f) ? 2 : 1;
			}
			if (m->mot.slit.side == 1) {
				if (d >= 180.0f) {
					marioChgPaper("PM_S_2");
					m->mot.slit.timer = 6;
					SLIT_STATE(m) = 0x15;
					m->mot.slit.side = 2;
					m->baseSpeed = slitWalkSpeed();
#ifndef VERSION_G8ME01_DEMO
					m->displayDirection = 260.0f;
#endif
					SLITSTOP2(m)
				}
			} else if (m->mot.slit.side == 2) {
				if (d <= 180.0f) {
					marioChgPaper("PM_S_2");
					m->mot.slit.timer = 6;
					SLIT_STATE(m) = 0x15;
					m->mot.slit.side = 1;
					m->baseSpeed = slitWalkSpeed();
#ifndef VERSION_G8ME01_DEMO
					m->displayDirection = 280.0f;
#endif
					SLITSTOP2(m)
				}
			}
		}
		break;
	case 0x15:
		if (--m->mot.slit.timer > 0) {
			SLITSTOP2(m)
			break;
		}
		marioChgPaper("PM_S_1D");
		SLIT_STATE(m) = 0x14;
#ifdef VERSION_G8ME01_DEMO
		SLITDIR(m)
#else
		m->displayDirection = (m->mot.slit.side == 1) ? 260.0f : 280.0f;
#endif
		break;
	}
	if (m->flags & 0x100000) {
		if (m->hitobjPush != NULL) {
#ifdef VERSION_G8ME01_DEMO
			if (hitGetAttr(m->hitobjPush) & 0x2000) {
				HitCheckQuery q;
				f32 sn, cs;
				d = revise360(m->controlStickAngle - m->targetYaw);
				if (d > 90.0f && d < 270.0f) {
					m->mot.slit.pushDir = 180.0f;
				} else {
					m->mot.slit.pushDir = 0.0f;
				}
				if (++m->mot.slit.counter >= sysMsec2Frame(50)) {
					m->directionView = revise360(m->mot.slit.pushDir + m->targetYaw);
					sincosf(&sn, &cs, m->directionView);
					q.targetPos = m->position;
					q.targetPos.y += 11.0f;
					{ Vec tmp = {0, 0, 0};
					tmp.x = sn;
					tmp.z = cs;
					q.targetDir = tmp; }
					q.targetDistance = 20.0f;
					if (hitCheckVecHitObjXZ(&q, m->hitobjPush)) {
						SLIT_STATE(m) = 0x50;
					}
				}
			} else {
				m->mot.slit.counter = 0;
			}
#else
			if (m->hitobjStandOn != NULL && m->currMotionId == 0x15) {
				if (hitGetAttr(m->hitobjPush) & 0x2000) {
					HitCheckQuery q;
					HitCheckQuery* qp;
					f32 sn, cs;
					d = revise360(m->controlStickAngle - m->targetYaw);
					if (d > 90.0f && d < 270.0f) {
						m->mot.slit.pushDir = 180.0f;
					} else {
						m->mot.slit.pushDir = 0.0f;
					}
					if (++m->mot.slit.counter >= sysMsec2Frame(50)) {
						qp = &q; m->directionView = revise360(m->mot.slit.pushDir + m->targetYaw);
						m->mot.slit.counter = 0;
						sincosf(&sn, &cs, m->directionView);
						{ Vec tmp = {0, 0, 0};
						q.targetPos.x = m->position.x;
						q.targetPos.y = 11.0f + m->position.y;
						q.targetPos.z = m->position.z;
						tmp.x = sn;
						tmp.z = cs;
						q.targetDir = tmp; }
						q.targetDistance = 20.0f;
						if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
							q.targetPos.x = m->position.x;
							q.targetPos.z = m->position.z;
							q.targetDistance = 20.0f;
							movePos(&qp->targetPos.x, &qp->targetPos.z, 1.0f, reviseAngle(90.0f + m->moveDirection));
							if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
								q.targetPos.x = m->position.x;
								q.targetPos.z = m->position.z;
								q.targetDistance = 20.0f;
								movePos(&qp->targetPos.x, &qp->targetPos.z, 1.0f, reviseAngle(m->moveDirection - 90.0f));
								if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
									SLIT_STATE(m) = 0x50;
								}
							}
						}
					}
				} else {
					m->mot.slit.counter = 0;
				}
			}
#endif
		} else {
			st = SLIT_STATE(m);
			if (!(st >= 0x5a && st <= 0x5e) && m->hitobjStandOn != NULL && (hitGetAttr(m->hitobjStandOn) & 0x2000)) {
				m->mot.slit.counter += 3;
				marioChgPaper("PM_S_1H");
#ifdef VERSION_G8ME01_DEMO
				if (m->mot.slit.counter >= 0xf) {
#else
				if (m->mot.slit.counter >= 0xf && m->currMotionId == 0x15) {
#endif
					SLIT_STATE(m) = 0x5a;
				}
			} else {
				m->mot.slit.counter--;
				if (m->mot.slit.counter < 0) {
					m->mot.slit.counter = 0;
				}
			}
		}
	}
	switch (SLIT_STATE(m)) {
	case 0x50:
		camGetPtr(8)->flags |= 0x200;
		CAMFIX(m)
		m->flags |= 0x10000000;
		if (0.0f == m->mot.slit.pushDir) {
			marioChgPaper("PM_S_1F");
		} else {
			marioChgPaper("PM_S_1G");
		}
		m->flags |= 0x400;
		SLIT_TIMER(m) = 20;
		m->baseSpeed = (2.0f * m->wPlayerCollisionBox.x) / (f32)SLIT_TIMER(m);
		SLIT_STATE(m) = 0x51;
		m->flags |= 0x200000;
		break;
	case 0x51:
		if (--SLIT_TIMER(m) <= 0) {
			SLIT_STATE(m) = 0x52;
		}
		break;
	case 0x52:
		camGetPtr(8)->flags &= ~0x200;
		m->flags &= ~0x400;
		SLIT_STATE(m) = 0x14;
		m->flags &= ~0x10000000;
		break;
	}
	switch (SLIT_STATE(m)) {
	case 0x5a:
		camGetPtr(8)->flags |= 0x200;
		CAMFIX(m)
		m->flags |= 0x10000000;
		marioChgPaper("PM_S_1H");
		SLIT_TIMER(m) = sysMsec2Frame(500);
		m->baseSpeed = 0.0f;
		SLIT_STATE(m) = 0x5b;
		{
			MarioWork* p = marioGetPtr();
			p->slitPosSet = 1;
			// copy
			p->slitPos = p->position;
		}
	case 0x5b:
#ifdef VERSION_G8ME01_DEMO
		SLIT_TIMER(m) = 20;
#else
		SLIT_TIMER(m) = 15;
#endif
		SLIT_STATE(m) = 0x5c;
		m->flags |= 0x100;
		marioSetFallPara();
		m->flags &= ~0x10000;
		m->flags |= 0xA0000;
	case 0x5c:
		SLITDIR(m)
		if (--SLIT_TIMER(m) > 0) {
			break;
		}
		SLIT_STATE(m) = 0x5d;
		m->flags &= ~0x100;
#ifndef VERSION_G8ME01_DEMO
		m->flags &= ~0x10000000;
#endif
	case 0x5d:
		if (m->hitobjStandOn == NULL) {
			break;
		}
		m->flags &= ~0xF0000;
		SLIT_STATE(m) = 0x5e;
	case 0x5e:
		camGetPtr(8)->flags &= ~0x200;
		SLIT_STATE(m) = 0x14;
#ifdef VERSION_G8ME01_DEMO
		m->flags &= ~0x10000000;
#endif
		break;
	}
	switch (SLIT_STATE(m)) {
	case 0x64:
		m->flags &= ~0x200000;
		SLIT_MARK(m)
		SLIT_TIMER2(m) = 0;
		m->flags &= ~0x100000;
		m->wPlayerCollisionBox.x = 20.0f;
#ifdef VERSION_G8ME01
		SPEEDCHK_IF(m, m->controlStickSensitivity)
#endif
		if (m->baseSpeed == 0.0f) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1C");
		SLIT_TIMER2(m) = 30;
		SLIT_STATE(m) = 0x65;
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
			if (!m->controlStickSensitivity) {
				m->directionView = toMovedirSimple(m->displayDirection);
			}
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
			if (!m->controlStickSensitivity) {
				m->directionView = toMovedirSimple(m->displayDirection);
			}
		}
		psndSFXOn_3D((char*)0x178, &m->position);
	case 0x65:
		SLIT_SAVE(m)
#ifdef VERSION_G8MP01
		if (m->flags & 0x20) {
			break;
		}
#endif
#ifdef VERSION_G8ME01
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		} else {
			SPEEDCHK_IF(m, 1)
			m->directionView = m->controlStickAngle;
		}
#else
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		}
#endif
		if (--SLIT_TIMER2(m) > 0) {
			break;
		}
		SLIT_STATE(m) = 0x66;
		break;
	case 0x66:
		SLIT_SAVE(m)
#if defined(VERSION_G8MP01)
		if (!(m->flags & 0x20)) {
			if (!m->controlStickSensitivity) {
				m->baseSpeed = 0.0f;
				marioChgPose("M_S_1");
			} else {
				SPEEDCHK_IF(m, 1)
			}
		}
#elif defined(VERSION_G8ME01)
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		} else {
			SPEEDCHK_IF(m, 1)
		}
#else
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		}
#endif
		m->flags &= ~0x400000; m->flags &= ~0x200000; m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
#ifdef VERSION_G8MP01
		if (!(m->flags & 0x20)) {
			marioAdjustMoveDir();
		}
#else
		marioAdjustMoveDir();
#endif
#ifndef VERSION_G8ME01
		allPartySlitOff();
#endif
		CAMFIX(m)
		marioChgMotSub(0, 0);
		break;
	case 0x6e:
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->flags &= ~0x10000000;
		m->flags &= ~0x400;
		SLIT_MARK(m)
		SLIT_TIMER2(m) = 0;
		m->flags &= ~0x100000;
		m->wPlayerCollisionBox.x = 20.0f;
		if (!m->controlStickSensitivity) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1C");
		SLIT_TIMER2(m) = 30;
		SLIT_STATE(m) = 0x6f;
		m->baseSpeed = 0.0f;
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
			m->directionView = toMovedirSimple(m->displayDirection);
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
			m->directionView = toMovedirSimple(m->displayDirection);
		}
		psndSFXOn_3D((char*)0x178, &m->position);
	case 0x6f:
		SLIT_SAVE(m)
		if (--SLIT_TIMER2(m) > 0) {
			break;
		}
		SLIT_STATE(m) = 0x70;
		break;
	case 0x70:
		SLIT_SAVE(m)
		m->flags &= ~0x400000; m->flags &= ~0x200000; m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		allPartySlitOff();
		CAMFIX(m)
		marioChgMot(0);
		break;
	case 0x78:
		SLIT_MARK(m)
		SLIT_TIMER2(m) = 0;
		m->flags &= ~0x100000;
		m->wPlayerCollisionBox.x = 20.0f;
		if (!m->controlStickSensitivity) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1C");
		SLIT_TIMER2(m) = 30;
		SLIT_STATE(m) = 0x79;
		m->baseSpeed = 0.0f;
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->displayDirection = 0.0f;
			m->displayDirectionTarget = m->displayDirection;
			m->directionView = toMovedirSimple(m->displayDirection);
		} else {
			m->displayDirection = 180.0f;
			m->displayDirectionTarget = m->displayDirection;
			m->directionView = toMovedirSimple(m->displayDirection);
		}
		psndSFXOn_3D((char*)0x178, &m->position);
	case 0x79:
		SLIT_SAVE(m)
		if (--SLIT_TIMER2(m) > 0) {
			break;
		}
		SLIT_STATE(m) = 0x7a;
		break;
	case 0x7a:
		SLIT_SAVE(m)
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->flags &= ~0x400;
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		allPartySlitOff();
		CAMFIX(m)
		marioChgMot(0);
		break;
	}
}
