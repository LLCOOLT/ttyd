#pragma once

#include <dolphin/mtx.h>

/* typedef union SoundData {
    const char* name;
    s32 value;
} SoundData; */

typedef struct SoundEnvList {
    u16 field_0x0;  // 0x0
    u16 field_0x2;  // 0x2
    u8 field_0x4;   // 0x4
    u8 field_0x5;   // 0x5
    u8 field_0x6;   // 0x6
    u8 field_0x7;   // 0x7
    u8 field_0x8;   // 0x8
    u32 field_0xC;  // 0xC
    u32 field_0x10; // 0x10
    u32 field_0x14; // 0x14
    u8 field_0x18;  // 0x18
    u8 field_0x19;  // 0x19
    u8 field_0x1A;  // 0x1A
    // pad 1 byte
} SoundEnvList;

typedef enum SoundEffectFlags {
    SFX_FLAG_2 = (1 << 29),
    SFX_FLAG_4 = (1 << 30),
    SFX_FLAG_8 = (1 << 31)
} SoundEffectFlags;

// most are translated in __psndSFXOn, TODO
typedef struct SoundEffectEntry {
    const char* name;      // 0x0, sfx name
    u32 field_0x4;         // 0x4, lower 2 bytes are SND_FXID
    const char* field_0x8; // 0x8, .stm name
    u8 field_0xC;          // 0xC
    u8 field_0xD;          // 0xD
    u8 field_0xE;          // 0xE
    u8 field_0xF;          // 0xF, reverb
    u8 field_0x10;         // 0x10
    u8 field_0x11;         // 0x11
    u16 field_0x12;        // 0x12
} SoundEffectEntry;

typedef struct PaperSoundFade {
    u8 state;              // 0x0
    u8 unk1;               // 0x1
    s16 time;              // 0x2
    s16 timeMax;           // 0x4
    u8 dipState;           // 0x6, partial volume dip: 8 = going down (psndBGMOff_f_d), 0x10 = coming back (psndBGMOn_f_d), 0 = idle
    u8 dipPercent;         // 0x7, dip target volume in percent
    s16 dipTimeMax;        // 0x8, dip length in frames (fadetime / 16.67)
    s16 dipTime;           // 0xA, current dip level, steps toward dipTimeMax * dipPercent / 100
} PaperSoundFade;

typedef struct PaperSoundBGM {
    u32 listId;            // 0x0, index into psbgmlist, 0xFFFFFFFF = idle
    s32 streamId;          // 0x4, sound stream/song channel
    u32 flags;             // 0x8, psndBGMOn flags (0x40 = paused/muted)
    u8 unkC;               // 0xC
    u8 unkD;               // 0xD, from SoundBGMEntry byte 2
    u8 volume;             // 0xE, base volume from SoundBGMEntry
    u8 pan;                // 0xF
    u8 scopeTimer;         // 0x10, psndBGMScope: 0xFF = full scope, 0 = none, else counts down
    u8 unk11[0x20 - 0x11]; // 0x11
    PaperSoundFade fade;   // 0x20
    u8 unk2C[0x30 - 0x2C]; // 0x2C
    s64 startTime;         // 0x30, gp->renderTime when started (psndBGMPlayTime)
} PaperSoundBGM;

typedef struct PaperSoundEffect {
    s32 listId;            // 0x0, searchPSSFXList id, 0xFFFFFFFF = free slot
    u16 serial;            // 0x4, psnd.sfxSerial at start (checked against the id handed out)
    u16 flags;             // 0x6
    u8 volume;             // 0x8
    u8 unk9[0x12 - 0x9];   // 0x9
    u16 dist;              // 0x12, 3D attenuation distance (psndSFX_dist)
    u16 pitch;             // 0x14 (psndSFX_pit)
    u8 unk16[0x18 - 0x16]; // 0x16
    s32 channel;           // 0x18, sound effect/stream channel, -1 = none
    Vec position;          // 0x1C, 3D source position (psndSFX_pos)
} PaperSoundEffect;

typedef struct PaperSoundEnv {
    u8 unk0[0x4 - 0x0];  // 0x0
    s16 unk4;            // 0x4
    u8 unk6[0x24 - 0x6]; // 0x6
} PaperSoundEnv;

typedef struct PaperSoundWork {
    PaperSoundFade fade[2]; // 0x0
    u16 envId[2];          // 0x18, active ENV id per channel (psndENVOn/Off)
    u8 unk1C[0x20 - 0x1C]; // 0x1C
    u16 envFreq[2];        // 0x20, ENV play frequency per channel (default 0x7D00)
    u8 sfxFadeState;       // 0x24, global SFX fade (2 = fading out, 0 = idle)
    u8 unk25;              // 0x25
    s16 sfxFadeMax;        // 0x26, fade length in frames
    s16 sfxFadeTime;       // 0x28, frames left
    u8 unk2A[0x30 - 0x2A]; // 0x2A
    Vec position;          // 0x30
    f32 direction;         // 0x3C
    char mapName[0x10];    // 0x40, map the sound state was set up for (psndMapChange)
    s16 sfxSerial;         // 0x50, incremented per SFX start, packed into SFX ids
    s16 reverb;            // 0x52, psndSetReverb level (0/20/40/60)
    s16 unk54;             // 0x54
    u16 flags;             // 0x56, psndSetFlag/psndClearFlag/psndGetFlag
    s8 bgmVolume;          // 0x58, BGM master volume, ramps toward 100 (65 when flag 0x20)
    s8 sfxVolume;          // 0x59, SFX master volume, ramps toward 100 (120 when flag 0x20)
    s8 envVolume;          // 0x5A, ENV master volume, ramps toward 100 (80 when flag 0x20)
    u8 unk5B[0x5C - 0x5B]; // 0x5B
    s8 sfxCooldown;        // 0x5C, frames before certain repeating SFX may restart (set to 6)
    u8 unk5D[0x60 - 0x5D]; // 0x5D
} PaperSoundWork;

s32 searchPSSFXList(const char* name);
void psndInit(void);
void psndMain(void);
void psndMainInt(void);
void psndExit(void);

BOOL psndPushGroup(void);

BOOL psndBGMOn(u32 r3, char* bgm_name);
void psndStopAllFadeOut(void);
BOOL psndENVOff(u32 r3);
void psndSFXAllOff(void);

void psndSFXOn(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);

BOOL psndBGMOff_f_d(s32 flags, u32 fadetime, u32 someswitch);
BOOL psndBGMStartCheck(s32 id);

void psndSetFlag(s32 flag);
void psndSFXOff(s32 id);
void L_psndBGM_stop(void);
void psndClearFlag(s32 flag);

void psndSetPosDirListener(Vec* position, f32 direction);

extern PaperSoundBGM psbgm[2];
