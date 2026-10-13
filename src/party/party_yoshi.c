#include "dolphin/types.h"
#include "driver/animdrv.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "mario/mario_sbr.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "mario/mario_party.h"
#include "memory.h"
#include "party.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <string.h>

typedef struct YoshiWork {
    u8 pad0[0x4];         // 0x0
    s32 dir;              // 0x4
    s32 count;            // 0x8
    f32 angle;            // 0xC
    s32 timer;            // 0x10
    EffectEntry* effect;  // 0x14
} YoshiWork;

#define MARIO_U16(m, off) (*(u16*)((u8*)(m) + (off)))
#define MARIO_F32(m, off) (*(f32*)((u8*)(m) + (off)))

extern void partyChgRunMode(PartyEntry* party, s32 mode);
extern void partyChgPose(PartyEntry* party, const char* pose);
extern void partyGoodbyeInit(PartyEntry* party);
extern s32 partyGoodbyeMain(PartyEntry* party);
extern void party_force_ride_yoshi(PartyEntry* party);
void yoshi_use(PartyEntry* party);
extern f32 marioGetMoveRate(void);
extern HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth);
extern void marioSetSplash(s32 kind, Vec* pos);
extern HitEntry* partySearchWallFront(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
extern BOOL marioChkBero(HitEntry* hit);
extern HitEntry* dou10_yoko_yari2(void* out);
extern void* partyChkFrontStep(PartyEntry* party, f32 range, f32* y, f32* a, f32* b);
extern void set_damage_root_ypos(f32 y);
extern void psndSFXOff(s32 id);
extern void partyUpdateKeyData(PartyEntry* party);
extern void L_partyClearCont(PartyEntry* party);
extern void marioChgSmallJumpMotion(void);
extern void partyChkGnd(PartyEntry* party);
extern s32 psndSFXOn_3D(s32 id, Vec* pos);
extern f32 partyGetHeight(PartyEntry* party);
extern void* marioSearchHead(Vec* pos, f32 range, f32* height);
extern void party_ride_yoshi_force_move(void);
extern EffectEntry* effSweatN64Entry(s32 type, f32 x, f32 y, f32 z, f32 base, f32 angle, s32 life);
extern f32 marioGetJumpHeight(void);
extern void marioSetPeakYpos(void);
extern s32 marioChkDamageSink(void);
extern void marioSetFallPara(void);
extern void marioUpdateCamCollision(Vec* pos);
double sin(double);

f32 ofs_PYS_S_2[52] = {
    0.0f, -0.011f, -0.042f, -0.087f, -0.142f, -0.202f, -0.262f, -0.317f, -0.362f, -0.393f, -0.404f, -0.404f, -0.404f,
    -0.404f, -0.404f, -0.387f, -0.341f, -0.276f, -0.202f, -0.128f, -0.063f, -0.017f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.011f, -0.042f, -0.087f, -0.142f, -0.202f, -0.262f, -0.317f, -0.362f, -0.393f, -0.404f, -0.404f, -0.404f,
    -0.404f, -0.404f, -0.387f, -0.341f, -0.276f, -0.202f, -0.128f, -0.063f, -0.017f, 0.0f, 0.0f, 0.0f, 0.0f,
};
static f32 marioJumpStandData[10] = {1.52f, -0.188f, 2.925f, -0.847f, -0.1f, -0.4f, 0.024f, -0.004f, 0.125f, 0.7f};
f32 ofs_PYS_R_2[10] = {0.0f, 0.0f, 0.366f, 0.555f, 0.38f, 0.0f, 0.0f, 0.366f, 0.555f, 0.38f};
f32 ofs_PYS_F_1[10] = {0.0f, 0.0f, 0.433f, 0.557f, 0.512f, 0.0f, 0.0f, 0.433f, 0.557f, 0.512f};

#define YW(party) ((YoshiWork*)(party)->useStruct)
#define ADD_OFS(party)                                              \
    if ((party)->field_138) {                                       \
        (party)->position.x += P_F32(party, 0xAC);                  \
        (party)->position.y += P_F32(party, 0xB0);                  \
        (party)->position.z += P_F32(party, 0xB4);                  \
    }
#define SYNC_MARIO(mario, party)                                    \
    P_F32(mario, 0xEC) = (party)->position.x;                       \
    P_F32(mario, 0xF4) = (party)->position.z;                       \
    P_F32(mario, 0x8C) = (party)->position.x;                       \
    P_F32(mario, 0x94) = (party)->position.z;                       \
    P_F32(mario, 0x1A8) = (party)->field_10C;                       \
    P_F32(mario, 0x1AC) = (party)->field_110;
void unk_800b474c(PartyEntry* party);

#define P_S8(p, off) (*(s8*)((u8*)(p) + (off)))
#define P_PTR(p, off) (*(void**)((u8*)(p) + (off)))
#define P_S16(p, off) (*(s16*)((u8*)(p) + (off)))
#define P_S32(p, off) (*(s32*)((u8*)(p) + (off)))
#define P_F32(p, off) (*(f32*)((u8*)(p) + (off)))

f32 jumpheight;
s32 evt_yoshi_frm;
f32 evt_yoshi_spd;

s32 yoshiGetStatus(void);
void inertia(PartyEntry* party);
void searchGround(PartyEntry* party);
void searchGround2(PartyEntry* party);
void checkWall(PartyEntry* party, f32 spd, f32 dir);
void L_getStick(PartyEntry* party, f32* angle, f32* speed);
void L_yoshiFlyMove(PartyEntry* party);

void evt_set_yoshi_frm(s32 msec) {
    evt_yoshi_frm = sysMsec2Frame(msec);
}

void evt_set_yoshi_spd(f32 spd) {
    evt_yoshi_spd = spd;
}

s32 evt_get_yoshi_frm(void) {
    return evt_yoshi_frm;
}

void L_sweatEntry(PartyEntry* party, void* hit) {
    party->field_138 = hit;
    if (yoshiGetStatus() == 1 && !(party->playerPtr->flags & 0xF0000)) {
        party->playerPtr->hitobjStandOn = hit;
    }
}

void L_sweatMain(PartyEntry* party) {
    if (party->useStruct && ((YoshiWork*)party->useStruct)->effect) {
        f32 x = party->position.x;
        f32 y = party->position.y + 18.0f;
        f32 z = party->position.z;
        ((f32*)((YoshiWork*)party->useStruct)->effect->userdata)[1] = x;
        ((f32*)((YoshiWork*)party->useStruct)->effect->userdata)[2] = y;
        ((f32*)((YoshiWork*)party->useStruct)->effect->userdata)[3] = z;
        if (--((YoshiWork*)party->useStruct)->timer <= 0) {
            effDelete(((YoshiWork*)party->useStruct)->effect);
            ((YoshiWork*)party->useStruct)->effect = NULL;
        }
    }
}

s32 yoshiGetStatus(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    s32 status = 5;
    u8 motion;

    if (party == NULL || party->currentMemberId != 4 || !(party->flags & 0x100)) {
        return 0;
    }
    motion = party->useMotionId;
    if (motion >= 10 && motion <= 13) {
        status = 1;
    } else if (motion >= 20 && motion <= 22) {
        status = 2;
    } else if (motion >= 100 && motion <= 101) {
        status = 5;
    } else if (motion >= 60 && motion <= 65) {
        status = 3;
    } else if (motion >= 50 && motion <= 52) {
        status = 4;
    }
    return status;
}

void marioRideYoshi(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    PartyEntry* extra;

    party->field_8 &= ~8;
    party->field_8 &= ~4;
    party->field_8 &= ~2;
    party->flags |= 0x100;
    party->field_34 = 3;
    party->useMotionId = 11;
    if (party->useStruct == NULL) {
        party->useStruct = __memAlloc(HEAP_DEFAULT, sizeof(YoshiWork));
        memset(party->useStruct, 0, sizeof(YoshiWork));
        ((YoshiWork*)party->useStruct)->effect = NULL;
    }
    extra = partyGetPtr(marioGetExtraPartyId());
    if (extra) {
        party_force_ride_yoshi(extra);
    }
}

s32 marioGetoffYoshi(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());

    if (!(party->flags & 0x100)) {
        return 0;
    }
    if (yoshiGetStatus() == 1) {
        party->useMotionId = 100;
        return 1;
    }
    return 0;
}

