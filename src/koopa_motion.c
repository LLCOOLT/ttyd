#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "manager/evtmgr.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/types.h>
#include "evt/evt_cam.h"
#include "mario/mario_cam.h"
#include "mario/mario_sbr.h"
#include "koopa.h"
#include "mot/mot_jump.h"
#include "driver/animdrv.h"
#include "koopa_motion.h"

#ifdef VERSION_G8ME01
// US exports this as the global kpa_fall (mot_jump calls it by that name)
#define kpa_fall_80213C38 kpa_fall
#endif

extern s32 kpaFireAttackCheck(void);
extern void kpaClearHitobjRide(void);
extern void kpaCamFollow(void);
extern void kpaSetFallPara(void);
extern f32 marioMakeJumpPara(void);
extern void marioChgMot2(s32 id);
extern void* marioChkLandon(f32* outY, f32 y);
extern void marioChgMotSub(s32 a, s32 b);
f32 kpaStickSpd(s32 dash);

#define MF(m, off) (*(f32*)((u8*)(m) + MWOFF(off)))
#define MI(m, off) (*(s32*)((u8*)(m) + MWOFF(off)))
#define MS16(m, off) (*(s16*)((u8*)(m) + MWOFF(off)))
#define MS8(m, off) (*(s8*)((u8*)(m) + MWOFF(off)))
#define MU(m, off) (*(u32*)((u8*)(m) + MWOFF(off)))
#define MU16(m, off) (*(u16*)((u8*)(m) + MWOFF(off)))
#define MU8(m, off) (*(u8*)((u8*)(m) + MWOFF(off)))
#define MV(m, off) (*(Vec*)((u8*)(m) + MWOFF(off)))
typedef struct V3 {
    s32 a, b, c;
} V3;
#define KPW(m) (*(s32**)((u8*)(m) + MWOFF(0x28C)))

f32 _walkSpdTbl[4] = {0.6f, 1.4f, 1.4f, 1.4f};
f32 _dashSpdTbl[4] = {1.2f, 2.0f, 2.0f, 2.0f};
s32 _rateTbl[4] = {0, 0, 0, 0};
s32 _rateTbl2[4] = {0, 0, 0, 0};
f32 scaleDt[9] = {1.0f, 0.0f, 2.0f, 1.0f, 3.0f, 2.0f, 4.0f, 3.0f, 5.0f};

s32 quake_kpaLandOn_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, -230000000, -229999990, 30, 2, 1,
};

s32 quake_kpaHipAttack_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, -230000000, -229999980, 60, 2, 1,
};

extern void* effMizutamaEntry(s32 type, f32 x, f32 y, f32 z, f32 angle);
extern void* kpaGetHitobjHead2(void);
extern void* kpaChkHitobjRide(void);
void kpaSetSpec(void);

static inline void kpa_hip_launch(MarioWork* m) {
    MI(m, 0x44) = 0x14;
    m->jumpAccelerationY = -0.4744f;
    m->jumpJerkY = 0.4704f;
    m->jumpSnapY = -0.1904f;
    m->jumpVelocityY = m->jumpAccelerationY;
}

static inline s32 kpa_stay_chk(void) {
    MarioWork* m2 = marioGetPtr();
    if (kpaGetStageViewType() == 1) {
        return 0;
    }
    if (!(m2->buttonBuffer & 0x100)) {
        return 0;
    }
    if (kpaGetBodyStatus() == 2) {
        marioChgMot(0x25);
        return 1;
    }
    marioChgMot(3);
    return 1;
}

static inline void kpa_swim_splash(void) {
    MarioWork* m = marioGetPtr();
    s32 st;
    s32 lim;
    KPW(m)[0x150 / 4]++;
    st = MI(m, 0x44);
    if (st == 0x1E || st == 0x1F) {
        if (KPW(m)[0x150 / 4] > 0) {
            f32 rx;
            f32 rz;
            KPW(m)[0x150 / 4] = 0;
            rx = (f32)(irand(40) - 20);
            rz = (f32)(irand(40) - 20);
            effMizutamaEntry(0, m->position.x + rx, 0.6f * m->wPlayerCollisionBox.y + (m->position.y + rz), m->position.z,
                             m->directionView < 180.0f ? 225.0f : 135.0f);
        }
    } else {
        s32 in = FALSE;
        if (st >= 0 && st < 0x14) {
            in = TRUE;
        }
        lim = in ? 10 : 30;
        if (KPW(m)[0x150 / 4] > lim) {
            KPW(m)[0x150 / 4] = 0;
            effMizutamaEntry(0, m->position.x, m->position.y + m->wPlayerCollisionBox.y / 3.0f, m->position.z,
                             m->directionView < 180.0f ? 225.0f : 135.0f);
        }
    }
}

