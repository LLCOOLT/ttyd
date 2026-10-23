#include "version.h"
#include "dolphin/types.h"
#include "evt/evt_cmd.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_pouch.h"
#include "mario/mario_sbr.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

BOOL marioGetRub(s32 mask, s32* a, s32* b, s32* c);
void allPartyRideOff(void);
void marioClearJumpPara(void);
void marioVoiceGlareOn(void);
void marioVoiceGlareOff(void);
void marioPaperOff(void);

#define MW(m, off, T) (*(T*)((u8*)(m) + MWOFF(off)))
typedef struct MotJabaraWork {
	u32 flags;          // 0x00: 1 = swing input taken (swingMain); 0x10000 / 0x20000 / 0x40000 = one-shot charge-level sounds played
	f32 swingAccel;     // 0x04: added to the swing angle while the push timer runs (2.4 start, 0.1 walk)
	f32 swingDecel;     // 0x08: added once the push timer hits 0 (-0.4 start, -0.1 walk)
	f32 field_0xC;      // 0x0C: cleared at sub-motion 0x32
	f32 swingRotStep;   // 0x10: 0.18, swing tilt step
	s32 wobbleCount;    // 0x14: wobble direction changes, picks SFX 0x189..0x18B
	f32 wobbleDir;      // 0x18: +-0.6, last wobble direction
	s32 headBlockTimer; // 0x1C: frames with a ceiling overhead, > 5 s ends the spring
} MotJabaraWork;        // size 0x20


static inline void jabaraSetSpd(f32 a, f32 b, f32 c) {
	MarioWork* mp = marioGetPtr();
	mp->camShiftTargetZ = a;
	mp->camShiftRate.z = b;
	mp->field_68 = c;
	mp->field_6C = (Vec){0.0f, 40.0f, 0.0f};
}

static inline void jabaraResetPose(void) {
	MarioWork* m2 = marioGetPtr();
	m2->displayDirection = m2->mot.jabara.dir;
	m2->displayDirectionTarget = m2->mot.jabara.dir;
	m2->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
	m2->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
	m2->rot = (Vec){0.0f, 0.0f, 0.0f};
	m2->wPlayerCollisionBox.x = 20.0f;
	m2->wPlayerCollisionBox.y = 37.0f;
	marioAdjustMoveDir();
	m2->dispFlags &= ~0x4;
	m2->dispFlags &= ~0x100;
}

static inline void* jabaraHitFront(f32 ang) {
	f32 sn, cs, hx, hy, hz, dist, nx, ny, nz;
	MarioWork* mp = marioGetPtr();
	f32 px = mp->position.x;
	f32 py = 2.0f + (mp->position.y + mp->wPlayerCollisionBox.y);
	f32 pz = mp->position.z;
	dist = 0.5f * mp->wPlayerCollisionBox.x;
	sincosf(&sn, &cs, ang);
	return hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, px, py, pz, sn, 0.0f, cs);
}

USER_FUNC(evt_cam_shake);

static EVT_BEGIN(quake_evt)
	CALL(evt_cam_shake, 4, 0xF24A7A80, 0xF24A7A8F, 0xF0)
	RETURN
EVT_END()

s32 marioGetJabaraState(void) {
	s32 state = 7;
	MarioWork* mario = marioGetPtr();
	if ((u16)mario->currMotionId != 0x14) {
		state = 0;
	} else {
		s32 id = (s32)mario->currSubMotionId;
		if (id == 0x14) {
			state = 1;
		} else if (id >= 0x46 && id <= 0x47) {
			state = 2;
		} else if (id == 0x50) {
			state = 3;
		} else if (id >= 0x28 && id <= 0x2b) {
			state = 4;
		} else if (id >= 0x32 && id <= 0x34) {
			state = 5;
		} else if (id >= 0x1e && id <= 0x1f) {
			state = 6;
		}
	}
	return state;
}

BOOL marioPriCheckJabara(void) {
	MarioWork* mario = marioGetPtr();
	u32 flags = mario->flags;
	if ((flags & 0x80000000) || (flags & VERSION_PICK(0x100000, 0x2100000))) {
		mario->wMotionTimer = 0;
		return FALSE;
	}
	return pouchCheckItem(8) != 0;
}

static inline BOOL priChk(void) {
	MarioWork* mario = marioGetPtr();
	u32 flags = mario->flags;
	BOOL ret;
	if ((flags & 0x80000000) || (flags & VERSION_PICK(0x100000, 0x2100000))) {
		mario->wMotionTimer = 0;
		ret = FALSE;
	} else {
		if ((s32)pouchCheckItem(8) == 0) {
			ret = FALSE;
		} else {
			ret = TRUE;
		}
	}
	return ret;
}