static inline void L_resetOfs(PartyEntry* party) {
    PartyEntry* extra;

    MarioWork* player = party->playerPtr;

    player->field_0x98 = (Vec){0.0f, 0.0f, 0.0f};
    player->field_0xA4 = (Vec){0.0f, 0.0f, 0.0f};
    extra = partyGetPtr(marioGetExtraPartyId());
    if (extra) {
        *(Vec*)extra->field_7C = (Vec){0.0f, 0.0f, 0.0f};
    }
}

static inline u32 L_chgMotion(PartyEntry* party, u8 motion) {
    if (party->useMotionId == 5) {
        return FALSE;
    }
    party->useMotionId = motion;
    return TRUE;
}

static inline void L_fall(PartyEntry* party) {
    if (!(party->flags & 0x20)) {
        party->flags |= 0x20;
        P_F32(party, 0x11C) = -0.4f;
        P_F32(party, 0x174) = -0.4f;
        P_F32(party, 0x178) = 0.0f;
        P_F32(party, 0x118) = 0.0f;
    }
    P_F32(party, 0x178) += P_F32(party, 0x118);
    P_F32(party, 0x174) += P_F32(party, 0x178);
    P_F32(party, 0x11C) += P_F32(party, 0x174);
    if (P_F32(party, 0x11C) < -15.0f) {
        P_F32(party, 0x11C) = -15.0f;
    }
}

void marioYoshiForceCancel(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    PartyEntry* extra;

    if (yoshiGetStatus() == 0) {
        return;
    }
    L_resetOfs(party);
    marioChgPose("M_S_1");
    if (party->flags & 0x100) {
        party->flags &= ~0x100;
        if (party->useStruct) {
            __memFree(HEAP_DEFAULT, party->useStruct);
            party->useStruct = NULL;
        }
        if (mario->currMotionId == 0x20) {
            partyChgRunMode(party, 0xd);
            extra = partyGetPtr(marioGetExtraPartyId());
            if (extra) {
                partyChgRunMode(extra, 0xd);
            }
            return;
        }
    }
    if (party->field_34 != 8 && party->field_34 != 0xd) {
        partyChgRunMode(party, 2);
        party->field_3A[1] = 0;
    }
}

void yoshi_bye(PartyEntry* party) {
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        partyGoodbyeInit(party);
    }
    if (party->flags & 0x100) {
        if (yoshiGetStatus() == 1) {
            party->useMotionId = 100;
        }
        yoshi_use(party);
    } else if (partyGoodbyeMain(party)) {
        partyChgRunMode(party, 0xe);
    }
}

void yoshi_exit(PartyEntry* party) {
    party->playerPtr->flags &= ~0x10000000;
    marioYoshiForceCancel();
    marioChgMot(0);
}

void yoshi_jumpStand(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());

    if (party == NULL || party->currentMemberId != 4 || !(party->flags & 0x100)) {
        return;
    }
    if (!(party->useMotionId >= 60 && party->useMotionId <= 66)) {
            party->useMotionId = 60;
        }
}

void unk_800b474c(PartyEntry* party) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* extra;

    L_sweatEntry(party, NULL);
    marioChgMot(0x20);
    party->useMotionId = 10;
    partyChgPose(party, "PYS_S_2");
    marioChgPose("M_Y_2");
    MARIO_F32(mario, 0x2B0) = 0.0f;
    MARIO_F32(mario, 0x2B4) = 0.0f;
    partyChgRunMode(party, 0xd);
    extra = partyGetPtr(marioGetExtraPartyId());
    if (extra) {
        partyChgRunMode(extra, 0xd);
    }
}

