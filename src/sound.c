// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on
#define _MATH_H_ // skip math.h (its sqrtf statics are not in this TU)
#include "sound.h"
#include <dolphin/os.h>
#include "manager/dvdmgr.h"
#include "memory.h"
#include "musyx/musyx.h"
#include "system.h"
double sin(double);
double cos(double);
#include <string.h>
#ifndef NONMATCHING
__declspec(section ".rodata") extern const u32 jumptable_802E5710[2];
__declspec(section ".rodata") extern const f64 double_to_int_mask_802e5718;
__declspec(section ".rodata") extern const f64 double_to_int_802e5720;
__declspec(section ".rodata") extern const char str_802E5728[];
__declspec(section ".sdata2") extern const f32 float_0_8041b6d8;
__declspec(section ".sdata2") extern const f32 float_63_8041b6dc;
__declspec(section ".sdata2") extern const f32 float_16p667_8041b6e0;
__declspec(section ".sdata2") extern const f32 float_1_8041b6e4;
__declspec(section ".sdata2") extern const f32 float_127_8041b6e8;
__declspec(section ".sdata2") extern const char str_8041B6EC[];
__declspec(section ".sdata2") extern const f32 float_6p2832_8041b6f4;
__declspec(section ".sdata2") extern const f32 float_360_8041b6f8;
__declspec(section ".sdata2") extern const char str_8041B6FC[];
__declspec(section ".sdata2") extern const char str_8041B704[];
__declspec(section ".sdata2") extern const char str_8041B70C[];
__declspec(section ".sdata2") extern const char str_8041B714[];
__declspec(section ".sdata2") extern const char str_8041B71C[];
__declspec(section ".sdata2") extern const char str_8041B724[];
__declspec(section ".sdata2") extern const char str_8041B72C[];
__declspec(section ".sdata2") extern const f32 float_3_8041b734;
__declspec(section ".sdata2") extern const f32 float_0p1_8041b738;
__declspec(section ".sdata2") extern const f32 float_0p3_8041b73c;
__declspec(section ".sdata2") extern const f32 float_0p8_8041b740;
__declspec(section ".sdata2") extern const f32 float_2_8041b744;
__declspec(section ".sdata2") extern const f32 float_0p5_8041b748;
#define EXT_LIT(sym, val) (sym)

#endif
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
__declspec(section ".sdata") u32 gap_08_80418924_sbss[1];
__declspec(section ".data") u32 gap_06_803DB7AC_bss[1];

// TODO: use SoundInit to fill in SoundStream/Entry

extern int sprintf(char* str, const char* format, ...);

//.bss
#ifdef NONMATCHING
SND_AUX_REVERBHI revH;
SND_AUX_REVERBSTD revS;
SND_AUX_CHORUS cho;
SND_AUX_DELAY dly;
SoundWork sound;
#else
extern SND_AUX_REVERBHI revH;
extern SND_AUX_REVERBSTD revS;
extern SND_AUX_CHORUS cho;
extern SND_AUX_DELAY dly;
extern SoundWork sound;
#ifndef NONMATCHING
extern u8 g5_str_s436[256];
#endif
#endif

//.sbss
u32 aramMemArray[8];

#ifdef NONMATCHING
static inline char* _ssGetStr(void) {
    static char str[0x100];
    return str;
}
#else
static inline char* _ssGetStr(void) {
    return (char*)g5_str_s436;
}
#endif
#define str _ssGetStr()

// local prototypes
void* sndMalloc(size_t size);
void sndFree(void* ptr);
void* loadDVD_callback(u32 offset, u32 length);
void SoundEfxMain(void);
void SoundDVDMain(void);

void SoundSSMainInt(void);
void SoundSSMain(void);

void SoundAIDMACallback(void);

#ifdef NONMATCHING
void* sndMalloc(size_t size) {
    return __memAlloc(HEAP_DEFAULT, size);
#endif
#ifndef NONMATCHING
void* sndMalloc(size_t size);

void sndFree(void* ptr);

u32 AIGetStreamSampleCount(void);
void AIInit(u8* stack);
AIDCallback AIRegisterDMACallback(AIDCallback callback);
void AISetStreamPlayState(u32 state);
void AISetStreamVolLeft(u8 vol);
void AISetStreamVolRight(u8 vol);
u32 ARAlloc(u32 length);
u32 ARInit(u32* stack_index_addr, u32 num_entries);
void ARQInit(void);
void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority, u32 source, u32 dest, u32 length,
                    ARQCallback callback);
void DCInvalidateRange(void* addr, u32 nBytes);
s32 DVDCancelStream(DVDCommandBlock* block);
BOOL DVDClose(DVDFileInfo* fileInfo);
BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
bool sndAuxCallbackPrepareChorus(SND_AUX_CHORUS* ch);
bool sndAuxCallbackPrepareDelay(SND_AUX_DELAY* delay);
bool sndAuxCallbackPrepareReverbHI(SND_AUX_REVERBHI* rev);
bool sndAuxCallbackPrepareReverbSTD(SND_AUX_REVERBSTD* rev);
bool sndCheckEmitter(SND_EMITTER* em);
SND_VOICEID sndEmitterVoiceID(SND_EMITTER* em);
SND_VOICEID sndFXCheck(SND_VOICEID vid);
bool sndFXKeyOff(SND_VOICEID vid);
s32 sndInit(u8 voices, u8 music, u8 sfx, u8 studios, u32 flags, u32 aramSize);
void sndOutputMode(SND_OUTPUTMODE mode);
bool sndRemoveEmitter(SND_EMITTER* em);
void sndSetAuxProcessingCallbacks(u8 studio,
                                  void (*auxA)(u8 reason, SND_AUX_INFO* info, void* user),
                                  void* userA, u8 midiA, SND_SEQID seqIDA,
                                  void (*auxB)(u8 reason, SND_AUX_INFO* info, void* user),
                                  void* userB, u8 midiB, SND_SEQID seqIDB);
void sndSetHooks(SND_HOOKS* hooks);
bool sndStreamActivate(SND_STREAMID stid);
SND_STREAMID sndStreamAllocEx(u8 prio, void* buffer, u32 samples, u32 frq, u8 vol, u8 pan, u8 span,
                              u8 auxa, u8 auxb, u8 studio, u32 flags,
                              u32 (*updateFunction)(void* buffer1, u32 len1, void* buffer2,
                                                    u32 len2, u32 user),
                              u32 user, SND_ADPCMSTREAM_INFO* adpcmInfo);
u32 sndStreamAllocLength(u32 num, u32 flags);
void sndStreamFree(SND_STREAMID stid);
void sndStreamMixParameter(SND_STREAMID stid, u8 vol, u8 pan, u8 span, u8 fxvol);
bool sndUpdateEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, u8 maxVol,
                      SND_ROOM* room);
bool sndUpdateListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading,
                       SND_FVECTOR* up, u8 vol, SND_ROOM* room);
void sndVolume(u8 volume, u16 time, u8 volGroup);
u8* ssDecodeDPCM(SoundStream* stream, SoundStreamEntry* entry, s16* out, u32 count, u8* src);
void SoundInit(void);

void SoundMain(void);

void SoundMainInt(void);

void SoundSetFadeTime(u16 in, u16 out);

void* loadDVD_callback(u32 offset, u32 bytes);

BOOL SoundLoadDVD2(const char* path);

BOOL SoundLoadDVD2PushGroup(u8* groupIds);

void SoundLoadDVD2Free(void);

BOOL SoundSLibLoadDVD(const char* path);

static inline void _ssDropStop(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        SoundSong* song = &sound.songs[i];
        if (sndSeqGetValid(song->seqId)) {
            sndSeqStop(song->seqId);
            song->seqId = (SND_SEQID)-1;
        }
    }
    for (i = 0; i < 40; i++) {
        SoundEffect* effect = &sound.effects[i];
        if (effect->flags) {
            sndFXKeyOff(effect->voiceId);
            if (effect->flags & 0x10) {
                sndRemoveEmitter(&effect->emitter);
            }
            effect->flags = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        SoundDVD* dvd = &sound.dvds[i];
        if (dvd->flags & 3) {
            AISetStreamPlayState(0);
            dvd->flags = 0;
            sound.unkFC = -1;
            DVDCancelStream(&dvd->info.cb);
            DVDClose(&dvd->info);
        }
    }

    for (i = 0; i < 3; i++) {
        SoundStream* stream;
        if (sound.streams[i].flags) {
            stream = &sound.streams[i];
            if (!sound.unk20C) {
                sound.interrupts = OSDisableInterrupts();
            }
            sound.unk20C++;
            if (stream->flags & 0x400) {
                sound.slotUsed[stream->slot] = 0;
            }
            stream->flags = 0;
            DVDMgrClose(stream->entries[0].dvd);
            DVDMgrClose(stream->entries[1].dvd);
            sndStreamFree(stream->entries[0].streamId);
            if (stream->count == 2) {
                sndStreamFree(stream->entries[1].streamId);
            }
            if (sound.unk20C) {
                if (!--sound.unk20C) {
                    OSRestoreInterrupts(sound.interrupts);
                }
            }
            sound.unk104 = -1;
        }
    }
#endif
}

#ifdef NONMATCHING
void sndFree(void* ptr) {
    __memFree(HEAP_DEFAULT, ptr);
#endif
#ifndef NONMATCHING
BOOL SoundDropData(void);

void SoundSetOutputMode(SND_OUTPUTMODE mode);

void SoundOpenCover(void);

void SoundCloseCover(void);

inline SoundGroup* SoundSongGetGroup(u8 a1) {
    u16 temp = a1;
    SoundGroup* group;

    for (group = sound.groups;; group = group->next) {
        if (group == 0) {
            return 0;
        }
        if (group->unk2 == temp) {
            break;
        }
    }
    return group;
#endif
}

#ifdef NONMATCHING
void SoundInit(void) { // 1:1, assuming sndMalloc inlines
    SND_HOOKS hooks = (SND_HOOKS){ sndMalloc, sndFree };
    void* data;
    SoundStream* streams;
    SoundSong* songs;
    SoundDVD* dvds;
    SoundEffect* effects;
    int i;
    SoundStream* temp;
    SoundSong* tempsong;
    SoundDVD* tempdvd;
    void* ptr;
    u32 size;
    SoundTemp* slot;
#endif
#ifndef NONMATCHING
void SoundSongPlayCh(s32 chan, u32 a2);
#endif

#ifdef NONMATCHING
    ARInit(aramMemArray, 8);
    ARQInit();
    AIInit(0);
    ARAlloc(0xBFC000); // 12MB-16KB (reserved)
    sndSetHooks(&hooks);
    sndInit(0x40, 0xC, 0x2C, 1, 1, 0xBFC000);
    revH.tempDisableFX = 0;
    revH.time = 3.0f;
    revH.preDelay = 0.1f;
    revH.damping = 0.3f;
    revH.coloration = 0.0f;
    revH.crosstalk = 0.0f;
    revH.mix = 0.8f;
    sndAuxCallbackPrepareReverbHI(&revH);
    revS.tempDisableFX = 0;
    revS.time = 2.0f;
    revS.preDelay = 0.1f;
    revS.damping = 0.5f;
    revS.coloration = 0.5f;
    revS.mix = 0.5f;
    sndAuxCallbackPrepareReverbSTD(&revS);
    cho.baseDelay = 10;
    cho.variation = 0;
    cho.period = 500;
    sndAuxCallbackPrepareChorus(&cho);
    dly.delay[0] = 60;
    dly.delay[1] = 90;
    dly.delay[2] = 70;
    dly.feedback[0] = 20;
    dly.feedback[1] = 20;
    dly.feedback[2] = 20;
    dly.output[0] = 50;
    dly.output[1] = 50;
    dly.output[2] = 50;
    sndAuxCallbackPrepareDelay(&dly);
    sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &revH, 0xFF, 0, sndAuxCallbackChorus, &cho, 0xFF, 0);
    sndVolume(0x7F, 0, 0xFF);
    if (sound.outputMode != SND_OUTPUTMODE_STEREO) {
        sound.outputMode = SND_OUTPUTMODE_STEREO;
        sndOutputMode(SND_OUTPUTMODE_STEREO);
#endif
#ifndef NONMATCHING
void SoundSongContinueCh(s32 chan);

void SoundSongStopCh(s32 chan);

void SoundSongFadeoutCh(s32 chan);

void SoundSongFadeinCh(s32 chan);

void SoundSongSetVolCh(s32 chan, u8 vol);

u8 SoundSongGetVolCh(s32 chan);

BOOL SoundSongCheck(s32 chan);

inline void SoundEfxMuteCh(s32 chan) {
    SoundEffect* sfx = &sound.effects[chan];
    if (sfx->flags) {
        sndFXKeyOff(sfx->voiceId);
        if (sfx->flags & 0x10) {
            sndRemoveEmitter(&sfx->emitter);
        }
        sfx->flags = 0;
#endif
    }
#ifdef NONMATCHING
    sound.callback = AIRegisterDMACallback(SoundAIDMACallback);
    sound.sampleBank = 0;
    sound.sampleIndex = 0;
    sound.fadeIn = 10;
    sound.fadeOut = 500;
    sound.dataId = 0;
    sound.slibId = 0;
    sound.unk214 = 0;
    sound.slotCount = 0;
    sound.unkE8 = 0;

    data = sndMalloc(0x20000);
    sound.filedata = data;
    if (data == 0) {
        while (1)
            ;
    } // infinite loop

    sound.groups = 0;

    // force register
    tempsong = (sound.songs = sndMalloc(sizeof(SoundSong) * 4));
    songs = tempsong;
    if (songs == 0) {
        while (1)
            ;
    } // infinite loop

    for (i = 0; i < 4; i++, songs++) {
        songs->seqId = -1;
        songs->group = NULL;
    }

    effects = sndMalloc(sizeof(SoundEffect) * 40);
    sound.effects = effects;
    if (effects == 0) {
        while (1)
            ;
    } // infinite loop

    for (i = 0; i < 40; i++, effects++) {
        effects->flags = 0;
        effects->voiceId = -1;
        effects->unk2 = 0;
        effects->vol = 0x7F;
        effects->pan = 0x40;
    }

    // force register
    tempdvd = (sound.dvds = sndMalloc(sizeof(SoundDVD) * 2));
    dvds = tempdvd;
    if (dvds == 0) {
        while (1)
            ;
    } // infinite loop

    for (i = 0; i < 2; i++, dvds++) {
        dvds->flags = 0;
    }

    streams = sndMalloc(sizeof(SoundStream) * 3);
    sound.streams = streams;
    if (streams == 0) {
        while (1)
            ;
    } // infinite loop

    temp = streams;
    for (i = 0; i < 3; i++, temp++) {
        temp->flags = 0;

        ptr = sndMalloc(0x8000);
        if (ptr == 0) {
            while (1)
                ;
        } // infinite loop
        temp->entries[0].loadBuffer[0] = ptr;

        ptr = sndMalloc(0x8000);
        if (ptr == 0) {
            while (1)
                ;
        } // infinite loop
        temp->entries[0].loadBuffer[1] = ptr;

        size = sndStreamAllocLength(0xE00, 0);
        ptr = sndMalloc(size);
        if (ptr == 0) {
            while (1)
                ;
        } // infinite loop
        temp->entries[0].buffer = ptr;

        ptr = sndMalloc(0x8000);
        if (ptr == 0) {
            while (1)
                ;
        } // infinite loop
        temp->entries[1].loadBuffer[0] = ptr;

        ptr = sndMalloc(0x8000);
        if (ptr == 0) {
            while (1)
                ;
        } // infinite loop
        temp->entries[1].loadBuffer[1] = ptr;

        size = sndStreamAllocLength(0xE00, 0);
        ptr = sndMalloc(size);
        if (ptr == 0) {
            while (1)
                ;
        } // infinite loop
        temp->entries[1].buffer = ptr;
    }

    slot = sound.unk108;
    slot->callback = sndAuxCallbackReverbHI;
    slot->data = &revH;
    slot->unk8 = 0xFF;
    slot->unkC = 0;

    slot++;
    slot->callback = sndAuxCallbackChorus;
    slot->data = &cho;
    slot->unk8 = 0xFF;
    slot->unkC = 0;
#endif
}

#ifndef NONMATCHING

inline u32 SoundEfxCheckPlay(s32 chan) {
    SoundEffect* sfx = &sound.effects[chan];
    SND_VOICEID vid;
    if (!sfx->flags) {
        return FALSE;
    }
    if (!(sfx->flags & 0x10)) {
        if (sfx->flags & 0x10) {
            vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
        } else {
            vid = sndFXCheck(sfx->voiceId);
        }
        if (sndFXCheck(vid) == -1) {
            return FALSE;
        }
    } else if (!sndCheckEmitter(&sfx->emitter)) {
        return FALSE;
    }
    return TRUE;
}

s32 SoundEfxPlayEx(SND_FXID fid, u8 a2, u8 vol, u8 pan);

void SoundEfxStop(s32 chan);

void SoundEfxSetPitch(s32 chan, u16 pitch);

void SoundEfxSetVolume(s32 chan, u8 vol);

u8 SoundEfxGetVolume(s32 chan);

void SoundEfxSetAux1(s32 chan, u8 reverb);

void SoundEfxSetPan(s32 chan, u8 pan);

void SoundEfxSetSrndPan(s32 chan, u8 span);

void SoundEfxSetLPF(s32 chan, s16 freq);

BOOL SoundEfxCheck(s32 chan);


void SoundEfxMain(void);



void SoundDVDMain(void);

void _ssDVDReadAsync_activeChk(s32 result, DVDFileInfo* fileInfo);
void cache_flush(u32 pointerToARQRequest);
void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest);
void _ssDVDReadAsync_cache_next(s32 result, DVDFileInfo* fileInfo);
void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo);
void SoundSSStopCh(s32 chan);
void SoundSSSetPanCh(s32 chan, u8 pan);

inline void SoundIntOff(void) {
    if (!sound.unk20C) {
        sound.interrupts = OSDisableInterrupts();
    }
    sound.unk20C++;
}

inline void SoundIntOn(void) {
    if (sound.unk20C) {
        if (!--sound.unk20C) {
            OSRestoreInterrupts(sound.interrupts);
        }
    }
}


inline void _ssResetEntries(SoundStream* stream) {
    stream->entries[0].curBuf = 0;
    stream->entries[0].srcPos = 0;
    stream->entries[0].offset = 0;
    stream->entries[0].pos = 0;
    stream->entries[0].loaded = 0;
    stream->entries[0].ready = 0;
    stream->entries[0].scale = 0;
    stream->entries[0].nibble = 0;
    stream->entries[0].runCount = 0;
    stream->entries[1].curBuf = 0;
    stream->entries[1].srcPos = 0;
    stream->entries[1].offset = 0;
    stream->entries[1].pos = 0;
    stream->entries[1].loaded = 0;
    stream->entries[1].ready = 0;
    stream->entries[1].scale = 0;
    stream->entries[1].nibble = 0;
    stream->entries[1].runCount = 0;
}

void _ssDVDReadAsync_activeChk(s32 result, DVDFileInfo* fileInfo);

void cache_flush(u32 pointerToARQRequest);

void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest);

void _ssDVDReadAsync_cache_next(s32 result, DVDFileInfo* fileInfo);

s16 dtbl[16] = {0x0001, 0x0007, 0x0018, 0x003B, 0x0053, 0x006F, 0x00EC, 0x022B,
                0x02E6, 0x0375, 0x041C, 0x08AD, 0x0CD5, 0x1150, 0x1B32, 0x2454};

u8* ssDecodeDPCM(SoundStream* stream, SoundStreamEntry* entry, s16* out, u32 count, u8* src);
u32 _sscallback(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user);

void SoundSSPlayChEx(s32 chan, const char* name, s32 aram);

void SoundSSPlayCh(s32 chan, const char* name);

void SoundSSPlayChEx(s32 chan, const char* name, s32 aram);

void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo);

void SoundSSStopCh(s32 chan);

void SoundSSFadeoutCh(s32 chan);

void SoundSSContinueCh(s32 chan);

void SoundSSSetPanCh(s32 chan, u8 pan);

void SoundSSSetVolCh(s32 chan, u8 vol);

s32 SoundSSGetVolCh(s32 chan);

void SoundSSSetSrndPanCh(s32 chan, u8 span);

void SoundSSSetPlayFreqCh(s32 chan, u16 freq);

