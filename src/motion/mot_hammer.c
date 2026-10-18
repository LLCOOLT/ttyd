#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_pouch.h"
#include "mario/mario_sbr.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "driver/animdrv.h"
#include "eff/eff_kemu_test.h"
#include "eff/eff_ultra_hammer.h"
#include "system.h"
#include <string.h>

double cos(float);
void sincosf(f32* s, f32* c, f32 deg);
f32 revise360(f32);
void marioVoiceGlareOn(void);
void marioVoiceGlareOff(void);
s32 psndSFXOn_3D(s32 id, Vec* pos);
f32 toMovedir(f32 angle);
f32 toMovedir2(f32 angle, f32 off);
void* mobjHitObjPtrToPtr(HitEntry* hit);
USER_FUNC(evt_cam_shake);
HitEntry* hitEstimate(s32* out);
static HitEntry* hammerHitWall(f32 ang, f32* s, f32* co, f32* len, f32* hx, f32* hy, f32* hz, f32* nx, f32* ny, f32* nz);
void marioChgMotSub(s32 a, s32 b);
s32 marioGetRub(s32 mask, s32* a, s32* b, f32* c);

#define MF(o) (*(f32*)((u8*)mario + (o)))
#define MI(o) (*(s32*)((u8*)mario + (o)))
#define MB(o) (*(s8*)((u8*)mario + (o)))
#define MH(o) (*(u16*)((u8*)mario + (o)))


s32 se_data[] = {315, 357, 316, 359, 317, 358, 318, 360, 319, 361};

EVT_BEGIN(lv1quake_evt)
CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.009765625f), 90)
RETURN
EVT_END()

EVT_BEGIN(lv2quake_evt)
CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.01953125f), 110)
RETURN
EVT_END()

EVT_BEGIN(lv3quake_evt)
CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.029296875f), 140)
RETURN
EVT_END()

inline BOOL chkRevDir(f32 angle) {
	BOOL ret = FALSE;
	if (angle >= 90.0f && angle <= 270.0f) {
		ret = TRUE;
	}
	return ret;
}

#define HAM_DIR(mario, dst)                                         	{                                                               		f32 a = MF(0x1A8);                                          		MarioWork* p = marioGetPtr(); f32 r;                         		f32 off = 0.0f;                                             		if (p->dispFlags & 0x80000000) {                            			off = chkRevDir(p->displayDirection) ? 30.0f : -30.0f;            		} if (a >= 90.0f && a <= 270.0f) { r = revise360(180.0f + off); } else { r = revise360(off); } dst = r;                                                           	}

static inline s32 hamLv(void) {
	return pouchGetHammerLv();
}


typedef struct { u8 pad[0x15]; char name[0x10]; } HamMobj;

static const char isS1_str[14];
static const char isB1_str[17];
static const char isS2_str[14];
static const char isB2_str[17];
static const char isS3_str[14];
static const char isB3_str[17];
#define isB3(n) (strcmp((n), isB3_str) == 0)

#define isS3(n) (strcmp((n), isS3_str) == 0)

#define isB2(n) (strcmp((n), isB2_str) == 0)

#define isS2(n) (strcmp((n), isS2_str) == 0)

#define isB1(n) (strcmp((n), isB1_str) == 0)

#define isS1(n) (strcmp((n), isS1_str) == 0)

static inline s32 chkBlock(HamMobj* obj) {
	s32 ok = 0;
	if ((isS1(obj->name) || isB1(obj->name))) {
		if (pouchGetPtr()->hammerLevel >= 1) {
			ok = 1;
		}
	} else if ((isS2(obj->name) || isB2(obj->name))) {
		if (pouchGetPtr()->hammerLevel >= 2) {
			ok = 1;
		}
	} else if ((isS3(obj->name) || isB3(obj->name))) {
		if (pouchGetPtr()->hammerLevel >= 3) {
			ok = 1;
		}
	}
	return ok;
}

s32 marioGetHammerLevel(void) {
	return pouchGetPtr()->hammerLevel;
}


