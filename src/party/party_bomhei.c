#include "dolphin/types.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_sbr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "party.h"
#include "pmario_sound.h"
#include "system.h"
#include "driver/animdrv.h"
#include "mario/mario_motion.h"
#include "driver/camdrv.h"
#include "driver/hitdrv.h"
#include <dolphin/mtx.h>
#include <string.h>

extern void partyChgRunMode(PartyEntry* party, s32 mode);
extern void partyGoodbyeInit(PartyEntry* party);
extern s32 partyGoodbyeMain(PartyEntry* party);
extern void partyGetAppearPos(PartyEntry* party, Vec* pos);

extern f32 partyToMovedir(f32 dir);
extern void* mobjHitObjPtrToPtr(HitEntry* hit);
extern u8* caseCheckHitObj2(void* hit);

extern s32 evt_cam_shake(void* evt, BOOL isFirstCall);

s32 m_w_7_sync[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 8, 7, 5, 3, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 9, 8, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0};

s32 longQuake_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, (s32)0xF24A7A8F, (s32)0xF24A7A8F, 600, 2, 1,
};

static s32 quake_evt[] = {
    0x0005005B, (s32)evt_cam_shake, 4, (s32)0xF24A7A8F, (s32)0xF24A7A8F, 200, 2, 1,
};

static inline BOOL isBombRock(HitEntry* hit) {
    u8* c;
    if (hit == NULL) {
        return FALSE;
    }
    if (hitGetAttr(hit) & 0x80000000) {
        if (strcmp((char*)mobjHitObjPtrToPtr(hit) + 0x15, "MOBJ_BombRock") == 0) {
            return TRUE;
        }
    } else {
        c = caseCheckHitObj2(hit);
        if (c != NULL && *(s32*)(c + 4) == 15) {
            return TRUE;
        }
    }
    return FALSE;
}

#define PF(p, off, T) (*(T*)((u8*)(p) + (off)))

#define BOMHEI_CLEAN_SFX(p)                    \
    if ((u32)PF(p, 0x180, s32) != 0xFFFFFFFFU) {             \
        psndSFXOff(PF(p, 0x180, s32));         \
        PF(p, 0x180, s32) = -1;                \
    }                                          \
    if ((u32)PF(p, 0x184, s32) != 0xFFFFFFFFU) {             \
        psndSFXOff(PF(p, 0x184, s32));         \
        PF(p, 0x184, s32) = -1;                \
    }

#define BOMHEI_CLEAN_FLAGS(p)                  \
    (p)->flags2 &= ~(1 << 4);                  \
    (p)->flags &= ~(1 << 25);                  \
    (p)->flags &= ~(1U << 31);                 \
    (p)->flags &= ~(1 << 8);

#define BOMHEI_FREE(p)                         \
    if (PF(p, 0x170, void*) != NULL) {         \
        __memFree(0, PF(p, 0x170, void*));     \
        PF(p, 0x170, void*) = NULL;            \
    }

void bomhei_bye(PartyEntry* party) {
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyGoodbyeInit(party);
        party->playerPtr->flags &= ~(1 << 13);
        BOMHEI_CLEAN_SFX(party);
    }
    if (partyGoodbyeMain(party)) {
        partyChgRunMode(party, 14);
    }
}

void bomhei_init_800BFBB0(PartyEntry* party) {
    PF(party, 0x33, u8) = 3;
    PF(party, 0x32, u8) = 0;
    PF(party, 0xF0, f32) = 28.0f;
    PF(party, 0xF4, f32) = 28.0f;
    PF(party, 0x17A, u8) = 100;
    PF(party, 0x17C, s32) = -1;
    PF(party, 0x180, s32) = -1;
    PF(party, 0x184, s32) = -1;
}

u8 bomheiGetStatus() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    u8 status = 2;

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_BOBBERY && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        status = 0;
        return status;
    } else if (party->useMotionId == 60) {
        status = 1;
    }
    return status;
}

void bomhei_exit(PartyEntry* party) {
    PartyEntry* p;
    party->playerPtr->flags &= ~(1 << 13);
    p = partyGetPtr(marioGetPartyId());
    if (p != NULL && p->currentMemberId == PARTY_MEMBER_BOBBERY && (p->flags & PARTY_FLAG_IS_BEING_USED)) {
        p->playerPtr->flags &= ~(1 << 13);
        if (p->field_34 != 9) {
            partyChgRunMode(p, 2);
            p->field_3A[1] = 0;
        }
        BOMHEI_CLEAN_FLAGS(p);
        BOMHEI_CLEAN_SFX(p);
        BOMHEI_FREE(p);
    }
}