BOOL kpaHipAttackOk(void) {
    MarioWork* m = marioGetPtr();
    if (m->currMotionId == 0x10) {
        return FALSE;
    }
    return ((*(u32*)KPW(m) >> 4) & 1) ^ 1;
}

f32 kpaStickSpd(s32 dash) {
    MarioWork* m = marioGetPtr();
    f32 stick = MS8(m, 0x24E);
    f32 spd;
    f32 max;
    f32 lim = 70.0f;
    f32 k;
    if (stick >= lim) {
        stick = lim;
    }
    lim = 70.0f;
    if (stick <= -lim) {
        stick = -lim;
    }
    spd = MF(m, 0x2C4);
    if (!stick) {
        k = -0.2f;
        if (*(u32*)((u8*)m + MWOFF(0x1F0))) {
            k = -0.7f;
        }
        spd += spd * k;
        if (__fabsf(spd) < 0.01f) {
            spd = 0.0f;
        }
    } else {
        if (dash == 0) {
            max = kpaGetBodyStatus() == 2 ? 0.2f : 1.3f;
        } else {
            max = kpaGetBodyStatus() == 2 ? 0.633f : 2.3f;
        }
        if (stick * spd > 0.0f) {
            spd += 0.002f * stick;
            if (spd >= max) {
                spd = max;
            }
            if (spd <= -max) {
                spd = -max;
            }
        } else {
            spd += 0.002f * stick;
            if (spd >= max) {
                spd = max;
            }
            if (spd <= -max) {
                spd = -max;
            }
        }
    }
    MF(m, 0x2C4) = spd;
    m->baseSpeed = __fabsf(spd);
    {
        f32 a = angleABf(0.0f, 0.0f, spd, 0.0f);
        if (m->baseSpeed) {
            m->directionView = a;
        }
    }
    return m->baseSpeed;
}

void kpa_stay(void) {
    MarioWork* m = marioGetPtr();
    f32 spd;
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0xF0000;
        m->airTimer = 0;
        MI(m, 0x48) = 0;
        MI(m, 0x44) = 0;
        if (kpaGetAttackMode() == 0) {
            if (!(*(u32*)KPW(m) & 0x1000000)) {
                kpaChgPose("KPA_S_1", "KPA2_S_1");
            } else {
                kpaChgPose("KPA_S_2", "KPA2_S_1");
            }
        }
        if (!(m->flags & 0x20)) {
            m->baseSpeed = 0.0f;
        }
    }
    if (kpaGetAttackMode() == 0) {
        s32 r = kpa_stay_chk();
        if (r == 0) {
            if (m->buttonBuffer & 0x200) {
                kpaAttackStart();
            } else {
                if (m->forceMoveTimer == 0) {
                    spd = kpaStickSpd(0);
                } else {
                    spd = m->baseSpeed;
                }
                if (kpaGetStageViewType() == 0) {
                    m->baseSpeed = spd;
                    if (m->baseSpeed > 0.0f) {
                        marioChgMot(1);
                    }
                } else if (m->controlStickSensitivity > 0.0f) {
                    marioChgMot(1);
                }
            }
        }
    }
}

