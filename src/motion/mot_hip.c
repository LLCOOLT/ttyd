#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "pmario_sound.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_pouch.h"
#include "mario/mario_sbr.h"
#include "manager/evtmgr.h"
#include "system.h"

extern s32 evt_cam_shake[];

HitEntry* marioChkLandon(f32* outY, f32 y);
HitEntry* marioSearchGround(f32* a, f32* b, f32* c, f32 d, f32 e);
f32 marioGetFallSpd(void);
void marioChgMotSub(s32 a, s32 b);
void set_damage_root_ypos(f32 y);
void kpa_hip(void);

#define MF(o) (*(f32*)((u8*)mario + (o)))
#define MI(o) (*(s32*)((u8*)mario + (o)))
typedef struct HipExt {
    u8 pad[0x2A0];
    f32 ang;
    s32 snd1;
    s32 snd2;
} HipExt;

#define EX ((HipExt*)mario)
#define MH(o) (*(s16*)((u8*)mario + (o)))

static s32 quake_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, -230000000, -229999980, 110, 2, 1,
};

static s32 quake_bgmode_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, -230000000, -229999990, 110, 2, 1,
};

s32 U_chkground(void);
void mot_hip_post(void);

BOOL marioChkHipAttack(void) {
    BOOL ret;
    MarioWork* mario;

    ret = FALSE;
    mario = marioGetPtr();
    if (MH(0x52) >= 10 && (mario->field_0x248 & 0x100) && pouchGetJumpLv() >= 2) {
        ret = TRUE;
    }
    return ret;
}

BOOL marioChkHipBump(void) {
    BOOL ret = FALSE;

    if (marioGetPtr()->currMotionId == MARIO_MOTION_HIP_2) {
        ret = TRUE;
    }
    return ret;
}

void mot_hip(void) {
    MarioWork* mario;
    HitEntry* hit;
    f32 fall;
    f32 y;
    f32 tmp1;
    f32 tmp2;
    f32 d;
    u32 attr;

    mario = marioGetPtr();
    if (mario->characterId == 2) {
        kpa_hip();
        return;
    }
    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        mario->flags &= ~0xF0000;
        mario->flags |= 0x20000;
        mario->flags |= 0x80;
        marioAdjustMoveDir();
        {
            s32 f = 0;
            if (MF(0x1AC) >= 90.0f && MF(0x1AC) <= 270.0f) {
                f = 1;
            }
            MF(0x19C) = toMovedir(f ? 180.0f : 0.0f);
        }
        MF(0x1A0) = MF(0x19C);
        marioChgPose("M_A_1A");
        MF(0x7C) = 5.2f;
        MF(0x80) = 0.0f;
        MF(0x84) = 0.0f;
        MF(0x88) = 0.0f;
        d = -2.0f * marioGetScale() / 2.0f;
        MF(0x90) += d;
        d = 14.0f * marioGetScale() / 2.0f;
        MF(0xB4) += d;
        MF(0xA8) = 0.0f;
        mario->currSubMotionId = 0;
        EX->snd1 = -1;
        EX->snd2 = -1;
    }
    switch (mario->currSubMotionId) {
    case 0:
        EX->snd1 = psndSFXOn_3D((char*)0x158, &mario->position);
        EX->snd2 = psndSFXOn_3D((char*)0xDB, &mario->position);
        EX->ang = 0.0f;
        MF(0x180) = 0.0f;
        mario->currSubMotionId = 1;
    case 1:
        if ((EX->ang += 20.0f) >= 360.0f) {
            EX->ang = 360.0f;
        }
        MF(0x7C) -= 0.42f;
        if (mario->field_0x1F4 == NULL) {
            MF(0xA8) += MF(0x7C);
        }
        if (360.0f == EX->ang && MF(0x7C) <= 0.0f) {
            MI(0x48) = 5;
            mario->currSubMotionId = 2;
            MF(0x7C) = 2.0f;
        }
        switch (U_chkground()) {
        case 1:
            return;
        case 2:
            marioChgMotSub(0, 0);
            mot_hip_post();
            return;
        }
        break;
    case 2:
        if (MF(0x7C) >= 0.0f) {
            MF(0x7C) -= 1.4f;
            if (mario->field_0x1F4 == NULL) {
                MF(0xA8) += MF(0x7C);
            }
        }
        if (--MI(0x48) <= 0) {
            mario->currSubMotionId = 10;
        }
        switch (U_chkground()) {
        case 1:
            return;
        case 2:
            marioChgMotSub(0, 0);
            mot_hip_post();
            return;
        }
        break;
    case 10:
        marioChkLandon(&y, 0.0f);
        if ((EX->ang += 22.5f) >= 360.0f) {
            mario->flags &= ~0x10000;
            mario->flags |= 0x20000;
            EX->ang = 0.0f;
            mario->currSubMotionId = 20;
            MF(0x80) = -3.4744f;
            MF(0x84) = 0.4704f;
            MF(0x88) = -1.1904f;
            MF(0x7C) = MF(0x80);
        }
        switch (U_chkground()) {
        case 1:
            return;
        case 2:
            marioChgMotSub(0, 0);
            mot_hip_post();
            return;
        }
        break;
    case 20:
        MI(0x48) = sysMsec2Frame(200);
        mario->currSubMotionId = 21;
    case 21:
        if (--MI(0x48) > 0) {
            break;
        }
        fall = marioGetFallSpd();
        hit = marioSearchGround(&y, &tmp1, &tmp2, fall, fall);
        if (fall < -100.0f) {
            fall = -100.0f;
            MF(0x88) = 0.0f;
            MF(0x84) = 0.0f;
            MF(0x80) = 0.0f;
            MF(0x7C) = fall;
        }
        if (hit != NULL) {
            mario->currMotionId = MARIO_MOTION_HIP_2;
            mario->currSubMotionId = 22;
            MI(0x48) = 20;
            MI(0x1E4) = (s32)hit;
            MI(0x1E8) = 0;
            MF(0x90) = y;
            EX->ang = 0.0f;
            MF(0xB4) = 0.0f;
            MH(0x50) = 0;
            MH(0x52) = 0;
            MF(0xA8) = 0.0f;
            marioChgPose("M_A_1B");
            attr = hitGetAttr(hit);
            if (attr & 0x200) {
                set_damage_root_ypos(MF(0x90));
                d = -0.4f;
                MF(0x7C) = d;
                MF(0x80) = d;
                MF(0x84) = 0.0f;
                MF(0x88) = 0.0f;
                marioChgMot(MARIO_MOTION_DAMAGE);
                return;
            }
            if (attr & 0x400) {
                set_damage_root_ypos(MF(0x90));
                marioChgMot(MARIO_MOTION_DAMAGE_TOGE);
                return;
            }
            if (attr & 0x800) {
                set_damage_root_ypos(MF(0x90));
                marioChgMot(MARIO_MOTION_DAMAGE_TOGE);
                return;
            }
            psndSFXOn_3D((char*)0x159, &mario->position);
            evtEntryType(marioBgmodeChk() == 0 ? quake_evt : quake_bgmode_evt, 0, 0, 0);
        } else {
            MF(0x90) += fall;
        }
        if (mario->unk16C > 400 && !marioBgmodeChk()) {
            camFollowYOn();
        }
        break;
    case 22:
        if (U_chkground() == 1) {
            return;
        }
        if (--MI(0x48) <= 0) {
            mario->dispFlags &= ~0x08000000;
            if (!marioBgmodeChk()) {
                camFollowYOn();
            }
            mario->dispFlags &= ~4;
            mario->flags &= ~0x80;
            marioChgMotSub(0, 0);
            mot_hip_post();
        }
        break;
    case 50:
        marioChgPose("M_A_1A");
        MF(0x7C) = 0.0f;
        MF(0x80) = 0.0f;
        MF(0x84) = 0.0f;
        MF(0x88) = 0.0f;
        EX->ang += (f32)keyGetSubStickY(2) / 10.0f;
        break;
    }
    MF(0xC4) = EX->ang;
    if (MH(0x50) != 0) {
        MF(0x174) = 0.0f;
        MF(0x17C) = 0.0f;
        MF(0x178) = 0.0f;
    }
}

