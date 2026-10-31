// pmario_sound.c: the game's sound API (psnd*): BGM, ENV and sound effects (PaperSoundWork and its entry structs).
#pragma once

#include <dolphin/mtx.h>
#include "version.h"

/* typedef union SoundData {
    const char* name;
    s32 value;
} SoundData; */

typedef struct SoundEnvList {
    u16 id;          // 0x0, psenvlistname index; 0x76 ends the list
    u16 sfxId;       // 0x2, ORed with 0x4/0x5/0x6000000 and passed to __psndSFXOn as the name
    u8 volume;       // 0x4
    u8 reserved_05;  // 0x5, copied into PaperSoundEnv+0x7 by psndENVOn_f_d, never read (0 in every entry)
    u8 type;         // 0x6, 0: random position + interval, 1: loop, 2: interval, 3: one-shot
    u8 intervalRand; // 0x7, seconds, irand(intervalRand) added to interval
    u8 interval;     // 0x8, seconds between plays (types 0 and 2)
    Vec pos;         // 0xC, copied to the PaperSoundEnv position
    u8 radiusMin;    // 0x18, type 0 spawn radius = (radiusMin + irand(radiusRange)) * 10
    u8 radiusRange;  // 0x19
    u8 dist;         // 0x1A, __psndSFXOn dist
    // pad 1 byte
} SoundEnvList;

// The top bits of SoundEffectEntry.fxId and SoundBGMEntry.flags say what kind of sound the entry plays.
// The code tests SFX_FLAG_STREAM, then SFX_FLAG_SONG; anything else is played as a MusyX sound effect.
typedef enum SoundEffectFlags {
    SFX_FLAG_EFFECT = (1 << 29), // MusyX sound effect, low 16 bits are the SND_FXID (the bit itself is never tested)
    SFX_FLAG_SONG = (1 << 30),   // MusyX song, played with SoundSongPlayCh(fxId & 0x0FFFFFFF)
    SFX_FLAG_STREAM = (1 << 31)  // streamed .stm file (SoundSSPlayCh), the name is the third field
} SoundEffectFlags;

// a MusyX sound effect id
#define SFX_EFFECT(fxId) (SFX_FLAG_EFFECT | (fxId))
// a MusyX song: SoundSongPlayCh takes group << 16 | song << 8 | the loaded group slot to look up, which is the song
// number in every table entry
#define SFX_SONG(group, song) (SFX_FLAG_SONG | ((group) << 16) | ((song) << 8) | (song))

// most fields are translated in __psndSFXOn
typedef struct SoundEffectEntry {
    const char* name;       // 0x0, sfx name
    u32 fxId;               // 0x4, SFX_EFFECT(id) or SFX_SONG(group, song) (SoundEffectFlags in the top bits)
    const char* streamName; // 0x8, the sound's label in the sound project (SE1_...), the .stm name for a stream
    u8 volume;              // 0xC
    u8 pan;                 // 0xD
    u8 specialFlag;         // 0xE, 1 sets PaperSoundEffect flag 0x200
    u8 reverb;              // 0xF, aux/reverb send
    u8 priority;            // 0x10, an existing SFX with a higher priority is not stolen
    u8 delay;               // 0x11, start delay frames
    s16 pitch;              // 0x12, signed (0xFAAB etc. are downward shifts)
} SoundEffectEntry;

// Bits a sound effect id can carry above the pssfxlist index (low 13 bits). The ENV player and some callers add them
// to the id they pass as the name; __psndSFXOn and calc3D read them.
typedef enum PaperSoundIdBits {
    PSND_ID_DOOR_MUTE = 0x10000,     // PSND_SFX_DOOR_MUTE: silent while PSND_FLAG_MUTE_DOOR_SFX is set
    PSND_ID_EXEMPT = 0x20000,        // PSND_SFX_EXEMPT
    PSND_ID_KEEP = 0x40000,          // PSND_SFX_KEEP (not in the demo)
    PSND_ID_RELATIVE = 0x1000000,    // the position is relative to the listener
    PSND_ID_AT_LISTENER = 0x2000000, // the sound plays at the listener position
    PSND_ID_ENV = 0x4000000          // started by the ENV player (PSND_SFX_ENV)
} PaperSoundIdBits;

