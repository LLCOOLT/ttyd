// Bowser (koopa) as the player in the Super Mario Bros. style side-scrolling interludes: work, level, camera,
// fire attack and jump parameters.
#include "eff/eff_gonbaba_breath.h"
#include "mario/mario.h"
#include "koopa.h"
#include "mario/mariost.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include "koopa_motion.h"
#include "mario/mario_balloon.h"
#include "mario/mario_cam.h"
#include "mario/mario_hit.h"
#include "mario/mario_sbr.h"
#include "mot/mot_jump.h"
#include "party.h"
#include "memory.h"
#include <string.h>
#include "koopa_hit.h"
#include "mario/mario_motion.h"
#include "mario/mario_kemuri.h"
#include "mario/mario_hit.h"
#include "version.h"
#include <dolphin/pad.h>

// mario_motion.c's MarioJumpData; read here as a plain array of floats (koopa.c addresses it as a far object,
// which it does only through an array of unknown size).
extern f32 marioJumpData[];

static void kpa2DMain(void);
static void kpa3DMain(void);
static void kpaFireAttack(void);
static void kpaFireMain(void);
static void kpaFall(void);
const f32 kpaZeroVec[3] = {0.0f, 0.0f, 0.0f};

#define KPW(m) ((m)->kpaWork)

f32 kpaWidthDat[4] = {20.0f, 60.0f, 84.0f, 186.0f};
f32 baseScaleTbl[4] = {0.3f, 1.0f, 1.4f, 3.1f};
s32 kpaPauseSeTable[28] = {0x10C, 0x10D, 0x10E, 0x10F, 0x111, 0x112, 0x113, 0x114, 0x116, 0x117,
                           0x118, 0x119, 0x11B, 0x11E, 0x11F, 0x120, 0x122, 0x123, 0x124, 0x125,
                           0x127, 0x128, 0x129, 0x12A, 0x12C, 0x12D, 0x12E, 0x12F};
static EffectEntry* fireefp;

static inline void kpaFireEntry2(Vec pos) {
    MarioWork* mario = marioGetPtr();
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
        EffectEntry* child;
        s32 t;
        dir = (mario->displayDirection >= 90.0f && mario->displayDirection <= 270.0f) ? 1.0f : -1.0f;
        scale = kpaGetBaseScale(kpaGetLevel());
        x = 40.0f * dir * scale + pos.x;
        t = (marioGetPtr()->stageFlags & 1) ^ 1;
        y = pos.y + (20.0f * scale + (t == 1 ? 6.0f : 0.0f));
        z = pos.z;
        type = 7;
        sz = 0.4f;
        switch (KPW(mario)->level) {
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
        if (mario->displayDirectionTarget >= 90.0f && mario->displayDirectionTarget <= 270.0f) {
            flag = 1;
        }
        ((EffGonbabaBreathWork*)fireefp->userdata)->yaw = (f32)(flag ? 180 : 0);
        child = ((EffGonbabaBreathWork*)fireefp->userdata)->child;
        if (child) {
            flag = 0;
            if (mario->displayDirectionTarget >= 90.0f && mario->displayDirectionTarget <= 270.0f) {
                flag = 1;
            }
            ang = flag ? 180 : 0;
            ((EffGonbabaBreathWork*)child->userdata)->yaw = (f32)ang;
        }
    }
}

static inline void kpaFireEntry(Vec pos) {
    MarioWork* mario = marioGetPtr();
    kpaFireEntry2(pos);
}

static inline void kpaFireSEOn(void) {
    MarioWork* mario = marioGetPtr();
    if (KPW(mario)->fireSfxId == 0xFFFFFFFFU) {
        KPW(mario)->fireSfxId = psndSFXOn_3D((const char*)0x821, &mario->position);
        psndSFXOn_3D((const char*)0x131, &mario->position);
    }
}

static inline void kpaFireSEInit(void) {
    MarioWork* mario = marioGetPtr();
    KPW(mario)->fireSfxId = -1;
}

static inline void kpaFireSEOff(void) {
    MarioWork* mario = marioGetPtr();
    if (KPW(mario)->fireSfxId != 0xFFFFFFFFU) {
        psndSFXOff(KPW(mario)->fireSfxId);
        KPW(mario)->fireSfxId = -1;
    }
}

EffectEntry* getKoopaFireEfp(void) {
    return fireefp;
}

