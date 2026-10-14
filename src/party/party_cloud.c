#define _MATH_H_
double fabs(double x);
double sin(double x);
double cos(double x);
#define fabs(x) __fabs(x)
#define fabsf(x) __fabsf(x)
#include "party/party_cloud.h"
#include "dolphin/types.h"
#include "musyx/musyx.h"
#include "party.h"
#include "mario/mario.h"
#include "mario/mario_sbr.h"
#include "mario/mario_party.h"
#include "mario/mario_cam.h"
#include "system.h"

Vec cloud_at;


#define CLD_F(p, off) (*(f32*)((u8*)(p) + (off)))
#define CLD_S(p, off) (*(s32*)((u8*)(p) + (off)))
#define CLD_B(p, off) (*(u8*)((u8*)(p) + (off)))
void partyMoveFlyInit(PartyEntry* party, s32 arg);
void partyFlyMain(PartyEntry* party);

#include "driver/hitdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include "pmario_sound.h"
#include "mario/mario_motion.h"
void N__cloud_use(PartyEntry* party);
void getHitBreatheout2(PartyEntry* party, f32 unk);
void partyChgRunMode(PartyEntry* party, s32 mode);
s32 partyChgPoseId(PartyEntry* party, s32 id);
void partyChgPose(PartyEntry* party, s32 pose);
void partyChgMot(PartyEntry* party, s32 mot);

#define CLD_P(p, off) (*(void**)((u8*)(p) + (off)))
#define CLD_H(p, off) (*(u16*)((u8*)(p) + (off)))
#define CLD_U(p, off) (*(u32*)((u8*)(p) + (off)))

static inline void cloudSweep(PartyEntry* party, f32 sign, s32 off) {
    u8* cl = CLD_P(party, 0x170);
    if (CLD_S(cl, off + 4) == 0) {
        CLD_F(cl, off) += 1.0f;
        cl = CLD_P(party, 0x170);
        if (CLD_F(cl, off) >= 20.0f) {
            CLD_F(cl, off) = 20.0f;
            CLD_S(CLD_P(party, 0x170), off + 4) = 1;
        }
    } else {
        CLD_F(cl, off) -= 1.0f;
        cl = CLD_P(party, 0x170);
        if (CLD_F(cl, off) <= -20.0f) {
            CLD_F(cl, off) = -20.0f;
            CLD_S(CLD_P(party, 0x170), off + 4) = 0;
        }
    }
}

void* effKumokumoN64Entry(s32 a, s32 b, f32 x, f32 y, f32 z, f32 w, f32 s, f32 t);
void partyChgMoveMode(PartyEntry* party, s32 mode);
void partyUpdateKeyData(PartyEntry* party);
void* memset(void*, int, unsigned long);



#define cloudCalcPos(party) {                                                          u8* m_ = CLD_P(party, 0x160);                                                         f32 dir_;                                                                                                                                                                   *(Vec*)&CLD_F(party, 0x94) = *(Vec*)&CLD_F(m_, 0x8C);                                 dir_ = CLD_F(m_, 0x1AC);                                                              movePos((f32*)((u32)party + 0x94), (f32*)((u32)party + 0x9C), 3.3f,                           toMovedir(dir_ + ((dir_ < 90.0f || dir_ >= 270.0f) ? -90.0f : 90.0f)));       CLD_F(party, 0x98) += 10.0f;                                                      }

void mot_cloud() {
    MarioWork* mario = marioGetPtr();
    
    if((mario->trigFlags & 0x1) != 0) {
        mario->trigFlags &= ~0x1;
        mario->flags &= ~(MARIO_FLAG_HAS_INPUT_JUMP|MARIO_FLAG_IS_STEPPING|MARIO_FLAG_IS_FALLING|MARIO_FLAG_IS_JUMPING);
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
    }
}

