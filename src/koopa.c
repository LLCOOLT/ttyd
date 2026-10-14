#include "mario/mario.h"
#include "mario/mariost.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include "memory.h"
#include <string.h>

void kpaSetSpec(void);
void kpa2DMain(void);
void kpa3DMain(void);
void marioChgMot(s32);
void psndSFXOff(s32);
void marioResetCamFollowRate(void);
void camFollowYOff(void);
void camFollowYOn(void);
void marioPreJump(void);
void marioMakeJumpPara(void);
void marioSetPeakYpos(void);
void marioBottomless(void);
void marioPreDisp(void);
void marioBalloonMain(void);
void mario_kemuri_80130474(void);
void partyMain(void);
void marioCamMain(void);
void marioSetFallPara(void);
void marioChkOverhead(void);
void marioChkGnd(void);
void marioChkGnd2(void);
void marioBoots(void);
void marioForceMoveMain(void);
void marioMove(void);
void marioCheckWall(f32, f32);
void* kpaHitCheck(void);
void kpaSearchFrontUnder(void);
void kpaFireAttack(void);
void kpaFireMain(void);
void kpaFall(void);
void* kpaFlameHitCheck(f32, f32, f32, f32);
const f32 vec3_802fc920[3] = {0.0f, 0.0f, 0.0f};
extern f32 marioJumpData[];
void kpaClearHitobjRide(void);
void* kpaChkHitobjRide(void);
f32 marioGetFallSpd(void);
void* marioChkLandon(f32* outY, f32 y);
void marioLandOn(void);
s32 hitGetAttr(void* hit);
s32 marioKeyOffChk(void);
s32 marioCtrlOffChk(void);

#define MU32(m, off) (*(u32*)((u8*)(m) + (off)))
#define MF(m, off) (*(f32*)((u8*)(m) + (off)))
#define KPW(m) (*(u8**)((u8*)(m) + 0x28C))

f32 kpaWidthDat[4] = {20.0f, 60.0f, 84.0f, 186.0f};
f32 baseScaleTbl[4] = {0.3f, 1.0f, 1.4f, 3.1f};
s32 kpaPauseSeTable[28] = {0x10C, 0x10D, 0x10E, 0x10F, 0x111, 0x112, 0x113, 0x114, 0x116, 0x117,
                           0x118, 0x119, 0x11B, 0x11E, 0x11F, 0x120, 0x122, 0x123, 0x124, 0x125,
                           0x127, 0x128, 0x129, 0x12A, 0x12C, 0x12D, 0x12E, 0x12F};
static u8* fireefp;
static u8* fireefp_pad;
s32 kpaGetLevel(void);
f32 kpaGetBaseScale(s32 lv);
u8* effGonbabaBreathEntry(s32 type, s32 life, f32 x, f32 y, f32 z, f32 scale);

static inline void kpaFireEntry2(Vec pos) {
    MarioWork* mp = marioGetPtr();
    if (fireefp == NULL) {
        s32 flag = 0;
        s32 ang;
        f32 dir;
        f32 scale;
        f32 x;
        f32 y;
        f32 z;
        f32 sz;
        s32 type;
        u8* child;
        s32 t;
        dir = (mp->unk1A8 >= 90.0f && mp->unk1A8 <= 270.0f) ? 1.0f : -1.0f;
        scale = kpaGetBaseScale(kpaGetLevel());
        x = 40.0f * dir * scale + pos.x;
        t = (MU32(marioGetPtr(), 0x14) & 1) ^ 1;
        y = pos.y + (20.0f * scale + (t == 1 ? 6.0f : 0.0f));
        z = pos.z;
        type = 7;
        sz = 0.4f;
        switch (MU32(KPW(mp), 4)) {
        case 0:
            sz = 0.3f;
            break;
        case 1:
            sz = 1.0f;
            break;
        case 2:
            sz = 1.4f;
            break;
        case 3:
            sz = 1.5f;
            type = 0;
            break;
        }
        fireefp = effGonbabaBreathEntry(type, 0, x, y, z, sz);
        flag = 0;
        if (mp->unk1AC >= 90.0f && mp->unk1AC <= 270.0f) {
            flag = 1;
        }
        MF(*(u8**)(fireefp + 0xC), 0x48) = (f32)(flag ? 180 : 0);
        child = *(u8**)(*(u8**)(fireefp + 0xC) + 0x4C);
        if (child) {
            flag = 0;
            if (mp->unk1AC >= 90.0f && mp->unk1AC <= 270.0f) {
                flag = 1;
            }
            ang = flag ? 180 : 0;
            MF(*(u8**)(child + 0xC), 0x48) = ang;
        }
    }
}

