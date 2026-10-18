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
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
__declspec(section ".sdata") u32 gap_08_80418924_sbss[1];
__declspec(section ".data") u32 gap_06_803DB7AC_bss[1];

// TODO: use SoundInit to fill in SoundStream/Entry

extern int sprintf(char* str, const char* format, ...);

//.bss
SND_AUX_REVERBHI revH;
SND_AUX_REVERBSTD revS;
SND_AUX_CHORUS cho;
SND_AUX_DELAY dly;
SoundWork sound;

//.sbss
u32 aramMemArray[8];

#ifdef NONMATCHING  // G5: its static local would be emitted as a stray .bss object
static inline char* _ssGetStr(void) {
    static char str[0x100];
    return str;
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
}
#endif

#ifdef NONMATCHING
void sndFree(void* ptr) {
    __memFree(HEAP_DEFAULT, ptr);
}
#endif

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
    }
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
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void SoundMainInt(void) {
    SoundSSMainInt();
}
#endif

#ifdef NONMATCHING
void SoundSetFadeTime(u16 in, u16 out) { // 1:1
    sound.fadeIn = in;
    sound.fadeOut = out;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
BOOL SoundLoadDVD2(const char* path) { // 1:1
    DVDEntry* entry;
    u32 length;
    void* pointer;

    if (sound.dataId >= 8) {
        return 0;
    }

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".pool");
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

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".proj");
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

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".sdir");
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

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".samp");
    strcpy(sound.filepath, str);
    sndSetSampleDataUploadCallback(loadDVD_callback, 0x20000);
    return TRUE;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void SoundLoadDVD2Free(void) {
    if (sound.filedata) {
        __memFree(HEAP_DEFAULT, sound.filedata);
        sound.filedata = NULL;
    }
}
#endif

#ifdef NONMATCHING
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

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".slib");
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

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".stbl");
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

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".etbl");
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
}
#endif

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
}

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void SoundSetOutputMode(SND_OUTPUTMODE mode) {
    if (sound.outputMode != mode) {
        sound.outputMode = mode;
        sndOutputMode(mode);
    }
}
#endif

#ifdef NONMATCHING
void SoundOpenCover(void) {
    if (!sound.unk214) {
        sound.unk214 = 1;
    }
}
#endif

#ifdef NONMATCHING
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
#endif

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

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void SoundSongContinueCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqContinue(song->seqId);
        sndSeqVolume((u8)song->vol, 0, song->seqId, SND_SEQVOL_CONTINUE);
    }
}
#endif

#ifdef NONMATCHING
void SoundSongStopCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqStop(song->seqId);
        song->seqId = (SND_SEQID)-1;
    }
}
#endif

#ifdef NONMATCHING
void SoundSongFadeoutCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqVolume(0, sound.fadeOut, song->seqId, SND_SEQVOL_STOP);
        song->seqId = (SND_SEQID)-1;
    }
}
#endif

#ifdef NONMATCHING
void SoundSongFadeinCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId)) {
        sndSeqVolume((u8)song->vol, sound.fadeIn, song->seqId, SND_SEQVOL_CONTINUE);
    }
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
u8 SoundSongGetVolCh(s32 chan) {
    SoundSong* song = &sound.songs[chan];

    if (sndSeqGetValid(song->seqId) == 0) {
        return 0;
    }
    return (u8)song->vol;
}
#endif

#ifdef NONMATCHING
BOOL SoundSongCheck(s32 chan) {
    return sndSeqGetValid(sound.songs[chan].seqId) != 0;
}
#endif

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
}

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
u8 SoundEfxGetVolume(s32 chan) {
    s32 off = chan * sizeof(SoundEffect);
    return (u8)*(u16*)((u8*)sound.effects + off + 4);
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

inline void SoundEfxCheckCh(s32 chan) {
    SoundEffect* effect;
    SND_VOICEID vid;

    effect = &sound.effects[chan];
    if (effect->flags & 0x10) {
        vid = sndFXCheck(sndEmitterVoiceID(&effect->emitter));
    } else {
        vid = sndFXCheck(effect->voiceId);
    }
    if (sndFXCheck(vid) == -1) {
        SoundEfxMuteCh(chan);
    }
}

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
#endif

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

#ifdef NONMATCHING
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
#endif

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

#ifdef NONMATCHING
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

#ifdef NONMATCHING
void cache_flush(u32 pointerToARQRequest) {
    _ssDVDReadAsync_activeChk(0, &((SoundStreamEntry*)((ARQRequest*)pointerToARQRequest)->owner)->dvd->info);
}
#endif

#ifdef NONMATCHING
void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest) {
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
}
#endif

#ifdef NONMATCHING
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
#endif

s16 dtbl[16] = {0x0001, 0x0007, 0x0018, 0x003B, 0x0053, 0x006F, 0x00EC, 0x022B,
                0x02E6, 0x0375, 0x041C, 0x08AD, 0x0CD5, 0x1150, 0x1B32, 0x2454};

#ifdef NONMATCHING
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
#endif
#ifdef NONMATCHING
u32 _sscallback(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user) {
    s16* dst;
    SoundStream* stream;
    SoundStreamEntry* entry;
    s16* src16;
    u8* dst8;
    u8* src8;
    u32 i;
    u32 n;
    s32 j;

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
#endif

void SoundSSPlayChEx(s32 chan, const char* name, s32 aram);

#ifdef NONMATCHING
void SoundSSPlayCh(s32 chan, const char* name) {
    SoundSSPlayChEx(chan, name, 0);
}
#endif

#ifdef NONMATCHING
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
    stream->curVol = 0.0f;
    stream->vol = 127.0f;
    stream->flags = 1;
    if (aram) {
        stream->flags |= 0x400;
    }
    new_var2 [1] = getMarioStDvdRoot ();
    sprintf(str, "%s/%s%s", new_var2 [1], name, ".stm");
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
#endif

#ifdef NONMATCHING
void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo) {
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
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void SoundSSFadeoutCh(s32 chan) {
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
}
#endif

#ifdef NONMATCHING
void SoundSSContinueCh(s32 chan) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->flags &= ~2;
        stream->fadeStep = stream->vol;
        stream->flags |= 0x10;
    }
}
#endif

#ifdef NONMATCHING
void SoundSSSetPanCh(s32 chan, u8 pan) {
    SoundStream* stream = (0, &sound.streams[chan]);
    f32 left, right;

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
}
#endif

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

#ifdef NONMATCHING
s32 SoundSSGetVolCh(s32 chan) {
    SoundStream* stream;

    stream = &sound.streams[chan];
    if (stream->flags) {
        return (s32)stream->vol;
    } else {
        return 0;
    }
}
#endif

#ifdef NONMATCHING
void SoundSSSetSrndPanCh(s32 chan, u8 span) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->span = span;
        if (stream->flags & 8) {
            SoundSSSetPanCh(chan, stream->pan);
        }
    }
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
u16 SoundSSCheck(s32 chan) {
    return sound.streams[chan].flags;
}
#endif

#ifdef NONMATCHING
void SoundSSMuteOn(s32 chan) {
    if (sound.streams[chan].flags) {
        sound.streams[chan].flags |= 2;
    }
}
#endif

#ifdef NONMATCHING
void SoundSSMuteOff(s32 chan) {
    if (sound.streams[chan].flags) {
        sound.streams[chan].flags &= ~2;
    }
}
#endif

#ifdef NONMATCHING
void SoundSSMain(void) {
    u32 i;
    SoundStream* stream;

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
}
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