BOOL marioChkJabara(void) {
	MarioWork* mario = marioGetPtr();
	s32 a, b, c;
	if (!priChk()) {
		return FALSE;
	}
	if (!(mario->buttonHold & 0x100)) {
		if (!(mario->buttonHold & 0x200)) {
			if (strcmp(mario->animName, "M_I_Y") == 0 && (u16)mario->currMotionId == 0) {
				marioChgPose("M_S_1");
				marioVoiceGlareOff();
			}
			mario->wMotionTimer = 0;
		}
		return FALSE;
	}
#ifdef VERSION_G8ME01
	if ((mario->trigFlags & 0x400000) && (u16)mario->currMotionId == 0 && !((u32)mario->dispFlags & 0x40000000) &&
	    mario->controlStickSensitivity) {
		marioChgPose("M_I_Y");
		marioVoiceGlareOn();
	}
#else
	mario->wMotionTimer++;
	if (mario->controlStickSensitivity && mario->wMotionTimer > 10 && (u16)mario->currMotionId == 0 &&
	    !((u32)mario->dispFlags & 0x40000000)) {
		marioChgPose("M_I_Y");
		marioVoiceGlareOn();
	}
	if (mario->wMotionTimer >= 0x32) {
		mario->wMotionTimer = 0x32;
		if ((u16)mario->currMotionId == 0 && !((u32)mario->dispFlags & 0x40000000)) {
			marioChgPose("M_I_Y");
			marioVoiceGlareOn();
		}
	}
#endif
	if (marioGetRub(0x100, &b, &a, &c) == FALSE) {
		return FALSE;
	} else {
		return a >= 1;
	}
}

static inline void jabaraHitPos(HitEntry* hit, Vec* v) {
	marioGetPtr();
	hitObjGetPos(hitGetName(hit), v);
}

static inline void jabaraLand(f32 y_, void* h_) {
	MarioWork* mp_ = marioGetPtr();
	mp_->airTimer = 0;
	mp_->jumpPeakAirTime = 0;
	mp_->hitobjStandOn = h_;
	mp_->hitobjJumpFrom = NULL;
	mp_->position.y = y_;
	mp_->flags &= ~0xF0000;
}

#define VC(m, off, src) MW(m, off, Vec) = src
#define M(off, T) MW(mario, off, T)
#define POS ((Vec*)((u8*)mario + 0x8c))
#define SFX(id) psndSFXOn_3D((const char*)(id), POS)
#define ANIM_STEP() animPoseSetLocalTime(mario->paperAnimGroupId[marioAnimeId()], (f32)(s32)mario->mot.jabara.animFrame)
#define JAB_TAIL(MOTSUB) \
	{ \
		jabaraResetPose(); \
		MOTSUB \
		if (marioGetPtr()->motStruct) { \
			__memFree(HEAP_DEFAULT, marioGetPtr()->motStruct); \
			marioGetPtr()->motStruct = NULL; \
		} \
	}
#define MOTSUB_ marioChgMotSub(0, 0);
#define JAB_LAND(HIT, Y) \
	marioPaperOff(); \
	jabaraLand((Y), (HIT)); \
	camFollowYOn(); \
	marioGetPtr(); \
	allPartyRideOff(); \
	JAB_TAIL(MOTSUB_)

void mario_land_kemuri(void);
void mot_slit_post(void);
void L_allPartyRideOn(void);
f32 marioChkOverheadJabara(s32* a, s32* b);
void marioChkOverhead(void);
void* marioSearchHead(Vec* p, f32* h, f32 r);
void* marioSearchHead_jabara(Vec* p, f32* a, f32* b, f32 r);
void* marioChkLandon2(f32* out, f32 y, f32 z);
void marioChgSmallJumpMotion(void);
void swingMain(void);
f32 marioGetFallSpd(void);
void* marioChkLandon(f32* outY, f32 y);
double sin(double);
double cos(double);
#pragma opt_common_subs off
void jabaraSwingStart(s32 s);
void jabaraSwingWalk(void);