static inline void kpaFireEntry(Vec pos) {
    MarioWork* mp = marioGetPtr();
    kpaFireEntry2(pos);
}
static inline void kpaFireSEOn(void) {
    MarioWork* mp = marioGetPtr();
    if (*(u32*)(KPW(mp) + 0x14C) == 0xFFFFFFFFU) {
        *(s32*)(KPW(mp) + 0x14C) = psndSFXOn_3D((const char*)0x821, &mp->position);
        psndSFXOn_3D((const char*)0x131, &mp->position);
    }
}

static inline void kpaFireSEOff(void) {
    MarioWork* mp = marioGetPtr();
    if (*(u32*)(KPW(mp) + 0x14C) != 0xFFFFFFFFU) {
        psndSFXOff(*(s32*)(KPW(mp) + 0x14C));
        *(s32*)(KPW(mp) + 0x14C) = -1;
    }
}


u8* getKoopaFireEfp(void) {
    return fireefp;
}

s32 kpaNoHitEnemyCheck(void) {
    return *(s16*)((u8*)marioGetPtr() + 0x78);
}

s32 kpaMutekiCheck(void) {
    return (MU32(KPW(marioGetPtr()), 0) >> 16) & 1;
}

void kpaMutekiOn(void) {
    MarioWork* mp = marioGetPtr();
    animPoseSetMaterialFlagOn(mp->paperAnimGroupId[0], 0x80000000);
    MU32(KPW(mp), 0) |= 0x10000;
}

void kpaMutekiOff(void) {
    MarioWork* mp = marioGetPtr();
    animPoseSetMaterialFlagOff(mp->paperAnimGroupId[0], 0x80000000);
    MU32(KPW(mp), 0) &= ~0x10000;
}

void kpaMSetMutekiTimer(void) {
    MarioWork* mp = marioGetPtr();
    MU32(KPW(mp), 0x138) = sysMsec2Frame(12000);
    *(s16*)((u8*)mp + 0x78) = 0;
}

void kpaChgPose(const char* a, const char* b) {
    s32 v = (MU32(marioGetPtr(), 0x14) & 1) ^ 1;
    marioChgPose(v == 1 ? a : b);
}

s32 kpaGetLevel(void) {
    s32 lv = 0;
    MarioWork* mp = marioGetPtr();
    if (mp->characterId == 2) {
        lv = MU32(KPW(mp), 4);
    }
    return lv;
}

void kpaSetLevel(s32 lv) {
    MarioWork* mp = marioGetPtr();
    if (mp->characterId == 2 && KPW(mp) != NULL) {
        f32 s;
        MU32(KPW(mp), 4) = lv;
        s = baseScaleTbl[lv];
        MF(mp, 0xC8) = MF(mp, 0xCC) = s;
        MF(mp, 0xD0) = 1.0f;
        kpaSetSpec();
    }
}

f32 kpaGetWidth(s32 lv) {
    return kpaWidthDat[lv];
}

s32 kpaGetBodyStatus(void) {
    MarioWork* mp = marioGetPtr();
    s32 st;
    if (mp->characterId != 2) {
        return -1;
    }
    st = 0;
    if (strcmp((char*)gp + 0x12C, "kpa_03") == 0) {
        if (MF(mp, 0x90) > 370.0f) {
            return 0;
        }
        if (MF(mp, 0x90) + MF(mp, 0x1B8) < 370.0f) {
            st = 2;
        } else {
            st = 1;
        }
    }
    return st;
}

s32 kpaGetStageType(void) {
    return (MU32(marioGetPtr(), 0x14) >> 1) & 1;
}

