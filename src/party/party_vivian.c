#include "party/party_vivian.h"
#include "driver/animdrv.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mariost.h"
#include "party.h"
#include "system.h"
#include <string.h>

typedef struct VivianParty {
    u32 flags;               // 0x0
    u32 flags2;              // 0x4
    u32 field_8;             // 0x8
    u8 pad0C[0x31 - 0xC];    // 0xC
    s8 currentMemberId;      // 0x31
    u8 field_32;             // 0x32
    u8 field_33;             // 0x33
    u8 pad34[0x39 - 0x34];   // 0x34
    u8 useMotionId;          // 0x39
    u8 pad3A;                // 0x3A
    u8 field_3B;             // 0x3B
    u8 pad3C[0x4F - 0x3C];   // 0x3C
    s8 field_4F;             // 0x4F
    u8 pad50[0x58 - 0x50];   // 0x50
    Vec position;            // 0x58
    u8 pad64[0x7C - 0x64];   // 0x64
    Vec field_7C;            // 0x7C
    u8 pad88[0xB8 - 0x88];   // 0x88
    Vec shadow;              // 0xB8
    u8 padC4[0xF0 - 0xC4];   // 0xC4
    f32 field_F0;            // 0xF0
    f32 field_F4;            // 0xF4
    u8 padF8[0x174 - 0xF8];  // 0xF8
    f32 field_174;           // 0x174
    u8 pad178[0x184 - 0x178]; // 0x178
    s32 field_184;           // 0x184
} VivianParty;

typedef struct VivianTail {
    u8 pad : 7;
    u8 off : 1;
} VivianTail;

#define TAIL_OFF(p) (((VivianTail*)&(p)->field_4F)->off)

extern GlobalWork* gp;
extern void partyMoveFlyInit(VivianParty* party, s32 arg);
extern void partyFlyMain(VivianParty* party);
extern void partyPaperOff(VivianParty* party);
extern void partyChgRunMode(VivianParty* party, s32 mode);
extern char* partyChgPoseId(VivianParty* party, s32 index);

#pragma force_active on
s32 gap_08_80418A34_sbss;
#pragma force_active reset
s32 vivian_cancel_req;

void N_marioForceVivianAnime(void) {
    MarioWork* mario = marioGetPtr();

    marioPaperOff();
    marioChgPaper(NULL);
    marioPaperOn("p_bibi");
    marioChgPose("M_B_3");
    marioChgPaper("PM_B_1");
    mario->poseTime = 0x18;
    animPoseSetLocalTime(mario->paperAnimGroupId[marioAnimeId()], *(u16*)&mario->poseTime);
}

void mot_vivian(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        mario->flags &= ~0xF0000;
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
        mario->baseSpeed = 0.0f;
        *(s32*)((u8*)mario + 0x1E0) = 0;
        *(s32*)((u8*)mario + 0x1DC) = 0;
        *(s32*)((u8*)mario + 0x1EC) = 0;
        *(s32*)((u8*)mario + 0x1F0) = 0;
    }
}


void L_partyVivianTailStart(VivianParty* party);

void mot_vivian_post(void) {
    VivianParty* party = (VivianParty*)partyGetPtr(marioGetPartyId());
    MarioWork* mario = marioGetPtr();

    if (mario->currMotionId == 0x20 || mario->currMotionId == 0x1F) {
        mario->dispFlags &= ~0x1000;
        marioPaperOff();
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            mario->field_0xA4 = zero;
        }
        mario->flags &= ~0x400;
        if (party) {
            partyPaperOff(party);
            party->flags &= ~0x100;
            party->flags &= ~0x80000000;
            party->flags2 &= ~0x200000;
            party->field_174 = 10.0f;
            {
                Vec zero2 = {0.0f, 0.0f, 0.0f};
                party->field_7C = zero2;
            }
            partyChgRunMode(party, 2);
            party->field_3B = 0;
            partyChgPoseId(party, 1);
            L_partyVivianTailStart(party);
        }
    } else if (party && party->currentMemberId == 6 && (party->flags & 0x100)) {
        goto cancel;
    }
    return;