void bomhei_use_cancel() {
    PartyEntry* p = partyGetPtr(marioGetPartyId());
    if (p != NULL && p->currentMemberId == PARTY_MEMBER_BOBBERY && (p->flags & PARTY_FLAG_IS_BEING_USED)) {
        p->playerPtr->flags &= ~(1 << 13);
        if (p->field_34 != 9) {
            partyChgRunMode(p, 2);
            p->field_3A[1] = 0;
        }
        BOMHEI_CLEAN_FLAGS(p);
        BOMHEI_CLEAN_SFX(p);
        BOMHEI_FREE(p);
    }
}

void bomhei_use_cancel2() {
    PartyEntry* p = partyGetPtr(marioGetPartyId());
    if (p != NULL && p->currentMemberId == PARTY_MEMBER_BOBBERY && (p->flags & PARTY_FLAG_IS_BEING_USED) && (p->playerPtr->flags & (1 << 13))) {
        p->playerPtr->flags &= ~(1 << 13);
        marioChgPose("M_S_1");
        if (p->field_34 != 9) {
            partyChgRunMode(p, 2);
            p->field_3A[1] = 0;
        }
        BOMHEI_CLEAN_FLAGS(p);
        BOMHEI_CLEAN_SFX(p);
        BOMHEI_FREE(p);
    }
}

void bomhei_use_post(PartyEntry* party) {
    MarioWork* player = party->playerPtr;
    const char* name;
    if (party->useMotionId >= 70 && party->useMotionId < 100) {
        partyGetAppearPos(party, &party->position);
    }
    if (player->flags & (1 << 13)) {
        player->flags &= ~(1 << 13);
        if (PF(player, 0x2E, u16) == 1) {
            name = "M_W_1";
        } else if (PF(player, 0x2E, u16) == 2) {
            name = "M_R_1";
        } else if (player->flags & (1 << 16)) {
            name = "M_J_1B";
        } else {
            name = "M_S_1";
        }
        marioChgPose(name);
    }
    BOMHEI_CLEAN_FLAGS(party);
    if (party->field_34 != 9) {
        party->field_3A[1] = 0;
        party->field_8 |= 8;
    }
    party->playerPtr->flags &= ~(1 << 13);
    BOMHEI_CLEAN_SFX(party);
    BOMHEI_FREE(party);
}

typedef struct BomheiMobj {
    u8 pad[0x15];
    char name[0x10];
} BomheiMobj;

extern void partyChkGnd(PartyEntry* party);
extern void partyChgMot(PartyEntry* party, s32 mot);
void bomhei_use_main(PartyEntry* party);
void mario_controll(PartyEntry* party);

void bomhei_use(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    BomheiMobj* mobj;

    if (party->flags & PARTY_FLAG_IS_BEING_USED) {
        bomhei_use_main(party);
        if ((party->useMotionId >= 30 && party->useMotionId <= 32) ||
            (party->useMotionId >= 50 && party->useMotionId <= 51) || party->useMotionId == 60) {
            partyChkGnd(party);
            if (party->flags & 2) {
                partyChgMot(party, 0);
                PF(party, 0x114, f32) = 0.0f;
            }
            if (strcmp(gp->currentMapName, "muj_05") == 0 && party->field_138 != NULL &&
                strcmp(hitGetName(party->field_138), "A_dokuro_bero") == 0) {
                party->field_100 = angleABf(party->position.x, party->position.z, 638.0f, 12.5f);
                party->field_FC = party->field_100;
            }
        }
        if (PF(party, 0x17A, u8) != 0x66) {
            if (mario->currMotionId == 0x1F || mario->currMotionId == 0x20) {
                PF(party, 0x17A, u8) = 0x66;
                return;
            }
            mario_controll(party);
        }
        if (party->useMotionId <= 10 && mario->hitobjStandOn != NULL && (hitGetAttr(mario->hitobjStandOn) & 0x80000000)) {
            mobj = (BomheiMobj*)mobjHitObjPtrToPtr(mario->hitobjStandOn);
            if (strcmp(mobj->name, "MOBJ_RedJumpStand") == 0 ||
                strcmp(mobj->name, "MOBJ_RedJumpStand2") == 0 ||
                strcmp(mobj->name, "MOBJ_BlueJumpStand") == 0 ||
                strcmp(mobj->name, "MOBJ_BlueJumpStand2") == 0) {
                bomhei_use_cancel();
                return;
            }
        }
        if (!(party->flags & 0x80000000) && marioKeyOffChk()) {
            bomhei_use_cancel();
        } else if (mario->forceMoveTimer != 0) {
            bomhei_use_cancel();
        } else if (party->useMotionId <= 10 && (mario->dispFlags & 0x1000000)) {
            bomhei_use_cancel();
        }
    }
}