void unk_800b45e0(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;

    if (!strcmp(party->field_18, "PYS_S_2")) {
        if (++MARIO_U16(mario, 0x28) >= 52) {
            MARIO_U16(mario, 0x28) = 0;
        }
        party->field_20 = MARIO_U16(mario, 0x28);
        animPoseSetLocalTime(party->paperAnimGroup, MARIO_U16(mario, 0x28));
    } else if (!strcmp(party->field_18, "PYS_R_2")) {
        if (++MARIO_U16(mario, 0x28) >= 10) {
            MARIO_U16(mario, 0x28) = 0;
        }
        party->field_20 = MARIO_U16(mario, 0x28);
        animPoseSetLocalTime(party->paperAnimGroup, MARIO_U16(mario, 0x28));
    } else if (!strcmp(party->field_18, "PYS_F_1")) {
        if (++MARIO_U16(mario, 0x28) >= 10) {
            MARIO_U16(mario, 0x28) = 0;
        }
        party->field_20 = MARIO_U16(mario, 0x28);
        animPoseSetLocalTime(party->paperAnimGroup, MARIO_U16(mario, 0x28));
    }
}

void yoshi_init(PartyEntry* party) {
    party->field_32[1] = 4;
    party->field_32[0] = 0;
    party->field_F0 = 26.0f;
    party->width = 20.0f;
    party->yoshiPsndSFXId = -1;
}

static inline void L_searchHead(PartyEntry* party);
static inline f32 L_getOfs(PartyEntry* party) {
    MarioWork* p = party->playerPtr;
    f32 ofs = 0.0f;

    if (!strcmp(party->field_18, "PYS_S_2")) {
        ofs += 2.0f * ofs_PYS_S_2[MARIO_U16(p, 0x28)];
    } else if (!strcmp(party->field_18, "PYS_R_2")) {
        ofs += 2.0f * ofs_PYS_R_2[MARIO_U16(p, 0x28)];
    } else if (!strcmp(party->field_18, "PYS_F_1")) {
        ofs += 2.0f * ofs_PYS_F_1[MARIO_U16(p, 0x28)];
    }
    return ofs;
}

