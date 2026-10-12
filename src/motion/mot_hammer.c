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

#define HAM_DIR(mario, dst)                                         	{                                                               		f32 a = MF(0x1A8);                                          		MarioWork* p = marioGetPtr(); f32 r;                         		f32 off = 0.0f;                                             		if (p->dispFlags & 0x80000000) {                            			off = chkRevDir(p->unk1A8) ? 30.0f : -30.0f;            		} if (a >= 90.0f && a <= 270.0f) { r = revise360(180.0f + off); } else { r = revise360(off); } dst = r;                                                           	}

static inline s32 hamLv(void) {
	return pouchGetHammerLv();
}


typedef struct { u8 pad[0x15]; char name[0x10]; } HamMobj;

static inline s32 chkBlock(HamMobj* obj) {
	s32 ok = 0;
	if (strcmp(obj->name, "MOBJ_Lv1Block") == 0 || strcmp(obj->name, "MOBJ_Lv1BigBlock") == 0) {
		if (pouchGetPtr()->hammerLevel >= 1) {
			ok = 1;
		}
	} else if (strcmp(obj->name, "MOBJ_Lv2Block") == 0 || strcmp(obj->name, "MOBJ_Lv2BigBlock") == 0) {
		if (pouchGetPtr()->hammerLevel >= 2) {
			ok = 1;
		}
	} else if (strcmp(obj->name, "MOBJ_Lv3Block") == 0 || strcmp(obj->name, "MOBJ_Lv3BigBlock") == 0) {
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
	s32 kind;
	f32 px, pz;
	s32 done;
	s32 n;
	s32 i;
	s32 snd;
	f32 py, ez;
	s32 efType;
	HitEntry* hit;

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
			f32 a = MF(0x1A8);
			f32 off = marioGetPtr()->dispFlags & 0x80000000 ? -30.0f : 0.0f;
			f32 r;
			if (a >= 90.0f && a <= 270.0f) {
				r = toMovedir2(180.0f, off);
			} else {
				r = toMovedir2(0.0f, off);
			}
			MF(0x1A0) = r;
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
				s32 v = 3;
				if (kind != 7) {
					v = kind;
				}
				MI(0x2A0) = v;
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
		MF(0x1A8) = r ? 180.0f : 0.0f;
	}
	MF(0x1AC) = MF(0x1A8);
	MF(0x19C) = toMovedir(MF(0x2A4));
	done = 0;
	MF(0x1A0) = MF(0x19C);
	if (mario->flags & 0x800) {
		s32 lim = MI(0x2A0);
		s32 t = MI(0x48);
		n = lim < t ? lim : t;
		if (t == lim) {
			done = 1;
		}
	} else {
		s32 t = MI(0x48);
		if (t > 10) {
			n = 10;
		} else {
			n = t;
		}
		if (t == 10) {
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
				movePos(&px, &pz, 16.0f, toMovedir2(MF(0x1AC), 0.0f));
				ez = 53.0f;
				efType = 0x16;
				break;
			case 0:
			case 6:
				movePos(&px, &pz, 25.0f, toMovedir2(MF(0x1AC), 0.0f));
				ez = -3.0f;
				efType = 0x15;
				break;
			case 5:
				movePos(&px, &pz, 31.0f, toMovedir2(MF(0x1AC), 0.0f));
				ez = 5.0f;
				efType = 0x15;
				break;
			case 4:
				movePos(&px, &pz, 30.0f, toMovedir2(MF(0x1AC), 0.0f));
				ez = 30.0f;
				efType = 0x16;
				break;
			}
		} else {
			efType = -1;
			switch (MI(0x2A8)) {
			case 7:
				movePos(&px, &pz, 16.0f, toMovedir2(MF(0x1AC), -2.0f));
				ez = 53.0f;
				efType = 0x16;
				break;
			case 0:
			case 6:
				movePos(&px, &pz, 30.0f, toMovedir2(MF(0x1AC), -6.0f));
				ez = -3.0f;
				efType = 0x15;
				break;
			case 5:
				movePos(&px, &pz, 36.0f, toMovedir2(MF(0x1AC), -6.0f));
				ez = 20.0f;
				efType = 0x16;
				break;
			case 4:
				movePos(&px, &pz, 37.0f, toMovedir2(MF(0x1AC), -6.0f));
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
	s32 a, b;
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
	if (mario->controlStickSensitivity != 0 && mario->wMotionTimer > 10 && mario->currMotionId == 0 && !(mario->dispFlags & 0x40000000)) {
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

static const Vec v = {0.0f, 40.0f, 0.0f};

#define H2_LV(lvl, a148, a68)                                       \
	{                                                               \
		MarioWork* m = marioGetPtr();                               \
		m->unk148 = a148;                                           \
		*(f32*)((u8*)m + 0x158) = 0.005f;                           \
		m->field_68 = a68;                                          \
		m->field_6C = v;                                            \
		MS(0x2B4) |= 0x1000;                                        \
	}

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
	s32 a, b;
	f32 c;
	HitEntry* hit;
	f32 ang, ang2;
	f32 s, co;
	f32 len;
	f32 hx, hy, hz, nx, ny, nz;

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
		MF(0x180) = 0.0f;
		MS(0x50) = 0;
		MI(0x44) = 1;
		MI(0x48) = 30;
		if (MB(0x42) == 3) {
			MF(0x2A8) = 38.0f;
		} else if (MB(0x42) <= 2) {
			MF(0x2A8) = 15.0f;
		} else {
			MF(0x2A8) = 10.0f;
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
		if (180.0f == MF(0x1AC) && MB(0x43) == 1) {
			mario->dispFlags |= 8;
		}
		if (0.0f == MF(0x1AC) && MB(0x43) == 0) {
			mario->dispFlags |= 0x10;
		}
		marioPaperOn("p_kaiten_h");
		marioChgPaper("P_H_1C");
		marioPaperLightOff();
		MI(0x2B8) = psndSFXOn_3D(0x162, (Vec*)&MF(0x8C));
		MF(0x2B0) = 0.0f;
		MS(0x28) = 0;
		animPoseSetLocalTime(MI(0x228 + marioAnimeId() * 4), MF(0x2B0));
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
			animPoseSetLocalTime(MI(0x228 + marioAnimeId() * 4), MF(0x2B0) / 6.0f);
		}
	case 11:
		if (!(MH(0x246) & 0x200)) {
			if ((u32)MI(0x2B8) != 0xFFFFFFFFU) {
				psndSFXOff(MI(0x2B8));
				MI(0x2B8) = -1;
			}
			{
				MarioWork* m = marioGetPtr();
				m->unk148 = 0.0f;
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
				MF(0x2A8) = 38.0f;
			} else if (MB(0x42) == 2) {
				MF(0x2A8) = 22.0f;
			} else if (MB(0x42) <= 1) {
				MF(0x2A8) = 15.0f;
			}
			effUltraHammerEntry(MB(0x43) != 0, MI(0x48), MF(0x8C), 20.0f + MF(0x90), MF(0x94), 1.0f);
		}
		break;
	case 20:
		ang = MF(0x1A8);
		MS(0x2A4) = 10;
		mario->dispFlags |= 0x100;
		ang2 = revise360(270.0f - MF(0x1A8));
		{
			MarioWork* m = marioGetPtr();
			sincosf(&s, &co, ang2);
			len = (f32){2.0f} * MF(0x1B4);
			hit = hitCheckFilter(0, &hx, &hy, &hz, &len, &nx, &ny, &nz, m->position.x, (f32){0.5f} * MF(0x1B8) + m->position.y, m->position.z, s, 0.0f, co);
		}
		if (hit && (hitGetAttr(hit) & 0x800005)) {
			ang = ang;
		}
		if (hit) {
			MI(0x1FC) = (s32)hit;
		}
		MF(0x1A8) = MF(0x2A8) * (MB(0x43) ? -1.0f : 1.0f) + MF(0x1A8);
		if ((s32)ang / 360 != (s32)MF(0x1A8) / 360) {
			psndSFXOn_3D(0x163, (Vec*)&MF(0x8C));
		}
		if (MS(0x2A4) == 1) {
			psndSFXOn_3D(0x163, (Vec*)&MF(0x8C));
		}
		MI(0x48)--;
		if (MB(0x42) > 2 && MI(0x48) == 10) {
			H2_CLR_PAPER()
		}
		if (MI(0x48) <= 0) {
			if (MB(0x42) <= 2) {
				MI(0x48) = sysMsec2Frame(300);
			} else {
				MF(0x1A8) = revise360(MF(0x1A8));
				marioAdjustMoveDir();
				MI(0x48) = 30;
			}
			MI(0x44) = 22;
		}
	case 22:
		if (--MI(0x48) > 0) {
			break;
		}
		if (MB(0x42) <= 2) {
			H2_CLR_PAPER()
			MF(0x1A8) = revise360(MF(0x1A8));
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
	return revise360(270.0f - mario->unk1A8);
}


void mot_ham2_post(void) {
	MarioWork* mario = marioGetPtr();
	if (mario->dispFlags & 0x40000000) {
		marioPaperOff();
	}
	{
		MarioWork* m = marioGetPtr();
		m->unk148 = 0.0f;
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

HitEntry* hitEstimate(s32* out) {
	MarioWork* mario;
	HitCheckQuery q;
	Vec pos;
	HitEntry* hit;
	f32 s, c;
	f32 cy;
	f32 a, h;
	s32 i;

	mario = marioGetPtr();
	*out = 0;
	a = mario->unk1A8;
	{
		f32 off = !(marioGetPtr()->dispFlags & 0x80000000) ? 0.0f : -20.0f;
		if (a >= 90.0f && a <= 270.0f) {
			a = toMovedir2(180.0f, off);
		} else {
			a = toMovedir2(0.0f, off);
		}
	}
	sincosf(&s, &c, a);
	h = MF(0x1B8);
	cy = (f32)cos(3.14159265f);
	{
	Vec dir1 = {0.0f, 0.0f, 0.0f};
	dir1.x = s;
	dir1.y = -cy;
	dir1.z = c;
	pos = mario->position;
	pos.y = 4.0f + (mario->position.y + h);
	q.targetPos = pos;
	q.targetDir = dir1;
	q.targetDistance = 14.0f;
	hit = hitCheckVecFilter(&q, NULL);
	if (hit && !(hitGetAttr(hit) & 0x800005)) {
		*out = 7;
		return hit;
	}
	}
	cy = (f32)cos(1.2217306f);
	{
	Vec dir2 = {0.0f, 0.0f, 0.0f};
	dir2.x = s;
	dir2.y = -cy;
	dir2.z = c;
	pos.x = s * 5.0f + mario->position.x;
	pos.y = mario->position.y + h;
	pos.z = 5.0f * c + mario->position.z;
	q.targetPos = pos;
	q.targetDir = dir2;
	q.targetDistance = 26.0f;
	hit = hitCheckVecFilter(&q, NULL);
	if (hit && !(hitGetAttr(hit) & 0x800005)) {
		*out = (q.hitPos.y - mario->position.y > 30.0f) ? 4 : 5;
		return hit;
	}
	}
	cy = (f32)cos(0.78539816f);
	{
	Vec dir3 = {0.0f, 0.0f, 0.0f};
	dir3.x = s;
	dir3.y = -cy;
	dir3.z = c;
	pos.x = s * 5.0f + mario->position.x;
	pos.y = mario->position.y + h;
	pos.z = 5.0f * c + mario->position.z;
	q.targetPos = pos;
	q.targetDir = dir3;
	q.targetDistance = 30.0f;
	hit = hitCheckVecFilter(&q, NULL);
	if (hit && !(hitGetAttr(hit) & 0x800005)) {
		*out = 5;
		return hit;
	}
	}
	cy = (f32)cos(0.0f);
	{
	Vec dir4 = {0.0f, 0.0f, 0.0f};
	dir4.y = -cy;
	{
	Vec dir4b = dir4;
	for (i = 0; i < 2; i++) {
		f32 d, m;
		if (i == 0) {
			d = 36.0f;
			m = 20.0f;
		} else {
			d = 34.0f;
			if (mario->dispFlags & 0x80000000) {
				m = 37.0f;
			} else {
				m = d;
			}
		}
		pos.x = s * m + mario->position.x;
		pos.y = mario->position.y + h;
		pos.z = c * m + mario->position.z;
		q.targetPos = pos;
		q.targetDir = dir4b;
		q.targetDistance = d;
		hit = hitCheckVecFilter(&q, NULL);
		if (hit && !(hitGetAttr(hit) & 0x800005)) {
			*out = (q.hitPos.y - mario->position.y > 13.0f) ? 5 : 6;
			return hit;
		}
	}
	}
	}
	return hit;
}

