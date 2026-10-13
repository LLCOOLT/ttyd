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

#define MW(m, off, T) (*(T*)((u8*)(m) + (off)))
#define MS(off, T) MW(marioGetPtr()->motStruct, off, T)


static inline void jabaraSetSpd(f32 a, f32 b, f32 c) {
	MarioWork* mp = marioGetPtr();
	MW(mp, 0x148, f32) = a;
	MW(mp, 0x158, f32) = b;
	MW(mp, 0x68, f32) = c;
	MW(mp, 0x6c, Vec) = (Vec){0.0f, 40.0f, 0.0f};
}

static inline void jabaraResetPose(void) {
	MarioWork* m2 = marioGetPtr();
	MW(m2, 0x1a8, f32) = MW(m2, 0x2a4, f32);
	MW(m2, 0x1ac, f32) = MW(m2, 0x2a4, f32);
	MW(m2, 0xb0, Vec) = (Vec){0.0f, 0.0f, 0.0f};
	MW(m2, 0x98, Vec) = (Vec){0.0f, 0.0f, 0.0f};
	MW(m2, 0xbc, Vec) = (Vec){0.0f, 0.0f, 0.0f};
	MW(m2, 0x1b4, f32) = 20.0f;
	MW(m2, 0x1b8, f32) = 37.0f;
	marioAdjustMoveDir();
	MW(m2, 4, u32) &= ~0x4;
	MW(m2, 4, u32) &= ~0x100;
}

