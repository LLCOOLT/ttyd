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

static u8 gap_08_804188DC_sbss[4];  // .sbss pad after nokoSe
static s32 nokoSe;
double sin(double);
double cos(double);
#include "driver/hitdrv.h"
#include "mario/mario_sbr.h"

extern void itemNokoForceGet(ItemEntry* entry);
#include "eff/eff_kemu_test.h"
#include "eff/n64/eff_small_star_n64.h"
#include "mario/mariost.h"
void effKemuTestDrawCam();
EffectEntry* effKemuTestEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
EffectEntry* effSmallStarN64Entry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6,
                                  f32 arg7);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
s32 hitGetAttr(HitEntry* hit);
void marioChgMot(MarioMotion);
MarioWork* marioGetPtr(void);
void marioGetScreenPos(Vec position, f32* x, f32* y, f32* z);
void psndSFXOff(s32 id);
s32 psndSFXOn_3D(const char* name, Vec* position);
void sincosf(f32* ret_sin, f32* ret_cos, f32 degree);
f32 toMovedir(f32 angle);
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 vec3_802ce138[3];
extern const f64 double_to_int_802ce148;
extern const char str_802CE150[8];
extern const char str_802CE158[8];
extern const f64 double_180_802ce160;
extern const f32 float_3p1416_8041b510;
extern const f32 float_180_8041b514;
extern const f32 float_0p1_8041b518;
extern const f32 float_0_8041b51c;
extern const f32 float_neg1_8041b520;
extern const f32 float_1p5708_8041b524;
extern const f32 float_4p7124_8041b528;
extern const f32 float_90_8041b52c;
extern const f32 float_0p5_8041b530;
extern const f32 float_10_8041b534;
extern const f32 float_30_8041b538;
extern const f32 float_100_8041b53c;
extern const f32 float_11_8041b540;
extern const f32 float_6_8041b544;
extern const f32 float_1_8041b548;
extern const f32 float_0p4_8041b54c;
extern const f32 float_37_8041b550;
extern const f32 float_160_8041b554;
extern const f32 float_18p5_8041b558;
extern const f32 float_2_8041b55c;
extern const f32 float_45_8041b560;
extern const f32 float_6p2832_8041b564;
extern const f32 float_360_8041b568;
extern const f32 float_50_8041b56c;
extern const f32 float_0p25_8041b570;
extern const f32 float_0p3_8041b574;
extern const f32 float_12_8041b578;
extern const f32 float_120_8041b57c;
extern const f32 float_0p15_8041b580;
extern const f32 float_20_8041b584;
extern const f32 float_2p2_8041b588;
extern const f32 float_neg2_8041b58c;
extern const f32 float_0p2_8041b590;
extern const f32 float_135_8041b594;
extern const f32 float_315_8041b598;
extern const f32 float_225_8041b59c;
extern const f32 float_270_8041b5a0;
extern const f32 float_4_8041b5a4;
extern const f32 float_5_8041b5a8;
extern const f32 float_neg90_8041b5ac;
extern const f32 float_75_8041b5b0;
extern const f32 float_3_8041b5b4;
extern const f32 float_18_8041b5b8;
extern const f32 float_0p35_8041b5bc;
extern const f32 float_15_8041b5c0;
extern const f32 float_neg300_8041b5c4;
extern const f32 float_neg30_8041b5c8;
extern const f32 float_1000_8041b5cc;
extern const f32 float_240_8041b5d0;
extern const f32 float_neg6_8041b5d4;
extern const f32 float_neg2000_8041b5d8;
extern const f32 float_200_8041b5dc;
extern const f32 float_24_8041b5e0;
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
    party->height = EXT_LIT(float_37_8041b550, 37.0f);
    party->width = EXT_LIT(float_24_8041b5e0, 24.0f);
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
            party->height = EXT_LIT(float_37_8041b550, 37.0f);
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
    party->height = EXT_LIT(float_37_8041b550, 37.0f);
    PW(party, 0x178) = 0;
    PW(party, 0x17c) = 0;
    PW(party, 0x180) = 0;
}

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
    if (revise360(party->targetDir - PF(party, 0xf8)) > EXT_LIT(float_180_8041b514, 180.0f)) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    party->displayDirection = revise360(EXT_LIT(float_50_8041b56c, 50.0f) * dir + party->displayDirection);
}

static inline void noko_star(PartyEntry* party, s32 n) {
    f32 c = (f32)cos(6.2831855f * party->targetDir / 360.0f);
    f32 s = (f32)sin(EXT_LIT(float_6p2832_8041b564, 6.2831855f) * party->targetDir / EXT_LIT(float_360_8041b568, 360.0f));
    effSmallStarN64Entry(3, n, party->position.x, party->position.y + party->height, party->position.z, s, EXT_LIT(float_neg1_8041b520, -1.0f), -c);
}

