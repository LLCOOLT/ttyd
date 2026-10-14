#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "mot/mot_slit.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

#define MW(m, off, T) (*(T*)((u8*)(m) + (off)))

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



void unk_800a4e40(void) {
	MarioWork* mario = marioGetPtr();
	marioChgMot2(MARIO_MOTION_SLIT);
	MW(mario, 0x2d8, s16) = 10;
	mario->flags &= ~0xF0000;
}

void N_marioSlitSetAfterLand(void) {
	MarioWork* mario = marioGetPtr();
	marioChgMot2(MARIO_MOTION_SLIT);
	mario->flags &= ~0xF0000;
}

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
	if (mario->trigFlags & 2) {
		return 0;
	}
	if (marioKeyOffChk()) {
		return 0;
	}
	if (marioBgmodeChk() == 1) {
		return 0;
	}
	if (!(mario->dispFlags & 0x1000000)) {
		if (MW(mario, 0x246, u16) & 0x20) {
			return 1;
		}
	} else {
		if (MW(mario, 0x246, u16) & 0x20) {
			return 2;
		}
		if (MW(mario, 0x253, u8) >= 50) {
			return 2;
		}
	}
	return 0;
}

BOOL marioSlitKeyDisable(void) {
	MarioWork* mario = marioGetPtr();
	s16 st;
	if (!(mario->flags & 0x100000)) {
		return TRUE;
	}
	st = MW(mario, 0x2d8, s16);
	if (st >= 0x50 && st <= 0x52) {
		return FALSE;
	}
	if (st >= 0x5a && st <= 0x5e) {
		return FALSE;
	}
	return TRUE;
}

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
	MW(mario, 0x268, s32) = 0;
}

BOOL marioGetSlitFloorPos(Vec* out) {
	MarioWork* mario = marioGetPtr();
	if (MW(mario, 0x268, s32)) {
		*out = MW(mario, 0x26c, Vec);
		return TRUE;
	}
	return FALSE;
}

BOOL marioChkSlitThrouh(void) {
	MarioWork* mario = marioGetPtr();
	s16 st;
	if (mario->currMotionId != MARIO_MOTION_SLIT) {
		return FALSE;
	}
	st = MW(mario, 0x2d8, s16);
	if (st >= 0x50 && st <= 0x5e) {
		return TRUE;
	}
	return FALSE;
}

BOOL marioChkSlitThrouhEnd(void) {
	MarioWork* mario = marioGetPtr();
	s16 st;
	if (mario->currMotionId != MARIO_MOTION_SLIT) {
		return FALSE;
	}
	st = MW(mario, 0x2d8, s16);
	if (st == 0x52 || st == 0x5e) {
		return TRUE;
	}
	return FALSE;
}

void motSlitContinue(void) {
	s16 v;
	v = 0x14;
	marioChgMot2(MARIO_MOTION_SLIT);
	MW(marioGetPtr(), 0x2d8, s16) = v;
}

BOOL marioChkSlitEnd(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->currMotionId != MARIO_MOTION_SLIT) {
		return FALSE;
	}
	return MW(mario, 0x2d8, s16) >= 0x64;
}

void motSlitCancel(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x100000) {
		MW(mario, 0x2d8, s16) = 0x64;
	}
}

void motSlitCancel2(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x100000) {
		allPartyForceSlitOff();
		MW(mario, 0x2d8, s16) = 0x6e;
	}
}

void motSlitCancel3(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->flags & 0x100000) {
		MW(mario, 0x2d8, s16) = 0x78;
	}
}

BOOL marioGetMotSlitCancel3(void) {
	s16 st;
	BOOL r = FALSE;
	MarioWork* mario = marioGetPtr();
	if (mario->currMotionId == MARIO_MOTION_SLIT) {
		st = MW(mario, 0x2d8, s16);
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
		m->unk1A8 = 260.0f;
	} else {
		m->unk1A8 = 280.0f;
	}
}