cancel:
    vivian_cancel_req = 1;
}

void vivian_init_801809C0(VivianParty* party) {
    party->field_33 = 6;
    party->field_32 = 1;
    party->field_F0 = 35.0f;
    party->field_F4 = 24.0f;
    party->field_174 = 10.0f;
    party->field_4F = 0;
    party->shadow = party->position;
    party->field_184 = 0;
    vivian_cancel_req = 0;
}

s32 vivianGetStatus(void) {
    VivianParty* party = (VivianParty*)partyGetPtr(marioGetPartyId());
    u8 st;

    if (party == NULL) {
        return 0;
    }
    if (party->currentMemberId != 6 || !(party->flags & 0x100)) {
        return 0;
    }
    st = party->useMotionId;
    if (st < 10) {
        return 1;
    }
    if (st == 10) {
        return 2;
    }
    if (st >= 20 && st <= 27) {
        return 3;
    }
    return 4;
}

void vivianUnhold(VivianParty* party) {
    if (party == NULL || party->currentMemberId != 6 || !(party->flags & 0x100)) {
        return;
    }
    if (party->useMotionId == 10) {
        party->useMotionId = 20;
    }
}

void L_partyVivianTailStop(VivianParty* party) {
    if (party->currentMemberId == 6) {
        party->field_4F |= 1;
    }
}

void L_partyVivianTailStart(VivianParty* party) {
    if (party->currentMemberId == 6) {
        party->field_4F &= ~1;
    }
}

BOOL N_vivianDisplayTailCheck(VivianParty* party) {
    if (party->currentMemberId != 6) {
        return FALSE;
    }
    if ((party->field_4F & 1)) {
        return FALSE;
    }
    if (party->flags2 & 0x800000) {
        return FALSE;
    }
    if (strcmp(gp->currentMapName, "bom_01") == 0 && -1000.0f == party->position.y) {
        return FALSE;
    }
    return TRUE;
}

void vivianShadow(VivianParty* party) {
    f32 dx, dy, dz;

    if (party && party->currentMemberId == 6) {
        dx = 0.1f * (party->position.x - party->shadow.x);
        dy = 0.1f * (party->position.y - party->shadow.y);
        dz = 0.1f * (party->position.z - party->shadow.z);
        party->shadow.x += dx;
        party->shadow.y += dy;
        party->shadow.z += dz;
        if (distABf(party->position.x, party->position.z, party->shadow.x, party->shadow.z) >= 22.0f) {
            party->shadow = party->position;
            movePos(&party->shadow.x, &party->shadow.z, 22.0f,
                    angleABf(party->position.x, party->position.z, party->shadow.x, party->shadow.z));
        }
    }
}

void vivian_move(VivianParty* party) {
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyMoveFlyInit(party, 1);
    }
    partyFlyMain(party);
    vivianShadow(party);
}

typedef struct VivianUseWork {
    u8 pad0[0x94];
    Vec target; // 0x94
} VivianUseWork;
#define VU(p) ((VivianUseWork*)(p))
#define PF(t, o) (*(t*)((u8*)party + (o)))
#define MF(t, o) (*(t*)((u8*)m + (o)))

extern void L_partyForceSlitOff(void);
extern void* marioSearchGround(f32* x, f32* y, f32* z, f32 a, f32 b);
extern s32 hitGetAttr(void* hit);
extern f32 toMovedirSimple(f32 angle);
extern f32 toMovedir(f32 angle);
extern void marioChkWallAround(Vec* pos, s32 arg, f32 a, f32 b, f32 c, f32 d);
extern void partyChgPose(VivianParty* party, const char* name);
extern void partyChgPaper(VivianParty* party, const char* name);
extern s32 psndSFXOn_3D(s32 id, Vec* pos);
extern void* effRippleEntry(s32 type, f32 x, f32 y, f32 z);
extern void effRippleSetCamId(void* eff, s32 cam);
extern void effRippleSetPosition(void* eff, f32 x, f32 y, f32 z);
extern void partyUpdateKeyData(VivianParty* party);
extern void marioAdjustMoveDir(void);
extern void marioChgSmallJumpMotion(void);
extern void marioChgMot(s32 mot);

