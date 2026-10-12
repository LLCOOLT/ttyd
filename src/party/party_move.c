#include "party.h"
#include "driver/camdrv.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_sbr.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <string.h>

#define PF(p, off) (*(f32*)((u8*)(p) + (off)))
#define PU8(p, off) (*(u8*)((u8*)(p) + (off)))
#define PS16(p, off) (*(s16*)((u8*)(p) + (off)))
#define PS8(p, off) (*(s8*)((u8*)(p) + (off)))
#define PU32(p, off) (*(u32*)((u8*)(p) + (off)))
#define PPTR(p, off) (*(void**)((u8*)(p) + (off)))

typedef struct Footmark {
    u8 flag;    // 0x0
    u8 pad[3];  // 0x1
    Vec pos;    // 0x4
} Footmark;

extern s32 nokonokoGetStatus(PartyEntry* party);
extern BOOL chuchu_searchObject(void);
extern char* partyChgPoseId(PartyEntry* party, s32 index);
extern BOOL marioChkDeepSleep(void);
extern HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
extern void* mobjHitObjPtrToPtr(HitEntry* hit);

s32 partyMoveMain(PartyEntry* party, s32 hosei);
f32 unk_800c92c4(PartyEntry* party, f32 spd);
extern s32 N_marioGetMovementSpeed(void);
extern void party_set_behind_dir(PartyEntry* party);
extern void party_motion_beside_mario(PartyEntry* party);
extern void party_motion_behind_mario(PartyEntry* party);
extern void party_motion_behind_mario_fly(PartyEntry* party);
extern void party_motion_jump2(PartyEntry* party);
extern void party_motion_fall(PartyEntry* party);
extern void party_motion_upstairs(PartyEntry* party);
extern void party_motion_damage(PartyEntry* party);
extern void party_motion_stay(PartyEntry* party);
extern void party_motion_homing_walk(PartyEntry* party);
extern void party_motion_homing_fly(PartyEntry* party);
extern void party_motion_jump(PartyEntry* party);
extern void marioSetSplash(s32 type, Vec* pos);
extern void partyChgRunMode(PartyEntry* party, s32 mode);
extern void unk_8018206c(PartyEntry* party);
extern void unk_801820d0(PartyEntry* party);
extern void unk_8014bbc8(PartyEntry* party);
extern void vivianShadow(PartyEntry* party);
extern HitEntry* marioChkWallAround(Vec* pos, s32 a, f32 spd, f32 dir, f32 w, f32 h);
extern HitEntry* partySearchHead(PartyEntry* party, Vec* pos, f32* h, f32 a);
extern f32 toMovedirSimple(f32 dir);
extern HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
double sin(double);
double cos(double);

static inline void partyModeTail(PartyEntry* party) {
    Vec pos;

    party->field_FC = party->field_100;
    if (party->field_8 & 0x1000000) {
        party->field_8 &= ~0x1000000;
        pos = party->position;
        marioSetSplash(0, &pos);
        PS8(party, 0x4C) = 20;
    }
    if (--PS8(party, 0x4C) < 0) {
        PS8(party, 0x4C) = 0;
    }
    if (party->field_34 != 13) {
        if (party->field_138 && (hitGetAttr(party->field_138) & 0x800)) {
            partyChgRunMode(party, 13);
        } else if (PPTR(party, 0x12C) && (hitGetAttr(PPTR(party, 0x12C)) & 0x800)) {
            partyChgRunMode(party, 13);
        } else if (PPTR(party, 0x140) && (hitGetAttr(PPTR(party, 0x140)) & 0x800)) {
            partyChgRunMode(party, 13);
        }
    }
}
extern HitEntry* partySearchGround(PartyEntry* party, f32 a, f32 b);
void partyGetMoveDirSpd(PartyEntry* party, f32* dir, f32* spd);

Footmark footmarkBuf[2][80];
s32 readId[2];
s32 writeId[2];