void marioSlitForceCancel(void) {
	MarioWork* m = marioGetPtr();
	if (m->flags & 0x100000) {
		m->flags &= ~0x100000;
		if (m->directionView >= 180.0f) {
			m->unk1A8 = 0.0f;
			m->unk1AC = m->unk1A8;
		} else {
			m->unk1A8 = 180.0f;
			m->unk1AC = m->unk1A8;
		}
		m->dispFlags &= CLR_DISP;
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		MW(m, 0x1b4, f32) = 10.0f;
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		{
			MarioWork* p = marioGetPtr();
			MW(p, 0x148, f32) = 0.0f;
			MW(p, 0x158, f32) = 0.004f;
		}
		allPartyForceSlitOff();
	}
}

void mot_slit_post(void) {
	MarioWork* m = marioGetPtr();
	u16 id = m->currMotionId;
	int new_var;
	if (id == 0x15 || (u16)(id - 0xb) <= 1 || m->currMotionId <= 7 || m->currMotionId == 8) {
		return;
	}
	if (!(m->flags & 0x100000)) {
		if (m->dispFlags & 0x1000000) {
			MW(m, 0x1b4, f32) = 20.0f;
			if (m->directionView >= 180.0f) {
				m->unk1A8 = 0.0f;
				m->unk1AC = m->unk1A8;
			} else {
				m->unk1A8 = 180.0f;
				m->unk1AC = m->unk1A8;
			}
			CLR_SLITFLAGS(m)
			marioPaperOff();
			mapResetPaperAmbColor();
			m->dispFlags &= ~4;
			marioAdjustMoveDir();
			allPartyForceSlitOff();
		}
	} else if (m->currMotionId != 10) {
		m->flags &= ~0x100000;
		MW(m, 0x1b4, f32) = 20.0f;
		new_var = 0xFEFFF3FF;
		if (m->directionView >= 180.0f) {
			m->unk1A8 = 0.0f;
			m->unk1AC = m->unk1A8;
		} else {
			m->unk1A8 = 180.0f;
			m->unk1AC = m->unk1A8;
		}
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->dispFlags &= new_var;
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		allPartyForceSlitOff();
	}
}

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
	MW(m, 0x2a0, f32) = 0.0f;
	MW(m, 0x2a4, s32) = 0;
	MW(m, 0x2b6, s16) = 0;
	MW(m, 0x2b4, s16) = 0;
	MW(m, 0x2ba, s16) = 0;
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
	MW(m, 0x2d8, s16) = 10;
	m->unk1A8 = 270.0f;
	m->unk1AC = m->unk1A8;
	marioChgPose("M_S_1");
	marioChgPaper("PM_S_1B");
	MW(m, 0x2d8, s16) = 10;
	MW(m, 0x2b6, s16) = 0;
	MW(m, 0x1b4, f32) = 6.0f;
	m->flags |= 0x100000;
	m->dispFlags |= 0x1000000;
	allPartySlitOn();
}

