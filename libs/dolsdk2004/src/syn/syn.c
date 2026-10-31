#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/ax.h>
#include <dolphin/mix.h>
#include <dolphin/syn.h>
#include "fake_tgmath.h"

#include "__syn.h"

SYNSYNTH* __SYNSynthList;

// prototypes
static void __SYNAddSynthToList(SYNSYNTH* synth);
static void __SYNRemoveSynthFromList(SYNSYNTH* synth);

/** Adds a synthesizer at the head of the global list that SYNRunAudioFrame services, with interrupts disabled. */
static void __SYNAddSynthToList(SYNSYNTH* synth) {
    BOOL old = OSDisableInterrupts();

    if (__SYNSynthList) {
        synth->next = __SYNSynthList;
    } else {
        synth->next = NULL;
    }
    __SYNSynthList = synth;
    OSRestoreInterrupts(old);
}

/**
 * Rebuilds the global synthesizer list without the given synth, keeping the order of the others,
 * with interrupts disabled.
 */
static void __SYNRemoveSynthFromList(SYNSYNTH* synth) {
    SYNSYNTH* tempHead;
    SYNSYNTH* tempTail;
    SYNSYNTH* tempSynth;
    BOOL old;

    old = OSDisableInterrupts();
    tempHead = NULL;
    tempTail = NULL;
    
    for (tempSynth = __SYNSynthList; tempSynth; tempSynth = tempSynth->next) {
        if (tempSynth != synth) {
            if (tempHead) {
                tempTail->next = tempSynth;
                tempTail = tempSynth;
            } else {
                tempHead = tempTail = tempSynth;
            }
        }
    }

    if (tempTail) {
        tempTail->next = NULL;
    }

    __SYNSynthList = tempHead;
    OSRestoreInterrupts(old);
}

/**
 * Initialises the synthesizer library: marks all 64 voice slots (one per AX voice) as unused
 * and empties the synthesizer list.
 */
void SYNInit(void) {
    int i;

    for (i = 0; i < 64; i++) {
        __SYNVoice[i].synth = 0;
    }
    __SYNSynthList = NULL;
}

/** Shuts the synthesizer library down; the same as SYNInit. */
void SYNQuit(void) {
    SYNInit();
}

/**
 * Per-audio-frame update: services all 64 voices (envelopes, LFO, pitch and mix),
 * then runs the queued MIDI input of every synthesizer.
 */
void SYNRunAudioFrame(void) {
    int i;
    SYNSYNTH* synth;

    for (i = 0; i < 64; i++) {
        __SYNServiceVoice(i);
    }

    for (synth = __SYNSynthList; synth; synth = synth->next) {
        __SYNRunInputBufferEvents(synth);
    }
}

/**
 * Sets up a software synthesizer from a wavetable image:
 * resolves its six section offsets (percussion and melodic instruments, regions, articulations, samples,
 * ADPCM data), stores the ARAM and zero-sample addresses in word, byte and nibble units,
 * the three voice priorities, resets all MIDI controllers and clears the voice and key-group tables,
 * then adds it to the service list.
 */
void SYNInitSynth(SYNSYNTH* synth, void* wavetable, u32 aramBase, u32 zeroBase, u32 priorityVoiceAlloc, u32 priorityNoteOn, u32 priorityNoteRelease) {
    u32* p;
    u32 midiChannel;
    u32 noteNumber;

    ASSERTLINE(158, synth);
    ASSERTLINE(159, wavetable);
    ASSERTLINE(160, aramBase);

    p = wavetable;
    synth->percussiveInst = (void*)((u32)wavetable + *(p)); p += 1;
    synth->melodicInst = (void*)((u32)wavetable + *(p)); p += 1;
    synth->region = (void*)((u32)wavetable + *(p)); p += 1;
    synth->art = (void*)((u32)wavetable + *(p)); p += 1;
    synth->sample = (void*)((u32)wavetable + *(p)); p += 1;
    synth->adpcm = (void*)((u32)wavetable + *(p)); p += 1;
    synth->aramBaseWord = (aramBase >> 1);
    synth->aramBaseByte = aramBase;
    synth->aramBaseNibble = (aramBase << 1);
    synth->zeroBaseWord = zeroBase >> 1;
    synth->zeroBaseByte = zeroBase;
    synth->zeroBaseNibble = (zeroBase << 1);
    synth->priorityVoiceAlloc = priorityVoiceAlloc;
    synth->priorityNoteOn = priorityNoteOn;
    synth->priorityNoteRelease = priorityNoteRelease;
    synth->masterVolume = 0;
    __SYNResetAllControllers(synth);
    synth->inputPosition = &synth->input[0][0];
    synth->inputCounter = 0;
    synth->notes = 0;

    for (midiChannel = 0; midiChannel < 16; midiChannel++) {
        for (noteNumber = 0; noteNumber < 16; noteNumber++) {
            synth->keyGroup[midiChannel][noteNumber] = 0;
        }
    }

    for (midiChannel = 0; midiChannel < 16; midiChannel++) {
        for (noteNumber = 0; noteNumber < 128; noteNumber++) {
            synth->voice[midiChannel][noteNumber] = 0;
        }
    }

    __SYNAddSynthToList(synth);
}

/**
 * Frees every AX voice the synthesizer is using, releasing their mixer channels,
 * and removes it from the service list.
 */
void SYNQuitSynth(SYNSYNTH* synth) {
    int i;
    BOOL old;
    SYNVOICE* voice;

    old = OSDisableInterrupts();
    if (synth->notes) {
        for (i = 0; i < 64; i++) {
            voice = &__SYNVoice[i];
            if (voice->synth == synth) {
                MIXReleaseChannel(voice->axvpb);
                AXFreeVoice(voice->axvpb);
                voice->synth = 0;
            }
        }
    }

    __SYNRemoveSynthFromList(synth);
    OSRestoreInterrupts(old);
}

/**
 * Copies a three-byte MIDI message into the synthesizer's input buffer;
 * it is executed during the next SYNRunAudioFrame.
 */
void SYNMidiInput(SYNSYNTH* synth, u8* input) {
    u8* src;

    ASSERTLINE(244, synth);
    ASSERTLINE(245, input);

    src = input;
    *(synth->inputPosition) = *(src); (synth->inputPosition) += 1; (src) += 1;
    *(synth->inputPosition) = *(src); (synth->inputPosition) += 1; (src) += 1;
    *(synth->inputPosition) = *(src); (synth->inputPosition) += 1; (src) += 1;
    synth->inputCounter++;

    if (synth->inputCounter >= SYN_INPUT_BUFFER_SIZE) {
        ASSERTMSGLINE(258, FALSE, "synth input buffer exceeded, increase SYN_INPUT_BUFFER_SIZE");
    }
}

/** Sets the synthesizer's master volume in decibels (stored in 16.16 fixed point). */
void SYNSetMasterVolume(SYNSYNTH* synth, s32 dB) {
    ASSERTLINE(267, synth);
    synth->masterVolume = (dB << 0x10);
}

/** Returns the synthesizer's master volume in decibels. */
s32 SYNGetMasterVolume(SYNSYNTH* synth) {
    ASSERTLINE(278, synth);
    return synth->masterVolume >> 0x10;
}

/** Returns the number of voices the synthesizer currently has playing. */
u32 SYNGetActiveNotes(SYNSYNTH* synth) {
    ASSERTLINE(289, synth);
    return synth->notes;
}