void yoshi_use(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* extra;
    f32 dir;
    f32 spd;
    HitEntry* hit;
    s32 attr;
    f32 angle;
    f32 speed;
    f32 ox;
    f32 oz;

    if (!P_S8(mario, 0x39)) {
        partyUpdateKeyData(party);
    } else {
        L_partyClearCont(party);
    }
    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        party->flags &= ~0x70;
        party->flags &= ~0x3000000;
        party->flags &= ~0x4000000;
        party->useStruct = __memAlloc(HEAP_DEFAULT, sizeof(YoshiWork));
        memset(party->useStruct, 0, sizeof(YoshiWork));
        YW(party)->effect = NULL;
        if (party->flags & 0x80000000) {
            evt_yoshi_spd = 1.0f;
        } else {
            evt_yoshi_frm = -1;
            evt_yoshi_spd = 0.0f;
        }
        if (!(party->flags & 0x80000000)) {
            party->useMotionId = 0;
        } else {
            party->useMotionId = 4;
        }
        P_S32(party, 0x24) = 3;
        P_F32(mario, 0x180) = 0.0f;
        P_F32(mario, 0x2A4) = 0.0f;
        P_F32(mario, 0x2A0) = 0.0f;
        P_F32(mario, 0x2B0) = 0.0f;
        P_F32(mario, 0x2B4) = 0.0f;
        YW(party)->dir = 0;
    }

    switch (party->useMotionId) {
        case 0:
            if (--P_S32(party, 0x24) > 0) {
                if (!marioKeyOffChk() && mario->hitobjStandOn) {
                    return;
                }
                if (party->flags & 0x100) {
                    party->flags &= ~0x100;
                    if (party->useStruct) {
                        __memFree(HEAP_DEFAULT, party->useStruct);
                        party->useStruct = NULL;
                    }
                }
                if (party->field_34 != 8 && party->field_34 != 0xd) {
                    partyChgRunMode(party, 2);
                    party->field_3A[1] = 0;
                }
                return;
            }
            party->useMotionId = 4;
        case 4:
            P_F32(mario, 0x1A0) = P_F32(mario, 0x1A0) <= 180.0f ? 90.0f : 270.0f;
            P_F32(mario, 0x19C) = P_F32(mario, 0x1A0);
            *(Vec*)((u8*)party + 0x94) = *(Vec*)((u8*)mario + 0x8C);
            P_S32(party, 0x24) = 4;
            P_F32(party, 0x114) = 0.0f;
            P_F32(party, 0x11C) = 0.0f;
            P_F32(party, 0x174) = 0.0f;
            P_F32(party, 0x178) = 0.0f;
            P_F32(party, 0x118) = 0.0f;
            party->field_100 = angleABf(party->position.x, party->position.z, P_F32(party, 0x94), P_F32(party, 0x9C));
            party->field_104 = distABf(party->position.x, party->position.z, P_F32(party, 0x94), P_F32(party, 0x9C)) / P_S32(party, 0x24);
            party->useMotionId = 5;
        case 5:
            *(Vec*)((u8*)party + 0x94) = *(Vec*)((u8*)mario + 0x8C);
            party->position.x += (P_F32(party, 0x94) - party->position.x) / P_S32(party, 0x24);
            party->position.y += (P_F32(party, 0x98) - party->position.y) / P_S32(party, 0x24);
            party->position.z += (P_F32(party, 0x9C) - party->position.z) / P_S32(party, 0x24);
            if (--P_S32(party, 0x24) != 0) {
                searchGround(party);
                ADD_OFS(party);
                return;
            }
            mario->trigFlags |= 0x20000;
            marioChgSmallJumpMotion();
            P_F32(mario, 0x180) = 0.0f;
            party->field_FC = P_F32(mario, 0x19C);
            party->field_100 = P_F32(mario, 0x1A0);
            party->field_110 = P_F32(mario, 0x1AC);
            party->field_10C = P_F32(mario, 0x1A8);
            party->field_104 = 0.0f;
            party->useMotionId = 7;
            ADD_OFS(party);
            partyChkGnd(party);
            return;
        case 7:
            if (!(party->flags & 0x80000000)) {
                if (marioKeyOffChk()) {
                    party->useMotionId = 101;
                    break;
                }
                if (!(party->flags & 2)) {
                    party->useMotionId = 101;
                    break;
                }
            }
            if (mario->hitobjStandOn == NULL) {
                ADD_OFS(party);
                partyChkGnd(party);
                return;
            }
            party->useMotionId = 10;
            extra = partyGetPtr(marioGetExtraPartyId());
            if (extra) {
                partyChgRunMode(extra, 0xc);
            }
            partyChkGnd(party);
            break;
    }

    switch (party->useMotionId) {
        case 10:
            psndSFXOn_3D(0x93F, &party->position);
            party->flags &= ~0x2000000;
        case 11:
            marioChgMot(0x1A);
            partyChgPose(party, "PYS_H_1");
            marioChgPose("M_Y_1");
            party->field_104 = 0.0f;
            P_F32(party, 0x128) = 0.0f;
            party->position.x = P_F32(mario, 0x8C);
            party->position.y = P_F32(mario, 0x90);
            party->position.z = P_F32(mario, 0x94);
            P_F32(mario, 0xEC) = party->position.x;
            P_F32(mario, 0xF4) = party->position.z;
            party->useMotionId = 12;
            *(Vec*)((u8*)mario + 0x11C) = party->position;
            break;
        case 12:
            MARIO_U16(party->playerPtr, 0x28) = 0;
            party->useMotionId = 13;
        case 13:
            if (mario->flags & 0x20) {
                marioChgPose("M_Y_2");
                partyChgPose(party, "PYS_R_2");
                P_PTR(party, 0x12C) = NULL;
                P_PTR(party, 0x134) = NULL;
                P_PTR(party, 0x140) = NULL;
                mario->field_0x1E0 = NULL;
                mario->hitobjPush = NULL;
                mario->field_0x1F0 = NULL;
                P_PTR(mario, 0x1F4) = NULL;
                dir = P_F32(mario, 0x1A0);
                spd = P_F32(mario, 0x180);
                L_searchHead(party);
                checkWall(party, spd, dir);
                SYNC_MARIO(mario, party);
                party_ride_yoshi_force_move();
                *(Vec*)((u8*)mario + 0x11C) = party->position;
                searchGround(party);
                if (--P_S16(mario, 0x4E) <= 0) {
                    P_S16(mario, 0x4E) = 0;
                    mario->flags &= ~0x20;
                }
                YW(party)->count++;
                if (YW(party)->count % 10 == 0) {
                    psndSFXOn_3D(0x940, &party->position);
                }
                break;
            }
            if (party->field_34 == 8) {
                break;
            }
            if (yoshiGetStatus() == 1) {
                P_F32(party, 0xAC) = P_F32(mario, 0x174);
                P_F32(party, 0xB0) = P_F32(mario, 0x178);
                P_F32(party, 0xB4) = P_F32(mario, 0x17C);
            }
            if (party->flags & 2) {
                if (!(party->flags & 0x80000000)) {
                    if (MARIO_U16(party, 0x152) & 0x100) {
                        party->useMotionId = 20;
                        break;
                    }
                } else if (evt_yoshi_frm >= 0) {
                    party->useMotionId = 20;
                    break;
                }
            }
            if (party->flags & 0x80000000) {
                angle = P_F32(mario, 0x1A0);
                speed = evt_yoshi_spd;
            } else {
                L_getStick(party, &angle, &speed);
            }
            if (speed > 0.0f) {
                party->field_104 = speed;
                party->field_100 = angle;
                party->field_FC = angle;
                marioChgPose("M_Y_2");
                partyChgPose(party, "PYS_R_2");
                YW(party)->count++;
                if (YW(party)->count % 10 == 0) {
                    psndSFXOn_3D(0x940, &party->position);
                }
            } else {
                if (strcmp(party->field_18, "PYS_S_2")) {
                    MARIO_U16(mario, 0x28) = 0;
                }
                partyChgPose(party, "PYS_S_2");
                party->field_104 = 0.0f;
                YW(party)->count = 0;
            }
            inertia(party);
            party->position.x = P_F32(mario, 0x8C);
            party->position.z = P_F32(mario, 0x94);
            P_PTR(party, 0x12C) = NULL;
            P_PTR(party, 0x134) = NULL;
            mario->field_0x1E0 = NULL;
            mario->hitobjPush = NULL;
            mario->field_0x1F0 = NULL;
            dir = party->field_100;
            spd = party->field_104;
            L_searchHead(party);
            checkWall(party, spd, dir);
            SYNC_MARIO(mario, party);
            if (MARIO_U16(party, 0x152) & 0x600) {
                party->useMotionId = 100;
            }
            searchGround(party);
            P_F32(mario, 0x18C) = spd;
            break;
    }

    switch (party->useMotionId) {
        case 100:
            L_resetOfs(party);
            marioChgSmallJumpMotion();
            P_F32(mario, 0x180) = 0.0f;
            partyChgPose(party, "PYS_H_2");
            party->field_104 = 0.0f;
            party->useMotionId = 101;
            ADD_OFS(party);
            partyChkGnd(party);
            return;
        case 101:
            if (mario->hitobjStandOn == NULL) {
                ADD_OFS(party);
                partyChkGnd(party);
                return;
            }
            party->flags &= ~0x100;
            if (party->field_34 != 8) {
                partyChgRunMode(party, 2);
                party->field_3A[1] = 0;
            }
            ADD_OFS(party);
            partyChkGnd(party);
            if (party->useStruct) {
                __memFree(HEAP_DEFAULT, party->useStruct);
                party->useStruct = NULL;
            }
            return;
    }

    switch (party->useMotionId) {
        case 40:
            party->flags |= 0x40;
            P_F32(party, 0x114) = 0.0f;
            P_F32(party, 0x118) = 0.0f;
            P_F32(party, 0x11C) = 0.0f;
            P_S32(party, 0x24) = 3;
            P_F32(party, 0x114) = (P_F32(party, 0x120) - party->position.y) / P_S32(party, 0x24);
            party->useMotionId = 41;
        case 41:
            party->position.y += P_F32(party, 0x114);
            if (--P_S32(party, 0x24) <= 0) {
                party->flags &= ~0x40;
                party->useMotionId = 13;
            }
            break;
    }

    switch (party->useMotionId) {
        case 20:
            YW(party)->dir = (P_F32(mario, 0x1A8) >= 90.0f && P_F32(mario, 0x1A8) <= 270.0f) ? 1 : -1;
            mario->hitobjJumpFrom = mario->hitobjStandOn;
            mario->hitobjStandOn = NULL;
            *(Vec*)((u8*)mario + 0x11C) = party->position;
            partyChgPose(party, "PYS_F_1");
            marioChgPose("M_Y_3");
            P_S16(mario, 0x50) = 0;
            party->useMotionId = 21;
            party->field_104 += -0.01f;
            if (party->field_104 <= 0.0f) {
                party->field_104 = 0.0f;
            }
            YW(party)->angle = 1.0f;
            P_F32(mario, 0x2A0) = sin(3.141592653589793f * YW(party)->angle / 180.0f);
            P_F32(mario, 0x2A4) = 0.0f;
            P_F32(mario, 0x2A8) = party->position.y;
            party->yoshiPsndSFXId = psndSFXOn_3D(0x941, &party->position);
        case 21:
            {
                f32 s = sin(3.141592653589793f * YW(party)->angle / 180.0f);
                P_F32(mario, 0x2A0) = s * (YW(party)->angle <= 180.0f ? 0.5f : 0.37f);
            }
            P_F32(mario, 0x2A4) += P_F32(mario, 0x2A0);
            YW(party)->angle += 7.0f;
            if (YW(party)->angle >= 360.0f) {
                YW(party)->angle = 360.0f;
                party->useMotionId = 22;
            }
        case 22:
            {
                f32 y = 18.0f + party->position.y;
                f32 x = party->position.x;
                f32 z = party->position.z;
                if (YW(party)->effect == NULL) {
                    YW(party)->effect = effSweatN64Entry(1, x, y, z, 1.0f, 70.0f * (party->field_110 == 180.0f ? -1.0f : 1.0f), 0x16);
                    YW(party)->timer = 20;
                }
            }
            hit = partySearchGround(party, 11.0f, 11.0f);
            if (hit == NULL) {
                party->position.y = P_F32(mario, 0x2A8) + P_F32(mario, 0x2A4);
            } else {
                attr = hitGetAttr(hit);
                if (attr & 0x200) {
                    if (party->position.y <= P_F32(party, 0xE4)) {
                        party->useMotionId = 70;
                    }
                } else if (attr & 0xC00) {
                    if (party->position.y <= P_F32(party, 0xE4)) {
                        unk_800b474c(party);
                        return;
                    }
                }
                L_sweatEntry(party, NULL);
                P_F32(mario, 0x2A8) = P_F32(party, 0xE4);
                party->position.y = P_F32(party, 0xE4) + P_F32(mario, 0x2A4);
            }
            party->position.x = P_F32(mario, 0x8C);
            party->position.z = P_F32(mario, 0x94);
            if (party->flags & 0x80000000) {
                f32 s = evt_yoshi_spd;
                angle = P_F32(mario, 0x1A0);
                speed = s;
                party->field_104 = s;
            } else {
                L_getStick(party, &angle, &speed);
                L_yoshiFlyMove(party);
            }
            P_PTR(party, 0x12C) = NULL;
            P_PTR(party, 0x134) = NULL;
            dir = party->field_100;
            spd = party->field_104;
            L_searchHead(party);
            checkWall(party, spd, dir);
            if (party->field_138 == NULL && P_S16(mario, 0x50) >= 10) {
                searchGround2(party);
                if (party->field_138) {
                    mario->hitobjJumpFrom = NULL;
                    if (party->yoshiPsndSFXId != -1) {
                        psndSFXOff(party->yoshiPsndSFXId);
                        party->yoshiPsndSFXId = -1;
                    }
                    party->useMotionId = 10;
                    partyChgPose(party, "PYS_S_2");
                    marioChgPose("M_Y_2");
                    P_F32(mario, 0x2B0) = 0.0f;
                    P_F32(mario, 0x2B4) = 0.0f;
                    if (party->flags & 0x80000000) {
                        evt_yoshi_spd = 0.0f;
                        evt_yoshi_frm = -1;
                        party->field_104 = 0.0f;
                        party->useMotionId = 52;
                    }
                    break;
                }
                YW(party)->dir = 0;
            }
            SYNC_MARIO(mario, party);
            P_S16(mario, 0x50)++;
            if (P_S16(mario, 0x50) > 14) {
                if (party->flags & 0x80000000) {
                    if (P_S16(mario, 0x50) > 68) {
                        evt_yoshi_frm = 0;
                        P_F32(party, 0x114) = 0.0f;
                        P_F32(party, 0x11C) = -1.0f;
                        party->useMotionId = 50;
                    }
                } else if (P_S16(mario, 0x50) > 68 || !(MARIO_U16(party, 0x150) & 0x100) || marioKeyOffChk()) {
                    P_F32(party, 0x114) = 0.0f;
                    P_F32(party, 0x11C) = -1.0f;
                    party->useMotionId = 50;
                }
            }
            break;
    }

    unk_800b45e0(party);
    if (party->useMotionId == 13 || yoshiGetStatus() == 3 || yoshiGetStatus() == 4 || yoshiGetStatus() == 2) {
        ox = 0.0f;
        oz = 0.0f;
        movePos(&ox, &oz, -6.0f, toMovedir(party->field_10C));
        P_F32(mario, 0x98) = ox;
        P_F32(mario, 0xA0) = oz;
        P_F32(mario, 0xA8) = 8.0f + L_getOfs(party);
        extra = partyGetPtr(marioGetExtraPartyId());
        if (extra) {
            P_F32(extra, 0x80) = L_getOfs(party);
        }
    }

    switch (party->useMotionId) {
        case 60:
            party->field_104 = 0.0f;
            party->flags &= ~0x20;
            party->flags |= 0x10;
            P_S16(mario, 0x50) = 0;
            P_S16(mario, 0x52) = 0;
            P_PTR(party, 0x13C) = party->field_138;
            L_sweatEntry(party, NULL);
            mario->hitobjStandOn = NULL;
            *(Vec*)((u8*)mario + 0x11C) = *(Vec*)((u8*)mario + 0x8C);
            jumpheight = 100.0f;
            P_F32(mario, 0x128) = 0.0f;
            party->useMotionId = 61;
            P_S32(party, 0x24) = 0;
            P_F32(party, 0x11C) = marioJumpStandData[0];
            P_F32(party, 0x174) = marioJumpStandData[1];
            P_F32(party, 0x178) = marioJumpStandData[2];
            P_F32(party, 0x118) = marioJumpStandData[3];
        case 61:
            {
                f32 prev = P_F32(party, 0x11C);
                P_F32(party, 0x178) += P_F32(party, 0x118);
                P_F32(party, 0x174) += P_F32(party, 0x178);
                P_F32(party, 0x11C) += P_F32(party, 0x174);
                if (prev >= P_F32(party, 0x11C)) {
                    party->useMotionId = 62;
                }
            }
            party->position.y += P_F32(party, 0x11C);
            P_F32(mario, 0x128) += P_F32(party, 0x11C);
            break;
        case 62:
            party->position.y += P_F32(party, 0x11C);
            P_F32(mario, 0x128) += P_F32(party, 0x11C);
            if (P_F32(mario, 0x128) >= 0.7f * marioGetJumpHeight()) {
                party->useMotionId = 63;
            }
            break;
        case 63:
            P_F32(party, 0x11C) += 0.125f * (-1.0f - P_F32(party, 0x11C));
            party->position.y += P_F32(party, 0x11C);
            P_F32(mario, 0x128) += P_F32(party, 0x11C);
            if (P_F32(party, 0x11C) <= 0.0f) {
                party->useMotionId = 64;
                marioSetPeakYpos();
                P_F32(party, 0x11C) = -0.4f;
                P_F32(party, 0x174) = -0.4f;
                P_F32(party, 0x178) = 0.0f;
                P_F32(party, 0x118) = 0.0f;
                party->flags &= ~0x10;
                party->flags |= 0x20;
                party->useMotionId = 64;
            }
            break;
        case 64:
            P_F32(party, 0x178) += P_F32(party, 0x118);
            P_F32(party, 0x174) += P_F32(party, 0x178);
            P_F32(party, 0x11C) += P_F32(party, 0x174);
            if (P_F32(party, 0x11C) <= 0.0f) {
                marioSetPeakYpos();
                P_F32(party, 0x11C) = -0.4f;
                P_F32(party, 0x174) = -0.4f;
                P_F32(party, 0x178) = 0.0f;
                P_F32(party, 0x118) = 0.0f;
                party->flags &= ~0x10;
                party->flags |= 0x20;
                party->useMotionId = 65;
            }
            party->position.y += P_F32(party, 0x11C);
            break;
        case 65:
            if (--P_S32(party, 0x24) <= 0) {
                party->field_104 = 0.0f;
                P_F32(party, 0x114) = 0.0f;
                P_F32(party, 0x11C) = -1.0f;
                party->useMotionId = 50;
            }
            break;
    }

    if (party->useMotionId >= 64 && party->useMotionId <= 65) {
        P_S16(mario, 0x50)++;
        searchGround(party);
        if (party->field_138) {
            mario->hitobjJumpFrom = NULL;
            P_F32(party, 0x114) = 0.0f;
            P_F32(party, 0x11C) = -1.0f;
            party->useMotionId = 50;
        }
    }

    switch (party->useMotionId) {
        case 50:
        case 51:
            party->position.x = P_F32(mario, 0x8C);
            party->position.z = P_F32(mario, 0x94);
            if (party->flags & 0x80000000) {
                f32 s = evt_yoshi_spd;
                angle = P_F32(mario, 0x1A0);
                speed = s;
                party->field_104 = s;
            } else {
                L_getStick(party, &angle, &speed);
                L_yoshiFlyMove(party);
            }
            if (!(MARIO_U16(party, 0x150) & 0x100) || marioKeyOffChk()) {
                if (party->useMotionId == 50) {
                    party->useMotionId = 51;
                }
                {
                    MarioWork* m = marioGetPtr();
                    P_F32(m, 0x2A0) += P_F32(m, 0x2A4);
                }
            }
            if (P_F32(mario, 0x2A0) <= -10.0f) {
                P_F32(mario, 0x2A0) = -10.0f;
            }
            P_PTR(party, 0x12C) = NULL;
            P_PTR(party, 0x134) = NULL;
            mario->field_0x1E0 = NULL;
            mario->hitobjPush = NULL;
            mario->field_0x1F0 = NULL;
            dir = party->field_100;
            spd = party->field_104;
            L_searchHead(party);
            checkWall(party, spd, dir);
            searchGround(party);
            if (party->field_138) {
                mario->hitobjJumpFrom = NULL;
                party->useMotionId = 13;
                partyChgPose(party, "PYS_S_2");
                marioChgPose("M_Y_2");
                P_F32(mario, 0x2B0) = 0.0f;
                P_F32(mario, 0x2B4) = 0.0f;
                YW(party)->dir = 0;
                if (party->flags & 0x80000000) {
                    evt_yoshi_spd = 0.0f;
                    evt_yoshi_frm = -1;
                    party->field_104 = 0.0f;
                    party->useMotionId = 52;
                }
            }
            break;
        case 52:
            if (!(party->flags & 0x80000000)) {
                party->useMotionId = 13;
            }
            break;
    }

    L_sweatMain(party);
    if (party->useMotionId == 70) {
        if (marioChkDamageSink()) {
            party->position = *(Vec*)((u8*)party->playerPtr + 0x8C);
            return;
        }
        party->useMotionId = 71;
        return;
    }
    if (party->useMotionId == 71) {
        party->flags &= ~0x100;
        if (party->useStruct) {
            __memFree(HEAP_DEFAULT, party->useStruct);
            party->useStruct = NULL;
        }
        marioSetFallPara();
        marioChgMot(0x1F);
        partyChgRunMode(party, 0xd);
        extra = partyGetPtr(marioGetExtraPartyId());
        if (extra) {
            partyChgRunMode(extra, 0xd);
        }
        return;
    }
    if (party->useMotionId >= 10 && party->useMotionId <= 13 && mario->currMotionId != 0x1A) {
        party->flags &= ~0x100;
        if (party->useStruct) {
            __memFree(HEAP_DEFAULT, party->useStruct);
            party->useStruct = NULL;
        }
        partyChgRunMode(party, 2);
        party->field_3A[1] = 0;
        L_resetOfs(party);
        return;
    }
    ADD_OFS(party);
    P_F32(mario, 0xEC) = party->position.x;
    P_F32(mario, 0xF4) = party->position.z;
    P_F32(mario, 0x1A8) = party->field_10C;
    P_F32(mario, 0x1AC) = party->field_110;
    *(Vec*)((u8*)mario + 0x8C) = party->position;
    {
        Vec cam = party->position;
        marioUpdateCamCollision(&cam);
    }
}