#define JP(m, i) (*(f32*)((u8*)(m) + 0x7C + (i) * 4))
#define SETP(m, a, b, c, d)     do { JP(m, 0) = (a); JP(m, 1) = (b); JP(m, 2) = (c); JP(m, 3) = (d); } while (0)

s32 kpaGetStageViewType(void) {
    return !(MU32(marioGetPtr(), 0x14) & 1);
}

s32 kpaCamFollow(void) {
    MarioWork* mp = marioGetPtr();
    s32 v;
    if (marioBgmodeChk() == 1 || (v = (MU32(marioGetPtr(), 0x14) & 1) ^ 1, (s32)v == 1)) {
        return 0;
    }
    if (mp->position.y > 76.0f) {
        camFollowYOn();
    }
    return 1;
}

void kpaPreInit(void) {
    u8* new_var;
    MarioWork* mp = marioGetPtr();
    if (KPW(mp) == NULL) {
        KPW(mp) = (u8*)__memAlloc(0, 0x154);
    }
    memset(KPW(mp), 0, 0x154);
    MU32(KPW(mp), 4) = 1;
    MU32(KPW(mp), 0xD0) = 1;
    MU32(KPW(mp), 0xE0) = 0;
    MU32(KPW(mp), 0xD8) = 1;
    new_var = KPW(marioGetPtr()) + 0x14C;
    *(s32*)new_var = -1;
    mp = marioGetPtr();
    if (strcmp((char*)gp + 0x12C, "kpa_02") == 0 || strcmp((char*)gp + 0x12C, "kpa_03") == 0 ||
        strcmp((char*)gp + 0x12C, "kpa_04") == 0 || strcmp((char*)gp + 0x12C, "kpa_05") == 0 ||
        strcmp((char*)gp + 0x12C, "kpa_06\0") == 0) {
        MU32(mp, 0x14) |= 1;
    } else {
        MU32(mp, 0x14) &= ~1;
    }
    mp = marioGetPtr();
    if (strcmp((char*)gp + 0x12C, "kpa_03") == 0) {
        MU32(mp, 0x14) |= 2;
    } else {
        MU32(mp, 0x14) &= ~2;
    }
    fireefp = 0;
}

f32 __fabsf(f32);

void kpaMain(void) {
    if (MU32(marioGetPtr(), 0x14) & 1) {
        kpa2DMain();
    } else {
        kpa3DMain();
    }
}

void kpa2DMain(void) {
    MarioWork* mp = marioGetPtr();
    Vec diff;
    Vec saved;
    f32 spd;
    f32 sn;
    f32 cs;
    f32 t;
    kpaHitCheck();
    if (*(s16*)((u8*)mp + 0x78)) {
        (*(s16*)((u8*)mp + 0x78))--;
    }
    MU32(mp, 0x1F4) = 0;
    MU32(mp, 0x1E0) = 0;
    MU32(mp, 0x1DC) = 0;
    MU32(mp, 0x1EC) = 0;
    MU32(mp, 0x1F0) = 0;
    marioItemGetChk();
    kpaFireAttack();
    kpaFireMain();
    {
        MarioWork* m2 = marioGetPtr();
        if (*(s32*)(KPW(m2) + 0x138) > 0) {
            if (--*(s32*)(KPW(m2) + 0x138) <= 0) {
                MU32(KPW(m2), 0x138) = 0;
                kpaMutekiOff();
            }
        }
    }
    if (mp->currMotionId == 8) {
        *(Vec*)((u8*)mp + 0x110) = mp->position;
        MF(mp, 0x174) = 0.0f;
        MF(mp, 0x178) = 0.0f;
        MF(mp, 0x17C) = 0.0f;
        marioBottomless();
        marioPreDisp();
        mario_kemuri_80130474();
        marioCamMain();
        MU32(mp, 0x34)++;
        return;
    }
    saved = mp->position;
    spd = 0.0f;
    if (!(mp->flags & 0x80) && mp->airTimer != 0) {
        spd = mp->controlStickSensitivity * mp->playerGravity;
        spd *= 0.015f;
        if (!(mp->flags & 0x70000)) {
            spd *= 0.25f;
        }
        sincosf(&sn, &cs, mp->controlStickAngle);
        spd *= sn;
    }
    sincosf(&sn, &cs, mp->directionView);
    t = mp->baseSpeed * sn + spd;
    spd = __fabsf(t);
    {
        f32 ang = angleABf(0.0f, 0.0f, t, 0.0f);
        f32 mx = mp->mBaseDashSpeed * mp->playerGravity;
        if (spd > mx) {
            spd = mx;
        }
        marioCheckWall(spd, ang);
    }
    mp->position.y += MF(mp, 0x178);
    PSVECSubtract(&mp->position, &saved, &diff);
    {
        f32 mag = PSVECMag(&diff);
        if (mag > spd) {
            PSVECScale(&diff, &diff, spd / mag);
            PSVECAdd(&saved, &diff, &mp->position);
        }
    }
    if (mp->flags & 0x10000) {
        marioChkOverhead();
        if (mp->airTimer > 5) {
            marioChkGnd2();
        }
    } else if (mp->flags & 0x20000) {
        kpaFall();
        marioChkOverhead();
        if (mp->currMotionId != 0x10 && mp->currMotionId != 0x11 && mp->airTimer > 5) {
            marioChkGnd2();
        }
    } else {
        marioChkOverhead();
        marioChkGnd();
    }
    marioBoots();
    marioForceMoveMain();
    marioBottomless();
    marioPreDisp();
    marioBalloonMain();
    mario_kemuri_80130474();
    marioCamMain();
    MU32(mp, 0x34)++;
    *(Vec*)((u8*)mp + 0x110) = mp->position;
    MF(mp, 0x174) = 0.0f;
    MF(mp, 0x178) = 0.0f;
    MF(mp, 0x17C) = 0.0f;
}