s32 mario_bomhei_keychk() {
    MarioWork* mario = marioGetPtr();
    PartyEntry* p = partyGetPtr(marioGetPartyId());
    u8 m;
    if (p == NULL) return 1;
    if (p->currentMemberId != PARTY_MEMBER_BOBBERY) return 1;
    if ((p->flags & PARTY_FLAG_IS_BEING_USED) == 0) return 1;
    m = PF(p, 0x17A, u8);
    if (m == 10 || (m >= 20 && m <= 21) || m == 101 || (m >= 40 && m <= 41) || (m >= 30 && m <= 36)) return 0;
    m = p->useMotionId;
    if ((m >= 50 && m <= 51) || m == 60 || (m >= 70 && m <= 71)) return 0;
    return 1;
}

s32 mario_bomhei_keychk2() {
    MarioWork* mario = marioGetPtr();
    PartyEntry* p = partyGetPtr(marioGetPartyId());
    u8 m;
    if (p == NULL) return 1;
    if (p->currentMemberId != PARTY_MEMBER_BOBBERY) return 1;
    if ((p->flags & PARTY_FLAG_IS_BEING_USED) == 0) return 1;
    m = PF(p, 0x17A, u8);
    if (m == 10 || m == 101 || (m >= 30 && m <= 36)) return 0;
    return 1;
}

void mario_controll(PartyEntry* party) {
    MarioWork* player = party->playerPtr;
    s32 cnt;

    switch (PF(party, 0x17A, u8)) {
    case 10:
        marioAdjustMoveDir();
        marioChgPose("M_U_2");
        player->flags |= 0x2000;
        PF(party, 0x17A, u8) = 101;
        break;
    case 20:
        player->flags |= 0x2000;
        PF(party, 0x17A, u8) = 21;
        break;
    case 21:
        if (strcmp(player->animName, "M_W_7") == 0) {
            animPoseSetLocalTime(player->paperAnimGroupId[marioAnimeId()], PF(party, 0x17B, u8));
            cnt = PF(party, 0x17B, u8) + 1;
            PF(party, 0x17B, u8) = cnt;
            if ((u8)cnt >= 40) {
                PF(party, 0x17B, u8) = 0;
            }
        } else {
            PF(party, 0x17B, u8) = 0;
        }
        break;
    case 40:
        marioChgMot(0);
        PF(party, 0x17A, u8) = 41;
        PF(party, 0x178, s16) = 40;
        break;
    case 41:
        if (--PF(party, 0x178, s16) <= 0) {
            marioChgMot(0);
            PF(party, 0x17A, u8) = 100;
        }
        break;
    case 30:
        marioChgMot(0);
        PF(party, 0x17A, u8) = 31;
        break;
    case 31:
        marioChgPose("M_C_1");
        player->flags &= ~0x2000;
        PF(party, 0x178, s16) = 50;
        PF(party, 0x17A, u8) = 32;
        break;
    case 32:
        if (--PF(party, 0x178, s16) <= 0) {
            PF(party, 0x17A, u8) = 36;
            PF(party, 0x178, s16) = 10;
        }
        break;
    case 36:
        animPoseSetLocalTime(player->paperAnimGroupId[marioAnimeId()], PF(party, 0x178, s16));
        if (--PF(party, 0x178, s16) < 0) {
            marioChgMot(0);
            PF(party, 0x17A, u8) = 100;
        }
        break;
    }
}

extern f32 toMovedirSimple(f32 dir);