void kpa_walk(void) {
    MarioWork* m = marioGetPtr();
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0xF0000;
        MI(m, 0x44) = 0;
        MI(m, 0x48) = 0;
        if (!(*(u32*)KPW(m) & 0x1000000)) {
            kpaChgPose("KPA_W_1", "KPA2_W_1");
        } else {
            kpaChgPose("KPA_W_2", "KPA2_W_1");
        }
        MS16(m, 0x2A0) = 0;
        MS16(m, 0x2A2) = 0;
        MF(KPW(m), 0x10) = 0.02f;
        MF(KPW(m), 0x14) = -0.02f;
    }
    if (!kpa_stay_chk()) {
        if (m->buttonBuffer & 0x200) {
            kpaAttackStart();
            marioChgMot(0);
            return;
        }
        if (kpaGetBodyStatus() == 2) {
            MU16(m, 0x2A0)++;
            if (MU16(m, 0x2A0) > 0x50) {
                MU16(m, 0x2A0) = 0;
            }
            MU16(m, 0x28) = MU16(m, 0x2A0) / 2;
            animPoseSetLocalTime(m->paperAnimGroupId[marioAnimeId()], (f32)MU16(m, 0x28));
            if (kpaGetBodyStatus() == 0) {
                if (MI(m, 0x48) % 40 == 0) {
                    psndSFXOn_3D((const char*)0x819, &MV(m, 0x8C));
                } else if (MI(m, 0x48) % 20 == 0) {
                    psndSFXOn_3D((const char*)0x818, &MV(m, 0x8C));
                }
                MI(m, 0x48)++;
            }
        } else if (kpaGetBodyStatus() == 0) {
            if (MI(m, 0x48) % 40 == 0) {
                psndSFXOn_3D((const char*)0x819, &MV(m, 0x8C));
            } else if (MI(m, 0x48) % 20 == 0) {
                psndSFXOn_3D((const char*)0x818, &MV(m, 0x8C));
            }
            MI(m, 0x48)++;
        }
    if (m->forceMoveTimer == 0) {
        if (kpaGetStageViewType() == 0) {
            m->baseSpeed = kpaStickSpd(0);
        } else {
            MarioWork* mm = marioGetPtr();
            s32 lv = kpaGetLevel();
            f32 sp = _walkSpdTbl[lv];
            s32 rt = _rateTbl[lv];
            *(s32*)((u8*)KPW(mm) + 0xD0) = rt;
            m->baseSpeed = sp;
        }
    }
    if (kpaGetStageViewType() == 0) {
        if (!m->baseSpeed && !(m->flags & 0x20)) {
            marioChgMot(0);
            return;
        }
    } else {
        if (!m->controlStickSensitivity && !(m->flags & 0x20)) {
            marioChgMot(0);
            return;
        }
    }
    if (!marioKeyOffChk()) {
        marioCamZoomOffReq();
        if (kpaGetStageViewType() == 1) {
            m->directionView = m->controlStickAngle;
        }
        if (MS8(m, 0x24E) * MS8(m, 0x24E) + MS8(m, 0x24F) * MS8(m, 0x24F) > 3025) {
            marioChgMot(2);
        }
    }
    }
}

void kpa_dash(void) {
    MarioWork* m = marioGetPtr();
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0xF0000;
        kpaChgPose("KPA_R_1", "KPA2_R_1");
        MI(m, 0x44) = 0;
        MI(m, 0x48) = 0;
        MS16(m, 0x2A0) = 0;
    }
    if (!kpa_stay_chk()) {
        if (m->buttonBuffer & 0x200) {
            kpaAttackStart();
            marioChgMot(0);
            return;
        }
        if (kpaGetBodyStatus() == 2) {
            MU16(m, 0x2A0)++;
            if (MU16(m, 0x2A0) > 0x50) {
                MU16(m, 0x2A0) = 0;
            }
            MU16(m, 0x28) = MU16(m, 0x2A0) / 2;
            animPoseSetLocalTime(m->paperAnimGroupId[marioAnimeId()], (f32)MU16(m, 0x28));
        }
        if (kpaGetBodyStatus() == 0) {
            if (MI(m, 0x48) % 30 == 0) {
                psndSFXOn_3D((const char*)0x819, &MV(m, 0x8C));
            } else if (MI(m, 0x48) % 15 == 0) {
                psndSFXOn_3D((const char*)0x818, &MV(m, 0x8C));
            }
            MI(m, 0x48)++;
        }
    if (m->forceMoveTimer == 0) {
        if (kpaGetStageViewType() == 0) {
            m->baseSpeed = kpaStickSpd(1);
        } else {
            MarioWork* mm = marioGetPtr();
            s32 lv = kpaGetLevel();
            f32 sp = _dashSpdTbl[lv];
            s32 rt = _rateTbl2[lv];
            *(s32*)((u8*)KPW(mm) + 0xD0) = rt;
            m->baseSpeed = sp;
        }
    }
    if (kpaGetStageViewType() == 0) {
        if (!m->baseSpeed && !(m->flags & 0x20)) {
            marioChgMot(0);
            return;
        }
    } else {
        if (!m->controlStickSensitivity && !(m->flags & 0x20)) {
            marioChgMot(0);
            return;
        }
    }
    if (!marioKeyOffChk()) {
        marioCamZoomOffReq();
        if (kpaGetStageViewType() == 1) {
            m->directionView = m->controlStickAngle;
        }
        if (MS8(m, 0x24E) * MS8(m, 0x24E) + MS8(m, 0x24F) * MS8(m, 0x24F) <= 3025) {
            marioChgMot(1);
        }
    }
    }
}