void L_yoshiFlyMove(PartyEntry* party) {
    MarioWork* mario = marioGetPtr();
    f32 z;
    f32 x;
    f32 spd;
    f32 max;
    f32 one = 1.0f;

    inertia(party);
    z = -P_F32(mario, 0x2B4);
    x = P_F32(mario, 0x2B0);
    spd = 0.1f * distABf(0.0f, 0.0f, x, z);
    max = mario->mBaseDashSpeed * one;
    if (spd >= max) {
        spd = max;
    }
    z = angleABf(0.0f, 0.0f, x, z);
    if (spd < 0.01f) {
        spd = 0.0f;
    }
    party->field_104 = spd;
    if (spd) {
        party->field_100 = revise360(z + P_F32(party, 0xF8));
        party->field_FC = revise360(z + P_F32(party, 0xF8));
    }
    P_F32(mario, 0x18C) = spd;
}

void inertia(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 sx = P_S8(party, 0x158);
    f32 vx = P_F32(mario, 0x2B0);
    f32 vz = P_F32(mario, 0x2B4);
    f32 k;
    f32 lim = 16.0f;
    f32 acc = 0.01f;
    f32 zero = 0.0f;
    s32 dir;

    if (!sx) {
        k = -0.07f;
        if (mario->field_0x1F0) {
            if (lim) {
            }
            k = -0.5f;
        }
        vx = vx * k + vx;
        vz = vz * k + vz;
        if (__fabsf(vx) < 0.01f) {
            vx = 0.0f;
        }
        if (__fabsf(vz) < 0.01f) {
            vz = 0.0f;
        }
    } else if (vx * vx + vz * vz <= 256.0f) {
        dir = ((YoshiWork*)party->useStruct)->dir;
        vx += sx * acc;
        if (dir > 0 && vx <= 0.0f) {
            vx = 0.0f;
        }
        if (dir < 0 && vx >= 0.0f) {
            vx = 0.0f;
        }
        vz -= zero;
    } else {
        vz -= zero;
        vx += sx * acc;
        if (vx < -lim) {
            vx = -lim;
        }
        if (vx > lim) {
            vx = lim;
        }
        if (vz < -lim) {
            vz = -lim;
        }
        if (vz > lim) {
            vz = lim;
        }
    }
    P_F32(mario, 0x2B0) = vx;
    P_F32(mario, 0x2B4) = vz;
}