#define NOKO_ITEM(party, body)                                                                              if (PW(party, 0x174) == 0) {                                                                                  PW(party, 0x174) = (u32)itemNearDistCheck(party->position.x, party->position.y, party->position.z,                                                   0.5f * party->width + 12.0f);                                    if (PW(party, 0x174) != 0) {                                                                                  itemPickUp((ItemEntry*)PW(party, 0x174));                                                                 body                                                                                                  }                                                                                                     }
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
            movePos(&mx, &mz, EXT_LIT(float_160_8041b554, 160.0f), angleABf(mario->position.x, mario->position.z, party->position.x, party->position.z));
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
        party->height = EXT_LIT(float_18p5_8041b558, 18.5f);
        party->useMotionId = 1;
        party->moveFrames = 100;
        PW(party, 0x174) = 0;
        PH(party, 0x17c) = 0;
        marioAdjustMoveDir();
        mario->baseSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        PV(party, 0x94) = mario->position;
        movePos(&party->moveTarget.x, &party->moveTarget.z, EXT_LIT(float_2_8041b55c, 2.0f), toMovedirSimple(mario->displayDirectionTarget));
        party->moveFrames = 4;
        party->velY = EXT_LIT(float_0_8041b51c, 0.0f);
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        party->moveSpeed = distABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z) /
                           (f32)party->moveFrames;
        party->displayDirection = revise360(EXT_LIT(float_45_8041b560, 45.0f) + party->displayDirection);
        party->useMotionId = 1;
        marioChgSmallJumpMotion();
        mario->trigFlags |= 0x20000;
        mario->baseSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        break;
    case 1:
        if (mario->currMotionId == 0x20 || mario->currMotionId == 0x1f) {
            party->useMotionId = 70;
            break;
        }
        party->displayDirection = revise360(EXT_LIT(float_45_8041b560, 45.0f) + party->displayDirection);
        party->position.x += (PV(party, 0x94).x - party->position.x) / (f32)party->moveFrames;
        party->position.y += (PV(party, 0x94).y - party->position.y) / (f32)party->moveFrames;
        party->position.z += (PV(party, 0x94).z - party->position.z) / (f32)party->moveFrames;
        if (--party->moveFrames > 0) {
            break;
        }
        party->position = PV(party, 0x94);
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
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
        mario->baseSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        party->useMotionId = 10;
        party->moveFrames = 15;
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        party->moveDistance = EXT_LIT(float_0_8041b51c, 0.0f);
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
        party->moveSpeed += EXT_LIT(float_2_8041b55c, 2.0f);
        if (party->moveSpeed > EXT_LIT(float_10_8041b534, 10.0f)) {
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
        if (party->moveDistance >= EXT_LIT(float_120_8041b57c, 120.0f)) {
            party->useMotionId = 12;
            party->moveSpeed += EXT_LIT(float_0p15_8041b580, 0.15f) * (EXT_LIT(float_neg1_8041b520, -1.0f) - party->moveSpeed);
            if (party->moveSpeed <= EXT_LIT(float_0_8041b51c, 0.0f)) {
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
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        psndSFXOn_3D((const char*)0x92b, &party->position);
        break;
    case 51: {
        f32 lim = PH(party, 0x17c) != 0 ? 20.0f : 10.0f;
        party->moveSpeed += EXT_LIT(float_0p3_8041b574, 0.3f) * (lim - party->moveSpeed);
        if (party->moveSpeed >= lim) {
            party->moveSpeed = lim;
            if ((*(f32*)new_var) < EXT_LIT(float_10_8041b534, 10.0f)) {
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
        party->moveSpeed += EXT_LIT(float_0p1_8041b518, 0.1f) * (EXT_LIT(float_neg1_8041b520, -1.0f) - party->moveSpeed);
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= EXT_LIT(float_0_8041b51c, 0.0f)) {
            (*(f32*)new_var) = 0.0f;
            party->useMotionId = 53;
            party->moveSpeed += EXT_LIT(float_0p1_8041b518, 0.1f) * (EXT_LIT(float_neg1_8041b520, -1.0f) - party->moveSpeed);
            PF(party, 0x178) = EXT_LIT(float_50_8041b56c, 50.0f);
        }
        break;
    case 53:
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 70;
            return;
        }
        PF(party, 0x178) -= EXT_LIT(float_2p2_8041b588, 2.2f);
        if (PF(party, 0x178) <= EXT_LIT(float_0_8041b51c, 0.0f)) {
            PF(party, 0x178) = 0.0f;
        }
        noko_spin(party);
        party->moveSpeed += (EXT_LIT(float_neg2_8041b58c, -2.0f) - party->moveSpeed) * (PH(party, 0x17c) != 0 ? EXT_LIT(float_0p2_8041b590, 0.2f) : EXT_LIT(float_0p1_8041b518, 0.1f));
        (*(f32*)new_var) -= party->moveSpeed;
        if (party->moveSpeed <= EXT_LIT(float_0_8041b51c, 0.0f)) {
            party->moveSpeed = 0.0f;
            flags = lookupSafetyPos(PV(party, 0x94), party->height, &out);
            if (party->field_138 != NULL && ((u32)(flags - 1) <= 1 || flags == 4 || flags == 8)) {
                party->useMotionId = 70;
                break;
            }
            switch (flags) {
            case 3:
                lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_135_8041b594, 135.0f), &out);
                break;
            case 5:
                lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_315_8041b598, 315.0f), &out);
                break;
            case 10:
                lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_225_8041b59c, 225.0f), &out);
                break;
            case 12:
                lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_315_8041b598, 315.0f), &out);
                break;
            case 7:
            case 14:
            case 15:
                party->useMotionId = 70;
                break;
            case 1:
                lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_270_8041b5a0, 270.0f), &out);
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
        party->moveSpeed += EXT_LIT(float_0p5_8041b530, 0.5f);
        if (party->moveSpeed >= EXT_LIT(float_4_8041b5a4, 4.0f)) {
            party->moveSpeed = 4.0f;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= EXT_LIT(float_10_8041b534, 10.0f)) {
            party->useMotionId = 70;
            party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
            return;
        }
        break;
    case 55:
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 70;
            return;
        }
        noko_spin(party);
        PF(party, 0x178) -= EXT_LIT(float_2p2_8041b588, 2.2f);
        if (PF(party, 0x178) <= EXT_LIT(float_0_8041b51c, 0.0f)) {
            PF(party, 0x178) = 0.0f;
        }
        party->moveSpeed += (EXT_LIT(float_neg2_8041b58c, -2.0f) - party->moveSpeed) * (PH(party, 0x17c) != 0 ? EXT_LIT(float_0p2_8041b590, 0.2f) : EXT_LIT(float_0p1_8041b518, 0.1f));
        if (party->moveSpeed <= EXT_LIT(float_0_8041b51c, 0.0f)) {
            party->useMotionId = 70;
            party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
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
        if ((f32)sqrt(qz + (qx + qy)) < EXT_LIT(float_5_8041b5a8, 5.0f)) {
            f32 a;
            a = mario->directionView + (mario->directionView >= EXT_LIT(double_180_802ce160, 180.0) ? EXT_LIT(float_neg90_8041b5ac, -90.0f) : EXT_LIT(float_90_8041b52c, 90.0f));
            movePos(&party->position.x, &party->position.z, EXT_LIT(float_0p5_8041b530, 0.5f) * mario->wPlayerCollisionBox.x, a);
            ccwall(party, 1);
        }
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
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
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        party->targetDir = angleABf(party->position.x, party->position.z, PV(party, 0x94).x, PV(party, 0x94).z);
        (*(f32*)new_var) += EXT_LIT(float_75_8041b5b0, 75.0f);
        psndSFXOn_3D((const char*)0x92b, &party->position);
    case 81:
        noko_spin(party);
        party->moveSpeed += EXT_LIT(float_3_8041b5b4, 3.0f);
        if (party->moveSpeed >= EXT_LIT(float_18_8041b5b8, 18.0f)) {
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
        if ((*(f32*)new_var) <= EXT_LIT(float_20_8041b584, 20.0f)) {
            party->useMotionId = 82;
        }
        break;
    case 82:
        noko_spin(party);
        party->moveSpeed += EXT_LIT(float_0p35_8041b5bc, 0.35f) * (EXT_LIT(float_neg1_8041b520, -1.0f) - party->moveSpeed);
        NOKO_ITEM(party, psndSFXOn_3D((const char*)0x92c, &party->position); noko_star(party, 1);)
        if (ccwall(party, 1) != NULL) {
            party->useMotionId = 100;
            break;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= EXT_LIT(float_0_8041b51c, 0.0f)) {
            (*(f32*)new_var) = distABf(PV(party, 0x94).x, PV(party, 0x94).z, party->position.x, party->position.z);
            party->useMotionId = 84;
            PF(party, 0x178) = EXT_LIT(float_50_8041b56c, 50.0f);
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
        if ((*(f32*)new_var) <= EXT_LIT(float_30_8041b538, 30.0f)) {
            party->useMotionId = 86;
            party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
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
        if ((f32)sqrt(qz + (qx + qy)) < EXT_LIT(float_5_8041b5a8, 5.0f)) {
            f32 a;
            a = mario->directionView + (mario->directionView >= EXT_LIT(double_180_802ce160, 180.0) ? EXT_LIT(float_90_8041b52c, 90.0f) : EXT_LIT(float_neg90_8041b5ac, -90.0f));
            movePos(&party->position.x, &party->position.z, EXT_LIT(float_0p5_8041b530, 0.5f) * mario->wPlayerCollisionBox.x, a);
            ccwall(party, 1);
        }
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
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
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        flags = lookupSafetyPos(PV(party, 0x94), party->height, &out2);
        if (party->field_138 != NULL && ((u32)(flags - 1) <= 1 || flags == 4 || flags == 8)) {
            party->useMotionId = 70;
            break;
        }
        switch (flags) {
        case 3:
            lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_135_8041b594, 135.0f), &out2);
            break;
        case 5:
            lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_315_8041b598, 315.0f), &out2);
            break;
        case 10:
            lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_225_8041b59c, 225.0f), &out2);
            break;
        case 12:
            lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_315_8041b598, 315.0f), &out2);
            break;
        case 7:
        case 14:
        case 15:
            party->useMotionId = 70;
            break;
        case 1:
            lookupSafetyPosSub(PV(party, 0x94), party->height, EXT_LIT(float_270_8041b5a0, 270.0f), &out2);
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
        PF(party, 0x178) = EXT_LIT(float_50_8041b56c, 50.0f);
        break;
    case 90:
        noko_spin(party);
        party->moveSpeed += EXT_LIT(float_0p5_8041b530, 0.5f);
        if (party->moveSpeed >= EXT_LIT(float_4_8041b5a4, 4.0f)) {
            party->moveSpeed = 4.0f;
        }
        (*(f32*)new_var) -= party->moveSpeed;
        if ((*(f32*)new_var) <= EXT_LIT(float_10_8041b534, 10.0f)) {
            party->useMotionId = 70;
            party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        }
        break;
    case 110:
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        party->velY = EXT_LIT(float_15_8041b5c0, 15.0f);
        party->accelY = EXT_LIT(float_0_8041b51c, 0.0f);
        party->moveFrames = sysMsec2Frame(1000);
        party->useMotionId = 111;
    case 111:
        party->position.y += party->velY;
        marioGetScreenPos(party->position, &s2x, &s2y, &s2z);
        if (s2y <= EXT_LIT(float_neg300_8041b5c4, -300.0f)) {
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
            if (mario->displayDirectionTarget >= EXT_LIT(float_90_8041b52c, 90.0f) && mario->displayDirectionTarget <= EXT_LIT(float_270_8041b5a0, 270.0f)) {
                b = TRUE;
            }
            movePos(&rp.x, &rp.z, EXT_LIT(float_30_8041b538, 30.0f), toMovedir2(b ? EXT_LIT(float_0_8041b51c, 0.0f) : EXT_LIT(float_180_8041b514, 180.0f), EXT_LIT(float_neg30_8041b5c8, -30.0f)));
        }
        party->position.x = rp.x;
        party->position.y = EXT_LIT(float_1000_8041b5cc, 1000.0f) + rp.y;
        party->position.z = rp.z;
        party->velY = EXT_LIT(float_0_8041b51c, 0.0f);
        party->accelY = EXT_LIT(float_neg1_8041b520, -1.0f);
        party->moveSpeed = EXT_LIT(float_0_8041b51c, 0.0f);
        party->flags |= 0x20;
        party->flags |= 0x02000000;
        party->flags &= ~0x04000000;
        party->flags &= ~0x01000000;
        party->flags2 &= ~0x20;
        party->flags2 &= ~0x10;
        party->height = EXT_LIT(float_37_8041b550, 37.0f);
        party->useMotionId = 113;
        break;
    case 113:
        marioGetScreenPos(party->position, &s3x, &s3y, &s3z);
        if (s3y > EXT_LIT(float_240_8041b5d0, 240.0f)) {
            party->flags &= ~0x02000000;
        }
        partyMove(party);
        if (party->velY <= EXT_LIT(float_neg6_8041b5d4, -6.0f)) {
            party->accelY = 0.0f;
            party->velY = EXT_LIT(float_neg6_8041b5d4, -6.0f);
        }
        if (party->position.y < EXT_LIT(float_neg2000_8041b5d8, -2000.0f)) {
            party->position = mario->position;
            party->position.y += EXT_LIT(float_200_8041b5dc, 200.0f);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void nokonoko_use(PartyEntry* party) {
	char _af_pad[340];
	asm volatile {
		mr r29, r3
		lis r3, vec3_802ce138@ha
		opword 0x801D0000
		addi r31, r3, vec3_802ce138@l
		opword 0x83DD0160
		opword 0x54000001
		opword 0x408200BC
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x418200B0
		opword 0x80FD0058
		la r3, _af_pad+268
		opword 0x801D005C
		opword 0x38810038
		opword 0x38A10034
		opword 0x38C10030
		opword 0x90E10114
		opword 0x90010118
		opword 0x801D0060
		opword 0x9001011C
		bl marioGetScreenPos
		opword 0xC0210038
		opword 0xC0010034
		opword 0xFC20081E
		opword 0xFC00001E
		opword 0xD8210148
		opword 0xD8010150
		opword 0x8061014C
		opword 0x80810154
		bl marioChkInScreen
		opword 0x2C030000
		opword 0x40820058
		opword 0xC01E008C
		opword 0xD001002C
		opword 0xC01E0094
		opword 0xD0010028
		opword 0xC03E008C
		opword 0xC05E0094
		opword 0xC07D0058
		opword 0xC09D0060
		bl angleABf
		opword 0xFC400890
		lfs f1, float_160_8041b554(r2)
		opword 0x3861002C
		opword 0x38810028
		bl movePos
		opword 0xC001002C
		opword 0x7FA3EB78
		opword 0xD01D0058
		opword 0xC0010028
		opword 0xD01D0060
		bl nokonoko_finish
		opword 0x48001D44
		opword 0x807D0008
		opword 0x54600739
		opword 0x4182005C
		opword 0x54630776
		opword 0x38000000
		opword 0x907D0008
		opword 0x901D0174
		opword 0x901D0178
		opword 0x901D017C
		opword 0x901D0180
		opword 0x801D0000
		opword 0x54000001
		opword 0x41820020
		opword 0x801D016C
		opword 0x2C000000
		opword 0x40810020
		opword 0xA81D017E
		opword 0x60000001
		opword 0xB01D017E
		opword 0x48000010
		opword 0xA81D017E
		opword 0x5400003C
		opword 0xB01D017E
		opword 0x38000000
		opword 0x981D0039
		opword 0x881D0039
		opword 0x28000015
		opword 0x41810A38
		lis r3, jumptable_803137C4@ha
		opword 0x5400103A
		addi r3, r3, jumptable_803137C4@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xA01E002E
		opword 0x28000020
		opword 0x4182000C
		opword 0x2800001F
		opword 0x40820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x48000A00
		opword 0x7FA3EB78
		bl partyClearJumpPara
		opword 0x801D0000
		opword 0x7FA3EB78
		opword 0x389F0018
		opword 0x64000400
		opword 0x901D0000
		opword 0x801D0004
		opword 0x60000010
		opword 0x901D0004
		bl partyChgPose
		lfs f0, float_18p5_8041b558(r2)
		opword 0x38800001
		opword 0x38600064
		opword 0x38000000
		opword 0xD01D00F0
		opword 0x989D0039
		opword 0x907D0024
		opword 0x901D0174
		opword 0xB01D017C
		bl marioAdjustMoveDir
		lfs f0, float_0_8041b51c(r2)
		opword 0xD01E0180
		opword 0x807E008C
		opword 0x801E0090
		opword 0x907D0094
		opword 0x901D0098
		opword 0x801E0094
		opword 0x901D009C
		opword 0xC03E01AC
		bl toMovedirSimple
		opword 0xFC400890
		lfs f1, float_2_8041b55c(r2)
		opword 0x387D0094
		opword 0x389D009C
		bl movePos
		opword 0x38000004
		lfs f0, float_0_8041b51c(r2)
		opword 0x901D0024
		opword 0xD01D0114
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl distABf
		opword 0x807D0024
		opword 0x3C004330
		opword 0x90010150
		opword 0x6C608000
		opword 0xC87F0010
		opword 0x90010154
		lfs f2, float_45_8041b560(r2)
		opword 0xC8010150
		opword 0xEC001828
		opword 0xEC010024
		opword 0xD01D0104
		opword 0xC01D010C
		opword 0xEC22002A
		bl revise360
		opword 0xD03D010C
		opword 0x38000001
		opword 0x981D0039
		bl marioChgSmallJumpMotion
		opword 0x801E000C
		lfs f0, float_0_8041b51c(r2)
		opword 0x64000002
		opword 0x901E000C
		opword 0xD01E0180
		opword 0x480008D4
		opword 0xA01E002E
		opword 0x28000020
		opword 0x4182000C
		opword 0x2800001F
		opword 0x40820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x480008B4
		lfs f1, float_45_8041b560(r2)
		opword 0xC01D010C
		opword 0xEC21002A
		bl revise360
		opword 0xD03D010C
		opword 0x3C004330
		opword 0xC87F0010
		opword 0x807D0024
		opword 0x90010150
		opword 0x6C638000
		opword 0xC05D0058
		opword 0x90610154
		opword 0xC03D0094
		opword 0xC8010150
		opword 0xEC211028
		opword 0x90010148
		opword 0xEC001828
		opword 0x90010158
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xD01D0058
		opword 0x801D0024
		opword 0xC05D005C
		opword 0x6C008000
		opword 0xC01D0098
		opword 0x9001014C
		opword 0xEC201028
		opword 0xC8010148
		opword 0xEC001828
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xD01D005C
		opword 0x801D0024
		opword 0xC05D0060
		opword 0x6C008000
		opword 0xC01D009C
		opword 0x9001015C
		opword 0xEC201028
		opword 0xC8010158
		opword 0xEC001828
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xD01D0060
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x418107F8
		opword 0x80DD0094
		opword 0x38000002
		opword 0x80BD0098
		opword 0x7FA3EB78
		lfs f0, float_0_8041b51c(r2)
		opword 0x389F0020
		opword 0x90DD0058
		opword 0x90BD005C
		opword 0x80BD009C
		opword 0x90BD0060
		opword 0xD01D0104
		opword 0xC01E01AC
		opword 0xD01D0110
		opword 0xC01E01AC
		opword 0xD01D010C
		opword 0x981D0039
		bl partyChgPose
		opword 0xA01E002E
		opword 0x28000020
		opword 0x4182000C
		opword 0x2800001F
		opword 0x40820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x48000794
		opword 0x801E01E4
		opword 0x28000000
		opword 0x41820788
		opword 0x38600003
		bl marioChgMot
		opword 0x809E0000
		opword 0x3860000A
		lfs f0, float_0_8041b51c(r2)
		opword 0x3800000F
		opword 0x60840080
		opword 0x909E0000
		opword 0xD01E0180
		opword 0x987D0039
		opword 0x901D0024
		opword 0xD01D0104
		opword 0xD01D0128
		opword 0xC03E01AC
		bl toMovedir
		opword 0xD03D0100
		opword 0x389D0058
		opword 0x3860092D
		bl psndSFXOn_3D
		opword 0x48000738
		opword 0x389D0058
		opword 0x3860092A
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		frsp f31, f1
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800003
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		opword 0x807D0000
		opword 0x3800000B
		opword 0x64630400
		opword 0x907D0000
		opword 0x807D0000
		opword 0x64630100
		opword 0x907D0000
		opword 0x981D0039
		opword 0xC05D0104
		lfs f1, float_2_8041b55c(r2)
		lfs f0, float_10_8041b534(r2)
		opword 0xEC22082A
		opword 0xD03D0104
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01D0104
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lwz r3, gp(r13)
		opword 0x8003001C
		opword 0x540007FF
		opword 0x41820030
		opword 0xC07D00F0
		opword 0x38600000
		lfs f2, float_0p25_8041b570(r2)
		opword 0xC01D005C
		opword 0xC03D0058
		opword 0xEC4300BA
		opword 0xC07D0060
		lfs f4, float_0p3_8041b574(r2)
		bl effKemuTestEntry
		opword 0x809D0164
		bl effKemuTestDrawCam
		opword 0xC03D0128
		opword 0xC01D0104
		opword 0xEC01002A
		opword 0xD01D0128
		opword 0x801D0174
		opword 0x28000000
		opword 0x408200B0
		lfs f3, float_0p5_8041b530(r2)
		opword 0xC05D00F4
		lfs f0, float_12_8041b578(r2)
		opword 0xC03D0058
		opword 0xEC8300BA
		opword 0xC05D005C
		opword 0xC07D0060
		bl itemNearDistCheck
		opword 0x907D0174
		opword 0x807D0174
		opword 0x28030000
		opword 0x41820080
		bl itemPickUp
		opword 0x38000032
		opword 0x389D0058
		opword 0x981D0039
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		opword 0x48000548
		opword 0x7FA3EB78
		opword 0x38800000
		bl ccwall
		opword 0x28030000
		opword 0x4182007C
		opword 0x38000032
		opword 0x389D0058
		opword 0x981D0039
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		opword 0x480004BC
		opword 0xC03D0128
		lfs f0, float_120_8041b57c(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x408204A8
		opword 0x3800000C
		lfs f1, float_neg1_8041b520(r2)
		opword 0x981D0039
		lfs f3, float_0p15_8041b580(r2)
		opword 0xC05D0104
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC211028
		opword 0xEC23107A
		opword 0xD03D0104
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820474
		opword 0xD01D0104
		opword 0x801D0000
		opword 0x54000001
		opword 0x40820030
		opword 0xA01E0246
		opword 0x5400056B
		opword 0x41820018
		opword 0x3860000D
		opword 0x38000000
		opword 0x987D0039
		opword 0x901D0024
		opword 0x48000444
		opword 0x38000032
		opword 0x981D0039
		opword 0x48000438
		opword 0xA81D017E
		opword 0x540007FF
		opword 0x41820040
		opword 0x38000005
		opword 0x38600015
		opword 0x901D0024
		opword 0x38000001
		opword 0x987D0039
		opword 0xB01D017C
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x40820404
		opword 0x389D0058
		opword 0x3860092E
		bl psndSFXOn_3D
		stw r3, nokoSe(r13)
		opword 0x480003F0
		opword 0x38000032
		opword 0x981D0039
		opword 0x480003E4
		opword 0x807D0024
		opword 0x38030001
		opword 0x2C000005
		opword 0x901D0024
		opword 0x4180003C
		opword 0x38000005
		opword 0x38600014
		opword 0x901D0024
		opword 0x38000001
		opword 0x987D0039
		opword 0xB01D017C
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x40820014
		opword 0x389D0058
		opword 0x3860092E
		bl psndSFXOn_3D
		stw r3, nokoSe(r13)
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		opword 0x3C608889
		opword 0x38038889
		lwz r3, gp(r13)
		opword 0x8063001C
		opword 0x7C001816
		opword 0x5400E13E
		opword 0x1C00001E
		opword 0x7C001851
		opword 0x40820024
		opword 0xC03D0058
		opword 0x38600005
		opword 0xC05D005C
		opword 0xC07D0060
		lfs f4, float_1_8041b548(r2)
		bl effKemuTestEntry
		opword 0x809D0164
		bl effKemuTestDrawCam
		opword 0x7FA3EB78
		opword 0x38800000
		bl ccwall
		opword 0x28030000
		opword 0x4182009C
		opword 0x38000032
		opword 0x389D0058
		opword 0x981D0039
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		bl marioGetPtr
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x4182027C
		bl psndSFXOff
		opword 0x3800FFFF
		stw r0, nokoSe(r13)
		opword 0x4800026C
		opword 0x801D0174
		opword 0x28000000
		opword 0x408200D0
		lfs f3, float_0p5_8041b530(r2)
		opword 0xC05D00F4
		lfs f0, float_12_8041b578(r2)
		opword 0xC03D0058
		opword 0xEC8300BA
		opword 0xC05D005C
		opword 0xC07D0060
		bl itemNearDistCheck
		opword 0x907D0174
		opword 0x807D0174
		opword 0x28030000
		opword 0x418200A0
		bl itemPickUp
		opword 0x38000032
		opword 0x389D0058
		opword 0x981D0039
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		bl marioGetPtr
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x418201A4
		bl psndSFXOff
		opword 0x3800FFFF
		stw r0, nokoSe(r13)
		opword 0x48000194
		opword 0x801D0000
		opword 0x54000001
		opword 0x408200C4
		opword 0xA07E002E
		opword 0x28030019
		opword 0x41820044
		opword 0x28030014
		opword 0x4182003C
		opword 0x28030018
		opword 0x41820034
		opword 0x28030016
		opword 0x4182002C
		opword 0x3803FFE1
		opword 0x5400043E
		opword 0x28000001
		opword 0x4081001C
		opword 0x801E0000
		opword 0x540006B5
		opword 0x40820010
		bl marioChkKey
		opword 0x2C030000
		opword 0x40820030
		opword 0x7FA3EB78
		bl nokonoko_finish
		bl marioGetPtr
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820120
		bl psndSFXOff
		opword 0x3800FFFF
		stw r0, nokoSe(r13)
		opword 0x48000110
		opword 0xA01E0246
		opword 0x5400056B
		opword 0x40820104
		opword 0xA81D017C
		opword 0x38600032
		opword 0x2C000000
		opword 0x41820008
		opword 0x38600050
		opword 0x987D0039
		bl marioGetPtr
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x418200D8
		bl psndSFXOff
		opword 0x3800FFFF
		stw r0, nokoSe(r13)
		opword 0x480000C8
		opword 0xA81D017E
		opword 0x540007FF
		opword 0x41820010
		opword 0x38000050
		opword 0x981D0039
		opword 0x4800000C
		opword 0x38000032
		opword 0x981D0039
		bl marioGetPtr
		lwz r3, nokoSe(r13)
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820094
		bl psndSFXOff
		opword 0x3800FFFF
		stw r0, nokoSe(r13)
		opword 0x48000084
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		opword 0x3C608889
		opword 0x38038889
		lwz r3, gp(r13)
		opword 0x8063001C
		opword 0x7C001816
		opword 0x5400E13E
		opword 0x1C00001E
		opword 0x7C001851
		opword 0x40820024
		opword 0xC03D0058
		opword 0x38600005
		opword 0xC05D005C
		opword 0xC07D0060
		lfs f4, float_1_8041b548(r2)
		bl effKemuTestEntry
		opword 0x809D0164
		bl effKemuTestDrawCam
		opword 0x887D0039
		opword 0x3803FFCE
		opword 0x28000015
		opword 0x41810760
		lis r3, jumptable_8031376C@ha
		opword 0x5400103A
		addi r3, r3, jumptable_8031376C@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7FA3EB78
		bl partyClearJumpPara
		opword 0x38000033
		lfs f0, float_0_8041b51c(r2)
		opword 0x981D0039
		opword 0xD01D0104
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x389D0058
		opword 0x3860092B
		bl psndSFXOn_3D
		opword 0x48000708
		opword 0xA81D017C
		opword 0x2C000000
		opword 0x4182000C
		lfs f3, float_20_8041b584(r2)
		opword 0x48000008
		lfs f3, float_10_8041b534(r2)
		opword 0xC03D0104
		lfs f2, float_0p3_8041b574(r2)
		opword 0xEC030828
		opword 0xEC02083A
		opword 0xD01D0104
		opword 0xC01D0104
		opword 0xFC001840
		opword 0x4C411382
		opword 0x40820020
		opword 0xD07D0104
		lfs f0, float_10_8041b534(r2)
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000034
		opword 0x981D0039
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x28030000
		opword 0x418200A8
		opword 0x7FA3EB78
		opword 0x38810024
		opword 0x38A10020
		bl partyGetMoveDirSpd
		opword 0xC0210020
		opword 0x387D0058
		opword 0xC0410024
		opword 0x38800001
		opword 0xC07D00F4
		opword 0xC09D00F0
		bl marioChkWallAround
		opword 0x38000046
		opword 0x389D0058
		opword 0x981D0039
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		opword 0x48001128
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f3, float_neg1_8041b520(r2)
		opword 0xC05D0104
		lfs f4, float_0p1_8041b518(r2)
		opword 0xEC231028
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC24107A
		opword 0xD03D0104
		opword 0xC05D0128
		opword 0xC03D0104
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820580
		opword 0xD01D0128
		opword 0x38000035
		lfs f0, float_50_8041b56c(r2)
		opword 0x981D0039
		opword 0xC05D0104
		opword 0xEC231028
		opword 0xEC24107A
		opword 0xD03D0104
		opword 0xD01D0178
		opword 0x48000558
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x28030000
		opword 0x41820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x48001068
		opword 0xC05D0178
		lfs f1, float_2p2_8041b588(r2)
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC220828
		opword 0xD03D0178
		opword 0xC03D0178
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD01D0178
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f1, float_neg2_8041b58c(r2)
		opword 0xC01D0104
		opword 0xA81D017C
		opword 0xEC610028
		opword 0x2C000000
		opword 0x4182000C
		lfs f2, float_0p2_8041b590(r2)
		opword 0x48000008
		lfs f2, float_0p1_8041b518(r2)
		opword 0xC03D0104
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC2308BA
		opword 0xD03D0104
		opword 0xC05D0128
		opword 0xC03D0104
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820480
		opword 0xD01D0104
		opword 0x38610108
		opword 0x38810138
		opword 0x80BD0094
		opword 0x801D0098
		opword 0x90A10108
		opword 0x9001010C
		opword 0x801D009C
		opword 0x90010110
		opword 0xC03D00F0
		bl lookupSafetyPos
		opword 0x801D0138
		opword 0x28000000
		opword 0x4182002C
		opword 0x3803FFFF
		opword 0x28000001
		opword 0x40810014
		opword 0x28030004
		opword 0x4182000C
		opword 0x28030008
		opword 0x40820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x48000420
		opword 0x2803000F
		opword 0x41810144
		lis r4, jumptable_8031372C@ha
		opword 0x5460103A
		addi r3, r4, jumptable_8031372C@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x80BD0094
		opword 0x386100FC
		opword 0x801D0098
		opword 0x38810138
		lfs f2, float_135_8041b594(r2)
		opword 0x90A100FC
		opword 0x90010100
		opword 0x801D009C
		opword 0x90010104
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x48000124
		opword 0x80BD0094
		opword 0x386100F0
		opword 0x801D0098
		opword 0x38810138
		lfs f2, float_315_8041b598(r2)
		opword 0x90A100F0
		opword 0x900100F4
		opword 0x801D009C
		opword 0x900100F8
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x480000F4
		opword 0x80BD0094
		opword 0x386100E4
		opword 0x801D0098
		opword 0x38810138
		lfs f2, float_225_8041b59c(r2)
		opword 0x90A100E4
		opword 0x900100E8
		opword 0x801D009C
		opword 0x900100EC
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x480000C4
		opword 0x80BD0094
		opword 0x386100D8
		opword 0x801D0098
		opword 0x38810138
		lfs f2, float_315_8041b598(r2)
		opword 0x90A100D8
		opword 0x900100DC
		opword 0x801D009C
		opword 0x900100E0
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x48000094
		opword 0x38000046
		opword 0x981D0039
		opword 0x48000088
		opword 0x80BD0094
		opword 0x386100CC
		opword 0x801D0098
		opword 0x38810138
		lfs f2, float_270_8041b5a0(r2)
		opword 0x90A100CC
		opword 0x900100D0
		opword 0x801D009C
		opword 0x900100D4
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x48000058
		opword 0x80BD0094
		opword 0x386100C0
		opword 0x801D0098
		opword 0x38810138
		opword 0x90A100C0
		opword 0x900100C4
		opword 0x801D009C
		opword 0x900100C8
		opword 0xC03D00F0
		bl lookupSafetyPos3
		opword 0x4800002C
		opword 0x80BD0094
		opword 0x386100B4
		opword 0x801D0098
		opword 0x38810138
		opword 0x90A100B4
		opword 0x900100B8
		opword 0x801D009C
		opword 0x900100BC
		opword 0xC03D00F0
		bl lookupSafetyPos2
		opword 0x38000036
		opword 0x981D0039
		opword 0x80610138
		opword 0x8001013C
		opword 0x907D0094
		opword 0x901D0098
		opword 0x80010140
		opword 0x901D009C
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl distABf
		opword 0xD03D0128
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x4800025C
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f1, float_0p5_8041b530(r2)
		opword 0xC05D0104
		lfs f0, float_4_8041b5a4(r2)
		opword 0xEC22082A
		opword 0xD03D0104
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		opword 0xD01D0104
		opword 0xC05D0128
		opword 0xC03D0104
		lfs f0, float_10_8041b534(r2)
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408201D4
		opword 0x38000046
		lfs f0, float_0_8041b51c(r2)
		opword 0x981D0039
		opword 0xD01D0104
		opword 0x48000CF0
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x28030000
		opword 0x41820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x48000CD0
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f1, float_2p2_8041b588(r2)
		opword 0xC05D0178
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC220828
		opword 0xD03D0178
		opword 0xC03D0178
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD01D0178
		opword 0xA81D017C
		lfs f1, float_neg2_8041b58c(r2)
		opword 0xC01D0104
		opword 0x2C000000
		opword 0xEC610028
		opword 0x4182000C
		lfs f2, float_0p2_8041b590(r2)
		opword 0x48000008
		lfs f2, float_0p1_8041b518(r2)
		opword 0xC03D0104
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC2308BA
		opword 0xD03D0104
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408200F8
		opword 0x38000046
		opword 0x981D0039
		opword 0xD01D0104
		opword 0x48000C18
		opword 0xC07D0058
		opword 0xC05E008C
		opword 0xC03D005C
		opword 0xC01E0090
		opword 0xEC831028
		opword 0xC05D0060
		opword 0xEC610028
		opword 0xC01E0094
		opword 0xEC240132
		opword 0xEC420028
		opword 0xEC0300F2
		opword 0xEC4200B2
		opword 0xEC01002A
		opword 0xEC22002A
		bl sqrt
		opword 0xFC200818
		lfs f0, float_5_8041b5a8(r2)
		opword 0xFC010040
		opword 0x4080004C
		opword 0xC05E01A0
		opword 0xC81F0028
		opword 0xFC020040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_neg90_8041b5ac(r2)
		opword 0x48000008
		lfs f0, float_90_8041b52c(r2)
		lfs f1, float_0p5_8041b530(r2)
		opword 0xEC42002A
		opword 0xC01E01B4
		opword 0x387D0058
		opword 0x389D0060
		opword 0xEC210032
		bl movePos
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		lfs f0, float_0_8041b51c(r2)
		opword 0x38000047
		opword 0xD01D0104
		opword 0x807D0004
		opword 0x54630734
		opword 0x907D0004
		opword 0x807D0004
		opword 0x60630020
		opword 0x907D0004
		opword 0x981D0039
		opword 0x48000028
		opword 0x807D0174
		opword 0x28030000
		opword 0x41820010
		bl itemNokoForceGet
		opword 0x38000000
		opword 0x901D0174
		opword 0x7FA3EB78
		bl nokonoko_finish
		opword 0x48000B34
		opword 0x887D0039
		opword 0x3803FFB0
		opword 0x28000022
		opword 0x41810B10
		lis r3, jumptable_803136A0@ha
		opword 0x5400103A
		addi r3, r3, jumptable_803136A0@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38000051
		lfs f0, float_0_8041b51c(r2)
		opword 0x981D0039
		opword 0xD01D0104
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x389D0058
		lfs f0, float_75_8041b5b0(r2)
		opword 0x3860092B
		opword 0xC03D0128
		opword 0xEC01002A
		opword 0xD01D0128
		bl psndSFXOn_3D
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f1, float_3_8041b5b4(r2)
		opword 0xC05D0104
		lfs f0, float_18_8041b5b8(r2)
		opword 0xEC22082A
		opword 0xD03D0104
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		opword 0xD01D0104
		opword 0x801D0174
		opword 0x28000000
		opword 0x408200A4
		lfs f3, float_0p5_8041b530(r2)
		opword 0xC05D00F4
		lfs f0, float_12_8041b578(r2)
		opword 0xC03D0058
		opword 0xEC8300BA
		opword 0xC05D005C
		opword 0xC07D0060
		bl itemNearDistCheck
		opword 0x907D0174
		opword 0x807D0174
		opword 0x28030000
		opword 0x41820074
		bl itemPickUp
		opword 0x389D0058
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x7C7E1B79
		opword 0x41820030
		bl hitGetAttr
		opword 0x54600001
		opword 0x40820010
		opword 0x38000064
		opword 0x981D0039
		opword 0x4800098C
		opword 0x7FC3F378
		bl mobjHitObjPtrToPtr
		opword 0x3800006E
		opword 0x981D0039
		opword 0x48000978
		opword 0xC05D0128
		opword 0xC03D0104
		lfs f0, float_20_8041b584(r2)
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820940
		opword 0x38000052
		opword 0x981D0039
		opword 0x48000934
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f0, float_neg1_8041b520(r2)
		opword 0xC03D0104
		lfs f2, float_0p35_8041b5bc(r2)
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01D0104
		opword 0x801D0174
		opword 0x28000000
		opword 0x408200A4
		lfs f3, float_0p5_8041b530(r2)
		opword 0xC05D00F4
		lfs f0, float_12_8041b578(r2)
		opword 0xC03D0058
		opword 0xEC8300BA
		opword 0xC05D005C
		opword 0xC07D0060
		bl itemNearDistCheck
		opword 0x907D0174
		opword 0x807D0174
		opword 0x28030000
		opword 0x41820074
		bl itemPickUp
		opword 0x389D0058
		opword 0x3860092C
		bl psndSFXOn_3D
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl cos
		lfs f2, float_6p2832_8041b564(r2)
		opword 0xFFE00818
		opword 0xC03D0100
		lfs f0, float_360_8041b568(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC05D005C
		opword 0xFC800818
		opword 0xC01D00F0
		opword 0xFCC0F850
		opword 0xC03D0058
		opword 0x38600003
		opword 0xEC42002A
		opword 0xC07D0060
		opword 0x38800001
		lfs f5, float_neg1_8041b520(r2)
		bl effSmallStarN64Entry
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x28030000
		opword 0x41820010
		opword 0x38000064
		opword 0x981D0039
		opword 0x48000814
		opword 0xC05D0128
		opword 0xC03D0104
		lfs f0, float_0_8041b51c(r2)
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408207F0
		opword 0xC03D0094
		opword 0xC05D009C
		opword 0xC07D0058
		opword 0xC09D0060
		bl distABf
		opword 0xD03D0128
		opword 0x38000054
		lfs f0, float_50_8041b56c(r2)
		opword 0x981D0039
		opword 0xD01D0178
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x480007AC
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x28030000
		opword 0x41820010
		opword 0x38000064
		opword 0x981D0039
		opword 0x48000750
		opword 0xC05D0128
		opword 0xC03D0104
		lfs f0, float_30_8041b538(r2)
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082072C
		opword 0x38000056
		lfs f0, float_0_8041b51c(r2)
		opword 0x981D0039
		opword 0x386001F4
		opword 0xD01D0104
		bl sysMsec2Frame
		opword 0x907D0024
		opword 0x4800070C
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x4181000C
		opword 0x38000064
		opword 0x981D0039
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0x28030000
		opword 0x418206A4
		opword 0x38000064
		opword 0x981D0039
		opword 0x48000698
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		opword 0xC07D0058
		opword 0xC05E008C
		opword 0xC03D005C
		opword 0xC01E0090
		opword 0xEC831028
		opword 0xC05D0060
		opword 0xEC610028
		opword 0xC01E0094
		opword 0xEC240132
		opword 0xEC420028
		opword 0xEC0300F2
		opword 0xEC4200B2
		opword 0xEC01002A
		opword 0xEC22002A
		bl sqrt
		opword 0xFC200818
		lfs f0, float_5_8041b5a8(r2)
		opword 0xFC010040
		opword 0x4080004C
		opword 0xC05E01A0
		opword 0xC81F0028
		opword 0xFC020040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_90_8041b52c(r2)
		opword 0x48000008
		lfs f0, float_neg90_8041b5ac(r2)
		lfs f1, float_0p5_8041b530(r2)
		opword 0xEC42002A
		opword 0xC01E01B4
		opword 0x387D0058
		opword 0x389D0060
		opword 0xEC210032
		bl movePos
		opword 0x7FA3EB78
		opword 0x38800001
		bl ccwall
		lfs f0, float_0_8041b51c(r2)
		opword 0xD01D0104
		opword 0x801D0004
		opword 0x54000734
		opword 0x901D0004
		opword 0x807D0174
		opword 0x28030000
		opword 0x41820010
		bl itemNokoForceGet
		opword 0x38000000
		opword 0x901D0174
		opword 0x801D0138
		opword 0x28000000
		opword 0x40820010
		opword 0x38000058
		opword 0x981D0039
		opword 0x480005B4
		opword 0x807D0174
		opword 0x28030000
		opword 0x41820010
		bl itemNokoForceGet
		opword 0x38000000
		opword 0x901D0174
		opword 0x7FA3EB78
		bl nokonoko_finish
		opword 0x480005A4
		lfs f0, float_0_8041b51c(r2)
		opword 0x386100A8
		opword 0x3881012C
		opword 0xD01D0104
		opword 0x80BD0094
		opword 0x801D0098
		opword 0x90A100A8
		opword 0x900100AC
		opword 0x801D009C
		opword 0x900100B0
		opword 0xC03D00F0
		bl lookupSafetyPos
		opword 0x801D0138
		opword 0x28000000
		opword 0x4182002C
		opword 0x3803FFFF
		opword 0x28000001
		opword 0x40810014
		opword 0x28030004
		opword 0x4182000C
		opword 0x28030008
		opword 0x40820010
		opword 0x38000046
		opword 0x981D0039
		opword 0x4800052C
		opword 0x2803000F
		opword 0x41810144
		lis r4, jumptable_80313660@ha
		opword 0x5460103A
		addi r3, r4, jumptable_80313660@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x80BD0094
		opword 0x3861009C
		opword 0x801D0098
		opword 0x3881012C
		lfs f2, float_135_8041b594(r2)
		opword 0x90A1009C
		opword 0x900100A0
		opword 0x801D009C
		opword 0x900100A4
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x48000124
		opword 0x80BD0094
		opword 0x38610090
		opword 0x801D0098
		opword 0x3881012C
		lfs f2, float_315_8041b598(r2)
		opword 0x90A10090
		opword 0x90010094
		opword 0x801D009C
		opword 0x90010098
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x480000F4
		opword 0x80BD0094
		opword 0x38610084
		opword 0x801D0098
		opword 0x3881012C
		lfs f2, float_225_8041b59c(r2)
		opword 0x90A10084
		opword 0x90010088
		opword 0x801D009C
		opword 0x9001008C
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x480000C4
		opword 0x80BD0094
		opword 0x38610078
		opword 0x801D0098
		opword 0x3881012C
		lfs f2, float_315_8041b598(r2)
		opword 0x90A10078
		opword 0x9001007C
		opword 0x801D009C
		opword 0x90010080
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x48000094
		opword 0x38000046
		opword 0x981D0039
		opword 0x48000088
		opword 0x80BD0094
		opword 0x3861006C
		opword 0x801D0098
		opword 0x3881012C
		lfs f2, float_270_8041b5a0(r2)
		opword 0x90A1006C
		opword 0x90010070
		opword 0x801D009C
		opword 0x90010074
		opword 0xC03D00F0
		bl lookupSafetyPosSub
		opword 0x48000058
		opword 0x80BD0094
		opword 0x38610060
		opword 0x801D0098
		opword 0x3881012C
		opword 0x90A10060
		opword 0x90010064
		opword 0x801D009C
		opword 0x90010068
		opword 0xC03D00F0
		bl lookupSafetyPos3
		opword 0x4800002C
		opword 0x80BD0094
		opword 0x38610054
		opword 0x801D0098
		opword 0x3881012C
		opword 0x90A10054
		opword 0x90010058
		opword 0x801D009C
		opword 0x9001005C
		opword 0xC03D00F0
		bl lookupSafetyPos2
		opword 0x3800005A
		opword 0x981D0039
		opword 0x8061012C
		opword 0x80010130
		opword 0x907D0094
		opword 0x901D0098
		opword 0x80010134
		opword 0x901D009C
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl distABf
		opword 0xD03D0128
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		lfs f0, float_50_8041b56c(r2)
		opword 0xD01D0178
		opword 0x48000360
		opword 0xC03D0100
		opword 0xC01D00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041b514(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f2, float_1_8041b548(r2)
		opword 0x48000008
		lfs f2, float_neg1_8041b520(r2)
		lfs f1, float_50_8041b56c(r2)
		opword 0xC01D010C
		opword 0xEC2100BA
		bl revise360
		opword 0xD03D010C
		lfs f1, float_0p5_8041b530(r2)
		opword 0xC05D0104
		lfs f0, float_4_8041b5a4(r2)
		opword 0xEC22082A
		opword 0xD03D0104
		opword 0xC03D0104
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		opword 0xD01D0104
		opword 0xC05D0128
		opword 0xC03D0104
		lfs f0, float_10_8041b534(r2)
		opword 0xEC220828
		opword 0xD03D0128
		opword 0xC03D0128
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408202D8
		opword 0x38000046
		lfs f0, float_0_8041b51c(r2)
		opword 0x981D0039
		opword 0xD01D0104
		opword 0x480002C4
		lfs f1, float_0_8041b51c(r2)
		opword 0x386003E8
		lfs f0, float_15_8041b5c0(r2)
		opword 0xD03D0104
		opword 0xD01D0114
		opword 0xD03D0118
		bl sysMsec2Frame
		opword 0x907D0024
		opword 0x3800006F
		opword 0x981D0039
		opword 0xC03D005C
		opword 0x38610048
		opword 0xC01D0114
		opword 0x3881001C
		opword 0x38A10018
		opword 0x38C10014
		opword 0xEC01002A
		opword 0xD01D005C
		opword 0x80FD0058
		opword 0x801D005C
		opword 0x90E10048
		opword 0x9001004C
		opword 0x801D0060
		opword 0x90010050
		bl marioGetScreenPos
		opword 0xC0210018
		lfs f0, float_neg300_8041b5c4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082024C
		opword 0x38600320
		bl sysMsec2Frame
		opword 0x907D0024
		opword 0x38000070
		opword 0x981D0039
		opword 0x48000234
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x41810224
		opword 0x801D0000
		opword 0x54000001
		opword 0x40820010
		opword 0x38610120
		bl partyGetReturnPos
		opword 0x48000078
		opword 0x809E008C
		opword 0x38000000
		opword 0x807E0090
		lfs f0, float_90_8041b52c(r2)
		opword 0x90810120
		opword 0x90610124
		opword 0x807E0094
		opword 0x90610128
		opword 0xC03E01AC
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820018
		lfs f0, float_270_8041b5a0(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182000C
		lfs f1, float_0_8041b51c(r2)
		opword 0x48000008
		lfs f1, float_180_8041b514(r2)
		lfs f2, float_neg30_8041b5c8(r2)
		bl toMovedir2
		opword 0xFC400890
		lfs f1, float_30_8041b538(r2)
		opword 0x38610120
		opword 0x38810128
		bl movePos
		opword 0xC0010120
		opword 0x38000071
		lfs f3, float_1000_8041b5cc(r2)
		opword 0xD01D0058
		lfs f2, float_0_8041b51c(r2)
		opword 0xC0010124
		lfs f1, float_neg1_8041b520(r2)
		opword 0xEC63002A
		lfs f0, float_37_8041b550(r2)
		opword 0xD07D005C
		opword 0xC0610128
		opword 0xD07D0060
		opword 0xD05D0114
		opword 0xD03D0118
		opword 0xD05D0104
		opword 0x807D0000
		opword 0x60630020
		opword 0x907D0000
		opword 0x807D0000
		opword 0x64630200
		opword 0x907D0000
		opword 0x807D0000
		opword 0x54630188
		opword 0x907D0000
		opword 0x807D0000
		opword 0x5463020C
		opword 0x907D0000
		opword 0x807D0004
		opword 0x546306F2
		opword 0x907D0004
		opword 0x807D0004
		opword 0x54630734
		opword 0x907D0004
		opword 0xD01D00F0
		opword 0x981D0039
		opword 0x48000108
		opword 0x80FD0058
		opword 0x3861003C
		opword 0x801D005C
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x90E1003C
		opword 0x90010040
		opword 0x801D0060
		opword 0x90010044
		bl marioGetScreenPos
		opword 0xC021000C
		lfs f0, float_240_8041b5d0(r2)
		opword 0xFC010040
		opword 0x40810010
		opword 0x801D0000
		opword 0x540001CA
		opword 0x901D0000
		opword 0x7FA3EB78
		bl partyMove
		opword 0xC01D0114
		lfs f1, float_neg6_8041b5d4(r2)
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820010
		lfs f0, float_0_8041b51c(r2)
		opword 0xD01D0118
		opword 0xD03D0114
		opword 0xC03D005C
		lfs f0, float_neg2000_8041b5d8(r2)
		opword 0xFC010040
		opword 0x4080002C
		opword 0x807E008C
		opword 0x801E0090
		lfs f0, float_200_8041b5dc(r2)
		opword 0x907D0058
		opword 0x901D005C
		opword 0x801E0094
		opword 0x901D0060
		opword 0xC03D005C
		opword 0xEC01002A
		opword 0xD01D005C
		opword 0x801D0138
		opword 0x28000000
		opword 0x41820054
		opword 0xC01E01AC
		opword 0xD01D0110
		opword 0xC01D0110
		opword 0xD01D010C
		opword 0x807D0138
		bl hitGetAttr
		opword 0x5460BFFF
		opword 0x40820034
		opword 0x38600072
		opword 0x3800001E
		opword 0x987D0039
		opword 0x901D0024
		opword 0x48000020
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x41810010
		opword 0x7FA3EB78
		bl nokonoko_finish
		opword 0x48000018
		opword 0x881D0039
		opword 0x28000064
		opword 0x4182000C
		opword 0x7FA3EB78
		bl partyMoveNoHosei
	}
}
#pragma pop
#endif

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

void nokotaro_hold_cancel(PartyEntry* party) {
    party->useMotionId = 20;
}

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
  yofs = EXT_LIT(float_10_8041b534, 10.0f);
  y0 = party->position.y + party->height;
  x = party->position.x;
  dist = party->height + EXT_LIT(float_30_8041b538, 30.0f);
  y0 = yofs + y0;
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y0, party->position.z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f));
  if (((hitGetAttr(hit) >> 9) & 1) == 1)
  {
    hit = NULL;
  }
  party->field_138 = hit;
  if (hit != (NULL))
  {
    hy = ((f32) ((s32) ((100.0f * hy) + 0.5f))) / 100.0f;
    py = ((f32) ((s32) ((EXT_LIT(float_100_8041b53c, 100.0f) * party->position.y) + EXT_LIT(float_0p5_8041b530, 0.5f)))) / EXT_LIT(float_100_8041b53c, 100.0f);
    if (__fabsf(py - hy) <= EXT_LIT(float_11_8041b540, 11.0f))
    {
      if (py <= hy)
      {
        if (mode == 0)
        {
          party->position.y = hy;
          if (__fabsf(py - hy) >= EXT_LIT(float_1_8041b548, 1.0f))
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
        if (__fabsf(py - hy) <= EXT_LIT(float_6_8041b544, 6.0f))
        {
          party->position.y = hy;
        }
      }
    }
  }
  PW(party, 0x130) = 0;
  PW(party, 0x12c) = 0;
  yofs += EXT_LIT(float_1_8041b548, 1.0f);
  x = party->position.x;
  z = party->position.z;
  y = party->position.y + yofs;
  dist = (EXT_LIT(float_0p5_8041b530, 0.5f) * party->width) + party->moveSpeed;
  sincosf(&s, &c, party->targetDir);
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, EXT_LIT(float_0_8041b51c, 0.0f), c);
  if ((hit != (NULL)) && (!(hitGetAttr(hit) & 5)))
  {
    sincosf(&s1, &c1, 180.0f + party->targetDir);
    party->position.x = hx + (EXT_LIT(float_0p5_8041b530, 0.5f) * (s1 * party->width));
    party->position.z = hz + (EXT_LIT(float_0p5_8041b530, 0.5f) * (c1 * party->width));
    vx = s * party->moveSpeed;
    vz = c * party->moveSpeed;
    d = (vx * nx) + (vz * nz);
    party->position.x += EXT_LIT(float_0p5_8041b530, 0.5f) * (vx - (d * nx));
    party->position.z += EXT_LIT(float_0p5_8041b530, 0.5f) * (vz - (d * nz));
    if (((PH(party, 0x17c)) != 0) || (mode == 0))
    {
      PW(party, 0x130) = (u32) hit;
    }
    PW(party, 0x12c) = (u32) hit;
    return hit;
  }
  w = EXT_LIT(float_0p4_8041b54c, 0.4f) * party->width;
  z = (w * ((f32) cos((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (party->targetDir - 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f)))) + party->position.z;
  x = (w * ((f32) sin((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (party->targetDir - 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f)))) + party->position.x;
  y = party->position.y + yofs;
  dist = (EXT_LIT(float_0p4_8041b54c, 0.4f) * party->width) + party->moveSpeed;
  sincosf(&s, &c, party->targetDir);
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, EXT_LIT(float_0_8041b51c, 0.0f), c);
  if ((hit != (NULL)) && (!(hitGetAttr(hit) & 5)))
  {
    sincosf(&s2, &c2, 180.0f + party->targetDir);
    party->position.x = hx + (EXT_LIT(float_0p5_8041b530, 0.5f) * (s2 * party->width));
    party->position.z = hz + (EXT_LIT(float_0p5_8041b530, 0.5f) * (c2 * party->width));
    party->position.z -= w * ((f32) cos((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (party->targetDir - 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f)));
    party->position.x -= w * ((f32) sin((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (party->targetDir - 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f)));
    vx = s * party->moveSpeed;
    vz = c * party->moveSpeed;
    d = (vx * nx) + (vz * nz);
    party->position.x += EXT_LIT(float_0p5_8041b530, 0.5f) * (vx - (d * nx));
    party->position.z += EXT_LIT(float_0p5_8041b530, 0.5f) * (vz - (d * nz));
    if (((PH(party, 0x17c)) != 0) || (mode == 0))
    {
      PW(party, 0x130) = (u32) hit;
    }
    PW(party, 0x12c) = (u32) hit;
    party->position.x = hx;
    return hit;
  }
  w = EXT_LIT(float_0p4_8041b54c, 0.4f) * party->width;
  z = (w * ((f32) cos((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (EXT_LIT(float_90_8041b52c, 90.0f) + party->targetDir)) / EXT_LIT(float_180_8041b514, 180.0f)))) + party->position.z;
  x = (w * ((f32) sin((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (EXT_LIT(float_90_8041b52c, 90.0f) + party->targetDir)) / EXT_LIT(float_180_8041b514, 180.0f)))) + party->position.x;
  y = party->position.y + yofs;
  dist = (EXT_LIT(float_0p4_8041b54c, 0.4f) * party->width) + party->moveSpeed;
  sincosf(&s, &c, party->targetDir);
  hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, s, EXT_LIT(float_0_8041b51c, 0.0f), c);
  if ((hit != (NULL)) && (!(hitGetAttr(hit) & 5)))
  {
    sincosf(&s3, &c3, 180.0f + party->targetDir);
    party->position.x = hx + (EXT_LIT(float_0p5_8041b530, 0.5f) * (s3 * party->width));
    party->position.z = hz + (EXT_LIT(float_0p5_8041b530, 0.5f) * (c3 * party->width));
    party->position.z -= w * ((f32) cos((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (EXT_LIT(float_90_8041b52c, 90.0f) + party->targetDir)) / EXT_LIT(float_180_8041b514, 180.0f)));
    party->position.x -= w * ((f32) sin((EXT_LIT(float_3p1416_8041b510, 3.1415927f) * (EXT_LIT(float_90_8041b52c, 90.0f) + party->targetDir)) / EXT_LIT(float_180_8041b514, 180.0f)));
    vx = s * party->moveSpeed;
    vz = c * party->moveSpeed;
    d = (vx * nx) + (vz * nz);
    party->position.x += EXT_LIT(float_0p5_8041b530, 0.5f) * (vx - (d * nx));
    party->position.z += EXT_LIT(float_0p5_8041b530, 0.5f) * (vz - (d * nz));
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry *ccwall(PartyEntry *party, s32 mode) {
	char _af_pad[100];
	asm volatile {
		opword 0xC023005C
		opword 0x7C9F2378
		opword 0xC0A300F0
		opword 0x7C7E1B78
		lfs f0, float_30_8041b538(r2)
		la r4, _af_pad+44
		opword 0xEC41282A
		lfs f4, float_0_8041b51c(r2)
		lfs f30, float_10_8041b534(r2)
		opword 0xEC05002A
		opword 0xC0230058
		opword 0xFCC02090
		opword 0xC0630060
		opword 0xEC5E102A
		lfs f5, float_neg1_8041b520(r2)
		opword 0x38A10030
		opword 0xD0010038
		opword 0x38C1002C
		opword 0x38E10038
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7D1B78
		bl hitGetAttr
		opword 0x5460BFFE
		opword 0x2C000001
		opword 0x40820008
		li r29, 0x0
		opword 0x281D0000
		opword 0x93BE0138
		opword 0x41820108
		lfs f5, float_100_8041b53c(r2)
		opword 0x3C004330
		opword 0xC0010030
		lis r3, double_to_int_802ce148@ha
		lfs f4, float_0p5_8041b530(r2)
		opword 0x90010050
		opword 0xEC25203A
		lfd f3, double_to_int_802ce148@l(r3)
		opword 0x90010060
		lfs f0, float_11_8041b540(r2)
		opword 0xFC20081E
		opword 0xD8210048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010054
		opword 0xC8210050
		opword 0xEC211828
		opword 0xEC412824
		opword 0xD0410030
		opword 0xC03E005C
		opword 0xEC25207A
		opword 0xFC20081E
		opword 0xD8210058
		opword 0x8001005C
		opword 0x6C008000
		opword 0x90010064
		opword 0xC8210060
		opword 0xEC211828
		opword 0xEC612824
		opword 0xEC231028
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820080
		opword 0xFC031040
		opword 0x4C401382
		opword 0x4082003C
		opword 0x2C1F0000
		opword 0x4082006C
		opword 0xD05E005C
		lfs f0, float_1_8041b548(r2)
		opword 0xC0210030
		opword 0xEC230828
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082004C
		opword 0xA81E017E
		opword 0x60000002
		opword 0xB01E017E
		opword 0x4800003C
		opword 0xA81E017E
		opword 0x540007BD
		opword 0x41820010
		opword 0x2C1F0001
		opword 0x40820008
		opword 0xD05E005C
		opword 0xC0410030
		lfs f0, float_6_8041b544(r2)
		opword 0xEC231028
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD05E005C
		opword 0x38000000
		lfs f0, float_1_8041b548(r2)
		opword 0x901E0130
		opword 0x38610040
		lfs f2, float_0p5_8041b530(r2)
		opword 0xEFDE002A
		opword 0x901E012C
		opword 0x3881003C
		opword 0xC03E00F4
		opword 0xC01E0104
		opword 0xC07E005C
		opword 0xEC02007A
		opword 0xC3BE0058
		opword 0xC39E0060
		fadds f27, f3, f30
		opword 0xD0010038
		opword 0xC03E0100
		bl sincosf
		opword 0xFC20E890
		opword 0xC0810040
		opword 0xFC40D890
		lfs f5, float_0_8041b51c(r2)
		opword 0xFC60E090
		opword 0xC0C1003C
		opword 0x38810034
		opword 0x38A10030
		opword 0x38C1002C
		opword 0x38E10038
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7D1B79
		opword 0x418200C8
		bl hitGetAttr
		opword 0x70600005
		opword 0x408200BC
		lfs f1, float_180_8041b514(r2)
		opword 0x3861001C
		opword 0xC01E0100
		opword 0x38810018
		opword 0xEC21002A
		bl sincosf
		opword 0xC021001C
		opword 0xC01E00F4
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC210032
		opword 0xC0010034
		opword 0xEC03007A
		opword 0xD01E0058
		opword 0xC0410018
		opword 0xC03E00F4
		opword 0xC001002C
		opword 0xEC220072
		opword 0xEC03007A
		opword 0xD01E0060
		opword 0xC09E0104
		opword 0xC001003C
		opword 0xC0410040
		opword 0xECA00132
		opword 0xC0210020
		opword 0xEC820132
		opword 0xC0410028
		opword 0xC01E0058
		opword 0xEC250072
		opword 0xECC408BA
		opword 0xEC2620BC
		opword 0xEC03007A
		opword 0xD01E0058
		opword 0xC0210020
		opword 0xC01E0060
		opword 0xEC26287C
		opword 0xEC03007A
		opword 0xD01E0060
		opword 0xA81E017C
		opword 0x2C000000
		opword 0x4082000C
		opword 0x2C1F0000
		opword 0x40820008
		opword 0x93BE0130
		opword 0x93BE012C
		opword 0x7FA3EB78
		opword 0x48000420
		opword 0xC03E0100
		lfs f0, float_90_8041b52c(r2)
		lfs f2, float_3p1416_8041b510(r2)
		opword 0xEC210028
		lfs f0, float_180_8041b514(r2)
		lfs f4, float_0p4_8041b54c(r2)
		opword 0xC07E00F4
		opword 0xEC220072
		opword 0xEFE400F2
		opword 0xEC210024
		bl cos
		opword 0xC05E0100
		opword 0xFC800818
		lfs f0, float_90_8041b52c(r2)
		opword 0xC07E0060
		opword 0xEC220028
		lfs f2, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEF9F193A
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		lfs f2, float_0p4_8041b54c(r2)
		opword 0xFCA00818
		opword 0xC03E00F4
		opword 0x38610040
		opword 0xC01E0104
		opword 0x3881003C
		opword 0xC09E0058
		opword 0xC07E005C
		opword 0xEC02007A
		opword 0xEFBF217A
		opword 0xEF63F02A
		opword 0xD0010038
		opword 0xC03E0100
		bl sincosf
		opword 0xFC20E890
		opword 0xC0810040
		opword 0xFC40D890
		lfs f5, float_0_8041b51c(r2)
		opword 0xFC60E090
		opword 0xC0C1003C
		opword 0x38810034
		opword 0x38A10030
		opword 0x38C1002C
		opword 0x38E10038
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7D1B79
		opword 0x41820134
		bl hitGetAttr
		opword 0x70600005
		opword 0x40820128
		lfs f1, float_180_8041b514(r2)
		opword 0x38610014
		opword 0xC01E0100
		opword 0x38810010
		opword 0xEC21002A
		bl sincosf
		opword 0xC0210014
		opword 0xC01E00F4
		lfs f6, float_0p5_8041b530(r2)
		opword 0xEC410032
		opword 0xC0010034
		lfs f1, float_90_8041b52c(r2)
		lfs f3, float_3p1416_8041b510(r2)
		opword 0xEC4600BA
		lfs f0, float_180_8041b514(r2)
		opword 0xD05E0058
		opword 0xC0A10010
		opword 0xC09E00F4
		opword 0xC041002C
		opword 0xEC850132
		opword 0xEC46113A
		opword 0xD05E0060
		opword 0xC05E0100
		opword 0xEC220828
		opword 0xEC230072
		opword 0xEC210024
		bl cos
		opword 0xFC400818
		opword 0xC01E0060
		lfs f1, float_90_8041b52c(r2)
		lfs f3, float_3p1416_8041b510(r2)
		opword 0xEC5F00BC
		lfs f0, float_180_8041b514(r2)
		opword 0xD05E0060
		opword 0xC05E0100
		opword 0xEC220828
		opword 0xEC230072
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		opword 0xC01E0058
		lfs f2, float_0p5_8041b530(r2)
		opword 0xEC1F007C
		opword 0xD01E0058
		opword 0xC09E0104
		opword 0xC001003C
		opword 0xC0610040
		opword 0xECA00132
		opword 0xC0210020
		opword 0xEC830132
		opword 0xC0610028
		opword 0xC01E0058
		opword 0xEC250072
		opword 0xECC408FA
		opword 0xEC2620FC
		opword 0xEC02007A
		opword 0xD01E0058
		opword 0xC0210020
		opword 0xC01E0060
		opword 0xEC26287C
		opword 0xEC02007A
		opword 0xD01E0060
		opword 0xA81E017C
		opword 0x2C000000
		opword 0x4082000C
		opword 0x2C1F0000
		opword 0x40820008
		opword 0x93BE0130
		opword 0x93BE012C
		opword 0x7FA3EB78
		opword 0xC0010034
		opword 0xD01E0058
		opword 0x4800021C
		lfs f1, float_90_8041b52c(r2)
		opword 0xC01E0100
		lfs f2, float_3p1416_8041b510(r2)
		opword 0xEC21002A
		lfs f0, float_180_8041b514(r2)
		lfs f4, float_0p4_8041b54c(r2)
		opword 0xC07E00F4
		opword 0xEC220072
		opword 0xEFE400F2
		opword 0xEC210024
		bl cos
		lfs f2, float_90_8041b52c(r2)
		opword 0xFC800818
		opword 0xC01E0100
		opword 0xC07E0060
		opword 0xEC22002A
		lfs f2, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEF9F193A
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		lfs f2, float_0p4_8041b54c(r2)
		opword 0xFCA00818
		opword 0xC03E00F4
		opword 0x38610040
		opword 0xC01E0104
		opword 0x3881003C
		opword 0xC09E0058
		opword 0xC07E005C
		opword 0xEC02007A
		opword 0xEFBF217A
		opword 0xEFC3F02A
		opword 0xD0010038
		opword 0xC03E00F4
		opword 0xC01E0104
		opword 0xEC02007A
		opword 0xD0010038
		opword 0xC03E0100
		bl sincosf
		opword 0xFC20E890
		opword 0xC0810040
		opword 0xFC40F090
		lfs f5, float_0_8041b51c(r2)
		opword 0xFC60E090
		opword 0xC0C1003C
		opword 0x38810034
		opword 0x38A10030
		opword 0x38C1002C
		opword 0x38E10038
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C7D1B79
		opword 0x41820134
		bl hitGetAttr
		opword 0x70600005
		opword 0x40820128
		lfs f1, float_180_8041b514(r2)
		opword 0x3861000C
		opword 0xC01E0100
		opword 0x38810008
		opword 0xEC21002A
		bl sincosf
		opword 0xC021000C
		opword 0xC01E00F4
		lfs f6, float_0p5_8041b530(r2)
		opword 0xEC210032
		opword 0xC0010034
		lfs f2, float_90_8041b52c(r2)
		lfs f3, float_3p1416_8041b510(r2)
		opword 0xEC26007A
		lfs f0, float_180_8041b514(r2)
		opword 0xD03E0058
		opword 0xC0A10008
		opword 0xC09E00F4
		opword 0xC021002C
		opword 0xEC850132
		opword 0xEC26093A
		opword 0xD03E0060
		opword 0xC03E0100
		opword 0xEC22082A
		opword 0xEC230072
		opword 0xEC210024
		bl cos
		opword 0xFC200818
		opword 0xC01E0060
		lfs f2, float_90_8041b52c(r2)
		lfs f3, float_3p1416_8041b510(r2)
		opword 0xEC3F007C
		lfs f0, float_180_8041b514(r2)
		opword 0xD03E0060
		opword 0xC03E0100
		opword 0xEC22082A
		opword 0xEC230072
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		opword 0xC01E0058
		lfs f2, float_0p5_8041b530(r2)
		opword 0xEC1F007C
		opword 0xD01E0058
		opword 0xC09E0104
		opword 0xC001003C
		opword 0xC0610040
		opword 0xECA00132
		opword 0xC0210020
		opword 0xEC830132
		opword 0xC0610028
		opword 0xC01E0058
		opword 0xEC250072
		opword 0xECC408FA
		opword 0xEC2620FC
		opword 0xEC02007A
		opword 0xD01E0058
		opword 0xC0210020
		opword 0xC01E0060
		opword 0xEC26287C
		opword 0xEC02007A
		opword 0xD01E0060
		opword 0xA81E017C
		opword 0x2C000000
		opword 0x4082000C
		opword 0x2C1F0000
		opword 0x40820008
		opword 0x93BE0130
		opword 0x93BE012C
		opword 0x7FA3EB78
		opword 0xC0010034
		opword 0xD01E0058
		opword 0x48000008
		opword 0x38600000
	}
}
#pragma pop
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
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * revise360(toMovedir(player->displayDirectionTarget) - 180.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    x = w * (f32)sin(rad) + pos.x;
    p[3].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[3].y = y;
    z = w * -c + pos.z;
    p[3].z = z;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    h0 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f));
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * revise360(toMovedir(player->displayDirectionTarget) - 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    x = w * (f32)sin(rad) + pos.x;
    p[2].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[2].y = y;
    z = w * -c + pos.z;
    p[2].z = z;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    h1 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f));
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * revise360(EXT_LIT(float_90_8041b52c, 90.0f) + toMovedir(player->displayDirectionTarget))) / EXT_LIT(float_180_8041b514, 180.0f);
    x = w * (f32)sin(rad) + pos.x;
    p[1].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[1].y = y;
    z = w * -c + pos.z;
    p[1].z = z;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    h2 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f));
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * revise360(toMovedir(player->displayDirectionTarget))) / EXT_LIT(float_180_8041b514, 180.0f);
    x = w * (f32)sin(rad) + pos.x;
    p[0].x = x;
    c = (f32)cos(rad);
    y = pos.y;
    p[0].y = y;
    z = w * -c + pos.z;
    p[0].z = z;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    h3 = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f));
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
u32 lookupSafetyPos(Vec pos, f32 height, Vec* out) {
	asm volatile {
		opword 0x9421FF50
		opword 0x7C0802A6
		opword 0x900100B4
		opword 0xDBE100A0
		opword 0xF3E100A8
		opword 0xDBC10090
		opword 0xF3C10098
		opword 0xDBA10080
		opword 0xF3A10088
		opword 0xDB810070
		opword 0xF3810078
		opword 0xBF61005C
		opword 0xFFA00890
		opword 0x7C7B1B78
		opword 0x7C9F2378
		bl marioGetPtr
		opword 0x7C7E1B78
		opword 0xC3C301B4
		opword 0xC02301AC
		bl toMovedir
		lfs f0, float_180_8041b514(r2)
		opword 0xEC210028
		bl revise360
		lfs f2, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEC220072
		opword 0xEFE10024
		opword 0xFC20F890
		bl sin
		opword 0xFC400818
		opword 0xC01B0000
		opword 0xFC20F890
		opword 0xEF9E00BA
		opword 0xD3810048
		bl cos
		opword 0xFC600818
		opword 0xC0BB0004
		lfs f0, float_0p1_8041b518(r2)
		opword 0xFC20E090
		lfs f4, float_0_8041b51c(r2)
		opword 0xEC45E82A
		opword 0xFCC01850
		opword 0xC07B0008
		opword 0xEFE0E82A
		opword 0xD0A1004C
		lfs f5, float_neg1_8041b520(r2)
		opword 0x3881001C
		opword 0xEC7E19BA
		opword 0xD3E10020
		opword 0xFCC02090
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0xD0610050
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0xC03E01AC
		opword 0x7C7C1B78
		bl toMovedir
		lfs f0, float_90_8041b52c(r2)
		opword 0xEC210028
		bl revise360
		lfs f2, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEC220072
		opword 0xEF810024
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		opword 0xC01B0000
		opword 0xFC20E090
		opword 0xEF9E00BA
		opword 0xD381003C
		bl cos
		opword 0xFC600818
		opword 0xC0BB0004
		lfs f4, float_0_8041b51c(r2)
		opword 0xFC20E090
		opword 0xC01B0008
		opword 0xEC45E82A
		opword 0xFC601850
		opword 0xD0A10040
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0xD3E10020
		opword 0x3881001C
		opword 0xEC7E00FA
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0x39010010
		opword 0x3921000C
		opword 0xD0610044
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0xC03E01AC
		opword 0x7C7D1B78
		bl toMovedir
		lfs f0, float_90_8041b52c(r2)
		opword 0xEC20082A
		bl revise360
		lfs f2, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEC220072
		opword 0xEF810024
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		opword 0xC01B0000
		opword 0xFC20E090
		opword 0xEF9E00BA
		opword 0xD3810030
		bl cos
		opword 0xFC600818
		opword 0xC0BB0004
		lfs f4, float_0_8041b51c(r2)
		opword 0xFC20E090
		opword 0xC01B0008
		opword 0xEC45E82A
		opword 0xFC601850
		opword 0xD0A10034
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0xD3E10020
		opword 0x3881001C
		opword 0xEC7E00FA
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0x39010010
		opword 0x3921000C
		opword 0xD0610038
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0xC03E01AC
		opword 0x7C7E1B78
		bl toMovedir
		bl revise360
		lfs f2, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEC220072
		opword 0xEF810024
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		opword 0xC01B0000
		opword 0xFC20E090
		opword 0xEF9E00BA
		opword 0xD3810024
		bl cos
		opword 0xFC600818
		opword 0xC0BB0004
		lfs f4, float_0_8041b51c(r2)
		opword 0xFC20E090
		opword 0xC01B0008
		opword 0xEC45E82A
		opword 0xFC601850
		opword 0xD0A10028
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0xD3E10020
		opword 0x3881001C
		opword 0xEC7E00FA
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0x39010010
		opword 0x3921000C
		opword 0xD061002C
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x281E0000
		opword 0x38800000
		opword 0x41820008
		opword 0x60840004
		opword 0x28030000
		opword 0x41820008
		opword 0x60840008
		opword 0x281C0000
		opword 0x41820008
		opword 0x60840001
		opword 0x281D0000
		opword 0x41820008
		opword 0x60840002
		opword 0x281C0000
		opword 0x41820140
		opword 0x281D0000
		opword 0x41820050
		opword 0x281E0000
		opword 0x41820048
		opword 0x28030000
		opword 0x41820040
		opword 0xC0610048
		opword 0x7C832378
		opword 0xC0410030
		opword 0xC0210050
		opword 0xC0010038
		opword 0xEC43102A
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC21002A
		opword 0xC001004C
		opword 0xEC4300B2
		opword 0xEC230072
		opword 0xD05F0000
		opword 0xD03F0008
		opword 0xD01F0004
		opword 0x48000204
		opword 0x281D0000
		opword 0x41820040
		opword 0xC0610048
		opword 0x7C832378
		opword 0xC041003C
		opword 0xC0210050
		opword 0xC0010044
		opword 0xEC43102A
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC21002A
		opword 0xC01B0004
		opword 0xEC4300B2
		opword 0xEC230072
		opword 0xD05F0000
		opword 0xD03F0008
		opword 0xD01F0004
		opword 0x480001C0
		opword 0x281E0000
		opword 0x41820040
		opword 0xC0610048
		opword 0x7C832378
		opword 0xC0410030
		opword 0xC0210050
		opword 0xC0010038
		opword 0xEC43102A
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC21002A
		opword 0xC001004C
		opword 0xEC4300B2
		opword 0xEC230072
		opword 0xD05F0000
		opword 0xD03F0008
		opword 0xD01F0004
		opword 0x4800017C
		opword 0x28030000
		opword 0x41820040
		opword 0xC0610048
		opword 0x7C832378
		opword 0xC0410024
		opword 0xC0210050
		opword 0xC001002C
		opword 0xEC43102A
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC21002A
		opword 0xC001004C
		opword 0xEC4300B2
		opword 0xEC230072
		opword 0xD05F0000
		opword 0xD03F0008
		opword 0xD01F0004
		opword 0x48000138
		opword 0x80010048
		opword 0x8061004C
		opword 0x901F0000
		opword 0x80010050
		opword 0x907F0004
		opword 0x901F0008
		opword 0x48000100
		opword 0x28030000
		opword 0x418200A8
		opword 0x281D0000
		opword 0x41820040
		opword 0xC0610024
		opword 0x7C832378
		opword 0xC041003C
		opword 0xC021002C
		opword 0xC0010044
		opword 0xEC43102A
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC21002A
		opword 0xC0010028
		opword 0xEC4300B2
		opword 0xEC230072
		opword 0xD05F0000
		opword 0xD03F0008
		opword 0xD01F0004
		opword 0x480000D0
		opword 0x281E0000
		opword 0x41820040
		opword 0xC0610030
		opword 0x7C832378
		opword 0xC041003C
		opword 0xC0210038
		opword 0xC0010044
		opword 0xEC43102A
		lfs f3, float_0p5_8041b530(r2)
		opword 0xEC21002A
		opword 0xC0010034
		opword 0xEC4300B2
		opword 0xEC230072
		opword 0xD05F0000
		opword 0xD03F0008
		opword 0xD01F0004
		opword 0x4800008C
		opword 0x80010024
		opword 0x80610028
		opword 0x901F0000
		opword 0x8001002C
		opword 0x907F0004
		opword 0x901F0008
		opword 0x48000054
		opword 0x281D0000
		opword 0x41820024
		opword 0x8001003C
		opword 0x7C832378
		opword 0x80810040
		opword 0x901F0000
		opword 0x80010044
		opword 0x909F0004
		opword 0x901F0008
		opword 0x48000048
		opword 0x281E0000
		opword 0x41820024
		opword 0x80010030
		opword 0x7C832378
		opword 0x80810034
		opword 0x901F0000
		opword 0x80010038
		opword 0x909F0004
		opword 0x901F0008
		opword 0x48000020
		opword 0x801B0000
		opword 0x7C832378
		opword 0x809B0004
		opword 0x901F0000
		opword 0x801B0008
		opword 0x909F0004
		opword 0x901F0008
		opword 0xE3E100A8
		opword 0xCBE100A0
		opword 0xE3C10098
		opword 0xCBC10090
		opword 0xE3A10088
		opword 0xCBA10080
		opword 0xE3810078
		opword 0xCB810070
		opword 0xBB61005C
		opword 0x800100B4
		opword 0x7C0803A6
		opword 0x382100B0
	}
}
#pragma pop
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
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * EXT_LIT(float_90_8041b52c, 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    y = pos.y;
    z = pos.z + dz;
    d = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * EXT_LIT(float_270_8041b5a0, 270.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    y = pos.y;
    z = pos.z + dz;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * EXT_LIT(float_180_8041b514, 180.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    dx = (f32)sin(rad);
    dz = (f32)cos(rad);
    x = pos.x;
    y = pos.y;
    z = pos.z;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * EXT_LIT(float_0_8041b51c, 0.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    y = pos.y;
    z = pos.z + dz;
    dist = d;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    *out = pos;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void lookupSafetyPos2(Vec pos, f32 height, Vec* out) {
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0xDBE10080
		opword 0xF3E10088
		opword 0xDBC10070
		opword 0xF3C10078
		opword 0xDBA10060
		opword 0xF3A10068
		opword 0xDB810050
		opword 0xF3810058
		opword 0xDB610040
		opword 0xF3610048
		opword 0xDB410030
		opword 0xF3410038
		opword 0x93E1002C
		opword 0x93C10028
		opword 0xFFA00890
		opword 0x7C7E1B78
		opword 0x7C9F2378
		bl marioGetPtr
		opword 0xC3C301B4
		lfs f1, float_1p5708_8041b524(r2)
		bl sin
		opword 0xFFE00818
		lfs f1, float_1p5708_8041b524(r2)
		bl cos
		opword 0xFC600818
		lfs f0, float_0p1_8041b518(r2)
		opword 0xC39E0004
		opword 0xEC3E07F2
		opword 0xC05E0000
		opword 0xEFE0E82A
		opword 0xFC001850
		lfs f4, float_0_8041b51c(r2)
		opword 0xEF42082A
		opword 0xC07E0008
		opword 0xFCC02090
		opword 0xD3E10020
		opword 0xEC1E0032
		lfs f5, float_neg1_8041b520(r2)
		opword 0xFC20D090
		opword 0x3881001C
		opword 0xEC5CE82A
		opword 0x38A10018
		opword 0xEF63002A
		opword 0x38C10014
		opword 0x38E10020
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0xFC60D890
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xD35F0000
		opword 0xD37F0008
		opword 0xD39F0004
		opword 0x480001B0
		lfs f1, float_4p7124_8041b528(r2)
		bl sin
		opword 0xFF800818
		lfs f1, float_4p7124_8041b528(r2)
		bl cos
		opword 0xFC000818
		opword 0xC37E0004
		lfs f4, float_0_8041b51c(r2)
		opword 0xEC3E0732
		opword 0xC0BE0000
		opword 0xEC5BE82A
		opword 0xFC000050
		opword 0xC07E0008
		opword 0xEF85082A
		opword 0xD3E10020
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0xEC1E0032
		opword 0x3881001C
		opword 0xFC20E090
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0xEF43002A
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xFC60D090
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xD39F0000
		opword 0xD35F0008
		opword 0xD37F0004
		opword 0x48000120
		lfs f1, float_3p1416_8041b510(r2)
		bl sin
		lfs f1, float_3p1416_8041b510(r2)
		bl cos
		opword 0xC39E0000
		opword 0x3881001C
		opword 0xC35E0008
		opword 0x38A10018
		opword 0xC37E0004
		opword 0xFC20E090
		lfs f4, float_0_8041b51c(r2)
		opword 0xFC60D090
		opword 0xEC5BE82A
		opword 0xD3E10020
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0x38C10014
		opword 0x38E10020
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xD39F0000
		opword 0xD35F0008
		opword 0xD37F0004
		opword 0x480000AC
		lfs f1, float_0_8041b51c(r2)
		bl sin
		opword 0xFF800818
		lfs f1, float_0_8041b51c(r2)
		bl cos
		opword 0xFC000818
		opword 0xC37E0004
		lfs f4, float_0_8041b51c(r2)
		opword 0xEC3E0732
		opword 0xC0BE0000
		opword 0xEC5BE82A
		opword 0xFC000050
		opword 0xC07E0008
		opword 0xEF85082A
		opword 0xD3E10020
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0xEC1E0032
		opword 0x3881001C
		opword 0xFC20E090
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0xEFA3002A
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xFC60E890
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xD39F0000
		opword 0xD3BF0008
		opword 0xD37F0004
		opword 0x4800001C
		opword 0x801E0000
		opword 0x807E0004
		opword 0x901F0000
		opword 0x801E0008
		opword 0x907F0004
		opword 0x901F0008
		opword 0xE3E10088
		opword 0xCBE10080
		opword 0xE3C10078
		opword 0xCBC10070
		opword 0xE3A10068
		opword 0xCBA10060
		opword 0xE3810058
		opword 0xCB810050
		opword 0xE3610048
		opword 0xCB610040
		opword 0xE3410038
		opword 0xCB410030
		opword 0x83E1002C
		opword 0x80010094
		opword 0x83C10028
		opword 0x7C0803A6
		opword 0x38210090
	}
}
#pragma pop
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

    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * EXT_LIT(float_90_8041b52c, 90.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    z = pos.z + dz;
    y = pos.y;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * EXT_LIT(float_270_8041b5a0, 270.0f)) / EXT_LIT(float_180_8041b514, 180.0f);
    dx = (f32)sin(rad);
    dz = -(f32)cos(rad);
    dx = w * dx;
    dz = w * dz;
    x = pos.x + dx;
    z = pos.z + dz;
    y = pos.y;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + height, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
        out->x = x;
        out->z = z;
        out->y = y;
        return;
    }
    *out = pos;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void lookupSafetyPos3(Vec pos, f32 height, Vec* out) {
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0xDBE10080
		opword 0xF3E10088
		opword 0xDBC10070
		opword 0xF3C10078
		opword 0xDBA10060
		opword 0xF3A10068
		opword 0xDB810050
		opword 0xF3810058
		opword 0xDB610040
		opword 0xF3610048
		opword 0xDB410030
		opword 0xF3410038
		opword 0x93E1002C
		opword 0x93C10028
		opword 0xFFC00890
		opword 0x7C7E1B78
		opword 0x7C9F2378
		bl marioGetPtr
		opword 0xC3E301B4
		lfs f1, float_1p5708_8041b524(r2)
		bl sin
		opword 0xFFA00818
		lfs f1, float_1p5708_8041b524(r2)
		bl cos
		opword 0xFC600818
		lfs f0, float_0p1_8041b518(r2)
		opword 0xC39E0004
		opword 0xEC3F0772
		opword 0xC05E0000
		opword 0xEF60F02A
		opword 0xFC001850
		lfs f4, float_0_8041b51c(r2)
		opword 0xEFA2082A
		opword 0xC07E0008
		opword 0xFCC02090
		opword 0xD3610020
		opword 0xEC1F0032
		lfs f5, float_neg1_8041b520(r2)
		opword 0xFC20E890
		opword 0x3881001C
		opword 0xEC5CF02A
		opword 0x38A10018
		opword 0xEF43002A
		opword 0x38C10014
		opword 0x38E10020
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0xFC60D090
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xD3BF0000
		opword 0xD35F0008
		opword 0xD39F0004
		opword 0x480000AC
		lfs f1, float_4p7124_8041b528(r2)
		bl sin
		opword 0xFFA00818
		lfs f1, float_4p7124_8041b528(r2)
		bl cos
		opword 0xFC000818
		opword 0xC39E0004
		lfs f4, float_0_8041b51c(r2)
		opword 0xEC3F0772
		opword 0xC0BE0000
		opword 0xEC5CF02A
		opword 0xFC000050
		opword 0xC07E0008
		opword 0xEFA5082A
		opword 0xD3610020
		opword 0xFCC02090
		lfs f5, float_neg1_8041b520(r2)
		opword 0xEC1F0032
		opword 0x3881001C
		opword 0xFC20E890
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0xEF63002A
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xFC60D890
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xD3BF0000
		opword 0xD37F0008
		opword 0xD39F0004
		opword 0x4800001C
		opword 0x801E0000
		opword 0x807E0004
		opword 0x901F0000
		opword 0x801E0008
		opword 0x907F0004
		opword 0x901F0008
		opword 0xE3E10088
		opword 0xCBE10080
		opword 0xE3C10078
		opword 0xCBC10070
		opword 0xE3A10068
		opword 0xCBA10060
		opword 0xE3810058
		opword 0xCB810050
		opword 0xE3610048
		opword 0xCB610040
		opword 0xE3410038
		opword 0xCB410030
		opword 0x83E1002C
		opword 0x80010094
		opword 0x83C10028
		opword 0x7C0803A6
		opword 0x38210090
	}
}
#pragma pop
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
    rad = (EXT_LIT(float_3p1416_8041b510, 3.1415927f) * angle) / EXT_LIT(float_180_8041b514, 180.0f);
    angle = player->wPlayerCollisionBox.x;
    x = angle * (f32)sin(rad) + pos.x;
    z = angle * -(f32)cos(rad) + pos.z;
    y = pos.y + height;
    dist = EXT_LIT(float_0p1_8041b518, 0.1f) + height;
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, EXT_LIT(float_0_8041b51c, 0.0f), EXT_LIT(float_neg1_8041b520, -1.0f), EXT_LIT(float_0_8041b51c, 0.0f)) != NULL) {
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void lookupSafetyPosSub(Vec pos, f32 height, f32 angle, Vec* out) {
	asm volatile {
		opword 0x9421FF80
		opword 0x7C0802A6
		opword 0x90010084
		opword 0xDBE10070
		opword 0xF3E10078
		opword 0xDBC10060
		opword 0xF3C10068
		opword 0xDBA10050
		opword 0xF3A10058
		opword 0xDB810040
		opword 0xF3810048
		opword 0x93E1003C
		opword 0x93C10038
		opword 0xFF800890
		opword 0x7C7E1B78
		opword 0xFFA01090
		opword 0x7C9F2378
		bl marioGetPtr
		lfs f1, float_3p1416_8041b510(r2)
		lfs f0, float_180_8041b514(r2)
		opword 0xEC210772
		opword 0xC3A301B4
		opword 0xEFE10024
		opword 0xFC20F890
		bl sin
		opword 0xFC400818
		opword 0xC01E0000
		opword 0xFC20F890
		opword 0xEFFD00BA
		bl cos
		opword 0xFC600818
		opword 0xC05E0004
		lfs f0, float_0p1_8041b518(r2)
		opword 0xFC20F890
		opword 0xEFC2E02A
		lfs f4, float_0_8041b51c(r2)
		opword 0xFCC01850
		opword 0xC07E0008
		opword 0xEC00E02A
		lfs f5, float_neg1_8041b520(r2)
		opword 0xFC40F090
		opword 0x3881001C
		opword 0xEFBD19BA
		opword 0xD0010020
		opword 0xFCC02090
		opword 0x38A10018
		opword 0x38C10014
		opword 0x38E10020
		opword 0xFC60E890
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820038
		lis r3, vec3_802ce138@ha
		opword 0x38C10024
		addi r5, r3, vec3_802ce138@l
		opword 0x80850000
		opword 0x80650004
		opword 0x80050008
		opword 0x90810024
		opword 0x90610028
		opword 0x9001002C
		opword 0xD3E10024
		opword 0xD3C10028
		opword 0xD3A1002C
		opword 0x48000008
		opword 0x7FC6F378
		opword 0x80660000
		opword 0x80060004
		opword 0x907F0000
		opword 0x901F0004
		opword 0x80060008
		opword 0x901F0008
		opword 0xE3E10078
		opword 0xCBE10070
		opword 0xE3C10068
		opword 0xCBC10060
		opword 0xE3A10058
		opword 0xCBA10050
		opword 0xE3810048
		opword 0xCB810040
		opword 0x83E1003C
		opword 0x80010084
		opword 0x83C10038
		opword 0x7C0803A6
		opword 0x38210080
	}
}
#pragma pop
#endif


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_8031381C_data[1] = {0};

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802ce138[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802ce148 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802CE150[8] = "PNK_K_2";
__declspec(section ".rodata") const char str_802CE158[8] = "PNK_A_1";
__declspec(section ".rodata") const f64 double_180_802ce160 = 180.0;
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
__declspec(section ".sdata2") const u32 gap_09_8041B5E4_sdata2[1] = {0};
#endif