void cloudResetAt() {
    MarioWork* mario = marioGetPtr();
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);

    if(party != NULL && party->currentMemberId == PARTY_MEMBER_FLURRIE) {
        cloud_at.x = camGetPtr(CAMERA_3D)->cameraAt.x;
        cloud_at.y = camGetPtr(CAMERA_3D)->cameraAt.y;
        cloud_at.z = camGetPtr(CAMERA_3D)->cameraAt.z;

        marioCamZoomOffReq2(600);
    }

    mario->dispFlags &= ~(1 << 8); //kDisableMakeDispDir
    mario->dispFlags &= ~(1 << 2); //kForceFrontPose
    marioAdjustMoveDir();
    mario->unk150.x = 0.01f;
    mario->unk138 = 0.0f;
}

u8 cloudGetStatus() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    u8 status = 2;

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        status = 0;
        return status;
    }
    else if (party->useMotionId == 10 && party->useMotionId < 20) {
        status = 1;
    }

    return status;
}

f32 cloudGetBreathDir() {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathDir;

    if (party == NULL) {
        return 0.0f;
    }

    if ((party->flags & PARTY_FLAG_IS_BEING_USED) != 0 && (party->useMotionId < MARIO_MOTION_FALL)){
        breathDir = -1.0f;
    }
    else if (party->useStruct == NULL) {
        breathDir = 0.0f;
    }
    else {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDir = toMovedir(cloud->unk4);
    }
    
    return breathDir;
}

f32 cloudGetBreathPower(f32 param_1, Vec* param_2) {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathPower;
    f32 dist;
    f32 angle;
    f32 unk8;
    f32 val;

    breathPower = 0.0f;
    if (party == NULL)  {
        return breathPower;
    }

    val = 10.0f;
    if(
        party->currentMemberId == PARTY_MEMBER_FLURRIE 
        && (party->flags & PARTY_FLAG_IS_BEING_USED) != 0 
        && party->useMotionId >= MARIO_MOTION_FALL
        && ((fabs(party->position.y - param_2->y - 18.0f)) <= val)
    ) {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        unk8 = cloud->unk8;
        if (-((0.5f * param_1) - distABf(party->position.x, party->position.z, param_2->x, param_2->z)) <= unk8) {
            PartyCloud* cloud = (PartyCloud*)party->useStruct;
            dist = toMovedir(cloud->unk4);
            angle = angleABf(party->position.x, party->position.z, param_2->x, param_2->z);
            dist = revise360(angle - dist);
            
            if (dist <= 30.0f || dist >= 330.0f) {
                breathPower = cos((3.1415927f * dist) / 180.0f);
                val = 100.0f;
                breathPower = val * fabsf(breathPower);
            }
        }
    }

    return breathPower;
}

s32 cloudGetHitBreathout(s32 param_1) {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    s32 hitBreathout;

    if (party == NULL) {
        return 0;
    }

    if (
        party->currentMemberId != PARTY_MEMBER_FLURRIE 
        || (party->flags & PARTY_FLAG_IS_BEING_USED) == 0
        || party->useMotionId < MARIO_MOTION_FALL
    ){
            return 0;
    }

    hitBreathout = 0;
    if (param_1 == 0) {
        hitBreathout = ((PartyCloud*)party->useStruct)->unk20;
    }
    else if (param_1 == 1) { 
        hitBreathout = ((PartyCloud*)party->useStruct)->unk24;
    }
    else if (param_1 == 2) {
        hitBreathout = ((PartyCloud*)party->useStruct)->unk28;
    }
    else if (param_1 == 3) { 
        hitBreathout = ((PartyCloud*)party->useStruct)->unk2C;
    }
    
    return hitBreathout;
}

f32 cloudGetBreathDist() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    f32 breathDist;

    if (party == NULL) {
        breathDist = 0.0f;
        return breathDist;
    }

    if ((party->currentMemberId != PARTY_MEMBER_FLURRIE || (party->flags & PARTY_FLAG_IS_BEING_USED) == 0) || party->useMotionId < MARIO_MOTION_FALL) {
        breathDist = 0.0f;
    }
    else {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDist = cloud->unk8;
    }

    return breathDist;
}