void searchGround(PartyEntry* party) {
    HitEntry* hit;
    MarioWork* mario;
    s32 attr;
    f32 groundY;
    f32 range;
    Vec pos;
    f32 stepY;
    f32 stepA;
    f32 stepB;
    f32 diff;
    void* step;

    mario = party->playerPtr;
    hit = NULL;
    if (!(party->flags & 0x2000000)) {
        range = __fabsf(P_F32(party, 0x11C));
        if (range < 1.0f) {
            range = 1.0f;
        }
        hit = partySearchGround(party, range, range);
        groundY = P_F32(party, 0xE4);
    }
    if (hit) {
        attr = hitGetAttr(hit);
        if (party->yoshiPsndSFXId != -1) {
            psndSFXOff(party->yoshiPsndSFXId);
            party->yoshiPsndSFXId = -1;
        }
        if (attr & 0x200) {
            if (!L_chgMotion(party, 70)) {
                return;
            }
            pos = party->position;
            marioSetSplash(0, &pos);
            L_sweatEntry(party, NULL);
            L_fall(party);
            party->position.y += P_F32(party, 0x11C);
            set_damage_root_ypos(P_F32(mario, 0x90) - 8.0f);
            L_resetOfs(party);
            party->flags |= 0x2000000;
            if (P_F32(party, 0x11C) <= -6.0f) {
                P_F32(party, 0x11C) = -6.0f;
                P_F32(party, 0x174) = 0.0f;
                P_F32(party, 0x178) = 0.0f;
                P_F32(party, 0x118) = 0.0f;
            }
            P_F32(mario, 0x7C) = P_F32(party, 0x11C);
            P_F32(mario, 0x80) = P_F32(party, 0x174);
            P_F32(mario, 0x84) = P_F32(party, 0x178);
            P_F32(mario, 0x88) = P_F32(party, 0x118);
            marioChgMot(0x1F);
            return;
        }
        if (attr & 0xC00) {
            unk_800b474c(party);
            partyChgRunMode(party, 0xd);
            {
                PartyEntry* extra = partyGetPtr(marioGetExtraPartyId());
                if (extra) {
                    partyChgRunMode(extra, 0xd);
                }
            }
            return;
        }
        if (hit && (hitGetAttr(hit) & 0x40000000)) {
            P_PTR(mario, 0x204) = hit;
        }
        if (!(party->flags & 0x30)) {
            step = partyChkFrontStep(party, 11.0f, &stepY, &stepA, &stepB);
            diff = stepY - party->position.y;
            if (step && diff <= 11.0f && diff >= 5.0f && P_F32(party, 0xE0) <= 30.0f) {
                P_F32(party, 0x120) = stepY;
                if (party->field_104) {
                    if (L_chgMotion(party, 40)) {
                        return;
                    }
                }
            }
        }
    }
    L_sweatEntry(party, hit);
    if (hit == NULL) {
        party->flags &= ~2;
        L_fall(party);
        party->position.y += P_F32(party, 0x11C);
    } else {
        party->flags |= 2;
        if (party->flags & 0x20) {
            party->flags &= ~0x70;
            mario->flags &= ~0xF0000;
            P_F32(party, 0x114) = 0.0f;
            party->position.y = groundY;
            if (party->yoshiPsndSFXId != -1) {
                psndSFXOff(party->yoshiPsndSFXId);
                party->yoshiPsndSFXId = -1;
            }
        } else {
            party->position.y = groundY;
        }
    }
}

