#include "dolphin/types.h"
#include "evt/evt_cmd.h"
#include "evt/evt_snd.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_sbr.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

void marioClearJumpPara(void);
void marioPaperOff(void);
void marioUpdateCamCollision(Vec pos);
void allPartyRideOff2(void);
void allPartyRidePlane(void);
void marioSetSplash(s32 kind, Vec* pos);
void set_damage_root_ypos(f32 y);
HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz);
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
HitEntry* marioSearchGround(f32* a, f32* b, f32* c, f32 d, f32 e);
f32 revise360(f32 angle);
s32 marioKeyOffChk(void);
void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames);
s32 marioAnimeId(void);
s32 sysMsec2Frame(s32 msec);
void marioMakeJumpPara(void);
void marioSetFallPara(void);
void marioPreJump(void);
void marioChkOverhead(void);

#define MW(m, off, T) (*(T*)((u8*)(m) + (off)))
#define MS(off, T) MW(marioGetPtr()->motStruct, off, T)
#define MD(off, T) MW(mp->motStruct, off, T)
#define SFX3D(id, pos) ((s32 (*)(s32, Vec*))psndSFXOn_3D)(id, pos)

BOOL chkCollision(f32* outY);
static void flyMain(void);


f32 planeData[41] = {
	5.0f, -0.02f, -0.03f, 25.0f, -45.0f, 0.4f, 1.0f, 0.1f, -0.1f, 1.5f,
	0.2f, 0.05f, 3.4f, 1.0f, 0.025f, 0.045f, 0.8f, 1.5f, -0.3f, -5.0f,
	3.9f, -0.112f, 0.118f, 0.5f, 0.4f, -8.0f, -2.0f, -4.0f, -2.0f, 0.2f,
	0.0f, 1.2f, 1.0f, 15.0f, -30.0f, 12.0f, 0.0f, 30.0f, -30.0f, 6.0f,
	28.0f,
};

EVT_BEGIN(sound_evt)
CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_AIRPLANE1"), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_AIRPLANE1"), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_AIRPLANE1"), LW(0), LW(1), LW(2), 0)
WAIT_FRAMES(12)
CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_AIRPLANE1"), LW(0), LW(1), LW(2), 0)
RETURN
EVT_END()

static inline void planeSetSpd(f32 a, f32 b, f32 c) {
	MarioWork* m = marioGetPtr();
	MW(m, 0x148, f32) = a;
	MW(m, 0x158, f32) = b;
	MW(m, 0x68, f32) = c;
	MW(m, 0x6c, Vec) = (Vec){0.0f, 40.0f, 0.0f};
}

const char* paper_plane[4] = {"p_hikohki", "p_hikohki_g", "p_hikohki_y", "p_hikohki_v"};

static inline void planeSfxOff(void) {
	MarioWork* m = marioGetPtr();
	if (m->motStruct != NULL && MW(m->motStruct, 0x28, u32) != 0xFFFFFFFF) {
		psndSFXOff(MW(m->motStruct, 0x28, s32));
		MW(m->motStruct, 0x28, s32) = -1;
	}
}

static inline void planeReset(void) {
	MarioWork* m = marioGetPtr();
	MW(m, 0x1b4, f32) = 20.0f;
	MW(m, 0x1b8, f32) = 37.0f;
	MW(m, 0xbc, Vec) = (Vec){0.0f, 0.0f, 0.0f};
	MW(m, 0xb0, Vec) = (Vec){0.0f, 0.0f, 0.0f};
	MW(m, 0x98, Vec) = (Vec){0.0f, 0.0f, 0.0f};
	marioPaperOff();
	marioChgPaper(NULL);
	MW(m, 4, u32) &= ~0x8;
	MW(m, 0, u32) |= 0x80;
	marioAdjustMoveDir();
	MW(m, 4, u32) &= ~0x100;
}

static inline BOOL planeCancel(void) {
	MarioWork* m = marioGetPtr();
	if (MW(m, 0x2e, u16) != 0x18) {
		return FALSE;
	}
	if ((s32)m->currSubMotionId >= 12 && (s32)m->currSubMotionId < 20) {
		m->currSubMotionId = 50;
		MW(m, 0x2ac, f32) = MW(m, 0x90, f32);
		return TRUE;
	}
	return FALSE;
}

