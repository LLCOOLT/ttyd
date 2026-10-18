// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include "driver/hitdrv.h"
#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include "mario/mariost.h"
#include <string.h>

// file-local full-layout view of PartyEntry (party.h is not included)
typedef struct PartyMarioView {
    u32 flags0;             // 0x0
    u8 unk4[0xC - 0x4];     // 0x4
    u32 flags;              // 0xC
    u8 unk10[0x2E - 0x10];  // 0x10
    u16 motionId;           // 0x2E
    u8 unk30[0x3C - 0x30];  // 0x30
    u8 unk3C;               // 0x3C
    u8 unk3D[0x50 - 0x3D];  // 0x3D
    s16 unk50;              // 0x50
    u8 unk52[0x8C - 0x52];  // 0x52
    Vec position;           // 0x8C
    u8 unk98[0x180 - 0x98]; // 0x98
    f32 unk180;             // 0x180
    u8 unk184[0x190 - 0x184]; // 0x184
    f32 unk190;             // 0x190
    u8 unk194[0x198 - 0x194]; // 0x194
    f32 unk198;             // 0x198
    u8 unk19C[0x1A8 - 0x19C]; // 0x19C
    f32 unk1A8;             // 0x1A8
    f32 unk1AC;             // 0x1AC
    u8 unk1B0[0x1B4 - 0x1B0]; // 0x1B0
    f32 unk1B4;             // 0x1B4
    u8 unk1B8[0x1E4 - 0x1B8]; // 0x1B8
    HitEntry* unk1E4;       // 0x1E4
    u8 unk1E8[0x224 - 0x1E8]; // 0x1E8
    f32 unk224;             // 0x224
} PartyMarioView;

typedef struct PartyEntry {
    u32 flags;                  // 0x0
    u32 flags2;                 // 0x4
    u32 flags3;                 // 0x8
    u8 unkC[0x24 - 0xC];        // 0xC
    s32 unk24;                  // 0x24
    s16 unk28;                  // 0x28
    u8 unk2A[0x2F - 0x2A];      // 0x2A
    s8 unk2F;                   // 0x2F
    u8 unk30;                   // 0x30
    s8 currentMemberId;         // 0x31
    u8 unk32;                   // 0x32
    u8 unk33;                   // 0x33
    u8 unk34;                   // 0x34
    u8 unk35[0x37 - 0x35];      // 0x35
    u8 unk37;                   // 0x37
    u8 unk38;                   // 0x38
    u8 unk39;                   // 0x39
    u8 unk3A;                   // 0x3A
    u8 unk3B;                   // 0x3B
    u8 unk3C[0x40 - 0x3C];      // 0x3C
    f32 unk40;                  // 0x40
    u8 unk44[0x4C - 0x44];      // 0x44
    s8 unk4C;                   // 0x4C
    s8 unk4D;                   // 0x4D
    s8 unk4E;                   // 0x4E
    u8 unk4F[0x54 - 0x4F];      // 0x4F
    f32 unk54;                  // 0x54
    Vec position;               // 0x58
    f32 unk64;                  // 0x64
    u8 unk68[0x6C - 0x68];      // 0x68
    f32 unk6C;                  // 0x6C
    u8 unk70[0x7C - 0x70];      // 0x70
    Vec unk7C;                  // 0x7C
    Vec unk88;                  // 0x88
    Vec unk94;                  // 0x94
    f32 unkA0;                  // 0xA0
    f32 unkA4;                  // 0xA4
    f32 unkA8;                  // 0xA8
    u8 unkAC[0xE0 - 0xAC];      // 0xAC
    f32 unkE0;                  // 0xE0
    f32 unkE4;                  // 0xE4
    u8 unkE8[0xF0 - 0xE8];      // 0xE8
    f32 unkF0;                  // 0xF0
    f32 unkF4;                  // 0xF4
    f32 unkF8;                  // 0xF8
    f32 unkFC;                  // 0xFC
    f32 unk100;                 // 0x100
    f32 unk104;                 // 0x104
    u8 unk108[0x10C - 0x108];   // 0x108
    f32 unk10C;                 // 0x10C
    f32 unk110;                 // 0x110
    f32 unk114;                 // 0x114
    f32 unk118;                 // 0x118
    f32 unk11C;                 // 0x11C
    f32 unk120;                 // 0x120
    u8 unk124[0x128 - 0x124];   // 0x124
    f32 unk128;                 // 0x128
    HitEntry* unk12C;           // 0x12C
    u8 unk130[0x134 - 0x130];   // 0x130
    HitEntry* unk134;           // 0x134
    HitEntry* unk138;           // 0x138
    u8 unk13C[0x140 - 0x13C];   // 0x13C
    void* unk140;               // 0x140
    u8 unk144[0x14C - 0x144];   // 0x144
    HitEntry* unk14C;           // 0x14C
    u8 unk150[0x160 - 0x150];   // 0x150
    PartyMarioView* playerPtr;  // 0x160
    u8 unk164[0x168 - 0x164];   // 0x164
    s32 unk168;                 // 0x168
} PartyEntry;

typedef struct PartyCamView {
    u8 unk0[0x114];
    f32 unk114;
} PartyCamView;

PartyEntry* partyGetPtr(s32 index);
s32 marioGetPartyId(void);
s32 marioGetExtraPartyId(void);
f32 revise360(f32 angle);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
void partyChgMot(PartyEntry* party, s32 mot);
void partyPaperOff(PartyEntry* party);
void partyChgPoseId(PartyEntry* party, s32 pose);
void partyChgMotSlitFloor(PartyEntry* party);
void sincosf(f32* ret_sin, f32* ret_cos, f32 degree);

static s32 unk_804189f4;
static f32 touch_wall_ct;
static s32 unk_804189ec;
static f32 unk_804189e8;

void L_partyForceSlitOff(PartyEntry* party);
BOOL party_slit(PartyEntry* party);
BOOL party_roll(PartyEntry* party);
void unk_8014b824(PartyEntry* party);
void unk_8014ba3c(PartyEntry* party);
void* partySearchHead(PartyEntry* party, Vec* pos, f32* height, f32 dir);
HitEntry* partySearchGround(PartyEntry* party, f32 up, f32 down);
s32 unk_800c8dd0(HitEntry* hit);
void partyGetAppearPos5(PartyEntry* party, HitEntry* hit, Vec* out);
void partyClearFootmark(void);
void partyClearFootmark2(void);
void unk_800c9044(PartyEntry* party);
void partyChkWall(PartyEntry* party);
void partyChkGnd(PartyEntry* party);
void partyChgRunMode(PartyEntry* party, s32 mode);
void partyMoveBehindMario(PartyEntry* party, s32 a);
s32 marioKeyOffChk(void);
s32 marioChkDeepSleep(void);
s32 chuchu_searchObject(void);
void partyChgPose(PartyEntry* party, const char* pose);
void marioGetScreenPos(Vec pos, f32* x, f32* y, f32* z);
void partyGetReturnPos(Vec* pos);
void unk_800c9398(PartyEntry* party, f32 a);
BOOL partyPaperOn(PartyEntry* party, const char* name);
void partyChgPaper(PartyEntry* party, const char* name);
void partyPaperLightOff(PartyEntry* party);
void marioClearSlitFloor(void);
f32 partyToMovedir(PartyEntry* party, f32 dir);
void movePos(f32* x, f32* z, f32 dist, f32 dir);
void partyMoveCheckWall(PartyEntry* party);
void unk_800c8f24(PartyEntry* party, f32 speed);
void partyChgMoveMode(PartyEntry* party, s32 mode);
void partySetDir(PartyEntry* party, f32 x, f32 z);
void partyMove(PartyEntry* party);
s32 partyGetFootmarkId();
void partyNextReadId(s32 id);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 toMovedir(f32 angle);
void partyGetAppearPos4(PartyEntry* party, Vec* pos);
HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 dir);
void N_partyPlaySfxPartyLanding1(PartyEntry* party);

// Note: the real evt_snd user functions live in this split (see evt_snd.c).
// Functions are defined in reverse order (-inline deferred).

void psndSetReverb(s32 mode);
BOOL psndENVOn(s32 a, s32 b);
BOOL psndENVOn_f_d(s32 a, s32 b, s32 c, s32 d);
BOOL psndENVOff_f_d(s32 a, s32 b, s32 c);
void psndENV_LPF(s32 a, u16 b);
void psndSFX_dist(s32 id, u16 dist);
void psndSFX_pos(s32 id, Vec* pos);
void psndSFX_vol(s32 id, u8 vol);
void psndSFX_pit(s32 id, s16 pit);
s32 psndSFXChk(s32 id);
s32 psndSFXOnEx_3D(const char* name, Vec* pos, u8 a, u8 b, u16 c, u16 d);
s32 psndSFXOn_(const char* name);
void psndBGMScope(s32 a, s32 b);
void psndBGM_rate(s32 a, u16 b);
BOOL psndBGMOn_f_d(s32 a, s32 b, s32 c, s32 d, s32 e);
BOOL psndBGMOff(s32 a);
void unk_800d7270(s32 a, s32 b, s32 c, s32 d);

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmon) {
    s32* args = event->args;
    psndBGMOn(args[0], (char*)args[1]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmon_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    unk_800d7270(a, b, c, 0);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(unk_8014cc24) {
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    evtGetValue(event, args[3]);
    psndBGMOn_f_d(a, b, c, c, 0);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmoff) {
    psndBGMOff(event->args[0]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmoff_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    ((BOOL (*)(s32, s32, s32))psndBGMOff_f_d)(a, t, 0);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgm_freq) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGM_rate(a, t);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgm_scope) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMScope(a, t);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon) {
    s32* args = event->args;
    const char* name = (const char*)args[0];
    s32 out = args[1];
    if (!out) {
        psndSFXOn(name);
    } else {
        evtSetValue(event, out, ((s32 (*)(const char*))psndSFXOn)(name));
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon__) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 out = args[1];
    if (!out) {
        psndSFXOn(name);
    } else {
        evtSetValue(event, out, ((s32 (*)(const char*))psndSFXOn)(name));
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon_) {
    s32* args = event->args;
    const char* name = (const char*)args[0];
    s32 out = args[1];
    if (!out) {
        psndSFXOn_(name);
    } else {
        evtSetValue(event, out, psndSFXOn_(name));
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon_3d) {
    s32* args = event->args;
    const char* name = (const char*)args[0];
    Vec pos;
    s32 out;
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    out = args[4];
    if (!out || out == -250000000) {
        psndSFXOn_3D(name, &pos);
    } else {
        evtSetValue(event, out, psndSFXOn_3D(name, &pos));
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon_3d_ex) {
    s32* args = event->args;
    const char* name = (const char*)args[0];
    Vec pos;
    u16 a, b, c, d;
    s32 out;
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    a = evtGetValue(event, args[4]);
    b = evtGetValue(event, args[5]);
    c = evtGetValue(event, args[6]);
    d = evtGetValue(event, args[7]);
    out = args[8];
    if (!out) {
        psndSFXOnEx_3D(name, &pos, a, b, c, d);
    } else {
        evtSetValue(event, out, psndSFXOnEx_3D(name, &pos, a, b, c, d));
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxoff) {
    psndSFXOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxchk) {
    s32* args = event->args;
    evtSetValue(event, args[1], psndSFXChk(evtGetValue(event, args[0])));
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_pit) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_pit(id, t);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_vol) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_vol(id, t);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_pos) {
    s32* args = event->args;
    Vec pos;
    s32 id = evtGetValue(event, args[0]);
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    psndSFX_pos(id, &pos);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_dist) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    psndSFX_dist(id, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_envon) {
    s32* args = event->args;
    psndENVOn(args[0], args[1]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_envon_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    psndENVOn_f_d(a, b, c, 0);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_envoff) {
    psndENVOff(event->args[0]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_envoff_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndENVOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_env_lpf) {
    s32* args = event->args;
    s32 a = args[0];
    psndENV_LPF(a, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_set_rev_mode) {
    psndSetReverb(event->args[0]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_all_stop) {
    psndSFXAllOff();
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
void unk_8014c47c(void) {
    touch_wall_ct = 60.0f;
}
#endif

#ifdef NONMATCHING
void N_partyFollowCloseOn(PartyEntry* party) {
    party->flags3 |= 0x20000;
}
#endif

#ifdef NONMATCHING
void N_partyFollowCloseOff(PartyEntry* party) {
    party->flags3 &= ~0x20000;
}
#endif

void unk_800c8e74(PartyEntry* party);
void unk_800c93d0(PartyEntry* party, f32 spd);
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
void partyGetAppearPos3(PartyEntry* party, Vec* pos);
s32 marioCtrlOffChk(void);
extern int __float_nan[];
#ifdef NONMATCHING
static inline HitEntry* partyBehindGround(PartyEntry* party) {
    HitEntry* hit = partySearchGround(party, 10.0f, 0.0f);
    if (hit && (hitGetAttr(hit) & 0x200)) {
        hit = NULL;
        if (!party->unk4C) {
            party->flags3 |= 0x1000000;
            party->flags |= 0x2000000;
        }
    }
    return hit;
}
#endif

s32 partyGetFootmarkWriteId(s32 id);
s32 partyGetFootmarkReadId(s32 id);
f32 partyGetTargetDist(s32 id, f32 x, f32 z);
f32 partyGetTargetDir(s32 id, f32 x, f32 z);
f32 partyGetTargetDistY(s32 id);
void partyGetReadId(s32 id, f32* x, f32* y, f32* z);
static f32 partyStayDist(PartyEntry* party);
static u32 partyGetFrontAttr(PartyEntry* party, f32 dir);
static f32 partyHomingOff(PartyEntry* party);
static f32 partyGetGndY(f32 x, f32 y, f32 z);
static f32 partyGetDirGndY(Vec u, f32 md);
static u32 partyGetFrontAttrFar(PartyEntry* party);
static void partyGorFix(PartyEntry* party);
static void partyPoseA2(PartyEntry* party);
s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir);










f32 partyGetTargetDist3D(s32 id, Vec* p);
f32 partyGetTargetDist(s32 id, f32 x, f32 z);
s32 nokonokoGetStatus(PartyEntry* party);
HitEntry* marioChkWallAround(Vec* pos, s32 a, f32 spd, f32 dir, f32 w, f32 h);
s32 marioChkSlitThrouh(void);
void partyGetMoveDirSpd(PartyEntry* party, f32* dir, f32* spd);
PartyEntry* anotherPartyGetPtr(s32 id);
HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 dir);


void party_force_reset_outofscreen(PartyEntry* party);

#ifdef NONMATCHING
void party_motion_stay(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    s32 id;
    PartyEntry* other;
    HitEntry* hit;
    f32 lim;
    f32 x, z;
    f32 dir, spd;
    Vec v;
    Vec p;

    id = partyGetFootmarkId(party);
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        partyChgPoseId(party, 1);
        if (!(party->flags3 & 0x800000)) {
            if (!(party->flags & 8)) {
                partyClearFootmark();
            } else {
                partyClearFootmark2();
            }
        }
        party->flags3 &= ~0x800000;
        party->unk168 = -1;
        unk_800c9398(party, 0.0f);
    }
    if (mario->motionId != 0xE && (party->flags & 0x80000)) {
        party->flags &= ~0x80000;
    }
    lim = party->unk40;
    if (!mario->unk190 && mario->unk180 < 1.0f) {
        lim = 100.0f;
    }
    if ((s8)mario->unk3C == 2) {
        lim = 70.0f;
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12"))
    {
        if (!marioKeyOffChk()) {
            {
                f32 sd;
                if (party->unk32 == 0) {
                    sd = 18.0f;
                } else if (party->currentMemberId == 5) {
                    if (party->flags3 & 0x200000) {
                        sd = 8.0f;
                    } else {
                        sd = 30.0f;
                    }
                } else if (party->currentMemberId == 6) {
                    if (party->flags3 & 0x200000) {
                        sd = 8.0f;
                    } else {
                        sd = 30.0f;
                    }
                }
                lim = sd;
            }
            party->flags3 |= 0x20000;
        }
    }
    if ((party->flags3 >> 17) & 1) {
        {
            f32 sd;
            if (party->unk32 == 0) {
                sd = 18.0f;
            } else if (party->currentMemberId == 5) {
                if (party->flags3 & 0x200000) {
                    sd = 8.0f;
                } else {
                    sd = 30.0f;
                }
            } else if (party->currentMemberId == 6) {
                if (party->flags3 & 0x200000) {
                    sd = 8.0f;
                } else {
                    sd = 30.0f;
                }
            }
            lim = sd;
        }
    }
    party_slit(party);
    party_roll(party);
    unk_800c9044(party);
    if (mario->motionId == 0xE && !(party->flags & 0x80000)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (party->unk34 != 0) {
        if (!party->unk2F || !partyGetPtr(marioGetPartyId())) {
            if (partyChkMarioFollowY(party->playerPtr)) {
                f32 d;
                if (party->unk32 == 0) {
                    p = party->position;
                    d = partyGetTargetDist3D(id, &p);
                    partyGetTargetDist(id, party->position.x, party->position.z);
                } else {
                    x = party->position.x;
                    z = party->position.z;
                    movePos(&x, &z, 0.5f * party->unkF4,
                            angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z));
                    d = distABf(x, z, mario->position.x, mario->position.z);
                }
                if (marioChkSlitThrouh() || d >= lim) {
                    if (!marioChkDeepSleep()) {
                        partyChgMot(party, 1);
                    }
                }
            }
        } else {
            other = anotherPartyGetPtr(party->unk2F);
            if (other) {
                if (nokonokoGetStatus(other) == 3 || PSVECDistance(&mario->position, &other->position) >= 150.0f) {
                    if (partyGetTargetDist(id, party->position.x, party->position.z) >= lim) {
                        partyChgMot(party, 1);
                        partyClearFootmark2();
                    }
                } else if (other->currentMemberId == 3 && other->unk34 == 3) {
                    if (mario->motionId != 0x1F && mario->motionId != 0x10 && mario->motionId != 0x11 &&
                        distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) >= lim)
                    {
                        partyChgMot(party, 1);
                    }
                } else if (!(other->flags & 0x100) || other->currentMemberId == 4) {
                    if (distABf(party->position.x, party->position.z, other->position.x, other->position.z) >= lim) {
                        partyChgMot(party, 1);
                    }
                }
                if (marioChkSlitThrouh()) {
                    partyChgMot(party, 1);
                }
            }
        }
    }
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &spd);
    hit = partySearchFrontWall(party, &v, spd, dir);
    if (hit) {
        party->unk12C = hit;
        if (party->unk104) {
            party->unk134 = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    partyGetMoveDirSpd(party, &dir, &spd);
    marioChkWallAround(&v, 1, spd, dir, party->unkF4, party->unkF0);
    party->position.x = v.x;
    party->position.z = v.z;
    if (party->unk32 == 1) {
        unk_8014b824(party);
        return;
    }
    unk_8014ba3c(party);
    party_force_reset_outofscreen(party);
    if (party->currentMemberId == 7 && !(party->flags2 & 0x8000) && !marioKeyOffChk() && marioChkDeepSleep() != 1 &&
        chuchu_searchObject())
    {
        switch (party->unk39) {
        case 1:
            if (--party->unk24 > 0) {
                break;
            }
            partyChgPoseId(party, 1);
            party->unk24 = 30;
            party->unk39 = 2;
            break;
        case 2:
            if (--party->unk24 > 0) {
                break;
            }
            party->unk39 = 0;
            break;
        case 0:
        default:
            partyPoseA2(party);
            break;
        }
    }
}
#endif

#ifdef NONMATCHING
void unk_8014bbc8(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        partyChgPoseId(party, 1);
        if (!(party->flags & 8)) {
            partyClearFootmark();
        } else {
            partyClearFootmark2();
        }
        party->unk168 = -1;
    }
    party_slit(party);
    party_roll(party);
    unk_800c9044(party);
    if (!(party->flags & 0x1000000)) {
        partyChkWall(party);
    }
    partyChkGnd(party);
    if (distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) > 31.0f) {
        partyChgRunMode(party, 2);
    }
    if (mario->motionId == 0xE && !(party->flags & 0x80000)) {
        partyMoveBehindMario(party, 0);
    } else if (party->unk32 == 1) {
        unk_8014b824(party);
    } else {
        unk_8014ba3c(party);
        if (party->currentMemberId == 7 && !(party->flags2 & 0x8000) && !marioKeyOffChk() &&
            marioChkDeepSleep() != 1 && chuchu_searchObject())
        {
            switch (party->unk39) {
                case 1:
                    if (--party->unk24 <= 0) {
                        partyChgPoseId(party, 1);
                        party->unk24 = 30;
                        party->unk39 = 2;
                    }
                    break;
                case 2:
                    if (--party->unk24 <= 0) {
                        party->unk39 = 0;
                    }
                    break;
                case 0:
                default:
                    partyPoseA2(party);
                    break;
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void unk_8014ba3c(PartyEntry* party) {
    Vec pos;
    f32 height;
    void* head;
    HitEntry* hit;
    s32 attr;

    pos = party->position;
    height = party->unkF0;
    head = partySearchHead(party, &pos, &height, party->unk10C);
    if (head) {
        party->unk140 = head;
    }
    if (party->flags & 0x4000000) {
        return;
    }
    party->flags &= ~0x80;
    hit = partySearchGround(party, 15.0f, -15.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & 0x200) {
            hit = NULL;
            if (!party->unk4C) {
                party->flags3 |= 0x1000000;
                party->flags |= 0x2000000;
            }
        }
    }
    party->unk138 = hit;
    if (!hit) {
        party->flags &= ~2;
        partyChgMot(party, 3);
        party->unk11C = -1.5f;
        return;
    }
    party->position.y = party->unkE4;
    party->flags |= 2;
    if (attr & 0x100) {
        party->flags |= 0x80;
    } else {
        party->flags &= ~0x80;
    }
    if (attr & 0x40000000) {
        party->unk14C = hit;
    }
    if (unk_800c8dd0(hit)) {
        partyGetAppearPos5(party, hit, &party->unk94);
        party->flags3 |= 0x400000;
        party->unk94.y = party->position.y;
        partyChgMot(party, 2);
    }
}
#endif

#ifdef NONMATCHING
static inline BOOL partyChkMarioFollowY(PartyMarioView* mario) {
    if (mario->unk50 != 0 && mario->unk180 == 0.0f) {
        return FALSE;
    }
    if (mario->motionId == 0x1F || mario->motionId == 0x20 || mario->motionId == 0x10 ||
        mario->motionId == 0x11)
    {
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
void unk_8014b824(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    s32 attr;
    f32 target;
    f32 rate;
    f32 diff;
    f32 add;

    if (party->flags & 0x4000000) {
        return;
    }
    hit = partySearchGround(party, 10.0f, 0.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & 0x800) {
            partyChgRunMode(party, 0xD);
            return;
        }
        if (attr & 0x100) {
            party->flags |= 0x80;
        } else {
            party->flags &= ~0x80;
        }
    }
    if (partyChkMarioFollowY(party->playerPtr)) {
        rate = 0.05f;
        if (hit) {
            if (mario->position.y > party->unkE4) {
                target = mario->position.y;
                rate = 0.1f;
            } else {
                target = party->unkE4;
                rate = 0.1f;
            }
            if (party->position.y < party->unkE4) {
                target = 18.5f + party->unkE4;
                rate = 0.1f;
            }
        } else {
            target = mario->position.y;
        }
        add = 5.0f;
        if (party->flags2 & 0x8000) {
            add = 1.0f;
        }
        target += add;
        diff = target - party->position.y;
        if (diff > 5.0f || 0.0f > diff) {
            party->position.y += diff * rate;
        }
    } else {
        if (hit) {
            if (mario->position.y > party->unkE4) {
                target = mario->position.y;
            } else {
                target = party->unkE4;
            }
            if (party->position.y < party->unkE4) {
                target = 18.5f + party->unkE4;
            }
        } else {
            target = party->position.y;
        }
        add = 5.0f;
        if (party->flags2 & 0x8000) {
            add = 1.0f;
        }
        target += add;
        diff = target - party->position.y;
        if (diff > 5.0f || 0.0f > diff) {
            rate = 0.05f;
            party->position.y += diff * rate;
        }
    }
}
#endif

typedef struct PartyFootmark {
    u8 unk0;
    u8 unk1[3];
    Vec pos;
} PartyFootmark;

f32 partyGetTargetMovespd2(PartyEntry* party);
PartyFootmark* partyGetFootmarkPtr(s32 id);
s32 marioGetSlitFloorPos(Vec* pos);
f32 unk_800c9f48(s32 id, f32 y);

PartyMarioView* marioGetPtr(void);
void partyGetReadId2(s32 id, Vec* pos);
void L_getTargetPos(s32 id, Vec* pos);
void partyChkFrontStep(PartyEntry* party, f32 dist, f32* y, f32* a, f32* b);

#ifdef NONMATCHING
void party_motion_homing_walk(PartyEntry* party) {
    HitEntry* hit = NULL;
    s32 id;
    PartyMarioView* mario;
    PartyEntry* other;
    s32 i;
    PartyFootmark* fm;
    PartyMarioView* m3;
    u32 attr;
    f32 lim;
    f32 lim2;
    f32 spd;
    f32 px, py, pz;
    f32 d3;
    f32 a;
    f32 gy;
    f32 md;
    Vec v;
    Vec t;
    Vec tp;
    Vec hp;
    Vec p2;
    Vec p3;
    Vec u;
    f32 sp;
    f32 dir;
    f32 s4;
    f32 c4;
    f32 rx, ry, rz;
    f32 fsy, fsa, fsb;
    f32 c, s;
    f32 s2, c2;
    f32 c3, s3;
    f32 hh;
    HitCheckQuery q;
    HitCheckQuery q2;
    HitCheckQuery q3;

    id = partyGetFootmarkId(party);
    mario = party->playerPtr;
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->flags &= ~0x80000;
    }
    if (party->unk28 != 0) {
        lim = 28.0f;
    } else {
        lim = 37.5f;
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12"))
    {
        if (!marioKeyOffChk()) {
            lim = partyStayDist(party);
            party->flags3 |= 0x20000;
        }
    }
    if (partyGetTargetDistY(id)) {
        lim2 = 50.0f;
    } else {
        lim2 = 35.0f;
    }
    if ((s32)mario->unk3C == 2) {
        lim2 = 70.0f;
    }
    if ((party->flags3 >> 17) & 1) {
        lim2 = partyStayDist(party);
    }
    if (!party_slit(party)) {
        return;
    }
    if (!party_roll(party)) {
        return;
    }
    if (mario->motionId == 0xE && !(party->flags & 0x80000)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (!partyChkMarioFollowY(party->playerPtr)) {
        partyChgMot(party, 0);
        return;
    }
    spd = partyGetTargetMovespd2(party);
    if (!(party->flags & 8)) {
        d3 = PSVECDistance(&mario->position, &party->position);
        if (d3 < 35.0f) {
            spd = 1.0f;
        } else if (d3 >= 50.0f) {
            spd = 3.0f;
        }
        if (party->playerPtr->flags0 & 0x8000) {
            spd = 1.0f;
            lim = 100.0f;
        }
        unk_800c93d0(party, spd);
    } else if ((other = partyGetPtr(marioGetPartyId()))) {
        v = other->position;
        if (nokonokoGetStatus(other) == 3 || PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            d3 = PSVECDistance(&mario->position, &party->position);
            if (d3 < 35.0f) {
                spd = 1.0f;
            } else if (d3 >= 50.0f) {
                spd = 3.0f;
            }
            if (party->playerPtr->flags0 & 0x8000) {
                spd = 1.0f;
            }
            unk_800c93d0(party, spd);
        } else {
            d3 = PSVECDistance(&other->position, &party->position);
            if (d3 < 35.0f) {
                spd = 1.0f;
            } else if (d3 >= 50.0f) {
                spd = 3.0f;
            }
            if (party->playerPtr->flags0 & 0x8000) {
                spd = 1.0f;
            }
            unk_800c93d0(party, spd);
        }
    }
    px = party->position.x;
    i = 0;
    py = party->position.y;
    pz = party->position.z;
    do {
        fm = partyGetFootmarkPtr(id);
        t = fm->pos;
        dir = angleABf(px, pz, t.x, t.z);
        attr = partyGetFrontAttr(party, dir);
        if (!(attr & 0x800)) {
            goto found;
        }
        partyNextReadId(id);
        partyGetReadId2(id, &t);
    } while (++i <= 10);
    t = marioGetPtr()->position;
found:
    p2 = party->position;
    if (partyGetTargetDist3D(id, &p2) >= lim) {
        unk_800c93d0(party, spd);
    }
    if (lim2 < 20.0f) {
        unk_800c93d0(party, spd);
    }
    while (TRUE) {
        d3 = distABf(px, pz, t.x, t.z);
        dir = angleABf(px, pz, t.x, t.z);
        if (mario->flags0 & 0x8000) {
            a = party->unkF4 + mario->unk1B4;
        } else {
            a = 0.5f * party->unkF4 + party->unk104;
        }
        if (d3 > a) {
            p3 = (Vec){px, py, pz};
            d3 = partyGetTargetDist3D(id, &p3);
            if (d3 >= lim) {
                if (party->flags3 & 0x20000) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    unk_800c9398(party, mario->unk180 + a);
                }
                break;
            }
            if (marioGetSlitFloorPos(&v)) {
                unk_800c93d0(party, 1.5f);
                partyNextReadId(id);
                if (marioGetSlitFloorPos(&v)) {
                    t = v;
                    py = distABf(px, pz, t.x, t.z);
                    dir = angleABf(px, pz, t.x, t.z);
                    if (py <= 5.0f) {
                        ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
                    }
                }
                break;
            }
            if (d3 > lim2) {
                if (party->flags3 & 0x20000) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    unk_800c9398(party, mario->unk180 + a);
                } else {
                    a = d3 - lim2;
                    if (a >= 1.0f) {
                        a = 1.0f;
                        if (lim2 < 20.0f) {
                            a = spd;
                        }
                    }
                    unk_800c93d0(party, a);
                }
                break;
            } else if (party->unkA0 == 0.0f && party->unkA8 == 0.0f) {
                unk_800c93d0(party, party->playerPtr->unk180);
            } else {
                unk_800c9398(party, 0.0f);
                party->unk100 = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
                partyChgPoseId(party, 1);
            }
        }
        if (partyGetFootmarkReadId(id) == (i = partyGetFootmarkWriteId(id))) {
            unk_800c93d0(party, party->playerPtr->unk180);
            if (party->playerPtr->unk180 == 0.0f || party->unkA0 != 0.0f || party->unkA8 != 0.0f) {
                dir = party->unk100;
                unk_800c93d0(party, 0.0f);
                party->unk11C = 0.0f;
                if (!(party->flags & 0x200)) {
                    partyChgPoseId(party, 1);
                }
                partyChgMot(party, 0);
            }
            break;
        }
        partyNextReadId(id);
        partyGetReadId2(id, &t);
        if (!(party->flags & 0x4000000)) {
            party->flags &= ~0x80;
            hit = partySearchGround(party, 10.0f, 0.0f);
            if (hit && (hitGetAttr(hit) & 0x200)) {
                hit = NULL;
                if (!party->unk4C) {
                    party->flags3 |= 0x1000000;
                    party->flags |= 0x2000000;
                }
            }
            party->unk138 = hit;
            if (!hit) {
                partyChgMot(party, 3);
                party->unk11C = -1.0f;
            } else {
                attr = hitGetAttr(hit);
                if (attr & 0x100) {
                    party->flags |= 0x80;
                } else {
                    party->flags &= ~0x80;
                }
                if (attr & 0x800) {
                    partyChgMot(party, 0);
                    break;
                }
            }
        }
        if ((party->flags & 2) && (fm->unk0 & 1)) {
            md = toMovedir(party->unk110);
            partyGetReadId(id, &rx, &ry, &rz);
            L_getTargetPos(id, &tp);
            if (tp.y < ry) {
                ry = tp.y;
            }
            party->unk94.x = rx;
            party->unk94.z = rz;
            party->unk94.y = ry;
            gy = partyGetDirGndY(party->unk94, md);
            if (gy > party->position.y) {
                dir = partyToMovedir(party, party->unk110);
                sincosf(&s4, &c4, dir);
                { f32 k = 40.0f;
                party->unk94.x = s4 * k;
                party->unk94.z = c4 * k; }
                party->unk94.y = gy;
            }
            partyChgMot(party, 2);
            break;
        }
        if (unk_800c8dd0(hit)) {
            partyGetAppearPos5(party, hit, &party->unk94);
            party->flags3 |= 0x400000;
            partyChgMot(party, 2);
            break;
        }
        if ((party->flags & 2) && (fm->unk0 & 4)) {
            if (distABf(px, pz, t.x, t.z) <= 5.0f) {
                ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
            }
            break;
        }
    }
    if (party->unk104) {
        unk_800c8f24(party, party->unk104);
    } else if (!(fm->unk0 & 4)) {
        partyChgMot(party, 0);
    }
    party->unk100 = dir;
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &sp);
    hit = partySearchFrontWall(party, &v, sp, dir);
    if (party->flags & 0x1000000) {
        hit = NULL;
    }
    if (!hit) {
        party->unk4D = 0;
        if (!(party->flags3 & 0x200000)) {
            getFrontFloor(party, &t, party->unk100);
        } else {
            party->unk54 = revise360(270.0f + mario->unk198);
            partyGetAppearPos4(party, &t);
        }
        if (t.y > party->position.y) {
            a = t.y - party->position.y;
            if (a > 12.0 && a < 60.0f) {
                party->unk94 = t;
                partyChgMot(party, 2);
                return;
            }
            if (t.y > party->position.y) {
                party->position.y = t.y;
            }
        }
        if (party->unk104) {
            attr = partyGetFrontAttrFar(party);
            if (!(attr & 0x200)) {
                v.x = party->position.x;
                v.z = party->position.z;
                movePos(&v.x, &v.z, party->unk104, party->unk100);
            }
        }
    } else {
        party->unk12C = hit;
        if (party->unk104) {
            party->unk134 = hit;
            if (hitGetAttr(hit) & 0x2000) {
                if (party->unk37 != 1) {
                    if (!(party->playerPtr->flags & 0x80000000)) {
                        party->flags3 |= 1;
                        party->unk37 = 1;
                    }
                } else if (party->unk104) {
                    v.x = party->position.x;
                    v.z = party->position.z;
                    movePos(&v.x, &v.z, party->unk104, party->unk100);
                }
            } else {
                party->unk4D++;
                if (party->unk4D > 8) {
                    party->unk4D = 0;
                    if (unk_800c9f48(id, party->position.y) >= 1.0f) {
                        getFrontFloor(party, &t, party->unk100);
                        if (t.y - party->position.y > 5.0f) {
                            party->unk94 = t;
                            partyChgMot(party, 2);
                            return;
                        }
                        if (!(party->flags & 0x30)) {
                            partyChkFrontStep(party, 11.0f, &fsy, &fsa, &fsb);
                            if (fsy - party->position.y >= 5.0f && party->unkE0 <= 30.0f) {
                                party->unk120 = fsy;
                                if (party->unk104) {
                                    partyChgMot(party, 6);
                                    return;
                                }
                            }
                        }
                    } else {
                        dir = partyGetTargetDir(id, party->position.x, party->position.z);
                        getFrontFloor(party, &t, dir);
                        a = t.y - party->position.y;
                        if (a > 100.0f) {
                            party->position = t;
                            partyChgMot(party, 1);
                        } else if (a >= 0.0f) {
                            party->unk94 = t;
                            partyChgMot(party, 2);
                        } else {
                            partyChgMot(party, 0);
                        }
                    }
                }
            }
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    hh = party->unkF0;
    hp = party->position;
    hit = partySearchHead(party, &hp, &hh, party->unk10C);
    if (hit) {
        party->unk140 = hit;
    }
    party->flags &= ~0x80;
    hit = partySearchGround(party, 10.0f, 10.0f);
    v.y = party->unkE4;
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & 0x200) {
            hit = NULL;
            if (!party->unk4C) {
                party->flags3 |= 0x1000000;
                party->flags |= 0x2000000;
            }
        } else if (attr & 0x800) {
            partyChgRunMode(party, 13);
            return;
        }
    }
    party->unk138 = hit;
    if (!hit) {
        partyChgMot(party, 3);
        party->unk11C = -1.0f;
    } else {
        if (hitGetAttr(hit) & 0x100) {
            party->flags |= 0x80;
        } else {
            party->flags &= ~0x80;
        }
        if (hitGetAttr(hit) & 0x40000000) {
            party->unk14C = hit;
        }
    }
    party->position.y = v.y;
    party_force_reset_outofscreen(party);
    partyGorFix(party);
}
#endif

#ifdef NONMATCHING
void party_motion_homing_fly(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    s32 id;
    s32 near;
    s32 w;
    HitEntry* hit;
    PartyMarioView* m2;
    PartyFootmark* fm;
    u32 attr;
    f32 lim;
    f32 lim2;
    f32 spd;
    f32 px, py, pz;
    f32 d3;
    f32 dd;
    f32 a;
    f32 off;
    f32 gy;
    Vec v;
    Vec s2;
    Vec ap;
    Vec ff;
    Vec p2;
    Vec p3;
    f32 dir, sp;
    f32 tx, ty, tz;
    f32 x, z;

    id = partyGetFootmarkId(party);
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->flags &= ~0x80000;
        party->unk4E = 0;
    }
    if (party->unk28 != 0) {
        lim = 28.0f;
    } else {
        lim = 32.0f;
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12"))
    {
        if (!marioKeyOffChk()) {
            lim = partyStayDist(party);
            party->flags3 |= 0x20000;
        }
    }
    if (partyGetTargetDistY(id)) {
        lim2 = 50.0f;
    } else {
        lim2 = 35.0f;
    }
    if ((party->flags3 >> 17) & 1) {
        lim2 = partyStayDist(party);
    }
    if (!party_slit(party)) {
        return;
    }
    if (!party_roll(party)) {
        return;
    }
    if (mario->motionId == 0xE && !(party->flags & 0x80000)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (!partyChkMarioFollowY(party->playerPtr)) {
        partyChgMot(party, 0);
        return;
    }
    spd = partyGetTargetMovespd2(party);
    d3 = PSVECDistance(&mario->position, &party->position);
    if (d3 < 35.0f) {
        spd = 1.0f;
    } else if (d3 >= 50.0f) {
        spd = 3.0f;
    }
    if (party->playerPtr->flags0 & 0x8000) {
        spd = 1.0f;
        lim = 100.0f;
    }
    unk_800c93d0(party, spd);
    px = party->position.x;
    py = party->position.y;
    pz = party->position.z;
    fm = partyGetFootmarkPtr(id);
    tx = fm->pos.x;
    off = partyHomingOff(party);
    ty = fm->pos.y + off;
    tz = fm->pos.z;
    p2 = party->position;
    if (partyGetTargetDist3D(id, &p2) >= lim) {
        unk_800c93d0(party, spd);
    }
    if (lim2 < 20.0f) {
        unk_800c93d0(party, spd);
    }
    near = 0;
    while (TRUE) {
        dir = angleABf(px, pz, tx, tz);
        dd = distABf(px, pz, tx, tz);
        if (mario->flags0 & 0x8000) {
            a = party->unkF4 + mario->unk1B4;
        } else {
            a = 0.5f * party->unkF4 + party->unk104;
        }
        if (dd > a) {
            p3 = (Vec){px, py, pz};
            d3 = partyGetTargetDist3D(id, &p3);
            if (d3 >= lim) {
                if (party->flags3 & 0x20000) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    unk_800c9398(party, mario->unk180 + a);
                }
                near = 1;
                break;
            }
            if (marioGetSlitFloorPos(&v)) {
                unk_800c93d0(party, 1.5f);
                partyNextReadId(id);
                if (marioGetSlitFloorPos(&v)) {
                    s2 = v;
                    py = distABf(px, pz, s2.x, s2.z);
                    dir = angleABf(px, pz, s2.x, s2.z);
                    if (py <= 5.0f) {
                        ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
                    }
                }
                break;
            }
            if (d3 > lim2) {
                if (party->flags3 & 0x20000) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    unk_800c9398(party, mario->unk180 + a);
                } else {
                    a = d3 - lim2;
                    if (a >= 1.0f) {
                        a = 1.0f;
                        if (lim2 < 20.0f) {
                            a = spd;
                        }
                    }
                    unk_800c93d0(party, a);
                    break;
                }
            } else if (party->unkA0 == 0.0f && party->unkA8 == 0.0f) {
                unk_800c93d0(party, party->playerPtr->unk180);
            } else {
                unk_800c9398(party, 0.0f);
                party->unk100 = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
                partyChgPoseId(party, 1);
            }
        }
        if (partyGetFootmarkReadId(id) == (w = partyGetFootmarkWriteId(id))) {
            unk_800c93d0(party, party->playerPtr->unk180);
            if (party->playerPtr->unk180 == 0.0f || party->unkA0 != 0.0f || party->unkA8 != 0.0f) {
                dir = party->unk100;
                unk_800c93d0(party, 0.0f);
                party->unk11C = 0.0f;
                if (!(party->flags & 0x200)) {
                    partyChgPoseId(party, 1);
                }
                partyChgMot(party, 0);
            }
            break;
        }
        partyNextReadId(id);
        partyGetReadId(id, &tx, &ty, &tz);
        if (party->flags & 0x4000000) {
            continue;
        }
        party->flags &= ~0x80;
        hit = partySearchGround(party, 100.0f, 100.0f);
        if (hit && (hitGetAttr(hit) & 0x200)) {
            hit = NULL;
        }
        party->unk138 = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->unk11C = -1.0f;
            continue;
        }
        attr = hitGetAttr(hit);
        if (attr & 0x100) {
            party->flags |= 0x80;
        } else {
            party->flags &= ~0x80;
        }
        if (attr & 0x800) {
            partyChgMot(party, 0);
            break;
        }
    }
    if (party->unk104) {
        unk_800c8f24(party, party->unk104);
    } else {
        partyChgMot(party, 0);
    }
    if (party->unk4E > 10) {
        dir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
    }
    if (near) {
        m2 = party->playerPtr;
        partyGetAppearPos3(party, &ap);
        dir = angleABf(party->position.x, party->position.z, ap.x, ap.z);
        hit = partySearchGround(party, 10.0f, 0.0f);
        ap.y = party->unkE4;
        if (hit && (hitGetAttr(hit) & 0x200)) {
            hit = NULL;
        }
        if (hit) {
            party->position.y = ap.y;
        } else {
            off = partyHomingOff(party);
            party->position.y += 0.05f * ((m2->position.y + off) - party->position.y);
        }
    }
    party->unk100 = dir;
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &sp);
    hit = partySearchFrontWall(party, &v, sp, dir);
    if (party->flags & 0x1000000) {
        hit = NULL;
    }
    if (!hit) {
        if (!(party->flags3 & 0x200000)) {
            getFrontFloor(party, &ff, party->unk100);
        } else {
            party->unk54 = revise360(270.0f + mario->unk198);
            partyGetAppearPos4(party, &ff);
        }
        if (ff.y >= mario->position.y) {
            off = partyHomingOff(party);
            party->position.y += 0.05f * ((ff.y + off) - party->position.y);
        }
        party->unk4E = 0;
        if (party->unk104) {
            v.x = party->position.x;
            v.z = party->position.z;
            movePos(&v.x, &v.z, party->unk104, party->unk100);
        }
    } else {
        party->unk12C = hit;
        if (party->unk104) {
            party->unk134 = hit;
            if (hitGetAttr(hit) & 0x2000) {
                if (party->unk37 != 1) {
                    if (!(party->playerPtr->flags & 0x80000000)) {
                        party->flags3 |= 1;
                        party->unk37 = 1;
                    }
                } else if (party->unk104) {
                    v.x = party->position.x;
                    v.z = party->position.z;
                    movePos(&v.x, &v.z, party->unk104, party->unk100);
                }
            } else {
                x = party->position.x;
                gy = party->position.y;
                z = party->position.z;
                movePos(&x, &z, party->unkF4, dir);
                gy = partyGetGndY(x, gy, z);
                if (gy > -2000.0f) {
                    party->position.y += 0.05f * ((gy + party->unkF0) - party->position.y);
                } else {
                    party->unk4E++;
                    if (unk_800c9f48(id, party->position.y) >= 1.0f &&
                        __fabsf(mario->position.y - party->position.y) >= 10.0f)
                    {
                        party->position.y = party->position.y + 0.1f * ((10.0f + mario->position.y) - party->position.y);
                        party->position.x = v.x;
                        party->position.z = v.z;
                        return;
                    }
                }
            }
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    party->flags &= ~0x80;
    hit = partySearchGround(party, 10.0f, 10.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & 0x800) {
            partyChgRunMode(party, 13);
            return;
        }
        if (attr & 0x100) {
            party->flags |= 0x80;
        } else {
            party->flags &= ~0x80;
        }
    }
    party_force_reset_outofscreen(party);
}
#endif

#ifdef NONMATCHING
void party_set_behind_dir(PartyEntry* party, f32 dir) {
    party->unk54 = revise360(dir + ((PartyCamView*)camGetPtr((CameraId)4))->unk114);
    party->flags3 |= 0x100000;
}
#endif

#ifdef NONMATCHING
static inline f32 partyGetFollowDir(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    PartyEntry* other;
    if (!(party->flags & 8)) {
        return toMovedir(mario->unk1A8);
    }
    other = partyGetPtr(marioGetPartyId());
    if (other) {
        return partyToMovedir(party, other->unk10C);
    }
    return toMovedir(mario->unk1A8);
}
#endif

void partyGetMoveDirSpd(PartyEntry* party, f32* dir, f32* spd);
PartyEntry* anotherPartyGetPtr(s32 id);

#ifdef NONMATCHING
void party_motion_behind_mario(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    f32 ang;
    f32 gy;
    f32 dist;
    f32 thr;
    f32 ty;
    f32 x, z;
    Vec target;

    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->flags3 |= 0x40000;
        if (!(party->flags3 & 0x100000)) {
            {
            f32 t;
            if (!(party->flags3 & 0x10000)) {
                t = partyGetFollowDir(party); t += 180.0f; t = revise360(t);
            } else {
                party->flags3 &= ~0x10000;
                t = revise360(180.0f + angleABf(mario->position.x, mario->position.z, party->unk94.x, party->unk94.z));
            }
            party->unk54 = t;
            }
        }
        partyGetAppearPos4(party, &target);
        party->unk24 = distABf(party->position.x, party->position.z, target.x, target.z);
        if (party->unk24 <= 0) {
            party->unk24 = 1;
        }
    }
    if (!(party->flags3 & 0x100000) && marioKeyOffChk()) {
        { f32 t2 = partyGetFollowDir(party); t2 += 180.0f; party->unk54 = revise360(t2); }
    }
    partyGetAppearPos4(party, &target);
    x = target.x;
    z = target.z;
    ty = target.y;
    ang = angleABf(party->position.x, party->position.z, x, z);
    {
        f32 py = ty;
        f32 nz, ny, nx, dd, hz, hy, hx;
        py += touch_wall_ct;
        dd = 1000.0f;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
        if (!hit) {
            gy = -2000.0f;
        } else {
            gy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            hitGetAttr(hit);
        }
    }
    if (gy <= -2000.0f) {
        gy = 1.5f * mario->unk1B4;
        movePos(&x, &z, gy, toMovedir(mario->unk1A8));
    }
    thr = 2.0f;
    if (mario->unk180 > 1.0f) {
        thr = 10.0f;
    }
    dist = distABf(party->position.x, party->position.z, x, z);
    party->unk24--;
    if (dist >= thr && party->unk24 > 0) {
        party->unk100 = angleABf(party->position.x, party->position.z, x, z);
        distABf(party->position.x, party->position.z, x, z);
        unk_800c9398(party, (party->flags3 & 0x100000) ? 3.6f : 2.0f);
        partyMoveCheckWall(party);
        unk_800c8f24(party, party->unk104);
        if (party->unk12C) {
            x = party->position.x;
            z = party->position.z;
            movePos(&x, &z, dist, ang);
            angleABf(party->position.x, party->position.z, x, z);
            {
                f32 py = ty;
                f32 GG;
                f32 nz, ny, nx, dd, hz, hy, hx;
                py += touch_wall_ct;
                dd = 1000.0f;
                hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
                if (!hit) {
                    GG = -2000.0f;
                } else {
                    GG = (s32)(100.0f * hy + 0.5f) / 100.0f;
                    hitGetAttr(hit);
                }
                thr = GG;
            }
            if (__fabsf(party->position.y - thr) > 1.0f) {
                party->unk94.x = x;
                party->unk94.y = thr;
                party->unk94.z = z;
                partyChgMot(party, 2);
                return;
            }
        } else if (ty > party->position.y) {
            x = party->position.x;
            z = party->position.z;
            movePos(&x, &z, dist, ang);
            angleABf(party->position.x, party->position.z, x, z);
            {
                f32 py = ty;
                f32 GG;
                f32 nz, ny, nx, dd, hz, hy, hx;
                py += touch_wall_ct;
                dd = 1000.0f;
                hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
                if (!hit) {
                    GG = -2000.0f;
                } else {
                    GG = (s32)(100.0f * hy + 0.5f) / 100.0f;
                    hitGetAttr(hit);
                }
                thr = GG;
            }
            if (__fabsf(party->position.y - thr) > 1.0f) {
                party->unk94.x = x;
                party->unk94.y = thr;
                party->unk94.z = z;
                partyChgMot(party, 2);
                return;
            }
        }
        hit = partyBehindGround(party);
        party->unk138 = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->unk11C = -1.0f;
        }
        party->position.y = party->unkE4;
    } else {
        party->unk24 = 0;
        if (party->flags3 & 0x200000) {
            party->flags3 &= ~0x20000;
        }
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->unk40 = 50.0f;
        party->flags2 &= ~0x10;
        party->flags |= 0x80000;
        party->flags3 &= ~0x100000;
        party->flags3 &= ~0x40000;
    }
    if (party->unk134) {
        party->flags |= 0x80000;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, x, z);
        party->unk40 = 50.0f;
        party->flags2 &= ~0x10;
        party->flags3 &= ~0x40000;
    }
}
#endif

#ifdef NONMATCHING
void party_motion_behind_mario_continue(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    PartyEntry* other;
    HitEntry* hit;
    f32 y;
    f32 gy;
    f32 sp;
    f32 thr;
    f32 x, z;

    { f32 t = partyGetFollowDir(party); t += 180.0f; party->unk54 = revise360(t); }
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        sp = 1.5f * mario->unk1B4;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, party->unk54);
        party->unk24 = distABf(party->position.x, party->position.z, x, z);
        if (party->unk24 <= 0) {
            party->unk24 = 1;
        }
    }
    if (marioKeyOffChk()) {
        { f32 t = partyGetFollowDir(party); t += 180.0f; party->unk54 = revise360(t); }
    }
    if (!(party->flags & 8)) {
        sp = 1.5f * mario->unk1B4;
        x = mario->position.x;
        z = mario->position.z;
        y = mario->position.y;
    } else {
        sp = 1.5f * mario->unk1B4;
        other = anotherPartyGetPtr(party->unk2F);
        if (other) {
            x = other->position.x;
            z = other->position.z;
            y = other->position.y;
        } else {
            x = mario->position.x;
            z = mario->position.z;
            y = mario->position.y;
        }
    }
    movePos(&x, &z, sp, party->unk54);
    angleABf(party->position.x, party->position.z, x, z);
    {
        f32 py = y;
        f32 nz, ny, nx, dist, hz, hy, hx;
        py += touch_wall_ct;
        dist = 1000.0f;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
        if (!hit) {
            gy = -2000.0f;
        } else {
            gy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            hitGetAttr(hit);
        }
    }
    if (gy <= -2000.0f) {
        sp = 1.5f * mario->unk1B4;
        movePos(&x, &z, sp, toMovedir(mario->unk1A8));
    }
    thr = 2.0f;
    if (mario->unk180 > 1.0f) {
        thr = 10.0f;
    }
    sp = distABf(party->position.x, party->position.z, x, z);
    party->unk24--;
    if (sp >= thr) {
        party->unk100 = angleABf(party->position.x, party->position.z, x, z);
        sp = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (sp > 2.0f) {
            sp = 2.0f;
        }
        if (sp < 1.0f) {
            sp = 1.0f;
        }
        unk_800c9398(party, sp);
        partyMoveCheckWall(party);
        unk_800c8f24(party, party->unk104);
        hit = partyBehindGround(party);
        party->unk138 = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->unk11C = -1.0f;
        }
        party->position.y = party->unkE4;
    } else {
        party->unk24 = 0;
        if (mario->unk180 == 0.0f) {
            party->flags |= 0x80000;
            partyChgMoveMode(party, 1);
            partyChgMot(party, 0);
            partySetDir(party, mario->position.x, mario->position.z);
            party->unk40 = 50.0f;
            party->flags2 &= ~0x10;
        }
    }
    if (party->unk134) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, x, z);
        party->unk40 = 50.0f;
        party->flags2 &= ~0x10;
    }
}
#endif

