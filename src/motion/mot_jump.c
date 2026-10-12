#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mot/mot_slit.h"
#include "pmario_sound.h"
#include <string.h>

void kpa_fall_80213C38(void);
void kpa_jump(void);
void kpa_jumpNpc(void);
void kpaChgPose(const char* a, const char* b);
void clear_hitobj_ride(void);
void marioSetJumpPara(void);
void marioMakeJumpPara(void);
void marioSetPeakYpos(void);
void marioClearJumpPara(void);
void marioChgMot2(MarioMotion);
void marioChgMotAuto(void);
void marioSlitForceCancel(void);
void* marioChkFront(Vec* out, Vec* pos, f32 dir, f32 dist);
f32 revise360(f32);
f32 distABf(f32, f32, f32, f32);
void sincosf(f32* s, f32* c, f32 deg);
s32 irand(s32);
void* mobjHitObjPtrToPtr(void* hit);
void marioPreJump(void);

#define MF(o) (*(f32*)((u8*)mario + (o)))
#define MI(o) (*(s32*)((u8*)mario + (o)))
#define MH(o) (*(s16*)((u8*)mario + (o)))
#define MO(p, o) (*(f32*)((u8*)(p) + (o)))

static f32 marioJumpStandData[] = {1.52f, -0.188f, 2.925f, -0.847f, -0.1f, -0.4f, 0.024f, -0.004f, 0.125f, 0.7f};
f32 marioJumpSwData[] = {2.5f, -0.1f, 0.02f, -0.01f, -0.08f, -0.4f, 0.0f, -0.002f};

static inline void chgPoseB(MarioWork* mario) {
	if (!(mario->flags & 0x2000) && mario->characterId == 0) {
		marioChgPose("M_J_1B\x00");
	}
}
static inline void chgPoseC(MarioWork* mario) {
	if (!(mario->flags & 0x2000) && mario->characterId == 0) {
		marioChgPose("M_J_1C");
	}
}

void marioPreJump(void) {
	MarioWork* mario = marioGetPtr();
	mario->flags &= ~0x20000;
	mario->flags |= 0x10000;
	mario->airTimer = 0;
	MH(0x52) = 0;
	mario->hitobjJumpFrom = mario->hitobjStandOn;
	clear_hitobj_ride();
	marioSetJumpPara();
	*(Vec*)((u8*)mario + 0x11C) = mario->position;
}

f32 marioGetJumpHeight(void) {
	MarioWork* mario = marioGetPtr();
	return MF(0x2B8);
}

void mot_jumpStand(void) {
	MarioWork* mario = marioGetPtr();
	f32 prev;
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		MF(0x180) = 0.0f;
		marioPreJump();
		MF(0x2B0) = 0.0f;
		MI(0x44) = 0;
		MI(0x48) = 0;
	}
	switch (mario->currSubMotionId) {
	case 0:
		if (++MI(0x48) >= 3) {
			MI(0x44) = 4;
			MF(0x7C) = marioJumpStandData[0];
			MF(0x80) = marioJumpStandData[1];
			MF(0x84) = marioJumpStandData[2];
			MF(0x88) = marioJumpStandData[3];
			chgPoseB(mario);
		}
		break;
	case 4:
		prev = MF(0x7C);
		marioMakeJumpPara();
		if (prev >= MF(0x7C)) {
			MI(0x44) = 6;
		}
		MF(0x90) += MF(0x7C);
		MF(0x2B0) += MF(0x7C);
		break;
	case 6:
		MF(0x90) += MF(0x7C);
		MF(0x2B0) += MF(0x7C);
		if (MF(0x2B0) >= MF(0x2B8) * marioJumpStandData[9]) {
			MI(0x44) = 8;
		}
		if (MF(0x7C) <= 0.0f) {
			MI(0x44) = 8;
		}
		break;
	case 8:
		MF(0x7C) += (-1.0f - MF(0x7C)) * marioJumpStandData[8];
		MF(0x90) += MF(0x7C);
		MF(0x2B0) += MF(0x7C);
		if (MF(0x7C) <= 0.0f) {
			MI(0x44) = 10;
			chgPoseC(mario);
			marioSetPeakYpos();
			MF(0x7C) = marioJumpStandData[4];
			MF(0x80) = marioJumpStandData[5];
			MF(0x84) = marioJumpStandData[6];
			MF(0x88) = marioJumpStandData[7];
			mario->flags &= ~0x10000;
			mario->flags |= 0x20000;
			MI(0x44) = 20;
		}
		break;
	case 10:
		marioMakeJumpPara();
		if (MF(0x7C) <= 0.0f) {
			chgPoseC(mario);
			marioSetPeakYpos();
			MF(0x7C) = marioJumpStandData[4];
			MF(0x80) = marioJumpStandData[5];
			MF(0x84) = marioJumpStandData[6];
			MF(0x88) = marioJumpStandData[7];
			mario->flags &= ~0x10000;
			mario->flags |= 0x20000;
			MI(0x44) = 20;
		}
		MF(0x90) += MF(0x7C);
		break;
	case 20:
		if (--MI(0x48) <= 0) {
			MF(0x180) = 0.0f;
			MI(0x44) = 30;
		}
		break;
	}
	mario->airTimer++;
	if (marioSlitButton() != 2) {
		marioSlitForceCancel();
	}
}

