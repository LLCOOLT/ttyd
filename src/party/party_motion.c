#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include "driver/hitdrv.h"
#include <dolphin/types.h>
#include <dolphin/mtx.h>

// file-local full-layout view of PartyEntry (party.h is not included)
typedef struct PartyMarioView {
    u32 flags0;             // 0x0
    u8 unk4[0xC - 0x4];     // 0x4
    u32 flags;              // 0xC
    u8 unk10[0x2E - 0x10];  // 0x10
    u16 motionId;           // 0x2E
    u8 unk30[0x50 - 0x30];  // 0x30
    s16 unk50;              // 0x50
    u8 unk52[0x8C - 0x52];  // 0x52
    Vec position;           // 0x8C
    u8 unk98[0x180 - 0x98]; // 0x98
    f32 unk180;             // 0x180
    u8 unk184[0x198 - 0x184]; // 0x184
    f32 unk198;             // 0x198
    u8 unk19C[0x1A8 - 0x19C]; // 0x19C
    f32 unk1A8;             // 0x1A8
    f32 unk1AC;             // 0x1AC
    u8 unk1B0[0x1B4 - 0x1B0]; // 0x1B0
    f32 unk1B4;             // 0x1B4
    u8 unk1B8[0x224 - 0x1B8]; // 0x1B8
    f32 unk224;             // 0x224
} PartyMarioView;

typedef struct PartyEntry {
    u32 flags;                  // 0x0
    u32 flags2;                 // 0x4
    u32 flags3;                 // 0x8
    u8 unkC[0x24 - 0xC];        // 0xC
    s32 unk24;                  // 0x24
    u8 unk28[0x31 - 0x28];      // 0x28
    s8 currentMemberId;         // 0x31
    u8 unk32;                   // 0x32
    u8 unk33[0x37 - 0x33];      // 0x33
    u8 unk37;                   // 0x37
    u8 unk38;                   // 0x38
    u8 unk39;                   // 0x39
    u8 unk3A;                   // 0x3A
    u8 unk3B;                   // 0x3B
    u8 unk3C[0x40 - 0x3C];      // 0x3C
    f32 unk40;                  // 0x40
    u8 unk44[0x4C - 0x44];      // 0x44
    s8 unk4C;                   // 0x4C
    u8 unk4D[0x54 - 0x4D];      // 0x4D
    f32 unk54;                  // 0x54
    Vec position;               // 0x58
    f32 unk64;                  // 0x64
    u8 unk68[0x6C - 0x68];      // 0x68
    f32 unk6C;                  // 0x6C
    u8 unk70[0x7C - 0x70];      // 0x70
    Vec unk7C;                  // 0x7C
    Vec unk88;                  // 0x88
    Vec unk94;                  // 0x94
    u8 unkA0[0xE4 - 0xA0];      // 0xA0
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

static f32 unk_804189e8;
static s32 unk_804189ec;
static f32 touch_wall_ct;

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
s32 partyGetFootmarkId(void);
void partyNextReadId(s32 id);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 toMovedir(f32 angle);
void partyGetAppearPos4(PartyEntry* party, Vec* pos);
void partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 dir);
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