s32 marioPlaneGetFlyingDir(void) {
	MarioWork* mp = marioGetPtr();
	s32 ret;
	if (MW(mp, 0x2e, u16) != 0x18) {
		return 0;
	}
	ret = -1;
	if (MD(0, u32) & 1) {
		ret = 1;
	}
	return ret;
}

s32 marioGetPlaneStatus(void) {
	MarioWork* mp = marioGetPtr();
	if (MW(mp, 0x2e, u16) != 0x18) {
		return 0;
	}
	if ((s32)mp->currSubMotionId >= 12 && (s32)mp->currSubMotionId < 20) {
		return 2;
	}
	return 1;
}

BOOL mario_plane_cancel(void) {
	MarioWork* mp = marioGetPtr();
	if (MW(mp, 0x2e, u16) != 0x18) {
		return FALSE;
	}
	if ((s32)mp->currSubMotionId >= 12 && (s32)mp->currSubMotionId < 20) {
		mp->currSubMotionId = 50;
		MW(mp, 0x2ac, f32) = MW(mp, 0x90, f32);
		return TRUE;
	}
	return FALSE;
}

void marioForcePlaneAnime(void) {
	MarioWork* mp = marioGetPtr();
	marioPaperOff();
	marioChgPaper(NULL);
	marioPaperOn(paper_plane[marioGetColor()]);
	marioChgPaper("PM_P_1B");
	marioChgPose("M_Z_1");
	MW(mp, 4, u32) |= 8;
}

#define DIRF(mp) ((MD(0, u32) & 1) ? 1.0f : -1.0f)

static inline void planeRoll1(MarioWork* mp, f32 rate, f32 max) {
	f32 tg = max * DIRF(mp);
	MW(mp, 0x2a4, f32) += rate * (tg - MW(mp, 0x2a4, f32));
}

static inline void planeRoll2(MarioWork* mp, f32 rate, f32 max) {
	MW(mp, 0x2a4, f32) += rate * (max * DIRF(mp) - MW(mp, 0x2a4, f32));
}