void kpa3DMain(void) {
    MarioWork* mp = marioGetPtr();
    void* h = kpaHitCheck();
    if (h) {
        MU32(mp, 0x1F4) = (u32)h;
    }
    if (*(s16*)((u8*)mp + 0x78)) {
        (*(s16*)((u8*)mp + 0x78))--;
    }
    if (mp->currMotionId == 0x18 || mp->currMotionId == 0x1F || mp->currMotionId == 0x20) {
        marioPreDisp();
        marioBottomless();
        MU32(mp, 0x34)++;
        partyMain();
        marioCamMain();
        MU32(mp, 0x1F4) = 0;
        MU32(mp, 0x1E0) = 0;
        MU32(mp, 0x1DC) = 0;
        MU32(mp, 0x1EC) = 0;
        MU32(mp, 0x1F0) = 0;
        return;
    }
    marioItemGetChk();
    kpaFireAttack();
    kpaFireMain();
    {
        MarioWork* m2 = marioGetPtr();
        if (*(s32*)(KPW(m2) + 0x138) > 0) {
            if (--*(s32*)(KPW(m2) + 0x138) <= 0) {
                MU32(KPW(m2), 0x138) = 0;
                kpaMutekiOff();
            }
        }
    }
    if (mp->currMotionId == 8) {
        *(Vec*)((u8*)mp + 0x110) = mp->position;
        MF(mp, 0x174) = 0.0f;
        MF(mp, 0x178) = 0.0f;
        MF(mp, 0x17C) = 0.0f;
        marioBottomless();
        marioPreDisp();
        marioBalloonMain();
        mario_kemuri_80130474();
        partyMain();
        marioCamMain();
        MU32(mp, 0x34)++;
        return;
    }
    if (mp->flags & 0x40000) {
        marioMove();
        marioChkOverhead();
        if (mp->airTimer > 100) {
            marioChgMot(10);
            marioSetFallPara();
        }
    } else if (mp->flags & 0x10000) {
        marioMove();
        marioChkOverhead();
        if (mp->airTimer > 5) {
            marioChkGnd2();
        }
    } else if (mp->flags & 0x20000) {
        marioMove();
        kpaFall();
        kpaSearchFrontUnder();
        marioChkOverhead();
        if (mp->currMotionId != 0x10 && mp->currMotionId != 0x11 && mp->airTimer > 5) {
            marioChkGnd2();
        }
    } else {
        marioMove();
        kpaSearchFrontUnder();
        marioChkOverhead();
        marioChkGnd();
    }
    marioBoots();
    marioForceMoveMain();
    marioBottomless();
    marioPreDisp();
    marioBalloonMain();
    mario_kemuri_80130474();
    partyMain();
    marioCamMain();
    MU32(mp, 0x34)++;
    *(Vec*)((u8*)mp + 0x110) = mp->position;
    MF(mp, 0x174) = 0.0f;
    MF(mp, 0x178) = 0.0f;
    MF(mp, 0x17C) = 0.0f;
}

