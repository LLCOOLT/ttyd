// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "driver/itemdrv.h"
#include "party.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/mtx.h>

extern void unk_800c92c4(PartyEntry* party);
extern void partyRecordFootmark(PartyEntry* party);
extern void partyWalkInit(PartyEntry* party, s32 mode);
extern void party_move_mode_stay(PartyEntry* party);
extern void party_move_mode_walk(PartyEntry* party);
extern void party_move_mode_behind_mario(PartyEntry* party);
extern void party_move_mode_beside_mario(PartyEntry* party);
extern void partyGoodbyeInit(PartyEntry* party);
extern s32 partyGoodbyeMain(PartyEntry* party);
extern void partyChgRunMode(PartyEntry* party, s32 mode);

#define PB(p, o) (*(u8*)((u8*)(p) + (o)))
#define PH(p, o) (*(s16*)((u8*)(p) + (o)))
#define PW(p, o) (*(u32*)((u8*)(p) + (o)))

#ifndef NONMATCHING
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".sdata") u32 gap_08_804188DC_sbss[1]; // FAKE: target .sbss pad after nokoSe (uninit statics emit in reverse order)
#endif
static s32 nokoSe;
double sin(double);
double cos(double);
#include "driver/hitdrv.h"
#include "mario/mario_sbr.h"

extern void itemNokoForceGet(ItemEntry* entry);
#include "eff/eff_kemu_test.h"
#include "eff/n64/eff_small_star_n64.h"
#include "mario/mariost.h"
#ifndef NONMATCHING
extern void marioChgMot(void);
#endif
#ifndef NONMATCHING
extern void effKemuTestDrawCam(void);
#endif
extern ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range);
extern void itemPickUp(ItemEntry* entry);
extern void* mobjHitObjPtrToPtr(HitEntry* hit);
extern void marioChkWallAround(Vec* pos, s32 a1, f32 a2, f32 angle, f32 radius, f32 height);
extern void partyGetMoveDirSpd(PartyEntry* party, f32* dir, f32* spd);
extern void partyGetReturnPos(Vec* pos);
extern void partyMove(PartyEntry* party);
extern void partyMoveNoHosei(PartyEntry* party);
extern void partyClearJumpPara(PartyEntry* party);
extern void partyChgPose(PartyEntry* party, char* pose);
extern void marioChgSmallJumpMotion(void);
extern s32 marioKeyOffChk(void);
extern BOOL marioChkKey(void);
extern void marioAdjustMoveDir(void);
extern BOOL marioChkInScreen(s32 x, s32 y);
extern f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
extern f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
extern void movePos(float* ret_sin, float* ret_cos, f32 a3, f32 degree);
extern f32 toMovedirSimple(f32 a);
extern f32 toMovedir2(f32 a, f32 b);
extern s32 sysMsec2Frame(s32 msec);
double sqrt(double);
void nokonoko_finish(PartyEntry* party);
HitEntry* ccwall(PartyEntry* party, s32 mode);
void lookupSafetyPosSub(Vec pos, f32 height, f32 angle, Vec* out);
void lookupSafetyPos3(Vec pos, f32 height, Vec* out);
void lookupSafetyPos2(Vec pos, f32 height, Vec* out);
u32 lookupSafetyPos(Vec pos, f32 height, Vec* out);

#ifdef NONMATCHING
s32 nokonokoGetStatus(PartyEntry* party) {
    u32 m;
    s32 status;
    if (party == NULL) {
        return 0;
    }
    if (party->currentMemberId != 2 || !(party->flags & 0x100)) {
        return 0;
    }
    status = 7;
    m = party->useMotionId;
    if (m <= 2) {
        return 1;
    }
    if (m >= 10 && m <= 13) {
        return 2;
    }
    if (m >= 20 && m <= 21) {
        return 3;
    }
    if (m >= 50 && m <= 71) {
        return 4;
    }
    if (m >= 80 && m <= 100) {
        return 5;
    }
    if (m >= 110 && m <= 114) {
        status = 6;
    }
    return status;
}
#endif

#ifdef NONMATCHING
BOOL nokonoko_holdItem(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party == NULL) {
        return FALSE;
    }
    if (party->currentMemberId != 2 || !(party->flags & 0x100)) {
        return FALSE;
    }
    return PW(party, 0x174) != 0;
}
#endif

#ifdef NONMATCHING
void nokonoko_bye(PartyEntry* party) {
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyGoodbyeInit(party);
    }
    if (partyGoodbyeMain(party)) {
        partyChgRunMode(party, 14);
    }
}
#endif

#ifdef NONMATCHING
void nokonoko_init(PartyEntry* party) {
    party->field_32 [1] = 2;
    party->field_32 [0] = 0;
    party->height = 37.0f;
    party->width = 24.0f;
    nokoSe = -1;
}
#endif

#ifdef NONMATCHING
void nokonoko_move(PartyEntry* party) {
    marioGetPtr();
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyWalkInit(party, 1);
    }
    unk_800c92c4(party);
    partyRecordFootmark(party);
    switch (PB(party, 0x3b)) {
    case 0:
        party_move_mode_stay(party);
        break;
    case 1:
        party_move_mode_walk(party);
        break;
    case 2:
        party_move_mode_behind_mario(party);
        break;
    case 3:
        party_move_mode_beside_mario(party);
        break;
    case 4:
        break;
    }
}
#endif

#ifdef NONMATCHING
void unk_800cd9a0(void) {
    PartyEntry* party;
    marioGetPtr();
    party = partyGetPtr(marioGetPartyId());
    if (nokonokoGetStatus(party) != 0) {
        if (party->flags & 0x100) {
            marioGetPtr();
            if ((u32)nokoSe != 0xFFFFFFFFU) {
                psndSFXOff(nokoSe);
                nokoSe = -1;
            }
            party->flags &= ~0x100;
            party->flags &= ~0x04000000;
            party->flags &= ~0x01000000;
            party->flags &= ~0x02000000;
            party->flags2 &= ~0x20;
            party->flags2 &= ~0x10;
            party->height = 37.0f;
            PW(party, 0x178) = 0;
            PW(party, 0x17c) = 0;
            PW(party, 0x180) = 0;
        }
        if (party->runMode != 8 && party->runMode != 0xd) {
            partyChgRunMode(party, 2);
            PB(party, 0x3b) = 0;
        }
    }
}
#endif

#ifdef NONMATCHING
void nokonoko_use_post(PartyEntry* party) {
    if (PW(party, 0x174) != 0) {
        itemNokoForceGet((ItemEntry*)PW(party, 0x174));
        PW(party, 0x174) = 0;
    }
    marioGetPtr();
    if ((u32)nokoSe != 0xFFFFFFFFU) {
        psndSFXOff(nokoSe);
        nokoSe = -1;
    }
    party->flags &= ~0x100;
    party->flags &= ~0x04000000;
    party->flags &= ~0x01000000;
    party->flags &= ~0x02000000;
    party->flags2 &= ~0x20;
    party->flags2 &= ~0x10;
    party->height = 37.0f;
    PW(party, 0x178) = 0;
    PW(party, 0x17c) = 0;
    PW(party, 0x180) = 0;
}
#endif

#define PF(p, o) (*(f32*)((u8*)(p) + (o)))
#define PS32(p, o) (*(s32*)((u8*)(p) + (o)))
typedef struct NokoPad94 {
    u8 pad[0x94];
    Vec v;
} NokoPad94;
#define PV(p, o) (((NokoPad94*)(p))->v)
#define MH(p, o) (*(u16*)((u8*)(p) + (o)))

static inline void noko_se_off(void) {
    marioGetPtr();
    if ((u32)nokoSe != 0xFFFFFFFFU) {
        psndSFXOff(nokoSe);
        nokoSe = -1;
    }
}

static inline void noko_spin(PartyEntry* party) {
    f32 dir;
    if (revise360(party->targetDir - PF(party, 0xf8)) > 180.0f) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    party->displayDirection = revise360(50.0f * dir + party->displayDirection);
}

static inline void noko_star(PartyEntry* party, s32 n) {
    f32 c = (f32)cos(6.2831855f * party->targetDir / 360.0f);
    f32 s = (f32)sin(6.2831855f * party->targetDir / 360.0f);
    effSmallStarN64Entry(3, n, party->position.x, party->position.y + party->height, party->position.z, s, -1.0f, -c);
}