void mot_jumpSw(void) {
	MarioWork* mario = marioGetPtr();
	void* mobj;
	f32 dir;
	f32 x, z;
	f32 c, s;
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		marioResetCamFollowRate();
		mario->flags |= 0x80;
		camFollowYOff();
		marioPreJump();
		chgPoseB(mario);
		if (mario->hitobjJumpFrom != NULL) {
			if (hitGetAttr((HitEntry*)MI(0x1E8)) & 0x80000000) {
				mobj = mobjHitObjPtrToPtr(mario->hitobjJumpFrom);
				MF(0x2B4) = MO(mobj, 0x38);
				MF(0x2B8) = MO(mobj, 0x40);
				{
				Vec v;
				Vec t = {0.0f, 0.0f, 0.0f};
				Vec out;
				t.x = MO(mobj, 0x38);
				t.y = 0.5f * MF(0x1B8) + MO(mobj, 0x3C);
				t.z = MO(mobj, 0x40);
				v = t;
				if (marioChkFront(&out, &v, MF(0x1A0), 5.0f * MF(0x1B4)) != NULL && out.x >= 0.0f &&
				    out.x <= 0.5f * MF(0x1B4) + 30.0f) {
					MF(0x19C) = MF(0x1A0) = revise360(180.0f + MF(0x1A0));
				}
				}
				{
				sincosf(&s, &c, MF(0x1A0));
				x = 30.0f * s + MO(mobj, 0x38);
				z = 30.0f * c + MO(mobj, 0x40);
				MI(0x48) = 20;
				MF(0x180) = distABf(MF(0x8C), MF(0x94), x, z) / (f32)MI(0x48);
				}
			}
		} else {
			dir = revise360(180.0f + MF(0x1A0));
			sincosf(&s, &c, dir);
			x = 30.0f * s + MF(0x8C);
			z = 30.0f * c + MF(0x94);
			MF(0x1A0) = dir;
			MF(0x19C) = dir;
			MI(0x48) = 20;
			MF(0x180) = distABf(MF(0x8C), MF(0x94), x, z) / (f32)MI(0x48);
		}
		MI(0x44) = 0;
	}
	switch (MI(0x44)) {
	case 0:
		MI(0x48) = MI(0x48) - 1;
		marioMakeJumpPara();
		if (MF(0x7C) <= 0.0f) {
			chgPoseC(mario);
			marioSetPeakYpos();
			MF(0x7C) = marioJumpSwData[4];
			MF(0x80) = marioJumpSwData[5];
			MF(0x84) = marioJumpSwData[6];
			MF(0x88) = marioJumpSwData[7];
			mario->flags &= ~0x10000;
			mario->flags |= 0x20000;
			MI(0x44) = 10;
		}
		MF(0x90) += MF(0x7C);
		break;
	case 10:
		if (--MI(0x48) <= 0) {
			MF(0x180) = 0.0f;
			MI(0x44) = 20;
		}
		break;
	}
	mario->airTimer++;
}