static const char* objNames[] = {
    "MOBJ_TreasureBox",
    "MOBJ_BigTreasureBox",
    "MOBJ_GrayTreasureBox",
    "MOBJ_BlackTreasureBox",
    "MOBJ_GoldenTreasureBox",
    "MOBJ_BlueJumpStand",
    "MOBJ_BlueJumpStand2",
    "MOBJ_RedJumpStand",
    "MOBJ_RedJumpStand2",
    "MOBJ_MapJumpStand",
    "MOBJ_SaveBlock",
    "MOBJ_RecoveryBlock",
    "MOBJ_CoinTakenRecoveryBlock",
    "MOBJ_eki_06_su1",
    "MOBJ_eki_06_su2",
    "MOBJ_eki_06_su3",
    "MOBJ_RedSwitch",
    "MOBJ_BlueSwitch",
    "MOBJ_WhiteSwitch",
    "MOBJ_BlackSwitch",
    "MOBJ_green_FlowBlockSwitch",
    "MOBJ_purple_FlowBlockSwitch",
    "MOBJ_orange_FlowBlockSwitch",
    "MOBJ_RedTimerSwitch",
    "MOBJ_BlueTimerSwitch",
    NULL,
};

Footmark* partyGetFootmarkPtr(s32 id) {
    return &footmarkBuf[id][readId[id]];
}

s32 partyGetFootmarkReadId(s32 id) {
    return readId[id];
}

s32 partyGetFootmarkWriteId(s32 id) {
    return writeId[id];
}

s32 partyGetFootmarkId(PartyEntry* party) {
    return (party->flags >> 2) & 1;
}

static inline void getTargetPos(s32 id, Vec* pos) {
    MarioWork* mario = marioGetPtr();
    BOOL far = FALSE;
    MarioWork* mario2 = marioGetPtr();
    PartyEntry* other = anotherPartyGetPtr(id != 0);

    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario2->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (far) {
        other = NULL;
    }
    if (other) {
        pos->x = other->position.x;
        pos->y = other->position.y;
        pos->z = other->position.z;
    } else {
        pos->x = mario->position.x;
        pos->y = mario->position.y;
        pos->z = mario->position.z;
    }
}

void L_getTargetPos(s32 id, Vec* pos) {
    MarioWork* mario2;
    MarioWork* mario;
    PartyEntry* other;
    BOOL far;

    mario = marioGetPtr();
    far = FALSE;
    mario2 = marioGetPtr();
    other = anotherPartyGetPtr(id != 0);

    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario2->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (far) {
        other = NULL;
    }
    if (other) {
        pos->x = other->position.x;
        pos->y = other->position.y;
        pos->z = other->position.z;
    } else {
        pos->x = mario->position.x;
        pos->y = mario->position.y;
        pos->z = mario->position.z;
    }
}

f32 partyGetTargetDir(s32 id, f32 x, f32 z) {
    MarioWork* mario = marioGetPtr();
    BOOL far = FALSE;
    PartyEntry* other = anotherPartyGetPtr(id != 0);
    Vec pos;

    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (other && !far) {
        getTargetPos(id, &pos);
        return angleABf(x, z, pos.x, pos.z);
    }
    return angleABf(x, z, mario->position.x, mario->position.z);
}

f32 partyGetTargetDist(s32 id, f32 x, f32 z) {
    MarioWork* mario = marioGetPtr();
    BOOL far = FALSE;
    PartyEntry* other = anotherPartyGetPtr(id != 0);
    Vec pos;

    if (id == 0) {
        return distABf(x, z, mario->position.x, mario->position.z);
    }
    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (other && !far) {
        getTargetPos(id, &pos);
        return distABf(x, z, pos.x, pos.z);
    }
    return distABf(x, z, mario->position.x, mario->position.z);
}

f32 partyGetTargetDist3D(s32 id, Vec* p) {
    MarioWork* mario = marioGetPtr();
    BOOL far = FALSE;
    PartyEntry* other = anotherPartyGetPtr(id != 0);
    Vec pos;

    if (id == 0) {
        return PSVECDistance(&marioGetPtr()->position, p);
    }
    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (other && !far) {
        getTargetPos(id, &pos);
        return PSVECDistance(&pos, p);
    }
    return PSVECDistance(&marioGetPtr()->position, p);
}

