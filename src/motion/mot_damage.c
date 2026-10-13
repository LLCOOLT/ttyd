#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "driver/npcdrv.h"
#include "manager/evtmgr.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_pouch.h"
#include "mario/mario_sbr.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

extern s32 evt_cam_shake[];
extern s32 evt_gazigazi_appear[];

EffectEntry* effSplashEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
HitEntry* marioChkLandon(f32* outY, f32 y);
f32 marioGetFallSpd(void);
void marioClearSlitFloor(void);
void marioSlitForceCancel(void);
void marioYoshiForceCancel(void);
void unk_800cd9a0(void);
void bomhei_use_cancel2(void);
void mario_simple_kemuri(void);
void marioSetFallPara(void);
void marioMakeJumpPara(void);

#define MF(o) (*(f32*)((u8*)mario + (o)))
#define MI(o) (*(s32*)((u8*)mario + (o)))

static s32 quake_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, (s32)0xF24A7A8A, (s32)0xF24A7A80, 0x32, 2, 1,
};

static s32 quake_bgmode_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, (s32)0xF24A7A86, (s32)0xF24A7A80, 0x1E, 2, 1,
};

s32 gazigazi(EventEntry* evt, BOOL isFirstCall);

s32 evt_gazigazi[] = {
    0x0001005B, (s32)gazigazi, 0x0001005C, (s32)evt_gazigazi_appear, 2, 1,
};

void marioDmgRetQuakeOn(void) {
    s32* evt;
    if (marioBgmodeChk() == 0) {
        evt = quake_evt;
    } else {
        evt = quake_bgmode_evt;
    }
    evtEntry(evt, 0, 0);
}

void marioSetSplash(s32 kind, Vec* pos) {
    if (kind == 0) {
        psndSFXOn_3D((char*)0x194, pos);
    }
    if (marioBgmodeChk() != 1) {
        effSplashEntry(kind != 0, pos->x, pos->y, pos->z, 1.0f);
    }
    if (kind == 1) {
        psndSFXOn_3D((char*)0xBA, pos);
    }
}

s32 gazigazi(EventEntry* evt, BOOL isFirstCall) {
    MarioWork* mario = marioGetPtr();
    evt->lwData[0] = (s32)mario->position.x;
    evt->lwData[1] = (s32)MF(0x2A0);
    evt->lwData[2] = (s32)mario->position.z;
    return 2;
}

BOOL marioChkDamageSink(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_DAMAGE && (s32)mario->currSubMotionId >= 0 && (s32)mario->currSubMotionId < 10) {
        return TRUE;
    }
    return FALSE;
}

void set_damage_root_ypos(f32 y) {
    MarioWork* mario = marioGetPtr();
    MF(0x2A0) = y;
}