u16 SoundSSCheck(s32 chan);

void SoundSSMuteOn(s32 chan);

void SoundSSMuteOff(s32 chan);

void SoundSSMain(void);

void SoundSSMainInt(void);

void SoundAIDMACallback(void);


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on

static inline void SoundSSStopCh__af_inl(s32 chan) {
    SoundStream* stream;

    if (sound.streams[chan].flags) {
        stream = (0, &sound.streams[chan]);
        SoundIntOff();
        if (stream->flags & 0x400) {
            sound.slotUsed[stream->slot] = 0;
        }
        stream->flags = 0;
        DVDMgrClose(stream->entries[0].dvd);
        DVDMgrClose(stream->entries[1].dvd);
        sndStreamFree(stream->entries[0].streamId);
        if (stream->count == 2) {
            sndStreamFree(stream->entries[1].streamId);
        }
        SoundIntOn();
        sound.unk104 = -1;
    }
}

#pragma dont_inline on
#endif
void SoundMain(void) {
    int i;
    SoundSong* song;

    for (i = 0, song = sound.songs; i < 4; i++, song++) {
        if (song->group && song->seqId != -1 && sndSeqGetValid(song->seqId) != TRUE) {
            song->group->flags |= 2;
            sndSeqStop(song->seqId);
            song->seqId = -1;
        }
    }
    SoundEfxMain();
    SoundDVDMain();
    SoundSSMain();
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void SoundMainInt(void) {
    SoundSSMainInt();
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void SoundSetFadeTime(u16 in, u16 out) { // 1:1
    sound.fadeIn = in;
    sound.fadeOut = out;
}

void* loadDVD_callback(u32 offset, u32 bytes) { // 1:1
    DVDFileInfo info;

    if (!DVDOpen(sound.filepath, &info)) {
        return NULL;
    }
    if (DVDRead(&info, sound.filedata, (s32)bytes, (s32)offset) <= 0) {
        return NULL;
    }
    DVDClose(&info);
    return sound.filedata;
}

BOOL SoundLoadDVD2(const char* path) { // 1:1
    DVDEntry* entry;
    u32 length;
    void* pointer;

    if (sound.dataId >= 8) {
        return 0;
    }

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".pool");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B714, ".pool"));
#endif
    entry = DVDMgrOpen(str, 2, 0);
    length = entry == NULL; // fixes regalloc
    if (entry == NULL) {
        pointer = NULL;
    } else {
        length = DVDMgrGetLength(entry);
        if (length == 0) {
            pointer = NULL;
        } else {
            length = OSRoundUp32B(length);
            pointer = __memAlloc(HEAP_DEFAULT, length);
            if (pointer == NULL) {
                pointer = NULL;
            } else if (DVDMgrRead(entry, pointer, length, 0) <= 0) {
                __memFree(HEAP_DEFAULT, pointer);
                pointer = NULL;
            } else {
                DVDMgrClose(entry);
            }
        }
    }
    if (pointer == NULL) {
        return FALSE;
    }
    sound.poolData[sound.dataId] = pointer;

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".proj");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B71C, ".proj"));
#endif
    entry = DVDMgrOpen(str, 2, 0);
    if (entry == NULL) {
        pointer = NULL;
    } else {
        length = DVDMgrGetLength(entry);
        if (length == 0) {
            pointer = NULL;
        } else {
            length = OSRoundUp32B(length);
            pointer = __memAlloc(HEAP_DEFAULT, length);
            if (pointer == NULL) {
                pointer = NULL;
            } else if (DVDMgrRead(entry, pointer, length, 0) <= 0) {
                __memFree(HEAP_DEFAULT, pointer);
                pointer = NULL;
            } else {
                DVDMgrClose(entry);
            }
        }
    }
    if (pointer == NULL) {
        return FALSE;
    }
    sound.projData[sound.dataId] = pointer;

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".sdir");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B724, ".sdir"));
#endif
    entry = DVDMgrOpen(str, 2, 0);
    if (entry == NULL) {
        pointer = NULL;
    } else {
        length = DVDMgrGetLength(entry);
        if (length == 0) {
            pointer = NULL;
        } else {
            length = OSRoundUp32B(length);
            pointer = __memAlloc(HEAP_DEFAULT, length);
            if (pointer == NULL) {
                pointer = NULL;
            } else if (DVDMgrRead(entry, pointer, length, 0) <= 0) {
                __memFree(HEAP_DEFAULT, pointer);
                pointer = NULL;
            } else {
                DVDMgrClose(entry);
            }
        }
    }
    if (pointer == NULL) {
        return FALSE;
    }
    sound.sdirData[sound.dataId] = pointer;

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".samp");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B72C, ".samp"));
#endif
    strcpy(sound.filepath, str);
    sndSetSampleDataUploadCallback(loadDVD_callback, 0x20000);
    return TRUE;
}

BOOL SoundLoadDVD2PushGroup(u8* groupIds) { // 1:1
    SND_GROUPID id;
    s32 temp;

    if (sound.dataId >= 8) {
        return 0;
    }
    sound.groupCount[sound.dataId] = 0;
    if (groupIds) {
        while (*groupIds != 0xFF) {
            id = *groupIds;
            sndPushGroup(sound.projData[sound.dataId], id, 0, sound.sdirData[sound.dataId],
                         sound.poolData[sound.dataId]);
            sound.groupCount[sound.dataId]++;
            groupIds++;
        };
    } else {
        temp = sound.unkE8;
        while (temp < 0xFF) {
            if (sndPushGroup(sound.projData[sound.dataId], (SND_GROUPID)temp, 0, sound.sdirData[sound.dataId],
                             sound.poolData[sound.dataId]) != TRUE) {
                break;
            }
            sound.groupCount[sound.dataId]++;
            sound.unkE8++;
            temp++;
        }
    }
    return TRUE;
}

void SoundLoadDVD2Free(void) {
    if (sound.filedata) {
        __memFree(HEAP_DEFAULT, sound.filedata);
        sound.filedata = NULL;
    }
}

BOOL SoundSLibLoadDVD(const char* path) { // regalloc, stack, otherwise 1:1
    SoundGroup* temp_r0;
    u32 length2;
    u32 length3;
    SoundGroup* iter;
    SoundGroup* group;
    SoundGroup* var_r4;
    u32 temp_r28;
    u32* var_r27;
    u16 id;
    void* temp_r0_3;
    DVDEntry* entry;
    u32 length;
    void* pointer;
    void* pointer2;
    void* pointer3;

    if (sound.slibId >= 8) {
        return FALSE;
    }

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".slib");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B6FC, ".slib"));
#endif
    entry = DVDMgrOpen(str, 2, 0);
    if (entry == NULL) {
        pointer = NULL;
    } else {
        length = DVDMgrGetLength(entry);
        if (length == 0) {
            pointer = NULL;
        } else {
            length = OSRoundUp32B(length);
            pointer = __memAlloc(HEAP_DEFAULT, length);
            if (pointer == NULL) {
                pointer = NULL;
            } else if (DVDMgrRead(entry, pointer, length, 0) <= 0) {
                __memFree(HEAP_DEFAULT, pointer);
                pointer = NULL;
            } else {
                DVDMgrClose(entry);
            }
        }
    }
    if ((var_r27 = pointer) == NULL) {
        return FALSE;
    }
    sound.slibData[sound.slibId] = pointer;

    while (1) {
        temp_r28 = *var_r27;
        if (*var_r27 == 0xFFFFFFFF) {
            break;
        }
        group = __memAlloc(HEAP_DEFAULT, 0x10);
        if (group == NULL) {
            while (1)
                ;
        }
        temp_r0 = sound.groups;
        id = 0;
        if (temp_r0 == NULL) {
            sound.groups = group;
        } else {
            for (iter = sound.groups;; iter = iter->next) {
                id++;
                if (!iter->next) {
                    break;
                }
            }
            iter->next = group;
        }
        group->flags = 1;
        group->unk2 = id;
        group->groupId = 0;
        group->songId = 0;
        group->arrfile = var_r27 + 8;
        group->next = 0;
        var_r27 = (u32*)((u32)var_r27 + (u32)temp_r28);
    }

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".stbl");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B704, ".stbl"));
#endif
    entry = DVDMgrOpen(str, 2, 0);
    if (entry == NULL) {
        pointer2 = NULL;
    } else {
        length2 = DVDMgrGetLength(entry);
        if (length2 == 0) {
            pointer2 = NULL;
        } else {
            length2 = OSRoundUp32B(length2);
            pointer2 = __memAlloc(HEAP_DEFAULT, length2);
            if (pointer2 == NULL) {
                pointer2 = NULL;
            } else if (DVDMgrRead(entry, pointer2, length2, 0) <= 0) {
                __memFree(HEAP_DEFAULT, pointer2);
                pointer2 = NULL;
            } else {
                DVDMgrClose(entry);
            }
        }
    }
    if (pointer2 == NULL) {
        return FALSE;
    }
    sound.stblData[sound.slibId] = pointer2;

#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".etbl");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), getMarioStDvdRoot(), path, EXT_LIT((char*)str_8041B70C, ".etbl"));
#endif
    entry = DVDMgrOpen(str, 2, 0);
    if (entry == NULL) {
        pointer3 = NULL;
    } else {
        length3 = DVDMgrGetLength(entry);
        if (length3 == 0) {
            pointer3 = NULL;
        } else {
            length3 = OSRoundUp32B(length3);
            pointer3 = __memAlloc(HEAP_DEFAULT, length3);
            if (pointer3 == NULL) {
                pointer3 = NULL;
            } else if (DVDMgrRead(entry, pointer3, length3, 0) <= 0) {
                __memFree(HEAP_DEFAULT, pointer3);
                pointer3 = NULL;
            } else {
                DVDMgrClose(entry);
            }
        }
    }
    if (pointer3 == NULL) {
        return FALSE;
    }
    sound.etblData[sound.slibId] = pointer3;
    sound.slibId++;
    return TRUE;
#ifdef NONMATCHING
}

static inline void _ssDropStop(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        SoundSong* song = &sound.songs[i];
        if (sndSeqGetValid(song->seqId)) {
            sndSeqStop(song->seqId);
            song->seqId = (SND_SEQID)-1;
        }
    }
    for (i = 0; i < 40; i++) {
        SoundEffect* effect = &sound.effects[i];
        if (effect->flags) {
            sndFXKeyOff(effect->voiceId);
            if (effect->flags & 0x10) {
                sndRemoveEmitter(&effect->emitter);
            }
            effect->flags = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        SoundDVD* dvd = &sound.dvds[i];
        if (dvd->flags & 3) {
            AISetStreamPlayState(0);
            dvd->flags = 0;
            sound.unkFC = -1;
            DVDCancelStream(&dvd->info.cb);
            DVDClose(&dvd->info);
        }
    }

    for (i = 0; i < 3; i++) {
        SoundStream* stream;
        if (sound.streams[i].flags) {
            stream = &sound.streams[i];
            if (!sound.unk20C) {
                sound.interrupts = OSDisableInterrupts();
            }
            sound.unk20C++;
            if (stream->flags & 0x400) {
                sound.slotUsed[stream->slot] = 0;
            }
            stream->flags = 0;
            DVDMgrClose(stream->entries[0].dvd);
            DVDMgrClose(stream->entries[1].dvd);
            sndStreamFree(stream->entries[0].streamId);
            if (stream->count == 2) {
                sndStreamFree(stream->entries[1].streamId);
            }
            if (sound.unk20C) {
                if (!--sound.unk20C) {
                    OSRestoreInterrupts(sound.interrupts);
                }
            }
            sound.unk104 = -1;
        }
    }
#endif
}

BOOL SoundDropData(void) {
    SoundGroup *group; SoundGroup *temp;
    u32 i;

    group = sound.groups;
    _ssDropStop();
    sndSilence();
    for (i = 0; i < 4; i++) {
        SoundSong* song = &sound.songs[i];
        if (sndSeqGetValid(song->seqId)) {
            sndSeqStop(song->seqId);
            song->seqId = (SND_SEQID)(-1);
        }
    }
    for (i = 0; i < 40; i++) {
        SoundEffect* effect = (0, &sound.effects[i]);
        if (effect->flags) {
            sndFXKeyOff(effect->voiceId);
            if (effect->flags & 0x10) {
                sndRemoveEmitter(&effect->emitter);
            }
            effect->flags = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        SoundDVD* dvd = (0, &sound.dvds[i]);
        if (dvd->flags & 3) {
            AISetStreamPlayState(0);
            dvd->flags = 0;
            sound.unkFC = -1;
            DVDCancelStream(&dvd->info.cb);
            DVDClose(&dvd->info);
        }
    }

    for (i = 0; i < 3; i++) {
        SoundStream* stream;
        if (sound.streams[i].flags) {
            stream = &sound.streams[i];
            if (!sound.unk20C) {
                sound.interrupts = OSDisableInterrupts();
            }
            sound.unk20C++;
            if (stream->flags & 0x400) {
                sound.slotUsed[stream->slot] = 0;
            }
            stream->flags = 0;
            DVDMgrClose(stream->entries[0].dvd);
            DVDMgrClose(stream->entries[1].dvd);
            sndStreamFree(stream->entries[0].streamId);
            if (stream->count == 2) {
                sndStreamFree(stream->entries[1].streamId);
            }
            if (sound.unk20C) {
                if (!(--sound.unk20C)) {
                    OSRestoreInterrupts(sound.interrupts);
                }
            }
            sound.unk104 = -1;
        }
    }

    for (i = 0; i < sound.dataId; i++) {
        while (sound.groupCount[i]) {
            sndPopGroup();
            sound.groupCount[i]--;
        }
    }

    for (i = 0; i < sound.dataId; i++) {
        __memFree(HEAP_DEFAULT, sound.poolData[i]);
    }

    for (i = 0; i < sound.dataId; i++) {
        __memFree(HEAP_DEFAULT, sound.projData[i]);
    }

    for (i = 0; i < sound.dataId; i++) {
        __memFree(HEAP_DEFAULT, sound.sdirData[i]);
    }

    for (i = 0; i < sound.slibId; i++) {
        __memFree(HEAP_DEFAULT, sound.slibData[i]);
        __memFree(HEAP_DEFAULT, sound.stblData[i]);
        __memFree(HEAP_DEFAULT, sound.etblData[i]);
    }

    sound.dataId = 0;
    sound.slibId = 0;
    sound.unkE8 = 0;

    while (1) {
        if (!group) {
            break;
        }
        temp = group->next;
        if (!(group->flags & 1)) {
            __memFree(HEAP_DEFAULT, group->arrfile);
        }
        __memFree(HEAP_DEFAULT, group);
        group = temp;
    }
    sound.groups = 0;

    return TRUE;
}

void SoundSetOutputMode(SND_OUTPUTMODE mode) {
    if (sound.outputMode != mode) {
        sound.outputMode = mode;
        sndOutputMode(mode);
    }
}

void SoundOpenCover(void) {
    if (!sound.unk214) {
        sound.unk214 = 1;
    }
}

void SoundCloseCover(void) {
    SoundStream* stream;
    BOOL close;
    int i;

    if (sndIsInstalled() && sound.unk214 == 1) {
        close = FALSE;
        for (i = 0; i < 3; i++) {
            stream = &sound.streams[i];
            if (stream->flags & 8 && !(stream->flags & 0x400) && !(stream->flags & 2)) {
                if (stream->flags & 0x1000) {
                    close = TRUE;
                }
                if (stream->count == 2 && stream->flags & 0x2000) {
                    close = TRUE;
                }
            }
        }
        if (close) {
            sound.unk214 = 2;
        } else {
            sound.unk214 = 0;
        }
    }
}

#ifdef NONMATCHING
inline SoundGroup* SoundSongGetGroup(u8 a1) {
    u16 temp = a1;
    SoundGroup* group;

    for (group = sound.groups;; group = group->next) {
        if (group == 0) {
            return 0;
        }
        if (group->unk2 == temp) {
            break;
        }
    }
    return group;
}

#endif
void SoundSongPlayCh(s32 chan, u32 a2) {
    SoundSong* song;
    SoundGroup* group;

    song = &sound.songs[chan];
    if (sndSeqGetValid(song->seqId) == 1) {
        sndSeqStop(song->seqId);
    }
    song->vol = 127;
    group = SoundSongGetGroup((u8)a2);
    if (group) {
        song->group = group;
        group->groupId = (SND_GROUPID)((a2 >> 16) & 0xFF);
        group->songId = (SND_SONGID)((a2 >> 8) & 0xFF);
        song->mask = 0xFFFFFFFF;
        song->seqId = sndSeqPlayEx(group->groupId, group->songId, group->arrfile, 0, 0);
        sndSeqVolume((u8)song->vol, 0, song->seqId, 0);
        sndSeqContinue(song->seqId);
        sndSeqMute(song->seqId, song->mask, 0);
    }
}

void SoundSongContinueCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqContinue(song->seqId);
        sndSeqVolume((u8)song->vol, 0, song->seqId, SND_SEQVOL_CONTINUE);
    }
}

void SoundSongStopCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqStop(song->seqId);
        song->seqId = (SND_SEQID)-1;
    }
}

void SoundSongFadeoutCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqVolume(0, sound.fadeOut, song->seqId, SND_SEQVOL_STOP);
        song->seqId = (SND_SEQID)-1;
    }
}

void SoundSongFadeinCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqVolume((u8)song->vol, sound.fadeIn, song->seqId, SND_SEQVOL_CONTINUE);
    }
}

void SoundSongSetVolCh(s32 chan, u8 vol) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        if (vol > 127) {
            vol = 127;
        }
        song->vol = vol;
        sndSeqVolume((u8)song->vol, 0, song->seqId, SND_SEQVOL_CONTINUE);
    }
}

u8 SoundSongGetVolCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId) == 0) {
        return 0;
    }
    return (u8)song->vol;
}

BOOL SoundSongCheck(s32 chan) {
    return sndSeqGetValid(sound.songs[chan].seqId) != 0;
#ifdef NONMATCHING
}

inline void SoundEfxMuteCh(s32 chan) {
    SoundEffect* sfx = &sound.effects[chan];
    if (sfx->flags) {
        sndFXKeyOff(sfx->voiceId);
        if (sfx->flags & 0x10) {
            sndRemoveEmitter(&sfx->emitter);
        }
        sfx->flags = 0;
    }
}

inline s32 SoundEfxStopAll(u8 a1) {
    s32 chan;
    SoundEffect* sfx = sound.effects;

    for (chan = 0; chan < 40; chan++, sfx++) {
        if (sfx->unk2 <= a1) {
            SoundEfxMuteCh(chan);
            return chan;
        }
    }
    return chan;
}

inline u32 SoundEfxCheckPlay(s32 chan) {
    SoundEffect* sfx = &sound.effects[chan];
    SND_VOICEID vid;
    if (!sfx->flags) {
        return FALSE;
    }
    if (!(sfx->flags & 0x10)) {
        if (sfx->flags & 0x10) {
            vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
        } else {
            vid = sndFXCheck(sfx->voiceId);
        }
        if (sndFXCheck(vid) == -1) {
            return FALSE;
        }
    } else if (!sndCheckEmitter(&sfx->emitter)) {
        return FALSE;
    }
    return TRUE;
#endif
}

s32 SoundEfxPlayEx(SND_FXID fid, u8 a2, u8 vol, u8 pan) {
    SoundEffect* sfx;
    s32 chan;

    sfx = sound.effects;
    for (chan = 0; chan < 40; chan++, sfx++) {
        if (!sfx->flags) {
            break;
        }
    }
    if (chan >= 40u) {
        sfx = sound.effects;
        for (chan = 0; chan < 40; chan++, sfx++) {
            if (sfx->unk2 <= a2) {
                SoundEfxMuteCh(chan);
                break;
            }
        }
        if (chan >= 40u) {
            return -1;
        }
    }
    sfx->flags = 0;
    if (!sound.unk20C) {
        sound.interrupts = OSDisableInterrupts();
    }
    ++sound.unk20C;
    sfx->voiceId = sndFXStart(fid, 127, pan);
    sndFXVolume(sfx->voiceId, vol);
    if (sound.unk20C && !--sound.unk20C) {
        OSRestoreInterrupts(sound.interrupts);
    }
    if (sfx->voiceId == -1) {
        return -1;
    }
    sfx->flags = 1;
    sfx->unk2 = a2;
    sfx->vol = vol;
    sfx->pan = pan;
    sfx->span = 0;
    sfx->fid = fid;
    if (sound.unk214) {
        sndFXVolume(sfx->voiceId, 0);
    }
    if (!SoundEfxCheckPlay(chan)) {
        chan = -1;
    }
    return chan;
}