f32 unk_800c9f48(s32 id, f32 y) {
    MarioWork* mario = marioGetPtr();
    BOOL far = FALSE;
    PartyEntry* other = anotherPartyGetPtr(id != 0);
    Vec pos;

    if (id == 0) {
        return __fabsf(mario->position.y - y);
    }
    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (other && !far) {
        getTargetPos(id, &pos);
        return __fabsf(pos.y - y);
    }
    return __fabsf(mario->position.y - y);
}

f32 partyGetTargetDistY(s32 id) {
    MarioWork* mario = marioGetPtr();
    BOOL far;
    PartyEntry* other;

    if (id == 0) {
        if (mario->baseSpeed > 0.0f) {
            return mario->baseSpeed;
        }
        return mario->mBaseDashSpeed;
    }
    far = FALSE;
    other = anotherPartyGetPtr(id != 0);
    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (other && !far) {
        return other->field_104;
    }
    mario = marioGetPtr();
    if (mario->baseSpeed > 0.0f) {
        return mario->baseSpeed;
    }
    return mario->mBaseDashSpeed;
}

f32 partyGetTargetMovespd2(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    BOOL far;
    PartyEntry* other;

    if (!(party->flags & 0x8)) {
        if (mario->baseSpeed > 0.0f) {
            return mario->baseSpeed;
        }
        return mario->mBaseDashSpeed;
    }
    if (party->field_8 & 0x20000) {
        if (mario->baseSpeed > 0.0f) {
            return mario->baseSpeed;
        }
        return mario->mBaseDashSpeed;
    }
    far = FALSE;
    other = partyGetPtr(marioGetPartyId());
    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            far = TRUE;
        }
    }
    if (other && !far) {
        return other->field_104;
    }
    if (mario->baseSpeed > 0.0f) {
        return mario->baseSpeed;
    }
    return mario->mBaseDashSpeed;
}

void partyNextReadId(s32 id) {
    if (readId[id] != writeId[id]) {
        readId[id]++;
        if (readId[id] >= 80) {
            readId[id] = 0;
        }
    }
}

void partyGetReadId(s32 id, f32* x, f32* y, f32* z) {
    Footmark* fm = &footmarkBuf[id][readId[id]];
    *x = fm->pos.x;
    *y = fm->pos.y;
    *z = fm->pos.z;
}

void partyGetReadId2(s32 id, Vec* pos) {
    Footmark* fm = &footmarkBuf[id][readId[id]];
    pos->x = fm->pos.x;
    pos->y = fm->pos.y;
    pos->z = fm->pos.z;
}

void partyClearFootmark(void) {
    Vec pos = marioGetPtr()->position;
    u32 i;

    for (i = 0; i < 80; i++) {
        footmarkBuf[0][i].pos = pos;
        footmarkBuf[0][i].flag = 0;
    }
    writeId[0] = 0;
    readId[0] = 0;
}

void partyClearFootmark2(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* other = partyGetPtr(marioGetPartyId());
    Vec pos;
    u32 i;
    Footmark* fm;

    if (other) {
        if (nokonokoGetStatus(other) == 3 ||
            PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            pos = mario->position;
        } else {
            pos = other->position;
        }
    } else {
        pos = mario->position;
    }
    fm = footmarkBuf[1];
    for (i = 0; i < 80; i++) {
        fm->pos = pos;
        fm->flag = 0;
        fm++;
    }
    writeId[1] = 0;
    readId[1] = 0;
}

void partyClearJumpPara(PartyEntry* party) {
    party->flags &= ~0x70;
    PF(party, 0x114) = 0.0f;
    PF(party, 0x118) = 0.0f;
    PF(party, 0x11C) = 0.0f;
}