USER_FUNC(evt_snd_bgmon) {
    s32* args = event->args;
    psndBGMOn(args[0], (char*)args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgmon_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    unk_800d7270(a, b, c, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_8014cc24) {
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    evtGetValue(event, args[3]);
    psndBGMOn_f_d(a, b, c, c, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgmoff) {
    psndBGMOff(event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgmoff_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    ((BOOL (*)(s32, s32, s32))psndBGMOff_f_d)(a, t, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgm_freq) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGM_rate(a, t);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgm_scope) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMScope(a, t);
    return EVT_RETURN_DONE;
}

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

USER_FUNC(evt_snd_sfxoff) {
    psndSFXOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfxchk) {
    s32* args = event->args;
    evtSetValue(event, args[1], psndSFXChk(evtGetValue(event, args[0])));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfx_pit) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_pit(id, t);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfx_vol) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_vol(id, t);
    return EVT_RETURN_DONE;
}

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

USER_FUNC(evt_snd_sfx_dist) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    psndSFX_dist(id, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envon) {
    s32* args = event->args;
    psndENVOn(args[0], args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envon_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    psndENVOn_f_d(a, b, c, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envoff) {
    psndENVOff(event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envoff_f) {
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndENVOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_env_lpf) {
    s32* args = event->args;
    s32 a = args[0];
    psndENV_LPF(a, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_set_rev_mode) {
    psndSetReverb(event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfx_all_stop) {
    psndSFXAllOff();
    return EVT_RETURN_DONE;
}

void unk_8014c47c(void) {
    touch_wall_ct = 60.0f;
}

void N_partyFollowCloseOn(PartyEntry* party) {
    party->flags3 |= 0x20000;
}

void N_partyFollowCloseOff(PartyEntry* party) {
    party->flags3 &= ~0x20000;
}

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
                    partyChgPose(party, "PCH_A2_1");
                    party->unk39 = 1;
                    party->unk24 = 30;
                    break;
            }
        }
    }
}

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

void party_set_behind_dir(PartyEntry* party, f32 dir) {
    party->unk54 = revise360(dir + ((PartyCamView*)camGetPtr((CameraId)4))->unk114);
    party->flags3 |= 0x100000;
}

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

void party_motion_beside_mario(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    f32 x, z;
    f32 y;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 thr;
    f32 sp;

    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->unk54 = revise360(90.0f + partyGetFollowDir(party));
        sp = mario->unk1B4;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, 1.5f * sp, party->unk54);
        party->unk24 = distABf(party->position.x, party->position.z, x, z);
        if (party->unk24 <= 0) {
            party->unk24 = 1;
        }
    }
    if (marioKeyOffChk()) {
        party->unk54 = revise360(90.0f + partyGetFollowDir(party));
    }
    sp = mario->unk1B4;
    x = mario->position.x;
    z = mario->position.z;
    y = mario->position.y;
    movePos(&x, &z, 1.5f * sp, party->unk54);
    angleABf(party->position.x, party->position.z, x, z);
    dist = 1000.0f;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y + touch_wall_ct, z, 0.0f, -1.0f, 0.0f);
    if (!hit) {
        y = -2000.0f;
    } else {
        y = (s32)(100.0f * hy + 0.5f) / 100.0f;
        hitGetAttr(hit);
    }
    if (y <= -2000.0f) {
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, 1.5f * mario->unk1B4, toMovedir(mario->unk1A8));
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

static inline BOOL partyChkHitAttr200(HitEntry* hit) {
    if (!hit) {
        return FALSE;
    }
    if (hitGetAttr(hit) & 0x200) {
        return TRUE;
    }
    return FALSE;
}

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

BOOL party_roll(PartyEntry* party) {
    BOOL ret = TRUE;
    f32 x;
    f32 d;
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
                    x = party->unk10C;
                    d = 0.1f * (90.0f - x);
                    x = d + x;
                    if (__fabsf(90.0f - x < 1.0f)) {
                        x = 90.0f;
                    }
                    party->unk10C = x;
                    party->unk110 = x;
                } else {
                    x = party->unk10C;
                    d = 0.1f * (270.0f - x);
                    x = d + x;
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

extern int __float_nan[];
void sincosf(f32* ret_sin, f32* ret_cos, f32 degree);
s32 marioCtrlOffChk(void);
void partyGetAppearPos3(PartyEntry* party, Vec* pos);
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);

static inline s32 pm_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 pm_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (pm_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir) {
    f32 c2, s2;
    HitCheckQuery q2;
    HitCheckQuery q;
    f32 c, s;
    f32 r;
    f32 wallct;
    f32 y;
    f32 rf;
    s32 i;
    HitEntry* hit;
    Vec up = {0.0f, 1.0f, 0.0f};
    Vec down = {0.0f, -1.0f, 0.0f};

    r = 2.0f * party->unkF4 / 3.0f;
    q.targetDir = up;
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
    q2.targetDir = down;
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

void party_force_reset_outofscreen(PartyEntry* party) {
    PartyMarioView* mario = party->playerPtr;
    s32 margin;
    PartyMarioView* m2;
    s32 i;
    f32 speed;
    s32 j;
    f32 up;
    f32 y;
    HitEntry* hit;
    f32 sz, sy, sx;
    f32 dist;
    Vec nrm;
    Vec hitPos;
    Vec dir;
    Vec start;
    Vec pos;

    if (marioCtrlOffChk() || marioKeyOffChk()) {
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
        movePos(&pos.x, &pos.z, speed, angleABf(pos.x, pos.z, m2->position.x, m2->position.z));
        up = 200.0f;
        j = 0;
        y = pos.y;
        while (TRUE) {
            start = pos;
            start.y += up;
            dist = 300.0f;
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
                start = pos;
                dist = 100.0f;
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