void SoundEfxStop(s32 chan) {
    SoundEffect* sfx;

    sfx = &sound.effects[chan];
    if (sfx->flags) {
        sndFXKeyOff(sfx->voiceId);
        if (sfx->flags & 0x10) {
            sndRemoveEmitter(&sfx->emitter);
        }
        sfx->flags = 0;
    }
}

void SoundEfxSetPitch(s32 chan, u16 pitch) {
    SoundEffect* sfx;
    SND_VOICEID vid;

    sfx = &sound.effects[chan];
    if (sfx->flags & 0x10) {
        vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
    } else {
        vid = sndFXCheck(sfx->voiceId);
    }
    if (vid != -1) {
        sndFXPitchBend(vid, (u16)(pitch + 0x2000));
    }
}

void SoundEfxSetVolume(s32 chan, u8 vol) {
    SoundEffect* sfx;
    SND_VOICEID vid;

    sfx = &sound.effects[chan];
    if (sfx->flags & 0x10) {
        vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
    } else {
        vid = sndFXCheck(sfx->voiceId);
    }
    if (vid != -1) {
        sfx->vol = vol;
        sndFXVolume(vid, vol);
        if (sound.unk214) {
            sndFXVolume(vid, 0);
        }
    }
}

u8 SoundEfxGetVolume(s32 chan) {
    s32 off = chan * sizeof(SoundEffect);
    return (u8)*(u16*)((u8*)sound.effects + off + 4);
}

void SoundEfxSetAux1(s32 chan, u8 reverb) {
    SoundEffect* sfx;
    SND_VOICEID vid;

    sfx = &sound.effects[chan];
    if (sfx->flags & 0x10) {
        vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
    } else {
        vid = sndFXCheck(sfx->voiceId);
    }
    if (vid != -1) {
        sndFXReverb(vid, reverb);
    }
}

void SoundEfxSetPan(s32 chan, u8 pan) {
    SoundEffect* sfx;
    SND_VOICEID vid;
    s32 off = chan * sizeof(SoundEffect);

    *(u16*)((u8*)sound.effects + off + 6) = pan;
    sfx = (SoundEffect*)((u8*)sound.effects + off);
    if (sfx->flags & 0x10) {
        vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
    } else {
        vid = sndFXCheck(sfx->voiceId);
    }
    if (vid != -1) {
        sndFXPanning(vid, pan);
    }
}

void SoundEfxSetSrndPan(s32 chan, u8 span) {
    SoundEffect* sfx;
    SND_VOICEID vid;
    s32 doppler;
    s32 off = chan * sizeof(SoundEffect);

    *(u16*)((u8*)sound.effects + off + 8) = span;
    sfx = (SoundEffect*)((u8*)sound.effects + off);
    vid = (sfx->flags & 0x10) ? sndFXCheck(sndEmitterVoiceID(&sfx->emitter))
                              : sndFXCheck(sfx->voiceId);
    if (vid != -1) {
        sndFXSurroundPanning(vid, span);
        if (span == 0) {
            doppler = 0x2000;
        } else if (span < 64) {
            doppler = 0x2000 - 3 * (64 - span);
        } else {
            doppler = 0x2000 - 3 * (span - 64);
        }
        sndFXDoppler(vid, doppler);
    }
}

void SoundEfxSetLPF(s32 chan, s16 freq) {
    SoundEffect* sfx;
    u32 voiceId;

    sfx = &sound.effects[chan];
    if (sfx->flags & 0x10) {
        voiceId = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
    } else {
        voiceId = sndFXCheck(sfx->voiceId);
    }
    if (voiceId != -1) {
        if (!freq) {
            sndFXSetFilter(voiceId, SND_FILTER_NONE, 0);
        } else if (freq >= 16000) {
            sndFXSetFilter(voiceId, SND_FILTER_NONE, 0);
        } else {
            sndFXSetFilter(voiceId, SND_FILTER_LOWPASS, freq);
        }
    }
}

BOOL SoundEfxCheck(s32 chan) {
    SoundEffect* sfx;

    sfx = &sound.effects[chan];
    if (!sfx->flags) {
        return FALSE;
    }
    if (!(sfx->flags & 0x10)) {
        SND_VOICEID vid;
        if (sfx->flags & 0x10) {
            vid = sndFXCheck(sndEmitterVoiceID(&sfx->emitter));
        } else {
            vid = sndFXCheck(sfx->voiceId);
        }
        if (sndFXCheck(vid) == -1) {
            return FALSE;
        }
    } else {
        if (!sndCheckEmitter(&sfx->emitter)) {
            return FALSE;
        }
    }
    return TRUE;
}