void unk_801820d0(PartyEntry* party) {
    CLD_F(party, 0x17C) = 0.0f;
    CLD_F(party, 0x180) = 4.25f;
}

void unk_8018206c(PartyEntry* party) {
    f32 a;
    CLD_F(party, 0x17C) = revise360(CLD_F(party, 0x17C) - CLD_F(party, 0x180));
    a = sin((3.1415927f * CLD_F(party, 0x17C)) / 180.0f);
    CLD_F(party, 0x80) = 3.0f + 3.0f * a;
}

void cloud_move(PartyEntry* party) {
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyMoveFlyInit(party, 1);
        unk_801820d0(party);
    }
    partyFlyMain(party);
    unk_8018206c(party);
    if (CLD_B(party, 0x3B) != 2) {
        party->field_8 &= ~0x40000;
    }
}

void cloud_init(PartyEntry* party) {
    CLD_B(party, 0x33) = 5;
    CLD_B(party, 0x32) = 1;
    party->field_F0 = 38.0f;
    party->width = 24.0f;
    CLD_S(party, 0x174) = 0;
    CLD_S(party, 0x178) = 0;
    CLD_S(party, 0x17C) = 0;
    CLD_S(party, 0x180) = 0;
    party->useStruct = NULL;
    CLD_S(party, 0x178) = 0;
}

void cloud_use(PartyEntry* party) {
    u8* mario = CLD_P(party, 0x160);
    u16 mot;
    s32 flag;
    f32 dir;
    u8* m;

    N__cloud_use(party);
    mot = CLD_H(mario, 0x2E);
    if (mot == 0x1B || mot <= 1 || mot == 2) {
        return;
    }
    CLD_U(party, 0) &= ~0x100;
    if (CLD_P(party, 0x170) != NULL && CLD_U(CLD_P(party, 0x170), 0x34) != 0xFFFFFFFF) {
        psndSFXOff(CLD_S(CLD_P(party, 0x170), 0x34));
        CLD_S(CLD_P(party, 0x170), 0x34) = -1;
    }
    if (CLD_P(party, 0x178) != NULL) {
        effSoftDelete(CLD_P(party, 0x178));
        CLD_P(party, 0x178) = NULL;
    }
    cloudCalcPos(party);
    party->position = *(Vec*)&CLD_F(party, 0x94);
    CLD_U(party, 4) |= 0x10;
    CLD_U(party, 0) &= ~0x80000000;
    if (CLD_P(party, 0x170) != NULL) {
        __memFree(HEAP_DEFAULT, CLD_P(party, 0x170));
        CLD_P(party, 0x170) = NULL;
    }
    mot = CLD_H(mario, 0x2E);
    if (mot == 0x1F || mot == 0x20) {
        partyChgRunMode(party, 13);
    } else {
        partyChgPose(party, partyChgPoseId(party, 1));
        partyChgRunMode(party, 2);
        partyChgMot(party, 0);
    }
}