#pragma opt_common_subs off
static inline void vivianFollow(VivianParty* party) {
    void* hit;
    u8 id;
    MarioWork* m = PF(MarioWork*, 0x160);
    f32 gx, gy, gz;
    f32 sx, sy, sz;
    f32 ofs;

    marioGetScreenPos(m->position, &sx, &sy, &sz);
    hit = marioSearchGround(&gx, &gy, &gz, 37.0f, -37.0f);
    if (hit && !(hitGetAttr(hit) & 0xA00)) {
        MF(void*, 0x1E4) = hit;
        MF(f32, 0x90) = gx;
        if (MF(f32, 0x178) < 0.0f) {
            gx += 0.2f;
        }
    }
    id = party->useMotionId;
    if (id >= 20 && id < 30) {
        PF(f32, 0x17C) += -0.4f;
        if (PF(f32, 0x17C) < -13.0f) {
            PF(f32, 0x17C) = -13.0f;
        }
        PF(Vec, 0x94) = m->position;
        movePos(&PF(f32, 0x94), &PF(f32, 0x9C), PF(f32, 0x17C), toMovedirSimple(MF(f32, 0x1A8)));
        movePos(&PF(f32, 0x94), &PF(f32, 0x9C), 0.0f, toMovedirSimple(MF(f32, 0x1A8)));
        if (0.0f == MF(f32, 0x1AC)) {
            ofs = -2.5f;
        } else {
            ofs = 2.5f;
        }
        movePos(&PF(f32, 0x94), &PF(f32, 0x9C), ofs, toMovedir(270.0f + MF(f32, 0x1A8)));
    } else {
        if (id >= 4) {
            PF(f32, 0x17C) += 0.4f;
            if (PF(f32, 0x17C) >= 0.0f) {
                PF(f32, 0x17C) = 0.0f;
            }
        }
        PF(Vec, 0x94) = m->position;
        movePos(&PF(f32, 0x94), &PF(f32, 0x9C), PF(f32, 0x17C), toMovedirSimple(MF(f32, 0x1A8)));
        if (0.0f == MF(f32, 0x1AC)) {
            ofs = -2.5f;
        } else {
            ofs = 2.5f;
        }
        movePos(&PF(f32, 0x94), &PF(f32, 0x9C), ofs, toMovedir(270.0f + MF(f32, 0x1A8)));
    }
    if (strcmp(gp->currentMapName, "eki_02") == 0) {
        marioChkWallAround(&m->position, 1, 0.0f, MF(f32, 0x1A0), MF(f32, 0x1BC), 0.5f);
    }
}