void mot_jabara(void) {
	MarioWork* mario = marioGetPtr();
	Vec v74;
	Vec v68;
	Vec v5c;
	Vec v50;
	s32 sp4c;
	s32 sp48;
	s32 sp44;
	s32 sp40;
	f32 sp3c;
	s32 sp38;
	f32 sp34;
	f32 sp30;
	f32 sp2c;
	f32 rr;
	if (M(0xc, u32) & 1) {
		M(0xc, u32) &= ~1;
		mario->mot.word[0] = 0;
		mario->mot.word[1] = 0;
		mario->mot.jabara.floorY = 0;
		mario->mot.word[3] = 0;
		mario->mot.word[4] = 0;
		mario->mot.word[5] = 0;
		mario->mot.word[6] = 0;
		if (M(4, u32) & 0x1000000) {
			mot_slit_post();
		}
		M(0, u32) &= ~0xF0000;
		M(0x44, s32) = 0;
		marioGetPtr()->motStruct = __memAlloc(HEAP_DEFAULT, 0x20);
		memset(marioGetPtr()->motStruct, 0, 0x20);
	}
	M(0x1f4, s32) = 0;
	switch (M(0x44, s32)) {
	case 0:
		M(4, u32) |= 0x100;
		M(0x41, s8) = 1;
		M(0x42, s8) = 0;
		M(0x50, s16) = 0;
		M(0x52, s16) = 0;
		M(0x180, f32) = 0.0f;
		M(0x44, s32) = 10;
		marioChgPose("M_J_1A");
		marioPaperOn("p_jyabara");
		marioChgPaper("PM_J_1B");
		M(0x11c, Vec) = M(0x8c, Vec);
		marioChkGnd();
		if (M(0x2e, u16) != 0x14) {
			M(0x44, s32) = 0x64;
		}
		break;
	case 10:
		if (M(0x2e, u16) != 0x14) {
			M(0x44, s32) = 0x64;
			break;
		}
		L_allPartyRideOn();
		SFX(0x182);
		jabaraSetSpd(0.2f, 0.005f, 1.5f);
		M(0x48, s32) = 8;
		M(0x44, s32) = 11;
	case 11:
		if (--M(0x48, s32) <= 0) {
			M(0x44, s32) = 12;
			if (!(marioGetPtr()->motJabara->flags & 0x10000)) {
				marioGetPtr()->motJabara->flags |= 0x10000;
			}
		}
	case 12:
		sp3c = marioChkOverheadJabara(&sp40, &sp38);
		if (marioGetRub(0x100, &sp48, &sp4c, &sp44) == 1) {
			M(0x41, s8)++;
			if (M(0x41, s8) >= 0x14) {
				M(0x41, s8) = 0x14;
			}
		}
		if (M(0x41, s8) == 3) {
			if (!(marioGetPtr()->motJabara->flags & 0x40000)) {
				marioGetPtr()->motJabara->flags |= 0x40000;
				SFX(0x184);
			}
			marioChgPaper("PM_J_3B");
			M(0x42, s8) = 3;
			jabaraSetSpd(0.4f, 0.005f, 1.7f);
		} else if (M(0x41, s8) == 2) {
			if (!(marioGetPtr()->motJabara->flags & 0x20000)) {
				marioGetPtr()->motJabara->flags |= 0x20000;
				SFX(0x183);
			}
			marioChgPaper("PM_J_2B");
			M(0x42, s8) = 2;
			jabaraSetSpd(0.3f, 0.005f, 1.6f);
		}
		marioChkGnd();
		if (M(0x2e, u16) != 0x14) {
			M(0x44, s32) = 0x64;
			return;
		}
		if ((f32)M(0x16c, s32) > 480.0f || (f32)M(0x16c, s32) < 50.0f) {
			camFollowYOn();
		}
		if (M(0x90, f32) == M(0x114, f32)) {
			camFollowYOff();
		}
		{
			BOOL found = FALSE;
			v74 = M(0x8c, Vec);
			sp34 = 25.0f;
			if (marioSearchHead(&v74, &sp34, 200.0f)) {
				if (!(M(0x246, u16) & 0x100)) {
					marioGetPtr()->motJabara->headBlockTimer++;
					if (marioGetPtr()->motJabara->headBlockTimer > sysMsec2Frame(5000)) {
						found = TRUE;
					}
				}
				if (!found) {
					break;
				}
			}
			if (!found && (M(0x246, u16) & 0x100) && !(M(0x24c, u16) & 0x100)) {
				break;
			}
		}
		{
			MarioWork* mp = marioGetPtr();
			mp->camShiftTargetZ = 0.0f;
			mp->camShiftRate.z = 0.01f;
		}
		camFollowYOff();
		marioChgPose("M_J_5A");
		marioChgPaper("PM_J_1C");
		SFX(0x20185);
		SFX(0x200b5);
		if (M(0x42, s8) == 3) {
			M(0x7c, f32) = 10.45f;
			M(0x80, f32) = 0.278f;
			M(0x84, f32) = -0.031f;
			M(0x88, f32) = 0.0f;
		} else if (M(0x42, s8) == 2) {
			M(0x7c, f32) = 8.0f;
			M(0x80, f32) = -0.84f;
			M(0x84, f32) = 0.08f;
			M(0x88, f32) = -0.015f;
		} else {
			M(0x7c, f32) = 4.3f;
			M(0x80, f32) = -0.84f;
			M(0x84, f32) = 0.08f;
			M(0x88, f32) = -0.015f;
		}
		if (M(0x42, s8) == 3) {
			mario_land_kemuri();
		}
		M(0x1e8, s32) = M(0x1e4, s32);
		M(0x1e4, s32) = 0;
		mario->mot.jabara.dir = M(0x1ac, f32);
		M(0x44, s32) = 0x14;
		break;
	case 0x14:
		marioMakeJumpPara();
		if (M(0x42, s8) == 3) {
			sp3c = marioChkOverheadJabara(&sp40, &sp38);
		} else {
			sp3c = ((f32 (*)(void))marioChkOverhead)();
		}
		if (M(0x1f4, void*) == NULL) {
			if (M(0x7c, f32) <= 0.0f) {
				M(0x44, s32) = 0x1e;
				marioSetPeakYpos();
			}
			M(0x90, f32) += M(0x7c, f32);
			break;
		}
		if ((f32)sp3c < M(0x120, f32)) {
			marioPaperOff(); { void* h = M(0x1e4, void*); jabaraLand(M(0x120, f32), h); } camFollowYOn(); marioGetPtr(); allPartyRideOff(); JAB_TAIL(MOTSUB_)
			return;
		}
		M(0x90, f32) = sp3c;
		if (M(0x42, s8) <= 2) {
			M(0x44, s32) = 0x1e;
			break;
		}
		if (hitGetAttr(M(0x1f4, HitEntry*)) & 0x40000) {
			mario->mot.jabara.dir = M(0x1ac, f32);
			M(0x1a8, f32) = M(0x1ac, f32);
			M(0x44, s32) = 0x46;
			M(0x48, s32) = 10;
			mario->mot.jabara.floorY = (s32)(sp3c + M(0x1b8, f32));
			{
				jabaraHitPos(M(0x1f4, HitEntry*), &v50);
				M(0x94, f32) = (s32)((100.0f * v50.z + 0.5f) / 100.0f);
				M(0x90, f32) = (f32)mario->mot.jabara.floorY - M(0x1b8, f32) - 3.5f;
				M(0xb4, f32) = 9.0f + M(0x1b8, f32);
			}
			marioPaperOff();
			camFollowYOn();
			M(4, u32) |= 4;
			marioChgPose("M_J_5A");
			SFX(0x186);
				jabaraSwingStart(sp40);
		} else {
			M(0x44, s32) = 0x28;
		}
		break;
	case 0x1e:
		marioChgPose("M_J_1C");
		marioChgPaper("PM_J_1D");
		marioSetFallPara();
		M(0x44, s32) = 0x1f;
	case 0x1f: {
		f32 spd = marioGetFallSpd();
		void* land;
		if (spd < -6.0f) {
			spd = -6.0f;
		}
		land = marioChkLandon(&sp3c, spd);
		if (land == NULL) {
			M(0x90, f32) += spd;
			break;
		}
		JAB_LAND(land, sp3c)
		return;
	}
	}
	switch (M(0x44, s32)) {
	case 0x28:
		if (strcmp(gp->currentMapName, "eki_02") == 0 && M(0x8c, f32) >= -450.0f && M(0x8c, f32) <= -190.0f) {
			M(0, u32) |= 0x400;
		}
		SFX(0x188);
		evtEntryType(quake_evt, 0, 0, 0);
		marioClearJumpPara();
		marioChgPose("M_J_5A");
		marioChgPaper("PM_J_1F");
		mario->mot.jabara.animFrame = 1;
		M(0x28, s16) = mario->mot.jabara.animFrame;
		M(0x9c, f32) = -8.0f;
		M(0x48, s32) = 0x32;
		M(0x44, s32) = 0x29;
		break;
	case 0x29:
		ANIM_STEP();
		mario->mot.jabara.animFrame++;
		if (mario->mot.jabara.animFrame >= 8) {
			mario->mot.jabara.animFrame = 8;
			M(0x1b8, f32) = 4.0f;
		}
		if (--M(0x48, s32) <= 0) {
			M(0x44, s32) = 0x2a;
		}
		break;
	case 0x2a:
		M(0x9c, f32) += 2.0f;
		if (M(0x9c, f32) >= 0.0f) {
			M(0x9c, f32) = 0.0f;
		}
		ANIM_STEP();
		if (++mario->mot.jabara.animFrame >= 0x10) {
			mario->mot.jabara.animFrame = 0x10;
			marioChgPaper("PM_J_1G");
			marioPaperLightOff();
			M(0x44, s32) = 0x2b;
			M(0x48, s32) = 0x18;
		}
		break;
	case 0x2b:
		if (--M(0x48, s32) > 0) {
			break;
		}
		marioChgPose("M_S_1");
		marioChgPaper("PM_J_1H");
		marioPaperLightOff();
		M(0x44, s32) = 0x32;
		mario->mot.jabara.animFrame = 0;
		marioGetPtr()->motJabara->field_0xC = 0.0f;
	case 0x32: {
		BOOL changed;
		f32 f28;
		ANIM_STEP();
		changed = FALSE;
		if (mario->mot.jabara.animFrame >= 0x23 && mario->mot.jabara.animFrame <= 0x62) {
			f28 = (180.0f == M(0x1ac, f32)) ? 0.6f : -0.6f;
			if (f28 != marioGetPtr()->motJabara->wobbleDir) {
				marioGetPtr()->motJabara->wobbleCount++;
				changed = TRUE;
			}
			marioGetPtr()->motJabara->wobbleDir = f28;
		} else {
			f28 = (180.0f == M(0x1ac, f32)) ? -0.6f : 0.6f;
			if (f28 != marioGetPtr()->motJabara->wobbleDir) {
				marioGetPtr()->motJabara->wobbleCount++;
				changed = TRUE;
			}
			marioGetPtr()->motJabara->wobbleDir = f28;
		}
		if (changed) {
			if (marioGetPtr()->motJabara->wobbleCount == 1) {
				SFX(0x189);
			} else if (marioGetPtr()->motJabara->wobbleCount == 2) {
				SFX(0x18a);
			} else if (marioGetPtr()->motJabara->wobbleCount == 3) {
				SFX(0x18b);
			}
		}
		M(0x98, f32) += f28 * (f32)cos(3.1415927f * M(0x198, f32) / 180.0f);
		M(0xa0, f32) += f28 * (f32)sin(3.1415927f * M(0x198, f32) / 180.0f);
		f28 = -1.0f * (f32)sin(1.5707963705062866);
		{
			void* land = marioChkLandon2(&sp3c, f28, M(0x9c, f32));
			if (land == NULL) {
				M(0x90, f32) += f28;
				if ((f32)M(0x16c, s32) > 480.0f) {
					camFollowYOn();
				}
				if (++mario->mot.jabara.animFrame > 0x78) {
					mario->mot.jabara.animFrame = 0;
				}
				if (M(0x248, u16) & 0x200) {
					M(0, u32) |= 0x80;
					M(0, u32) &= ~0x400;
					marioPaperOff();
					marioGetPtr();
					allPartyRideOff();
					JAB_TAIL(MOTSUB_)
					return;
				}
			} else {
				M(0x1e4, void*) = land;
				M(0x1e8, s32) = 0;
				M(0x90, f32) = sp3c;
				M(0x44, s32) = 0x34;
				mario->mot.jabara.animFrame = 0;
				M(0x48, s32) = 0x14;
			}
		}
		break;
	}
	case 0x34:
		ANIM_STEP();
		if (--M(0x48, s32) <= 0) {
			M(0x44, s32) = 0x3c;
		}
		break;
	}
	switch (M(0x44, s32)) {
	case 0x3c:
		allPartyRideOff();
		M(0x44, s32) = 0x3d;
		M(0x1e8, s32) = M(0x1e4, s32);
		M(0x1e4, s32) = 0;
		M(0x180, f32) = 0.0f;
		M(0, u32) &= ~0x400;
		JAB_TAIL()
		marioPaperOff();
		camFollowYOff();
		marioChgSmallJumpMotion();
		M(0x180, f32) = 0.0f;
		return;
	}
	{
	s32 st = M(0x44, s32);
	if (st >= 0x3c && st < 0x46) {
		return;
	}
	switch (st) {
	case 0x46:
		if (M(0x48, s32)-- <= 0) {
			marioChgPose("M_S_4");
			M(0x44, s32) = 0x47;
		}
	case 0x47:
		if (mario->mot.jabara.state == 5 || mario->mot.jabara.state == 0xf) {
			if (M(0x24e, s8) != 0 || M(0x24f, s8) != 0) {
				M(0x44, s32) = 0x50;
				M(0xbc, f32) = 0.0f;
				M(0xb0, f32) = 0.0f;
				mario->mot.jabara.state = 0;
				mario->mot.jabara.rotSpeed = 0.0f;
				M(0x90, f32) = (f32)mario->mot.jabara.floorY - M(0x1b8, f32) - 3.5f;
				M(0xb4, f32) = 9.0f + M(0x1b8, f32);
			}
		}
		if (mario->mot.jabara.state == 0 || mario->mot.jabara.state == 0xa) {
			M(0x44, s32) = 0x50;
			M(0xbc, f32) = 0.0f;
			M(0xb0, f32) = 0.0f;
			mario->mot.jabara.state = 0;
			mario->mot.jabara.rotSpeed = 0.0f;
			M(0x90, f32) = (f32)mario->mot.jabara.floorY - M(0x1b8, f32) - 3.5f;
			M(0xb4, f32) = 9.0f + M(0x1b8, f32);
		}
		break;
	case 0x50:
		if (M(0x248, u16) & 0x100) {
			M(0, u32) |= 0x80;
			M(0x180, f32) = 0.0f;
			M(0xbc, f32) = 0.0f;
			M(0x44, s32) = 0x5a;
		} else if (M(0x248, u16) & 0x200) {
			M(0, u32) |= 0x80;
			marioGetPtr();
			allPartyRideOff();
			JAB_TAIL(MOTSUB_)
			return;
		} else {
			ANIM_STEP();
			v68 = M(0x8c, Vec);
			sp2c = 10.0f + M(0x1b8, f32);
			rr = 1.0f;
			v68.x = v68.x + rr * (f32)sin(3.1415927f * (M(0x194, f32) + M(0x198, f32)) / 180.0f);
			v68.z = v68.z - rr * (f32)cos(3.1415927f * (M(0x194, f32) + M(0x198, f32)) / 180.0f);
			M(0x1f4, void*) = marioSearchHead_jabara(&v68, &sp2c, &sp30, 0.0f);
			if (M(0x1f4, void*) == NULL) {
				sp2c = 5.0f + M(0x1b8, f32);
				M(0x1f4, void*) = marioSearchHead(&v68, &sp2c, 0.0f);
			}
			if (M(0x190, f32)) {
				marioChgPose("M_W_6");
					jabaraSwingWalk();
				{
					BOOL hit = FALSE;
					f32 f31 = 1.0f;
					if (M(0x1f4, void*) != NULL && (hitGetAttr(M(0x1f4, HitEntry*)) & 0x40000)) {
						hit = TRUE;
					}
					if (hit) {
						if (jabaraHitFront(M(0x194, f32)) == NULL) {
							f31 = f31 * (f32)sin(3.1415927f * M(0x194, f32) / 180.0f);
							M(0x8c, f32) += f31;
							if (f31 > 0.0f) {
								if (M(0x1a8, f32) >= 90.0f && M(0x1a8, f32) <= 270.0f) {
									mario->mot.jabara.animFrame++;
									if (mario->mot.jabara.animFrame > 0x20) {
										mario->mot.jabara.animFrame = 0;
									}
								} else {
									mario->mot.jabara.animFrame--;
									if (mario->mot.jabara.animFrame < 0) {
										mario->mot.jabara.animFrame = 0x20;
									}
								}
							} else {
								if (M(0x1a8, f32) >= 90.0f && M(0x1a8, f32) <= 270.0f) {
									mario->mot.jabara.animFrame--;
									if (mario->mot.jabara.animFrame < 0) {
										mario->mot.jabara.animFrame = 0x20;
									}
								} else {
									mario->mot.jabara.animFrame++;
									if (mario->mot.jabara.animFrame > 0x20) {
										mario->mot.jabara.animFrame = 0;
									}
								}
							}
							if (mario->mot.jabara.animFrame == 0) {
								SFX(0x187);
							}
							if (mario->mot.jabara.animFrame == 0x10) {
								SFX(0x187);
							}
						}
					}
				}
				{
					v5c = M(0x8c, Vec);
					marioUpdateCamCollision(&v5c);
				}
			}
		}
		break;
	}
	}
	switch (M(0x44, s32)) {
	case 0x5a:
		marioChgPose("M_J_1B");
		M(0x44, s32) = 0x5b;
		M(4, u32) |= 4;
		marioAdjustMoveDir();
		M(0x7c, f32) = 4.0f;
		M(0x80, f32) = -0.5f;
		M(0x84, f32) = 0.0f;
		M(0x88, f32) = 0.0f;
		M(0x44, s32) = 0x5b;
	case 0x5b:
		M(0x90, f32) += M(0x7c, f32);
		marioMakeJumpPara();
		if (M(0x7c, f32) <= 0.0f) {
			marioChgMot(10);
			marioSetFallPara();
		}
		break;
	}
	if (M(0x44, s32) >= 0x46) {
		swingMain();
	}
}