#define NOKO_ITEM(party, body)                                                                              if (PW(party, 0x174) == 0) {                                                                                  PW(party, 0x174) = (u32)itemNearDistCheck(party->position.x, party->position.y, party->position.z,                                                   0.5f * party->width + 12.0f);                                    if (PW(party, 0x174) != 0) {                                                                                  itemPickUp((ItemEntry*)PW(party, 0x174));                                                                 body                                                                                                  }                                                                                                     }
#ifdef NONMATCHING
void nokonoko_use(PartyEntry* party) {
    Vec out;
    Vec out2;
    Vec rp;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 mx;
    f32 mz;
    f32 dir;
    f32 spd;
    f32 s2x;
    u8* new_var;
    f32 s2y;
    f32 s2z;
    f32 s3x;
    f32 s3y;
    f32 s3z;
    u32 flags;
    HitEntry* hit;
    BOOL b;
    f32 dy;
    f32 dx;
    f32 qx;
    f32 qy;
    f32 qz;
    f32 dz;
    MarioWork* mario = party->playerPtr;

    if (!(party->flags & 0x80000000) && marioKeyOffChk()) {
        marioGetScreenPos(party->position, &sx, &sy, &sz);
        if (!marioChkInScreen((s32)sx, (s32)sy)) {
            mx = mario->position.x;
            mz = mario->position.z;
            movePos(&mx, &mz, 160.0f, angleABf(mario->position.x, mario->position.z, party->position.x, party->position.z));
            party->position.x = mx;
            party->position.z = mz;
            nokonoko_finish(party);
            return;
        }
    }
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        PW(party, 0x174) = 0;
        PW(party, 0x178) = 0;
        PW(party, 0x17c) = 0;
        PW(party, 0x180) = 0;
        if (party->flags & 0x80000000) {
            if (party->unk16C > 0) {
                PH(party, 0x17e) |= 1;
            }
        } else {
            PH(party, 0x17e) &= ~1;
        }
        party->useMotionId = 0;
    }

    switch (party->useMotionId) {
    case 0:
        if (mario->currMotionId == 0x20 || mario->currMotionId == 0x1f) {
            party->useMotionId = 70;
            break;
        }
        partyClearJumpPara(party);
        party->flags |= 0x04000000;
        party->flags2 |= 0x10;
        partyChgPose(party, "PNK_K_2");
        party->height = 18.5f;
        party->useMotionId = 1;
        party->moveFrames = 100;
        PW(party, 0x174) = 0;
        PH(party, 0x17c) = 0;
        marioAdjustMoveDir();
        mario->baseSpeed = 0.0f;
        PV(party, 0x94) = mario->position;
        movePos(&party->moveTarget.x, &party->moveTarget.z, 2.0f, toMovedirSimple(mario->displayDirectionTarget));
        party->moveFrames = 4;
        party->velY = 0.0f;
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        party->moveSpeed = distABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z) /
                           (f32)party->moveFrames;
        party->displayDirection = revise360(45.0f + party->displayDirection);
        party->useMotionId = 1;
        marioChgSmallJumpMotion();
        mario->trigFlags |= 0x20000;
        mario->baseSpeed = 0.0f;
        break;
    case 1:
        if (mario->currMotionId == 0x20 || mario->currMotionId == 0x1f) {
            party->useMotionId = 70;
            break;
        }
        party->displayDirection = revise360(45.0f + party->displayDirection);
        party->position.x += (PV(party, 0x94).x - party->position.x) / (f32)party->moveFrames;
        party->position.y += (PV(party, 0x94).y - party->position.y) / (f32)party->moveFrames;
        party->position.z += (PV(party, 0x94).z - party->position.z) / (f32)party->moveFrames;
        if (--party->moveFrames > 0) {
            break;
        }
        party->position = PV(party, 0x94);
        party->moveSpeed = 0.0f;
        party->displayDirectionTarget = mario->displayDirectionTarget;
        party->displayDirection = mario->displayDirectionTarget;
        party->useMotionId = 2;
        partyChgPose(party, "PNK_A_1");
    case 2:
        if (mario->currMotionId == 0x20 || mario->currMotionId == 0x1f) {
            party->useMotionId = 70;
            break;
        }
        if (mario->hitobjStandOn == NULL) {
            break;
        }
        marioChgMot(3);
        mario->flags |= 0x80;
        mario->baseSpeed = 0.0f;
        party->useMotionId = 10;
        party->moveFrames = 15;
        party->moveSpeed = 0.0f;
        party->moveDistance = 0.0f;
        party->targetDir = toMovedir(mario->displayDirectionTarget);
        psndSFXOn_3D((const char*)0x92d, &party->position);
        break;
    case 10:
        psndSFXOn_3D((const char*)0x92a, &party->position);
        noko_star(party, 3);
        party->flags |= 0x04000000;
        party->flags |= 0x01000000;
        party->useMotionId = 11;
    case 11:
        party->moveSpeed += 2.0f;
        if (party->moveSpeed > 10.0f) {
            party->moveSpeed = 10.0f;
        }
    case 12:
        noko_spin(party);
        if (gp->retraceCount & 1) {
            effKemuTestDrawCam(effKemuTestEntry(0, party->position.x, party->height / 4.0f + party->position.y,
                                                party->position.z, 0.3f),
                               party->camId);
        }
        party->moveDistance += party->moveSpeed;
        NOKO_ITEM(party, party->useMotionId = 50; psndSFXOn_3D((const char*)0x92c, &party->position); noko_star(party, 1); break;)
        if (ccwall(party, 0) != NULL) {
            party->useMotionId = 50;
            psndSFXOn_3D((const char*)0x92c, &party->position);
            noko_star(party, 1);
            break;
        }
        if (party->moveDistance >= 120.0f) {
            party->useMotionId = 12;
            party->moveSpeed += 0.15f * (-1.0f - party->moveSpeed);
            if (party->moveSpeed <= 0.0f) {
                party->moveSpeed = 0.0f;
                if (!(party->flags & 0x80000000)) {
                    if (MH(mario, 0x246) & 0x400) {
                        party->useMotionId = 13;
                        party->moveFrames = 0;
                    } else {
                        party->useMotionId = 50;
                    }
                } else if (PH(party, 0x17e) & 1) {
                    party->moveFrames = 5;
                    party->useMotionId = 21;
                    PH(party, 0x17c) = 1;
                    if ((u32)nokoSe == 0xFFFFFFFFU) {
                        nokoSe = psndSFXOn_3D((const char*)0x92e, &party->position);
                    }
                } else {
                    party->useMotionId = 50;
                }
            }
        }
        break;
    case 13:
        if (++party->moveFrames >= 5) {
            party->moveFrames = 5;
            party->useMotionId = 20;
            PH(party, 0x17c) = 1;
            if ((u32)nokoSe == 0xFFFFFFFFU) {
                nokoSe = psndSFXOn_3D((const char*)0x92e, &party->position);
            }
        }
    case 20:
        noko_spin(party);
        if (gp->retraceCount % 30 == 0) {
            effKemuTestDrawCam(effKemuTestEntry(5, party->position.x, party->position.y, party->position.z, 1.0f),
                               party->camId);
        }
        if (ccwall(party, 0) != NULL) {
            party->useMotionId = 50;
            psndSFXOn_3D((const char*)0x92c, &party->position);
            noko_star(party, 1);
            noko_se_off();
            break;
        }
        NOKO_ITEM(party, party->useMotionId = 50; psndSFXOn_3D((const char*)0x92c, &party->position); noko_star(party, 1); noko_se_off(); break;)
        if (!(party->flags & 0x80000000)) {
            if (mario->currMotionId == 0x19 || mario->currMotionId == 0x14 || mario->currMotionId == 0x18 || mario->currMotionId == 0x16 || (u16)(mario->currMotionId - 0x1f) <= 1 ||
                (mario->flags & 0x20) || !marioChkKey()) {
                nokonoko_finish(party);
                noko_se_off();
                break;
            }
            if (MH(mario, 0x246) & 0x400) {
                break;
            }
            party->useMotionId = PH(party, 0x17c) != 0 ? 80 : 50;
            noko_se_off();
            break;
        }
        if (PH(party, 0x17e) & 1) {
            party->useMotionId = 80;
        } else {
            party->useMotionId = 50;
        }
        noko_se_off();
        break;
    case 21:
        noko_spin(party);
        if (gp->retraceCount % 30 == 0) {
            effKemuTestDrawCam(effKemuTestEntry(5, party->position.x, party->position.y, party->position.z, 1.0f),
                               party->camId);
        }
        break;
    }

    new_var = ((u8*)party) + 0x128;
    switch (party->useMotionId) {
    case 50:
        partyClearJumpPara(party);
        party->useMotionId = 51;
        party->moveSpeed = 0.0f;
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        psndSFXOn_3D((const char*)0x92b, &party->position);
        break;
    case 51: {
        f32 lim = PH(party, 0x17c) != 0 ? 20.0f : 10.0f;
        party->moveSpeed += 0.3f * (lim - party->moveSpeed);
        if (party->moveSpeed >= lim) {
            party->moveSpeed = lim;
            if ((*(f32*)new_var) < 10.0f) {
                party->useMotionId = 52;
            }
        }
    }
    case 52:
        if (ccwall(party, 1) != NULL) {
            partyGetMoveDirSpd(party, &dir, &spd);
            marioChkWallAround(&party->position, 1, spd, dir, party->width, party->height);
            party->useMotionId = 70;
            psndSFXOn_3D((const char*)0x92c, &party->position);
            noko_star(party, 1);
            return;
        }
        noko_spin(party);
        party->moveSpeed += 0.1f * (-1.0f - party->moveSpeed);
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= 0.0f) {
            (*(f32*)new_var) = 0.0f;
            party->useMotionId = 53;
            party->moveSpeed += 0.1f * (-1.0f - party->moveSpeed);
            PF(party, 0x178) = 50.0f;
        }
        break;
    case 53:
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 70;
            return;
        }
        PF(party, 0x178) -= 2.2f;
        if (PF(party, 0x178) <= 0.0f) {
            PF(party, 0x178) = 0.0f;
        }
        noko_spin(party);
        party->moveSpeed += (-2.0f - party->moveSpeed) * (PH(party, 0x17c) != 0 ? 0.2f : 0.1f);
        (*(f32*)new_var) -= party->moveSpeed;
        if (party->moveSpeed <= 0.0f) {
            party->moveSpeed = 0.0f;
            flags = lookupSafetyPos(PV(party, 0x94), party->height, &out);
            if (party->field_138 != NULL && ((u32)(flags - 1) <= 1 || flags == 4 || flags == 8)) {
                party->useMotionId = 70;
                break;
            }
            switch (flags) {
            case 3:
                lookupSafetyPosSub(PV(party, 0x94), party->height, 135.0f, &out);
                break;
            case 5:
                lookupSafetyPosSub(PV(party, 0x94), party->height, 315.0f, &out);
                break;
            case 10:
                lookupSafetyPosSub(PV(party, 0x94), party->height, 225.0f, &out);
                break;
            case 12:
                lookupSafetyPosSub(PV(party, 0x94), party->height, 315.0f, &out);
                break;
            case 7:
            case 14:
            case 15:
                party->useMotionId = 70;
                break;
            case 1:
                lookupSafetyPosSub(PV(party, 0x94), party->height, 270.0f, &out);
                break;
            case 8:
                lookupSafetyPos3(PV(party, 0x94), party->height, &out);
                break;
            default:
                lookupSafetyPos2(PV(party, 0x94), party->height, &out);
                break;
            }
            party->useMotionId = 54;
            PV(party, 0x94) = out;
            (*(f32*)new_var) = distABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
            party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        }
        break;
    case 54:
        noko_spin(party);
        party->moveSpeed += 0.5f;
        if (party->moveSpeed >= 4.0f) {
            party->moveSpeed = 4.0f;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= 10.0f) {
            party->useMotionId = 70;
            party->moveSpeed = 0.0f;
            return;
        }
        break;
    case 55:
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 70;
            return;
        }
        noko_spin(party);
        PF(party, 0x178) -= 2.2f;
        if (PF(party, 0x178) <= 0.0f) {
            PF(party, 0x178) = 0.0f;
        }
        party->moveSpeed += (-2.0f - party->moveSpeed) * (PH(party, 0x17c) != 0 ? 0.2f : 0.1f);
        if (party->moveSpeed <= 0.0f) {
            party->useMotionId = 70;
            party->moveSpeed = 0.0f;
            return;
        }
        break;
    case 70:
        dx = party->position.x - mario->position.x;
        dy = party->position.y - mario->position.y;
        dz = party->position.z - mario->position.z;
        qx = dx * dx;
        qy = dy * dy;
        qz = dz * dz;
        if ((f32)sqrt(qz + (qx + qy)) < 5.0f) {
            f32 a;
            a = mario->directionView + (mario->directionView >= 180.0 ? -90.0f : 90.0f);
            movePos(&party->position.x, &party->position.z, 0.5f * mario->wPlayerCollisionBox.x, a);
            ccwall(party, 1);
        }
        party->moveSpeed = 0.0f;
        party->flags2 &= ~0x10;
        party->flags2 |= 0x20;
        party->useMotionId = 71;
        break;
    case 71:
        if (PW(party, 0x174) != 0) {
            itemNokoForceGet((ItemEntry*)PW(party, 0x174));
            PW(party, 0x174) = 0;
        }
        nokonoko_finish(party);
        return;
    }

    switch (party->useMotionId) {
    case 80:
        party->useMotionId = 81;
        party->moveSpeed = 0.0f;
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        (*(f32*)new_var) += 75.0f;
        psndSFXOn_3D((const char*)0x92b, &party->position);
    case 81:
        noko_spin(party);
        party->moveSpeed += 3.0f;
        if (party->moveSpeed >= 18.0f) {
            party->moveSpeed = 18.0f;
        }
        NOKO_ITEM(party, psndSFXOn_3D((const char*)0x92c, &party->position); noko_star(party, 1);)
        hit = ccwall(party, 1);
        if (hit != NULL) {
            if (!(hitGetAttr(hit) & 0x80000000)) {
                party->useMotionId = 100;
                return;
            }
            mobjHitObjPtrToPtr(hit);
            party->useMotionId = 110;
            return;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= 20.0f) {
            party->useMotionId = 82;
        }
        break;
    case 82:
        noko_spin(party);
        party->moveSpeed += 0.35f * (-1.0f - party->moveSpeed);
        NOKO_ITEM(party, psndSFXOn_3D((const char*)0x92c, &party->position); noko_star(party, 1);)
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 100;
            break;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= 0.0f) {
            (*(f32*)new_var) = distABf(PV(party, 0x94).x, PV(party, 0x94).z, party->position.x, party->position.z);
            party->useMotionId = 84;
            PF(party, 0x178) = 50.0f;
            party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        }
        break;
    case 84:
        noko_spin(party);
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 100;
            break;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= 30.0f) {
            party->useMotionId = 86;
            party->moveSpeed = 0.0f;
            party->moveFrames = sysMsec2Frame(500);
        }
        break;
    case 86:
        noko_spin(party);
        if (--party->moveFrames <= 0) {
            party->useMotionId = 100;
        }
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 100;
        }
        break;
    case 100:
        ccwall(party, 1);
        dy = party->position.x - mario->position.x;
        dx = party->position.y - mario->position.y;
        dz = party->position.z - mario->position.z;
        qx = dy * dy;
        qy = dx * dx;
        qz = dz * dz;
        if ((f32)sqrt(qz + (qx + qy)) < 5.0f) {
            f32 a;
            a = mario->directionView + (mario->directionView >= 180.0 ? 90.0f : -90.0f);
            movePos(&party->position.x, &party->position.z, 0.5f * mario->wPlayerCollisionBox.x, a);
            ccwall(party, 1);
        }
        party->moveSpeed = 0.0f;
        party->flags2 &= ~0x10;
        if (PW(party, 0x174) != 0) {
            itemNokoForceGet((ItemEntry*)PW(party, 0x174));
            PW(party, 0x174) = 0;
        }
        if (party->field_138 == NULL) {
            party->useMotionId = 88;
            break;
        }
        if (PW(party, 0x174) != 0) {
            itemNokoForceGet((ItemEntry*)PW(party, 0x174));
            PW(party, 0x174) = 0;
        }
        nokonoko_finish(party);
        return;
    case 88:
        party->moveSpeed = 0.0f;
        flags = lookupSafetyPos(PV(party, 0x94), party->height, &out2);
        if (party->field_138 != NULL && ((u32)(flags - 1) <= 1 || flags == 4 || flags == 8)) {
            party->useMotionId = 70;
            break;
        }
        switch (flags) {
        case 3:
            lookupSafetyPosSub(PV(party, 0x94), party->height, 135.0f, &out2);
            break;
        case 5:
            lookupSafetyPosSub(PV(party, 0x94), party->height, 315.0f, &out2);
            break;
        case 10:
            lookupSafetyPosSub(PV(party, 0x94), party->height, 225.0f, &out2);
            break;
        case 12:
            lookupSafetyPosSub(PV(party, 0x94), party->height, 315.0f, &out2);
            break;
        case 7:
        case 14:
        case 15:
            party->useMotionId = 70;
            break;
        case 1:
            lookupSafetyPosSub(PV(party, 0x94), party->height, 270.0f, &out2);
            break;
        case 8:
            lookupSafetyPos3(PV(party, 0x94), party->height, &out2);
            break;
        default:
            lookupSafetyPos2(PV(party, 0x94), party->height, &out2);
            break;
        }
        party->useMotionId = 90;
        PV(party, 0x94) = out2;
        (*(f32*)new_var) = distABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        PF(party, 0x178) = 50.0f;
        break;
    case 90:
        noko_spin(party);
        party->moveSpeed += 0.5f;
        if (party->moveSpeed >= 4.0f) {
            party->moveSpeed = 4.0f;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= 10.0f) {
            party->useMotionId = 70;
            party->moveSpeed = 0.0f;
        }
        break;
    case 110:
        party->moveSpeed = 0.0f;
        party->velY = 15.0f;
        party->accelY = 0.0f;
        party->moveFrames = sysMsec2Frame(1000);
        party->useMotionId = 111;
    case 111:
        party->position.y += party->velY;
        marioGetScreenPos(party->position, &s2x, &s2y, &s2z);
        if (s2y <= -300.0f) {
            party->moveFrames = sysMsec2Frame(800);
            party->useMotionId = 112;
        }
        break;
    case 112:
        if (--party->moveFrames > 0) {
            break;
        }
        if (!(party->flags & 0x80000000)) {
            partyGetReturnPos(&rp);
        } else {
            rp = mario->position;
            b = FALSE;
            if (mario->displayDirectionTarget >= 90.0f && mario->displayDirectionTarget <= 270.0f) {
                b = TRUE;
            }
            movePos(&rp.x, &rp.z, 30.0f, toMovedir2(b ? 0.0f : 180.0f, -30.0f));
        }
        party->position.x = rp.x;
        party->position.y = 1000.0f + rp.y;
        party->position.z = rp.z;
        party->velY = 0.0f;
        party->accelY = -1.0f;
        party->moveSpeed = 0.0f;
        party->flags |= 0x20;
        party->flags |= 0x02000000;
        party->flags &= ~0x04000000;
        party->flags &= ~0x01000000;
        party->flags2 &= ~0x20;
        party->flags2 &= ~0x10;
        party->height = 37.0f;
        party->useMotionId = 113;
        break;
    case 113:
        marioGetScreenPos(party->position, &s3x, &s3y, &s3z);
        if (s3y > 240.0f) {
            party->flags &= ~0x02000000;
        }
        partyMove(party);
        if (party->velY <= -6.0f) {
            party->accelY = 0.0f;
            party->velY = -6.0f;
        }
        if (party->position.y < -2000.0f) {
            party->position = mario->position;
            party->position.y += 200.0f;
        }
        if (party->field_138 != NULL) {
            party->displayDirectionTarget = mario->displayDirectionTarget;
            party->displayDirection = party->displayDirectionTarget;
            if (!((hitGetAttr(party->field_138) >> 9) & 1)) {
                party->useMotionId = 114;
                party->moveFrames = 30;
            }
        }
        break;
    case 114:
        if (--party->moveFrames > 0) {
            break;
        }
        nokonoko_finish(party);
        return;
    }
    if (party->useMotionId != 100) {
        partyMoveNoHosei(party);
    }
}
#endif

#ifdef NONMATCHING
void nokonoko_finish(PartyEntry* party) {
    if (party != NULL && party->currentMemberId == 2 && (party->flags & 0x100)) {
        nokonoko_use_post(party);
        if (party->runMode != 9) {
            if (!(party->flags & 0x80000000)) {
                partyChgRunMode(party, 2);
                PB(party, 0x3b) = 0;
            } else {
                party->flags &= 0x7FFFFFFF;
                partyChgRunMode(party, 0);
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void nokotaro_hold_cancel(PartyEntry* party) {
    party->useMotionId = 20;
}
#endif

#ifdef NONMATCHING
HitEntry *ccwall(PartyEntry *party, s32 mode)
{
  f32 s;
  f32 c;
  f32 dist;
  f32 hx;
  f32 hy;
  f32 hz;
  f32 nx;
  f32 ny;
  f32 nz;
  f32 s1;
  f32 c1;
  f32 s2;
  f32 c2;
  f32 s3;
  f32 c3;
  HitEntry *hit;
  f32 py;
  f32 vx;
  f32 vz;
  f32 d;
  f32 y0;
  f32 y;
  f32 z;
  f32 x;
  f32 yofs;
  f32 w;
  yofs = 10.0f;
  y0 = party->position.y + party->height;
  x = party->position.x;
  dist = party->height + 30.0f;
  y0 = yofs + y0;
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y0, party->position.z, 0.0f, -1.0f, 0.0f);
  if (((hitGetAttr(hit) >> 9) & 1) == 1)
  {
    hit = NULL;
  }
  party->field_138 = hit;
  if (hit != (NULL))
  {
    hy = ((f32) ((s32) ((100.0f * hy) + 0.5f))) / 100.0f;
    py = ((f32) ((s32) ((100.0f * party->position.y) + 0.5f))) / 100.0f;
    if (__fabsf(py - hy) <= 11.0f)
    {
      if (py <= hy)
      {
        if (mode == 0)
        {
          party->position.y = hy;
          if (__fabsf(py - hy) >= 1.0f)
          {
            PH(party, 0x17e) |= 2;
          }
        }
      }
      else
      {
        if (((PH(party, 0x17e)) & 2) && (mode == 1))
        {
          party->position.y = hy;
        }
        if (__fabsf(py - hy) <= 6.0f)
        {
          party->position.y = hy;
        }
      }
    }
  }
  PW(party, 0x130) = 0;
  PW(party, 0x12c) = 0;
  yofs += 1.0f;
  x = party->position.x;
  z = party->position.z;
  y = party->position.y + yofs;
  dist = (0.5f * party->width) + party->moveSpeed;
  sincosf(&s, &c, party->targetDir);
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, 0.0f, c);
  if ((hit != (NULL)) && (!(hitGetAttr(hit) & 5)))
  {
    sincosf(&s1, &c1, 180.0f + party->targetDir);
    party->position.x = hx + (0.5f * (s1 * party->width));
    party->position.z = hz + (0.5f * (c1 * party->width));
    vx = s * party->moveSpeed;
    vz = c * party->moveSpeed;
    d = (vx * nx) + (vz * nz);
    party->position.x += 0.5f * (vx - (d * nx));
    party->position.z += 0.5f * (vz - (d * nz));
    if (((PH(party, 0x17c)) != 0) || (mode == 0))
    {
      PW(party, 0x130) = (u32) hit;
    }
    PW(party, 0x12c) = (u32) hit;
    return hit;
  }
  w = 0.4f * party->width;
  z = (w * ((f32) cos((3.1415927f * (party->targetDir - 90.0f)) / 180.0f))) + party->position.z;
  x = (w * ((f32) sin((3.1415927f * (party->targetDir - 90.0f)) / 180.0f))) + party->position.x;
  y = party->position.y + yofs;
  dist = (0.4f * party->width) + party->moveSpeed;
  sincosf(&s, &c, party->targetDir);
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, 0.0f, c);
  if ((hit != (NULL)) && (!(hitGetAttr(hit) & 5)))
  {
    sincosf(&s2, &c2, 180.0f + party->targetDir);
    party->position.x = hx + (0.5f * (s2 * party->width));
    party->position.z = hz + (0.5f * (c2 * party->width));
    party->position.z -= w * ((f32) cos((3.1415927f * (party->targetDir - 90.0f)) / 180.0f));
    party->position.x -= w * ((f32) sin((3.1415927f * (party->targetDir - 90.0f)) / 180.0f));
    vx = s * party->moveSpeed;
    vz = c * party->moveSpeed;
    d = (vx * nx) + (vz * nz);
    party->position.x += 0.5f * (vx - (d * nx));
    party->position.z += 0.5f * (vz - (d * nz));
    if (((PH(party, 0x17c)) != 0) || (mode == 0))
    {
      PW(party, 0x130) = (u32) hit;
    }
    PW(party, 0x12c) = (u32) hit;
    party->position.x = hx;
    return hit;
  }
  w = 0.4f * party->width;
  z = (w * ((f32) cos((3.1415927f * (90.0f + party->targetDir)) / 180.0f))) + party->position.z;
  x = (w * ((f32) sin((3.1415927f * (90.0f + party->targetDir)) / 180.0f))) + party->position.x;
  y = party->position.y + yofs;
  dist = (0.4f * party->width) + party->moveSpeed;
  sincosf(&s, &c, party->targetDir);
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, 0.0f, c);
  if ((hit != (NULL)) && (!(hitGetAttr(hit) & 5)))
  {
    sincosf(&s3, &c3, 180.0f + party->targetDir);
    party->position.x = hx + (0.5f * (s3 * party->width));
    party->position.z = hz + (0.5f * (c3 * party->width));
    party->position.z -= w * ((f32) cos((3.1415927f * (90.0f + party->targetDir)) / 180.0f));
    party->position.x -= w * ((f32) sin((3.1415927f * (90.0f + party->targetDir)) / 180.0f));
    vx = s * party->moveSpeed;
    vz = c * party->moveSpeed;
    d = (vx * nx) + (vz * nz);
    party->position.x += 0.5f * (vx - (d * nx));
    party->position.z += 0.5f * (vz - (d * nz));
    if (((PH(party, 0x17c)) != 0) || (mode == 0))
    {
      PW(party, 0x130) = (u32) hit;
    }
    PW(party, 0x12c) = (u32) hit;
    party->position.x = hx;
    return hit;
  }
  return NULL;
}
#endif