// PaperSoundEffect.flags
typedef enum PaperSoundEffectFlags {
    PSND_SFX_PENDING = 0x1,     // not started yet: psndSFXMain starts it once its delay has run out
    PSND_SFX_3D = 0x2,          // volume, pan and surround pan come from calc3D every frame
    PSND_SFX_POSITION = 0x4,    // started with a position and a nonzero r8 argument (never read)
    PSND_SFX_WITH_BGM = 0x10,   // started while PSND_FLAG_SFX_WITH_BGM was set: L_psndBGM_stop stops it
    PSND_SFX_ENV = 0x20,        // an ENV sound (PSND_ID_ENV)
    PSND_SFX_FADE_OUT = 0x40,   // fading out with the global SFX fade, stopped at volume 0
    PSND_SFX_KEEP = 0x80,       // not faded out by psndSFXAllOff (map change)
    PSND_SFX_NEW = 0x100,       // started this frame: another start of the same sound is delayed 8 frames
    PSND_SFX_SPECIAL = 0x200,   // SoundEffectEntry.specialFlag == 1: not silenced by PSND_FLAG_MUTE_SFX
    PSND_SFX_DOOR_MUTE = 0x400, // PSND_ID_DOOR_MUTE: silent while PSND_FLAG_MUTE_DOOR_SFX is set
    PSND_SFX_EXEMPT = 0x800     // PSND_ID_EXEMPT: neither silenced by PSND_FLAG_MUTE_SFX nor stopped by L_psndBGM_stop
} PaperSoundEffectFlags;

// PaperSoundWork.flags (psndSetFlag, psndClearFlag)
typedef enum PaperSoundFlags {
    PSND_FLAG_BGM_OFF = 0x1,         // BGM stopped and psndBGMOn refused
    PSND_FLAG_ENV_OFF = 0x2,         // ENV stopped and psndENVOn refused
    PSND_FLAG_SFX_OFF = 0x4,         // psndSFXOn refused (psndSFXOn_ still plays)
    PSND_FLAG_SFX_WITH_BGM = 0x10,   // new SFX get PSND_SFX_WITH_BGM; cleared by L_psndBGM_stop
    PSND_FLAG_IDLE_MIX = 0x20,       // camera idle zoom: BGM 65%, SFX 120%, ENV 80% of the normal volume
    PSND_FLAG_IDLE_MIX_OFF = 0x40,   // overrides PSND_FLAG_IDLE_MIX
    PSND_FLAG_MUTE_SFX = 0x80,       // silences the SFX without PSND_SFX_WITH_BGM/ENV/SPECIAL/EXEMPT (item get)
    PSND_FLAG_MUTE_DOOR_SFX = 0x100, // silences PSND_SFX_DOOR_MUTE sounds (snd_door_in); cleared by psndMapChange
    // Not read by the sound code: seq_mapchange holds the next map's setup until BGM channel 0 (1) has played
    // 3000 ms, then clears the flag (3000 us in the demo, whose psndBGMPlayTime counts microseconds).
    PSND_FLAG_WAIT_BGM_0 = 0x1000, // set by the bgm_wait_stop script functions (end_00, rsh_02)
    PSND_FLAG_WAIT_BGM_1 = 0x2000  // nothing sets it
} PaperSoundFlags;

// Flag word of psndBGMOn/psndBGMOff/psndENVOn/psndENVOff, their _f/_f_d forms and the evt_snd_bgmon/bgmoff/envon/
// envoff(_f) script functions. Bits 0-3 pick the channel (psbgm[] / psnd.envId[] index, PSND_CH), bits 12-15 the dip
// level (PSND_FADE_DIP_TO). An Off call with none of FADE_OUT/HOLD/DIP stops the channel at once.
// The fade time is a separate argument (1000 ms for psndBGMOn/Off and psndENVOn/Off).
typedef enum PaperSoundFadeFlags {
    PSND_FADE_RESTART = 0x10,  // On: start the named sound even when it (or a BGM of the same group) already plays on
                               // the channel, and skip PSND_FADE_RESUME; for a new stream BGM the old one fades in 100 ms
    PSND_FADE_RESUME = 0x20,   // On: keep what plays on the channel (continue a paused BGM) and apply FADE_IN/UNDIP to it
    PSND_FADE_DIP_FAST = 0x40, // BGM: the dip and undip move 5 steps a frame (kept in PaperSoundBGM.flags; always after
                               // a save is loaded); US/PAL psndENVOff_f_d: the ENV dips at once
    PSND_FADE_UNDIP = 0x80,    // On with PSND_FADE_RESUME: raise a dipped channel back to full volume over the fade time
    PSND_FADE_IN = 0x100,      // On: fade in over the fade time (without it: full volume at once)
    PSND_FADE_OUT = 0x200,     // Off: fade out over the fade time, then stop. The On functions do not test it (they fade
                               // the old BGM out anyway), but most scripts pass it to evt_snd_bgmon
    PSND_FADE_HOLD = 0x400,    // Off: fade to silence but keep the channel; PSND_FADE_RESUME continues it
    PSND_FADE_DIP = 0x800      // Off: lower the volume to the PSND_FADE_DIP_TO level over the fade time
} PaperSoundFadeFlags;
#define PSND_CH(ch) (ch)
// PSND_FADE_DIP to percent (10-100 in steps of 10) of the normal volume: bits 12-15 index silent_tbl
#define PSND_FADE_DIP_TO(percent) (PSND_FADE_DIP | (((percent) / 10 - 1) << 12))