s32 kpaNoHitEnemyCheck(void) {
    return marioGetPtr()->kpaNoHitTimer;
}

s32 kpaMutekiCheck(void) {
    return (KPW(marioGetPtr())->flags >> 16) & 1;
}

void kpaMutekiOn(void) {
    MarioWork* mario = marioGetPtr();
    animPoseSetMaterialFlagOn(mario->paperAnimGroupId[0], ANIM_MATERIAL_FLAG_HIGHLIGHT);
    KPW(mario)->flags |= 0x10000;
}

void kpaMutekiOff(void) {
    MarioWork* mario = marioGetPtr();
    animPoseSetMaterialFlagOff(mario->paperAnimGroupId[0], ANIM_MATERIAL_FLAG_HIGHLIGHT);
    KPW(mario)->flags &= ~0x10000;
}

void kpaMSetMutekiTimer(void) {
    MarioWork* mario = marioGetPtr();
    KPW(mario)->mutekiTimer = sysMsec2Frame(12000);
    mario->kpaNoHitTimer = 0;
}

void kpaChgPose(const char* a, const char* b) {
    s32 v = (marioGetPtr()->stageFlags & 1) ^ 1;
    marioChgPose(v == 1 ? a : b);
}

s32 kpaGetLevel(void) {
    s32 lv = 0;
    MarioWork* mario = marioGetPtr();
    if (mario->characterId == 2) {
        lv = KPW(mario)->level;
    }
    return lv;
}

void kpaSetLevel(s32 lv) {
    MarioWork* mario = marioGetPtr();
    if (mario->characterId == 2 && KPW(mario) != NULL) {
        f32 s;
        KPW(mario)->level = lv;
        s = baseScaleTbl[lv];
        mario->scale.x = mario->scale.y = s;
        mario->scale.z = 1.0f;
        kpaSetSpec();
    }
}

f32 kpaGetWidth(s32 lv) {
    return kpaWidthDat[lv];
}

s32 kpaGetBodyStatus(void) {
    MarioWork* mario = marioGetPtr();
    s32 st;
    if (mario->characterId != 2) {
        return -1;
    }
    st = 0;
    if (strcmp(gp->currentMapName, "kpa_03") == 0) {
        if (mario->position.y > 370.0f) {
            return 0;
        }
        if (mario->position.y + mario->wPlayerCollisionBox.y < 370.0f) {
            st = 2;
        } else {
            st = 1;
        }
    }
    return st;
}

s32 kpaGetStageType(void) {
    return (marioGetPtr()->stageFlags >> 1) & 1;
}

#define JP(m, i) ((&(m)->jumpVelocityY)[i]) // jumpVelocityY..jumpSnapY as f32[4]
#define SETP(m, a, b, c, d) \
    do {                    \
        JP(m, 0) = (a);     \
        JP(m, 1) = (b);     \
        JP(m, 2) = (c);     \
        JP(m, 3) = (d);     \
    } while (0)

s32 kpaGetStageViewType(void) {
    return !(marioGetPtr()->stageFlags & 1);
}

s32 kpaCamFollow(void) {
    MarioWork* mario = marioGetPtr();
    s32 v;
    if (marioBgmodeChk() == 1 || (v = (marioGetPtr()->stageFlags & 1) ^ 1, (s32)v == 1)) {
        return 0;
    }
    if (mario->position.y > 76.0f) {
        camFollowYOn();
    }
    return 1;
}

void kpaPreInit(void) {
    MarioWork* mario = marioGetPtr();
    if (KPW(mario) == NULL) {
        KPW(mario) = (KpaWork*)__memAlloc(0, sizeof(KpaWork));
    }
    memset(KPW(mario), 0, sizeof(KpaWork));
    KPW(mario)->level = 1;
    KPW(mario)->walkRate = 1;
    KPW(mario)->fireCount = 0;
    KPW(mario)->fireRate = 1;
    kpaFireSEInit();
    mario = marioGetPtr();
    if (strcmp(gp->currentMapName, "kpa_02") == 0 || strcmp(gp->currentMapName, "kpa_03") == 0 ||
        strcmp(gp->currentMapName, "kpa_04") == 0 || strcmp(gp->currentMapName, "kpa_05") == 0 ||
        strcmp(gp->currentMapName, "kpa_06") == 0) {
        mario->stageFlags |= 1;
    } else {
        mario->stageFlags &= ~1;
    }
    mario = marioGetPtr();
    if (strcmp(gp->currentMapName, "kpa_03") == 0) {
        mario->stageFlags |= 2;
    } else {
        mario->stageFlags &= ~2;
    }
    fireefp = 0;
}