void N__cloud_use(PartyEntry* party) {
    u8* mario = CLD_P(party, 0x160);
    f32 ofsX, ofsZ;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 yc, ys, dirCos, dirSin;
    HitEntry* hit;
    s32 flag;
    f32 dir;
    u8* cl;

    if (CLD_U(party, 8) & 8) {
        CLD_U(party, 8) &= ~8;
        CLD_S(party, 0x17C) = 0;
        CLD_S(party, 0x180) = 0;
        marioAdjustMoveDir();
        CLD_B(party, 0x39) = 0;
        CLD_P(party, 0x170) = __memAlloc(HEAP_DEFAULT, 0x48);
        memset(CLD_P(party, 0x170), 0, 0x48);
        CLD_F(CLD_P(party, 0x170), 0) = 100.0f;
        CLD_F(CLD_P(party, 0x170), 0xC) = 120.0f;
        CLD_F(CLD_P(party, 0x170), 0x10) = 0.0f;
        CLD_S(CLD_P(party, 0x170), 0x14) = 0;
        CLD_F(CLD_P(party, 0x170), 0x18) = 0.0f;
        CLD_S(CLD_P(party, 0x170), 0x1C) = 1;
        CLD_P(party, 0x178) = NULL;
        if (CLD_P(party, 0x170) != NULL) {
            CLD_S(CLD_P(party, 0x170), 0x34) = -1;
        }
        if (CLD_U(party, 0) & 0x80000000) {
            CLD_S(CLD_P(party, 0x170), 0x30) = sysMsec2Frame(CLD_S(party, 0x16C));
        }
    }

    switch (CLD_B(party, 0x39)) {
    case 0:
        CLD_U(mario, 4) |= 0x100;
        CLD_S(party, 0x24) = 4;
        CLD_B(party, 0x39) = 1;
    case 1:
        cloudCalcPos(party);
        CLD_F(party, 0x10C) = CLD_F(mario, 0x1A8);
        CLD_F(party, 0x110) = CLD_F(mario, 0x1AC);
        CLD_F(party, 0x58) += (CLD_F(party, 0x94) - CLD_F(party, 0x58)) / (f32)CLD_S(party, 0x24);
        CLD_F(party, 0x5C) += (CLD_F(party, 0x98) - CLD_F(party, 0x5C)) / (f32)CLD_S(party, 0x24);
        CLD_F(party, 0x60) += (CLD_F(party, 0x9C) - CLD_F(party, 0x60)) / (f32)CLD_S(party, 0x24);
        if (--CLD_S(party, 0x24) > 0) {
            break;
        }
        CLD_B(party, 0x39) = 10;
    case 10:
        cloudCalcPos(party);
        party->position = *(Vec*)&CLD_F(party, 0x94);
        if (CLD_P(party, 0x178) == NULL) {
            CLD_P(party, 0x178) = effKumokumoN64Entry(0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -2.0f, 0.0f);
            CLD_P(CLD_P(CLD_P(party, 0x178), 0xC), 0x60) = CLD_P(party, 0x164);
            CLD_S(CLD_P(CLD_P(party, 0x178), 0xC), 0x18) = 0x4C;
            CLD_S(CLD_P(CLD_P(party, 0x178), 0xC), 0x1C) = 0xA7;
            CLD_S(CLD_P(CLD_P(party, 0x178), 0xC), 0x20) = 0xCA;
            CLD_S(CLD_P(CLD_P(party, 0x178), 0xC), 0x28) = 0x7D;
            CLD_S(CLD_P(CLD_P(party, 0x178), 0xC), 0x2C) = 0x1B;
            CLD_S(CLD_P(CLD_P(party, 0x178), 0xC), 0x30) = 0xF5;
        }
        marioChgMot(0x1B);
        marioChgPose("M_A_2A");
        partyChgPose(party, (s32)"PWD_A_5");
        CLD_S(party, 0x24) = 16;
        CLD_B(party, 0x39) = 11;
        CLD_U(mario, 4) |= 4;
        CLD_U(mario, 4) |= 0x100;
        CLD_U(party, 4) |= 0x10;
        CLD_F(CLD_P(party, 0x170), 8) = 0.0f;
        CLD_F(CLD_P(party, 0x170), 4) = CLD_F(mario, 0x1A8);
        if (!(CLD_U(party, 0) & 0x80000000)) {
            CLD_F(mario, 0x150) = 0.03f;
            CLD_F(mario, 0x138) = 70.0f * (revise360(270.0f - CLD_F(mario, 0x1AC)) <= 180.0f ? -1.0f : 1.0f);
        }
        if (CLD_P(party, 0x170) != NULL && CLD_U(CLD_P(party, 0x170), 0x34) == 0xFFFFFFFF) {
            CLD_S(CLD_P(party, 0x170), 0x34) =
                psndSFXOn_3D((const char*)0x930, (Vec*)((u8*)CLD_P(party, 0x160) + 0x8C));
        }
    case 11:
        cloudCalcPos(party);
        party->position = *(Vec*)&CLD_F(party, 0x94);
        if (--CLD_S(party, 0x24) > 0) {
            break;
        }
        partyChgPose(party, (s32)"PWD_A_6");
        marioChgPose("M_A_2B");
        CLD_B(party, 0x39) = 12;
    case 12:
        cloudCalcPos(party);
        party->position = *(Vec*)&CLD_F(party, 0x94);
        partyUpdateKeyData(party);
        CLD_F(mario, 0x1A8) = CLD_F(CLD_P(party, 0x170), 4);
        CLD_F(mario, 0x1AC) = CLD_F(CLD_P(party, 0x170), 4);
        CLD_F(party, 0x10C) = CLD_F(CLD_P(party, 0x170), 4);
        CLD_F(party, 0x110) = CLD_F(CLD_P(party, 0x170), 4);
        ofsX = CLD_F(mario, 0x8C);
        ofsZ = CLD_F(mario, 0x94);
        flag = 0;
        dir = CLD_F(mario, 0x1A8);
        if (dir < 90.0f || dir >= 270.0f) {
            flag = 1;
        }
        movePos(&ofsX, &ofsZ, 3.3f, toMovedir(dir + (flag ? -90.0f : 90.0f)));
        CLD_F(party, 0x58) = ofsX;
        CLD_F(party, 0x60) = ofsZ;
        CLD_F(party, 0x5C) = 10.0f + CLD_F(mario, 0x90);
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            *(Vec*)&CLD_F(party, 0x7C) = zero;
        }
        CLD_F(CLD_P(party, 0x170), 8) += 2.0f;
        cl = CLD_P(party, 0x170);
        mario = CLD_P(party, 0x160);
        if (CLD_F(cl, 8) >= CLD_F(cl, 0xC)) {
            CLD_F(cl, 8) = CLD_F(cl, 0xC);
        }
        sincosf(&dirSin, &dirCos, toMovedir(CLD_F(CLD_P(party, 0x170), 4)));
        sincosf(&ys, &yc, -45.0f);
        dist = CLD_F(CLD_P(party, 0x170), 8);
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                             CLD_F(party, 0x58), 18.0f + CLD_F(mario, 0x90), CLD_F(party, 0x60),
                             dirSin, ys, dirCos);
        if (hit != NULL && (hitGetAttr(hit) & 4)) {
            hit = NULL;
        }
        CLD_P(CLD_P(party, 0x170), 0x24) = hit;
        getHitBreatheout2(party, 0.0f);
        if (++*(s16*)((u8*)CLD_P(party, 0x170) + 0x38) > 2) {
            *(s16*)((u8*)CLD_P(party, 0x170) + 0x38) = 0;
        }
        if (!(CLD_U(party, 0) & 0x80000000)) {
            if (CLD_H(party, 0x150) & 0x400) {
                if (marioKeyOffChk() == 0) {
                    break;
                }
            }
        } else if (--CLD_S(CLD_P(party, 0x170), 0x30) > 0) {
            break;
        }
        CLD_P(CLD_P(party, 0x170), 0x20) = NULL;
        CLD_P(CLD_P(party, 0x170), 0x24) = NULL;
        CLD_P(CLD_P(party, 0x170), 0x28) = NULL;
        CLD_P(CLD_P(party, 0x170), 0x2C) = NULL;
        CLD_S(party, 0x24) = sysMsec2Frame(200);
        CLD_B(party, 0x39) = 13;
        if (CLD_U(party, 0) & 0x80000000) {
            CLD_B(party, 0x39) = 20;
        }
        if (CLD_P(party, 0x170) != NULL && CLD_U(CLD_P(party, 0x170), 0x34) != 0xFFFFFFFF) {
            psndSFXOff(CLD_S(CLD_P(party, 0x170), 0x34));
            CLD_S(CLD_P(party, 0x170), 0x34) = -1;
        }
        break;
    case 13:
        cloudCalcPos(party);
        party->position = *(Vec*)&CLD_F(party, 0x94);
        partyUpdateKeyData(party);
        if (CLD_H(party, 0x152) & 0x400) {
            CLD_B(party, 0x39) = 10;
        }
        if (--CLD_S(party, 0x24) <= 0) {
            CLD_B(party, 0x39) = 20;
            break;
        }
        if (*(s8*)((u8*)party + 0x158) == 0 && *(s8*)((u8*)party + 0x159) == 0) {
            break;
        }
        CLD_B(party, 0x39) = 20;
    case 20:
        CLD_U(party, 0) &= ~0x100;
        if (CLD_P(party, 0x170) != NULL && CLD_U(CLD_P(party, 0x170), 0x34) != 0xFFFFFFFF) {
            psndSFXOff(CLD_S(CLD_P(party, 0x170), 0x34));
            CLD_S(CLD_P(party, 0x170), 0x34) = -1;
        }
        if (CLD_P(party, 0x178) != NULL) {
            effSoftDelete(CLD_P(party, 0x178));
            CLD_P(party, 0x178) = NULL;
        }
        cloudCalcPos(party);
        party->position = *(Vec*)&CLD_F(party, 0x94);
        CLD_U(party, 4) &= ~0x10;
        if (CLD_H(mario, 0x2E) == 0x1B) {
            CLD_U(mario, 4) &= ~0x100;
            CLD_U(mario, 4) &= ~4;
            marioAdjustMoveDir();
            CLD_U(party, 8) |= 0x40000;
            CLD_U(mario, 4) &= ~0x100;
            marioChgMot(0);
        }
        CLD_U(party, 4) |= 0x10;
        partyChgRunMode(party, 2);
        CLD_B(party, 0x3D) = 0;
        partyChgMoveMode(party, 2);
        partyChgMot(party, 1);
        if (!(CLD_U(party, 0) & 0x80000000)) {
            CLD_F(mario, 0x150) = 0.01f;
            CLD_F(mario, 0x138) = 0.0f;
        }
        CLD_U(party, 0) &= ~0x80000000;
        if (CLD_P(party, 0x170) != NULL) {
            __memFree(HEAP_DEFAULT, CLD_P(party, 0x170));
            CLD_P(party, 0x170) = NULL;
        }
        break;
    }
}