#pragma dont_inline on
s32 U_chkground(void) {
    MarioWork* mario;
    HitEntry* hit;
    u32 attr;
    f32 y;
    f32 v;

    mario = marioGetPtr();
    hit = marioChkLandon(&y, 1.0f);
    if (hit != NULL) {
        MI(0x1E4) = (s32)hit;
        MI(0x1E8) = 0;
        MF(0x90) = y;
        EX->ang = 0.0f;
        MF(0xB4) = 0.0f;
        MF(0xA8) = 0.0f;
        MH(0x50) = 0;
        MH(0x52) = 0;
        mario->dispFlags &= ~4;
        mario->flags &= ~0x80;
        camFollowYOn();
        attr = hitGetAttr(hit);
        if (attr & 0x200) {
            set_damage_root_ypos(MF(0x90));
            v = -0.4f;
            MF(0x7C) = v;
            MF(0x80) = v;
            MF(0x84) = 0.0f;
            MF(0x88) = 0.0f;
            marioChgMot(MARIO_MOTION_DAMAGE);
            return 1;
        }
        if (attr & 0xC00) {
            set_damage_root_ypos(MF(0x90));
            marioChgMot(MARIO_MOTION_DAMAGE_TOGE);
            return 1;
        }
        return 2;
    }
    return 0;
}

#pragma dont_inline reset

void mot_hip_post(void) {
    MarioWork* mario;

    mario = marioGetPtr();
    marioOfsRotReset();
    MH(0x50) = 0;
    MH(0x52) = 0;
    if ((u32)EX->snd1 != 0xFFFFFFFFU) {
        psndSFXOff(EX->snd1);
        EX->snd1 = -1;
    }
    if ((u32)EX->snd2 != 0xFFFFFFFFU) {
        psndSFXOff(EX->snd2);
        EX->snd2 = -1;
    }
}