typedef struct PaperSoundFade {
    u8 state;       // 0x0
    u8 pad_01;      // 0x1, never accessed
    s16 time;       // 0x2
    s16 timeMax;    // 0x4
    u8 dipState;    // 0x6, partial volume dip: 8 = going down (psndBGMOff_f_d), 0x10 = coming back (psndBGMOn_f_d), 0 = idle
    u8 dipPercent;  // 0x7, dip target volume in percent
    s16 dipTimeMax; // 0x8, dip length in frames (fadetime / 16.67)
    s16 dipTime;    // 0xA, current dip level, steps toward dipTimeMax * dipPercent / 100
} PaperSoundFade;

typedef struct PaperSoundBGM {
    u32 listId;             // 0x0, index into psbgmlist, 0xFFFFFFFF = idle
    s32 streamId;           // 0x4, sound stream/song channel
    u32 flags;              // 0x8, PaperSoundFadeFlags of the psndBGMOn call; only PSND_FADE_DIP_FAST is read
    u8 pad_0C;              // 0xC, never accessed
    u8 group;               // 0xD, SoundBGMEntry params byte 2; a new BGM in the same nonzero group keeps playing
    u8 volume;              // 0xE, base volume from SoundBGMEntry
    u8 pan;                 // 0xF
    u8 scopeTimer;          // 0x10, psndBGMScope: 0xFF = full scope, 0 = none, else counts down
    u8 pad_11[0x20 - 0x11]; // 0x11
    PaperSoundFade fade;    // 0x20
    u8 pad_2C[0x30 - 0x2C]; // 0x2C
    s64 startTime;          // 0x30, gp->renderTime when started (psndBGMPlayTime)
} PaperSoundBGM;

typedef struct PaperSoundEffect {
    u32 listId;      // 0x0, searchPSSFXList id, 0xFFFFFFFF = free slot
    u16 serial;      // 0x4, psnd.sfxSerial at start (checked against the id handed out)
    u16 flags;       // 0x6
    u8 volume;       // 0x8
    u8 entryVolume;  // 0x9, SoundEffectEntry volume, scales volume
    u8 pan;          // 0xA
    u8 reverb;       // 0xB
    u16 priority;    // 0xC, SoundEffectEntry priority
    u16 delay;       // 0xE, start delay frames
    u16 attenuation; // 0x10, subtracted from the scaled volume
    u16 dist;        // 0x12, 3D attenuation distance (psndSFX_dist)
    s16 pitch;       // 0x14 (psndSFX_pit)
    u16 lpf;         // 0x16, low-pass value set from PaperSoundWork.envLpf
    u32 channel;     // 0x18, sound effect/stream channel, -1 = none
    Vec position;    // 0x1C, 3D source position (psndSFX_pos)
} PaperSoundEffect;

typedef struct PaperSoundEnv {
    u32 sfxId;       // 0x0, SoundEnvList sfxId, ORed with 0x4/0x5/0x6000000 for __psndSFXOn
    u16 id;          // 0x4, SoundEnvList id, 0 = free slot
    u8 volume;       // 0x6
    u8 reserved_07;  // 0x7, copied from SoundEnvList reserved_05, never read
    u8 type;         // 0x8, 0: random position + interval, 1: loop, 2: interval, 3: one-shot
    u8 intervalRand; // 0x9, seconds
    u8 interval;     // 0xA, seconds
    u8 radiusMin;    // 0xB, type 0 spawn radius = (radiusMin + irand(radiusRange)) * 10
    u8 radiusRange;  // 0xC
    u8 state;        // 0xD
    u16 timer;       // 0xE, frames until the next play
    u16 dist;        // 0x10, __psndSFXOn dist
    u16 pad_12;      // 0x12, never accessed
    u32 sfx;         // 0x14, playing SFX handle, 0xFFFFFFFF = none
    Vec position;    // 0x18
} PaperSoundEnv;