static inline f32 partyUpdSpd(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 f;
    f32 target;
    f32 cur = party->field_104;

    if (mario->flags & 0x8000) {
        target = mario->baseSpeed;
    } else {
        target = PF(party, 0x108) * mario->playerGravity * ((party->flags & 0x80) ? 0.75f : 1.0f);
    }
    if (target > 0.0f) {
        f = cur + 0.05f * ((0.5f + target) - cur);
        if (f >= target) {
            f = target;
        }
        party->field_104 = f;
        return f;
    }
    f = cur + 0.1f * (-1.0f - cur);
    if (f <= 0.0f) {
        f = 0.0f;
    }
    party->field_104 = f;
    return f;
}

void unk_800c93d0(PartyEntry* party, f32 spd) {
    if (spd) {
        PF(party, 0x108) = spd;
        unk_800c92c4(party, spd);
        return;
    }
    PF(party, 0x108) = 0.0f;
}

void unk_800c9398(PartyEntry* party, f32 spd) {
    f32 s = spd * party->playerPtr->playerGravity;
    PF(party, 0x108) = s * ((party->flags & 0x80) ? 0.75f : 1.0f);
    party->field_104 = PF(party, 0x108);
}

f32 unk_800c92c4(PartyEntry* party, f32 spd) {
    if (party->field_28 != 0 || PU8(party, 0x36) == 2 || PU8(party, 0x36) == 3 || PU8(party, 0x36) == 6) {
        return party->field_104;
    }
    return partyUpdSpd(party);
}

void unk_800c90d4(PartyEntry* party, s32 arg) {
    s32 a;
    s32 b;

    PS8(party, 0x2D)++;
    if (party->currentMemberId == 9) {
        if (arg == 0) {
            a = 20;
            b = 40;
        } else {
            a = 10;
            b = 20;
        }
        if (PS8(party, 0x2D) >= b) {
            PS8(party, 0x2D) = 0;
            psndSFXOn_3D((const char*)0x60D, &party->position);
        } else if (PS8(party, 0x2D) == a) {
            psndSFXOn_3D((const char*)0x60C, &party->position);
        }
    } else if (party->currentMemberId == 8) {
        if (PS8(party, 0x2D) >= 15) {
            PS8(party, 0x2D) = 0;
            psndSFXOn_3D((const char*)0x942, &party->position);
        }
    } else if (party->currentMemberId == 10) {
        if (arg == 0) {
            a = 5;
            b = 10;
        } else {
            a = 5;
            b = 10;
        }
        if (PS8(party, 0x2D) >= b) {
            PS8(party, 0x2D) = 0;
            psndSFXOn_3D((const char*)0x3FF, &party->position);
        } else if (PS8(party, 0x2D) == a) {
            psndSFXOn_3D((const char*)0x3FF, &party->position);
        }
    } else if (PU8(party, 0x32) == 1) {
        if (PS8(party, 0x2D) >= (!arg ? 40 : 20)) {
            PS8(party, 0x2D) = 0;
            psndSFXOn_3D((const char*)0x926, &party->position);
        }
    } else {
        if (arg == 0) {
            a = 20;
            b = 40;
        } else {
            a = 10;
            b = 20;
        }
        if (PS8(party, 0x2D) >= b) {
            PS8(party, 0x2D) = 0;
            psndSFXOn_3D((const char*)0x925, &party->position);
        } else if (PS8(party, 0x2D) == a) {
            psndSFXOn_3D((const char*)0x924, &party->position);
        }
    }
}


void N_partyPlaySfxPartyLanding1(PartyEntry* party) {
    psndSFXOn_3D((const char*)0x928, &party->position);
}

void unk_800c9044(PartyEntry* party) {
    if (party->field_34 != 0) {
        if (marioChkDeepSleep() == TRUE || (party->flags & 0x400000)) {
            partyChgPoseId(party, 6);
        } else if (party->currentMemberId != 7) {
            partyChgPoseId(party, 1);
        } else if (!chuchu_searchObject()) {
            partyChgPoseId(party, 1);
        }
    }
}