void kpa_jump(void) {
    MarioWork* m = marioGetPtr();
    f32 prevVy;
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags |= 0x80000;
        MI(m, 0x48) = 2;
        MI(m, 0x44) = 0;
        marioPreJump();
        if (m->currMotionId != 8) {
            camFollowYOff();
        }
        kpaChgPose("KPA_J_1A", "KPA2_J_1A");
        {
        psndSFXOn_3D((const char*)0x81E, &m->position);
        if (m->airTimer == 0) {
            {
                MV(m, 0xD4) = MV(m, 0x8C);
            }
        }
        }
        MS16(m, 0x2A0) = 0;
    }
    m->airTimer++;
    if (m->currMotionId != 8) {
        prevVy = m->jumpVelocityY;
        marioMakeJumpPara();
        if (m->jumpVelocityY > 0.0f && m->airTimer >= 4 && !(MU16(m, 0x246) & 0x100)) {
            m->jumpVelocityY += -0.526f;
        }
        if (m->jumpVelocityY <= 0.0f) {
            if (prevVy > 0.0f) {
                m->jumpPeakAirTime = m->airTimer;
            }
            marioSetPeakYpos();
            kpaSetFallPara();
            marioMakeJumpPara();
            marioChgMot(10);
        }
        m->position.y += m->jumpVelocityY;
    }
}

void kpa_fall_80213C38(void) {
    MarioWork* m = marioGetPtr();
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0x10000;
        m->flags |= 0x20000;
        MI(m, 0x44) = 0;
        if (m->currMotionId != 0xB) {
            if ((s32)MU8(m, 0x3C) == 2) {
                if (!kpaFireAttackCheck()) {
                    kpaChgPose("KPA_J_1B", "KPA2_J_1B");
                }
            } else if (!(m->flags & 0x2000)) {
                marioChgPose("M_J_1C");
            }
        } else {
            m->flags |= 0x80;
        }
        if (m->airTimer == 0) {
            MV(m, 0xD4) = MV(m, 0x8C);
        }
    }
    switch (MI(m, 0x44)) {
    case 0:
        if (m->position.y <= m->lastGroundPos.y) {
            if (m->position.y <= 75.0f) {
                if ((MU(m, 4) |= 0x20000) != 0) {
                    camFollowYOn();
                }
            }
            kpaCamFollow();
            MI(m, 0x44) = 10;
        }
        break;
    }
    m->airTimer++;
    if (kpaGetStageType() == 1 && kpaGetBodyStatus() <= 1) {
        KPW(m)[0] |= 0x100;
    }
    if (kpaGetBodyStatus() == 2) {
        m = marioGetPtr();
        if (m->currMotionId != 0x25) {
            marioChgMot2(0x25);
        }
        kpaClearHitobjRide();
        m->flags &= ~0x10000;
        m->flags |= 0x20000;
        MI(m, 0x44) = 0x1E;
        m->airTimer = 0;
        MI(m, 0x48) = 0;
        m->baseSpeed = 0.0f;
        MF(m, 0x2C4) = 0.0f;
    }
}

