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

// TODO: use SoundInit to fill in SoundStream/Entry

extern int sprintf(char* str, const char* format, ...);

//.bss
SND_AUX_REVERBHI revH;
SND_AUX_REVERBSTD revS;
SND_AUX_CHORUS cho;
SND_AUX_DELAY dly;
SoundWork sound;
static char str[0x100];

//.sbss
u32 aramMemArray[8];

// local prototypes
void* sndMalloc(size_t size);
void sndFree(void* ptr);
void* loadDVD_callback(u32 offset, u32 length);
void SoundEfxMain(void);
void SoundDVDMain(void);

void SoundSSMainInt(void);
void SoundSSMain(void);

void SoundAIDMACallback(void);

void* sndMalloc(size_t size) {
    return __memAlloc(HEAP_DEFAULT, size);
}

void sndFree(void* ptr) {
    __memFree(HEAP_DEFAULT, ptr);
}

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
    tempdvd = (sound.dvds = sndMalloc((sizeof(SoundDVD)) * 2));
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

void SoundMainInt(void) {
    SoundSSMainInt();
}

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
    DVDEntry* entry;
    SoundGroup* temp_r0;
    SoundGroup* iter;
    SoundGroup* group;
    SoundGroup* var_r4;
    u32 temp_r28;
    u32* var_r27;
    u16 id;
    u32 length;
    void* temp_r0_3;
    void* pointer;

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
    var_r27 = pointer;
    if (pointer == NULL) {
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
        temp_r0_3 = var_r27 + 8;
        group->flags = 1;
        var_r27 = (u32*)((u32)var_r27 + (u32)temp_r28);
        group->unk2 = id;
        group->groupId = 0;
        group->songId = 0;
        group->arrfile = temp_r0_3;
        group->next = 0;
    }

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".stbl");
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
    sound.stblData[sound.slibId] = pointer;

    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), path, ".etbl");
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
    sound.etblData[sound.slibId] = pointer;
    sound.slibId++;
    return TRUE;
}