void unk_800c8f24(PartyEntry* party, f32 spd) {
    f32 g;
    f32 a;
    f32 b;

    if (party->flags2 & 0x100) {
        partyChgPoseId(party, 3);
        unk_800c90d4(party, 1);
        return;
    }
    g = party->playerPtr->playerGravity;
    a = (1.0f == g) ? 1.65f : 2.0f;
    b = (1.0f == g) ? 0.8f : 0.0f;
    if (a - b < spd && spd < spd + b) {
        if (N_marioGetMovementSpeed() == 1) {
            partyChgPoseId(party, 2);
            unk_800c90d4(party, 0);
        } else {
            partyChgPoseId(party, 3);
            unk_800c90d4(party, 1);
        }
    } else if (spd >= a) {
        partyChgPoseId(party, 3);
        unk_800c90d4(party, 1);
    } else {
        partyChgPoseId(party, 2);
        unk_800c90d4(party, 0);
    }
}

void unk_800c8e74(PartyEntry* party) {
    f32 dir = angleABf(party->position.x, party->position.z,
                       party->playerPtr->position.x, party->playerPtr->position.z);
    f32 a = revise360(camGetPtr(4)->viewYaw + 270.0f - dir);
    BOOL b = FALSE;
    if (a >= 90.0f && a <= 270.0f) {
        b = TRUE;
    }
    party->field_110 = b ? 180.0f : 0.0f;
}

BOOL unk_800c8dd0(HitEntry* hit) {
    struct { u8 pad[0x15]; char name[1]; }* mobj;
    BOOL ret;
    const char** names;

    if (!hit) {
        return FALSE;
    }
    if (!(hitGetAttr(hit) & 0x80000000)) {
        return FALSE;
    }
    names = objNames;
    mobj = mobjHitObjPtrToPtr(hit);
    ret = FALSE;
    while (*names) {
        if (strcmp(mobj->name, *names) == 0) {
            ret = TRUE;
            break;
        }
        names++;
    }
    return ret;
}

void partyMove(PartyEntry* party) {
    partyMoveMain(party, 1);
}

void partyMoveNoHosei(PartyEntry* party) {
    partyMoveMain(party, 0);
}

s32 partyMoveMain(PartyEntry* party, s32 hosei) {
    Vec pos;
    Vec pos2;
    f32 spd;
    f32 dir;
    f32 h;
    HitEntry* hit;
    f32 v;

    PPTR(party, 0x12C) = NULL;
    PPTR(party, 0x134) = NULL;
    pos = party->position;
    spd = 0.0f;
    if (hosei) {
        partyGetMoveDirSpd(party, &dir, &spd);
    } else {
        dir = party->field_100;
        spd = party->field_104 * ((party->flags & 0x80) ? 0.75f : 1.0f);
    }
    if (!(party->flags & 0x1000000)) {
        hit = partySearchFrontWall(party, &pos, spd, dir);
        if (hit) {
            PPTR(party, 0x12C) = hit;
            if (party->field_104) {
                PPTR(party, 0x134) = hit;
            }
        }
        if (hit) {
            party->position.x = pos.x;
            party->position.z = pos.z;
        } else {
            marioChkWallAround(&pos, 1, spd, dir, party->width, party->field_F0);
            party->position.x = pos.x;
            party->position.z = pos.z;
        }
    } else {
        movePos(&party->position.x, &party->position.z, spd, dir);
    }
    if (!(party->flags & 0x2000000)) {
        pos2 = party->position;
        h = party->field_F0;
        hit = partySearchHead(party, &pos2, &h, party->field_10C);
        if (hit) {
            PPTR(party, 0x140) = hit;
        }
    }
    if (party->flags & 0x10) {
        dir = toMovedirSimple(party->field_110);
        if (!PPTR(party, 0x140)) {
            party->position.y += PF(party, 0x114);
        }
        PF(party, 0x114) += PF(party, 0x118);
        party->flags &= ~2;
        return 1;
    }
    hit = NULL;
    if (!(party->flags & 0x2000000) && PF(party, 0x114) <= 0.0f) {
        v = __fabsf(PF(party, 0x114));
        hit = partySearchGround(party, v, v);
        pos.y = PF(party, 0xE4);
        if (hit) {
            if (hitGetAttr(hit) & 0x200) {
                party->field_138 = hit;
                party->flags &= ~2;
                if (!(party->flags & 0x20)) {
                    party->flags |= 0x20;
                    if (!PF(party, 0x118)) {
                        PF(party, 0x118) = -1.4f;
                    }
                }
                party->position.y += PF(party, 0x114);
                PF(party, 0x114) += PF(party, 0x118);
                return 2;
            }
            if (PF(party, 0xE8) != 0.0f) {
                hit = NULL;
            } else {
                party->position.y = pos.y;
            }
        }
    }
    party->field_138 = hit;
    if (!hit) {
        if (!(party->flags & 0x4000000)) {
            party->flags &= ~2;
            if (!(party->flags & 0x20)) {
                party->flags |= 0x20;
                if (!PF(party, 0x118)) {
                    PF(party, 0x118) = -1.4f;
                }
            }
            party->position.y += PF(party, 0x114);
            PF(party, 0x114) += PF(party, 0x118);
            return 2;
        }
    } else if (party->flags & 0x20) {
        party->flags &= ~0x20;
        party->flags |= 2;
        PF(party, 0x114) = 0.0f;
        PF(party, 0x118) = 0.0f;
        party->position.y = pos.y;
        return 3;
    } else {
        party->position.y = pos.y;
    }
    return 0;
}