void mot_hammer(void) {
	MarioWork* mario = marioGetPtr();
	Vec* unused;
	s32 snd;
	s32 kind;
	f32 px, pz;
	s32 done;
	s32 i;
	f32 py, ez;
	s32 efType;
	HitEntry* hit;
	s32 n;

	if (MI(0xC) & 1) {
		MI(0xC) &= ~1;
		mario->flags &= ~0xF0000;
		mario->flags |= 0x80;
		HAM_DIR(mario, MF(0x2A4));
		MI(0x48) = 0;
		MH(0x50) = 0;
		MI(0x44) = 0;
		mario->baseSpeed = 0.0f;
		MI(0x200) = 0;
		hit = hitEstimate(&kind);
		MI(0x200) = (s32)hit;
		if (hit) {
			f32 a = mario->displayDirection;
			f32 off = marioGetPtr()->dispFlags & 0x80000000 ? -30.0f : 0.0f;
			f32 r;
			if (a >= 90.0f && a <= 270.0f) {
				r = toMovedir2(180.0f, off);
			} else {
				r = toMovedir2(0.0f, off);
			}
			mario->directionView = r;
			HAM_DIR(mario, MF(0x2A4));
		}
		if (hitGetAttr(hit) & 0x80000000) {
			s32 ok = chkBlock((HamMobj*)mobjHitObjPtrToPtr(hit));
			if (ok) {
				kind = 0;
			}
		}
		switch (pouchGetHammerLv()) {
		case 1:
			marioChgPose(kind == 7 ? "M_H_2" : "M_H_1");
			break;
		case 2:
			marioChgPose(kind == 7 ? "M_H_5" : "M_H_4");
			break;
		case 3:
			marioChgPose(kind == 7 ? "M_H_8" : "M_H_7");
			break;
		}
		if (kind != 0) {
			{
				s32 k = kind;
				MI(0x2A0) = k == 7 ? 3 : k;
			}
			mario->flags |= 0x800;
		} else {
			mario->flags &= ~0x800;
		}
		{
			MarioWork* m = marioGetPtr();
			snd = 0x15B;
			switch (pouchGetHammerLv()) {
			case 1:
				snd = 0x15B;
				break;
			case 2:
				snd = 0x15C;
				break;
			case 3:
				snd = 0x15D;
				break;
			}
			psndSFXOn_3D(snd, &m->position);
		}
		MI(0x2A8) = kind;
	}
	{
		f32 a = MF(0x2A4);
		BOOL r = FALSE;
		if (a >= 90.0f && a <= 270.0f) {
			r = TRUE;
		}
		mario->displayDirection = r ? 180.0f : 0.0f;
	}
	mario->displayDirectionTarget = mario->displayDirection;
	mario->moveDirection = toMovedir(MF(0x2A4));
	done = 0;
	mario->directionView = mario->moveDirection;
	if (mario->flags & 0x800) {
		s32 t = MI(0x48);
		s32 lim = MI(0x2A0);
		n = t <= lim ? t : lim;
		if (t == lim) {
			done = 1;
		}
	} else {
		n = MI(0x48) <= 10 ? MI(0x48) : 10;
		if (MI(0x48) == 10) {
			done = 1;
		}
	}
	MH(0x28) = n;
	animPoseSetLocalTime(mario->paperAnimGroupId[marioAnimeId()], (f32)n);
	if (done) {
		{
			s32 lv = pouchGetPtr()->hammerLevel;
			if (lv == 1) {
				evtEntry(lv1quake_evt, 0, 0);
			} else if (lv == 2) {
				evtEntry(lv2quake_evt, 0, 0);
			} else if (lv == 3) {
				evtEntry(lv3quake_evt, 0, 0);
			}
		}
		MI(0x44) = 1;
		MI(0x1FC) = MI(0x200);
		px = mario->position.x;
		py = mario->position.y;
		pz = mario->position.z;
		if (!(mario->dispFlags & 0x80000000)) {
			efType = -1;
			switch (MI(0x2A8)) {
			case 7:
				movePos(&px, &pz, 16.0f, toMovedir2(mario->displayDirectionTarget, 0.0f));
				ez = 53.0f;
				efType = 0x16;
				break;
			case 0:
			case 6:
				movePos(&px, &pz, 25.0f, toMovedir2(mario->displayDirectionTarget, 0.0f));
				ez = -3.0f;
				efType = 0x15;
				break;
			case 5:
				movePos(&px, &pz, 31.0f, toMovedir2(mario->displayDirectionTarget, 0.0f));
				ez = 5.0f;
				efType = 0x15;
				break;
			case 4:
				movePos(&px, &pz, 30.0f, toMovedir2(mario->displayDirectionTarget, 0.0f));
				ez = 30.0f;
				efType = 0x16;
				break;
			}
		} else {
			efType = -1;
			switch (MI(0x2A8)) {
			case 7:
				movePos(&px, &pz, 16.0f, toMovedir2(mario->displayDirectionTarget, -2.0f));
				ez = 53.0f;
				efType = 0x16;
				break;
			case 0:
			case 6:
				movePos(&px, &pz, 30.0f, toMovedir2(mario->displayDirectionTarget, -6.0f));
				ez = -3.0f;
				efType = 0x15;
				break;
			case 5:
				movePos(&px, &pz, 36.0f, toMovedir2(mario->displayDirectionTarget, -6.0f));
				ez = 20.0f;
				efType = 0x16;
				break;
			case 4:
				movePos(&px, &pz, 37.0f, toMovedir2(mario->displayDirectionTarget, -6.0f));
				ez = 28.0f;
				efType = 0x16;
				break;
			}
		}
		if (efType > 0) {
			effKemuTestEntry(efType, px, py + ez, pz, 1.0f);
		}
		{
			MarioWork* m = marioGetPtr();
			snd = 0x161;
			switch (pouchGetHammerLv()) {
			case 1:
				psndSFXOn_3D(0x15E, &m->position);
				break;
			case 2:
				psndSFXOn_3D(0x15F, &m->position);
				break;
			case 3:
				psndSFXOn_3D(0x160, &m->position);
				break;
			}
			for (i = 0; (u32)i < 10; i++) {
				if (pouchEquipCheckBadge(se_data[*(s8*)((u8*)m + 0x3A)])) {
					snd = se_data[*(s8*)((u8*)m + 0x3A) + 1];
					*(s8*)((u8*)m + 0x3A) += 2;
					if (*(s8*)((u8*)m + 0x3A) >= 10) {
						*(s8*)((u8*)m + 0x3A) -= 10;
					}
					break;
				} else {
					*(s8*)((u8*)m + 0x3A) += 2;
					if (*(s8*)((u8*)m + 0x3A) >= 10) {
						*(s8*)((u8*)m + 0x3A) -= 10;
					}
				}
			}
			psndSFXOn_3D(snd, &m->position);
		}
	}
	if (++MI(0x48) > 20) {
		mario->flags &= ~0x80;
		marioChgMot(0);
	}
}