#ifdef NONMATCHING
void party_motion_behind_mario_fly(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    f32 thr;
    f32 spd;
    f32 dist;
    Vec pos;
    f32 sp, dir;

    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->flags3 |= 0x40000;
        if (!(party->flags3 & 0x100000)) {
            {
            f32 t;
            if (!(party->flags3 & 0x10000)) {
                t = partyGetFollowDir(party); t += 180.0f; t = revise360(t);
            } else {
                party->flags3 &= ~0x10000;
                t = revise360(angleABf(mario->position.x, mario->position.z, party->unk94.x, party->unk94.z) + 180.0f);
            }
            party->unk54 = t;
            }
        }
        partyGetAppearPos4(party, &party->unk94);
        party->unk24 = distABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
        if (party->unk24 <= 0) {
            party->unk24 = 1;
        }
    }
    if (!(party->flags3 & 0x100000) && marioKeyOffChk()) {
        f32 t2 = partyGetFollowDir(party); t2 += 180.0f; party->unk54 = revise360(t2);
    }
    angleABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
    if (mario->unk180 > 1.0f) {
        thr = 6.0f;
    } else {
        thr = 2.0f;
    }
    dist = distABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
    party->unk24--;
    if ((dist >= thr || __fabsf(party->unk94.y - party->position.y) > 2.0f) && party->unk24 > 0) {
        party->unk100 = angleABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
        distABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
        if (party->flags3 & 0x100000) {
            spd = 3.6f;
        } else {
            spd = 2.0f;
        }
        if (dist < thr) {
            spd = 0.0f;
            unk_800c9398(party, spd);
        }
        unk_800c93d0(party, spd);
        pos = party->position;
        partyGetMoveDirSpd(party, &dir, &sp);
        hit = partySearchFrontWall(party, &pos, sp, dir);
        if (hit) {
            party->unk12C = hit;
            if (party->unk104) {
                party->unk134 = hit;
            }
        }
        party->position.x = pos.x;
        party->position.z = pos.z;
        party->position.y += 0.05f * (party->unk94.y - party->position.y);
        unk_800c8f24(party, party->unk104);
        return;
    }
    party->unk24 = 0;
    if (party->flags3 & 0x200000) {
        party->flags3 &= ~0x20000;
        if (party->unk32 == 1) {
            party->flags2 &= ~0x10;
        }
    }
    partyChgMoveMode(party, 1);
    partyChgMot(party, 0);
    partySetDir(party, mario->position.x, mario->position.z);
    party->unk40 = 50.0f;
    party->flags2 &= ~0x10;
    unk_800c9398(party, 0.0f);
    party->flags |= 0x80000;
    party->flags3 &= ~0x100000;
    party->flags3 &= ~0x40000;
    unk_800c8e74(party);
    if (party->unk134) {
        party->flags |= 0x80000;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->unk40 = 50.0f;
        party->flags2 &= ~0x10;
        party->flags3 &= ~0x40000;
    }
    hit = partySearchGround(party, 100.0f, 100.0f);
    if (hit) {
        if (hitGetAttr(hit) & 0x200) {
            hit = NULL;
            if (!party->unk4C) {
                party->flags3 |= 0x1000000;
                party->flags |= 0x2000000;
            }
        }
        if (dist > party->unkF0) {
            hit = NULL;
        }
        party->position.y += 0.05f * (party->unkE4 - party->position.y);
    }
    party->unk138 = hit;
}
#endif

#ifdef NONMATCHING
void party_motion_beside_mario(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    f32 x, z;
    f32 y;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 thr;
    f32 sp;
    f32 t;

    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        t = partyGetFollowDir(party); t += 90.0f; party->unk54 = revise360(t);
        sp = 1.5f * mario->unk1B4;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, party->unk54);
        party->unk24 = distABf(party->position.x, party->position.z, x, z);
        if (party->unk24 <= 0) {
            party->unk24 = 1;
        }
    }
    if (marioKeyOffChk()) {
        t = partyGetFollowDir(party); t += 90.0f; party->unk54 = revise360(t);
    }
    sp = 1.5f * mario->unk1B4;
    x = mario->position.x;
    z = mario->position.z;
    y = mario->position.y;
    movePos(&x, &z, sp, party->unk54);
    angleABf(party->position.x, party->position.z, x, z);
    y = partyGetGndY(x, y, z);
    if (y <= -2000.0f) {
        sp = 1.5f * mario->unk1B4;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, toMovedir(mario->unk1A8));
    }
    thr = 2.0f;
    if (mario->unk180 > 1.0f) {
        thr = 10.0f;
    }
    sp = distABf(party->position.x, party->position.z, x, z);
    party->unk24--;
    if (sp >= thr && party->unk24 > 0) {
        party->unk100 = angleABf(party->position.x, party->position.z, x, z);
        sp = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (sp > 2.0f) {
            sp = 2.0f;
        }
        if (sp < 1.0f) {
            sp = 1.0f;
        }
        unk_800c9398(party, sp);
        partyMoveCheckWall(party);
        unk_800c8f24(party, party->unk104);
        hit = partySearchGround(party, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & 0x200)) {
            hit = NULL;
            if (!party->unk4C) {
                party->flags3 |= 0x1000000;
                party->flags |= 0x2000000;
            }
        }
        party->unk138 = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->unk11C = -1.0f;
        }
        party->position.y = party->unkE4;
    } else {
        party->unk24 = 0;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->unk40 = 50.0f;
        party->flags2 &= ~0x10;
        party->flags |= 0x80000;
    }
    if (party->unk134) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->unk40 = 50.0f;
        party->flags2 &= ~0x10;
    }
}
#endif

#ifdef NONMATCHING
static inline void partyJumpWallMove(PartyEntry* party) {
    Vec v;
    HitEntry* hit;

    if (party->flags & 0x1000000) {
        movePos(&v.x, &v.z, party->unk104, party->unk100);
        return;
    }
    v = party->position;
    hit = partySearchFrontWall(party, &v, party->unk104, party->unk100);
    if (hit) {
        party->unk12C = hit;
        if (party->unk104) {
            party->unk134 = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
}
#endif

#ifdef NONMATCHING
void party_motion_jump(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    s32 id;
    s32 w;
    HitEntry* hit;
    f32 dir;
    f32 dist;
    f32 lim;
    f32 t, dy, g;
    Vec fl;
    f32 s, c;
    f32 x, y, z;

    id = partyGetFootmarkId(party);
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->unk38 = 0;
    }
    if (party->unk38 == 0) {
        x = party->unk94.x;
        y = party->unk94.y;
        z = party->unk94.z;
        if (party->unk28 != 0 || party->unk34 == 9) {
            x = party->position.x;
            y = party->position.y;
            z = party->position.z;
            movePos(&x, &z, party->unk104, party->unk100);
            party->unk94 = (Vec){x, y, z};
        } else if (!(party->flags3 & 0x400000)) {
            if (partyGetFootmarkReadId(id) == partyGetFootmarkWriteId(id)) {
                if (partyGetTargetDist(id, party->position.x, party->position.z) > 2.0f * mario->unk1B4) {
                    dir = partyGetTargetDir(id, party->position.x, party->position.z);
                    getFrontFloor(party, &fl, dir);
                    fl.y += 10.0f;
                    y = fl.y;
                    x = party->position.x;
                    z = party->position.z;
                    movePos(&x, &z, 0.6f * party->unkF4, dir);
                }
                party->unk94 = (Vec){x, y, z};
            } else {
                partyGetReadId(id, &x, &y, &z);
                lim = 50.0f;
                dist = distABf(party->position.x, party->position.z, x, z);
                if (50.0f > 1.4f * (y - party->position.y)) {
                    lim = 1.4f * (y - party->position.y);
                }
                sincosf(&s, &c, angleABf(party->position.x, party->position.z, x, z));
                if (dist > lim) {
                    dist = lim;
                    if (partyGetTargetDistY(id) == 0.0f) {
                        dist = 0.0f;
                    }
                    x = party->position.x;
                    z = party->position.z;
                    x = x + dist * s;
                    z = z + dist * c;
                    y += 10.0f;
                    party->unk94 = (Vec){x, y, z};
                } else {
                    if (partyGetTargetDistY(id) == 0.0f) {
                        dist = 0.0f;
                    }
                    x = x + dist * s;
                    z = z + dist * c;
                    party->unk94 = (Vec){x, y, z};
                }
                if (dist < lim) {
                    partyNextReadId(id);
                }
            }
        }
        party->unk128 = distABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
        if (party->unk28 == 0) {
            party->unk100 = angleABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
            party->unk104 = 2.25f * party->playerPtr->unk224;
        }
        party->unk24 = (10.0f * (0.9f * (party->unk128 / party->unk104)) + 0.5f) / 10.0f;
        if (party->unk24 < 12) {
            party->unk24 = 12;
        }
        if (party->unk24 > 40) {
            party->unk24 = 40;
        }
        dy = party->unk94.y - party->position.y;
        t = 0.5f * party->unk24;
        if (__fabsf(dy) < 1.0f) {
            dy = 25.0f;
        } else if (dy < 0.0f) {
            dy = 10.0f;
        }
        g = (dy + dy) / (t * t - t);
        party->unk114 = mario->unk224 * (g * t);
        if (party->unk114 > 13.0f) {
            party->unk114 = 13.0f;
        }
        if (party->unk114 < 3.0f) {
            party->unk114 = 3.0f;
        }
        party->unk11C = -g * mario->unk224;
        party->flags |= 0x10;
        party->flags &= ~2;
        partyChgPoseId(party, 4);
        psndSFXOn_3D((const char*)0x927, &party->position);
        party->unk38 = 10;
        if (!(party->flags & 8)) {
            partyNextReadId(partyGetFootmarkId(party));
        }
    } else if (party->unk38 == 10) {
        if (!(party->flags & 8)) {
            partyNextReadId(partyGetFootmarkId(party));
        }
        party->unk114 += party->unk11C;
        party->position.y += party->unk114;
        if (party->position.y < -2000.0f) {
            party->flags &= ~0x10;
            party->unk114 = 0.0f;
            party->unk100 = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
            party->position = mario->position;
            partyChgMot(party, 0);
            return;
        }
        if (party->unk114 <= 0.0f) {
            party->flags &= ~0x10;
            party->flags |= 0x20;
            hit = partySearchGround(party, __fabsf(party->unk114), 0.0f);
            if (hit && (hitGetAttr(hit) & 0x200)) {
                if (!party->unk4C) {
                    party->flags3 |= 0x1000000;
                    party->flags |= 0x2000000;
                }
                party->unk138 = NULL;
                partyChgMot(party, 3);
                party->unk11C = -1.0f;
                return;
            }
            party->unk138 = hit;
            party->position.y = party->unkE4;
            if (hit) {
                party->flags |= 2;
                party->flags &= ~0x70;
                N_partyPlaySfxPartyLanding1(party);
                party->unk114 = 0.0f;
                partyChgMot(party, 0);
                party->flags3 |= 0x800000;
                return;
            }
        }
        partyJumpWallMove(party);
    }
}
#endif

#ifdef NONMATCHING
void party_motion_jump2(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    Vec pos;
    f32 dist;
    f32 dy;
    f32 fr;
    s32 frames;

    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->unk24 = 0;
        party->unk11C = -1.0f * mario->unk224;
        party->unk104 = 2.25f * mario->unk224;
        party->unk100 = angleABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
        dist = distABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z);
        if (dist > 50.0f) {
            dist = 50.0f;
        }
        party->unk128 = dist;
        dy = party->unk94.y - party->position.y;
        frames = (10.0f * (dist / party->unk104) + 0.5f) / 10.0f;
        if (frames < 10) {
            frames = 10;
        }
        fr = frames;
        party->unk24 = frames;
        party->unk104 = mario->unk224 * (party->unk128 / fr);
        party->unk114 = (0.5f * (fr * (fr * __fabsf(party->unk11C))) + dy) / fr;
        party->unk114 *= mario->unk224;
        if (party->unk114 > 20.0f) {
            party->unk114 = 20.0f;
        }
        if (party->unk114 < 0.0f) {
            party->unk114 = 0.0f;
        }
        partyChgPoseId(party, 4);
        party->flags |= 0x10;
        party->flags &= ~2;
        psndSFXOn_3D((const char*)0x927, &party->position);
        party->unk38 = 0;
    }
    switch (party->unk38) {
        case 0:
            party->unk38 = 1;
            break;
        case 1:
            party->unk114 += party->unk11C;
            party->position.y += party->unk114;
            pos = party->position;
            partySearchFrontWall(party, &pos, party->unk104, party->unk100);
            party->position.x = pos.x;
            party->position.z = pos.z;
            if (party->unk114 <= 0.0f) {
                hit = partySearchGround(party, __fabsf(party->unk114), 0.0f);
                pos.y = party->unkE4;
                if (hit && (hitGetAttr(hit) & 0x200)) {
                    if (!party->unk4C) {
                        party->flags3 |= 0x1000000;
                        party->flags |= 0x2000000;
                    }
                    party->unk138 = NULL;
                    partyChgMot(party, 3);
                    party->unk11C = -1.0f;
                    return;
                }
                party->position.y = pos.y;
                party->unk138 = hit;
                if (hit) {
                    N_partyPlaySfxPartyLanding1(party);
                    party->flags &= ~0x70;
                    party->flags |= 2;
                    party->unk114 = 0.0f;
                    partyChgMot(party, distABf(party->position.x, party->position.z, party->unk94.x, party->unk94.z) < 5.0f ? 0 : 1);
                }
            }
            break;
    }
    if (party->position.y < -2000.0f) {
        party->flags &= ~0x10;
        party->unk114 = 0.0f;
        party->unk100 = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
        party->position = mario->position;
        partyChgMot(party, 0);
    }
}
#endif

#ifdef NONMATCHING
s32 party_motion_fall(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    Vec pos;

    if (!(party->flags & 8)) {
        partyNextReadId(partyGetFootmarkId());
    }
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        partyChgPoseId(party, 4);
        party->flags &= ~0x80000;
    }
    hit = NULL;
    if (!(party->flags & 0x2000000)) {
        hit = partySearchGround(party, 10.0f, __fabsf(party->unk114));
    }
    if (hit && (hitGetAttr(hit) & 0x200)) {
        hit = NULL;
        if (party->unk32 == 0 && !party->unk4C) {
            party->flags3 |= 0x1000000;
            party->flags |= 0x2000000;
        }
    }
    party->unk138 = hit;
    if (!hit) {
        party->flags &= ~2;
        if (!(party->flags & 0x20)) {
            party->flags |= 0x20;
            if (party->unk11C == 0.0f) {
                party->unk11C = -1.4f;
            }
        }
        party->unk114 += party->unk11C;
        if (party->unk114 < -16.0f) {
            party->unk114 = -16.0f;
        }
        party->position.y += party->unk114;
        if (party->position.y < -2000.0f) {
            party->position.y = -2001.0f;
            if (mario->motionId == 0x1F || mario->motionId == 0x20) {
                return 2;
            }
            party->flags &= ~0x70;
            party->unk114 = 0.0f;
            party->unk11C = 0.0f;
            party->unk100 = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
            party->unk54 = revise360(180.0f + toMovedir(mario->unk1AC));
            partyGetAppearPos4(party, &party->position);
            party->position.y += 37.0f;
            partyChgMot(party, 0);
            party->flags &= ~0x2000000;
        }
        if (party->unk104) {
            pos = party->position;
            partySearchFrontWall(party, &pos, 1.3f * party->unk104, party->unk100);
            party->position.x = pos.x;
            party->position.z = pos.z;
        }
        return 2;
    }
    if (party->flags & 0x20) {
        party->flags &= ~0x70;
        party->flags |= 2;
        party->unk114 = 0.0f;
        party->position.y = party->unkE4;
        if (party->unk104 == 0.0f) {
            partyChgMot(party, 0);
        } else {
            partyChgMot(party, 1);
        }
        N_partyPlaySfxPartyLanding1(party);
        return 3;
    }
    party->flags &= ~0x2000;
    party->flags &= ~0x70;
    party->flags |= 2;
    party->unk114 = 0.0f;
    party->position.y = party->unkE4;
    if (party->unk104 == 0.0f) {
        partyChgMot(party, 0);
    } else {
        partyChgMot(party, 1);
    }
    N_partyPlaySfxPartyLanding1(party);
    if (!(party->flags & 8)) {
        partyClearFootmark();
    } else {
        partyClearFootmark2();
    }
    return 3;
}
#endif

#ifdef NONMATCHING
void party_motion_upstairs(PartyEntry* party) {
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->flags |= 0x40;
        unk_804189ec = 3;
        unk_804189e8 = (party->unk120 - party->position.y) / 3.0f;
    }
    party->position.y += unk_804189e8;
    if (--unk_804189ec <= 0) {
        party->flags &= ~0x40;
        partyChgMot(party, 1);
    }
}
#endif

#ifdef NONMATCHING
static inline BOOL partyChkHitAttr200(HitEntry* hit) {
    if (!hit) {
        return FALSE;
    }
    if (hitGetAttr(hit) & 0x200) {
        return TRUE;
    }
    return FALSE;
}
#endif