void partyChgMoveMode(PartyEntry* party, s32 mode) {
    switch (PU8(party, 0x3B)) {
        case 6:
            party->flags &= ~0x8000;
            break;
        case 4:
            break;
        case 5:
            break;
    }
    PU8(party, 0x3B) = mode;
    party->field_8 |= 4;
}

void partyChgMot(PartyEntry* party, s32 mot) {
    if (PU8(party, 0x36) == 3) {
        party->flags &= ~0x70;
        party->flags &= ~0x3000000;
        party->flags &= ~0x4000000;
    }
    PU8(party, 0x36) = mot;
    party->field_8 |= 2;
}

void partySetDir(PartyEntry* party, f32 x, f32 z) {
    party->field_100 = angleABf(party->position.x, party->position.z, x, z);
}

void partyMoveBehindMario(PartyEntry* party, s32 arg) {
    if (party->currentMemberId == 4 && party->field_34 == 3) {
        return;
    }
    PU8(party, 0x3D) = arg;
    partyChgMoveMode(party, 2);
    partyChgMot(party, 1);
}

void partyMoveBehindMario3(PartyEntry* party, s32 arg) {
    if (party->currentMemberId == 4 && party->field_34 == 3) {
        return;
    }
    party->field_8 |= 0x100000;
    party->field_8 |= 0x40000;
    party_set_behind_dir(party);
    PU8(party, 0x3D) = arg;
    partyChgMoveMode(party, 2);
    partyChgMot(party, 1);
}

void partyMoveBesideMario(PartyEntry* party, s32 arg) {
    if (party->currentMemberId == 4 && party->field_34 == 3) {
        return;
    }
    PU8(party, 0x3D) = arg;
    partyChgMoveMode(party, 3);
    partyChgMot(party, 1);
}

void partyMoveCheckWall(PartyEntry* party) {
    f32 dir;
    f32 spd;
    Vec pos;
    HitEntry* hit;

    pos = party->position;
    partyGetMoveDirSpd(party, &dir, &spd);
    hit = partySearchFrontWall(party, &pos, spd, dir);
    if (hit) {
        PPTR(party, 0x12C) = hit;
        if (party->field_104) {
            PPTR(party, 0x134) = hit;
        }
    }
    party->position.x = pos.x;
    party->position.z = pos.z;
    hit = partySearchGround(party, 10.0f, 10.0f);
    pos.y = PF(party, 0xE4);
    if (hit && (hitGetAttr(hit) & 0x200)) {
        hit = NULL;
    }
    party->field_138 = hit;
    if (!hit) {
        party->position.y += PF(party, 0x114);
        if (PF(party, 0x118) == 0.0f) {
            PF(party, 0x118) = -1.4f;
        }
        PF(party, 0x114) += PF(party, 0x118);
    }
}