#pragma opt_common_subs reset
BOOL jabaraNoHitChk(void) {
	MarioWork* mario = marioGetPtr();
	if ((u16)mario->currMotionId != 0x14) {
		return FALSE;
	}
	if ((s32)mario->currSubMotionId >= 0x28 && (s32)mario->currSubMotionId < 0x32) {
		return TRUE;
	}
	return FALSE;
}

void mot_jabara_post(void) {
	MarioWork* mario = marioGetPtr();
	MarioWork* m2;
	mario->flags &= ~0x400;
	m2 = marioGetPtr();
	m2->camShiftTargetZ = 0.0f;
	m2->camShiftRate.z = 0.01f;
	if ((u32)mario->dispFlags & 0x40000000) {
		marioPaperOff();
	}
	allPartyRideOff();
	jabaraResetPose();
	if (marioGetPtr()->motStruct) {
		__memFree(HEAP_DEFAULT, marioGetPtr()->motStruct);
		marioGetPtr()->motStruct = NULL;
	}
	switch ((u16)mario->currMotionId) {
	case 9:
	default:
		marioClearJumpPara();
		break;
	case 3: case 4: case 5: case 6: case 7: case 8:
	case 10: case 11:
		break;
	}
}

void jabaraSwingStart(s32 s) {
	MarioWork* mp = marioGetPtr();
	mp->mot.jabara.rotTimer = 4;
	mp->mot.jabara.rotSpeed = 24.0f;
	marioGetPtr()->motJabara->swingAccel = 2.4f;
	marioGetPtr()->motJabara->swingDecel = -0.4f;
	marioGetPtr()->motJabara->swingRotStep = 0.18f;
	if (s < 0) {
		mp->mot.jabara.state = 0xb;
	} else {
		mp->mot.jabara.state = 1;
	}
}