typedef struct PaperSoundWork {
    PaperSoundFade fade[2];         // 0x0
    u16 envId[2];                   // 0x18, active ENV id per channel (psndENVOn/Off)
    u16 envLpf[2];                  // 0x1C, ENV low-pass per channel, set to 0x7D00 and ramped toward envFreq
    u16 envFreq[2];                 // 0x20, ENV play frequency per channel (default 0x7D00)
    u8 sfxFadeState;                // 0x24, global SFX fade (2 = fading out, 0 = idle)
    u8 pad_25;                      // 0x25
    s16 sfxFadeMax;                 // 0x26, fade length in frames
    s16 sfxFadeTime;                // 0x28, frames left
    u8 pad_2A[0x30 - 0x2A];         // 0x2A
    Vec position;                   // 0x30
    f32 direction;                  // 0x3C
    char mapName[0x10];             // 0x40, map the sound state was set up for (psndMapChange)
    u16 sfxSerial;                  // 0x50, incremented per SFX start, packed into SFX ids
    u16 reverb;                     // 0x52, psndSetReverb level (0/20/40/60)
    u16 sfxDelay;                   // 0x54, +8 for each repeat of a SFX already playing this frame, reset each frame
    u16 flags;                      // 0x56, psndSetFlag/psndClearFlag/psndGetFlag
    s8 bgmVolume;                   // 0x58, BGM master volume, ramps toward 100 (65 when flag 0x20)
    s8 sfxVolume;                   // 0x59, SFX master volume, ramps toward 100 (120 when flag 0x20)
    s8 envVolume;                   // 0x5A, ENV master volume, ramps toward 100 (80 when flag 0x20)
    u8 sfxActiveCount[0x5C - 0x5B]; // 0x5B, active PaperSoundEffect slots counted by psndSFXMain
#if VERSION >= VERSION_JP
    s8 sfxCooldown;         // 0x5C, frames before certain repeating SFX may restart (set to 6)
    u8 pad_5D[0x60 - 0x5D]; // 0x5D
#endif
} PaperSoundWork;

s32 searchPSSFXList(const char* name);
void psndInit(void);
void psndMain(void);
void psndMainInt(void);
void psndExit(void);

BOOL psndPushGroup(void);

BOOL psndBGMOn(u32 r3, char* bgm_name);
BOOL psndBGMOn_f(u32 flags, char* bgm_name, u32 fadetime, s32 unused);
#if VERSION <= VERSION_DEMO_JP
BOOL psndBGMOn_f_d(u32 flags, char* bgm_name, u32 fadetime, s32 unused); // the demo always fades the old BGM out over 750 ms
#else
BOOL psndBGMOn_f_d(u32 flags, char* bgm_name, u32 fadetime, u32 fadeout, s32 unused);
#endif
BOOL psndENVOn_f_d(u32 flags, const char* name, u32 fadetime, s32 unused);
void psndStopAllFadeOut(void);
BOOL psndENVOff(u32 r3);
void psndSFXAllOff(void);

#include "sfx_name_word.h"

s32 psndSFXOn(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);
s32 psndSFXOnEx_3D(const char* name, Vec* position, u8 vol, u8 pan, u16 pitch, u16 dist);

BOOL psndBGMOff_f_d(s32 flags, u32 fadetime, u32 someswitch);
BOOL psndBGMStartCheck(s32 id);

void psndSetFlag(s32 flag);
void psndSFXOff(s32 id);
void L_psndBGM_stop(void);
void psndClearFlag(s32 flag);

void psndSetPosDirListener(Vec* position, f32 direction);

extern PaperSoundBGM psbgm[2];

BOOL psndBGMOff(u32 flags);
s32 psndGetFlag(void);
void psndSFX_pos(s32 id, Vec* position);

void psndSetReverb(s32 mode);
void psndMapChange(void);
void psndBGM_rate(s32 id, u16 rate);
void psndBGMScope(s32 id, s32 scope);
s32 psndBGMPlayTime(s32 id);
s32 psndSFXOn_(const char* name);
s32 psndSFXOnVol(const char* name, u8 vol);
void psndSFX_dist(s32 id, u16 dist);
void psndSFX_pit(s32 id, s16 pitch);
s32 psndSFXChk(s32 id);
u8 psndSFX_get_vol(s32 id);
s32 psndBGMChk(s32 id);
BOOL psndENV_LPF(s32 id, u16 freq);
u32 psndBGMChkSilent(s32 id);
BOOL psndENVOff_f_d(u32 flags, u32 fadetime, s32 unused);
BOOL psndENVOn(u32 flags, const char* name);
void psndSFX_vol(s32 id, u8 vol);