s16 partyMarioHosei(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 kx;
    f32 kz;
    f32 ky;
    f32 w;
    f32 h;
    f32 a;
    f32 dir;
    f32 scale;
    f32 d;

    if (!(party->field_8 & 0x40000)) {
        kx = 0.4f;
        kz = 0.3f;
        ky = kx;
    } else {
        kx = 0.2f;
        kz = 0.15f;
        ky = kx;
    }
    if (mario->flags & 0x8000) {
        kx = 0.2f;
        kz = 0.15f;
        ky = kx;
    }
    w = party->width + PF(mario, 0x1B4);
    h = PF(mario, 0x1B8) + party->field_F0;
    PF(party, 0xA0) = 0.0f;
    kx *= w;
    kz *= w;
    PF(party, 0xA8) = 0.0f;
    ky *= h;
    if (__fabs(party->position.x - mario->position.x) <= kx &&
        __fabs(party->position.z - mario->position.z) <= kz &&
        __fabs(party->position.y - mario->position.y) <= ky) {
        dir = angleABf(mario->position.x, mario->position.z, party->position.x, party->position.z);
        if (mario->baseSpeed) {
            d = dir - PF(mario, 0x1A0);
            if (__fabsf(d) <= 4.0f) {
                if (d >= 0.0f) {
                    dir += 90.0f;
                } else {
                    dir -= 90.0f;
                }
            }
            if (++PS16(party, 0x52) > 100) {
                PS16(party, 0x52) = 100;
            }
            scale = 1.0f;
        } else {
            dir = angleABf(mario->position.x, mario->position.z, party->position.x, party->position.z);
            scale = 4.0f;
        }
        if (mario->baseSpeed > 1.0f) {
            scale = 0.8f * mario->baseSpeed;
        }
        a = (3.1416f * dir) / 180.0f;
        PF(party, 0xA0) = scale * (f32)sin(a);
        PF(party, 0xA8) = scale * -(f32)cos(a);
    } else if (PS16(party, 0x52) > 0) {
        PS16(party, 0x52)--;
    }
    return PS16(party, 0x52);
}

void partyChkWall(PartyEntry* party) {
    f32 dir;
    f32 spd;
    Vec pos;
    HitEntry* hit;

    pos = party->position;
    party->field_104 = 0.0f;
    partyGetMoveDirSpd(party, &dir, &spd);
    hit = partySearchFrontWall(party, &pos, spd, dir);
    if (hit) {
        PPTR(party, 0x12C) = hit;
        if (party->field_104) {
            PPTR(party, 0x134) = hit;
        }
    }
    party->position.x = pos.x;
    party->position.z = pos.z;
}

void unk_800c7c98(PartyEntry* party) {
    if (party->field_8 & 4) {
        party->field_8 &= ~4;
        partyChgPoseId(party, 1);
        party->flags &= ~0x100;
        if (party->currentMemberId == 5) {
            unk_801820d0(party);
        }
    }
    switch (PU8(party, 0x36)) {
        case 0:
            unk_8014bbc8(party);
            if (party->currentMemberId == 5) {
                unk_8018206c(party);
            }
            break;
        case 1:
        case 2:
        case 6:
            partyChgMot(party, 0);
            break;
        case 3:
            party_motion_fall(party);
            break;
    }
    partyModeTail(party);
    vivianShadow(party);
}