s32 marioChkHammer2(void) {
	MarioWork* mario = marioGetPtr();
	s32 b, a;
	f32 c;
	if (pouchGetPtr()->hammerLevel < 2) {
		return 0;
	}
	if (!(MH(0x246) & 0x200)) {
		if (!(MH(0x246) & 0x100)) {
			if (strcmp(mario->animName, "M_I_Y") == 0 && mario->currMotionId == 0) {
				marioChgPose("M_S_1");
				marioVoiceGlareOff();
			}
			mario->wMotionTimer = 0;
		}
		return 0;
	}
	mario->wMotionTimer++;
	if (mario->controlStickSensitivity && mario->wMotionTimer > 10 && mario->currMotionId == 0 && !(mario->dispFlags & 0x40000000)) {
		marioChgPose("M_I_Y");
		marioVoiceGlareOn();
	}
	if (mario->wMotionTimer >= 50) {
		mario->wMotionTimer = 50;
		if (mario->currMotionId == 0 && !(mario->dispFlags & 0x40000000)) {
			marioChgPose("M_I_Y");
			marioVoiceGlareOn();
		}
	}
	if (marioGetRub(0x200, &a, &b, &c) != 1) {
		return 0;
	}
	mario->baseSpeed = 0.0f;
	if (b < 1) {
		return 0;
	}
	*(u8*)((u8*)mario + 0x43) = a;
	return 1;
}