void searchGround2(PartyEntry* party) {
    HitEntry* hit = NULL;
    MarioWork* mario = party->playerPtr;
    s32 attr;

    if (!(party->flags & 0x2000000)) {
        hit = partySearchGround(party, 11.0f, 0.0f);
    }
    if (hit == NULL) {
        L_sweatEntry(party, hit);
        return;
    }
    attr = hitGetAttr(hit);
    if (attr & 0x200) {
        Vec pos = party->position;
        marioSetSplash(0, &pos);
        L_sweatEntry(party, NULL);
        P_F32(party, 0x11C) = -0.4f;
        P_F32(party, 0x174) = -0.4f;
        P_F32(party, 0x178) = 0.0f;
        P_F32(party, 0x118) = 0.0f;
        P_F32(party, 0x178) += P_F32(party, 0x118);
        P_F32(party, 0x174) += P_F32(party, 0x178);
        P_F32(party, 0x11C) += P_F32(party, 0x174);
        if (P_F32(party, 0x11C) < -15.0f) {
            P_F32(party, 0x11C) = -15.0f;
        }
        party->position.y += P_F32(party, 0x11C);
        party->useMotionId = 70;
        return;
    }
    if (attr & 0x800) {
        unk_800b474c(party);
    }
    party->flags |= 2;
    P_F32(party, 0x114) = 0.0f;
    party->position.y = P_F32(party, 0xE4);
    party->flags &= ~0x70;
    mario->flags &= ~0xF0000;
}