void mot_plane(void) {
	MarioWork* mp;
	BOOL done;
	void* evt;
	f32 y, b, c;

	mp = marioGetPtr();
	if (mp->trigFlags & 1) {
		mp->trigFlags &= ~1;
		mp->motStruct = __memAlloc(HEAP_DEFAULT, 0x48);
		memset(mp->motStruct, 0, 0x48);
		MS(0x28, s32) = -1;
		mp->currSubMotionId = 0;
	}
	switch (mp->currSubMotionId) {
	case 0:
		planeSetSpd(0.4f, 0.01f, 2.0f);
		marioPreJump();
		marioChgPose("M_J_1B");
		MW(mp, 4, u32) |= 0x100;
		mp->currSubMotionId = 1;
		MW(mp, 0x50, s16) = 0;
		MW(mp, 0x180, f32) = 0.0f;
		MW(mp, 0x2a4, f32) = 0.0f;
		MW(mp, 0x2a8, f32) = MW(mp, 0x90, f32);
		MW(mp, 0x2ac, f32) = 0.0f;
		MD(0, u32) = (hitGetAttr(MW(mp, 0x1e8, HitEntry*)) >> 4) & 1;
		SFX3D(0x17d, &mp->position);
		SFX3D(0xaf, &mp->position);
	case 1:
		marioMakeJumpPara();
		planeRoll1(mp, 0.125f, 30.0f);
		done = FALSE;
		MW(mp, 0x1a8, f32) += MW(mp, 0x2a4, f32);
		if (MD(0, u32) & 1) {
			if (MW(mp, 0x1a8, f32) >= 630.0f) {
				done = TRUE;
			}
		} else {
			if (MW(mp, 0x1a8, f32) <= -630.0f) {
				done = TRUE;
			}
		}
		if (done) {
			mp->currSubMotionId = 2;
			MW(mp, 0x48, s32) = 20;
			marioPaperOn(paper_plane[marioGetColor()]);
			marioChgPaper("PM_P_1A");
			marioChgPose("M_Z_1");
			MW(mp, 4, u32) |= 8;
			animPoseSetLocalTime(MW(mp, 0x23c, s32), 0.0f);
			animPoseSetLocalTime(MW(mp, 0x228 + marioAnimeId() * 4, s32), 0.0f);
			evt = evtEntry(sound_evt, 0, 0);
			MW(evt, 0x9c, s32) = (s32)(1024.0f * MW(mp, 0x8c, f32)) + -230000000;
			MW(evt, 0xa0, s32) = (s32)(1024.0f * MW(mp, 0x90, f32)) + -230000000;
			MW(evt, 0xa4, s32) = (s32)(1024.0f * MW(mp, 0x94, f32)) + -230000000;
		}
		if (MW(mp, 0x7c, f32) > 0.0f) {
			MW(mp, 0x90, f32) += MW(mp, 0x7c, f32);
		}
		break;
	case 2:
		animPoseSetLocalTime(MW(mp, 0x23c, s32), 0.0f);
		animPoseSetLocalTime(MW(mp, 0x228 + marioAnimeId() * 4, s32), 0.0f);
		planeRoll1(mp, 0.125f, 30.0f);
		done = FALSE;
		MW(mp, 0x1a8, f32) += MW(mp, 0x2a4, f32);
		if (MD(0, u32) & 1) {
			if (MW(mp, 0x1a8, f32) >= 1260.0f) {
				MW(mp, 0x1a8, f32) = 1260.0f;
				done = TRUE;
			}
		} else {
			if (MW(mp, 0x1a8, f32) <= -1080.0f) {
				MW(mp, 0x1a8, f32) = -1080.0f;
				done = TRUE;
			}
		}
		if (done) {
			MW(mp, 0x48, s32) = 60;
			mp->currSubMotionId = 3;
		}
		break;
	case 3:
		if (--MW(mp, 0x48, s32) > 0) {
			if (MW(mp, 0x48, s32) == 40) {
				allPartyRidePlane();
			}
			break;
		}
		marioChgPaper("PM_P_1B");
		MD(8, f32) = (MD(0, u32) & 1) ? 90.0f : 270.0f;
		MW(mp, 0x2a4, f32) = 0.0f;
		MD(4, f32) = 0.0f;
		MD(0xc, f32) = 0.0f;
		MD(0x14, f32) = 0.0f;
		MD(0x10, f32) = 0.0f;
		if (MD(0, u32) & 1) {
			MW(mp, 0xb0, f32) = planeData[33];
			MW(mp, 0x98, f32) = planeData[34];
		} else {
			MW(mp, 0xb0, f32) = planeData[35];
			MW(mp, 0x98, f32) = planeData[36];
		}
		MW(mp, 0x1b4, f32) = 20.0f;
		MW(mp, 0x1b8, f32) = 12.333333f;
		MW(mp, 0x180, f32) = __fabsf(0.02f * MW(mp, 0x24e, s8));
		mp->currSubMotionId = 12;
		MW(mp, 0x180, f32) = 1.0f;
		MD(0x10, f32) = 2.0f;
		{
			MarioWork* m = marioGetPtr();
			MW(m, 0x148, f32) = 0.0f;
			MW(m, 0x158, f32) = 0.004f;
		}
		MW(mp, 0x138, f32) = 70.0f * ((MD(0, u32) & 1) ? -1.0f : 1.0f);
		MW(mp, 0x140, f32) = -70.0f;
		break;
	}
	if (MW(mp, 0x90, f32) < 100.0f) {
		MW(mp, 0x140, f32) = __fabsf(planeData[38]);
	}
	flyMain();
	if (marioKeyOffChk() && !(mp->trigFlags & 4)) {
		if (planeCancel()) {
			return;
		}
	}
	if ((s32)mp->currSubMotionId == 20 || (s32)mp->currSubMotionId == 30) {
		camFollowYOff();
		MW(mp, 0x140, f32) = 0.0f;
		MW(mp, 0x138, f32) = 0.0f;
		marioClearJumpPara();
		MW(mp, 0x180, f32) = 0.0f;
		planeSfxOff();
		planeReset();
		allPartyRideOff2();
		if ((s32)mp->currSubMotionId == 20) {
			marioChgMot(3);
		} else if ((s32)mp->currSubMotionId == 30) {
			marioChgMot(0);
		}
	}
	switch (mp->currSubMotionId) {
	case 40:
		camFollowYOff();
		planeSfxOff();
		MW(mp, 0x48, s32) = sysMsec2Frame(520);
		mp->currSubMotionId = 41;
		break;
	case 41:
		if (--MW(mp, 0x48, s32) > 0) {
			break;
		}
		planeReset();
		marioChgPose("M_J_1C\0");
		MW(mp, 0x90, f32) = 1.0f + (MW(mp, 0x2ac, f32) - 37.0f);
		MW(mp, 0x180, f32) = 0.0f;
		marioSetFallPara();
		MW(mp, 0x7c, f32) = 0.0f;
		MW(mp, 0x80, f32) *= 0.5f;
		MW(mp, 0x84, f32) *= 0.5f;
		MW(mp, 0x88, f32) *= 0.5f;
		mp->currSubMotionId = 90;
		MW(mp, 4, u32) |= 0x100;
		allPartyRideOff2();
		break;
	case 60:
		camFollowYOff();
		MW(mp, 0x48, s32) = sysMsec2Frame(520);
		mp->currSubMotionId = 61;
	case 61:
		if (MW(mp, 0x180, f32) > 1.0f) {
			mp->currSubMotionId = 14;
			break;
		}
		if (--MW(mp, 0x48, s32) > 0) {
			break;
		}
		mp->currSubMotionId = 52;
		break;
	case 50:
		camFollowYOff();
		MW(mp, 0x48, s32) = sysMsec2Frame(520);
		mp->currSubMotionId = 52;
		break;
	case 51:
		camFollowYOff();
		MW(mp, 0x48, s32) = sysMsec2Frame(100);
		mp->currSubMotionId = 52;
		break;
	case 52:
		if (--MW(mp, 0x48, s32) > 0) {
			break;
		}
	case 53:
		planeSfxOff();
		planeReset();
		MW(mp, 4, u32) &= ~0x100;
		MW(mp, 0x180, f32) = 0.0f;
		MW(mp, 0x2a4, f32) = 0.0f;
		MW(mp, 0x90, f32) = 1.0f + MW(mp, 0x2ac, f32);
		marioPreJump();
		MW(mp, 0x7c, f32) *= 0.5f;
		marioChgPose("M_J_1B");
		mp->currSubMotionId = 80;
		SFX3D(0x180, &MW(mp, 0x8c, Vec));
		allPartyRideOff2();
	case 80:
		planeRoll2(mp, 0.3f, 28.0f);
		MW(mp, 0x1a8, f32) = revise360(MW(mp, 0x1a8, f32) + MW(mp, 0x2a4, f32));
		marioMakeJumpPara();
		MW(mp, 0x90, f32) += MW(mp, 0x7c, f32);
		marioChkOverhead();
		if (MW(mp, 0x7c, f32) < 0.0f || MW(mp, 0x1f4, void*) != NULL) {
			marioSetFallPara();
			MW(mp, 0x7c, f32) *= 0.5f;
			MW(mp, 0x80, f32) *= 0.5f;
			MW(mp, 0x84, f32) *= 0.5f;
			MW(mp, 0x88, f32) *= 0.5f;
			mp->currSubMotionId = 90;
			MW(mp, 4, u32) |= 0x100;
			MW(mp, 0x48, s32) = 20;
		}
		break;
	case 90:
		if (MW(mp, 0x48, s32) > 0) {
			planeRoll2(mp, 0.3f, 28.0f);
			MW(mp, 0x1a8, f32) = revise360(MW(mp, 0x1a8, f32) + MW(mp, 0x2a4, f32));
			if (--MW(mp, 0x48, s32) <= 0) {
				MW(mp, 4, u32) &= ~0x100;
			}
		}
		marioMakeJumpPara();
		if (MW(mp, 0x7c, f32) <= -20.0f) {
			MW(mp, 0x7c, f32) = -20.0f;
		}
		{
			HitEntry* hit;
			MW(mp, 0x1e4, HitEntry*) = NULL;
			hit = marioSearchGround(&y, &b, &c, MW(mp, 0x7c, f32), MW(mp, 0x7c, f32));
			if (hit != NULL) {
				MW(mp, 0x90, f32) = y;
				MW(mp, 0x1e4, HitEntry*) = hit;
			} else {
				MW(mp, 0x90, f32) += MW(mp, 0x7c, f32);
			}
		}
		if (MW(mp, 0x1e4, HitEntry*) != NULL) {
			camFollowYOn();
			allPartyRideOff2();
			MW(mp, 0x50, s16) = 0;
			MW(mp, 0x52, s16) = 0;
			MW(mp, 0, u32) &= ~0x80;
			marioAdjustMoveDir();
			planeReset();
			if (mp->motStruct != NULL) {
				__memFree(HEAP_DEFAULT, mp->motStruct);
				mp->motStruct = NULL;
			}
			MW(mp, 0x138, f32) = 0.0f;
			MW(mp, 0x140, f32) = 0.0f;
			marioChgMot(0);
		}
		break;
	case 70: {
		Vec p;
		set_damage_root_ypos(MW(mp, 0x90, f32));
		p = MW(mp, 0x8c, Vec);
		marioSetSplash(0, &p);
		MW(mp, 0x48, s32) = 16;
		mp->currSubMotionId = 71;
		MW(mp, 0x7c, f32) = -2.0f;
		MW(mp, 0x80, f32) = 0.0f;
		MW(mp, 0x84, f32) = 0.0f;
		MW(mp, 0x88, f32) = 0.0f;
		camFollowYOff();
	}
	case 71:
		marioMakeJumpPara();
		MW(mp, 0x90, f32) += MW(mp, 0x7c, f32);
		if (MW(mp, 0x90, f32) >= MW(mp, 0x2ac, f32) - 100.0f) {
			break;
		}
		mp->currSubMotionId = 72;
	case 72:
		MW(mp, 0x140, f32) = 0.0f;
		MW(mp, 0x138, f32) = 0.0f;
		marioClearJumpPara();
		planeSfxOff();
		MW(mp, 0x180, f32) = 0.0f;
		planeReset();
		allPartyRideOff2();
		marioSetFallPara();
		camFollowYOn();
		marioChgMot(0x1f);
	}
	marioUpdateCamCollision(MW(mp, 0x8c, Vec));
	MW(mp, 0x18c, f32) = MW(mp, 0x180, f32);
}