void jabaraSwingWalk(void) {
	MarioWork* mp = marioGetPtr();
	if (mp->mot.jabara.state != 0) {
	return;
	}
	mp->mot.jabara.state = 1;
	mp->mot.jabara.rotTimer = 10;
	mp->mot.jabara.rotSpeed = 0.0f;
	marioGetPtr()->motJabara->swingAccel = 0.1f;
	marioGetPtr()->motJabara->swingDecel = -0.1f;
	marioGetPtr()->motJabara->swingRotStep = 0.18f;
}

void swingMain(void) {
	MarioWork* m = marioGetPtr();
	if (marioGetPtr()->motStruct) {
		if ((s32)m->currSubMotionId < 0x5a && (m->buttonBuffer & 0x300) && !(marioGetPtr()->motJabara->flags & 1)) {
			m->mot.jabara.rotTimer = 0;
			marioGetPtr()->motJabara->flags |= 1;
		}
		switch (m->mot.jabara.state) {
		case 0:
			break;
		case 1:
			if (m->mot.jabara.rotTimer > 0) {
				m->mot.jabara.rotTimer--;
				m->mot.jabara.rotSpeed += marioGetPtr()->motJabara->swingAccel;
				if (m->mot.jabara.rotSpeed >= 40.0f) {
					m->mot.jabara.rotSpeed = 40.0f;
				}
			} else if (m->mot.jabara.rotTimer == 0) {
				m->mot.jabara.rotSpeed += marioGetPtr()->motJabara->swingDecel;
				if (m->mot.jabara.rotSpeed <= 0.0f) {
					m->mot.jabara.rotSpeed = 0.0f;
					m->mot.jabara.rotAccel = 0.1f;
					if (m->rot.x >= 180.0f) {
						m->mot.jabara.state = 2;
					} else {
						m->mot.jabara.state = 4;
					}
				}
			}
			if (marioGetPtr()->motJabara->flags & 1) {
				f32 old = m->rot.x;
				m->rot.x = revise360(old + m->mot.jabara.rotSpeed);
				if (m->rot.x < old) {
					m->mot.jabara.rotSpeed = 1.4f;
					m->mot.jabara.rotAccel = 0.1f;
					if (m->rot.x >= 180.0f) {
						m->mot.jabara.state = 2;
					} else {
						m->mot.jabara.state = 4;
					}
				}
			} else {
				m->rot.x = revise360(m->rot.x + m->mot.jabara.rotSpeed);
			}
			break;
		default:
			break;
		}
		switch (m->mot.jabara.state) {
		case 2:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed + m->mot.jabara.rotAccel;
			m->rot.x = revise360(m->rot.x + m->mot.jabara.rotSpeed);
			if (m->rot.x < 180.0f) {
				m->mot.jabara.state = 3;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel + marioGetPtr()->motJabara->swingRotStep;
			}
			break;
		case 3:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed - m->mot.jabara.rotAccel;
			if (m->mot.jabara.rotSpeed <= 0.0f) {
				m->mot.jabara.rotSpeed = 0.0f;
				m->mot.jabara.state = 4;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel - marioGetPtr()->motJabara->swingRotStep;
				if (__fabsf(m->rot.x) < 0.8f) {
					m->mot.jabara.state = 0;
				}
			}
			m->rot.x = revise360(m->rot.x + m->mot.jabara.rotSpeed);
			break;
		case 4:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed - m->mot.jabara.rotAccel;
			m->rot.x = revise360(m->rot.x + m->mot.jabara.rotSpeed);
			if (m->rot.x > 180.0f) {
				m->mot.jabara.state = 5;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel + marioGetPtr()->motJabara->swingRotStep;
			}
			break;
		case 5:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed + m->mot.jabara.rotAccel;
			if (m->mot.jabara.rotSpeed >= 0.0f) {
				m->mot.jabara.rotSpeed = 0.0f;
				m->mot.jabara.state = 2;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel - marioGetPtr()->motJabara->swingRotStep;
				if (__fabsf(m->rot.x) < 0.8f) {
					m->mot.jabara.state = 0;
				}
			}
			m->rot.x = revise360(m->rot.x + m->mot.jabara.rotSpeed);
			break;
		}
		switch (m->mot.jabara.state) {
		case 0xa:
			break;
		case 0xb:
			if (m->mot.jabara.rotTimer > 0) {
				m->mot.jabara.rotTimer--;
				m->mot.jabara.rotSpeed += marioGetPtr()->motJabara->swingAccel;
				if (m->mot.jabara.rotSpeed >= 40.0f) {
					m->mot.jabara.rotSpeed = 40.0f;
				}
			} else if (m->mot.jabara.rotTimer == 0) {
				m->mot.jabara.rotSpeed += marioGetPtr()->motJabara->swingDecel;
				if (m->mot.jabara.rotSpeed <= 0.0f) {
					m->mot.jabara.rotSpeed = 1.4f;
					m->mot.jabara.rotAccel = 0.1f;
					if (m->rot.x >= 180.0f) {
						m->mot.jabara.state = 0xc;
					} else {
						m->mot.jabara.state = 0xe;
					}
				}
			}
			if (marioGetPtr()->motJabara->flags & 1) {
				f32 old = m->rot.x;
				m->rot.x = revise360(old - m->mot.jabara.rotSpeed);
				if (m->rot.x > old) {
					m->mot.jabara.rotSpeed = 5.0f;
					m->mot.jabara.rotAccel = 0.1f;
					if (m->rot.x >= 180.0f) {
						m->mot.jabara.state = 0xc;
					} else {
						m->mot.jabara.state = 0xe;
					}
				}
			} else {
				m->rot.x = revise360(m->rot.x - m->mot.jabara.rotSpeed);
			}
			break;
		}
		switch (m->mot.jabara.state) {
		case 0xc:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed + m->mot.jabara.rotAccel;
			m->rot.x = revise360(m->rot.x - m->mot.jabara.rotSpeed);
			if (m->rot.x > 180.0f) {
				m->mot.jabara.state = 0xd;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel + marioGetPtr()->motJabara->swingRotStep;
			}
			break;
		case 0xd:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed - m->mot.jabara.rotAccel;
			if (m->mot.jabara.rotSpeed <= 0.0f) {
				m->mot.jabara.rotSpeed = 0.0f;
				m->mot.jabara.state = 0xe;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel - marioGetPtr()->motJabara->swingRotStep;
				if (__fabsf(m->rot.x) < 0.8f) {
					m->mot.jabara.state = 0;
				}
			}
			m->rot.x = revise360(m->rot.x - m->mot.jabara.rotSpeed);
			break;
		case 0xe:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed - m->mot.jabara.rotAccel;
			m->rot.x = revise360(m->rot.x - m->mot.jabara.rotSpeed);
			if (m->rot.x < 180.0f) {
				m->mot.jabara.state = 0xf;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel + marioGetPtr()->motJabara->swingRotStep;
			}
			break;
		case 0xf:
			m->mot.jabara.rotSpeed = m->mot.jabara.rotSpeed + m->mot.jabara.rotAccel;
			if (m->mot.jabara.rotSpeed >= 0.0f) {
				m->mot.jabara.rotSpeed = 0.0f;
				m->mot.jabara.state = 0xc;
				m->mot.jabara.rotAccel = m->mot.jabara.rotAccel - marioGetPtr()->motJabara->swingRotStep;
				if (__fabsf(m->rot.x) < 0.8f) {
					m->mot.jabara.state = 0xa;
				}
			}
			m->rot.x = revise360(m->rot.x - m->mot.jabara.rotSpeed);
			break;
		}
	}
}

void mot_grasp(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		mario->flags &= ~0xf0000;
	}
}