#ifdef NONMATCHING
void nokoStrippedPool(f32* p) { p[0] = 10.0f; p[1] = 30.0f; p[2] = 100.0f; p[3] = 11.0f; p[4] = 6.0f; }
#endif
#ifdef NONMATCHING
u32 lookupSafetyPos(Vec pos, f32 height, Vec* out) {
    Vec p[4];
    f32 dist;
    f32 hx; f32 hy; f32 hz; f32 nx; f32 ny; f32 nz;
    f32 rad;
    f32 x; f32 y; f32 z; f32 c;
    f32 w;
    HitEntry* h0;
    HitEntry* h1;
    HitEntry* h2;
    HitEntry* h3;
    u32 flags;
    MarioWork* player = marioGetPtr();
    w = player->wPlayerCollisionBox.x;
    rad = (3.1415927f * revise360(toMovedir(player->displayDirectionTarget) - 180.0f)) / 180.0f;
    x = w * (f32)sin(rad) + pos.x;
    p[3].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[3].y = y;
    z = w * -c + pos.z;
    p[3].z = z;
    dist = 0.1f + height;
    h0 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f);
    rad = (3.1415927f * revise360(toMovedir(player->displayDirectionTarget) - 90.0f)) / 180.0f;
    x = w * (f32)sin(rad) + pos.x;
    p[2].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[2].y = y;
    z = w * -c + pos.z;
    p[2].z = z;
    dist = 0.1f + height;
    h1 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f);
    rad = (3.1415927f * revise360(90.0f + toMovedir(player->displayDirectionTarget))) / 180.0f;
    x = w * (f32)sin(rad) + pos.x;
    p[1].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[1].y = y;
    z = w * -c + pos.z;
    p[1].z = z;
    dist = 0.1f + height;
    h2 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f);
    rad = (3.1415927f * revise360(toMovedir(player->displayDirectionTarget))) / 180.0f;
    x = w * (f32)sin(rad) + pos.x;
    p[0].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[0].y = y;
    z = w * -c + pos.z;
    p[0].z = z;
    dist = 0.1f + height;
    h3 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f);
    flags = 0;
    if (h2) flags |= 4;
    if (h3) flags |= 8;
    if (h0) flags |= 1;
    if (h1) flags |= 2;
    if (h0) {
        if (h1 && h2 && h3) {
        out->x = 0.5f * (p[3].x + p[1].x); out->z = 0.5f * (p[3].z + p[1].z); out->y = p[3].y; return flags;
        }
        if (h1) {
        out->x = 0.5f * (p[3].x + p[2].x); out->z = 0.5f * (p[3].z + p[2].z); out->y = pos.y; return flags;
        }
        if (h2) {
        out->x = 0.5f * (p[3].x + p[1].x); out->z = 0.5f * (p[3].z + p[1].z); out->y = p[3].y; return flags;
        }
        if (h3) {
        out->x = 0.5f * (p[3].x + p[0].x); out->z = 0.5f * (p[3].z + p[0].z); out->y = p[3].y; return flags;
        }
        *out = p[3];
    } else if (h3) {
        if (h1) {
        out->x = 0.5f * (p[0].x + p[2].x); out->z = 0.5f * (p[0].z + p[2].z); out->y = p[0].y; return flags;
        }
        if (h2) {
        out->x = 0.5f * (p[1].x + p[2].x); out->z = 0.5f * (p[1].z + p[2].z); out->y = p[1].y; return flags;
        }
        *out = p[0];
    } else {
        if (h1) {
            *out = p[2];
            return flags;
        }
        if (h2) {
            *out = p[1];
            return flags;
        }
    }
    *out = pos;
    return flags;
}
#endif

#ifdef NONMATCHING
void lookupSafetyPos2(Vec pos, f32 height, Vec* out) {
    f32 rad;
    f32 dx;
    f32 dz;
    f32 d;
    f32 dist;
    f32 w;
    f32 x;
    f32 z;
    f32 y;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 nx;
    f32 ny;
    f32 nz;
    MarioWork* player = marioGetPtr();

    w = player->wPlayerCollisionBox.x;
    rad = (3.1415927f * 90.0f) / 180.0f;
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    y = pos.y;
    z = pos.z + dz;
    d = 0.1f + height;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (3.1415927f * 270.0f) / 180.0f;
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    y = pos.y;
    z = pos.z + dz;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (3.1415927f * 180.0f) / 180.0f;
    dx = (f32)sin(rad);
    dz = (f32)cos(rad);
    x = pos.x;
    y = pos.y;
    z = pos.z;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (3.1415927f * 0.0f) / 180.0f;
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    y = pos.y;
    z = pos.z + dz;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    *out = pos;
}
#endif

#ifdef NONMATCHING
void lookupSafetyPos3(Vec pos, f32 height, Vec* out) {
    f32 rad;
    f32 dx;
    f32 dz;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 nx;
    f32 ny;
    f32 nz;
    MarioWork* player = marioGetPtr();
    f32 w = player->wPlayerCollisionBox.x;

    rad = (3.1415927f * 90.0f) / 180.0f;
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    z = pos.z + dz;
    y = pos.y;
    dist = 0.1f + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (3.1415927f * 270.0f) / 180.0f;
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    z = pos.z + dz;
    y = pos.y;
    dist = 0.1f + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, 0.0f, -1.0f, 0.0f) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    *out = pos;
}
#endif