static inline void L_searchHead(PartyEntry* party) {
    MarioWork* p = party->playerPtr;
    Vec pos = party->position;
    f32 height = partyGetHeight(party);

    P_PTR(p, 0x1F4) = marioSearchHead(&pos, 10.0f, &height);
}

void checkWall(PartyEntry* party, f32 spd, f32 dir) {
    MarioWork* mario = marioGetPtr();
    HitEntry* hit;
    Vec pos;
    s32 work1;
    s32 work2;
    s32 attr;

    pos = party->position;
    hit = partySearchWallFront(party, &pos, spd, dir);
    if (hit) {
        P_PTR(party, 0x12C) = hit;
        mario->field_0x1E0 = hit;
        if (spd) {
            if ((party->flags & 0x100) && marioChkBero(hit) == TRUE) {
                P_PTR(party, 0x134) = hit;
                mario->hitobjPush = hit;
                mario->field_0x1F0 = hit;
            } else {
                P_PTR(party, 0x134) = NULL;
                mario->hitobjPush = NULL;
                mario->field_0x1F0 = NULL;
            }
        }
        if (hitGetAttr(hit) & 0x800) {
            unk_800b474c(party);
        }
        attr = hitGetAttr(hit);
        if ((attr & 0x800004) && !(attr & 0x80080)) {
            movePos(&party->position.x, &party->position.z, spd, dir);
            return;
        }
        party->position = pos;
    } else if (!spd) {
        pos = party->position;
        hit = partySearchWallFront(party, &pos, spd, party->field_100);
        P_PTR(party, 0x12C) = hit;
        mario->field_0x1E0 = hit;
        if (hit == NULL) {
            f32 d = toMovedir(party->field_10C);
            pos = party->position;
            hit = partySearchWallFront(party, &pos, spd, d);
            P_PTR(party, 0x12C) = hit;
            mario->field_0x1E0 = hit;
        }
        if (MARIO_U16(party, 0x152) & 0x100) {
            pos = party->position;
            hit = partySearchWallFront(party, &pos, spd, party->field_100);
            if (hit == NULL) {
                P_PTR(party, 0x130) = hit;
                mario->field_0x1DC = hit;
            } else {
                P_PTR(party, 0x130) = P_PTR(party, 0x12C);
                mario->field_0x1DC = P_PTR(party, 0x12C);
            }
        }
        hit = dou10_yoko_yari2(&work1);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            unk_800b474c(party);
        }
    } else {
        hit = dou10_yoko_yari2(&work2);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            unk_800b474c(party);
        }
    }
    marioChkWallAround(&pos, 1, spd, dir, party->width, mario->wPlayerCollisionBox.y);
    party->position.x = pos.x;
    party->position.z = pos.z;
}

void L_getStick(PartyEntry* party, f32* angle, f32* speed) {
    s32 x;
    s32 y;
    MarioWork* mario = party->playerPtr;
    f32 dist;
    f32 ang;

    if (P_S8(mario, 0x39)) {
        *speed = 0.0f;
        *angle = party->field_FC;
        return;
    }
    y = -P_S8(party, 0x159);
    x = P_S8(party, 0x158);
    dist = distABf(0.0f, 0.0f, x, -y);
    if (dist >= 70.0f) {
        dist = 70.0f;
    }
    ang = angleABf(0.0f, 0.0f, x, -y);
    if (!dist) {
        ang = party->field_FC;
    }
    *angle = revise360(ang + P_F32(party, 0xF8));
    if (dist > 0.0f) {
        if (x * x + y * y > 3025) {
            dist = 1.5f * (mario->mBaseDashSpeed * marioGetMoveRate());
        } else {
            dist = 1.5f * (mario->mBaseWalkSpeed * marioGetMoveRate());
        }
        if (hitGetAttr(mario->hitobjStandOn) & 0x100) {
            mario->flags |= 0x4000000;
            dist *= 0.75f;
        } else {
            mario->flags &= ~0x4000000;
        }
        dist *= mario->playerGravity;
    }
    *speed = dist;
}