static inline BOOL slitContinueChk(void) {
	MarioWork* mario = marioGetPtr();
	Vec pos;
	if (marioSlitButton()) {
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

#define SPEEDCHK(m) \
	if ((m)->baseSpeed >= (m)->mBaseDashSpeed) { \
		(m)->baseSpeed = (m)->mBaseWalkSpeed; \
		if (!((m)->trigFlags & 0x8000)) { \
			marioChgPose("M_R_1"); \
		} \
		MW(m, 0x2b8, s16) |= 1; \
	}

static inline f32 slitWalkSpeed(void) {
	MarioWork* p = marioGetPtr();
	f32 spd = p->mBaseWalkSpeed;
	if (p->flags & 0x100000) {
		if (MW(p, 0x2b4, s16) != 0) return spd; {
			int a = MW(p, 0x24e, s8); int b = MW(p, 0x24f, s8);
			if (a * a + b * b <= 0xbd1) {
				spd *= 0.5f;
			}

		}
	} else if (p->flags & 0x2000000) {
		spd *= 0.5f;
	}
	return spd;
}

#define SLITDIR(m) 	(m)->unk1A8 = (revise360((m)->directionView - (m)->targetYaw) <= 180.0f) ? 260.0f : 280.0f;

#define SLITDIR2(m) 	if (revise360((m)->directionView - (m)->targetYaw) <= 180.0f) { 		MW(m, 0x2ba, s16) = 1; 		(m)->unk1A8 = 260.0f; 	} else { 		MW(m, 0x2ba, s16) = 2; 		(m)->unk1A8 = 280.0f; 	}

#define CAMFIX(m) \
	{ \
		MarioWork* p = marioGetPtr(); \
		MW(p, 0x148, f32) = 0.0f; \
		MW(p, 0x158, f32) = 0.004f; \
	}

void mot_slit(void) {
	MarioWork* m = marioGetPtr();
	f32 d;
	s16 st;
	if (!m->controlStickSensitivity) {
		m->trigFlags &= ~0x8000;
	}
	if (m->trigFlags & 1) {
		slitInit();
		MW(m, 0x2d8, s16) = 0;
		m->airTimer = 0;
	}
	if (marioRollChgChk()) {
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->unk1A8 = 0.0f;
			m->unk1AC = m->unk1A8;
		} else {
			m->unk1A8 = 180.0f;
			m->unk1AC = m->unk1A8;
		}
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->dispFlags &= CLR_DISP;
		marioPaperOff();
		m->flags &= ~0x100000;
		return;
	}
	switch (MW(m, 0x2d8, s16)) {
	case 0:
		MW(m, 0x2dc, s32) = 30;
		MW(m, 0x2a4, s32) = 0;
		MW(m, 0x2d8, s16) = 2;
		MW(m, 0x2ac, f32) = m->position.y;
		SPEEDCHK(m)
		marioGetPtr();
		psndSFXOn_3D((char*)0x177, &m->position);
		break;
	case 2:
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		}
		if (--MW(m, 0x2dc, s32) <= 0) {
			m->flags |= 0x100000;
			MW(m, 0x2d8, s16) = 4;
			MW(m, 0x1b4, f32) = 6.0f;
		}
		if (MW(m, 0x2dc, s32) == 0x14) {
			allPartySlitOn();
		}
		break;
	case 4:
		if (marioChkKey()) {
			if (!m->controlStickSensitivity) {
				m->baseSpeed = 0.0f;
				marioChgPose("M_S_1");
			}
			m->directionView = toMovedirSimple(m->unk1A8);
		}
		SPEEDCHK(m)
		m->unk1A8 = 270.0f;
		m->unk1AC = m->unk1A8;
		if (!m->controlStickSensitivity) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1B");
		MW(m, 0x2d8, s16) = 10;
		MW(m, 0x2b6, s16) = 0;
	case 10:
		if (m->position.y != MW(m, 0x2ac, f32)) {
			CAMFIX(m)
		}
		MW(m, 0x2ac, f32) = m->position.y;
		if (m->forceMoveTimer != 0) {
			if (!(m->trigFlags & 0x8000)) {
				marioChgPose("M_W_1");
			}
			marioChgPaper("PM_S_1D");
			if (revise360(m->directionView - m->targetYaw) <= 180.0f) {
				MW(m, 0x2ba, s16) = 1;
				m->unk1A8 = 260.0f;
			} else {
				MW(m, 0x2ba, s16) = 2;
				m->unk1A8 = 280.0f;
			}
			break;
		}
		SPEEDCHK(m)
		if (marioChkKey()) {
			if (slitContinueChk() != TRUE) {
				m->directionView = m->controlStickAngle;
				MW(m, 0x2d8, s16) = 0x64;
				break;
			}
		}
		if (marioChkJump()) {
			return;
		}
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			if (!MW(m, 0x2a4, s32)) {
				marioChgPose("M_S_1");
				marioChgPaper("PM_S_1B");
			}
			break;
		}
		if (strcmp(m->animName, "M_I_Y") == 0) {
			marioChgPose("M_W_1");
		}
		if (!(MW(m, 0x2b8, s16) & 1)) {
			CAMFIX(m)
		} else {
			MW(m, 0x2b8, s16) &= ~1;
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
		MW(m, 0x2d8, s16) = 0x14;
		break;
	}
	switch (MW(m, 0x2d8, s16)) {
	case 0x14:
		if (MW(m, 0x2b4, s16) > 0) {
			MW(m, 0x2b4, s16) = 0;
			marioChgPaper("PM_S_1D");
			SLITDIR(m)
		}
		if (marioChkKey()) {
			if (slitContinueChk() != TRUE) {
				MW(m, 0x2d8, s16) = 0x64;
			}
		}
		if (!(m->flags & 0x30000)) {
			marioChkJump();
		}
		if (marioChkKey()) {
			if (!m->controlStickSensitivity) {
				m->baseSpeed = 0.0f;
				if (++MW(m, 0x2b6, s16) < 6) {
					if (slitContinueChk() != TRUE) {
						MW(m, 0x2d8, s16) = 0x64;
					}
					break;
				} else {
					MW(m, 0x2d8, s16) = 4;
					break;
				}
			} else {
				s32 sum;
				MW(m, 0x2b6, s16) = 0;
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
			MW(m, 0x2b6, s16) = 6;
			MW(m, 0x2ba, s16) = 0;
			SLITDIR(m)
			break;
		} else {
			marioChgPaper("PM_S_1D");
			d = revise360(m->directionView - m->targetYaw);
			if (MW(m, 0x2ba, s16) == 0) {
				MW(m, 0x2ba, s16) = (d >= 180.0f) ? 2 : 1;
			}
			if (MW(m, 0x2ba, s16) == 1) {
				if (d >= 180.0f) {
					marioChgPaper("PM_S_2");
					MW(m, 0x2b4, s16) = 6;
					MW(m, 0x2d8, s16) = 0x15;
					MW(m, 0x2ba, s16) = 2;
					m->baseSpeed = slitWalkSpeed();
					m->unk1A8 = 260.0f;
				}
			} else if (MW(m, 0x2ba, s16) == 2) {
				if (d <= 180.0f) {
					marioChgPaper("PM_S_2");
					MW(m, 0x2b4, s16) = 6;
					MW(m, 0x2d8, s16) = 0x15;
					MW(m, 0x2ba, s16) = 1;
					m->baseSpeed = slitWalkSpeed();
					m->unk1A8 = 280.0f;
				}
			}
		}
		break;
	case 0x15:
		if (--MW(m, 0x2b4, s16) > 0) {
			break;
		}
		marioChgPaper("PM_S_1D");
		MW(m, 0x2d8, s16) = 0x14;
		m->unk1A8 = (MW(m, 0x2ba, s16) == 1) ? 260.0f : 280.0f;
		break;
	}
	if (m->flags & 0x100000) {
		if (m->hitobjPush != NULL) {
			if (m->hitobjStandOn != NULL && m->currMotionId == 0x15) {
				if (hitGetAttr(m->hitobjPush) & 0x2000) {
					HitCheckQuery q;
					HitCheckQuery* qp;
					f32 sn, cs;
					d = revise360(m->controlStickAngle - m->targetYaw);
					if (d > 90.0f && d < 270.0f) {
						MW(m, 0x2a8, f32) = 180.0f;
					} else {
						MW(m, 0x2a8, f32) = 0.0f;
					}
					if (++MW(m, 0x2a4, s32) >= sysMsec2Frame(50)) {
						qp = &q; m->directionView = revise360(MW(m, 0x2a8, f32) + m->targetYaw);
						MW(m, 0x2a4, s32) = 0;
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
							movePos(&qp->targetPos.x, &qp->targetPos.z, 1.0f, reviseAngle(90.0f + m->unk19C));
							if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
								q.targetPos.x = m->position.x;
								q.targetPos.z = m->position.z;
								q.targetDistance = 20.0f;
								movePos(&qp->targetPos.x, &qp->targetPos.z, 1.0f, reviseAngle(m->unk19C - 90.0f));
								if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
									MW(m, 0x2d8, s16) = 0x50;
								}
							}
						}
					}
				} else {
					MW(m, 0x2a4, s32) = 0;
				}
			}
		} else {
			st = MW(m, 0x2d8, s16);
			if (!(st >= 0x5a && st <= 0x5e) && m->hitobjStandOn != NULL && (hitGetAttr(m->hitobjStandOn) & 0x2000)) {
				MW(m, 0x2a4, s32) += 3;
				marioChgPaper("PM_S_1H");
				if (MW(m, 0x2a4, s32) >= 0xf && m->currMotionId == 0x15) {
					MW(m, 0x2d8, s16) = 0x5a;
				}
			} else {
				MW(m, 0x2a4, s32)--;
				if (MW(m, 0x2a4, s32) < 0) {
					MW(m, 0x2a4, s32) = 0;
				}
			}
		}
	}
	switch (MW(m, 0x2d8, s16)) {
	case 0x50:
		camGetPtr(8)->flags |= 0x200;
		CAMFIX(m)
		m->flags |= 0x10000000;
		if (0.0f == MW(m, 0x2a8, f32)) {
			marioChgPaper("PM_S_1F");
		} else {
			marioChgPaper("PM_S_1G");
		}
		m->flags |= 0x400;
		MW(m, 0x2dc, s32) = 20;
		m->baseSpeed = (2.0f * MW(m, 0x1b4, f32)) / (f32)MW(m, 0x2dc, s32);
		MW(m, 0x2d8, s16) = 0x51;
		m->flags |= 0x200000;
		break;
	case 0x51:
		if (--MW(m, 0x2dc, s32) <= 0) {
			MW(m, 0x2d8, s16) = 0x52;
		}
		break;
	case 0x52:
		camGetPtr(8)->flags &= ~0x200;
		m->flags &= ~0x400;
		MW(m, 0x2d8, s16) = 0x14;
		m->flags &= ~0x10000000;
		break;
	}
	switch (MW(m, 0x2d8, s16)) {
	case 0x5a:
		camGetPtr(8)->flags |= 0x200;
		CAMFIX(m)
		m->flags |= 0x10000000;
		marioChgPaper("PM_S_1H");
		MW(m, 0x2dc, s32) = sysMsec2Frame(500);
		m->baseSpeed = 0.0f;
		MW(m, 0x2d8, s16) = 0x5b;
		{
			MarioWork* p = marioGetPtr();
			MW(p, 0x268, s32) = 1;
			// copy
			MW(p, 0x26c, Vec) = MW(p, 0x8c, Vec);
		}
	case 0x5b:
		MW(m, 0x2dc, s32) = 15;
		MW(m, 0x2d8, s16) = 0x5c;
		m->flags |= 0x100;
		marioSetFallPara();
		m->flags &= ~0x10000;
		m->flags |= 0xA0000;
	case 0x5c:
		SLITDIR(m)
		if (--MW(m, 0x2dc, s32) > 0) {
			break;
		}
		MW(m, 0x2d8, s16) = 0x5d;
		m->flags &= ~0x100;
		m->flags &= ~0x10000000;
	case 0x5d:
		if (m->hitobjStandOn == NULL) {
			break;
		}
		m->flags &= ~0xF0000;
		MW(m, 0x2d8, s16) = 0x5e;
	case 0x5e:
		camGetPtr(8)->flags &= ~0x200;
		MW(m, 0x2d8, s16) = 0x14;
		break;
	}
	switch (MW(m, 0x2d8, s16)) {
	case 0x64:
		m->flags &= ~0x200000;
		MW(m, 0x2da, s16) = 0;
		m->flags &= ~0x100000;
		MW(m, 0x1b4, f32) = 20.0f;
		if (m->baseSpeed == 0.0f) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1C");
		MW(m, 0x2da, s16) = 30;
		MW(m, 0x2d8, s16) = 0x65;
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->unk1A8 = 0.0f;
			m->unk1AC = m->unk1A8;
			if (!m->controlStickSensitivity) {
				m->directionView = toMovedirSimple(m->unk1A8);
			}
		} else {
			m->unk1A8 = 180.0f;
			m->unk1AC = m->unk1A8;
			if (!m->controlStickSensitivity) {
				m->directionView = toMovedirSimple(m->unk1A8);
			}
		}
		psndSFXOn_3D((char*)0x178, &m->position);
	case 0x65:
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		}
		if (--MW(m, 0x2da, s16) > 0) {
			break;
		}
		MW(m, 0x2d8, s16) = 0x66;
		break;
	case 0x66:
		if (!m->controlStickSensitivity) {
			m->baseSpeed = 0.0f;
			marioChgPose("M_S_1");
		}
		m->flags &= ~0x400000; m->flags &= ~0x200000; m->dispFlags &= CLR_DISP;
		marioPaperOff();
		mapResetPaperAmbColor();
		m->dispFlags &= ~4;
		marioAdjustMoveDir();
		allPartySlitOff();
		CAMFIX(m)
		marioChgMotSub(0, 0);
		break;
	case 0x6e:
		m->flags &= ~0x400000;
		m->flags &= ~0x200000;
		m->flags &= ~0x10000000;
		m->flags &= ~0x400;
		MW(m, 0x2da, s16) = 0;
		m->flags &= ~0x100000;
		MW(m, 0x1b4, f32) = 20.0f;
		if (!m->controlStickSensitivity) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1C");
		MW(m, 0x2da, s16) = 30;
		MW(m, 0x2d8, s16) = 0x6f;
		m->baseSpeed = 0.0f;
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->unk1A8 = 0.0f;
			m->unk1AC = m->unk1A8;
			m->directionView = toMovedirSimple(m->unk1A8);
		} else {
			m->unk1A8 = 180.0f;
			m->unk1AC = m->unk1A8;
			m->directionView = toMovedirSimple(m->unk1A8);
		}
		psndSFXOn_3D((char*)0x178, &m->position);
	case 0x6f:
		if (--MW(m, 0x2da, s16) > 0) {
			break;
		}
		MW(m, 0x2d8, s16) = 0x70;
		break;
	case 0x70:
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
		MW(m, 0x2da, s16) = 0;
		m->flags &= ~0x100000;
		MW(m, 0x1b4, f32) = 20.0f;
		if (!m->controlStickSensitivity) {
			marioChgPose("M_S_1");
		}
		marioChgPaper("PM_S_1C");
		MW(m, 0x2da, s16) = 30;
		MW(m, 0x2d8, s16) = 0x79;
		m->baseSpeed = 0.0f;
		if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
			m->unk1A8 = 0.0f;
			m->unk1AC = m->unk1A8;
			m->directionView = toMovedirSimple(m->unk1A8);
		} else {
			m->unk1A8 = 180.0f;
			m->unk1AC = m->unk1A8;
			m->directionView = toMovedirSimple(m->unk1A8);
		}
		psndSFXOn_3D((char*)0x178, &m->position);
	case 0x79:
		if (--MW(m, 0x2da, s16) > 0) {
			break;
		}
		MW(m, 0x2d8, s16) = 0x7a;
		break;
	case 0x7a:
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