#ifdef NONMATCHING
void lookupSafetyPosSub(Vec pos, f32 height, f32 angle, Vec* out) {
    f32 rad;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 nx;
    f32 ny;
    f32 nz;
    Vec* p;
    MarioWork* player = marioGetPtr();
    rad = (3.1415927f * angle) / 180.0f;
    angle = player->wPlayerCollisionBox.x;
    x = angle * (f32)sin(rad) + pos.x;
    z = angle * -(f32)cos(rad) + pos.z;
    y = pos.y + height;
    dist = 0.1f + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, 0.0f, -1.0f, 0.0f) != NULL) {
        Vec v = {0.0f, 0.0f, 0.0f};
        v.x = x;
        v.y = y;
        v.z = z;
        p = &v;
    } else {
        p = &pos;
    }
    *out = *p;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: nokonokoGetStatus (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const f32 vec3_802ce138[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802ce148 = 4503601774854144;
__declspec(section ".rodata") const char str_802CE150[] = "PNK_K_2";
__declspec(section ".rodata") const char str_802CE158[] = "PNK_A_1";
__declspec(section ".rodata") const f64 double_180_802ce160 = 180;
__declspec(section ".sdata2") const f32 float_3p1416_8041b510 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_8041b514 = 180.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041b518 = 0.1f;
__declspec(section ".sdata2") const f32 float_0_8041b51c = 0.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041b520 = -1.0f;
__declspec(section ".sdata2") const f32 float_1p5708_8041b524 = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_8041b528 = 4.712389f;
__declspec(section ".sdata2") const f32 float_90_8041b52c = 90.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041b530 = 0.5f;
__declspec(section ".sdata2") const f32 float_10_8041b534 = 10.0f;
__declspec(section ".sdata2") const f32 float_30_8041b538 = 30.0f;
__declspec(section ".sdata2") const f32 float_100_8041b53c = 100.0f;
__declspec(section ".sdata2") const f32 float_11_8041b540 = 11.0f;
__declspec(section ".sdata2") const f32 float_6_8041b544 = 6.0f;
__declspec(section ".sdata2") const f32 float_1_8041b548 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p4_8041b54c = 0.4f;
__declspec(section ".sdata2") const f32 float_37_8041b550 = 37.0f;
__declspec(section ".sdata2") const f32 float_160_8041b554 = 160.0f;
__declspec(section ".sdata2") const f32 float_18p5_8041b558 = 18.5f;
__declspec(section ".sdata2") const f32 float_2_8041b55c = 2.0f;
__declspec(section ".sdata2") const f32 float_45_8041b560 = 45.0f;
__declspec(section ".sdata2") const f32 float_6p2832_8041b564 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041b568 = 360.0f;
__declspec(section ".sdata2") const f32 float_50_8041b56c = 50.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041b570 = 0.25f;
__declspec(section ".sdata2") const f32 float_0p3_8041b574 = 0.3f;
__declspec(section ".sdata2") const f32 float_12_8041b578 = 12.0f;
__declspec(section ".sdata2") const f32 float_120_8041b57c = 120.0f;
__declspec(section ".sdata2") const f32 float_0p15_8041b580 = 0.15f;
__declspec(section ".sdata2") const f32 float_20_8041b584 = 20.0f;
__declspec(section ".sdata2") const f32 float_2p2_8041b588 = 2.2f;
__declspec(section ".sdata2") const f32 float_neg2_8041b58c = -2.0f;
__declspec(section ".sdata2") const f32 float_0p2_8041b590 = 0.2f;
__declspec(section ".sdata2") const f32 float_135_8041b594 = 135.0f;
__declspec(section ".sdata2") const f32 float_315_8041b598 = 315.0f;
__declspec(section ".sdata2") const f32 float_225_8041b59c = 225.0f;
__declspec(section ".sdata2") const f32 float_270_8041b5a0 = 270.0f;
__declspec(section ".sdata2") const f32 float_4_8041b5a4 = 4.0f;
__declspec(section ".sdata2") const f32 float_5_8041b5a8 = 5.0f;
__declspec(section ".sdata2") const f32 float_neg90_8041b5ac = -90.0f;
__declspec(section ".sdata2") const f32 float_75_8041b5b0 = 75.0f;
__declspec(section ".sdata2") const f32 float_3_8041b5b4 = 3.0f;
__declspec(section ".sdata2") const f32 float_18_8041b5b8 = 18.0f;
__declspec(section ".sdata2") const f32 float_0p35_8041b5bc = 0.35f;
__declspec(section ".sdata2") const f32 float_15_8041b5c0 = 15.0f;
__declspec(section ".sdata2") const f32 float_neg300_8041b5c4 = -300.0f;
__declspec(section ".sdata2") const f32 float_neg30_8041b5c8 = -30.0f;
__declspec(section ".sdata2") const f32 float_1000_8041b5cc = 1000.0f;
__declspec(section ".sdata2") const f32 float_240_8041b5d0 = 240.0f;
__declspec(section ".sdata2") const f32 float_neg6_8041b5d4 = -6.0f;
__declspec(section ".sdata2") const f32 float_neg2000_8041b5d8 = -2000.0f;
__declspec(section ".sdata2") const f32 float_200_8041b5dc = 200.0f;
__declspec(section ".sdata2") const f32 float_24_8041b5e0 = 24.0f;

void nokonoko_use(PartyEntry* party);
__declspec(section ".data") static void* jumptable_80313660[] = {
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x19E4,
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x1918,
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x1948,
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x19D8,
    (char*)nokonoko_use + 0x1A14,
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x1978,
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x19A8,
    (char*)nokonoko_use + 0x1A40,
    (char*)nokonoko_use + 0x19D8,
    (char*)nokonoko_use + 0x19D8,
};
void nokonoko_use(PartyEntry* party);
__declspec(section ".data") static void* jumptable_803136A0[] = {
    (char*)nokonoko_use + 0x132C,
    (char*)nokonoko_use + 0x1370,
    (char*)nokonoko_use + 0x14F0,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1678,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1718,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1894,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1AC4,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x178C,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1E20,
    (char*)nokonoko_use + 0x1B60,
    (char*)nokonoko_use + 0x1B88,
    (char*)nokonoko_use + 0x1BF0,
    (char*)nokonoko_use + 0x1D1C,
    (char*)nokonoko_use + 0x1E04,
};
void nokonoko_use(PartyEntry* party);
__declspec(section ".data") static void* jumptable_8031372C[] = {
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xFD4,
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xF08,
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xF38,
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xFC8,
    (char*)nokonoko_use + 0x1004,
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xF68,
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xF98,
    (char*)nokonoko_use + 0x1030,
    (char*)nokonoko_use + 0xFC8,
    (char*)nokonoko_use + 0xFC8,
};
void nokonoko_use(PartyEntry* party);
__declspec(section ".data") static void* jumptable_8031376C[] = {
    (char*)nokonoko_use + 0xBC0,
    (char*)nokonoko_use + 0xC00,
    (char*)nokonoko_use + 0xC58,
    (char*)nokonoko_use + 0xDB0,
    (char*)nokonoko_use + 0x10AC,
    (char*)nokonoko_use + 0x1148,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1304,
    (char*)nokonoko_use + 0x1220,
    (char*)nokonoko_use + 0x12E0,
};
void nokonoko_use(PartyEntry* party);
__declspec(section ".data") static void* jumptable_803137C4[] = {
    (char*)nokonoko_use + 0x17C,
    (char*)nokonoko_use + 0x2C8,
    (char*)nokonoko_use + 0x3E8,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0x464,
    (char*)nokonoko_use + 0x4F0,
    (char*)nokonoko_use + 0x514,
    (char*)nokonoko_use + 0x7B8,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0xB98,
    (char*)nokonoko_use + 0x804,
    (char*)nokonoko_use + 0xB18,
};
asm void lookupSafetyPosSub(Vec pos, f32 height, f32 angle, Vec* out) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stfd f28, 0x40(r1)
	psq_st f28, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	fmr f28, f1
	mr r30, r3
	fmr f29, f2
	mr r31, r4
	bl marioGetPtr
	lfs f1, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmuls f1, f1, f29
	lfs f29, 0x1b4(r3)
	fdivs f31, f1, f0
	fmr f1, f31
	bl sin
	frsp f2, f1
	lfs f0, 0x0(r30)
	fmr f1, f31
	fmadds f31, f29, f2, f0
	bl cos
	frsp f3, f1
	lfs f2, 0x4(r30)
	lfs f0, float_0p1_8041b518(r2)
	fmr f1, f31
	fadds f30, f2, f28
	lfs f4, float_0_8041b51c(r2)
	fneg f6, f3
	lfs f3, 0x8(r30)
	fadds f0, f0, f28
	lfs f5, float_neg1_8041b520(r2)
	fmr f2, f30
	addi r4, r1, 0x1c
	fmadds f29, f29, f6, f3
	stfs f0, 0x20(r1)
	fmr f6, f4
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	fmr f3, f29
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @1
	lis r3, vec3_802ce138@ha
	addi r6, r1, 0x24
	addi r5, r3, vec3_802ce138@l
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x24(r1)
	stw r3, 0x28(r1)
	stw r0, 0x2c(r1)
	stfs f31, 0x24(r1)
	stfs f30, 0x28(r1)
	stfs f29, 0x2c(r1)
	b @2
	@1:
	mr r6, r30
	@2:
	lwz r3, 0x0(r6)
	lwz r0, 0x4(r6)
	stw r3, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0x8(r6)
	stw r0, 0x8(r31)
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r0, 0x84(r1)
	lwz r30, 0x38(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void lookupSafetyPos3(Vec pos, f32 height, Vec* out) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stfd f28, 0x50(r1)
	psq_st f28, 0x58(r1), 0, 0
	stfd f27, 0x40(r1)
	psq_st f27, 0x48(r1), 0, 0
	stfd f26, 0x30(r1)
	psq_st f26, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	fmr f30, f1
	mr r30, r3
	mr r31, r4
	bl marioGetPtr
	lfs f31, 0x1b4(r3)
	lfs f1, float_1p5708_8041b524(r2)
	bl sin
	frsp f29, f1
	lfs f1, float_1p5708_8041b524(r2)
	bl cos
	frsp f3, f1
	lfs f0, float_0p1_8041b518(r2)
	lfs f28, 0x4(r30)
	fmuls f1, f31, f29
	lfs f2, 0x0(r30)
	fadds f27, f0, f30
	fneg f0, f3
	lfs f4, float_0_8041b51c(r2)
	fadds f29, f2, f1
	lfs f3, 0x8(r30)
	fmr f6, f4
	stfs f27, 0x20(r1)
	fmuls f0, f31, f0
	lfs f5, float_neg1_8041b520(r2)
	fmr f1, f29
	addi r4, r1, 0x1c
	fadds f2, f28, f30
	addi r5, r1, 0x18
	fadds f26, f3, f0
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	fmr f3, f26
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @1
	stfs f29, 0x0(r31)
	stfs f26, 0x8(r31)
	stfs f28, 0x4(r31)
	b @2
	@1:
	lfs f1, float_4p7124_8041b528(r2)
	bl sin
	frsp f29, f1
	lfs f1, float_4p7124_8041b528(r2)
	bl cos
	frsp f0, f1
	lfs f28, 0x4(r30)
	lfs f4, float_0_8041b51c(r2)
	fmuls f1, f31, f29
	lfs f5, 0x0(r30)
	fadds f2, f28, f30
	fneg f0, f0
	lfs f3, 0x8(r30)
	fadds f29, f5, f1
	stfs f27, 0x20(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	fmuls f0, f31, f0
	addi r4, r1, 0x1c
	fmr f1, f29
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	fadds f27, f3, f0
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fmr f3, f27
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @3
	stfs f29, 0x0(r31)
	stfs f27, 0x8(r31)
	stfs f28, 0x4(r31)
	b @2
	@3:
	lwz r0, 0x0(r30)
	lwz r3, 0x4(r30)
	stw r0, 0x0(r31)
	lwz r0, 0x8(r30)
	stw r3, 0x4(r31)
	stw r0, 0x8(r31)
	@2:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	psq_l f27, 0x48(r1), 0, 0
	lfd f27, 0x40(r1)
	psq_l f26, 0x38(r1), 0, 0
	lfd f26, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r0, 0x94(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void lookupSafetyPos2(Vec pos, f32 height, Vec* out) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stfd f28, 0x50(r1)
	psq_st f28, 0x58(r1), 0, 0
	stfd f27, 0x40(r1)
	psq_st f27, 0x48(r1), 0, 0
	stfd f26, 0x30(r1)
	psq_st f26, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	fmr f29, f1
	mr r30, r3
	mr r31, r4
	bl marioGetPtr
	lfs f30, 0x1b4(r3)
	lfs f1, float_1p5708_8041b524(r2)
	bl sin
	frsp f31, f1
	lfs f1, float_1p5708_8041b524(r2)
	bl cos
	frsp f3, f1
	lfs f0, float_0p1_8041b518(r2)
	lfs f28, 0x4(r30)
	fmuls f1, f30, f31
	lfs f2, 0x0(r30)
	fadds f31, f0, f29
	fneg f0, f3
	lfs f4, float_0_8041b51c(r2)
	fadds f26, f2, f1
	lfs f3, 0x8(r30)
	fmr f6, f4
	stfs f31, 0x20(r1)
	fmuls f0, f30, f0
	lfs f5, float_neg1_8041b520(r2)
	fmr f1, f26
	addi r4, r1, 0x1c
	fadds f2, f28, f29
	addi r5, r1, 0x18
	fadds f27, f3, f0
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	fmr f3, f27
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @1
	stfs f26, 0x0(r31)
	stfs f27, 0x8(r31)
	stfs f28, 0x4(r31)
	b @2
	@1:
	lfs f1, float_4p7124_8041b528(r2)
	bl sin
	frsp f28, f1
	lfs f1, float_4p7124_8041b528(r2)
	bl cos
	frsp f0, f1
	lfs f27, 0x4(r30)
	lfs f4, float_0_8041b51c(r2)
	fmuls f1, f30, f28
	lfs f5, 0x0(r30)
	fadds f2, f27, f29
	fneg f0, f0
	lfs f3, 0x8(r30)
	fadds f28, f5, f1
	stfs f31, 0x20(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	fmuls f0, f30, f0
	addi r4, r1, 0x1c
	fmr f1, f28
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	fadds f26, f3, f0
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fmr f3, f26
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @3
	stfs f28, 0x0(r31)
	stfs f26, 0x8(r31)
	stfs f27, 0x4(r31)
	b @2
	@3:
	lfs f1, float_3p1416_8041b510(r2)
	bl sin
	lfs f1, float_3p1416_8041b510(r2)
	bl cos
	lfs f28, 0x0(r30)
	addi r4, r1, 0x1c
	lfs f26, 0x8(r30)
	addi r5, r1, 0x18
	lfs f27, 0x4(r30)
	fmr f1, f28
	lfs f4, float_0_8041b51c(r2)
	fmr f3, f26
	fadds f2, f27, f29
	stfs f31, 0x20(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @4
	stfs f28, 0x0(r31)
	stfs f26, 0x8(r31)
	stfs f27, 0x4(r31)
	b @2
	@4:
	lfs f1, float_0_8041b51c(r2)
	bl sin
	frsp f28, f1
	lfs f1, float_0_8041b51c(r2)
	bl cos
	frsp f0, f1
	lfs f27, 0x4(r30)
	lfs f4, float_0_8041b51c(r2)
	fmuls f1, f30, f28
	lfs f5, 0x0(r30)
	fadds f2, f27, f29
	fneg f0, f0
	lfs f3, 0x8(r30)
	fadds f28, f5, f1
	stfs f31, 0x20(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	fmuls f0, f30, f0
	addi r4, r1, 0x1c
	fmr f1, f28
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	fadds f29, f3, f0
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fmr f3, f29
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @5
	stfs f28, 0x0(r31)
	stfs f29, 0x8(r31)
	stfs f27, 0x4(r31)
	b @2
	@5:
	lwz r0, 0x0(r30)
	lwz r3, 0x4(r30)
	stw r0, 0x0(r31)
	lwz r0, 0x8(r30)
	stw r3, 0x4(r31)
	stw r0, 0x8(r31)
	@2:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	psq_l f27, 0x48(r1), 0, 0
	lfd f27, 0x40(r1)
	psq_l f26, 0x38(r1), 0, 0
	lfd f26, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r0, 0x94(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm u32 lookupSafetyPos(Vec pos, f32 height, Vec* out) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stfd f29, 0x80(r1)
	psq_st f29, 0x88(r1), 0, 0
	stfd f28, 0x70(r1)
	psq_st f28, 0x78(r1), 0, 0
	stmw r27, 0x5c(r1)
	fmr f29, f1
	mr r27, r3
	mr r31, r4
	bl marioGetPtr
	mr r30, r3
	lfs f30, 0x1b4(r3)
	lfs f1, 0x1ac(r3)
	bl toMovedir
	lfs f0, float_180_8041b514(r2)
	fsubs f1, f1, f0
	bl revise360
	lfs f2, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmuls f1, f2, f1
	fdivs f31, f1, f0
	fmr f1, f31
	bl sin
	frsp f2, f1
	lfs f0, 0x0(r27)
	fmr f1, f31
	fmadds f28, f30, f2, f0
	stfs f28, 0x48(r1)
	bl cos
	frsp f3, f1
	lfs f5, 0x4(r27)
	lfs f0, float_0p1_8041b518(r2)
	fmr f1, f28
	lfs f4, float_0_8041b51c(r2)
	fadds f2, f5, f29
	fneg f6, f3
	lfs f3, 0x8(r27)
	fadds f31, f0, f29
	stfs f5, 0x4c(r1)
	lfs f5, float_neg1_8041b520(r2)
	addi r4, r1, 0x1c
	fmadds f3, f30, f6, f3
	stfs f31, 0x20(r1)
	fmr f6, f4
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	stfs f3, 0x50(r1)
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	lfs f1, 0x1ac(r30)
	mr r28, r3
	bl toMovedir
	lfs f0, float_90_8041b52c(r2)
	fsubs f1, f1, f0
	bl revise360
	lfs f2, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, 0x0(r27)
	fmr f1, f28
	fmadds f28, f30, f2, f0
	stfs f28, 0x3c(r1)
	bl cos
	frsp f3, f1
	lfs f5, 0x4(r27)
	lfs f4, float_0_8041b51c(r2)
	fmr f1, f28
	lfs f0, 0x8(r27)
	fadds f2, f5, f29
	fneg f3, f3
	stfs f5, 0x40(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	stfs f31, 0x20(r1)
	addi r4, r1, 0x1c
	fmadds f3, f30, f3, f0
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	stfs f3, 0x44(r1)
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	lfs f1, 0x1ac(r30)
	mr r29, r3
	bl toMovedir
	lfs f0, float_90_8041b52c(r2)
	fadds f1, f0, f1
	bl revise360
	lfs f2, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, 0x0(r27)
	fmr f1, f28
	fmadds f28, f30, f2, f0
	stfs f28, 0x30(r1)
	bl cos
	frsp f3, f1
	lfs f5, 0x4(r27)
	lfs f4, float_0_8041b51c(r2)
	fmr f1, f28
	lfs f0, 0x8(r27)
	fadds f2, f5, f29
	fneg f3, f3
	stfs f5, 0x34(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	stfs f31, 0x20(r1)
	addi r4, r1, 0x1c
	fmadds f3, f30, f3, f0
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	stfs f3, 0x38(r1)
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	lfs f1, 0x1ac(r30)
	mr r30, r3
	bl toMovedir
	bl revise360
	lfs f2, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, 0x0(r27)
	fmr f1, f28
	fmadds f28, f30, f2, f0
	stfs f28, 0x24(r1)
	bl cos
	frsp f3, f1
	lfs f5, 0x4(r27)
	lfs f4, float_0_8041b51c(r2)
	fmr f1, f28
	lfs f0, 0x8(r27)
	fadds f2, f5, f29
	fneg f3, f3
	stfs f5, 0x28(r1)
	fmr f6, f4
	lfs f5, float_neg1_8041b520(r2)
	stfs f31, 0x20(r1)
	addi r4, r1, 0x1c
	fmadds f3, f30, f3, f0
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	addi r7, r1, 0x20
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	stfs f3, 0x2c(r1)
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r30, 0x0
	li r4, 0x0
	beq @1
	ori r4, r4, 0x4
	@1:
	cmplwi r3, 0x0
	beq @2
	ori r4, r4, 0x8
	@2:
	cmplwi r28, 0x0
	beq @3
	ori r4, r4, 0x1
	@3:
	cmplwi r29, 0x0
	beq @4
	ori r4, r4, 0x2
	@4:
	cmplwi r28, 0x0
	beq @5
	cmplwi r29, 0x0
	beq @6
	cmplwi r30, 0x0
	beq @6
	cmplwi r3, 0x0
	beq @6
	lfs f3, 0x48(r1)
	mr r3, r4
	lfs f2, 0x30(r1)
	lfs f1, 0x50(r1)
	lfs f0, 0x38(r1)
	fadds f2, f3, f2
	lfs f3, float_0p5_8041b530(r2)
	fadds f1, f1, f0
	lfs f0, 0x4c(r1)
	fmuls f2, f3, f2
	fmuls f1, f3, f1
	stfs f2, 0x0(r31)
	stfs f1, 0x8(r31)
	stfs f0, 0x4(r31)
	b @7
	@6:
	cmplwi r29, 0x0
	beq @8
	lfs f3, 0x48(r1)
	mr r3, r4
	lfs f2, 0x3c(r1)
	lfs f1, 0x50(r1)
	lfs f0, 0x44(r1)
	fadds f2, f3, f2
	lfs f3, float_0p5_8041b530(r2)
	fadds f1, f1, f0
	lfs f0, 0x4(r27)
	fmuls f2, f3, f2
	fmuls f1, f3, f1
	stfs f2, 0x0(r31)
	stfs f1, 0x8(r31)
	stfs f0, 0x4(r31)
	b @7
	@8:
	cmplwi r30, 0x0
	beq @9
	lfs f3, 0x48(r1)
	mr r3, r4
	lfs f2, 0x30(r1)
	lfs f1, 0x50(r1)
	lfs f0, 0x38(r1)
	fadds f2, f3, f2
	lfs f3, float_0p5_8041b530(r2)
	fadds f1, f1, f0
	lfs f0, 0x4c(r1)
	fmuls f2, f3, f2
	fmuls f1, f3, f1
	stfs f2, 0x0(r31)
	stfs f1, 0x8(r31)
	stfs f0, 0x4(r31)
	b @7
	@9:
	cmplwi r3, 0x0
	beq @10
	lfs f3, 0x48(r1)
	mr r3, r4
	lfs f2, 0x24(r1)
	lfs f1, 0x50(r1)
	lfs f0, 0x2c(r1)
	fadds f2, f3, f2
	lfs f3, float_0p5_8041b530(r2)
	fadds f1, f1, f0
	lfs f0, 0x4c(r1)
	fmuls f2, f3, f2
	fmuls f1, f3, f1
	stfs f2, 0x0(r31)
	stfs f1, 0x8(r31)
	stfs f0, 0x4(r31)
	b @7
	@10:
	lwz r0, 0x48(r1)
	lwz r3, 0x4c(r1)
	stw r0, 0x0(r31)
	lwz r0, 0x50(r1)
	stw r3, 0x4(r31)
	stw r0, 0x8(r31)
	b @11
	@5:
	cmplwi r3, 0x0
	beq @12
	cmplwi r29, 0x0
	beq @13
	lfs f3, 0x24(r1)
	mr r3, r4
	lfs f2, 0x3c(r1)
	lfs f1, 0x2c(r1)
	lfs f0, 0x44(r1)
	fadds f2, f3, f2
	lfs f3, float_0p5_8041b530(r2)
	fadds f1, f1, f0
	lfs f0, 0x28(r1)
	fmuls f2, f3, f2
	fmuls f1, f3, f1
	stfs f2, 0x0(r31)
	stfs f1, 0x8(r31)
	stfs f0, 0x4(r31)
	b @7
	@13:
	cmplwi r30, 0x0
	beq @14
	lfs f3, 0x30(r1)
	mr r3, r4
	lfs f2, 0x3c(r1)
	lfs f1, 0x38(r1)
	lfs f0, 0x44(r1)
	fadds f2, f3, f2
	lfs f3, float_0p5_8041b530(r2)
	fadds f1, f1, f0
	lfs f0, 0x34(r1)
	fmuls f2, f3, f2
	fmuls f1, f3, f1
	stfs f2, 0x0(r31)
	stfs f1, 0x8(r31)
	stfs f0, 0x4(r31)
	b @7
	@14:
	lwz r0, 0x24(r1)
	lwz r3, 0x28(r1)
	stw r0, 0x0(r31)
	lwz r0, 0x2c(r1)
	stw r3, 0x4(r31)
	stw r0, 0x8(r31)
	b @11
	@12:
	cmplwi r29, 0x0
	beq @15
	lwz r0, 0x3c(r1)
	mr r3, r4
	lwz r4, 0x40(r1)
	stw r0, 0x0(r31)
	lwz r0, 0x44(r1)
	stw r4, 0x4(r31)
	stw r0, 0x8(r31)
	b @7
	@15:
	cmplwi r30, 0x0
	beq @11
	lwz r0, 0x30(r1)
	mr r3, r4
	lwz r4, 0x34(r1)
	stw r0, 0x0(r31)
	lwz r0, 0x38(r1)
	stw r4, 0x4(r31)
	stw r0, 0x8(r31)
	b @7
	@11:
	lwz r0, 0x0(r27)
	mr r3, r4
	lwz r4, 0x4(r27)
	stw r0, 0x0(r31)
	lwz r0, 0x8(r27)
	stw r4, 0x4(r31)
	stw r0, 0x8(r31)
	@7:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	psq_l f28, 0x78(r1), 0, 0
	lfd f28, 0x70(r1)
	lmw r27, 0x5c(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm HitEntry *ccwall(PartyEntry *party, s32 mode) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stfd f31, 0xc0(r1)
	psq_st f31, 0xc8(r1), 0, 0
	stfd f30, 0xb0(r1)
	psq_st f30, 0xb8(r1), 0, 0
	stfd f29, 0xa0(r1)
	psq_st f29, 0xa8(r1), 0, 0
	stfd f28, 0x90(r1)
	psq_st f28, 0x98(r1), 0, 0
	stfd f27, 0x80(r1)
	psq_st f27, 0x88(r1), 0, 0
	stw r31, 0x7c(r1)
	stw r30, 0x78(r1)
	stw r29, 0x74(r1)
	lfs f1, 0x5c(r3)
	mr r31, r4
	lfs f5, 0xf0(r3)
	mr r30, r3
	lfs f0, float_30_8041b538(r2)
	addi r4, r1, 0x34
	fadds f2, f1, f5
	lfs f4, float_0_8041b51c(r2)
	lfs f30, float_10_8041b534(r2)
	fadds f0, f5, f0
	lfs f1, 0x58(r3)
	fmr f6, f4
	lfs f3, 0x60(r3)
	fadds f2, f30, f2
	lfs f5, float_neg1_8041b520(r2)
	addi r5, r1, 0x30
	stfs f0, 0x38(r1)
	addi r6, r1, 0x2c
	addi r7, r1, 0x38
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	mr r29, r3
	bl hitGetAttr
	extrwi r0, r3, 1, 22
	cmpwi r0, 0x1
	bne @1
	li r29, 0x0
	@1:
	cmplwi r29, 0x0
	stw r29, 0x138(r30)
	beq @2
	lfs f5, float_100_8041b53c(r2)
	lis r0, 0x4330
	lfs f0, 0x30(r1)
	lis r3, double_to_int_802ce148@ha
	lfs f4, float_0p5_8041b530(r2)
	stw r0, 0x50(r1)
	fmadds f1, f5, f0, f4
	lfd f3, double_to_int_802ce148@l(r3)
	stw r0, 0x60(r1)
	lfs f0, float_11_8041b540(r2)
	fctiwz f1, f1
	stfd f1, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x54(r1)
	lfd f1, 0x50(r1)
	fsubs f1, f1, f3
	fdivs f2, f1, f5
	stfs f2, 0x30(r1)
	lfs f1, 0x5c(r30)
	fmadds f1, f5, f1, f4
	fctiwz f1, f1
	stfd f1, 0x58(r1)
	lwz r0, 0x5c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	lfd f1, 0x60(r1)
	fsubs f1, f1, f3
	fdivs f3, f1, f5
	fsubs f1, f3, f2
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @2
	fcmpo cr0, f3, f2
	cror eq, lt, eq
	bne @3
	cmpwi r31, 0x0
	bne @2
	stfs f2, 0x5c(r30)
	lfs f0, float_1_8041b548(r2)
	lfs f1, 0x30(r1)
	fsubs f1, f3, f1
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @2
	lha r0, 0x17e(r30)
	ori r0, r0, 0x2
	sth r0, 0x17e(r30)
	b @2
	@3:
	lha r0, 0x17e(r30)
	rlwinm. r0, r0, 0, 30, 30
	beq @4
	cmpwi r31, 0x1
	bne @4
	stfs f2, 0x5c(r30)
	@4:
	lfs f2, 0x30(r1)
	lfs f0, float_6_8041b544(r2)
	fsubs f1, f3, f2
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @2
	stfs f2, 0x5c(r30)
	@2:
	li r0, 0x0
	lfs f0, float_1_8041b548(r2)
	stw r0, 0x130(r30)
	addi r3, r1, 0x40
	lfs f2, float_0p5_8041b530(r2)
	fadds f30, f30, f0
	stw r0, 0x12c(r30)
	addi r4, r1, 0x3c
	lfs f1, 0xf4(r30)
	lfs f0, 0x104(r30)
	lfs f3, 0x5c(r30)
	fmadds f0, f2, f1, f0
	lfs f29, 0x58(r30)
	lfs f28, 0x60(r30)
	fadds f27, f3, f30
	stfs f0, 0x38(r1)
	lfs f1, 0x100(r30)
	bl sincosf
	fmr f1, f29
	lfs f4, 0x40(r1)
	fmr f2, f27
	lfs f5, float_0_8041b51c(r2)
	fmr f3, f28
	lfs f6, 0x3c(r1)
	addi r4, r1, 0x34
	addi r5, r1, 0x30
	addi r6, r1, 0x2c
	addi r7, r1, 0x38
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	mr. r29, r3
	beq @5
	bl hitGetAttr
	andi. r0, r3, 0x5
	bne @5
	lfs f1, float_180_8041b514(r2)
	addi r3, r1, 0x1c
	lfs f0, 0x100(r30)
	addi r4, r1, 0x18
	fadds f1, f1, f0
	bl sincosf
	lfs f1, 0x1c(r1)
	lfs f0, 0xf4(r30)
	lfs f3, float_0p5_8041b530(r2)
	fmuls f1, f1, f0
	lfs f0, 0x34(r1)
	fmadds f0, f3, f1, f0
	stfs f0, 0x58(r30)
	lfs f2, 0x18(r1)
	lfs f1, 0xf4(r30)
	lfs f0, 0x2c(r1)
	fmuls f1, f2, f1
	fmadds f0, f3, f1, f0
	stfs f0, 0x60(r30)
	lfs f4, 0x104(r30)
	lfs f0, 0x3c(r1)
	lfs f2, 0x40(r1)
	fmuls f5, f0, f4
	lfs f1, 0x20(r1)
	fmuls f4, f2, f4
	lfs f2, 0x28(r1)
	lfs f0, 0x58(r30)
	fmuls f1, f5, f1
	fmadds f6, f4, f2, f1
	fnmsubs f1, f6, f2, f4
	fmadds f0, f3, f1, f0
	stfs f0, 0x58(r30)
	lfs f1, 0x20(r1)
	lfs f0, 0x60(r30)
	fnmsubs f1, f6, f1, f5
	fmadds f0, f3, f1, f0
	stfs f0, 0x60(r30)
	lha r0, 0x17c(r30)
	cmpwi r0, 0x0
	bne @6
	cmpwi r31, 0x0
	bne @7
	@6:
	stw r29, 0x130(r30)
	@7:
	stw r29, 0x12c(r30)
	mr r3, r29
	b @8
	@5:
	lfs f1, 0x100(r30)
	lfs f0, float_90_8041b52c(r2)
	lfs f2, float_3p1416_8041b510(r2)
	fsubs f1, f1, f0
	lfs f0, float_180_8041b514(r2)
	lfs f4, float_0p4_8041b54c(r2)
	lfs f3, 0xf4(r30)
	fmuls f1, f2, f1
	fmuls f31, f4, f3
	fdivs f1, f1, f0
	bl cos
	lfs f2, 0x100(r30)
	frsp f4, f1
	lfs f0, float_90_8041b52c(r2)
	lfs f3, 0x60(r30)
	fsubs f1, f2, f0
	lfs f2, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmadds f28, f31, f4, f3
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, float_0p4_8041b54c(r2)
	frsp f5, f1
	lfs f1, 0xf4(r30)
	addi r3, r1, 0x40
	lfs f0, 0x104(r30)
	addi r4, r1, 0x3c
	lfs f4, 0x58(r30)
	lfs f3, 0x5c(r30)
	fmadds f0, f2, f1, f0
	fmadds f29, f31, f5, f4
	fadds f27, f3, f30
	stfs f0, 0x38(r1)
	lfs f1, 0x100(r30)
	bl sincosf
	fmr f1, f29
	lfs f4, 0x40(r1)
	fmr f2, f27
	lfs f5, float_0_8041b51c(r2)
	fmr f3, f28
	lfs f6, 0x3c(r1)
	addi r4, r1, 0x34
	addi r5, r1, 0x30
	addi r6, r1, 0x2c
	addi r7, r1, 0x38
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	mr. r29, r3
	beq @9
	bl hitGetAttr
	andi. r0, r3, 0x5
	bne @9
	lfs f1, float_180_8041b514(r2)
	addi r3, r1, 0x14
	lfs f0, 0x100(r30)
	addi r4, r1, 0x10
	fadds f1, f1, f0
	bl sincosf
	lfs f1, 0x14(r1)
	lfs f0, 0xf4(r30)
	lfs f6, float_0p5_8041b530(r2)
	fmuls f2, f1, f0
	lfs f0, 0x34(r1)
	lfs f1, float_90_8041b52c(r2)
	lfs f3, float_3p1416_8041b510(r2)
	fmadds f2, f6, f2, f0
	lfs f0, float_180_8041b514(r2)
	stfs f2, 0x58(r30)
	lfs f5, 0x10(r1)
	lfs f4, 0xf4(r30)
	lfs f2, 0x2c(r1)
	fmuls f4, f5, f4
	fmadds f2, f6, f4, f2
	stfs f2, 0x60(r30)
	lfs f2, 0x100(r30)
	fsubs f1, f2, f1
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl cos
	frsp f2, f1
	lfs f0, 0x60(r30)
	lfs f1, float_90_8041b52c(r2)
	lfs f3, float_3p1416_8041b510(r2)
	fnmsubs f2, f31, f2, f0
	lfs f0, float_180_8041b514(r2)
	stfs f2, 0x60(r30)
	lfs f2, 0x100(r30)
	fsubs f1, f2, f1
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, 0x58(r30)
	lfs f2, float_0p5_8041b530(r2)
	fnmsubs f0, f31, f1, f0
	stfs f0, 0x58(r30)
	lfs f4, 0x104(r30)
	lfs f0, 0x3c(r1)
	lfs f3, 0x40(r1)
	fmuls f5, f0, f4
	lfs f1, 0x20(r1)
	fmuls f4, f3, f4
	lfs f3, 0x28(r1)
	lfs f0, 0x58(r30)
	fmuls f1, f5, f1
	fmadds f6, f4, f3, f1
	fnmsubs f1, f6, f3, f4
	fmadds f0, f2, f1, f0
	stfs f0, 0x58(r30)
	lfs f1, 0x20(r1)
	lfs f0, 0x60(r30)
	fnmsubs f1, f6, f1, f5
	fmadds f0, f2, f1, f0
	stfs f0, 0x60(r30)
	lha r0, 0x17c(r30)
	cmpwi r0, 0x0
	bne @10
	cmpwi r31, 0x0
	bne @11
	@10:
	stw r29, 0x130(r30)
	@11:
	stw r29, 0x12c(r30)
	mr r3, r29
	lfs f0, 0x34(r1)
	stfs f0, 0x58(r30)
	b @8
	@9:
	lfs f1, float_90_8041b52c(r2)
	lfs f0, 0x100(r30)
	lfs f2, float_3p1416_8041b510(r2)
	fadds f1, f1, f0
	lfs f0, float_180_8041b514(r2)
	lfs f4, float_0p4_8041b54c(r2)
	lfs f3, 0xf4(r30)
	fmuls f1, f2, f1
	fmuls f31, f4, f3
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_90_8041b52c(r2)
	frsp f4, f1
	lfs f0, 0x100(r30)
	lfs f3, 0x60(r30)
	fadds f1, f2, f0
	lfs f2, float_3p1416_8041b510(r2)
	lfs f0, float_180_8041b514(r2)
	fmadds f28, f31, f4, f3
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, float_0p4_8041b54c(r2)
	frsp f5, f1
	lfs f1, 0xf4(r30)
	addi r3, r1, 0x40
	lfs f0, 0x104(r30)
	addi r4, r1, 0x3c
	lfs f4, 0x58(r30)
	lfs f3, 0x5c(r30)
	fmadds f0, f2, f1, f0
	fmadds f29, f31, f5, f4
	fadds f30, f3, f30
	stfs f0, 0x38(r1)
	lfs f1, 0xf4(r30)
	lfs f0, 0x104(r30)
	fmadds f0, f2, f1, f0
	stfs f0, 0x38(r1)
	lfs f1, 0x100(r30)
	bl sincosf
	fmr f1, f29
	lfs f4, 0x40(r1)
	fmr f2, f30
	lfs f5, float_0_8041b51c(r2)
	fmr f3, f28
	lfs f6, 0x3c(r1)
	addi r4, r1, 0x34
	addi r5, r1, 0x30
	addi r6, r1, 0x2c
	addi r7, r1, 0x38
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	mr. r29, r3
	beq @12
	bl hitGetAttr
	andi. r0, r3, 0x5
	bne @12
	lfs f1, float_180_8041b514(r2)
	addi r3, r1, 0xc
	lfs f0, 0x100(r30)
	addi r4, r1, 0x8
	fadds f1, f1, f0
	bl sincosf
	lfs f1, 0xc(r1)
	lfs f0, 0xf4(r30)
	lfs f6, float_0p5_8041b530(r2)
	fmuls f1, f1, f0
	lfs f0, 0x34(r1)
	lfs f2, float_90_8041b52c(r2)
	lfs f3, float_3p1416_8041b510(r2)
	fmadds f1, f6, f1, f0
	lfs f0, float_180_8041b514(r2)
	stfs f1, 0x58(r30)
	lfs f5, 0x8(r1)
	lfs f4, 0xf4(r30)
	lfs f1, 0x2c(r1)
	fmuls f4, f5, f4
	fmadds f1, f6, f4, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x100(r30)
	fadds f1, f2, f1
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl cos
	frsp f1, f1
	lfs f0, 0x60(r30)
	lfs f2, float_90_8041b52c(r2)
	lfs f3, float_3p1416_8041b510(r2)
	fnmsubs f1, f31, f1, f0
	lfs f0, float_180_8041b514(r2)
	stfs f1, 0x60(r30)
	lfs f1, 0x100(r30)
	fadds f1, f2, f1
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, 0x58(r30)
	lfs f2, float_0p5_8041b530(r2)
	fnmsubs f0, f31, f1, f0
	stfs f0, 0x58(r30)
	lfs f4, 0x104(r30)
	lfs f0, 0x3c(r1)
	lfs f3, 0x40(r1)
	fmuls f5, f0, f4
	lfs f1, 0x20(r1)
	fmuls f4, f3, f4
	lfs f3, 0x28(r1)
	lfs f0, 0x58(r30)
	fmuls f1, f5, f1
	fmadds f6, f4, f3, f1
	fnmsubs f1, f6, f3, f4
	fmadds f0, f2, f1, f0
	stfs f0, 0x58(r30)
	lfs f1, 0x20(r1)
	lfs f0, 0x60(r30)
	fnmsubs f1, f6, f1, f5
	fmadds f0, f2, f1, f0
	stfs f0, 0x60(r30)
	lha r0, 0x17c(r30)
	cmpwi r0, 0x0
	bne @13
	cmpwi r31, 0x0
	bne @14
	@13:
	stw r29, 0x130(r30)
	@14:
	stw r29, 0x12c(r30)
	mr r3, r29
	lfs f0, 0x34(r1)
	stfs f0, 0x58(r30)
	b @8
	@12:
	li r3, 0x0
	@8:
	psq_l f31, 0xc8(r1), 0, 0
	lfd f31, 0xc0(r1)
	psq_l f30, 0xb8(r1), 0, 0
	lfd f30, 0xb0(r1)
	psq_l f29, 0xa8(r1), 0, 0
	lfd f29, 0xa0(r1)
	psq_l f28, 0x98(r1), 0, 0
	lfd f28, 0x90(r1)
	psq_l f27, 0x88(r1), 0, 0
	lfd f27, 0x80(r1)
	lwz r31, 0x7c(r1)
	lwz r30, 0x78(r1)
	lwz r0, 0xd4(r1)
	lwz r29, 0x74(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm void nokotaro_hold_cancel(PartyEntry* party) {
	nofralloc
	li r0, 0x14
	stb r0, 0x39(r3)
	blr
}

asm void nokonoko_finish(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr. r31, r3
	beq @1
	lbz r0, 0x31(r31)
	cmpwi r0, 0x2
	bne @1
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @1
	lwz r3, 0x174(r31)
	cmplwi r3, 0x0
	beq @2
	bl itemNokoForceGet
	li r0, 0x0
	stw r0, 0x174(r31)
	@2:
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @3
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	@3:
	lwz r3, 0x0(r31)
	li r0, 0x0
	lfs f0, float_37_8041b550(r2)
	rlwinm r3, r3, 0, 24, 22
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 6, 4
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 8, 6
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 7, 5
	stw r3, 0x0(r31)
	lwz r3, 0x4(r31)
	rlwinm r3, r3, 0, 27, 25
	stw r3, 0x4(r31)
	lwz r3, 0x4(r31)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r31)
	stfs f0, 0xf0(r31)
	stw r0, 0x178(r31)
	stw r0, 0x17c(r31)
	stw r0, 0x180(r31)
	lbz r0, 0x34(r31)
	cmplwi r0, 0x9
	beq @1
	lwz r3, 0x0(r31)
	clrrwi. r0, r3, 31
	bne @4
	mr r3, r31
	li r4, 0x2
	bl partyChgRunMode
	li r0, 0x0
	stb r0, 0x3b(r31)
	b @1
	@4:
	clrlwi r0, r3, 1
	mr r3, r31
	stw r0, 0x0(r31)
	li r4, 0x0
	bl partyChgRunMode
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void nokonoko_use(PartyEntry* party) {
	nofralloc
	stwu r1, -0x180(r1)
	mflr r0
	stw r0, 0x184(r1)
	stfd f31, 0x170(r1)
	psq_st f31, 0x178(r1), 0, 0
	stw r31, 0x16c(r1)
	stw r30, 0x168(r1)
	stw r29, 0x164(r1)
	mr r29, r3
	lis r3, vec3_802ce138@ha
	lwz r0, 0x0(r29)
	addi r31, r3, vec3_802ce138@l
	lwz r30, 0x160(r29)
	clrrwi. r0, r0, 31
	bne @1
	bl marioKeyOffChk
	cmpwi r3, 0x0
	beq @1
	lwz r7, 0x58(r29)
	addi r3, r1, 0x114
	lwz r0, 0x5c(r29)
	addi r4, r1, 0x38
	addi r5, r1, 0x34
	addi r6, r1, 0x30
	stw r7, 0x114(r1)
	stw r0, 0x118(r1)
	lwz r0, 0x60(r29)
	stw r0, 0x11c(r1)
	bl marioGetScreenPos
	lfs f1, 0x38(r1)
	lfs f0, 0x34(r1)
	fctiwz f1, f1
	fctiwz f0, f0
	stfd f1, 0x148(r1)
	stfd f0, 0x150(r1)
	lwz r3, 0x14c(r1)
	lwz r4, 0x154(r1)
	bl marioChkInScreen
	cmpwi r3, 0x0
	bne @1
	lfs f0, 0x8c(r30)
	stfs f0, 0x2c(r1)
	lfs f0, 0x94(r30)
	stfs f0, 0x28(r1)
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f3, 0x58(r29)
	lfs f4, 0x60(r29)
	bl angleABf
	fmr f2, f1
	lfs f1, float_160_8041b554(r2)
	addi r3, r1, 0x2c
	addi r4, r1, 0x28
	bl movePos
	lfs f0, 0x2c(r1)
	mr r3, r29
	stfs f0, 0x58(r29)
	lfs f0, 0x28(r1)
	stfs f0, 0x60(r29)
	bl nokonoko_finish
	b @2
	@1:
	lwz r3, 0x8(r29)
	rlwinm. r0, r3, 0, 28, 28
	beq @3
	rlwinm r3, r3, 0, 29, 27
	li r0, 0x0
	stw r3, 0x8(r29)
	stw r0, 0x174(r29)
	stw r0, 0x178(r29)
	stw r0, 0x17c(r29)
	stw r0, 0x180(r29)
	lwz r0, 0x0(r29)
	clrrwi. r0, r0, 31
	beq @4
	lwz r0, 0x16c(r29)
	cmpwi r0, 0x0
	ble @5
	lha r0, 0x17e(r29)
	ori r0, r0, 0x1
	sth r0, 0x17e(r29)
	b @5
	@4:
	lha r0, 0x17e(r29)
	clrrwi r0, r0, 1
	sth r0, 0x17e(r29)
	@5:
	li r0, 0x0
	stb r0, 0x39(r29)
	@3:
	lbz r0, 0x39(r29)
	cmplwi r0, 0x15
	bgt @6
	lis r3, jumptable_803137C4@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_803137C4@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@7:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x20
	beq @8
	cmplwi r0, 0x1f
	bne @9
	@8:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @6
	@9:
	mr r3, r29
	bl partyClearJumpPara
	lwz r0, 0x0(r29)
	mr r3, r29
	addi r4, r31, 0x18
	oris r0, r0, 0x400
	stw r0, 0x0(r29)
	lwz r0, 0x4(r29)
	ori r0, r0, 0x10
	stw r0, 0x4(r29)
	bl partyChgPose
	lfs f0, float_18p5_8041b558(r2)
	li r4, 0x1
	li r3, 0x64
	li r0, 0x0
	stfs f0, 0xf0(r29)
	stb r4, 0x39(r29)
	stw r3, 0x24(r29)
	stw r0, 0x174(r29)
	sth r0, 0x17c(r29)
	bl marioAdjustMoveDir
	lfs f0, float_0_8041b51c(r2)
	stfs f0, 0x180(r30)
	lwz r3, 0x8c(r30)
	lwz r0, 0x90(r30)
	stw r3, 0x94(r29)
	stw r0, 0x98(r29)
	lwz r0, 0x94(r30)
	stw r0, 0x9c(r29)
	lfs f1, 0x1ac(r30)
	bl toMovedirSimple
	fmr f2, f1
	lfs f1, float_2_8041b55c(r2)
	addi r3, r29, 0x94
	addi r4, r29, 0x9c
	bl movePos
	li r0, 0x4
	lfs f0, float_0_8041b51c(r2)
	stw r0, 0x24(r29)
	stfs f0, 0x114(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl distABf
	lwz r3, 0x24(r29)
	lis r0, 0x4330
	stw r0, 0x150(r1)
	xoris r0, r3, 0x8000
	lfd f3, 0x10(r31)
	stw r0, 0x154(r1)
	lfs f2, float_45_8041b560(r2)
	lfd f0, 0x150(r1)
	fsubs f0, f0, f3
	fdivs f0, f1, f0
	stfs f0, 0x104(r29)
	lfs f0, 0x10c(r29)
	fadds f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	li r0, 0x1
	stb r0, 0x39(r29)
	bl marioChgSmallJumpMotion
	lwz r0, 0xc(r30)
	lfs f0, float_0_8041b51c(r2)
	oris r0, r0, 0x2
	stw r0, 0xc(r30)
	stfs f0, 0x180(r30)
	b @6
	@10:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x20
	beq @11
	cmplwi r0, 0x1f
	bne @12
	@11:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @6
	@12:
	lfs f1, float_45_8041b560(r2)
	lfs f0, 0x10c(r29)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lis r0, 0x4330
	lfd f3, 0x10(r31)
	lwz r3, 0x24(r29)
	stw r0, 0x150(r1)
	xoris r3, r3, 0x8000
	lfs f2, 0x58(r29)
	stw r3, 0x154(r1)
	lfs f1, 0x94(r29)
	lfd f0, 0x150(r1)
	fsubs f1, f1, f2
	stw r0, 0x148(r1)
	fsubs f0, f0, f3
	stw r0, 0x158(r1)
	fdivs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x58(r29)
	lwz r0, 0x24(r29)
	lfs f2, 0x5c(r29)
	xoris r0, r0, 0x8000
	lfs f0, 0x98(r29)
	stw r0, 0x14c(r1)
	fsubs f1, f0, f2
	lfd f0, 0x148(r1)
	fsubs f0, f0, f3
	fdivs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x5c(r29)
	lwz r0, 0x24(r29)
	lfs f2, 0x60(r29)
	xoris r0, r0, 0x8000
	lfs f0, 0x9c(r29)
	stw r0, 0x15c(r1)
	fsubs f1, f0, f2
	lfd f0, 0x158(r1)
	fsubs f0, f0, f3
	fdivs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x60(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @6
	lwz r6, 0x94(r29)
	li r0, 0x2
	lwz r5, 0x98(r29)
	mr r3, r29
	lfs f0, float_0_8041b51c(r2)
	addi r4, r31, 0x20
	stw r6, 0x58(r29)
	stw r5, 0x5c(r29)
	lwz r5, 0x9c(r29)
	stw r5, 0x60(r29)
	stfs f0, 0x104(r29)
	lfs f0, 0x1ac(r30)
	stfs f0, 0x110(r29)
	lfs f0, 0x1ac(r30)
	stfs f0, 0x10c(r29)
	stb r0, 0x39(r29)
	bl partyChgPose
	@13:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x20
	beq @14
	cmplwi r0, 0x1f
	bne @15
	@14:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @6
	@15:
	lwz r0, 0x1e4(r30)
	cmplwi r0, 0x0
	beq @6
	li r3, 0x3
	bl marioChgMot
	lwz r4, 0x0(r30)
	li r3, 0xa
	lfs f0, float_0_8041b51c(r2)
	li r0, 0xf
	ori r4, r4, 0x80
	stw r4, 0x0(r30)
	stfs f0, 0x180(r30)
	stb r3, 0x39(r29)
	stw r0, 0x24(r29)
	stfs f0, 0x104(r29)
	stfs f0, 0x128(r29)
	lfs f1, 0x1ac(r30)
	bl toMovedir
	stfs f1, 0x100(r29)
	addi r4, r29, 0x58
	li r3, 0x92d
	bl psndSFXOn_3D
	b @6
	@16:
	addi r4, r29, 0x58
	li r3, 0x92a
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x3
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	lwz r3, 0x0(r29)
	li r0, 0xb
	oris r3, r3, 0x400
	stw r3, 0x0(r29)
	lwz r3, 0x0(r29)
	oris r3, r3, 0x100
	stw r3, 0x0(r29)
	stb r0, 0x39(r29)
	@17:
	lfs f2, 0x104(r29)
	lfs f1, float_2_8041b55c(r2)
	lfs f0, float_10_8041b534(r2)
	fadds f1, f2, f1
	stfs f1, 0x104(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	ble @18
	stfs f0, 0x104(r29)
	@18:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @19
	lfs f2, float_1_8041b548(r2)
	b @20
	@19:
	lfs f2, float_neg1_8041b520(r2)
	@20:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lwz r3, gp(r13)
	lwz r0, 0x1c(r3)
	clrlwi. r0, r0, 31
	beq @21
	lfs f3, 0xf0(r29)
	li r3, 0x0
	lfs f2, float_0p25_8041b570(r2)
	lfs f0, 0x5c(r29)
	lfs f1, 0x58(r29)
	fmadds f2, f3, f2, f0
	lfs f3, 0x60(r29)
	lfs f4, float_0p3_8041b574(r2)
	bl effKemuTestEntry
	lwz r4, 0x164(r29)
	bl effKemuTestDrawCam
	@21:
	lfs f1, 0x128(r29)
	lfs f0, 0x104(r29)
	fadds f0, f1, f0
	stfs f0, 0x128(r29)
	lwz r0, 0x174(r29)
	cmplwi r0, 0x0
	bne @22
	lfs f3, float_0p5_8041b530(r2)
	lfs f2, 0xf4(r29)
	lfs f0, float_12_8041b578(r2)
	lfs f1, 0x58(r29)
	fmadds f4, f3, f2, f0
	lfs f2, 0x5c(r29)
	lfs f3, 0x60(r29)
	bl itemNearDistCheck
	stw r3, 0x174(r29)
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @22
	bl itemPickUp
	li r0, 0x32
	addi r4, r29, 0x58
	stb r0, 0x39(r29)
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	b @6
	@22:
	mr r3, r29
	li r4, 0x0
	bl ccwall
	cmplwi r3, 0x0
	beq @23
	li r0, 0x32
	addi r4, r29, 0x58
	stb r0, 0x39(r29)
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	b @6
	@23:
	lfs f1, 0x128(r29)
	lfs f0, float_120_8041b57c(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	li r0, 0xc
	lfs f1, float_neg1_8041b520(r2)
	stb r0, 0x39(r29)
	lfs f3, float_0p15_8041b580(r2)
	lfs f2, 0x104(r29)
	lfs f0, float_0_8041b51c(r2)
	fsubs f1, f1, f2
	fmadds f1, f3, f1, f2
	stfs f1, 0x104(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @6
	stfs f0, 0x104(r29)
	lwz r0, 0x0(r29)
	clrrwi. r0, r0, 31
	bne @24
	lhz r0, 0x246(r30)
	rlwinm. r0, r0, 0, 21, 21
	beq @25
	li r3, 0xd
	li r0, 0x0
	stb r3, 0x39(r29)
	stw r0, 0x24(r29)
	b @6
	@25:
	li r0, 0x32
	stb r0, 0x39(r29)
	b @6
	@24:
	lha r0, 0x17e(r29)
	clrlwi. r0, r0, 31
	beq @26
	li r0, 0x5
	li r3, 0x15
	stw r0, 0x24(r29)
	li r0, 0x1
	stb r3, 0x39(r29)
	sth r0, 0x17c(r29)
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne @6
	addi r4, r29, 0x58
	li r3, 0x92e
	bl psndSFXOn_3D
	stw r3, nokoSe(r13)
	b @6
	@26:
	li r0, 0x32
	stb r0, 0x39(r29)
	b @6
	@27:
	lwz r3, 0x24(r29)
	addi r0, r3, 0x1
	cmpwi r0, 0x5
	stw r0, 0x24(r29)
	blt @28
	li r0, 0x5
	li r3, 0x14
	stw r0, 0x24(r29)
	li r0, 0x1
	stb r3, 0x39(r29)
	sth r0, 0x17c(r29)
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne @28
	addi r4, r29, 0x58
	li r3, 0x92e
	bl psndSFXOn_3D
	stw r3, nokoSe(r13)
	@28:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @29
	lfs f2, float_1_8041b548(r2)
	b @30
	@29:
	lfs f2, float_neg1_8041b520(r2)
	@30:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lis r3, 0x8889
	subi r0, r3, 0x7777
	lwz r3, gp(r13)
	lwz r3, 0x1c(r3)
	mulhwu r0, r0, r3
	srwi r0, r0, 4
	mulli r0, r0, 0x1e
	subf. r0, r0, r3
	bne @31
	lfs f1, 0x58(r29)
	li r3, 0x5
	lfs f2, 0x5c(r29)
	lfs f3, 0x60(r29)
	lfs f4, float_1_8041b548(r2)
	bl effKemuTestEntry
	lwz r4, 0x164(r29)
	bl effKemuTestDrawCam
	@31:
	mr r3, r29
	li r4, 0x0
	bl ccwall
	cmplwi r3, 0x0
	beq @32
	li r0, 0x32
	addi r4, r29, 0x58
	stb r0, 0x39(r29)
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @6
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	b @6
	@32:
	lwz r0, 0x174(r29)
	cmplwi r0, 0x0
	bne @33
	lfs f3, float_0p5_8041b530(r2)
	lfs f2, 0xf4(r29)
	lfs f0, float_12_8041b578(r2)
	lfs f1, 0x58(r29)
	fmadds f4, f3, f2, f0
	lfs f2, 0x5c(r29)
	lfs f3, 0x60(r29)
	bl itemNearDistCheck
	stw r3, 0x174(r29)
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @33
	bl itemPickUp
	li r0, 0x32
	addi r4, r29, 0x58
	stb r0, 0x39(r29)
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @6
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	b @6
	@33:
	lwz r0, 0x0(r29)
	clrrwi. r0, r0, 31
	bne @34
	lhz r3, 0x2e(r30)
	cmplwi r3, 0x19
	beq @35
	cmplwi r3, 0x14
	beq @35
	cmplwi r3, 0x18
	beq @35
	cmplwi r3, 0x16
	beq @35
	subi r0, r3, 0x1f
	clrlwi r0, r0, 16
	cmplwi r0, 0x1
	ble @35
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 26, 26
	bne @35
	bl marioChkKey
	cmpwi r3, 0x0
	bne @36
	@35:
	mr r3, r29
	bl nokonoko_finish
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @6
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	b @6
	@36:
	lhz r0, 0x246(r30)
	rlwinm. r0, r0, 0, 21, 21
	bne @6
	lha r0, 0x17c(r29)
	li r3, 0x32
	cmpwi r0, 0x0
	beq @37
	li r3, 0x50
	@37:
	stb r3, 0x39(r29)
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @6
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	b @6
	@34:
	lha r0, 0x17e(r29)
	clrlwi. r0, r0, 31
	beq @38
	li r0, 0x50
	stb r0, 0x39(r29)
	b @39
	@38:
	li r0, 0x32
	stb r0, 0x39(r29)
	@39:
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @6
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	b @6
	@40:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @41
	lfs f2, float_1_8041b548(r2)
	b @42
	@41:
	lfs f2, float_neg1_8041b520(r2)
	@42:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lis r3, 0x8889
	subi r0, r3, 0x7777
	lwz r3, gp(r13)
	lwz r3, 0x1c(r3)
	mulhwu r0, r0, r3
	srwi r0, r0, 4
	mulli r0, r0, 0x1e
	subf. r0, r0, r3
	bne @6
	lfs f1, 0x58(r29)
	li r3, 0x5
	lfs f2, 0x5c(r29)
	lfs f3, 0x60(r29)
	lfs f4, float_1_8041b548(r2)
	bl effKemuTestEntry
	lwz r4, 0x164(r29)
	bl effKemuTestDrawCam
	@6:
	lbz r3, 0x39(r29)
	subi r0, r3, 0x32
	cmplwi r0, 0x15
	bgt @43
	lis r3, jumptable_8031376C@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8031376C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@44:
	mr r3, r29
	bl partyClearJumpPara
	li r0, 0x33
	lfs f0, float_0_8041b51c(r2)
	stb r0, 0x39(r29)
	stfs f0, 0x104(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	addi r4, r29, 0x58
	li r3, 0x92b
	bl psndSFXOn_3D
	b @43
	@45:
	lha r0, 0x17c(r29)
	cmpwi r0, 0x0
	beq @46
	lfs f3, float_20_8041b584(r2)
	b @47
	@46:
	lfs f3, float_10_8041b534(r2)
	@47:
	lfs f1, 0x104(r29)
	lfs f2, float_0p3_8041b574(r2)
	fsubs f0, f3, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x104(r29)
	lfs f0, 0x104(r29)
	fcmpo cr0, f0, f3
	cror eq, gt, eq
	bne @48
	stfs f3, 0x104(r29)
	lfs f0, float_10_8041b534(r2)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	bge @48
	li r0, 0x34
	stb r0, 0x39(r29)
	@48:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	cmplwi r3, 0x0
	beq @49
	mr r3, r29
	addi r4, r1, 0x24
	addi r5, r1, 0x20
	bl partyGetMoveDirSpd
	lfs f1, 0x20(r1)
	addi r3, r29, 0x58
	lfs f2, 0x24(r1)
	li r4, 0x1
	lfs f3, 0xf4(r29)
	lfs f4, 0xf0(r29)
	bl marioChkWallAround
	li r0, 0x46
	addi r4, r29, 0x58
	stb r0, 0x39(r29)
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	b @2
	@49:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @50
	lfs f2, float_1_8041b548(r2)
	b @51
	@50:
	lfs f2, float_neg1_8041b520(r2)
	@51:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f3, float_neg1_8041b520(r2)
	lfs f2, 0x104(r29)
	lfs f4, float_0p1_8041b518(r2)
	fsubs f1, f3, f2
	lfs f0, float_0_8041b51c(r2)
	fmadds f1, f4, f1, f2
	stfs f1, 0x104(r29)
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @43
	stfs f0, 0x128(r29)
	li r0, 0x35
	lfs f0, float_50_8041b56c(r2)
	stb r0, 0x39(r29)
	lfs f2, 0x104(r29)
	fsubs f1, f3, f2
	fmadds f1, f4, f1, f2
	stfs f1, 0x104(r29)
	stfs f0, 0x178(r29)
	b @43
	@52:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	cmplwi r3, 0x0
	beq @53
	li r0, 0x46
	stb r0, 0x39(r29)
	b @2
	@53:
	lfs f2, 0x178(r29)
	lfs f1, float_2p2_8041b588(r2)
	lfs f0, float_0_8041b51c(r2)
	fsubs f1, f2, f1
	stfs f1, 0x178(r29)
	lfs f1, 0x178(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @54
	stfs f0, 0x178(r29)
	@54:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @55
	lfs f2, float_1_8041b548(r2)
	b @56
	@55:
	lfs f2, float_neg1_8041b520(r2)
	@56:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, float_neg2_8041b58c(r2)
	lfs f0, 0x104(r29)
	lha r0, 0x17c(r29)
	fsubs f3, f1, f0
	cmpwi r0, 0x0
	beq @57
	lfs f2, float_0p2_8041b590(r2)
	b @58
	@57:
	lfs f2, float_0p1_8041b518(r2)
	@58:
	lfs f1, 0x104(r29)
	lfs f0, float_0_8041b51c(r2)
	fmadds f1, f3, f2, f1
	stfs f1, 0x104(r29)
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @43
	stfs f0, 0x104(r29)
	addi r3, r1, 0x108
	addi r4, r1, 0x138
	lwz r5, 0x94(r29)
	lwz r0, 0x98(r29)
	stw r5, 0x108(r1)
	stw r0, 0x10c(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x110(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPos
	lwz r0, 0x138(r29)
	cmplwi r0, 0x0
	beq @59
	subi r0, r3, 0x1
	cmplwi r0, 0x1
	ble @60
	cmplwi r3, 0x4
	beq @60
	cmplwi r3, 0x8
	bne @59
	@60:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @43
	@59:
	cmplwi r3, 0xf
	bgt @61
	lis r4, jumptable_8031372C@ha
	slwi r0, r3, 2
	addi r3, r4, jumptable_8031372C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@62:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xfc
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	lfs f2, float_135_8041b594(r2)
	stw r5, 0xfc(r1)
	stw r0, 0x100(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x104(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @63
	@64:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xf0
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	lfs f2, float_315_8041b598(r2)
	stw r5, 0xf0(r1)
	stw r0, 0xf4(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xf8(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @63
	@65:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xe4
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	lfs f2, float_225_8041b59c(r2)
	stw r5, 0xe4(r1)
	stw r0, 0xe8(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xec(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @63
	@66:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xd8
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	lfs f2, float_315_8041b598(r2)
	stw r5, 0xd8(r1)
	stw r0, 0xdc(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xe0(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @63
	@67:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @63
	@68:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xcc
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	lfs f2, float_270_8041b5a0(r2)
	stw r5, 0xcc(r1)
	stw r0, 0xd0(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xd4(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @63
	@69:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xc0
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	stw r5, 0xc0(r1)
	stw r0, 0xc4(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xc8(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPos3
	b @63
	@61:
	lwz r5, 0x94(r29)
	addi r3, r1, 0xb4
	lwz r0, 0x98(r29)
	addi r4, r1, 0x138
	stw r5, 0xb4(r1)
	stw r0, 0xb8(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xbc(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPos2
	@63:
	li r0, 0x36
	stb r0, 0x39(r29)
	lwz r3, 0x138(r1)
	lwz r0, 0x13c(r1)
	stw r3, 0x94(r29)
	stw r0, 0x98(r29)
	lwz r0, 0x140(r1)
	stw r0, 0x9c(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl distABf
	stfs f1, 0x128(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	b @43
	@70:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @71
	lfs f2, float_1_8041b548(r2)
	b @72
	@71:
	lfs f2, float_neg1_8041b520(r2)
	@72:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, float_0p5_8041b530(r2)
	lfs f2, 0x104(r29)
	lfs f0, float_4_8041b5a4(r2)
	fadds f1, f2, f1
	stfs f1, 0x104(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @73
	stfs f0, 0x104(r29)
	@73:
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	lfs f0, float_10_8041b534(r2)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @43
	li r0, 0x46
	lfs f0, float_0_8041b51c(r2)
	stb r0, 0x39(r29)
	stfs f0, 0x104(r29)
	b @2
	@74:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	cmplwi r3, 0x0
	beq @75
	li r0, 0x46
	stb r0, 0x39(r29)
	b @2
	@75:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @76
	lfs f2, float_1_8041b548(r2)
	b @77
	@76:
	lfs f2, float_neg1_8041b520(r2)
	@77:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, float_2p2_8041b588(r2)
	lfs f2, 0x178(r29)
	lfs f0, float_0_8041b51c(r2)
	fsubs f1, f2, f1
	stfs f1, 0x178(r29)
	lfs f1, 0x178(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @78
	stfs f0, 0x178(r29)
	@78:
	lha r0, 0x17c(r29)
	lfs f1, float_neg2_8041b58c(r2)
	lfs f0, 0x104(r29)
	cmpwi r0, 0x0
	fsubs f3, f1, f0
	beq @79
	lfs f2, float_0p2_8041b590(r2)
	b @80
	@79:
	lfs f2, float_0p1_8041b518(r2)
	@80:
	lfs f1, 0x104(r29)
	lfs f0, float_0_8041b51c(r2)
	fmadds f1, f3, f2, f1
	stfs f1, 0x104(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @43
	li r0, 0x46
	stb r0, 0x39(r29)
	stfs f0, 0x104(r29)
	b @2
	@81:
	lfs f3, 0x58(r29)
	lfs f2, 0x8c(r30)
	lfs f1, 0x5c(r29)
	lfs f0, 0x90(r30)
	fsubs f4, f3, f2
	lfs f2, 0x60(r29)
	fsubs f3, f1, f0
	lfs f0, 0x94(r30)
	fmuls f1, f4, f4
	fsubs f2, f2, f0
	fmuls f0, f3, f3
	fmuls f2, f2, f2
	fadds f0, f1, f0
	fadds f1, f2, f0
	bl sqrt
	frsp f1, f1
	lfs f0, float_5_8041b5a8(r2)
	fcmpo cr0, f1, f0
	bge @82
	lfs f2, 0x1a0(r30)
	lfd f0, 0x28(r31)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @83
	lfs f0, float_neg90_8041b5ac(r2)
	b @84
	@83:
	lfs f0, float_90_8041b52c(r2)
	@84:
	lfs f1, float_0p5_8041b530(r2)
	fadds f2, f2, f0
	lfs f0, 0x1b4(r30)
	addi r3, r29, 0x58
	addi r4, r29, 0x60
	fmuls f1, f1, f0
	bl movePos
	mr r3, r29
	li r4, 0x1
	bl ccwall
	@82:
	lfs f0, float_0_8041b51c(r2)
	li r0, 0x47
	stfs f0, 0x104(r29)
	lwz r3, 0x4(r29)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r29)
	lwz r3, 0x4(r29)
	ori r3, r3, 0x20
	stw r3, 0x4(r29)
	stb r0, 0x39(r29)
	b @43
	@85:
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @86
	bl itemNokoForceGet
	li r0, 0x0
	stw r0, 0x174(r29)
	@86:
	mr r3, r29
	bl nokonoko_finish
	b @2
	@43:
	lbz r3, 0x39(r29)
	subi r0, r3, 0x50
	cmplwi r0, 0x22
	bgt @87
	lis r3, jumptable_803136A0@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_803136A0@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@88:
	li r0, 0x51
	lfs f0, float_0_8041b51c(r2)
	stb r0, 0x39(r29)
	stfs f0, 0x104(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	addi r4, r29, 0x58
	lfs f0, float_75_8041b5b0(r2)
	li r3, 0x92b
	lfs f1, 0x128(r29)
	fadds f0, f1, f0
	stfs f0, 0x128(r29)
	bl psndSFXOn_3D
	@89:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @90
	lfs f2, float_1_8041b548(r2)
	b @91
	@90:
	lfs f2, float_neg1_8041b520(r2)
	@91:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, float_3_8041b5b4(r2)
	lfs f2, 0x104(r29)
	lfs f0, float_18_8041b5b8(r2)
	fadds f1, f2, f1
	stfs f1, 0x104(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @92
	stfs f0, 0x104(r29)
	@92:
	lwz r0, 0x174(r29)
	cmplwi r0, 0x0
	bne @93
	lfs f3, float_0p5_8041b530(r2)
	lfs f2, 0xf4(r29)
	lfs f0, float_12_8041b578(r2)
	lfs f1, 0x58(r29)
	fmadds f4, f3, f2, f0
	lfs f2, 0x5c(r29)
	lfs f3, 0x60(r29)
	bl itemNearDistCheck
	stw r3, 0x174(r29)
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @93
	bl itemPickUp
	addi r4, r29, 0x58
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	@93:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	mr. r30, r3
	beq @94
	bl hitGetAttr
	clrrwi. r0, r3, 31
	bne @95
	li r0, 0x64
	stb r0, 0x39(r29)
	b @2
	@95:
	mr r3, r30
	bl mobjHitObjPtrToPtr
	li r0, 0x6e
	stb r0, 0x39(r29)
	b @2
	@94:
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	lfs f0, float_20_8041b584(r2)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @87
	li r0, 0x52
	stb r0, 0x39(r29)
	b @87
	@96:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @97
	lfs f2, float_1_8041b548(r2)
	b @98
	@97:
	lfs f2, float_neg1_8041b520(r2)
	@98:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f0, float_neg1_8041b520(r2)
	lfs f1, 0x104(r29)
	lfs f2, float_0p35_8041b5bc(r2)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x104(r29)
	lwz r0, 0x174(r29)
	cmplwi r0, 0x0
	bne @99
	lfs f3, float_0p5_8041b530(r2)
	lfs f2, 0xf4(r29)
	lfs f0, float_12_8041b578(r2)
	lfs f1, 0x58(r29)
	fmadds f4, f3, f2, f0
	lfs f2, 0x5c(r29)
	lfs f3, 0x60(r29)
	bl itemNearDistCheck
	stw r3, 0x174(r29)
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @99
	bl itemPickUp
	addi r4, r29, 0x58
	li r3, 0x92c
	bl psndSFXOn_3D
	lfs f2, float_6p2832_8041b564(r2)
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	lfs f2, float_6p2832_8041b564(r2)
	frsp f31, f1
	lfs f1, 0x100(r29)
	lfs f0, float_360_8041b568(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, 0x5c(r29)
	frsp f4, f1
	lfs f0, 0xf0(r29)
	fneg f6, f31
	lfs f1, 0x58(r29)
	li r3, 0x3
	fadds f2, f2, f0
	lfs f3, 0x60(r29)
	li r4, 0x1
	lfs f5, float_neg1_8041b520(r2)
	bl effSmallStarN64Entry
	@99:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	cmplwi r3, 0x0
	beq @100
	li r0, 0x64
	stb r0, 0x39(r29)
	b @87
	@100:
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	lfs f0, float_0_8041b51c(r2)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @87
	lfs f1, 0x94(r29)
	lfs f2, 0x9c(r29)
	lfs f3, 0x58(r29)
	lfs f4, 0x60(r29)
	bl distABf
	stfs f1, 0x128(r29)
	li r0, 0x54
	lfs f0, float_50_8041b56c(r2)
	stb r0, 0x39(r29)
	stfs f0, 0x178(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	b @87
	@101:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @102
	lfs f2, float_1_8041b548(r2)
	b @103
	@102:
	lfs f2, float_neg1_8041b520(r2)
	@103:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	mr r3, r29
	li r4, 0x1
	bl ccwall
	cmplwi r3, 0x0
	beq @104
	li r0, 0x64
	stb r0, 0x39(r29)
	b @87
	@104:
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	lfs f0, float_30_8041b538(r2)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @87
	li r0, 0x56
	lfs f0, float_0_8041b51c(r2)
	stb r0, 0x39(r29)
	li r3, 0x1f4
	stfs f0, 0x104(r29)
	bl sysMsec2Frame
	stw r3, 0x24(r29)
	b @87
	@105:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @106
	lfs f2, float_1_8041b548(r2)
	b @107
	@106:
	lfs f2, float_neg1_8041b520(r2)
	@107:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @108
	li r0, 0x64
	stb r0, 0x39(r29)
	@108:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	cmplwi r3, 0x0
	beq @87
	li r0, 0x64
	stb r0, 0x39(r29)
	b @87
	@109:
	mr r3, r29
	li r4, 0x1
	bl ccwall
	lfs f3, 0x58(r29)
	lfs f2, 0x8c(r30)
	lfs f1, 0x5c(r29)
	lfs f0, 0x90(r30)
	fsubs f4, f3, f2
	lfs f2, 0x60(r29)
	fsubs f3, f1, f0
	lfs f0, 0x94(r30)
	fmuls f1, f4, f4
	fsubs f2, f2, f0
	fmuls f0, f3, f3
	fmuls f2, f2, f2
	fadds f0, f1, f0
	fadds f1, f2, f0
	bl sqrt
	frsp f1, f1
	lfs f0, float_5_8041b5a8(r2)
	fcmpo cr0, f1, f0
	bge @110
	lfs f2, 0x1a0(r30)
	lfd f0, 0x28(r31)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @111
	lfs f0, float_90_8041b52c(r2)
	b @112
	@111:
	lfs f0, float_neg90_8041b5ac(r2)
	@112:
	lfs f1, float_0p5_8041b530(r2)
	fadds f2, f2, f0
	lfs f0, 0x1b4(r30)
	addi r3, r29, 0x58
	addi r4, r29, 0x60
	fmuls f1, f1, f0
	bl movePos
	mr r3, r29
	li r4, 0x1
	bl ccwall
	@110:
	lfs f0, float_0_8041b51c(r2)
	stfs f0, 0x104(r29)
	lwz r0, 0x4(r29)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r29)
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @113
	bl itemNokoForceGet
	li r0, 0x0
	stw r0, 0x174(r29)
	@113:
	lwz r0, 0x138(r29)
	cmplwi r0, 0x0
	bne @114
	li r0, 0x58
	stb r0, 0x39(r29)
	b @87
	@114:
	lwz r3, 0x174(r29)
	cmplwi r3, 0x0
	beq @115
	bl itemNokoForceGet
	li r0, 0x0
	stw r0, 0x174(r29)
	@115:
	mr r3, r29
	bl nokonoko_finish
	b @2
	@116:
	lfs f0, float_0_8041b51c(r2)
	addi r3, r1, 0xa8
	addi r4, r1, 0x12c
	stfs f0, 0x104(r29)
	lwz r5, 0x94(r29)
	lwz r0, 0x98(r29)
	stw r5, 0xa8(r1)
	stw r0, 0xac(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xb0(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPos
	lwz r0, 0x138(r29)
	cmplwi r0, 0x0
	beq @117
	subi r0, r3, 0x1
	cmplwi r0, 0x1
	ble @118
	cmplwi r3, 0x4
	beq @118
	cmplwi r3, 0x8
	bne @117
	@118:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @87
	@117:
	cmplwi r3, 0xf
	bgt @119
	lis r4, jumptable_80313660@ha
	slwi r0, r3, 2
	addi r3, r4, jumptable_80313660@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@120:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x9c
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	lfs f2, float_135_8041b594(r2)
	stw r5, 0x9c(r1)
	stw r0, 0xa0(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0xa4(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @121
	@122:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x90
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	lfs f2, float_315_8041b598(r2)
	stw r5, 0x90(r1)
	stw r0, 0x94(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x98(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @121
	@123:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x84
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	lfs f2, float_225_8041b59c(r2)
	stw r5, 0x84(r1)
	stw r0, 0x88(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x8c(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @121
	@124:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x78
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	lfs f2, float_315_8041b598(r2)
	stw r5, 0x78(r1)
	stw r0, 0x7c(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x80(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @121
	@125:
	li r0, 0x46
	stb r0, 0x39(r29)
	b @121
	@126:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x6c
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	lfs f2, float_270_8041b5a0(r2)
	stw r5, 0x6c(r1)
	stw r0, 0x70(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x74(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPosSub
	b @121
	@127:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x60
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	stw r5, 0x60(r1)
	stw r0, 0x64(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x68(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPos3
	b @121
	@119:
	lwz r5, 0x94(r29)
	addi r3, r1, 0x54
	lwz r0, 0x98(r29)
	addi r4, r1, 0x12c
	stw r5, 0x54(r1)
	stw r0, 0x58(r1)
	lwz r0, 0x9c(r29)
	stw r0, 0x5c(r1)
	lfs f1, 0xf0(r29)
	bl lookupSafetyPos2
	@121:
	li r0, 0x5a
	stb r0, 0x39(r29)
	lwz r3, 0x12c(r1)
	lwz r0, 0x130(r1)
	stw r3, 0x94(r29)
	stw r0, 0x98(r29)
	lwz r0, 0x134(r1)
	stw r0, 0x9c(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl distABf
	stfs f1, 0x128(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	lfs f0, float_50_8041b56c(r2)
	stfs f0, 0x178(r29)
	b @87
	@128:
	lfs f1, 0x100(r29)
	lfs f0, 0xf8(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041b514(r2)
	fcmpo cr0, f1, f0
	ble @129
	lfs f2, float_1_8041b548(r2)
	b @130
	@129:
	lfs f2, float_neg1_8041b520(r2)
	@130:
	lfs f1, float_50_8041b56c(r2)
	lfs f0, 0x10c(r29)
	fmadds f1, f1, f2, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, float_0p5_8041b530(r2)
	lfs f2, 0x104(r29)
	lfs f0, float_4_8041b5a4(r2)
	fadds f1, f2, f1
	stfs f1, 0x104(r29)
	lfs f1, 0x104(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @131
	stfs f0, 0x104(r29)
	@131:
	lfs f2, 0x128(r29)
	lfs f1, 0x104(r29)
	lfs f0, float_10_8041b534(r2)
	fsubs f1, f2, f1
	stfs f1, 0x128(r29)
	lfs f1, 0x128(r29)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @87
	li r0, 0x46
	lfs f0, float_0_8041b51c(r2)
	stb r0, 0x39(r29)
	stfs f0, 0x104(r29)
	b @87
	@132:
	lfs f1, float_0_8041b51c(r2)
	li r3, 0x3e8
	lfs f0, float_15_8041b5c0(r2)
	stfs f1, 0x104(r29)
	stfs f0, 0x114(r29)
	stfs f1, 0x118(r29)
	bl sysMsec2Frame
	stw r3, 0x24(r29)
	li r0, 0x6f
	stb r0, 0x39(r29)
	@133:
	lfs f1, 0x5c(r29)
	addi r3, r1, 0x48
	lfs f0, 0x114(r29)
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	fadds f0, f1, f0
	stfs f0, 0x5c(r29)
	lwz r7, 0x58(r29)
	lwz r0, 0x5c(r29)
	stw r7, 0x48(r1)
	stw r0, 0x4c(r1)
	lwz r0, 0x60(r29)
	stw r0, 0x50(r1)
	bl marioGetScreenPos
	lfs f1, 0x18(r1)
	lfs f0, float_neg300_8041b5c4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @87
	li r3, 0x320
	bl sysMsec2Frame
	stw r3, 0x24(r29)
	li r0, 0x70
	stb r0, 0x39(r29)
	b @87
	@134:
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @87
	lwz r0, 0x0(r29)
	clrrwi. r0, r0, 31
	bne @135
	addi r3, r1, 0x120
	bl partyGetReturnPos
	b @136
	@135:
	lwz r4, 0x8c(r30)
	li r0, 0x0
	lwz r3, 0x90(r30)
	lfs f0, float_90_8041b52c(r2)
	stw r4, 0x120(r1)
	stw r3, 0x124(r1)
	lwz r3, 0x94(r30)
	stw r3, 0x128(r1)
	lfs f1, 0x1ac(r30)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @137
	lfs f0, float_270_8041b5a0(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @137
	li r0, 0x1
	@137:
	cmpwi r0, 0x0
	beq @138
	lfs f1, float_0_8041b51c(r2)
	b @139
	@138:
	lfs f1, float_180_8041b514(r2)
	@139:
	lfs f2, float_neg30_8041b5c8(r2)
	bl toMovedir2
	fmr f2, f1
	lfs f1, float_30_8041b538(r2)
	addi r3, r1, 0x120
	addi r4, r1, 0x128
	bl movePos
	@136:
	lfs f0, 0x120(r1)
	li r0, 0x71
	lfs f3, float_1000_8041b5cc(r2)
	stfs f0, 0x58(r29)
	lfs f2, float_0_8041b51c(r2)
	lfs f0, 0x124(r1)
	lfs f1, float_neg1_8041b520(r2)
	fadds f3, f3, f0
	lfs f0, float_37_8041b550(r2)
	stfs f3, 0x5c(r29)
	lfs f3, 0x128(r1)
	stfs f3, 0x60(r29)
	stfs f2, 0x114(r29)
	stfs f1, 0x118(r29)
	stfs f2, 0x104(r29)
	lwz r3, 0x0(r29)
	ori r3, r3, 0x20
	stw r3, 0x0(r29)
	lwz r3, 0x0(r29)
	oris r3, r3, 0x200
	stw r3, 0x0(r29)
	lwz r3, 0x0(r29)
	rlwinm r3, r3, 0, 6, 4
	stw r3, 0x0(r29)
	lwz r3, 0x0(r29)
	rlwinm r3, r3, 0, 8, 6
	stw r3, 0x0(r29)
	lwz r3, 0x4(r29)
	rlwinm r3, r3, 0, 27, 25
	stw r3, 0x4(r29)
	lwz r3, 0x4(r29)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r29)
	stfs f0, 0xf0(r29)
	stb r0, 0x39(r29)
	b @87
	@140:
	lwz r7, 0x58(r29)
	addi r3, r1, 0x3c
	lwz r0, 0x5c(r29)
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	stw r7, 0x3c(r1)
	stw r0, 0x40(r1)
	lwz r0, 0x60(r29)
	stw r0, 0x44(r1)
	bl marioGetScreenPos
	lfs f1, 0xc(r1)
	lfs f0, float_240_8041b5d0(r2)
	fcmpo cr0, f1, f0
	ble @141
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r29)
	@141:
	mr r3, r29
	bl partyMove
	lfs f0, 0x114(r29)
	lfs f1, float_neg6_8041b5d4(r2)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @142
	lfs f0, float_0_8041b51c(r2)
	stfs f0, 0x118(r29)
	stfs f1, 0x114(r29)
	@142:
	lfs f1, 0x5c(r29)
	lfs f0, float_neg2000_8041b5d8(r2)
	fcmpo cr0, f1, f0
	bge @143
	lwz r3, 0x8c(r30)
	lwz r0, 0x90(r30)
	lfs f0, float_200_8041b5dc(r2)
	stw r3, 0x58(r29)
	stw r0, 0x5c(r29)
	lwz r0, 0x94(r30)
	stw r0, 0x60(r29)
	lfs f1, 0x5c(r29)
	fadds f0, f1, f0
	stfs f0, 0x5c(r29)
	@143:
	lwz r0, 0x138(r29)
	cmplwi r0, 0x0
	beq @87
	lfs f0, 0x1ac(r30)
	stfs f0, 0x110(r29)
	lfs f0, 0x110(r29)
	stfs f0, 0x10c(r29)
	lwz r3, 0x138(r29)
	bl hitGetAttr
	extrwi. r0, r3, 1, 22
	bne @87
	li r3, 0x72
	li r0, 0x1e
	stb r3, 0x39(r29)
	stw r0, 0x24(r29)
	b @87
	@144:
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @87
	mr r3, r29
	bl nokonoko_finish
	b @2
	@87:
	lbz r0, 0x39(r29)
	cmplwi r0, 0x64
	beq @2
	mr r3, r29
	bl partyMoveNoHosei
	@2:
	psq_l f31, 0x178(r1), 0, 0
	lwz r0, 0x184(r1)
	lfd f31, 0x170(r1)
	lwz r31, 0x16c(r1)
	lwz r30, 0x168(r1)
	lwz r29, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x180
	blr
}

asm void nokonoko_use_post(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x174(r3)
	cmplwi r3, 0x0
	beq @1
	bl itemNokoForceGet
	li r0, 0x0
	stw r0, 0x174(r31)
	@1:
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @2
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	@2:
	lwz r3, 0x0(r31)
	li r0, 0x0
	lfs f0, float_37_8041b550(r2)
	rlwinm r3, r3, 0, 24, 22
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 6, 4
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 8, 6
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 7, 5
	stw r3, 0x0(r31)
	lwz r3, 0x4(r31)
	rlwinm r3, r3, 0, 27, 25
	stw r3, 0x4(r31)
	lwz r3, 0x4(r31)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r31)
	stfs f0, 0xf0(r31)
	stw r0, 0x178(r31)
	stw r0, 0x17c(r31)
	stw r0, 0x180(r31)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void unk_800cd9a0(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPtr
	bl marioGetPartyId
	bl partyGetPtr
	mr. r31, r3
	bne @1
	li r0, 0x0
	b @2
	@1:
	lbz r0, 0x31(r31)
	cmpwi r0, 0x2
	bne @3
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	bne @4
	@3:
	li r0, 0x0
	b @2
	@4:
	lbz r3, 0x39(r31)
	li r0, 0x7
	cmplwi r3, 0x2
	bgt @5
	li r0, 0x1
	b @2
	@5:
	cmplwi r3, 0xa
	blt @6
	cmplwi r3, 0xd
	bgt @6
	li r0, 0x2
	b @2
	@6:
	cmplwi r3, 0x14
	blt @7
	cmplwi r3, 0x15
	bgt @7
	li r0, 0x3
	b @2
	@7:
	cmplwi r3, 0x32
	blt @8
	cmplwi r3, 0x47
	bgt @8
	li r0, 0x4
	b @2
	@8:
	cmplwi r3, 0x50
	blt @9
	cmplwi r3, 0x64
	bgt @9
	li r0, 0x5
	b @2
	@9:
	cmplwi r3, 0x6e
	blt @2
	cmplwi r3, 0x72
	bgt @2
	li r0, 0x6
	@2:
	cmpwi r0, 0x0
	beq @10
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @11
	bl marioGetPtr
	lwz r3, nokoSe(r13)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @12
	bl psndSFXOff
	li r0, -0x1
	stw r0, nokoSe(r13)
	@12:
	lwz r3, 0x0(r31)
	li r0, 0x0
	lfs f0, float_37_8041b550(r2)
	rlwinm r3, r3, 0, 24, 22
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 6, 4
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 8, 6
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 7, 5
	stw r3, 0x0(r31)
	lwz r3, 0x4(r31)
	rlwinm r3, r3, 0, 27, 25
	stw r3, 0x4(r31)
	lwz r3, 0x4(r31)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r31)
	stfs f0, 0xf0(r31)
	stw r0, 0x178(r31)
	stw r0, 0x17c(r31)
	stw r0, 0x180(r31)
	@11:
	lbz r0, 0x34(r31)
	cmplwi r0, 0x8
	beq @10
	cmplwi r0, 0xd
	beq @10
	mr r3, r31
	li r4, 0x2
	bl partyChgRunMode
	li r0, 0x0
	stb r0, 0x3b(r31)
	@10:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void nokonoko_move(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl marioGetPtr
	lwz r3, 0x8(r31)
	rlwinm. r0, r3, 0, 28, 28
	beq @1
	rlwinm r0, r3, 0, 29, 27
	mr r3, r31
	stw r0, 0x8(r31)
	li r4, 0x1
	bl partyWalkInit
	@1:
	mr r3, r31
	bl unk_800c92c4
	mr r3, r31
	bl partyRecordFootmark
	lbz r0, 0x3b(r31)
	cmpwi r0, 0x2
	beq @2
	bge @3
	cmpwi r0, 0x0
	beq @4
	bge @5
	b @6
	@3:
	cmpwi r0, 0x4
	beq @6
	bge @6
	b @7
	@4:
	mr r3, r31
	bl party_move_mode_stay
	b @6
	@5:
	mr r3, r31
	bl party_move_mode_walk
	b @6
	@2:
	mr r3, r31
	bl party_move_mode_behind_mario
	b @6
	@7:
	mr r3, r31
	bl party_move_mode_beside_mario
	@6:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void nokonoko_init(PartyEntry* party) {
	nofralloc
	li r0, 0x2
	li r4, 0x0
	stb r0, 0x33(r3)
	li r0, -0x1
	lfs f1, float_37_8041b550(r2)
	stb r4, 0x32(r3)
	lfs f0, float_24_8041b5e0(r2)
	stfs f1, 0xf0(r3)
	stfs f0, 0xf4(r3)
	stw r0, nokoSe(r13)
	blr
}

asm void nokonoko_bye(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r4, 0x8(r3)
	rlwinm. r0, r4, 0, 28, 28
	beq @1
	rlwinm r0, r4, 0, 29, 27
	stw r0, 0x8(r31)
	bl partyGoodbyeInit
	@1:
	mr r3, r31
	bl partyGoodbyeMain
	cmpwi r3, 0x0
	beq @2
	mr r3, r31
	li r4, 0xe
	bl partyChgRunMode
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL nokonoko_holdItem(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lbz r0, 0x31(r3)
	cmpwi r0, 0x2
	bne @3
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 23, 23
	bne @4
	@3:
	li r3, 0x0
	b @2
	@4:
	lwz r3, 0x174(r3)
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 nokonokoGetStatus(PartyEntry* party) {
	nofralloc
	cmplwi r3, 0x0
	bne @1
	li r3, 0x0
	blr
	@1:
	lbz r0, 0x31(r3)
	cmpwi r0, 0x2
	bne @2
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 23, 23
	bne @3
	@2:
	li r3, 0x0
	blr
	@3:
	lbz r0, 0x39(r3)
	li r3, 0x7
	cmplwi r0, 0x2
	bgt @4
	li r3, 0x1
	blr
	@4:
	cmplwi r0, 0xa
	blt @5
	cmplwi r0, 0xd
	bgt @5
	li r3, 0x2
	blr
	@5:
	cmplwi r0, 0x14
	blt @6
	cmplwi r0, 0x15
	bgt @6
	li r3, 0x3
	blr
	@6:
	cmplwi r0, 0x32
	blt @7
	cmplwi r0, 0x47
	bgt @7
	li r3, 0x4
	blr
	@7:
	cmplwi r0, 0x50
	blt @8
	cmplwi r0, 0x64
	bgt @8
	li r3, 0x5
	blr
	@8:
	cmplwi r0, 0x6e
	bltlr
	cmplwi r0, 0x72
	bgtlr
	li r3, 0x6
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_8031381C_data[1] = {0};
__declspec(section ".sdata2") const u32 gap_09_8041B5E4_sdata2[1] = {0};