#define MS(o) (*(s16*)((u8*)mario + (o)))


static inline void mot_ham(f32 a148, f32 a68) {
	MarioWork* m = marioGetPtr();
	m->camShiftTargetZ = a148;
	*(f32*)((u8*)m + 0x158) = 0.005f;
	m->field_68 = a68;
	m->field_6C = (Vec){0.0f, 40.0f, 0.0f};
}

#define H2_LV(lvl, a148, a68) { mot_ham(a148, a68); MS(0x2B4) |= 0x1000; }

#define H2_RAMP(maxv, midv, minv, lvl, a148, a68)                         \
	marioChgPaper("P_H_1A");                                        \
	if (!(MS(0x2B4) & 1)) {                                         \
		MF(0x2B0) += 6.0f;                                          \
		if (MF(0x2B0) >= maxv) {                                    \
			MF(0x2B0) = maxv;                                       \
			MS(0x2B4) |= 1;                                         \
			MB(0x42) = lvl;                                         \
			H2_LV(lvl, a148, a68)                                   \
		}                                                           \
	} else if (!(MS(0x2B4) & 0x10)) {                               \
		MF(0x2B0) += 1.0f;                                          \
		if (MF(0x2B0) >= midv) {                                    \
			MF(0x2B0) = midv;                                       \
			MS(0x2B4) |= 0x10;                                      \
		}                                                           \
	} else {                                                        \
		MF(0x2B0) -= 1.0f;                                          \
		if (MF(0x2B0) <= minv) {                                    \
			MF(0x2B0) = minv;                                       \
			MS(0x2B4) &= ~0x10;                                     \
		}                                                           \
	}

#define H2_CLR_PAPER()                                              \
	marioPaperOff();                                                \
	marioPaperLightOn();                                            \
	marioChgPose("M_S_1");                                          \
	mario->dispFlags &= ~0x4;                                       \
	mario->dispFlags &= ~0x8;                                       \
	mario->dispFlags &= ~0x10;

