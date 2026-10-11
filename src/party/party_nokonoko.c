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
#define PW(p, o) (*(u32*)((u8*)(p) + (o)))

extern s32 nokoSe;
double sin(double);
double cos(double);
#include "driver/hitdrv.h"

extern void itemNokoForceGet(ItemEntry* entry);

void lookupSafetyPosSub(Vec* pos, f32 height, f32 angle, Vec* out) {
    f32 rad;
    f32 x;
    f32 y;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 dist;
    f32 nx;
    f32 ny;
    f32 nz;
    MarioWork* player = marioGetPtr();
    rad = (3.1415927f * angle) / 180.0f;
    angle = player->wPlayerCollisionBox.x;
    x = angle * (f32)sin(rad) + pos->x;
    z = -angle * (f32)cos(rad) + pos->z;
    y = pos->y + height;
    dist = 0.1f + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, 0.0f, -1.0f, 0.0f) != NULL) {
        Vec v = {0.0f, 0.0f, 0.0f};
        v.x = x;
        v.y = y;
        v.z = z;
        *out = v;
    } else {
        *out = *pos;
    }
}

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

void nokonoko_bye(PartyEntry* party) {
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyGoodbyeInit(party);
    }
    if (partyGoodbyeMain(party)) {
        partyChgRunMode(party, 14);
    }
}

void nokonoko_init(PartyEntry* party) {
    party->field_32 [1] = 2;
    party->field_32 [0] = 0;
    party->field_F0 = 37.0f;
    party->width = 24.0f;
    nokoSe = -1;
}

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

void nokotaro_hold_cancel(PartyEntry* party) {
    party->useMotionId = 20;
}

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
    party->field_F0 = 37.0f;
    PW(party, 0x178) = 0;
    PW(party, 0x17c) = 0;
    PW(party, 0x180) = 0;
}

void nokonoko_finish(PartyEntry* party) {
    if (party != NULL && party->currentMemberId == 2 && (party->flags & 0x100)) {
        nokonoko_use_post(party);
        if (party->field_34 != 9) {
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
            party->field_F0 = 37.0f;
            PW(party, 0x178) = 0;
            PW(party, 0x17c) = 0;
            PW(party, 0x180) = 0;
            if (party->field_34 != 8 && party->field_34 != 0xd) {
                partyChgRunMode(party, 2);
                PB(party, 0x3b) = 0;
            }
        }
    }
}