void mot_damage(void) {
    MarioWork* mario = marioGetPtr();
    Vec dest;
    f32 d;

    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        if (MF(0x7C) == 0.0f) {
            MF(0x7C) = -6.0f;
            MF(0x80) = 0.0f;
            MF(0x84) = 0.0f;
            MF(0x88) = 0.0f;
        }
        marioClearSlitFloor();
        marioOfsRotReset();
        mario->dispFlags &= ~0x100;
        marioAdjustMoveDir();
        marioSlitForceCancel();
        bomhei_use_cancel2();
        marioNoUpdateCamPos();
        if (mario->characterId == 2) {
            marioChgPose("KPA_D_1");
        } else {
            marioChgEvtPose("M_F_1");
        }
        mario->currSubMotionId = 0;
        mario->airTimer = 0;
        MF(0x180) = 0.0f;
        mario->multiTimer = 20;
        if (mario->prevMotionId != MARIO_MOTION_YOSHI && mario->prevMotionId != MARIO_MOTION_PLANE) {
            Vec pos = mario->position;
            marioSetSplash(0, &pos);
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            mario->field_0x98 = v;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            mario->field_0xA4 = v;
        }
        npcStopForEvent();
    }

    switch (mario->currSubMotionId) {
    case 0:
        if (MF(0x90) >= MF(0x2A0) - 160.0f) {
            marioMakeJumpPara();
            if (MF(0x7C) <= -6.0f) {
                MF(0x7C) = -6.0f;
                MF(0x80) = 0.0f;
                MF(0x84) = 0.0f;
                MF(0x88) = 0.0f;
            }
            MF(0x90) += MF(0x7C);
        } else {
            MF(0x7C) = 0.3f;
            mario->currSubMotionId = 1;
            mario->multiTimer = 40;
        }
        break;
    case 1:
        if (--MI(0x48) > 0) {
            break;
        }
        MI(0x48) = 0;
        mario->currSubMotionId = 10;
        MF(0x2AC) = 20.0f;
        break;
    case 10:
        if (++MI(0x48) == 2) {
            mario->currSubMotionId = 11;
            psndSFXOn_3D((char*)0x195, &mario->position);
            if (mario->damageHit != NULL) {
                evtEntry(evt_gazigazi, 0, 0);
            }
        }
    case 11: {
        f32 v;
        f32 prevY = MF(0x90);
        v = MF(0x2AC);
        MF(0x90) += v;
        v -= 1.0f;
        if (v < 10.0f) {
            v = 10.0f;
        }
        MF(0x2AC) = v;
        if (MF(0x90) >= MF(0x2A0) && MF(0x2A0) > prevY) {
            Vec pos = mario->position;
            marioSetSplash(1, &pos);
        }
        if (MF(0x90) < 500.0f + MF(0x2A0)) {
            break;
        }
        {
            if (mario->damageHit != NULL) {
                Vec* p = hitGetDamageReturnPos((HitEntry*)mario->damageHit);
                Vec t = {0.0f, 0.0f, 0.0f};
                t.x = p->x;
                t.y = p->y;
                t.z = p->z;
                dest = t;
            } else {
                Vec z = {0.0f, 0.0f, 0.0f};
                dest = z;
                if (strcmp(gp->currentMapName, "muj_00") == 0) {
                    Vec a = {400.0f, 35.0f, -100.0f};
                    dest = a;
                }
                if (strcmp(gp->currentMapName, "gor_00") == 0) {
                    Vec a = {0.0f, 0.0f, -200.0f};
                    dest = a;
                }
                if (strcmp(gp->currentMapName, "gor_04") == 0) {
                    Vec a = {146.0f, 0.0f, 146.0f};
                    dest = a;
                }
            }
            if (mario->flags & MARIO_FLAG_BG_MODE) {
                Vec t = {0.0f, 0.0f, 0.0f};
                t.x = MF(0xE0);
                t.y = MF(0xE4);
                t.z = MF(0xE8);
                dest = t;
            }
            MF(0x180) = 8.0f;
            d = distABf(dest.x, dest.z, mario->position.x, mario->position.z);
            mario->multiTimer = (s16)(d / 8);
            MF(0x1A0) = angleABf(mario->position.x, mario->position.z, dest.x, dest.z);
            MF(0x2A8) = (dest.y - MF(0x2A0)) / (f32)MI(0x48);
            mario->currSubMotionId = 12;
            mario->dispFlags |= 1;
            if (MI(0x48) == 0) {
                MI(0x48) = 10;
                MF(0x2A8) = (dest.y - MF(0x2A0)) / (f32)MI(0x48);
                mario->currSubMotionId = 14;
            }
        }
        break;
    }
    case 12:
        MF(0xF0) += MF(0x2A8);
        movePos(&mario->position.x, &mario->position.z, MF(0x180), MF(0x1A0));
        MF(0xEC) = mario->position.x;
        MF(0xF4) = mario->position.z;
        if (--MI(0x48) > 0) {
            break;
        }
        mario->currSubMotionId = 13;
        mario->flags |= 0x80;
        marioSetFallPara();
        mario->dispFlags &= ~1;
        MI(0x48) = 1;
        break;
    case 13:
        if (--MI(0x48) > 0) {
            break;
        }
        mario->currSubMotionId = 20;
        break;
    case 14:
        MF(0xF0) += MF(0x2A8);
        MF(0xEC) = mario->position.x;
        MF(0xF4) = mario->position.z;
        if (--MI(0x48) > 0) {
            break;
        }
        mario->flags |= 0x80;
        marioSetFallPara();
        mario->dispFlags &= ~1;
        mario->currSubMotionId = 20;
        break;
    case 20: {
        HitEntry* h;
        f32 landY;
        f32 spd; f32 baseY;

        mario->hitobjStandOn = NULL;
        spd = marioGetFallSpd();
        if (spd <= -10.0f) {
            spd = -10.0f;
        }
        baseY = mario->damageHit != NULL ? hitGetDamageReturnPos((HitEntry*)mario->damageHit)->y : mario->position.y;
        if (marioBgmodeChk() == 1 || mario->position.y - baseY <= 50.0f) {
            h = marioChkLandon(&landY, spd);
        } else {
            h = NULL;
        }
        if (h == NULL) {
            mario->position.y += spd;
        } else {
            mario->hitobjStandOn = h;
            mario->hitobjJumpFrom = NULL;
            mario->position.y = landY;
            if (mario->characterId == 2) {
                marioChgPose("KPA_D_2");
            } else {
                marioChgPose("M_D_2");
            }
            marioDmgRetQuakeOn();
            psndSFXOn_3D((char*)0xCB, &mario->position);
            psndSFXOn_3D((char*)0x197, &mario->position);
            mario_simple_kemuri();
        }
        if (mario->hitobjStandOn == NULL) {
            break;
        }
    }
    case 30:
        mario->multiTimer = 50;
        mario->currSubMotionId = 31;
    case 31:
        if (--MI(0x48) > 0) {
            break;
        }
        if (mario->characterId == 0) {
            pouchAddHP(-1);
        }
        if (((s32(*)(void))pouchGetHP)() <= 0) {
            mario->currSubMotionId = 33;
            marioUpdateCamPos();
            break;
        }
        if (mario->characterId != 2) {
            marioChgPose("M_U_3");
        }
        mario->multiTimer = 12;
        mario->currSubMotionId = 32;
    case 32:
        if (--MI(0x48) > 0) {
            break;
        }
        marioChgMot(MARIO_MOTION_STAY);
        marioUpdateCamPos();
        npcStartForEvent();
        break;
    }
}