void mot_hammer2(void) {
	MarioWork* mario = marioGetPtr();
	s32 b, a;
	f32 c;
	HitEntry* hit;
	f32 ang2, ang;
	f32 nz, ny, nx, len, hz, hy, hx;
	f32 co, s;

	if (MI(0xC) & 1) {
		MI(0xC) &= ~1;
		mario->flags &= ~0xF0000;
		MS(0x2B4) = 0;
		MI(0x44) = 0;
		MI(0x2B8) = -1;
	}
	switch (MI(0x44)) {
	case 0:
		mario->flags |= 0x80;
		mario->dispFlags |= 4;
		MB(0x41) = 0;
		MB(0x42) = 0;
		mario->baseSpeed = 0.0f;
		mario->airTimer = 0;
		MI(0x44) = 1;
		MI(0x48) = 30;
		if (MB(0x42) == 3) {
			mario->wCamVal1 = 38.0f;
		} else if (MB(0x42) <= 2) {
			mario->wCamVal1 = 15.0f;
		} else {
			mario->wCamVal1 = 10.0f;
		}
		switch (pouchGetHammerLv()) {
		case 1:
			marioChgPose("M_H_3");
			break;
		case 2:
			marioChgPose("M_H_6");
			break;
		case 3:
			marioChgPose("M_H_9");
			break;
		}
		MI(0x200) = 0;
		MI(0x44) = 1;
		MI(0x48) = 1;
		break;
	case 1:
		if (--MI(0x48) > 0) {
			break;
		}
		if (180.0f == mario->displayDirectionTarget && MB(0x43) == 1) {
			mario->dispFlags |= 8;
		}
		if (0.0f == mario->displayDirectionTarget && MB(0x43) == 0) {
			mario->dispFlags |= 0x10;
		}
		marioPaperOn("p_kaiten_h");
		marioChgPaper("P_H_1C");
		marioPaperLightOff();
		MI(0x2B8) = psndSFXOn_3D(0x162, (Vec*)&mario->position.x);
		MF(0x2B0) = 0.0f;
		mario->poseTime = 0;
		animPoseSetLocalTime(mario->paperAnimGroupId[marioAnimeId()], MF(0x2B0));
		MI(0x44) = 10;
		MI(0x48) = 30;
	case 10:
		if (marioGetRub(0x200, &a, &b, &c) == 1) {
			MS(0x2B4) &= ~1;
			MB(0x41)++;
			if (MB(0x41) >= 20) {
				MB(0x41) = 20;
			}
		}
		if (MB(0x41) >= 4) {
			MF(0x2B0) += 6.0f;
			if (MF(0x2B0) >= 72.0f) {
				MF(0x2B0) = 72.0f;
			}
			MI(0x44) = 11;
			marioChgPaper("P_H_1B");
			MB(0x42) = 3;
			H2_LV(3, 0.4f, 1.7f)
		} else if (MB(0x41) >= 3) {
			H2_RAMP(54.0f, 54.0f, 42.0f, 3, 0.4f, 1.7f)
		} else if (MB(0x41) >= 2) {
			H2_RAMP(36.0f, 36.0f, 30.0f, 2, 0.3f, 1.6f)
		} else {
			H2_RAMP(18.0f, 24.0f, 18.0f, 1, 0.2f, 1.5f)
		}
		if (MS(0x2B4) & 0x1000) {
			MS(0x2B4) &= ~0x1000;
			if (!(MS(0x2B4) & 0x2000)) {
				MS(0x2B4) |= 0x2000;
				switch (pouchGetHammerLv()) {
				case 1:
					marioChgPose("M_H_3A");
					break;
				case 2:
					marioChgPose("M_H_6A");
					break;
				case 3:
					marioChgPose("M_H_9A");
					break;
				}
			}
		}
		if (strcmp(mario->paperAnimName, "P_H_1A") == 0) {
			animPoseSetLocalTime(mario->paperAnimGroupId[marioAnimeId()], MF(0x2B0) / 6.0f);
		}
	case 11:
		if (!(MH(0x246) & 0x200)) {
			if ((u32)MI(0x2B8) != 0xFFFFFFFFU) {
				psndSFXOff(MI(0x2B8));
				MI(0x2B8) = -1;
			}
			{
				MarioWork* m = marioGetPtr();
				m->camShiftTargetZ = 0.0f;
				*(f32*)((u8*)m + 0x158) = 0.01f;
			}
			switch (pouchGetHammerLv()) {
			case 1:
				marioChgPose("M_H_3B");
				break;
			case 2:
				marioChgPose("M_H_6B");
				break;
			case 3:
				marioChgPose("M_H_9B");
				break;
			}
			marioChgPaper("P_H_1C");
			MI(0x44) = 20;
			if (MB(0x42) == 3) {
				MI(0x48) = 0x30;
			} else if (MB(0x42) == 2) {
				MI(0x48) = 0x42;
			} else {
				MI(0x48) = 0x48;
			}
			MS(0x2A4) = 0;
			if (MB(0x42) == 3) {
				mario->wCamVal1 = 38.0f;
			} else if (MB(0x42) == 2) {
				mario->wCamVal1 = 22.0f;
			} else if (MB(0x42) <= 1) {
				mario->wCamVal1 = 15.0f;
			}
			((EffectEntry* (*)(f32, f32, f32, f32, BOOL, s32))effUltraHammerEntry)(mario->position.x, 20.0f + mario->position.y, mario->position.z, 1.0f, MB(0x43) != 0, MI(0x48));
		}
		break;
	case 20:
		ang = mario->displayDirection;
		MS(0x2A4) = 10;
		mario->dispFlags |= 0x100;
		ang2 = revise360(270.0f - mario->displayDirection);
		hit = hammerHitWall(ang2, &s, &co, &len, &hx, &hy, &hz, &nx, &ny, &nz);
		if (hit && (hitGetAttr(hit) & 0x800005)) {
			ang = ang; // FAKE: self-assignment keeps the branch; removing it (or the if) changes codegen
		}
		if (hit) {
			MI(0x1FC) = (s32)hit;
		}
		mario->displayDirection = mario->wCamVal1 * (MB(0x43) ? -1.0f : 1.0f) + mario->displayDirection;
		if ((s32)ang / 360 != (s32)mario->displayDirection / 360) {
			psndSFXOn_3D(0x163, (Vec*)&mario->position.x);
		}
		if (MS(0x2A4) == 1) {
			psndSFXOn_3D(0x163, (Vec*)&mario->position.x);
		}
		MI(0x48)--;
		if (MB(0x42) > 2 && MI(0x48) == 10) {
			H2_CLR_PAPER()
		}
		if (MI(0x48) > 0) {
			break;
		}
		if (MB(0x42) <= 2) {
			MI(0x48) = sysMsec2Frame(300);
		} else {
			mario->displayDirection = revise360(mario->displayDirection);
			marioAdjustMoveDir();
			MI(0x48) = 30;
		}
		MI(0x44) = 22;
	case 22:
		if (--MI(0x48) > 0) {
			break;
		}
		if (MB(0x42) <= 2) {
			H2_CLR_PAPER()
			mario->displayDirection = revise360(mario->displayDirection);
			marioAdjustMoveDir();
		}
		mario->dispFlags &= ~0x100;
		MI(0x44) = 23;
		MI(0x48) = 1;
	case 23:
		if (--MI(0x48) > 0) {
			break;
		}
		MI(0x48) = 1;
	case 24:
		if (--MI(0x48) > 0) {
			break;
		}
		mario->dispFlags &= ~0x4;
		mario->flags &= ~0x80;
		marioAdjustMoveDir();
		marioChgMotSub(0, 0);
		break;
	}
}