f32 __fabsf(f32);

void kpaMain(void) {
    if (marioGetPtr()->stageFlags & 1) {
        kpa2DMain();
    } else {
        kpa3DMain();
    }
}

static void kpa2DMain(void) {
    MarioWork* mp = marioGetPtr();
    Vec diff;
    Vec saved;
    f32 spd;
    f32 sn;
    f32 cs;
    f32 t;
    kpaHitCheck();
    if (mp->kpaNoHitTimer) {
        mp->kpaNoHitTimer--;
    }
#if VERSION >= VERSION_JP
    mp->hitobjHead = NULL;
    mp->hitobjFront = NULL;
    mp->hitobjFrontA = NULL;
    mp->hitobjPush = NULL;
    mp->hitobjWall = NULL;
#endif
    marioItemGetChk();
    kpaFireAttack();
    kpaFireMain();
    {
        MarioWork* m2 = marioGetPtr();
        if (KPW(m2)->mutekiTimer > 0) {
            if (--KPW(m2)->mutekiTimer <= 0) {
                KPW(m2)->mutekiTimer = 0;
                kpaMutekiOff();
            }
        }
    }
    if (mp->currMotionId == MARIO_MOTION_JUMP_3) {
        mp->basePos = mp->position;
        mp->floorMove.x = 0.0f;
        mp->floorMove.y = 0.0f;
        mp->floorMove.z = 0.0f;
        marioBottomless();
        marioPreDisp();
        mario_kemuri();
        marioCamMain();
        mp->frameCounter++;
        return;
    }
    saved = mp->position;
    spd = 0.0f;
    if (!(mp->flags & MARIO_FLAG_STOP_AIR_MOVEMENT) && mp->airTimer != 0) {
        spd = mp->controlStickSensitivity * mp->playerGravity;
        spd *= 0.015f;
        if (!(mp->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING))) {
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
        f32 mx = mp->baseDashSpeed * mp->playerGravity;
        if (spd > mx) {
            spd = mx;
        }
        marioCheckWall(spd, ang);
    }
#if VERSION >= VERSION_JP
    mp->position.y += mp->floorMove.y;
#endif
    PSVECSubtract(&mp->position, &saved, &diff);
    {
        f32 mag = PSVECMag(&diff);
        if (mag > spd) {
            PSVECScale(&diff, &diff, spd / mag);
            PSVECAdd(&saved, &diff, &mp->position);
        }
    }
    if (mp->flags & MARIO_FLAG_IS_JUMPING) {
        marioChkOverhead();
        if (mp->airTimer > 5) {
            marioChkGnd2();
        }
    } else if (mp->flags & MARIO_FLAG_IS_FALLING) {
        kpaFall();
        marioChkOverhead();
        if (mp->currMotionId != MARIO_MOTION_HIP && mp->currMotionId != MARIO_MOTION_HIP_2 && mp->airTimer > 5) {
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
    mario_kemuri();
    marioCamMain();
    mp->frameCounter++;
    mp->basePos = mp->position;
    mp->floorMove.x = 0.0f;
    mp->floorMove.y = 0.0f;
    mp->floorMove.z = 0.0f;
}

static void kpa3DMain(void) {
    MarioWork* mp = marioGetPtr();
    struct HitEntry* h = kpaHitCheck();
    if (h) {
        mp->hitobjHead = h;
    }
    if (mp->kpaNoHitTimer) {
        mp->kpaNoHitTimer--;
    }
    if (mp->currMotionId == MARIO_MOTION_PLANE || mp->currMotionId == MARIO_MOTION_DAMAGE || mp->currMotionId == MARIO_MOTION_DAMAGE_TOGE) {
        marioPreDisp();
        marioBottomless();
        mp->frameCounter++;
        partyMain();
        marioCamMain();
        mp->hitobjHead = NULL;
        mp->hitobjFront = NULL;
        mp->hitobjFrontA = NULL;
        mp->hitobjPush = NULL;
        mp->hitobjWall = NULL;
        return;
    }
    marioItemGetChk();
    kpaFireAttack();
    kpaFireMain();
    {
        MarioWork* m2 = marioGetPtr();
        if (KPW(m2)->mutekiTimer > 0) {
            if (--KPW(m2)->mutekiTimer <= 0) {
                KPW(m2)->mutekiTimer = 0;
                kpaMutekiOff();
            }
        }
    }
    if (mp->currMotionId == MARIO_MOTION_JUMP_3) {
        mp->basePos = mp->position;
        mp->floorMove.x = 0.0f;
        mp->floorMove.y = 0.0f;
        mp->floorMove.z = 0.0f;
        marioBottomless();
        marioPreDisp();
        marioBalloonMain();
        mario_kemuri();
        partyMain();
        marioCamMain();
        mp->frameCounter++;
        return;
    }
    if (mp->flags & MARIO_FLAG_IS_STEPPING) {
        marioMove();
        marioChkOverhead();
        if (mp->airTimer > 100) {
            marioChgMot(MARIO_MOTION_FALL);
            marioSetFallPara();
        }
    } else if (mp->flags & MARIO_FLAG_IS_JUMPING) {
        marioMove();
        marioChkOverhead();
        if (mp->airTimer > 5) {
            marioChkGnd2();
        }
    } else if (mp->flags & MARIO_FLAG_IS_FALLING) {
        marioMove();
        kpaFall();
        kpaSearchFrontUnder();
        marioChkOverhead();
        if (mp->currMotionId != MARIO_MOTION_HIP && mp->currMotionId != MARIO_MOTION_HIP_2 && mp->airTimer > 5) {
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
    mario_kemuri();
    partyMain();
    marioCamMain();
    mp->frameCounter++;
    mp->basePos = mp->position;
    mp->floorMove.x = 0.0f;
    mp->floorMove.y = 0.0f;
    mp->floorMove.z = 0.0f;
}

f32 kpaSetJumpPara(void) {
    f32* jd = marioJumpData;
    MarioWork* mario = marioGetPtr();
    mario->jumpVelocityY = *jd++;
    mario->jumpAccelerationY = *jd++;
    mario->jumpJerkY = *jd++;
    mario->jumpSnapY = *jd;
    switch (KPW(mario)->level) {
        case 0:
            SETP(mario, 7.0f, -0.4f, 0.08f, -0.02f);
            break;
        case 1:
            SETP(mario, 8.1f, -0.3f, 0.08f, -0.02f);
            break;
        case 2:
            SETP(mario, 8.4f, -0.1f, 0.08f, -0.018f);
            break;
        case 3:
            SETP(mario, 10.5f, -0.12f, 0.08f, -0.018f);
            break;
    }
    return JP(mario, 0);
}

// No return statement: the original falls off the end (callers ignore the result). Declared void, the
// constants load into other float registers, so the f32 return type stays.
f32 kpaSetFallPara(void) {
    MarioWork* mario = marioGetPtr();
    if ((mario->buttonHold & PAD_BUTTON_A)) {
        SETP(mario, -0.05f, -0.08f, -0.006f, -0.002f);
    } else {
        SETP(mario, -0.1f, -0.2f, -0.024f, -0.01f);
    }
}

void kpa_jumpNpc(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        marioResetCamFollowRate();
        mario->flags &= ~MARIO_FLAG_STOP_AIR_MOVEMENT;
        camFollowYOff();
        marioPreJump();
        SETP(mario, 2.6f, -0.06f, -0.01f, -0.002f);
        if (!(mario->flags & MARIO_FLAG_IS_CARRYING_BOBBERY) && mario->characterId == 0) {
            marioChgPose("M_J_1B");
        }
        mario->flags |= MARIO_FLAG_IS_JUMPING;
        mario->currSubMotionId = 0;
    }
    switch ((s32)mario->currSubMotionId) {
        case 0: {
            marioMakeJumpPara();
            if (mario->jumpVelocityY <= 0.0f) {
                if (!(mario->flags & MARIO_FLAG_IS_CARRYING_BOBBERY) && mario->characterId == 0) {
                    marioChgPose("M_J_1C");
                }
                marioSetPeakYpos();
                mario->jumpAccelerationY = -0.06f;
                mario->jumpJerkY = -0.004f;
                mario->jumpSnapY = -0.002f;
                mario->flags &= ~MARIO_FLAG_IS_JUMPING;
                mario->flags |= MARIO_FLAG_IS_FALLING;
            }
        } break;
    }
    mario->position.y += mario->jumpVelocityY;
    mario->airTimer++;
}

static void kpaFall(void) {
    MarioWork* mario = marioGetPtr();
    f32 fs;
    f32 ly;
    if (strcmp(gp->currentMapName, "kpa_03") == 0) {
        void* h;
        mario->hitobjStandOn = NULL;
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
            mario->hitobjStandOn = h;
            mario->hitobjJumpFrom = NULL;
            mario->position.y = ly;
        } else {
            mario->position.y += fs;
        }
        if (mario->hitobjStandOn) {
            marioLandOn();
            psndSFXOn_3D((char*)0x81D, &mario->position);
        }
    } else {
        void* h;
        if (mario->currMotionId == MARIO_MOTION_HIP || mario->currMotionId == MARIO_MOTION_HIP_2) {
            return;
        }
        {
            if (!marioKeyOffChk() || !marioCtrlOffChk()) {
                if (!(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                    f32 bs = mario->baseSpeed;
                    bs += 0.01f * (-0.5f - bs);
                    if (bs < 0.0f) {
                        bs = 0.0f;
                    }
                    mario->baseSpeed = bs;
                }
            }
            if (mario->currMotionId != MARIO_MOTION_JUMP_NPC) {
                if (mario->buttonHold & PAD_BUTTON_A) {
                    mario->jumpSnapY = -0.001f;
                } else {
                    mario->jumpSnapY = -0.01f;
                }
            }
            mario->hitobjStandOn = NULL;
            kpaClearHitobjRide();
            fs = marioGetFallSpd();
            if (fs < -20.0f) {
                fs = -20.0f;
            }
            h = marioChkLandon(&ly, fs);
            if (!h) {
                mario->position.y += fs;
            } else {
                mario->hitobjStandOn = h;
                mario->hitobjJumpFrom = NULL;
                if (hitGetAttr(h) & 0x200) {
                    mario->position.y += fs;
                } else {
                    mario->position.y = ly;
                }
            }
            if (h || kpaChkHitobjRide()) {
                marioLandOn();
            }
        }
    }
}

void kpaStrippedFallPool(f32* f) {
    f[0] = -0.05f;
    f[1] = -0.08f;
    f[2] = -0.006f;
    f[3] = -0.002f;
    f[4] = -0.1f;
    f[5] = -0.2f;
    f[6] = -0.024f;
    f[7] = -0.01f;
}

s32 kpaFireAttackCheck(void) {
    s32 m;
    MarioWork* mario = marioGetPtr();
    if (!(mario->flags & MARIO_FLAG_ACTIVE)) {
        return 0;
    }
    m = KPW(mario)->attackState;
    if ((m >= 20 && m <= 23) || (m >= 40 && m <= 43)) {
        return 1;
    }
    return 0;
}

void kpaAttackStart(void) {
    MarioWork* mario = marioGetPtr();
    if (KPW(mario)->attackState == 0) {
        marioChgMot(MARIO_MOTION_STAY);
        KPW(mario)->attackState = 1;
    }
}

void kpaAttackStart2(void) {
    KpaWork* w = KPW(marioGetPtr());
    if (w->attackState == 0) {
        w->attackState = 30;
    }
}

static void kpaFireAttack(void) {
    MarioWork* mario = marioGetPtr();
    switch (KPW(mario)->attackState) {
        case 1:
            mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
            mario->airTimer = 0;
            KPW(mario)->fireRate = KPW(mario)->level == 0 ? 12 : 8;
            KPW(mario)->fireCount = 0;
            KPW(mario)->attackTimer = 0;
            KPW(mario)->attackState = 20;
            if (!(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                mario->baseSpeed = 0.0f;
                mario->kpaSpeed = 0.0f;
            }
        case 20:
            kpaChgPose("KPA_A_1A", "KPA2_A_1A");
            KPW(mario)->attackTimer = 6;
            KPW(mario)->attackState = 21;
            break;
        case 21:
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            kpaChgPose("KPA_A_1B", "KPA2_A_1B");
            KPW(mario)->attackTimer = 8;
            KPW(mario)->attackState = 22;
            kpaFireSEOn();
            break;
        case 22:
            kpaFireEntry(mario->position);
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            KPW(mario)->attackTimer = sysMsec2Frame(400);
            kpaChgPose("KPA_A_1C", "KPA2_A_1C");
            KPW(mario)->attackState = 23;
            break;
        case 23:
            kpaFireEntry(mario->position);
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            if (mario->buttonHold & PAD_BUTTON_B) {
                break;
            }
            if (KPW(mario)->fireHold != 0) {
                break;
            }
            kpaChgPose("KPA_A_1D", "KPA2_A_1D");
            KPW(mario)->attackState = 24;
            KPW(mario)->attackTimer = 6;
            kpaFireSEOff();
            break;
        case 24:
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            KPW(mario)->attackState = 0;
            kpaChgPose("KPA_S_1", "KPA2_S_1");
            break;
    }
    switch (KPW(mario)->attackState) {
        case 30:
            KPW(mario)->fireRate = KPW(mario)->level == 0 ? 12 : 8;
            KPW(mario)->fireCount = 0;
            KPW(mario)->attackTimer = 0;
            KPW(mario)->attackState = 40;
            if (!(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                mario->baseSpeed = 0.0f;
                mario->kpaSpeed = 0.0f;
            }
        case 40:
            kpaChgPose("KPA_A_1A", "KPA2_A_1A");
            KPW(mario)->attackTimer = 6;
            KPW(mario)->attackState = 41;
            break;
        case 41:
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            kpaChgPose("KPA_A_1B", "KPA2_A_1B");
            KPW(mario)->attackTimer = 8;
            KPW(mario)->attackState = 42;
            kpaFireSEOn();
            break;
        case 42:
            kpaFireEntry(mario->position);
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            KPW(mario)->attackTimer = sysMsec2Frame(400);
            kpaChgPose("KPA_A_1C", "KPA2_A_1C");
            KPW(mario)->attackState = 43;
            break;
        case 43:
            kpaFireEntry(mario->position);
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            if (mario->buttonHold & PAD_BUTTON_B) {
                break;
            }
            if (KPW(mario)->fireHold != 0) {
                break;
            }
            kpaChgPose("KPA_A_1D", "KPA2_A_1D");
            KPW(mario)->attackState = 44;
            KPW(mario)->attackTimer = 6;
            kpaFireSEOff();
            break;
        case 44:
            if (--KPW(mario)->attackTimer > 0) {
                break;
            }
            KPW(mario)->attackState = 0;
            switch ((u16)mario->currMotionId) {
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
    MarioWork* mario;
    KpaWork* w = KPW(marioGetPtr());
    w->attackState = 0;
    mario = marioGetPtr();
    if (KPW(mario)->fireSfxId != 0xFFFFFFFFU) {
        psndSFXOff(KPW(mario)->fireSfxId);
        KPW(mario)->fireSfxId = -1;
    }
}

s32 kpaGetAttackMode(void) {
    return KPW(marioGetPtr())->attackState != 0;
}

void kpaFireDelete(void) {
    if (fireefp) {
        MarioWork* mario;
        effSoftDelete((void*)fireefp);
        fireefp = 0;
        mario = marioGetPtr();
        if (KPW(mario)->fireSfxId != 0xFFFFFFFFU) {
            psndSFXOff(KPW(mario)->fireSfxId);
            KPW(mario)->fireSfxId = -1;
        }
    }
}

void kpaStrippedPool(f32* f, s32 i) {
    *f = (f32)i;
}

static void kpaFireMain(void) {
    MarioWork* mario = marioGetPtr();
    Mtx mb0;
    Mtx m80;
    Mtx m50;
    Mtx m20;
    Vec out;
    Vec zero;
    s32 flag;
    s32 lv;
    EffectEntry* fe;
    EffGonbabaBreathWork* w;
    s32 i;
    f32 f31;
    f32 f30;
    f32 f29;
    KPW(mario)->flameHit = NULL;
    flag = 0;
    if (fireefp && (f32)flag == 0.0f) {
        f32 dir;
        f32 scale;
        f32 x;
        f32 y;
        f32 z;
        s32 t;
        dir = (mario->displayDirection >= 90.0f && mario->displayDirection <= 270.0f) ? 1.0f : -1.0f;
        scale = kpaGetBaseScale(kpaGetLevel());
        f30 = 40.0f * dir * scale + mario->position.x;
        t = (marioGetPtr()->stageFlags & 1) ^ 1;
        y = mario->position.y + (20.0f * scale + (t == 1 ? 6.0f : 0.0f));
        z = mario->position.z;
        ((EffGonbabaBreathWork*)fireefp->userdata)->position.x = f30;
        ((EffGonbabaBreathWork*)fireefp->userdata)->position.y = y;
        ((EffGonbabaBreathWork*)fireefp->userdata)->position.z = z;
        {
            EffectEntry* w2 = ((EffGonbabaBreathWork*)fireefp->userdata)->child;
            if (w2) {
                ((EffGonbabaBreathWork*)w2->userdata)->position.x = f30;
                ((EffGonbabaBreathWork*)((EffGonbabaBreathWork*)fireefp->userdata)->child->userdata)->position.y = y;
                ((EffGonbabaBreathWork*)((EffGonbabaBreathWork*)fireefp->userdata)->child->userdata)->position.z = z;
            }
        }
#if VERSION <= VERSION_DEMO_US
        // the demo checks the flame against every hit at every level, without the size cut-off
        {
            f32 sc;
            f32 base;
            fe = fireefp;
            camGetPtr(CAMERA_3D);
            w = (EffGonbabaBreathWork*)fe->userdata;
            base = w->scale;
            PSMTXTrans(m80, w->position.x, w->position.y, w->position.z);
            PSMTXRotRad(m50, 'y', 0.017453292f * (w->yaw - camGetPtr(CAMERA_3D)->viewYaw));
            if (w->yaw > 90.0f && w->yaw < 270.0f) {
                PSMTXScale(mb0, w->scale, w->scale, -w->scale);
            } else {
                PSMTXScale(mb0, w->scale, w->scale, w->scale);
            }
            PSMTXConcat(m80, m50, m80);
            PSMTXConcat(m80, mb0, m20);
            w = w + 1;
            for (i = 1; i < fe->count; i++, w++) {
                if (((i - 1) & 3) == 0 && w->delay == 0 && w->life > 0x10) {
                    void* hit;
                    sc = 7.0f * w->scale;
                    PSMTXTrans(m80, w->position.x, w->position.y, w->position.z);
                    PSMTXScale(mb0, sc, sc, sc);
                    PSMTXConcat(m80, mb0, m80);
                    PSMTXConcat(m20, m80, m80);
                    zero = *(Vec*)kpaZeroVec;
                    PSMTXMultVec(m80, &zero, &out);
                    hit = kpaFlameHitCheck(out.x, out.y, out.z, sc * base);
                    if (hit) {
                        KPW(mario)->flameHit = hit;
                        break;
                    }
                }
            }
        }
#else
        lv = kpaGetLevel();
        if (lv != 0) {
            fe = fireefp;
            camGetPtr(CAMERA_3D);
            w = (EffGonbabaBreathWork*)fe->userdata;
            f29 = w->scale;
            PSMTXTrans(m80, w->position.x, w->position.y, w->position.z);
            PSMTXRotRad(m50, 'y', 0.017453292f * (w->yaw - camGetPtr(CAMERA_3D)->viewYaw));
            if (w->yaw > 90.0f && w->yaw < 270.0f) {
                PSMTXScale(mb0, w->scale, w->scale, -w->scale);
            } else {
                PSMTXScale(mb0, w->scale, w->scale, w->scale);
            }
            PSMTXConcat(m80, m50, m80);
            PSMTXConcat(m80, mb0, m20);
            w = w + 1;
            for (i = 1; i < fe->count; i++, w++) {
                if (((i - 1) & 3) == 0 && w->delay == 0 && w->life > 0x10) {
                    void* hit;
                    f31 = 7.0f * w->scale;
                    f30 = f31 * f29;
                    if (!(f30 < 7.0f)) {
                        PSMTXTrans(m80, w->position.x, w->position.y, w->position.z);
                        PSMTXScale(mb0, f31, f31, f31);
                        PSMTXConcat(m80, mb0, m80);
                        PSMTXConcat(m20, m80, m80);
                        zero = *(Vec*)kpaZeroVec;
                        PSMTXMultVec(m80, &zero, &out);
                        hit = kpaFlameHitCheck(out.x, out.y, out.z, f30);
                        if (hit) {
                            KPW(mario)->flameHit = hit;
                            break;
                        }
                    }
                }
            }
        }
#endif
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
    MarioWork* mario = marioGetPtr();
    if (mario->characterId != 2) {
        return 0;
    }
    if (mario->currMotionId == MARIO_MOTION_HIP_2) {
        r = 1;
    }
    return r;
}

s32 kpaJumpChk(void) {
    return ((MarioWork*)marioGetPtr())->airTimer != 0;
}

void kpaPauseSE2(void) {
    psndSFXOn(SFX_NAME_WORD(kpaPauseSeTable[irand(28)] | 0x20000));
}