#ifdef NONMATCHING
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
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): sndMalloc (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const u32 jumptable_802E5710[2] = { (u32)&sndMalloc, (u32)&sndFree };
__declspec(section ".rodata") const f64 double_to_int_mask_802e5718 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802e5720 = 4503601774854144;
__declspec(section ".rodata") const char str_802E5728[] = "%s/%s%s";
#pragma force_active on
__declspec(section ".sdata2") const f32 float_0_8041b6d8 = 0.0f;
__declspec(section ".sdata2") const f32 float_63_8041b6dc = 63.0f;
__declspec(section ".sdata2") const f32 float_16p667_8041b6e0 = 16.666666f;
__declspec(section ".sdata2") const f32 float_1_8041b6e4 = 1.0f;
__declspec(section ".sdata2") const f32 float_127_8041b6e8 = 127.0f;
__declspec(section ".sdata2") const char str_8041B6EC[8] = ".stm\0\0\0";
__declspec(section ".sdata2") const f32 float_6p2832_8041b6f4 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041b6f8 = 360.0f;
__declspec(section ".sdata2") const char str_8041B6FC[8] = ".slib\0\0";
__declspec(section ".sdata2") const char str_8041B704[8] = ".stbl\0\0";
__declspec(section ".sdata2") const char str_8041B70C[8] = ".etbl\0\0";
__declspec(section ".sdata2") const char str_8041B714[8] = ".pool\0\0";
__declspec(section ".sdata2") const char str_8041B71C[8] = ".proj\0\0";
__declspec(section ".sdata2") const char str_8041B724[8] = ".sdir\0\0";
__declspec(section ".sdata2") const char str_8041B72C[8] = ".samp\0\0";
__declspec(section ".sdata2") const f32 float_3_8041b734 = 3.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041b738 = 0.1f;
__declspec(section ".sdata2") const f32 float_0p3_8041b73c = 0.3f;
__declspec(section ".sdata2") const f32 float_0p8_8041b740 = 0.8f;
__declspec(section ".sdata2") const f32 float_2_8041b744 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041b748 = 0.5f;

u8* ssDecodeDPCM(SoundStream* stream, SoundStreamEntry* entry, s16* out, u32 count, u8* src);
static u32 g5_str_s436[64];
static u32 g5_owner_no_s1419[1];
u32 _sscallback(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user);
asm void SoundAIDMACallback(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, (g5_str_s436+0x100)@ha
	stw r0, 0x14(r1)
	addi r3, r3, (g5_str_s436+0x100)@l
	stw r31, 0xc(r1)
	lwz r12, 0x5bc(r3)
	mtctr r12
	bctrl
	bl AIGetDMAStartAddr
	lis r4, sound@ha
	oris r0, r3, 0x8000
	addi r31, r4, sound@l
	stw r0, 0x334(r31)
	bl AIGetDMALength
	lis r4, sound@ha
	lwz r6, 0x334(r31)
	addi r5, r4, sound@l
	addi r8, r5, 0x33c
	stw r3, 0x338(r5)
	mr r7, r8
	b L_g5_1
	L_g5_2:
	lbz r4, 0x0(r6)
	subi r3, r3, 0x2
	lbz r0, 0x1(r6)
	addi r6, r6, 0x2
	rlwimi r0, r4, 8, 16, 23
	sth r0, 0x0(r7)
	addi r7, r7, 0x2
	L_g5_1:
	cmpwi r3, 0x0
	bne L_g5_2
	lis r3, sound@ha
	lwz r0, 0x338(r5)
	addi r5, r3, sound@l
	li r4, 0x0
	lhz r3, 0x330(r5)
	srwi r6, r0, 1
	lwz r0, 0x15c0(r5)
	slwi r3, r3, 11
	add r3, r5, r3
	slwi r0, r0, 1
	addi r7, r3, 0x5c0
	add r7, r7, r0
	b L_g5_3
	L_g5_4:
	lha r0, 0x0(r8)
	addi r8, r8, 0x4
	sth r0, 0x0(r7)
	addi r7, r7, 0x2
	lwz r3, 0x15c0(r5)
	addi r0, r3, 0x1
	cmplwi r0, 0x400
	stw r0, 0x15c0(r5)
	blt L_g5_5
	lhz r0, 0x330(r5)
	stw r4, 0x15c0(r5)
	subfic r3, r0, 0x1
	clrlslwi r0, r3, 16, 11
	sth r3, 0x330(r5)
	add r3, r5, r0
	addi r7, r3, 0x5c0
	L_g5_5:
	subi r6, r6, 0x2
	L_g5_3:
	cmpwi r6, 0x0
	bne L_g5_4
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSSMainInt(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r3, sound@ha
	stw r0, 0x34(r1)
	stmw r24, 0x10(r1)
	li r31, 0x0
	addi r29, r3, sound@l
	li r25, 0x0
	L_g5_1:
	lwz r0, 0x100(r29)
	add r30, r0, r25
	lhz r0, 0x0(r30)
	rlwinm. r3, r0, 0, 28, 28
	beq L_g5_2
	rlwinm. r3, r0, 0, 30, 30
	bne L_g5_2
	clrlwi. r3, r0, 31
	beq L_g5_2
	lwz r3, 0x6c(r30)
	cmplwi r3, 0x0
	beq L_g5_3
	lha r3, 0x7c(r30)
	cmpwi r3, 0x0
	bne L_g5_3
	rlwinm. r3, r0, 0, 19, 19
	bne L_g5_3
	addi r28, r30, 0x28
	lis r4, 0x1
	lwz r6, 0x5c(r30)
	addi r26, r4, -0x8000
	lwz r7, 0x88(r30)
	addis r3, r6, 0x1
	addi r3, r3, -0x8000
	cmplw r3, r7
	ble L_g5_4
	subf r26, r6, r7
	b L_g5_5
	L_g5_4:
	li r3, 0x4
	li r5, 0x2
	mtctr r3
	L_g5_6:
	add r3, r6, r4
	cmplw r3, r7
	ble L_g5_7
	subi r4, r5, 0x1
	lis r3, 0x1
	slwi r4, r4, 15
	add r4, r6, r4
	addi r3, r3, -0x8000
	subf r4, r4, r7
	subf r3, r4, r3
	divwu r3, r3, r5
	subf r26, r3, r26
	clrlwi r3, r26, 27
	subfic r3, r3, 0x20
	add r26, r26, r3
	b L_g5_5
	L_g5_7:
	addis r4, r4, 0x1
	addi r5, r5, 0x1
	addi r4, r4, -0x8000
	bdnz L_g5_6
	L_g5_5:
	rlwinm. r0, r0, 0, 21, 21
	addi r3, r26, 0x1f
	clrrwi r27, r3, 5
	bne L_g5_8
	lhz r4, 0x4c(r28)
	lis r3, _ssDVDReadAsync_activeChk@ha
	lhz r0, 0x4(r30)
	addi r7, r3, _ssDVDReadAsync_activeChk@l
	subfic r4, r4, 0x1
	lwz r3, 0x0(r28)
	slwi r4, r4, 2
	mr r5, r27
	addi r4, r4, 0x2c
	add r6, r0, r6
	lwzx r4, r28, r4
	bl DVDMgrReadAsync
	b L_g5_9
	L_g5_8:
	lhz r5, 0x2(r30)
	lis r3, sound@ha
	lhz r0, 0x4c(r28)
	lis r4, 0x1
	slwi r5, r5, 2
	addi r3, r3, sound@l
	add r5, r3, r5
	subfic r0, r0, 0x1
	slwi r3, r0, 2
	lwz r7, 0x21c(r5)
	addi r0, r3, 0x2c
	lhz r5, 0x4(r30)
	add r24, r6, r7
	lwzx r3, r28, r0
	add r24, r5, r24
	addi r4, r4, -0x8000
	bl DCInvalidateRange
	lhz r0, 0x4c(r28)
	lis r3, cache_flush@ha
	addi r10, r3, cache_flush@l
	mr r4, r28
	subfic r0, r0, 0x1
	mr r7, r24
	slwi r3, r0, 2
	mr r9, r27
	addi r0, r3, 0x2c
	li r5, 0x1
	lwzx r8, r28, r0
	addi r3, r28, 0x4
	li r6, 0x0
	bl ARQPostRequest
	L_g5_9:
	stw r26, 0x48(r28)
	lhz r0, 0x0(r30)
	ori r0, r0, 0x1000
	sth r0, 0x0(r30)
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_3
	li r0, 0x1
	sth r0, 0x7c(r30)
	L_g5_3:
	lhz r0, 0x1a(r30)
	cmplwi r0, 0x2
	bne L_g5_2
	lwz r0, 0xf4(r30)
	cmplwi r0, 0x0
	beq L_g5_2
	lha r0, 0x104(r30)
	cmpwi r0, 0x0
	bne L_g5_2
	lhz r4, 0x0(r30)
	rlwinm. r0, r4, 0, 18, 18
	bne L_g5_2
	addi r28, r30, 0xb0
	lis r6, 0x1
	lwz r3, 0xe4(r30)
	addi r27, r6, -0x8000
	lwz r8, 0x110(r30)
	addis r5, r3, 0x1
	addi r0, r5, -0x8000
	clrlwi r5, r8, 27
	cmplw r0, r8
	subfic r0, r5, 0x20
	add r0, r8, r0
	ble L_g5_10
	subf r27, r3, r8
	b L_g5_11
	L_g5_10:
	li r5, 0x4
	li r7, 0x2
	mtctr r5
	L_g5_12:
	add r5, r3, r6
	cmplw r5, r8
	ble L_g5_13
	subi r6, r7, 0x1
	lis r5, 0x1
	slwi r6, r6, 15
	add r6, r3, r6
	addi r5, r5, -0x8000
	subf r6, r6, r8
	subf r5, r6, r5
	divwu r5, r5, r7
	subf r27, r5, r27
	clrlwi r5, r27, 27
	subfic r5, r5, 0x20
	add r27, r27, r5
	b L_g5_11
	L_g5_13:
	addis r6, r6, 0x1
	addi r7, r7, 0x1
	addi r6, r6, -0x8000
	bdnz L_g5_12
	L_g5_11:
	rlwinm. r4, r4, 0, 21, 21
	addi r5, r27, 0x1f
	clrrwi r26, r5, 5
	bne L_g5_14
	lhz r5, 0x4c(r28)
	lis r4, _ssDVDReadAsync_activeChk@ha
	addi r7, r4, _ssDVDReadAsync_activeChk@l
	add r6, r3, r0
	subfic r4, r5, 0x1
	lhz r8, 0x4(r30)
	slwi r4, r4, 2
	lwz r3, 0x0(r28)
	addi r0, r4, 0x2c
	mr r5, r26
	lwzx r4, r28, r0
	add r6, r8, r6
	bl DVDMgrReadAsync
	b L_g5_15
	L_g5_14:
	lhz r7, 0x2(r30)
	lis r6, sound@ha
	lhz r5, 0x4c(r28)
	lis r4, 0x1
	slwi r7, r7, 2
	addi r6, r6, sound@l
	add r6, r6, r7
	subfic r5, r5, 0x1
	slwi r5, r5, 2
	lwz r7, 0x21c(r6)
	add r3, r3, r0
	lhz r6, 0x4(r30)
	addi r0, r5, 0x2c
	addi r4, r4, -0x8000
	add r24, r3, r7
	lwzx r3, r28, r0
	add r24, r6, r24
	bl DCInvalidateRange
	lhz r0, 0x4c(r28)
	lis r3, cache_flush@ha
	addi r10, r3, cache_flush@l
	mr r4, r28
	subfic r0, r0, 0x1
	mr r7, r24
	slwi r3, r0, 2
	mr r9, r26
	addi r0, r3, 0x2c
	li r5, 0x1
	lwzx r8, r28, r0
	addi r3, r28, 0x4
	li r6, 0x0
	bl ARQPostRequest
	L_g5_15:
	stw r27, 0x48(r28)
	lhz r0, 0x0(r30)
	ori r0, r0, 0x2000
	sth r0, 0x0(r30)
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_2
	li r0, 0x1
	sth r0, 0x104(r30)
	L_g5_2:
	addi r31, r31, 0x1
	addi r25, r25, 0x138
	cmpwi r31, 0x3
	blt L_g5_1
	lmw r24, 0x10(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void SoundSSMain(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stmw r26, 0x28(r1)
	li r26, 0x0
	lis r3, sound@ha
	mr r30, r26
	li r28, 0x0
	addi r31, r3, sound@l
	L_g5_1:
	lwz r0, 0x100(r31)
	add r27, r0, r30
	lhz r3, 0x0(r27)
	rlwinm. r0, r3, 0, 28, 28
	beq L_g5_2
	rlwinm. r0, r3, 0, 30, 30
	bne L_g5_2
	rlwinm. r0, r3, 0, 29, 29
	beq L_g5_3
	rlwinm r0, r3, 0, 30, 28
	sth r0, 0x0(r27)
	lwz r0, 0x100(r31)
	add r29, r0, r26
	lhz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq L_g5_2
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_4
	bl OSDisableInterrupts
	stw r3, 0x210(r31)
	L_g5_4:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_5
	lhz r4, 0x2(r29)
	lis r3, sound@ha
	addi r0, r3, sound@l
	li r5, 0x0
	slwi r3, r4, 1
	add r3, r0, r3
	sth r5, 0x226(r3)
	L_g5_5:
	li r0, 0x0
	sth r0, 0x0(r29)
	lwz r3, 0x28(r29)
	bl DVDMgrClose
	lwz r3, 0xb0(r29)
	bl DVDMgrClose
	lwz r3, 0x4c(r29)
	bl sndStreamFree
	lhz r0, 0x1a(r29)
	cmplwi r0, 0x2
	bne L_g5_6
	lwz r3, 0xd4(r29)
	bl sndStreamFree
	L_g5_6:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_7
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_7
	lwz r3, 0x210(r31)
	bl OSRestoreInterrupts
	L_g5_7:
	li r0, -0x1
	stw r0, 0x104(r31)
	b L_g5_2
	L_g5_3:
	rlwinm. r0, r3, 0, 25, 25
	beq L_g5_8
	lfs f2, float_0_8041b6d8(r2)
	lfs f1, 0x10(r27)
	fcmpu cr0, f2, f1
	bne L_g5_9
	ori r0, r3, 0x2
	sth r0, 0x0(r27)
	lhz r0, 0x0(r27)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r27)
	b L_g5_2
	L_g5_9:
	lfs f0, 0x14(r27)
	fsubs f0, f1, f0
	stfs f0, 0x10(r27)
	lfs f0, 0x10(r27)
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne L_g5_10
	stfs f2, 0x10(r27)
	L_g5_10:
	lwz r0, 0x100(r31)
	lhz r3, 0x6(r27)
	add r29, r0, r26
	lhz r0, 0x0(r29)
	clrlwi r5, r3, 24
	cmplwi r0, 0x0
	beq L_g5_8
	sth r5, 0x6(r29)
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_8
	lhz r0, 0x1a(r29)
	cmplwi r0, 0x1
	bne L_g5_11
	lfs f0, 0x10(r29)
	li r7, 0x0
	lhz r0, 0x8(r29)
	fctiwz f0, f0
	lwz r3, 0x4c(r29)
	clrlwi r6, r0, 24
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	b L_g5_8
	L_g5_11:
	lfs f3, 0x10(r29)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_12
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0xc(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x8(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_12:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_13
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x14(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x10(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x10(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_13:
	fctiwz f0, f3
	lhz r0, 0x8(r29)
	lwz r3, 0x4c(r29)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r29)
	lwz r3, 0xd4(r29)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	L_g5_8:
	lhz r3, 0x0(r27)
	rlwinm. r0, r3, 0, 26, 26
	beq L_g5_14
	lfs f2, float_0_8041b6d8(r2)
	lfs f1, 0x10(r27)
	fcmpu cr0, f2, f1
	bne L_g5_15
	rlwinm r0, r3, 0, 27, 25
	sth r0, 0x0(r27)
	lwz r0, 0x100(r31)
	add r29, r0, r26
	lhz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq L_g5_2
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_16
	bl OSDisableInterrupts
	stw r3, 0x210(r31)
	L_g5_16:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_17
	lhz r4, 0x2(r29)
	lis r3, sound@ha
	addi r0, r3, sound@l
	li r5, 0x0
	slwi r3, r4, 1
	add r3, r0, r3
	sth r5, 0x226(r3)
	L_g5_17:
	li r0, 0x0
	sth r0, 0x0(r29)
	lwz r3, 0x28(r29)
	bl DVDMgrClose
	lwz r3, 0xb0(r29)
	bl DVDMgrClose
	lwz r3, 0x4c(r29)
	bl sndStreamFree
	lhz r0, 0x1a(r29)
	cmplwi r0, 0x2
	bne L_g5_18
	lwz r3, 0xd4(r29)
	bl sndStreamFree
	L_g5_18:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_19
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_19
	lwz r3, 0x210(r31)
	bl OSRestoreInterrupts
	L_g5_19:
	li r0, -0x1
	stw r0, 0x104(r31)
	b L_g5_2
	L_g5_15:
	lfs f0, 0x14(r27)
	fsubs f0, f1, f0
	stfs f0, 0x10(r27)
	lfs f0, 0x10(r27)
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne L_g5_20
	stfs f2, 0x10(r27)
	L_g5_20:
	lwz r0, 0x100(r31)
	lhz r3, 0x6(r27)
	add r29, r0, r26
	lhz r0, 0x0(r29)
	clrlwi r5, r3, 24
	cmplwi r0, 0x0
	beq L_g5_14
	sth r5, 0x6(r29)
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_14
	lhz r0, 0x1a(r29)
	cmplwi r0, 0x1
	bne L_g5_21
	lfs f0, 0x10(r29)
	li r7, 0x0
	lhz r0, 0x8(r29)
	fctiwz f0, f0
	lwz r3, 0x4c(r29)
	clrlwi r6, r0, 24
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	b L_g5_14
	L_g5_21:
	lfs f3, 0x10(r29)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_22
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0x24(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x20(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_22:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_23
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x1c(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x18(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x18(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_23:
	fctiwz f0, f3
	lhz r0, 0x8(r29)
	lwz r3, 0x4c(r29)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x10(r1)
	lwz r4, 0x14(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r29)
	lwz r3, 0xd4(r29)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	L_g5_14:
	lhz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_2
	lfs f1, 0x10(r27)
	lfs f0, 0x14(r27)
	fadds f0, f1, f0
	stfs f0, 0x10(r27)
	lfs f0, 0x10(r27)
	lfs f1, 0xc(r27)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne L_g5_24
	stfs f1, 0x10(r27)
	lfs f0, float_0_8041b6d8(r2)
	stfs f0, 0x14(r27)
	lhz r0, 0x0(r27)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r27)
	L_g5_24:
	lwz r0, 0x100(r31)
	lhz r3, 0x6(r27)
	add r29, r0, r26
	lhz r0, 0x0(r29)
	clrlwi r5, r3, 24
	cmplwi r0, 0x0
	beq L_g5_2
	sth r5, 0x6(r29)
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_2
	lhz r0, 0x1a(r29)
	cmplwi r0, 0x1
	bne L_g5_25
	lfs f0, 0x10(r29)
	li r7, 0x0
	lhz r0, 0x8(r29)
	fctiwz f0, f0
	lwz r3, 0x4c(r29)
	clrlwi r6, r0, 24
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	b L_g5_2
	L_g5_25:
	lfs f3, 0x10(r29)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_26
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0x24(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x20(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_26:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_27
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x1c(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x18(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x18(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_27:
	fctiwz f0, f3
	lhz r0, 0x8(r29)
	lwz r3, 0x4c(r29)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x10(r1)
	lwz r4, 0x14(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r29)
	lwz r3, 0xd4(r29)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	L_g5_2:
	addi r28, r28, 0x1
	addi r26, r26, 0x138
	cmpwi r28, 0x3
	addi r30, r30, 0x138
	blt L_g5_1
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	lmw r26, 0x28(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void SoundSSMuteOff(s32 chan) {
	nofralloc
	lis r4, sound@ha
	addi r4, r4, sound@l
	mulli r3, r3, 0x138
	lwz r4, 0x100(r4)
	lhzx r0, r4, r3
	cmplwi r0, 0x0
	beqlr
	rlwinm r0, r0, 0, 31, 29
	sthx r0, r4, r3
	blr
}

asm void SoundSSMuteOn(s32 chan) {
	nofralloc
	lis r4, sound@ha
	addi r4, r4, sound@l
	mulli r3, r3, 0x138
	lwz r4, 0x100(r4)
	lhzx r0, r4, r3
	cmplwi r0, 0x0
	beqlr
	ori r0, r0, 0x2
	sthx r0, r4, r3
	blr
}

asm u16 SoundSSCheck(s32 chan) {
	nofralloc
	lis r4, sound@ha
	addi r4, r4, sound@l
	mulli r0, r3, 0x138
	lwz r3, 0x100(r4)
	lhzx r3, r3, r0
	blr
}

asm void SoundSSSetPlayFreqCh(s32 chan, u16 freq) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x14(r1)
	mulli r0, r3, 0x138
	stw r31, 0xc(r1)
	addi r31, r5, sound@l
	stw r30, 0x8(r1)
	lwz r3, 0x100(r31)
	add r30, r3, r0
	lhz r0, 0x0(r30)
	cmplwi r0, 0x0
	beq L_g5_1
	sth r4, 0x18(r30)
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_1
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_2
	bl OSDisableInterrupts
	lis r4, sound@ha
	addi r4, r4, sound@l
	stw r3, 0x210(r4)
	L_g5_2:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lwz r3, 0x4c(r30)
	lhz r4, 0x18(r30)
	bl sndStreamFrq
	lhz r0, 0x1a(r30)
	cmplwi r0, 0x2
	bne L_g5_3
	lwz r3, 0xd4(r30)
	lhz r4, 0x18(r30)
	bl sndStreamFrq
	L_g5_3:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_1
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_1
	lis r3, sound@ha
	addi r3, r3, sound@l
	lwz r3, 0x210(r3)
	bl OSRestoreInterrupts
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSSSetSrndPanCh(s32 chan, u8 span) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	lis r5, sound@ha
	addi r5, r5, sound@l
	mulli r6, r3, 0x138
	lwz r0, 0x100(r5)
	add r3, r0, r6
	lhz r0, 0x0(r3)
	cmplwi r0, 0x0
	beq L_g5_1
	clrlwi r0, r4, 24
	sth r0, 0x8(r3)
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_1
	lwz r0, 0x100(r5)
	lhz r3, 0x6(r3)
	add r31, r0, r6
	lhz r0, 0x0(r31)
	clrlwi r5, r3, 24
	cmplwi r0, 0x0
	beq L_g5_1
	sth r5, 0x6(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_1
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x1
	bne L_g5_2
	lfs f0, 0x10(r31)
	li r7, 0x0
	lhz r0, 0x8(r31)
	fctiwz f0, f0
	lwz r3, 0x4c(r31)
	clrlwi r6, r0, 24
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	b L_g5_1
	L_g5_2:
	lfs f3, 0x10(r31)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_3
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0xc(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x8(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_3:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_4
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x14(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x10(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x10(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_4:
	fctiwz f0, f3
	lhz r0, 0x8(r31)
	lwz r3, 0x4c(r31)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r31)
	lwz r3, 0xd4(r31)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	L_g5_1:
	psq_l f31, 0x38(r1), 0, 0
	lwz r0, 0x44(r1)
	lfd f31, 0x30(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 SoundSSGetVolCh(s32 chan) {
	nofralloc
	lis r4, sound@ha
	stwu r1, -0x10(r1)
	addi r4, r4, sound@l
	mulli r0, r3, 0x138
	lwz r3, 0x100(r4)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	cmplwi r0, 0x0
	beq L_g5_1
	lfs f0, 0xc(r3)
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r3, 0xc(r1)
	b L_g5_2
	L_g5_1:
	li r3, 0x0
	L_g5_2:
	addi r1, r1, 0x10
	blr
}

asm void SoundSSSetVolCh(s32 chan, u8 vol) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	lis r5, sound@ha
	addi r5, r5, sound@l
	mulli r7, r3, 0x138
	lwz r0, 0x100(r5)
	add r6, r0, r7
	lhz r0, 0x0(r6)
	cmplwi r0, 0x0
	beq L_g5_1
	clrlwi r0, r4, 24
	lis r4, 0x4330
	stw r0, 0xc(r1)
	lis r3, double_to_int_mask_802e5718@ha
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r4, 0x8(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f2
	stfs f0, 0x10(r6)
	stfs f0, 0xc(r6)
	lhz r0, 0x0(r6)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_1
	lwz r0, 0x100(r5)
	lhz r3, 0x6(r6)
	add r31, r0, r7
	lhz r0, 0x0(r31)
	clrlwi r5, r3, 24
	cmplwi r0, 0x0
	beq L_g5_1
	sth r5, 0x6(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_1
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x1
	bne L_g5_2
	lfs f0, 0x10(r31)
	li r7, 0x0
	lhz r0, 0x8(r31)
	fctiwz f0, f0
	lwz r3, 0x4c(r31)
	clrlwi r6, r0, 24
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	b L_g5_1
	L_g5_2:
	lfs f3, 0x10(r31)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_3
	stw r5, 0xc(r1)
	lfs f0, float_63_8041b6dc(r2)
	stw r4, 0x8(r1)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_3:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_4
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x14(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x10(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x10(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_4:
	fctiwz f0, f3
	lhz r0, 0x8(r31)
	lwz r3, 0x4c(r31)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r31)
	lwz r3, 0xd4(r31)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	L_g5_1:
	psq_l f31, 0x38(r1), 0, 0
	lwz r0, 0x44(r1)
	lfd f31, 0x30(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void SoundSSSetPanCh(s32 chan, u8 pan) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	lis r5, sound@ha
	addi r5, r5, sound@l
	mulli r0, r3, 0x138
	lwz r3, 0x100(r5)
	add r31, r3, r0
	lhz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq L_g5_1
	clrlwi r5, r4, 24
	sth r5, 0x6(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_1
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x1
	bne L_g5_2
	lfs f0, 0x10(r31)
	mr r5, r4
	lhz r0, 0x8(r31)
	li r7, 0x0
	fctiwz f0, f0
	lwz r3, 0x4c(r31)
	clrlwi r6, r0, 24
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	b L_g5_1
	L_g5_2:
	lfs f3, 0x10(r31)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_3
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0xc(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x8(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_3:
	clrlwi r3, r4, 24
	subi r0, r3, 0x40
	srwi. r0, r0, 31
	bne L_g5_4
	subfic r3, r3, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x14(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x10(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x10(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_4:
	fctiwz f0, f3
	lhz r0, 0x8(r31)
	lwz r3, 0x4c(r31)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r31)
	lwz r3, 0xd4(r31)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	L_g5_1:
	psq_l f31, 0x38(r1), 0, 0
	lwz r0, 0x44(r1)
	lfd f31, 0x30(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void SoundSSContinueCh(s32 chan) {
	nofralloc
	lis r4, sound@ha
	addi r4, r4, sound@l
	mulli r0, r3, 0x138
	lwz r3, 0x100(r4)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	cmplwi r0, 0x0
	beqlr
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x0(r3)
	lfs f0, 0xc(r3)
	stfs f0, 0x14(r3)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x10
	sth r0, 0x0(r3)
	blr
}

asm void SoundSSFadeoutCh(s32 chan) {
	nofralloc
	lis r4, sound@ha
	stwu r1, -0x10(r1)
	addi r4, r4, sound@l
	mulli r0, r3, 0x138
	lwz r3, 0x100(r4)
	add r5, r3, r0
	lhz r0, 0x0(r5)
	cmplwi r0, 0x0
	beq L_g5_1
	lhz r4, 0x20a(r4)
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r0, 0x8(r1)
	lfd f3, double_to_int_mask_802e5718@l(r3)
	stw r4, 0xc(r1)
	lfs f1, float_16p667_8041b6e0(r2)
	lfd f2, 0x8(r1)
	lfs f0, float_1_8041b6e4(r2)
	fsubs f2, f2, f3
	fdivs f1, f2, f1
	fcmpo cr0, f1, f0
	bge L_g5_2
	fmr f1, f0
	L_g5_2:
	lfs f0, 0x10(r5)
	fdivs f0, f0, f1
	stfs f0, 0x14(r5)
	lhz r0, 0x0(r5)
	ori r0, r0, 0x20
	sth r0, 0x0(r5)
	L_g5_1:
	addi r1, r1, 0x10
	blr
}

asm void SoundSSStopCh(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	mulli r0, r3, 0x138
	stw r31, 0xc(r1)
	addi r31, r4, sound@l
	stw r30, 0x8(r1)
	lwz r3, 0x100(r31)
	add r30, r3, r0
	lhz r0, 0x0(r30)
	cmplwi r0, 0x0
	beq L_g5_1
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_2
	bl OSDisableInterrupts
	lis r4, sound@ha
	addi r4, r4, sound@l
	stw r3, 0x210(r4)
	L_g5_2:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_3
	lhz r0, 0x2(r30)
	lis r3, sound@ha
	addi r3, r3, sound@l
	li r4, 0x0
	slwi r0, r0, 1
	add r3, r3, r0
	sth r4, 0x226(r3)
	L_g5_3:
	li r0, 0x0
	sth r0, 0x0(r30)
	lwz r3, 0x28(r30)
	bl DVDMgrClose
	lwz r3, 0xb0(r30)
	bl DVDMgrClose
	lwz r3, 0x4c(r30)
	bl sndStreamFree
	lhz r0, 0x1a(r30)
	cmplwi r0, 0x2
	bne L_g5_4
	lwz r3, 0xd4(r30)
	bl sndStreamFree
	L_g5_4:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_5
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_5
	lis r3, sound@ha
	addi r3, r3, sound@l
	lwz r3, 0x210(r3)
	bl OSRestoreInterrupts
	L_g5_5:
	lis r3, sound@ha
	li r0, -0x1
	addi r3, r3, sound@l
	stw r0, 0x104(r3)
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stmw r25, 0x44(r1)
	cmpwi r3, 0x0
	blt L_g5_1
	lis r3, sound@ha
	li r30, 0x0
	addi r29, r3, sound@l
	lwz r5, 0x100(r29)
	lhz r0, 0x0(r5)
	mr r31, r5
	cmplwi r0, 0x0
	beq L_g5_2
	lwz r3, 0x28(r5)
	addi r0, r3, 0x40
	cmplw r0, r4
	beq L_g5_3
	L_g5_2:
	lhzu r0, 0x138(r5)
	li r30, 0x1
	cmplwi r0, 0x0
	mr r31, r5
	beq L_g5_4
	lwz r3, 0x28(r5)
	addi r0, r3, 0x40
	cmplw r0, r4
	beq L_g5_3
	L_g5_4:
	lhzu r0, 0x138(r5)
	li r30, 0x2
	cmplwi r0, 0x0
	mr r31, r5
	beq L_g5_5
	lwz r3, 0x28(r5)
	addi r0, r3, 0x40
	cmplw r0, r4
	beq L_g5_3
	L_g5_5:
	li r30, 0x3
	L_g5_3:
	lwz r3, 0x50(r31)
	lbz r5, 0x0(r3)
	lhz r0, 0x2(r3)
	sth r0, 0x18(r31)
	lwz r0, 0x4(r3)
	sth r0, 0x1a(r31)
	lwz r0, 0x8(r3)
	stw r0, 0x1c(r31)
	lwz r0, 0xc(r3)
	stw r0, 0x20(r31)
	lwz r0, 0x10(r3)
	stw r0, 0x88(r31)
	lwz r0, 0x14(r3)
	stw r0, 0x110(r31)
	lwz r0, 0x18(r3)
	stw r0, 0x8c(r31)
	lwz r0, 0x1c(r3)
	stw r0, 0x114(r31)
	lhz r0, 0x20(r3)
	sth r0, 0x76(r31)
	lhz r0, 0x22(r3)
	sth r0, 0xfe(r31)
	lhz r0, 0x24(r3)
	sth r0, 0x78(r31)
	lhz r0, 0x26(r3)
	sth r0, 0x100(r31)
	lwz r4, 0x20(r31)
	addis r0, r4, 0x1
	cmplwi r0, 0xffff
	beq L_g5_6
	lhz r0, 0x0(r31)
	ori r0, r0, 0x200
	sth r0, 0x0(r31)
	b L_g5_7
	L_g5_6:
	li r0, 0x0
	stw r0, 0x20(r31)
	L_g5_7:
	cmpwi r5, 0x1
	beq L_g5_8
	bge L_g5_9
	cmpwi r5, 0x0
	bge L_g5_10
	b L_g5_11
	L_g5_9:
	cmpwi r5, 0x3
	bge L_g5_11
	b L_g5_12
	L_g5_10:
	lwz r3, 0x1c(r31)
	li r0, 0x40
	stw r3, 0x88(r31)
	lwz r3, 0x1c(r31)
	stw r3, 0x110(r31)
	lwz r3, 0x20(r31)
	stw r3, 0x8c(r31)
	lwz r3, 0x20(r31)
	stw r3, 0x114(r31)
	sth r0, 0x4(r31)
	b L_g5_11
	L_g5_8:
	lhz r3, 0x0(r31)
	li r0, 0x40
	ori r3, r3, 0x80
	sth r3, 0x0(r31)
	lha r3, 0x76(r31)
	sth r3, 0x7a(r31)
	lha r3, 0xfe(r31)
	sth r3, 0x102(r31)
	sth r0, 0x4(r31)
	b L_g5_11
	L_g5_12:
	lhz r4, 0x0(r31)
	li r0, 0x4
	addi r6, r3, 0x5c
	addi r5, r31, 0x90
	ori r4, r4, 0x100
	sth r4, 0x0(r31)
	mtctr r0
	L_g5_13:
	lbz r0, 0x0(r6)
	stb r0, 0x0(r5)
	lbz r0, 0x1(r6)
	stb r0, 0x1(r5)
	lbz r0, 0x2(r6)
	stb r0, 0x2(r5)
	lbz r0, 0x3(r6)
	stb r0, 0x3(r5)
	lbz r0, 0x4(r6)
	stb r0, 0x4(r5)
	lbz r0, 0x5(r6)
	stb r0, 0x5(r5)
	lbz r0, 0x6(r6)
	stb r0, 0x6(r5)
	lbz r0, 0x7(r6)
	addi r6, r6, 0x8
	stb r0, 0x7(r5)
	addi r5, r5, 0x8
	bdnz L_g5_13
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x2
	bne L_g5_14
	li r0, 0x4
	addi r4, r3, 0xbc
	addi r3, r31, 0x118
	mtctr r0
	L_g5_15:
	lbz r0, 0x0(r4)
	stb r0, 0x0(r3)
	lbz r0, 0x1(r4)
	stb r0, 0x1(r3)
	lbz r0, 0x2(r4)
	stb r0, 0x2(r3)
	lbz r0, 0x3(r4)
	stb r0, 0x3(r3)
	lbz r0, 0x4(r4)
	stb r0, 0x4(r3)
	lbz r0, 0x5(r4)
	stb r0, 0x5(r3)
	lbz r0, 0x6(r4)
	stb r0, 0x6(r3)
	lbz r0, 0x7(r4)
	addi r4, r4, 0x8
	stb r0, 0x7(r3)
	addi r3, r3, 0x8
	bdnz L_g5_15
	L_g5_14:
	li r0, 0x100
	sth r0, 0x4(r31)
	L_g5_11:
	li r0, 0x0
	sth r0, 0x74(r31)
	stw r0, 0x6c(r31)
	stw r0, 0x5c(r31)
	stw r0, 0x60(r31)
	sth r0, 0x7c(r31)
	sth r0, 0x7e(r31)
	sth r0, 0x80(r31)
	sth r0, 0x82(r31)
	sth r0, 0x84(r31)
	sth r0, 0xfc(r31)
	stw r0, 0xf4(r31)
	stw r0, 0xe4(r31)
	stw r0, 0xe8(r31)
	sth r0, 0x104(r31)
	sth r0, 0x106(r31)
	sth r0, 0x108(r31)
	sth r0, 0x10a(r31)
	sth r0, 0x10c(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 21, 21
	bne L_g5_16
	li r0, 0x1
	lis r4, 0x1
	sth r0, 0x74(r31)
	addi r28, r31, 0x28
	addi r26, r4, -0x8000
	lwz r6, 0x5c(r31)
	lwz r7, 0x88(r31)
	addis r3, r6, 0x1
	addi r0, r3, -0x8000
	cmplw r0, r7
	ble L_g5_17
	subf r26, r6, r7
	b L_g5_18
	L_g5_17:
	li r0, 0x4
	li r5, 0x2
	mtctr r0
	L_g5_19:
	add r0, r6, r4
	cmplw r0, r7
	ble L_g5_20
	subi r0, r5, 0x1
	lis r3, 0x1
	slwi r0, r0, 15
	add r4, r6, r0
	addi r0, r3, -0x8000
	subf r3, r4, r7
	subf r0, r3, r0
	divwu r0, r0, r5
	subf r26, r0, r26
	clrlwi r0, r26, 27
	subfic r0, r0, 0x20
	add r26, r26, r0
	b L_g5_18
	L_g5_20:
	addis r4, r4, 0x1
	addi r5, r5, 0x1
	addi r4, r4, -0x8000
	bdnz L_g5_19
	L_g5_18:
	lhz r0, 0x0(r31)
	addi r3, r26, 0x1f
	clrrwi r27, r3, 5
	rlwinm. r0, r0, 0, 21, 21
	bne L_g5_21
	lhz r4, 0x4c(r28)
	lis r3, _ssDVDReadAsync_activeChk@ha
	lhz r0, 0x4(r31)
	addi r7, r3, _ssDVDReadAsync_activeChk@l
	subfic r4, r4, 0x1
	lwz r3, 0x0(r28)
	slwi r4, r4, 2
	mr r5, r27
	add r4, r28, r4
	add r6, r0, r6
	lwz r4, 0x2c(r4)
	bl DVDMgrReadAsync
	b L_g5_22
	L_g5_21:
	lhz r3, 0x2(r31)
	lis r5, sound@ha
	lhz r0, 0x4c(r28)
	lis r4, 0x1
	addi r5, r5, sound@l
	slwi r3, r3, 2
	add r3, r5, r3
	subfic r0, r0, 0x1
	slwi r0, r0, 2
	lwz r5, 0x21c(r3)
	add r3, r28, r0
	lhz r0, 0x4(r31)
	add r25, r6, r5
	lwz r3, 0x2c(r3)
	add r25, r0, r25
	addi r4, r4, -0x8000
	bl DCInvalidateRange
	lhz r0, 0x4c(r28)
	lis r3, cache_flush@ha
	addi r10, r3, cache_flush@l
	mr r4, r28
	subfic r0, r0, 0x1
	mr r7, r25
	slwi r0, r0, 2
	mr r9, r27
	add r3, r28, r0
	li r5, 0x1
	lwz r8, 0x2c(r3)
	addi r3, r28, 0x4
	li r6, 0x0
	bl ARQPostRequest
	L_g5_22:
	stw r26, 0x48(r28)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x1000
	sth r0, 0x0(r31)
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x2
	bne L_g5_16
	li r0, 0x1
	lis r5, 0x1
	sth r0, 0xfc(r31)
	addi r28, r31, 0xb0
	addi r27, r5, -0x8000
	lwz r3, 0xe4(r31)
	lwz r7, 0x110(r31)
	addis r4, r3, 0x1
	addi r0, r4, -0x8000
	clrlwi r4, r7, 27
	cmplw r0, r7
	subfic r0, r4, 0x20
	add r0, r7, r0
	ble L_g5_23
	subf r27, r3, r7
	b L_g5_24
	L_g5_23:
	li r4, 0x4
	li r6, 0x2
	mtctr r4
	L_g5_25:
	add r4, r3, r5
	cmplw r4, r7
	ble L_g5_26
	subi r5, r6, 0x1
	lis r4, 0x1
	slwi r5, r5, 15
	add r5, r3, r5
	addi r4, r4, -0x8000
	subf r5, r5, r7
	subf r4, r5, r4
	divwu r4, r4, r6
	subf r27, r4, r27
	clrlwi r4, r27, 27
	subfic r4, r4, 0x20
	add r27, r27, r4
	b L_g5_24
	L_g5_26:
	addis r5, r5, 0x1
	addi r6, r6, 0x1
	addi r5, r5, -0x8000
	bdnz L_g5_25
	L_g5_24:
	lhz r4, 0x0(r31)
	addi r5, r27, 0x1f
	clrrwi r26, r5, 5
	rlwinm. r4, r4, 0, 21, 21
	bne L_g5_27
	lhz r5, 0x4c(r28)
	lis r4, _ssDVDReadAsync_activeChk@ha
	addi r7, r4, _ssDVDReadAsync_activeChk@l
	add r6, r3, r0
	subfic r4, r5, 0x1
	lhz r8, 0x4(r31)
	slwi r0, r4, 2
	lwz r3, 0x0(r28)
	add r4, r28, r0
	mr r5, r26
	lwz r4, 0x2c(r4)
	add r6, r8, r6
	bl DVDMgrReadAsync
	b L_g5_28
	L_g5_27:
	lhz r6, 0x2(r31)
	lis r7, sound@ha
	lhz r5, 0x4c(r28)
	lis r4, 0x1
	addi r7, r7, sound@l
	slwi r6, r6, 2
	add r6, r7, r6
	subfic r5, r5, 0x1
	slwi r5, r5, 2
	lwz r7, 0x21c(r6)
	add r0, r3, r0
	lhz r6, 0x4(r31)
	add r3, r28, r5
	addi r4, r4, -0x8000
	add r25, r0, r7
	lwz r3, 0x2c(r3)
	add r25, r6, r25
	bl DCInvalidateRange
	lhz r0, 0x4c(r28)
	lis r3, cache_flush@ha
	addi r10, r3, cache_flush@l
	mr r4, r28
	subfic r0, r0, 0x1
	mr r7, r25
	slwi r0, r0, 2
	mr r9, r26
	add r3, r28, r0
	li r5, 0x1
	lwz r8, 0x2c(r3)
	addi r3, r28, 0x4
	li r6, 0x0
	bl ARQPostRequest
	L_g5_28:
	stw r27, 0x48(r28)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x2000
	sth r0, 0x0(r31)
	L_g5_16:
	li r3, 0xe00
	li r4, 0x0
	bl sndStreamAllocLength
	cmplwi r3, 0x0
	lwz r6, 0x50(r31)
	li r5, 0x0
	mr r4, r3
	beq L_g5_29
	srwi. r0, r4, 3
	mtctr r0
	beq L_g5_30
	L_g5_31:
	stb r5, 0x0(r6)
	stb r5, 0x1(r6)
	stb r5, 0x2(r6)
	stb r5, 0x3(r6)
	stb r5, 0x4(r6)
	stb r5, 0x5(r6)
	stb r5, 0x6(r6)
	stb r5, 0x7(r6)
	addi r6, r6, 0x8
	bdnz L_g5_31
	andi. r4, r4, 0x7
	beq L_g5_29
	L_g5_30:
	mtctr r4
	L_g5_32:
	stb r5, 0x0(r6)
	addi r6, r6, 0x1
	bdnz L_g5_32
	L_g5_29:
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x2
	bne L_g5_33
	cmplwi r3, 0x0
	lwz r5, 0xd8(r31)
	li r4, 0x0
	beq L_g5_33
	srwi. r0, r3, 3
	mtctr r0
	beq L_g5_34
	L_g5_35:
	stb r4, 0x0(r5)
	stb r4, 0x1(r5)
	stb r4, 0x2(r5)
	stb r4, 0x3(r5)
	stb r4, 0x4(r5)
	stb r4, 0x5(r5)
	stb r4, 0x6(r5)
	stb r4, 0x7(r5)
	addi r5, r5, 0x8
	bdnz L_g5_35
	andi. r3, r3, 0x7
	beq L_g5_33
	L_g5_34:
	mtctr r3
	L_g5_36:
	stb r4, 0x0(r5)
	addi r5, r5, 0x1
	bdnz L_g5_36
	L_g5_33:
	lhz r0, 0x1a(r31)
	li r8, 0x0
	cmplwi r0, 0x1
	bne L_g5_37
	li r8, 0x40
	L_g5_37:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	bne L_g5_38
	li r6, 0x0
	lis r3, _sscallback@ha
	stw r6, 0x8(r1)
	addi r0, r3, _sscallback@l
	lis r4, 0x1
	li r3, 0xff
	stw r6, 0xc(r1)
	li r5, 0xe00
	li r7, 0x0
	li r9, 0x0
	stw r4, 0x10(r1)
	li r10, 0x0
	stw r0, 0x14(r1)
	stw r30, 0x18(r1)
	stw r6, 0x1c(r1)
	lwz r4, 0x50(r31)
	lhz r6, 0x18(r31)
	bl sndStreamAllocEx
	stw r3, 0x4c(r31)
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x2
	bne L_g5_39
	li r11, 0x0
	lis r3, _sscallback@ha
	stw r11, 0x8(r1)
	lis r6, 0x1
	addi r4, r3, _sscallback@l
	ori r0, r30, 0x100
	stw r11, 0xc(r1)
	li r3, 0xff
	li r5, 0xe00
	li r7, 0x0
	stw r6, 0x10(r1)
	li r8, 0x7f
	li r9, 0x0
	li r10, 0x0
	stw r4, 0x14(r1)
	stw r0, 0x18(r1)
	stw r11, 0x1c(r1)
	lwz r4, 0xd8(r31)
	lhz r6, 0x18(r31)
	bl sndStreamAllocEx
	stw r3, 0xd4(r31)
	L_g5_39:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x8
	sth r0, 0x0(r31)
	b L_g5_40
	L_g5_38:
	li r6, 0x0
	lis r4, 0x1
	stw r6, 0x8(r1)
	addi r5, r4, 0x1
	lis r3, _sscallback@ha
	addi r0, r31, 0x90
	stw r6, 0xc(r1)
	addi r4, r3, _sscallback@l
	li r3, 0xff
	li r7, 0x0
	stw r5, 0x10(r1)
	li r5, 0xe00
	li r9, 0x0
	li r10, 0x0
	stw r4, 0x14(r1)
	stw r30, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r4, 0x50(r31)
	lhz r6, 0x18(r31)
	bl sndStreamAllocEx
	stw r3, 0x4c(r31)
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x2
	bne L_g5_40
	li r0, 0x0
	lis r4, 0x1
	stw r0, 0x8(r1)
	lis r3, _sscallback@ha
	addi r5, r4, 0x1
	ori r4, r30, 0x100
	stw r0, 0xc(r1)
	addi r6, r3, _sscallback@l
	addi r0, r31, 0x118
	li r3, 0xff
	stw r5, 0x10(r1)
	li r5, 0xe00
	li r7, 0x0
	li r8, 0x7f
	stw r6, 0x14(r1)
	li r9, 0x0
	li r10, 0x0
	stw r4, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r4, 0xd8(r31)
	lhz r6, 0x18(r31)
	bl sndStreamAllocEx
	stw r3, 0xd4(r31)
	L_g5_40:
	lfs f0, 0xc(r31)
	mulli r0, r30, 0x138
	stfs f0, 0x14(r31)
	lhz r3, 0x0(r31)
	ori r3, r3, 0x10
	sth r3, 0x0(r31)
	lwz r3, 0x100(r29)
	lhz r4, 0x6(r31)
	add r26, r3, r0
	lhz r0, 0x0(r26)
	clrlwi r5, r4, 24
	cmplwi r0, 0x0
	beq L_g5_41
	sth r5, 0x6(r26)
	lhz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_41
	lhz r0, 0x1a(r26)
	cmplwi r0, 0x1
	bne L_g5_42
	lfs f0, 0x10(r26)
	li r7, 0x0
	lhz r0, 0x8(r26)
	fctiwz f0, f0
	lwz r3, 0x4c(r26)
	clrlwi r6, r0, 24
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	b L_g5_41
	L_g5_42:
	lfs f3, 0x10(r26)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_43
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0x24(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x20(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_43:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_44
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x2c(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x28(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x28(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_44:
	fctiwz f0, f3
	lhz r0, 0x8(r26)
	lwz r3, 0x4c(r26)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x30(r1)
	lwz r4, 0x34(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r26)
	lwz r3, 0xd4(r26)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	bl sndStreamMixParameter
	L_g5_41:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_1
	lwz r3, 0x28(r31)
	bl DVDMgrGetLength
	lwz r6, 0x5c(r31)
	lis r4, 0x1
	addi r26, r4, -0x8000
	addis r4, r6, 0x1
	addi r0, r4, -0x8000
	cmplw r0, r3
	blt L_g5_45
	subf r26, r6, r3
	L_g5_45:
	lis r3, _ssDVDReadAsync_cache_next@ha
	addi r0, r26, 0x1f
	addi r7, r3, _ssDVDReadAsync_cache_next@l
	lwz r3, 0x28(r31)
	lwz r4, 0x54(r31)
	clrrwi r5, r0, 5
	bl DVDMgrReadAsync
	stw r26, 0x70(r31)
	L_g5_1:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	lmw r25, 0x44(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void SoundSSPlayChEx(s32 chan, const char* name, s32 aram) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	lis r3, sound@ha
	mr r28, r4
	addi r31, r3, sound@l
	mr r29, r5
	mulli r0, r27, 0x138
	lwz r3, 0x100(r31)
	add r30, r3, r0
	lhz r0, 0x0(r30)
	cmplwi r0, 0x0
	beq L_g5_1
	beq L_g5_1
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_2
	bl OSDisableInterrupts
	lis r4, sound@ha
	addi r4, r4, sound@l
	stw r3, 0x210(r4)
	L_g5_2:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_3
	lhz r0, 0x2(r30)
	lis r3, sound@ha
	addi r3, r3, sound@l
	li r4, 0x0
	slwi r0, r0, 1
	add r3, r3, r0
	sth r4, 0x226(r3)
	L_g5_3:
	li r0, 0x0
	sth r0, 0x0(r30)
	lwz r3, 0x28(r30)
	bl DVDMgrClose
	lwz r3, 0xb0(r30)
	bl DVDMgrClose
	lwz r3, 0x4c(r30)
	bl sndStreamFree
	lhz r0, 0x1a(r30)
	cmplwi r0, 0x2
	bne L_g5_4
	lwz r3, 0xd4(r30)
	bl sndStreamFree
	L_g5_4:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_5
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_5
	lis r3, sound@ha
	addi r3, r3, sound@l
	lwz r3, 0x210(r3)
	bl OSRestoreInterrupts
	L_g5_5:
	lis r3, sound@ha
	li r0, -0x1
	addi r3, r3, sound@l
	stw r0, 0x104(r3)
	L_g5_1:
	cmpwi r29, 0x0
	beq L_g5_6
	lis r3, sound@ha
	li r6, 0x0
	addi r5, r3, sound@l
	lhz r0, 0x224(r5)
	mr r3, r5
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_7
	L_g5_8:
	lhz r0, 0x226(r3)
	cmplwi r0, 0x0
	bne L_g5_9
	lis r3, sound@ha
	slwi r0, r6, 1
	addi r3, r3, sound@l
	li r4, 0x1
	add r3, r3, r0
	sth r4, 0x226(r3)
	sth r6, 0x2(r30)
	b L_g5_7
	L_g5_9:
	addi r3, r3, 0x2
	addi r6, r6, 0x1
	bdnz L_g5_8
	L_g5_7:
	lhz r0, 0x224(r5)
	cmpw r6, r0
	bge L_g5_10
	L_g5_6:
	lis r3, sound@ha
	li r4, 0x0
	addi r5, r3, sound@l
	li r3, 0x40
	stw r27, 0x104(r5)
	cmpwi r29, 0x0
	lfs f1, float_0_8041b6d8(r2)
	li r0, 0x1
	sth r4, 0x74(r30)
	lfs f0, float_127_8041b6e8(r2)
	stw r4, 0x6c(r30)
	stw r4, 0x5c(r30)
	stw r4, 0x60(r30)
	sth r4, 0x7c(r30)
	sth r4, 0x7e(r30)
	sth r4, 0x80(r30)
	sth r4, 0x82(r30)
	sth r4, 0x84(r30)
	sth r4, 0xfc(r30)
	stw r4, 0xf4(r30)
	stw r4, 0xe4(r30)
	stw r4, 0xe8(r30)
	sth r4, 0x104(r30)
	sth r4, 0x106(r30)
	sth r4, 0x108(r30)
	sth r4, 0x10a(r30)
	sth r4, 0x10c(r30)
	sth r3, 0x6(r30)
	sth r4, 0x8(r30)
	stfs f1, 0x10(r30)
	stfs f0, 0xc(r30)
	sth r0, 0x0(r30)
	beq L_g5_11
	lhz r0, 0x0(r30)
	ori r0, r0, 0x400
	sth r0, 0x0(r30)
	L_g5_11:
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r28
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B6EC(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x0
	addi r27, r3, g5_str_s436@l
	li r5, 0x0
	mr r3, r27
	bl DVDMgrOpen
	cmplwi r3, 0x0
	stw r3, 0x28(r30)
	bne L_g5_12
	li r0, 0x0
	sth r0, 0x0(r30)
	b L_g5_10
	L_g5_12:
	mr r3, r27
	li r4, 0x0
	li r5, 0x0
	bl DVDMgrOpen
	cmplwi r3, 0x0
	stw r3, 0xb0(r30)
	bne L_g5_13
	li r0, 0x0
	sth r0, 0x0(r30)
	b L_g5_10
	L_g5_13:
	lis r4, SoundSSPlayChEx_main@ha
	lwz r3, 0x28(r30)
	addi r7, r4, SoundSSPlayChEx_main@l
	lwz r4, 0x50(r30)
	li r5, 0x100
	li r6, 0x0
	bl DVDMgrReadAsync
	L_g5_10:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void SoundSSPlayCh(s32 chan, const char* name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x0
	stw r0, 0x14(r1)
	bl SoundSSPlayChEx
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm u32 _sscallback(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r8, sound@ha
	stw r0, 0x24(r1)
	clrlwi r0, r7, 24
	addi r10, r8, sound@l
	stw r31, 0x1c(r1)
	mulli r8, r0, 0x138
	li r0, 0x0
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r6
	mr r6, r3
	stw r28, 0x10(r1)
	mr r28, r5
	lwz r9, 0x100(r10)
	add r31, r9, r8
	mr r8, r4
	stw r0, 0x24(r31)
	lhz r3, 0x0(r31)
	andi. r0, r3, 0x8006
	bne L_g5_1
	lhz r0, 0x214(r10)
	cmplwi r0, 0x0
	beq L_g5_2
	L_g5_1:
	rlwinm. r0, r3, 0, 23, 23
	bne L_g5_3
	cmplwi r8, 0x0
	mr r3, r8
	li r5, 0x0
	beq L_g5_4
	srwi. r0, r8, 3
	mtctr r0
	beq L_g5_5
	L_g5_6:
	sth r5, 0x0(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x2(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x4(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x6(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x8(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0xa(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0xc(r6)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0xe(r6)
	addi r6, r6, 0x10
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	bdnz L_g5_6
	andi. r3, r3, 0x7
	beq L_g5_4
	L_g5_5:
	mtctr r3
	L_g5_7:
	sth r5, 0x0(r6)
	addi r6, r6, 0x2
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	bdnz L_g5_7
	L_g5_4:
	cmplwi r29, 0x0
	mr r3, r29
	li r5, 0x0
	beq L_g5_8
	srwi. r0, r29, 3
	mtctr r0
	beq L_g5_9
	L_g5_10:
	sth r5, 0x0(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x2(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x4(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x6(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0x8(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0xa(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0xc(r28)
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	sth r5, 0xe(r28)
	addi r28, r28, 0x10
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	bdnz L_g5_10
	andi. r3, r3, 0x7
	beq L_g5_8
	L_g5_9:
	mtctr r3
	L_g5_11:
	sth r5, 0x0(r28)
	addi r28, r28, 0x2
	lwz r4, 0x24(r31)
	addi r0, r4, 0x1
	stw r0, 0x24(r31)
	bdnz L_g5_11
	L_g5_8:
	lwz r3, 0x24(r31)
	b L_g5_12
	L_g5_3:
	lis r3, 0x2492
	li r4, 0x0
	addi r0, r3, 0x4925
	mulhwu r3, r0, r8
	subf r0, r3, r8
	srwi r0, r0, 1
	add r0, r0, r3
	clrrwi r3, r0, 3
	srwi r0, r0, 31
	add r0, r0, r3
	srawi. r3, r0, 1
	beq L_g5_13
	srwi. r0, r3, 3
	mtctr r0
	beq L_g5_14
	L_g5_15:
	sth r4, 0x0(r6)
	sth r4, 0x2(r6)
	sth r4, 0x4(r6)
	sth r4, 0x6(r6)
	sth r4, 0x8(r6)
	sth r4, 0xa(r6)
	sth r4, 0xc(r6)
	sth r4, 0xe(r6)
	addi r6, r6, 0x10
	bdnz L_g5_15
	andi. r3, r3, 0x7
	beq L_g5_13
	L_g5_14:
	mtctr r3
	L_g5_16:
	sth r4, 0x0(r6)
	addi r6, r6, 0x2
	bdnz L_g5_16
	L_g5_13:
	lis r3, 0x2492
	li r4, 0x0
	addi r0, r3, 0x4925
	mulhwu r3, r0, r29
	subf r0, r3, r29
	srwi r0, r0, 1
	add r0, r0, r3
	clrrwi r3, r0, 3
	srwi r0, r0, 31
	add r0, r0, r3
	srawi. r3, r0, 1
	beq L_g5_17
	srwi. r0, r3, 3
	mtctr r0
	beq L_g5_18
	L_g5_19:
	sth r4, 0x0(r28)
	sth r4, 0x2(r28)
	sth r4, 0x4(r28)
	sth r4, 0x6(r28)
	sth r4, 0x8(r28)
	sth r4, 0xa(r28)
	sth r4, 0xc(r28)
	sth r4, 0xe(r28)
	addi r28, r28, 0x10
	bdnz L_g5_19
	andi. r3, r3, 0x7
	beq L_g5_17
	L_g5_18:
	mtctr r3
	L_g5_20:
	sth r4, 0x0(r28)
	addi r28, r28, 0x2
	bdnz L_g5_20
	L_g5_17:
	add r3, r8, r29
	b L_g5_12
	L_g5_2:
	rlwinm. r0, r7, 0, 23, 23
	beq L_g5_21
	addi r30, r31, 0xb0
	b L_g5_22
	L_g5_21:
	addi r30, r31, 0x28
	L_g5_22:
	rlwinm. r0, r3, 0, 24, 24
	beq L_g5_23
	lhz r5, 0x4c(r30)
	mr r3, r31
	lwz r0, 0x44(r30)
	mr r4, r30
	slwi r7, r5, 2
	mr r5, r6
	add r7, r30, r7
	mr r6, r8
	lwz r7, 0x2c(r7)
	add r7, r7, r0
	bl ssDecodeDPCM
	mr r7, r3
	mr r3, r31
	mr r4, r30
	mr r5, r28
	mr r6, r29
	bl ssDecodeDPCM
	b L_g5_24
	L_g5_23:
	rlwinm. r0, r3, 0, 23, 23
	beq L_g5_25
	lis r3, 0x2492
	lhz r4, 0x4c(r30)
	addi r0, r8, 0xd
	lwz r7, 0x44(r30)
	slwi r5, r4, 2
	addi r3, r3, 0x4925
	mulhwu r4, r3, r0
	add r5, r30, r5
	lwz r5, 0x2c(r5)
	mr r3, r6
	add r5, r5, r7
	subf r0, r4, r0
	srwi r0, r0, 1
	add r0, r0, r4
	clrrwi r4, r0, 3
	b L_g5_26
	L_g5_27:
	lbz r0, 0x0(r5)
	addi r5, r5, 0x1
	subi r4, r4, 0x1
	stb r0, 0x0(r3)
	addi r3, r3, 0x1
	lwz r6, 0x44(r30)
	addi r0, r6, 0x1
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	lwz r7, 0x44(r30)
	slwi r6, r0, 2
	addi r0, r6, 0x3c
	lwzx r0, r30, r0
	cmplw r7, r0
	blt L_g5_28
	lha r0, 0x54(r30)
	cmpwi r0, 0x0
	bne L_g5_29
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 17, 17
	bne L_g5_29
	lwz r5, 0x38(r30)
	li r0, 0x0
	subf r5, r7, r5
	stw r5, 0x38(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	b L_g5_26
	L_g5_29:
	li r0, 0x0
	sth r0, 0x54(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	subfic r0, r0, 0x1
	sth r0, 0x4c(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	L_g5_28:
	lwz r6, 0x38(r30)
	addi r0, r6, 0x1
	stw r0, 0x38(r30)
	lwz r6, 0x38(r30)
	lwz r0, 0x1c(r31)
	cmplw r6, r0
	blt L_g5_26
	lwz r0, 0x20(r31)
	stw r0, 0x38(r30)
	lhz r6, 0x0(r31)
	rlwinm. r0, r6, 0, 22, 22
	bne L_g5_26
	ori r0, r6, 0x4
	sth r0, 0x0(r31)
	b L_g5_30
	L_g5_26:
	cmplwi r4, 0x0
	bne L_g5_27
	L_g5_30:
	lis r3, 0x2492
	addi r0, r29, 0xd
	addi r3, r3, 0x4925
	mulhwu r4, r3, r0
	mr r3, r28
	subf r0, r4, r0
	srwi r0, r0, 1
	add r0, r0, r4
	clrrwi r4, r0, 3
	b L_g5_31
	L_g5_32:
	lbz r0, 0x0(r5)
	addi r5, r5, 0x1
	subi r4, r4, 0x1
	stb r0, 0x0(r3)
	addi r3, r3, 0x1
	lwz r6, 0x44(r30)
	addi r0, r6, 0x1
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	lwz r7, 0x44(r30)
	slwi r6, r0, 2
	addi r0, r6, 0x3c
	lwzx r0, r30, r0
	cmplw r7, r0
	blt L_g5_33
	lha r0, 0x54(r30)
	cmpwi r0, 0x0
	bne L_g5_34
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 17, 17
	bne L_g5_34
	lwz r5, 0x38(r30)
	li r0, 0x0
	subf r5, r7, r5
	stw r5, 0x38(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	b L_g5_31
	L_g5_34:
	li r0, 0x0
	sth r0, 0x54(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	subfic r0, r0, 0x1
	sth r0, 0x4c(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	L_g5_33:
	lwz r6, 0x38(r30)
	addi r0, r6, 0x1
	stw r0, 0x38(r30)
	lwz r6, 0x38(r30)
	lwz r0, 0x1c(r31)
	cmplw r6, r0
	blt L_g5_31
	lwz r0, 0x20(r31)
	stw r0, 0x38(r30)
	lhz r6, 0x0(r31)
	rlwinm. r0, r6, 0, 22, 22
	bne L_g5_31
	ori r0, r6, 0x4
	sth r0, 0x0(r31)
	b L_g5_35
	L_g5_31:
	cmplwi r4, 0x0
	bne L_g5_32
	L_g5_35:
	add r0, r8, r29
	stw r0, 0x24(r31)
	b L_g5_24
	L_g5_25:
	lhz r5, 0x4c(r30)
	mr r4, r8
	lwz r0, 0x44(r30)
	mr r3, r6
	slwi r5, r5, 2
	add r5, r30, r5
	clrrwi r0, r0, 1
	lwz r5, 0x2c(r5)
	add r5, r5, r0
	b L_g5_36
	L_g5_37:
	lha r0, 0x0(r5)
	addi r5, r5, 0x2
	subi r4, r4, 0x1
	sth r0, 0x0(r3)
	addi r3, r3, 0x2
	lwz r6, 0x24(r31)
	addi r0, r6, 0x1
	stw r0, 0x24(r31)
	lwz r6, 0x44(r30)
	addi r0, r6, 0x2
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	lwz r7, 0x44(r30)
	slwi r6, r0, 2
	addi r0, r6, 0x3c
	lwzx r0, r30, r0
	cmplw r7, r0
	blt L_g5_38
	lha r0, 0x54(r30)
	cmpwi r0, 0x0
	bne L_g5_39
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 17, 17
	bne L_g5_39
	lwz r5, 0x38(r30)
	li r0, 0x0
	subf r5, r7, r5
	stw r5, 0x38(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	b L_g5_36
	L_g5_39:
	li r0, 0x0
	sth r0, 0x54(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	subfic r0, r0, 0x1
	sth r0, 0x4c(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	L_g5_38:
	lwz r6, 0x38(r30)
	addi r0, r6, 0x2
	stw r0, 0x38(r30)
	lwz r6, 0x38(r30)
	lwz r0, 0x1c(r31)
	cmplw r6, r0
	blt L_g5_36
	lwz r0, 0x20(r31)
	stw r0, 0x38(r30)
	lhz r6, 0x0(r31)
	rlwinm. r0, r6, 0, 22, 22
	bne L_g5_36
	ori r0, r6, 0x4
	sth r0, 0x0(r31)
	b L_g5_40
	L_g5_36:
	cmplwi r4, 0x0
	bne L_g5_37
	L_g5_40:
	mr r4, r29
	mr r3, r28
	b L_g5_41
	L_g5_42:
	lha r0, 0x0(r5)
	addi r5, r5, 0x2
	subi r4, r4, 0x1
	sth r0, 0x0(r3)
	addi r3, r3, 0x2
	lwz r6, 0x24(r31)
	addi r0, r6, 0x1
	stw r0, 0x24(r31)
	lwz r6, 0x44(r30)
	addi r0, r6, 0x2
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	lwz r7, 0x44(r30)
	slwi r6, r0, 2
	addi r0, r6, 0x3c
	lwzx r0, r30, r0
	cmplw r7, r0
	blt L_g5_43
	lha r0, 0x54(r30)
	cmpwi r0, 0x0
	bne L_g5_44
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 17, 17
	bne L_g5_44
	lwz r5, 0x38(r30)
	li r0, 0x0
	subf r5, r7, r5
	stw r5, 0x38(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	b L_g5_41
	L_g5_44:
	li r0, 0x0
	sth r0, 0x54(r30)
	stw r0, 0x44(r30)
	lhz r0, 0x4c(r30)
	subfic r0, r0, 0x1
	sth r0, 0x4c(r30)
	lhz r0, 0x4c(r30)
	slwi r5, r0, 2
	addi r0, r5, 0x2c
	lwzx r5, r30, r0
	L_g5_43:
	lwz r6, 0x38(r30)
	addi r0, r6, 0x2
	stw r0, 0x38(r30)
	lwz r6, 0x38(r30)
	lwz r0, 0x1c(r31)
	cmplw r6, r0
	blt L_g5_41
	lwz r0, 0x20(r31)
	stw r0, 0x38(r30)
	lhz r6, 0x0(r31)
	rlwinm. r0, r6, 0, 22, 22
	bne L_g5_41
	ori r0, r6, 0x4
	sth r0, 0x0(r31)
	b L_g5_24
	L_g5_41:
	cmplwi r4, 0x0
	bne L_g5_42
	L_g5_24:
	lwz r3, 0x24(r31)
	L_g5_12:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm u8* ssDecodeDPCM(SoundStream* stream, SoundStreamEntry* entry, s16* out, u32 count, u8* src) {
	nofralloc
	b L_g5_1
	L_g5_2:
	lhz r0, 0x5c(r4)
	lbz r10, 0x0(r7)
	cmplwi r0, 0x0
	beq L_g5_3
	lhz r8, 0x5a(r4)
	extrwi r0, r10, 4, 24
	extsb r9, r0
	clrlwi. r0, r8, 31
	beq L_g5_4
	clrlwi r9, r10, 28
	L_g5_4:
	lhz r8, 0x5a(r4)
	extsb r0, r9
	lhz r10, 0x58(r4)
	slwi r9, r0, 4
	addi r0, r8, 0x1
	sth r0, 0x5a(r4)
	extsb r9, r9
	srawi r0, r9, 4
	lhz r8, 0x5a(r4)
	extsb r9, r0
	lhz r0, 0x5c(r4)
	cmplw r8, r0
	blt L_g5_5
	li r0, 0x0
	addi r7, r7, 0x1
	sth r0, 0x5c(r4)
	lwz r8, 0x44(r4)
	addi r0, r8, 0x1
	stw r0, 0x44(r4)
	b L_g5_6
	L_g5_5:
	clrlwi. r0, r8, 31
	bne L_g5_6
	lwz r8, 0x44(r4)
	addi r7, r7, 0x1
	addi r0, r8, 0x1
	stw r0, 0x44(r4)
	b L_g5_6
	L_g5_3:
	lwz r8, 0x44(r4)
	clrlwi r9, r10, 28
	cmpwi r9, 0x8
	addi r7, r7, 0x1
	addi r0, r8, 0x1
	stw r0, 0x44(r4)
	bne L_g5_7
	extrwi r8, r10, 4, 24
	li r0, 0x0
	addi r8, r8, 0x4
	sth r8, 0x5c(r4)
	sth r0, 0x5a(r4)
	b L_g5_1
	L_g5_7:
	extsb r9, r9
	extrwi r10, r10, 4, 24
	slwi r0, r9, 4
	sth r10, 0x58(r4)
	extsb r9, r0
	srawi r0, r9, 4
	extsb r9, r0
	L_g5_6:
	slwi r0, r10, 1
	la r8, dtbl(r13)
	lhax r0, r8, r0
	extsb r8, r9
	lha r9, 0x52(r4)
	mullw r0, r8, r0
	add r0, r9, r0
	cmpwi r0, 0x7fff
	ble L_g5_8
	li r0, 0x7fff
	L_g5_8:
	cmpwi r0, -0x8000
	bge L_g5_9
	li r0, -0x8000
	L_g5_9:
	sth r0, 0x52(r4)
	subi r6, r6, 0x1
	sth r0, 0x0(r5)
	addi r5, r5, 0x2
	lwz r8, 0x24(r3)
	addi r0, r8, 0x1
	stw r0, 0x24(r3)
	lhz r0, 0x4c(r4)
	lwz r9, 0x44(r4)
	slwi r8, r0, 2
	addi r0, r8, 0x3c
	lwzx r0, r4, r0
	cmplw r9, r0
	blt L_g5_10
	lha r0, 0x54(r4)
	cmpwi r0, 0x0
	bne L_g5_11
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 17, 17
	bne L_g5_11
	lwz r7, 0x38(r4)
	li r0, 0x0
	subf r7, r9, r7
	stw r7, 0x38(r4)
	stw r0, 0x44(r4)
	lhz r0, 0x4c(r4)
	slwi r7, r0, 2
	addi r0, r7, 0x2c
	lwzx r7, r4, r0
	b L_g5_1
	L_g5_11:
	li r0, 0x0
	sth r0, 0x54(r4)
	stw r0, 0x44(r4)
	lhz r0, 0x4c(r4)
	subfic r0, r0, 0x1
	sth r0, 0x4c(r4)
	lhz r0, 0x4c(r4)
	slwi r7, r0, 2
	addi r0, r7, 0x2c
	lwzx r7, r4, r0
	L_g5_10:
	lwz r8, 0x38(r4)
	addi r0, r8, 0x2
	stw r0, 0x38(r4)
	lwz r8, 0x38(r4)
	lwz r0, 0x1c(r3)
	cmplw r8, r0
	blt L_g5_1
	lwz r0, 0x20(r3)
	stw r0, 0x38(r4)
	lha r0, 0x50(r4)
	sth r0, 0x52(r4)
	lhz r8, 0x0(r3)
	rlwinm. r0, r8, 0, 22, 22
	bne L_g5_1
	ori r0, r8, 0x4
	sth r0, 0x0(r3)
	b L_g5_12
	L_g5_1:
	cmplwi r6, 0x0
	bne L_g5_2
	L_g5_12:
	mr r3, r7
	blr
}

asm void _ssDVDReadAsync_cache_next(s32 result, DVDFileInfo* fileInfo) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x24(r1)
	li r0, 0x3
	addi r5, r5, sound@l
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	lwz r31, 0x100(r5)
	mtctr r0
	L_g5_1:
	lhz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq L_g5_2
	lwz r5, 0x28(r31)
	addi r0, r5, 0x40
	cmplw r0, r4
	bne L_g5_2
	cmpwi r3, 0x0
	blt L_g5_3
	lwz r6, 0x5c(r31)
	lis r4, sound@ha
	lwz r0, 0x70(r31)
	lis r3, 0x1
	addi r5, r4, sound@l
	add r0, r6, r0
	addi r4, r3, -0x8000
	stw r0, 0x5c(r31)
	lhz r0, 0x2(r31)
	lwz r6, 0x60(r31)
	slwi r0, r0, 2
	lwz r3, 0x54(r31)
	add r5, r5, r0
	lwz r0, 0x21c(r5)
	add r29, r6, r0
	bl DCFlushRange
	lwz r4, g5_owner_no_s1419(r13)
	lis r3, _ssDVDReadAsync_cache_aram@ha
	addi r10, r3, _ssDVDReadAsync_cache_aram@l
	lis r5, 0x1
	addi r3, r4, 0x1
	slwi r0, r4, 16
	stw r3, g5_owner_no_s1419(r13)
	addi r9, r5, -0x8000
	mr r8, r29
	addi r3, r31, 0x2c
	lwz r7, 0x54(r31)
	or r4, r0, r30
	li r5, 0x0
	li r6, 0x0
	bl ARQPostRequest
	lwz r3, 0x60(r31)
	lwz r0, 0x70(r31)
	add r0, r3, r0
	stw r0, 0x60(r31)
	b L_g5_3
	L_g5_2:
	addi r31, r31, 0x138
	addi r30, r30, 0x1
	bdnz L_g5_1
	L_g5_3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	lwz r0, 0x4(r3)
	lis r3, sound@ha
	addi r3, r3, sound@l
	clrlwi r0, r0, 24
	lwz r3, 0x100(r3)
	mulli r0, r0, 0x138
	add r28, r3, r0
	lwz r3, 0x28(r28)
	bl DVDMgrGetLength
	lwz r0, 0x60(r28)
	cmplw r0, r3
	blt L_g5_1
	li r3, 0x0
	lis r4, 0x1
	stw r3, 0x5c(r28)
	li r0, 0x1
	addi r31, r28, 0x28
	addi r29, r4, -0x8000
	stw r3, 0x60(r28)
	stw r3, 0xe4(r28)
	stw r3, 0xe8(r28)
	sth r0, 0x74(r28)
	lwz r6, 0x5c(r28)
	lwz r7, 0x88(r28)
	addis r3, r6, 0x1
	addi r0, r3, -0x8000
	cmplw r0, r7
	ble L_g5_2
	subf r29, r6, r7
	b L_g5_3
	L_g5_2:
	li r0, 0x4
	li r5, 0x2
	mtctr r0
	L_g5_4:
	add r0, r6, r4
	cmplw r0, r7
	ble L_g5_5
	subi r0, r5, 0x1
	lis r3, 0x1
	slwi r0, r0, 15
	add r4, r6, r0
	addi r0, r3, -0x8000
	subf r3, r4, r7
	subf r0, r3, r0
	divwu r0, r0, r5
	subf r29, r0, r29
	clrlwi r0, r29, 27
	subfic r0, r0, 0x20
	add r29, r29, r0
	b L_g5_3
	L_g5_5:
	addis r4, r4, 0x1
	addi r5, r5, 0x1
	addi r4, r4, -0x8000
	bdnz L_g5_4
	L_g5_3:
	lhz r0, 0x0(r28)
	addi r3, r29, 0x1f
	clrrwi r30, r3, 5
	rlwinm. r0, r0, 0, 21, 21
	bne L_g5_6
	lhz r4, 0x4c(r31)
	lis r3, _ssDVDReadAsync_activeChk@ha
	lhz r0, 0x4(r28)
	addi r7, r3, _ssDVDReadAsync_activeChk@l
	subfic r4, r4, 0x1
	lwz r3, 0x0(r31)
	slwi r4, r4, 2
	mr r5, r30
	add r4, r31, r4
	add r6, r0, r6
	lwz r4, 0x2c(r4)
	bl DVDMgrReadAsync
	b L_g5_7
	L_g5_6:
	lhz r3, 0x2(r28)
	lis r5, sound@ha
	lhz r0, 0x4c(r31)
	lis r4, 0x1
	addi r5, r5, sound@l
	slwi r3, r3, 2
	add r3, r5, r3
	subfic r0, r0, 0x1
	slwi r0, r0, 2
	lwz r5, 0x21c(r3)
	add r3, r31, r0
	lhz r0, 0x4(r28)
	add r27, r6, r5
	lwz r3, 0x2c(r3)
	add r27, r0, r27
	addi r4, r4, -0x8000
	bl DCInvalidateRange
	lhz r0, 0x4c(r31)
	lis r3, cache_flush@ha
	addi r10, r3, cache_flush@l
	mr r4, r31
	subfic r0, r0, 0x1
	mr r7, r27
	slwi r0, r0, 2
	mr r9, r30
	add r3, r31, r0
	li r5, 0x1
	lwz r8, 0x2c(r3)
	addi r3, r31, 0x4
	li r6, 0x0
	bl ARQPostRequest
	L_g5_7:
	stw r29, 0x48(r31)
	lhz r0, 0x1a(r28)
	cmplwi r0, 0x2
	bne L_g5_8
	li r0, 0x1
	lis r5, 0x1
	sth r0, 0xfc(r28)
	addi r31, r28, 0xb0
	addi r30, r5, -0x8000
	lwz r3, 0xe4(r28)
	lwz r7, 0x110(r28)
	addis r4, r3, 0x1
	addi r0, r4, -0x8000
	clrlwi r4, r7, 27
	cmplw r0, r7
	subfic r0, r4, 0x20
	add r0, r7, r0
	ble L_g5_9
	subf r30, r3, r7
	b L_g5_10
	L_g5_9:
	li r4, 0x4
	li r6, 0x2
	mtctr r4
	L_g5_11:
	add r4, r3, r5
	cmplw r4, r7
	ble L_g5_12
	subi r5, r6, 0x1
	lis r4, 0x1
	slwi r5, r5, 15
	add r5, r3, r5
	addi r4, r4, -0x8000
	subf r5, r5, r7
	subf r4, r5, r4
	divwu r4, r4, r6
	subf r30, r4, r30
	clrlwi r4, r30, 27
	subfic r4, r4, 0x20
	add r30, r30, r4
	b L_g5_10
	L_g5_12:
	addis r5, r5, 0x1
	addi r6, r6, 0x1
	addi r5, r5, -0x8000
	bdnz L_g5_11
	L_g5_10:
	lhz r4, 0x0(r28)
	addi r5, r30, 0x1f
	clrrwi r29, r5, 5
	rlwinm. r4, r4, 0, 21, 21
	bne L_g5_13
	lhz r5, 0x4c(r31)
	lis r4, _ssDVDReadAsync_activeChk@ha
	addi r7, r4, _ssDVDReadAsync_activeChk@l
	add r6, r3, r0
	subfic r4, r5, 0x1
	lhz r8, 0x4(r28)
	slwi r0, r4, 2
	lwz r3, 0x0(r31)
	add r4, r31, r0
	mr r5, r29
	lwz r4, 0x2c(r4)
	add r6, r8, r6
	bl DVDMgrReadAsync
	b L_g5_14
	L_g5_13:
	lhz r6, 0x2(r28)
	lis r7, sound@ha
	lhz r5, 0x4c(r31)
	lis r4, 0x1
	addi r7, r7, sound@l
	slwi r6, r6, 2
	add r6, r7, r6
	subfic r5, r5, 0x1
	slwi r5, r5, 2
	lwz r7, 0x21c(r6)
	add r0, r3, r0
	lhz r6, 0x4(r28)
	add r3, r31, r5
	addi r4, r4, -0x8000
	add r27, r0, r7
	lwz r3, 0x2c(r3)
	add r27, r6, r27
	bl DCInvalidateRange
	lhz r0, 0x4c(r31)
	lis r3, cache_flush@ha
	addi r10, r3, cache_flush@l
	mr r4, r31
	subfic r0, r0, 0x1
	mr r7, r27
	slwi r0, r0, 2
	mr r9, r29
	add r3, r31, r0
	li r5, 0x1
	lwz r8, 0x2c(r3)
	addi r3, r31, 0x4
	li r6, 0x0
	bl ARQPostRequest
	L_g5_14:
	stw r30, 0x48(r31)
	b L_g5_8
	L_g5_1:
	lwz r3, 0x28(r28)
	bl DVDMgrGetLength
	lwz r6, 0x5c(r28)
	lis r4, 0x1
	addi r29, r4, -0x8000
	addis r4, r6, 0x1
	addi r0, r4, -0x8000
	cmplw r0, r3
	blt L_g5_15
	subf r29, r6, r3
	L_g5_15:
	lis r3, _ssDVDReadAsync_cache_next@ha
	addi r0, r29, 0x1f
	addi r7, r3, _ssDVDReadAsync_cache_next@l
	lwz r3, 0x28(r28)
	lwz r4, 0x54(r28)
	clrrwi r5, r0, 5
	bl DVDMgrReadAsync
	stw r29, 0x70(r28)
	L_g5_8:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void cache_flush(u32 pointerToARQRequest) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r4, r3
	li r3, 0x0
	stw r0, 0x14(r1)
	lwz r4, 0x4(r4)
	lwz r4, 0x0(r4)
	addi r4, r4, 0x40
	bl _ssDVDReadAsync_activeChk
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _ssDVDReadAsync_activeChk(s32 result, DVDFileInfo* fileInfo) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stmw r27, 0x2c(r1)
	lis r5, sound@ha
	mr r28, r3
	addi r30, r5, sound@l
	mr r27, r4
	lhz r0, 0x20c(r30)
	cmplwi r0, 0x0
	bne L_g5_1
	bl OSDisableInterrupts
	lis r4, sound@ha
	addi r4, r4, sound@l
	stw r3, 0x210(r4)
	L_g5_1:
	lhz r4, 0x20c(r30)
	lis r3, sound@ha
	addi r31, r3, sound@l
	li r0, 0x3
	addi r4, r4, 0x1
	lwz r3, 0x100(r31)
	sth r4, 0x20c(r30)
	mtctr r0
	L_g5_2:
	lhz r0, 0x0(r3)
	cmplwi r0, 0x0
	beq L_g5_3
	lwz r4, 0x28(r3)
	li r6, 0x0
	li r7, 0x0
	addi r0, r4, 0x40
	cmplw r0, r27
	bne L_g5_4
	addi r6, r3, 0x28
	li r7, 0x0
	L_g5_4:
	lwz r4, 0xb0(r3)
	addi r0, r4, 0x40
	cmplw r0, r27
	bne L_g5_5
	addi r6, r3, 0xb0
	li r7, 0x1
	L_g5_5:
	cmplwi r6, 0x0
	beq L_g5_3
	cmpwi r28, 0x0
	blt L_g5_6
	lwz r5, 0x34(r6)
	li r0, 0x1
	lwz r4, 0x48(r6)
	add r4, r5, r4
	stw r4, 0x34(r6)
	lhz r4, 0x4c(r6)
	lwz r5, 0x48(r6)
	subfic r4, r4, 0x1
	slwi r4, r4, 2
	add r4, r6, r4
	stw r5, 0x3c(r4)
	sth r0, 0x54(r6)
	lwz r4, 0x34(r6)
	lwz r0, 0x60(r6)
	cmplw r4, r0
	blt L_g5_7
	lwz r0, 0x64(r6)
	stw r0, 0x34(r6)
	lhz r4, 0x0(r3)
	rlwinm. r0, r4, 0, 22, 22
	beq L_g5_8
	cmpwi r7, 0x0
	bne L_g5_9
	rlwinm r0, r4, 0, 20, 18
	sth r0, 0x0(r3)
	b L_g5_10
	L_g5_9:
	rlwinm r0, r4, 0, 19, 17
	sth r0, 0x0(r3)
	b L_g5_10
	L_g5_8:
	ori r0, r4, 0x4000
	sth r0, 0x0(r3)
	b L_g5_10
	L_g5_7:
	cmpwi r7, 0x0
	bne L_g5_11
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 20, 18
	sth r0, 0x0(r3)
	b L_g5_10
	L_g5_11:
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 19, 17
	sth r0, 0x0(r3)
	L_g5_10:
	lhz r0, 0x1a(r3)
	cmplwi r0, 0x2
	bne L_g5_12
	lis r4, sound@ha
	addi r4, r4, sound@l
	lhz r0, 0x214(r4)
	cmplwi r0, 0x2
	bne L_g5_13
	lha r0, 0x7c(r3)
	cmpwi r0, 0x1
	bne L_g5_13
	lha r0, 0x104(r3)
	cmpwi r0, 0x1
	bne L_g5_13
	li r0, 0x0
	sth r0, 0x214(r4)
	b L_g5_13
	L_g5_12:
	lis r4, sound@ha
	addi r4, r4, sound@l
	lhz r0, 0x214(r4)
	cmplwi r0, 0x2
	bne L_g5_13
	lha r0, 0x7c(r3)
	cmpwi r0, 0x1
	bne L_g5_13
	li r0, 0x0
	sth r0, 0x214(r4)
	b L_g5_13
	L_g5_3:
	addi r3, r3, 0x138
	bdnz L_g5_2
	L_g5_13:
	li r29, 0x0
	li r0, 0x3
	mr r4, r29
	mtctr r0
	L_g5_14:
	lwz r0, 0x100(r31)
	add r28, r0, r4
	lhz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_15
	rlwinm. r0, r0, 0, 28, 28
	bne L_g5_15
	lwz r3, 0x28(r28)
	addi r0, r3, 0x40
	cmplw r0, r27
	bne L_g5_16
	li r0, 0x1
	sth r0, 0x7e(r28)
	L_g5_16:
	lwz r3, 0xb0(r28)
	addi r0, r3, 0x40
	cmplw r0, r27
	bne L_g5_17
	li r0, 0x1
	sth r0, 0x106(r28)
	L_g5_17:
	lhz r0, 0x1a(r28)
	cmplwi r0, 0x2
	bne L_g5_18
	lha r0, 0x7e(r28)
	cmpwi r0, 0x0
	beq L_g5_15
	lha r0, 0x106(r28)
	cmpwi r0, 0x0
	bne L_g5_19
	b L_g5_15
	L_g5_18:
	lha r0, 0x7e(r28)
	cmpwi r0, 0x0
	beq L_g5_15
	L_g5_19:
	li r0, 0x0
	sth r0, 0x74(r28)
	sth r0, 0xfc(r28)
	sth r0, 0x7c(r28)
	sth r0, 0x104(r28)
	lwz r3, 0x4c(r28)
	bl sndStreamActivate
	lhz r0, 0x1a(r28)
	cmplwi r0, 0x2
	bne L_g5_20
	lwz r3, 0xd4(r28)
	bl sndStreamActivate
	L_g5_20:
	mulli r0, r29, 0x138
	lwz r3, 0x100(r31)
	lhz r4, 0x6(r28)
	add r31, r3, r0
	clrlwi r5, r4, 24
	lhz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq L_g5_21
	sth r5, 0x6(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_21
	lhz r0, 0x1a(r31)
	cmplwi r0, 0x1
	bne L_g5_22
	lfs f0, 0x10(r31)
	li r7, 0x0
	lhz r0, 0x8(r31)
	fctiwz f0, f0
	lwz r3, 0x4c(r31)
	clrlwi r6, r0, 24
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	bl sndStreamMixParameter
	b L_g5_21
	L_g5_22:
	lfs f3, 0x10(r31)
	cmplwi r5, 0x40
	fmr f31, f3
	bge L_g5_23
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r5, 0xc(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x8(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_23:
	subi r0, r5, 0x40
	srwi. r0, r0, 31
	bne L_g5_24
	subfic r3, r5, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x14(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x10(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x10(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_24:
	fctiwz f0, f3
	lhz r0, 0x8(r31)
	lwz r3, 0x4c(r31)
	li r5, 0x0
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	bl sndStreamMixParameter
	fctiwz f0, f31
	lhz r0, 0x8(r31)
	lwz r3, 0xd4(r31)
	li r5, 0x7f
	clrlwi r6, r0, 24
	li r7, 0x0
	stfd f0, 0x20(r1)
	lwz r4, 0x24(r1)
	bl sndStreamMixParameter
	L_g5_21:
	lhz r0, 0x0(r28)
	ori r0, r0, 0x8
	sth r0, 0x0(r28)
	b L_g5_6
	L_g5_15:
	addi r4, r4, 0x138
	addi r29, r29, 0x1
	bdnz L_g5_14
	L_g5_6:
	lhz r3, 0x20c(r30)
	cmplwi r3, 0x0
	beq L_g5_25
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r30)
	bne L_g5_25
	lis r3, sound@ha
	addi r3, r3, sound@l
	lwz r3, 0x210(r3)
	bl OSRestoreInterrupts
	L_g5_25:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	lmw r27, 0x2c(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void SoundDVDMain(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stmw r26, 0x28(r1)
	li r27, 0x0
	lis r3, sound@ha
	mr r30, r27
	li r29, 0x0
	addi r31, r3, sound@l
	L_g5_1:
	lwz r0, 0xf8(r31)
	add r28, r0, r30
	lhz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 30, 30
	bne L_g5_2
	rlwinm. r0, r3, 0, 25, 25
	beq L_g5_3
	lfs f2, float_0_8041b6d8(r2)
	lfs f1, 0x8(r28)
	fcmpu cr0, f2, f1
	bne L_g5_4
	bl AIGetStreamSampleCount
	stw r3, 0x114(r28)
	lwz r0, 0xf8(r31)
	add r26, r0, r27
	lhz r0, 0x0(r26)
	clrlwi. r0, r0, 30
	beq L_g5_5
	li r3, 0x0
	bl AISetStreamPlayState
	li r3, 0x0
	li r0, -0x1
	sth r3, 0x0(r26)
	addi r3, r26, 0x118
	stw r0, 0xfc(r31)
	bl DVDCancelStream
	addi r3, r26, 0x118
	bl DVDClose
	L_g5_5:
	lhz r0, 0x0(r28)
	ori r0, r0, 0x2
	sth r0, 0x0(r28)
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r28)
	b L_g5_2
	L_g5_4:
	lfs f0, 0xc(r28)
	fsubs f0, f1, f0
	stfs f0, 0x8(r28)
	lfs f0, 0x8(r28)
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne L_g5_6
	stfs f2, 0x8(r28)
	L_g5_6:
	lhz r3, 0x2(r28)
	lwz r0, 0xf8(r31)
	clrlwi r4, r3, 24
	add r3, r0, r27
	sth r4, 0x2(r3)
	cmplwi r4, 0x40
	lfs f3, 0x8(r3)
	fmr f31, f3
	bge L_g5_7
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r4, 0xc(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x8(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_7:
	subi r0, r4, 0x40
	srwi. r0, r0, 31
	bne L_g5_8
	subfic r3, r4, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x14(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x10(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x10(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_8:
	fctiwz f0, f3
	stfd f0, 0x18(r1)
	lwz r3, 0x1c(r1)
	bl AISetStreamVolLeft
	fctiwz f0, f31
	stfd f0, 0x20(r1)
	lwz r3, 0x24(r1)
	bl AISetStreamVolRight
	L_g5_3:
	lhz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 26, 26
	beq L_g5_9
	lfs f2, float_0_8041b6d8(r2)
	lfs f1, 0x8(r28)
	fcmpu cr0, f2, f1
	bne L_g5_10
	rlwinm r0, r3, 0, 27, 25
	sth r0, 0x0(r28)
	lwz r0, 0xf8(r31)
	add r26, r0, r27
	lhz r0, 0x0(r26)
	clrlwi. r0, r0, 30
	beq L_g5_2
	li r3, 0x0
	bl AISetStreamPlayState
	li r3, 0x0
	li r0, -0x1
	sth r3, 0x0(r26)
	addi r3, r26, 0x118
	stw r0, 0xfc(r31)
	bl DVDCancelStream
	addi r3, r26, 0x118
	bl DVDClose
	b L_g5_2
	L_g5_10:
	lfs f0, 0xc(r28)
	fsubs f0, f1, f0
	stfs f0, 0x8(r28)
	lfs f0, 0x8(r28)
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	bne L_g5_11
	stfs f2, 0x8(r28)
	L_g5_11:
	lhz r3, 0x2(r28)
	lwz r0, 0xf8(r31)
	clrlwi r4, r3, 24
	add r3, r0, r27
	sth r4, 0x2(r3)
	cmplwi r4, 0x40
	lfs f3, 0x8(r3)
	fmr f31, f3
	bge L_g5_12
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r4, 0x24(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x20(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_12:
	subi r0, r4, 0x40
	srwi. r0, r0, 31
	bne L_g5_13
	subfic r3, r4, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x1c(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x18(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x18(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_13:
	fctiwz f0, f3
	stfd f0, 0x10(r1)
	lwz r3, 0x14(r1)
	bl AISetStreamVolLeft
	fctiwz f0, f31
	stfd f0, 0x8(r1)
	lwz r3, 0xc(r1)
	bl AISetStreamVolRight
	L_g5_9:
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_2
	lfs f1, 0x8(r28)
	lfs f0, 0xc(r28)
	fadds f0, f1, f0
	stfs f0, 0x8(r28)
	lfs f0, 0x8(r28)
	lfs f1, 0x4(r28)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne L_g5_14
	stfs f1, 0x8(r28)
	lfs f0, float_0_8041b6d8(r2)
	stfs f0, 0xc(r28)
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r28)
	L_g5_14:
	lhz r3, 0x2(r28)
	lwz r0, 0xf8(r31)
	clrlwi r4, r3, 24
	add r3, r0, r27
	sth r4, 0x2(r3)
	cmplwi r4, 0x40
	lfs f3, 0x8(r3)
	fmr f31, f3
	bge L_g5_15
	lis r0, 0x4330
	lis r3, double_to_int_mask_802e5718@ha
	stw r4, 0x24(r1)
	lfd f2, double_to_int_mask_802e5718@l(r3)
	stw r0, 0x20(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f31, f1, f0
	L_g5_15:
	subi r0, r4, 0x40
	srwi. r0, r0, 31
	bne L_g5_16
	subfic r3, r4, 0x7f
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802e5720@ha
	stw r3, 0x1c(r1)
	lfd f2, double_to_int_802e5720@l(r4)
	stw r0, 0x18(r1)
	lfs f0, float_63_8041b6dc(r2)
	lfd f1, 0x18(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f3
	fdivs f3, f1, f0
	L_g5_16:
	fctiwz f0, f3
	stfd f0, 0x10(r1)
	lwz r3, 0x14(r1)
	bl AISetStreamVolLeft
	fctiwz f0, f31
	stfd f0, 0x8(r1)
	lwz r3, 0xc(r1)
	bl AISetStreamVolRight
	L_g5_2:
	addi r29, r29, 0x1
	addi r27, r27, 0x154
	cmpwi r29, 0x2
	addi r30, r30, 0x154
	blt L_g5_1
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	lmw r26, 0x28(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void SoundEfxMain(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stfd f29, 0x20(r1)
	psq_st f29, 0x28(r1), 0, 0
	stmw r27, 0xc(r1)
	lis r3, sound@ha
	lfs f30, float_0_8041b6d8(r2)
	addi r3, r3, sound@l
	lfs f2, float_6p2832_8041b6f4(r2)
	lfs f1, 0x1f4(r3)
	addi r27, r3, 0x1b8
	lfs f0, float_360_8041b6f8(r2)
	fmr f31, f30
	fmuls f1, f2, f1
	lfs f5, 0x1b8(r3)
	lfs f4, 0x1c4(r3)
	addi r28, r3, 0x1d0
	lfs f3, 0x1bc(r3)
	fdivs f29, f1, f0
	lfs f2, 0x1c8(r3)
	lfs f1, 0x1c0(r3)
	lfs f0, 0x1cc(r3)
	stfs f5, 0x1c4(r3)
	stfs f3, 0x1c8(r3)
	fsubs f4, f5, f4
	stfs f1, 0x1cc(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fmr f1, f29
	stfs f4, 0x1d0(r3)
	stfs f2, 0x1d4(r3)
	stfs f0, 0x1d8(r3)
	bl sin
	frsp f2, f1
	lfs f0, float_1_8041b6e4(r2)
	fmr f1, f29
	fmadds f30, f0, f2, f30
	bl cos
	frsp f2, f1
	lfs f1, float_1_8041b6e4(r2)
	lis r3, sound@ha
	lfs f0, float_0_8041b6d8(r2)
	addi r10, r3, sound@l
	mr r4, r27
	fnmsubs f31, f1, f2, f31
	lwz r0, 0x204(r10)
	stfs f30, 0x1dc(r10)
	addi r6, r10, 0x1dc
	addi r7, r10, 0x1e8
	mr r5, r28
	stfs f0, 0x1e0(r10)
	addi r3, r10, 0x128
	clrlwi r8, r0, 24
	li r9, 0x0
	stfs f31, 0x1e4(r10)
	stfs f0, 0x1e8(r10)
	stfs f1, 0x1ec(r10)
	stfs f0, 0x1f0(r10)
	bl sndUpdateListener
	lis r3, sound@ha
	li r28, 0x0
	addi r31, r3, sound@l
	lwz r27, 0xf4(r31)
	L_g5_1:
	lhz r0, 0x0(r27)
	cmplwi r0, 0x0
	beq L_g5_2
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_2
	lfs f1, 0x64(r27)
	addi r3, r27, 0x14
	lfs f0, 0x70(r27)
	addi r4, r27, 0x64
	addi r5, r27, 0x7c
	li r7, 0x0
	fsubs f0, f1, f0
	stfs f0, 0x7c(r27)
	lfs f1, 0x68(r27)
	lfs f0, 0x74(r27)
	fsubs f0, f1, f0
	stfs f0, 0x80(r27)
	lfs f1, 0x6c(r27)
	lfs f0, 0x78(r27)
	fsubs f0, f1, f0
	stfs f0, 0x84(r27)
	lfs f0, 0x64(r27)
	stfs f0, 0x70(r27)
	lfs f0, 0x68(r27)
	stfs f0, 0x74(r27)
	lfs f0, 0x6c(r27)
	stfs f0, 0x78(r27)
	lhz r0, 0x4(r27)
	clrlwi r6, r0, 24
	bl sndUpdateEmitter
	L_g5_2:
	addi r28, r28, 0x1
	addi r27, r27, 0x88
	cmpwi r28, 0x28
	blt L_g5_1
	li r29, 0x0
	lwz r30, 0xf4(r31)
	mr r28, r29
	L_g5_3:
	lhz r0, 0x0(r30)
	cmplwi r0, 0x0
	beq L_g5_4
	rlwinm. r0, r0, 0, 27, 27
	bne L_g5_5
	lwz r0, 0xf4(r31)
	add r3, r0, r28
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_6
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_7
	L_g5_6:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_7:
	bl sndFXCheck
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne L_g5_4
	lwz r0, 0xf4(r31)
	add r27, r0, r28
	lhz r0, 0x0(r27)
	cmplwi r0, 0x0
	beq L_g5_4
	lwz r3, 0xc(r27)
	bl sndFXKeyOff
	lhz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_8
	addi r3, r27, 0x14
	bl sndRemoveEmitter
	L_g5_8:
	li r0, 0x0
	sth r0, 0x0(r27)
	b L_g5_4
	L_g5_5:
	addi r3, r30, 0x14
	bl sndCheckEmitter
	cmplwi r3, 0x0
	bne L_g5_9
	lwz r0, 0xf4(r31)
	add r27, r0, r28
	lhz r0, 0x0(r27)
	cmplwi r0, 0x0
	beq L_g5_9
	lwz r3, 0xc(r27)
	bl sndFXKeyOff
	lhz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_10
	addi r3, r27, 0x14
	bl sndRemoveEmitter
	L_g5_10:
	li r0, 0x0
	sth r0, 0x0(r27)
	L_g5_9:
	lhz r3, 0xa(r30)
	cmplwi r3, 0x0
	beq L_g5_11
	subi r0, r3, 0x1
	sth r0, 0xa(r30)
	b L_g5_4
	L_g5_11:
	lwz r0, 0xf4(r31)
	add r3, r0, r28
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_12
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_13
	L_g5_12:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_13:
	bl sndFXCheck
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne L_g5_4
	lwz r0, 0xf4(r31)
	add r27, r0, r28
	lhz r0, 0x0(r27)
	cmplwi r0, 0x0
	beq L_g5_4
	lwz r3, 0xc(r27)
	bl sndFXKeyOff
	lhz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_14
	addi r3, r27, 0x14
	bl sndRemoveEmitter
	L_g5_14:
	li r0, 0x0
	sth r0, 0x0(r27)
	L_g5_4:
	addi r29, r29, 0x1
	addi r30, r30, 0x88
	cmpwi r29, 0x28
	addi r28, r28, 0x88
	blt L_g5_3
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	psq_l f29, 0x28(r1), 0, 0
	lfd f29, 0x20(r1)
	lmw r27, 0xc(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm BOOL SoundEfxCheck(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	addi r4, r4, sound@l
	mulli r0, r3, 0x88
	lwz r3, 0xf4(r4)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	cmplwi r0, 0x0
	bne L_g5_1
	li r3, 0x0
	b L_g5_2
	L_g5_1:
	rlwinm. r0, r0, 0, 27, 27
	bne L_g5_3
	beq L_g5_4
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_5
	L_g5_4:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_5:
	bl sndFXCheck
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne L_g5_6
	li r3, 0x0
	b L_g5_2
	L_g5_3:
	addi r3, r3, 0x14
	bl sndCheckEmitter
	cmplwi r3, 0x0
	bne L_g5_6
	li r3, 0x0
	b L_g5_2
	L_g5_6:
	li r3, 0x1
	L_g5_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundEfxSetLPF(s32 chan, s16 freq) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x14(r1)
	mulli r0, r3, 0x88
	stw r31, 0xc(r1)
	mr r31, r4
	addi r4, r5, sound@l
	lwz r3, 0xf4(r4)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_1
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_2
	L_g5_1:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_2:
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq L_g5_3
	extsh. r0, r31
	bne L_g5_4
	li r4, 0x0
	li r5, 0x0
	bl sndFXSetFilter
	b L_g5_3
	L_g5_4:
	extsh r5, r31
	cmpwi r5, 0x3e80
	blt L_g5_5
	li r4, 0x0
	li r5, 0x0
	bl sndFXSetFilter
	b L_g5_3
	L_g5_5:
	li r4, 0x1
	bl sndFXSetFilter
	L_g5_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundEfxSetSrndPan(s32 chan, u8 span) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mulli r6, r3, 0x88
	lis r3, sound@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	addi r0, r6, 0x8
	stw r30, 0x8(r1)
	mr r30, r4
	addi r4, r3, sound@l
	lwz r3, 0xf4(r4)
	clrlwi r5, r30, 24
	sthx r5, r3, r0
	lwz r0, 0xf4(r4)
	add r3, r0, r6
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_1
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_2
	L_g5_1:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_2:
	addis r0, r3, 0x1
	mr r31, r3
	cmplwi r0, 0xffff
	beq L_g5_3
	mr r5, r30
	li r4, 0x83
	bl sndFXCtrl
	clrlwi. r3, r30, 24
	bne L_g5_4
	li r0, 0x2000
	b L_g5_5
	L_g5_4:
	cmplwi r3, 0x40
	bge L_g5_6
	subfic r0, r3, 0x40
	mulli r0, r0, 0x3
	subfic r0, r0, 0x2000
	b L_g5_5
	L_g5_6:
	subi r0, r3, 0x40
	mulli r0, r0, 0x3
	subfic r0, r0, 0x2000
	L_g5_5:
	mr r3, r31
	clrlwi r5, r0, 16
	li r4, 0x84
	bl sndFXCtrl14
	L_g5_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundEfxSetPan(s32 chan, u8 pan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mulli r6, r3, 0x88
	lis r3, sound@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	addi r4, r3, sound@l
	addi r0, r6, 0x6
	lwz r3, 0xf4(r4)
	clrlwi r5, r31, 24
	sthx r5, r3, r0
	lwz r0, 0xf4(r4)
	add r3, r0, r6
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_1
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_2
	L_g5_1:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_2:
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq L_g5_3
	mr r5, r31
	li r4, 0xa
	bl sndFXCtrl
	L_g5_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundEfxSetAux1(s32 chan, u8 reverb) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x14(r1)
	mulli r0, r3, 0x88
	stw r31, 0xc(r1)
	mr r31, r4
	addi r4, r5, sound@l
	lwz r3, 0xf4(r4)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_1
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_2
	L_g5_1:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_2:
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq L_g5_3
	mr r5, r31
	li r4, 0x5b
	bl sndFXCtrl
	L_g5_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm u8 SoundEfxGetVolume(s32 chan) {
	nofralloc
	mulli r3, r3, 0x88
	lis r4, sound@ha
	addi r4, r4, sound@l
	lwz r4, 0xf4(r4)
	addi r0, r3, 0x4
	lhzx r0, r4, r0
	clrlwi r3, r0, 24
	blr
}

asm void SoundEfxSetVolume(s32 chan, u8 vol) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x24(r1)
	mulli r0, r3, 0x88
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r4
	addi r4, r5, sound@l
	lwz r3, 0xf4(r4)
	add r30, r3, r0
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_1
	addi r3, r30, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	mr r31, r3
	b L_g5_2
	L_g5_1:
	lwz r3, 0xc(r30)
	bl sndFXCheck
	mr r31, r3
	L_g5_2:
	addis r0, r31, 0x1
	cmplwi r0, 0xffff
	beq L_g5_3
	clrlwi r0, r29, 24
	mr r3, r31
	sth r0, 0x4(r30)
	mr r5, r29
	li r4, 0x7
	bl sndFXCtrl
	lis r3, sound@ha
	addi r3, r3, sound@l
	lhz r0, 0x214(r3)
	cmplwi r0, 0x0
	beq L_g5_3
	mr r3, r31
	li r4, 0x7
	li r5, 0x0
	bl sndFXCtrl
	L_g5_3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void SoundEfxSetPitch(s32 chan, u16 pitch) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x14(r1)
	mulli r0, r3, 0x88
	stw r31, 0xc(r1)
	mr r31, r4
	addi r4, r5, sound@l
	lwz r3, 0xf4(r4)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_1
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_2
	L_g5_1:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_2:
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq L_g5_3
	addi r0, r31, 0x2000
	li r4, 0x80
	clrlwi r5, r0, 16
	bl sndFXCtrl14
	L_g5_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundEfxStop(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	addi r4, r4, sound@l
	mulli r0, r3, 0x88
	stw r31, 0xc(r1)
	lwz r3, 0xf4(r4)
	add r31, r3, r0
	lhz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq L_g5_1
	lwz r3, 0xc(r31)
	bl sndFXKeyOff
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_2
	addi r3, r31, 0x14
	bl sndRemoveEmitter
	L_g5_2:
	li r0, 0x0
	sth r0, 0x0(r31)
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 SoundEfxPlayEx(SND_FXID fid, u8 a2, u8 vol, u8 pan) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r7, sound@ha
	stw r0, 0x34(r1)
	li r0, 0x4
	stmw r24, 0x10(r1)
	addi r31, r7, sound@l
	mr r25, r3
	mr r26, r4
	mr r27, r5
	mr r28, r6
	li r29, 0x0
	lwz r7, 0xf4(r31)
	mr r30, r7
	mtctr r0
	L_g5_1:
	lhz r0, 0x0(r30)
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	lhzu r0, 0x88(r30)
	addi r29, r29, 0x1
	cmplwi r0, 0x0
	beq L_g5_2
	addi r29, r29, 0x1
	addi r30, r30, 0x88
	bdnz L_g5_1
	L_g5_2:
	cmplwi r29, 0x28
	blt L_g5_3
	li r0, 0x28
	mr r30, r7
	clrlwi r3, r26, 24
	li r29, 0x0
	mtctr r0
	L_g5_4:
	lhz r0, 0x2(r30)
	cmpw r0, r3
	bgt L_g5_5
	mulli r0, r29, 0x88
	add r24, r7, r0
	lhz r0, 0x0(r24)
	cmplwi r0, 0x0
	beq L_g5_6
	lwz r3, 0xc(r24)
	bl sndFXKeyOff
	lhz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_7
	addi r3, r24, 0x14
	bl sndRemoveEmitter
	L_g5_7:
	li r0, 0x0
	sth r0, 0x0(r24)
	b L_g5_6
	L_g5_5:
	addi r29, r29, 0x1
	addi r30, r30, 0x88
	bdnz L_g5_4
	L_g5_6:
	cmplwi r29, 0x28
	blt L_g5_3
	li r3, -0x1
	b L_g5_8
	L_g5_3:
	li r0, 0x0
	lis r3, sound@ha
	sth r0, 0x0(r30)
	addi r24, r3, sound@l
	lhz r0, 0x20c(r24)
	cmplwi r0, 0x0
	bne L_g5_9
	bl OSDisableInterrupts
	lis r4, sound@ha
	addi r4, r4, sound@l
	stw r3, 0x210(r4)
	L_g5_9:
	lhz r6, 0x20c(r24)
	mr r3, r25
	mr r5, r28
	li r4, 0x7f
	addi r0, r6, 0x1
	li r6, 0x0
	sth r0, 0x20c(r24)
	bl sndFXStartEx
	stw r3, 0xc(r30)
	mr r5, r27
	li r4, 0x7
	lwz r3, 0xc(r30)
	bl sndFXCtrl
	lhz r3, 0x20c(r24)
	cmplwi r3, 0x0
	beq L_g5_10
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r24)
	bne L_g5_10
	lis r3, sound@ha
	addi r3, r3, sound@l
	lwz r3, 0x210(r3)
	bl OSRestoreInterrupts
	L_g5_10:
	lwz r3, 0xc(r30)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne L_g5_11
	li r3, -0x1
	b L_g5_8
	L_g5_11:
	li r0, 0x1
	lis r3, sound@ha
	sth r0, 0x0(r30)
	clrlwi r0, r26, 24
	clrlwi r5, r27, 24
	clrlwi r4, r28, 24
	sth r0, 0x2(r30)
	li r0, 0x0
	addi r3, r3, sound@l
	sth r5, 0x4(r30)
	sth r4, 0x6(r30)
	sth r0, 0x8(r30)
	sth r25, 0x10(r30)
	lhz r0, 0x214(r3)
	cmplwi r0, 0x0
	beq L_g5_12
	lwz r3, 0xc(r30)
	li r4, 0x7
	li r5, 0x0
	bl sndFXCtrl
	L_g5_12:
	mulli r0, r29, 0x88
	lwz r3, 0xf4(r31)
	add r3, r3, r0
	lhz r0, 0x0(r3)
	cmplwi r0, 0x0
	bne L_g5_13
	li r0, 0x0
	b L_g5_14
	L_g5_13:
	rlwinm. r0, r0, 0, 27, 27
	bne L_g5_15
	beq L_g5_16
	addi r3, r3, 0x14
	bl sndEmitterVoiceID
	bl sndFXCheck
	b L_g5_17
	L_g5_16:
	lwz r3, 0xc(r3)
	bl sndFXCheck
	L_g5_17:
	bl sndFXCheck
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne L_g5_18
	li r0, 0x0
	b L_g5_14
	L_g5_15:
	addi r3, r3, 0x14
	bl sndCheckEmitter
	cmplwi r3, 0x0
	bne L_g5_18
	li r0, 0x0
	b L_g5_14
	L_g5_18:
	li r0, 0x1
	L_g5_14:
	cmplwi r0, 0x0
	bne L_g5_19
	li r29, -0x1
	L_g5_19:
	mr r3, r29
	L_g5_8:
	lmw r24, 0x10(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL SoundSongCheck(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	slwi r0, r3, 4
	addi r3, r4, sound@l
	lwz r3, 0xf0(r3)
	lwzx r3, r3, r0
	bl sndSeqGetValid
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm u8 SoundSongGetVolCh(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	slwi r0, r3, 4
	addi r3, r4, sound@l
	stw r31, 0xc(r1)
	lwz r3, 0xf0(r3)
	add r31, r3, r0
	lwz r3, 0x0(r31)
	bl sndSeqGetValid
	cmplwi r3, 0x0
	bne L_g5_1
	li r3, 0x0
	b L_g5_2
	L_g5_1:
	lwz r0, 0x4(r31)
	clrlwi r3, r0, 24
	L_g5_2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSongSetVolCh(s32 chan, u8 vol) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x14(r1)
	slwi r0, r3, 4
	addi r3, r5, sound@l
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r4
	lwz r3, 0xf0(r3)
	add r31, r3, r0
	lwz r3, 0x0(r31)
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_1
	clrlwi r0, r30, 24
	cmplwi r0, 0x7f
	ble L_g5_2
	li r30, 0x7f
	L_g5_2:
	clrlwi r0, r30, 24
	li r4, 0x0
	stw r0, 0x4(r31)
	li r6, 0x0
	lwz r0, 0x4(r31)
	lwz r5, 0x0(r31)
	clrlwi r3, r0, 24
	bl sndSeqVolume
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSongFadeinCh(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	slwi r0, r3, 4
	addi r3, r4, sound@l
	stw r31, 0xc(r1)
	lwz r3, 0xf0(r3)
	add r31, r3, r0
	lwz r3, 0x0(r31)
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_1
	lis r3, sound@ha
	lwz r0, 0x4(r31)
	addi r3, r3, sound@l
	lwz r5, 0x0(r31)
	lhz r4, 0x208(r3)
	clrlwi r3, r0, 24
	li r6, 0x0
	bl sndSeqVolume
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSongFadeoutCh(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	slwi r31, r3, 4
	addi r3, r4, sound@l
	stw r30, 0x8(r1)
	lwz r30, 0xf0(r3)
	lwzx r3, r30, r31
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_1
	lis r3, sound@ha
	lwzx r5, r30, r31
	addi r4, r3, sound@l
	li r3, 0x0
	lhz r4, 0x20a(r4)
	li r6, 0x1
	bl sndSeqVolume
	li r0, -0x1
	stwx r0, r30, r31
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSongStopCh(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	slwi r31, r3, 4
	addi r3, r4, sound@l
	stw r30, 0x8(r1)
	lwz r30, 0xf0(r3)
	lwzx r3, r30, r31
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_1
	lwzx r3, r30, r31
	bl sndSeqStop
	li r0, -0x1
	stwx r0, r30, r31
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSongContinueCh(s32 chan) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	slwi r0, r3, 4
	addi r3, r4, sound@l
	stw r31, 0xc(r1)
	lwz r3, 0xf0(r3)
	add r31, r3, r0
	lwz r3, 0x0(r31)
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_1
	lwz r3, 0x0(r31)
	bl sndSeqContinue
	lwz r0, 0x4(r31)
	li r4, 0x0
	lwz r5, 0x0(r31)
	li r6, 0x0
	clrlwi r3, r0, 24
	bl sndSeqVolume
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundSongPlayCh(s32 chan, u32 a2) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x14(r1)
	slwi r0, r3, 4
	addi r3, r5, sound@l
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r4
	lwz r3, 0xf0(r3)
	add r31, r3, r0
	lwz r3, 0x0(r31)
	bl sndSeqGetValid
	cmplwi r3, 0x1
	bne L_g5_1
	lwz r3, 0x0(r31)
	bl sndSeqStop
	L_g5_1:
	li r0, 0x7f
	lis r3, sound@ha
	stw r0, 0x4(r31)
	addi r3, r3, sound@l
	clrlwi r4, r30, 24
	lwz r5, 0xec(r3)
	L_g5_2:
	cmplwi r5, 0x0
	bne L_g5_3
	li r5, 0x0
	b L_g5_4
	L_g5_3:
	lhz r0, 0x2(r5)
	cmplw r0, r4
	beq L_g5_4
	lwz r5, 0xc(r5)
	b L_g5_2
	L_g5_4:
	cmplwi r5, 0x0
	beq L_g5_5
	stw r5, 0x8(r31)
	extrwi r4, r30, 8, 8
	extrwi r3, r30, 8, 16
	li r0, -0x1
	sth r4, 0x4(r5)
	li r6, 0x0
	li r7, 0x0
	sth r3, 0x6(r5)
	stw r0, 0xc(r31)
	lhz r3, 0x4(r5)
	lhz r4, 0x6(r5)
	lwz r5, 0x8(r5)
	bl sndSeqPlayEx
	stw r3, 0x0(r31)
	li r4, 0x0
	li r6, 0x0
	lwz r0, 0x4(r31)
	lwz r5, 0x0(r31)
	clrlwi r3, r0, 24
	bl sndSeqVolume
	lwz r3, 0x0(r31)
	bl sndSeqContinue
	lwz r3, 0x0(r31)
	li r5, 0x0
	lwz r4, 0xc(r31)
	bl sndSeqMute
	L_g5_5:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundCloseCover(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl sndIsInstalled
	cmplwi r3, 0x0
	beq L_g5_1
	lis r3, sound@ha
	addi r3, r3, sound@l
	lhz r0, 0x214(r3)
	cmplwi r0, 0x1
	bne L_g5_1
	lwz r4, 0x100(r3)
	li r6, 0x0
	lhz r5, 0x0(r4)
	rlwinm. r0, r5, 0, 28, 28
	beq L_g5_2
	rlwinm. r0, r5, 0, 21, 21
	bne L_g5_2
	rlwinm. r0, r5, 0, 30, 30
	bne L_g5_2
	rlwinm. r0, r5, 0, 19, 19
	beq L_g5_3
	li r6, 0x1
	L_g5_3:
	lhz r0, 0x1a(r4)
	cmplwi r0, 0x2
	bne L_g5_2
	rlwinm. r0, r5, 0, 18, 18
	beq L_g5_2
	li r6, 0x1
	L_g5_2:
	lhz r5, 0x138(r4)
	rlwinm. r0, r5, 0, 28, 28
	beq L_g5_4
	rlwinm. r0, r5, 0, 21, 21
	bne L_g5_4
	rlwinm. r0, r5, 0, 30, 30
	bne L_g5_4
	rlwinm. r0, r5, 0, 19, 19
	beq L_g5_5
	li r6, 0x1
	L_g5_5:
	lhz r0, 0x152(r4)
	cmplwi r0, 0x2
	bne L_g5_4
	rlwinm. r0, r5, 0, 18, 18
	beq L_g5_4
	li r6, 0x1
	L_g5_4:
	lhz r5, 0x270(r4)
	rlwinm. r0, r5, 0, 28, 28
	beq L_g5_6
	rlwinm. r0, r5, 0, 21, 21
	bne L_g5_6
	rlwinm. r0, r5, 0, 30, 30
	bne L_g5_6
	rlwinm. r0, r5, 0, 19, 19
	beq L_g5_7
	li r6, 0x1
	L_g5_7:
	lhz r0, 0x28a(r4)
	cmplwi r0, 0x2
	bne L_g5_6
	rlwinm. r0, r5, 0, 18, 18
	beq L_g5_6
	li r6, 0x1
	L_g5_6:
	cmpwi r6, 0x0
	beq L_g5_8
	li r0, 0x2
	sth r0, 0x214(r3)
	b L_g5_1
	L_g5_8:
	li r0, 0x0
	sth r0, 0x214(r3)
	L_g5_1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundOpenCover(void) {
	nofralloc
	lis r3, sound@ha
	addi r3, r3, sound@l
	lhz r0, 0x214(r3)
	cmplwi r0, 0x0
	bnelr
	li r0, 0x1
	sth r0, 0x214(r3)
	blr
}

asm void SoundSetOutputMode(SND_OUTPUTMODE mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	addi r4, r4, sound@l
	lwz r0, 0x218(r4)
	cmpw r0, r3
	beq L_g5_1
	stw r3, 0x218(r4)
	bl sndOutputMode
	L_g5_1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL SoundDropData(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r3, sound@ha
	stw r0, 0x34(r1)
	stmw r23, 0xc(r1)
	addi r28, r3, sound@l
	li r27, 0x0
	li r25, -0x1
	mr r29, r27
	lwz r24, 0xec(r28)
	L_g5_1:
	lwz r26, 0xf0(r28)
	lwzx r3, r26, r29
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_2
	lwzx r3, r26, r29
	bl sndSeqStop
	stwx r25, r26, r29
	L_g5_2:
	addi r27, r27, 0x1
	addi r29, r29, 0x10
	cmplwi r27, 0x4
	blt L_g5_1
	li r23, 0x0
	lis r3, sound@ha
	mr r27, r23
	mr r25, r23
	addi r29, r3, sound@l
	L_g5_3:
	lwz r0, 0xf4(r29)
	add r26, r0, r27
	lhz r0, 0x0(r26)
	cmplwi r0, 0x0
	beq L_g5_4
	lwz r3, 0xc(r26)
	bl sndFXKeyOff
	lhz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_5
	addi r3, r26, 0x14
	bl sndRemoveEmitter
	L_g5_5:
	sth r25, 0x0(r26)
	L_g5_4:
	addi r23, r23, 0x1
	addi r27, r27, 0x88
	cmplwi r23, 0x28
	blt L_g5_3
	li r23, 0x0
	lis r3, sound@ha
	mr r31, r23
	li r25, -0x1
	mr r26, r23
	addi r30, r3, sound@l
	L_g5_6:
	lwz r0, 0xf8(r30)
	add r27, r0, r31
	lhz r0, 0x0(r27)
	clrlwi. r0, r0, 30
	beq L_g5_7
	li r3, 0x0
	bl AISetStreamPlayState
	sth r26, 0x0(r27)
	addi r3, r27, 0x118
	stw r25, 0xfc(r30)
	bl DVDCancelStream
	addi r3, r27, 0x118
	bl DVDClose
	L_g5_7:
	addi r23, r23, 0x1
	addi r31, r31, 0x154
	cmplwi r23, 0x2
	blt L_g5_6
	li r25, 0x0
	lis r3, sound@ha
	mr r27, r25
	addi r31, r3, sound@l
	L_g5_8:
	lwz r0, 0x100(r31)
	add r26, r0, r27
	lhz r0, 0x0(r26)
	cmplwi r0, 0x0
	beq L_g5_9
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_10
	bl OSDisableInterrupts
	stw r3, 0x210(r31)
	L_g5_10:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lhz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_11
	lhz r4, 0x2(r26)
	lis r3, sound@ha
	addi r0, r3, sound@l
	li r5, 0x0
	slwi r3, r4, 1
	add r3, r0, r3
	sth r5, 0x226(r3)
	L_g5_11:
	li r0, 0x0
	sth r0, 0x0(r26)
	lwz r3, 0x28(r26)
	bl DVDMgrClose
	lwz r3, 0xb0(r26)
	bl DVDMgrClose
	lwz r3, 0x4c(r26)
	bl sndStreamFree
	lhz r0, 0x1a(r26)
	cmplwi r0, 0x2
	bne L_g5_12
	lwz r3, 0xd4(r26)
	bl sndStreamFree
	L_g5_12:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_13
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_13
	lwz r3, 0x210(r31)
	bl OSRestoreInterrupts
	L_g5_13:
	li r0, -0x1
	stw r0, 0x104(r31)
	L_g5_9:
	addi r25, r25, 0x1
	addi r27, r27, 0x138
	cmplwi r25, 0x3
	blt L_g5_8
	bl sndSilence
	li r23, 0x0
	li r27, 0x0
	li r25, -0x1
	L_g5_14:
	lwz r26, 0xf0(r28)
	lwzx r3, r26, r27
	bl sndSeqGetValid
	cmplwi r3, 0x0
	beq L_g5_15
	lwzx r3, r26, r27
	bl sndSeqStop
	stwx r25, r26, r27
	L_g5_15:
	addi r23, r23, 0x1
	addi r27, r27, 0x10
	cmplwi r23, 0x4
	blt L_g5_14
	li r23, 0x0
	mr r27, r23
	mr r25, r23
	L_g5_16:
	lwz r0, 0xf4(r29)
	add r26, r0, r27
	lhz r0, 0x0(r26)
	cmplwi r0, 0x0
	beq L_g5_17
	lwz r3, 0xc(r26)
	bl sndFXKeyOff
	lhz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_18
	addi r3, r26, 0x14
	bl sndRemoveEmitter
	L_g5_18:
	sth r25, 0x0(r26)
	L_g5_17:
	addi r23, r23, 0x1
	addi r27, r27, 0x88
	cmplwi r23, 0x28
	blt L_g5_16
	li r23, 0x0
	li r25, -0x1
	mr r29, r23
	mr r26, r23
	L_g5_19:
	lwz r0, 0xf8(r30)
	add r27, r0, r29
	lhz r0, 0x0(r27)
	clrlwi. r0, r0, 30
	beq L_g5_20
	li r3, 0x0
	bl AISetStreamPlayState
	sth r26, 0x0(r27)
	addi r3, r27, 0x118
	stw r25, 0xfc(r30)
	bl DVDCancelStream
	addi r3, r27, 0x118
	bl DVDClose
	L_g5_20:
	addi r23, r23, 0x1
	addi r29, r29, 0x154
	cmplwi r23, 0x2
	blt L_g5_19
	li r25, 0x0
	mr r27, r25
	L_g5_21:
	lwz r0, 0x100(r31)
	add r26, r0, r27
	lhz r0, 0x0(r26)
	cmplwi r0, 0x0
	beq L_g5_22
	lhz r0, 0x20c(r31)
	cmplwi r0, 0x0
	bne L_g5_23
	bl OSDisableInterrupts
	stw r3, 0x210(r31)
	L_g5_23:
	lhz r3, 0x20c(r31)
	addi r0, r3, 0x1
	sth r0, 0x20c(r31)
	lhz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 21, 21
	beq L_g5_24
	lhz r4, 0x2(r26)
	lis r3, sound@ha
	addi r0, r3, sound@l
	li r5, 0x0
	slwi r3, r4, 1
	add r3, r0, r3
	sth r5, 0x226(r3)
	L_g5_24:
	li r0, 0x0
	sth r0, 0x0(r26)
	lwz r3, 0x28(r26)
	bl DVDMgrClose
	lwz r3, 0xb0(r26)
	bl DVDMgrClose
	lwz r3, 0x4c(r26)
	bl sndStreamFree
	lhz r0, 0x1a(r26)
	cmplwi r0, 0x2
	bne L_g5_25
	lwz r3, 0xd4(r26)
	bl sndStreamFree
	L_g5_25:
	lhz r3, 0x20c(r31)
	cmplwi r3, 0x0
	beq L_g5_26
	subi r3, r3, 0x1
	clrlwi. r0, r3, 16
	sth r3, 0x20c(r31)
	bne L_g5_26
	lwz r3, 0x210(r31)
	bl OSRestoreInterrupts
	L_g5_26:
	li r0, -0x1
	stw r0, 0x104(r31)
	L_g5_22:
	addi r25, r25, 0x1
	addi r27, r27, 0x138
	cmplwi r25, 0x3
	blt L_g5_21
	lis r3, sound@ha
	li r23, 0x0
	addi r26, r3, sound@l
	mr r27, r26
	b L_g5_27
	L_g5_28:
	addi r25, r27, 0xc0
	b L_g5_29
	L_g5_30:
	bl sndPopGroup
	lwz r3, 0x0(r25)
	subi r0, r3, 0x1
	stw r0, 0x0(r25)
	L_g5_29:
	lwz r0, 0x0(r25)
	cmplwi r0, 0x0
	bne L_g5_30
	addi r27, r27, 0x4
	addi r23, r23, 0x1
	L_g5_27:
	lwz r0, 0xe0(r26)
	cmplw r23, r0
	blt L_g5_28
	mr r25, r26
	li r23, 0x0
	b L_g5_31
	L_g5_32:
	lwz r4, 0x0(r25)
	li r3, 0x0
	bl __memFree
	addi r25, r25, 0x4
	addi r23, r23, 0x1
	L_g5_31:
	lwz r0, 0xe0(r26)
	cmplw r23, r0
	blt L_g5_32
	mr r25, r26
	li r23, 0x0
	b L_g5_33
	L_g5_34:
	lwz r4, 0x20(r25)
	li r3, 0x0
	bl __memFree
	addi r25, r25, 0x4
	addi r23, r23, 0x1
	L_g5_33:
	lwz r0, 0xe0(r26)
	cmplw r23, r0
	blt L_g5_34
	mr r25, r26
	li r23, 0x0
	b L_g5_35
	L_g5_36:
	lwz r4, 0x40(r25)
	li r3, 0x0
	bl __memFree
	addi r25, r25, 0x4
	addi r23, r23, 0x1
	L_g5_35:
	lwz r0, 0xe0(r26)
	cmplw r23, r0
	blt L_g5_36
	lis r3, sound@ha
	mr r27, r26
	addi r25, r3, sound@l
	li r23, 0x0
	b L_g5_37
	L_g5_38:
	lwz r4, 0x60(r27)
	li r3, 0x0
	bl __memFree
	lwz r4, 0x80(r27)
	li r3, 0x0
	bl __memFree
	lwz r4, 0xa0(r27)
	li r3, 0x0
	bl __memFree
	addi r27, r27, 0x4
	addi r23, r23, 0x1
	L_g5_37:
	lwz r0, 0xe4(r25)
	cmplw r23, r0
	blt L_g5_38
	lis r3, sound@ha
	li r0, 0x0
	addi r3, r3, sound@l
	stw r0, 0xe0(r26)
	stw r0, 0xe4(r25)
	stw r0, 0xe8(r3)
	L_g5_39:
	cmplwi r24, 0x0
	beq L_g5_40
	lhz r0, 0x0(r24)
	lwz r23, 0xc(r24)
	clrlwi. r0, r0, 31
	bne L_g5_41
	lwz r4, 0x8(r24)
	li r3, 0x0
	bl __memFree
	L_g5_41:
	mr r4, r24
	li r3, 0x0
	bl __memFree
	mr r24, r23
	b L_g5_39
	L_g5_40:
	li r0, 0x0
	li r3, 0x1
	stw r0, 0xec(r28)
	lmw r23, 0xc(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL SoundSLibLoadDVD(const char* path) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	addi r31, r4, sound@l
	mr r30, r3
	lwz r0, 0xe4(r31)
	cmplwi r0, 0x8
	blt L_g5_1
	li r3, 0x0
	b L_g5_2
	L_g5_1:
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B6FC(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x2
	addi r3, r3, g5_str_s436@l
	li r5, 0x0
	bl DVDMgrOpen
	mr. r27, r3
	bne L_g5_3
	li r28, 0x0
	b L_g5_4
	L_g5_3:
	bl DVDMgrGetLength
	cmplwi r3, 0x0
	bne L_g5_5
	li r28, 0x0
	b L_g5_4
	L_g5_5:
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r29, r0, 5
	mr r4, r29
	bl __memAlloc
	mr. r28, r3
	bne L_g5_6
	li r28, 0x0
	b L_g5_4
	L_g5_6:
	mr r3, r27
	mr r4, r28
	mr r5, r29
	li r6, 0x0
	bl DVDMgrRead
	cmpwi r3, 0x0
	bgt L_g5_7
	mr r4, r28
	li r3, 0x0
	bl __memFree
	li r28, 0x0
	b L_g5_4
	L_g5_7:
	mr r3, r27
	bl DVDMgrClose
	L_g5_4:
	cmplwi r28, 0x0
	mr r27, r28
	bne L_g5_8
	li r3, 0x0
	b L_g5_2
	L_g5_8:
	lwz r0, 0xe4(r31)
	lis r3, sound@ha
	addi r29, r3, sound@l
	slwi r0, r0, 2
	add r3, r29, r0
	stw r28, 0x60(r3)
	L_g5_9:
	lwz r28, 0x0(r27)
	addis r0, r28, 0x1
	cmplwi r0, 0xffff
	beq L_g5_10
	li r3, 0x0
	li r4, 0x10
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_11
	L_g5_12:
	b L_g5_12
	L_g5_11:
	lwz r0, 0xec(r29)
	li r5, 0x0
	cmplwi r0, 0x0
	bne L_g5_13
	stw r3, 0xec(r29)
	b L_g5_14
	L_g5_13:
	mr r4, r0
	L_g5_15:
	lwz r0, 0xc(r4)
	addi r5, r5, 0x1
	cmplwi r0, 0x0
	beq L_g5_16
	mr r4, r0
	b L_g5_15
	L_g5_16:
	stw r3, 0xc(r4)
	L_g5_14:
	li r4, 0x1
	addi r0, r27, 0x20
	sth r4, 0x0(r3)
	li r4, 0x0
	add r27, r27, r28
	sth r5, 0x2(r3)
	sth r4, 0x4(r3)
	sth r4, 0x6(r3)
	stw r0, 0x8(r3)
	stw r4, 0xc(r3)
	b L_g5_9
	L_g5_10:
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B704(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x2
	addi r3, r3, g5_str_s436@l
	li r5, 0x0
	bl DVDMgrOpen
	mr. r29, r3
	bne L_g5_17
	li r27, 0x0
	b L_g5_18
	L_g5_17:
	bl DVDMgrGetLength
	cmplwi r3, 0x0
	bne L_g5_19
	li r27, 0x0
	b L_g5_18
	L_g5_19:
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r28, r0, 5
	mr r4, r28
	bl __memAlloc
	mr. r27, r3
	bne L_g5_20
	li r27, 0x0
	b L_g5_18
	L_g5_20:
	mr r3, r29
	mr r4, r27
	mr r5, r28
	li r6, 0x0
	bl DVDMgrRead
	cmpwi r3, 0x0
	bgt L_g5_21
	mr r4, r27
	li r3, 0x0
	bl __memFree
	li r27, 0x0
	b L_g5_18
	L_g5_21:
	mr r3, r29
	bl DVDMgrClose
	L_g5_18:
	cmplwi r27, 0x0
	bne L_g5_22
	li r3, 0x0
	b L_g5_2
	L_g5_22:
	lwz r0, 0xe4(r31)
	lis r3, sound@ha
	addi r3, r3, sound@l
	slwi r0, r0, 2
	add r3, r3, r0
	stw r27, 0x80(r3)
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B70C(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x2
	addi r3, r3, g5_str_s436@l
	li r5, 0x0
	bl DVDMgrOpen
	mr. r29, r3
	bne L_g5_23
	li r27, 0x0
	b L_g5_24
	L_g5_23:
	bl DVDMgrGetLength
	cmplwi r3, 0x0
	bne L_g5_25
	li r27, 0x0
	b L_g5_24
	L_g5_25:
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r28, r0, 5
	mr r4, r28
	bl __memAlloc
	mr. r27, r3
	bne L_g5_26
	li r27, 0x0
	b L_g5_24
	L_g5_26:
	mr r3, r29
	mr r4, r27
	mr r5, r28
	li r6, 0x0
	bl DVDMgrRead
	cmpwi r3, 0x0
	bgt L_g5_27
	mr r4, r27
	li r3, 0x0
	bl __memFree
	li r27, 0x0
	b L_g5_24
	L_g5_27:
	mr r3, r29
	bl DVDMgrClose
	L_g5_24:
	cmplwi r27, 0x0
	bne L_g5_28
	li r3, 0x0
	b L_g5_2
	L_g5_28:
	lwz r0, 0xe4(r31)
	lis r3, sound@ha
	addi r4, r3, sound@l
	li r3, 0x1
	slwi r0, r0, 2
	add r4, r4, r0
	stw r27, 0xa0(r4)
	lwz r4, 0xe4(r31)
	addi r0, r4, 0x1
	stw r0, 0xe4(r31)
	L_g5_2:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void SoundLoadDVD2Free(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, sound@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	addi r31, r3, sound@l
	lwz r4, 0x32c(r31)
	cmplwi r4, 0x0
	beq L_g5_1
	li r3, 0x0
	bl __memFree
	li r0, 0x0
	stw r0, 0x32c(r31)
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL SoundLoadDVD2PushGroup(u8* groupIds) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	addi r31, r4, sound@l
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r0, 0xe0(r31)
	cmplwi r0, 0x8
	blt L_g5_1
	li r3, 0x0
	b L_g5_2
	L_g5_1:
	slwi r0, r0, 2
	cmplwi r30, 0x0
	add r3, r31, r0
	li r0, 0x0
	stw r0, 0xc0(r3)
	beq L_g5_3
	b L_g5_4
	L_g5_5:
	lwz r0, 0xe0(r31)
	li r5, 0x0
	slwi r0, r0, 2
	add r7, r31, r0
	lwz r3, 0x20(r7)
	lwz r6, 0x40(r7)
	lwz r7, 0x0(r7)
	bl sndPushGroup
	lwz r0, 0xe0(r31)
	addi r30, r30, 0x1
	slwi r0, r0, 2
	add r4, r31, r0
	lwz r3, 0xc0(r4)
	addi r0, r3, 0x1
	stw r0, 0xc0(r4)
	L_g5_4:
	lbz r4, 0x0(r30)
	cmplwi r4, 0xff
	bne L_g5_5
	b L_g5_6
	L_g5_3:
	lwz r30, 0xe8(r31)
	b L_g5_7
	L_g5_8:
	lwz r0, 0xe0(r31)
	clrlwi r4, r30, 16
	li r5, 0x0
	slwi r0, r0, 2
	add r7, r31, r0
	lwz r3, 0x20(r7)
	lwz r6, 0x40(r7)
	lwz r7, 0x0(r7)
	bl sndPushGroup
	cmplwi r3, 0x1
	bne L_g5_6
	lwz r0, 0xe0(r31)
	addi r30, r30, 0x1
	slwi r0, r0, 2
	add r4, r31, r0
	lwz r3, 0xc0(r4)
	addi r0, r3, 0x1
	stw r0, 0xc0(r4)
	lwz r3, 0xe8(r31)
	addi r0, r3, 0x1
	stw r0, 0xe8(r31)
	L_g5_7:
	cmpwi r30, 0xff
	blt L_g5_8
	L_g5_6:
	li r3, 0x1
	L_g5_2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL SoundLoadDVD2(const char* path) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, sound@ha
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	addi r31, r4, sound@l
	mr r30, r3
	lwz r0, 0xe0(r31)
	cmplwi r0, 0x8
	blt L_g5_1
	li r3, 0x0
	b L_g5_2
	L_g5_1:
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B714(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x2
	addi r3, r3, g5_str_s436@l
	li r5, 0x0
	bl DVDMgrOpen
	mr. r27, r3
	bne L_g5_3
	li r29, 0x0
	b L_g5_4
	L_g5_3:
	bl DVDMgrGetLength
	cmplwi r3, 0x0
	bne L_g5_5
	li r29, 0x0
	b L_g5_4
	L_g5_5:
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r28, r0, 5
	mr r4, r28
	bl __memAlloc
	mr. r29, r3
	bne L_g5_6
	li r29, 0x0
	b L_g5_4
	L_g5_6:
	mr r3, r27
	mr r4, r29
	mr r5, r28
	li r6, 0x0
	bl DVDMgrRead
	cmpwi r3, 0x0
	bgt L_g5_7
	mr r4, r29
	li r3, 0x0
	bl __memFree
	li r29, 0x0
	b L_g5_4
	L_g5_7:
	mr r3, r27
	bl DVDMgrClose
	L_g5_4:
	cmplwi r29, 0x0
	bne L_g5_8
	li r3, 0x0
	b L_g5_2
	L_g5_8:
	lwz r0, 0xe0(r31)
	lis r3, sound@ha
	addi r3, r3, sound@l
	slwi r0, r0, 2
	stwx r29, r3, r0
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B71C(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x2
	addi r3, r3, g5_str_s436@l
	li r5, 0x0
	bl DVDMgrOpen
	mr. r29, r3
	bne L_g5_9
	li r27, 0x0
	b L_g5_10
	L_g5_9:
	bl DVDMgrGetLength
	cmplwi r3, 0x0
	bne L_g5_11
	li r27, 0x0
	b L_g5_10
	L_g5_11:
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r28, r0, 5
	mr r4, r28
	bl __memAlloc
	mr. r27, r3
	bne L_g5_12
	li r27, 0x0
	b L_g5_10
	L_g5_12:
	mr r3, r29
	mr r4, r27
	mr r5, r28
	li r6, 0x0
	bl DVDMgrRead
	cmpwi r3, 0x0
	bgt L_g5_13
	mr r4, r27
	li r3, 0x0
	bl __memFree
	li r27, 0x0
	b L_g5_10
	L_g5_13:
	mr r3, r29
	bl DVDMgrClose
	L_g5_10:
	cmplwi r27, 0x0
	bne L_g5_14
	li r3, 0x0
	b L_g5_2
	L_g5_14:
	lwz r0, 0xe0(r31)
	lis r3, sound@ha
	addi r3, r3, sound@l
	slwi r0, r0, 2
	add r3, r3, r0
	stw r27, 0x20(r3)
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B724(r2)
	crclr 6
	bl sprintf
	lis r3, g5_str_s436@ha
	li r4, 0x2
	addi r3, r3, g5_str_s436@l
	li r5, 0x0
	bl DVDMgrOpen
	mr. r29, r3
	bne L_g5_15
	li r27, 0x0
	b L_g5_16
	L_g5_15:
	bl DVDMgrGetLength
	cmplwi r3, 0x0
	bne L_g5_17
	li r27, 0x0
	b L_g5_16
	L_g5_17:
	addi r0, r3, 0x1f
	li r3, 0x0
	clrrwi r28, r0, 5
	mr r4, r28
	bl __memAlloc
	mr. r27, r3
	bne L_g5_18
	li r27, 0x0
	b L_g5_16
	L_g5_18:
	mr r3, r29
	mr r4, r27
	mr r5, r28
	li r6, 0x0
	bl DVDMgrRead
	cmpwi r3, 0x0
	bgt L_g5_19
	mr r4, r27
	li r3, 0x0
	bl __memFree
	li r27, 0x0
	b L_g5_16
	L_g5_19:
	mr r3, r29
	bl DVDMgrClose
	L_g5_16:
	cmplwi r27, 0x0
	bne L_g5_20
	li r3, 0x0
	b L_g5_2
	L_g5_20:
	lwz r0, 0xe0(r31)
	lis r3, sound@ha
	addi r3, r3, sound@l
	slwi r0, r0, 2
	add r3, r3, r0
	stw r27, 0x40(r3)
	bl getMarioStDvdRoot
	lis r4, str_802E5728@ha
	lis r7, g5_str_s436@ha
	mr r5, r3
	mr r6, r30
	addi r3, r7, g5_str_s436@l
	addi r4, r4, str_802E5728@l
	la r7, str_8041B72C(r2)
	crclr 6
	bl sprintf
	lis r4, sound@ha
	lis r3, g5_str_s436@ha
	addi r5, r4, sound@l
	addi r4, r3, g5_str_s436@l
	addi r3, r5, 0x22a
	bl strcpy
	lis r3, loadDVD_callback@ha
	lis r4, 0x2
	addi r3, r3, loadDVD_callback@l
	bl sndSetSampleDataUploadCallback
	li r3, 0x1
	L_g5_2:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void* loadDVD_callback(u32 offset, u32 bytes) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r5, sound@ha
	stw r0, 0x54(r1)
	stw r31, 0x4c(r1)
	mr r31, r4
	addi r4, r5, sound@l
	stw r30, 0x48(r1)
	mr r30, r3
	addi r3, r4, 0x22a
	addi r4, r1, 0x8
	bl DVDOpen
	cmpwi r3, 0x0
	bne L_g5_1
	li r3, 0x0
	b L_g5_2
	L_g5_1:
	lis r3, sound@ha
	mr r5, r31
	addi r31, r3, sound@l
	mr r6, r30
	lwz r4, 0x32c(r31)
	addi r3, r1, 0x8
	li r7, 0x2
	bl DVDReadPrio
	cmpwi r3, 0x0
	bgt L_g5_3
	li r3, 0x0
	b L_g5_2
	L_g5_3:
	addi r3, r1, 0x8
	bl DVDClose
	lwz r3, 0x32c(r31)
	L_g5_2:
	lwz r0, 0x54(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void SoundSetFadeTime(u16 in, u16 out) {
	nofralloc
	lis r5, sound@ha
	addi r5, r5, sound@l
	sth r3, 0x208(r5)
	sth r4, 0x20a(r5)
	blr
}

asm void SoundMainInt(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl SoundSSMainInt
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void SoundMain(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, sound@ha
	stw r0, 0x24(r1)
	addi r3, r3, sound@l
	stw r31, 0x1c(r1)
	li r31, -0x1
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	lwz r29, 0xf0(r3)
	L_g5_1:
	lwz r0, 0x8(r29)
	cmplwi r0, 0x0
	beq L_g5_2
	lwz r3, 0x0(r29)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq L_g5_2
	bl sndSeqGetValid
	cmplwi r3, 0x1
	beq L_g5_2
	lwz r3, 0x8(r29)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x2
	sth r0, 0x0(r3)
	lwz r3, 0x0(r29)
	bl sndSeqStop
	stw r31, 0x0(r29)
	L_g5_2:
	addi r30, r30, 0x1
	addi r29, r29, 0x10
	cmpwi r30, 0x4
	blt L_g5_1
	bl SoundEfxMain
	bl SoundDVDMain
	bl SoundSSMain
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

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
	beq L_g5_1
	li r0, 0x1
	li r3, 0x1
	stw r0, 0x218(r4)
	bl sndOutputMode
	L_g5_1:
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
	bne L_g5_2
	L_g5_3:
	b L_g5_3
	L_g5_2:
	li r0, 0x0
	li r3, 0x0
	stw r0, 0xec(r4)
	li r4, 0x40
	bl __memAlloc
	mr. r6, r3
	addi r4, r31, 0x100
	stw r6, 0xf0(r4)
	bne L_g5_4
	L_g5_5:
	b L_g5_5
	L_g5_4:
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
	bne L_g5_6
	L_g5_7:
	b L_g5_7
	L_g5_6:
	li r0, 0x4
	li r7, 0x0
	li r6, -0x1
	li r5, 0x7f
	li r4, 0x40
	mtctr r0
	L_g5_8:
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
	bdnz L_g5_8
	li r3, 0x0
	li r4, 0x2a8
	bl __memAlloc
	mr. r5, r3
	addi r4, r31, 0x100
	stw r5, 0xf8(r4)
	bne L_g5_9
	L_g5_10:
	b L_g5_10
	L_g5_9:
	li r0, 0x0
	li r3, 0x0
	sth r0, 0x0(r5)
	li r4, 0x3a8
	sth r0, 0x154(r5)
	bl __memAlloc
	addi r4, r31, 0x100
	cmplwi r3, 0x0
	stw r3, 0x100(r4)
	bne L_g5_11
	L_g5_12:
	b L_g5_12
	L_g5_11:
	mr r28, r3
	li r29, 0x0
	lis r30, 0x1
	L_g5_13:
	li r0, 0x0
	addi r4, r30, -0x8000
	sth r0, 0x0(r28)
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_14
	L_g5_15:
	b L_g5_15
	L_g5_14:
	stw r3, 0x54(r28)
	addi r4, r30, -0x8000
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_16
	L_g5_17:
	b L_g5_17
	L_g5_16:
	stw r3, 0x58(r28)
	li r3, 0xe00
	li r4, 0x0
	bl sndStreamAllocLength
	mr r0, r3
	li r3, 0x0
	mr r4, r0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_18
	L_g5_19:
	b L_g5_19
	L_g5_18:
	stw r3, 0x50(r28)
	addi r4, r30, -0x8000
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_20
	L_g5_21:
	b L_g5_21
	L_g5_20:
	stw r3, 0xdc(r28)
	addi r4, r30, -0x8000
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_22
	L_g5_23:
	b L_g5_23
	L_g5_22:
	stw r3, 0xe0(r28)
	li r3, 0xe00
	li r4, 0x0
	bl sndStreamAllocLength
	mr r4, r3
	li r3, 0x0
	bl __memAlloc
	cmplwi r3, 0x0
	bne L_g5_24
	L_g5_25:
	b L_g5_25
	L_g5_24:
	addi r29, r29, 0x1
	stw r3, 0xd8(r28)
	cmpwi r29, 0x3
	addi r28, r28, 0x138
	blt L_g5_13
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

asm void sndFree(void* ptr) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r4, r3
	li r3, 0x0
	stw r0, 0x14(r1)
	bl __memFree
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void* sndMalloc(size_t size) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r4, r3
	li r3, 0x0
	stw r0, 0x14(r1)
	bl __memAlloc
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8041B74C_sdata2[1] = {0};