#ifdef NONMATCHING
void party_motion_damage(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    f32 x, y, z;
    Vec ret;

    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->unk38 = 0;
    }
    switch (party->unk38) {
        case 0:
            partyChgPoseId(party, 8);
            party->unk114 = 15.0f;
            party->unk118 = 0.0f;
            party->unk24 = 60;
            party->unk38 = 1;
        case 1:
            party->position.y += party->unk114;
            marioGetScreenPos(party->position, &x, &y, &z);
            if (y <= -300.0f) {
                party->unk24 = 20;
                party->unk38 = 10;
            }
            break;
        case 10:
            if (mario->motionId == 0x1F || mario->motionId == 0x20) {
                break;
            }
            if (--party->unk24 <= 0) {
                partyGetReturnPos(&ret);
                party->position.x = ret.x;
                party->position.y = 200.0f + ret.y;
                party->position.z = ret.z;
                party->unk114 = 0.0f;
                party->unk118 = -1.0f;
                unk_800c9398(party, 0.0f);
                party->flags |= 0x20;
                party->flags |= 0x2000000;
                party->unk38 = 11;
            }
            break;
        case 11:
            marioGetScreenPos(party->position, &x, &y, &z);
            if (y > 240.0f) {
                party->flags &= ~0x2000000;
            }
            partyMove(party);
            if (party->unk114 <= -6.0f) {
                party->unk118 = 0.0f;
                party->unk114 = -6.0f;
            }
            if (party->position.y < -2000.0f) {
                party->position = mario->position;
                party->position.y += 200.0f;
                party->flags &= ~0x70;
            }
            if (party->unk138 && !partyChkHitAttr200(party->unk138)) {
                party->unk38 = 12;
                party->unk24 = 30;
            }
            break;
        case 12:
            if (--party->unk24 <= 0) {
                partyChgRunMode(party, 2);
                party->unk3B = 0;
                party->flags2 &= ~0x10;
            }
            break;
    }
}
#endif

#ifdef NONMATCHING
void allPartySlitOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        if (!(party->playerPtr->flags & 0x80000000)) {
            party->flags3 |= 1;
            party->unk37 = 1;
        }
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        if (!(party->playerPtr->flags & 0x80000000)) {
            party->flags3 |= 1;
            party->unk37 = 1;
        }
    }
}
#endif

#ifdef NONMATCHING
void allPartySlitOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && (party->flags & 0x1000) && party->unk3A < 0x28) {
        party->unk3A = 0x28;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && (party->flags & 0x1000) && party->unk3A < 0x28) {
        party->unk3A = 0x28;
    }
}
#endif

#ifdef NONMATCHING
void allPartyForceSlitOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        L_partyForceSlitOff(party);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        L_partyForceSlitOff(party);
    }
}
#endif

#ifdef NONMATCHING
void L_partyForceSlitOff(PartyEntry* party) {
    if ((party->flags & 0x1000) || (party->flags2 & 0x100)) {
        party->unk10C = revise360(party->unk100 - party->unkF8) >= 180.0f ? 0.0f : 180.0f;
        party->unk110 = party->unk10C;
        party->unkFC = revise360(270.0f - party->unk10C);
        party->unk100 = party->unkFC;
        party->flags2 &= ~0x3C0;
        partyPaperOff(party);
        party->flags &= ~0x3000;
        party->unk37 = 0;
        partyChgPoseId(party, 1);
    }
}
#endif

#ifdef NONMATCHING
void partyChgMotSlitFloor(PartyEntry* party) {
    if (party->flags & 0x2000) {
        return;
    }
    if (!(party->playerPtr->flags & 0x80000000)) {
        party->flags3 |= 1;
        party->unk37 = 1;
    }
    party->flags |= 0x2000;
}
#endif

#ifdef NONMATCHING
BOOL party_slit(PartyEntry* party) {
    BOOL ret = TRUE;
    PartyMarioView* mario;
    f32 a;

    mario = party->playerPtr;
    if (party->unk37 != 1) {
        return TRUE;
    }
    if (party->flags3 & 1) {
        party->flags3 &= ~1;
        party->flags2 |= 0x100;
        partyPaperOn(party, "p_slit");
        partyChgPaper(party, "PM_S_1A");
        party->unk24 = 30;
        unk_800c9398(party, 0.0f);
        if (revise360(party->unk100 - mario->unk198) <= 180.0f) {
            party->flags2 &= ~0x200;
            party->unk3A = 0;
        } else {
            party->flags2 |= 0x200;
            party->unk3A = 2;
        }
    }
    switch (party->unk3A) {
        case 0:
            if (--party->unk24 < 0) {
                party->flags |= 0x1000;
                party->unk10C = 270.0f;
                party->unk110 = party->unk10C;
                partyChgPaper(party, "PM_S_1B");
                if (!(party->flags & 0x2000)) {
                    party->unk3A = 10;
                    ret = FALSE;
                } else {
                    party->unk3A = 20;
                }
            }
            break;
        case 2:
            if (--party->unk24 < 0) {
                party->flags |= 0x1000;
                party->unk10C = 270.0f;
                party->unk110 = party->unk10C;
                partyChgPaper(party, "PM_S_1B");
                if (!(party->flags & 0x2000)) {
                    party->unk3A = 10;
                    ret = FALSE;
                } else {
                    party->unk3A = 20;
                }
            }
            break;
        case 10:
            if (!party->unk104) {
                partyChgPaper(party, "PM_S_1B");
                party->unk10C = 270.0f;
            } else {
                if (revise360(party->unk100 - mario->unk198) >= 180.0) {
                    party->flags2 |= 0x200;
                } else {
                    party->flags2 &= ~0x200;
                }
                party->unk10C = (party->flags2 & 0x200) ? 280.0f : 260.0f;
                a = revise360(party->unk100 - mario->unk198);
                if (a >= 315.0f || a <= 45.0f || (a >= 135.0f && a <= 225.0f)) {
                    partyChgPaper(party, "PM_S_1E");
                } else {
                    partyChgPaper(party, "PM_S_1D");
                }
            }
            if (!(mario->flags0 & 0x100000) && !(hitGetAttr(party->unk12C) & 0x2000) &&
                !(hitGetAttr(party->unk134) & 0x2000))
            {
                party->unk3A = 40;
            }
            break;
    }
    switch (party->unk3A) {
        case 20:
            partyChgPaper(party, "PM_S_1H");
            party->flags |= 0x2000000;
            party->flags |= 0x20;
            party->unk24 = 20;
            unk_800c9398(party, 0.0f);
            party->unk3A = 21;
            break;
        case 21:
            party->unk10C = revise360(party->unk100 - party->unkF8) <= 180.0f ? 260.0f : 280.0f;
            party->position.y += -3.0f;
            if (--party->unk24 <= 0) {
                party->unk3A = 22;
            }
            break;
        case 22:
            party->unk3A = 10;
            party->flags &= ~0x2000000;
            marioClearSlitFloor();
            break;
    }
    switch (party->unk3A) {
        case 40:
            partyChgPaper(party, "PM_S_1C");
            party->unk24 = 30;
            party->unk3A = 41;
            party->unk10C = revise360(party->unk100 - mario->unk198) >= 180.0f ? 0.0f : 180.0f;
            party->unk110 = party->unk10C;
        case 41:
            if (--party->unk24 <= 0) {
                party->unk3A = 42;
            }
            break;
        case 42:
            party->flags2 &= ~0x3C0;
            partyPaperOff(party);
            party->flags &= ~0x3000;
            party->unk37 = 0;
            break;
    }
    return ret;
}
#endif

#ifdef NONMATCHING
BOOL party_roll(PartyEntry* party) {
    BOOL ret = TRUE;
    f32 d;
    f32 x;
    f32 t;

    if (party->unk37 != 2) {
        return TRUE;
    }
    if (party->flags3 & 1) {
        party->flags3 &= ~1;
        partyPaperOn(party, "p_roll");
        partyChgPaper(party, "PM_R_1A");
        partyChgPoseId(party, 0);
        party->unk88.x = -6.0f;
        party->unk88.y = 6.0f;
        party->unk7C.x = 6.0f;
        party->unk7C.y = 2.0f;
        party->unk24 = 0x41;
        party->unk3A = 0;
        unk_800c9398(party, 0.0f);
    }
    switch (party->unk3A) {
        case 0:
            party->unk24--;
            if (party->unk24 <= 0) {
                partyChgPaper(party, "PM_R_1B");
                party->unk3A = 10;
            }
            break;
        case 10:
            party->unk10C = revise360(270.0f - party->unk100);
            if (revise360(party->unkFC + party->unk10C) > 180.0f) {
                party->unk6C = revise360(7.0f * party->unk104 + party->unk6C);
            } else {
                party->unk6C = revise360(party->unk6C - 7.0f * party->unk104);
            }
            break;
    }
    switch (party->unk3A) {
        case 100:
            party->unk104 = 0.0f;
            party->unk64 = 0.0f;
            party->unk6C = 0.0f;
            party->unk88.x = 0.0f;
            party->unk88.y = 0.0f;
            party->unk7C.x = party->unk100 < 180.0f ? 3.0f : -3.0f;
            party->unk7C.y = 0.0f;
            party->unk24 = 0x41;
            party->unk3A = 101;
            partyChgPaper(party, "PM_R_1C");
            partyPaperLightOff(party);
        case 101:
            ret = FALSE;
            party->unk24--;
            if (party->unk24 > 0) {
                if (party->unk100 < 180.0f) {
                    x = 0.1f * (90.0f - party->unk10C);
                    x += party->unk10C;
                    if (__fabsf(90.0f - x < 1.0f)) {
                        x = 90.0f;
                    }
                    party->unk10C = x;
                    party->unk110 = x;
                } else {
                    x = 0.1f * (270.0f - party->unk10C);
                    x += party->unk10C;
                    if (__fabsf(270.0f - x < 1.0f)) {
                        x = 270.0f;
                    }
                    party->unk10C = x;
                    party->unk110 = x;
                }
            } else {
                ret = TRUE;
                if (party->unk100 >= 180.0f) {
                    party->unk10C = 0.0f;
                    party->unk110 = 0.0f;
                    party->unkFC = 270.0f;
                    party->unk100 = 270.0f;
                } else {
                    party->unk10C = 180.0f;
                    party->unk110 = 180.0f;
                    party->unkFC = 90.0f;
                    party->unk100 = 90.0f;
                }
                party->unk88 = (Vec){0.0f, 0.0f, 0.0f};
                party->unk7C = (Vec){0.0f, 0.0f, 0.0f};
                party->unk37 = 0;
                party->flags &= ~0x1000;
                party->flags2 &= ~0x100;
                party->flags &= ~0x200;
                party->flags2 &= ~0x10;
                party->flags2 &= ~0x8;
                party->unk3A = 100;
                partyPaperOff(party);
            }
            break;
    }
    return ret;
}
#endif



static inline s32 pm_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 pm_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (pm_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }







































#ifdef NONMATCHING
static f32 partyStayDist(PartyEntry* party) {
    f32 d;
    if (party->unk32 == 0) {
        d = 18.0f;
    } else if (party->currentMemberId == 5) {
        if (party->flags3 & 0x200000) {
            d = 8.0f;
        } else {
            d = 30.0f;
        }
    } else if (party->currentMemberId == 6) {
        if (party->flags3 & 0x200000) {
            d = 8.0f;
        } else {
            d = 30.0f;
        }
    }
    return d;
}
#endif

#ifdef NONMATCHING
static f32 partyHomingOff(PartyEntry* party) {
    f32 off = 5.0f;
    if (party->flags2 & 0x8000) {
        off = 1.0f;
    }
    return off;
}
#endif

#ifdef NONMATCHING
s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir) {
    f32 s2, c2;
    HitCheckQuery q2;
    HitCheckQuery q;
    f32 c, s;
    f32 r;
    f32 wallct;
    f32 y;
    f32 rf;
    s32 i;
    HitEntry* hit;

    r = 2.0f * party->unkF4 / 3.0f;
    q.targetDir = (Vec){0.0f, 1.0f, 0.0f};
    wallct = touch_wall_ct;
    sincosf(&s, &c, dir);
    for (i = 0; i < 3; i++) {
        q.targetPos.x = party->position.x + (f32)i * (s * r);
        q.targetPos.z = party->position.z + (f32)i * (c * r);
        q.targetPos.y = party->position.y + party->unkF0;
        q.targetDistance = 100.0f;
        if (hitCheckVecFilter(&q, NULL)) {
            if (pm_sqrtf(q.hitNormal.x * q.hitNormal.x + q.hitNormal.z * q.hitNormal.z) < 45.0f) {
                y = q.hitPos.y;
                goto found;
            }
        }
    }
    y = -2000.0f;
found:
    if (y > -2000.0f) {
        f32 t = party->position.y + wallct;
        f32 u = y - 2.0f;
        if (t < u) {
            q2.targetPos.y = t;
        } else {
            q2.targetPos.y = u;
        }
    } else {
        q2.targetPos.y = party->position.y + wallct;
    }
    r = 0.75f * party->unkF4;
    sincosf(&s2, &c2, dir);
    q2.targetPos.x = s2 * r + party->position.x;
    q2.targetPos.z = c2 * r + party->position.z;
    q2.targetDistance = 300.0f;
    q2.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q2, NULL);
    if (!hit) {
        out->x = party->position.x;
        out->y = party->position.y;
        out->z = party->position.z;
        return 0;
    }
    rf = q2.hitPos.x >= 0.0f ? 0.5f : -0.5f;
    out->x = (s32)((1000.0f * q2.hitPos.x) + rf) / 1000.0f;
    rf = q2.hitPos.y >= 0.0f ? 0.5f : -0.5f;
    out->y = (s32)((1000.0f * q2.hitPos.y) + rf) / 1000.0f;
    rf = q2.hitPos.z >= 0.0f ? 0.5f : -0.5f;
    out->z = (s32)((1000.0f * q2.hitPos.z) + rf) / 1000.0f;
    return hitGetAttr(hit);
}
#endif



















#ifdef NONMATCHING
static inline void partyDownDirX(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}
#endif

#ifdef NONMATCHING
static f32 partyGetDirGndY(Vec u, f32 md) {
    f32 k = 40.0f;
    HitCheckQuery q2;
    HitEntry* hit;
    f32 s2, c2;
    f32 gy;
    f32 a;
    gy = touch_wall_ct;
    sincosf(&s2, &c2, md);
    q2.targetPos = u;
    q2.targetPos.x = s2 * k + q2.targetPos.x;
    q2.targetPos.z = c2 * k + q2.targetPos.z;
    q2.targetPos.y = q2.targetPos.y + gy;
    q2.targetDistance = 1000.0f;
    q2.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q2, NULL);
    if (hit) {
        a = q2.hitPos.y >= 0.0f ? 0.5f : -0.5f;
        gy = (s32)((1000.0f * q2.hitPos.y) + a) / 1000.0f;
        hitGetAttr(hit);
    } else {
        gy = -2000.0f;
    }
    return gy;
}
#endif

#ifdef NONMATCHING
static f32 partyGetGndY(f32 x, f32 y, f32 z) {
    f32 r;
    f32 hx, hy, hz, dist, nx, ny, nz;
    HitEntry* hit;
    y += touch_wall_ct;
    dist = 1000.0f;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, 0.0f, -1.0f, 0.0f);
    if (!hit) {
        r = -2000.0f;
    } else {
        r = (s32)(100.0f * hy + 0.5f) / 100.0f;
        hitGetAttr(hit);
    }
    return r;
}
#endif

#ifdef NONMATCHING
static u32 partyGetFrontAttr(PartyEntry* party, f32 dir) {
    HitCheckQuery q;
    HitEntry* hit;
    f32 s, c;
    sincosf(&s, &c, dir);
    q.targetDistance = 40.0f;
    q.targetPos.x = 20.0f * s + party->position.x;
    q.targetPos.z = 20.0f * c + party->position.z;
    q.targetPos.y = 20.0f + party->position.y;
    q.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q, NULL);
    return hit ? hitGetAttr(hit) : 0;
}
#endif























































#ifdef NONMATCHING
static inline u32 partyGetFrontAttrFar(PartyEntry* party) {
    HitCheckQuery q;
    HitEntry* hit;
    f32 s, c;
    f32 k = 40.0f;
    sincosf(&s, &c, party->unk100);
    q.targetDistance = 100.0f;
    q.targetPos.x = s * k + party->position.x;
    q.targetPos.z = c * k + party->position.z;
    q.targetPos.y = party->position.y + k;
    q.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q, NULL);
    return hit ? hitGetAttr(hit) : 0;
}
#endif

#ifdef NONMATCHING
static inline void partyDownDirY(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}
#endif

#ifdef NONMATCHING
void party_force_reset_outofscreen(PartyEntry* party) {
    PartyMarioView* m2;
    s32 i;
    s32 margin;
    s32 j;
    PartyMarioView* mario = party->playerPtr;
    f32 speed;
    f32 y;
    f32 up;
    HitEntry* hit;
    f32 dist;
    f32 sx, sy, sz;
    Vec pos;
    Vec start;
    Vec dir;
    Vec hitPos;
    Vec nrm;

    if (marioCtrlOffChk()) {
        return;
    }
    if (marioKeyOffChk()) {
        return;
    }
    marioGetScreenPos(party->position, &sx, &sy, &sz);
    if (distABf(mario->position.x, mario->position.z, party->position.x, party->position.z) < 20.0f &&
        sy > 800.0f)
    {
        partyGetAppearPos3(party, &pos);
        party->position = pos;
        return;
    }
    margin = 100;
    if (-100.0f <= sx && sx <= 700.0f && sy <= 650.0f) {
        return;
    }
    if (!(party->flags & 8)) {
        partyClearFootmark();
    } else {
        partyClearFootmark();
    }
    m2 = party->playerPtr;
    i = 0;
    pos = party->position;
    if (party->unk32 == 0) {
        speed = party->unkF4;
    } else if (party->currentMemberId == 5) {
        speed = 10.0f;
        margin = 70;
    } else {
        speed = 10.0f;
        margin = 50;
    }
    {
        Vec d = {0.0f, -1.0f, 0.0f};
        dir = d;
    }
    while (TRUE) {
        marioGetScreenPos(pos, &sx, &sy, &sz);
        if ((f32)-margin <= sx && sx <= (f32)(margin + 600)) {
            party->position = pos;
            return;
        }
        if (i > 100) {
            return;
        }
        {
            f32 a = angleABf(pos.x, pos.z, m2->position.x, m2->position.z);
            movePos(&pos.x, &pos.z, speed, a);
        }
        up = 200.0f;
        j = 0;
        y = pos.y;
        while (TRUE) {
            dist = 300.0f;
            start = pos;
            start.y += up;
            hit = partyHitCheck(party, &start, &dir, &hitPos, &nrm, &dist);
            if (hit) {
                if (!partyChkHitAttr200(hit)) {
                    y = hitPos.y;
                }
            } else {
                y = m2->position.y;
            }
            start.y = y;
            marioGetScreenPos(start, &sx, &sy, &sz);
            if (sy > 100.0f) {
                dist = 100.0f;
                start = pos;
                if (pos.y + 74.0f > y) {
                    start.y += 74.0f;
                    hit = partyHitCheck(party, &start, &dir, &hitPos, &nrm, &dist);
                    if (hit && !partyChkHitAttr200(hit)) {
                        y = hitPos.y;
                    }
                }
                break;
            }
            if (++j > 4) {
                break;
            }
            up -= 50.0f;
            if (up < 0.0f) {
                up = 0.0f;
            }
        }
        pos.y = y;
        i++;
    }
}
#endif























#ifdef NONMATCHING
static void partyGorFix(PartyEntry* party) {
    PartyMarioView* m3 = party->playerPtr;
    if (!strcmp(gp->currentMapName, "gor_01") && m3->unk1E4 && party->unk138 &&
        !strcmp(hitGetName(m3->unk1E4), "A_ie_03_yuka_f1_C") && !strcmp(hitGetName(party->unk138), "A_ie_03_yuka_f2_C"))
    {
        Vec fix = {122.0f, 130.0f, -313.0f};
        party->position = fix;
    }
}
#endif