BOOL SoundDropData(void) {
    SoundSong* song;
    SoundEffect* effect;
    SoundDVD* dvd;
    SoundStream* stream;
    SoundGroup *group, *temp;
    u32 i, *j;

    group = sound.groups;
    for (i = 0; i < 4; i++) {
        song = &sound.songs[i];
        if (sndSeqGetValid(song->seqId)) {
            sndSeqStop(song->seqId);
            song->seqId = (SND_SEQID)-1;
        }
    }
    for (i = 0; i < 40; i++) {
        effect = &sound.effects[i];
        if (effect->flags) {
            sndFXKeyOff(effect->voiceId);
            if (effect->flags & 0x10) {
                sndRemoveEmitter(&effect->emitter);
            }
            effect->flags = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        dvd = &sound.dvds[i];
        if (dvd->flags & 3) {
            AISetStreamPlayState(0);
            dvd->flags = 0;
            sound.unkFC = -1;
            DVDCancelStream(&dvd->info.cb);
            DVDClose(&dvd->info);
        }
    }

    for (i = 0; i < 3; i++) {
        stream = &sound.streams[i];
        if (stream->flags) {
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

    sndSilence();

    for (i = 0; i < 4; i++) {
        song = &sound.songs[i];
        if (sndSeqGetValid(song->seqId)) {
            sndSeqStop(song->seqId);
            song->seqId = (SND_SEQID)-1;
        }
    }
    for (i = 0; i < 40; i++) {
        effect = &sound.effects[i];
        if (effect->flags) {
            sndFXKeyOff(effect->voiceId);
            if (effect->flags & 0x10) {
                sndRemoveEmitter(&effect->emitter);
            }
            effect->flags = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        dvd = &sound.dvds[i];
        if (dvd->flags & 3) {
            AISetStreamPlayState(0);
            dvd->flags = 0;
            sound.unkFC = -1;
            DVDCancelStream(&dvd->info.cb);
            DVDClose(&dvd->info);
        }
    }

    for (i = 0; i < 3; i++) {
        stream = &sound.streams[i];
        if (stream->flags) {
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

    for (i = 0; i < sound.dataId; i++) {
        for (j = sound.groupCount; *j;) {
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
        stream = sound.streams;
        for (i = 0; i < 3; i++, stream++) {
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
    SoundEffect* sfx = sound.effects;
    s32 chan = 0;

    for (chan = 0; chan < 40; chan++, sfx++) {
        if (sfx->unk2 <= a1) {
            SoundEfxMuteCh(chan);
            break;
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

s32 SoundEfxPlayEx(SND_FXID fid, u8 a2, u8 vol, u8 pan) {
    SoundEffect* sfx;
    s32 chan;

    sfx = sound.effects;
    for (chan = 0; chan < 40; chan++, sfx++) {
        if (!sfx->flags) {
            break;
        }
    }
    if (chan >= 40u && SoundEfxStopAll(a2) >= 40u) {
        return -1;
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

void SoundEfxMain(void) {
    SoundEffect* effect;
    f32 x, y, z;
    f32 v6, v9, v10;
    int i;

    x = sound.prevPos.x;
    y = sound.prevPos.y;
    z = sound.prevPos.z;
    v6 = ((TWO_PI * sound.unk1F4) / 360.0f);
    sound.prevPos.x = sound.pos.x;
    sound.prevPos.y = sound.pos.y;
    sound.prevPos.z = sound.pos.z;
    sound.dir.x = sound.pos.x - x;
    sound.dir.y = sound.pos.y - y;
    sound.dir.z = sound.pos.z - z;
    v9 = ((1.0f * (f32)sin(v6)) + 0.0f);
    v10 = (f32)cos(v6);
    sound.heading.x = v9;
    sound.heading.y = 0.0f;
    sound.heading.z = -((1.0f * v10) - 0.0f);
    sound.up.x = 0.0f;
    sound.up.y = 1.0f;
    sound.up.z = 0.0f;
    sndUpdateListener(&sound.listener, &sound.pos, &sound.dir, &sound.heading, &sound.up, (u8)sound.listenerVol, NULL);

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

    effect = sound.effects;
    for (i = 0; i < 40; i++, effect++) {
        if (effect->flags) {
            if (!(effect->flags & 0x10)) {
                SoundEfxCheckCh(i);
            } else {
                if (!sndCheckEmitter(&effect->emitter)) {
                    SoundEfxMuteCh(i);
                }
                if (effect->unkA) {
                    effect->unkA--;
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
    SoundDVD* dvd;
    f32 left, right;

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
    SoundDVD* dvd;
    int i;

    for (i = 0; i < 2; i++) {
        dvd = &sound.dvds[i];
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
    u32 len;
    u32 aligned;
    u32 extra;
    u32 addr;
    int i;

    entry = &stream->entries[ch];
    extra = 0;
    if (ch) {
        extra = entry->size + (0x20 - (entry->size % 0x20));
    }
    len = 0x8000;
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
    SoundStream* stream;
    SoundStreamEntry* entry;
    int ch;
    int i;

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
        stream = &sound.streams[i];
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

void cache_flush(u32 pointerToARQRequest) {
    _ssDVDReadAsync_activeChk(0, &((SoundStreamEntry*)((ARQRequest*)pointerToARQRequest)->owner)->dvd->info);
}

void _ssDVDReadAsync_cache_aram(u32 pointerToARQRequest) {
    SoundStream* stream;
    u32 len;

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

void _ssDVDReadAsync_cache_next(s32 result, DVDFileInfo* fileInfo) {
    static u32 owner_no;
    SoundStream* stream;
    u32 dest;
    int i;

    stream = sound.streams;
    for (i = 0; i < 3; i++, stream++) {
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

s16 dtbl[16] = {0x0001, 0x0007, 0x0018, 0x003B, 0x0053, 0x006F, 0x00EC, 0x022B,
                0x02E6, 0x0375, 0x041C, 0x08AD, 0x0CD5, 0x1150, 0x1B32, 0x2454};

u8* ssDecodeDPCM(SoundStream* stream, SoundStreamEntry* entry, s16* out, u32 count, u8* src) {
    s8 delta;
    u32 b;
    u32 scale;
    s32 sample;

    while (count != 0) {
        b = *src;
        if (entry->runCount != 0) {
            delta = (b >> 4) & 0xF;
            if (entry->nibble & 1) {
                delta = b & 0xF;
            }
            scale = entry->scale;
            entry->nibble++;
            delta <<= 4;
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
            delta = b & 0xF;
            if (delta == 8) {
                entry->runCount = ((b >> 4) & 0xF) + 4;
                entry->nibble = 0;
                continue;
            }
            scale = (b >> 4) & 0xF;
            entry->scale = scale;
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

u32 _sscallback(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user) {
    SoundStream* stream;
    SoundStreamEntry* entry;
    s16* dst;
    s16* src16;
    u8* dst8;
    u8* src8;
    u32 i;
    u32 n;

    stream = &sound.streams[(u8)user];
    stream->samplePos = 0;
    if ((stream->flags & 0x8006) || sound.unk214) {
        if (!(stream->flags & 0x100)) {
            dst = buffer1;
            for (i = len1; i != 0; i--) {
                *dst++ = 0;
                stream->samplePos++;
            }
            dst = buffer2;
            for (i = len2; i != 0; i--) {
                *dst++ = 0;
                stream->samplePos++;
            }
            return stream->samplePos;
        } else {
            dst = buffer1;
            for (i = 0; i < (s32)(len1 / 14 * 8) / 2; i++) {
                *dst++ = 0;
            }
            dst = buffer2;
            for (i = 0; i < (s32)(len2 / 14 * 8) / 2; i++) {
                *dst++ = 0;
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
        src8 = ssDecodeDPCM(stream, entry, buffer1, len1, entry->loadBuffer[entry->curBuf] + entry->srcPos);
        ssDecodeDPCM(stream, entry, buffer2, len2, src8);
    } else if (stream->flags & 0x100) {
        dst8 = buffer1;
        src8 = entry->loadBuffer[entry->curBuf] + entry->srcPos;
        n = (len1 + 13) / 14 * 8;
        while (n != 0) {
            *dst8++ = *src8++;
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
        n = (len2 + 13) / 14 * 8;
        while (n != 0) {
            *dst8++ = *src8++;
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
        dst = buffer1;
        src16 = (s16*)(entry->loadBuffer[entry->curBuf] + (entry->srcPos & ~1));
        n = len1;
        while (n != 0) {
            *dst++ = *src16++;
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
        dst = buffer2;
        n = len2;
        while (n != 0) {
            *dst++ = *src16++;
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

void SoundSSPlayCh(s32 chan, const char* name) {
    SoundSSPlayChEx(chan, name, 0);
}

void SoundSSPlayChEx(s32 chan, const char* name, s32 aram) {
    SoundStream* stream;
    char* path;
    int i;

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
    sprintf(str, "%s/%s%s", getMarioStDvdRoot(), name, ".stm");
    path = str;
    if (!(stream->entries[0].dvd = DVDMgrOpen(path, 0, 0))) {
        stream->flags = 0;
        return;
    }
    if (!(stream->entries[1].dvd = DVDMgrOpen(path, 0, 0))) {
        stream->flags = 0;
        return;
    }
    DVDMgrReadAsync(stream->entries[0].dvd, stream->entries[0].buffer, 0x100, 0, SoundSSPlayChEx_main);
}

void SoundSSPlayChEx_main(s32 result, DVDFileInfo* fileInfo) {
    SoundStream* stream;
    StreamHeader* header;
    u8* src;
    u8* dst;
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
        type = header->field_0x0;
        stream->freq = header->freq;
        stream->count = header->count;
        stream->loopEnd = header->field_0x8;
        stream->loopStart = header->field_0xC;
        stream->entries[0].size = header->field_0x10;
        stream->entries[1].size = header->field_0x14;
        stream->entries[0].loopStart = header->field_0x18;
        stream->entries[1].loopStart = header->field_0x1C;
        stream->entries[0].initHist = header->field_0x20;
        stream->entries[1].initHist = header->field_0x22;
        stream->entries[0].loopHist = header->field_0x24;
        stream->entries[1].loopHist = header->field_0x26;
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
                    src = (u8*)header + 0xBC;
                    dst = (u8*)&stream->entries[1].info;
                    for (j = 32; j != 0; j--) {
                        *dst++ = *src++;
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
        memset(stream->entries[0].buffer, 0, size);
        if (stream->count == 2) {
            memset(stream->entries[1].buffer, 0, size);
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
            size = 0x8000;
            if (stream->entries[0].offset + 0x8000 >= len) {
                size = len - stream->entries[0].offset;
            }
            DVDMgrReadAsync(stream->entries[0].dvd, stream->entries[0].loadBuffer[0], (size + 0x1F) & ~0x1F,
                            stream->entries[0].offset, _ssDVDReadAsync_cache_next);
            stream->entries[0].requestLength = size;
        }
    }
}

void SoundSSStopCh(s32 chan) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
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

void SoundSSContinueCh(s32 chan) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->flags &= ~2;
        stream->fadeStep = stream->vol;
        stream->flags |= 0x10;
    }
}

void SoundSSSetPanCh(s32 chan, u8 pan) {
    SoundStream* stream = &sound.streams[chan];
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

void SoundSSSetVolCh(s32 chan, u8 vol) {
    SoundStream* stream;

    stream = &sound.streams[chan];

    if (stream->flags) {
        stream->vol = stream->curVol = vol;
        if (stream->flags & 8) {
            SoundSSSetPanCh(chan, stream->pan);
        }
    }
}

s32 SoundSSGetVolCh(s32 chan) {
    SoundStream* stream;

    stream = &sound.streams[chan];
    if (stream->flags) {
        return (s32)stream->vol;
    } else {
        return 0;
    }
}

void SoundSSSetSrndPanCh(s32 chan, u8 span) {
    SoundStream* stream = &sound.streams[chan];

    if (stream->flags) {
        stream->span = span;
        if (stream->flags & 8) {
            SoundSSSetPanCh(chan, stream->pan);
        }
    }
}

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

void SoundSSMain(void) {
    SoundStream* stream;
    int i;

    for (i = 0; i < 3; i++) {
        stream = &sound.streams[i];
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