#pragma opt_common_subs off
void vivian_use(VivianParty* party) {
    f32 d;
    void* rip;
    Vec s;
    MarioWork* m;
    u32 fl = party->field_8;
    m = PF(MarioWork*, 0x160);
    if (fl & 8) {
        party->field_8 &= ~8;
        party->useMotionId = 0;
        party->field_174 = 10.0f;
        party->shadow = party->position;
        vivian_cancel_req = 0;
        L_partyForceSlitOff();
    }
    MF(f32, 0x180) = 0.0f;
    PF(f32, 0x104) = 0.0f;

    switch (party->useMotionId) {
    case 0:
        marioChgMot(0x1C);
        PF(f32, 0x17C) = -13.0f;
        vivianFollow(party);
        PF(f32, 0x100) = angleABf(party->position.x, party->position.z, PF(f32, 0x94), PF(f32, 0x9C));
        PF(f32, 0x10C) = MF(f32, 0x1A8);
        PF(f32, 0x110) = MF(f32, 0x1AC);
        PF(f32, 0x104) = 0.0f;
        PF(f32, 0x114) = 0.0f;
        party->useMotionId = 1;
        PF(s32, 0x24) = 6;
        partyChgPose(party, "PTR_A2_1");
    case 1:
        vivianFollow(party);
        party->position.x += (PF(f32, 0x94) - party->position.x) / PF(s32, 0x24);
        party->position.y += (PF(f32, 0x98) - party->position.y) / PF(s32, 0x24);
        party->position.z += (PF(f32, 0x9C) - party->position.z) / PF(s32, 0x24);
        party->shadow = party->position;
        if (--PF(s32, 0x24) > 0) {
            break;
        }
        party->flags2 |= 0x200000;
        PF(f32, 0x110) = MF(f32, 0x1AC);
        PF(f32, 0xFC) = toMovedirSimple(PF(f32, 0x110));
        party->shadow = party->position;
        MF(u32, 0x4) |= 0x1000;
        partyChgPose(party, "PTR_A2_3");
        partyPaperOn((PartyEntry*)party, "p_bibi");
        partyChgPaper(party, "PM_B_1");
        party->field_7C.y += 1.6f;
        MF(u32, 0x4) |= 0x1000;
        marioPaperOn("p_bibi");
        marioChgPose("M_B_3");
        marioChgPaper("PM_B_1");
        party->useMotionId = 4;
        PF(s32, 0x24) = 30;
        psndSFXOn_3D(0x936, &party->position);
    case 4:
        vivianFollow(party);
        if (30 - PF(s32, 0x24) <= 24) {
            party->field_7C.y += 0.4f;
            MF(f32, 0xA8) += 0.4f;
            if (party->field_7C.y >= 8.0f) {
                party->field_7C.y = 8.0f;
            }
            if (MF(f32, 0xA8) >= 8.0f) {
                MF(f32, 0xA8) = 8.0f;
            }
        }
        party->field_174 += 1.0f;
        if (party->field_174 >= 20.0f) {
            party->field_174 = 20.0f;
            MF(u32, 0x4) |= 0x1000;
        }
        if (--PF(s32, 0x24) > 0) {
            break;
        }
        rip = effRippleEntry(1, PF(MarioWork*, 0x160)->position.x, 1.5f + PF(MarioWork*, 0x160)->position.y, PF(MarioWork*, 0x160)->position.z);
        party->field_184 = (s32)rip;
        if (PF(s32, 0x164) != 4) {
            effRippleSetCamId(rip, PF(s32, 0x164));
        }
        psndSFXOn_3D(0x935, &party->position);
        L_partyVivianTailStop(party);
        party->useMotionId = 5;
    case 5:
        vivianFollow(party);
        party->field_174 -= 1.0f;
        if (party->field_174 <= 10.0f) {
            party->field_174 = 10.0f;
            party->useMotionId = 10;
            MF(u32, 0x0) |= 0x400;
        }
        break;
    case 10:
        vivianFollow(party);
        partyUpdateKeyData(party);
        if (vivian_cancel_req) {
            party->useMotionId = 20;
        }
        if (!(party->flags & 0x80000000) && (PF(u16, 0x152) & 0x600)) {
            party->useMotionId = 20;
        }
        break;
    }

    MF(f32, 0x8C) += MF(f32, 0x174);
    MF(f32, 0x94) += MF(f32, 0x17C);
    MF(f32, 0x90) += MF(f32, 0x178);
    if (party->useMotionId >= 2) {
        party->position = PF(Vec, 0x94);
        party->shadow = m->position;
    } else {
        party->shadow = party->position;
    }
    d = MF(f32, 0x90) - MF(f32, 0x114);
    if (d > 0.0f) {
        party->shadow.y += d;
    }
    s = party->shadow;
    if ((void*)party->field_184 == NULL) {
        party->field_184 = 0;
    } else if (*(u32*)party->field_184 == 0) {
        party->field_184 = 0;
    } else {
        effRippleSetPosition((void*)party->field_184, s.x, 1.5f + s.y, s.z);
    }

    switch (party->useMotionId) {
    case 20:
        PF(f32, 0x17C) = 0.0f;
        MF(u32, 0x0) &= ~0x400;
        psndSFXOn_3D(0x934, &party->position);
        party->useMotionId = 21;
    case 21:
        vivianFollow(party);
        party->field_174 += 1.0f;
        if (party->field_174 >= 20.0f) {
            party->field_174 = 20.0f;
            party->useMotionId = 22;
        }
        break;
    case 22:
        marioAdjustMoveDir();
        partyChgPose(party, "PTR_A2_4");
        PF(s16, 0x20) = 24;
        L_partyVivianTailStart(party);
        party->useMotionId = 23;
        break;
    case 23:
        vivianFollow(party);
        animPoseSetLocalTime(PF(s32, 0xC), 24.0f);
        PF(s16, 0x20) = 24;
        party->useMotionId = 24;
        PF(s32, 0x24) = 24;
        psndSFXOn_3D(0x937, &party->position);
    case 24:
        vivianFollow(party);
        animPoseSetLocalTime(PF(s32, 0xC), PF(s32, 0x24));
        party->field_7C.y -= 0.4f;
        if (party->field_7C.y <= 2.7f) {
            party->field_7C.y = 2.7f;
        }
        if (--PF(s32, 0x24) <= 0) {
            break;
        }
        if (PF(s32, 0x24) == 20) {
            marioChgPose("M_S_1");
            MF(s16, 0x28) = 24;
            PF(s16, 0x182) = 24;
            party->useMotionId = 25;
        }
        break;
    case 25:
        vivianFollow(party);
        animPoseSetLocalTime(PF(s32, 0xC), PF(s32, 0x24));
        animPoseSetLocalTime(m->paperAnimGroupId[marioAnimeId()], PF(s16, 0x182));
        MF(f32, 0xA8) -= 0.4f;
        if (MF(f32, 0xA8) <= 2.7f) {
            MF(f32, 0xA8) = 2.7f;
        }
        party->field_7C.y -= 0.4f;
        if (party->field_7C.y <= 2.7f) {
            party->field_7C.y = 2.7f;
        }
        PF(s16, 0x182)--;
        if (--PF(s32, 0x24) > 0) {
            break;
        }
        party->useMotionId = 26;
        PF(s32, 0x24) = 24;
    case 26:
        vivianFollow(party);
        animPoseSetLocalTime(PF(s32, 0xC), 0.0f);
        animPoseSetLocalTime(m->paperAnimGroupId[marioAnimeId()], PF(s16, 0x182));
        MF(f32, 0xA8) -= 0.4f;
        if (MF(f32, 0xA8) <= 2.7f) {
            MF(f32, 0xA8) = 2.7f;
        }
        party->field_7C.y -= 0.4f;
        if (party->field_7C.y <= 2.7f) {
            party->field_7C.y = 2.7f;
        }
        if (--PF(s16, 0x182) > 0) {
            PF(s16, 0x182) = 0;
        }
        if (--PF(s32, 0x24) > 0) {
            PF(s32, 0x24) = 0;
        }
        if (PF(s16, 0x182) == 0 && PF(s32, 0x24) == 0) {
            party->useMotionId = 27;
            marioPaperOff();
            MF(s32, 0x20) = 0;
            MF(u32, 0x4) &= ~0x1000;
            MF(void*, 0x1E8) = MF(void*, 0x1E4);
            MF(void*, 0x1E4) = NULL;
            {
                Vec zero = {0.0f, 0.0f, 0.0f};
                MF(Vec, 0xA4) = zero;
            }
            marioChgSmallJumpMotion();
            MF(f32, 0x180) = 0.0f;
        }
        break;
    case 27:
        animPoseSetLocalTime(PF(s32, 0xC), 0.0f);
        party->field_174 -= 1.0f;
        if (!(party->field_174 > 10.0f)) {
            party->field_174 = 10.0f;
            partyPaperOff(party);
            party->flags &= ~0x100;
            party->flags2 &= ~0x200000;
            party->field_174 = 10.0f;
            party->field_7C.y = 0.0f;
            partyChgRunMode(party, 2);
            party->field_3B = 0;
            partyChgPoseId(party, 1);
            party->flags &= ~0x80000000;
        }
        break;
    }
}
#pragma opt_common_subs reset