void cloud_exit(PartyEntry* party) {
    u8* mario = CLD_P(party, 0x160);

    if (CLD_P(party, 0x170) != NULL && CLD_U(CLD_P(party, 0x170), 0x34) != 0xFFFFFFFF) {
        psndSFXOff(CLD_S(CLD_P(party, 0x170), 0x34));
        CLD_S(CLD_P(party, 0x170), 0x34) = -1;
    }
    if (CLD_P(party, 0x178) != NULL) {
        effSoftDelete(CLD_P(party, 0x178));
        CLD_P(party, 0x178) = NULL;
    }
    if (CLD_P(party, 0x170) != NULL) {
        __memFree(HEAP_DEFAULT, CLD_P(party, 0x170));
        CLD_P(party, 0x170) = NULL;
    }
    CLD_U(mario, 4) &= ~0x100;
    CLD_U(mario, 4) &= ~4;
    marioAdjustMoveDir();
    marioChgMot(0);
    CLD_F(mario, 0x150) = 0.01f;
    CLD_F(mario, 0x138) = 0.0f;
}

void getHitBreatheout2(PartyEntry* party, f32 unk) {
    f32 dirSin, dirCos, ys, yc;
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 ofsZ, ofsX;
    f32 dir, sign, height;
    s16 kind;
    HitEntry* hit;
    u8* cl = CLD_P(party, 0x170);
    u8* mario = CLD_P(party, 0x160);

    kind = *(s16*)(cl + 0x38);

    if (kind == 0) {
        height = 8.0f;
    } else if (kind == 1) {
        height = 20.0f;
    } else if (kind == 2) {
        height = 40.0f;
    }
    if (CLD_F(cl, 8) >= CLD_F(cl, 0xC)) {
        CLD_F(cl, 8) = CLD_F(cl, 0xC);
    }
    sincosf(&ys, &yc, unk);
    dir = toMovedir(CLD_F(CLD_P(party, 0x170), 4));
    sincosf(&dirSin, &dirCos, dir);
    dist = CLD_F(CLD_P(party, 0x170), 8);
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         CLD_F(party, 0x58), CLD_F(mario, 0x90) + height, CLD_F(party, 0x60),
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CLD_P(CLD_P(party, 0x170), 0x20) = hit;
    ofsX = 0.0f;
    ofsZ = 0.0f;
    if (CLD_P(party, 0x178) != NULL) {
        movePos(&ofsX, &ofsZ, 24.0f, dir);
        CLD_F(CLD_P(CLD_P(party, 0x178), 0xC), 4) = CLD_F(party, 0x58) + ofsX;
        CLD_F(CLD_P(CLD_P(party, 0x178), 0xC), 8) = 18.0f + CLD_F(party, 0x5C);
        CLD_F(CLD_P(CLD_P(party, 0x178), 0xC), 0xC) = CLD_F(party, 0x60) + ofsZ;
        cl = CLD_P(party, 0x170);
        CLD_F(CLD_P(CLD_P(party, 0x178), 0xC), 0x5C) = 0.6f * (CLD_F(cl, 8) / CLD_F(cl, 0xC));
        cl = CLD_P(party, 0x170);
        if (CLD_F(cl, 4) >= 90.0f && CLD_F(cl, 4) <= 270.0f) {
            CLD_F(CLD_P(CLD_P(party, 0x178), 0xC), 0x58) = -25.0f;
        } else {
            CLD_F(CLD_P(CLD_P(party, 0x178), 0xC), 0x58) = 205.0f;
        }
    }
    cl = CLD_P(party, 0x170);
    if (CLD_F(cl, 4) >= 90.0f && CLD_F(cl, 4) <= 270.0f) {
        sign = 1.0f;
    } else {
        sign = -1.0f;
    }

    cloudSweep(party, sign, 0x10);
    cl = CLD_P(party, 0x170);
    sincosf(&dirSin, &dirCos, toMovedir(CLD_F(cl, 0x10) * sign + CLD_F(cl, 4)));
    dist = CLD_F(CLD_P(party, 0x170), 8);
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         CLD_F(party, 0x58), CLD_F(mario, 0x90) + height, CLD_F(party, 0x60),
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CLD_P(CLD_P(party, 0x170), 0x28) = hit;

    cloudSweep(party, sign, 0x18);
    cl = CLD_P(party, 0x170);
    sincosf(&dirSin, &dirCos, toMovedir(CLD_F(cl, 0x18) * sign + CLD_F(cl, 4)));
    dist = CLD_F(CLD_P(party, 0x170), 8);
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         CLD_F(party, 0x58), CLD_F(mario, 0x90) + height, CLD_F(party, 0x60),
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CLD_P(CLD_P(party, 0x170), 0x2C) = hit;
}

void cloudGetAt(Vec* position) {
    MarioWork* mario = marioGetPtr();
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        return;
    }

    if ((mario->dispFlags & (1 << 20)) == 0) {
        CameraEntry* camera = camGetPtr(CAMERA_3D);

        if(camera->stateA == 0) {
            cloud_at = *position;
        }
        else {
            *position = cloud_at;
        }
    }
}