BOOL marioWaitDamageReturnFall(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId != MARIO_MOTION_DAMAGE) {
        return -1;
    }
    if ((s32)mario->currSubMotionId >= 20) {
        f32 x, y, z;
        Vec pos = mario->position;
        marioGetScreenPos(pos, &x, &y, &z);
        if (marioChkInScreen((s32)x, (s32)y)) {
            return TRUE;
        }
    }
    return FALSE;
}

void mot_damageToge(void) {
    MarioWork* mario = marioGetPtr();
    Vec dest;
    f32 d;

    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        marioClearSlitFloor();
        mario->dispFlags &= ~0x100;
        marioAdjustMoveDir();
        marioSlitForceCancel();
        marioYoshiForceCancel();
        unk_800cd9a0();
        marioNoUpdateCamPos();
        bomhei_use_cancel2();
        mario->currSubMotionId = 0;
        mario->airTimer = 0;
        MF(0x180) = 0.0f;
        MF(0x2A0) = MF(0x90);
        mario->multiTimer = 5;
        MF(0x2AC) = 4.0f;
    }

    switch (mario->currSubMotionId) {
    case 0:
        if (--MI(0x48) > 0) {
            break;
        }
        if (mario->prevMotionId == MARIO_MOTION_HIP || mario->prevMotionId == MARIO_MOTION_HIP_2) {
            marioChgEvtPose("M_D_7");
        } else {
            marioChgPose("M_D_6");
        }
        psndSFXOn_3D((char*)0xBA, &mario->position);
        mario_simple_kemuri();
        mario->currSubMotionId = 11;
    case 11: {
        f32 v = MF(0x2AC);
        MF(0x90) += v;
        v -= 1.0f;
        if (v < 10.0f) {
            v = 10.0f;
        }
        MF(0x2AC) = v;
        if (MF(0x90) < 500.0f + MF(0x2A0)) {
            break;
        }
        {
            if (mario->damageHit != NULL) {
                Vec* p = hitGetDamageReturnPos((HitEntry*)mario->damageHit);
                Vec t = {0.0f, 0.0f, 0.0f};
                t.x = p->x;
                t.y = p->y;
                t.z = p->z;
                dest = t;
            } else {
                Vec z = {0.0f, 0.0f, 0.0f};
                dest = z;
            }
            MF(0x180) = 8.0f;
            d = distABf(dest.x, dest.z, mario->position.x, mario->position.z);
            mario->multiTimer = (s16)(d / 8);
            MF(0x1A0) = angleABf(mario->position.x, mario->position.z, dest.x, dest.z);
            MF(0x2A8) = (dest.y - MF(0x2A0)) / (f32)MI(0x48);
            mario->currSubMotionId = 12;
        }
        break;
    }
    case 12:
        MF(0xF0) += MF(0x2A8);
        movePos(&mario->position.x, &mario->position.z, MF(0x180), MF(0x1A0));
        MF(0xEC) = mario->position.x;
        MF(0xF4) = mario->position.z;
        if (--MI(0x48) > 0) {
            break;
        }
        mario->currSubMotionId = 13;
        mario->flags |= 0x80;
        marioSetFallPara();
        break;
    case 13:
        if (--MI(0x48) > 0) {
            break;
        }
        mario->currSubMotionId = 20;
        break;
    case 20: {
        f32 spd;
        HitEntry* h;
        f32 landY;
        mario->hitobjStandOn = NULL;
        spd = marioGetFallSpd();
        if (spd <= -10.0f) {
            spd = -10.0f;
        }
        h = marioChkLandon(&landY, spd);
        if (h == NULL) {
            mario->position.y += spd;
        } else {
            marioChgPose("M_D_2");
            marioDmgRetQuakeOn();
            psndSFXOn_3D((char*)0xCB, &mario->position);
            psndSFXOn_3D((char*)0x197, &mario->position);
            mario_simple_kemuri();
            mario->hitobjStandOn = h;
            mario->hitobjJumpFrom = NULL;
            mario->position.y = landY;
        }
        if (mario->hitobjStandOn == NULL) {
            break;
        }
    }
    case 30:
        mario->multiTimer = 50;
        mario->currSubMotionId = 31;
    case 31:
        if (--MI(0x48) > 0) {
            break;
        }
        pouchAddHP(-1);
        if (((s32(*)(void))pouchGetHP)() <= 0) {
            mario->currSubMotionId = 33;
            marioUpdateCamPos();
            break;
        }
        marioChgPose("M_U_3");
        mario->multiTimer = 12;
        mario->currSubMotionId = 32;
    case 32:
        if (--MI(0x48) > 0) {
            break;
        }
        marioChgMot(MARIO_MOTION_STAY);
        marioUpdateCamPos();
        break;
    }
}

BOOL marioWaitDamageTogeReturnFall(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId != MARIO_MOTION_DAMAGE_TOGE) {
        return -1;
    }
    if ((s32)mario->currSubMotionId >= 20) {
        f32 x, y, z;
        Vec pos = mario->position;
        marioGetScreenPos(pos, &x, &y, &z);
        if (marioChkInScreen((s32)x, (s32)y)) {
            return TRUE;
        }
    }
    return FALSE;
}
