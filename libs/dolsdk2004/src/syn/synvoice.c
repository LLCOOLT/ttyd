#include <dolphin.h>
#include <dolphin/ax.h>
#include <dolphin/mix.h>
#include <dolphin/syn.h>
#include "fake_tgmath.h"

#include "__syn.h"

#define AX_MAX_VOICES 64

SYNVOICE __SYNVoice[64];

/**
 * Callback given to AXAcquireVoice, called when AX takes a voice back:
 * releases its mixer channel and clears the synthesizer's key-group and key references to the voice.
 */
void __SYNClearVoiceReferences(void* p) {
    AXVPB* axvpb;
    SYNSYNTH* synth;
    SYNVOICE* voice;

    ASSERTLINE(33, p);

    axvpb = p;
    synth = (void*)axvpb->userContext;
    voice = &__SYNVoice[axvpb->index];

    ASSERTLINE(38, synth);
    ASSERTLINE(39, axvpb->index < AX_MAX_VOICES);
    MIXReleaseChannel(axvpb);

    if (voice->keyGroup) {
        synth->keyGroup[voice->midiChannel][voice->keyGroup] = 0;
    }
    if (synth->voice[voice->midiChannel][voice->keyNum] == voice) {
        synth->voice[voice->midiChannel][voice->keyNum] = 0;
    }

    voice->synth = 0;
    synth->notes--;
}

/** Puts a voice's volume and pitch envelopes into release and sets its AX priority. */
void __SYNSetVoiceToRelease(SYNVOICE* voice, u32 priority) {
    ASSERTLINE(63, voice);
    voice->veState = 3;
    voice->peState = 3;
    AXSetVoicePriority(voice->axvpb, priority);
}

/**
 * Per-frame update of voice slot i if it is in use:
 * ends non-looping voices whose AX state has stopped,
 * runs the volume envelope (freeing the voice when it finishes), then the LFO, pitch envelope,
 * mixer update and sample-rate update.
 */
void __SYNServiceVoice(int i) {
    SYNVOICE* voice;
    SYNSYNTH* synth;

    voice = &__SYNVoice[i];
    synth = voice->synth;

    if (synth != NULL) {
        if ((voice->type == 0) && (voice->axvpb->pb.state == 0)) {
            if (voice->keyGroup != 0) {
                voice->synth->keyGroup[voice->midiChannel][voice->keyGroup] = 0;
            }
            if (synth->voice[voice->midiChannel][voice->keyNum] == voice) {
                synth->voice[voice->midiChannel][voice->keyNum] = 0;
            }
            voice->veState = 4;
        }

        __SYNRunVolumeEnvelope(voice);

        if (voice->veState == 4) {
            if (voice->keyGroup != 0) {
                voice->synth->keyGroup[voice->midiChannel][voice->keyGroup] = 0;
            }
            voice->synth = NULL;
            MIXReleaseChannel(voice->axvpb);
            AXFreeVoice(voice->axvpb);
            synth->notes--;
            return;
        }

        __SYNRunLfo(voice);
        __SYNRunPitchEnvelope(voice);
        __SYNUpdateMix(voice);
        __SYNUpdateSrc(voice);
    }
}
