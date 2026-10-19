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
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_802f3e40[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e4c[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e58[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e64[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e70[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e7c[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e88[3];
__declspec(section ".rodata") extern const f32 vec3_802f3e94[3];
__declspec(section ".rodata") extern const f32 vec3_802f3ea0[3];
__declspec(section ".rodata") extern const f32 vec3_802f3eac[3];
__declspec(section ".rodata") extern const f32 vec3_802f3eb8[3];
__declspec(section ".rodata") extern const f32 vec3_802f3ec4[3];
__declspec(section ".rodata") extern const f32 vec3_802f3ed0[3];
__declspec(section ".rodata") extern const f32 vec3_802f3edc[3];
__declspec(section ".rodata") extern const f32 vec3_802f3ee8[3];
__declspec(section ".rodata") extern const f32 vec3_802f3ef4[3];
__declspec(section ".rodata") extern const f32 vec3_802f3f00[3];
__declspec(section ".rodata") extern const char str_802F3F0C[];
__declspec(section ".rodata") extern const char str_802F3F18[];
__declspec(section ".rodata") extern const char str_802F3F20[];
__declspec(section ".rodata") extern const char str_802F3F34[];
__declspec(section ".rodata") extern const f64 double_to_int_802f3f48;
__declspec(section ".rodata") extern const f64 double_0p5_802f3f50;
__declspec(section ".rodata") extern const f64 double_3_802f3f58;
__declspec(section ".rodata") extern const f64 double_0_802f3f60;
__declspec(section ".rodata") extern const char str_802F3F68[];
__declspec(section ".rodata") extern const char str_802F3F70[];
__declspec(section ".rodata") extern const char str_802F3F78[];
__declspec(section ".rodata") extern const char str_802F3F80[];
__declspec(section ".rodata") extern const char str_802F3F88[];
__declspec(section ".rodata") extern const char str_802F3F90[];
__declspec(section ".rodata") extern const char str_802F3F98[];
__declspec(section ".rodata") extern const f64 double_180_802f3fa0;
__declspec(section ".rodata") extern const char str_802F3FA8[];
__declspec(section ".rodata") extern const char str_802F3FB0[];
__declspec(section ".rodata") extern const char str_802F3FB8[];
__declspec(section ".rodata") extern const char str_802F3FC0[];
__declspec(section ".rodata") extern const char str_802F3FC8[];
__declspec(section ".rodata") extern const char str_802F3FD0[];
__declspec(section ".rodata") extern const char str_802F3FD8[];
__declspec(section ".rodata") extern const f64 double_12_802f3fe0;
__declspec(section ".sdata2") extern const f32 float_20_8041cdc0;
__declspec(section ".sdata2") extern const f32 float_800_8041cdc4;
__declspec(section ".sdata2") extern const f32 float_neg100_8041cdc8;
__declspec(section ".sdata2") extern const f32 float_700_8041cdcc;
__declspec(section ".sdata2") extern const f32 float_650_8041cdd0;
__declspec(section ".sdata2") extern const f32 float_10_8041cdd4;
__declspec(section ".sdata2") extern const f32 float_200_8041cdd8;
__declspec(section ".sdata2") extern const f32 float_300_8041cddc;
__declspec(section ".sdata2") extern const f32 float_100_8041cde0;
__declspec(section ".sdata2") extern const f32 float_74_8041cde4;
__declspec(section ".sdata2") extern const f32 float_50_8041cde8;
__declspec(section ".sdata2") extern const f32 float_0_8041cdec;
__declspec(section ".sdata2") extern const f32 float_40_8041cdf0;
__declspec(section ".sdata2") extern const f32 float_1000_8041cdf4;
__declspec(section ".sdata2") extern const f32 float_neg1_8041cdf8;
__declspec(section ".sdata2") extern const f32 float_neg2000_8041cdfc;
__declspec(section ".sdata2") extern const f32 float_0p5_8041ce00;
__declspec(section ".sdata2") extern const f32 float_neg0p5_8041ce04;
__declspec(section ".sdata2") extern const f32 float_2_8041ce08;
__declspec(section ".sdata2") extern const f32 float_3_8041ce0c;
__declspec(section ".sdata2") extern const f32 float_45_8041ce10;
__declspec(section ".sdata2") extern const f32 float_0p75_8041ce14;
__declspec(section ".sdata2") extern const f32 float_5_8041ce18;
__declspec(section ".sdata2") extern const f32 float_1_8041ce1c;
__declspec(section ".sdata2") extern const f32 float_18_8041ce20;
__declspec(section ".sdata2") extern const f32 float_8_8041ce24;
__declspec(section ".sdata2") extern const f32 float_30_8041ce28;
__declspec(section ".sdata2") extern const f32 float_neg6_8041ce2c;
__declspec(section ".sdata2") extern const f32 float_6_8041ce30;
__declspec(section ".sdata2") extern const f32 float_270_8041ce34;
__declspec(section ".sdata2") extern const f32 float_180_8041ce38;
__declspec(section ".sdata2") extern const f32 float_7_8041ce3c;
__declspec(section ".sdata2") extern const f32 float_neg3_8041ce40;
__declspec(section ".sdata2") extern const f32 float_0p1_8041ce44;
__declspec(section ".sdata2") extern const f32 float_90_8041ce48;
__declspec(section ".sdata2") extern const f32 float_280_8041ce4c;
__declspec(section ".sdata2") extern const f32 float_260_8041ce50;
__declspec(section ".sdata2") extern const f32 float_315_8041ce54;
__declspec(section ".sdata2") extern const f32 float_135_8041ce58;
__declspec(section ".sdata2") extern const f32 float_225_8041ce5c;
__declspec(section ".sdata2") extern const f32 float_15_8041ce60;
__declspec(section ".sdata2") extern const f32 float_neg300_8041ce64;
__declspec(section ".sdata2") extern const f32 float_240_8041ce68;
__declspec(section ".sdata2") extern const f32 float_neg1p4_8041ce6c;
__declspec(section ".sdata2") extern const f32 float_neg16_8041ce70;
__declspec(section ".sdata2") extern const f32 float_neg2001_8041ce74;
__declspec(section ".sdata2") extern const f32 float_37_8041ce78;
__declspec(section ".sdata2") extern const f32 float_1p3_8041ce7c;
__declspec(section ".sdata2") extern const f32 float_2p25_8041ce80;
__declspec(section ".sdata2") extern const f32 float_0p6_8041ce84;
__declspec(section ".sdata2") extern const f32 float_1p4_8041ce88;
__declspec(section ".sdata2") extern const f32 float_0p9_8041ce8c;
__declspec(section ".sdata2") extern const f32 float_25_8041ce90;
__declspec(section ".sdata2") extern const f32 float_13_8041ce94;
__declspec(section ".sdata2") extern const f32 float_1p5_8041ce98;
__declspec(section ".sdata2") extern const f32 float_3p6_8041ce9c;
__declspec(section ".sdata2") extern const f32 float_0p05_8041cea0;
__declspec(section ".sdata2") extern const f32 float_28_8041cea4;
__declspec(section ".sdata2") extern const f32 float_32_8041cea8;
__declspec(section ".sdata2") extern const f32 float_35_8041ceac;
__declspec(section ".sdata2") extern const f32 float_4_8041ceb0;
__declspec(section ".sdata2") extern const f32 float_37p5_8041ceb4;
__declspec(section ".sdata2") extern const f32 float_70_8041ceb8;
__declspec(section ".sdata2") extern const f32 float_150_8041cebc;
__declspec(section ".sdata2") extern const f32 float_60_8041cec0;
__declspec(section ".sdata2") extern const f32 float_11_8041cec4;
__declspec(section ".sdata2") extern const f32 float_18p5_8041cec8;
__declspec(section ".sdata2") extern const f32 float_neg15_8041cecc;
__declspec(section ".sdata2") extern const f32 float_neg1p5_8041ced0;
__declspec(section ".sdata2") extern const f32 float_31_8041ced4;
#define EXT_LIT(sym, val) (sym)

#endif

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
#endif
#ifndef NONMATCHING
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    psndBGMOn(args[0], (char*)args[1]);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmon_f) {
#endif
#ifndef NONMATCHING
s32 evt_snd_bgmon_f(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    unk_800d7270(a, b, c, 0);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(unk_8014cc24) {
#endif
#ifndef NONMATCHING
s32 unk_8014cc24(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    evtGetValue(event, args[3]);
    psndBGMOn_f_d(a, b, c, c, 0);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmoff) {
#endif
#ifndef NONMATCHING
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall) {
#endif
    psndBGMOff(event->args[0]);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgmoff_f) {
#endif
#ifndef NONMATCHING
s32 evt_snd_bgmoff_f(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    ((BOOL (*)(s32, s32, s32))psndBGMOff_f_d)(a, t, 0);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgm_freq) {
#endif
#ifndef NONMATCHING
s32 evt_snd_bgm_freq(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGM_rate(a, t);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_bgm_scope) {
#endif
#ifndef NONMATCHING
s32 evt_snd_bgm_scope(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMScope(a, t);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxon(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon__) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxon__(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon_) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxon_(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon_3d) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxon_3d_ex) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxon_3d_ex(EventEntry* event, BOOL isFirstCall) {
#endif
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

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxoff) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall) {
#endif
    psndSFXOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfxchk) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfxchk(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    evtSetValue(event, args[1], psndSFXChk(evtGetValue(event, args[0])));
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_pit) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfx_pit(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_pit(id, t);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_vol) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfx_vol(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_vol(id, t);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_pos) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfx_pos(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    Vec pos;
    s32 id = evtGetValue(event, args[0]);
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    psndSFX_pos(id, &pos);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_dist) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfx_dist(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    psndSFX_dist(id, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_envon) {
#endif
#ifndef NONMATCHING
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    psndENVOn(args[0], args[1]);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_envon_f) {
#endif
#ifndef NONMATCHING
s32 evt_snd_envon_f(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 b = args[1];
    s32 c = evtGetValue(event, args[2]);
    psndENVOn_f_d(a, b, c, 0);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_envoff) {
#endif
#ifndef NONMATCHING
s32 evt_snd_envoff(EventEntry* event, BOOL isFirstCall) {
#endif
    psndENVOff(event->args[0]);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_envoff_f) {
#endif
#ifndef NONMATCHING
s32 evt_snd_envoff_f(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndENVOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_env_lpf) {
#endif
#ifndef NONMATCHING
s32 evt_snd_env_lpf(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 a = args[0];
    psndENV_LPF(a, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_set_rev_mode) {
#endif
#ifndef NONMATCHING
s32 evt_snd_set_rev_mode(EventEntry* event, BOOL isFirstCall) {
#endif
    psndSetReverb(event->args[0]);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_snd_sfx_all_stop) {
#endif
#ifndef NONMATCHING
s32 evt_snd_sfx_all_stop(EventEntry* event, BOOL isFirstCall) {
#endif
    psndSFXAllOff();
    return EVT_RETURN_DONE;
}

#ifndef NONMATCHING
f32 PSVECDistance(const Vec* a, const Vec* b);
int strcmp(const char *s1, const char *s2);
void L_getTargetPos(s32 id, Vec* pos);
PartyEntry* anotherPartyGetPtr(s32 id);
s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir);
s32 marioChkSlitThrouh(void);
HitEntry* marioChkWallAround(Vec* pos, s32 a, f32 spd, f32 dir, f32 w, f32 h);
s32 marioCtrlOffChk(void);
PartyMarioView* marioGetPtr(void);
s32 marioGetSlitFloorPos(Vec* pos);
s32 nokonokoGetStatus(PartyEntry* party);
void partyChkFrontStep(PartyEntry* party, f32 dist, f32* y, f32* a, f32* b);
void partyGetAppearPos3(PartyEntry* party, Vec* pos);
struct PartyFootmark* partyGetFootmarkPtr(s32 id);
s32 partyGetFootmarkReadId(s32 id);
s32 partyGetFootmarkWriteId(s32 id);
void partyGetMoveDirSpd(PartyEntry* party, f32* dir, f32* spd);
void partyGetReadId(s32 id, f32* x, f32* y, f32* z);
void partyGetReadId2(s32 id, Vec* pos);
f32 partyGetTargetDir(s32 id, f32 x, f32 z);
f32 partyGetTargetDist(s32 id, f32 x, f32 z);
f32 partyGetTargetDist3D(s32 id, Vec* p);
f32 partyGetTargetDistY(s32 id);
f32 partyGetTargetMovespd2(PartyEntry* party);
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
void party_force_reset_outofscreen(PartyEntry* party);
void unk_800c8e74(PartyEntry* party);
void unk_800c93d0(PartyEntry* party, f32 spd);
f32 unk_800c9f48(s32 id, f32 y);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void unk_8014c47c(void) {
#ifdef NONMATCHING
    touch_wall_ct = 60.0f;
#endif
#ifndef NONMATCHING
	asm volatile {
		lfs f0, float_60_8041cec0(r2)
		stfs f0, touch_wall_ct(r13)
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void N_partyFollowCloseOn(PartyEntry* party) {
    party->flags3 |= 0x20000;
}

void N_partyFollowCloseOff(PartyEntry* party) {
    party->flags3 &= ~0x20000;
}

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void party_motion_stay(PartyEntry* party) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[44];
	asm volatile {
		opword 0x7C7C1B78
		lis r4, vec3_802f3e40@ha
		opword 0x83C30160
		addi r31, r4, vec3_802f3e40@l
		bl partyGetFootmarkId
		opword 0x809C0008
		opword 0x7C7D1B78
		opword 0x548007BD
		opword 0x4182005C
		opword 0x548007FA
		opword 0x7F83E378
		opword 0x901C0008
		opword 0x38800001
		bl partyChgPoseId
		opword 0x801C0008
		opword 0x54000211
		opword 0x4082001C
		opword 0x801C0000
		opword 0x54000739
		opword 0x4082000C
		bl partyClearFootmark
		opword 0x48000008
		bl partyClearFootmark2
		opword 0x809C0008
		opword 0x3800FFFF
		lfs f1, float_0_8041cdec(r2)
		opword 0x7F83E378
		opword 0x5484024E
		opword 0x909C0008
		opword 0x901C0168
		bl unk_800c9398
		opword 0xA01E002E
		opword 0x2800000E
		opword 0x41820018
		opword 0x807C0000
		opword 0x54600319
		opword 0x4182000C
		opword 0x54600356
		opword 0x901C0000
		opword 0xC03E0190
		lfs f0, float_0_8041cdec(r2)
		opword 0xC3FC0040
		opword 0xFC010000
		opword 0x40820018
		opword 0xC03E0180
		lfs f0, float_1_8041ce1c(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f31, float_100_8041cde0(r2)
		opword 0x881E003C
		opword 0x2C000002
		opword 0x40820008
		lfs f31, float_70_8041ceb8(r2)
		lwz r3, gp(r13)
		opword 0x389F0188
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x41820034
		lwz r3, gp(r13)
		opword 0x389F0190
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		lwz r3, gp(r13)
		opword 0x389F0198
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x40820080
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x40820074
		opword 0x881C0032
		opword 0x28000000
		opword 0x4082000C
		lfs f30, float_18_8041ce20(r2)
		opword 0x48000050
		opword 0x881C0031
		opword 0x7C000774
		opword 0x2C000005
		opword 0x40820020
		opword 0x801C0008
		opword 0x54000295
		opword 0x4182000C
		lfs f30, float_8_8041ce24(r2)
		opword 0x4800002C
		lfs f30, float_30_8041ce28(r2)
		opword 0x48000024
		opword 0x2C000006
		opword 0x4082001C
		opword 0x801C0008
		opword 0x54000295
		opword 0x4182000C
		lfs f30, float_8_8041ce24(r2)
		opword 0x48000008
		lfs f30, float_30_8041ce28(r2)
		opword 0x801C0008
		opword 0xFFE0F090
		opword 0x64000002
		opword 0x901C0008
		opword 0x807C0008
		opword 0x54607FFF
		opword 0x41820060
		opword 0x881C0032
		opword 0x28000000
		opword 0x4082000C
		lfs f29, float_18_8041ce20(r2)
		opword 0x48000048
		opword 0x881C0031
		opword 0x7C000774
		opword 0x2C000005
		opword 0x4082001C
		opword 0x54600295
		opword 0x4182000C
		lfs f29, float_8_8041ce24(r2)
		opword 0x48000028
		lfs f29, float_30_8041ce28(r2)
		opword 0x48000020
		opword 0x2C000006
		opword 0x40820018
		opword 0x54600295
		opword 0x4182000C
		lfs f29, float_8_8041ce24(r2)
		opword 0x48000008
		lfs f29, float_30_8041ce28(r2)
		opword 0xFFE0E890
		opword 0x7F83E378
		bl party_slit
		opword 0x7F83E378
		bl party_roll
		opword 0x7F83E378
		bl unk_800c9044
		opword 0xA01E002E
		opword 0x2800000E
		opword 0x40820020
		opword 0x801C0000
		opword 0x54000319
		opword 0x40820014
		opword 0x7F83E378
		opword 0x38800000
		bl partyMoveBehindMario
		opword 0x48000424
		opword 0x881C0034
		opword 0x28000000
		opword 0x41820284
		opword 0x881C002F
		opword 0x7C000775
		opword 0x41820014
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x4082013C
		opword 0x807C0160
		opword 0xA8030050
		opword 0x2C000000
		opword 0x4182001C
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0030180
		opword 0xFC010000
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000034
		opword 0xA003002E
		opword 0x2800001F
		opword 0x4182001C
		opword 0x28000020
		opword 0x41820014
		opword 0x28000010
		opword 0x4182000C
		opword 0x28000011
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820208
		opword 0x881C0032
		opword 0x28000000
		opword 0x40820044
		opword 0x80BC0058
		opword 0x7FA3EB78
		opword 0x801C005C
		la r4, _af_pad+16
		opword 0x90A10018
		opword 0x9001001C
		opword 0x801C0060
		opword 0x90010020
		bl partyGetTargetDist3D
		opword 0xFC000890
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0x7FA3EB78
		opword 0xFFA00090
		bl partyGetTargetDist
		opword 0x4800005C
		opword 0xC01C0058
		opword 0xD0010014
		opword 0xC01C0060
		opword 0xD0010010
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC07E008C
		opword 0xC09E0094
		bl angleABf
		lfs f3, float_0p5_8041ce00(r2)
		opword 0xFC400890
		opword 0xC01C00F4
		opword 0x38610014
		opword 0x38810010
		opword 0xEC230032
		bl movePos
		opword 0xC0210014
		opword 0xC0410010
		opword 0xC07E008C
		opword 0xC09E0094
		bl distABf
		opword 0xFFA00890
		bl marioChkSlitThrouh
		opword 0x2C030000
		opword 0x40820010
		opword 0xFC1DF840
		opword 0x4C411382
		opword 0x4082014C
		bl marioChkDeepSleep
		opword 0x2C030000
		opword 0x40820140
		opword 0x7F83E378
		opword 0x38800001
		bl partyChgMot
		opword 0x48000130
		opword 0x887C002F
		opword 0x7C630774
		bl anotherPartyGetPtr
		mr. r27, r3
		opword 0x4182011C
		bl nokonokoGetStatus
		opword 0x2C030003
		opword 0x41820020
		opword 0x387E008C
		opword 0x389B0058
		bl PSVECDistance
		lfs f0, float_150_8041cebc(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820034
		opword 0xC03C0058
		opword 0x7FA3EB78
		opword 0xC05C0060
		bl partyGetTargetDist
		opword 0xFC01F840
		opword 0x4C411382
		opword 0x408200C0
		opword 0x7F83E378
		opword 0x38800001
		bl partyChgMot
		bl partyClearFootmark2
		opword 0x480000AC
		opword 0x887B0031
		opword 0x2C030003
		opword 0x4082005C
		opword 0x881B0034
		opword 0x28000003
		opword 0x40820050
		opword 0xA01E002E
		opword 0x2800001F
		opword 0x41820088
		opword 0x28000010
		opword 0x41820080
		opword 0x28000011
		opword 0x41820078
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC07E008C
		opword 0xC09E0094
		bl distABf
		opword 0xFC01F840
		opword 0x4C411382
		opword 0x40820058
		opword 0x7F83E378
		opword 0x38800001
		bl partyChgMot
		opword 0x48000048
		opword 0x801B0000
		opword 0x540005EF
		opword 0x41820010
		opword 0x7C600774
		opword 0x2C000004
		opword 0x40820030
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC07B0058
		opword 0xC09B0060
		bl distABf
		opword 0xFC01F840
		opword 0x4C411382
		opword 0x40820010
		opword 0x7F83E378
		opword 0x38800001
		bl partyChgMot
		bl marioChkSlitThrouh
		opword 0x2C030000
		opword 0x41820010
		opword 0x7F83E378
		opword 0x38800001
		bl partyChgMot
		opword 0x80DC0058
		opword 0x7F83E378
		opword 0x801C005C
		opword 0x3881000C
		opword 0x38A10008
		opword 0x90C10024
		opword 0x90010028
		opword 0x801C0060
		opword 0x9001002C
		bl partyGetMoveDirSpd
		opword 0xC0210008
		opword 0x7F83E378
		opword 0xC041000C
		opword 0x38810024
		bl partySearchFrontWall
		opword 0x28030000
		opword 0x4182001C
		opword 0x907C012C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC03C0104
		opword 0xFC010000
		opword 0x41820008
		opword 0x907C0134
		opword 0xC0010024
		opword 0x7F83E378
		opword 0x3881000C
		opword 0x38A10008
		opword 0xD01C0058
		opword 0xC001002C
		opword 0xD01C0060
		bl partyGetMoveDirSpd
		opword 0xC0210008
		opword 0x38610024
		opword 0xC041000C
		opword 0x38800001
		opword 0xC07C00F4
		opword 0xC09C00F0
		bl marioChkWallAround
		opword 0xC0010024
		opword 0xD01C0058
		opword 0xC001002C
		opword 0xD01C0060
		opword 0x881C0032
		opword 0x28000001
		opword 0x40820010
		opword 0x7F83E378
		bl unk_8014b824
		opword 0x480000D8
		opword 0x7F83E378
		bl unk_8014ba3c
		opword 0x7F83E378
		bl party_force_reset_outofscreen
		opword 0x881C0031
		opword 0x2C000007
		opword 0x408200BC
		opword 0x801C0004
		opword 0x54000421
		opword 0x408200B0
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x408200A4
		bl marioChkDeepSleep
		opword 0x2C030001
		opword 0x41820098
		bl chuchu_searchObject
		opword 0x2C030000
		opword 0x4182008C
		opword 0x881C0039
		opword 0x2C000001
		opword 0x41820018
		opword 0x40800008
		opword 0x4800005C
		opword 0x2C000003
		opword 0x40800054
		opword 0x48000034
		opword 0x807C0024
		opword 0x3403FFFF
		opword 0x901C0024
		opword 0x4181005C
		opword 0x7F83E378
		opword 0x38800001
		bl partyChgPoseId
		opword 0x3860001E
		opword 0x38000002
		opword 0x907C0024
		opword 0x981C0039
		opword 0x4800003C
		opword 0x807C0024
		opword 0x3403FFFF
		opword 0x901C0024
		opword 0x4181002C
		opword 0x38000000
		opword 0x981C0039
		opword 0x48000020
		opword 0x7F83E378
		opword 0x389F00CC
		bl partyChgPose
		opword 0x38600001
		opword 0x3800001E
		opword 0x987C0039
		opword 0x901C0024
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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
#ifdef NONMATCHING
    if (distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) > 31.0f) {
#endif
#ifndef NONMATCHING
    if (distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) > EXT_LIT(float_31_8041ced4, 31.0f)) {
#endif
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
#ifdef NONMATCHING
    hit = partySearchGround(party, 15.0f, -15.0f);
#endif
#ifndef NONMATCHING
    hit = partySearchGround(party, EXT_LIT(float_15_8041ce60, 15.0f), EXT_LIT(float_neg15_8041cecc, -15.0f));
#endif
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
#ifdef NONMATCHING
        party->unk11C = -1.5f;
#endif
#ifndef NONMATCHING
        party->unk11C = EXT_LIT(float_neg1p5_8041ced0, -1.5f);
#endif
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
#endif
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void unk_8014b824(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x93C10018
		opword 0x93A10014
		opword 0x80030000
		opword 0x83A30160
		opword 0x5400014B
		opword 0x408201D4
		lfs f1, float_10_8041cdd4(r2)
		lfs f2, float_0_8041cdec(r2)
		bl partySearchGround
		opword 0x7C7E1B79
		opword 0x41820044
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820014
		opword 0x7FE3FB78
		opword 0x3880000D
		bl partyChgRunMode
		opword 0x480001A4
		opword 0x546005EF
		opword 0x41820014
		opword 0x801F0000
		opword 0x60000080
		opword 0x901F0000
		opword 0x48000010
		opword 0x801F0000
		opword 0x5400066E
		opword 0x901F0000
		opword 0x807F0160
		opword 0xA8030050
		opword 0x2C000000
		opword 0x4182001C
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0030180
		opword 0xFC010000
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000034
		opword 0xA003002E
		opword 0x2800001F
		opword 0x4182001C
		opword 0x28000020
		opword 0x41820014
		opword 0x28000010
		opword 0x4182000C
		opword 0x28000011
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182009C
		opword 0x281E0000
		lfs f3, float_0p05_8041cea0(r2)
		opword 0x41820044
		opword 0xC01D0090
		opword 0xC03F00E4
		opword 0xFC000840
		opword 0x40810010
		opword 0xFC400090
		lfs f3, float_0p1_8041ce44(r2)
		opword 0x4800000C
		opword 0xFC400890
		lfs f3, float_0p1_8041ce44(r2)
		opword 0xC01F005C
		opword 0xFC000840
		opword 0x40800018
		lfs f0, float_18p5_8041cec8(r2)
		lfs f3, float_0p1_8041ce44(r2)
		opword 0xEC40082A
		opword 0x48000008
		opword 0xC05D0090
		opword 0x801F0004
		lfs f0, float_5_8041ce18(r2)
		opword 0x54000421
		opword 0x41820008
		lfs f0, float_1_8041ce1c(r2)
		opword 0xEC42002A
		opword 0xC03F005C
		lfs f0, float_5_8041ce18(r2)
		opword 0xEC220828
		opword 0xFC010040
		opword 0x41810010
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC000840
		opword 0x40810098
		opword 0xC01F005C
		opword 0xEC0100FA
		opword 0xD01F005C
		opword 0x48000088
		opword 0x281E0000
		opword 0x41820034
		opword 0xC05D0090
		opword 0xC03F00E4
		opword 0xFC020840
		opword 0x40810008
		opword 0x48000008
		opword 0xFC400890
		opword 0xC01F005C
		opword 0xFC000840
		opword 0x40800014
		lfs f0, float_18p5_8041cec8(r2)
		opword 0xEC40082A
		opword 0x48000008
		opword 0xC05F005C
		opword 0x801F0004
		lfs f0, float_5_8041ce18(r2)
		opword 0x54000421
		opword 0x41820008
		lfs f0, float_1_8041ce1c(r2)
		opword 0xEC42002A
		opword 0xC03F005C
		lfs f0, float_5_8041ce18(r2)
		opword 0xEC420828
		opword 0xFC020040
		opword 0x41810010
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC001040
		opword 0x40810014
		lfs f1, float_0p05_8041cea0(r2)
		opword 0xC01F005C
		opword 0xEC02007A
		opword 0xD01F005C
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void party_motion_homing_walk(PartyEntry* party) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[372];
	asm volatile {
		lis r4, vec3_802f3e40@ha
		opword 0x7C7F1B78
		addi r29, r4, vec3_802f3e40@l
		opword 0x3B800000
		bl partyGetFootmarkId
		opword 0x809F0008
		opword 0x7C7B1B78
		opword 0x835F0160
		opword 0x548007BD
		opword 0x41820018
		opword 0x548007FA
		opword 0x901F0008
		opword 0x801F0000
		opword 0x54000356
		opword 0x901F0000
		opword 0xA81F0028
		opword 0x2C000000
		opword 0x4182000C
		lfs f31, float_28_8041cea4(r2)
		opword 0x48000008
		lfs f31, float_37p5_8041ceb4(r2)
		lwz r3, gp(r13)
		opword 0x389D0188
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x41820034
		lwz r3, gp(r13)
		opword 0x389D0190
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		lwz r3, gp(r13)
		opword 0x389D0198
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x40820080
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x40820074
		opword 0x881F0032
		opword 0x28000000
		opword 0x4082000C
		lfs f24, float_18_8041ce20(r2)
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000005
		opword 0x40820020
		opword 0x801F0008
		opword 0x54000295
		opword 0x4182000C
		lfs f24, float_8_8041ce24(r2)
		opword 0x4800002C
		lfs f24, float_30_8041ce28(r2)
		opword 0x48000024
		opword 0x2C000006
		opword 0x4082001C
		opword 0x801F0008
		opword 0x54000295
		opword 0x4182000C
		lfs f24, float_8_8041ce24(r2)
		opword 0x48000008
		lfs f24, float_30_8041ce28(r2)
		opword 0x801F0008
		opword 0xFFE0C090
		opword 0x64000002
		opword 0x901F0008
		opword 0x7F63DB78
		bl partyGetTargetDistY
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x4182000C
		lfs f30, float_50_8041cde8(r2)
		opword 0x48000008
		lfs f30, float_35_8041ceac(r2)
		opword 0x881A003C
		opword 0x2C000002
		opword 0x40820008
		lfs f30, float_70_8041ceb8(r2)
		opword 0x807F0008
		opword 0x54607FFF
		opword 0x41820060
		opword 0x881F0032
		opword 0x28000000
		opword 0x4082000C
		lfs f25, float_18_8041ce20(r2)
		opword 0x48000048
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000005
		opword 0x4082001C
		opword 0x54600295
		opword 0x4182000C
		lfs f25, float_8_8041ce24(r2)
		opword 0x48000028
		lfs f25, float_30_8041ce28(r2)
		opword 0x48000020
		opword 0x2C000006
		opword 0x40820018
		opword 0x54600295
		opword 0x4182000C
		lfs f25, float_8_8041ce24(r2)
		opword 0x48000008
		lfs f25, float_30_8041ce28(r2)
		opword 0xFFC0C890
		opword 0x7FE3FB78
		bl party_slit
		opword 0x2C030000
		opword 0x41820FC0
		opword 0x7FE3FB78
		bl party_roll
		opword 0x2C030000
		opword 0x41820FB0
		opword 0xA01A002E
		opword 0x2800000E
		opword 0x40820020
		opword 0x801F0000
		opword 0x54000319
		opword 0x40820014
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyMoveBehindMario
		opword 0x48000F88
		opword 0x807F0160
		opword 0xA8030050
		opword 0x2C000000
		opword 0x4182001C
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0030180
		opword 0xFC010000
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000034
		opword 0xA003002E
		opword 0x2800001F
		opword 0x4182001C
		opword 0x28000020
		opword 0x41820014
		opword 0x28000010
		opword 0x4182000C
		opword 0x28000011
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x40820014
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0x48000F18
		opword 0x7FE3FB78
		bl partyGetTargetMovespd2
		opword 0x801F0000
		opword 0xFFA00890
		opword 0x54000739
		opword 0x40820060
		opword 0x387A008C
		opword 0x389F0058
		bl PSVECDistance
		lfs f0, float_35_8041ceac(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f29, float_1_8041ce1c(r2)
		opword 0x48000018
		lfs f0, float_50_8041cde8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f29, float_3_8041ce0c(r2)
		opword 0x807F0160
		opword 0x80030000
		opword 0x54000421
		opword 0x4182000C
		lfs f29, float_1_8041ce1c(r2)
		lfs f31, float_100_8041cde0(r2)
		opword 0xFC20E890
		opword 0x7FE3FB78
		bl unk_800c93d0
		opword 0x48000100
		bl marioGetPartyId
		bl partyGetPtr
		mr. r25, r3
		opword 0x418200F0
		opword 0x80990058
		opword 0x8019005C
		stw r4, _af_pad+152(r1)
		opword 0x900100A4
		opword 0x80190060
		opword 0x900100A8
		bl nokonokoGetStatus
		opword 0x2C030003
		opword 0x41820020
		opword 0x387A008C
		opword 0x38990058
		bl PSVECDistance
		lfs f0, float_150_8041cebc(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082005C
		opword 0x387A008C
		opword 0x389F0058
		bl PSVECDistance
		lfs f0, float_35_8041ceac(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f29, float_1_8041ce1c(r2)
		opword 0x48000018
		lfs f0, float_50_8041cde8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f29, float_3_8041ce0c(r2)
		opword 0x807F0160
		opword 0x80030000
		opword 0x54000421
		opword 0x41820008
		lfs f29, float_1_8041ce1c(r2)
		opword 0xFC20E890
		opword 0x7FE3FB78
		bl unk_800c93d0
		opword 0x48000058
		opword 0x38790058
		opword 0x389F0058
		bl PSVECDistance
		lfs f0, float_35_8041ceac(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f29, float_1_8041ce1c(r2)
		opword 0x48000018
		lfs f0, float_50_8041cde8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f29, float_3_8041ce0c(r2)
		opword 0x807F0160
		opword 0x80030000
		opword 0x54000421
		opword 0x41820008
		lfs f29, float_1_8041ce1c(r2)
		opword 0xFC20E890
		opword 0x7FE3FB78
		bl unk_800c93d0
		opword 0xC39F0058
		opword 0x3B200000
		opword 0xC37F005C
		opword 0xC35F0060
		lfs f24, float_40_8041cdf0(r2)
		lfs f25, float_20_8041cdc0(r2)
		opword 0x7F63DB78
		bl partyGetFootmarkPtr
		opword 0x7C7E1B78
		opword 0xFC20E090
		opword 0x80630004
		opword 0xFC40D090
		opword 0x801E0008
		opword 0x90610094
		opword 0x90010098
		opword 0xC0610094
		opword 0x801E000C
		opword 0x9001009C
		opword 0xC081009C
		bl angleABf
		opword 0xD0210044
		opword 0xFC200818
		opword 0x38610018
		opword 0x3881001C
		bl sincosf
		opword 0xD3010168
		opword 0x3861012C
		opword 0xC0410018
		opword 0x38800000
		opword 0xC01F0058
		opword 0xC021001C
		opword 0xEC1900BA
		opword 0x80DD0090
		opword 0x80BD0094
		opword 0x801D0098
		opword 0xD0010138
		opword 0xC01F0060
		opword 0xEC19007A
		opword 0xD0010140
		opword 0xC01F005C
		opword 0xEC19002A
		opword 0x90C10144
		opword 0x90A10148
		opword 0xD001013C
		opword 0x9001014C
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4182000C
		bl hitGetAttr
		opword 0x48000008
		opword 0x38600000
		opword 0x54600529
		opword 0x41820040
		opword 0x7F63DB78
		bl partyNextReadId
		opword 0x7F63DB78
		opword 0x38810094
		bl partyGetReadId2
		opword 0x3B390001
		opword 0x2C19000A
		opword 0x4081FF28
		bl marioGetPtr
		opword 0x8083008C
		opword 0x80030090
		opword 0x90810094
		opword 0x90010098
		opword 0x80030094
		opword 0x9001009C
		opword 0x80BF0058
		opword 0x7F63DB78
		opword 0x801F005C
		opword 0x38810070
		opword 0x90A10070
		opword 0x90010074
		opword 0x801F0060
		opword 0x90010078
		bl partyGetTargetDist3D
		opword 0xFC01F840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC20E890
		opword 0x7FE3FB78
		bl unk_800c93d0
		lfs f0, float_20_8041cdc0(r2)
		opword 0xFC1E0040
		opword 0x40800010
		opword 0xFC20E890
		opword 0x7FE3FB78
		bl unk_800c93d0
		opword 0xFC20E090
		opword 0xC0610094
		opword 0xFC40D090
		opword 0xC081009C
		bl distABf
		opword 0xFF200890
		opword 0xC0610094
		opword 0xFC20E090
		opword 0xC081009C
		opword 0xFC40D090
		bl angleABf
		opword 0xD0210044
		opword 0x801A0000
		opword 0x54000421
		opword 0x41820014
		opword 0xC03F00F4
		opword 0xC01A01B4
		opword 0xEC01002A
		opword 0x48000014
		lfs f2, float_0p5_8041ce00(r2)
		opword 0xC03F00F4
		opword 0xC01F0104
		opword 0xEC02007A
		opword 0xFC190040
		opword 0x40810228
		opword 0x80DD0000
		opword 0x7F63DB78
		opword 0x80BD0004
		opword 0x38810064
		opword 0x801D0008
		opword 0x90C10058
		opword 0x90A1005C
		opword 0x90010060
		opword 0xD3810058
		opword 0xD361005C
		opword 0x80C10058
		opword 0xD3410060
		opword 0x80A1005C
		opword 0x80010060
		opword 0x90C10064
		opword 0x90A10068
		opword 0x9001006C
		bl partyGetTargetDist3D
		opword 0xFF200890
		opword 0xFC19F840
		opword 0x4C411382
		opword 0x40820050
		opword 0x801F0008
		opword 0x5400039D
		opword 0x41820590
		opword 0xEC39F028
		lfs f2, float_0p1_8041ce44(r2)
		lfs f0, float_4_8041ceb0(r2)
		opword 0xEC220072
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_0p5_8041ce00(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f1, float_0_8041cdec(r2)
		opword 0xC01A0180
		opword 0x7FE3FB78
		opword 0xEC20082A
		bl unk_800c9398
		opword 0x48000550
		opword 0x386100A0
		bl marioGetSlitFloorPos
		opword 0x2C030000
		opword 0x4182008C
		lfs f1, float_1p5_8041ce98(r2)
		opword 0x7FE3FB78
		bl unk_800c93d0
		opword 0x7F63DB78
		bl partyNextReadId
		opword 0x386100A0
		bl marioGetSlitFloorPos
		opword 0x2C030000
		opword 0x4182051C
		opword 0x806100A0
		opword 0xFC20E090
		opword 0x800100A8
		opword 0xFC40D090
		opword 0x90610094
		opword 0x806100A4
		opword 0x9001009C
		opword 0xC0610094
		opword 0x90610098
		opword 0xC081009C
		bl distABf
		opword 0xFF600890
		opword 0xC0610094
		opword 0xFC20E090
		opword 0xC081009C
		opword 0xFC40D090
		bl angleABf
		lfs f0, float_5_8041ce18(r2)
		opword 0xD0210044
		opword 0xFC1B0040
		opword 0x4C401382
		opword 0x408204C4
		opword 0x7FE3FB78
		bl partyChgMotSlitFloor
		opword 0x480004B8
		opword 0xFC19F040
		opword 0x40810084
		opword 0x801F0008
		opword 0x5400039D
		opword 0x41820044
		opword 0xEC39F028
		lfs f2, float_0p1_8041ce44(r2)
		lfs f0, float_4_8041ceb0(r2)
		opword 0xEC220072
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_0p5_8041ce00(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f1, float_0_8041cdec(r2)
		opword 0xC01A0180
		opword 0x7FE3FB78
		opword 0xEC20082A
		bl unk_800c9398
		opword 0x48000464
		opword 0xEC39F028
		lfs f2, float_1_8041ce1c(r2)
		opword 0xFC011040
		opword 0x4C411382
		opword 0x40820018
		lfs f0, float_20_8041cdc0(r2)
		opword 0xFC201090
		opword 0xFC1E0040
		opword 0x40800008
		opword 0xFC20E890
		opword 0x7FE3FB78
		bl unk_800c93d0
		opword 0x48000430
		lfs f1, float_0_8041cdec(r2)
		opword 0xC01F00A0
		opword 0xFC010000
		opword 0x40820024
		opword 0xC01F00A8
		opword 0xFC010000
		opword 0x40820018
		opword 0x809F0160
		opword 0x7FE3FB78
		opword 0xC0240180
		bl unk_800c93d0
		opword 0x48000034
		lfs f1, float_0_8041cdec(r2)
		opword 0x7FE3FB78
		bl unk_800c9398
		opword 0xC03F0058
		opword 0xC05F0060
		opword 0xC07A008C
		opword 0xC09A0094
		bl angleABf
		opword 0xD03F0100
		opword 0x7FE3FB78
		opword 0x38800001
		bl partyChgPoseId
		opword 0x7F63DB78
		bl partyGetFootmarkWriteId
		opword 0x7C791B78
		opword 0x7F63DB78
		bl partyGetFootmarkReadId
		opword 0x7C03C800
		opword 0x40820084
		opword 0x809F0160
		opword 0x7FE3FB78
		opword 0xC0240180
		bl unk_800c93d0
		opword 0x807F0160
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0030180
		opword 0xFC010000
		opword 0x4182001C
		opword 0xC01F00A0
		opword 0xFC010000
		opword 0x40820010
		opword 0xC01F00A8
		opword 0xFC010000
		opword 0x41820378
		opword 0xC01F0100
		opword 0x7FE3FB78
		lfs f1, float_0_8041cdec(r2)
		opword 0xD0010044
		bl unk_800c93d0
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01F011C
		opword 0x801F0000
		opword 0x540005AD
		opword 0x40820010
		opword 0x7FE3FB78
		opword 0x38800001
		bl partyChgPoseId
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0x48000334
		opword 0x7F63DB78
		bl partyNextReadId
		opword 0x7F63DB78
		opword 0x38810094
		bl partyGetReadId2
		opword 0x807F0000
		opword 0x5460014B
		opword 0x408200C0
		opword 0x5460066E
		lfs f1, float_10_8041cdd4(r2)
		opword 0x901F0000
		opword 0x7FE3FB78
		lfs f2, float_0_8041cdec(r2)
		bl partySearchGround
		opword 0x7C7C1B79
		opword 0x41820038
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182002C
		opword 0x881F004C
		opword 0x3B800000
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801F0008
		opword 0x64000100
		opword 0x901F0008
		opword 0x801F0000
		opword 0x64000200
		opword 0x901F0000
		opword 0x281C0000
		opword 0x939F0138
		opword 0x4082001C
		opword 0x7FE3FB78
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01F011C
		opword 0x48000048
		opword 0x7F83E378
		bl hitGetAttr
		opword 0x546005EF
		opword 0x41820014
		opword 0x801F0000
		opword 0x60000080
		opword 0x901F0000
		opword 0x48000010
		opword 0x801F0000
		opword 0x5400066E
		opword 0x901F0000
		opword 0x54600529
		opword 0x41820014
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0x48000258
		opword 0x801F0000
		opword 0x540007BD
		opword 0x418201CC
		opword 0x881E0000
		opword 0x540007FF
		opword 0x418201C0
		opword 0xC03F0110
		bl toMovedir
		opword 0xFF000890
		opword 0x7F63DB78
		opword 0x38810038
		opword 0x38A10034
		opword 0x38C10030
		bl partyGetReadId
		opword 0x7F63DB78
		opword 0x38810088
		bl L_getTargetPos
		opword 0xC021008C
		opword 0xC0010034
		opword 0xFC010040
		opword 0x40800008
		opword 0xD0210034
		opword 0xC0010038
		opword 0xFC20C090
		opword 0x38610010
		opword 0x38810014
		opword 0xD01F0094
		opword 0xC0010030
		opword 0xD01F009C
		opword 0xC0010034
		opword 0xD01F0098
		opword 0x80DF0094
		opword 0x80BF0098
		opword 0x801F009C
		opword 0x90C1004C
		lfs f24, touch_wall_ct(r13)
		opword 0x90A10050
		opword 0x90010054
		bl sincosf
		opword 0x80C1004C
		opword 0x386100EC
		opword 0x80A10050
		opword 0x38800000
		opword 0x80010054
		opword 0x90C100F8
		opword 0xC0410010
		opword 0x90A100FC
		lfs f5, float_40_8041cdf0(r2)
		opword 0x90010100
		opword 0xC00100F8
		opword 0xC02100FC
		opword 0xEC82017A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xEC21C02A
		opword 0x80DD0084
		opword 0x80BD0088
		opword 0x801D008C
		opword 0xC0610014
		opword 0xC0410100
		opword 0xD08100F8
		opword 0xEC43117A
		opword 0xD02100FC
		opword 0xD0410100
		opword 0xD0010128
		opword 0x90C10104
		opword 0x90A10108
		opword 0x9001010C
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x41820060
		opword 0xC0210114
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041ce04(r2)
		lfs f2, float_1000_8041cdf4(r2)
		opword 0x3C004330
		opword 0x90010178
		opword 0xEC02007A
		opword 0xC83D0108
		opword 0xFC00001E
		opword 0xD8010170
		opword 0x80010174
		opword 0x6C008000
		opword 0x9001017C
		opword 0xC8010178
		opword 0xEC000828
		opword 0xEF001024
		bl hitGetAttr
		opword 0x48000008
		lfs f24, float_neg2000_8041cdfc(r2)
		opword 0xC01F005C
		opword 0xFC180040
		opword 0x40810044
		opword 0xC03F0110
		opword 0x7FE3FB78
		bl partyToMovedir
		opword 0xD0210044
		opword 0xFC200818
		opword 0x38610040
		opword 0x3881003C
		bl sincosf
		opword 0xC0010040
		lfs f1, float_40_8041cdf0(r2)
		opword 0xEC000072
		opword 0xD01F0094
		opword 0xC001003C
		opword 0xEC000072
		opword 0xD01F009C
		opword 0xD31F0098
		opword 0x7FE3FB78
		opword 0x38800002
		bl partyChgMot
		opword 0x48000084
		opword 0x7F83E378
		bl unk_800c8dd0
		opword 0x2C030000
		opword 0x41820030
		opword 0x7FE3FB78
		opword 0x7F84E378
		opword 0x38BF0094
		bl partyGetAppearPos5
		opword 0x801F0008
		opword 0x7FE3FB78
		opword 0x38800002
		opword 0x64000040
		opword 0x901F0008
		bl partyChgMot
		opword 0x48000048
		opword 0x801F0000
		opword 0x540007BD
		opword 0x4182F9E8
		opword 0x881E0000
		opword 0x5400077B
		opword 0x4182F9DC
		opword 0xFC20E090
		opword 0xC0610094
		opword 0xFC40D090
		opword 0xC081009C
		bl distABf
		lfs f0, float_5_8041ce18(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		opword 0x7FE3FB78
		bl partyChgMotSlitFloor
		opword 0xC03F0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x41820010
		opword 0x7FE3FB78
		bl unk_800c8f24
		opword 0x4800001C
		opword 0x881E0000
		opword 0x5400077B
		opword 0x40820010
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0xC0010044
		opword 0x7FE3FB78
		opword 0x38810044
		opword 0x38A10048
		opword 0xD01F0100
		opword 0x80DF0058
		opword 0x801F005C
		opword 0x90C100A0
		opword 0x900100A4
		opword 0x801F0060
		opword 0x900100A8
		bl partyGetMoveDirSpd
		opword 0xC0210048
		opword 0x7FE3FB78
		opword 0xC0410044
		opword 0x388100A0
		bl partySearchFrontWall
		opword 0x801F0000
		opword 0x540001CF
		opword 0x41820008
		opword 0x38600000
		opword 0x28030000
		opword 0x4082016C
		opword 0x38000000
		opword 0x981F004D
		opword 0x801F0008
		opword 0x54000295
		opword 0x40820018
		opword 0xC03F0100
		opword 0x7FE3FB78
		opword 0x38810094
		bl getFrontFloor
		opword 0x48000024
		lfs f1, float_270_8041ce34(r2)
		opword 0xC01A0198
		opword 0xEC21002A
		bl revise360
		opword 0xD03F0054
		opword 0x7FE3FB78
		opword 0x38810094
		bl partyGetAppearPos4
		opword 0xC0410098
		opword 0xC03F005C
		opword 0xFC020840
		opword 0x40810054
		opword 0xEC620828
		opword 0xC81D01A0
		opword 0xFC030040
		opword 0x40810038
		lfs f0, float_60_8041cec0(r2)
		opword 0xFC030040
		opword 0x4080002C
		opword 0x80A10094
		opword 0x7FE3FB78
		opword 0x80010098
		opword 0x38800002
		opword 0x90BF0094
		opword 0x901F0098
		opword 0x8001009C
		opword 0x901F009C
		bl partyChgMot
		opword 0x480004C4
		opword 0xFC020840
		opword 0x40810008
		opword 0xD05F005C
		opword 0xC03F0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x418202F0
		opword 0xC03F0100
		opword 0x38610008
		opword 0x3881000C
		bl sincosf
		lfs f0, float_100_8041cde0(r2)
		opword 0x386100AC
		opword 0xC0610008
		opword 0x38800000
		opword 0xD00100E8
		lfs f2, float_40_8041cdf0(r2)
		opword 0xC01F0058
		opword 0xC021000C
		opword 0xEC0300BA
		opword 0x80DD009C
		opword 0x80BD00A0
		opword 0x801D00A4
		opword 0xD00100B8
		opword 0xC01F0060
		opword 0xEC0100BA
		opword 0xD00100C0
		opword 0xC01F005C
		opword 0xEC00102A
		opword 0x90C100C4
		opword 0x90A100C8
		opword 0xD00100BC
		opword 0x900100CC
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4182000C
		bl hitGetAttr
		opword 0x48000008
		opword 0x38600000
		opword 0x546005AD
		opword 0x40820268
		opword 0xC01F0058
		opword 0x388100A8
		opword 0x386100A0
		opword 0xD00100A0
		opword 0xC01F0060
		opword 0xD00100A8
		opword 0xC03F0104
		opword 0xC05F0100
		bl movePos
		opword 0x48000240
		opword 0x907F012C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC03F0104
		opword 0xFC010000
		opword 0x4182022C
		opword 0x907F0134
		bl hitGetAttr
		opword 0x546004A5
		opword 0x4182006C
		opword 0x881F0037
		opword 0x28000001
		opword 0x4182002C
		opword 0x807F0160
		opword 0x8003000C
		opword 0x54000001
		opword 0x40820200
		opword 0x807F0008
		opword 0x38000001
		opword 0x60630001
		opword 0x907F0008
		opword 0x981F0037
		opword 0x480001E8
		opword 0xC03F0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x418201D8
		opword 0xC01F0058
		opword 0x388100A8
		opword 0x386100A0
		opword 0xD00100A0
		opword 0xC01F0060
		opword 0xD00100A8
		opword 0xC05F0100
		bl movePos
		opword 0x480001B4
		opword 0x887F004D
		opword 0x38030001
		opword 0x981F004D
		opword 0x881F004D
		opword 0x7C000774
		opword 0x2C000008
		opword 0x40810198
		opword 0x38000000
		opword 0x7F63DB78
		opword 0x981F004D
		opword 0xC03F005C
		bl unk_800c9f48
		lfs f0, float_1_8041ce1c(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x408200CC
		opword 0xC03F0100
		opword 0x7FE3FB78
		opword 0x38810094
		bl getFrontFloor
		opword 0xC0410098
		opword 0xC03F005C
		lfs f0, float_5_8041ce18(r2)
		opword 0xEC220828
		opword 0xFC010040
		opword 0x4081002C
		opword 0x80A10094
		opword 0x7FE3FB78
		opword 0x80010098
		opword 0x38800002
		opword 0x90BF0094
		opword 0x901F0098
		opword 0x8001009C
		opword 0x901F009C
		bl partyChgMot
		opword 0x480002DC
		opword 0x801F0000
		opword 0x540006B7
		opword 0x40820118
		lfs f1, float_11_8041cec4(r2)
		opword 0x7FE3FB78
		opword 0x3881002C
		opword 0x38A10028
		opword 0x38C10024
		bl partyChkFrontStep
		opword 0xC041002C
		opword 0xC03F005C
		lfs f0, float_5_8041ce18(r2)
		opword 0xEC220828
		opword 0xFC010040
		opword 0x4C411382
		opword 0x408200E4
		opword 0xC03F00E0
		lfs f0, float_30_8041ce28(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408200D0
		opword 0xD05F0120
		lfs f0, float_0_8041cdec(r2)
		opword 0xC03F0104
		opword 0xFC010000
		opword 0x418200BC
		opword 0x7FE3FB78
		opword 0x38800006
		bl partyChgMot
		opword 0x48000264
		opword 0xC03F0058
		opword 0x7F63DB78
		opword 0xC05F0060
		bl partyGetTargetDir
		opword 0xD0210044
		opword 0xFC200818
		opword 0x7FE3FB78
		opword 0x38810094
		bl getFrontFloor
		opword 0xC0410098
		opword 0xC03F005C
		lfs f0, float_100_8041cde0(r2)
		opword 0xEC220828
		opword 0xFC010040
		opword 0x4081002C
		opword 0x80A10094
		opword 0x7FE3FB78
		opword 0x80010098
		opword 0x38800001
		opword 0x90BF0058
		opword 0x901F005C
		opword 0x8001009C
		opword 0x901F0060
		bl partyChgMot
		opword 0x48000048
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082002C
		opword 0x80A10094
		opword 0x7FE3FB78
		opword 0x80010098
		opword 0x38800002
		opword 0x90BF0094
		opword 0x901F0098
		opword 0x8001009C
		opword 0x901F009C
		bl partyChgMot
		opword 0x48000010
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0xC00100A0
		opword 0x7FE3FB78
		opword 0x3881007C
		opword 0x38A10020
		opword 0xD01F0058
		opword 0xC00100A8
		opword 0xD01F0060
		opword 0xC01F00F0
		opword 0xD0010020
		opword 0x80DF0058
		opword 0x801F005C
		opword 0x90C1007C
		opword 0x90010080
		opword 0x801F0060
		opword 0x90010084
		opword 0xC03F010C
		bl partySearchHead
		opword 0x28030000
		opword 0x41820008
		opword 0x907F0140
		opword 0x801F0000
		opword 0x7FE3FB78
		lfs f1, float_10_8041cdd4(r2)
		opword 0x5400066E
		opword 0xFC400890
		opword 0x901F0000
		bl partySearchGround
		opword 0xC01F00E4
		opword 0x7C791B79
		opword 0xD00100A4
		opword 0x41820054
		bl hitGetAttr
		opword 0x546005AD
		opword 0x41820030
		opword 0x881F004C
		opword 0x3B200000
		opword 0x7C000775
		opword 0x40820038
		opword 0x801F0008
		opword 0x64000100
		opword 0x901F0008
		opword 0x801F0000
		opword 0x64000200
		opword 0x901F0000
		opword 0x4800001C
		opword 0x54600529
		opword 0x41820014
		opword 0x7FE3FB78
		opword 0x3880000D
		bl partyChgRunMode
		opword 0x480000F0
		opword 0x28190000
		opword 0x933F0138
		opword 0x4082001C
		opword 0x7FE3FB78
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01F011C
		opword 0x48000044
		opword 0x7F23CB78
		bl hitGetAttr
		opword 0x546005EF
		opword 0x41820014
		opword 0x801F0000
		opword 0x60000080
		opword 0x901F0000
		opword 0x48000010
		opword 0x801F0000
		opword 0x5400066E
		opword 0x901F0000
		opword 0x7F23CB78
		bl hitGetAttr
		opword 0x54600043
		opword 0x41820008
		opword 0x933F014C
		opword 0xC00100A4
		opword 0x7FE3FB78
		opword 0xD01F005C
		bl party_force_reset_outofscreen
		lwz r3, gp(r13)
		opword 0x389D00D8
		opword 0x833F0160
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x40820060
		opword 0x807901E4
		opword 0x28030000
		opword 0x41820054
		opword 0x801F0138
		opword 0x28000000
		opword 0x41820048
		bl hitGetName
		opword 0x389D00E0
		bl strcmp
		opword 0x2C030000
		opword 0x40820034
		opword 0x807F0138
		bl hitGetName
		opword 0x389D00F4
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807D00C0
		opword 0x801D00C4
		opword 0x907F0058
		opword 0x901F005C
		opword 0x801D00C8
		opword 0x901F0060
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void party_motion_homing_fly(PartyEntry* party) {
	char _af_pad[152];
	asm volatile {
		opword 0x7C7B1B78
		lis r4, vec3_802f3e40@ha
		opword 0x83C30160
		addi r31, r4, vec3_802f3e40@l
		bl partyGetFootmarkId
		opword 0x809B0008
		opword 0x7C7D1B78
		opword 0x548007BD
		opword 0x41820020
		opword 0x548307FA
		opword 0x38000000
		opword 0x907B0008
		opword 0x807B0000
		opword 0x54630356
		opword 0x907B0000
		opword 0x981B004E
		opword 0xA81B0028
		opword 0x2C000000
		opword 0x4182000C
		lfs f31, float_28_8041cea4(r2)
		opword 0x48000008
		lfs f31, float_32_8041cea8(r2)
		lwz r3, gp(r13)
		opword 0x389F0188
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x41820034
		lwz r3, gp(r13)
		opword 0x389F0190
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		lwz r3, gp(r13)
		opword 0x389F0198
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x40820080
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x40820074
		opword 0x881B0032
		opword 0x28000000
		opword 0x4082000C
		lfs f25, float_18_8041ce20(r2)
		opword 0x48000050
		opword 0x881B0031
		opword 0x7C000774
		opword 0x2C000005
		opword 0x40820020
		opword 0x801B0008
		opword 0x54000295
		opword 0x4182000C
		lfs f25, float_8_8041ce24(r2)
		opword 0x4800002C
		lfs f25, float_30_8041ce28(r2)
		opword 0x48000024
		opword 0x2C000006
		opword 0x4082001C
		opword 0x801B0008
		opword 0x54000295
		opword 0x4182000C
		lfs f25, float_8_8041ce24(r2)
		opword 0x48000008
		lfs f25, float_30_8041ce28(r2)
		opword 0x801B0008
		opword 0xFFE0C890
		opword 0x64000002
		opword 0x901B0008
		opword 0x7FA3EB78
		bl partyGetTargetDistY
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x4182000C
		lfs f30, float_50_8041cde8(r2)
		opword 0x48000008
		lfs f30, float_35_8041ceac(r2)
		opword 0x807B0008
		opword 0x54607FFF
		opword 0x41820060
		opword 0x881B0032
		opword 0x28000000
		opword 0x4082000C
		lfs f26, float_18_8041ce20(r2)
		opword 0x48000048
		opword 0x881B0031
		opword 0x7C000774
		opword 0x2C000005
		opword 0x4082001C
		opword 0x54600295
		opword 0x4182000C
		lfs f26, float_8_8041ce24(r2)
		opword 0x48000028
		lfs f26, float_30_8041ce28(r2)
		opword 0x48000020
		opword 0x2C000006
		opword 0x40820018
		opword 0x54600295
		opword 0x4182000C
		lfs f26, float_8_8041ce24(r2)
		opword 0x48000008
		lfs f26, float_30_8041ce28(r2)
		opword 0xFFC0D090
		opword 0x7F63DB78
		bl party_slit
		opword 0x2C030000
		opword 0x41820A00
		opword 0x7F63DB78
		bl party_roll
		opword 0x2C030000
		opword 0x418209F0
		opword 0xA01E002E
		opword 0x2800000E
		opword 0x40820020
		opword 0x801B0000
		opword 0x54000319
		opword 0x40820014
		opword 0x7F63DB78
		opword 0x38800000
		bl partyMoveBehindMario
		opword 0x480009C8
		opword 0x807B0160
		opword 0xA8030050
		opword 0x2C000000
		opword 0x4182001C
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0030180
		opword 0xFC010000
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000034
		opword 0xA003002E
		opword 0x2800001F
		opword 0x4182001C
		opword 0x28000020
		opword 0x41820014
		opword 0x28000010
		opword 0x4182000C
		opword 0x28000011
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x40820014
		opword 0x7F63DB78
		opword 0x38800000
		bl partyChgMot
		opword 0x48000958
		opword 0x7F63DB78
		bl partyGetTargetMovespd2
		opword 0xFFA00890
		opword 0x387E008C
		opword 0x389B0058
		bl PSVECDistance
		lfs f0, float_35_8041ceac(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f29, float_1_8041ce1c(r2)
		opword 0x48000018
		lfs f0, float_50_8041cde8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f29, float_3_8041ce0c(r2)
		opword 0x807B0160
		opword 0x80030000
		opword 0x54000421
		opword 0x4182000C
		lfs f29, float_1_8041ce1c(r2)
		lfs f31, float_100_8041cde0(r2)
		opword 0xFC20E890
		opword 0x7F63DB78
		bl unk_800c93d0
		opword 0xC39B0058
		opword 0x7FA3EB78
		opword 0xC37B005C
		opword 0xC35B0060
		bl partyGetFootmarkPtr
		opword 0xC0030004
		lfs f1, float_5_8041ce18(r2)
		stfs f0, _af_pad+44(r1)
		opword 0x801B0004
		opword 0x54000421
		opword 0x41820008
		lfs f1, float_1_8041ce1c(r2)
		opword 0xC0030008
		opword 0x38810058
		opword 0xEC00082A
		opword 0xD0010030
		opword 0xC003000C
		opword 0x7FA3EB78
		opword 0xD001002C
		opword 0x80BB0058
		opword 0x801B005C
		opword 0x90A10058
		opword 0x9001005C
		opword 0x801B0060
		opword 0x90010060
		bl partyGetTargetDist3D
		opword 0xFC01F840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC20E890
		opword 0x7F63DB78
		bl unk_800c93d0
		lfs f0, float_20_8041cdc0(r2)
		opword 0xFC1E0040
		opword 0x40800010
		opword 0xFC20E890
		opword 0x7F63DB78
		bl unk_800c93d0
		opword 0x3B800000
		opword 0xFC20E090
		opword 0xC0610034
		opword 0xFC40D090
		opword 0xC081002C
		bl angleABf
		opword 0xD021003C
		opword 0xFC20E090
		opword 0xFC40D090
		opword 0xC0610034
		opword 0xC081002C
		bl distABf
		opword 0x801E0000
		opword 0x54000421
		opword 0x41820014
		opword 0xC05B00F4
		opword 0xC01E01B4
		opword 0xEC02002A
		opword 0x48000014
		lfs f3, float_0p5_8041ce00(r2)
		opword 0xC05B00F4
		opword 0xC01B0104
		opword 0xEC0300BA
		opword 0xFC010040
		opword 0x40810230
		opword 0x80DF000C
		opword 0x7FA3EB78
		opword 0x80BF0010
		opword 0x3881004C
		opword 0x801F0014
		opword 0x90C10040
		opword 0x90A10044
		opword 0x90010048
		opword 0xD3810040
		opword 0xD3610044
		opword 0x80C10040
		opword 0xD3410048
		opword 0x80A10044
		opword 0x80010048
		opword 0x90C1004C
		opword 0x90A10050
		opword 0x90010054
		bl partyGetTargetDist3D
		opword 0xFF200890
		opword 0xFC19F840
		opword 0x4C411382
		opword 0x40820054
		opword 0x801B0008
		opword 0x5400039D
		opword 0x41820040
		opword 0xEC39F028
		lfs f2, float_0p1_8041ce44(r2)
		lfs f0, float_4_8041ceb0(r2)
		opword 0xEC220072
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_0p5_8041ce00(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f1, float_0_8041cdec(r2)
		opword 0xC01E0180
		opword 0x7F63DB78
		opword 0xEC20082A
		bl unk_800c9398
		opword 0x3B800001
		opword 0x480002E0
		opword 0x38610088
		bl marioGetSlitFloorPos
		opword 0x2C030000
		opword 0x41820090
		lfs f1, float_1p5_8041ce98(r2)
		opword 0x7F63DB78
		bl unk_800c93d0
		opword 0x7FA3EB78
		bl partyNextReadId
		opword 0x38610088
		bl marioGetSlitFloorPos
		opword 0x2C030000
		opword 0x418202AC
		opword 0x80010090
		opword 0xFC20E090
		opword 0x80610088
		opword 0xFC40D090
		opword 0x90010084
		opword 0x8001008C
		opword 0xC3210084
		opword 0x9061007C
		opword 0xFC80C890
		opword 0x90010080
		opword 0xC061007C
		bl distABf
		opword 0xFF600890
		opword 0xC061007C
		opword 0xFC20E090
		opword 0xFC40D090
		opword 0xFC80C890
		bl angleABf
		lfs f0, float_5_8041ce18(r2)
		opword 0xD021003C
		opword 0xFC1B0040
		opword 0x4C401382
		opword 0x40820250
		opword 0x7F63DB78
		bl partyChgMotSlitFloor
		opword 0x48000244
		opword 0xFC19F040
		opword 0x40810084
		opword 0x801B0008
		opword 0x5400039D
		opword 0x41820044
		opword 0xEC39F028
		lfs f2, float_0p1_8041ce44(r2)
		lfs f0, float_4_8041ceb0(r2)
		opword 0xEC220072
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_0p5_8041ce00(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f1, float_0_8041cdec(r2)
		opword 0xC01E0180
		opword 0x7F63DB78
		opword 0xEC20082A
		bl unk_800c9398
		opword 0x48000098
		opword 0xEC39F028
		lfs f2, float_1_8041ce1c(r2)
		opword 0xFC011040
		opword 0x4C411382
		opword 0x40820018
		lfs f0, float_20_8041cdc0(r2)
		opword 0xFC201090
		opword 0xFC1E0040
		opword 0x40800008
		opword 0xFC20E890
		opword 0x7F63DB78
		bl unk_800c93d0
		opword 0x480001BC
		lfs f1, float_0_8041cdec(r2)
		opword 0xC01B00A0
		opword 0xFC010000
		opword 0x40820024
		opword 0xC01B00A8
		opword 0xFC010000
		opword 0x40820018
		opword 0x809B0160
		opword 0x7F63DB78
		opword 0xC0240180
		bl unk_800c93d0
		opword 0x48000034
		lfs f1, float_0_8041cdec(r2)
		opword 0x7F63DB78
		bl unk_800c9398
		opword 0xC03B0058
		opword 0xC05B0060
		opword 0xC07E008C
		opword 0xC09E0094
		bl angleABf
		opword 0xD03B0100
		opword 0x7F63DB78
		opword 0x38800001
		bl partyChgPoseId
		opword 0x7FA3EB78
		bl partyGetFootmarkWriteId
		opword 0x7C7A1B78
		opword 0x7FA3EB78
		bl partyGetFootmarkReadId
		opword 0x7C03D000
		opword 0x40820084
		opword 0x809B0160
		opword 0x7F63DB78
		opword 0xC0240180
		bl unk_800c93d0
		opword 0x807B0160
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0030180
		opword 0xFC010000
		opword 0x4182001C
		opword 0xC01B00A0
		opword 0xFC010000
		opword 0x40820010
		opword 0xC01B00A8
		opword 0xFC010000
		opword 0x41820104
		opword 0xC01B0100
		opword 0x7F63DB78
		lfs f1, float_0_8041cdec(r2)
		opword 0xD001003C
		bl unk_800c93d0
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01B011C
		opword 0x801B0000
		opword 0x540005AD
		opword 0x40820010
		opword 0x7F63DB78
		opword 0x38800001
		bl partyChgPoseId
		opword 0x7F63DB78
		opword 0x38800000
		bl partyChgMot
		opword 0x480000C0
		opword 0x7FA3EB78
		bl partyNextReadId
		opword 0x7FA3EB78
		opword 0x38810034
		opword 0x38A10030
		opword 0x38C1002C
		bl partyGetReadId
		opword 0x807B0000
		opword 0x5460014B
		opword 0x4082FCB4
		lfs f1, float_100_8041cde0(r2)
		opword 0x5460066E
		opword 0x901B0000
		opword 0x7F63DB78
		opword 0xFC400890
		bl partySearchGround
		mr. r26, r3
		opword 0x41820014
		bl hitGetAttr
		opword 0x546005AD
		opword 0x41820008
		opword 0x3B400000
		opword 0x281A0000
		opword 0x935B0138
		opword 0x4082001C
		opword 0x7F63DB78
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01B011C
		opword 0x4BFFFC60
		opword 0x7F43D378
		bl hitGetAttr
		opword 0x546005EF
		opword 0x41820014
		opword 0x801B0000
		opword 0x60000080
		opword 0x901B0000
		opword 0x48000010
		opword 0x801B0000
		opword 0x5400066E
		opword 0x901B0000
		opword 0x54600529
		opword 0x4182FC2C
		opword 0x7F63DB78
		opword 0x38800000
		bl partyChgMot
		opword 0xC03B0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x41820010
		opword 0x7F63DB78
		bl unk_800c8f24
		opword 0x48000010
		opword 0x7F63DB78
		opword 0x38800000
		bl partyChgMot
		opword 0x881B004E
		opword 0x7C000774
		opword 0x2C00000A
		opword 0x4081001C
		opword 0xC03B0058
		opword 0xC05B0060
		opword 0xC07E008C
		opword 0xC09E0094
		bl angleABf
		opword 0xD021003C
		opword 0x2C1C0000
		opword 0x418200A0
		opword 0x839B0160
		opword 0x7F63DB78
		opword 0x38810070
		bl partyGetAppearPos3
		opword 0xC03B0058
		opword 0xC05B0060
		opword 0xC0610070
		opword 0xC0810078
		bl angleABf
		opword 0xD021003C
		opword 0x7F63DB78
		lfs f1, float_10_8041cdd4(r2)
		lfs f2, float_0_8041cdec(r2)
		bl partySearchGround
		opword 0xC01B00E4
		opword 0x7C7A1B79
		opword 0xD0010074
		opword 0x41820014
		bl hitGetAttr
		opword 0x546005AD
		opword 0x41820008
		opword 0x3B400000
		opword 0x281A0000
		opword 0x41820010
		opword 0xC0010074
		opword 0xD01B005C
		opword 0x48000034
		opword 0x801B0004
		lfs f2, float_5_8041ce18(r2)
		opword 0x54000421
		opword 0x41820008
		lfs f2, float_1_8041ce1c(r2)
		opword 0xC01C0090
		opword 0xC03B005C
		opword 0xEC00102A
		lfs f2, float_0p05_8041cea0(r2)
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01B005C
		opword 0xC001003C
		opword 0x7F63DB78
		opword 0x3881003C
		opword 0x38A10038
		opword 0xD01B0100
		opword 0x80DB0058
		opword 0x801B005C
		opword 0x90C10088
		opword 0x9001008C
		opword 0x801B0060
		opword 0x90010090
		bl partyGetMoveDirSpd
		opword 0xC0210038
		opword 0x7F63DB78
		opword 0xC041003C
		opword 0x38810088
		bl partySearchFrontWall
		opword 0x801B0000
		opword 0x540001CF
		opword 0x41820008
		opword 0x38600000
		opword 0x28030000
		opword 0x408200C0
		opword 0x801B0008
		opword 0x54000295
		opword 0x40820018
		opword 0xC03B0100
		opword 0x7F63DB78
		opword 0x38810064
		bl getFrontFloor
		opword 0x48000024
		lfs f1, float_270_8041ce34(r2)
		opword 0xC01E0198
		opword 0xEC21002A
		bl revise360
		opword 0xD03B0054
		opword 0x7F63DB78
		opword 0x38810064
		bl partyGetAppearPos4
		opword 0xC0210068
		opword 0xC01E0090
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820030
		opword 0x801B0004
		lfs f0, float_5_8041ce18(r2)
		opword 0x54000421
		opword 0x41820008
		lfs f0, float_1_8041ce1c(r2)
		opword 0xEC01002A
		opword 0xC03B005C
		lfs f2, float_0p05_8041cea0(r2)
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01B005C
		opword 0x38000000
		lfs f0, float_0_8041cdec(r2)
		opword 0x981B004E
		opword 0xC03B0104
		opword 0xFC010000
		opword 0x41820210
		opword 0xC01B0058
		opword 0x38810090
		opword 0x38610088
		opword 0xD0010088
		opword 0xC01B0060
		opword 0xD0010090
		opword 0xC05B0100
		bl movePos
		opword 0x480001EC
		opword 0x907B012C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC03B0104
		opword 0xFC010000
		opword 0x418201D8
		opword 0x907B0134
		bl hitGetAttr
		opword 0x546004A5
		opword 0x4182006C
		opword 0x881B0037
		opword 0x28000001
		opword 0x4182002C
		opword 0x807B0160
		opword 0x8003000C
		opword 0x54000001
		opword 0x408201AC
		opword 0x807B0008
		opword 0x38000001
		opword 0x60630001
		opword 0x907B0008
		opword 0x981B0037
		opword 0x48000194
		opword 0xC03B0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x41820184
		opword 0xC01B0058
		opword 0x38810090
		opword 0x38610088
		opword 0xD0010088
		opword 0xC01B0060
		opword 0xD0010090
		opword 0xC05B0100
		bl movePos
		opword 0x48000160
		opword 0xC01B0058
		opword 0x38610028
		opword 0xC041003C
		opword 0x38810024
		opword 0xD0010028
		opword 0xC33B005C
		opword 0xC01B0060
		opword 0xD0010024
		opword 0xC03B00F4
		bl movePos
		lfs f0, touch_wall_ct(r13)
		opword 0x38810008
		lfs f4, float_0_8041cdec(r2)
		opword 0x38A1000C
		opword 0xEC59002A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xFCC02090
		opword 0xC0210028
		opword 0xD0010014
		opword 0x38C10010
		opword 0xC0610024
		opword 0x38E10014
		lfs f5, float_neg1_8041cdf8(r2)
		opword 0x39010018
		opword 0x3921001C
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4082000C
		lfs f25, float_neg2000_8041cdfc(r2)
		opword 0x48000044
		lfs f2, float_100_8041cde0(r2)
		opword 0x3C004330
		opword 0xC021000C
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x900100A0
		opword 0xEC02007A
		opword 0xC83F0108
		opword 0xFC00001E
		opword 0xD8010098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEF201024
		bl hitGetAttr
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC190040
		opword 0x40810024
		opword 0xC01B00F0
		opword 0xC03B005C
		opword 0xEC19002A
		lfs f2, float_0p05_8041cea0(r2)
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01B005C
		opword 0x48000074
		opword 0x889B004E
		opword 0x7FA3EB78
		opword 0x38040001
		opword 0x981B004E
		opword 0xC03B005C
		bl unk_800c9f48
		lfs f0, float_1_8041ce1c(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082004C
		opword 0xC07E0090
		opword 0xC05B005C
		lfs f0, float_10_8041cdd4(r2)
		opword 0xEC231028
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082002C
		opword 0xEC00182A
		lfs f1, float_0p1_8041ce44(r2)
		opword 0xEC001028
		opword 0xEC01103A
		opword 0xD01B005C
		opword 0xC0010088
		opword 0xD01B0058
		opword 0xC0010090
		opword 0xD01B0060
		opword 0x48000080
		opword 0xC0010088
		opword 0x7F63DB78
		lfs f1, float_10_8041cdd4(r2)
		opword 0xD01B0058
		opword 0xFC400890
		opword 0xC0010090
		opword 0xD01B0060
		opword 0x801B0000
		opword 0x5400066E
		opword 0x901B0000
		bl partySearchGround
		opword 0x28030000
		opword 0x41820044
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820014
		opword 0x7F63DB78
		opword 0x3880000D
		bl partyChgRunMode
		opword 0x48000030
		opword 0x546005EF
		opword 0x41820014
		opword 0x801B0000
		opword 0x60000080
		opword 0x901B0000
		opword 0x48000010
		opword 0x801B0000
		opword 0x5400066E
		opword 0x901B0000
		opword 0x7F63DB78
		bl party_force_reset_outofscreen
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
#endif

void party_set_behind_dir(PartyEntry* party, f32 dir) {
    party->unk54 = revise360(dir + ((PartyCamView*)camGetPtr((CameraId)4))->unk114);
    party->flags3 |= 0x100000;
}

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void party_motion_behind_mario(PartyEntry* party) {
#ifdef NONMATCHING
    PartyMarioView* mario = party->playerPtr;
    HitEntry* hit;
    f32 ang;
    f32 gy;
    f32 dist;
    f32 thr;
    f32 ty;
    f32 x, z;
    Vec target;
#endif
#ifndef NONMATCHING
	char _af_pad[116];
	asm volatile {
		opword 0x7C7E1B78
		opword 0x80630008
		opword 0x83FE0160
		opword 0x546007BD
		opword 0x418200F0
		opword 0x546007FA
		opword 0x901E0008
		opword 0x801E0008
		opword 0x64000004
		opword 0x901E0008
		opword 0x807E0008
		opword 0x546002D7
		opword 0x4082008C
		opword 0x546003DF
		opword 0x40820058
		opword 0x801E0000
		lwz r29, 0x160(r30)
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC21002A
		bl revise360
		opword 0x4800002C
		opword 0x5460041C
		opword 0x901E0008
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC07E0094
		opword 0xC09E009C
		bl angleABf
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC20082A
		bl revise360
		opword 0xD03E0054
		opword 0x7FC3F378
		la r4, _af_pad+92
		bl partyGetAppearPos4
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610064
		opword 0xC081006C
		bl distABf
		opword 0xFC00081E
		opword 0xD8010070
		opword 0x80010074
		opword 0x901E0024
		opword 0x801E0024
		opword 0x2C000000
		opword 0x4181000C
		opword 0x38000001
		opword 0x901E0024
		opword 0x801E0008
		opword 0x540002D7
		opword 0x40820064
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x41820058
		opword 0x801E0000
		opword 0x83BE0160
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03E0054
		opword 0x7FC3F378
		opword 0x38810064
		bl partyGetAppearPos4
		opword 0xC0610064
		opword 0xC081006C
		opword 0xD0610060
		opword 0xC3C10068
		opword 0xD081005C
		opword 0xC03E0058
		opword 0xC05E0060
		bl angleABf
		lfs f0, touch_wall_ct(r13)
		opword 0xFFE00890
		lfs f4, float_0_8041cdec(r2)
		opword 0x38810040
		opword 0xEC5E002A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xFCC02090
		opword 0xD001004C
		opword 0x38A10044
		opword 0xC0210060
		opword 0xC061005C
		opword 0x38C10048
		lfs f5, float_neg1_8041cdf8(r2)
		opword 0x38E1004C
		opword 0x39010050
		opword 0x39210054
		opword 0x39410058
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4082000C
		lfs f29, float_neg2000_8041cdfc(r2)
		opword 0x48000048
		lfs f2, float_100_8041cde0(r2)
		opword 0x3C004330
		opword 0xC0210044
		lis r4, double_to_int_802f3f48@ha
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x90010078
		opword 0xEC02007A
		lfd f1, double_to_int_802f3f48@l(r4)
		opword 0xFC00001E
		opword 0xD8010070
		opword 0x80010074
		opword 0x6C008000
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC000828
		opword 0xEFA01024
		bl hitGetAttr
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC1D0040
		opword 0x4C401382
		opword 0x4082002C
		lfs f2, float_1p5_8041ce98(r2)
		opword 0xC01F01B4
		opword 0xC03F01A8
		opword 0xEFA20032
		bl toMovedir
		opword 0xFC400890
		opword 0x38610060
		opword 0xFC20E890
		opword 0x3881005C
		bl movePos
		opword 0xC03F0180
		lfs f0, float_1_8041ce1c(r2)
		lfs f28, float_2_8041ce08(r2)
		opword 0xFC010040
		opword 0x40810008
		lfs f28, float_10_8041cdd4(r2)
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610060
		opword 0xC081005C
		bl distABf
		opword 0xFFA00890
		opword 0x807E0024
		opword 0x3803FFFF
		opword 0xFC1DE040
		opword 0x901E0024
		opword 0x4C411382
		opword 0x40820320
		opword 0x801E0024
		opword 0x2C000000
		opword 0x40810314
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610060
		opword 0xC081005C
		bl angleABf
		opword 0xD03E0100
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610060
		opword 0xC081005C
		bl distABf
		opword 0x801E0008
		opword 0x7FC3F378
		opword 0x540002D7
		opword 0x4182000C
		lfs f1, float_3p6_8041ce9c(r2)
		opword 0x48000008
		lfs f1, float_2_8041ce08(r2)
		bl unk_800c9398
		opword 0x7FC3F378
		bl partyMoveCheckWall
		opword 0xC03E0104
		opword 0x7FC3F378
		bl unk_800c8f24
		opword 0x801E012C
		opword 0x28000000
		opword 0x41820114
		opword 0xC01E0058
		opword 0xFC20E890
		opword 0xFC40F890
		opword 0x38610060
		opword 0xD0010060
		opword 0x3881005C
		opword 0xC01E0060
		opword 0xD001005C
		bl movePos
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610060
		opword 0xC081005C
		bl angleABf
		lfs f0, touch_wall_ct(r13)
		opword 0x38810024
		lfs f4, float_0_8041cdec(r2)
		opword 0x38A10028
		opword 0xEC5E002A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xFCC02090
		opword 0xC0210060
		opword 0xD0010030
		opword 0x38C1002C
		opword 0xC061005C
		opword 0x38E10030
		lfs f5, float_neg1_8041cdf8(r2)
		opword 0x39010034
		opword 0x39210038
		opword 0x3941003C
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4082000C
		lfs f28, float_neg2000_8041cdfc(r2)
		opword 0x48000048
		lfs f2, float_100_8041cde0(r2)
		opword 0x3C004330
		opword 0xC0210028
		lis r4, double_to_int_802f3f48@ha
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x90010070
		opword 0xEC02007A
		lfd f1, double_to_int_802f3f48@l(r4)
		opword 0xFC00001E
		opword 0xD8010078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xEF801024
		bl hitGetAttr
		opword 0xC03E005C
		lfs f0, float_1_8041ce1c(r2)
		opword 0xEC21E028
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810144
		opword 0xC0010060
		opword 0x7FC3F378
		opword 0x38800002
		opword 0xD01E0094
		opword 0xD39E0098
		opword 0xC001005C
		opword 0xD01E009C
		bl partyChgMot
		opword 0x48000274
		opword 0xC01E005C
		opword 0xFC1E0040
		opword 0x40810114
		opword 0xC01E0058
		opword 0xFC20E890
		opword 0xFC40F890
		opword 0x38610060
		opword 0xD0010060
		opword 0x3881005C
		opword 0xC01E0060
		opword 0xD001005C
		bl movePos
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610060
		opword 0xC081005C
		bl angleABf
		lfs f0, touch_wall_ct(r13)
		opword 0x38810008
		lfs f4, float_0_8041cdec(r2)
		opword 0x38A1000C
		opword 0xEC5E002A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xFCC02090
		opword 0xC0210060
		opword 0xD0010014
		opword 0x38C10010
		opword 0xC061005C
		opword 0x38E10014
		lfs f5, float_neg1_8041cdf8(r2)
		opword 0x39010018
		opword 0x3921001C
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4082000C
		lfs f28, float_neg2000_8041cdfc(r2)
		opword 0x48000048
		lfs f2, float_100_8041cde0(r2)
		opword 0x3C004330
		opword 0xC021000C
		lis r4, double_to_int_802f3f48@ha
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x90010070
		opword 0xEC02007A
		lfd f1, double_to_int_802f3f48@l(r4)
		opword 0xFC00001E
		opword 0xD8010078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xEF801024
		bl hitGetAttr
		opword 0xC03E005C
		lfs f0, float_1_8041ce1c(r2)
		opword 0xEC21E028
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810028
		opword 0xC0010060
		opword 0x7FC3F378
		opword 0x38800002
		opword 0xD01E0094
		opword 0xD39E0098
		opword 0xC001005C
		opword 0xD01E009C
		bl partyChgMot
		opword 0x48000158
		lfs f1, float_10_8041cdd4(r2)
		opword 0x7FC3F378
		lfs f2, float_0_8041cdec(r2)
		bl partySearchGround
		opword 0x7C7D1B79
		opword 0x41820038
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182002C
		opword 0x881E004C
		opword 0x3BA00000
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801E0008
		opword 0x64000100
		opword 0x901E0008
		opword 0x801E0000
		opword 0x64000200
		opword 0x901E0000
		opword 0x281D0000
		opword 0x93BE0138
		opword 0x40820018
		opword 0x7FC3F378
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01E011C
		opword 0xC01E00E4
		opword 0xD01E005C
		opword 0x48000080
		opword 0x38000000
		opword 0x901E0024
		opword 0x807E0008
		opword 0x54600295
		opword 0x4182000C
		opword 0x546003DA
		opword 0x901E0008
		opword 0x7FC3F378
		opword 0x38800001
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC03F008C
		opword 0x7FC3F378
		opword 0xC05F0094
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		opword 0x801E0000
		opword 0x64000008
		opword 0x901E0000
		opword 0x801E0008
		opword 0x54000314
		opword 0x901E0008
		opword 0x801E0008
		opword 0x54000398
		opword 0x901E0008
		opword 0x801E0134
		opword 0x28000000
		opword 0x41820058
		opword 0x801E0000
		opword 0x7FC3F378
		opword 0x38800001
		opword 0x64000008
		opword 0x901E0000
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC0210060
		opword 0x7FC3F378
		opword 0xC041005C
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		opword 0x801E0008
		opword 0x54000398
		opword 0x901E0008
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void party_motion_behind_mario_continue(PartyEntry* party) {
	char _af_pad[52];
	asm volatile {
		opword 0x80030000
		opword 0x7C7E1B78
		opword 0x83E30160
		opword 0x54000739
		opword 0x40820010
		opword 0xC03F01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03F01A8
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03E0054
		opword 0x807E0008
		opword 0x546007BD
		opword 0x41820070
		opword 0x546007FA
		lfs f2, float_1p5_8041ce98(r2)
		opword 0x901E0008
		la r3, _af_pad+32
		opword 0x38810024
		opword 0xC03F01B4
		opword 0xC01F008C
		opword 0xEC220072
		opword 0xD0010028
		opword 0xC01F0094
		opword 0xD0010024
		opword 0xC05E0054
		bl movePos
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl distABf
		opword 0xFC00081E
		opword 0xD8010030
		opword 0x80010034
		opword 0x901E0024
		opword 0x801E0024
		opword 0x2C000000
		opword 0x4181000C
		opword 0x38000001
		opword 0x901E0024
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x41820058
		opword 0x801E0000
		lwz r29, 0x160(r30)
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03E0054
		opword 0x801E0000
		opword 0x54000739
		opword 0x40820028
		opword 0xC03F01B4
		opword 0xC01F008C
		lfs f2, float_1p5_8041ce98(r2)
		opword 0xD0010028
		opword 0xEFE20072
		opword 0xC01F0094
		opword 0xD0010024
		opword 0xC3DF0090
		opword 0x48000050
		lfs f1, float_1p5_8041ce98(r2)
		opword 0xC01F01B4
		opword 0x887E002F
		opword 0xEFE10032
		opword 0x7C630774
		bl anotherPartyGetPtr
		opword 0x28030000
		opword 0x4182001C
		opword 0xC0030058
		opword 0xD0010028
		opword 0xC0030060
		opword 0xD0010024
		opword 0xC3C3005C
		opword 0x48000018
		opword 0xC01F008C
		opword 0xD0010028
		opword 0xC01F0094
		opword 0xD0010024
		opword 0xC3DF0090
		opword 0xFC20F890
		opword 0xC05E0054
		opword 0x38610028
		opword 0x38810024
		bl movePos
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl angleABf
		lfs f0, touch_wall_ct(r13)
		opword 0x38810008
		lfs f4, float_0_8041cdec(r2)
		opword 0x38A1000C
		opword 0xEC5E002A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xFCC02090
		opword 0xC0210028
		opword 0xD0010014
		opword 0x38C10010
		opword 0xC0610024
		opword 0x38E10014
		lfs f5, float_neg1_8041cdf8(r2)
		opword 0x39010018
		opword 0x3921001C
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4082000C
		lfs f30, float_neg2000_8041cdfc(r2)
		opword 0x48000048
		lfs f2, float_100_8041cde0(r2)
		opword 0x3C004330
		opword 0xC021000C
		lis r4, double_to_int_802f3f48@ha
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x90010038
		opword 0xEC02007A
		lfd f1, double_to_int_802f3f48@l(r4)
		opword 0xFC00001E
		opword 0xD8010030
		opword 0x80010034
		opword 0x6C008000
		opword 0x9001003C
		opword 0xC8010038
		opword 0xEC000828
		opword 0xEFC01024
		bl hitGetAttr
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC1E0040
		opword 0x4C401382
		opword 0x4082002C
		lfs f2, float_1p5_8041ce98(r2)
		opword 0xC01F01B4
		opword 0xC03F01A8
		opword 0xEFE20032
		bl toMovedir
		opword 0xFC400890
		opword 0x38610028
		opword 0xFC20F890
		opword 0x38810024
		bl movePos
		opword 0xC03F0180
		lfs f0, float_1_8041ce1c(r2)
		lfs f30, float_2_8041ce08(r2)
		opword 0xFC010040
		opword 0x40810008
		lfs f30, float_10_8041cdd4(r2)
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl distABf
		opword 0x807E0024
		opword 0xFC01F040
		opword 0x3803FFFF
		opword 0x901E0024
		opword 0x4C411382
		opword 0x408200EC
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl angleABf
		opword 0xD03E0100
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl distABf
		lfs f2, float_10_8041cdd4(r2)
		lfs f0, float_2_8041ce08(r2)
		opword 0xEC211024
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_1_8041ce1c(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0xFC200090
		opword 0x7FC3F378
		bl unk_800c9398
		opword 0x7FC3F378
		bl partyMoveCheckWall
		opword 0xC03E0104
		opword 0x7FC3F378
		bl unk_800c8f24
		lfs f1, float_10_8041cdd4(r2)
		opword 0x7FC3F378
		lfs f2, float_0_8041cdec(r2)
		bl partySearchGround
		opword 0x7C7D1B79
		opword 0x41820038
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182002C
		opword 0x881E004C
		opword 0x3BA00000
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801E0008
		opword 0x64000100
		opword 0x901E0008
		opword 0x801E0000
		opword 0x64000200
		opword 0x901E0000
		opword 0x281D0000
		opword 0x93BE0138
		opword 0x40820018
		opword 0x7FC3F378
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01E011C
		opword 0xC01E00E4
		opword 0xD01E005C
		opword 0x48000064
		opword 0x38000000
		lfs f1, float_0_8041cdec(r2)
		opword 0x901E0024
		opword 0xC01F0180
		opword 0xFC010000
		opword 0x4082004C
		opword 0x801E0000
		opword 0x7FC3F378
		opword 0x38800001
		opword 0x64000008
		opword 0x901E0000
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC03F008C
		opword 0x7FC3F378
		opword 0xC05F0094
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		opword 0x801E0134
		opword 0x28000000
		opword 0x41820040
		opword 0x7FC3F378
		opword 0x38800001
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC0210028
		opword 0x7FC3F378
		opword 0xC0410024
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void party_motion_behind_mario_fly(PartyEntry* party) {
	char _af_pad[36];
	asm volatile {
		opword 0x7C7E1B78
		opword 0x80630008
		opword 0x83FE0160
		opword 0x546007BD
		opword 0x418200F0
		opword 0x546007FA
		opword 0x901E0008
		opword 0x801E0008
		opword 0x64000004
		opword 0x901E0008
		opword 0x807E0008
		opword 0x546002D7
		opword 0x4082008C
		opword 0x546003DF
		opword 0x40820058
		opword 0x801E0000
		lwz r29, 0x160(r30)
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC21002A
		bl revise360
		opword 0x4800002C
		opword 0x5460041C
		opword 0x901E0008
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC07E0094
		opword 0xC09E009C
		bl angleABf
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC20082A
		bl revise360
		opword 0xD03E0054
		opword 0x7FC3F378
		opword 0x389E0094
		bl partyGetAppearPos4
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl distABf
		opword 0xFC00081E
		stfd f0, _af_pad+24(r1)
		opword 0x80010024
		opword 0x901E0024
		opword 0x801E0024
		opword 0x2C000000
		opword 0x4181000C
		opword 0x38000001
		opword 0x901E0024
		opword 0x801E0008
		opword 0x540002D7
		opword 0x40820064
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x41820058
		opword 0x801E0000
		opword 0x83BE0160
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03E0054
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl angleABf
		opword 0xC03F0180
		lfs f0, float_1_8041ce1c(r2)
		opword 0xFC010040
		opword 0x4081000C
		lfs f30, float_6_8041ce30(r2)
		opword 0x48000008
		lfs f30, float_2_8041ce08(r2)
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl distABf
		opword 0xFFE00890
		opword 0x807E0024
		opword 0x3803FFFF
		opword 0xFC1FF040
		opword 0x901E0024
		opword 0x4C411382
		opword 0x41820020
		opword 0xC05E0098
		opword 0xC03E005C
		lfs f0, float_2_8041ce08(r2)
		opword 0xEC220828
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4081010C
		opword 0x801E0024
		opword 0x2C000000
		opword 0x40810100
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl angleABf
		opword 0xD03E0100
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl distABf
		opword 0x801E0008
		opword 0x540002D7
		opword 0x4182000C
		lfs f29, float_3p6_8041ce9c(r2)
		opword 0x48000008
		lfs f29, float_2_8041ce08(r2)
		opword 0xFC1FF040
		opword 0x40800014
		lfs f29, float_0_8041cdec(r2)
		opword 0x7FC3F378
		opword 0xFC20E890
		bl unk_800c9398
		opword 0xFC20E890
		opword 0x7FC3F378
		bl unk_800c93d0
		opword 0x80DE0058
		opword 0x7FC3F378
		opword 0x801E005C
		opword 0x38810008
		opword 0x38A1000C
		opword 0x90C10010
		opword 0x90010014
		opword 0x801E0060
		opword 0x90010018
		bl partyGetMoveDirSpd
		opword 0xC021000C
		opword 0x7FC3F378
		opword 0xC0410008
		opword 0x38810010
		bl partySearchFrontWall
		opword 0x28030000
		opword 0x4182001C
		opword 0x907E012C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC03E0104
		opword 0xFC010000
		opword 0x41820008
		opword 0x907E0134
		opword 0xC0010010
		opword 0x7FC3F378
		lfs f2, float_0p05_8041cea0(r2)
		opword 0xD01E0058
		opword 0xC0010018
		opword 0xD01E0060
		opword 0xC01E0098
		opword 0xC03E005C
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01E005C
		opword 0xC03E0104
		bl unk_800c8f24
		opword 0x48000184
		opword 0x38000000
		opword 0x901E0024
		opword 0x807E0008
		opword 0x54600295
		opword 0x41820024
		opword 0x546003DA
		opword 0x901E0008
		opword 0x881E0032
		opword 0x28000001
		opword 0x40820010
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		opword 0x7FC3F378
		opword 0x38800001
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC03F008C
		opword 0x7FC3F378
		opword 0xC05F0094
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0x7FC3F378
		lfs f1, float_0_8041cdec(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		bl unk_800c9398
		opword 0x801E0000
		opword 0x7FC3F378
		opword 0x64000008
		opword 0x901E0000
		opword 0x801E0008
		opword 0x54000314
		opword 0x901E0008
		opword 0x801E0008
		opword 0x54000398
		opword 0x901E0008
		bl unk_800c8e74
		opword 0x801E0134
		opword 0x28000000
		opword 0x41820058
		opword 0x801E0000
		opword 0x7FC3F378
		opword 0x38800001
		opword 0x64000008
		opword 0x901E0000
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC03F008C
		opword 0x7FC3F378
		opword 0xC05F0094
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		opword 0x801E0008
		opword 0x54000398
		opword 0x901E0008
		lfs f1, float_100_8041cde0(r2)
		opword 0x7FC3F378
		opword 0xFC400890
		bl partySearchGround
		opword 0x7C7D1B79
		opword 0x41820060
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182002C
		opword 0x881E004C
		opword 0x3BA00000
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801E0008
		opword 0x64000100
		opword 0x901E0008
		opword 0x801E0000
		opword 0x64000200
		opword 0x901E0000
		opword 0xC01E00F0
		opword 0xFC1F0040
		opword 0x40810008
		opword 0x3BA00000
		opword 0xC01E00E4
		opword 0xC03E005C
		lfs f2, float_0p05_8041cea0(r2)
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01E005C
		opword 0x93BE0138
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void party_motion_beside_mario(PartyEntry* party) {
	char _af_pad[52];
	asm volatile {
		opword 0x7C7E1B78
		opword 0x80630008
		opword 0x83FE0160
		opword 0x546007BD
		opword 0x418200C4
		opword 0x546007FA
		opword 0x901E0008
		opword 0x801E0000
		lwz r29, 0x160(r30)
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_90_8041ce48(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03E0054
		la r3, _af_pad+32
		lfs f2, float_1p5_8041ce98(r2)
		opword 0x38810024
		opword 0xC03F01B4
		opword 0xC01F008C
		opword 0xEC220072
		opword 0xD0010028
		opword 0xC01F0094
		opword 0xD0010024
		opword 0xC05E0054
		bl movePos
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl distABf
		opword 0xFC00081E
		opword 0xD8010030
		opword 0x80010034
		opword 0x901E0024
		opword 0x801E0024
		opword 0x2C000000
		opword 0x4181000C
		opword 0x38000001
		opword 0x901E0024
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x41820058
		opword 0x801E0000
		opword 0x83BE0160
		opword 0x54000739
		opword 0x40820010
		opword 0xC03D01A8
		bl toMovedir
		opword 0x4800002C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820014
		opword 0xC023010C
		opword 0x7FC3F378
		bl partyToMovedir
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		lfs f0, float_90_8041ce48(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03E0054
		opword 0xC03F01B4
		opword 0x38610028
		opword 0xC01F008C
		opword 0x38810024
		lfs f2, float_1p5_8041ce98(r2)
		opword 0xD0010028
		opword 0xEC220072
		opword 0xC01F0094
		opword 0xD0010024
		opword 0xC3FF0090
		opword 0xC05E0054
		bl movePos
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl angleABf
		lfs f0, touch_wall_ct(r13)
		opword 0x38810008
		lfs f4, float_0_8041cdec(r2)
		opword 0x38A1000C
		opword 0xEC5F002A
		lfs f0, float_1000_8041cdf4(r2)
		opword 0xFCC02090
		opword 0xC0210028
		opword 0xD0010014
		opword 0x38C10010
		opword 0xC0610024
		opword 0x38E10014
		lfs f5, float_neg1_8041cdf8(r2)
		opword 0x39010018
		opword 0x3921001C
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4082000C
		lfs f31, float_neg2000_8041cdfc(r2)
		opword 0x48000048
		lfs f2, float_100_8041cde0(r2)
		opword 0x3C004330
		opword 0xC021000C
		lis r4, double_to_int_802f3f48@ha
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x90010038
		opword 0xEC02007A
		lfd f1, double_to_int_802f3f48@l(r4)
		opword 0xFC00001E
		opword 0xD8010030
		opword 0x80010034
		opword 0x6C008000
		opword 0x9001003C
		opword 0xC8010038
		opword 0xEC000828
		opword 0xEFE01024
		bl hitGetAttr
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC1F0040
		opword 0x4C401382
		opword 0x4082003C
		opword 0xC03F01B4
		opword 0xC01F008C
		lfs f2, float_1p5_8041ce98(r2)
		opword 0xD0010028
		opword 0xEFE20072
		opword 0xC01F0094
		opword 0xD0010024
		opword 0xC03F01A8
		bl toMovedir
		opword 0xFC400890
		opword 0x38610028
		opword 0xFC20F890
		opword 0x38810024
		bl movePos
		opword 0xC03F0180
		lfs f0, float_1_8041ce1c(r2)
		lfs f31, float_2_8041ce08(r2)
		opword 0xFC010040
		opword 0x40810008
		lfs f31, float_10_8041cdd4(r2)
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl distABf
		opword 0x807E0024
		opword 0xFC01F840
		opword 0x3803FFFF
		opword 0x901E0024
		opword 0x4C411382
		opword 0x408200F8
		opword 0x801E0024
		opword 0x2C000000
		opword 0x408100EC
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl angleABf
		opword 0xD03E0100
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC0610028
		opword 0xC0810024
		bl distABf
		lfs f2, float_10_8041cdd4(r2)
		lfs f0, float_2_8041ce08(r2)
		opword 0xEC211024
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_1_8041ce1c(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0xFC200090
		opword 0x7FC3F378
		bl unk_800c9398
		opword 0x7FC3F378
		bl partyMoveCheckWall
		opword 0xC03E0104
		opword 0x7FC3F378
		bl unk_800c8f24
		lfs f1, float_10_8041cdd4(r2)
		opword 0x7FC3F378
		lfs f2, float_0_8041cdec(r2)
		bl partySearchGround
		opword 0x7C7D1B79
		opword 0x41820038
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182002C
		opword 0x881E004C
		opword 0x3BA00000
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801E0008
		opword 0x64000100
		opword 0x901E0008
		opword 0x801E0000
		opword 0x64000200
		opword 0x901E0000
		opword 0x281D0000
		opword 0x93BE0138
		opword 0x40820018
		opword 0x7FC3F378
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01E011C
		opword 0xC01E00E4
		opword 0xD01E005C
		opword 0x48000054
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x901E0024
		opword 0x38800001
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC03F008C
		opword 0x7FC3F378
		opword 0xC05F0094
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		opword 0x801E0000
		opword 0x64000008
		opword 0x901E0000
		opword 0x801E0134
		opword 0x28000000
		opword 0x41820040
		opword 0x7FC3F378
		opword 0x38800001
		bl partyChgMoveMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0xC03F008C
		opword 0x7FC3F378
		opword 0xC05F0094
		bl partySetDir
		lfs f0, float_50_8041cde8(r2)
		opword 0xD01E0040
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
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
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void party_motion_jump(PartyEntry* party) {
	char _af_pad[108];
	asm volatile {
		opword 0x7C7C1B78
		lis r4, vec3_802f3e40@ha
		opword 0x83C30160
		addi r31, r4, vec3_802f3e40@l
		bl partyGetFootmarkId
		opword 0x809C0008
		opword 0x7C7D1B78
		opword 0x548007BD
		opword 0x41820014
		opword 0x548307FA
		opword 0x38000000
		opword 0x907C0008
		opword 0x981C0038
		opword 0x881C0038
		opword 0x2C00000A
		opword 0x41820504
		opword 0x40800708
		opword 0x2C000000
		opword 0x41820008
		opword 0x480006FC
		opword 0xC01C0094
		stfs f0, _af_pad+8(r1)
		opword 0xC01C0098
		opword 0xD001000C
		opword 0xC01C009C
		opword 0xD0010008
		opword 0xA81C0028
		opword 0x2C000000
		opword 0x40820010
		opword 0x881C0034
		opword 0x28000009
		opword 0x4082007C
		opword 0xC01C0058
		opword 0x38610010
		opword 0x38810008
		opword 0xD0010010
		opword 0xC01C005C
		opword 0xD001000C
		opword 0xC01C0060
		opword 0xD0010008
		opword 0xC03C0104
		opword 0xC05C0100
		bl movePos
		opword 0x801F0018
		opword 0x807F001C
		opword 0x9001004C
		opword 0xC0010010
		opword 0x801F0020
		opword 0xD001004C
		opword 0xC021000C
		opword 0x90610050
		opword 0xC0010008
		opword 0x90010054
		opword 0x8001004C
		opword 0xD0210050
		opword 0xD0010054
		opword 0x80610050
		opword 0x901C0094
		opword 0x80010054
		opword 0x907C0098
		opword 0x901C009C
		opword 0x48000294
		opword 0x801C0008
		opword 0x54000253
		opword 0x40820288
		opword 0x7FA3EB78
		bl partyGetFootmarkWriteId
		mr r27, r3
		opword 0x7FA3EB78
		bl partyGetFootmarkReadId
		opword 0x7C03D800
		opword 0x408200D4
		opword 0xC03C0058
		opword 0x7FA3EB78
		opword 0xC05C0060
		bl partyGetTargetDist
		lfs f2, float_2_8041ce08(r2)
		opword 0xC01E01B4
		opword 0xEC020032
		opword 0xFC010040
		opword 0x40810064
		opword 0xC03C0058
		opword 0x7FA3EB78
		opword 0xC05C0060
		bl partyGetTargetDir
		opword 0xFFC00890
		opword 0x7F83E378
		opword 0x38810058
		bl getFrontFloor
		opword 0xC061005C
		opword 0xFC40F090
		lfs f0, float_10_8041cdd4(r2)
		opword 0x38610010
		lfs f1, float_0p6_8041ce84(r2)
		opword 0x38810008
		opword 0xEC03002A
		opword 0xD001005C
		opword 0xD001000C
		opword 0xC01C0058
		opword 0xD0010010
		opword 0xC01C0060
		opword 0xD0010008
		opword 0xC01C00F4
		opword 0xEC210032
		bl movePos
		opword 0x801F0024
		opword 0x807F0028
		opword 0x90010040
		opword 0xC0010010
		opword 0x801F002C
		opword 0xD0010040
		opword 0xC021000C
		opword 0x90610044
		opword 0xC0010008
		opword 0x90010048
		opword 0x80010040
		opword 0xD0210044
		opword 0xD0010048
		opword 0x80610044
		opword 0x901C0094
		opword 0x80010048
		opword 0x907C0098
		opword 0x901C009C
		opword 0x4800019C
		opword 0x7FA3EB78
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		bl partyGetReadId
		lfs f30, float_50_8041cde8(r2)
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC0610010
		opword 0xC0810008
		bl distABf
		opword 0xC041000C
		opword 0xFFE00890
		opword 0xC01C005C
		lfs f3, float_1p4_8041ce88(r2)
		opword 0xEC020028
		lfs f2, float_50_8041cde8(r2)
		opword 0xEC030032
		opword 0xFC020040
		opword 0x40810008
		opword 0xFFC00090
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC0610010
		opword 0xC0810008
		bl angleABf
		opword 0x38610018
		opword 0x38810014
		bl sincosf
		opword 0xFC1FF040
		opword 0x40810098
		opword 0xFFE0F090
		opword 0x7FA3EB78
		bl partyGetTargetDistY
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC000800
		opword 0x40820008
		opword 0xFFE00090
		opword 0xC03C0058
		opword 0xC0010018
		opword 0xD0210010
		opword 0x801F0030
		opword 0xEC7F083A
		opword 0xC03C0060
		opword 0xC0010014
		opword 0x90010034
		opword 0x807F0034
		opword 0xEC5F083A
		opword 0xD0210008
		opword 0x801F0038
		opword 0xD0610034
		opword 0xC021000C
		lfs f0, float_10_8041cdd4(r2)
		opword 0x9001003C
		opword 0xEC01002A
		opword 0x80810034
		opword 0x90610038
		opword 0xD0010038
		opword 0xD041003C
		opword 0x80610038
		opword 0xD0610010
		opword 0x8001003C
		opword 0xD0410008
		opword 0xD001000C
		opword 0x909C0094
		opword 0x907C0098
		opword 0x901C009C
		opword 0x4800007C
		opword 0x7FA3EB78
		bl partyGetTargetDistY
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC000800
		opword 0x40820008
		opword 0xFFE00090
		opword 0xC0210018
		opword 0xC0010010
		opword 0x801F003C
		opword 0xEC5F007A
		opword 0x807F0040
		opword 0x90010028
		opword 0x801F0044
		opword 0xD0410028
		opword 0xC0210014
		opword 0xC0010008
		opword 0x9061002C
		opword 0xEC3F007A
		opword 0xC001000C
		opword 0x90010030
		opword 0x80810028
		opword 0xD001002C
		opword 0xD0210030
		opword 0x8061002C
		opword 0xD0410010
		opword 0x80010030
		opword 0xD0210008
		opword 0x909C0094
		opword 0x907C0098
		opword 0x901C009C
		opword 0xFC1FF040
		opword 0x4080000C
		opword 0x7FA3EB78
		bl partyNextReadId
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC07C0094
		opword 0xC09C009C
		bl distABf
		opword 0xD03C0128
		opword 0xA81C0028
		opword 0x2C000000
		opword 0x40820030
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC07C0094
		opword 0xC09C009C
		bl angleABf
		opword 0xD03C0100
		lfs f1, float_2p25_8041ce80(r2)
		opword 0x807C0160
		opword 0xC0030224
		opword 0xEC010032
		opword 0xD01C0104
		opword 0xC0BC0128
		opword 0xC01C0104
		lfs f2, float_0p9_8041ce8c(r2)
		opword 0xEC250024
		lfs f3, float_10_8041cdd4(r2)
		lfs f0, float_0p5_8041ce00(r2)
		opword 0xEC220072
		opword 0xEC03007A
		opword 0xEC001824
		opword 0xFC00001E
		opword 0xD8010068
		opword 0x8001006C
		opword 0x901C0024
		opword 0x801C0024
		opword 0x2C00000C
		opword 0x4080000C
		opword 0x3800000C
		opword 0x901C0024
		opword 0x801C0024
		opword 0x2C000028
		opword 0x4081000C
		opword 0x38000028
		opword 0x901C0024
		opword 0x807C0024
		opword 0x3C004330
		opword 0xC03C0098
		opword 0x6C638000
		opword 0xC01C005C
		opword 0x9061006C
		opword 0xECC10028
		opword 0xC87F0108
		opword 0x90010068
		lfs f4, float_0p5_8041ce00(r2)
		opword 0xC8410068
		opword 0xFC203210
		lfs f0, float_1_8041ce1c(r2)
		opword 0xEC421828
		opword 0xFC010040
		opword 0xEC8400B2
		opword 0x4080000C
		lfs f6, float_25_8041ce90(r2)
		opword 0x4800001C
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC060040
		opword 0x4C411382
		opword 0x40820008
		opword 0x48000008
		lfs f6, float_10_8041cdd4(r2)
		opword 0xEC66302A
		opword 0xC05E0224
		opword 0xEC242138
		lfs f0, float_13_8041ce94(r2)
		opword 0xEC630824
		opword 0xEC230132
		opword 0xEC220072
		opword 0xD03C0114
		opword 0xC03C0114
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01C0114
		opword 0xC03C0114
		lfs f0, float_3_8041ce0c(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0xD01C0114
		opword 0xFC201850
		opword 0xC01E0224
		opword 0x7F83E378
		opword 0x38800004
		opword 0xEC010032
		opword 0xD01C011C
		opword 0x801C0000
		opword 0x60000010
		opword 0x901C0000
		opword 0x801C0000
		opword 0x540007FA
		opword 0x901C0000
		bl partyChgPoseId
		opword 0x389C0058
		opword 0x38600927
		bl psndSFXOn_3D
		opword 0x3800000A
		opword 0x981C0038
		opword 0x801C0000
		opword 0x54000739
		opword 0x4082021C
		opword 0x7F83E378
		bl partyGetFootmarkId
		bl partyNextReadId
		opword 0x4800020C
		opword 0x801C0000
		opword 0x54000739
		opword 0x40820010
		opword 0x7F83E378
		bl partyGetFootmarkId
		bl partyNextReadId
		opword 0xC05C0114
		opword 0xC03C011C
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xEC22082A
		opword 0xD03C0114
		opword 0xC05C005C
		opword 0xC03C0114
		opword 0xEC22082A
		opword 0xD03C005C
		opword 0xC03C005C
		opword 0xFC010040
		opword 0x40800058
		opword 0x801C0000
		lfs f0, float_0_8041cdec(r2)
		opword 0x54000734
		opword 0x901C0000
		opword 0xD01C0114
		opword 0xC03C0058
		opword 0xC05C0060
		opword 0xC07E008C
		opword 0xC09E0094
		bl angleABf
		opword 0xD03C0100
		opword 0x7F83E378
		opword 0x38800000
		opword 0x80BE008C
		opword 0x801E0090
		opword 0x90BC0058
		opword 0x901C005C
		opword 0x801E0094
		opword 0x901C0060
		bl partyChgMot
		opword 0x48000170
		opword 0xC01C0114
		lfs f2, float_0_8041cdec(r2)
		opword 0xFC001040
		opword 0x4C401382
		opword 0x408200DC
		opword 0x801C0000
		opword 0x7F83E378
		opword 0x54000734
		opword 0x901C0000
		opword 0x801C0000
		opword 0x60000020
		opword 0x901C0000
		opword 0xC01C0114
		opword 0xFC200210
		bl partySearchGround
		opword 0x7C7D1B79
		opword 0x41820054
		bl hitGetAttr
		opword 0x546005AD
		opword 0x41820048
		opword 0x881C004C
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801C0008
		opword 0x64000100
		opword 0x901C0008
		opword 0x801C0000
		opword 0x64000200
		opword 0x901C0000
		opword 0x38000000
		opword 0x7F83E378
		opword 0x901C0138
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01C011C
		opword 0x480000DC
		opword 0x93BC0138
		opword 0x281D0000
		opword 0xC01C00E4
		opword 0xD01C005C
		opword 0x41820048
		opword 0x801C0000
		opword 0x7F83E378
		opword 0x60000002
		opword 0x901C0000
		opword 0x801C0000
		opword 0x54000730
		opword 0x901C0000
		bl N_partyPlaySfxPartyLanding1
		lfs f0, float_0_8041cdec(r2)
		opword 0x7F83E378
		opword 0x38800000
		opword 0xD01C0114
		bl partyChgMot
		opword 0x801C0008
		opword 0x64000080
		opword 0x901C0008
		opword 0x48000084
		opword 0x801C0000
		opword 0x540001CF
		opword 0x4182001C
		opword 0xC03C0104
		opword 0x3861001C
		opword 0xC05C0100
		opword 0x38810024
		bl movePos
		opword 0x48000060
		opword 0x80BC0058
		opword 0x7F83E378
		opword 0x801C005C
		opword 0x3881001C
		opword 0x90A1001C
		opword 0x90010020
		opword 0x801C0060
		opword 0x90010024
		opword 0xC03C0104
		opword 0xC05C0100
		bl partySearchFrontWall
		opword 0x28030000
		opword 0x4182001C
		opword 0x907C012C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC03C0104
		opword 0xFC010000
		opword 0x41820008
		opword 0x907C0134
		opword 0xC001001C
		opword 0xD01C0058
		opword 0xC0010024
		opword 0xD01C0060
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void party_motion_jump2(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0x93E1003C
		opword 0x93C10038
		opword 0x7C7E1B78
		opword 0x93A10034
		opword 0x80630008
		opword 0x83FE0160
		opword 0x546007BD
		opword 0x41820178
		opword 0x546307FA
		opword 0x38000000
		opword 0x907E0008
		lfs f2, float_neg1_8041cdf8(r2)
		opword 0x901E0024
		lfs f1, float_2p25_8041ce80(r2)
		opword 0xC01F0224
		opword 0xEC020032
		opword 0xD01E011C
		opword 0xC01F0224
		opword 0xEC010032
		opword 0xD01E0104
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl angleABf
		opword 0xD03E0100
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl distABf
		lfs f0, float_50_8041cde8(r2)
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		opword 0xD03E0128
		lfs f3, float_10_8041cdd4(r2)
		opword 0xC05E0104
		lfs f0, float_0p5_8041ce00(r2)
		opword 0xEC211024
		opword 0xC09E0098
		opword 0xC05E005C
		opword 0xEC03007A
		opword 0xEC841028
		opword 0xEC001824
		opword 0xFC00001E
		opword 0xD8010018
		opword 0x80A1001C
		opword 0x2C05000A
		opword 0x40800008
		opword 0x38A0000A
		opword 0x6CA38000
		opword 0x3C004330
		opword 0x90610024
		lis r4, double_to_int_802f3f48@ha
		lfd f3, double_to_int_802f3f48@l(r4)
		opword 0x90010020
		lfs f2, float_0p5_8041ce00(r2)
		opword 0xC8010020
		opword 0x90BE0024
		opword 0xECA01828
		lfs f0, float_20_8041cdc0(r2)
		opword 0xC03E0128
		opword 0xC07F0224
		opword 0xEC212824
		opword 0xEC230072
		opword 0xD03E0104
		opword 0xC03E011C
		opword 0xFC200A10
		opword 0xEC250072
		opword 0xEC250072
		opword 0xEC22207A
		opword 0xEC212824
		opword 0xD03E0114
		opword 0xC05E0114
		opword 0xC03F0224
		opword 0xEC220072
		opword 0xD03E0114
		opword 0xC03E0114
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01E0114
		opword 0xC03E0114
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0xD01E0114
		opword 0x7FC3F378
		opword 0x38800004
		bl partyChgPoseId
		opword 0x801E0000
		opword 0x389E0058
		opword 0x38600927
		opword 0x60000010
		opword 0x901E0000
		opword 0x801E0000
		opword 0x540007FA
		opword 0x901E0000
		bl psndSFXOn_3D
		opword 0x38000000
		opword 0x981E0038
		opword 0x881E0038
		opword 0x2C000001
		opword 0x41820020
		opword 0x40800168
		opword 0x2C000000
		opword 0x40800008
		opword 0x4800015C
		opword 0x38000001
		opword 0x981E0038
		opword 0x48000150
		opword 0xC03E0114
		opword 0x7FC3F378
		opword 0xC01E011C
		opword 0x38810008
		opword 0xEC01002A
		opword 0xD01E0114
		opword 0xC03E005C
		opword 0xC01E0114
		opword 0xEC01002A
		opword 0xD01E005C
		opword 0x80BE0058
		opword 0x801E005C
		opword 0x90A10008
		opword 0x9001000C
		opword 0x801E0060
		opword 0x90010010
		opword 0xC03E0104
		opword 0xC05E0100
		bl partySearchFrontWall
		opword 0xC0010008
		lfs f2, float_0_8041cdec(r2)
		opword 0xD01E0058
		opword 0xC0010010
		opword 0xD01E0060
		opword 0xC01E0114
		opword 0xFC001040
		opword 0x4C401382
		opword 0x408200E0
		opword 0xFC200210
		opword 0x7FC3F378
		bl partySearchGround
		opword 0xC01E00E4
		opword 0x7C7D1B79
		opword 0xD001000C
		opword 0x41820054
		bl hitGetAttr
		opword 0x546005AD
		opword 0x41820048
		opword 0x881E004C
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801E0008
		opword 0x64000100
		opword 0x901E0008
		opword 0x801E0000
		opword 0x64000200
		opword 0x901E0000
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x901E0138
		opword 0x38800003
		bl partyChgMot
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xD01E011C
		opword 0x480000D4
		opword 0xC001000C
		opword 0x281D0000
		opword 0xD01E005C
		opword 0x93BE0138
		opword 0x41820060
		opword 0x7FC3F378
		bl N_partyPlaySfxPartyLanding1
		opword 0x801E0000
		lfs f0, float_0_8041cdec(r2)
		opword 0x54000730
		opword 0x901E0000
		opword 0x801E0000
		opword 0x60000002
		opword 0x901E0000
		opword 0xD01E0114
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07E0094
		opword 0xC09E009C
		bl distABf
		lfs f0, float_5_8041ce18(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38800000
		opword 0x48000008
		opword 0x38800001
		opword 0x7FC3F378
		bl partyChgMot
		opword 0xC03E005C
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC010040
		opword 0x40800054
		opword 0x801E0000
		lfs f0, float_0_8041cdec(r2)
		opword 0x54000734
		opword 0x901E0000
		opword 0xD01E0114
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07F008C
		opword 0xC09F0094
		bl angleABf
		opword 0xD03E0100
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x80BF008C
		opword 0x801F0090
		opword 0x90BE0058
		opword 0x901E005C
		opword 0x801F0094
		opword 0x901E0060
		bl partyChgMot
		opword 0x80010044
		opword 0x83E1003C
		opword 0x83C10038
		opword 0x83A10034
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 party_motion_fall(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0x93E1002C
		opword 0x93C10028
		opword 0x7C7E1B78
		opword 0x93A10024
		opword 0x80030000
		opword 0x83E30160
		opword 0x54000739
		opword 0x4082000C
		bl partyGetFootmarkId
		bl partyNextReadId
		opword 0x807E0008
		opword 0x546007BD
		opword 0x41820024
		opword 0x546007FA
		opword 0x7FC3F378
		opword 0x901E0008
		opword 0x38800004
		bl partyChgPoseId
		opword 0x801E0000
		opword 0x54000356
		opword 0x901E0000
		opword 0x801E0000
		opword 0x3BA00000
		opword 0x5400018D
		opword 0x4082001C
		opword 0xC01E0114
		opword 0x7FC3F378
		lfs f1, float_10_8041cdd4(r2)
		opword 0xFC400210
		bl partySearchGround
		opword 0x7C7D1B78
		opword 0x281D0000
		opword 0x41820048
		opword 0x7FA3EB78
		bl hitGetAttr
		opword 0x546005AD
		opword 0x41820038
		opword 0x881E0032
		opword 0x3BA00000
		opword 0x28000000
		opword 0x40820028
		opword 0x881E004C
		opword 0x7C000775
		opword 0x4082001C
		opword 0x801E0008
		opword 0x64000100
		opword 0x901E0008
		opword 0x801E0000
		opword 0x64000200
		opword 0x901E0000
		opword 0x281D0000
		opword 0x93BE0138
		opword 0x40820178
		opword 0x801E0000
		opword 0x540007FA
		opword 0x901E0000
		opword 0x807E0000
		opword 0x546006B5
		opword 0x40820024
		opword 0x60600020
		lfs f1, float_0_8041cdec(r2)
		opword 0x901E0000
		opword 0xC01E011C
		opword 0xFC010000
		opword 0x4082000C
		lfs f0, float_neg1p4_8041ce6c(r2)
		opword 0xD01E011C
		opword 0xC05E0114
		opword 0xC03E011C
		lfs f0, float_neg16_8041ce70(r2)
		opword 0xEC22082A
		opword 0xD03E0114
		opword 0xC03E0114
		opword 0xFC010040
		opword 0x40800008
		opword 0xD01E0114
		opword 0xC05E005C
		opword 0xC03E0114
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xEC22082A
		opword 0xD03E005C
		opword 0xC03E005C
		opword 0xFC010040
		opword 0x408000A4
		lfs f0, float_neg2001_8041ce74(r2)
		opword 0xD01E005C
		opword 0xA01F002E
		opword 0x2800001F
		opword 0x4182000C
		opword 0x28000020
		opword 0x4082000C
		opword 0x38600002
		opword 0x480001BC
		opword 0x801E0000
		lfs f0, float_0_8041cdec(r2)
		opword 0x54000730
		opword 0x901E0000
		opword 0xD01E0114
		opword 0xD01E011C
		opword 0xC03E0058
		opword 0xC05E0060
		opword 0xC07F008C
		opword 0xC09F0094
		bl angleABf
		opword 0xD03E0100
		opword 0xC03F01AC
		bl toMovedir
		lfs f0, float_180_8041ce38(r2)
		opword 0xEC20082A
		bl revise360
		opword 0xD03E0054
		opword 0x7FC3F378
		opword 0x389E0058
		bl partyGetAppearPos4
		opword 0xC03E005C
		opword 0x7FC3F378
		lfs f0, float_37_8041ce78(r2)
		opword 0x38800000
		opword 0xEC01002A
		opword 0xD01E005C
		bl partyChgMot
		opword 0x801E0000
		opword 0x540001CA
		opword 0x901E0000
		opword 0xC03E0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x41820044
		opword 0x80BE0058
		opword 0x7FC3F378
		opword 0x801E005C
		opword 0x38810008
		lfs f0, float_1p3_8041ce7c(r2)
		opword 0x90A10008
		opword 0xEC200072
		opword 0x9001000C
		opword 0x801E0060
		opword 0x90010010
		opword 0xC05E0100
		bl partySearchFrontWall
		opword 0xC0010008
		opword 0xD01E0058
		opword 0xC0010010
		opword 0xD01E0060
		opword 0x38600002
		opword 0x480000E8
		opword 0x807E0000
		opword 0x546006B5
		opword 0x41820060
		opword 0x54600730
		lfs f1, float_0_8041cdec(r2)
		opword 0x901E0000
		opword 0x801E0000
		opword 0x60000002
		opword 0x901E0000
		opword 0xD03E0114
		opword 0xC01E00E4
		opword 0xD01E005C
		opword 0xC01E0104
		opword 0xFC010000
		opword 0x40820014
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0x48000010
		opword 0x7FC3F378
		opword 0x38800001
		bl partyChgMot
		opword 0x7FC3F378
		bl N_partyPlaySfxPartyLanding1
		opword 0x38600003
		opword 0x48000080
		opword 0x546004E2
		lfs f1, float_0_8041cdec(r2)
		opword 0x901E0000
		opword 0x801E0000
		opword 0x54000730
		opword 0x901E0000
		opword 0x801E0000
		opword 0x60000002
		opword 0x901E0000
		opword 0xD03E0114
		opword 0xC01E00E4
		opword 0xD01E005C
		opword 0xC01E0104
		opword 0xFC010000
		opword 0x40820014
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0x48000010
		opword 0x7FC3F378
		opword 0x38800001
		bl partyChgMot
		opword 0x7FC3F378
		bl N_partyPlaySfxPartyLanding1
		opword 0x801E0000
		opword 0x54000739
		opword 0x4082000C
		bl partyClearFootmark
		opword 0x48000008
		bl partyClearFootmark2
		opword 0x38600003
		opword 0x80010034
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x83A10024
		opword 0x7C0803A6
		opword 0x38210030
	}
#endif
}
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
#endif
#ifndef NONMATCHING
#pragma pop
#endif

void party_motion_upstairs(PartyEntry* party) {
    if (party->flags3 & 2) {
        party->flags3 &= ~2;
        party->flags |= 0x40;
        unk_804189ec = 3;
#ifdef NONMATCHING
        unk_804189e8 = (party->unk120 - party->position.y) / 3.0f;
#endif
#ifndef NONMATCHING
        unk_804189e8 = (party->unk120 - party->position.y) / EXT_LIT(float_3_8041ce0c, 3.0f);
#endif
    }
    party->position.y += unk_804189e8;
    if (--unk_804189ec <= 0) {
        party->flags &= ~0x40;
        partyChgMot(party, 1);
    }
}

#ifdef NONMATCHING
static inline BOOL partyChkHitAttr200(HitEntry* hit) {
    if (!hit) {
        return FALSE;
    }
    if (hitGetAttr(hit) & 0x200) {
        return TRUE;
    }
    return FALSE;
#endif
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void party_motion_damage(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0x93E1003C
		opword 0x7C7F1B78
		opword 0x93C10038
		opword 0x80630008
		opword 0x83DF0160
		opword 0x546007BD
		opword 0x41820014
		opword 0x546307FA
		opword 0x38000000
		opword 0x907F0008
		opword 0x981F0038
		opword 0x881F0038
		opword 0x2C00000A
		opword 0x418200C0
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820050
		opword 0x40800268
		opword 0x2C000000
		opword 0x40800018
		opword 0x4800025C
		opword 0x2C00000C
		opword 0x41820224
		opword 0x40800250
		opword 0x4800011C
		opword 0x7FE3FB78
		opword 0x38800008
		bl partyChgPoseId
		lfs f1, float_15_8041ce60(r2)
		opword 0x3860003C
		lfs f0, float_0_8041cdec(r2)
		opword 0x38000001
		opword 0xD03F0114
		opword 0xD01F0118
		opword 0x907F0024
		opword 0x981F0038
		opword 0xC03F005C
		opword 0x38610020
		opword 0xC01F0114
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0xEC01002A
		opword 0xD01F005C
		opword 0x80FF0058
		opword 0x801F005C
		opword 0x90E10020
		opword 0x90010024
		opword 0x801F0060
		opword 0x90010028
		bl marioGetScreenPos
		opword 0xC021000C
		lfs f0, float_neg300_8041ce64(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x408201D0
		opword 0x38600014
		opword 0x3800000A
		opword 0x907F0024
		opword 0x981F0038
		opword 0x480001BC
		opword 0xA01E002E
		opword 0x2800001F
		opword 0x418201B0
		opword 0x28000020
		opword 0x418201A8
		opword 0x807F0024
		opword 0x3403FFFF
		opword 0x901F0024
		opword 0x41810198
		opword 0x3861002C
		bl partyGetReturnPos
		opword 0xC001002C
		opword 0x7FE3FB78
		lfs f3, float_200_8041cdd8(r2)
		opword 0xD01F0058
		lfs f1, float_0_8041cdec(r2)
		opword 0xC0410030
		lfs f0, float_neg1_8041cdf8(r2)
		opword 0xEC43102A
		opword 0xD05F005C
		opword 0xC0410034
		opword 0xD05F0060
		opword 0xD03F0114
		opword 0xD01F0118
		bl unk_800c9398
		opword 0x807F0000
		opword 0x3800000B
		opword 0x60630020
		opword 0x907F0000
		opword 0x807F0000
		opword 0x64630200
		opword 0x907F0000
		opword 0x981F0038
		opword 0x48000134
		opword 0x80FF0058
		opword 0x38610014
		opword 0x801F005C
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x90E10014
		opword 0x90010018
		opword 0x801F0060
		opword 0x9001001C
		bl marioGetScreenPos
		opword 0xC021000C
		lfs f0, float_240_8041ce68(r2)
		opword 0xFC010040
		opword 0x40810010
		opword 0x801F0000
		opword 0x540001CA
		opword 0x901F0000
		opword 0x7FE3FB78
		bl partyMove
		opword 0xC01F0114
		lfs f1, float_neg6_8041ce2c(r2)
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820010
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01F0118
		opword 0xD03F0114
		opword 0xC03F005C
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC010040
		opword 0x40800038
		opword 0x807E008C
		opword 0x801E0090
		lfs f0, float_200_8041cdd8(r2)
		opword 0x907F0058
		opword 0x901F005C
		opword 0x801E0094
		opword 0x901F0060
		opword 0xC03F005C
		opword 0xEC01002A
		opword 0xD01F005C
		opword 0x801F0000
		opword 0x54000730
		opword 0x901F0000
		opword 0x807F0138
		opword 0x28030000
		opword 0x41820074
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x40820048
		opword 0x3860000C
		opword 0x3800001E
		opword 0x987F0038
		opword 0x901F0024
		opword 0x48000034
		opword 0x807F0024
		opword 0x3403FFFF
		opword 0x901F0024
		opword 0x41810024
		opword 0x7FE3FB78
		opword 0x38800002
		bl partyChgRunMode
		opword 0x38000000
		opword 0x981F003B
		opword 0x801F0004
		opword 0x54000734
		opword 0x901F0004
		opword 0x80010044
		opword 0x83E1003C
		opword 0x83C10038
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void allPartyForceSlitOff(void) {
#ifdef NONMATCHING
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        L_partyForceSlitOff(party);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        L_partyForceSlitOff(party);
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x7C7F1B79
		opword 0x4182009C
		opword 0x801F0000
		opword 0x540004E7
		opword 0x40820010
		opword 0x801F0004
		opword 0x540005EF
		opword 0x41820084
		opword 0xC03F0100
		opword 0xC01F00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01F010C
		lfs f1, float_270_8041ce34(r2)
		opword 0xC01F010C
		opword 0xD01F0110
		opword 0xC01F010C
		opword 0xEC210028
		bl revise360
		opword 0xD03F00FC
		opword 0x7FE3FB78
		opword 0xC01F00FC
		opword 0xD01F0100
		opword 0x801F0004
		opword 0x540006AA
		opword 0x901F0004
		bl partyPaperOff
		opword 0x80BF0000
		opword 0x38000000
		opword 0x7FE3FB78
		opword 0x38800001
		opword 0x54A50522
		opword 0x90BF0000
		opword 0x981F0037
		bl partyChgPoseId
		bl marioGetExtraPartyId
		bl partyGetPtr
		opword 0x7C7F1B79
		opword 0x4182009C
		opword 0x801F0000
		opword 0x540004E7
		opword 0x40820010
		opword 0x801F0004
		opword 0x540005EF
		opword 0x41820084
		opword 0xC03F0100
		opword 0xC01F00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01F010C
		lfs f1, float_270_8041ce34(r2)
		opword 0xC01F010C
		opword 0xD01F0110
		opword 0xC01F010C
		opword 0xEC210028
		bl revise360
		opword 0xD03F00FC
		opword 0x7FE3FB78
		opword 0xC01F00FC
		opword 0xD01F0100
		opword 0x801F0004
		opword 0x540006AA
		opword 0x901F0004
		bl partyPaperOff
		opword 0x80BF0000
		opword 0x38000000
		opword 0x7FE3FB78
		opword 0x38800001
		opword 0x54A50522
		opword 0x90BF0000
		opword 0x981F0037
		bl partyChgPoseId
		opword 0x80010014
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void L_partyForceSlitOff(PartyEntry* party) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		opword 0x7C7F1B78
		opword 0x80030000
		opword 0x540004E7
		opword 0x40820010
		opword 0x801F0004
		opword 0x540005EF
		opword 0x41820084
		opword 0xC03F0100
		opword 0xC01F00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01F010C
		lfs f1, float_270_8041ce34(r2)
		opword 0xC01F010C
		opword 0xD01F0110
		opword 0xC01F010C
		opword 0xEC210028
		bl revise360
		opword 0xD03F00FC
		opword 0x7FE3FB78
		opword 0xC01F00FC
		opword 0xD01F0100
		opword 0x801F0004
		opword 0x540006AA
		opword 0x901F0004
		bl partyPaperOff
		opword 0x80BF0000
		opword 0x38000000
		opword 0x7FE3FB78
		opword 0x38800001
		opword 0x54A50522
		opword 0x90BF0000
		opword 0x981F0037
		bl partyChgPoseId
		opword 0x80010014
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
BOOL party_slit(PartyEntry* party) {
#ifdef NONMATCHING
    BOOL ret = TRUE;
    PartyMarioView* mario;
    f32 a;
#endif
#ifndef NONMATCHING
	asm {
		lis r4, vec3_802f3e40@ha
		addi r31, r4, vec3_802f3e40@l
		li r30, 0x1
	}
	asm volatile {
		mr r28, r3
		opword 0x88030037
		opword 0x83A30160
		opword 0x28000001
		opword 0x4182000C
		opword 0x38600001
		opword 0x4800043C
		opword 0x809C0008
		opword 0x548007FF
		opword 0x4182008C
		opword 0x5480003C
		opword 0x389F0148
		opword 0x901C0008
		opword 0x801C0004
		opword 0x60000100
		opword 0x901C0004
		bl partyPaperOn
		opword 0x7F83E378
		opword 0x389F0150
		bl partyChgPaper
		opword 0x3800001E
		lfs f1, float_0_8041cdec(r2)
		opword 0x901C0024
		opword 0x7F83E378
		bl unk_800c9398
		opword 0xC03C0100
		opword 0xC01D0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082001C
		opword 0x807C0004
		opword 0x38000000
		opword 0x546305EA
		opword 0x907C0004
		opword 0x981C003A
		opword 0x48000018
		opword 0x807C0004
		opword 0x38000002
		opword 0x60630200
		opword 0x907C0004
		opword 0x981C003A
		opword 0x881C003A
		opword 0x2C000002
		opword 0x41820080
		opword 0x40800010
		opword 0x2C000000
		opword 0x41820014
		opword 0x480001F0
		opword 0x2C00000A
		opword 0x418200C8
		opword 0x480001E4
		opword 0x807C0024
		opword 0x3403FFFF
		opword 0x901C0024
		opword 0x408001D4
		opword 0x801C0000
		opword 0x7F83E378
		lfs f0, float_270_8041ce34(r2)
		opword 0x389F0158
		opword 0x60001000
		opword 0x901C0000
		opword 0xD01C010C
		opword 0xC01C010C
		opword 0xD01C0110
		bl partyChgPaper
		opword 0x801C0000
		opword 0x540004A5
		opword 0x40820014
		opword 0x3800000A
		opword 0x3BC00000
		opword 0x981C003A
		opword 0x48000190
		opword 0x38000014
		opword 0x981C003A
		opword 0x48000184
		opword 0x807C0024
		opword 0x3403FFFF
		opword 0x901C0024
		opword 0x40800174
		opword 0x801C0000
		opword 0x7F83E378
		lfs f0, float_270_8041ce34(r2)
		opword 0x389F0158
		opword 0x60001000
		opword 0x901C0000
		opword 0xD01C010C
		opword 0xC01C010C
		opword 0xD01C0110
		bl partyChgPaper
		opword 0x801C0000
		opword 0x540004A5
		opword 0x40820014
		opword 0x3800000A
		opword 0x3BC00000
		opword 0x981C003A
		opword 0x48000130
		opword 0x38000014
		opword 0x981C003A
		opword 0x48000124
		opword 0xC03C0104
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010000
		opword 0x4082001C
		opword 0x7F83E378
		opword 0x389F0158
		bl partyChgPaper
		lfs f0, float_270_8041ce34(r2)
		opword 0xD01C010C
		opword 0x480000C8
		opword 0xC03C0100
		opword 0xC01D0198
		opword 0xEC210028
		bl revise360
		opword 0xC81F0160
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820014
		opword 0x801C0004
		opword 0x60000200
		opword 0x901C0004
		opword 0x48000010
		opword 0x801C0004
		opword 0x540005EA
		opword 0x901C0004
		opword 0x801C0004
		opword 0x540005AD
		opword 0x4182000C
		lfs f0, float_280_8041ce4c(r2)
		opword 0x48000008
		lfs f0, float_260_8041ce50(r2)
		opword 0xD01C010C
		opword 0xC03C0100
		opword 0xC01D0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_315_8041ce54(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820034
		lfs f0, float_45_8041ce10(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820024
		lfs f0, float_135_8041ce58(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820024
		lfs f0, float_225_8041ce5c(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820014
		opword 0x7F83E378
		opword 0x389F0168
		bl partyChgPaper
		opword 0x48000010
		opword 0x7F83E378
		opword 0x389F0170
		bl partyChgPaper
		opword 0x801D0000
		opword 0x540002D7
		opword 0x4082002C
		opword 0x807C012C
		bl hitGetAttr
		opword 0x546004A5
		opword 0x4082001C
		opword 0x807C0134
		bl hitGetAttr
		opword 0x546004A5
		opword 0x4082000C
		opword 0x38000028
		opword 0x981C003A
		opword 0x881C003A
		opword 0x2C000015
		opword 0x41820064
		opword 0x40800010
		opword 0x2C000014
		opword 0x40800014
		opword 0x480000C8
		opword 0x2C000017
		opword 0x408000C0
		opword 0x480000A4
		opword 0x7F83E378
		opword 0x389F0178
		bl partyChgPaper
		opword 0x809C0000
		opword 0x38000014
		lfs f1, float_0_8041cdec(r2)
		opword 0x7F83E378
		opword 0x64840200
		opword 0x909C0000
		opword 0x809C0000
		opword 0x60840020
		opword 0x909C0000
		opword 0x901C0024
		bl unk_800c9398
		opword 0x38000015
		opword 0x981C003A
		opword 0x48000078
		opword 0xC03C0100
		opword 0xC01C00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		lfs f0, float_260_8041ce50(r2)
		opword 0x48000008
		lfs f0, float_280_8041ce4c(r2)
		opword 0xD01C010C
		lfs f0, float_neg3_8041ce40(r2)
		opword 0xC03C005C
		opword 0xEC01002A
		opword 0xD01C005C
		opword 0x807C0024
		opword 0x3403FFFF
		opword 0x901C0024
		opword 0x41810028
		opword 0x38000016
		opword 0x981C003A
		opword 0x4800001C
		opword 0x3800000A
		opword 0x981C003A
		opword 0x801C0000
		opword 0x540001CA
		opword 0x901C0000
		bl marioClearSlitFloor
		opword 0x881C003A
		opword 0x2C000029
		opword 0x4182006C
		opword 0x40800010
		opword 0x2C000028
		opword 0x40800014
		opword 0x480000A0
		opword 0x2C00002B
		opword 0x40800098
		opword 0x4800006C
		opword 0x7F83E378
		opword 0x389F0180
		bl partyChgPaper
		opword 0x3860001E
		opword 0x38000029
		opword 0x907C0024
		opword 0x981C003A
		opword 0xC03C0100
		opword 0xC01D0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f0, float_0_8041cdec(r2)
		opword 0xD01C010C
		opword 0xC01C010C
		opword 0xD01C0110
		opword 0x807C0024
		opword 0x3403FFFF
		opword 0x901C0024
		opword 0x41810038
		opword 0x3800002A
		opword 0x981C003A
		opword 0x4800002C
		opword 0x801C0004
		opword 0x7F83E378
		opword 0x540006AA
		opword 0x901C0004
		bl partyPaperOff
		opword 0x807C0000
		opword 0x38000000
		opword 0x54630522
		opword 0x907C0000
		opword 0x981C0037
		opword 0x7FC3F378
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
BOOL party_roll(PartyEntry* party) {
	char _af_pad[4];
	asm {
		lis r4, vec3_802f3e40@ha
		addi r31, r4, vec3_802f3e40@l
		li r30, 0x1
	}
	asm volatile {
		mr r29, r3
		opword 0x88030037
		opword 0x28000002
		opword 0x4182000C
		opword 0x38600001
		opword 0x4800036C
		opword 0x809D0008
		opword 0x548007FF
		opword 0x41820064
		opword 0x5480003C
		opword 0x389F0128
		opword 0x901D0008
		bl partyPaperOn
		opword 0x7FA3EB78
		opword 0x389F0130
		bl partyChgPaper
		opword 0x7FA3EB78
		opword 0x38800000
		bl partyChgPoseId
		lfs f0, float_neg6_8041ce2c(r2)
		opword 0x38800041
		lfs f2, float_6_8041ce30(r2)
		opword 0x38000000
		opword 0xD01D0088
		opword 0x7FA3EB78
		lfs f0, float_2_8041ce08(r2)
		opword 0xD05D008C
		lfs f1, float_0_8041cdec(r2)
		opword 0xD05D007C
		opword 0xD01D0080
		opword 0x909D0024
		opword 0x981D003A
		bl unk_800c9398
		opword 0x881D003A
		opword 0x2C00000A
		opword 0x41820044
		opword 0x408000A4
		opword 0x2C000000
		opword 0x41820008
		opword 0x48000098
		opword 0x807D0024
		opword 0x3803FFFF
		opword 0x901D0024
		opword 0x801D0024
		opword 0x2C000000
		opword 0x41810080
		opword 0x7FA3EB78
		opword 0x389F0138
		bl partyChgPaper
		opword 0x3800000A
		opword 0x981D003A
		opword 0x48000068
		lfs f1, float_270_8041ce34(r2)
		opword 0xC01D0100
		opword 0xEC210028
		bl revise360
		opword 0xD03D010C
		opword 0xC03D00FC
		opword 0xC01D010C
		opword 0xEC21002A
		bl revise360
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x40810020
		lfs f2, float_7_8041ce3c(r2)
		opword 0xC03D0104
		opword 0xC01D006C
		opword 0xEC22007A
		bl revise360
		opword 0xD03D006C
		opword 0x4800001C
		lfs f2, float_7_8041ce3c(r2)
		opword 0xC03D0104
		opword 0xC01D006C
		opword 0xEC22007C
		bl revise360
		opword 0xD03D006C
		opword 0x881D003A
		opword 0x2C000065
		opword 0x41820078
		opword 0x4080023C
		opword 0x2C000064
		opword 0x40800008
		opword 0x48000230
		lfs f1, float_0_8041cdec(r2)
		lfs f0, float_180_8041ce38(r2)
		opword 0xD03D0104
		opword 0xD03D0064
		opword 0xD03D006C
		opword 0xD03D0088
		opword 0xD03D008C
		opword 0xC03D0100
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_3_8041ce0c(r2)
		opword 0x48000008
		lfs f0, float_neg3_8041ce40(r2)
		opword 0xD01D007C
		opword 0x38A00041
		lfs f0, float_0_8041cdec(r2)
		opword 0x38000065
		opword 0x7FA3EB78
		opword 0x389F0140
		opword 0xD01D0080
		opword 0x90BD0024
		opword 0x981D003A
		bl partyChgPaper
		opword 0x7FA3EB78
		bl partyPaperLightOff
		opword 0x807D0024
		opword 0x3BC00000
		opword 0x3803FFFF
		opword 0x901D0024
		opword 0x801D0024
		opword 0x2C000000
		opword 0x408100E4
		opword 0xC03D0100
		lfs f0, float_180_8041ce38(r2)
		opword 0xFC010040
		opword 0x4080006C
		lfs f3, float_90_8041ce48(r2)
		opword 0xC09D010C
		lfs f2, float_0p1_8041ce44(r2)
		opword 0xEC232028
		lfs f0, float_1_8041ce1c(r2)
		opword 0xECA20072
		opword 0xECA5202A
		opword 0xEC232828
		opword 0xFC010040
		opword 0x7C600026
		opword 0x3C004330
		opword 0x54630FFE
		stw r0, _af_pad+0(r1)
		opword 0x6C608000
		opword 0xC85F0108
		opword 0x9001000C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xFC200A10
		opword 0xFC010000
		opword 0x41820008
		opword 0xFCA01890
		opword 0xD0BD010C
		opword 0xD0BD0110
		opword 0x48000138
		lfs f3, float_270_8041ce34(r2)
		opword 0xC09D010C
		lfs f2, float_0p1_8041ce44(r2)
		opword 0xEC232028
		lfs f0, float_1_8041ce1c(r2)
		opword 0xECA20072
		opword 0xECA5202A
		opword 0xEC232828
		opword 0xFC010040
		opword 0x7C600026
		opword 0x3C004330
		opword 0x54630FFE
		opword 0x90010008
		opword 0x6C608000
		opword 0xC85F0108
		opword 0x9001000C
		lfs f0, float_0_8041cdec(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xFC200A10
		opword 0xFC010000
		opword 0x41820008
		opword 0xFCA01890
		opword 0xD0BD010C
		opword 0xD0BD0110
		opword 0x480000D0
		opword 0xC01D0100
		opword 0x3BC00001
		lfs f1, float_180_8041ce38(r2)
		opword 0xFC000840
		opword 0x4C411382
		opword 0x40820020
		lfs f1, float_0_8041cdec(r2)
		lfs f0, float_270_8041ce34(r2)
		opword 0xD03D010C
		opword 0xD03D0110
		opword 0xD01D00FC
		opword 0xD01D0100
		opword 0x48000018
		opword 0xD03D010C
		lfs f0, float_90_8041ce48(r2)
		opword 0xD03D0110
		opword 0xD01D00FC
		opword 0xD01D0100
		opword 0x80DF0048
		opword 0x38800000
		opword 0x80BF004C
		opword 0x38000064
		opword 0x7FA3EB78
		opword 0x90DD0088
		opword 0x90BD008C
		opword 0x80BF0050
		opword 0x90BD0090
		opword 0x80DF0054
		opword 0x80BF0058
		opword 0x90DD007C
		opword 0x90BD0080
		opword 0x80BF005C
		opword 0x90BD0084
		opword 0x989D0037
		opword 0x809D0000
		opword 0x54840524
		opword 0x909D0000
		opword 0x809D0004
		opword 0x5484062C
		opword 0x909D0004
		opword 0x809D0000
		opword 0x548405EA
		opword 0x909D0000
		opword 0x809D0004
		opword 0x54840734
		opword 0x909D0004
		opword 0x809D0004
		opword 0x54840776
		opword 0x909D0004
		opword 0x981D003A
		bl partyPaperOff
		opword 0x7FC3F378
	}
#endif
}
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



static inline s32 pm_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 pm_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (pm_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif
#ifndef NONMATCHING
#pragma pop
#endif







































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

static f32 partyHomingOff(PartyEntry* party) {
    f32 off = 5.0f;
    if (party->flags2 & 0x8000) {
        off = 1.0f;
    }
    return off;
}

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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir) {
	char _af_pad[204];
	asm volatile {
		opword 0x7C7D1B78
		lis r3, vec3_802f3e40@ha
		lfs f2, float_2_8041ce08(r2)
		addi r31, r3, vec3_802f3e40@l
		opword 0xC01D00F4
		opword 0x7C9E2378
		opword 0x809F0060
		opword 0xFF600890
		opword 0xEC420032
		lfs f0, float_3_8041ce0c(r2)
		opword 0x80BF0064
		la r3, _af_pad+4
		opword 0x801F0068
		opword 0xEFA20024
		opword 0x90810034
		opword 0x38810010
		lfs f28, touch_wall_ct(r13)
		opword 0x90A10038
		opword 0x9001003C
		bl sincosf
		opword 0xCBDF0108
		li r27, 0x0
		lfs f31, float_100_8041cde0(r2)
		opword 0x3F804330
		opword 0x6F608000
		opword 0xC021000C
		opword 0x900100A4
		opword 0x3861001C
		opword 0xC0010010
		opword 0xEC610772
		opword 0x938100A0
		opword 0x38800000
		opword 0xC05D0058
		opword 0xEC200772
		opword 0xC80100A0
		opword 0x900100AC
		opword 0xEC00F028
		opword 0x938100A8
		opword 0xEC6010FA
		opword 0xC80100A8
		opword 0xEC40F028
		opword 0xD0610028
		opword 0xC01D0060
		opword 0xEC02007A
		opword 0xD0010030
		opword 0xC03D005C
		opword 0xC01D00F0
		opword 0xEC01002A
		opword 0xD3E10058
		opword 0xD001002C
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x41820104
		opword 0xC001004C
		opword 0xC0210054
		opword 0xEC400032
		lfs f0, float_0_8041cdec(r2)
		opword 0xEC210072
		opword 0xEC82082A
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87F0110
		opword 0xC85F0118
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81F0120
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		lfs f0, float_45_8041ce10(r2)
		opword 0xFC040040
		opword 0x4080000C
		opword 0xC0410044
		opword 0x48000014
		opword 0x3B7B0001
		opword 0x2C1B0003
		opword 0x4180FE84
		lfs f2, float_neg2000_8041cdfc(r2)
		lfs f0, float_neg2000_8041cdfc(r2)
		opword 0xFC020040
		opword 0x4081002C
		opword 0xC03D005C
		lfs f0, float_2_8041ce08(r2)
		opword 0xEC21E02A
		opword 0xEC020028
		opword 0xFC010040
		opword 0x4080000C
		opword 0xD021006C
		opword 0x48000018
		opword 0xD001006C
		opword 0x48000010
		opword 0xC01D005C
		opword 0xEC00E02A
		opword 0xD001006C
		lfs f2, float_0p75_8041ce14(r2)
		opword 0xFC20D890
		opword 0xC01D00F4
		opword 0x38610018
		opword 0x38810014
		fmuls f27, f2, f0
		bl sincosf
		opword 0xC0210018
		opword 0x3861005C
		opword 0xC01D0058
		opword 0x38800000
		opword 0xC0410014
		opword 0xEC2106FA
		lfs f0, float_300_8041cddc(r2)
		opword 0x80DF006C
		opword 0x80BF0070
		opword 0xD0210068
		opword 0x801F0074
		opword 0xC03D0060
		opword 0xEC220EFA
		opword 0xD0010098
		opword 0x90C10074
		opword 0xD0210070
		opword 0x90A10078
		opword 0x9001007C
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x40820024
		opword 0xC01D0058
		opword 0x38600000
		opword 0xD01E0000
		opword 0xC01D005C
		opword 0xD01E0004
		opword 0xC01D0060
		opword 0xD01E0008
		opword 0x48000110
		opword 0xC0210080
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041ce04(r2)
		lfs f3, float_1000_8041cdf4(r2)
		opword 0x3C004330
		opword 0x900100A0
		opword 0xEC23007A
		opword 0xC85F0108
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC20081E
		opword 0xD82100A8
		opword 0x800100AC
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC82100A0
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03E0000
		opword 0xC0210084
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041ce04(r2)
		lfs f3, float_1000_8041cdf4(r2)
		opword 0x3C004330
		opword 0x900100B8
		opword 0xEC23007A
		opword 0xC85F0108
		lfs f0, float_0_8041cdec(r2)
		opword 0xFC20081E
		opword 0xD82100B0
		opword 0x800100B4
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC82100B8
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03E0004
		opword 0xC0210088
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041ce00(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041ce04(r2)
		lfs f2, float_1000_8041cdf4(r2)
		opword 0x3C004330
		opword 0x900100C8
		opword 0xEC02007A
		opword 0xC83F0108
		opword 0xFC00001E
		opword 0xD80100C0
		opword 0x800100C4
		opword 0x6C008000
		opword 0x900100CC
		opword 0xC80100C8
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01E0008
		bl hitGetAttr
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
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

static inline void partyDownDirY(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}

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
#endif
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void party_force_reset_outofscreen(PartyEntry* party) {
	char _af_pad[112];
	asm volatile {
		opword 0x7C791B78
		lwz r24, 0x160(r3)
		bl marioCtrlOffChk
		opword 0x2C030000
		opword 0x408203DC
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x408203D0
		opword 0x80F90058
		la r3, _af_pad+40
		opword 0x8019005C
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x90E10030
		opword 0x90010034
		opword 0x80190060
		opword 0x90010038
		bl marioGetScreenPos
		opword 0xC038008C
		opword 0xC0580094
		opword 0xC0790058
		opword 0xC0990060
		bl distABf
		lfs f0, float_20_8041cdc0(r2)
		opword 0xFC010040
		opword 0x4080003C
		opword 0xC021000C
		lfs f0, float_800_8041cdc4(r2)
		opword 0xFC010040
		opword 0x4081002C
		opword 0x7F23CB78
		opword 0x3881006C
		bl partyGetAppearPos3
		opword 0x8061006C
		opword 0x80010070
		opword 0x90790058
		opword 0x9019005C
		opword 0x80010074
		opword 0x90190060
		opword 0x4800034C
		lfs f0, float_neg100_8041cdc8(r2)
		opword 0x3B400064
		opword 0xC0210010
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820028
		lfs f0, float_700_8041cdcc(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820018
		opword 0xC021000C
		lfs f0, float_650_8041cdd0(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820310
		opword 0x80190000
		opword 0x54000739
		opword 0x4082000C
		bl partyClearFootmark
		opword 0x48000008
		bl partyClearFootmark
		opword 0x83990160
		opword 0x3B600000
		opword 0x80790058
		opword 0x8019005C
		opword 0x9061006C
		opword 0x90010070
		opword 0x80190060
		opword 0x90010074
		opword 0x88190032
		opword 0x28000000
		opword 0x4082000C
		opword 0xC3D900F4
		opword 0x48000024
		opword 0x88190031
		opword 0x2C000005
		opword 0x40820010
		lfs f30, float_10_8041cdd4(r2)
		opword 0x3B400046
		opword 0x4800000C
		lfs f30, float_10_8041cdd4(r2)
		opword 0x3B400032
		lis r4, vec3_802f3ef4@ha
		lis r3, double_to_int_802f3f48@ha
		addi r6, r4, vec3_802f3ef4@l
		opword 0x7CFA00D0
		opword 0x80A60000
		opword 0x3BA10074
		opword 0x80860004
		opword 0x6CFE8000
		opword 0x80060008
		opword 0x3FE04330
		opword 0x90A10054
		lfs f27, float_100_8041cde0(r2)
		opword 0x90810058
		lfs f28, float_50_8041cde8(r2)
		opword 0x9001005C
		lfs f29, float_0_8041cdec(r2)
		lfs f26, float_300_8041cddc(r2)
		lfd f31, double_to_int_802f3f48@l(r3)
		opword 0x80C1006C
		opword 0x38610024
		opword 0x80E10070
		opword 0x38810010
		opword 0x80010074
		opword 0x38A1000C
		opword 0x90C10024
		opword 0x38C10008
		opword 0x90E10028
		opword 0x9001002C
		bl marioGetScreenPos
		opword 0x93C1007C
		opword 0xC0410010
		opword 0x93E10078
		opword 0xC8010078
		opword 0xEC00F828
		opword 0xFC001040
		opword 0x4C401382
		opword 0x40820050
		opword 0x387A0258
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802f3f48@ha
		opword 0x9061007C
		lfd f1, double_to_int_802f3f48@l(r4)
		opword 0x90010078
		opword 0xC8010078
		opword 0xEC000828
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0x8061006C
		opword 0x80010070
		opword 0x90790058
		opword 0x9019005C
		opword 0x80010074
		opword 0x90190060
		opword 0x480001C4
		opword 0x2C1B0064
		opword 0x418101BC
		opword 0xC021006C
		opword 0xC0410074
		opword 0xC07C008C
		opword 0xC09C0094
		bl angleABf
		opword 0xFC000890
		opword 0x7FA4EB78
		opword 0xFC20F090
		opword 0x3861006C
		opword 0xFC400090
		bl movePos
		lfs f24, float_200_8041cdd8(r2)
		opword 0x3B000000
		opword 0xC3210070
		opword 0x80010070
		opword 0x7F23CB78
		opword 0x8121006C
		opword 0x38810060
		opword 0x90010064
		opword 0x38A10054
		opword 0x80010074
		opword 0x38C10048
		opword 0xC0010064
		opword 0x38E1003C
		opword 0xD3410014
		opword 0x39010014
		opword 0xEC00C02A
		opword 0x91210060
		opword 0x90010068
		opword 0xD0010064
		bl partyHitCheck
		opword 0x28030000
		opword 0x41820038
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x40820010
		opword 0xC321004C
		opword 0x48000008
		opword 0xC33C0090
		opword 0xD3210064
		opword 0x38610018
		opword 0x81010060
		opword 0x38810010
		opword 0x80E10064
		opword 0x38A1000C
		opword 0x80010068
		opword 0x38C10008
		opword 0x91010018
		opword 0x90E1001C
		opword 0x90010020
		bl marioGetScreenPos
		opword 0xC001000C
		opword 0xFC00D840
		opword 0x40810098
		lfs f1, float_74_8041cde4(r2)
		opword 0xC0010070
		opword 0x8081006C
		opword 0xEC01002A
		opword 0x80610070
		opword 0x80010074
		opword 0xD3610014
		opword 0xFC00C840
		opword 0x90810060
		opword 0x90610064
		opword 0x90010068
		opword 0x40810088
		opword 0xC0010064
		opword 0x7F23CB78
		opword 0x38810060
		opword 0x38A10054
		opword 0xEC00082A
		opword 0x38C10048
		opword 0x38E1003C
		opword 0x39010014
		opword 0xD0010064
		bl partyHitCheck
		opword 0x28030000
		opword 0x41820058
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		bl hitGetAttr
		opword 0x546005AD
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x4082002C
		opword 0xC321004C
		opword 0x48000024
		opword 0x3B180001
		opword 0x2C180004
		opword 0x41810018
		opword 0xEF18E028
		opword 0xFC18E840
		opword 0x4080FE98
		opword 0xFF00E890
		opword 0x4BFFFE90
		opword 0xD3210070
		opword 0x3B7B0001
		opword 0x4BFFFDAC
	}
#endif
}
#ifndef NONMATCHING
#pragma pop























#endif

#ifdef NONMATCHING
static void partyPoseA2(PartyEntry* party) {
#else
static inline void partyPoseA2(PartyEntry* party) {
#endif
#ifdef NONMATCHING
    partyChgPose(party, "PCH_A2_1");
#endif
#ifndef NONMATCHING
    partyChgPose(party, EXT_LIT((char*)str_802F3F0C, "PCH_A2_1"));
#endif
    party->unk39 = 1;
    party->unk24 = 30;
}


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802f3e40[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e58[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e70[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e7c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e88[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3e94[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3ea0[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3eac[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3eb8[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3ec4[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3ed0[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3edc[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3ee8[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3ef4[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3f00[3] = {122.0f, 130.0f, -313.0f};
__declspec(section ".rodata") const char str_802F3F0C[] = "PCH_A2_1\0\0\0";
__declspec(section ".rodata") const char str_802F3F18[] = "gor_01\0";
__declspec(section ".rodata") const char str_802F3F20[] = "A_ie_03_yuka_f1_C\0\0";
__declspec(section ".rodata") const char str_802F3F34[] = "A_ie_03_yuka_f2_C\0\0";
__declspec(section ".rodata") const f64 double_to_int_802f3f48 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_0p5_802f3f50 = 0.5;
__declspec(section ".rodata") const f64 double_3_802f3f58 = 3.0;
__declspec(section ".rodata") const f64 double_0_802f3f60 = 0.0;
__declspec(section ".rodata") const char str_802F3F68[] = "p_roll\0";
__declspec(section ".rodata") const char str_802F3F70[] = "PM_R_1A";
__declspec(section ".rodata") const char str_802F3F78[] = "PM_R_1B";
__declspec(section ".rodata") const char str_802F3F80[] = "PM_R_1C";
__declspec(section ".rodata") const char str_802F3F88[] = "p_slit\0";
__declspec(section ".rodata") const char str_802F3F90[] = "PM_S_1A";
__declspec(section ".rodata") const char str_802F3F98[] = "PM_S_1B";
__declspec(section ".rodata") const f64 double_180_802f3fa0 = 180.0;
__declspec(section ".rodata") const char str_802F3FA8[] = "PM_S_1E";
__declspec(section ".rodata") const char str_802F3FB0[] = "PM_S_1D";
__declspec(section ".rodata") const char str_802F3FB8[] = "PM_S_1H";
__declspec(section ".rodata") const char str_802F3FC0[] = "PM_S_1C";
__declspec(section ".rodata") const char str_802F3FC8[] = "aji_02\0";
__declspec(section ".rodata") const char str_802F3FD0[] = "aji_05\0";
__declspec(section ".rodata") const char str_802F3FD8[] = "aji_12\0";
__declspec(section ".rodata") const f64 double_12_802f3fe0 = 12.0;
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

#endif