void party_move_mode_stay(PartyEntry* party) {
    if (party->field_8 & 4) {
        party->field_8 &= ~4;
        partyChgPoseId(party, 1);
        if (party->currentMemberId == 5) {
            unk_801820d0(party);
        }
    }
    switch (PU8(party, 0x36)) {
        case 0:
            party_motion_stay(party);
            if (party->currentMemberId == 5) {
                unk_8018206c(party);
            }
            break;
        case 1:
        case 2:
        case 6:
            partyChgMot(party, 0);
            break;
        case 3:
            party_motion_fall(party);
            break;
    }
    partyModeTail(party);
}

void party_move_mode_walk(PartyEntry* party) {
    if (party->field_8 & 4) {
        party->field_8 &= ~4;
    }
    switch (PU8(party, 0x36)) {
        case 0:
            party_motion_stay(party);
            break;
        case 1:
            if (PU8(party, 0x32) == 0) {
                party_motion_homing_walk(party);
            } else {
                party_motion_homing_fly(party);
            }
            break;
        case 2:
            party_motion_jump(party);
            break;
        case 3:
            party_motion_fall(party);
            break;
        case 6:
            party_motion_upstairs(party);
            break;
        case 7:
            party_motion_damage(party);
            break;
    }
    partyModeTail(party);
}

void party_move_mode_behind_mario(PartyEntry* party) {
    if (party->field_8 & 4) {
        party->field_8 &= ~4;
    }
    switch (PU8(party, 0x36)) {
        case 0:
        case 1:
            if (PU8(party, 0x32) == 0) {
                party_motion_behind_mario(party);
            } else {
                party_motion_behind_mario_fly(party);
            }
            break;
        case 2:
            party_motion_jump2(party);
            break;
        case 3:
            party_motion_fall(party);
            break;
        case 6:
            party_motion_upstairs(party);
            break;
        case 7:
            party_motion_damage(party);
            break;
    }
    party->field_FC = party->field_100;
}

void party_move_mode_beside_mario(PartyEntry* party) {
    if (party->field_8 & 4) {
        party->field_8 &= ~4;
    }
    switch (PU8(party, 0x36)) {
        case 0:
        case 1:
            party_motion_beside_mario(party);
            break;
        case 2:
            party_motion_jump2(party);
            break;
        case 3:
            party_motion_fall(party);
            break;
        case 6:
            party_motion_upstairs(party);
            break;
        case 7:
            party_motion_damage(party);
            break;
    }
    party->field_FC = party->field_100;
}

BOOL partyGetAppearPos5(PartyEntry* party, HitEntry* hit, Vec* out) {
    s32 angles[12] = {0, 30, -30, 60, -60, 90, -90, 120, -120, 150, -150, 180};
    Vec pos;
    Vec dir;
    Vec hitPos;
    Vec hitNrm;
    f32 dist;
    f32 s;
    f32 c;
    Vec* mobj;
    u32 i;

    if (!hit) {
        return FALSE;
    }
    if (!(hitGetAttr(hit) & 0x80000000)) {
        return FALSE;
    }
    mobj = (Vec*)((u8*)mobjHitObjPtrToPtr(hit) + 0x38);
    pos.x = mobj->x;
    pos.z = mobj->z;
    pos.y = 50.0f + mobj->y;
    for (i = 0; i < 12; i++) {
        f32 ang = party->field_100 + angles[i];
        dist = 50.0f;
        sincosf(&s, &c, ang);
        dir = (Vec){s, 0.0f, c};
        if (!partyHitCheck(party, &pos, &dir, &hitPos, &hitNrm, &dist)) {
            HitEntry* floor;
            dist = 150.0f;
            pos.x = s * 50.0f + mobj->x;
            pos.z = c * 50.0f + mobj->z;
            dir = (Vec){0.0f, -1.0f, 0.0f};
            floor = partyHitCheck(party, &pos, &dir, &hitPos, &hitNrm, &dist);
            if (!floor || !(hitGetAttr(floor) & 0x200)) {
                break;
            }
        }
    }
    if (i >= 12) {
        return FALSE;
    }
    out->x = pos.x;
    out->y = pos.y;
    out->z = pos.z;
    return TRUE;
}