void kpa_hip(void) {
    MarioWork* m = marioGetPtr();
    f32 fall;
    f32 y;
    void* hit;
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0x80000;
        psndSFXOn_3D((const char*)0x81F, &MV(m, 0x8C));
        marioAdjustMoveDir();
        MI(m, 0x44) = 10;
        MI(m, 0x48) = 6;
        m->jumpVelocityY = 0.0f;
        m->jumpAccelerationY = 0.0f;
        m->jumpJerkY = 0.0f;
        m->jumpSnapY = 0.0f;
        m->baseSpeed = 0.0f;
        marioChgPose("KPA2_J_1C");
    }
    if (MF(m, 0xD8) >= m->position.y && (MU(m, 4) & 0x20000)) {
        camFollowYOn();
    }
    switch (MI(m, 0x44)) {
    case 10:
        marioChkLandon(&y, 0.0f);
        if (--MI(m, 0x48) <= 0) {
            kpa_hip_launch(m);
        } else {
            break;
        }
    case 20:
        fall = marioGetFallSpd();
        hit = marioChkLandon(&y, fall);
        if (fall < -100.0f) {
            fall = -100.0f;
            m->jumpAccelerationY = m->jumpJerkY = m->jumpSnapY = 0.0f;
            m->jumpVelocityY = fall;
        }
        if (hit) {
            MI(m, 0x1E4) = (s32)hit;
            MI(m, 0x1E8) = 0;
            m->currMotionId = 0x11;
            MI(m, 0x44) = 0x15;
            MI(m, 0x48) = 0x14;
            m->position.y = y;
            psndSFXOn_3D((const char*)0x820, &MV(m, 0x8C));
            evtEntry(quake_kpaHipAttack_evt, 0, 0);
            m->airTimer = 0;
            m->jumpPeakAirTime = 0;
        } else {
            m->position.y += fall;
        }
        break;
    case 21:
        if (--MI(m, 0x48) <= 0) {
            if (m->position.y > 75.0f) {
                camFollowYOn();
            }
            if ((MU16(m, 0x246) & 0x100) && !*(u32*)((u8*)m + MWOFF(0x1E4))) {
                kpa_hip_launch(m);
            } else {
                m->flags &= ~0x80;
                marioChgMotSub(0, 0);
            }
        }
        break;
    }
}

BOOL kpaPowUp(void) {
    MarioWork* m = marioGetPtr();
    if (kpaGetLevel() < 3) {
        KPW(m)[1]++;
        kpaCancelAttackMode();
        marioChgMot(0x26);
        return TRUE;
    }
    kpaMSetMutekiTimer();
    kpaMutekiOn();
    return FALSE;
}

BOOL kpaPowDown(void) {
    MarioWork* m = marioGetPtr();
    kpaCancelAttackMode();
    if (kpaGetLevel() > 0) {
        KPW(m)[1]--;
        MS16(m, 0x78) = sysMsec2Frame(3000);
        marioChgMot(0x27);
        return TRUE;
    }
    KPW(m)[0] |= 0x10000000;
    return FALSE;
}

void kpaSetSpec(void) {
    MarioWork* m = marioGetPtr();
    s32 lv;
    m->wPlayerCollisionBox.x = kpaGetWidth(KPW(m)[1]);
    lv = KPW(m)[1];
    if (lv == 0) {
        m->wPlayerCollisionBox.y = 24.0f;
    } else if (lv == 1) {
        m->wPlayerCollisionBox.y = 74.0f;
    } else if (lv == 2) {
        m->wPlayerCollisionBox.y = 103.6f;
    } else if (lv == 3) {
        m->wPlayerCollisionBox.y = 222.0f;
    }
}