#define SETPV(m, v, a, b, c, d) do { JP(m, v) = (a); JP(m, 1) = (b); JP(m, 2) = (c); JP(m, 3) = (d); } while (v)
f32 kpaSetJumpPara(void) {
    int new_var;
    f32* jd = marioJumpData;
    MarioWork* mp = marioGetPtr();
    new_var = 0;
    SETPV(mp, new_var, jd[new_var], jd[1], jd[2], jd[3]);
    switch (MU32(KPW(mp), 4)) {
    case 0:
        SETPV(mp, new_var, 7.0f, -0.4f, 0.08f, -0.02f);
        break;
    case 1:
        SETPV(mp, new_var, 8.1f, -0.3f, 0.08f, -0.02f);
        break;
    case 2:
        SETPV(mp, new_var, 8.4f, -0.1f, 0.08f, -0.018f);
        break;
        if (!new_var) {
        }
    case 3:
        SETPV(mp, new_var, 10.5f, -0.12f, 0.08f, -0.018f);
        break;
    }
    return JP(mp, new_var);
}

f32 kpaSetFallPara(void);
void kpa_jumpNpc(void) {
    MarioWork* mp = marioGetPtr();
    if (mp->trigFlags & 1) {
        mp->trigFlags &= ~1;
        marioResetCamFollowRate();
        mp->flags &= ~0x80;
        camFollowYOff();
        marioPreJump();
        SETP(mp, 2.6f, -0.06f, -0.01f, -0.002f);
        if (!(mp->flags & 0x2000) && mp->characterId == 0) {
            marioChgPose("M_J_1B");
        }
        mp->flags |= 0x10000;
        mp->currSubMotionId = 0;
    }
    switch ((s32)mp->currSubMotionId) { case 0: {
        marioMakeJumpPara();
        if (JP(mp, 0) <= 0.0f) {
            if (!(mp->flags & 0x2000) && mp->characterId == 0) {
                marioChgPose("M_J_1C");
            }
            marioSetPeakYpos();
            JP(mp, 1) = -0.06f;
            JP(mp, 2) = -0.004f;
            JP(mp, 3) = -0.002f;
            mp->flags &= ~0x10000;
            mp->flags |= 0x20000;
        }
    } break; }
    mp->position.y += JP(mp, 0);
    mp->airTimer++;
}

void kpaFall(void) {
    MarioWork* mp = marioGetPtr();
    f32 fs;
    f32 ly;
    if (strcmp((char*)gp + 0x12C, "kpa_03") == 0) {
        void* h;
        mp->hitobjStandOn = NULL;
        kpaClearHitobjRide();
        fs = marioGetFallSpd();
        if (fs < -20.0f) {
            fs = -20.0f;
        }
        if (!fs) {
            kpaSetFallPara();
            fs = marioGetFallSpd();
        }
        h = marioChkLandon(&ly, fs);
        if (h) {
            mp->hitobjStandOn = h;
            mp->hitobjJumpFrom = NULL;
            mp->position.y = ly;
        } else {
            mp->position.y += fs;
        }
        if (mp->hitobjStandOn) {
            marioLandOn();
            psndSFXOn_3D((char*)0x81D, &mp->position);
        }
    } else {
        void* h;
        if (mp->currMotionId == 0x10 || mp->currMotionId == 0x11) {
            return;
        }
        {
        if (!marioKeyOffChk() || !marioCtrlOffChk()) {
            if (!(mp->flags & 0x20)) {
                f32 bs = mp->baseSpeed;
                bs += 0.01f * (-0.5f - bs);
                if (bs < 0.0f) {
                    bs = 0.0f;
                }
                mp->baseSpeed = bs;
            }
        }
        if (mp->currMotionId != 4) {
            if (*(u16*)((u8*)mp + 0x246) & 0x100) {
                JP(mp, 3) = -0.001f;
            } else {
                JP(mp, 3) = -0.01f;
            }
        }
        mp->hitobjStandOn = NULL;
        kpaClearHitobjRide();
        fs = marioGetFallSpd();
        if (fs < -20.0f) {
            fs = -20.0f;
        }
        h = marioChkLandon(&ly, fs);
        if (!h) {
            mp->position.y += fs;
        } else {
            mp->hitobjStandOn = h;
            mp->hitobjJumpFrom = NULL;
            if (hitGetAttr(h) & 0x200) {
                mp->position.y += fs;
            } else {
                mp->position.y = ly;
            }
        }
        if (h || kpaChkHitobjRide()) {
            marioLandOn();
        }
    }
    }
}

