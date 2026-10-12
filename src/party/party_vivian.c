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
    } else if (party && party->currentMemberId == 6) {
        if (party->flags & 0x100) {
            vivian_cancel_req = 1;
        }
    }
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
    if (party == NULL) {
        return;
    }
    if (party->currentMemberId != 6) {
        return;
    }
    if (party->flags & 0x100) {
    } else {
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