void mot_jumpNpc(void) {
	MarioWork* mario = marioGetPtr();
	void* mobj;
	f32 dir;
	f32 x, z;
	f32 c, s;
	if (mario->characterId == 2) {
		kpa_jumpNpc();
		return;
	}
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		marioResetCamFollowRate();
		if (mario->characterId != 2) {
			mario->flags |= 0x80;
		}
		camFollowYOff();
		marioPreJump();
		if (mario->characterId == 2) {
			MF(0x7C) = 2.6f;
			MF(0x80) = -0.06f;
			MF(0x84) = -0.01f;
			MF(0x88) = -0.002f;
		} else {
			MF(0x7C) = 1.0f;
			MF(0x80) = -0.04f;
			MF(0x84) = -0.01f;
			MF(0x88) = -0.02f;
		}
		chgPoseB(mario);
		if (mario->hitobjJumpFrom != NULL) {
			if (hitGetAttr((HitEntry*)MI(0x1E8)) & 0x80000000) {
				mobj = mobjHitObjPtrToPtr(mario->hitobjJumpFrom);
				MF(0x2B4) = MO(mobj, 0x38);
				MF(0x2B8) = MO(mobj, 0x40);
				{
				Vec v;
				Vec t = {0.0f, 0.0f, 0.0f};
				Vec out;
				t.x = MO(mobj, 0x38);
				t.y = 0.5f * MF(0x1B8) + MO(mobj, 0x3C);
				t.z = MO(mobj, 0x40);
				v = t;
				if (marioChkFront(&out, &v, MF(0x1A0), 5.0f * MF(0x1B4)) != NULL && out.x >= 0.0f &&
				    out.x <= 0.5f * MF(0x1B4) + 30.0f) {
					MF(0x19C) = MF(0x1A0) = revise360(180.0f + MF(0x1A0));
				}
				}
				{
				sincosf(&s, &c, MF(0x1A0));
				x = 30.0f * s + MO(mobj, 0x38);
				z = 30.0f * c + MO(mobj, 0x40);
				MI(0x48) = 20;
				MF(0x180) = distABf(MF(0x8C), MF(0x94), x, z) / (f32)MI(0x48);
				}
			}
		} else {
			revise360(180.0f + MF(0x1A0));
			dir = MF(0x1A0);
			sincosf(&s, &c, dir);
			x = 30.0f * s + MF(0x8C);
			z = 30.0f * c + MF(0x94);
			MF(0x1A0) = dir;
			MF(0x19C) = dir;
			MI(0x48) = 20;
			MF(0x180) = distABf(MF(0x8C), MF(0x94), x, z) / (f32)MI(0x48);
		}
		MI(0x44) = 0;
	}
	switch (MI(0x44)) {
	case 0:
		MI(0x48) = MI(0x48) - 1;
		marioMakeJumpPara();
		if (MF(0x7C) <= 0.0f) {
			chgPoseC(mario);
			marioSetPeakYpos();
			MF(0x7C) = -0.03f;
			MF(0x80) = -0.02f;
			MF(0x84) = 0.04f;
			MF(0x88) = 0.0f;
			mario->flags &= ~0x10000;
			mario->flags |= 0x20000;
			MI(0x44) = 20;
		}
		MF(0x90) += MF(0x7C);
		break;
	case 20:
		if (--MI(0x48) <= 0) {
			MF(0x180) = 0.0f;
			MI(0x44) = 30;
		}
		break;
	}
	mario->airTimer++;
}

static inline void jumpSfx(MarioWork* mario) {
	s32 r = irand(10000);
	s32 id;
	if (r < 2000) {
		id = 0x9D;
	} else if (r < 4000) {
		id = 0x9E;
	} else if (r < 6000) {
		id = 0x9F;
	} else if (r < 8000) {
		id = 0xA0;
	} else {
		id = 0xA1;
	}
	psndSFXOn_3D((char*)id, &mario->position);
}

void mot_jump(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->characterId == 2) {
		kpa_jump();
		return;
	}
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		marioResetCamFollowRate();
		mario->flags |= 0x80000;
		MI(0x48) = 2;
		MI(0x44) = 0;
		marioPreJump();
		if (mario->currMotionId == 8) {
			camFollowYOn();
		} else {
			camFollowYOff();
		}
		chgPoseB(mario);
		if (mario->currMotionId != 8) {
			jumpSfx(mario);
		}
		psndSFXOn_3D((char*)0x14D, &mario->position);
		if (mario->airTimer == 0) {
			*(Vec*)((u8*)mario + 0xD4) = mario->position;
		}
		mario->trigFlags &= ~0x10000;
	}
	switch (MI(0x44)) {
	case 0:
		if (--MI(0x48) <= 0) {
			chgPoseB(mario);
			MI(0x44) = 10;
		}
		break;
	}
	mario->airTimer++;
}