double sin(double);
void marioSearchUnder(void);

#define PI 3.1415927f
#define D(off) MD(off, f32)
#define SPD MW(mp, 0x180, f32)
#define STICK MW(mp, 0x24e, s8)

static inline BOOL planeChkUnder(void) {
	BOOL ret = FALSE;
	MarioWork* m = marioGetPtr();
	if (MW(m, 0x1f8, HitEntry*) != NULL && (hitGetAttr(MW(m, 0x1f8, HitEntry*)) & 0x38)) {
		ret = TRUE;
	}
	return ret;
}

static void flyMain(void) {
	f32 s2, c2, s, c;
	MarioWork* mp;
	f32 t;
	f32 a;
	f32 v;
	BOOL flag;
	s32 n;

	mp = marioGetPtr();
	switch (mp->currSubMotionId) {
	case 12:
		if (MW(mp, 0x2a8, f32) >= MW(mp, 0x90, f32)) {
			mp->currSubMotionId = 14;
		}
		{
			MarioWork* m = marioGetPtr();
			if (MW(m->motStruct, 0x28, u32) == 0xFFFFFFFF) {
				MW(m->motStruct, 0x28, s32) = SFX3D(0x17f, &MW(m, 0x8c, Vec));
			}
		}
	case 14:
		if (MW(mp, 0x9c, f32) > planeData[38]) {
			MW(mp, 0x9c, f32) -= 2.0f;
			MW(mp, 0xb4, f32) += 2.0f;
			MW(mp, 0x90, f32) += 2.0f;
		} else {
			mp->currSubMotionId = 15;
		}
		break;
	}
	if ((s32)mp->currSubMotionId != 15) {
		return;
	}
	if (MW(mp, 0x248, u16) & 0x100) {
		mp->currSubMotionId = 51;
		MW(mp, 0x2ac, f32) = MW(mp, 0x90, f32);
		return;
	}
	if (MW(mp, 0x248, u16) & 0x200) {
		mp->currSubMotionId = 51;
		MW(mp, 0x2ac, f32) = MW(mp, 0x90, f32);
		return;
	}
	D(8) = revise360(D(0xc) * planeData[14] + D(8));
	if (MD(0, u32) & 1) {
		if (D(8) <= 60.0f) {
			D(8) += 0.1f * (60.0f - D(8));
		}
		if (D(8) >= 150.0f) {
			D(8) += 0.1f * (150.0f - D(8));
		}
	} else {
		if (D(8) >= 330.0f) {
			D(8) += 0.1f * (330.0f - D(8));
		}
		if (D(8) <= 210.0f) {
			D(8) += 0.1f * (210.0f - D(8));
		}
	}
	flag = FALSE;
	t = D(8);
	if (t >= 90.0f && t <= 270.0f) {
		flag = TRUE;
	}
	MW(mp, 0x1a8, f32) = revise360(flag ? -t - 90.0f : 270.0f - t);
	if (STICK != 0) {
		if (SPD) {
			a = __fabsf((f32)STICK);
			if (MD(0, u32) & 1) {
				if (STICK < 0) {
					if (D(4) >= planeData[3]) {
						D(4) += 0.1f * (planeData[3] - D(4));
					} else {
						D(4) += 0.1f * (a * planeData[5]);
					}
				}
				if (STICK > 0) {
					if (D(4) <= planeData[4]) {
						D(4) = planeData[4];
					} else {
						D(4) -= 0.1f * (a * planeData[6]);
					}
				}
			} else {
				if (STICK > 0) {
					if (D(4) >= planeData[3]) {
						D(4) += 0.1f * (planeData[3] - D(4));
					} else {
						D(4) += 0.1f * (a * planeData[5]);
					}
				}
				if (STICK < 0) {
					if (D(4) <= planeData[4]) {
						D(4) = planeData[4];
					} else {
						D(4) -= 0.1f * (a * planeData[6]);
					}
				}
			}
		}
	} else {
		if (D(4) <= 0.0f || D(0x14) <= 0.0f) {
			if (D(0x14) > 0.0f && D(0x14) < 1.0f) {
				D(4) += planeData[30];
			}
			t = planeData[0] - SPD;
			if (t <= 0.0f) {
				t = 0.0f;
			}
			t = planeData[27] * (f32)sin(PI * (t * (90.0f / planeData[0])) / 180.0f);
			if (t <= planeData[28]) {
				t = planeData[28];
			}
			if (!planeChkUnder()) {
				D(0x1c) = t;
				D(4) += D(0x1c);
			} else {
				D(4) += -0.001f;
				SPD += 0.5f;
				if (SPD > 2.0f) {
					SPD = 2.0f;
				}
			}
		}
		if (D(4) <= planeData[4]) {
			D(4) = planeData[4];
		}
		if (D(4) >= 6.0f) {
			D(0x14) = 0.0f;
		}
	}
	SPD += SPD * planeData[1];
	if (D(4) >= 0.0f) {
		MD(0, u32) |= 0x10;
		a = SPD * (planeData[8] * (f32)sin(PI * (D(4) * planeData[7]) / 180.0f));
		SPD = SPD + a;
		if (STICK != 0 && D(4) >= planeData[3]) {
			SPD += planeData[2];
		}
		if (SPD <= 0.0f) {
			SPD = 0.0f;
		}
		t = 0.0f;
		if (STICK == 0) {
			if (SPD < planeData[20]) {
				t = planeData[0] - SPD;
				t *= planeData[21] * (f32)sin(PI * D(4) / 180.0f);
				t += D(0x14);
				D(0x14) = t;
			} else {
				D(0x14) = planeData[22];
			}
			D(4) += D(0x14);
			if (t <= 0.0f && SPD <= planeData[0] * planeData[23]) {
				t = planeData[0] - SPD * planeData[24];
				if (t <= 0.0f) {
					t = 0.0f;
				}
				t *= 90.0f / planeData[0];
				if (!planeChkUnder()) {
					a = planeData[25] * (f32)sin(PI * t / 180.0f);
					if (a <= planeData[26]) {
						a = 2.0f * planeData[26];
					}
					D(0x1c) = a;
				}
			}
			D(4) += D(0x1c);
		}
		if (STICK != 0) {
			v = planeData[18] * (f32)sin(PI * (planeData[0] - SPD) / 180.0f);
			D(0x18) += v;
			if (D(0x18) <= planeData[19]) {
				D(0x18) = planeData[19];
			}
		} else {
			v = D(0x18) += 0.1f * (0.0f - D(0x18));
		}
		D(4) += v;
	} else if (D(4) >= -80.0f) {
		if (MD(0, u32) & 0x10) {
			MD(0, u32) &= ~0x10;
		}
		D(0x10) = planeData[10] * (f32)sin(PI * (planeData[9] * __fabsf(D(4))) / 180.0f);
		SPD += D(0x10);
		a = (D(4) > 0.0f) ? 0.0f : __fabsf(D(4));
		t = (f32)sin(PI * (planeData[12] * a) / 180.0f);
		a = planeData[13] * ((f32)sin(PI * (SPD * planeData[11]) / 180.0f) * t);
		D(0x14) = D(0x14) + a;
		if (STICK != 0) {
			if (MD(0, u32) & 1) {
				if (STICK > 0 && D(0x14) >= 1.0f) {
					D(0x14) = 1.0f;
				}
			} else {
				if (STICK < 0 && D(0x14) >= 1.0f) {
					D(0x14) = 1.0f;
				}
			}
			if (!planeChkUnder()) {
				D(0x1c) += 0.1f * (1.0f - D(0x1c));
				if (D(0x1c) >= 0.0f) {
					D(0x1c) = 0.0f;
				}
			}
		}
		if (planeChkUnder()) {
			D(0x24) = -22.0f;
		} else {
			D(0x24) += 0.1f * (planeData[4] - D(0x24));
		}
		D(4) += D(0x14);
		if (D(4) <= D(0x24)) {
			D(4) = D(0x24);
		}
		D(0x18) += 0.1f * (0.0f - D(0x18));
	}
	if (SPD >= planeData[0]) {
		SPD = planeData[0];
	}
	MW(mp, 0x90, f32) += D(0x18);
	MW(mp, 0x90, f32) -= planeData[29];
	MW(mp, 0xc4, f32) = revise360(-D(4));
	MW(mp, 0x1a0, f32) = D(8);
	sincosf(&s, &c, MW(mp, 0x1a0, f32));
	MW(mp, 0x94, f32) += SPD * c;
	sincosf(&s2, &c2, 90.0f + D(4));
	MW(mp, 0x90, f32) += (SPD * c2) * ((c2 >= 0.0f) ? planeData[31] : planeData[32]);
	MW(mp, 0x8c, f32) += s2 * (SPD * s);
	if (SPD <= planeData[16]) {
		n = sysMsec2Frame(1000.0f * planeData[17]);
		if (MD(0, u32) & 1) {
			if ((f32)STICK < 0.0f) {
				if (++MD(0x20, s32) >= n) {
					MW(mp, 0x2ac, f32) = MW(mp, 0x90, f32);
					mp->currSubMotionId = 60;
					return;
				}
			}
		} else {
			if ((f32)STICK > 0.0f) {
				if (++MD(0x20, s32) >= n) {
					MW(mp, 0x2ac, f32) = MW(mp, 0x90, f32);
					mp->currSubMotionId = 60;
					return;
				}
			}
		}
	} else {
		MD(0x20, s32) = 0;
	}
	MW(mp, 0x1f8, HitEntry*) = ((HitEntry * (*)(void)) marioSearchUnder)();
	if (chkCollision(&MW(mp, 0x2ac, f32))) {
		if (MW(mp, 0x1f4, HitEntry*) != NULL) {
			mp->currSubMotionId = 40;
		} else {
			HitEntry* h = NULL;
			mp->currSubMotionId = 50;
			if (MW(mp, 0x1e0, HitEntry*) != NULL) {
				h = MW(mp, 0x1e0, HitEntry*);
			}
			if (MW(mp, 0x1e4, HitEntry*) != NULL) {
				h = MW(mp, 0x1e4, HitEntry*);
			}
			if (h != NULL && (hitGetAttr(h) & 0x200)) {
				mp->currSubMotionId = 70;
			}
		}
	}
}