#ifdef NONMATCHING
inline void SoundEfxCheckCh(s32 chan) {
    SoundEffect* effect;
    SND_VOICEID vid;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void SoundEfxMain(void) {
	asm volatile {
		lis r3, sound@ha
		lfs f30, float_0_8041b6d8(r2)
		addi r3, r3, sound@l
		lfs f2, float_6p2832_8041b6f4(r2)
		opword 0xC02301F4
		addi r27, r3, 0x1b8
		lfs f0, float_360_8041b6f8(r2)
		opword 0xFFE0F090
		opword 0xEC220072
		opword 0xC0A301B8
		opword 0xC08301C4
		opword 0x3B8301D0
		opword 0xC06301BC
		fdivs f29, f1, f0
		opword 0xC04301C8
		opword 0xC02301C0
		opword 0xC00301CC
		opword 0xD0A301C4
		opword 0xD06301C8
		opword 0xEC852028
		opword 0xD02301CC
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC20E890
		opword 0xD08301D0
		opword 0xD04301D4
		opword 0xD00301D8
		bl sin
		opword 0xFC400818
		lfs f0, float_1_8041b6e4(r2)
		opword 0xFC20E890
		opword 0xEFC0F0BA
		bl cos
		opword 0xFC400818
		lfs f1, float_1_8041b6e4(r2)
		lis r3, sound@ha
		lfs f0, float_0_8041b6d8(r2)
		addi r10, r3, sound@l
		opword 0x7F64DB78
		opword 0xEFE1F8BC
		opword 0x800A0204
		opword 0xD3CA01DC
		opword 0x38CA01DC
		opword 0x38EA01E8
		opword 0x7F85E378
		opword 0xD00A01E0
		opword 0x386A0128
		opword 0x5408063E
		opword 0x39200000
		opword 0xD3EA01E4
		opword 0xD00A01E8
		opword 0xD02A01EC
		opword 0xD00A01F0
		bl sndUpdateListener
		lis r3, sound@ha
		opword 0x3B800000
		addi r31, r3, sound@l
		opword 0x837F00F4
		opword 0xA01B0000
		opword 0x28000000
		opword 0x41820070
		opword 0x540006F7
		opword 0x41820068
		opword 0xC03B0064
		opword 0x387B0014
		opword 0xC01B0070
		opword 0x389B0064
		opword 0x38BB007C
		opword 0x38E00000
		opword 0xEC010028
		opword 0xD01B007C
		opword 0xC03B0068
		opword 0xC01B0074
		opword 0xEC010028
		opword 0xD01B0080
		opword 0xC03B006C
		opword 0xC01B0078
		opword 0xEC010028
		opword 0xD01B0084
		opword 0xC01B0064
		opword 0xD01B0070
		opword 0xC01B0068
		opword 0xD01B0074
		opword 0xC01B006C
		opword 0xD01B0078
		opword 0xA01B0004
		opword 0x5406063E
		bl sndUpdateEmitter
		opword 0x3B9C0001
		opword 0x3B7B0088
		opword 0x2C1C0028
		opword 0x4180FF7C
		opword 0x3BA00000
		opword 0x83DF00F4
		opword 0x7FBCEB78
		opword 0xA01E0000
		opword 0x28000000
		opword 0x41820158
		opword 0x540006F7
		opword 0x4082007C
		opword 0x801F00F4
		opword 0x7C60E214
		opword 0xA0030000
		opword 0x540006F7
		opword 0x41820014
		opword 0x38630014
		bl sndEmitterVoiceID
		bl sndFXCheck
		opword 0x4800000C
		opword 0x8063000C
		bl sndFXCheck
		bl sndFXCheck
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x40820114
		opword 0x801F00F4
		opword 0x7F60E214
		opword 0xA01B0000
		opword 0x28000000
		opword 0x41820100
		opword 0x807B000C
		bl sndFXKeyOff
		opword 0xA01B0000
		opword 0x540006F7
		opword 0x4182000C
		opword 0x387B0014
		bl sndRemoveEmitter
		opword 0x38000000
		opword 0xB01B0000
		opword 0x480000D8
		opword 0x387E0014
		bl sndCheckEmitter
		opword 0x28030000
		opword 0x4082003C
		opword 0x801F00F4
		opword 0x7F60E214
		opword 0xA01B0000
		opword 0x28000000
		opword 0x41820028
		opword 0x807B000C
		bl sndFXKeyOff
		opword 0xA01B0000
		opword 0x540006F7
		opword 0x4182000C
		opword 0x387B0014
		bl sndRemoveEmitter
		opword 0x38000000
		opword 0xB01B0000
		opword 0xA07E000A
		opword 0x28030000
		opword 0x41820010
		opword 0x3803FFFF
		opword 0xB01E000A
		opword 0x48000078
		opword 0x801F00F4
		opword 0x7C60E214
		opword 0xA0030000
		opword 0x540006F7
		opword 0x41820014
		opword 0x38630014
		bl sndEmitterVoiceID
		bl sndFXCheck
		opword 0x4800000C
		opword 0x8063000C
		bl sndFXCheck
		bl sndFXCheck
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x4082003C
		opword 0x801F00F4
		opword 0x7F60E214
		opword 0xA01B0000
		opword 0x28000000
		opword 0x41820028
		opword 0x807B000C
		bl sndFXKeyOff
		opword 0xA01B0000
		opword 0x540006F7
		opword 0x4182000C
		opword 0x387B0014
		bl sndRemoveEmitter
		opword 0x38000000
		opword 0xB01B0000
		opword 0x3BBD0001
		opword 0x3BDE0088
		opword 0x2C1D0028
		opword 0x3B9C0088
		opword 0x4180FE90
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    effect = &sound.effects[chan];
    if (effect->flags & 0x10) {
        vid = sndFXCheck(sndEmitterVoiceID(&effect->emitter));
    } else {
        vid = sndFXCheck(effect->voiceId);
    }
    if (sndFXCheck(vid) == -1) {
        SoundEfxMuteCh(chan);
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void SoundDVDMain(void) {
	char _af_pad[24];
	asm volatile {
		opword 0x3B600000
		lis r3, sound@ha
		opword 0x7F7EDB78
		opword 0x3BA00000
		addi r31, r3, sound@l
		opword 0x801F00F8
		opword 0x7F80F214
		opword 0xA07C0000
		opword 0x546007BD
		opword 0x40820360
		opword 0x54600673
		opword 0x4182013C
		lfs f2, float_0_8041b6d8(r2)
		opword 0xC03C0008
		opword 0xFC020800
		opword 0x40820064
		bl AIGetStreamSampleCount
		opword 0x907C0114
		opword 0x801F00F8
		add r26, r0, r27
		opword 0xA01A0000
		opword 0x540007BF
		opword 0x4182002C
		opword 0x38600000
		bl AISetStreamPlayState
		opword 0x38600000
		opword 0x3800FFFF
		opword 0xB07A0000
		opword 0x387A0118
		opword 0x901F00FC
		bl DVDCancelStream
		opword 0x387A0118
		bl DVDClose
		opword 0xA01C0000
		opword 0x60000002
		opword 0xB01C0000
		opword 0xA01C0000
		opword 0x540006B0
		opword 0xB01C0000
		opword 0x480002E8
		opword 0xC01C000C
		opword 0xEC010028
		opword 0xD01C0008
		opword 0xC01C0008
		opword 0xFC001040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD05C0008
		opword 0xA07C0002
		opword 0x801F00F8
		opword 0x5464063E
		opword 0x7C60DA14
		opword 0xB0830002
		opword 0x28040040
		opword 0xC0630008
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		stw r4, _af_pad+4(r1)
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010008
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC2100F2
		fdivs f31, f1, f0
		opword 0x3804FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2064007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x90610014
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010010
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210010
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xD8010018
		opword 0x8061001C
		bl AISetStreamVolLeft
		opword 0xFC00F81E
		opword 0xD8010020
		opword 0x80610024
		bl AISetStreamVolRight
		opword 0xA07C0000
		opword 0x546006B5
		opword 0x41820124
		lfs f2, float_0_8041b6d8(r2)
		opword 0xC03C0008
		opword 0xFC020800
		opword 0x4082004C
		opword 0x546006F2
		opword 0xB01C0000
		opword 0x801F00F8
		opword 0x7F40DA14
		opword 0xA01A0000
		opword 0x540007BF
		opword 0x418201E8
		opword 0x38600000
		bl AISetStreamPlayState
		opword 0x38600000
		opword 0x3800FFFF
		opword 0xB07A0000
		opword 0x387A0118
		opword 0x901F00FC
		bl DVDCancelStream
		opword 0x387A0118
		bl DVDClose
		opword 0x480001BC
		opword 0xC01C000C
		opword 0xEC010028
		opword 0xD01C0008
		opword 0xC01C0008
		opword 0xFC001040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD05C0008
		opword 0xA07C0002
		opword 0x801F00F8
		opword 0x5464063E
		opword 0x7C60DA14
		opword 0xB0830002
		opword 0x28040040
		opword 0xC0630008
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90810024
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010020
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x3804FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2064007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x9061001C
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010018
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210018
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xD8010010
		opword 0x80610014
		bl AISetStreamVolLeft
		opword 0xFC00F81E
		opword 0xD8010008
		opword 0x8061000C
		bl AISetStreamVolRight
		opword 0xA01C0000
		opword 0x540006F7
		opword 0x418200E8
		opword 0xC03C0008
		opword 0xC01C000C
		opword 0xEC01002A
		opword 0xD01C0008
		opword 0xC01C0008
		opword 0xC03C0004
		opword 0xFC000840
		opword 0x4C411382
		opword 0x4082001C
		opword 0xD03C0008
		lfs f0, float_0_8041b6d8(r2)
		opword 0xD01C000C
		opword 0xA01C0000
		opword 0x54000734
		opword 0xB01C0000
		opword 0xA07C0002
		opword 0x801F00F8
		opword 0x5464063E
		opword 0x7C60DA14
		opword 0xB0830002
		opword 0x28040040
		opword 0xC0630008
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90810024
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010020
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x3804FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2064007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x9061001C
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010018
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210018
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xD8010010
		opword 0x80610014
		bl AISetStreamVolLeft
		opword 0xFC00F81E
		opword 0xD8010008
		opword 0x8061000C
		bl AISetStreamVolRight
		opword 0x3BBD0001
		opword 0x3B7B0154
		opword 0x2C1D0002
		opword 0x3BDE0154
		opword 0x4180FC80
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
void SoundEfxMain(void) {
    SND_FVECTOR* dir;
    SoundEffect* e2;
    SoundEffect* effect;
    int i;
    f32 v10;
    f32 v9;
    f32 r = 1.0f;
    f32 v6;
    f32 x, y, z;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void _ssDVDReadAsync_activeChk(s32 result, DVDFileInfo* fileInfo) {
	char _af_pad[28];
	asm volatile {
		lis r5, sound@ha
		opword 0x7C7C1B78
		addi r30, r5, sound@l
		mr r27, r4
		opword 0xA01E020C
		opword 0x28000000
		opword 0x40820014
		bl OSDisableInterrupts
		lis r4, sound@ha
		addi r4, r4, sound@l
		opword 0x90640210
		opword 0xA09E020C
		lis r3, sound@ha
		addi r31, r3, sound@l
		opword 0x38000003
		opword 0x38840001
		opword 0x807F0100
		opword 0xB09E020C
		opword 0x7C0903A6
		opword 0xA0030000
		opword 0x28000000
		opword 0x41820160
		opword 0x80830028
		opword 0x38C00000
		opword 0x38E00000
		opword 0x38040040
		opword 0x7C00D840
		opword 0x4082000C
		opword 0x38C30028
		opword 0x38E00000
		opword 0x808300B0
		opword 0x38040040
		opword 0x7C00D840
		opword 0x4082000C
		opword 0x38C300B0
		opword 0x38E00001
		opword 0x28060000
		opword 0x41820120
		opword 0x2C1C0000
		opword 0x4180031C
		opword 0x80A60034
		opword 0x38000001
		opword 0x80860048
		opword 0x7C852214
		opword 0x90860034
		opword 0xA086004C
		opword 0x80A60048
		opword 0x20840001
		opword 0x5484103A
		opword 0x7C862214
		opword 0x90A4003C
		opword 0xB0060054
		opword 0x80860034
		opword 0x80060060
		opword 0x7C040040
		opword 0x41800044
		opword 0x80060064
		opword 0x90060034
		opword 0xA0830000
		opword 0x548005AD
		opword 0x41820024
		opword 0x2C070000
		opword 0x40820010
		opword 0x54800524
		opword 0xB0030000
		opword 0x48000040
		opword 0x548004E2
		opword 0xB0030000
		opword 0x48000034
		opword 0x60804000
		opword 0xB0030000
		opword 0x48000028
		opword 0x2C070000
		opword 0x40820014
		opword 0xA0030000
		opword 0x54000524
		opword 0xB0030000
		opword 0x48000010
		opword 0xA0030000
		opword 0x540004E2
		opword 0xB0030000
		opword 0xA003001A
		opword 0x28000002
		opword 0x4082003C
		lis r4, sound@ha
		addi r4, r4, sound@l
		opword 0xA0040214
		opword 0x28000002
		opword 0x4082005C
		opword 0xA803007C
		opword 0x2C000001
		opword 0x40820050
		opword 0xA8030104
		opword 0x2C000001
		opword 0x40820044
		opword 0x38000000
		opword 0xB0040214
		opword 0x48000038
		lis r4, sound@ha
		addi r4, r4, sound@l
		opword 0xA0040214
		opword 0x28000002
		opword 0x40820024
		opword 0xA803007C
		opword 0x2C000001
		opword 0x40820018
		opword 0x38000000
		opword 0xB0040214
		opword 0x4800000C
		opword 0x38630138
		opword 0x4200FE94
		opword 0x3BA00000
		opword 0x38000003
		opword 0x7FA4EB78
		opword 0x7C0903A6
		opword 0x801F0100
		opword 0x7F802214
		opword 0xA01C0000
		opword 0x28000000
		opword 0x418201D0
		opword 0x54000739
		opword 0x408201C8
		opword 0x807C0028
		opword 0x38030040
		opword 0x7C00D840
		opword 0x4082000C
		opword 0x38000001
		opword 0xB01C007E
		opword 0x807C00B0
		opword 0x38030040
		opword 0x7C00D840
		opword 0x4082000C
		opword 0x38000001
		opword 0xB01C0106
		opword 0xA01C001A
		opword 0x28000002
		opword 0x40820020
		opword 0xA81C007E
		opword 0x2C000000
		opword 0x41820180
		opword 0xA81C0106
		opword 0x2C000000
		opword 0x40820014
		opword 0x48000170
		opword 0xA81C007E
		opword 0x2C000000
		opword 0x41820164
		opword 0x38000000
		opword 0xB01C0074
		opword 0xB01C00FC
		opword 0xB01C007C
		opword 0xB01C0104
		opword 0x807C004C
		bl sndStreamActivate
		opword 0xA01C001A
		opword 0x28000002
		opword 0x4082000C
		opword 0x807C00D4
		bl sndStreamActivate
		opword 0x1C1D0138
		opword 0x807F0100
		opword 0xA09C0006
		opword 0x7FE30214
		opword 0x5485063E
		opword 0xA01F0000
		opword 0x28000000
		opword 0x41820104
		opword 0xB0BF0006
		opword 0xA01F0000
		opword 0x54000739
		opword 0x418200F4
		opword 0xA01F001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01F0010
		opword 0x38E00000
		opword 0xA01F0008
		opword 0xFC00001E
		opword 0x807F004C
		opword 0x5406063E
		stfd f0, _af_pad+0(r1)
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0x480000C0
		opword 0xC07F0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A1000C
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010008
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC2100F2
		fdivs f31, f1, f0
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x90610014
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010010
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210010
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01F0008
		opword 0x807F004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010018
		opword 0x8081001C
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01F0008
		opword 0x807F00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0xA01C0000
		opword 0x60000008
		opword 0xB01C0000
		opword 0x48000010
		opword 0x38840138
		opword 0x3BBD0001
		opword 0x4200FE18
		opword 0xA07E020C
		opword 0x28030000
		opword 0x41820024
		opword 0x3863FFFF
		opword 0x5460043F
		opword 0xB07E020C
		opword 0x40820014
		lis r3, sound@ha
		addi r3, r3, sound@l
		opword 0x80630210
		bl OSRestoreInterrupts
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    v10 = v9 = 0.0f;
    x = sound.pos.x - sound.prevPos.x;
    y = sound.pos.y - sound.prevPos.y;
    z = sound.pos.z - sound.prevPos.z;
    v6 = (TWO_PI * sound.unk1F4 / 360.0f);
    sound.prevPos.x = sound.pos.x;
    sound.prevPos.y = sound.pos.y;
    sound.prevPos.z = sound.pos.z;
    dir = &sound.dir;
    dir->x = x;
    dir->y = y;
    dir->z = z;
    v9 += r * (f32)sin(v6);
    v10 -= r * (f32)cos(v6);
    sound.heading.x = v9;
    sound.heading.y = 0.0f;
    sound.heading.z = v10;
    sound.up.x = 0.0f;
    sound.up.y = 1.0f;
    sound.up.z = 0.0f;
    sndUpdateListener(&sound.listener, &sound.pos, dir, &sound.heading, &sound.up, (u8)sound.listenerVol, NULL);

    effect = sound.effects;
    for (i = 0; i < 40; i++, effect++) {
        if (effect->flags) {
            if (effect->flags & 0x10) {
                effect->dir.x = effect->pos.x - effect->prevPos.x;
                effect->dir.y = effect->pos.y - effect->prevPos.y;
                effect->dir.z = effect->pos.z - effect->prevPos.z;
                effect->prevPos.x = effect->pos.x;
                effect->prevPos.y = effect->pos.y;
                effect->prevPos.z = effect->pos.z;
                sndUpdateEmitter(&effect->emitter, &effect->pos, &effect->dir, (u8)effect->vol, NULL);
            }
        }
    }

    for (e2 = sound.effects, i = 0; i < 40; e2++, i++) {
        if (e2->flags) {
            if (!(e2->flags & 0x10)) {
                SoundEfxCheckCh(i);
            } else {
                if (!sndCheckEmitter(&e2->emitter)) {
                    SoundEfxMuteCh(i);
                }
                if (e2->unkA) {
                    e2->unkA--;
                } else {
                    SoundEfxCheckCh(i);
                }
            }
        }
    }
}

inline void SoundDVDStopCh(s32 chan) {
    SoundDVD* dvd = &sound.dvds[chan];
    if (dvd->flags & 3) {
        AISetStreamPlayState(0);
        dvd->flags = 0;
        sound.unkFC = -1;
        DVDCancelStream(&dvd->info.cb);
        DVDClose(&dvd->info);
    }
}

inline void SoundDVDSetPanCh(s32 chan, u8 pan) { // I think this is the correct func name
    f32 left, right;
    SoundDVD* dvd;

    dvd = &sound.dvds[chan];
    dvd->unk2 = pan;
    left = dvd->unk8;
    right = left;
    if (pan < 64) {
        right = (((f32)pan * dvd->unk8) / 63.0f);
    }
    if (!((u32)(pan - 64) >> 31)) {
        left = (((f32)(127 - pan) * dvd->unk8) / 63.0f);
    }
    AISetStreamVolLeft((u8)left);
    AISetStreamVolRight((u8)right);
}

void SoundDVDMain(void) {
    u32 i;
    SoundDVD* dvd;

    for (i = 0; (int)i < 2; i++) {
        SoundDVD* dvd = &sound.dvds[i];
        if (!(dvd->flags & 2)) {
            if (dvd->flags & 0x40) {
                if (dvd->unk8 == 0.0f) {
                    dvd->samples = AIGetStreamSampleCount();
                    SoundDVDStopCh(i);
                    dvd->flags |= 0x2;
                    dvd->flags &= ~0x40;
                    continue;
                }
                dvd->unk8 -= dvd->unkC;
                if (dvd->unk8 <= 0.0f) {
                    dvd->unk8 = 0.0f;
                }
                SoundDVDSetPanCh(i, (u8)dvd->unk2);
            }
            if (dvd->flags & 0x20) {
                if (dvd->unk8 == 0.0f) {
                    dvd->flags &= ~0x20;
                    SoundDVDStopCh(i);
                    continue;
                }
                dvd->unk8 -= dvd->unkC;
                if (dvd->unk8 <= 0.0f) {
                    dvd->unk8 = 0.0f;
                }
                SoundDVDSetPanCh(i, (u8)dvd->unk2);
            }
            if (dvd->flags & 0x10) {
                dvd->unk8 += dvd->unkC;
                if (dvd->unk8 >= dvd->unk4) {
                    dvd->unk8 = dvd->unk4;
                    dvd->unkC = 0.0f;
                    dvd->flags &= ~0x10;
                }
                SoundDVDSetPanCh(i, (u8)dvd->unk2);
            }
        }
    }
}

void _ssDVDReadAsync_activeChk(s32 result, DVDFileInfo* fileInfo);
void cache_flush(u32 pointerToARQRequest);
void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest);
void _ssDVDReadAsync_cache_next(s32 result, DVDFileInfo* fileInfo);
void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo);
void SoundSSStopCh(s32 chan);
void SoundSSSetPanCh(s32 chan, u8 pan);

inline void SoundIntOff(void) {
    if (!sound.unk20C) {
        sound.interrupts = OSDisableInterrupts();
    }
    sound.unk20C++;
}

inline void SoundIntOn(void) {
    if (sound.unk20C) {
        if (!--sound.unk20C) {
            OSRestoreInterrupts(sound.interrupts);
        }
    }
}

inline void _ssDVDReadAsync(SoundStream* stream, int ch) {
    SoundStreamEntry* entry;
    u32 extra;
    u32 len;
    u32 aligned;
    u32 addr;
    int i;

    len = 0x8000;
    entry = &stream->entries[ch];
    extra = 0;
    if (ch) {
        extra = entry->size + (0x20 - (entry->size % 0x20));
    }
    if (entry->offset + 0x8000 > entry->size) {
        len = entry->size - entry->offset;
    } else {
        for (i = 2; i < 6; i++) {
            if (entry->offset + i * 0x8000 > entry->size) {
                len -= (0x8000 - (entry->size - (entry->offset + (i - 1) * 0x8000))) / i;
                len += 0x20 - (len % 0x20);
                break;
            }
        }
    }
    aligned = (len + 0x1F) & ~0x1F;
    if (!(stream->flags & 0x400)) {
        DVDMgrReadAsync(entry->dvd, entry->loadBuffer[1 - entry->curBuf], aligned,
                        stream->dataOffset + entry->offset + extra, _ssDVDReadAsync_activeChk);
    } else {
        addr = stream->dataOffset + entry->offset + extra + sound.aramAddr[stream->slot];
        DCInvalidateRange(entry->loadBuffer[1 - entry->curBuf], 0x8000);
        ARQPostRequest(&entry->request, (u32)entry, 1, 0, addr, (u32)entry->loadBuffer[1 - entry->curBuf], aligned,
                       cache_flush);
    }
    entry->requestLength = len;
}

inline void _ssResetEntries(SoundStream* stream) {
    stream->entries[0].curBuf = 0;
    stream->entries[0].srcPos = 0;
    stream->entries[0].offset = 0;
    stream->entries[0].pos = 0;
    stream->entries[0].loaded = 0;
    stream->entries[0].ready = 0;
    stream->entries[0].scale = 0;
    stream->entries[0].nibble = 0;
    stream->entries[0].runCount = 0;
    stream->entries[1].curBuf = 0;
    stream->entries[1].srcPos = 0;
    stream->entries[1].offset = 0;
    stream->entries[1].pos = 0;
    stream->entries[1].loaded = 0;
    stream->entries[1].ready = 0;
    stream->entries[1].scale = 0;
    stream->entries[1].nibble = 0;
    stream->entries[1].runCount = 0;
}

void _ssDVDReadAsync_activeChk(s32 result, DVDFileInfo* fileInfo) {
    int i;
    SoundStream* stream;
    SoundStreamEntry* entry;
    int ch;

    SoundIntOff();
    stream = sound.streams;
    for (i = 0; i < 3; i++, stream++) {
        if (stream->flags) {
            entry = NULL;
            ch = 0;
            if (&stream->entries[0].dvd->info == fileInfo) {
                entry = &stream->entries[0];
                ch = 0;
            }
            if (&stream->entries[1].dvd->info == fileInfo) {
                entry = &stream->entries[1];
                ch = 1;
            }
            if (entry) {
                if (result < 0) {
                    goto end;
                }
                entry->offset += entry->requestLength;
                entry->loadedLen[1 - entry->curBuf] = entry->requestLength;
                entry->loaded = 1;
                if (entry->offset >= entry->size) {
                    entry->offset = entry->loopStart;
                    if (stream->flags & 0x200) {
                        if (ch == 0) {
                            stream->flags &= ~0x1000;
                        } else {
                            stream->flags &= ~0x2000;
                        }
                    } else {
                        stream->flags |= 0x4000;
                    }
                } else if (ch == 0) {
                    stream->flags &= ~0x1000;
                } else {
                    stream->flags &= ~0x2000;
                }
                if (stream->count == 2) {
                    if (sound.unk214 == 2 && stream->entries[0].loaded == 1 && stream->entries[1].loaded == 1) {
                        sound.unk214 = 0;
                    }
                } else if (sound.unk214 == 2 && stream->entries[0].loaded == 1) {
                    sound.unk214 = 0;
                }
                break;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        SoundStream* stream = &sound.streams[i];
        if (stream->flags && !(stream->flags & 8)) {
            if (&stream->entries[0].dvd->info == fileInfo) {
                stream->entries[0].ready = 1;
            }
            if (&stream->entries[1].dvd->info == fileInfo) {
                stream->entries[1].ready = 1;
            }
            if (stream->count == 2) {
                if (!stream->entries[0].ready || !stream->entries[1].ready) {
                    continue;
                }
            } else if (!stream->entries[0].ready) {
                continue;
            }
            stream->entries[0].curBuf = 0;
            stream->entries[1].curBuf = 0;
            stream->entries[0].loaded = 0;
            stream->entries[1].loaded = 0;
            sndStreamActivate(stream->entries[0].streamId);
            if (stream->count == 2) {
                sndStreamActivate(stream->entries[1].streamId);
            }
            SoundSSSetPanCh(i, stream->pan);
            stream->flags |= 8;
            break;
        }
    }
end:
    SoundIntOn();
}

#endif
#ifndef NONMATCHING
#pragma dont_inline on
#endif
void cache_flush(u32 pointerToARQRequest) {
    _ssDVDReadAsync_activeChk(0, &((SoundStreamEntry*)((ARQRequest*)pointerToARQRequest)->owner)->dvd->info);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest) {
#ifdef NONMATCHING
    u32 len;
    SoundStream* stream;

    stream = &sound.streams[(u8)((ARQRequest*)pointerToARQRequest)->owner];
    if (stream->entries[0].pos >= DVDMgrGetLength(stream->entries[0].dvd)) {
        stream->entries[0].offset = 0;
        stream->entries[0].pos = 0;
        stream->entries[1].offset = 0;
        stream->entries[1].pos = 0;
        stream->entries[0].curBuf = 1;
        _ssDVDReadAsync(stream, 0);
        if (stream->count == 2) {
            stream->entries[1].curBuf = 1;
            _ssDVDReadAsync(stream, 1);
        }
    } else {
        len = DVDMgrGetLength(stream->entries[0].dvd);
        if (stream->entries[0].offset + 0x8000 >= len) {
            len = len - stream->entries[0].offset;
        } else {
            len = 0x8000;
        }
        DVDMgrReadAsync(stream->entries[0].dvd, stream->entries[0].loadBuffer[0], (len + 0x1F) & ~0x1F,
                        stream->entries[0].offset, _ssDVDReadAsync_cache_next);
        stream->entries[0].requestLength = len;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBF61000C
		opword 0x80030004
		lis r3, sound@ha
		addi r3, r3, sound@l
		opword 0x5400063E
		opword 0x80630100
		opword 0x1C000138
		opword 0x7F830214
		opword 0x807C0028
		bl DVDMgrGetLength
		opword 0x801C0060
		opword 0x7C001840
		opword 0x418002EC
		opword 0x38600000
		opword 0x3C800001
		opword 0x907C005C
		opword 0x38000001
		opword 0x3BFC0028
		opword 0x3BA48000
		opword 0x907C0060
		opword 0x907C00E4
		opword 0x907C00E8
		opword 0xB01C0074
		opword 0x80DC005C
		opword 0x80FC0088
		opword 0x3C660001
		opword 0x38038000
		opword 0x7C003840
		opword 0x4081000C
		opword 0x7FA63850
		opword 0x48000060
		opword 0x38000004
		opword 0x38A00002
		opword 0x7C0903A6
		opword 0x7C062214
		opword 0x7C003840
		opword 0x40810038
		opword 0x3805FFFF
		opword 0x3C600001
		opword 0x54007820
		opword 0x7C860214
		opword 0x38038000
		opword 0x7C643850
		opword 0x7C030050
		opword 0x7C002B96
		opword 0x7FA0E850
		opword 0x57A006FE
		opword 0x20000020
		opword 0x7FBD0214
		opword 0x48000014
		opword 0x3C840001
		opword 0x38A50001
		opword 0x38848000
		opword 0x4200FFB4
		opword 0xA01C0000
		opword 0x387D001F
		opword 0x547E0034
		opword 0x5400056B
		opword 0x40820038
		opword 0xA09F004C
		lis r3, _ssDVDReadAsync_activeChk@ha
		opword 0xA01C0004
		addi r7, r3, _ssDVDReadAsync_activeChk@l
		opword 0x20840001
		opword 0x807F0000
		opword 0x5484103A
		opword 0x7FC5F378
		opword 0x7C9F2214
		opword 0x7CC03214
		opword 0x8084002C
		bl DVDMgrReadAsync
		opword 0x48000080
		opword 0xA07C0002
		lis r5, sound@ha
		opword 0xA01F004C
		opword 0x3C800001
		addi r5, r5, sound@l
		opword 0x5463103A
		opword 0x7C651A14
		opword 0x20000001
		opword 0x5400103A
		opword 0x80A3021C
		opword 0x7C7F0214
		opword 0xA01C0004
		opword 0x7F662A14
		opword 0x8063002C
		opword 0x7F60DA14
		opword 0x38848000
		bl DCInvalidateRange
		opword 0xA01F004C
		lis r3, cache_flush@ha
		addi r10, r3, cache_flush@l
		opword 0x7FE4FB78
		opword 0x20000001
		opword 0x7F67DB78
		opword 0x5400103A
		opword 0x7FC9F378
		opword 0x7C7F0214
		opword 0x38A00001
		opword 0x8103002C
		opword 0x387F0004
		opword 0x38C00000
		bl ARQPostRequest
		opword 0x93BF0048
		opword 0xA01C001A
		opword 0x28000002
		opword 0x408201BC
		opword 0x38000001
		opword 0x3CA00001
		opword 0xB01C00FC
		opword 0x3BFC00B0
		opword 0x3BC58000
		opword 0x807C00E4
		opword 0x80FC0110
		opword 0x3C830001
		opword 0x38048000
		opword 0x54E406FE
		opword 0x7C003840
		opword 0x20040020
		opword 0x7C070214
		opword 0x4081000C
		opword 0x7FC33850
		opword 0x48000060
		opword 0x38800004
		opword 0x38C00002
		opword 0x7C8903A6
		opword 0x7C832A14
		opword 0x7C043840
		opword 0x40810038
		opword 0x38A6FFFF
		opword 0x3C800001
		opword 0x54A57820
		opword 0x7CA32A14
		opword 0x38848000
		opword 0x7CA53850
		opword 0x7C852050
		opword 0x7C843396
		opword 0x7FC4F050
		opword 0x57C406FE
		opword 0x20840020
		opword 0x7FDE2214
		opword 0x48000014
		opword 0x3CA50001
		opword 0x38C60001
		opword 0x38A58000
		opword 0x4200FFB4
		opword 0xA09C0000
		opword 0x38BE001F
		opword 0x54BD0034
		opword 0x5484056B
		opword 0x4082003C
		opword 0xA0BF004C
		lis r4, _ssDVDReadAsync_activeChk@ha
		addi r7, r4, _ssDVDReadAsync_activeChk@l
		opword 0x7CC30214
		opword 0x20850001
		opword 0xA11C0004
		opword 0x5480103A
		opword 0x807F0000
		opword 0x7C9F0214
		opword 0x7FA5EB78
		opword 0x8084002C
		opword 0x7CC83214
		bl DVDMgrReadAsync
		opword 0x48000084
		opword 0xA0DC0002
		lis r7, sound@ha
		opword 0xA0BF004C
		opword 0x3C800001
		addi r7, r7, sound@l
		opword 0x54C6103A
		opword 0x7CC73214
		opword 0x20A50001
		opword 0x54A5103A
		opword 0x80E6021C
		opword 0x7C030214
		opword 0xA0DC0004
		opword 0x7C7F2A14
		opword 0x38848000
		opword 0x7F603A14
		opword 0x8063002C
		opword 0x7F66DA14
		bl DCInvalidateRange
		opword 0xA01F004C
		lis r3, cache_flush@ha
		addi r10, r3, cache_flush@l
		opword 0x7FE4FB78
		opword 0x20000001
		opword 0x7F67DB78
		opword 0x5400103A
		opword 0x7FA9EB78
		opword 0x7C7F0214
		opword 0x38A00001
		opword 0x8103002C
		opword 0x387F0004
		opword 0x38C00000
		bl ARQPostRequest
		opword 0x93DF0048
		opword 0x4800004C
		opword 0x807C0028
		bl DVDMgrGetLength
		opword 0x80DC005C
		opword 0x3C800001
		opword 0x3BA48000
		opword 0x3C860001
		opword 0x38048000
		opword 0x7C001840
		opword 0x41800008
		opword 0x7FA61850
		lis r3, _ssDVDReadAsync_cache_next@ha
		opword 0x381D001F
		addi r7, r3, _ssDVDReadAsync_cache_next@l
		opword 0x807C0028
		opword 0x809C0054
		opword 0x54050034
		bl DVDMgrReadAsync
		opword 0x93BC0070
		opword 0xBB61000C
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void _ssDVDReadAsync_cache_next(s32 result, DVDFileInfo* fileInfo) {
    static u32 owner_no;
    SoundStream* stream;
    u32 dest;
    int i;

    stream = sound.streams;
    for (i = 0; i < 3; stream++, i++) {
        if (stream->flags && &stream->entries[0].dvd->info == fileInfo) {
            if (result >= 0) {
                stream->entries[0].offset += stream->entries[0].requestLength;
                dest = stream->entries[0].pos + sound.aramAddr[stream->slot];
                DCFlushRange(stream->entries[0].loadBuffer[0], 0x8000);
                ARQPostRequest(&stream->entries[0].request, (owner_no++ << 16) | i, 0, 0,
                               (u32)stream->entries[0].loadBuffer[0], dest, 0x8000, _ssDVDReadAsync_cache_aram);
                stream->entries[0].pos += stream->entries[0].requestLength;
            }
            break;
        }
    }
}
#ifdef NONMATCHING

s16 dtbl[16] = {0x0001, 0x0007, 0x0018, 0x003B, 0x0053, 0x006F, 0x00EC, 0x022B,
                0x02E6, 0x0375, 0x041C, 0x08AD, 0x0CD5, 0x1150, 0x1B32, 0x2454};
#endif

u8* ssDecodeDPCM(SoundStream* stream, SoundStreamEntry* entry, s16* out, u32 count, u8* src) {
    s8 delta;
    u32 b;
    u32 scale;
    s32 sample;

    while (count != 0) {
        b = *src;
        if (entry->runCount != 0) {
            if (entry->nibble & 1) {
                delta = b & 0xF;
            } else {
                delta = (b >> 4) & 0xF;
            }
            scale = entry->scale;
            delta <<= 4;
            entry->nibble++;
            delta >>= 4;
            if (entry->nibble >= entry->runCount) {
                entry->runCount = 0;
                src++;
                entry->srcPos++;
            } else if (!(entry->nibble & 1)) {
                src++;
                entry->srcPos++;
            }
        } else {
            src++;
            entry->srcPos++;
            if ((s32)(b & 0xF) == 8) {
                entry->runCount = ((b >> 4) & 0xF) + 4;
                entry->nibble = 0;
                continue;
            }
            scale = (b >> 4) & 0xF;
            entry->scale = scale;
            delta = b & 0xF;
            delta <<= 4;
            delta >>= 4;
        }
        sample = entry->hist + delta * dtbl[scale];
        if (sample > 0x7FFF) {
            sample = 0x7FFF;
        }
        if (sample < -0x8000) {
            sample = -0x8000;
        }
        entry->hist = sample;
        count--;
        *out++ = sample;
        stream->samplePos++;
        if (entry->srcPos >= entry->loadedLen[entry->curBuf]) {
            if (entry->loaded == 0 && !(stream->flags & 0x4000)) {
                entry->pos -= entry->srcPos;
                entry->srcPos = 0;
                src = entry->loadBuffer[entry->curBuf];
                continue;
            }
            entry->loaded = 0;
            entry->srcPos = 0;
            entry->curBuf = 1 - entry->curBuf;
            src = entry->loadBuffer[entry->curBuf];
        }
        entry->pos += 2;
        if (entry->pos >= stream->loopEnd) {
            entry->pos = stream->loopStart;
            entry->hist = entry->loopHist;
            if (!(stream->flags & 0x200)) {
                stream->flags |= 4;
                break;
            }
        }
    }
    return src;
}
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
u32 _sscallback(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user) {
#ifdef NONMATCHING
    s16* dst;
    SoundStream* stream;
    SoundStreamEntry* entry;
    s16* src16;
    u8* dst8;
    u8* src8;
    u32 i;
    u32 n;
    s32 j;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		lis r8, sound@ha
		opword 0x90010024
		opword 0x54E0063E
		addi r10, r8, sound@l
		opword 0x93E1001C
		opword 0x1D000138
		opword 0x38000000
		opword 0x93C10018
		opword 0x93A10014
		opword 0x7CDD3378
		opword 0x7C661B78
		opword 0x93810010
		opword 0x7CBC2B78
		opword 0x812A0100
		opword 0x7FE94214
		opword 0x7C882378
		opword 0x901F0024
		opword 0xA07F0000
		opword 0x70608006
		opword 0x40820010
		opword 0xA00A0214
		opword 0x28000000
		opword 0x418202A4
		opword 0x546005EF
		opword 0x4082019C
		opword 0x28080000
		opword 0x7D034378
		opword 0x38A00000
		opword 0x418200BC
		opword 0x5500E8FF
		opword 0x7C0903A6
		opword 0x41820094
		opword 0xB0A60000
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A60002
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A60004
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A60006
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A60008
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A6000A
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A6000C
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0A6000E
		opword 0x38C60010
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0x4200FF7C
		opword 0x70630007
		opword 0x41820020
		opword 0x7C6903A6
		opword 0xB0A60000
		opword 0x38C60002
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0x4200FFEC
		opword 0x281D0000
		opword 0x7FA3EB78
		opword 0x38A00000
		opword 0x418200BC
		opword 0x57A0E8FF
		opword 0x7C0903A6
		opword 0x41820094
		opword 0xB0BC0000
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC0002
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC0004
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC0006
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC0008
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC000A
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC000C
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0xB0BC000E
		opword 0x3B9C0010
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0x4200FF7C
		opword 0x70630007
		opword 0x41820020
		opword 0x7C6903A6
		opword 0xB0BC0000
		opword 0x3B9C0002
		opword 0x809F0024
		opword 0x38040001
		opword 0x901F0024
		opword 0x4200FFEC
		opword 0x807F0024
		opword 0x480005D4
		opword 0x3C602492
		opword 0x38800000
		opword 0x38034925
		opword 0x7C604016
		opword 0x7C034050
		opword 0x5400F87E
		opword 0x7C001A14
		opword 0x54030038
		opword 0x54000FFE
		opword 0x7C001A14
		opword 0x7C030E71
		opword 0x41820050
		opword 0x5460E8FF
		opword 0x7C0903A6
		opword 0x41820034
		opword 0xB0860000
		opword 0xB0860002
		opword 0xB0860004
		opword 0xB0860006
		opword 0xB0860008
		opword 0xB086000A
		opword 0xB086000C
		opword 0xB086000E
		opword 0x38C60010
		opword 0x4200FFDC
		opword 0x70630007
		opword 0x41820014
		opword 0x7C6903A6
		opword 0xB0860000
		opword 0x38C60002
		opword 0x4200FFF8
		opword 0x3C602492
		opword 0x38800000
		opword 0x38034925
		opword 0x7C60E816
		opword 0x7C03E850
		opword 0x5400F87E
		opword 0x7C001A14
		opword 0x54030038
		opword 0x54000FFE
		opword 0x7C001A14
		opword 0x7C030E71
		opword 0x41820050
		opword 0x5460E8FF
		opword 0x7C0903A6
		opword 0x41820034
		opword 0xB09C0000
		opword 0xB09C0002
		opword 0xB09C0004
		opword 0xB09C0006
		opword 0xB09C0008
		opword 0xB09C000A
		opword 0xB09C000C
		opword 0xB09C000E
		opword 0x3B9C0010
		opword 0x4200FFDC
		opword 0x70630007
		opword 0x41820014
		opword 0x7C6903A6
		opword 0xB09C0000
		opword 0x3B9C0002
		opword 0x4200FFF8
		opword 0x7C68EA14
		opword 0x480004D4
		opword 0x54E005EF
		opword 0x4182000C
		opword 0x3BDF00B0
		opword 0x48000008
		opword 0x3BDF0028
		opword 0x54600631
		opword 0x4182004C
		opword 0xA0BE004C
		opword 0x7FE3FB78
		opword 0x801E0044
		opword 0x7FC4F378
		opword 0x54A7103A
		opword 0x7CC53378
		opword 0x7CFE3A14
		opword 0x7D064378
		opword 0x80E7002C
		opword 0x7CE70214
		bl ssDecodeDPCM
		opword 0x7C671B78
		opword 0x7FE3FB78
		opword 0x7FC4F378
		opword 0x7F85E378
		opword 0x7FA6EB78
		bl ssDecodeDPCM
		opword 0x4800046C
		opword 0x546005EF
		opword 0x41820248
		opword 0x3C602492
		opword 0xA09E004C
		opword 0x3808000D
		opword 0x80FE0044
		opword 0x5485103A
		opword 0x38634925
		opword 0x7C830016
		opword 0x7CBE2A14
		opword 0x80A5002C
		opword 0x7CC33378
		opword 0x7CA53A14
		opword 0x7C040050
		opword 0x5400F87E
		opword 0x7C002214
		opword 0x54040038
		opword 0x480000E4
		opword 0x88050000
		opword 0x38A50001
		opword 0x3884FFFF
		opword 0x98030000
		opword 0x38630001
		opword 0x80DE0044
		opword 0x38060001
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x80FE0044
		opword 0x5406103A
		opword 0x3806003C
		opword 0x7C1E002E
		opword 0x7C070040
		opword 0x4180006C
		opword 0xA81E0054
		opword 0x2C000000
		opword 0x40820038
		opword 0xA01F0000
		opword 0x54000463
		opword 0x4082002C
		opword 0x80BE0038
		opword 0x38000000
		opword 0x7CA72850
		opword 0x90BE0038
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x48000068
		opword 0x38000000
		opword 0xB01E0054
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x20000001
		opword 0xB01E004C
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x80DE0038
		opword 0x38060001
		opword 0x901E0038
		opword 0x80DE0038
		opword 0x801F001C
		opword 0x7C060040
		opword 0x41800024
		opword 0x801F0020
		opword 0x901E0038
		opword 0xA0DF0000
		opword 0x54C005AD
		opword 0x40820010
		opword 0x60C00004
		opword 0xB01F0000
		opword 0x4800000C
		opword 0x28040000
		opword 0x4082FF1C
		opword 0x3C602492
		opword 0x381D000D
		opword 0x38634925
		opword 0x7C830016
		opword 0x7F83E378
		opword 0x7C040050
		opword 0x5400F87E
		opword 0x7C002214
		opword 0x54040038
		opword 0x480000E4
		opword 0x88050000
		opword 0x38A50001
		opword 0x3884FFFF
		opword 0x98030000
		opword 0x38630001
		opword 0x80DE0044
		opword 0x38060001
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x80FE0044
		opword 0x5406103A
		opword 0x3806003C
		opword 0x7C1E002E
		opword 0x7C070040
		opword 0x4180006C
		opword 0xA81E0054
		opword 0x2C000000
		opword 0x40820038
		opword 0xA01F0000
		opword 0x54000463
		opword 0x4082002C
		opword 0x80BE0038
		opword 0x38000000
		opword 0x7CA72850
		opword 0x90BE0038
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x48000068
		opword 0x38000000
		opword 0xB01E0054
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x20000001
		opword 0xB01E004C
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x80DE0038
		opword 0x38060001
		opword 0x901E0038
		opword 0x80DE0038
		opword 0x801F001C
		opword 0x7C060040
		opword 0x41800024
		opword 0x801F0020
		opword 0x901E0038
		opword 0xA0DF0000
		opword 0x54C005AD
		opword 0x40820010
		opword 0x60C00004
		opword 0xB01F0000
		opword 0x4800000C
		opword 0x28040000
		opword 0x4082FF1C
		opword 0x7C08EA14
		opword 0x901F0024
		opword 0x48000220
		opword 0xA0BE004C
		opword 0x7D044378
		opword 0x801E0044
		opword 0x7CC33378
		opword 0x54A5103A
		opword 0x7CBE2A14
		opword 0x5400003C
		opword 0x80A5002C
		opword 0x7CA50214
		opword 0x480000F0
		opword 0xA8050000
		opword 0x38A50002
		opword 0x3884FFFF
		opword 0xB0030000
		opword 0x38630002
		opword 0x80DF0024
		opword 0x38060001
		opword 0x901F0024
		opword 0x80DE0044
		opword 0x38060002
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x80FE0044
		opword 0x5406103A
		opword 0x3806003C
		opword 0x7C1E002E
		opword 0x7C070040
		opword 0x4180006C
		opword 0xA81E0054
		opword 0x2C000000
		opword 0x40820038
		opword 0xA01F0000
		opword 0x54000463
		opword 0x4082002C
		opword 0x80BE0038
		opword 0x38000000
		opword 0x7CA72850
		opword 0x90BE0038
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x48000068
		opword 0x38000000
		opword 0xB01E0054
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x20000001
		opword 0xB01E004C
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x80DE0038
		opword 0x38060002
		opword 0x901E0038
		opword 0x80DE0038
		opword 0x801F001C
		opword 0x7C060040
		opword 0x41800024
		opword 0x801F0020
		opword 0x901E0038
		opword 0xA0DF0000
		opword 0x54C005AD
		opword 0x40820010
		opword 0x60C00004
		opword 0xB01F0000
		opword 0x4800000C
		opword 0x28040000
		opword 0x4082FF10
		opword 0x7FA4EB78
		opword 0x7F83E378
		opword 0x480000F0
		opword 0xA8050000
		opword 0x38A50002
		opword 0x3884FFFF
		opword 0xB0030000
		opword 0x38630002
		opword 0x80DF0024
		opword 0x38060001
		opword 0x901F0024
		opword 0x80DE0044
		opword 0x38060002
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x80FE0044
		opword 0x5406103A
		opword 0x3806003C
		opword 0x7C1E002E
		opword 0x7C070040
		opword 0x4180006C
		opword 0xA81E0054
		opword 0x2C000000
		opword 0x40820038
		opword 0xA01F0000
		opword 0x54000463
		opword 0x4082002C
		opword 0x80BE0038
		opword 0x38000000
		opword 0x7CA72850
		opword 0x90BE0038
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x48000068
		opword 0x38000000
		opword 0xB01E0054
		opword 0x901E0044
		opword 0xA01E004C
		opword 0x20000001
		opword 0xB01E004C
		opword 0xA01E004C
		opword 0x5405103A
		opword 0x3805002C
		opword 0x7CBE002E
		opword 0x80DE0038
		opword 0x38060002
		opword 0x901E0038
		opword 0x80DE0038
		opword 0x801F001C
		opword 0x7C060040
		opword 0x41800024
		opword 0x801F0020
		opword 0x901E0038
		opword 0xA0DF0000
		opword 0x54C005AD
		opword 0x40820010
		opword 0x60C00004
		opword 0xB01F0000
		opword 0x4800000C
		opword 0x28040000
		opword 0x4082FF10
		opword 0x807F0024
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x83810010
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    stream = &sound.streams[(u8)user];
    (& sound.streams [(u8) user])->samplePos = 0;
    dst = buffer1;
    if ((stream->flags & 0x8006) || sound.unk214) {
        if (!(stream->flags & 0x100)) {
            for (; len1 != 0; len1--) {
                *(dst++) = 0;
                stream->samplePos++;
            }
            for (; len2 != 0; len2--) {
                *(((s16*)buffer2)++) = 0;
                stream->samplePos++;
            }
            return stream->samplePos;
        } else {
            j = (s32)(len1 / 14 * 8);
            j /= 2;
            for (; j != 0; j--) {
                *(((s16*)buffer1)++) = 0;
            }
            j = (s32)(len2 / 14 * 8);
            j /= 2;
            for (; j != 0; j--) {
                *(((s16*)buffer2)++) = 0;
            }
            return len1 + len2;
        }
    }
    if (user & 0x100) {
        entry = &stream->entries[1];
    } else {
        entry = &stream->entries[0];
    }
    if (stream->flags & 0x80) {
        ssDecodeDPCM(stream, entry, buffer2, len2,
                     ssDecodeDPCM(stream, entry, buffer1, len1, entry->loadBuffer[entry->curBuf] + entry->srcPos));
    } else if (stream->flags & 0x100) {
        dst8 = buffer1;
        src8 = entry->loadBuffer[entry->curBuf]; src8 = src8 + entry->srcPos;
        n = ((len1 + 13) / 14) * 8;
        while (n != 0) {
            *(dst8++) = *(src8++);
            n--;
            entry->srcPos++;
            if (entry->srcPos >= entry->loadedLen[entry->curBuf]) {
                if (entry->loaded == 0 && !(stream->flags & 0x4000)) {
                    entry->pos -= entry->srcPos;
                    entry->srcPos = 0;
                    src8 = entry->loadBuffer[entry->curBuf];
                    continue;
                }
                entry->loaded = 0;
                entry->srcPos = 0;
                entry->curBuf = 1 - entry->curBuf;
                src8 = entry->loadBuffer[entry->curBuf];
            }
            entry->pos++;
            if (entry->pos >= stream->loopEnd) {
                entry->pos = stream->loopStart;
                if (!(stream->flags & 0x200)) {
                    stream->flags |= 4;
                    break;
                }
            }
        }
        dst8 = buffer2;
        n = ((len2 + 13) / 14) * 8;
        while (n != 0) {
            *(dst8++) = *(src8++);
            n--;
            entry->srcPos++;
            if (entry->srcPos >= entry->loadedLen[entry->curBuf]) {
                if (entry->loaded == 0 && !(stream->flags & 0x4000)) {
                    entry->pos -= entry->srcPos;
                    entry->srcPos = 0;
                    src8 = entry->loadBuffer[entry->curBuf];
                    continue;
                }
                entry->loaded = 0;
                entry->srcPos = 0;
                entry->curBuf = 1 - entry->curBuf;
                src8 = entry->loadBuffer[entry->curBuf];
            }
            entry->pos++;
            if (entry->pos >= stream->loopEnd) {
                entry->pos = stream->loopStart;
                if (!(stream->flags & 0x200)) {
                    stream->flags |= 4;
                    break;
                }
            }
        }
        stream->samplePos = len1 + len2;
    } else {
        n = len1;
        dst = buffer1;
        src16 = (s16*)(entry->loadBuffer[entry->curBuf] + (entry->srcPos & (~1)));
        while (n != 0) {
            *(dst++) = *(src16++);
            n--;
            stream->samplePos++;
            entry->srcPos += 2;
            if (entry->srcPos >= entry->loadedLen[entry->curBuf]) {
                if (entry->loaded == 0 && !(stream->flags & 0x4000)) {
                    entry->pos -= entry->srcPos;
                    entry->srcPos = 0;
                    src16 = (s16*)entry->loadBuffer[entry->curBuf];
                    continue;
                }
                entry->loaded = 0;
                entry->srcPos = 0;
                entry->curBuf = 1 - entry->curBuf;
                src16 = (s16*)entry->loadBuffer[entry->curBuf];
            }
            entry->pos += 2;
            if (entry->pos >= stream->loopEnd) {
                entry->pos = stream->loopStart;
                if (!(stream->flags & 0x200)) {
                    stream->flags |= 4;
                    break;
                }
            }
        }
        n = len2;
        dst = buffer2;
        while (n != 0) {
            *(dst++) = *(src16++);
            n--;
            stream->samplePos++;
            entry->srcPos += 2;
            if (entry->srcPos >= entry->loadedLen[entry->curBuf]) {
                if (entry->loaded == 0 && !(stream->flags & 0x4000)) {
                    entry->pos -= entry->srcPos;
                    entry->srcPos = 0;
                    src16 = (s16*)entry->loadBuffer[entry->curBuf];
                    continue;
                }
                entry->loaded = 0;
                entry->srcPos = 0;
                entry->curBuf = 1 - entry->curBuf;
                src16 = (s16*)entry->loadBuffer[entry->curBuf];
            }
            entry->pos += 2;
            if (entry->pos >= stream->loopEnd) {
                entry->pos = stream->loopStart;
                if (!(stream->flags & 0x200)) {
                    stream->flags |= 4;
                    break;
                }
            }
        }
    }
    return stream->samplePos;
}

void SoundSSPlayChEx(s32 chan, const char* name, s32 aram);

#endif
#ifndef NONMATCHING
#pragma dont_inline on
#endif
void SoundSSPlayCh(s32 chan, const char* name) {
    SoundSSPlayChEx(chan, name, 0);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#define SoundSSStopCh SoundSSStopCh__af_inl
#endif
void SoundSSPlayChEx(s32 chan, const char* name, s32 aram) {
    SoundStream* stream;
    int i;
    const char* new_var2 [2]; // FAKE: alias array needed for 100% (a plain str/root form is 5 rows off)

    stream = &sound.streams[chan];
    if (stream->flags) {
        SoundSSStopCh(chan);
    }
    if (aram) {
        for (i = 0; i < sound.slotCount; i++) {
            if (!sound.slotUsed[i]) {
                sound.slotUsed[i] = 1;
                stream->slot = i;
                break;
            }
        }
        if (i >= sound.slotCount) {
            return;
        }
    }
    sound.unk104 = chan;
    _ssResetEntries(stream);
    stream->pan = 0x40;
    stream->span = 0;
#ifdef NONMATCHING
    stream->curVol = 0.0f;
    stream->vol = 127.0f;
#endif
#ifndef NONMATCHING
    stream->curVol = EXT_LIT(float_0_8041b6d8, 0.0f);
    stream->vol = EXT_LIT(float_127_8041b6e8, 127.0f);
#endif
    stream->flags = 1;
    if (aram) {
        stream->flags |= 0x400;
    }
    new_var2 [1] = getMarioStDvdRoot ();
#ifdef NONMATCHING
    sprintf(str, "%s/%s%s", new_var2 [1], name, ".stm");
#endif
#ifndef NONMATCHING
    sprintf(str, EXT_LIT((char*)str_802E5728, "%s/%s%s"), new_var2 [1], name, EXT_LIT((char*)str_8041B6EC, ".stm"));
#endif
    if (!(stream->entries[0].dvd = DVDMgrOpen(new_var2 [0] = str, 0, 0))) {
        stream->flags = 0;
        return;
    }
    if (!(stream->entries[1].dvd = DVDMgrOpen(new_var2 [0], 0, 0))) {
        stream->flags = 0;
        return;
    }
    DVDMgrReadAsync(stream->entries[0].dvd, stream->entries[0].buffer, 0x100, 0, SoundSSPlayChEx_main);
}

#ifndef NONMATCHING
#undef SoundSSStopCh

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo) {
#ifdef NONMATCHING
    SoundStream* stream;
    u8* dst;
    u8* src;
    StreamHeader* header;
    u8 type;
    u8 pan;
    u32 size;
    u32 len;
    int i;
    int j;

    if (result >= 0) {
        for (i = 0; i < 3; i++) {
            stream = &sound.streams[i];
            if (stream->flags && &stream->entries[0].dvd->info == fileInfo) {
                break;
            }
        }
        header = stream->entries[0].buffer;
        type = header->type;
        stream->freq = header->freq;
        stream->count = header->count;
        stream->loopEnd = header->loopEnd;
        stream->loopStart = header->loopStart;
        stream->entries[0].size = header->size0;
        stream->entries[1].size = header->size1;
        stream->entries[0].loopStart = header->loopStart0;
        stream->entries[1].loopStart = header->loopStart1;
        stream->entries[0].initHist = header->initHist0;
        stream->entries[1].initHist = header->initHist1;
        stream->entries[0].loopHist = header->loopHist0;
        stream->entries[1].loopHist = header->loopHist1;
        if (stream->loopStart != -1) {
            stream->flags |= 0x200;
        } else {
            stream->loopStart = 0;
        }
        switch (type) {
            case 0:
                stream->entries[0].size = stream->loopEnd;
                stream->entries[1].size = stream->loopEnd;
                stream->entries[0].loopStart = stream->loopStart;
                stream->entries[1].loopStart = stream->loopStart;
                stream->dataOffset = 0x40;
                break;
            case 1:
                stream->flags |= 0x80;
                stream->entries[0].hist = stream->entries[0].initHist;
                stream->entries[1].hist = stream->entries[1].initHist;
                stream->dataOffset = 0x40;
                break;
            case 2:
                stream->flags |= 0x100;
                src = (u8*)header + 0x5C;
                dst = (u8*)&stream->entries[0].info;
                for (j = 32; j != 0; j--) {
                    *dst++ = *src++;
                }
                if (stream->count == 2) {
                    u8* d2;
                    u8* s2;
                    for (s2 = (u8*)header + 0xBC, d2 = (u8*)&stream->entries[1].info, j = 32; j != 0; j--) {
                        *d2++ = *s2++;
                    }
                }
                stream->dataOffset = 0x100;
                break;
        }
        _ssResetEntries(stream);
        if (!(stream->flags & 0x400)) {
            stream->entries[0].curBuf = 1;
            _ssDVDReadAsync(stream, 0);
            stream->flags |= 0x1000;
            if (stream->count == 2) {
                stream->entries[1].curBuf = 1;
                _ssDVDReadAsync(stream, 1);
                stream->flags |= 0x2000;
            }
        }
        size = sndStreamAllocLength(0xE00, 0);
        { u8* p = (u8*)stream->entries[0].buffer; u32 n; for (n = size; n != 0; n--) { *p++ = 0; } }
        if (stream->count == 2) {
            { u8* p = (u8*)stream->entries[1].buffer; u32 n; for (n = size; n != 0; n--) { *p++ = 0; } }
        }
        pan = 0;
        if (stream->count == 1) {
            pan = 0x40;
        }
        if (!(stream->flags & 0x100)) {
            stream->entries[0].streamId = sndStreamAllocEx(0xFF, stream->entries[0].buffer, 0xE00, stream->freq, 0, pan,
                                                           0, 0, 0, 0, 0x10000, _sscallback, i, NULL);
            if (stream->count == 2) {
                stream->entries[1].streamId = sndStreamAllocEx(0xFF, stream->entries[1].buffer, 0xE00, stream->freq, 0,
                                                               0x7F, 0, 0, 0, 0, 0x10000, _sscallback, i | 0x100, NULL);
            }
            stream->flags |= 8;
        } else {
            stream->entries[0].streamId =
                sndStreamAllocEx(0xFF, stream->entries[0].buffer, 0xE00, stream->freq, 0, pan, 0, 0, 0, 0, 0x10001,
                                 _sscallback, i, &stream->entries[0].info);
            if (stream->count == 2) {
                stream->entries[1].streamId =
                    sndStreamAllocEx(0xFF, stream->entries[1].buffer, 0xE00, stream->freq, 0, 0x7F, 0, 0, 0, 0, 0x10001,
                                     _sscallback, i | 0x100, &stream->entries[1].info);
            }
        }
        stream->fadeStep = stream->vol;
        stream->flags |= 0x10;
        SoundSSSetPanCh(i, stream->pan);
        if (stream->flags & 0x400) {
            len = DVDMgrGetLength(stream->entries[0].dvd);
            if (stream->entries[0].offset + 0x8000 >= len) {
                size = len - stream->entries[0].offset;
            } else {
                size = 0x8000;
            }
            DVDMgrReadAsync(stream->entries[0].dvd, stream->entries[0].loadBuffer[0], (size + 0x1F) & ~0x1F,
                            stream->entries[0].offset, _ssDVDReadAsync_cache_next);
            stream->entries[0].requestLength = size;
        }
    }
#endif
#ifndef NONMATCHING
	char _af_pad[52];
	asm volatile {
		opword 0x2C030000
		opword 0x41800994
		lis r3, sound@ha
		opword 0x3BC00000
		addi r29, r3, sound@l
		opword 0x80BD0100
		opword 0xA0050000
		opword 0x7CBF2B78
		opword 0x28000000
		opword 0x41820014
		opword 0x80650028
		opword 0x38030040
		opword 0x7C002040
		opword 0x41820050
		opword 0xA4050138
		opword 0x3BC00001
		opword 0x28000000
		opword 0x7CBF2B78
		opword 0x41820014
		opword 0x80650028
		opword 0x38030040
		opword 0x7C002040
		opword 0x4182002C
		opword 0xA4050138
		opword 0x3BC00002
		opword 0x28000000
		opword 0x7CBF2B78
		opword 0x41820014
		opword 0x80650028
		opword 0x38030040
		opword 0x7C002040
		opword 0x41820008
		opword 0x3BC00003
		opword 0x807F0050
		opword 0x88A30000
		opword 0xA0030002
		opword 0xB01F0018
		opword 0x80030004
		opword 0xB01F001A
		opword 0x80030008
		opword 0x901F001C
		opword 0x8003000C
		opword 0x901F0020
		opword 0x80030010
		opword 0x901F0088
		opword 0x80030014
		opword 0x901F0110
		opword 0x80030018
		opword 0x901F008C
		opword 0x8003001C
		opword 0x901F0114
		opword 0xA0030020
		opword 0xB01F0076
		opword 0xA0030022
		opword 0xB01F00FE
		opword 0xA0030024
		opword 0xB01F0078
		opword 0xA0030026
		opword 0xB01F0100
		opword 0x809F0020
		opword 0x3C040001
		opword 0x2800FFFF
		opword 0x41820014
		opword 0xA01F0000
		opword 0x60000200
		opword 0xB01F0000
		opword 0x4800000C
		opword 0x38000000
		opword 0x901F0020
		opword 0x2C050001
		opword 0x4182004C
		opword 0x40800010
		opword 0x2C050000
		opword 0x40800014
		opword 0x4800013C
		opword 0x2C050003
		opword 0x40800134
		opword 0x48000058
		opword 0x807F001C
		opword 0x38000040
		opword 0x907F0088
		opword 0x807F001C
		opword 0x907F0110
		opword 0x807F0020
		opword 0x907F008C
		opword 0x807F0020
		opword 0x907F0114
		opword 0xB01F0004
		opword 0x48000104
		opword 0xA07F0000
		opword 0x38000040
		opword 0x60630080
		opword 0xB07F0000
		opword 0xA87F0076
		opword 0xB07F007A
		opword 0xA87F00FE
		opword 0xB07F0102
		opword 0xB01F0004
		opword 0x480000DC
		opword 0xA09F0000
		opword 0x38000004
		opword 0x38C3005C
		opword 0x38BF0090
		opword 0x60840100
		opword 0xB09F0000
		opword 0x7C0903A6
		opword 0x88060000
		opword 0x98050000
		opword 0x88060001
		opword 0x98050001
		opword 0x88060002
		opword 0x98050002
		opword 0x88060003
		opword 0x98050003
		opword 0x88060004
		opword 0x98050004
		opword 0x88060005
		opword 0x98050005
		opword 0x88060006
		opword 0x98050006
		opword 0x88060007
		opword 0x38C60008
		opword 0x98050007
		opword 0x38A50008
		opword 0x4200FFB8
		opword 0xA01F001A
		opword 0x28000002
		opword 0x40820060
		opword 0x38000004
		opword 0x388300BC
		opword 0x387F0118
		opword 0x7C0903A6
		opword 0x88040000
		opword 0x98030000
		opword 0x88040001
		opword 0x98030001
		opword 0x88040002
		opword 0x98030002
		opword 0x88040003
		opword 0x98030003
		opword 0x88040004
		opword 0x98030004
		opword 0x88040005
		opword 0x98030005
		opword 0x88040006
		opword 0x98030006
		opword 0x88040007
		opword 0x38840008
		opword 0x98030007
		opword 0x38630008
		opword 0x4200FFB8
		opword 0x38000100
		opword 0xB01F0004
		opword 0x38000000
		opword 0xB01F0074
		opword 0x901F006C
		opword 0x901F005C
		opword 0x901F0060
		opword 0xB01F007C
		opword 0xB01F007E
		opword 0xB01F0080
		opword 0xB01F0082
		opword 0xB01F0084
		opword 0xB01F00FC
		opword 0x901F00F4
		opword 0x901F00E4
		opword 0x901F00E8
		opword 0xB01F0104
		opword 0xB01F0106
		opword 0xB01F0108
		opword 0xB01F010A
		opword 0xB01F010C
		opword 0xA01F0000
		opword 0x5400056B
		opword 0x408202EC
		opword 0x38000001
		opword 0x3C800001
		opword 0xB01F0074
		opword 0x3B9F0028
		opword 0x3B448000
		opword 0x80DF005C
		opword 0x80FF0088
		opword 0x3C660001
		opword 0x38038000
		opword 0x7C003840
		opword 0x4081000C
		opword 0x7F463850
		opword 0x48000060
		opword 0x38000004
		opword 0x38A00002
		opword 0x7C0903A6
		opword 0x7C062214
		opword 0x7C003840
		opword 0x40810038
		opword 0x3805FFFF
		opword 0x3C600001
		opword 0x54007820
		opword 0x7C860214
		opword 0x38038000
		opword 0x7C643850
		opword 0x7C030050
		opword 0x7C002B96
		opword 0x7F40D050
		opword 0x574006FE
		opword 0x20000020
		opword 0x7F5A0214
		opword 0x48000014
		opword 0x3C840001
		opword 0x38A50001
		opword 0x38848000
		opword 0x4200FFB4
		opword 0xA01F0000
		opword 0x387A001F
		opword 0x547B0034
		opword 0x5400056B
		opword 0x40820038
		opword 0xA09C004C
		lis r3, _ssDVDReadAsync_activeChk@ha
		opword 0xA01F0004
		addi r7, r3, _ssDVDReadAsync_activeChk@l
		opword 0x20840001
		opword 0x807C0000
		opword 0x5484103A
		opword 0x7F65DB78
		opword 0x7C9C2214
		opword 0x7CC03214
		opword 0x8084002C
		bl DVDMgrReadAsync
		opword 0x48000080
		opword 0xA07F0002
		lis r5, sound@ha
		opword 0xA01C004C
		opword 0x3C800001
		addi r5, r5, sound@l
		opword 0x5463103A
		opword 0x7C651A14
		opword 0x20000001
		opword 0x5400103A
		opword 0x80A3021C
		opword 0x7C7C0214
		opword 0xA01F0004
		add r25, r6, r5
		opword 0x8063002C
		opword 0x7F20CA14
		opword 0x38848000
		bl DCInvalidateRange
		opword 0xA01C004C
		lis r3, cache_flush@ha
		addi r10, r3, cache_flush@l
		opword 0x7F84E378
		opword 0x20000001
		opword 0x7F27CB78
		opword 0x5400103A
		opword 0x7F69DB78
		opword 0x7C7C0214
		opword 0x38A00001
		opword 0x8103002C
		opword 0x387C0004
		opword 0x38C00000
		bl ARQPostRequest
		opword 0x935C0048
		opword 0xA01F0000
		opword 0x60001000
		opword 0xB01F0000
		opword 0xA01F001A
		opword 0x28000002
		opword 0x4082017C
		opword 0x38000001
		opword 0x3CA00001
		opword 0xB01F00FC
		opword 0x3B9F00B0
		opword 0x3B658000
		opword 0x807F00E4
		opword 0x80FF0110
		opword 0x3C830001
		opword 0x38048000
		opword 0x54E406FE
		opword 0x7C003840
		opword 0x20040020
		opword 0x7C070214
		opword 0x4081000C
		opword 0x7F633850
		opword 0x48000060
		opword 0x38800004
		opword 0x38C00002
		opword 0x7C8903A6
		opword 0x7C832A14
		opword 0x7C043840
		opword 0x40810038
		opword 0x38A6FFFF
		opword 0x3C800001
		opword 0x54A57820
		opword 0x7CA32A14
		opword 0x38848000
		opword 0x7CA53850
		opword 0x7C852050
		opword 0x7C843396
		opword 0x7F64D850
		opword 0x576406FE
		opword 0x20840020
		opword 0x7F7B2214
		opword 0x48000014
		opword 0x3CA50001
		opword 0x38C60001
		opword 0x38A58000
		opword 0x4200FFB4
		opword 0xA09F0000
		opword 0x38BB001F
		opword 0x54BA0034
		opword 0x5484056B
		opword 0x4082003C
		opword 0xA0BC004C
		lis r4, _ssDVDReadAsync_activeChk@ha
		addi r7, r4, _ssDVDReadAsync_activeChk@l
		opword 0x7CC30214
		opword 0x20850001
		opword 0xA11F0004
		opword 0x5480103A
		opword 0x807C0000
		opword 0x7C9C0214
		opword 0x7F45D378
		opword 0x8084002C
		opword 0x7CC83214
		bl DVDMgrReadAsync
		opword 0x48000084
		opword 0xA0DF0002
		lis r7, sound@ha
		opword 0xA0BC004C
		opword 0x3C800001
		addi r7, r7, sound@l
		opword 0x54C6103A
		opword 0x7CC73214
		opword 0x20A50001
		opword 0x54A5103A
		opword 0x80E6021C
		opword 0x7C030214
		opword 0xA0DF0004
		opword 0x7C7C2A14
		opword 0x38848000
		opword 0x7F203A14
		opword 0x8063002C
		opword 0x7F26CA14
		bl DCInvalidateRange
		opword 0xA01C004C
		lis r3, cache_flush@ha
		addi r10, r3, cache_flush@l
		opword 0x7F84E378
		opword 0x20000001
		opword 0x7F27CB78
		opword 0x5400103A
		opword 0x7F49D378
		opword 0x7C7C0214
		opword 0x38A00001
		opword 0x8103002C
		opword 0x387C0004
		opword 0x38C00000
		bl ARQPostRequest
		opword 0x937C0048
		opword 0xA01F0000
		opword 0x60002000
		opword 0xB01F0000
		opword 0x38600E00
		opword 0x38800000
		bl sndStreamAllocLength
		opword 0x28030000
		opword 0x80DF0050
		opword 0x38A00000
		opword 0x7C641B78
		opword 0x41820050
		opword 0x5480E8FF
		opword 0x7C0903A6
		opword 0x41820034
		opword 0x98A60000
		opword 0x98A60001
		opword 0x98A60002
		opword 0x98A60003
		opword 0x98A60004
		opword 0x98A60005
		opword 0x98A60006
		opword 0x98A60007
		opword 0x38C60008
		opword 0x4200FFDC
		opword 0x70840007
		opword 0x41820014
		opword 0x7C8903A6
		opword 0x98A60000
		opword 0x38C60001
		opword 0x4200FFF8
		opword 0xA01F001A
		opword 0x28000002
		opword 0x40820060
		opword 0x28030000
		opword 0x80BF00D8
		opword 0x38800000
		opword 0x41820050
		opword 0x5460E8FF
		opword 0x7C0903A6
		opword 0x41820034
		opword 0x98850000
		opword 0x98850001
		opword 0x98850002
		opword 0x98850003
		opword 0x98850004
		opword 0x98850005
		opword 0x98850006
		opword 0x98850007
		opword 0x38A50008
		opword 0x4200FFDC
		opword 0x70630007
		opword 0x41820014
		opword 0x7C6903A6
		opword 0x98850000
		opword 0x38A50001
		opword 0x4200FFF8
		opword 0xA01F001A
		opword 0x39000000
		opword 0x28000001
		opword 0x40820008
		opword 0x39000040
		opword 0xA01F0000
		opword 0x540005EF
		opword 0x408200C0
		opword 0x38C00000
		lis r3, _sscallback@ha
		stw r6, _af_pad+0(r1)
		addi r0, r3, _sscallback@l
		opword 0x3C800001
		opword 0x386000FF
		opword 0x90C1000C
		opword 0x38A00E00
		opword 0x38E00000
		opword 0x39200000
		opword 0x90810010
		opword 0x39400000
		opword 0x90010014
		opword 0x93C10018
		opword 0x90C1001C
		opword 0x809F0050
		opword 0xA0DF0018
		bl sndStreamAllocEx
		opword 0x907F004C
		opword 0xA01F001A
		opword 0x28000002
		opword 0x40820058
		opword 0x39600000
		lis r3, _sscallback@ha
		opword 0x91610008
		opword 0x3CC00001
		addi r4, r3, _sscallback@l
		opword 0x63C00100
		opword 0x9161000C
		opword 0x386000FF
		opword 0x38A00E00
		opword 0x38E00000
		opword 0x90C10010
		opword 0x3900007F
		opword 0x39200000
		opword 0x39400000
		opword 0x90810014
		opword 0x90010018
		opword 0x9161001C
		opword 0x809F00D8
		opword 0xA0DF0018
		bl sndStreamAllocEx
		opword 0x907F00D4
		opword 0xA01F0000
		opword 0x60000008
		opword 0xB01F0000
		opword 0x480000C0
		opword 0x38C00000
		opword 0x3C800001
		opword 0x90C10008
		opword 0x38A40001
		lis r3, _sscallback@ha
		opword 0x381F0090
		opword 0x90C1000C
		addi r4, r3, _sscallback@l
		opword 0x386000FF
		opword 0x38E00000
		opword 0x90A10010
		opword 0x38A00E00
		opword 0x39200000
		opword 0x39400000
		opword 0x90810014
		opword 0x93C10018
		opword 0x9001001C
		opword 0x809F0050
		opword 0xA0DF0018
		bl sndStreamAllocEx
		opword 0x907F004C
		opword 0xA01F001A
		opword 0x28000002
		opword 0x40820060
		opword 0x38000000
		opword 0x3C800001
		opword 0x90010008
		lis r3, _sscallback@ha
		opword 0x38A40001
		opword 0x63C40100
		opword 0x9001000C
		addi r6, r3, _sscallback@l
		opword 0x381F0118
		opword 0x386000FF
		opword 0x90A10010
		opword 0x38A00E00
		opword 0x38E00000
		opword 0x3900007F
		opword 0x90C10014
		opword 0x39200000
		opword 0x39400000
		opword 0x90810018
		opword 0x9001001C
		opword 0x809F00D8
		opword 0xA0DF0018
		bl sndStreamAllocEx
		opword 0x907F00D4
		opword 0xC01F000C
		opword 0x1C1E0138
		opword 0xD01F0014
		opword 0xA07F0000
		opword 0x60630010
		opword 0xB07F0000
		opword 0x807D0100
		opword 0xA09F0006
		opword 0x7F430214
		opword 0xA01A0000
		opword 0x5485063E
		opword 0x28000000
		opword 0x41820104
		opword 0xB0BA0006
		opword 0xA01A0000
		opword 0x54000739
		opword 0x418200F4
		opword 0xA01A001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01A0010
		opword 0x38E00000
		opword 0xA01A0008
		opword 0xFC00001E
		opword 0x807A004C
		opword 0x5406063E
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0x480000C0
		opword 0xC07A0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A10024
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010020
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC2100F2
		fdivs f31, f1, f0
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x9061002C
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010028
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210028
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01A0008
		opword 0x807A004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010030
		opword 0x80810034
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01A0008
		opword 0x807A00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010038
		opword 0x8081003C
		bl sndStreamMixParameter
		opword 0xA01F0000
		opword 0x5400056B
		opword 0x4182004C
		opword 0x807F0028
		bl DVDMgrGetLength
		opword 0x80DF005C
		opword 0x3C800001
		opword 0x3B448000
		opword 0x3C860001
		opword 0x38048000
		opword 0x7C001840
		opword 0x41800008
		opword 0x7F461850
		lis r3, _ssDVDReadAsync_cache_next@ha
		opword 0x381A001F
		addi r7, r3, _ssDVDReadAsync_cache_next@l
		opword 0x807F0028
		opword 0x809F0054
		opword 0x54050034
		bl DVDMgrReadAsync
		opword 0x935F0070
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void SoundSSStopCh(s32 chan) {
    SoundStream* stream;

    if (sound.streams[chan].flags) {
        stream = (0, &sound.streams[chan]);
        SoundIntOff();
        if (stream->flags & 0x400) {
            sound.slotUsed[stream->slot] = 0;
        }
        stream->flags = 0;
        DVDMgrClose(stream->entries[0].dvd);
        DVDMgrClose(stream->entries[1].dvd);
        sndStreamFree(stream->entries[0].streamId);
        if (stream->count == 2) {
            sndStreamFree(stream->entries[1].streamId);
        }
        SoundIntOn();
        sound.unk104 = -1;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void SoundSSFadeoutCh(s32 chan) {
#ifdef NONMATCHING
    SoundStream* stream = &sound.streams[chan];
    f32 frames;

    if (stream->flags) {
        frames = sound.fadeOut / 16.666666f;
        if (frames < 1.0f) {
            frames = 1.0f;
        }
        stream->fadeStep = stream->curVol / frames;
        stream->flags |= 0x20;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		lis r4, sound@ha
		opword 0x9421FFF0
		addi r4, r4, sound@l
		opword 0x1C030138
		opword 0x80640100
		opword 0x7CA30214
		opword 0xA0050000
		opword 0x28000000
		opword 0x41820054
		opword 0xA084020A
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90010008
		lfd f3, double_to_int_mask_802e5718@l(r3)
		opword 0x9081000C
		lfs f1, float_16p667_8041b6e0(r2)
		opword 0xC8410008
		lfs f0, float_1_8041b6e4(r2)
		opword 0xEC421828
		opword 0xEC220824
		opword 0xFC010040
		opword 0x40800008
		opword 0xFC200090
		opword 0xC0050010
		opword 0xEC000824
		opword 0xD0050014
		opword 0xA0050000
		opword 0x60000020
		opword 0xB0050000
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void SoundSSContinueCh(s32 chan) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->flags &= ~2;
        stream->fadeStep = stream->vol;
        stream->flags |= 0x10;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void SoundSSSetPanCh(s32 chan, u8 pan) {
#ifdef NONMATCHING
    SoundStream* stream = (0, &sound.streams[chan]);
    f32 left, right;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0x93E1002C
		lis r5, sound@ha
		addi r5, r5, sound@l
		opword 0x1C030138
		opword 0x80650100
		opword 0x7FE30214
		opword 0xA01F0000
		opword 0x28000000
		opword 0x41820110
		opword 0x5485063E
		opword 0xB0BF0006
		opword 0xA01F0000
		opword 0x54000739
		opword 0x418200FC
		opword 0xA01F001A
		opword 0x28000001
		opword 0x40820030
		opword 0xC01F0010
		opword 0x7C852378
		opword 0xA01F0008
		opword 0x38E00000
		opword 0xFC00001E
		opword 0x807F004C
		opword 0x5406063E
		opword 0xD8010008
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0x480000C4
		opword 0xC07F0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A1000C
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010008
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x5483063E
		opword 0x3803FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2063007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x90610014
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010010
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210010
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01F0008
		opword 0x807F004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010018
		opword 0x8081001C
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01F0008
		opword 0x807F00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0xE3E10038
		opword 0x80010044
		opword 0xCBE10030
		opword 0x83E1002C
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    if (stream->flags) {
        stream->pan = pan;
        if (stream->flags & 8) {
            if (stream->count == 1) {
                sndStreamMixParameter(stream->entries[0].streamId, stream->curVol, pan, stream->span, 0);
            } else {
                left = stream->curVol;
                right = left;
                if (pan < 64) {
                    right = (((f32)pan * stream->curVol) / 63.0f);
                }
                if (!((u32)(pan - 64) >> 31)) {
                    left = (((f32)(127 - pan) * stream->curVol) / 63.0f);
                }
                sndStreamMixParameter(stream->entries[0].streamId, left, 0, stream->span, 0);
                sndStreamMixParameter(stream->entries[1].streamId, right, 0x7F, stream->span, 0);
            }
        }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void SoundSSSetVolCh(s32 chan, u8 vol) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0x93E1002C
		lis r5, sound@ha
		addi r5, r5, sound@l
		opword 0x1CE30138
		opword 0x80050100
		opword 0x7CC03A14
		opword 0xA0060000
		opword 0x28000000
		opword 0x41820148
		opword 0x5480063E
		opword 0x3C804330
		opword 0x9001000C
		lis r3, double_to_int_mask_802e5718@ha
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90810008
		opword 0xC8010008
		opword 0xEC001028
		opword 0xD0060010
		opword 0xD006000C
		opword 0xA0060000
		opword 0x54000739
		opword 0x41820114
		opword 0x80050100
		opword 0xA0660006
		opword 0x7FE03A14
		opword 0xA01F0000
		opword 0x5465063E
		opword 0x28000000
		opword 0x418200F8
		opword 0xB0BF0006
		opword 0xA01F0000
		opword 0x54000739
		opword 0x418200E8
		opword 0xA01F001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01F0010
		opword 0x38E00000
		opword 0xA01F0008
		opword 0xFC00001E
		opword 0x807F004C
		opword 0x5406063E
		opword 0xD8010008
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0x480000B4
		opword 0xC07F0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x40800020
		opword 0x90A1000C
		lfs f0, float_63_8041b6dc(r2)
		opword 0x90810008
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x90610014
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010010
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210010
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01F0008
		opword 0x807F004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010018
		opword 0x8081001C
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01F0008
		opword 0x807F00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0xE3E10038
		opword 0x80010044
		opword 0xCBE10030
		opword 0x83E1002C
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
#ifdef NONMATCHING

void SoundSSSetVolCh(s32 chan, u8 vol) {
    SoundStream* stream;

    if (sound.streams[chan].flags) {
        stream = &sound.streams[chan];
        stream->vol = stream->curVol = vol;
        if (stream->flags & 8) {
            SoundSSSetPanCh(chan, stream->pan);
        }
    }
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

s32 SoundSSGetVolCh(s32 chan) {
    SoundStream* stream;

    stream = &sound.streams[chan];
    if (stream->flags) {
        return (s32)stream->vol;
    } else {
        return 0;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void SoundSSSetSrndPanCh(s32 chan, u8 span) {
#ifdef NONMATCHING
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->span = span;
        if (stream->flags & 8) {
            SoundSSSetPanCh(chan, stream->pan);
        }
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0x93E1002C
		lis r5, sound@ha
		addi r5, r5, sound@l
		opword 0x1CC30138
		opword 0x80050100
		opword 0x7C603214
		opword 0xA0030000
		opword 0x28000000
		opword 0x41820134
		opword 0x5480063E
		opword 0xB0030008
		opword 0xA0030000
		opword 0x54000739
		opword 0x41820120
		opword 0x80050100
		opword 0xA0630006
		opword 0x7FE03214
		opword 0xA01F0000
		opword 0x5465063E
		opword 0x28000000
		opword 0x41820104
		opword 0xB0BF0006
		opword 0xA01F0000
		opword 0x54000739
		opword 0x418200F4
		opword 0xA01F001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01F0010
		opword 0x38E00000
		opword 0xA01F0008
		opword 0xFC00001E
		opword 0x807F004C
		opword 0x5406063E
		opword 0xD8010008
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0x480000C0
		opword 0xC07F0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A1000C
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010008
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x90610014
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010010
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210010
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01F0008
		opword 0x807F004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010018
		opword 0x8081001C
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01F0008
		opword 0x807F00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0xE3E10038
		opword 0x80010044
		opword 0xCBE10030
		opword 0x83E1002C
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void SoundSSSetPlayFreqCh(s32 chan, u16 freq) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->freq = freq;
        if (stream->flags & 8) {
            SoundIntOff();
            sndStreamFrq(stream->entries[0].streamId, stream->freq);
            if (stream->count == 2) {
                sndStreamFrq(stream->entries[1].streamId, stream->freq);
            }
            SoundIntOn();
        }
    }
}

u16 SoundSSCheck(s32 chan) {
    return sound.streams[chan].flags;
}

void SoundSSMuteOn(s32 chan) {
    if (sound.streams[chan].flags) {
        sound.streams[chan].flags |= 2;
    }
}

void SoundSSMuteOff(s32 chan) {
    if (sound.streams[chan].flags) {
        sound.streams[chan].flags &= ~2;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void SoundSSMain(void) {
#ifdef NONMATCHING
    u32 i;
    SoundStream* stream;
#endif
#ifndef NONMATCHING
	char _af_pad[24];
	asm volatile {
		li r26, 0x0
		lis r3, sound@ha
		opword 0x7F5ED378
		opword 0x3B800000
		addi r31, r3, sound@l
		opword 0x801F0100
		opword 0x7F60F214
		opword 0xA07B0000
		opword 0x54600739
		opword 0x418205CC
		opword 0x546007BD
		opword 0x408205C4
		opword 0x5460077B
		opword 0x418200CC
		opword 0x546007B8
		opword 0xB01B0000
		opword 0x801F0100
		opword 0x7FA0D214
		opword 0xA01D0000
		opword 0x28000000
		opword 0x418205A0
		opword 0xA01F020C
		opword 0x28000000
		opword 0x4082000C
		bl OSDisableInterrupts
		opword 0x907F0210
		opword 0xA07F020C
		opword 0x38030001
		opword 0xB01F020C
		opword 0xA01D0000
		opword 0x5400056B
		opword 0x41820020
		opword 0xA09D0002
		lis r3, sound@ha
		addi r0, r3, sound@l
		opword 0x38A00000
		opword 0x5483083C
		opword 0x7C601A14
		opword 0xB0A30226
		opword 0x38000000
		opword 0xB01D0000
		opword 0x807D0028
		bl DVDMgrClose
		opword 0x807D00B0
		bl DVDMgrClose
		opword 0x807D004C
		bl sndStreamFree
		opword 0xA01D001A
		opword 0x28000002
		opword 0x4082000C
		opword 0x807D00D4
		bl sndStreamFree
		opword 0xA07F020C
		opword 0x28030000
		opword 0x4182001C
		opword 0x3863FFFF
		opword 0x5460043F
		opword 0xB07F020C
		opword 0x4082000C
		opword 0x807F0210
		bl OSRestoreInterrupts
		opword 0x3800FFFF
		opword 0x901F0104
		opword 0x480004F4
		opword 0x54600673
		opword 0x41820168
		lfs f2, float_0_8041b6d8(r2)
		opword 0xC03B0010
		opword 0xFC020800
		opword 0x4082001C
		opword 0x60600002
		opword 0xB01B0000
		opword 0xA01B0000
		opword 0x540006B0
		opword 0xB01B0000
		opword 0x480004C4
		opword 0xC01B0014
		opword 0xEC010028
		opword 0xD01B0010
		opword 0xC01B0010
		opword 0xFC001040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD05B0010
		opword 0x801F0100
		opword 0xA07B0006
		opword 0x7FA0D214
		opword 0xA01D0000
		opword 0x5465063E
		opword 0x28000000
		opword 0x41820104
		opword 0xB0BD0006
		opword 0xA01D0000
		opword 0x54000739
		opword 0x418200F4
		opword 0xA01D001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01D0010
		opword 0x38E00000
		opword 0xA01D0008
		opword 0xFC00001E
		opword 0x807D004C
		opword 0x5406063E
		stfd f0, _af_pad+0(r1)
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0x480000C0
		opword 0xC07D0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A1000C
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010008
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC2100F2
		fdivs f31, f1, f0
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x90610014
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010010
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210010
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01D0008
		opword 0x807D004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010018
		opword 0x8081001C
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01D0008
		opword 0x807D00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0xA07B0000
		opword 0x546006B5
		opword 0x41820218
		lfs f2, float_0_8041b6d8(r2)
		opword 0xC03B0010
		opword 0xFC020800
		opword 0x408200CC
		opword 0x546006F2
		opword 0xB01B0000
		opword 0x801F0100
		opword 0x7FA0D214
		opword 0xA01D0000
		opword 0x28000000
		opword 0x41820350
		opword 0xA01F020C
		opword 0x28000000
		opword 0x4082000C
		bl OSDisableInterrupts
		opword 0x907F0210
		opword 0xA07F020C
		opword 0x38030001
		opword 0xB01F020C
		opword 0xA01D0000
		opword 0x5400056B
		opword 0x41820020
		opword 0xA09D0002
		lis r3, sound@ha
		addi r0, r3, sound@l
		opword 0x38A00000
		opword 0x5483083C
		opword 0x7C601A14
		opword 0xB0A30226
		opword 0x38000000
		opword 0xB01D0000
		opword 0x807D0028
		bl DVDMgrClose
		opword 0x807D00B0
		bl DVDMgrClose
		opword 0x807D004C
		bl sndStreamFree
		opword 0xA01D001A
		opword 0x28000002
		opword 0x4082000C
		opword 0x807D00D4
		bl sndStreamFree
		opword 0xA07F020C
		opword 0x28030000
		opword 0x4182001C
		opword 0x3863FFFF
		opword 0x5460043F
		opword 0xB07F020C
		opword 0x4082000C
		opword 0x807F0210
		bl OSRestoreInterrupts
		opword 0x3800FFFF
		opword 0x901F0104
		opword 0x480002A4
		opword 0xC01B0014
		opword 0xEC010028
		opword 0xD01B0010
		opword 0xC01B0010
		opword 0xFC001040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD05B0010
		opword 0x801F0100
		opword 0xA07B0006
		opword 0x7FA0D214
		opword 0xA01D0000
		opword 0x5465063E
		opword 0x28000000
		opword 0x41820104
		opword 0xB0BD0006
		opword 0xA01D0000
		opword 0x54000739
		opword 0x418200F4
		opword 0xA01D001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01D0010
		opword 0x38E00000
		opword 0xA01D0008
		opword 0xFC00001E
		opword 0x807D004C
		opword 0x5406063E
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0x480000C0
		opword 0xC07D0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A10024
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010020
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x9061001C
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010018
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210018
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01D0008
		opword 0x807D004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010010
		opword 0x80810014
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01D0008
		opword 0x807D00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010008
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0xA01B0000
		opword 0x540006F7
		opword 0x4182015C
		opword 0xC03B0010
		opword 0xC01B0014
		opword 0xEC01002A
		opword 0xD01B0010
		opword 0xC01B0010
		opword 0xC03B000C
		opword 0xFC000840
		opword 0x4C411382
		opword 0x4082001C
		opword 0xD03B0010
		lfs f0, float_0_8041b6d8(r2)
		opword 0xD01B0014
		opword 0xA01B0000
		opword 0x54000734
		opword 0xB01B0000
		opword 0x801F0100
		opword 0xA07B0006
		opword 0x7FA0D214
		opword 0xA01D0000
		opword 0x5465063E
		opword 0x28000000
		opword 0x41820104
		opword 0xB0BD0006
		opword 0xA01D0000
		opword 0x54000739
		opword 0x418200F4
		opword 0xA01D001A
		opword 0x28000001
		opword 0x4082002C
		opword 0xC01D0010
		opword 0x38E00000
		opword 0xA01D0008
		opword 0xFC00001E
		opword 0x807D004C
		opword 0x5406063E
		opword 0xD8010020
		opword 0x80810024
		bl sndStreamMixParameter
		opword 0x480000C0
		opword 0xC07D0010
		opword 0x28050040
		opword 0xFFE01890
		opword 0x4080002C
		opword 0x3C004330
		lis r3, double_to_int_mask_802e5718@ha
		opword 0x90A10024
		lfd f2, double_to_int_mask_802e5718@l(r3)
		opword 0x90010020
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEFE10024
		opword 0x3805FFC0
		opword 0x54000FFF
		opword 0x40820034
		opword 0x2065007F
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802e5720@ha
		opword 0x9061001C
		lfd f2, double_to_int_802e5720@l(r4)
		opword 0x90010018
		lfs f0, float_63_8041b6dc(r2)
		opword 0xC8210018
		opword 0xEC211028
		opword 0xEC2100F2
		opword 0xEC610024
		opword 0xFC00181E
		opword 0xA01D0008
		opword 0x807D004C
		opword 0x38A00000
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010010
		opword 0x80810014
		bl sndStreamMixParameter
		opword 0xFC00F81E
		opword 0xA01D0008
		opword 0x807D00D4
		opword 0x38A0007F
		opword 0x5406063E
		opword 0x38E00000
		opword 0xD8010008
		opword 0x8081000C
		bl sndStreamMixParameter
		opword 0x3B9C0001
		opword 0x3B5A0138
		opword 0x2C1C0003
		opword 0x3BDE0138
		opword 0x4180FA14
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    for (i = 0; (int)i < 3; i++) {
        stream = (0, &sound.streams[i]);
        if ((stream->flags & 8) && !(stream->flags & 2)) {
            if (stream->flags & 4) {
                stream->flags &= ~4;
                SoundSSStopCh(i);
                continue;
            }
            if (stream->flags & 0x40) {
                if (stream->curVol == 0.0f) {
                    stream->flags |= 2;
                    stream->flags &= ~0x40;
                    continue;
                }
                stream->curVol -= stream->fadeStep;
                if (stream->curVol <= 0.0f) {
                    stream->curVol = 0.0f;
                }
                SoundSSSetPanCh(i, stream->pan);
            }
            if (stream->flags & 0x20) {
                if (stream->curVol == 0.0f) {
                    stream->flags &= ~0x20;
                    SoundSSStopCh(i);
                    continue;
                }
                stream->curVol -= stream->fadeStep;
                if (stream->curVol <= 0.0f) {
                    stream->curVol = 0.0f;
                }
                SoundSSSetPanCh(i, stream->pan);
            }
            if (stream->flags & 0x10) {
                stream->curVol += stream->fadeStep;
                if (stream->curVol >= stream->vol) {
                    stream->curVol = stream->vol;
                    stream->fadeStep = 0.0f;
                    stream->flags &= ~0x10;
                }
                SoundSSSetPanCh(i, stream->pan);
            }
        }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void SoundSSMainInt(void) {
	asm {
		lis r3, sound@ha
	}
	asm volatile {
		opword 0x3BE00000
		addi r29, r3, sound@l
		opword 0x3B200000
		opword 0x801D0100
		opword 0x7FC0CA14
		opword 0xA01E0000
		opword 0x54030739
		opword 0x41820350
		opword 0x540307BD
		opword 0x40820348
		opword 0x540307FF
		opword 0x41820340
		opword 0x807E006C
		opword 0x28030000
		opword 0x41820184
		opword 0xA87E007C
		opword 0x2C030000
		opword 0x40820178
		opword 0x540304E7
		opword 0x40820170
		opword 0x3B9E0028
		opword 0x3C800001
		opword 0x80DE005C
		opword 0x3B448000
		opword 0x80FE0088
		opword 0x3C660001
		opword 0x38638000
		opword 0x7C033840
		opword 0x4081000C
		opword 0x7F463850
		opword 0x48000060
		opword 0x38600004
		opword 0x38A00002
		opword 0x7C6903A6
		opword 0x7C662214
		opword 0x7C033840
		opword 0x40810038
		opword 0x3885FFFF
		opword 0x3C600001
		opword 0x54847820
		opword 0x7C862214
		opword 0x38638000
		opword 0x7C843850
		opword 0x7C641850
		opword 0x7C632B96
		opword 0x7F43D050
		opword 0x574306FE
		opword 0x20630020
		opword 0x7F5A1A14
		opword 0x48000014
		opword 0x3C840001
		opword 0x38A50001
		opword 0x38848000
		opword 0x4200FFB4
		opword 0x5400056B
		opword 0x387A001F
		opword 0x547B0034
		opword 0x40820038
		opword 0xA09C004C
		lis r3, _ssDVDReadAsync_activeChk@ha
		opword 0xA01E0004
		addi r7, r3, _ssDVDReadAsync_activeChk@l
		opword 0x20840001
		opword 0x807C0000
		opword 0x5484103A
		opword 0x7F65DB78
		opword 0x3884002C
		opword 0x7CC03214
		opword 0x7C9C202E
		bl DVDMgrReadAsync
		opword 0x48000080
		opword 0xA0BE0002
		lis r3, sound@ha
		opword 0xA01C004C
		opword 0x3C800001
		opword 0x54A5103A
		addi r3, r3, sound@l
		opword 0x7CA32A14
		opword 0x20000001
		opword 0x5403103A
		opword 0x80E5021C
		opword 0x3803002C
		opword 0xA0BE0004
		add r24, r6, r7
		opword 0x7C7C002E
		opword 0x7F05C214
		opword 0x38848000
		bl DCInvalidateRange
		opword 0xA01C004C
		lis r3, cache_flush@ha
		addi r10, r3, cache_flush@l
		opword 0x7F84E378
		opword 0x20000001
		opword 0x7F07C378
		opword 0x5403103A
		opword 0x7F69DB78
		opword 0x3803002C
		opword 0x38A00001
		opword 0x7D1C002E
		opword 0x387C0004
		opword 0x38C00000
		bl ARQPostRequest
		opword 0x935C0048
		opword 0xA01E0000
		opword 0x60001000
		opword 0xB01E0000
		opword 0xA01E0000
		opword 0x5400056B
		opword 0x4182000C
		opword 0x38000001
		opword 0xB01E007C
		opword 0xA01E001A
		opword 0x28000002
		opword 0x408201A8
		opword 0x801E00F4
		opword 0x28000000
		opword 0x4182019C
		opword 0xA81E0104
		opword 0x2C000000
		opword 0x40820190
		opword 0xA09E0000
		opword 0x548004A5
		opword 0x40820184
		opword 0x3B9E00B0
		opword 0x3CC00001
		opword 0x807E00E4
		opword 0x3B668000
		opword 0x811E0110
		opword 0x3CA30001
		opword 0x38058000
		opword 0x550506FE
		opword 0x7C004040
		opword 0x20050020
		opword 0x7C080214
		opword 0x4081000C
		opword 0x7F634050
		opword 0x48000060
		opword 0x38A00004
		opword 0x38E00002
		opword 0x7CA903A6
		opword 0x7CA33214
		opword 0x7C054040
		opword 0x40810038
		opword 0x38C7FFFF
		opword 0x3CA00001
		opword 0x54C67820
		opword 0x7CC33214
		opword 0x38A58000
		opword 0x7CC64050
		opword 0x7CA62850
		opword 0x7CA53B96
		opword 0x7F65D850
		opword 0x576506FE
		opword 0x20A50020
		opword 0x7F7B2A14
		opword 0x48000014
		opword 0x3CC60001
		opword 0x38E70001
		opword 0x38C68000
		opword 0x4200FFB4
		opword 0x5484056B
		opword 0x38BB001F
		opword 0x54BA0034
		opword 0x4082003C
		opword 0xA0BC004C
		lis r4, _ssDVDReadAsync_activeChk@ha
		addi r7, r4, _ssDVDReadAsync_activeChk@l
		opword 0x7CC30214
		opword 0x20850001
		opword 0xA11E0004
		opword 0x5484103A
		opword 0x807C0000
		opword 0x3804002C
		opword 0x7F45D378
		opword 0x7C9C002E
		opword 0x7CC83214
		bl DVDMgrReadAsync
		opword 0x48000084
		opword 0xA0FE0002
		lis r6, sound@ha
		opword 0xA0BC004C
		opword 0x3C800001
		opword 0x54E7103A
		addi r6, r6, sound@l
		opword 0x7CC63A14
		opword 0x20A50001
		opword 0x54A5103A
		opword 0x80E6021C
		opword 0x7C630214
		opword 0xA0DE0004
		opword 0x3805002C
		opword 0x38848000
		opword 0x7F033A14
		opword 0x7C7C002E
		opword 0x7F06C214
		bl DCInvalidateRange
		opword 0xA01C004C
		lis r3, cache_flush@ha
		addi r10, r3, cache_flush@l
		opword 0x7F84E378
		opword 0x20000001
		opword 0x7F07C378
		opword 0x5403103A
		opword 0x7F49D378
		opword 0x3803002C
		opword 0x38A00001
		opword 0x7D1C002E
		opword 0x387C0004
		opword 0x38C00000
		bl ARQPostRequest
		opword 0x937C0048
		opword 0xA01E0000
		opword 0x60002000
		opword 0xB01E0000
		opword 0xA01E0000
		opword 0x5400056B
		opword 0x4182000C
		opword 0x38000001
		opword 0xB01E0104
		opword 0x3BFF0001
		opword 0x3B390138
		opword 0x2C1F0003
		opword 0x4180FC94
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
void SoundSSMainInt(void) {
    int i;
    SoundStream* stream;

    for (i = 0; i < 3; i++) {
        stream = &sound.streams[i];
        if ((stream->flags & 8) && !(stream->flags & 2) && (stream->flags & 1)) {
            if (stream->entries[0].srcPos != 0 && stream->entries[0].loaded == 0 && !(stream->flags & 0x1000)) {
                _ssDVDReadAsync(stream, 0);
                stream->flags |= 0x1000;
                if (stream->flags & 0x400) {
                    stream->entries[0].loaded = 1;
                }
            }
            if (stream->count == 2 && stream->entries[1].srcPos != 0 && stream->entries[1].loaded == 0 &&
                !(stream->flags & 0x2000)) {
                _ssDVDReadAsync(stream, 1);
                stream->flags |= 0x2000;
                if (stream->flags & 0x400) {
                    stream->entries[1].loaded = 1;
                }
            }
        }
    }
}

#endif
#ifndef NONMATCHING
#pragma defer_codegen off
#endif
void SoundAIDMACallback(void) {
    s32 length;
    u8* address;
    u16* dst;
    s16* src;
    s32 n;
    s16* out;

    sound.callback();
    sound.dmaAddress = (u8*)(AIGetDMAStartAddr() | 0x80000000);
    sound.dmaLength = length = AIGetDMALength();
    address = sound.dmaAddress;
    src = (s16*)sound.dmaBuf;
    dst = (u16*)src;
    while (length != 0) {
        *dst++ = (address[0] << 8) | address[1];
        address += 2;
        length -= 2;
    }
    n = sound.dmaLength >> 1;
    out = sound.samples[sound.sampleBank];
    out += sound.sampleIndex;
    while (n != 0) {
        *out++ = *src;
        src += 2;
        if (++sound.sampleIndex >= 0x400) {
            sound.sampleIndex = 0;
            sound.sampleBank = 1 - sound.sampleBank;
            out = sound.samples[sound.sampleBank];
        }
        n -= 2;
    }
}

#ifndef NONMATCHING
#pragma defer_codegen reset
#endif

#ifdef NONMATCHING
// target pad words (G5: section sizes must match or later DOL addresses shift)
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm void SoundInit(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r3, jumptable_802E5710@ha
	lis r6, g5_str_s436@ha
	stw r0, 0x34(r1)
	addi r4, r3, jumptable_802E5710@l
	la r3, aramMemArray(r13)
	stw r31, 0x2c(r1)
	addi r31, r6, g5_str_s436@l
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	stw r28, 0x20(r1)
	lwz r5, 0x0(r4)
	lwz r0, 0x4(r4)
	li r4, 0x8
	stw r5, 0x10(r1)
	stw r0, 0x14(r1)
	bl ARInit
	bl ARQInit
	li r3, 0x0
	bl AIInit
	lis r3, 0xc0
	subi r3, r3, 0x4000
	bl ARAlloc
	addi r3, r1, 0x10
	bl sndSetHooks
	lis r4, 0xc0
	li r3, 0x40
	subi r8, r4, 0x4000
	li r4, 0xc
	li r5, 0x2c
	li r6, 0x1
	li r7, 0x1
	bl sndInit
	lfs f4, float_3_8041b734(r2)
	addi r3, r31, 0x1914
	lfs f1, float_0_8041b6d8(r2)
	li r0, 0x0
	lfs f3, float_0p1_8041b738(r2)
	lfs f2, float_0p3_8041b73c(r2)
	lfs f0, float_0p8_8041b740(r2)
	stb r0, 0x1c4(r3)
	stfs f4, 0x1d0(r3)
	stfs f3, 0x1d8(r3)
	stfs f2, 0x1d4(r3)
	stfs f1, 0x1c8(r3)
	stfs f1, 0x1dc(r3)
	stfs f0, 0x1cc(r3)
	bl sndAuxCallbackPrepareReverbHI
	lfs f2, float_2_8041b744(r2)
	addi r3, r31, 0x17c0
	lfs f0, float_0p5_8041b748(r2)
	li r0, 0x0
	lfs f1, float_0p1_8041b738(r2)
	stb r0, 0x13c(r3)
	stfs f2, 0x148(r3)
	stfs f1, 0x150(r3)
	stfs f0, 0x14c(r3)
	stfs f0, 0x140(r3)
	stfs f0, 0x144(r3)
	bl sndAuxCallbackPrepareReverbSTD
	addi r3, r31, 0x1724
	li r5, 0xa
	li r4, 0x0
	li r0, 0x1f4
	stw r5, 0x90(r3)
	stw r4, 0x94(r3)
	stw r0, 0x98(r3)
	bl sndAuxCallbackPrepareChorus
	addi r3, r31, 0x16c4
	li r4, 0x14
	li r0, 0x32
	li r7, 0x3c
	li r6, 0x5a
	li r5, 0x46
	stw r7, 0x3c(r3)
	stw r6, 0x40(r3)
	stw r5, 0x44(r3)
	stw r4, 0x48(r3)
	stw r4, 0x4c(r3)
	stw r4, 0x50(r3)
	stw r0, 0x54(r3)
	stw r0, 0x58(r3)
	stw r0, 0x5c(r3)
	bl sndAuxCallbackPrepareDelay
	li r0, 0x0
	lis r4, sndAuxCallbackReverbHI@ha
	lis r3, sndAuxCallbackChorus@ha
	stw r0, 0x8(r1)
	addi r8, r3, sndAuxCallbackChorus@l
	addi r4, r4, sndAuxCallbackReverbHI@l
	addi r5, r31, 0x1914
	addi r9, r31, 0x1724
	li r3, 0x0
	li r6, 0xff
	li r7, 0x0
	li r10, 0xff
	bl sndSetAuxProcessingCallbacks
	li r3, 0x7f
	li r4, 0x0
	li r5, 0xff
	bl sndVolume
	addi r4, r31, 0x100
	lwz r0, 0x218(r4)
	cmpwi r0, 0x1
	beq L_af_1
	li r0, 0x1
	li r3, 0x1
	stw r0, 0x218(r4)
	bl sndOutputMode
L_af_1:
	lis r3, SoundAIDMACallback@ha
	addi r3, r3, SoundAIDMACallback@l
	bl AIRegisterDMACallback
	addi r7, r31, 0x100
	li r6, 0x0
	li r5, 0xa
	li r0, 0x1f4
	stw r3, 0x5bc(r7)
	li r3, 0x0
	lis r4, 0x2
	sth r6, 0x330(r7)
	stw r6, 0x15c0(r7)
	sth r5, 0x208(r7)
	sth r0, 0x20a(r7)
	stw r6, 0xe0(r7)
	stw r6, 0xe4(r7)
	sth r6, 0x214(r7)
	sth r6, 0x224(r7)
	stw r6, 0xe8(r7)
	bl __memAlloc
	addi r4, r31, 0x100
	cmplwi r3, 0x0
	stw r3, 0x32c(r4)
	bne L_af_2
L_af_3:
	b L_af_3
L_af_2:
	li r0, 0x0
	li r3, 0x0
	stw r0, 0xec(r4)
	li r4, 0x40
	bl __memAlloc
	mr. r6, r3
	addi r4, r31, 0x100
	stw r6, 0xf0(r4)
	bne L_af_4
L_af_5:
	b L_af_5
L_af_4:
	li r5, -0x1
	li r0, 0x0
	stw r5, 0x0(r6)
	li r3, 0x0
	li r4, 0x1540
	stw r0, 0x8(r6)
	stw r5, 0x10(r6)
	stw r0, 0x18(r6)
	stw r5, 0x20(r6)
	stw r0, 0x28(r6)
	stw r5, 0x30(r6)
	stw r0, 0x38(r6)
	bl __memAlloc
	addi r4, r31, 0x100
	cmplwi r3, 0x0
	stw r3, 0xf4(r4)
	bne L_af_6
L_af_7:
	b L_af_7
L_af_6:
	li r0, 0x4
	li r7, 0x0
	li r6, -0x1
	li r5, 0x7f
	li r4, 0x40
	mtctr r0
L_af_8:
	sth r7, 0x0(r3)
	stw r6, 0xc(r3)
	sth r7, 0x2(r3)
	sth r5, 0x4(r3)
	sth r4, 0x6(r3)
	sth r7, 0x88(r3)
	stw r6, 0x94(r3)
	sth r7, 0x8a(r3)
	sth r5, 0x8c(r3)
	sth r4, 0x8e(r3)
	sth r7, 0x110(r3)
	stw r6, 0x11c(r3)
	sth r7, 0x112(r3)
	sth r5, 0x114(r3)
	sth r4, 0x116(r3)
	sth r7, 0x198(r3)
	stw r6, 0x1a4(r3)
	sth r7, 0x19a(r3)
	sth r5, 0x19c(r3)
	sth r4, 0x19e(r3)
	sth r7, 0x220(r3)
	stw r6, 0x22c(r3)
	sth r7, 0x222(r3)
	sth r5, 0x224(r3)
	sth r4, 0x226(r3)
	sth r7, 0x2a8(r3)
	stw r6, 0x2b4(r3)
	sth r7, 0x2aa(r3)
	sth r5, 0x2ac(r3)
	sth r4, 0x2ae(r3)
	sth r7, 0x330(r3)
	stw r6, 0x33c(r3)
	sth r7, 0x332(r3)
	sth r5, 0x334(r3)
	sth r4, 0x336(r3)
	sth r7, 0x3b8(r3)
	stw r6, 0x3c4(r3)
	sth r7, 0x3ba(r3)
	sth r5, 0x3bc(r3)
	sth r4, 0x3be(r3)
	sth r7, 0x440(r3)
	stw r6, 0x44c(r3)
	sth r7, 0x442(r3)
	sth r5, 0x444(r3)
	sth r4, 0x446(r3)
	sth r7, 0x4c8(r3)
	stw r6, 0x4d4(r3)
	sth r7, 0x4ca(r3)
	sth r5, 0x4cc(r3)
	sth r4, 0x4ce(r3)
	addi r3, r3, 0x550
	bdnz L_af_8
	li r3, 0x0
	li r4, 0x2a8
	bl __memAlloc
	mr. r5, r3
	addi r4, r31, 0x100
	stw r5, 0xf8(r4)
	bne L_af_9
L_af_10:
	b L_af_10
L_af_9:
	li r0, 0x0
	li r3, 0x0
	sth r0, 0x0(r5)
	li r4, 0x3a8
	sth r0, 0x154(r5)
	bl __memAlloc
	addi r4, r31, 0x100
	cmplwi r3, 0x0
	stw r3, 0x100(r4)
	bne L_af_11
L_af_12:
	b L_af_12
L_af_11:
	mr r28, r3
	li r29, 0x0
	lis r30, 0x1
L_af_13:
	li r0, 0x0
	addi r4, r30, -0x8000
	sth r0, 0x0(r28)
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_af_14
L_af_15:
	b L_af_15
L_af_14:
	stw r3, 0x54(r28)
	addi r4, r30, -0x8000
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_af_16
L_af_17:
	b L_af_17
L_af_16:
	stw r3, 0x58(r28)
	li r3, 0xe00
	li r4, 0x0
	bl sndStreamAllocLength
	mr r0, r3
	li r3, 0x0
	mr r4, r0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_af_18
L_af_19:
	b L_af_19
L_af_18:
	stw r3, 0x50(r28)
	addi r4, r30, -0x8000
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_af_20
L_af_21:
	b L_af_21
L_af_20:
	stw r3, 0xdc(r28)
	addi r4, r30, -0x8000
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_af_22
L_af_23:
	b L_af_23
L_af_22:
	stw r3, 0xe0(r28)
	li r3, 0xe00
	li r4, 0x0
	bl sndStreamAllocLength
	mr r4, r3
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_af_24
L_af_25:
	b L_af_25
L_af_24:
	addi r29, r29, 0x1
	stw r3, 0xd8(r28)
	cmpwi r29, 0x3
	addi r28, r28, 0x138
	blt L_af_13
	lis r6, sndAuxCallbackReverbHI@ha
	lis r3, sndAuxCallbackChorus@ha
	addi r8, r31, 0x100
	li r5, 0xff
	li r4, 0x0
	addi r7, r6, sndAuxCallbackReverbHI@l
	addi r6, r31, 0x1914
	addi r3, r3, sndAuxCallbackChorus@l
	addi r0, r31, 0x1724
	stw r7, 0x108(r8)
	stw r6, 0x10c(r8)
	stb r5, 0x110(r8)
	stw r4, 0x114(r8)
	stw r3, 0x118(r8)
	stw r0, 0x11c(r8)
	stb r5, 0x120(r8)
	stw r4, 0x124(r8)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r28, 0x20(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

void* sndMalloc(size_t size) {
    return __memAlloc(HEAP_DEFAULT, size);
}

void sndFree(void* ptr) {
    __memFree(HEAP_DEFAULT, ptr);
}


// literal pool in target order (asmfake --minimal)
#endif
#pragma force_active on
#ifndef NONMATCHING
__declspec(section ".rodata") const u32 jumptable_802E5710[2] = {(u32)(char*)&sndMalloc, (u32)(char*)&sndFree};
__declspec(section ".rodata") const f64 double_to_int_mask_802e5718 = 4503599627370496.0;
__declspec(section ".rodata") const f64 double_to_int_802e5720 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802E5728[] = "%s/%s%s";
__declspec(section ".sdata2") const f32 float_0_8041b6d8 = 0.0f;
__declspec(section ".sdata2") const f32 float_63_8041b6dc = 63.0f;
__declspec(section ".sdata2") const f32 float_16p667_8041b6e0 = 16.666666f;
__declspec(section ".sdata2") const f32 float_1_8041b6e4 = 1.0f;
__declspec(section ".sdata2") const f32 float_127_8041b6e8 = 127.0f;
__declspec(section ".sdata2") const char str_8041B6EC[] = ".stm\0\0\0";
__declspec(section ".sdata2") const f32 float_6p2832_8041b6f4 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041b6f8 = 360.0f;
__declspec(section ".sdata2") const char str_8041B6FC[] = ".slib\0\0";
__declspec(section ".sdata2") const char str_8041B704[] = ".stbl\0\0";
__declspec(section ".sdata2") const char str_8041B70C[] = ".etbl\0\0";
__declspec(section ".sdata2") const char str_8041B714[] = ".pool\0\0";
__declspec(section ".sdata2") const char str_8041B71C[] = ".proj\0\0";
__declspec(section ".sdata2") const char str_8041B724[] = ".sdir\0\0";
__declspec(section ".sdata2") const char str_8041B72C[] = ".samp\0\0";
__declspec(section ".sdata2") const f32 float_3_8041b734 = 3.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041b738 = 0.1f;
__declspec(section ".sdata2") const f32 float_0p3_8041b73c = 0.3f;
__declspec(section ".sdata2") const f32 float_0p8_8041b740 = 0.8f;
__declspec(section ".sdata2") const f32 float_2_8041b744 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041b748 = 0.5f;
#endif
__declspec(section ".sdata2") const u32 gap_09_8041B74C_sdata2[1] = {0};

#ifndef NONMATCHING
SND_AUX_REVERBHI revH;
SND_AUX_REVERBSTD revS;
SND_AUX_CHORUS cho;
SND_AUX_DELAY dly;
SoundWork sound;
__declspec(section ".data") u8 g5_str_s436[256];
#endif