static inline BOOL bomheiChkReturnGround(Vec* pos, f32 dist, f32 angle) {
    HitCheckQuery query;
    HitEntry* hit;
    f32 x, z;
    f32 rf;

    marioGetPtr();
    x = pos->x;
    z = pos->z;
    movePos(&x, &z, dist, angle);
    query.targetDistance = 4.0f;
    {
        Vec start = {0.0f, 0.0f, 0.0f};
        Vec dir = {0.0f, -1.0f, 0.0f};
        start.x = x;
        start.y = 2.0f + pos->y;
        start.z = z;
        query.targetPos = start;
        query.targetDir = dir;
    }
    hit = hitCheckVecFilter(&query, NULL);
    if (hit != NULL && !(hitGetAttr(hit) & 0xE00)) {
    if (query.hitPos.x >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    pos->x = (s32)((1000.0f * query.hitPos.x) + rf) / 1000.0f;
    if (query.hitPos.y >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    pos->y = (s32)((1000.0f * query.hitPos.y) + rf) / 1000.0f;
    if (query.hitPos.z >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    pos->z = (s32)((1000.0f * query.hitPos.z) + rf) / 1000.0f;
    return TRUE;
    }
    return FALSE;
}

void partyGetReturnPos(Vec* out) {
    MarioWork* mario = marioGetPtr();
    f32 x, z, s, c;
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 y;
    f32 angle;
    Vec p;

    x = mario->position.x;
    y = 2.0f + mario->position.y;
    z = mario->position.z;
    dist = mario->wPlayerCollisionBox.x;
    angle = mario->targetYaw;
    sincosf(&s, &c, angle);
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, 0.0f, c) == NULL) {
        p = mario->position;
        if (bomheiChkReturnGround(&p, 6.0f, angle)) {
            out->x = p.x;
            out->y = p.y;
            out->z = p.z;
            return;
        }
    }

    x = mario->position.x;
    y = 2.0f + mario->position.y;
    z = mario->position.z;
    dist = mario->wPlayerCollisionBox.x;
    angle = revise360(toMovedirSimple(mario->unk1AC) - 180.0f);
    sincosf(&s, &c, angle);
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, 0.0f, c) == NULL) {
        p = mario->position;
        if (bomheiChkReturnGround(&p, mario->wPlayerCollisionBox.x, angle)) {
            out->x = p.x;
            out->y = p.y;
            out->z = p.z;
            return;
        }
    }

    angle = toMovedirSimple(mario->unk1AC);
    sincosf(&s, &c, angle);
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, 0.0f, c) == NULL) {
        p = mario->position;
        if (bomheiChkReturnGround(&p, mario->wPlayerCollisionBox.x, angle)) {
            out->x = p.x;
            out->y = p.y;
            out->z = p.z;
            return;
        }
    }

    x = mario->position.x;
    z = mario->position.z;
    movePos(&x, &z, mario->wPlayerCollisionBox.x, revise360(180.0f + mario->targetYaw));
    out->x = x;
    out->y = mario->position.y;
    out->z = z;
}

HitEntry* check_front(PartyEntry* party) {
    s32 angles[8] = {0, 45, -45, 90, -90, 135, -135, 180};
    static const Vec down = {0.0f, -1.0f, 0.0f};
    HitCheckQuery q;
    HitEntry* hit;
    HitEntry* found = NULL;
    HitEntry* last = NULL;
    f32 height = 0.8f * PF(party, 0xF0, f32);
    f32 movedir = partyToMovedir(PF(party, 0x10C, f32));
    f32 ang;
    f32 lim;
    u32 i;

    for (i = 0; i < 8; i++) {
        sincosf(&q.targetDir.x, &q.targetDir.z, movedir + (f32)angles[i]);
        q.targetDir.y = 0.0f;
        q.targetPos = party->position;
        q.targetPos.y = q.targetPos.y + height;
        q.targetDistance = 100.0f;
        hit = hitCheckVecFilter(&q, NULL);
        if (hit != NULL) {
            ang = revise360(movedir + (f32)angles[i] - camGetPtr(CAMERA_3D)->viewYaw);
            if ((ang >= 60.0f && ang <= 120.0f) || (ang >= 240.0f && ang <= 300.0f)) {
                lim = 50.0f;
            } else {
                lim = 30.0f;
            }
            if (q.targetDistance <= lim && isBombRock(hit)) {
                return hit;
            }
            found = NULL;
        }
    }

    q.targetPos = party->position;
    q.targetDir = down;
    q.targetDistance = 2.0f + height;
    hit = hitCheckVecFilter(&q, NULL);
    if (hit != NULL) {
        if (isBombRock(hit)) {
            return hit;
        }
        last = hit;
    }

    hit = party->field_138;
    if (hit != NULL && isBombRock(hit)) {
        return hit;
    }
    if (found != NULL) {
        return found;
    }
    if (last != NULL) {
        return last;
    }
    return hit;
}