void mot_jumpSmall(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->characterId == 2) {
		kpa_jump();
		return;
	}
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		marioResetCamFollowRate();
		mario->flags |= 0x80000;
		MI(0x48) = 2;
		MI(0x44) = 0;
		marioPreJump();
		if (mario->currMotionId != 8) {
			camFollowYOff();
		}
		chgPoseB(mario);
		if (mario->currMotionId != 8) {
			jumpSfx(mario);
		}
		psndSFXOn_3D((char*)0x14D, &mario->position);
		if (mario->airTimer == 0) {
			*(Vec*)((u8*)mario + 0xD4) = mario->position;
		}
		mario->trigFlags &= ~0x10000;
	}
	switch (MI(0x44)) {
	case 0:
		if (--MI(0x48) <= 0) {
			chgPoseB(mario);
			MI(0x44) = 10;
		}
		break;
	}
	mario->airTimer++;
}

void mot_upstairs(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		mario->flags |= 0x40000;
		mario->flags |= 0x80;
		marioClearJumpPara();
		MI(0x48) = 3;
		MF(0x7C) = (MF(0x1C4) - MF(0x90)) / (f32)MI(0x48);
		MI(0x44) = 0;
	}
	switch (MI(0x44)) {
	case 0:
		MF(0x90) = MF(0x90) + MF(0x7C);
		if (--MI(0x48) <= 0) {
			mario->flags &= ~0x80;
			mario->flags &= ~0x40;
			mario->flags &= ~0x40000;
			if (mario->flags & 0x100000) {
				motSlitContinue();
			} else if (mario->dispFlags & 0x1000000) {
				marioChgMot2(0x15);
			} else {
				marioChgMotAuto();
			}
		}
		break;
	}
}

void mot_fall(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->characterId == 2) {
		kpa_fall_80213C38();
		return;
	}
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		mario->flags &= ~0x10000;
		mario->flags |= 0x20000;
		if (mario->soundId[2] != (u32)-1) {
			psndSFXOff(mario->soundId[2]);
			mario->soundId[2] = -1;
		}
		marioResetCamFollowRate();
		MI(0x44) = 0;
		if (mario->currMotionId != 11) {
			if (mario->characterId == 2) {
				kpaChgPose("KPA_J_1B", "KPA2_J_1B");
			} else if (!(mario->flags & 0x2000) && mario->characterId == 0) {
				marioChgPose("M_J_1C");
			}
		} else {
			mario->flags |= 0x80;
		}
		if (mario->airTimer == 0) {
			*(Vec*)((u8*)mario + 0xD4) = mario->position;
		}
	}
	switch (MI(0x44)) {
	case 0:
		if (MF(0x90) <= MF(0x120)) {
			if (!marioBgmodeChk()) {
				camFollowYOn();
			}
			MI(0x44) = 10;
		}
		break;
	}
	mario->airTimer++;
	if (MI(0x16C) >= 0x1AE) {
		f32 r = marioGetCamFollowRate();
		r += 0.1f;
		if (r >= 0.8f) {
			r = 0.8f;
		}
		marioSetCamFollowRate(r);
	}
}

void mot_fall_post(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->soundId[2] != (u32)-1) {
		psndSFXOff(mario->soundId[2]);
		mario->soundId[2] = -1;
	}
}

void mot_land(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		mario->flags &= ~0xF0000;
		mario->airTimer = 0;
		MH(0x52) = 0;
		MI(0x44) = 0;
		MF(0x180) = 0.0f;
		marioResetCamFollowRate();
		if (mario->soundId[2] != (u32)-1) {
			psndSFXOff(mario->soundId[2]);
			mario->soundId[2] = -1;
		}
	}
	switch (MI(0x44)) {
	case 0:
		marioChgMot(0);
		break;
	case 1:
		if (--MI(0x48) <= 0) {
			marioChgMot(0);
		}
		break;
	case 10:
		if (--MI(0x48) <= 0) {
			marioChgMot(0);
		}
		break;
	}
}