f32 marioGetAngleKaitenHammer(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->currMotionId != 0x13) {
		return -1.0f;
	}
	if ((s32)mario->currSubMotionId != 0x14) {
		return -2.0f;
	}
	return revise360(270.0f - mario->displayDirection);
}


void mot_ham2_post(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->dispFlags & 0x40000000) {
		marioPaperOff();
	}
	{
		MarioWork* m = marioGetPtr();
		m->camShiftTargetZ = 0.0f;
		*(f32*)((u8*)m + 0x158) = 0.01f;
	}
	marioPaperOff();
	marioPaperLightOn();
	mario->dispFlags &= ~0x100;
	mario->dispFlags &= ~0x8;
	mario->dispFlags &= ~0x10;
	mario->dispFlags &= ~0x4;
	mario->flags &= ~0x80;
	marioAdjustMoveDir();
}

HitEntry *hitEstimate(s32 *out)
{
  MarioWork *mario;
  HitCheckQuery q;
  Vec pos;
  HitEntry *hit;
  f32 s;
  f32 c;
  f32 cy;
  f32 a;
  Vec new_var;
  f32 h;
  s32 i;
  f32 k5 = 5.0f;
  mario = marioGetPtr();
  *out = 0;
  a = mario->displayDirection;
  {
    f32 off = (marioGetPtr()->dispFlags & 0x80000000) ? (-20.0f) : (0.0f);
    if ((a >= 90.0f) && (a <= 270.0f))
    {
      a = toMovedir2(180.0f, off);
    }
    else
    {
      a = toMovedir2(0.0f, off);
    }
  }
  sincosf(&s, &c, a);
  h = *((f32 *) (((u8 *) mario) + 0x1B8));
  cy = (f32) cos(3.14159265f);
  pos = mario->position;
  {
    Vec dir1 = {0.0f, 0.0f, 0.0f};
    pos.y = 4.0f + (mario->position.y + h);
    dir1.x = s;
    dir1.y = -cy;
    dir1.z = c;
    q.targetPos = pos;
    q.targetDir = dir1;
    q.targetDistance = 14.0f;
    hit = hitCheckVecFilter(&q, NULL);
    if (hit && (!(hitGetAttr(hit) & 0x800005)))
    {
      *out = 7;
      return hit;
    }
  }
  cy = (f32) cos(1.2217306f);
  {
    Vec dir2 = {0.0f, 0.0f, 0.0f};
    pos.x = (s * k5) + mario->position.x;
    pos.z = (c * k5) + mario->position.z;
    pos.y = mario->position.y + h;
    dir2.x = s;
    dir2.y = -cy;
    dir2.z = c;
    q.targetPos = pos;
    q.targetDir = dir2;
    q.targetDistance = 26.0f;
    hit = hitCheckVecFilter(&q, NULL);
    if (hit && (!(hitGetAttr(hit) & 0x800005)))
    {
      *out = ((q.hitPos.y - mario->position.y) > 30.0f) ? (4) : (5);
      return hit;
    }
  }
  cy = (f32) cos(0.78539816f);
  {
    Vec dir3 = {0.0f, 0.0f, 0.0f};
    pos.x = (s * k5) + mario->position.x;
    pos.z = (c * k5) + mario->position.z;
    pos.y = mario->position.y + h;
    dir3.x = s;
    dir3.y = -cy;
    dir3.z = c;
    q.targetPos = pos;
    q.targetDir = dir3;
    q.targetDistance = 30.0f;
    hit = hitCheckVecFilter(&q, NULL);
    if (hit && (!(hitGetAttr(hit) & 0x800005)))
    {
      *out = 5;
      return hit;
    }
  }
  cy = (f32) cos(0.0f);
  {
    Vec dir4 = {0.0f, 0.0f, 0.0f};
    dir4.y = -cy;
    new_var = dir4; // FAKE: Vec copy through a temp; Vec dir4b = dir4 differs
    {
      Vec dir4b = new_var;
      for (i = 0; i < 2; i++)
      {
        f32 m;
        f32 d;
        if (i == 0)
        {
          d = 36.0f;
          m = 20.0f;
        }
        else
        {
          d = 34.0f;
          if (mario->dispFlags & 0x80000000)
          {
            m = 37.0f;
          }
          else
          {
            m = d;
          }
        }
        pos.x = (s * m) + mario->position.x;
        pos.z = (c * m) + mario->position.z;
        pos.y = mario->position.y + h;
        q.targetPos = pos;
        q.targetDir = dir4b;
        q.targetDistance = d;
        hit = hitCheckVecFilter(&q, NULL);
        if (hit && (!(hitGetAttr(hit) & 0x800005)))
        {
          *out = ((q.hitPos.y - mario->position.y) > 13.0f) ? (5) : (6);
          return hit;
        }
      }

    }
  }
  return hit;
}

static const char isS1_str[] = "MOBJ_Lv1Block";
static const char isB1_str[] = "MOBJ_Lv1BigBlock";
static const char isS2_str[] = "MOBJ_Lv2Block";
static const char isB2_str[] = "MOBJ_Lv2BigBlock";
static const char isS3_str[] = "MOBJ_Lv3Block";
static const char isB3_str[] = "MOBJ_Lv3BigBlock";

static HitEntry* hammerHitWall(f32 ang, f32* s, f32* co, f32* len, f32* hx, f32* hy, f32* hz, f32* nx, f32* ny, f32* nz) {
	MarioWork* m = marioGetPtr();
	sincosf(s, co, ang);
	*len = 2.0f * *(f32*)((u8*)m + 0x1B4);
	return hitCheckFilter(0, hx, hy, hz, len, nx, ny, nz, m->position.x, 0.5f * *(f32*)((u8*)m + 0x1B8) + m->position.y, m->position.z, *s, 0.0f, *co);
}