void kpa_powup(void) {
    MarioWork* m = marioGetPtr();
    MarioWork* m2;
    f32 step;
    f32 base;
    s32 lv;
    f32 k;
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0xF0000;
        m->airTimer = 0;
        MI(m, 0x48) = 0;
        kpaChgPose("KPA_Y_1", "KPA2_Y_1");
        MI(m, 0x44) = 0;
        if (!(m->flags & 0x20)) {
            m->baseSpeed = 0.0f;
        }
        m->flags |= 0x10000000;
        psndSFXOn_3D((const char*)0x111, &MV(m, 0x8C));
    }
    lv = kpaGetLevel();
    if (lv <= 3) {
        base = kpaGetBaseScale(lv - 1);
        step = (kpaGetBaseScale(lv) - base) / 5.0f;
    } else {
        marioChgMot(0);
        return;
    }
    switch (MI(m, 0x44)) {
    case 0:
        MI(m, 0x48) = 5;
        MI(m, 0x44) = 1;
        psndSFXOn_3D((const char*)0x823, &MV(m, 0x8C));
        break;
    default:
        if (--MI(m, 0x48) > 0) {
            break;
        }
        k = (scaleDt - 1)[MI(m, 0x44)];
        MI(m, 0x48) = 5;
        m->scale.x = step * k + base;
        m->scale.y = m->scale.x;
        MI(m, 0x44)++;
        if (5.0f == k) {
            m2 = marioGetPtr();
            if (KPW(m2)[1] == 3) {
                kpaMSetMutekiTimer();
                kpaMutekiOn();
            }
            kpaSetSpec();
            marioResetCamShiftRate();
            m2->camShiftTargetX = 20.0f * (f32)(-KPW(m2)[1]);
            m->flags &= ~0x10000000;
            marioChgMot(0);
            m->unk4C = 0;
        }
    }
}

void kpa_powdown(void) {
    MarioWork* m = marioGetPtr();
    MarioWork* m2;
    f32 step;
    f32 base;
    s32 lv;
    f32 k;
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0xF0000;
        m->airTimer = 0;
        MI(m, 0x48) = 0;
        kpaChgPose("KPA_D_1", "KPA2_D_1");
        MI(m, 0x44) = 0;
        if (!(m->flags & 0x20)) {
            m->baseSpeed = 0.0f;
        }
        m->flags |= 0x10000000;
        psndSFXOn_3D((const char*)0x11D, &MV(m, 0x8C));
    }
    lv = kpaGetLevel();
    if (lv >= 0) {
        base = kpaGetBaseScale(lv + 1);
        step = (base - kpaGetBaseScale(lv)) / 5.0f;
    } else {
        marioChgMot(0);
        return;
    }
    switch (MI(m, 0x44)) {
    case 0:
        MI(m, 0x48) = 5;
        MI(m, 0x44) = 1;
        psndSFXOn_3D((const char*)0x824, &MV(m, 0x8C));
        break;
    default:
        if (--MI(m, 0x48) > 0) {
            break;
        }
        k = (scaleDt - 1)[MI(m, 0x44)];
        MI(m, 0x48) = 5;
        m->scale.x = base - step * k;
        m->scale.y = m->scale.x;
        MI(m, 0x44)++;
        if (5.0f == k) {
            m2 = marioGetPtr();
            kpaMutekiOff();
            kpaSetSpec();
            marioResetCamShiftRate();
            m2->camShiftTargetX = 20.0f * (f32)(-KPW(m2)[1]);
            m->flags &= ~0x10000000;
            marioChgMot(0);
        }
    }
}

#pragma dont_inline on
void kpaSwimMove(void) {
    MarioWork* m = marioGetPtr();
    f32 spd = MF(m, 0x2C4);
    f32 stick = MS8(m, 0x24E);
    f32 f31;
    f32 lim = 40.0f;
    f32 rate = 0.01f;
    if (stick) {
        if (stick * spd < 0.0f) {
            spd = 0.0f;
        }
        if (spd * spd <= 1225.0f) {
            spd += stick * rate;
        } else {
            spd += stick * rate;
            if (spd < -lim) {
                spd = -lim;
            }
            lim = 40.0f;
            if (spd > lim) {
                spd = lim;
            }
        }
    }
    MF(m, 0x2C4) = spd;
    f31 = 0.06f * __fabsf(spd);
    if (f31 >= 2.0f) {
        f31 = 2.0f;
    }
    {
        f32 a = angleABf(0.0f, 0.0f, spd, 0.0f);
        if (f31 < 0.01f) {
            f31 = 0.0f;
        }
        m->baseSpeed = f31;
        if (f31) {
            m->directionView = a;
        }
    }
    MF(m, 0x18C) = f31;
}

#pragma dont_inline reset

