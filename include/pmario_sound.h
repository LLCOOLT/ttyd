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
    u8 unk6;               // 0x6
    u8 unk7;               // 0x7
    s16 unk8;              // 0x8
    s16 unkA;              // 0xA
} PaperSoundFade;

typedef struct PaperSoundBGM {
    u32 unk0;              // 0x0
    s32 streamId;          // 0x4, TODO verify re: seq_title
    u32 unk8;              // 0x8, flags
    u8 unkC[0x10 - 0xC];   // 0xC
    u8 unk10;              // 0x10
    u8 unk11[0x20 - 0x11]; // 0x11
    PaperSoundFade fade;   // 0x20
    u8 unk2C[0x30 - 0x2C]; // 0x2C
    s64 unk30;             // 0x30
} PaperSoundBGM;

typedef struct PaperSoundEffect {
    s32 unk0;              // 0x0
    u16 unk4;              // 0x4
    u16 unk6;              // 0x6
    u8 unk8;               // 0x8
    u8 unk9[0x12 - 0x9];   // 0x9
    u16 unk12;             // 0x12
    u16 unk14;             // 0x14
    u8 unk16[0x18 - 0x16]; // 0x16
    s32 unk18;             // 0x18
    Vec unk1C;             // 0x1C
} PaperSoundEffect;

typedef struct PaperSoundEnv {
    u8 unk0[0x4 - 0x0];  // 0x0
    s16 unk4;            // 0x4
    u8 unk6[0x24 - 0x6]; // 0x6
} PaperSoundEnv;

typedef struct PaperSoundWork {
    PaperSoundFade fade[2]; // 0x0
    u16 unk18[2];          // 0x18
    u8 unk1C[0x20 - 0x1C]; // 0x1C
    u16 unk20[2];          // 0x20
    u8 unk24;              // 0x24
    u8 unk25;              // 0x25
    s16 unk26;             // 0x26
    s16 unk28;             // 0x28
    u8 unk2A[0x30 - 0x2A]; // 0x2A
    Vec position;          // 0x30
    f32 direction;         // 0x3C
    char unk40[0x10];      // 0x40
    s16 unk50;             // 0x50
    s16 unk52;             // 0x52, reverb
    s16 unk54;             // 0x54
    u16 unk56;             // 0x56, verified u16
    s8 unk58;              // 0x58
    s8 unk59;              // 0x59
    s8 unk5A;              // 0x5A
    u8 unk5B[0x5C - 0x5B]; // 0x5B
    s8 unk5C;              // 0x5C
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