f32 kpaSetFallPara(void);
f32 kpaSetFallPara(void) {
    MarioWork* mp = marioGetPtr();
    if ((*(u16*)((u8*)mp + 0x246) & 0x100)) {
        SETP(mp, -0.05f, -0.08f, -0.006f, -0.002f);
    } else {
        SETP(mp, -0.1f, -0.2f, -0.024f, -0.01f);
    }
}

s32 kpaFireAttackCheck(void) {
    s32 m;
    MarioWork* mp = marioGetPtr();
    if (!(MU32(mp, 0) & 1)) {
        return 0;
    }
    m = *(s32*)(KPW(mp) + 0x13C);
    if ((m >= 20 && m <= 23) || (m >= 40 && m <= 43)) {
        return 1;
    }
    return 0;
}

void kpaAttackStart(void) {
    MarioWork* mp = marioGetPtr();
    if (*(s32*)(KPW(mp) + 0x13C) == 0) {
        marioChgMot(0);
        *(s32*)(KPW(mp) + 0x13C) = 1;
    }
}

void kpaAttackStart2(void) {
    u8* w = KPW(marioGetPtr());
    if (*(s32*)(w + 0x13C) == 0) {
        *(s32*)(w + 0x13C) = 30;
    }
}

void kpaFireAttack(void) {
    MarioWork* mp = marioGetPtr();
    switch (*(s32*)(KPW(mp) + 0x13C)) {
    case 1:
        MU32(mp, 0) &= ~0xF0000;
        *(s16*)((u8*)mp + 0x50) = 0;
        *(s32*)(KPW(mp) + 0xD8) = *(s32*)(KPW(mp) + 4) == 0 ? 12 : 8;
        *(s32*)(KPW(mp) + 0xE0) = 0;
        *(s32*)(KPW(mp) + 0x140) = 0;
        *(s32*)(KPW(mp) + 0x13C) = 20;
        if (!(MU32(mp, 0) & 0x20)) {
            MF(mp, 0x180) = 0.0f;
            MF(mp, 0x2C4) = 0.0f;
        }
    case 20:
        kpaChgPose("KPA_A_1A", "KPA2_A_1A");
        *(s32*)(KPW(mp) + 0x140) = 6;
        *(s32*)(KPW(mp) + 0x13C) = 21;
        break;
    case 21:
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        kpaChgPose("KPA_A_1B", "KPA2_A_1B");
        *(s32*)(KPW(mp) + 0x140) = 8;
        *(s32*)(KPW(mp) + 0x13C) = 22;
        kpaFireSEOn();
        break;
    case 22:
        kpaFireEntry(mp->position);
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        *(s32*)(KPW(mp) + 0x140) = sysMsec2Frame(400);
        kpaChgPose("KPA_A_1C", "KPA2_A_1C");
        *(s32*)(KPW(mp) + 0x13C) = 23;
        break;
    case 23:
        kpaFireEntry(mp->position);
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        if (*(u16*)((u8*)mp + 0x246) & 0x200) {
            break;
        }
        if (*(s32*)(KPW(mp) + 0x144) != 0) {
            break;
        }
        kpaChgPose("KPA_A_1D", "KPA2_A_1D");
        *(s32*)(KPW(mp) + 0x13C) = 24;
        *(s32*)(KPW(mp) + 0x140) = 6;
        kpaFireSEOff();
        break;
    case 24:
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        *(s32*)(KPW(mp) + 0x13C) = 0;
        kpaChgPose("KPA_S_1", "KPA2_S_1");
        break;
    }
    switch (*(s32*)(KPW(mp) + 0x13C)) {
    case 30:
        *(s32*)(KPW(mp) + 0xD8) = *(s32*)(KPW(mp) + 4) == 0 ? 12 : 8;
        *(s32*)(KPW(mp) + 0xE0) = 0;
        *(s32*)(KPW(mp) + 0x140) = 0;
        *(s32*)(KPW(mp) + 0x13C) = 40;
        if (!(MU32(mp, 0) & 0x20)) {
            MF(mp, 0x180) = 0.0f;
            MF(mp, 0x2C4) = 0.0f;
        }
    case 40:
        kpaChgPose("KPA_A_1A", "KPA2_A_1A");
        *(s32*)(KPW(mp) + 0x140) = 6;
        *(s32*)(KPW(mp) + 0x13C) = 41;
        break;
    case 41:
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        kpaChgPose("KPA_A_1B", "KPA2_A_1B");
        *(s32*)(KPW(mp) + 0x140) = 8;
        *(s32*)(KPW(mp) + 0x13C) = 42;
        kpaFireSEOn();
        break;
    case 42:
        kpaFireEntry(mp->position);
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        *(s32*)(KPW(mp) + 0x140) = sysMsec2Frame(400);
        kpaChgPose("KPA_A_1C", "KPA2_A_1C");
        *(s32*)(KPW(mp) + 0x13C) = 43;
        break;
    case 43:
        kpaFireEntry(mp->position);
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        if (*(u16*)((u8*)mp + 0x246) & 0x200) {
            break;
        }
        if (*(s32*)(KPW(mp) + 0x144) != 0) {
            break;
        }
        kpaChgPose("KPA_A_1D", "KPA2_A_1D");
        *(s32*)(KPW(mp) + 0x13C) = 44;
        *(s32*)(KPW(mp) + 0x140) = 6;
        kpaFireSEOff();
        break;
    case 44:
        if (--*(s32*)(KPW(mp) + 0x140) > 0) {
            break;
        }
        *(s32*)(KPW(mp) + 0x13C) = 0;
        switch (*(u16*)((u8*)mp + 0x2E)) {
        case 0:
            kpaChgPose("KPA_S_1", "KPA2_S_1");
            break;
        case 1:
            kpaChgPose("KPA_W_1", "KPA2_W_1");
            break;
        case 2:
            kpaChgPose("KPA_R_1", "KPA2_R_1");
            break;
        case 0x25:
            kpaChgPose("KPA_S_1", "KPA2_Z_2");
            break;
        }
        break;
    }
}