void mot_plane_post(void) {
	MarioWork* mp = marioGetPtr();
	camFollowYOn();
	planeSfxOff();
	planeReset();
	MW(mp, 0x138, f32) = 0.0f;
	MW(mp, 0x140, f32) = 0.0f;
	if (mp->motStruct != NULL) {
		__memFree(HEAP_DEFAULT, mp->motStruct);
		mp->motStruct = NULL;
	}
	allPartyRideOff2();
}

static f32 planeDead270(void) {
	return 270.0f;
}

BOOL chkCollision(f32* outY) {
	Vec dir, hpos, v, v2;
	f32 s1, c1, s0, c0, s2, c2;
	f32 ox, oy, oz, dist, nx, ny, nz;
	f32 x, y, z, r;
	HitEntry* hit;
	BOOL ret;
	MarioWork* mp;

	ret = FALSE;
	mp = marioGetPtr();
	sincosf(&s0, &c0, 90.0f + MD(4, f32));
	sincosf(&s1, &c1, MD(8, f32));
	{
		v = (Vec){MW(mp, 0xb0, f32) + (MW(mp, 0x8c, f32) + MW(mp, 0x98, f32)) + 4.0f * (s1 * c0),
		         MW(mp, 0xb4, f32) + (MW(mp, 0x90, f32) + MW(mp, 0x9c, f32)) + -s0 * 4.0f,
		         MW(mp, 0xb8, f32) + (MW(mp, 0x94, f32) + MW(mp, 0xa0, f32)) + 4.0f * (c1 * c0)};
	}
	MD(0x3c, Vec) = v;
	sincosf(&s2, &c2, MD(0xc, f32));
	sincosf(&s0, &c0, MD(4, f32));
	MW(mp, 0x1e0, HitEntry*) = NULL;
	r = planeData[40];
	sincosf(&s1, &c1, MD(8, f32));
	x = MW(mp, 0xb0, f32) + (MW(mp, 0x8c, f32) + MW(mp, 0x98, f32));
	y = MW(mp, 0xb4, f32) + (MW(mp, 0x90, f32) + MW(mp, 0x9c, f32));
	z = MW(mp, 0xb8, f32) + (MW(mp, 0x94, f32) + MW(mp, 0xa0, f32));
	x += r * (s1 * -c0);
	y += s0 * r;
	z += r * (c1 * -c0);
	sincosf(&s0, &c0, MD(4, f32) - 90.0f);
	r = planeData[39];
	x += r * (c0 * s1) - r * (s2 * c1);
	y += r * (s0 * c2);
	z += r * (c0 * c1) - r * (s2 * s1);
	{
		v2 = (Vec){x, y, z};
	}
	MD(0x30, Vec) = v2;
	dist = 10.0f + MW(mp, 0x180, f32);
	hit = marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, MD(0x30, f32) - 10.0f * s1, MD(0x34, f32),
	                    MD(0x38, f32) - 10.0f * c1, s1, 0.0f, c1);
	if (hit != NULL) {
		MW(mp, 0x1e0, HitEntry*) = hit;
		ret = TRUE;
		*outY = oy;
	}
	dist = MW(mp, 0x180, f32);
	hit = marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, MD(0x3c, f32), MD(0x40, f32), MD(0x44, f32), s1, 0.0f, c1);
	if (hit != NULL) {
		MW(mp, 0x1e0, HitEntry*) = hit;
		ret = TRUE;
		*outY = oy;
	}
	MW(mp, 0x1e4, HitEntry*) = NULL;
	dist = 10.1f;
	hit = marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, MD(0x30, f32), MD(0x34, f32) + 10.0f, MD(0x38, f32), 0.0f, -1.0f, 0.0f);
	if (hit != NULL) {
		MW(mp, 0x1e4, HitEntry*) = hit;
		ret = TRUE;
		*outY = oy;
	}
	if (!ret) {
		MW(mp, 0x1e4, HitEntry*) = NULL;
		dist = 10.1f;
		hit = marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, MD(0x3c, f32), MD(0x40, f32) + 10.0f, MD(0x44, f32), 0.0f, -1.0f, 0.0f);
		if (hit != NULL) {
			MW(mp, 0x1e4, HitEntry*) = hit;
			ret = TRUE;
			*outY = oy;
		}
	}
	if (!ret) {
		PSVECSubtract(&MD(0x3c, Vec), &MD(0x30, Vec), &dir);
		dist = PSVECMag(&dir);
		PSVECNormalize(&dir, &dir);
		hit = marioHitCheckVec(&MD(0x30, Vec), &dir, &hpos, NULL, &dist);
		if (hit != NULL) {
			MW(mp, 0x1e4, HitEntry*) = hit;
			ret = TRUE;
			*outY = hpos.y;
		}
	}
	MW(mp, 0x1f4, HitEntry*) = NULL;
	if (MW(mp, 0x1e4, HitEntry*) == NULL) {
		dist = 2.0f;
		hit = marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, MD(0x30, f32), MD(0x34, f32), MD(0x38, f32), 0.0f, 1.0f, 0.0f);
		if (hit != NULL) {
			MW(mp, 0x1f4, HitEntry*) = hit;
			ret = TRUE;
			*outY = oy;
		}
	}
	return ret;
}

static f32 planeDead4(void) {
	return 4.0f;
}