static inline void* jabaraHitFront(f32 ang) {
	f32 sn, cs, hx, hy, hz, dist, nx, ny, nz;
	MarioWork* mp = marioGetPtr();
	f32 px = MW(mp, 0x8c, f32);
	f32 py = 2.0f + (MW(mp, 0x90, f32) + MW(mp, 0x1b8, f32));
	f32 pz = MW(mp, 0x94, f32);
	dist = 0.5f * MW(mp, 0x1b4, f32);
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
	if (MW(mario, 0x2e, u16) != 0x14) {
		state = 0;
	} else {
		s32 id = MW(mario, 0x44, s32);
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
	u32 flags = MW(mario, 0, u32);
	if ((flags & 0x80000000) || (flags & 0x100000)) {
		MW(mario, 0x40, u8) = 0;
		return FALSE;
	}
	return pouchCheckItem(8) != 0;
}

static inline BOOL priChk(void) {
	MarioWork* mario = marioGetPtr();
	u32 flags = MW(mario, 0, u32);
	BOOL ret;
	if ((flags & 0x80000000) || (flags & 0x100000)) {
		MW(mario, 0x40, u8) = 0;
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
	if (!(MW(mario, 0x246, u16) & 0x100)) {
		if (!(MW(mario, 0x246, u16) & 0x200)) {
			if (strcmp(MW(mario, 0x18, char*), "M_I_Y") == 0 && MW(mario, 0x2e, u16) == 0) {
				marioChgPose("M_S_1");
				marioVoiceGlareOff();
			}
			MW(mario, 0x40, u8) = 0;
		}
		return FALSE;
	}
	MW(mario, 0x40, s8)++;
	if (MW(mario, 0x190, f32) && MW(mario, 0x40, s8) > 10 && MW(mario, 0x2e, u16) == 0 &&
	    !(MW(mario, 4, u32) & 0x40000000)) {
		marioChgPose("M_I_Y");
		marioVoiceGlareOn();
	}
	if (MW(mario, 0x40, s8) >= 0x32) {
		MW(mario, 0x40, s8) = 0x32;
		if (MW(mario, 0x2e, u16) == 0 && !(MW(mario, 4, u32) & 0x40000000)) {
			marioChgPose("M_I_Y");
			marioVoiceGlareOn();
		}
	}
	if (marioGetRub(0x100, &b, &a, &c) == FALSE) {
		return FALSE;
	} else {
		return a >= 1;
	}
}

#define VC(m, off, src) MW(m, off, Vec) = src
#define M(off, T) MW(mario, off, T)
#define POS ((Vec*)((u8*)mario + 0x8c))
#define SFX(id) psndSFXOn_3D((const char*)(id), POS)
#define ANIM_STEP() animPoseSetLocalTime(mario->paperAnimGroupId[marioAnimeId()], (f32)(s32)M(0x2bb, s8))
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
	{ \
		void* h_ = (HIT); \
		f32 y_ = (Y); \
		MarioWork* mp_ = marioGetPtr(); \
		MW(mp_, 0x50, s16) = 0; \
		MW(mp_, 0x52, s16) = 0; \
		MW(mp_, 0x1e4, void*) = h_; \
		MW(mp_, 0x1e8, s32) = 0; \
		MW(mp_, 0x90, f32) = y_; \
		MW(mp_, 0, u32) &= ~0xF0000; \
	} \
	camFollowYOn(); \
	marioGetPtr(); \
	allPartyRideOff(); \
	JAB_TAIL(MOTSUB_)

void unk_80130374(void);
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
static void jabaraSwingStart(s32 s);
static void jabaraSwingWalk(void);

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
		M(0x2a0, s32) = 0;
		M(0x2a4, s32) = 0;
		M(0x2a8, s32) = 0;
		M(0x2ac, s32) = 0;
		M(0x2b0, s32) = 0;
		M(0x2b4, s32) = 0;
		M(0x2b8, s32) = 0;
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
			if (!(MS(0, u32) & 0x10000)) {
				MS(0, u32) |= 0x10000;
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
			if (!(MS(0, u32) & 0x40000)) {
				MS(0, u32) |= 0x40000;
				SFX(0x184);
			}
			marioChgPaper("PM_J_3B");
			M(0x42, s8) = 3;
			jabaraSetSpd(0.4f, 0.005f, 1.7f);
		} else if (M(0x41, s8) == 2) {
			if (!(MS(0, u32) & 0x20000)) {
				MS(0, u32) |= 0x20000;
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
					MS(0x1c, s32)++;
					if (MS(0x1c, s32) > sysMsec2Frame(5000)) {
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
			MW(mp, 0x148, f32) = 0.0f;
			MW(mp, 0x158, f32) = 0.01f;
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
			unk_80130374();
		}
		M(0x1e8, s32) = M(0x1e4, s32);
		M(0x1e4, s32) = 0;
		M(0x2a4, f32) = M(0x1ac, f32);
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
			JAB_LAND(M(0x1e4, void*), M(0x120, f32))
			return;
		}
		M(0x90, f32) = sp3c;
		if (M(0x42, s8) <= 2) {
			M(0x44, s32) = 0x1e;
			break;
		}
		if (hitGetAttr(M(0x1f4, HitEntry*)) & 0x40000) {
			M(0x2a4, f32) = M(0x1ac, f32);
			M(0x1a8, f32) = M(0x1ac, f32);
			M(0x44, s32) = 0x46;
			M(0x48, s32) = 10;
			M(0x2a8, s32) = (s32)(sp3c + M(0x1b8, f32));
			{
				HitEntry* hit = M(0x1f4, HitEntry*);
				marioGetPtr();
				hitObjGetPos(hitGetName(hit), &v50);
				M(0x94, f32) = (s32)((100.0f * v50.z + 0.5f) / 100.0f);
				M(0x90, f32) = (f32)M(0x2a8, s32) - M(0x1b8, f32) - 3.5f;
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
		M(0x2bb, s8) = 1;
		M(0x28, s16) = M(0x2bb, s8);
		M(0x9c, f32) = -8.0f;
		M(0x48, s32) = 0x32;
		M(0x44, s32) = 0x29;
		break;
	case 0x29:
		ANIM_STEP();
		M(0x2bb, s8)++;
		if (M(0x2bb, s8) >= 8) {
			M(0x2bb, s8) = 8;
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
		if (++M(0x2bb, s8) >= 0x10) {
			M(0x2bb, s8) = 0x10;
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
		M(0x2bb, s8) = 0;
		MS(0xc, f32) = 0.0f;
	case 0x32: {
		BOOL changed;
		f32 f28;
		ANIM_STEP();
		changed = FALSE;
		if (M(0x2bb, s8) >= 0x23 && M(0x2bb, s8) <= 0x62) {
			f28 = (180.0f == M(0x1ac, f32)) ? 0.6f : -0.6f;
			if (f28 != MS(0x18, f32)) {
				MS(0x14, s32)++;
				changed = TRUE;
			}
			MS(0x18, f32) = f28;
		} else {
			f28 = (180.0f == M(0x1ac, f32)) ? -0.6f : 0.6f;
			if (f28 != MS(0x18, f32)) {
				MS(0x14, s32)++;
				changed = TRUE;
			}
			MS(0x18, f32) = f28;
		}
		if (changed) {
			if (MS(0x14, s32) == 1) {
				SFX(0x189);
			} else if (MS(0x14, s32) == 2) {
				SFX(0x18a);
			} else if (MS(0x14, s32) == 3) {
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
				if (++M(0x2bb, s8) > 0x78) {
					M(0x2bb, s8) = 0;
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
				M(0x2bb, s8) = 0;
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
		if (M(0x2ba, s8) == 5 || M(0x2ba, s8) == 0xf) {
			if (M(0x24e, s8) != 0 || M(0x24f, s8) != 0) {
				M(0x44, s32) = 0x50;
				M(0xbc, f32) = 0.0f;
				M(0xb0, f32) = 0.0f;
				M(0x2ba, s8) = 0;
				M(0x2b0, f32) = 0.0f;
				M(0x90, f32) = (f32)M(0x2a8, s32) - M(0x1b8, f32) - 3.5f;
				M(0xb4, f32) = 9.0f + M(0x1b8, f32);
			}
		}
		if (M(0x2ba, s8) == 0 || M(0x2ba, s8) == 0xa) {
			M(0x44, s32) = 0x50;
			M(0xbc, f32) = 0.0f;
			M(0xb0, f32) = 0.0f;
			M(0x2ba, s8) = 0;
			M(0x2b0, f32) = 0.0f;
			M(0x90, f32) = (f32)M(0x2a8, s32) - M(0x1b8, f32) - 3.5f;
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
									M(0x2bb, s8)++;
									if (M(0x2bb, s8) > 0x20) {
										M(0x2bb, s8) = 0;
									}
								} else {
									M(0x2bb, s8)--;
									if (M(0x2bb, s8) < 0) {
										M(0x2bb, s8) = 0x20;
									}
								}
							} else {
								if (M(0x1a8, f32) >= 90.0f && M(0x1a8, f32) <= 270.0f) {
									M(0x2bb, s8)--;
									if (M(0x2bb, s8) < 0) {
										M(0x2bb, s8) = 0x20;
									}
								} else {
									M(0x2bb, s8)++;
									if (M(0x2bb, s8) > 0x20) {
										M(0x2bb, s8) = 0;
									}
								}
							}
							if (M(0x2bb, s8) == 0) {
								SFX(0x187);
							}
							if (M(0x2bb, s8) == 0x10) {
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
	if (MW(mario, 0x2e, u16) != 0x14) {
		return FALSE;
	}
	if (MW(mario, 0x44, s32) >= 0x28 && MW(mario, 0x44, s32) < 0x32) {
		return TRUE;
	}
	return FALSE;
}

void mot_jabara_post(void) {
	MarioWork* mario = marioGetPtr();
	MarioWork* m2;
	MW(mario, 0, u32) &= ~0x400;
	m2 = marioGetPtr();
	MW(m2, 0x148, f32) = 0.0f;
	MW(m2, 0x158, f32) = 0.01f;
	if (MW(mario, 4, u32) & 0x40000000) {
		marioPaperOff();
	}
	allPartyRideOff();
	jabaraResetPose();
	if (marioGetPtr()->motStruct) {
		__memFree(HEAP_DEFAULT, marioGetPtr()->motStruct);
		marioGetPtr()->motStruct = NULL;
	}
	switch (MW(mario, 0x2e, u16)) {
	case 9:
	default:
		marioClearJumpPara();
		break;
	case 3: case 4: case 5: case 6: case 7: case 8:
	case 10: case 11:
		break;
	}
}

static void jabaraSwingStart(s32 s) {
	MarioWork* mp = marioGetPtr();
	MW(mp, 0x2b8, s16) = 4;
	MW(mp, 0x2b0, f32) = 24.0f;
	MS(4, f32) = 2.4f;
	MS(8, f32) = -0.4f;
	MS(0x10, f32) = 0.18f;
	if (s < 0) {
		MW(mp, 0x2ba, s8) = 0xb;
	} else {
		MW(mp, 0x2ba, s8) = 1;
	}
}

static void jabaraSwingWalk(void) {
	MarioWork* mp = marioGetPtr();
	if (MW(mp, 0x2ba, s8) == 0) {
		MW(mp, 0x2ba, s8) = 1;
		MW(mp, 0x2b8, s16) = 10;
		MW(mp, 0x2b0, f32) = 0.0f;
		MS(4, f32) = 0.1f;
		MS(8, f32) = -0.1f;
		MS(0x10, f32) = 0.18f;
	}
}

void swingMain(void) {
	MarioWork* m = marioGetPtr();
	if (marioGetPtr()->motStruct) {
		if (MW(m, 0x44, s32) < 0x5a && (MW(m, 0x248, u16) & 0x300) && !(MS(0, u32) & 1)) {
			MW(m, 0x2b8, s16) = 0;
			MS(0, u32) |= 1;
		}
		switch (MW(m, 0x2ba, s8)) {
		case 0:
			break;
		case 1:
			if (MW(m, 0x2b8, s16) > 0) {
				MW(m, 0x2b8, s16)--;
				MW(m, 0x2b0, f32) += MS(4, f32);
				if (MW(m, 0x2b0, f32) >= 40.0f) {
					MW(m, 0x2b0, f32) = 40.0f;
				}
			} else if (MW(m, 0x2b8, s16) == 0) {
				MW(m, 0x2b0, f32) += MS(8, f32);
				if (MW(m, 0x2b0, f32) <= 0.0f) {
					MW(m, 0x2b0, f32) = 0.0f;
					MW(m, 0x2b4, f32) = 0.1f;
					if (MW(m, 0xbc, f32) >= 180.0f) {
						MW(m, 0x2ba, s8) = 2;
					} else {
						MW(m, 0x2ba, s8) = 4;
					}
				}
			}
			if (MS(0, u32) & 1) {
				f32 old = MW(m, 0xbc, f32);
				MW(m, 0xbc, f32) = revise360(old + MW(m, 0x2b0, f32));
				if (MW(m, 0xbc, f32) < old) {
					MW(m, 0x2b0, f32) = 1.4f;
					MW(m, 0x2b4, f32) = 0.1f;
					if (MW(m, 0xbc, f32) >= 180.0f) {
						MW(m, 0x2ba, s8) = 2;
					} else {
						MW(m, 0x2ba, s8) = 4;
					}
				}
			} else {
				MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) + MW(m, 0x2b0, f32));
			}
			break;
		default:
			break;
		}
		switch (MW(m, 0x2ba, s8)) {
		case 2:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) + MW(m, 0x2b4, f32);
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) + MW(m, 0x2b0, f32));
			if (MW(m, 0xbc, f32) < 180.0f) {
				MW(m, 0x2ba, s8) = 3;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) + MS(0x10, f32);
			}
			break;
		case 3:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) - MW(m, 0x2b4, f32);
			if (MW(m, 0x2b0, f32) <= 0.0f) {
				MW(m, 0x2b0, f32) = 0.0f;
				MW(m, 0x2ba, s8) = 4;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) - MS(0x10, f32);
				if (__fabsf(MW(m, 0xbc, f32)) < 0.8f) {
					MW(m, 0x2ba, s8) = 0;
				}
			}
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) + MW(m, 0x2b0, f32));
			break;
		case 4:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) - MW(m, 0x2b4, f32);
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) + MW(m, 0x2b0, f32));
			if (MW(m, 0xbc, f32) > 180.0f) {
				MW(m, 0x2ba, s8) = 5;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) + MS(0x10, f32);
			}
			break;
		case 5:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) + MW(m, 0x2b4, f32);
			if (MW(m, 0x2b0, f32) >= 0.0f) {
				MW(m, 0x2b0, f32) = 0.0f;
				MW(m, 0x2ba, s8) = 2;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) - MS(0x10, f32);
				if (__fabsf(MW(m, 0xbc, f32)) < 0.8f) {
					MW(m, 0x2ba, s8) = 0;
				}
			}
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) + MW(m, 0x2b0, f32));
			break;
		}
		switch (MW(m, 0x2ba, s8)) {
		case 0xa:
			break;
		case 0xb:
			if (MW(m, 0x2b8, s16) > 0) {
				MW(m, 0x2b8, s16)--;
				MW(m, 0x2b0, f32) += MS(4, f32);
				if (MW(m, 0x2b0, f32) >= 40.0f) {
					MW(m, 0x2b0, f32) = 40.0f;
				}
			} else if (MW(m, 0x2b8, s16) == 0) {
				MW(m, 0x2b0, f32) += MS(8, f32);
				if (MW(m, 0x2b0, f32) <= 0.0f) {
					MW(m, 0x2b0, f32) = 1.4f;
					MW(m, 0x2b4, f32) = 0.1f;
					if (MW(m, 0xbc, f32) >= 180.0f) {
						MW(m, 0x2ba, s8) = 0xc;
					} else {
						MW(m, 0x2ba, s8) = 0xe;
					}
				}
			}
			if (MS(0, u32) & 1) {
				f32 old = MW(m, 0xbc, f32);
				MW(m, 0xbc, f32) = revise360(old - MW(m, 0x2b0, f32));
				if (MW(m, 0xbc, f32) > old) {
					MW(m, 0x2b0, f32) = 5.0f;
					MW(m, 0x2b4, f32) = 0.1f;
					if (MW(m, 0xbc, f32) >= 180.0f) {
						MW(m, 0x2ba, s8) = 0xc;
					} else {
						MW(m, 0x2ba, s8) = 0xe;
					}
				}
			} else {
				MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) - MW(m, 0x2b0, f32));
			}
			break;
		}
		switch (MW(m, 0x2ba, s8)) {
		case 0xc:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) + MW(m, 0x2b4, f32);
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) - MW(m, 0x2b0, f32));
			if (MW(m, 0xbc, f32) > 180.0f) {
				MW(m, 0x2ba, s8) = 0xd;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) + MS(0x10, f32);
			}
			break;
		case 0xd:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) - MW(m, 0x2b4, f32);
			if (MW(m, 0x2b0, f32) <= 0.0f) {
				MW(m, 0x2b0, f32) = 0.0f;
				MW(m, 0x2ba, s8) = 0xe;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) - MS(0x10, f32);
				if (__fabsf(MW(m, 0xbc, f32)) < 0.8f) {
					MW(m, 0x2ba, s8) = 0;
				}
			}
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) - MW(m, 0x2b0, f32));
			break;
		case 0xe:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) - MW(m, 0x2b4, f32);
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) - MW(m, 0x2b0, f32));
			if (MW(m, 0xbc, f32) < 180.0f) {
				MW(m, 0x2ba, s8) = 0xf;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) + MS(0x10, f32);
			}
			break;
		case 0xf:
			MW(m, 0x2b0, f32) = MW(m, 0x2b0, f32) + MW(m, 0x2b4, f32);
			if (MW(m, 0x2b0, f32) >= 0.0f) {
				MW(m, 0x2b0, f32) = 0.0f;
				MW(m, 0x2ba, s8) = 0xc;
				MW(m, 0x2b4, f32) = MW(m, 0x2b4, f32) - MS(0x10, f32);
				if (__fabsf(MW(m, 0xbc, f32)) < 0.8f) {
					MW(m, 0x2ba, s8) = 0xa;
				}
			}
			MW(m, 0xbc, f32) = revise360(MW(m, 0xbc, f32) - MW(m, 0x2b0, f32));
			break;
		}
	}
}

void mot_grasp(void) {
	MarioWork* mario = marioGetPtr();
	if (MW(mario, 0xc, u32) & 1) {
		MW(mario, 0xc, u32) &= ~1;
		MW(mario, 0, u32) &= ~0xf0000;
	}
}