void kpa_swim(void) {
    MarioWork* m = marioGetPtr();
    f32 v;
    if (m->trigFlags & 1) {
        m->trigFlags &= ~1;
        m->flags &= ~0xF0000;
        m->airTimer = 0;
        MI(m, 0x48) = 0;
        MI(m, 0x44) = 0;
        m->baseSpeed = 0.0f;
        MF(m, 0x2C4) = 0.0f;
        KPW(marioGetPtr())[0] |= 0x10;
    }
    if (m->buttonBuffer & 0x200) {
        kpaAttackStart2();
    }
    if (kpaFireAttackCheck() == 1) {
        MS8(m, 0x24E) = 0;
        MS8(m, 0x24F) = 0;
    } else if (kpaGetBodyStatus() == 2 && (m->buttonBuffer & 0x100)) {
        s32 st = MI(m, 0x44);
        if (st >= 0 && st <= 1 && m->position.y < 280.0f) {
            MI(m, 0x44) = 0;
        } else if (st >= 0x1E && st <= 0x20) {
            MI(m, 0x44) = 0;
        }
    }
    kpaSwimMove();
    kpa_swim_splash();
    switch (MI(m, 0x44)) {
    case 0:
        if (*(u32*)((u8*)m + MWOFF(0x1E4)) != 0) {
            m->jumpVelocityY = 1.0f;
            m->jumpAccelerationY = 0.0f;
            m->jumpJerkY = 0.0f;
            m->jumpSnapY = -0.0001f;
        } else {
            m->jumpVelocityY = 1.52f;
            m->jumpAccelerationY = 0.005f;
            m->jumpJerkY = 0.006f;
            m->jumpSnapY = -0.0008f;
        }
        kpaClearHitobjRide();
        MI(m, 0x44) = 1;
        m->flags &= ~0x20000;
        m->flags |= 0x10000;
        psndSFXOn_3D((const char*)"SFX_KUPPA_SWIM1", &MV(m, 0x8C));
        if (kpaGetAttackMode() == 0) {
            kpaChgPose("KPA_W_1", "KPA2_W_2");
        }
    case 1:
        if (kpaGetHitobjHead2()) {
            MI(m, 0x44) = 0x1E;
            m->jumpVelocityY += 0.02f * (-2.0f - m->jumpVelocityY);
            m->jumpAccelerationY = 0.0f;
            m->jumpJerkY = 0.0f;
            m->jumpSnapY = 0.0f;
            break;
        }
        v = marioMakeJumpPara();
        m->position.y += v;
        if (m->position.y + m->wPlayerCollisionBox.y >= 370.0f) {
            if (v < 0.0f) {
                MI(m, 0x44) = 0x28;
            }
#ifndef VERSION_G8ME01
            m->jumpVelocityY += 0.02f * (-2.0f - m->jumpVelocityY);
            m->jumpAccelerationY = 0.0f;
            m->jumpJerkY = 0.0f;
            m->jumpSnapY = 0.0f;
#endif
        } else if (v < 0.0f) {
            MI(m, 0x44) = 0x1E;
        }
        break;
    case 10:
        kpaClearHitobjRide();
        m->jumpVelocityY = 2.0f;
        m->jumpAccelerationY = -0.03f;
        m->jumpJerkY = 0.0f;
        m->jumpSnapY = 0.0f;
        MI(m, 0x44) = 0xB;
        m->flags &= ~0x20000;
        m->flags |= 0x10000;
        if (kpaGetAttackMode() == 0) {
            kpaChgPose("KPA_W_1", "KPA2_W_2");
        }
    case 11:
        v = marioMakeJumpPara();
        m->position.y += v;
        if (kpaGetBodyStatus() == 1) {
            m->jumpVelocityY += 0.06f * (-2.0f - m->jumpVelocityY);
            m->jumpAccelerationY = 0.0f;
            m->jumpJerkY = 0.0f;
            m->jumpSnapY = 0.0f;
            if (v < 0.0f) {
                MI(m, 0x44) = 0x28;
            }
        } else if (v < 0.0f) {
            MI(m, 0x44) = 0x1E;
        }
        break;
    case 20:
        KPW(m)[0] |= 0x100;
        m->flags &= ~0x20000;
        m->flags |= 0x10000;
        kpaChgPose("KPA_J_1A", "KPA2_J_1A");
        psndSFXOn_3D((const char*)"SFX_KUPPA_WATER_UP1", &MV(m, 0x8C));
        m->jumpVelocityY = 5.0f;
        m->jumpAccelerationY = -0.13f;
        m->jumpJerkY = 0.0f;
        m->jumpSnapY = -0.001f;
        MI(m, 0x44) = 0x15;
    case 21:
        v = marioMakeJumpPara();
        m->position.y += v;
        if (v <= 0.5f) {
            m->flags &= ~0xF0000;
            kpaSetFallPara();
            marioMakeJumpPara();
            marioChgMot(10);
            return;
        }
        break;
    case 22:
        break;
    }
    switch (MI(m, 0x44)) {
    case 0x1E:
        if (KPW(m)[0] & 0x100) {
            KPW(m)[0] &= ~0x100;
            psndSFXOn_3D((const char*)0x827, &MV(m, 0x8C));
        }
        if (kpaGetAttackMode() == 0) {
            kpaChgPose("KPA_W_1", "KPA2_Z_2");
        }
        m->flags &= ~0x10000;
        m->flags |= 0x20000;
        if (m->jumpVelocityY < 0.0f) {
            MI(m, 0x44) = 0x1F;
        } else {
            m->jumpVelocityY = -0.08f;
            m->jumpAccelerationY = -0.03f;
            m->jumpJerkY = 0.009f;
            m->jumpSnapY = 0.0f;
            MI(m, 0x44) = 0x20;
        }
        kpa_swim_splash();
        if (marioBgmodeChk() != 1) {
            camFollowYOn();
        }
        break;
    case 0x1F: {
        f32 d = (2.0f - m->jumpVelocityY) * (f32)(kpaGetBodyStatus() == 2);
        if (d) {
            d = 2.6f;
        } else {
            d = 0.21f;
        }
        m->jumpVelocityY += d;
        m->jumpAccelerationY = 0.0f;
        m->jumpJerkY = 0.0f;
        m->jumpSnapY = 0.0f;
        if (m->jumpVelocityY >= 0.0f) {
            m->jumpVelocityY = -0.08f;
            m->jumpAccelerationY = -0.03f;
            m->jumpJerkY = 0.009f;
            m->jumpSnapY = 0.0f;
            MI(m, 0x44) = 0x20;
        }
        if (kpaChkHitobjRide()) {
            MF(m, 0x2C4) = 0.0f;
            m->baseSpeed = 0.0f;
        }
        kpa_swim_splash();
        break;
    }
    case 0x20:
        if (kpaChkHitobjRide()) {
            MF(m, 0x2C4) = 0.0f;
            m->baseSpeed = 0.0f;
        }
        break;
    case 0x28:
        if (kpaGetAttackMode() == 0) {
            kpaChgPose("KPA_W_1", "KPA2_Z_2");
        }
        m->flags &= ~0x10000;
        m->flags |= 0x20000;
        m->jumpVelocityY = -0.283f;
        m->jumpAccelerationY = -0.023f;
        m->jumpJerkY = 0.01f;
        m->jumpSnapY = -0.001f;
        MI(m, 0x44) = 0x29;
        MI(m, 0x48) = 0x18;
    case 0x29:
        if ((m->buttonBuffer & 0x100) && !kpaFireAttackCheck()) {
            MI(m, 0x44) = 0x14;
        } else {
            MI(m, 0x48) = MI(m, 0x48) - 1;
            if (MI(m, 0x48) <= 0) {
                MI(m, 0x44) = 0x1E;
            }
        }
        break;
    }
}

void quake_kpaLandOn(void) {
    MarioWork* m = marioGetPtr();
    if (kpaGetStageType() != 1) {
        psndSFXOn_3D((const char*)0x81D, (Vec*)((u8*)m + 0x8C));
        if (kpaGetLevel() >= 2) {
            evtEntry(quake_kpaLandOn_evt, 0, 0);
        }
    }
}

void quake_kpaHipAttack(void) {
    evtEntry(quake_kpaHipAttack_evt, 0, 0);
}