void kpaCancelAttackMode(void) {
    MarioWork* mp;
    u8* w = KPW(marioGetPtr());
    *(s32*)(w + 0x13C) = 0;
    mp = marioGetPtr();
    if (*(u32*)(KPW(mp) + 0x14C) != 0xFFFFFFFFU) {
        psndSFXOff(*(s32*)(KPW(mp) + 0x14C));
        *(s32*)(KPW(mp) + 0x14C) = -1;
    }
}

s32 kpaGetAttackMode(void) {
    return *(s32*)(KPW(marioGetPtr()) + 0x13C) != 0;
}

void unk_801f8cd0(void) {
    if (fireefp) {
        MarioWork* mp;
        effSoftDelete((void*)fireefp);
        fireefp = 0;
        mp = marioGetPtr();
        if (*(u32*)(KPW(mp) + 0x14C) != 0xFFFFFFFFU) {
            psndSFXOff(*(s32*)(KPW(mp) + 0x14C));
            *(s32*)(KPW(mp) + 0x14C) = -1;
        }
    }
}

void kpaFireMain(void) {
    MarioWork* mp = marioGetPtr();
    Mtx mb0;
    Mtx m80;
    Mtx m50;
    Mtx m20;
    Vec out;
    Vec zero;
    s32 flag;
    s32 lv;
    u8* fe;
    u8* w;
    s32 i;
    f32 f31;
    f32 f30;
    f32 f29;
    *(s32*)(KPW(mp) + 0x18) = flag = 0;
    if (fireefp) {
        f32 dir;
        f32 scale;
        f32 x;
        f32 y;
        f32 z;
        s32 t;
        dir = (mp->unk1A8 >= 90.0f && mp->unk1A8 <= 270.0f) ? 1.0f : -1.0f;
        scale = kpaGetBaseScale(kpaGetLevel());
        f30 = 40.0f * dir * scale + mp->position.x;
        t = (MU32(marioGetPtr(), 0x14) & 1) ^ 1;
        y = mp->position.y + (20.0f * scale + (t == 1 ? 6.0f : 0.0f));
        z = mp->position.z;
                MF(*(u8**)(fireefp + 0xC), 4) = f30;
        MF(*(u8**)(fireefp + 0xC), 8) = y;
        MF(*(u8**)(fireefp + 0xC), 0xC) = z;
        {
            u8* w2 = *(u8**)(*(u8**)(fireefp + 0xC) + 0x4C);
            if (w2) {
                MF(*(u8**)(w2 + 0xC), 4) = f30;
                MF(*(u8**)(*(u8**)(*(u8**)(fireefp + 0xC) + 0x4C) + 0xC), 8) = y;
                MF(*(u8**)(*(u8**)(*(u8**)(fireefp + 0xC) + 0x4C) + 0xC), 0xC) = z;
            }
        }
        lv = kpaGetLevel();
        if (lv != 0) {
            fe = fireefp;
            camGetPtr(4);
            w = *(u8**)(fe + 0xC);
            f29 = MF(w, 0x40);
            PSMTXTrans(m80, MF(w, 4), MF(w, 8), MF(w, 0xC));
            PSMTXRotRad(m50, 'y', 0.017453292f * (MF(w, 0x48) - MF(camGetPtr(4), 0x114)));
            if (MF(w, 0x48) > 90.0f && MF(w, 0x48) < 270.0f) {
                PSMTXScale(mb0, MF(w, 0x40), MF(w, 0x40), -MF(w, 0x40));
            } else {
                PSMTXScale(mb0, MF(w, 0x40), MF(w, 0x40), MF(w, 0x40));
            }
            PSMTXConcat(m80, m50, m80);
            PSMTXConcat(m80, mb0, m20);
            w = w + 0x50;
            for (i = 1; i < *(s32*)(fe + 8); i++, w += 0x50) {
                if (((i - 1) & 3) == 0 && *(s32*)(w + 0x44) == 0 && *(s32*)(w + 0x1C) > 0x10) {
                    void* hit;
                    f31 = 7.0f * MF(w, 0x40);
                    f30 = f31 * f29;
                    if (!(f30 < 7.0f)) {
                        PSMTXTrans(m80, MF(w, 4), MF(w, 8), MF(w, 0xC));
                        PSMTXScale(mb0, f31, f31, f31);
                        PSMTXConcat(m80, mb0, m80);
                        PSMTXConcat(m20, m80, m80);
                        zero = *(Vec*)vec3_802fc920;
                        PSMTXMultVec(m80, &zero, &out);
                        hit = kpaFlameHitCheck(out.x, out.y, out.z, f30);
                        if (hit) {
                            *(void**)(KPW(mp) + 0x18) = hit;
                            break;
                        }
                    }
                }
            }
        }
    }
    {
        if (kpaFireAttackCheck() == 0) {
            if (fireefp) {
                effSoftDelete((void*)fireefp);
                fireefp = 0;
            }
        }
    }
}

f32 kpaGetBaseScale(s32 lv) {
    return baseScaleTbl[lv];
}

s32 kpaHipAttackCheck(void) {
    s32 r = 0;
    MarioWork* mp = marioGetPtr();
    if (mp->characterId != 2) {
        return 0;
    }
    if (mp->currMotionId == 0x11) {
        r = 1;
    }
    return r;
}

s32 kpaJumpChk(void) {
    return ((MarioWork*)marioGetPtr())->airTimer != 0;
}

void kpaPauseSE2(void) {
    psndSFXOn((char*)(kpaPauseSeTable[irand(28)] | 0x20000));
}