#ifdef NONMATCHING
static void partyPoseA2(PartyEntry* party) {
    partyChgPose(party, "PCH_A2_1");
    party->unk39 = 1;
    party->unk24 = 30;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: evt_snd_bgmon (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const f32 vec3_802f3e40[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e70[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e7c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e88[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3e94[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3ea0[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3eac[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3eb8[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3ec4[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3ed0[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3edc[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3ee8[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3ef4[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3f00[3] = { 122.0f, 130.0f, -313.0f };
__declspec(section ".rodata") const char str_802F3F0C[] = "PCH_A2_1\000\000\000";
__declspec(section ".rodata") const char str_802F3F18[] = "gor_01\000";
__declspec(section ".rodata") const char str_802F3F20[] = "A_ie_03_yuka_f1_C\000\000";
__declspec(section ".rodata") const char str_802F3F34[] = "A_ie_03_yuka_f2_C\000\000";
__declspec(section ".rodata") const f64 double_to_int_802f3f48 = 4503601774854144;
__declspec(section ".rodata") const f64 double_0p5_802f3f50 = 0.5;
__declspec(section ".rodata") const f64 double_3_802f3f58 = 3;
__declspec(section ".rodata") const f64 double_0_802f3f60 = 0;
__declspec(section ".rodata") const char str_802F3F68[] = "p_roll\000";
__declspec(section ".rodata") const char str_802F3F70[] = "PM_R_1A";
__declspec(section ".rodata") const char str_802F3F78[] = "PM_R_1B";
__declspec(section ".rodata") const char str_802F3F80[] = "PM_R_1C";
__declspec(section ".rodata") const char str_802F3F88[] = "p_slit\000";
__declspec(section ".rodata") const char str_802F3F90[] = "PM_S_1A";
__declspec(section ".rodata") const char str_802F3F98[] = "PM_S_1B";
__declspec(section ".rodata") const f64 double_180_802f3fa0 = 180;
__declspec(section ".rodata") const char str_802F3FA8[] = "PM_S_1E";
__declspec(section ".rodata") const char str_802F3FB0[] = "PM_S_1D";
__declspec(section ".rodata") const char str_802F3FB8[] = "PM_S_1H";
__declspec(section ".rodata") const char str_802F3FC0[] = "PM_S_1C";
__declspec(section ".rodata") const char str_802F3FC8[] = "aji_02\000";
__declspec(section ".rodata") const char str_802F3FD0[] = "aji_05\000";
__declspec(section ".rodata") const char str_802F3FD8[] = "aji_12\000";
__declspec(section ".rodata") const f64 double_12_802f3fe0 = 12;
__declspec(section ".sdata2") const f32 float_20_8041cdc0 = 20.0f;
__declspec(section ".sdata2") const f32 float_800_8041cdc4 = 800.0f;
__declspec(section ".sdata2") const f32 float_neg100_8041cdc8 = -100.0f;
__declspec(section ".sdata2") const f32 float_700_8041cdcc = 700.0f;
__declspec(section ".sdata2") const f32 float_650_8041cdd0 = 650.0f;
__declspec(section ".sdata2") const f32 float_10_8041cdd4 = 10.0f;
__declspec(section ".sdata2") const f32 float_200_8041cdd8 = 200.0f;
__declspec(section ".sdata2") const f32 float_300_8041cddc = 300.0f;
__declspec(section ".sdata2") const f32 float_100_8041cde0 = 100.0f;
__declspec(section ".sdata2") const f32 float_74_8041cde4 = 74.0f;
__declspec(section ".sdata2") const f32 float_50_8041cde8 = 50.0f;
__declspec(section ".sdata2") const f32 float_0_8041cdec = 0.0f;
__declspec(section ".sdata2") const f32 float_40_8041cdf0 = 40.0f;
__declspec(section ".sdata2") const f32 float_1000_8041cdf4 = 1000.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041cdf8 = -1.0f;
__declspec(section ".sdata2") const f32 float_neg2000_8041cdfc = -2000.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041ce00 = 0.5f;
__declspec(section ".sdata2") const f32 float_neg0p5_8041ce04 = -0.5f;
__declspec(section ".sdata2") const f32 float_2_8041ce08 = 2.0f;
__declspec(section ".sdata2") const f32 float_3_8041ce0c = 3.0f;
__declspec(section ".sdata2") const f32 float_45_8041ce10 = 45.0f;
__declspec(section ".sdata2") const f32 float_0p75_8041ce14 = 0.75f;
__declspec(section ".sdata2") const f32 float_5_8041ce18 = 5.0f;
__declspec(section ".sdata2") const f32 float_1_8041ce1c = 1.0f;
__declspec(section ".sdata2") const f32 float_18_8041ce20 = 18.0f;
__declspec(section ".sdata2") const f32 float_8_8041ce24 = 8.0f;
__declspec(section ".sdata2") const f32 float_30_8041ce28 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg6_8041ce2c = -6.0f;
__declspec(section ".sdata2") const f32 float_6_8041ce30 = 6.0f;
__declspec(section ".sdata2") const f32 float_270_8041ce34 = 270.0f;
__declspec(section ".sdata2") const f32 float_180_8041ce38 = 180.0f;
__declspec(section ".sdata2") const f32 float_7_8041ce3c = 7.0f;
__declspec(section ".sdata2") const f32 float_neg3_8041ce40 = -3.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041ce44 = 0.1f;
__declspec(section ".sdata2") const f32 float_90_8041ce48 = 90.0f;
__declspec(section ".sdata2") const f32 float_280_8041ce4c = 280.0f;
__declspec(section ".sdata2") const f32 float_260_8041ce50 = 260.0f;
__declspec(section ".sdata2") const f32 float_315_8041ce54 = 315.0f;
__declspec(section ".sdata2") const f32 float_135_8041ce58 = 135.0f;
__declspec(section ".sdata2") const f32 float_225_8041ce5c = 225.0f;
__declspec(section ".sdata2") const f32 float_15_8041ce60 = 15.0f;
__declspec(section ".sdata2") const f32 float_neg300_8041ce64 = -300.0f;
__declspec(section ".sdata2") const f32 float_240_8041ce68 = 240.0f;
__declspec(section ".sdata2") const f32 float_neg1p4_8041ce6c = -1.4f;
__declspec(section ".sdata2") const f32 float_neg16_8041ce70 = -16.0f;
__declspec(section ".sdata2") const f32 float_neg2001_8041ce74 = -2001.0f;
__declspec(section ".sdata2") const f32 float_37_8041ce78 = 37.0f;
__declspec(section ".sdata2") const f32 float_1p3_8041ce7c = 1.3f;
__declspec(section ".sdata2") const f32 float_2p25_8041ce80 = 2.25f;
__declspec(section ".sdata2") const f32 float_0p6_8041ce84 = 0.6f;
__declspec(section ".sdata2") const f32 float_1p4_8041ce88 = 1.4f;
__declspec(section ".sdata2") const f32 float_0p9_8041ce8c = 0.9f;
__declspec(section ".sdata2") const f32 float_25_8041ce90 = 25.0f;
__declspec(section ".sdata2") const f32 float_13_8041ce94 = 13.0f;
__declspec(section ".sdata2") const f32 float_1p5_8041ce98 = 1.5f;
__declspec(section ".sdata2") const f32 float_3p6_8041ce9c = 3.6f;
__declspec(section ".sdata2") const f32 float_0p05_8041cea0 = 0.05f;
__declspec(section ".sdata2") const f32 float_28_8041cea4 = 28.0f;
__declspec(section ".sdata2") const f32 float_32_8041cea8 = 32.0f;
__declspec(section ".sdata2") const f32 float_35_8041ceac = 35.0f;
__declspec(section ".sdata2") const f32 float_4_8041ceb0 = 4.0f;
__declspec(section ".sdata2") const f32 float_37p5_8041ceb4 = 37.5f;
__declspec(section ".sdata2") const f32 float_70_8041ceb8 = 70.0f;
__declspec(section ".sdata2") const f32 float_150_8041cebc = 150.0f;
__declspec(section ".sdata2") const f32 float_60_8041cec0 = 60.0f;
__declspec(section ".sdata2") const f32 float_11_8041cec4 = 11.0f;
__declspec(section ".sdata2") const f32 float_18p5_8041cec8 = 18.5f;
__declspec(section ".sdata2") const f32 float_neg15_8041cecc = -15.0f;
__declspec(section ".sdata2") const f32 float_neg1p5_8041ced0 = -1.5f;
__declspec(section ".sdata2") const f32 float_31_8041ced4 = 31.0f;

asm void party_force_reset_outofscreen(PartyEntry* party) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	stfd f31, 0x110(r1)
	psq_st f31, 0x118(r1), 0, 0
	stfd f30, 0x100(r1)
	psq_st f30, 0x108(r1), 0, 0
	stfd f29, 0xf0(r1)
	psq_st f29, 0xf8(r1), 0, 0
	stfd f28, 0xe0(r1)
	psq_st f28, 0xe8(r1), 0, 0
	stfd f27, 0xd0(r1)
	psq_st f27, 0xd8(r1), 0, 0
	stfd f26, 0xc0(r1)
	psq_st f26, 0xc8(r1), 0, 0
	stfd f25, 0xb0(r1)
	psq_st f25, 0xb8(r1), 0, 0
	stfd f24, 0xa0(r1)
	psq_st f24, 0xa8(r1), 0, 0
	stmw r24, 0x80(r1)
	mr r25, r3
	lwz r24, 0x160(r3)
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	bne @1
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @1
	lwz r7, 0x58(r25)
	addi r3, r1, 0x30
	lwz r0, 0x5c(r25)
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	stw r7, 0x30(r1)
	stw r0, 0x34(r1)
	lwz r0, 0x60(r25)
	stw r0, 0x38(r1)
	bl marioGetScreenPos
	lfs f1, 0x8c(r24)
	lfs f2, 0x94(r24)
	lfs f3, 0x58(r25)
	lfs f4, 0x60(r25)
	bl distABf
	lfs f0, float_20_8041cdc0(r2)
	fcmpo cr0, f1, f0
	bge @2
	lfs f1, 0xc(r1)
	lfs f0, float_800_8041cdc4(r2)
	fcmpo cr0, f1, f0
	ble @2
	mr r3, r25
	addi r4, r1, 0x6c
	bl partyGetAppearPos3
	lwz r3, 0x6c(r1)
	lwz r0, 0x70(r1)
	stw r3, 0x58(r25)
	stw r0, 0x5c(r25)
	lwz r0, 0x74(r1)
	stw r0, 0x60(r25)
	b @1
	@2:
	lfs f0, float_neg100_8041cdc8(r2)
	li r26, 0x64
	lfs f1, 0x10(r1)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @3
	lfs f0, float_700_8041cdcc(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @3
	lfs f1, 0xc(r1)
	lfs f0, float_650_8041cdd0(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq @1
	@3:
	lwz r0, 0x0(r25)
	rlwinm. r0, r0, 0, 28, 28
	bne @4
	bl partyClearFootmark
	b @5
	@4:
	bl partyClearFootmark
	@5:
	lwz r28, 0x160(r25)
	li r27, 0x0
	lwz r3, 0x58(r25)
	lwz r0, 0x5c(r25)
	stw r3, 0x6c(r1)
	stw r0, 0x70(r1)
	lwz r0, 0x60(r25)
	stw r0, 0x74(r1)
	lbz r0, 0x32(r25)
	cmplwi r0, 0x0
	bne @6
	lfs f30, 0xf4(r25)
	b @7
	@6:
	lbz r0, 0x31(r25)
	cmpwi r0, 0x5
	bne @8
	lfs f30, float_10_8041cdd4(r2)
	li r26, 0x46
	b @7
	@8:
	lfs f30, float_10_8041cdd4(r2)
	li r26, 0x32
	@7:
	lis r4, vec3_802f3ef4@ha
	lis r3, double_to_int_802f3f48@ha
	addi r6, r4, vec3_802f3ef4@l
	neg r7, r26
	lwz r5, 0x0(r6)
	addi r29, r1, 0x74
	lwz r4, 0x4(r6)
	xoris r30, r7, 0x8000
	lwz r0, 0x8(r6)
	lis r31, 0x4330
	stw r5, 0x54(r1)
	lfs f27, float_100_8041cde0(r2)
	stw r4, 0x58(r1)
	lfs f28, float_50_8041cde8(r2)
	stw r0, 0x5c(r1)
	lfs f29, float_0_8041cdec(r2)
	lfs f26, float_300_8041cddc(r2)
	lfd f31, double_to_int_802f3f48@l(r3)
	@9:
	lwz r6, 0x6c(r1)
	addi r3, r1, 0x24
	lwz r7, 0x70(r1)
	addi r4, r1, 0x10
	lwz r0, 0x74(r1)
	addi r5, r1, 0xc
	stw r6, 0x24(r1)
	addi r6, r1, 0x8
	stw r7, 0x28(r1)
	stw r0, 0x2c(r1)
	bl marioGetScreenPos
	stw r30, 0x7c(r1)
	lfs f2, 0x10(r1)
	stw r31, 0x78(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f31
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne @10
	addi r3, r26, 0x258
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802f3f48@ha
	stw r3, 0x7c(r1)
	lfd f1, double_to_int_802f3f48@l(r4)
	stw r0, 0x78(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f1
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne @10
	lwz r3, 0x6c(r1)
	lwz r0, 0x70(r1)
	stw r3, 0x58(r25)
	stw r0, 0x5c(r25)
	lwz r0, 0x74(r1)
	stw r0, 0x60(r25)
	b @1
	@10:
	cmpwi r27, 0x64
	bgt @1
	lfs f1, 0x6c(r1)
	lfs f2, 0x74(r1)
	lfs f3, 0x8c(r28)
	lfs f4, 0x94(r28)
	bl angleABf
	fmr f0, f1
	mr r4, r29
	fmr f1, f30
	addi r3, r1, 0x6c
	fmr f2, f0
	bl movePos
	lfs f24, float_200_8041cdd8(r2)
	li r24, 0x0
	lfs f25, 0x70(r1)
	@11:
	lwz r0, 0x70(r1)
	mr r3, r25
	lwz r9, 0x6c(r1)
	addi r4, r1, 0x60
	stw r0, 0x64(r1)
	addi r5, r1, 0x54
	lwz r0, 0x74(r1)
	addi r6, r1, 0x48
	lfs f0, 0x64(r1)
	addi r7, r1, 0x3c
	stfs f26, 0x14(r1)
	addi r8, r1, 0x14
	fadds f0, f0, f24
	stw r9, 0x60(r1)
	stw r0, 0x68(r1)
	stfs f0, 0x64(r1)
	bl partyHitCheck
	cmplwi r3, 0x0
	beq @12
	bne @13
	li r0, 0x0
	b @14
	@13:
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @15
	li r0, 0x1
	b @14
	@15:
	li r0, 0x0
	@14:
	cmpwi r0, 0x0
	bne @16
	lfs f25, 0x4c(r1)
	b @16
	@12:
	lfs f25, 0x90(r28)
	@16:
	stfs f25, 0x64(r1)
	addi r3, r1, 0x18
	lwz r8, 0x60(r1)
	addi r4, r1, 0x10
	lwz r7, 0x64(r1)
	addi r5, r1, 0xc
	lwz r0, 0x68(r1)
	addi r6, r1, 0x8
	stw r8, 0x18(r1)
	stw r7, 0x1c(r1)
	stw r0, 0x20(r1)
	bl marioGetScreenPos
	lfs f0, 0xc(r1)
	fcmpo cr0, f0, f27
	ble @17
	lfs f1, float_74_8041cde4(r2)
	lfs f0, 0x70(r1)
	lwz r4, 0x6c(r1)
	fadds f0, f1, f0
	lwz r3, 0x70(r1)
	lwz r0, 0x74(r1)
	stfs f27, 0x14(r1)
	fcmpo cr0, f0, f25
	stw r4, 0x60(r1)
	stw r3, 0x64(r1)
	stw r0, 0x68(r1)
	ble @18
	lfs f0, 0x64(r1)
	mr r3, r25
	addi r4, r1, 0x60
	addi r5, r1, 0x54
	fadds f0, f0, f1
	addi r6, r1, 0x48
	addi r7, r1, 0x3c
	addi r8, r1, 0x14
	stfs f0, 0x64(r1)
	bl partyHitCheck
	cmplwi r3, 0x0
	beq @18
	bne @19
	li r0, 0x0
	b @20
	@19:
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @21
	li r0, 0x1
	b @20
	@21:
	li r0, 0x0
	@20:
	cmpwi r0, 0x0
	bne @18
	lfs f25, 0x4c(r1)
	b @18
	@17:
	addi r24, r24, 0x1
	cmpwi r24, 0x4
	bgt @18
	fsubs f24, f24, f28
	fcmpo cr0, f24, f29
	bge @11
	fmr f24, f29
	b @11
	@18:
	stfs f25, 0x70(r1)
	addi r27, r27, 0x1
	b @9
	@1:
	psq_l f31, 0x118(r1), 0, 0
	lfd f31, 0x110(r1)
	psq_l f30, 0x108(r1), 0, 0
	lfd f30, 0x100(r1)
	psq_l f29, 0xf8(r1), 0, 0
	lfd f29, 0xf0(r1)
	psq_l f28, 0xe8(r1), 0, 0
	lfd f28, 0xe0(r1)
	psq_l f27, 0xd8(r1), 0, 0
	lfd f27, 0xd0(r1)
	psq_l f26, 0xc8(r1), 0, 0
	lfd f26, 0xc0(r1)
	psq_l f25, 0xb8(r1), 0, 0
	lfd f25, 0xb0(r1)
	psq_l f24, 0xa8(r1), 0, 0
	lfd f24, 0xa0(r1)
	lmw r24, 0x80(r1)
	lwz r0, 0x124(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stmw r27, 0xdc(r1)
	mr r29, r3
	lis r3, vec3_802f3e40@ha
	lfs f2, float_2_8041ce08(r2)
	addi r31, r3, vec3_802f3e40@l
	lfs f0, 0xf4(r29)
	mr r30, r4
	lwz r4, 0x60(r31)
	fmr f27, f1
	fmuls f2, f2, f0
	lfs f0, float_3_8041ce0c(r2)
	lwz r5, 0x64(r31)
	addi r3, r1, 0xc
	lwz r0, 0x68(r31)
	fdivs f29, f2, f0
	stw r4, 0x34(r1)
	addi r4, r1, 0x10
	lfs f28, touch_wall_ct(r13)
	stw r5, 0x38(r1)
	stw r0, 0x3c(r1)
	bl sincosf
	lfd f30, 0x108(r31)
	li r27, 0x0
	lfs f31, float_100_8041cde0(r2)
	lis r28, 0x4330
	@1:
	xoris r0, r27, 0x8000
	lfs f1, 0xc(r1)
	stw r0, 0xa4(r1)
	addi r3, r1, 0x1c
	lfs f0, 0x10(r1)
	fmuls f3, f1, f29
	stw r28, 0xa0(r1)
	li r4, 0x0
	lfs f2, 0x58(r29)
	fmuls f1, f0, f29
	lfd f0, 0xa0(r1)
	stw r0, 0xac(r1)
	fsubs f0, f0, f30
	stw r28, 0xa8(r1)
	fmadds f3, f0, f3, f2
	lfd f0, 0xa8(r1)
	fsubs f2, f0, f30
	stfs f3, 0x28(r1)
	lfs f0, 0x60(r29)
	fmadds f0, f2, f1, f0
	stfs f0, 0x30(r1)
	lfs f1, 0x5c(r29)
	lfs f0, 0xf0(r29)
	fadds f0, f1, f0
	stfs f31, 0x58(r1)
	stfs f0, 0x2c(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @2
	lfs f0, 0x4c(r1)
	lfs f1, 0x54(r1)
	fmuls f2, f0, f0
	lfs f0, float_0_8041cdec(r2)
	fmuls f1, f1, f1
	fadds f4, f2, f1
	fcmpo cr0, f4, f0
	ble @3
	frsqrte f1, f4
	lfd f3, 0x110(r31)
	lfd f2, 0x118(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b @4
	@3:
	lfd f0, 0x120(r31)
	fcmpo cr0, f4, f0
	bge @5
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b @4
	@5:
	stfs f4, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @6
	bge @7
	cmpwi r3, 0x0
	beq @8
	b @7
	@6:
	clrlwi. r0, r4, 9
	beq @9
	li r0, 0x1
	b @10
	@9:
	li r0, 0x2
	b @10
	@8:
	clrlwi. r0, r4, 9
	beq @11
	li r0, 0x5
	b @10
	@11:
	li r0, 0x3
	b @10
	@7:
	li r0, 0x4
	@10:
	cmpwi r0, 0x1
	bne @4
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	@4:
	lfs f0, float_45_8041ce10(r2)
	fcmpo cr0, f4, f0
	bge @2
	lfs f2, 0x44(r1)
	b @12
	@2:
	addi r27, r27, 0x1
	cmpwi r27, 0x3
	blt @1
	lfs f2, float_neg2000_8041cdfc(r2)
	@12:
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f2, f0
	ble @13
	lfs f1, 0x5c(r29)
	lfs f0, float_2_8041ce08(r2)
	fadds f1, f1, f28
	fsubs f0, f2, f0
	fcmpo cr0, f1, f0
	bge @14
	stfs f1, 0x6c(r1)
	b @15
	@14:
	stfs f0, 0x6c(r1)
	b @15
	@13:
	lfs f0, 0x5c(r29)
	fadds f0, f0, f28
	stfs f0, 0x6c(r1)
	@15:
	lfs f2, float_0p75_8041ce14(r2)
	fmr f1, f27
	lfs f0, 0xf4(r29)
	addi r3, r1, 0x18
	addi r4, r1, 0x14
	fmuls f27, f2, f0
	bl sincosf
	lfs f1, 0x18(r1)
	addi r3, r1, 0x5c
	lfs f0, 0x58(r29)
	li r4, 0x0
	lfs f2, 0x14(r1)
	fmadds f1, f1, f27, f0
	lfs f0, float_300_8041cddc(r2)
	lwz r6, 0x6c(r31)
	lwz r5, 0x70(r31)
	stfs f1, 0x68(r1)
	lwz r0, 0x74(r31)
	lfs f1, 0x60(r29)
	fmadds f1, f2, f27, f1
	stfs f0, 0x98(r1)
	stw r6, 0x74(r1)
	stfs f1, 0x70(r1)
	stw r5, 0x78(r1)
	stw r0, 0x7c(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	bne @16
	lfs f0, 0x58(r29)
	li r3, 0x0
	stfs f0, 0x0(r30)
	lfs f0, 0x5c(r29)
	stfs f0, 0x4(r30)
	lfs f0, 0x60(r29)
	stfs f0, 0x8(r30)
	b @17
	@16:
	lfs f1, 0x80(r1)
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @18
	lfs f0, float_0p5_8041ce00(r2)
	b @19
	@18:
	lfs f0, float_neg0p5_8041ce04(r2)
	@19:
	lfs f3, float_1000_8041cdf4(r2)
	lis r0, 0x4330
	stw r0, 0xa0(r1)
	fmadds f1, f3, f1, f0
	lfd f2, 0x108(r31)
	lfs f0, float_0_8041cdec(r2)
	fctiwz f1, f1
	stfd f1, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f1, 0xa0(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r30)
	lfs f1, 0x84(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @20
	lfs f0, float_0p5_8041ce00(r2)
	b @21
	@20:
	lfs f0, float_neg0p5_8041ce04(r2)
	@21:
	lfs f3, float_1000_8041cdf4(r2)
	lis r0, 0x4330
	stw r0, 0xb8(r1)
	fmadds f1, f3, f1, f0
	lfd f2, 0x108(r31)
	lfs f0, float_0_8041cdec(r2)
	fctiwz f1, f1
	stfd f1, 0xb0(r1)
	lwz r0, 0xb4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f1, 0xb8(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r30)
	lfs f1, 0x88(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @22
	lfs f0, float_0p5_8041ce00(r2)
	b @23
	@22:
	lfs f0, float_neg0p5_8041ce04(r2)
	@23:
	lfs f2, float_1000_8041cdf4(r2)
	lis r0, 0x4330
	stw r0, 0xc8(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x108(r31)
	fctiwz f0, f0
	stfd f0, 0xc0(r1)
	lwz r0, 0xc4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xcc(r1)
	lfd f0, 0xc8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r30)
	bl hitGetAttr
	@17:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	lmw r27, 0xdc(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm BOOL party_roll(PartyEntry* party) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, vec3_802f3e40@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r4, vec3_802f3e40@l
	stw r30, 0x18(r1)
	li r30, 0x1
	stw r29, 0x14(r1)
	mr r29, r3
	lbz r0, 0x37(r3)
	cmplwi r0, 0x2
	beq @1
	li r3, 0x1
	b @2
	@1:
	lwz r4, 0x8(r29)
	clrlwi. r0, r4, 31
	beq @3
	clrrwi r0, r4, 1
	addi r4, r31, 0x128
	stw r0, 0x8(r29)
	bl partyPaperOn
	mr r3, r29
	addi r4, r31, 0x130
	bl partyChgPaper
	mr r3, r29
	li r4, 0x0
	bl partyChgPoseId
	lfs f0, float_neg6_8041ce2c(r2)
	li r4, 0x41
	lfs f2, float_6_8041ce30(r2)
	li r0, 0x0
	stfs f0, 0x88(r29)
	mr r3, r29
	lfs f0, float_2_8041ce08(r2)
	stfs f2, 0x8c(r29)
	lfs f1, float_0_8041cdec(r2)
	stfs f2, 0x7c(r29)
	stfs f0, 0x80(r29)
	stw r4, 0x24(r29)
	stb r0, 0x3a(r29)
	bl unk_800c9398
	@3:
	lbz r0, 0x3a(r29)
	cmpwi r0, 0xa
	beq @4
	bge @5
	cmpwi r0, 0x0
	beq @6
	b @5
	@6:
	lwz r3, 0x24(r29)
	subi r0, r3, 0x1
	stw r0, 0x24(r29)
	lwz r0, 0x24(r29)
	cmpwi r0, 0x0
	bgt @5
	mr r3, r29
	addi r4, r31, 0x138
	bl partyChgPaper
	li r0, 0xa
	stb r0, 0x3a(r29)
	b @5
	@4:
	lfs f1, float_270_8041ce34(r2)
	lfs f0, 0x100(r29)
	fsubs f1, f1, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, 0xfc(r29)
	lfs f0, 0x10c(r29)
	fadds f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	ble @7
	lfs f2, float_7_8041ce3c(r2)
	lfs f1, 0x104(r29)
	lfs f0, 0x6c(r29)
	fmadds f1, f2, f1, f0
	bl revise360
	stfs f1, 0x6c(r29)
	b @5
	@7:
	lfs f2, float_7_8041ce3c(r2)
	lfs f1, 0x104(r29)
	lfs f0, 0x6c(r29)
	fnmsubs f1, f2, f1, f0
	bl revise360
	stfs f1, 0x6c(r29)
	@5:
	lbz r0, 0x3a(r29)
	cmpwi r0, 0x65
	beq @8
	bge @9
	cmpwi r0, 0x64
	bge @10
	b @9
	@10:
	lfs f1, float_0_8041cdec(r2)
	lfs f0, float_180_8041ce38(r2)
	stfs f1, 0x104(r29)
	stfs f1, 0x64(r29)
	stfs f1, 0x6c(r29)
	stfs f1, 0x88(r29)
	stfs f1, 0x8c(r29)
	lfs f1, 0x100(r29)
	fcmpo cr0, f1, f0
	bge @11
	lfs f0, float_3_8041ce0c(r2)
	b @12
	@11:
	lfs f0, float_neg3_8041ce40(r2)
	@12:
	stfs f0, 0x7c(r29)
	li r5, 0x41
	lfs f0, float_0_8041cdec(r2)
	li r0, 0x65
	mr r3, r29
	addi r4, r31, 0x140
	stfs f0, 0x80(r29)
	stw r5, 0x24(r29)
	stb r0, 0x3a(r29)
	bl partyChgPaper
	mr r3, r29
	bl partyPaperLightOff
	@8:
	lwz r3, 0x24(r29)
	li r30, 0x0
	subi r0, r3, 0x1
	stw r0, 0x24(r29)
	lwz r0, 0x24(r29)
	cmpwi r0, 0x0
	ble @13
	lfs f1, 0x100(r29)
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	bge @14
	lfs f3, float_90_8041ce48(r2)
	lfs f4, 0x10c(r29)
	lfs f2, float_0p1_8041ce44(r2)
	fsubs f1, f3, f4
	lfs f0, float_1_8041ce1c(r2)
	fmuls f5, f2, f1
	fadds f5, f5, f4
	fsubs f1, f3, f5
	fcmpo cr0, f1, f0
	mfcr r3
	lis r0, 0x4330
	srwi r3, r3, 31
	stw r0, 0x8(r1)
	xoris r0, r3, 0x8000
	lfd f2, 0x108(r31)
	stw r0, 0xc(r1)
	lfs f0, float_0_8041cdec(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fabs f1, f1
	fcmpu cr0, f1, f0
	beq @15
	fmr f5, f3
	@15:
	stfs f5, 0x10c(r29)
	stfs f5, 0x110(r29)
	b @9
	@14:
	lfs f3, float_270_8041ce34(r2)
	lfs f4, 0x10c(r29)
	lfs f2, float_0p1_8041ce44(r2)
	fsubs f1, f3, f4
	lfs f0, float_1_8041ce1c(r2)
	fmuls f5, f2, f1
	fadds f5, f5, f4
	fsubs f1, f3, f5
	fcmpo cr0, f1, f0
	mfcr r3
	lis r0, 0x4330
	srwi r3, r3, 31
	stw r0, 0x8(r1)
	xoris r0, r3, 0x8000
	lfd f2, 0x108(r31)
	stw r0, 0xc(r1)
	lfs f0, float_0_8041cdec(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fabs f1, f1
	fcmpu cr0, f1, f0
	beq @16
	fmr f5, f3
	@16:
	stfs f5, 0x10c(r29)
	stfs f5, 0x110(r29)
	b @9
	@13:
	lfs f0, 0x100(r29)
	li r30, 0x1
	lfs f1, float_180_8041ce38(r2)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @17
	lfs f1, float_0_8041cdec(r2)
	lfs f0, float_270_8041ce34(r2)
	stfs f1, 0x10c(r29)
	stfs f1, 0x110(r29)
	stfs f0, 0xfc(r29)
	stfs f0, 0x100(r29)
	b @18
	@17:
	stfs f1, 0x10c(r29)
	lfs f0, float_90_8041ce48(r2)
	stfs f1, 0x110(r29)
	stfs f0, 0xfc(r29)
	stfs f0, 0x100(r29)
	@18:
	lwz r6, 0x48(r31)
	li r4, 0x0
	lwz r5, 0x4c(r31)
	li r0, 0x64
	mr r3, r29
	stw r6, 0x88(r29)
	stw r5, 0x8c(r29)
	lwz r5, 0x50(r31)
	stw r5, 0x90(r29)
	lwz r6, 0x54(r31)
	lwz r5, 0x58(r31)
	stw r6, 0x7c(r29)
	stw r5, 0x80(r29)
	lwz r5, 0x5c(r31)
	stw r5, 0x84(r29)
	stb r4, 0x37(r29)
	lwz r4, 0x0(r29)
	rlwinm r4, r4, 0, 20, 18
	stw r4, 0x0(r29)
	lwz r4, 0x4(r29)
	rlwinm r4, r4, 0, 24, 22
	stw r4, 0x4(r29)
	lwz r4, 0x0(r29)
	rlwinm r4, r4, 0, 23, 21
	stw r4, 0x0(r29)
	lwz r4, 0x4(r29)
	rlwinm r4, r4, 0, 28, 26
	stw r4, 0x4(r29)
	lwz r4, 0x4(r29)
	rlwinm r4, r4, 0, 29, 27
	stw r4, 0x4(r29)
	stb r0, 0x3a(r29)
	bl partyPaperOff
	@9:
	mr r3, r30
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL party_slit(PartyEntry* party) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, vec3_802f3e40@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r4, vec3_802f3e40@l
	stw r30, 0x18(r1)
	li r30, 0x1
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lbz r0, 0x37(r3)
	lwz r29, 0x160(r3)
	cmplwi r0, 0x1
	beq @1
	li r3, 0x1
	b @2
	@1:
	lwz r4, 0x8(r28)
	clrlwi. r0, r4, 31
	beq @3
	clrrwi r0, r4, 1
	addi r4, r31, 0x148
	stw r0, 0x8(r28)
	lwz r0, 0x4(r28)
	ori r0, r0, 0x100
	stw r0, 0x4(r28)
	bl partyPaperOn
	mr r3, r28
	addi r4, r31, 0x150
	bl partyChgPaper
	li r0, 0x1e
	lfs f1, float_0_8041cdec(r2)
	stw r0, 0x24(r28)
	mr r3, r28
	bl unk_800c9398
	lfs f1, 0x100(r28)
	lfs f0, 0x198(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @4
	lwz r3, 0x4(r28)
	li r0, 0x0
	rlwinm r3, r3, 0, 23, 21
	stw r3, 0x4(r28)
	stb r0, 0x3a(r28)
	b @3
	@4:
	lwz r3, 0x4(r28)
	li r0, 0x2
	ori r3, r3, 0x200
	stw r3, 0x4(r28)
	stb r0, 0x3a(r28)
	@3:
	lbz r0, 0x3a(r28)
	cmpwi r0, 0x2
	beq @5
	bge @6
	cmpwi r0, 0x0
	beq @7
	b @8
	@6:
	cmpwi r0, 0xa
	beq @9
	b @8
	@7:
	lwz r3, 0x24(r28)
	subic. r0, r3, 0x1
	stw r0, 0x24(r28)
	bge @8
	lwz r0, 0x0(r28)
	mr r3, r28
	lfs f0, float_270_8041ce34(r2)
	addi r4, r31, 0x158
	ori r0, r0, 0x1000
	stw r0, 0x0(r28)
	stfs f0, 0x10c(r28)
	lfs f0, 0x10c(r28)
	stfs f0, 0x110(r28)
	bl partyChgPaper
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 18, 18
	bne @10
	li r0, 0xa
	li r30, 0x0
	stb r0, 0x3a(r28)
	b @8
	@10:
	li r0, 0x14
	stb r0, 0x3a(r28)
	b @8
	@5:
	lwz r3, 0x24(r28)
	subic. r0, r3, 0x1
	stw r0, 0x24(r28)
	bge @8
	lwz r0, 0x0(r28)
	mr r3, r28
	lfs f0, float_270_8041ce34(r2)
	addi r4, r31, 0x158
	ori r0, r0, 0x1000
	stw r0, 0x0(r28)
	stfs f0, 0x10c(r28)
	lfs f0, 0x10c(r28)
	stfs f0, 0x110(r28)
	bl partyChgPaper
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 18, 18
	bne @11
	li r0, 0xa
	li r30, 0x0
	stb r0, 0x3a(r28)
	b @8
	@11:
	li r0, 0x14
	stb r0, 0x3a(r28)
	b @8
	@9:
	lfs f1, 0x104(r28)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	bne @12
	mr r3, r28
	addi r4, r31, 0x158
	bl partyChgPaper
	lfs f0, float_270_8041ce34(r2)
	stfs f0, 0x10c(r28)
	b @13
	@12:
	lfs f1, 0x100(r28)
	lfs f0, 0x198(r29)
	fsubs f1, f1, f0
	bl revise360
	lfd f0, 0x160(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @14
	lwz r0, 0x4(r28)
	ori r0, r0, 0x200
	stw r0, 0x4(r28)
	b @15
	@14:
	lwz r0, 0x4(r28)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x4(r28)
	@15:
	lwz r0, 0x4(r28)
	rlwinm. r0, r0, 0, 22, 22
	beq @16
	lfs f0, float_280_8041ce4c(r2)
	b @17
	@16:
	lfs f0, float_260_8041ce50(r2)
	@17:
	stfs f0, 0x10c(r28)
	lfs f1, 0x100(r28)
	lfs f0, 0x198(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_315_8041ce54(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @18
	lfs f0, float_45_8041ce10(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq @18
	lfs f0, float_135_8041ce58(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @19
	lfs f0, float_225_8041ce5c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @19
	@18:
	mr r3, r28
	addi r4, r31, 0x168
	bl partyChgPaper
	b @13
	@19:
	mr r3, r28
	addi r4, r31, 0x170
	bl partyChgPaper
	@13:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 11, 11
	bne @8
	lwz r3, 0x12c(r28)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 18, 18
	bne @8
	lwz r3, 0x134(r28)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 18, 18
	bne @8
	li r0, 0x28
	stb r0, 0x3a(r28)
	@8:
	lbz r0, 0x3a(r28)
	cmpwi r0, 0x15
	beq @20
	bge @21
	cmpwi r0, 0x14
	bge @22
	b @23
	@21:
	cmpwi r0, 0x17
	bge @23
	b @24
	@22:
	mr r3, r28
	addi r4, r31, 0x178
	bl partyChgPaper
	lwz r4, 0x0(r28)
	li r0, 0x14
	lfs f1, float_0_8041cdec(r2)
	mr r3, r28
	oris r4, r4, 0x200
	stw r4, 0x0(r28)
	lwz r4, 0x0(r28)
	ori r4, r4, 0x20
	stw r4, 0x0(r28)
	stw r0, 0x24(r28)
	bl unk_800c9398
	li r0, 0x15
	stb r0, 0x3a(r28)
	b @23
	@20:
	lfs f1, 0x100(r28)
	lfs f0, 0xf8(r28)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @25
	lfs f0, float_260_8041ce50(r2)
	b @26
	@25:
	lfs f0, float_280_8041ce4c(r2)
	@26:
	stfs f0, 0x10c(r28)
	lfs f0, float_neg3_8041ce40(r2)
	lfs f1, 0x5c(r28)
	fadds f0, f1, f0
	stfs f0, 0x5c(r28)
	lwz r3, 0x24(r28)
	subic. r0, r3, 0x1
	stw r0, 0x24(r28)
	bgt @23
	li r0, 0x16
	stb r0, 0x3a(r28)
	b @23
	@24:
	li r0, 0xa
	stb r0, 0x3a(r28)
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r28)
	bl marioClearSlitFloor
	@23:
	lbz r0, 0x3a(r28)
	cmpwi r0, 0x29
	beq @27
	bge @28
	cmpwi r0, 0x28
	bge @29
	b @30
	@28:
	cmpwi r0, 0x2b
	bge @30
	b @31
	@29:
	mr r3, r28
	addi r4, r31, 0x180
	bl partyChgPaper
	li r3, 0x1e
	li r0, 0x29
	stw r3, 0x24(r28)
	stb r0, 0x3a(r28)
	lfs f1, 0x100(r28)
	lfs f0, 0x198(r29)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @32
	lfs f0, float_0_8041cdec(r2)
	@32:
	stfs f0, 0x10c(r28)
	lfs f0, 0x10c(r28)
	stfs f0, 0x110(r28)
	@27:
	lwz r3, 0x24(r28)
	subic. r0, r3, 0x1
	stw r0, 0x24(r28)
	bgt @30
	li r0, 0x2a
	stb r0, 0x3a(r28)
	b @30
	@31:
	lwz r0, 0x4(r28)
	mr r3, r28
	rlwinm r0, r0, 0, 26, 21
	stw r0, 0x4(r28)
	bl partyPaperOff
	lwz r3, 0x0(r28)
	li r0, 0x0
	rlwinm r3, r3, 0, 20, 17
	stw r3, 0x0(r28)
	stb r0, 0x37(r28)
	@30:
	mr r3, r30
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void partyChgMotSlitFloor(PartyEntry* party) {
	nofralloc
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 18, 18
	bnelr
	lwz r4, 0x160(r3)
	lwz r0, 0xc(r4)
	clrrwi. r0, r0, 31
	bne @1
	lwz r4, 0x8(r3)
	li r0, 0x1
	ori r4, r4, 0x1
	stw r4, 0x8(r3)
	stb r0, 0x37(r3)
	@1:
	lwz r0, 0x0(r3)
	ori r0, r0, 0x2000
	stw r0, 0x0(r3)
	blr
}

asm void L_partyForceSlitOff(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 19, 19
	bne @1
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @2
	@1:
	lfs f1, 0x100(r31)
	lfs f0, 0xf8(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @3
	lfs f0, float_0_8041cdec(r2)
	@3:
	stfs f0, 0x10c(r31)
	lfs f1, float_270_8041ce34(r2)
	lfs f0, 0x10c(r31)
	stfs f0, 0x110(r31)
	lfs f0, 0x10c(r31)
	fsubs f1, f1, f0
	bl revise360
	stfs f1, 0xfc(r31)
	mr r3, r31
	lfs f0, 0xfc(r31)
	stfs f0, 0x100(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 26, 21
	stw r0, 0x4(r31)
	bl partyPaperOff
	lwz r5, 0x0(r31)
	li r0, 0x0
	mr r3, r31
	li r4, 0x1
	rlwinm r5, r5, 0, 20, 17
	stw r5, 0x0(r31)
	stb r0, 0x37(r31)
	bl partyChgPoseId
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void allPartyForceSlitOff(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPartyId
	bl partyGetPtr
	mr. r31, r3
	beq @1
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 19, 19
	bne @2
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @1
	@2:
	lfs f1, 0x100(r31)
	lfs f0, 0xf8(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @3
	lfs f0, float_0_8041cdec(r2)
	@3:
	stfs f0, 0x10c(r31)
	lfs f1, float_270_8041ce34(r2)
	lfs f0, 0x10c(r31)
	stfs f0, 0x110(r31)
	lfs f0, 0x10c(r31)
	fsubs f1, f1, f0
	bl revise360
	stfs f1, 0xfc(r31)
	mr r3, r31
	lfs f0, 0xfc(r31)
	stfs f0, 0x100(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 26, 21
	stw r0, 0x4(r31)
	bl partyPaperOff
	lwz r5, 0x0(r31)
	li r0, 0x0
	mr r3, r31
	li r4, 0x1
	rlwinm r5, r5, 0, 20, 17
	stw r5, 0x0(r31)
	stb r0, 0x37(r31)
	bl partyChgPoseId
	@1:
	bl marioGetExtraPartyId
	bl partyGetPtr
	mr. r31, r3
	beq @4
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 19, 19
	bne @5
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @4
	@5:
	lfs f1, 0x100(r31)
	lfs f0, 0xf8(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041ce38(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_0_8041cdec(r2)
	@6:
	stfs f0, 0x10c(r31)
	lfs f1, float_270_8041ce34(r2)
	lfs f0, 0x10c(r31)
	stfs f0, 0x110(r31)
	lfs f0, 0x10c(r31)
	fsubs f1, f1, f0
	bl revise360
	stfs f1, 0xfc(r31)
	mr r3, r31
	lfs f0, 0xfc(r31)
	stfs f0, 0x100(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 26, 21
	stw r0, 0x4(r31)
	bl partyPaperOff
	lwz r5, 0x0(r31)
	li r0, 0x0
	mr r3, r31
	li r4, 0x1
	rlwinm r5, r5, 0, 20, 17
	stw r5, 0x0(r31)
	stb r0, 0x37(r31)
	bl partyChgPoseId
	@4:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void allPartySlitOff(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @1
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 19, 19
	beq @1
	lbz r0, 0x3a(r3)
	cmplwi r0, 0x28
	bge @1
	li r0, 0x28
	stb r0, 0x3a(r3)
	@1:
	bl marioGetExtraPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @2
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 19, 19
	beq @2
	lbz r0, 0x3a(r3)
	cmplwi r0, 0x28
	bge @2
	li r0, 0x28
	stb r0, 0x3a(r3)
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void allPartySlitOn(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @1
	lwz r4, 0x160(r3)
	lwz r0, 0xc(r4)
	clrrwi. r0, r0, 31
	bne @1
	lwz r4, 0x8(r3)
	li r0, 0x1
	ori r4, r4, 0x1
	stw r4, 0x8(r3)
	stb r0, 0x37(r3)
	@1:
	bl marioGetExtraPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @2
	lwz r4, 0x160(r3)
	lwz r0, 0xc(r4)
	clrrwi. r0, r0, 31
	bne @2
	lwz r4, 0x8(r3)
	li r0, 0x1
	ori r4, r4, 0x1
	stw r4, 0x8(r3)
	stb r0, 0x37(r3)
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void party_motion_damage(PartyEntry* party) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stw r31, 0x3c(r1)
	mr r31, r3
	stw r30, 0x38(r1)
	lwz r3, 0x8(r3)
	lwz r30, 0x160(r31)
	rlwinm. r0, r3, 0, 30, 30
	beq @1
	rlwinm r3, r3, 0, 31, 29
	li r0, 0x0
	stw r3, 0x8(r31)
	stb r0, 0x38(r31)
	@1:
	lbz r0, 0x38(r31)
	cmpwi r0, 0xa
	beq @2
	bge @3
	cmpwi r0, 0x1
	beq @4
	bge @5
	cmpwi r0, 0x0
	bge @6
	b @5
	@3:
	cmpwi r0, 0xc
	beq @7
	bge @5
	b @8
	@6:
	mr r3, r31
	li r4, 0x8
	bl partyChgPoseId
	lfs f1, float_15_8041ce60(r2)
	li r3, 0x3c
	lfs f0, float_0_8041cdec(r2)
	li r0, 0x1
	stfs f1, 0x114(r31)
	stfs f0, 0x118(r31)
	stw r3, 0x24(r31)
	stb r0, 0x38(r31)
	@4:
	lfs f1, 0x5c(r31)
	addi r3, r1, 0x20
	lfs f0, 0x114(r31)
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	fadds f0, f1, f0
	stfs f0, 0x5c(r31)
	lwz r7, 0x58(r31)
	lwz r0, 0x5c(r31)
	stw r7, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x60(r31)
	stw r0, 0x28(r1)
	bl marioGetScreenPos
	lfs f1, 0xc(r1)
	lfs f0, float_neg300_8041ce64(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @5
	li r3, 0x14
	li r0, 0xa
	stw r3, 0x24(r31)
	stb r0, 0x38(r31)
	b @5
	@2:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x1f
	beq @5
	cmplwi r0, 0x20
	beq @5
	lwz r3, 0x24(r31)
	subic. r0, r3, 0x1
	stw r0, 0x24(r31)
	bgt @5
	addi r3, r1, 0x2c
	bl partyGetReturnPos
	lfs f0, 0x2c(r1)
	mr r3, r31
	lfs f3, float_200_8041cdd8(r2)
	stfs f0, 0x58(r31)
	lfs f1, float_0_8041cdec(r2)
	lfs f2, 0x30(r1)
	lfs f0, float_neg1_8041cdf8(r2)
	fadds f2, f3, f2
	stfs f2, 0x5c(r31)
	lfs f2, 0x34(r1)
	stfs f2, 0x60(r31)
	stfs f1, 0x114(r31)
	stfs f0, 0x118(r31)
	bl unk_800c9398
	lwz r3, 0x0(r31)
	li r0, 0xb
	ori r3, r3, 0x20
	stw r3, 0x0(r31)
	lwz r3, 0x0(r31)
	oris r3, r3, 0x200
	stw r3, 0x0(r31)
	stb r0, 0x38(r31)
	b @5
	@8:
	lwz r7, 0x58(r31)
	addi r3, r1, 0x14
	lwz r0, 0x5c(r31)
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	stw r7, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x60(r31)
	stw r0, 0x1c(r1)
	bl marioGetScreenPos
	lfs f1, 0xc(r1)
	lfs f0, float_240_8041ce68(r2)
	fcmpo cr0, f1, f0
	ble @9
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r31)
	@9:
	mr r3, r31
	bl partyMove
	lfs f0, 0x114(r31)
	lfs f1, float_neg6_8041ce2c(r2)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @10
	lfs f0, float_0_8041cdec(r2)
	stfs f0, 0x118(r31)
	stfs f1, 0x114(r31)
	@10:
	lfs f1, 0x5c(r31)
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f1, f0
	bge @11
	lwz r3, 0x8c(r30)
	lwz r0, 0x90(r30)
	lfs f0, float_200_8041cdd8(r2)
	stw r3, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r0, 0x94(r30)
	stw r0, 0x60(r31)
	lfs f1, 0x5c(r31)
	fadds f0, f1, f0
	stfs f0, 0x5c(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 28, 24
	stw r0, 0x0(r31)
	@11:
	lwz r3, 0x138(r31)
	cmplwi r3, 0x0
	beq @5
	bne @12
	li r0, 0x0
	b @13
	@12:
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @14
	li r0, 0x1
	b @13
	@14:
	li r0, 0x0
	@13:
	cmpwi r0, 0x0
	bne @5
	li r3, 0xc
	li r0, 0x1e
	stb r3, 0x38(r31)
	stw r0, 0x24(r31)
	b @5
	@7:
	lwz r3, 0x24(r31)
	subic. r0, r3, 0x1
	stw r0, 0x24(r31)
	bgt @5
	mr r3, r31
	li r4, 0x2
	bl partyChgRunMode
	li r0, 0x0
	stb r0, 0x3b(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r31)
	@5:
	lwz r0, 0x44(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void party_motion_upstairs(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x8(r3)
	rlwinm. r0, r4, 0, 30, 30
	beq @1
	rlwinm r4, r4, 0, 31, 29
	li r0, 0x3
	stw r4, 0x8(r3)
	lfs f0, float_3_8041ce0c(r2)
	lwz r4, 0x0(r3)
	ori r4, r4, 0x40
	stw r4, 0x0(r3)
	stw r0, unk_804189ec(r13)
	lfs f2, 0x120(r3)
	lfs f1, 0x5c(r3)
	fsubs f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, unk_804189e8(r13)
	@1:
	lfs f1, 0x5c(r3)
	lfs f0, unk_804189e8(r13)
	fadds f0, f1, f0
	stfs f0, 0x5c(r3)
	lwz r4, unk_804189ec(r13)
	subic. r0, r4, 0x1
	stw r0, unk_804189ec(r13)
	bgt @2
	lwz r0, 0x0(r3)
	li r4, 0x1
	rlwinm r0, r0, 0, 26, 24
	stw r0, 0x0(r3)
	bl partyChgMot
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 party_motion_fall(PartyEntry* party) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	mr r30, r3
	stw r29, 0x24(r1)
	lwz r0, 0x0(r3)
	lwz r31, 0x160(r3)
	rlwinm. r0, r0, 0, 28, 28
	bne @1
	bl partyGetFootmarkId
	bl partyNextReadId
	@1:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq @2
	rlwinm r0, r3, 0, 31, 29
	mr r3, r30
	stw r0, 0x8(r30)
	li r4, 0x4
	bl partyChgPoseId
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 13, 11
	stw r0, 0x0(r30)
	@2:
	lwz r0, 0x0(r30)
	li r29, 0x0
	rlwinm. r0, r0, 0, 6, 6
	bne @3
	lfs f0, 0x114(r30)
	mr r3, r30
	lfs f1, float_10_8041cdd4(r2)
	fabs f2, f0
	bl partySearchGround
	mr r29, r3
	@3:
	cmplwi r29, 0x0
	beq @4
	mr r3, r29
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @4
	lbz r0, 0x32(r30)
	li r29, 0x0
	cmplwi r0, 0x0
	bne @4
	lbz r0, 0x4c(r30)
	extsb. r0, r0
	bne @4
	lwz r0, 0x8(r30)
	oris r0, r0, 0x100
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x200
	stw r0, 0x0(r30)
	@4:
	cmplwi r29, 0x0
	stw r29, 0x138(r30)
	bne @5
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r30)
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 26, 26
	bne @6
	ori r0, r3, 0x20
	lfs f1, float_0_8041cdec(r2)
	stw r0, 0x0(r30)
	lfs f0, 0x11c(r30)
	fcmpu cr0, f1, f0
	bne @6
	lfs f0, float_neg1p4_8041ce6c(r2)
	stfs f0, 0x11c(r30)
	@6:
	lfs f2, 0x114(r30)
	lfs f1, 0x11c(r30)
	lfs f0, float_neg16_8041ce70(r2)
	fadds f1, f2, f1
	stfs f1, 0x114(r30)
	lfs f1, 0x114(r30)
	fcmpo cr0, f1, f0
	bge @7
	stfs f0, 0x114(r30)
	@7:
	lfs f2, 0x5c(r30)
	lfs f1, 0x114(r30)
	lfs f0, float_neg2000_8041cdfc(r2)
	fadds f1, f2, f1
	stfs f1, 0x5c(r30)
	lfs f1, 0x5c(r30)
	fcmpo cr0, f1, f0
	bge @8
	lfs f0, float_neg2001_8041ce74(r2)
	stfs f0, 0x5c(r30)
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x1f
	beq @9
	cmplwi r0, 0x20
	bne @10
	@9:
	li r3, 0x2
	b @11
	@10:
	lwz r0, 0x0(r30)
	lfs f0, float_0_8041cdec(r2)
	rlwinm r0, r0, 0, 28, 24
	stw r0, 0x0(r30)
	stfs f0, 0x114(r30)
	stfs f0, 0x11c(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x8c(r31)
	lfs f4, 0x94(r31)
	bl angleABf
	stfs f1, 0x100(r30)
	lfs f1, 0x1ac(r31)
	bl toMovedir
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f0, f1
	bl revise360
	stfs f1, 0x54(r30)
	mr r3, r30
	addi r4, r30, 0x58
	bl partyGetAppearPos4
	lfs f1, 0x5c(r30)
	mr r3, r30
	lfs f0, float_37_8041ce78(r2)
	li r4, 0x0
	fadds f0, f1, f0
	stfs f0, 0x5c(r30)
	bl partyChgMot
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r30)
	@8:
	lfs f1, 0x104(r30)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @12
	lwz r5, 0x58(r30)
	mr r3, r30
	lwz r0, 0x5c(r30)
	addi r4, r1, 0x8
	lfs f0, float_1p3_8041ce7c(r2)
	stw r5, 0x8(r1)
	fmuls f1, f0, f1
	stw r0, 0xc(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x10(r1)
	lfs f2, 0x100(r30)
	bl partySearchFrontWall
	lfs f0, 0x8(r1)
	stfs f0, 0x58(r30)
	lfs f0, 0x10(r1)
	stfs f0, 0x60(r30)
	@12:
	li r3, 0x2
	b @11
	@5:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 26, 26
	beq @13
	rlwinm r0, r3, 0, 28, 24
	lfs f1, float_0_8041cdec(r2)
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x2
	stw r0, 0x0(r30)
	stfs f1, 0x114(r30)
	lfs f0, 0xe4(r30)
	stfs f0, 0x5c(r30)
	lfs f0, 0x104(r30)
	fcmpu cr0, f1, f0
	bne @14
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	b @15
	@14:
	mr r3, r30
	li r4, 0x1
	bl partyChgMot
	@15:
	mr r3, r30
	bl N_partyPlaySfxPartyLanding1
	li r3, 0x3
	b @11
	@13:
	rlwinm r0, r3, 0, 19, 17
	lfs f1, float_0_8041cdec(r2)
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 28, 24
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x2
	stw r0, 0x0(r30)
	stfs f1, 0x114(r30)
	lfs f0, 0xe4(r30)
	stfs f0, 0x5c(r30)
	lfs f0, 0x104(r30)
	fcmpu cr0, f1, f0
	bne @16
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	b @17
	@16:
	mr r3, r30
	li r4, 0x1
	bl partyChgMot
	@17:
	mr r3, r30
	bl N_partyPlaySfxPartyLanding1
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @18
	bl partyClearFootmark
	b @19
	@18:
	bl partyClearFootmark2
	@19:
	li r3, 0x3
	@11:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void party_motion_jump2(PartyEntry* party) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	mr r30, r3
	stw r29, 0x34(r1)
	lwz r3, 0x8(r3)
	lwz r31, 0x160(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq @1
	rlwinm r3, r3, 0, 31, 29
	li r0, 0x0
	stw r3, 0x8(r30)
	lfs f2, float_neg1_8041cdf8(r2)
	stw r0, 0x24(r30)
	lfs f1, float_2p25_8041ce80(r2)
	lfs f0, 0x224(r31)
	fmuls f0, f2, f0
	stfs f0, 0x11c(r30)
	lfs f0, 0x224(r31)
	fmuls f0, f1, f0
	stfs f0, 0x104(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl angleABf
	stfs f1, 0x100(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl distABf
	lfs f0, float_50_8041cde8(r2)
	fcmpo cr0, f1, f0
	ble @2
	fmr f1, f0
	@2:
	stfs f1, 0x128(r30)
	lfs f3, float_10_8041cdd4(r2)
	lfs f2, 0x104(r30)
	lfs f0, float_0p5_8041ce00(r2)
	fdivs f1, f1, f2
	lfs f4, 0x98(r30)
	lfs f2, 0x5c(r30)
	fmadds f0, f3, f1, f0
	fsubs f4, f4, f2
	fdivs f0, f0, f3
	fctiwz f0, f0
	stfd f0, 0x18(r1)
	lwz r5, 0x1c(r1)
	cmpwi r5, 0xa
	bge @3
	li r5, 0xa
	@3:
	xoris r3, r5, 0x8000
	lis r0, 0x4330
	stw r3, 0x24(r1)
	lis r4, double_to_int_802f3f48@ha
	lfd f3, double_to_int_802f3f48@l(r4)
	stw r0, 0x20(r1)
	lfs f2, float_0p5_8041ce00(r2)
	lfd f0, 0x20(r1)
	stw r5, 0x24(r30)
	fsubs f5, f0, f3
	lfs f0, float_20_8041cdc0(r2)
	lfs f1, 0x128(r30)
	lfs f3, 0x224(r31)
	fdivs f1, f1, f5
	fmuls f1, f3, f1
	stfs f1, 0x104(r30)
	lfs f1, 0x11c(r30)
	fabs f1, f1
	fmuls f1, f5, f1
	fmuls f1, f5, f1
	fmadds f1, f2, f1, f4
	fdivs f1, f1, f5
	stfs f1, 0x114(r30)
	lfs f2, 0x114(r30)
	lfs f1, 0x224(r31)
	fmuls f1, f2, f1
	stfs f1, 0x114(r30)
	lfs f1, 0x114(r30)
	fcmpo cr0, f1, f0
	ble @4
	stfs f0, 0x114(r30)
	@4:
	lfs f1, 0x114(r30)
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f1, f0
	bge @5
	stfs f0, 0x114(r30)
	@5:
	mr r3, r30
	li r4, 0x4
	bl partyChgPoseId
	lwz r0, 0x0(r30)
	addi r4, r30, 0x58
	li r3, 0x927
	ori r0, r0, 0x10
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r30)
	bl psndSFXOn_3D
	li r0, 0x0
	stb r0, 0x38(r30)
	@1:
	lbz r0, 0x38(r30)
	cmpwi r0, 0x1
	beq @6
	bge @7
	cmpwi r0, 0x0
	bge @8
	b @7
	@8:
	li r0, 0x1
	stb r0, 0x38(r30)
	b @7
	@6:
	lfs f1, 0x114(r30)
	mr r3, r30
	lfs f0, 0x11c(r30)
	addi r4, r1, 0x8
	fadds f0, f1, f0
	stfs f0, 0x114(r30)
	lfs f1, 0x5c(r30)
	lfs f0, 0x114(r30)
	fadds f0, f1, f0
	stfs f0, 0x5c(r30)
	lwz r5, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r5, 0x8(r1)
	stw r0, 0xc(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x10(r1)
	lfs f1, 0x104(r30)
	lfs f2, 0x100(r30)
	bl partySearchFrontWall
	lfs f0, 0x8(r1)
	lfs f2, float_0_8041cdec(r2)
	stfs f0, 0x58(r30)
	lfs f0, 0x10(r1)
	stfs f0, 0x60(r30)
	lfs f0, 0x114(r30)
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne @7
	fabs f1, f0
	mr r3, r30
	bl partySearchGround
	lfs f0, 0xe4(r30)
	mr. r29, r3
	stfs f0, 0xc(r1)
	beq @9
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @9
	lbz r0, 0x4c(r30)
	extsb. r0, r0
	bne @10
	lwz r0, 0x8(r30)
	oris r0, r0, 0x100
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x200
	stw r0, 0x0(r30)
	@10:
	li r0, 0x0
	mr r3, r30
	stw r0, 0x138(r30)
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r30)
	b @11
	@9:
	lfs f0, 0xc(r1)
	cmplwi r29, 0x0
	stfs f0, 0x5c(r30)
	stw r29, 0x138(r30)
	beq @7
	mr r3, r30
	bl N_partyPlaySfxPartyLanding1
	lwz r0, 0x0(r30)
	lfs f0, float_0_8041cdec(r2)
	rlwinm r0, r0, 0, 28, 24
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x2
	stw r0, 0x0(r30)
	stfs f0, 0x114(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl distABf
	lfs f0, float_5_8041ce18(r2)
	fcmpo cr0, f1, f0
	bge @12
	li r4, 0x0
	b @13
	@12:
	li r4, 0x1
	@13:
	mr r3, r30
	bl partyChgMot
	@7:
	lfs f1, 0x5c(r30)
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f1, f0
	bge @11
	lwz r0, 0x0(r30)
	lfs f0, float_0_8041cdec(r2)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r30)
	stfs f0, 0x114(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x8c(r31)
	lfs f4, 0x94(r31)
	bl angleABf
	stfs f1, 0x100(r30)
	mr r3, r30
	li r4, 0x0
	lwz r5, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r5, 0x58(r30)
	stw r0, 0x5c(r30)
	lwz r0, 0x94(r31)
	stw r0, 0x60(r30)
	bl partyChgMot
	@11:
	lwz r0, 0x44(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void party_motion_jump(PartyEntry* party) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stmw r27, 0x7c(r1)
	mr r28, r3
	lis r4, vec3_802f3e40@ha
	lwz r30, 0x160(r3)
	addi r31, r4, vec3_802f3e40@l
	bl partyGetFootmarkId
	lwz r4, 0x8(r28)
	mr r29, r3
	rlwinm. r0, r4, 0, 30, 30
	beq @1
	rlwinm r3, r4, 0, 31, 29
	li r0, 0x0
	stw r3, 0x8(r28)
	stb r0, 0x38(r28)
	@1:
	lbz r0, 0x38(r28)
	cmpwi r0, 0xa
	beq @2
	bge @3
	cmpwi r0, 0x0
	beq @4
	b @3
	@4:
	lfs f0, 0x94(r28)
	stfs f0, 0x10(r1)
	lfs f0, 0x98(r28)
	stfs f0, 0xc(r1)
	lfs f0, 0x9c(r28)
	stfs f0, 0x8(r1)
	lha r0, 0x28(r28)
	cmpwi r0, 0x0
	bne @5
	lbz r0, 0x34(r28)
	cmplwi r0, 0x9
	bne @6
	@5:
	lfs f0, 0x58(r28)
	addi r3, r1, 0x10
	addi r4, r1, 0x8
	stfs f0, 0x10(r1)
	lfs f0, 0x5c(r28)
	stfs f0, 0xc(r1)
	lfs f0, 0x60(r28)
	stfs f0, 0x8(r1)
	lfs f1, 0x104(r28)
	lfs f2, 0x100(r28)
	bl movePos
	lwz r0, 0x18(r31)
	lwz r3, 0x1c(r31)
	stw r0, 0x4c(r1)
	lfs f0, 0x10(r1)
	lwz r0, 0x20(r31)
	stfs f0, 0x4c(r1)
	lfs f1, 0xc(r1)
	stw r3, 0x50(r1)
	lfs f0, 0x8(r1)
	stw r0, 0x54(r1)
	lwz r0, 0x4c(r1)
	stfs f1, 0x50(r1)
	stfs f0, 0x54(r1)
	lwz r3, 0x50(r1)
	stw r0, 0x94(r28)
	lwz r0, 0x54(r1)
	stw r3, 0x98(r28)
	stw r0, 0x9c(r28)
	b @7
	@6:
	lwz r0, 0x8(r28)
	rlwinm. r0, r0, 0, 9, 9
	bne @7
	mr r3, r29
	bl partyGetFootmarkWriteId
	mr r27, r3
	mr r3, r29
	bl partyGetFootmarkReadId
	cmpw r3, r27
	bne @8
	lfs f1, 0x58(r28)
	mr r3, r29
	lfs f2, 0x60(r28)
	bl partyGetTargetDist
	lfs f2, float_2_8041ce08(r2)
	lfs f0, 0x1b4(r30)
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	ble @9
	lfs f1, 0x58(r28)
	mr r3, r29
	lfs f2, 0x60(r28)
	bl partyGetTargetDir
	fmr f30, f1
	mr r3, r28
	addi r4, r1, 0x58
	bl getFrontFloor
	lfs f3, 0x5c(r1)
	fmr f2, f30
	lfs f0, float_10_8041cdd4(r2)
	addi r3, r1, 0x10
	lfs f1, float_0p6_8041ce84(r2)
	addi r4, r1, 0x8
	fadds f0, f3, f0
	stfs f0, 0x5c(r1)
	stfs f0, 0xc(r1)
	lfs f0, 0x58(r28)
	stfs f0, 0x10(r1)
	lfs f0, 0x60(r28)
	stfs f0, 0x8(r1)
	lfs f0, 0xf4(r28)
	fmuls f1, f1, f0
	bl movePos
	@9:
	lwz r0, 0x24(r31)
	lwz r3, 0x28(r31)
	stw r0, 0x40(r1)
	lfs f0, 0x10(r1)
	lwz r0, 0x2c(r31)
	stfs f0, 0x40(r1)
	lfs f1, 0xc(r1)
	stw r3, 0x44(r1)
	lfs f0, 0x8(r1)
	stw r0, 0x48(r1)
	lwz r0, 0x40(r1)
	stfs f1, 0x44(r1)
	stfs f0, 0x48(r1)
	lwz r3, 0x44(r1)
	stw r0, 0x94(r28)
	lwz r0, 0x48(r1)
	stw r3, 0x98(r28)
	stw r0, 0x9c(r28)
	b @7
	@8:
	mr r3, r29
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	bl partyGetReadId
	lfs f30, float_50_8041cde8(r2)
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x10(r1)
	lfs f4, 0x8(r1)
	bl distABf
	lfs f2, 0xc(r1)
	fmr f31, f1
	lfs f0, 0x5c(r28)
	lfs f3, float_1p4_8041ce88(r2)
	fsubs f0, f2, f0
	lfs f2, float_50_8041cde8(r2)
	fmuls f0, f3, f0
	fcmpo cr0, f2, f0
	ble @10
	fmr f30, f0
	@10:
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x10(r1)
	lfs f4, 0x8(r1)
	bl angleABf
	addi r3, r1, 0x18
	addi r4, r1, 0x14
	bl sincosf
	fcmpo cr0, f31, f30
	ble @11
	fmr f31, f30
	mr r3, r29
	bl partyGetTargetDistY
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f0, f1
	bne @12
	fmr f31, f0
	@12:
	lfs f1, 0x58(r28)
	lfs f0, 0x18(r1)
	stfs f1, 0x10(r1)
	lwz r0, 0x30(r31)
	fmadds f3, f31, f0, f1
	lfs f1, 0x60(r28)
	lfs f0, 0x14(r1)
	stw r0, 0x34(r1)
	lwz r3, 0x34(r31)
	fmadds f2, f31, f0, f1
	stfs f1, 0x8(r1)
	lwz r0, 0x38(r31)
	stfs f3, 0x34(r1)
	lfs f1, 0xc(r1)
	lfs f0, float_10_8041cdd4(r2)
	stw r0, 0x3c(r1)
	fadds f0, f1, f0
	lwz r4, 0x34(r1)
	stw r3, 0x38(r1)
	stfs f0, 0x38(r1)
	stfs f2, 0x3c(r1)
	lwz r3, 0x38(r1)
	stfs f3, 0x10(r1)
	lwz r0, 0x3c(r1)
	stfs f2, 0x8(r1)
	stfs f0, 0xc(r1)
	stw r4, 0x94(r28)
	stw r3, 0x98(r28)
	stw r0, 0x9c(r28)
	b @13
	@11:
	mr r3, r29
	bl partyGetTargetDistY
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f0, f1
	bne @14
	fmr f31, f0
	@14:
	lfs f1, 0x18(r1)
	lfs f0, 0x10(r1)
	lwz r0, 0x3c(r31)
	fmadds f2, f31, f1, f0
	lwz r3, 0x40(r31)
	stw r0, 0x28(r1)
	lwz r0, 0x44(r31)
	stfs f2, 0x28(r1)
	lfs f1, 0x14(r1)
	lfs f0, 0x8(r1)
	stw r3, 0x2c(r1)
	fmadds f1, f31, f1, f0
	lfs f0, 0xc(r1)
	stw r0, 0x30(r1)
	lwz r4, 0x28(r1)
	stfs f0, 0x2c(r1)
	stfs f1, 0x30(r1)
	lwz r3, 0x2c(r1)
	stfs f2, 0x10(r1)
	lwz r0, 0x30(r1)
	stfs f1, 0x8(r1)
	stw r4, 0x94(r28)
	stw r3, 0x98(r28)
	stw r0, 0x9c(r28)
	@13:
	fcmpo cr0, f31, f30
	bge @7
	mr r3, r29
	bl partyNextReadId
	@7:
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x94(r28)
	lfs f4, 0x9c(r28)
	bl distABf
	stfs f1, 0x128(r28)
	lha r0, 0x28(r28)
	cmpwi r0, 0x0
	bne @15
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x94(r28)
	lfs f4, 0x9c(r28)
	bl angleABf
	stfs f1, 0x100(r28)
	lfs f1, float_2p25_8041ce80(r2)
	lwz r3, 0x160(r28)
	lfs f0, 0x224(r3)
	fmuls f0, f1, f0
	stfs f0, 0x104(r28)
	@15:
	lfs f5, 0x128(r28)
	lfs f0, 0x104(r28)
	lfs f2, float_0p9_8041ce8c(r2)
	fdivs f1, f5, f0
	lfs f3, float_10_8041cdd4(r2)
	lfs f0, float_0p5_8041ce00(r2)
	fmuls f1, f2, f1
	fmadds f0, f3, f1, f0
	fdivs f0, f0, f3
	fctiwz f0, f0
	stfd f0, 0x68(r1)
	lwz r0, 0x6c(r1)
	stw r0, 0x24(r28)
	lwz r0, 0x24(r28)
	cmpwi r0, 0xc
	bge @16
	li r0, 0xc
	stw r0, 0x24(r28)
	@16:
	lwz r0, 0x24(r28)
	cmpwi r0, 0x28
	ble @17
	li r0, 0x28
	stw r0, 0x24(r28)
	@17:
	lwz r3, 0x24(r28)
	lis r0, 0x4330
	lfs f1, 0x98(r28)
	xoris r3, r3, 0x8000
	lfs f0, 0x5c(r28)
	stw r3, 0x6c(r1)
	fsubs f6, f1, f0
	lfd f3, 0x108(r31)
	stw r0, 0x68(r1)
	lfs f4, float_0p5_8041ce00(r2)
	lfd f2, 0x68(r1)
	fabs f1, f6
	lfs f0, float_1_8041ce1c(r2)
	fsubs f2, f2, f3
	fcmpo cr0, f1, f0
	fmuls f4, f4, f2
	bge @18
	lfs f6, float_25_8041ce90(r2)
	b @19
	@18:
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f6, f0
	cror eq, gt, eq
	bne @20
	b @19
	@20:
	lfs f6, float_10_8041cdd4(r2)
	@19:
	fadds f3, f6, f6
	lfs f2, 0x224(r30)
	fmsubs f1, f4, f4, f4
	lfs f0, float_13_8041ce94(r2)
	fdivs f3, f3, f1
	fmuls f1, f3, f4
	fmuls f1, f2, f1
	stfs f1, 0x114(r28)
	lfs f1, 0x114(r28)
	fcmpo cr0, f1, f0
	ble @21
	stfs f0, 0x114(r28)
	@21:
	lfs f1, 0x114(r28)
	lfs f0, float_3_8041ce0c(r2)
	fcmpo cr0, f1, f0
	bge @22
	stfs f0, 0x114(r28)
	@22:
	fneg f1, f3
	lfs f0, 0x224(r30)
	mr r3, r28
	li r4, 0x4
	fmuls f0, f1, f0
	stfs f0, 0x11c(r28)
	lwz r0, 0x0(r28)
	ori r0, r0, 0x10
	stw r0, 0x0(r28)
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r28)
	bl partyChgPoseId
	addi r4, r28, 0x58
	li r3, 0x927
	bl psndSFXOn_3D
	li r0, 0xa
	stb r0, 0x38(r28)
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 28, 28
	bne @3
	mr r3, r28
	bl partyGetFootmarkId
	bl partyNextReadId
	b @3
	@2:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 28, 28
	bne @23
	mr r3, r28
	bl partyGetFootmarkId
	bl partyNextReadId
	@23:
	lfs f2, 0x114(r28)
	lfs f1, 0x11c(r28)
	lfs f0, float_neg2000_8041cdfc(r2)
	fadds f1, f2, f1
	stfs f1, 0x114(r28)
	lfs f2, 0x5c(r28)
	lfs f1, 0x114(r28)
	fadds f1, f2, f1
	stfs f1, 0x5c(r28)
	lfs f1, 0x5c(r28)
	fcmpo cr0, f1, f0
	bge @24
	lwz r0, 0x0(r28)
	lfs f0, float_0_8041cdec(r2)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r28)
	stfs f0, 0x114(r28)
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl angleABf
	stfs f1, 0x100(r28)
	mr r3, r28
	li r4, 0x0
	lwz r5, 0x8c(r30)
	lwz r0, 0x90(r30)
	stw r5, 0x58(r28)
	stw r0, 0x5c(r28)
	lwz r0, 0x94(r30)
	stw r0, 0x60(r28)
	bl partyChgMot
	b @3
	@24:
	lfs f0, 0x114(r28)
	lfs f2, float_0_8041cdec(r2)
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne @25
	lwz r0, 0x0(r28)
	mr r3, r28
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r28)
	lwz r0, 0x0(r28)
	ori r0, r0, 0x20
	stw r0, 0x0(r28)
	lfs f0, 0x114(r28)
	fabs f1, f0
	bl partySearchGround
	mr. r29, r3
	beq @26
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @26
	lbz r0, 0x4c(r28)
	extsb. r0, r0
	bne @27
	lwz r0, 0x8(r28)
	oris r0, r0, 0x100
	stw r0, 0x8(r28)
	lwz r0, 0x0(r28)
	oris r0, r0, 0x200
	stw r0, 0x0(r28)
	@27:
	li r0, 0x0
	mr r3, r28
	stw r0, 0x138(r28)
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r28)
	b @3
	@26:
	stw r29, 0x138(r28)
	cmplwi r29, 0x0
	lfs f0, 0xe4(r28)
	stfs f0, 0x5c(r28)
	beq @25
	lwz r0, 0x0(r28)
	mr r3, r28
	ori r0, r0, 0x2
	stw r0, 0x0(r28)
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 28, 24
	stw r0, 0x0(r28)
	bl N_partyPlaySfxPartyLanding1
	lfs f0, float_0_8041cdec(r2)
	mr r3, r28
	li r4, 0x0
	stfs f0, 0x114(r28)
	bl partyChgMot
	lwz r0, 0x8(r28)
	oris r0, r0, 0x80
	stw r0, 0x8(r28)
	b @3
	@25:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 7, 7
	beq @28
	lfs f1, 0x104(r28)
	addi r3, r1, 0x1c
	lfs f2, 0x100(r28)
	addi r4, r1, 0x24
	bl movePos
	b @3
	@28:
	lwz r5, 0x58(r28)
	mr r3, r28
	lwz r0, 0x5c(r28)
	addi r4, r1, 0x1c
	stw r5, 0x1c(r1)
	stw r0, 0x20(r1)
	lwz r0, 0x60(r28)
	stw r0, 0x24(r1)
	lfs f1, 0x104(r28)
	lfs f2, 0x100(r28)
	bl partySearchFrontWall
	cmplwi r3, 0x0
	beq @29
	stw r3, 0x12c(r28)
	lfs f0, float_0_8041cdec(r2)
	lfs f1, 0x104(r28)
	fcmpu cr0, f1, f0
	beq @29
	stw r3, 0x134(r28)
	@29:
	lfs f0, 0x1c(r1)
	stfs f0, 0x58(r28)
	lfs f0, 0x24(r1)
	stfs f0, 0x60(r28)
	@3:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	lmw r27, 0x7c(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm void party_motion_beside_mario(PartyEntry* party) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	mr r30, r3
	lwz r3, 0x8(r3)
	lwz r31, 0x160(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq @1
	rlwinm r0, r3, 0, 31, 29
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @2
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @3
	@2:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @4
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @3
	@4:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@3:
	lfs f0, float_90_8041ce48(r2)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r30)
	addi r3, r1, 0x28
	lfs f2, float_1p5_8041ce98(r2)
	addi r4, r1, 0x24
	lfs f1, 0x1b4(r31)
	lfs f0, 0x8c(r31)
	fmuls f1, f2, f1
	stfs f0, 0x28(r1)
	lfs f0, 0x94(r31)
	stfs f0, 0x24(r1)
	lfs f2, 0x54(r30)
	bl movePos
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl distABf
	fctiwz f0, f1
	stfd f0, 0x30(r1)
	lwz r0, 0x34(r1)
	stw r0, 0x24(r30)
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	bgt @1
	li r0, 0x1
	stw r0, 0x24(r30)
	@1:
	bl marioKeyOffChk
	cmpwi r3, 0x0
	beq @5
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @6
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @7
	@6:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @8
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @7
	@8:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@7:
	lfs f0, float_90_8041ce48(r2)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r30)
	@5:
	lfs f1, 0x1b4(r31)
	addi r3, r1, 0x28
	lfs f0, 0x8c(r31)
	addi r4, r1, 0x24
	lfs f2, float_1p5_8041ce98(r2)
	stfs f0, 0x28(r1)
	fmuls f1, f2, f1
	lfs f0, 0x94(r31)
	stfs f0, 0x24(r1)
	lfs f31, 0x90(r31)
	lfs f2, 0x54(r30)
	bl movePos
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl angleABf
	lfs f0, touch_wall_ct(r13)
	addi r4, r1, 0x8
	lfs f4, float_0_8041cdec(r2)
	addi r5, r1, 0xc
	fadds f2, f31, f0
	lfs f0, float_1000_8041cdf4(r2)
	fmr f6, f4
	lfs f1, 0x28(r1)
	stfs f0, 0x14(r1)
	addi r6, r1, 0x10
	lfs f3, 0x24(r1)
	addi r7, r1, 0x14
	lfs f5, float_neg1_8041cdf8(r2)
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne @9
	lfs f31, float_neg2000_8041cdfc(r2)
	b @10
	@9:
	lfs f2, float_100_8041cde0(r2)
	lis r0, 0x4330
	lfs f1, 0xc(r1)
	lis r4, double_to_int_802f3f48@ha
	lfs f0, float_0p5_8041ce00(r2)
	stw r0, 0x38(r1)
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802f3f48@l(r4)
	fctiwz f0, f0
	stfd f0, 0x30(r1)
	lwz r0, 0x34(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x3c(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	bl hitGetAttr
	@10:
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f31, f0
	cror eq, lt, eq
	bne @11
	lfs f1, 0x1b4(r31)
	lfs f0, 0x8c(r31)
	lfs f2, float_1p5_8041ce98(r2)
	stfs f0, 0x28(r1)
	fmuls f31, f2, f1
	lfs f0, 0x94(r31)
	stfs f0, 0x24(r1)
	lfs f1, 0x1a8(r31)
	bl toMovedir
	fmr f2, f1
	addi r3, r1, 0x28
	fmr f1, f31
	addi r4, r1, 0x24
	bl movePos
	@11:
	lfs f1, 0x180(r31)
	lfs f0, float_1_8041ce1c(r2)
	lfs f31, float_2_8041ce08(r2)
	fcmpo cr0, f1, f0
	ble @12
	lfs f31, float_10_8041cdd4(r2)
	@12:
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl distABf
	lwz r3, 0x24(r30)
	fcmpo cr0, f1, f31
	subi r0, r3, 0x1
	stw r0, 0x24(r30)
	cror eq, gt, eq
	bne @13
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	ble @13
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl angleABf
	stfs f1, 0x100(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl distABf
	lfs f2, float_10_8041cdd4(r2)
	lfs f0, float_2_8041ce08(r2)
	fdivs f1, f1, f2
	fcmpo cr0, f1, f0
	ble @14
	fmr f1, f0
	@14:
	lfs f0, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f0
	bge @15
	fmr f1, f0
	@15:
	mr r3, r30
	bl unk_800c9398
	mr r3, r30
	bl partyMoveCheckWall
	lfs f1, 0x104(r30)
	mr r3, r30
	bl unk_800c8f24
	lfs f1, float_10_8041cdd4(r2)
	mr r3, r30
	lfs f2, float_0_8041cdec(r2)
	bl partySearchGround
	mr. r29, r3
	beq @16
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @16
	lbz r0, 0x4c(r30)
	li r29, 0x0
	extsb. r0, r0
	bne @16
	lwz r0, 0x8(r30)
	oris r0, r0, 0x100
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x200
	stw r0, 0x0(r30)
	@16:
	cmplwi r29, 0x0
	stw r29, 0x138(r30)
	bne @17
	mr r3, r30
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r30)
	@17:
	lfs f0, 0xe4(r30)
	stfs f0, 0x5c(r30)
	b @18
	@13:
	li r0, 0x0
	mr r3, r30
	stw r0, 0x24(r30)
	li r4, 0x1
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x8c(r31)
	mr r3, r30
	lfs f2, 0x94(r31)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x8
	stw r0, 0x0(r30)
	@18:
	lwz r0, 0x134(r30)
	cmplwi r0, 0x0
	beq @19
	mr r3, r30
	li r4, 0x1
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x8c(r31)
	mr r3, r30
	lfs f2, 0x94(r31)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	@19:
	psq_l f31, 0x58(r1), 0, 0
	lwz r0, 0x64(r1)
	lfd f31, 0x50(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r29, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void party_motion_behind_mario_fly(PartyEntry* party) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	mr r30, r3
	lwz r3, 0x8(r3)
	lwz r31, 0x160(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq @1
	rlwinm r0, r3, 0, 31, 29
	stw r0, 0x8(r30)
	lwz r0, 0x8(r30)
	oris r0, r0, 0x4
	stw r0, 0x8(r30)
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 11, 11
	bne @2
	rlwinm. r0, r3, 0, 15, 15
	bne @3
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @4
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @5
	@4:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @6
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @5
	@6:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@5:
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f1, f0
	bl revise360
	b @7
	@3:
	rlwinm r0, r3, 0, 16, 14
	stw r0, 0x8(r30)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl angleABf
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f0, f1
	bl revise360
	@7:
	stfs f1, 0x54(r30)
	@2:
	mr r3, r30
	addi r4, r30, 0x94
	bl partyGetAppearPos4
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl distABf
	fctiwz f0, f1
	stfd f0, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r0, 0x24(r30)
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	bgt @1
	li r0, 0x1
	stw r0, 0x24(r30)
	@1:
	lwz r0, 0x8(r30)
	rlwinm. r0, r0, 0, 11, 11
	bne @8
	bl marioKeyOffChk
	cmpwi r3, 0x0
	beq @8
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @9
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @10
	@9:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @11
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @10
	@11:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@10:
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r30)
	@8:
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl angleABf
	lfs f1, 0x180(r31)
	lfs f0, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f0
	ble @12
	lfs f30, float_6_8041ce30(r2)
	b @13
	@12:
	lfs f30, float_2_8041ce08(r2)
	@13:
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl distABf
	fmr f31, f1
	lwz r3, 0x24(r30)
	subi r0, r3, 0x1
	fcmpo cr0, f31, f30
	stw r0, 0x24(r30)
	cror eq, gt, eq
	beq @14
	lfs f2, 0x98(r30)
	lfs f1, 0x5c(r30)
	lfs f0, float_2_8041ce08(r2)
	fsubs f1, f2, f1
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @15
	@14:
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	ble @15
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl angleABf
	stfs f1, 0x100(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl distABf
	lwz r0, 0x8(r30)
	rlwinm. r0, r0, 0, 11, 11
	beq @16
	lfs f29, float_3p6_8041ce9c(r2)
	b @17
	@16:
	lfs f29, float_2_8041ce08(r2)
	@17:
	fcmpo cr0, f31, f30
	bge @18
	lfs f29, float_0_8041cdec(r2)
	mr r3, r30
	fmr f1, f29
	bl unk_800c9398
	@18:
	fmr f1, f29
	mr r3, r30
	bl unk_800c93d0
	lwz r6, 0x58(r30)
	mr r3, r30
	lwz r0, 0x5c(r30)
	addi r4, r1, 0x8
	addi r5, r1, 0xc
	stw r6, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x18(r1)
	bl partyGetMoveDirSpd
	lfs f1, 0xc(r1)
	mr r3, r30
	lfs f2, 0x8(r1)
	addi r4, r1, 0x10
	bl partySearchFrontWall
	cmplwi r3, 0x0
	beq @19
	stw r3, 0x12c(r30)
	lfs f0, float_0_8041cdec(r2)
	lfs f1, 0x104(r30)
	fcmpu cr0, f1, f0
	beq @19
	stw r3, 0x134(r30)
	@19:
	lfs f0, 0x10(r1)
	mr r3, r30
	lfs f2, float_0p05_8041cea0(r2)
	stfs f0, 0x58(r30)
	lfs f0, 0x18(r1)
	stfs f0, 0x60(r30)
	lfs f0, 0x98(r30)
	lfs f1, 0x5c(r30)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x5c(r30)
	lfs f1, 0x104(r30)
	bl unk_800c8f24
	b @20
	@15:
	li r0, 0x0
	stw r0, 0x24(r30)
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 10, 10
	beq @21
	rlwinm r0, r3, 0, 15, 13
	stw r0, 0x8(r30)
	lbz r0, 0x32(r30)
	cmplwi r0, 0x1
	bne @21
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	@21:
	mr r3, r30
	li r4, 0x1
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x8c(r31)
	mr r3, r30
	lfs f2, 0x94(r31)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	mr r3, r30
	lfs f1, float_0_8041cdec(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	bl unk_800c9398
	lwz r0, 0x0(r30)
	mr r3, r30
	oris r0, r0, 0x8
	stw r0, 0x0(r30)
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x8(r30)
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 14, 12
	stw r0, 0x8(r30)
	bl unk_800c8e74
	lwz r0, 0x134(r30)
	cmplwi r0, 0x0
	beq @22
	lwz r0, 0x0(r30)
	mr r3, r30
	li r4, 0x1
	oris r0, r0, 0x8
	stw r0, 0x0(r30)
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x8c(r31)
	mr r3, r30
	lfs f2, 0x94(r31)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 14, 12
	stw r0, 0x8(r30)
	@22:
	lfs f1, float_100_8041cde0(r2)
	mr r3, r30
	fmr f2, f1
	bl partySearchGround
	mr. r29, r3
	beq @23
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @24
	lbz r0, 0x4c(r30)
	li r29, 0x0
	extsb. r0, r0
	bne @24
	lwz r0, 0x8(r30)
	oris r0, r0, 0x100
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x200
	stw r0, 0x0(r30)
	@24:
	lfs f0, 0xf0(r30)
	fcmpo cr0, f31, f0
	ble @25
	li r29, 0x0
	@25:
	lfs f0, 0xe4(r30)
	lfs f1, 0x5c(r30)
	lfs f2, float_0p05_8041cea0(r2)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x5c(r30)
	@23:
	stw r29, 0x138(r30)
	@20:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r0, 0x74(r1)
	lwz r29, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void party_motion_behind_mario_continue(PartyEntry* party) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	lwz r0, 0x0(r3)
	mr r30, r3
	lwz r31, 0x160(r3)
	rlwinm. r0, r0, 0, 28, 28
	bne @1
	lfs f1, 0x1a8(r31)
	bl toMovedir
	b @2
	@1:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @3
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @2
	@3:
	lfs f1, 0x1a8(r31)
	bl toMovedir
	@2:
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r30)
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq @4
	rlwinm r0, r3, 0, 31, 29
	lfs f2, float_1p5_8041ce98(r2)
	stw r0, 0x8(r30)
	addi r3, r1, 0x28
	addi r4, r1, 0x24
	lfs f1, 0x1b4(r31)
	lfs f0, 0x8c(r31)
	fmuls f1, f2, f1
	stfs f0, 0x28(r1)
	lfs f0, 0x94(r31)
	stfs f0, 0x24(r1)
	lfs f2, 0x54(r30)
	bl movePos
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl distABf
	fctiwz f0, f1
	stfd f0, 0x30(r1)
	lwz r0, 0x34(r1)
	stw r0, 0x24(r30)
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	bgt @4
	li r0, 0x1
	stw r0, 0x24(r30)
	@4:
	bl marioKeyOffChk
	cmpwi r3, 0x0
	beq @5
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @6
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @7
	@6:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @8
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @7
	@8:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@7:
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r30)
	@5:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @9
	lfs f1, 0x1b4(r31)
	lfs f0, 0x8c(r31)
	lfs f2, float_1p5_8041ce98(r2)
	stfs f0, 0x28(r1)
	fmuls f31, f2, f1
	lfs f0, 0x94(r31)
	stfs f0, 0x24(r1)
	lfs f30, 0x90(r31)
	b @10
	@9:
	lfs f1, float_1p5_8041ce98(r2)
	lfs f0, 0x1b4(r31)
	lbz r3, 0x2f(r30)
	fmuls f31, f1, f0
	extsb r3, r3
	bl anotherPartyGetPtr
	cmplwi r3, 0x0
	beq @11
	lfs f0, 0x58(r3)
	stfs f0, 0x28(r1)
	lfs f0, 0x60(r3)
	stfs f0, 0x24(r1)
	lfs f30, 0x5c(r3)
	b @10
	@11:
	lfs f0, 0x8c(r31)
	stfs f0, 0x28(r1)
	lfs f0, 0x94(r31)
	stfs f0, 0x24(r1)
	lfs f30, 0x90(r31)
	@10:
	fmr f1, f31
	lfs f2, 0x54(r30)
	addi r3, r1, 0x28
	addi r4, r1, 0x24
	bl movePos
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl angleABf
	lfs f0, touch_wall_ct(r13)
	addi r4, r1, 0x8
	lfs f4, float_0_8041cdec(r2)
	addi r5, r1, 0xc
	fadds f2, f30, f0
	lfs f0, float_1000_8041cdf4(r2)
	fmr f6, f4
	lfs f1, 0x28(r1)
	stfs f0, 0x14(r1)
	addi r6, r1, 0x10
	lfs f3, 0x24(r1)
	addi r7, r1, 0x14
	lfs f5, float_neg1_8041cdf8(r2)
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne @12
	lfs f30, float_neg2000_8041cdfc(r2)
	b @13
	@12:
	lfs f2, float_100_8041cde0(r2)
	lis r0, 0x4330
	lfs f1, 0xc(r1)
	lis r4, double_to_int_802f3f48@ha
	lfs f0, float_0p5_8041ce00(r2)
	stw r0, 0x38(r1)
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802f3f48@l(r4)
	fctiwz f0, f0
	stfd f0, 0x30(r1)
	lwz r0, 0x34(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x3c(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f1
	fdivs f30, f0, f2
	bl hitGetAttr
	@13:
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f30, f0
	cror eq, lt, eq
	bne @14
	lfs f2, float_1p5_8041ce98(r2)
	lfs f0, 0x1b4(r31)
	lfs f1, 0x1a8(r31)
	fmuls f31, f2, f0
	bl toMovedir
	fmr f2, f1
	addi r3, r1, 0x28
	fmr f1, f31
	addi r4, r1, 0x24
	bl movePos
	@14:
	lfs f1, 0x180(r31)
	lfs f0, float_1_8041ce1c(r2)
	lfs f30, float_2_8041ce08(r2)
	fcmpo cr0, f1, f0
	ble @15
	lfs f30, float_10_8041cdd4(r2)
	@15:
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl distABf
	lwz r3, 0x24(r30)
	fcmpo cr0, f1, f30
	subi r0, r3, 0x1
	stw r0, 0x24(r30)
	cror eq, gt, eq
	bne @16
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl angleABf
	stfs f1, 0x100(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x28(r1)
	lfs f4, 0x24(r1)
	bl distABf
	lfs f2, float_10_8041cdd4(r2)
	lfs f0, float_2_8041ce08(r2)
	fdivs f1, f1, f2
	fcmpo cr0, f1, f0
	ble @17
	fmr f1, f0
	@17:
	lfs f0, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f0
	bge @18
	fmr f1, f0
	@18:
	mr r3, r30
	bl unk_800c9398
	mr r3, r30
	bl partyMoveCheckWall
	lfs f1, 0x104(r30)
	mr r3, r30
	bl unk_800c8f24
	lfs f1, float_10_8041cdd4(r2)
	mr r3, r30
	lfs f2, float_0_8041cdec(r2)
	bl partySearchGround
	mr. r29, r3
	beq @19
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @19
	lbz r0, 0x4c(r30)
	li r29, 0x0
	extsb. r0, r0
	bne @19
	lwz r0, 0x8(r30)
	oris r0, r0, 0x100
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x200
	stw r0, 0x0(r30)
	@19:
	cmplwi r29, 0x0
	stw r29, 0x138(r30)
	bne @20
	mr r3, r30
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r30)
	@20:
	lfs f0, 0xe4(r30)
	stfs f0, 0x5c(r30)
	b @21
	@16:
	li r0, 0x0
	lfs f1, float_0_8041cdec(r2)
	stw r0, 0x24(r30)
	lfs f0, 0x180(r31)
	fcmpu cr0, f1, f0
	bne @21
	lwz r0, 0x0(r30)
	mr r3, r30
	li r4, 0x1
	oris r0, r0, 0x8
	stw r0, 0x0(r30)
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x8c(r31)
	mr r3, r30
	lfs f2, 0x94(r31)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	@21:
	lwz r0, 0x134(r30)
	cmplwi r0, 0x0
	beq @22
	mr r3, r30
	li r4, 0x1
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x28(r1)
	mr r3, r30
	lfs f2, 0x24(r1)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	@22:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r0, 0x74(r1)
	lwz r29, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void party_motion_behind_mario(PartyEntry* party) {
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
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	stw r29, 0x84(r1)
	mr r30, r3
	lwz r3, 0x8(r3)
	lwz r31, 0x160(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq @1
	rlwinm r0, r3, 0, 31, 29
	stw r0, 0x8(r30)
	lwz r0, 0x8(r30)
	oris r0, r0, 0x4
	stw r0, 0x8(r30)
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 11, 11
	bne @2
	rlwinm. r0, r3, 0, 15, 15
	bne @3
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @4
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @5
	@4:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @6
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @5
	@6:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@5:
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f1, f0
	bl revise360
	b @7
	@3:
	rlwinm r0, r3, 0, 16, 14
	stw r0, 0x8(r30)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x94(r30)
	lfs f4, 0x9c(r30)
	bl angleABf
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f0, f1
	bl revise360
	@7:
	stfs f1, 0x54(r30)
	@2:
	mr r3, r30
	addi r4, r1, 0x64
	bl partyGetAppearPos4
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x64(r1)
	lfs f4, 0x6c(r1)
	bl distABf
	fctiwz f0, f1
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r0, 0x24(r30)
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	bgt @1
	li r0, 0x1
	stw r0, 0x24(r30)
	@1:
	lwz r0, 0x8(r30)
	rlwinm. r0, r0, 0, 11, 11
	bne @8
	bl marioKeyOffChk
	cmpwi r3, 0x0
	beq @8
	lwz r0, 0x0(r30)
	lwz r29, 0x160(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @9
	lfs f1, 0x1a8(r29)
	bl toMovedir
	b @10
	@9:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @11
	lfs f1, 0x10c(r3)
	mr r3, r30
	bl partyToMovedir
	b @10
	@11:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@10:
	lfs f0, float_180_8041ce38(r2)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r30)
	@8:
	mr r3, r30
	addi r4, r1, 0x64
	bl partyGetAppearPos4
	lfs f3, 0x64(r1)
	lfs f4, 0x6c(r1)
	stfs f3, 0x60(r1)
	lfs f30, 0x68(r1)
	stfs f4, 0x5c(r1)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	bl angleABf
	lfs f0, touch_wall_ct(r13)
	fmr f31, f1
	lfs f4, float_0_8041cdec(r2)
	addi r4, r1, 0x40
	fadds f2, f30, f0
	lfs f0, float_1000_8041cdf4(r2)
	fmr f6, f4
	stfs f0, 0x4c(r1)
	addi r5, r1, 0x44
	lfs f1, 0x60(r1)
	lfs f3, 0x5c(r1)
	addi r6, r1, 0x48
	lfs f5, float_neg1_8041cdf8(r2)
	addi r7, r1, 0x4c
	addi r8, r1, 0x50
	addi r9, r1, 0x54
	addi r10, r1, 0x58
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne @12
	lfs f29, float_neg2000_8041cdfc(r2)
	b @13
	@12:
	lfs f2, float_100_8041cde0(r2)
	lis r0, 0x4330
	lfs f1, 0x44(r1)
	lis r4, double_to_int_802f3f48@ha
	lfs f0, float_0p5_8041ce00(r2)
	stw r0, 0x78(r1)
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802f3f48@l(r4)
	fctiwz f0, f0
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f1
	fdivs f29, f0, f2
	bl hitGetAttr
	@13:
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f29, f0
	cror eq, lt, eq
	bne @14
	lfs f2, float_1p5_8041ce98(r2)
	lfs f0, 0x1b4(r31)
	lfs f1, 0x1a8(r31)
	fmuls f29, f2, f0
	bl toMovedir
	fmr f2, f1
	addi r3, r1, 0x60
	fmr f1, f29
	addi r4, r1, 0x5c
	bl movePos
	@14:
	lfs f1, 0x180(r31)
	lfs f0, float_1_8041ce1c(r2)
	lfs f28, float_2_8041ce08(r2)
	fcmpo cr0, f1, f0
	ble @15
	lfs f28, float_10_8041cdd4(r2)
	@15:
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x60(r1)
	lfs f4, 0x5c(r1)
	bl distABf
	fmr f29, f1
	lwz r3, 0x24(r30)
	subi r0, r3, 0x1
	fcmpo cr0, f29, f28
	stw r0, 0x24(r30)
	cror eq, gt, eq
	bne @16
	lwz r0, 0x24(r30)
	cmpwi r0, 0x0
	ble @16
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x60(r1)
	lfs f4, 0x5c(r1)
	bl angleABf
	stfs f1, 0x100(r30)
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x60(r1)
	lfs f4, 0x5c(r1)
	bl distABf
	lwz r0, 0x8(r30)
	mr r3, r30
	rlwinm. r0, r0, 0, 11, 11
	beq @17
	lfs f1, float_3p6_8041ce9c(r2)
	b @18
	@17:
	lfs f1, float_2_8041ce08(r2)
	@18:
	bl unk_800c9398
	mr r3, r30
	bl partyMoveCheckWall
	lfs f1, 0x104(r30)
	mr r3, r30
	bl unk_800c8f24
	lwz r0, 0x12c(r30)
	cmplwi r0, 0x0
	beq @19
	lfs f0, 0x58(r30)
	fmr f1, f29
	fmr f2, f31
	addi r3, r1, 0x60
	stfs f0, 0x60(r1)
	addi r4, r1, 0x5c
	lfs f0, 0x60(r30)
	stfs f0, 0x5c(r1)
	bl movePos
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x60(r1)
	lfs f4, 0x5c(r1)
	bl angleABf
	lfs f0, touch_wall_ct(r13)
	addi r4, r1, 0x24
	lfs f4, float_0_8041cdec(r2)
	addi r5, r1, 0x28
	fadds f2, f30, f0
	lfs f0, float_1000_8041cdf4(r2)
	fmr f6, f4
	lfs f1, 0x60(r1)
	stfs f0, 0x30(r1)
	addi r6, r1, 0x2c
	lfs f3, 0x5c(r1)
	addi r7, r1, 0x30
	lfs f5, float_neg1_8041cdf8(r2)
	addi r8, r1, 0x34
	addi r9, r1, 0x38
	addi r10, r1, 0x3c
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne @20
	lfs f28, float_neg2000_8041cdfc(r2)
	b @21
	@20:
	lfs f2, float_100_8041cde0(r2)
	lis r0, 0x4330
	lfs f1, 0x28(r1)
	lis r4, double_to_int_802f3f48@ha
	lfs f0, float_0p5_8041ce00(r2)
	stw r0, 0x70(r1)
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802f3f48@l(r4)
	fctiwz f0, f0
	stfd f0, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	fdivs f28, f0, f2
	bl hitGetAttr
	@21:
	lfs f1, 0x5c(r30)
	lfs f0, float_1_8041ce1c(r2)
	fsubs f1, f1, f28
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @22
	lfs f0, 0x60(r1)
	mr r3, r30
	li r4, 0x2
	stfs f0, 0x94(r30)
	stfs f28, 0x98(r30)
	lfs f0, 0x5c(r1)
	stfs f0, 0x9c(r30)
	bl partyChgMot
	b @23
	@19:
	lfs f0, 0x5c(r30)
	fcmpo cr0, f30, f0
	ble @22
	lfs f0, 0x58(r30)
	fmr f1, f29
	fmr f2, f31
	addi r3, r1, 0x60
	stfs f0, 0x60(r1)
	addi r4, r1, 0x5c
	lfs f0, 0x60(r30)
	stfs f0, 0x5c(r1)
	bl movePos
	lfs f1, 0x58(r30)
	lfs f2, 0x60(r30)
	lfs f3, 0x60(r1)
	lfs f4, 0x5c(r1)
	bl angleABf
	lfs f0, touch_wall_ct(r13)
	addi r4, r1, 0x8
	lfs f4, float_0_8041cdec(r2)
	addi r5, r1, 0xc
	fadds f2, f30, f0
	lfs f0, float_1000_8041cdf4(r2)
	fmr f6, f4
	lfs f1, 0x60(r1)
	stfs f0, 0x14(r1)
	addi r6, r1, 0x10
	lfs f3, 0x5c(r1)
	addi r7, r1, 0x14
	lfs f5, float_neg1_8041cdf8(r2)
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne @24
	lfs f28, float_neg2000_8041cdfc(r2)
	b @25
	@24:
	lfs f2, float_100_8041cde0(r2)
	lis r0, 0x4330
	lfs f1, 0xc(r1)
	lis r4, double_to_int_802f3f48@ha
	lfs f0, float_0p5_8041ce00(r2)
	stw r0, 0x70(r1)
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802f3f48@l(r4)
	fctiwz f0, f0
	stfd f0, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	fdivs f28, f0, f2
	bl hitGetAttr
	@25:
	lfs f1, 0x5c(r30)
	lfs f0, float_1_8041ce1c(r2)
	fsubs f1, f1, f28
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @22
	lfs f0, 0x60(r1)
	mr r3, r30
	li r4, 0x2
	stfs f0, 0x94(r30)
	stfs f28, 0x98(r30)
	lfs f0, 0x5c(r1)
	stfs f0, 0x9c(r30)
	bl partyChgMot
	b @23
	@22:
	lfs f1, float_10_8041cdd4(r2)
	mr r3, r30
	lfs f2, float_0_8041cdec(r2)
	bl partySearchGround
	mr. r29, r3
	beq @26
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @26
	lbz r0, 0x4c(r30)
	li r29, 0x0
	extsb. r0, r0
	bne @26
	lwz r0, 0x8(r30)
	oris r0, r0, 0x100
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x200
	stw r0, 0x0(r30)
	@26:
	cmplwi r29, 0x0
	stw r29, 0x138(r30)
	bne @27
	mr r3, r30
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r30)
	@27:
	lfs f0, 0xe4(r30)
	stfs f0, 0x5c(r30)
	b @28
	@16:
	li r0, 0x0
	stw r0, 0x24(r30)
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 10, 10
	beq @29
	rlwinm r0, r3, 0, 15, 13
	stw r0, 0x8(r30)
	@29:
	mr r3, r30
	li r4, 0x1
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x8c(r31)
	mr r3, r30
	lfs f2, 0x94(r31)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x8
	stw r0, 0x0(r30)
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x8(r30)
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 14, 12
	stw r0, 0x8(r30)
	@28:
	lwz r0, 0x134(r30)
	cmplwi r0, 0x0
	beq @23
	lwz r0, 0x0(r30)
	mr r3, r30
	li r4, 0x1
	oris r0, r0, 0x8
	stw r0, 0x0(r30)
	bl partyChgMoveMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	lfs f1, 0x60(r1)
	mr r3, r30
	lfs f2, 0x5c(r1)
	bl partySetDir
	lfs f0, float_50_8041cde8(r2)
	stfs f0, 0x40(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 14, 12
	stw r0, 0x8(r30)
	@23:
	psq_l f31, 0xc8(r1), 0, 0
	lfd f31, 0xc0(r1)
	psq_l f30, 0xb8(r1), 0, 0
	lfd f30, 0xb0(r1)
	psq_l f29, 0xa8(r1), 0, 0
	lfd f29, 0xa0(r1)
	psq_l f28, 0x98(r1), 0, 0
	lfd f28, 0x90(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	lwz r0, 0xd4(r1)
	lwz r29, 0x84(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm void party_set_behind_dir(PartyEntry* party, f32 dir) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x10(r1)
	psq_st f31, 0x18(r1), 0, 0
	stw r31, 0xc(r1)
	fmr f31, f1
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lfs f0, 0x114(r3)
	fadds f1, f31, f0
	bl revise360
	stfs f1, 0x54(r31)
	lwz r0, 0x8(r31)
	oris r0, r0, 0x10
	stw r0, 0x8(r31)
	psq_l f31, 0x18(r1), 0, 0
	lwz r0, 0x24(r1)
	lfd f31, 0x10(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void party_motion_homing_fly(PartyEntry* party) {
	nofralloc
	stwu r1, -0x130(r1)
	mflr r0
	stw r0, 0x134(r1)
	stfd f31, 0x120(r1)
	psq_st f31, 0x128(r1), 0, 0
	stfd f30, 0x110(r1)
	psq_st f30, 0x118(r1), 0, 0
	stfd f29, 0x100(r1)
	psq_st f29, 0x108(r1), 0, 0
	stfd f28, 0xf0(r1)
	psq_st f28, 0xf8(r1), 0, 0
	stfd f27, 0xe0(r1)
	psq_st f27, 0xe8(r1), 0, 0
	stfd f26, 0xd0(r1)
	psq_st f26, 0xd8(r1), 0, 0
	stfd f25, 0xc0(r1)
	psq_st f25, 0xc8(r1), 0, 0
	stmw r26, 0xa8(r1)
	mr r27, r3
	lis r4, vec3_802f3e40@ha
	lwz r30, 0x160(r3)
	addi r31, r4, vec3_802f3e40@l
	bl partyGetFootmarkId
	lwz r4, 0x8(r27)
	mr r29, r3
	rlwinm. r0, r4, 0, 30, 30
	beq @1
	rlwinm r3, r4, 0, 31, 29
	li r0, 0x0
	stw r3, 0x8(r27)
	lwz r3, 0x0(r27)
	rlwinm r3, r3, 0, 13, 11
	stw r3, 0x0(r27)
	stb r0, 0x4e(r27)
	@1:
	lha r0, 0x28(r27)
	cmpwi r0, 0x0
	beq @2
	lfs f31, float_28_8041cea4(r2)
	b @3
	@2:
	lfs f31, float_32_8041cea8(r2)
	@3:
	lwz r3, gp(r13)
	addi r4, r31, 0x188
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	lwz r3, gp(r13)
	addi r4, r31, 0x190
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	lwz r3, gp(r13)
	addi r4, r31, 0x198
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	@4:
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @5
	lbz r0, 0x32(r27)
	cmplwi r0, 0x0
	bne @6
	lfs f25, float_18_8041ce20(r2)
	b @7
	@6:
	lbz r0, 0x31(r27)
	extsb r0, r0
	cmpwi r0, 0x5
	bne @8
	lwz r0, 0x8(r27)
	rlwinm. r0, r0, 0, 10, 10
	beq @9
	lfs f25, float_8_8041ce24(r2)
	b @7
	@9:
	lfs f25, float_30_8041ce28(r2)
	b @7
	@8:
	cmpwi r0, 0x6
	bne @7
	lwz r0, 0x8(r27)
	rlwinm. r0, r0, 0, 10, 10
	beq @10
	lfs f25, float_8_8041ce24(r2)
	b @7
	@10:
	lfs f25, float_30_8041ce28(r2)
	@7:
	lwz r0, 0x8(r27)
	fmr f31, f25
	oris r0, r0, 0x2
	stw r0, 0x8(r27)
	@5:
	mr r3, r29
	bl partyGetTargetDistY
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @11
	lfs f30, float_50_8041cde8(r2)
	b @12
	@11:
	lfs f30, float_35_8041ceac(r2)
	@12:
	lwz r3, 0x8(r27)
	extrwi. r0, r3, 1, 14
	beq @13
	lbz r0, 0x32(r27)
	cmplwi r0, 0x0
	bne @14
	lfs f26, float_18_8041ce20(r2)
	b @15
	@14:
	lbz r0, 0x31(r27)
	extsb r0, r0
	cmpwi r0, 0x5
	bne @16
	rlwinm. r0, r3, 0, 10, 10
	beq @17
	lfs f26, float_8_8041ce24(r2)
	b @15
	@17:
	lfs f26, float_30_8041ce28(r2)
	b @15
	@16:
	cmpwi r0, 0x6
	bne @15
	rlwinm. r0, r3, 0, 10, 10
	beq @18
	lfs f26, float_8_8041ce24(r2)
	b @15
	@18:
	lfs f26, float_30_8041ce28(r2)
	@15:
	fmr f30, f26
	@13:
	mr r3, r27
	bl party_slit
	cmpwi r3, 0x0
	beq @19
	mr r3, r27
	bl party_roll
	cmpwi r3, 0x0
	beq @19
	lhz r0, 0x2e(r30)
	cmplwi r0, 0xe
	bne @20
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 12, 12
	bne @20
	mr r3, r27
	li r4, 0x0
	bl partyMoveBehindMario
	b @19
	@20:
	lwz r3, 0x160(r27)
	lha r0, 0x50(r3)
	cmpwi r0, 0x0
	beq @21
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0x180(r3)
	fcmpu cr0, f1, f0
	bne @21
	li r0, 0x0
	b @22
	@21:
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1f
	beq @23
	cmplwi r0, 0x20
	beq @23
	cmplwi r0, 0x10
	beq @23
	cmplwi r0, 0x11
	bne @24
	@23:
	li r0, 0x0
	b @22
	@24:
	li r0, 0x1
	@22:
	cmpwi r0, 0x0
	bne @25
	mr r3, r27
	li r4, 0x0
	bl partyChgMot
	b @19
	@25:
	mr r3, r27
	bl partyGetTargetMovespd2
	fmr f29, f1
	addi r3, r30, 0x8c
	addi r4, r27, 0x58
	bl PSVECDistance
	lfs f0, float_35_8041ceac(r2)
	fcmpo cr0, f1, f0
	bge @26
	lfs f29, float_1_8041ce1c(r2)
	b @27
	@26:
	lfs f0, float_50_8041cde8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @27
	lfs f29, float_3_8041ce0c(r2)
	@27:
	lwz r3, 0x160(r27)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 16, 16
	beq @28
	lfs f29, float_1_8041ce1c(r2)
	lfs f31, float_100_8041cde0(r2)
	@28:
	fmr f1, f29
	mr r3, r27
	bl unk_800c93d0
	lfs f28, 0x58(r27)
	mr r3, r29
	lfs f27, 0x5c(r27)
	lfs f26, 0x60(r27)
	bl partyGetFootmarkPtr
	lfs f0, 0x4(r3)
	lfs f1, float_5_8041ce18(r2)
	stfs f0, 0x34(r1)
	lwz r0, 0x4(r27)
	rlwinm. r0, r0, 0, 16, 16
	beq @29
	lfs f1, float_1_8041ce1c(r2)
	@29:
	lfs f0, 0x8(r3)
	addi r4, r1, 0x58
	fadds f0, f0, f1
	stfs f0, 0x30(r1)
	lfs f0, 0xc(r3)
	mr r3, r29
	stfs f0, 0x2c(r1)
	lwz r5, 0x58(r27)
	lwz r0, 0x5c(r27)
	stw r5, 0x58(r1)
	stw r0, 0x5c(r1)
	lwz r0, 0x60(r27)
	stw r0, 0x60(r1)
	bl partyGetTargetDist3D
	fcmpo cr0, f1, f31
	cror eq, gt, eq
	bne @30
	fmr f1, f29
	mr r3, r27
	bl unk_800c93d0
	@30:
	lfs f0, float_20_8041cdc0(r2)
	fcmpo cr0, f30, f0
	bge @31
	fmr f1, f29
	mr r3, r27
	bl unk_800c93d0
	@31:
	li r28, 0x0
	@32:
	fmr f1, f28
	lfs f3, 0x34(r1)
	fmr f2, f26
	lfs f4, 0x2c(r1)
	bl angleABf
	stfs f1, 0x3c(r1)
	fmr f1, f28
	fmr f2, f26
	lfs f3, 0x34(r1)
	lfs f4, 0x2c(r1)
	bl distABf
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 16, 16
	beq @33
	lfs f2, 0xf4(r27)
	lfs f0, 0x1b4(r30)
	fadds f0, f2, f0
	b @34
	@33:
	lfs f3, float_0p5_8041ce00(r2)
	lfs f2, 0xf4(r27)
	lfs f0, 0x104(r27)
	fmadds f0, f3, f2, f0
	@34:
	fcmpo cr0, f1, f0
	ble @35
	lwz r6, 0xc(r31)
	mr r3, r29
	lwz r5, 0x10(r31)
	addi r4, r1, 0x4c
	lwz r0, 0x14(r31)
	stw r6, 0x40(r1)
	stw r5, 0x44(r1)
	stw r0, 0x48(r1)
	stfs f28, 0x40(r1)
	stfs f27, 0x44(r1)
	lwz r6, 0x40(r1)
	stfs f26, 0x48(r1)
	lwz r5, 0x44(r1)
	lwz r0, 0x48(r1)
	stw r6, 0x4c(r1)
	stw r5, 0x50(r1)
	stw r0, 0x54(r1)
	bl partyGetTargetDist3D
	fmr f25, f1
	fcmpo cr0, f25, f31
	cror eq, gt, eq
	bne @36
	lwz r0, 0x8(r27)
	rlwinm. r0, r0, 0, 14, 14
	beq @37
	fsubs f1, f25, f30
	lfs f2, float_0p1_8041ce44(r2)
	lfs f0, float_4_8041ceb0(r2)
	fmuls f1, f2, f1
	fcmpo cr0, f1, f0
	ble @38
	fmr f1, f0
	@38:
	lfs f0, float_0p5_8041ce00(r2)
	fcmpo cr0, f1, f0
	bge @39
	lfs f1, float_0_8041cdec(r2)
	@39:
	lfs f0, 0x180(r30)
	mr r3, r27
	fadds f1, f0, f1
	bl unk_800c9398
	@37:
	li r28, 0x1
	b @40
	@36:
	addi r3, r1, 0x88
	bl marioGetSlitFloorPos
	cmpwi r3, 0x0
	beq @41
	lfs f1, float_1p5_8041ce98(r2)
	mr r3, r27
	bl unk_800c93d0
	mr r3, r29
	bl partyNextReadId
	addi r3, r1, 0x88
	bl marioGetSlitFloorPos
	cmpwi r3, 0x0
	beq @40
	lwz r0, 0x90(r1)
	fmr f1, f28
	lwz r3, 0x88(r1)
	fmr f2, f26
	stw r0, 0x84(r1)
	lwz r0, 0x8c(r1)
	lfs f25, 0x84(r1)
	stw r3, 0x7c(r1)
	fmr f4, f25
	stw r0, 0x80(r1)
	lfs f3, 0x7c(r1)
	bl distABf
	fmr f27, f1
	lfs f3, 0x7c(r1)
	fmr f1, f28
	fmr f2, f26
	fmr f4, f25
	bl angleABf
	lfs f0, float_5_8041ce18(r2)
	stfs f1, 0x3c(r1)
	fcmpo cr0, f27, f0
	cror eq, lt, eq
	bne @40
	mr r3, r27
	bl partyChgMotSlitFloor
	b @40
	@41:
	fcmpo cr0, f25, f30
	ble @42
	lwz r0, 0x8(r27)
	rlwinm. r0, r0, 0, 14, 14
	beq @43
	fsubs f1, f25, f30
	lfs f2, float_0p1_8041ce44(r2)
	lfs f0, float_4_8041ceb0(r2)
	fmuls f1, f2, f1
	fcmpo cr0, f1, f0
	ble @44
	fmr f1, f0
	@44:
	lfs f0, float_0p5_8041ce00(r2)
	fcmpo cr0, f1, f0
	bge @45
	lfs f1, float_0_8041cdec(r2)
	@45:
	lfs f0, 0x180(r30)
	mr r3, r27
	fadds f1, f0, f1
	bl unk_800c9398
	b @35
	@43:
	fsubs f1, f25, f30
	lfs f2, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f2
	cror eq, gt, eq
	bne @46
	lfs f0, float_20_8041cdc0(r2)
	fmr f1, f2
	fcmpo cr0, f30, f0
	bge @46
	fmr f1, f29
	@46:
	mr r3, r27
	bl unk_800c93d0
	b @40
	@42:
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0xa0(r27)
	fcmpu cr0, f1, f0
	bne @47
	lfs f0, 0xa8(r27)
	fcmpu cr0, f1, f0
	bne @47
	lwz r4, 0x160(r27)
	mr r3, r27
	lfs f1, 0x180(r4)
	bl unk_800c93d0
	b @35
	@47:
	lfs f1, float_0_8041cdec(r2)
	mr r3, r27
	bl unk_800c9398
	lfs f1, 0x58(r27)
	lfs f2, 0x60(r27)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl angleABf
	stfs f1, 0x100(r27)
	mr r3, r27
	li r4, 0x1
	bl partyChgPoseId
	@35:
	mr r3, r29
	bl partyGetFootmarkWriteId
	mr r26, r3
	mr r3, r29
	bl partyGetFootmarkReadId
	cmpw r3, r26
	bne @48
	lwz r4, 0x160(r27)
	mr r3, r27
	lfs f1, 0x180(r4)
	bl unk_800c93d0
	lwz r3, 0x160(r27)
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0x180(r3)
	fcmpu cr0, f1, f0
	beq @49
	lfs f0, 0xa0(r27)
	fcmpu cr0, f1, f0
	bne @49
	lfs f0, 0xa8(r27)
	fcmpu cr0, f1, f0
	beq @40
	@49:
	lfs f0, 0x100(r27)
	mr r3, r27
	lfs f1, float_0_8041cdec(r2)
	stfs f0, 0x3c(r1)
	bl unk_800c93d0
	lfs f0, float_0_8041cdec(r2)
	stfs f0, 0x11c(r27)
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 22, 22
	bne @50
	mr r3, r27
	li r4, 0x1
	bl partyChgPoseId
	@50:
	mr r3, r27
	li r4, 0x0
	bl partyChgMot
	b @40
	@48:
	mr r3, r29
	bl partyNextReadId
	mr r3, r29
	addi r4, r1, 0x34
	addi r5, r1, 0x30
	addi r6, r1, 0x2c
	bl partyGetReadId
	lwz r3, 0x0(r27)
	rlwinm. r0, r3, 0, 5, 5
	bne @32
	lfs f1, float_100_8041cde0(r2)
	rlwinm r0, r3, 0, 25, 23
	stw r0, 0x0(r27)
	mr r3, r27
	fmr f2, f1
	bl partySearchGround
	mr. r26, r3
	beq @51
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @51
	li r26, 0x0
	@51:
	cmplwi r26, 0x0
	stw r26, 0x138(r27)
	bne @52
	mr r3, r27
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r27)
	b @32
	@52:
	mr r3, r26
	bl hitGetAttr
	rlwinm. r0, r3, 0, 23, 23
	beq @53
	lwz r0, 0x0(r27)
	ori r0, r0, 0x80
	stw r0, 0x0(r27)
	b @54
	@53:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	@54:
	rlwinm. r0, r3, 0, 20, 20
	beq @32
	mr r3, r27
	li r4, 0x0
	bl partyChgMot
	@40:
	lfs f1, 0x104(r27)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @55
	mr r3, r27
	bl unk_800c8f24
	b @56
	@55:
	mr r3, r27
	li r4, 0x0
	bl partyChgMot
	@56:
	lbz r0, 0x4e(r27)
	extsb r0, r0
	cmpwi r0, 0xa
	ble @57
	lfs f1, 0x58(r27)
	lfs f2, 0x60(r27)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl angleABf
	stfs f1, 0x3c(r1)
	@57:
	cmpwi r28, 0x0
	beq @58
	lwz r28, 0x160(r27)
	mr r3, r27
	addi r4, r1, 0x70
	bl partyGetAppearPos3
	lfs f1, 0x58(r27)
	lfs f2, 0x60(r27)
	lfs f3, 0x70(r1)
	lfs f4, 0x78(r1)
	bl angleABf
	stfs f1, 0x3c(r1)
	mr r3, r27
	lfs f1, float_10_8041cdd4(r2)
	lfs f2, float_0_8041cdec(r2)
	bl partySearchGround
	lfs f0, 0xe4(r27)
	mr. r26, r3
	stfs f0, 0x74(r1)
	beq @59
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @59
	li r26, 0x0
	@59:
	cmplwi r26, 0x0
	beq @60
	lfs f0, 0x74(r1)
	stfs f0, 0x5c(r27)
	b @58
	@60:
	lwz r0, 0x4(r27)
	lfs f2, float_5_8041ce18(r2)
	rlwinm. r0, r0, 0, 16, 16
	beq @61
	lfs f2, float_1_8041ce1c(r2)
	@61:
	lfs f0, 0x90(r28)
	lfs f1, 0x5c(r27)
	fadds f0, f0, f2
	lfs f2, float_0p05_8041cea0(r2)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x5c(r27)
	@58:
	lfs f0, 0x3c(r1)
	mr r3, r27
	addi r4, r1, 0x3c
	addi r5, r1, 0x38
	stfs f0, 0x100(r27)
	lwz r6, 0x58(r27)
	lwz r0, 0x5c(r27)
	stw r6, 0x88(r1)
	stw r0, 0x8c(r1)
	lwz r0, 0x60(r27)
	stw r0, 0x90(r1)
	bl partyGetMoveDirSpd
	lfs f1, 0x38(r1)
	mr r3, r27
	lfs f2, 0x3c(r1)
	addi r4, r1, 0x88
	bl partySearchFrontWall
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 7, 7
	beq @62
	li r3, 0x0
	@62:
	cmplwi r3, 0x0
	bne @63
	lwz r0, 0x8(r27)
	rlwinm. r0, r0, 0, 10, 10
	bne @64
	lfs f1, 0x100(r27)
	mr r3, r27
	addi r4, r1, 0x64
	bl getFrontFloor
	b @65
	@64:
	lfs f1, float_270_8041ce34(r2)
	lfs f0, 0x198(r30)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r27)
	mr r3, r27
	addi r4, r1, 0x64
	bl partyGetAppearPos4
	@65:
	lfs f1, 0x68(r1)
	lfs f0, 0x90(r30)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @66
	lwz r0, 0x4(r27)
	lfs f0, float_5_8041ce18(r2)
	rlwinm. r0, r0, 0, 16, 16
	beq @67
	lfs f0, float_1_8041ce1c(r2)
	@67:
	fadds f0, f1, f0
	lfs f1, 0x5c(r27)
	lfs f2, float_0p05_8041cea0(r2)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x5c(r27)
	@66:
	li r0, 0x0
	lfs f0, float_0_8041cdec(r2)
	stb r0, 0x4e(r27)
	lfs f1, 0x104(r27)
	fcmpu cr0, f1, f0
	beq @68
	lfs f0, 0x58(r27)
	addi r4, r1, 0x90
	addi r3, r1, 0x88
	stfs f0, 0x88(r1)
	lfs f0, 0x60(r27)
	stfs f0, 0x90(r1)
	lfs f2, 0x100(r27)
	bl movePos
	b @68
	@63:
	stw r3, 0x12c(r27)
	lfs f0, float_0_8041cdec(r2)
	lfs f1, 0x104(r27)
	fcmpu cr0, f1, f0
	beq @68
	stw r3, 0x134(r27)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 18, 18
	beq @69
	lbz r0, 0x37(r27)
	cmplwi r0, 0x1
	beq @70
	lwz r3, 0x160(r27)
	lwz r0, 0xc(r3)
	clrrwi. r0, r0, 31
	bne @68
	lwz r3, 0x8(r27)
	li r0, 0x1
	ori r3, r3, 0x1
	stw r3, 0x8(r27)
	stb r0, 0x37(r27)
	b @68
	@70:
	lfs f1, 0x104(r27)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @68
	lfs f0, 0x58(r27)
	addi r4, r1, 0x90
	addi r3, r1, 0x88
	stfs f0, 0x88(r1)
	lfs f0, 0x60(r27)
	stfs f0, 0x90(r1)
	lfs f2, 0x100(r27)
	bl movePos
	b @68
	@69:
	lfs f0, 0x58(r27)
	addi r3, r1, 0x28
	lfs f2, 0x3c(r1)
	addi r4, r1, 0x24
	stfs f0, 0x28(r1)
	lfs f25, 0x5c(r27)
	lfs f0, 0x60(r27)
	stfs f0, 0x24(r1)
	lfs f1, 0xf4(r27)
	bl movePos
	lfs f0, touch_wall_ct(r13)
	addi r4, r1, 0x8
	lfs f4, float_0_8041cdec(r2)
	addi r5, r1, 0xc
	fadds f2, f25, f0
	lfs f0, float_1000_8041cdf4(r2)
	fmr f6, f4
	lfs f1, 0x28(r1)
	stfs f0, 0x14(r1)
	addi r6, r1, 0x10
	lfs f3, 0x24(r1)
	addi r7, r1, 0x14
	lfs f5, float_neg1_8041cdf8(r2)
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne @71
	lfs f25, float_neg2000_8041cdfc(r2)
	b @72
	@71:
	lfs f2, float_100_8041cde0(r2)
	lis r0, 0x4330
	lfs f1, 0xc(r1)
	lfs f0, float_0p5_8041ce00(r2)
	stw r0, 0xa0(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x108(r31)
	fctiwz f0, f0
	stfd f0, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f25, f0, f2
	bl hitGetAttr
	@72:
	lfs f0, float_neg2000_8041cdfc(r2)
	fcmpo cr0, f25, f0
	ble @73
	lfs f0, 0xf0(r27)
	lfs f1, 0x5c(r27)
	fadds f0, f25, f0
	lfs f2, float_0p05_8041cea0(r2)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x5c(r27)
	b @68
	@73:
	lbz r4, 0x4e(r27)
	mr r3, r29
	addi r0, r4, 0x1
	stb r0, 0x4e(r27)
	lfs f1, 0x5c(r27)
	bl unk_800c9f48
	lfs f0, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @68
	lfs f3, 0x90(r30)
	lfs f2, 0x5c(r27)
	lfs f0, float_10_8041cdd4(r2)
	fsubs f1, f3, f2
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @68
	fadds f0, f0, f3
	lfs f1, float_0p1_8041ce44(r2)
	fsubs f0, f0, f2
	fmadds f0, f1, f0, f2
	stfs f0, 0x5c(r27)
	lfs f0, 0x88(r1)
	stfs f0, 0x58(r27)
	lfs f0, 0x90(r1)
	stfs f0, 0x60(r27)
	b @19
	@68:
	lfs f0, 0x88(r1)
	mr r3, r27
	lfs f1, float_10_8041cdd4(r2)
	stfs f0, 0x58(r27)
	fmr f2, f1
	lfs f0, 0x90(r1)
	stfs f0, 0x60(r27)
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	bl partySearchGround
	cmplwi r3, 0x0
	beq @74
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @75
	mr r3, r27
	li r4, 0xd
	bl partyChgRunMode
	b @19
	@75:
	rlwinm. r0, r3, 0, 23, 23
	beq @76
	lwz r0, 0x0(r27)
	ori r0, r0, 0x80
	stw r0, 0x0(r27)
	b @74
	@76:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	@74:
	mr r3, r27
	bl party_force_reset_outofscreen
	@19:
	psq_l f31, 0x128(r1), 0, 0
	lfd f31, 0x120(r1)
	psq_l f30, 0x118(r1), 0, 0
	lfd f30, 0x110(r1)
	psq_l f29, 0x108(r1), 0, 0
	lfd f29, 0x100(r1)
	psq_l f28, 0xf8(r1), 0, 0
	lfd f28, 0xf0(r1)
	psq_l f27, 0xe8(r1), 0, 0
	lfd f27, 0xe0(r1)
	psq_l f26, 0xd8(r1), 0, 0
	lfd f26, 0xd0(r1)
	psq_l f25, 0xc8(r1), 0, 0
	lfd f25, 0xc0(r1)
	lmw r26, 0xa8(r1)
	lwz r0, 0x134(r1)
	mtlr r0
	addi r1, r1, 0x130
	blr
}

asm void party_motion_homing_walk(PartyEntry* party) {
	nofralloc
	stwu r1, -0x220(r1)
	mflr r0
	stw r0, 0x224(r1)
	stfd f31, 0x210(r1)
	psq_st f31, 0x218(r1), 0, 0
	stfd f30, 0x200(r1)
	psq_st f30, 0x208(r1), 0, 0
	stfd f29, 0x1f0(r1)
	psq_st f29, 0x1f8(r1), 0, 0
	stfd f28, 0x1e0(r1)
	psq_st f28, 0x1e8(r1), 0, 0
	stfd f27, 0x1d0(r1)
	psq_st f27, 0x1d8(r1), 0, 0
	stfd f26, 0x1c0(r1)
	psq_st f26, 0x1c8(r1), 0, 0
	stfd f25, 0x1b0(r1)
	psq_st f25, 0x1b8(r1), 0, 0
	stfd f24, 0x1a0(r1)
	psq_st f24, 0x1a8(r1), 0, 0
	stmw r25, 0x184(r1)
	lis r4, vec3_802f3e40@ha
	mr r31, r3
	addi r29, r4, vec3_802f3e40@l
	li r28, 0x0
	bl partyGetFootmarkId
	lwz r4, 0x8(r31)
	mr r27, r3
	lwz r26, 0x160(r31)
	rlwinm. r0, r4, 0, 30, 30
	beq @1
	rlwinm r0, r4, 0, 31, 29
	stw r0, 0x8(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 13, 11
	stw r0, 0x0(r31)
	@1:
	lha r0, 0x28(r31)
	cmpwi r0, 0x0
	beq @2
	lfs f31, float_28_8041cea4(r2)
	b @3
	@2:
	lfs f31, float_37p5_8041ceb4(r2)
	@3:
	lwz r3, gp(r13)
	addi r4, r29, 0x188
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	lwz r3, gp(r13)
	addi r4, r29, 0x190
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	lwz r3, gp(r13)
	addi r4, r29, 0x198
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	@4:
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @5
	lbz r0, 0x32(r31)
	cmplwi r0, 0x0
	bne @6
	lfs f24, float_18_8041ce20(r2)
	b @7
	@6:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x5
	bne @8
	lwz r0, 0x8(r31)
	rlwinm. r0, r0, 0, 10, 10
	beq @9
	lfs f24, float_8_8041ce24(r2)
	b @7
	@9:
	lfs f24, float_30_8041ce28(r2)
	b @7
	@8:
	cmpwi r0, 0x6
	bne @7
	lwz r0, 0x8(r31)
	rlwinm. r0, r0, 0, 10, 10
	beq @10
	lfs f24, float_8_8041ce24(r2)
	b @7
	@10:
	lfs f24, float_30_8041ce28(r2)
	@7:
	lwz r0, 0x8(r31)
	fmr f31, f24
	oris r0, r0, 0x2
	stw r0, 0x8(r31)
	@5:
	mr r3, r27
	bl partyGetTargetDistY
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @11
	lfs f30, float_50_8041cde8(r2)
	b @12
	@11:
	lfs f30, float_35_8041ceac(r2)
	@12:
	lbz r0, 0x3c(r26)
	cmpwi r0, 0x2
	bne @13
	lfs f30, float_70_8041ceb8(r2)
	@13:
	lwz r3, 0x8(r31)
	extrwi. r0, r3, 1, 14
	beq @14
	lbz r0, 0x32(r31)
	cmplwi r0, 0x0
	bne @15
	lfs f25, float_18_8041ce20(r2)
	b @16
	@15:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x5
	bne @17
	rlwinm. r0, r3, 0, 10, 10
	beq @18
	lfs f25, float_8_8041ce24(r2)
	b @16
	@18:
	lfs f25, float_30_8041ce28(r2)
	b @16
	@17:
	cmpwi r0, 0x6
	bne @16
	rlwinm. r0, r3, 0, 10, 10
	beq @19
	lfs f25, float_8_8041ce24(r2)
	b @16
	@19:
	lfs f25, float_30_8041ce28(r2)
	@16:
	fmr f30, f25
	@14:
	mr r3, r31
	bl party_slit
	cmpwi r3, 0x0
	beq @20
	mr r3, r31
	bl party_roll
	cmpwi r3, 0x0
	beq @20
	lhz r0, 0x2e(r26)
	cmplwi r0, 0xe
	bne @21
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 12, 12
	bne @21
	mr r3, r31
	li r4, 0x0
	bl partyMoveBehindMario
	b @20
	@21:
	lwz r3, 0x160(r31)
	lha r0, 0x50(r3)
	cmpwi r0, 0x0
	beq @22
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0x180(r3)
	fcmpu cr0, f1, f0
	bne @22
	li r0, 0x0
	b @23
	@22:
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1f
	beq @24
	cmplwi r0, 0x20
	beq @24
	cmplwi r0, 0x10
	beq @24
	cmplwi r0, 0x11
	bne @25
	@24:
	li r0, 0x0
	b @23
	@25:
	li r0, 0x1
	@23:
	cmpwi r0, 0x0
	bne @26
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	b @20
	@26:
	mr r3, r31
	bl partyGetTargetMovespd2
	lwz r0, 0x0(r31)
	fmr f29, f1
	rlwinm. r0, r0, 0, 28, 28
	bne @27
	addi r3, r26, 0x8c
	addi r4, r31, 0x58
	bl PSVECDistance
	lfs f0, float_35_8041ceac(r2)
	fcmpo cr0, f1, f0
	bge @28
	lfs f29, float_1_8041ce1c(r2)
	b @29
	@28:
	lfs f0, float_50_8041cde8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @29
	lfs f29, float_3_8041ce0c(r2)
	@29:
	lwz r3, 0x160(r31)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 16, 16
	beq @30
	lfs f29, float_1_8041ce1c(r2)
	lfs f31, float_100_8041cde0(r2)
	@30:
	fmr f1, f29
	mr r3, r31
	bl unk_800c93d0
	b @31
	@27:
	bl marioGetPartyId
	bl partyGetPtr
	mr. r25, r3
	beq @31
	lwz r4, 0x58(r25)
	lwz r0, 0x5c(r25)
	stw r4, 0xa0(r1)
	stw r0, 0xa4(r1)
	lwz r0, 0x60(r25)
	stw r0, 0xa8(r1)
	bl nokonokoGetStatus
	cmpwi r3, 0x3
	beq @32
	addi r3, r26, 0x8c
	addi r4, r25, 0x58
	bl PSVECDistance
	lfs f0, float_150_8041cebc(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @33
	@32:
	addi r3, r26, 0x8c
	addi r4, r31, 0x58
	bl PSVECDistance
	lfs f0, float_35_8041ceac(r2)
	fcmpo cr0, f1, f0
	bge @34
	lfs f29, float_1_8041ce1c(r2)
	b @35
	@34:
	lfs f0, float_50_8041cde8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @35
	lfs f29, float_3_8041ce0c(r2)
	@35:
	lwz r3, 0x160(r31)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 16, 16
	beq @36
	lfs f29, float_1_8041ce1c(r2)
	@36:
	fmr f1, f29
	mr r3, r31
	bl unk_800c93d0
	b @31
	@33:
	addi r3, r25, 0x58
	addi r4, r31, 0x58
	bl PSVECDistance
	lfs f0, float_35_8041ceac(r2)
	fcmpo cr0, f1, f0
	bge @37
	lfs f29, float_1_8041ce1c(r2)
	b @38
	@37:
	lfs f0, float_50_8041cde8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @38
	lfs f29, float_3_8041ce0c(r2)
	@38:
	lwz r3, 0x160(r31)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 16, 16
	beq @39
	lfs f29, float_1_8041ce1c(r2)
	@39:
	fmr f1, f29
	mr r3, r31
	bl unk_800c93d0
	@31:
	lfs f28, 0x58(r31)
	li r25, 0x0
	lfs f27, 0x5c(r31)
	lfs f26, 0x60(r31)
	lfs f24, float_40_8041cdf0(r2)
	lfs f25, float_20_8041cdc0(r2)
	@40:
	mr r3, r27
	bl partyGetFootmarkPtr
	mr r30, r3
	fmr f1, f28
	lwz r3, 0x4(r3)
	fmr f2, f26
	lwz r0, 0x8(r30)
	stw r3, 0x94(r1)
	stw r0, 0x98(r1)
	lfs f3, 0x94(r1)
	lwz r0, 0xc(r30)
	stw r0, 0x9c(r1)
	lfs f4, 0x9c(r1)
	bl angleABf
	stfs f1, 0x44(r1)
	frsp f1, f1
	addi r3, r1, 0x18
	addi r4, r1, 0x1c
	bl sincosf
	stfs f24, 0x168(r1)
	addi r3, r1, 0x12c
	lfs f2, 0x18(r1)
	li r4, 0x0
	lfs f0, 0x58(r31)
	lfs f1, 0x1c(r1)
	fmadds f0, f25, f2, f0
	lwz r6, 0x90(r29)
	lwz r5, 0x94(r29)
	lwz r0, 0x98(r29)
	stfs f0, 0x138(r1)
	lfs f0, 0x60(r31)
	fmadds f0, f25, f1, f0
	stfs f0, 0x140(r1)
	lfs f0, 0x5c(r31)
	fadds f0, f25, f0
	stw r6, 0x144(r1)
	stw r5, 0x148(r1)
	stfs f0, 0x13c(r1)
	stw r0, 0x14c(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @41
	bl hitGetAttr
	b @42
	@41:
	li r3, 0x0
	@42:
	rlwinm. r0, r3, 0, 20, 20
	beq @43
	mr r3, r27
	bl partyNextReadId
	mr r3, r27
	addi r4, r1, 0x94
	bl partyGetReadId2
	addi r25, r25, 0x1
	cmpwi r25, 0xa
	ble @40
	bl marioGetPtr
	lwz r4, 0x8c(r3)
	lwz r0, 0x90(r3)
	stw r4, 0x94(r1)
	stw r0, 0x98(r1)
	lwz r0, 0x94(r3)
	stw r0, 0x9c(r1)
	@43:
	lwz r5, 0x58(r31)
	mr r3, r27
	lwz r0, 0x5c(r31)
	addi r4, r1, 0x70
	stw r5, 0x70(r1)
	stw r0, 0x74(r1)
	lwz r0, 0x60(r31)
	stw r0, 0x78(r1)
	bl partyGetTargetDist3D
	fcmpo cr0, f1, f31
	cror eq, gt, eq
	bne @44
	fmr f1, f29
	mr r3, r31
	bl unk_800c93d0
	@44:
	lfs f0, float_20_8041cdc0(r2)
	fcmpo cr0, f30, f0
	bge @45
	fmr f1, f29
	mr r3, r31
	bl unk_800c93d0
	@45:
	fmr f1, f28
	lfs f3, 0x94(r1)
	fmr f2, f26
	lfs f4, 0x9c(r1)
	bl distABf
	fmr f25, f1
	lfs f3, 0x94(r1)
	fmr f1, f28
	lfs f4, 0x9c(r1)
	fmr f2, f26
	bl angleABf
	stfs f1, 0x44(r1)
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 16, 16
	beq @46
	lfs f1, 0xf4(r31)
	lfs f0, 0x1b4(r26)
	fadds f0, f1, f0
	b @47
	@46:
	lfs f2, float_0p5_8041ce00(r2)
	lfs f1, 0xf4(r31)
	lfs f0, 0x104(r31)
	fmadds f0, f2, f1, f0
	@47:
	fcmpo cr0, f25, f0
	ble @48
	lwz r6, 0x0(r29)
	mr r3, r27
	lwz r5, 0x4(r29)
	addi r4, r1, 0x64
	lwz r0, 0x8(r29)
	stw r6, 0x58(r1)
	stw r5, 0x5c(r1)
	stw r0, 0x60(r1)
	stfs f28, 0x58(r1)
	stfs f27, 0x5c(r1)
	lwz r6, 0x58(r1)
	stfs f26, 0x60(r1)
	lwz r5, 0x5c(r1)
	lwz r0, 0x60(r1)
	stw r6, 0x64(r1)
	stw r5, 0x68(r1)
	stw r0, 0x6c(r1)
	bl partyGetTargetDist3D
	fmr f25, f1
	fcmpo cr0, f25, f31
	cror eq, gt, eq
	bne @49
	lwz r0, 0x8(r31)
	rlwinm. r0, r0, 0, 14, 14
	beq @50
	fsubs f1, f25, f30
	lfs f2, float_0p1_8041ce44(r2)
	lfs f0, float_4_8041ceb0(r2)
	fmuls f1, f2, f1
	fcmpo cr0, f1, f0
	ble @51
	fmr f1, f0
	@51:
	lfs f0, float_0p5_8041ce00(r2)
	fcmpo cr0, f1, f0
	bge @52
	lfs f1, float_0_8041cdec(r2)
	@52:
	lfs f0, 0x180(r26)
	mr r3, r31
	fadds f1, f0, f1
	bl unk_800c9398
	b @50
	@49:
	addi r3, r1, 0xa0
	bl marioGetSlitFloorPos
	cmpwi r3, 0x0
	beq @53
	lfs f1, float_1p5_8041ce98(r2)
	mr r3, r31
	bl unk_800c93d0
	mr r3, r27
	bl partyNextReadId
	addi r3, r1, 0xa0
	bl marioGetSlitFloorPos
	cmpwi r3, 0x0
	beq @50
	lwz r3, 0xa0(r1)
	fmr f1, f28
	lwz r0, 0xa8(r1)
	fmr f2, f26
	stw r3, 0x94(r1)
	lwz r3, 0xa4(r1)
	stw r0, 0x9c(r1)
	lfs f3, 0x94(r1)
	stw r3, 0x98(r1)
	lfs f4, 0x9c(r1)
	bl distABf
	fmr f27, f1
	lfs f3, 0x94(r1)
	fmr f1, f28
	lfs f4, 0x9c(r1)
	fmr f2, f26
	bl angleABf
	lfs f0, float_5_8041ce18(r2)
	stfs f1, 0x44(r1)
	fcmpo cr0, f27, f0
	cror eq, lt, eq
	bne @50
	mr r3, r31
	bl partyChgMotSlitFloor
	b @50
	@53:
	fcmpo cr0, f25, f30
	ble @54
	lwz r0, 0x8(r31)
	rlwinm. r0, r0, 0, 14, 14
	beq @55
	fsubs f1, f25, f30
	lfs f2, float_0p1_8041ce44(r2)
	lfs f0, float_4_8041ceb0(r2)
	fmuls f1, f2, f1
	fcmpo cr0, f1, f0
	ble @56
	fmr f1, f0
	@56:
	lfs f0, float_0p5_8041ce00(r2)
	fcmpo cr0, f1, f0
	bge @57
	lfs f1, float_0_8041cdec(r2)
	@57:
	lfs f0, 0x180(r26)
	mr r3, r31
	fadds f1, f0, f1
	bl unk_800c9398
	b @50
	@55:
	fsubs f1, f25, f30
	lfs f2, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f2
	cror eq, gt, eq
	bne @58
	lfs f0, float_20_8041cdc0(r2)
	fmr f1, f2
	fcmpo cr0, f30, f0
	bge @58
	fmr f1, f29
	@58:
	mr r3, r31
	bl unk_800c93d0
	b @50
	@54:
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0xa0(r31)
	fcmpu cr0, f1, f0
	bne @59
	lfs f0, 0xa8(r31)
	fcmpu cr0, f1, f0
	bne @59
	lwz r4, 0x160(r31)
	mr r3, r31
	lfs f1, 0x180(r4)
	bl unk_800c93d0
	b @48
	@59:
	lfs f1, float_0_8041cdec(r2)
	mr r3, r31
	bl unk_800c9398
	lfs f1, 0x58(r31)
	lfs f2, 0x60(r31)
	lfs f3, 0x8c(r26)
	lfs f4, 0x94(r26)
	bl angleABf
	stfs f1, 0x100(r31)
	mr r3, r31
	li r4, 0x1
	bl partyChgPoseId
	@48:
	mr r3, r27
	bl partyGetFootmarkWriteId
	mr r25, r3
	mr r3, r27
	bl partyGetFootmarkReadId
	cmpw r3, r25
	bne @60
	lwz r4, 0x160(r31)
	mr r3, r31
	lfs f1, 0x180(r4)
	bl unk_800c93d0
	lwz r3, 0x160(r31)
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0x180(r3)
	fcmpu cr0, f1, f0
	beq @61
	lfs f0, 0xa0(r31)
	fcmpu cr0, f1, f0
	bne @61
	lfs f0, 0xa8(r31)
	fcmpu cr0, f1, f0
	beq @50
	@61:
	lfs f0, 0x100(r31)
	mr r3, r31
	lfs f1, float_0_8041cdec(r2)
	stfs f0, 0x44(r1)
	bl unk_800c93d0
	lfs f0, float_0_8041cdec(r2)
	stfs f0, 0x11c(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	bne @62
	mr r3, r31
	li r4, 0x1
	bl partyChgPoseId
	@62:
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	b @50
	@60:
	mr r3, r27
	bl partyNextReadId
	mr r3, r27
	addi r4, r1, 0x94
	bl partyGetReadId2
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 5, 5
	bne @63
	rlwinm r0, r3, 0, 25, 23
	lfs f1, float_10_8041cdd4(r2)
	stw r0, 0x0(r31)
	mr r3, r31
	lfs f2, float_0_8041cdec(r2)
	bl partySearchGround
	mr. r28, r3
	beq @64
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @64
	lbz r0, 0x4c(r31)
	li r28, 0x0
	extsb. r0, r0
	bne @64
	lwz r0, 0x8(r31)
	oris r0, r0, 0x100
	stw r0, 0x8(r31)
	lwz r0, 0x0(r31)
	oris r0, r0, 0x200
	stw r0, 0x0(r31)
	@64:
	cmplwi r28, 0x0
	stw r28, 0x138(r31)
	bne @65
	mr r3, r31
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r31)
	b @63
	@65:
	mr r3, r28
	bl hitGetAttr
	rlwinm. r0, r3, 0, 23, 23
	beq @66
	lwz r0, 0x0(r31)
	ori r0, r0, 0x80
	stw r0, 0x0(r31)
	b @67
	@66:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r31)
	@67:
	rlwinm. r0, r3, 0, 20, 20
	beq @63
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	b @50
	@63:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @68
	lbz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq @68
	lfs f1, 0x110(r31)
	bl toMovedir
	fmr f24, f1
	mr r3, r27
	addi r4, r1, 0x38
	addi r5, r1, 0x34
	addi r6, r1, 0x30
	bl partyGetReadId
	mr r3, r27
	addi r4, r1, 0x88
	bl L_getTargetPos
	lfs f1, 0x8c(r1)
	lfs f0, 0x34(r1)
	fcmpo cr0, f1, f0
	bge @69
	stfs f1, 0x34(r1)
	@69:
	lfs f0, 0x38(r1)
	fmr f1, f24
	addi r3, r1, 0x10
	addi r4, r1, 0x14
	stfs f0, 0x94(r31)
	lfs f0, 0x30(r1)
	stfs f0, 0x9c(r31)
	lfs f0, 0x34(r1)
	stfs f0, 0x98(r31)
	lwz r6, 0x94(r31)
	lwz r5, 0x98(r31)
	lwz r0, 0x9c(r31)
	stw r6, 0x4c(r1)
	lfs f24, touch_wall_ct(r13)
	stw r5, 0x50(r1)
	stw r0, 0x54(r1)
	bl sincosf
	lwz r6, 0x4c(r1)
	addi r3, r1, 0xec
	lwz r5, 0x50(r1)
	li r4, 0x0
	lwz r0, 0x54(r1)
	stw r6, 0xf8(r1)
	lfs f2, 0x10(r1)
	stw r5, 0xfc(r1)
	lfs f5, float_40_8041cdf0(r2)
	stw r0, 0x100(r1)
	lfs f0, 0xf8(r1)
	lfs f1, 0xfc(r1)
	fmadds f4, f2, f5, f0
	lfs f0, float_1000_8041cdf4(r2)
	fadds f1, f1, f24
	lwz r6, 0x84(r29)
	lwz r5, 0x88(r29)
	lwz r0, 0x8c(r29)
	lfs f3, 0x14(r1)
	lfs f2, 0x100(r1)
	stfs f4, 0xf8(r1)
	fmadds f2, f3, f5, f2
	stfs f1, 0xfc(r1)
	stfs f2, 0x100(r1)
	stfs f0, 0x128(r1)
	stw r6, 0x104(r1)
	stw r5, 0x108(r1)
	stw r0, 0x10c(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @70
	lfs f1, 0x114(r1)
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @71
	lfs f0, float_0p5_8041ce00(r2)
	b @72
	@71:
	lfs f0, float_neg0p5_8041ce04(r2)
	@72:
	lfs f2, float_1000_8041cdf4(r2)
	lis r0, 0x4330
	stw r0, 0x178(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x108(r29)
	fctiwz f0, f0
	stfd f0, 0x170(r1)
	lwz r0, 0x174(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x17c(r1)
	lfd f0, 0x178(r1)
	fsubs f0, f0, f1
	fdivs f24, f0, f2
	bl hitGetAttr
	b @73
	@70:
	lfs f24, float_neg2000_8041cdfc(r2)
	@73:
	lfs f0, 0x5c(r31)
	fcmpo cr0, f24, f0
	ble @74
	lfs f1, 0x110(r31)
	mr r3, r31
	bl partyToMovedir
	stfs f1, 0x44(r1)
	frsp f1, f1
	addi r3, r1, 0x40
	addi r4, r1, 0x3c
	bl sincosf
	lfs f0, 0x40(r1)
	lfs f1, float_40_8041cdf0(r2)
	fmuls f0, f0, f1
	stfs f0, 0x94(r31)
	lfs f0, 0x3c(r1)
	fmuls f0, f0, f1
	stfs f0, 0x9c(r31)
	stfs f24, 0x98(r31)
	@74:
	mr r3, r31
	li r4, 0x2
	bl partyChgMot
	b @50
	@68:
	mr r3, r28
	bl unk_800c8dd0
	cmpwi r3, 0x0
	beq @75
	mr r3, r31
	mr r4, r28
	addi r5, r31, 0x94
	bl partyGetAppearPos5
	lwz r0, 0x8(r31)
	mr r3, r31
	li r4, 0x2
	oris r0, r0, 0x40
	stw r0, 0x8(r31)
	bl partyChgMot
	b @50
	@75:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @45
	lbz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 29, 29
	beq @45
	fmr f1, f28
	lfs f3, 0x94(r1)
	fmr f2, f26
	lfs f4, 0x9c(r1)
	bl distABf
	lfs f0, float_5_8041ce18(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @50
	mr r3, r31
	bl partyChgMotSlitFloor
	@50:
	lfs f1, 0x104(r31)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @76
	mr r3, r31
	bl unk_800c8f24
	b @77
	@76:
	lbz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 29, 29
	bne @77
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	@77:
	lfs f0, 0x44(r1)
	mr r3, r31
	addi r4, r1, 0x44
	addi r5, r1, 0x48
	stfs f0, 0x100(r31)
	lwz r6, 0x58(r31)
	lwz r0, 0x5c(r31)
	stw r6, 0xa0(r1)
	stw r0, 0xa4(r1)
	lwz r0, 0x60(r31)
	stw r0, 0xa8(r1)
	bl partyGetMoveDirSpd
	lfs f1, 0x48(r1)
	mr r3, r31
	lfs f2, 0x44(r1)
	addi r4, r1, 0xa0
	bl partySearchFrontWall
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq @78
	li r3, 0x0
	@78:
	cmplwi r3, 0x0
	bne @79
	li r0, 0x0
	stb r0, 0x4d(r31)
	lwz r0, 0x8(r31)
	rlwinm. r0, r0, 0, 10, 10
	bne @80
	lfs f1, 0x100(r31)
	mr r3, r31
	addi r4, r1, 0x94
	bl getFrontFloor
	b @81
	@80:
	lfs f1, float_270_8041ce34(r2)
	lfs f0, 0x198(r26)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x54(r31)
	mr r3, r31
	addi r4, r1, 0x94
	bl partyGetAppearPos4
	@81:
	lfs f2, 0x98(r1)
	lfs f1, 0x5c(r31)
	fcmpo cr0, f2, f1
	ble @82
	fsubs f3, f2, f1
	lfd f0, 0x1a0(r29)
	fcmpo cr0, f3, f0
	ble @83
	lfs f0, float_60_8041cec0(r2)
	fcmpo cr0, f3, f0
	bge @83
	lwz r5, 0x94(r1)
	mr r3, r31
	lwz r0, 0x98(r1)
	li r4, 0x2
	stw r5, 0x94(r31)
	stw r0, 0x98(r31)
	lwz r0, 0x9c(r1)
	stw r0, 0x9c(r31)
	bl partyChgMot
	b @20
	@83:
	fcmpo cr0, f2, f1
	ble @82
	stfs f2, 0x5c(r31)
	@82:
	lfs f1, 0x104(r31)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @84
	lfs f1, 0x100(r31)
	addi r3, r1, 0x8
	addi r4, r1, 0xc
	bl sincosf
	lfs f0, float_100_8041cde0(r2)
	addi r3, r1, 0xac
	lfs f3, 0x8(r1)
	li r4, 0x0
	stfs f0, 0xe8(r1)
	lfs f2, float_40_8041cdf0(r2)
	lfs f0, 0x58(r31)
	lfs f1, 0xc(r1)
	fmadds f0, f3, f2, f0
	lwz r6, 0x9c(r29)
	lwz r5, 0xa0(r29)
	lwz r0, 0xa4(r29)
	stfs f0, 0xb8(r1)
	lfs f0, 0x60(r31)
	fmadds f0, f1, f2, f0
	stfs f0, 0xc0(r1)
	lfs f0, 0x5c(r31)
	fadds f0, f0, f2
	stw r6, 0xc4(r1)
	stw r5, 0xc8(r1)
	stfs f0, 0xbc(r1)
	stw r0, 0xcc(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @85
	bl hitGetAttr
	b @86
	@85:
	li r3, 0x0
	@86:
	rlwinm. r0, r3, 0, 22, 22
	bne @84
	lfs f0, 0x58(r31)
	addi r4, r1, 0xa8
	addi r3, r1, 0xa0
	stfs f0, 0xa0(r1)
	lfs f0, 0x60(r31)
	stfs f0, 0xa8(r1)
	lfs f1, 0x104(r31)
	lfs f2, 0x100(r31)
	bl movePos
	b @84
	@79:
	stw r3, 0x12c(r31)
	lfs f0, float_0_8041cdec(r2)
	lfs f1, 0x104(r31)
	fcmpu cr0, f1, f0
	beq @84
	stw r3, 0x134(r31)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 18, 18
	beq @87
	lbz r0, 0x37(r31)
	cmplwi r0, 0x1
	beq @88
	lwz r3, 0x160(r31)
	lwz r0, 0xc(r3)
	clrrwi. r0, r0, 31
	bne @84
	lwz r3, 0x8(r31)
	li r0, 0x1
	ori r3, r3, 0x1
	stw r3, 0x8(r31)
	stb r0, 0x37(r31)
	b @84
	@88:
	lfs f1, 0x104(r31)
	lfs f0, float_0_8041cdec(r2)
	fcmpu cr0, f1, f0
	beq @84
	lfs f0, 0x58(r31)
	addi r4, r1, 0xa8
	addi r3, r1, 0xa0
	stfs f0, 0xa0(r1)
	lfs f0, 0x60(r31)
	stfs f0, 0xa8(r1)
	lfs f2, 0x100(r31)
	bl movePos
	b @84
	@87:
	lbz r3, 0x4d(r31)
	addi r0, r3, 0x1
	stb r0, 0x4d(r31)
	lbz r0, 0x4d(r31)
	extsb r0, r0
	cmpwi r0, 0x8
	ble @84
	li r0, 0x0
	mr r3, r27
	stb r0, 0x4d(r31)
	lfs f1, 0x5c(r31)
	bl unk_800c9f48
	lfs f0, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @89
	lfs f1, 0x100(r31)
	mr r3, r31
	addi r4, r1, 0x94
	bl getFrontFloor
	lfs f2, 0x98(r1)
	lfs f1, 0x5c(r31)
	lfs f0, float_5_8041ce18(r2)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	ble @90
	lwz r5, 0x94(r1)
	mr r3, r31
	lwz r0, 0x98(r1)
	li r4, 0x2
	stw r5, 0x94(r31)
	stw r0, 0x98(r31)
	lwz r0, 0x9c(r1)
	stw r0, 0x9c(r31)
	bl partyChgMot
	b @20
	@90:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 26, 27
	bne @84
	lfs f1, float_11_8041cec4(r2)
	mr r3, r31
	addi r4, r1, 0x2c
	addi r5, r1, 0x28
	addi r6, r1, 0x24
	bl partyChkFrontStep
	lfs f2, 0x2c(r1)
	lfs f1, 0x5c(r31)
	lfs f0, float_5_8041ce18(r2)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @84
	lfs f1, 0xe0(r31)
	lfs f0, float_30_8041ce28(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @84
	stfs f2, 0x120(r31)
	lfs f0, float_0_8041cdec(r2)
	lfs f1, 0x104(r31)
	fcmpu cr0, f1, f0
	beq @84
	mr r3, r31
	li r4, 0x6
	bl partyChgMot
	b @20
	@89:
	lfs f1, 0x58(r31)
	mr r3, r27
	lfs f2, 0x60(r31)
	bl partyGetTargetDir
	stfs f1, 0x44(r1)
	frsp f1, f1
	mr r3, r31
	addi r4, r1, 0x94
	bl getFrontFloor
	lfs f2, 0x98(r1)
	lfs f1, 0x5c(r31)
	lfs f0, float_100_8041cde0(r2)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	ble @91
	lwz r5, 0x94(r1)
	mr r3, r31
	lwz r0, 0x98(r1)
	li r4, 0x1
	stw r5, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r0, 0x9c(r1)
	stw r0, 0x60(r31)
	bl partyChgMot
	b @84
	@91:
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @92
	lwz r5, 0x94(r1)
	mr r3, r31
	lwz r0, 0x98(r1)
	li r4, 0x2
	stw r5, 0x94(r31)
	stw r0, 0x98(r31)
	lwz r0, 0x9c(r1)
	stw r0, 0x9c(r31)
	bl partyChgMot
	b @84
	@92:
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	@84:
	lfs f0, 0xa0(r1)
	mr r3, r31
	addi r4, r1, 0x7c
	addi r5, r1, 0x20
	stfs f0, 0x58(r31)
	lfs f0, 0xa8(r1)
	stfs f0, 0x60(r31)
	lfs f0, 0xf0(r31)
	stfs f0, 0x20(r1)
	lwz r6, 0x58(r31)
	lwz r0, 0x5c(r31)
	stw r6, 0x7c(r1)
	stw r0, 0x80(r1)
	lwz r0, 0x60(r31)
	stw r0, 0x84(r1)
	lfs f1, 0x10c(r31)
	bl partySearchHead
	cmplwi r3, 0x0
	beq @93
	stw r3, 0x140(r31)
	@93:
	lwz r0, 0x0(r31)
	mr r3, r31
	lfs f1, float_10_8041cdd4(r2)
	rlwinm r0, r0, 0, 25, 23
	fmr f2, f1
	stw r0, 0x0(r31)
	bl partySearchGround
	lfs f0, 0xe4(r31)
	mr. r25, r3
	stfs f0, 0xa4(r1)
	beq @94
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @95
	lbz r0, 0x4c(r31)
	li r25, 0x0
	extsb. r0, r0
	bne @94
	lwz r0, 0x8(r31)
	oris r0, r0, 0x100
	stw r0, 0x8(r31)
	lwz r0, 0x0(r31)
	oris r0, r0, 0x200
	stw r0, 0x0(r31)
	b @94
	@95:
	rlwinm. r0, r3, 0, 20, 20
	beq @94
	mr r3, r31
	li r4, 0xd
	bl partyChgRunMode
	b @20
	@94:
	cmplwi r25, 0x0
	stw r25, 0x138(r31)
	bne @96
	mr r3, r31
	li r4, 0x3
	bl partyChgMot
	lfs f0, float_neg1_8041cdf8(r2)
	stfs f0, 0x11c(r31)
	b @97
	@96:
	mr r3, r25
	bl hitGetAttr
	rlwinm. r0, r3, 0, 23, 23
	beq @98
	lwz r0, 0x0(r31)
	ori r0, r0, 0x80
	stw r0, 0x0(r31)
	b @99
	@98:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r31)
	@99:
	mr r3, r25
	bl hitGetAttr
	rlwinm. r0, r3, 0, 1, 1
	beq @97
	stw r25, 0x14c(r31)
	@97:
	lfs f0, 0xa4(r1)
	mr r3, r31
	stfs f0, 0x5c(r31)
	bl party_force_reset_outofscreen
	lwz r3, gp(r13)
	addi r4, r29, 0xd8
	lwz r25, 0x160(r31)
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @20
	lwz r3, 0x1e4(r25)
	cmplwi r3, 0x0
	beq @20
	lwz r0, 0x138(r31)
	cmplwi r0, 0x0
	beq @20
	bl hitGetName
	addi r4, r29, 0xe0
	bl strcmp
	cmpwi r3, 0x0
	bne @20
	lwz r3, 0x138(r31)
	bl hitGetName
	addi r4, r29, 0xf4
	bl strcmp
	cmpwi r3, 0x0
	bne @20
	lwz r3, 0xc0(r29)
	lwz r0, 0xc4(r29)
	stw r3, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r0, 0xc8(r29)
	stw r0, 0x60(r31)
	@20:
	psq_l f31, 0x218(r1), 0, 0
	lfd f31, 0x210(r1)
	psq_l f30, 0x208(r1), 0, 0
	lfd f30, 0x200(r1)
	psq_l f29, 0x1f8(r1), 0, 0
	lfd f29, 0x1f0(r1)
	psq_l f28, 0x1e8(r1), 0, 0
	lfd f28, 0x1e0(r1)
	psq_l f27, 0x1d8(r1), 0, 0
	lfd f27, 0x1d0(r1)
	psq_l f26, 0x1c8(r1), 0, 0
	lfd f26, 0x1c0(r1)
	psq_l f25, 0x1b8(r1), 0, 0
	lfd f25, 0x1b0(r1)
	psq_l f24, 0x1a8(r1), 0, 0
	lfd f24, 0x1a0(r1)
	lmw r25, 0x184(r1)
	lwz r0, 0x224(r1)
	mtlr r0
	addi r1, r1, 0x220
	blr
}

asm void unk_8014b824(PartyEntry* party) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r0, 0x0(r3)
	lwz r29, 0x160(r3)
	rlwinm. r0, r0, 0, 5, 5
	bne @1
	lfs f1, float_10_8041cdd4(r2)
	lfs f2, float_0_8041cdec(r2)
	bl partySearchGround
	mr. r30, r3
	beq @2
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @3
	mr r3, r31
	li r4, 0xd
	bl partyChgRunMode
	b @1
	@3:
	rlwinm. r0, r3, 0, 23, 23
	beq @4
	lwz r0, 0x0(r31)
	ori r0, r0, 0x80
	stw r0, 0x0(r31)
	b @2
	@4:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r31)
	@2:
	lwz r3, 0x160(r31)
	lha r0, 0x50(r3)
	cmpwi r0, 0x0
	beq @5
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0x180(r3)
	fcmpu cr0, f1, f0
	bne @5
	li r0, 0x0
	b @6
	@5:
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1f
	beq @7
	cmplwi r0, 0x20
	beq @7
	cmplwi r0, 0x10
	beq @7
	cmplwi r0, 0x11
	bne @8
	@7:
	li r0, 0x0
	b @6
	@8:
	li r0, 0x1
	@6:
	cmpwi r0, 0x0
	beq @9
	cmplwi r30, 0x0
	lfs f3, float_0p05_8041cea0(r2)
	beq @10
	lfs f0, 0x90(r29)
	lfs f1, 0xe4(r31)
	fcmpo cr0, f0, f1
	ble @11
	fmr f2, f0
	lfs f3, float_0p1_8041ce44(r2)
	b @12
	@11:
	fmr f2, f1
	lfs f3, float_0p1_8041ce44(r2)
	@12:
	lfs f0, 0x5c(r31)
	fcmpo cr0, f0, f1
	bge @13
	lfs f0, float_18p5_8041cec8(r2)
	lfs f3, float_0p1_8041ce44(r2)
	fadds f2, f0, f1
	b @13
	@10:
	lfs f2, 0x90(r29)
	@13:
	lwz r0, 0x4(r31)
	lfs f0, float_5_8041ce18(r2)
	rlwinm. r0, r0, 0, 16, 16
	beq @14
	lfs f0, float_1_8041ce1c(r2)
	@14:
	fadds f2, f2, f0
	lfs f1, 0x5c(r31)
	lfs f0, float_5_8041ce18(r2)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	bgt @15
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f0, f1
	ble @1
	@15:
	lfs f0, 0x5c(r31)
	fmadds f0, f1, f3, f0
	stfs f0, 0x5c(r31)
	b @1
	@9:
	cmplwi r30, 0x0
	beq @16
	lfs f2, 0x90(r29)
	lfs f1, 0xe4(r31)
	fcmpo cr0, f2, f1
	ble @17
	b @18
	@17:
	fmr f2, f1
	@18:
	lfs f0, 0x5c(r31)
	fcmpo cr0, f0, f1
	bge @19
	lfs f0, float_18p5_8041cec8(r2)
	fadds f2, f0, f1
	b @19
	@16:
	lfs f2, 0x5c(r31)
	@19:
	lwz r0, 0x4(r31)
	lfs f0, float_5_8041ce18(r2)
	rlwinm. r0, r0, 0, 16, 16
	beq @20
	lfs f0, float_1_8041ce1c(r2)
	@20:
	fadds f2, f2, f0
	lfs f1, 0x5c(r31)
	lfs f0, float_5_8041ce18(r2)
	fsubs f2, f2, f1
	fcmpo cr0, f2, f0
	bgt @21
	lfs f0, float_0_8041cdec(r2)
	fcmpo cr0, f0, f2
	ble @1
	@21:
	lfs f1, float_0p05_8041cea0(r2)
	lfs f0, 0x5c(r31)
	fmadds f0, f2, f1, f0
	stfs f0, 0x5c(r31)
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void unk_8014ba3c(PartyEntry* party) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r6, 0x58(r3)
	lwz r0, 0x5c(r3)
	stw r6, 0xc(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x60(r3)
	stw r0, 0x14(r1)
	lfs f0, 0xf0(r3)
	stfs f0, 0x8(r1)
	lfs f1, 0x10c(r3)
	bl partySearchHead
	cmplwi r3, 0x0
	beq @1
	stw r3, 0x140(r29)
	@1:
	lwz r3, 0x0(r29)
	rlwinm. r0, r3, 0, 5, 5
	bne @2
	rlwinm r0, r3, 0, 25, 23
	lfs f1, float_15_8041ce60(r2)
	stw r0, 0x0(r29)
	mr r3, r29
	lfs f2, float_neg15_8041cecc(r2)
	bl partySearchGround
	mr. r31, r3
	beq @3
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	mr r30, r3
	beq @3
	lbz r0, 0x4c(r29)
	li r31, 0x0
	extsb. r0, r0
	bne @3
	lwz r0, 0x8(r29)
	oris r0, r0, 0x100
	stw r0, 0x8(r29)
	lwz r0, 0x0(r29)
	oris r0, r0, 0x200
	stw r0, 0x0(r29)
	@3:
	cmplwi r31, 0x0
	stw r31, 0x138(r29)
	bne @4
	lwz r0, 0x0(r29)
	mr r3, r29
	li r4, 0x3
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r29)
	bl partyChgMot
	lfs f0, float_neg1p5_8041ced0(r2)
	stfs f0, 0x11c(r29)
	b @2
	@4:
	lfs f0, 0xe4(r29)
	rlwinm. r0, r30, 0, 23, 23
	stfs f0, 0x5c(r29)
	lwz r0, 0x0(r29)
	ori r0, r0, 0x2
	stw r0, 0x0(r29)
	beq @5
	lwz r0, 0x0(r29)
	ori r0, r0, 0x80
	stw r0, 0x0(r29)
	b @6
	@5:
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r29)
	@6:
	rlwinm. r0, r30, 0, 1, 1
	beq @7
	stw r31, 0x14c(r29)
	@7:
	mr r3, r31
	bl unk_800c8dd0
	cmpwi r3, 0x0
	beq @2
	mr r3, r29
	mr r4, r31
	addi r5, r29, 0x94
	bl partyGetAppearPos5
	lwz r0, 0x8(r29)
	mr r3, r29
	li r4, 0x2
	oris r0, r0, 0x40
	stw r0, 0x8(r29)
	lfs f0, 0x5c(r29)
	stfs f0, 0x98(r29)
	bl partyChgMot
	@2:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void unk_8014bbc8(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	lwz r4, 0x8(r3)
	lwz r30, 0x160(r3)
	rlwinm. r0, r4, 0, 30, 30
	beq @1
	rlwinm r0, r4, 0, 31, 29
	li r4, 0x1
	stw r0, 0x8(r31)
	bl partyChgPoseId
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @2
	bl partyClearFootmark
	b @3
	@2:
	bl partyClearFootmark2
	@3:
	li r0, -0x1
	stw r0, 0x168(r31)
	@1:
	mr r3, r31
	bl party_slit
	mr r3, r31
	bl party_roll
	mr r3, r31
	bl unk_800c9044
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne @4
	mr r3, r31
	bl partyChkWall
	@4:
	mr r3, r31
	bl partyChkGnd
	lfs f1, 0x58(r31)
	lfs f2, 0x60(r31)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl distABf
	lfs f0, float_31_8041ced4(r2)
	fcmpo cr0, f1, f0
	ble @5
	mr r3, r31
	li r4, 0x2
	bl partyChgRunMode
	@5:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0xe
	bne @6
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 12, 12
	bne @6
	mr r3, r31
	li r4, 0x0
	bl partyMoveBehindMario
	b @7
	@6:
	lbz r0, 0x32(r31)
	cmplwi r0, 0x1
	bne @8
	mr r3, r31
	bl unk_8014b824
	b @7
	@8:
	mr r3, r31
	bl unk_8014ba3c
	lbz r0, 0x31(r31)
	cmpwi r0, 0x7
	bne @7
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @7
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @7
	bl marioChkDeepSleep
	cmpwi r3, 0x1
	beq @7
	bl chuchu_searchObject
	cmpwi r3, 0x0
	beq @7
	lbz r0, 0x39(r31)
	cmpwi r0, 0x1
	beq @9
	bge @10
	b @11
	@10:
	cmpwi r0, 0x3
	bge @11
	b @12
	@9:
	lwz r3, 0x24(r31)
	subic. r0, r3, 0x1
	stw r0, 0x24(r31)
	bgt @7
	mr r3, r31
	li r4, 0x1
	bl partyChgPoseId
	li r3, 0x1e
	li r0, 0x2
	stw r3, 0x24(r31)
	stb r0, 0x39(r31)
	b @7
	@12:
	lwz r3, 0x24(r31)
	subic. r0, r3, 0x1
	stw r0, 0x24(r31)
	bgt @7
	li r0, 0x0
	stb r0, 0x39(r31)
	b @7
	@11:
	lis r4, str_802F3F0C@ha
	mr r3, r31
	addi r4, r4, str_802F3F0C@l
	bl partyChgPose
	li r3, 0x1
	li r0, 0x1e
	stb r3, 0x39(r31)
	stw r0, 0x24(r31)
	@7:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void party_motion_stay(PartyEntry* party) {
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
	stmw r27, 0x3c(r1)
	mr r28, r3
	lis r4, vec3_802f3e40@ha
	lwz r30, 0x160(r3)
	addi r31, r4, vec3_802f3e40@l
	bl partyGetFootmarkId
	lwz r4, 0x8(r28)
	mr r29, r3
	rlwinm. r0, r4, 0, 30, 30
	beq @1
	rlwinm r0, r4, 0, 31, 29
	mr r3, r28
	stw r0, 0x8(r28)
	li r4, 0x1
	bl partyChgPoseId
	lwz r0, 0x8(r28)
	rlwinm. r0, r0, 0, 8, 8
	bne @2
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 28, 28
	bne @3
	bl partyClearFootmark
	b @2
	@3:
	bl partyClearFootmark2
	@2:
	lwz r4, 0x8(r28)
	li r0, -0x1
	lfs f1, float_0_8041cdec(r2)
	mr r3, r28
	rlwinm r4, r4, 0, 9, 7
	stw r4, 0x8(r28)
	stw r0, 0x168(r28)
	bl unk_800c9398
	@1:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0xe
	beq @4
	lwz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 12, 12
	beq @4
	rlwinm r0, r3, 0, 13, 11
	stw r0, 0x0(r28)
	@4:
	lfs f1, 0x190(r30)
	lfs f0, float_0_8041cdec(r2)
	lfs f31, 0x40(r28)
	fcmpu cr0, f1, f0
	bne @5
	lfs f1, 0x180(r30)
	lfs f0, float_1_8041ce1c(r2)
	fcmpo cr0, f1, f0
	bge @5
	lfs f31, float_100_8041cde0(r2)
	@5:
	lbz r0, 0x3c(r30)
	cmpwi r0, 0x2
	bne @6
	lfs f31, float_70_8041ceb8(r2)
	@6:
	lwz r3, gp(r13)
	addi r4, r31, 0x188
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @7
	lwz r3, gp(r13)
	addi r4, r31, 0x190
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @7
	lwz r3, gp(r13)
	addi r4, r31, 0x198
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @8
	@7:
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @8
	lbz r0, 0x32(r28)
	cmplwi r0, 0x0
	bne @9
	lfs f30, float_18_8041ce20(r2)
	b @10
	@9:
	lbz r0, 0x31(r28)
	extsb r0, r0
	cmpwi r0, 0x5
	bne @11
	lwz r0, 0x8(r28)
	rlwinm. r0, r0, 0, 10, 10
	beq @12
	lfs f30, float_8_8041ce24(r2)
	b @10
	@12:
	lfs f30, float_30_8041ce28(r2)
	b @10
	@11:
	cmpwi r0, 0x6
	bne @10
	lwz r0, 0x8(r28)
	rlwinm. r0, r0, 0, 10, 10
	beq @13
	lfs f30, float_8_8041ce24(r2)
	b @10
	@13:
	lfs f30, float_30_8041ce28(r2)
	@10:
	lwz r0, 0x8(r28)
	fmr f31, f30
	oris r0, r0, 0x2
	stw r0, 0x8(r28)
	@8:
	lwz r3, 0x8(r28)
	extrwi. r0, r3, 1, 14
	beq @14
	lbz r0, 0x32(r28)
	cmplwi r0, 0x0
	bne @15
	lfs f29, float_18_8041ce20(r2)
	b @16
	@15:
	lbz r0, 0x31(r28)
	extsb r0, r0
	cmpwi r0, 0x5
	bne @17
	rlwinm. r0, r3, 0, 10, 10
	beq @18
	lfs f29, float_8_8041ce24(r2)
	b @16
	@18:
	lfs f29, float_30_8041ce28(r2)
	b @16
	@17:
	cmpwi r0, 0x6
	bne @16
	rlwinm. r0, r3, 0, 10, 10
	beq @19
	lfs f29, float_8_8041ce24(r2)
	b @16
	@19:
	lfs f29, float_30_8041ce28(r2)
	@16:
	fmr f31, f29
	@14:
	mr r3, r28
	bl party_slit
	mr r3, r28
	bl party_roll
	mr r3, r28
	bl unk_800c9044
	lhz r0, 0x2e(r30)
	cmplwi r0, 0xe
	bne @20
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 12, 12
	bne @20
	mr r3, r28
	li r4, 0x0
	bl partyMoveBehindMario
	b @21
	@20:
	lbz r0, 0x34(r28)
	cmplwi r0, 0x0
	beq @22
	lbz r0, 0x2f(r28)
	extsb. r0, r0
	beq @23
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	bne @24
	@23:
	lwz r3, 0x160(r28)
	lha r0, 0x50(r3)
	cmpwi r0, 0x0
	beq @25
	lfs f1, float_0_8041cdec(r2)
	lfs f0, 0x180(r3)
	fcmpu cr0, f1, f0
	bne @25
	li r0, 0x0
	b @26
	@25:
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1f
	beq @27
	cmplwi r0, 0x20
	beq @27
	cmplwi r0, 0x10
	beq @27
	cmplwi r0, 0x11
	bne @28
	@27:
	li r0, 0x0
	b @26
	@28:
	li r0, 0x1
	@26:
	cmpwi r0, 0x0
	beq @22
	lbz r0, 0x32(r28)
	cmplwi r0, 0x0
	bne @29
	lwz r5, 0x58(r28)
	mr r3, r29
	lwz r0, 0x5c(r28)
	addi r4, r1, 0x18
	stw r5, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x60(r28)
	stw r0, 0x20(r1)
	bl partyGetTargetDist3D
	fmr f0, f1
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	mr r3, r29
	fmr f29, f0
	bl partyGetTargetDist
	b @30
	@29:
	lfs f0, 0x58(r28)
	stfs f0, 0x14(r1)
	lfs f0, 0x60(r28)
	stfs f0, 0x10(r1)
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl angleABf
	lfs f3, float_0p5_8041ce00(r2)
	fmr f2, f1
	lfs f0, 0xf4(r28)
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	fmuls f1, f3, f0
	bl movePos
	lfs f1, 0x14(r1)
	lfs f2, 0x10(r1)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl distABf
	fmr f29, f1
	@30:
	bl marioChkSlitThrouh
	cmpwi r3, 0x0
	bne @31
	fcmpo cr0, f29, f31
	cror eq, gt, eq
	bne @22
	@31:
	bl marioChkDeepSleep
	cmpwi r3, 0x0
	bne @22
	mr r3, r28
	li r4, 0x1
	bl partyChgMot
	b @22
	@24:
	lbz r3, 0x2f(r28)
	extsb r3, r3
	bl anotherPartyGetPtr
	mr. r27, r3
	beq @22
	bl nokonokoGetStatus
	cmpwi r3, 0x3
	beq @32
	addi r3, r30, 0x8c
	addi r4, r27, 0x58
	bl PSVECDistance
	lfs f0, float_150_8041cebc(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @33
	@32:
	lfs f1, 0x58(r28)
	mr r3, r29
	lfs f2, 0x60(r28)
	bl partyGetTargetDist
	fcmpo cr0, f1, f31
	cror eq, gt, eq
	bne @34
	mr r3, r28
	li r4, 0x1
	bl partyChgMot
	bl partyClearFootmark2
	b @34
	@33:
	lbz r3, 0x31(r27)
	cmpwi r3, 0x3
	bne @35
	lbz r0, 0x34(r27)
	cmplwi r0, 0x3
	bne @35
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x1f
	beq @34
	cmplwi r0, 0x10
	beq @34
	cmplwi r0, 0x11
	beq @34
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl distABf
	fcmpo cr0, f1, f31
	cror eq, gt, eq
	bne @34
	mr r3, r28
	li r4, 0x1
	bl partyChgMot
	b @34
	@35:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 23, 23
	beq @36
	extsb r0, r3
	cmpwi r0, 0x4
	bne @34
	@36:
	lfs f1, 0x58(r28)
	lfs f2, 0x60(r28)
	lfs f3, 0x58(r27)
	lfs f4, 0x60(r27)
	bl distABf
	fcmpo cr0, f1, f31
	cror eq, gt, eq
	bne @34
	mr r3, r28
	li r4, 0x1
	bl partyChgMot
	@34:
	bl marioChkSlitThrouh
	cmpwi r3, 0x0
	beq @22
	mr r3, r28
	li r4, 0x1
	bl partyChgMot
	@22:
	lwz r6, 0x58(r28)
	mr r3, r28
	lwz r0, 0x5c(r28)
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	stw r6, 0x24(r1)
	stw r0, 0x28(r1)
	lwz r0, 0x60(r28)
	stw r0, 0x2c(r1)
	bl partyGetMoveDirSpd
	lfs f1, 0x8(r1)
	mr r3, r28
	lfs f2, 0xc(r1)
	addi r4, r1, 0x24
	bl partySearchFrontWall
	cmplwi r3, 0x0
	beq @37
	stw r3, 0x12c(r28)
	lfs f0, float_0_8041cdec(r2)
	lfs f1, 0x104(r28)
	fcmpu cr0, f1, f0
	beq @37
	stw r3, 0x134(r28)
	@37:
	lfs f0, 0x24(r1)
	mr r3, r28
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	stfs f0, 0x58(r28)
	lfs f0, 0x2c(r1)
	stfs f0, 0x60(r28)
	bl partyGetMoveDirSpd
	lfs f1, 0x8(r1)
	addi r3, r1, 0x24
	lfs f2, 0xc(r1)
	li r4, 0x1
	lfs f3, 0xf4(r28)
	lfs f4, 0xf0(r28)
	bl marioChkWallAround
	lfs f0, 0x24(r1)
	stfs f0, 0x58(r28)
	lfs f0, 0x2c(r1)
	stfs f0, 0x60(r28)
	lbz r0, 0x32(r28)
	cmplwi r0, 0x1
	bne @38
	mr r3, r28
	bl unk_8014b824
	b @21
	@38:
	mr r3, r28
	bl unk_8014ba3c
	mr r3, r28
	bl party_force_reset_outofscreen
	lbz r0, 0x31(r28)
	cmpwi r0, 0x7
	bne @21
	lwz r0, 0x4(r28)
	rlwinm. r0, r0, 0, 16, 16
	bne @21
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @21
	bl marioChkDeepSleep
	cmpwi r3, 0x1
	beq @21
	bl chuchu_searchObject
	cmpwi r3, 0x0
	beq @21
	lbz r0, 0x39(r28)
	cmpwi r0, 0x1
	beq @39
	bge @40
	b @41
	@40:
	cmpwi r0, 0x3
	bge @41
	b @42
	@39:
	lwz r3, 0x24(r28)
	subic. r0, r3, 0x1
	stw r0, 0x24(r28)
	bgt @21
	mr r3, r28
	li r4, 0x1
	bl partyChgPoseId
	li r3, 0x1e
	li r0, 0x2
	stw r3, 0x24(r28)
	stb r0, 0x39(r28)
	b @21
	@42:
	lwz r3, 0x24(r28)
	subic. r0, r3, 0x1
	stw r0, 0x24(r28)
	bgt @21
	li r0, 0x0
	stb r0, 0x39(r28)
	b @21
	@41:
	mr r3, r28
	addi r4, r31, 0xcc
	bl partyChgPose
	li r3, 0x1
	li r0, 0x1e
	stb r3, 0x39(r28)
	stw r0, 0x24(r28)
	@21:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	lmw r27, 0x3c(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void N_partyFollowCloseOff(PartyEntry* party) {
	nofralloc
	lwz r0, 0x8(r3)
	rlwinm r0, r0, 0, 15, 13
	stw r0, 0x8(r3)
	blr
}

asm void N_partyFollowCloseOn(PartyEntry* party) {
	nofralloc
	lwz r0, 0x8(r3)
	oris r0, r0, 0x2
	stw r0, 0x8(r3)
	blr
}

asm void unk_8014c47c(void) {
	nofralloc
	lfs f0, float_60_8041cec0(r2)
	stfs f0, touch_wall_ct(r13)
	blr
}

asm s32 evt_snd_sfx_all_stop(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl psndSFXAllOff
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_set_rev_mode(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, 0x18(r3)
	lwz r3, 0x0(r3)
	bl psndSetReverb
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_env_lpf(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r4, 0x4(r4)
	bl evtGetValue
	clrlwi r4, r3, 16
	mr r3, r31
	bl psndENV_LPF
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_envoff_f(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r4, 0x4(r4)
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	mr r4, r0
	li r5, 0x0
	bl psndENVOff_f_d
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_envoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, 0x18(r3)
	lwz r3, 0x0(r3)
	bl psndENVOff
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_envon_f(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r30, 0x4(r4)
	lwz r4, 0x8(r4)
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	mr r5, r0
	mr r4, r30
	li r6, 0x0
	bl psndENVOn_f_d
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r3, 0x0(r4)
	lwz r4, 0x4(r4)
	bl psndENVOn
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfx_dist(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	clrlwi r4, r3, 16
	mr r3, r31
	bl psndSFX_dist
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfx_pos(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	stfs f1, 0x8(r1)
	mr r3, r29
	lwz r4, 0x8(r31)
	bl evtGetFloat
	stfs f1, 0xc(r1)
	mr r3, r29
	lwz r4, 0xc(r31)
	bl evtGetFloat
	stfs f1, 0x10(r1)
	mr r3, r30
	addi r4, r1, 0x8
	bl psndSFX_pos
	lwz r0, 0x34(r1)
	li r3, 0x2
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_snd_sfx_vol(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	clrlwi r4, r0, 24
	bl psndSFX_vol
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfx_pit(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	extsh r4, r0
	bl psndSFX_pit
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfxchk(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	bl psndSFXChk
	lwz r4, 0x4(r31)
	mr r5, r3
	mr r3, r30
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl psndSFXOff
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfxon_3d_ex(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r26, 0x18(r1)
	mr r26, r3
	lwz r31, 0x18(r3)
	lwz r30, 0x0(r31)
	lwz r4, 0x4(r31)
	bl evtGetFloat
	stfs f1, 0x8(r1)
	mr r3, r26
	lwz r4, 0x8(r31)
	bl evtGetFloat
	stfs f1, 0xc(r1)
	mr r3, r26
	lwz r4, 0xc(r31)
	bl evtGetFloat
	stfs f1, 0x10(r1)
	mr r3, r26
	lwz r4, 0x10(r31)
	bl evtGetValue
	lwz r4, 0x14(r31)
	clrlwi r29, r3, 16
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x18(r31)
	clrlwi r28, r3, 16
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x1c(r31)
	clrlwi r27, r3, 16
	mr r3, r26
	bl evtGetValue
	lwz r31, 0x20(r31)
	clrlwi r8, r3, 16
	cmpwi r31, 0x0
	bne @1
	mr r3, r30
	mr r7, r27
	addi r4, r1, 0x8
	clrlwi r5, r29, 24
	clrlwi r6, r28, 24
	bl psndSFXOnEx_3D
	b @2
	@1:
	mr r3, r30
	mr r7, r27
	addi r4, r1, 0x8
	clrlwi r5, r29, 24
	clrlwi r6, r28, 24
	bl psndSFXOnEx_3D
	mr r5, r3
	mr r3, r26
	mr r4, r31
	bl evtSetValue
	@2:
	lmw r26, 0x18(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r30, 0x0(r31)
	lwz r4, 0x4(r31)
	bl evtGetFloat
	stfs f1, 0x8(r1)
	mr r3, r29
	lwz r4, 0x8(r31)
	bl evtGetFloat
	stfs f1, 0xc(r1)
	mr r3, r29
	lwz r4, 0xc(r31)
	bl evtGetFloat
	stfs f1, 0x10(r1)
	lwz r31, 0x10(r31)
	cmpwi r31, 0x0
	beq @1
	addis r0, r31, 0xee7
	cmplwi r0, 0x4d80
	bne @2
	@1:
	mr r3, r30
	addi r4, r1, 0x8
	bl psndSFXOn_3D
	b @3
	@2:
	mr r3, r30
	addi r4, r1, 0x8
	bl psndSFXOn_3D
	mr r5, r3
	mr r3, r29
	mr r4, r31
	bl evtSetValue
	@3:
	lwz r0, 0x34(r1)
	li r3, 0x2
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 evt_snd_sfxon_(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r3, 0x18(r3)
	lwz r31, 0x4(r3)
	lwz r3, 0x0(r3)
	cmpwi r31, 0x0
	bne @1
	bl psndSFXOn_
	b @2
	@1:
	bl psndSFXOn_
	mr r5, r3
	mr r3, r30
	mr r4, r31
	bl evtSetValue
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfxon__(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r31, 0x4(r31)
	cmpwi r31, 0x0
	bne @1
	bl psndSFXOn
	b @2
	@1:
	bl psndSFXOn
	mr r5, r3
	mr r3, r30
	mr r4, r31
	bl evtSetValue
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_sfxon(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r3, 0x18(r3)
	lwz r31, 0x4(r3)
	lwz r3, 0x0(r3)
	cmpwi r31, 0x0
	bne @1
	bl psndSFXOn
	b @2
	@1:
	bl psndSFXOn
	mr r5, r3
	mr r3, r30
	mr r4, r31
	bl evtSetValue
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_bgm_scope(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r4, 0x4(r4)
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl psndBGMScope
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_bgm_freq(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r4, 0x4(r4)
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	clrlwi r4, r0, 16
	bl psndBGM_rate
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_bgmoff_f(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r4, 0x4(r4)
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	mr r4, r0
	li r5, 0x0
	bl psndBGMOff_f_d
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, 0x18(r3)
	lwz r3, 0x0(r3)
	bl psndBGMOff
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unk_8014cc24(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r31, 0x18(r3)
	lwz r30, 0x0(r31)
	lwz r29, 0x4(r31)
	lwz r4, 0x8(r31)
	bl evtGetValue
	lwz r4, 0xc(r31)
	mr r31, r3
	mr r3, r28
	bl evtGetValue
	mr r3, r30
	mr r4, r29
	mr r5, r31
	mr r6, r31
	li r7, 0x0
	bl psndBGMOn_f_d
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_snd_bgmon_f(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	lwz r4, 0x18(r3)
	lwz r31, 0x0(r4)
	lwz r30, 0x4(r4)
	lwz r4, 0x8(r4)
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	mr r5, r0
	mr r4, r30
	li r6, 0x0
	bl unk_800d7270
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r3, 0x0(r4)
	lwz r4, 0x4(r4)
	bl psndBGMOn
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
