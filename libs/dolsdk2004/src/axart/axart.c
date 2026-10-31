#include <dolphin/axart.h>
#include <dolphin/os.h>
#include <dolphin/mix.h>

static AXART_SOUND* __AXARTSoundList;

/**
 * Initializes the AXART articulator layer: empties the list of active sounds
 * and sets the default 3D distance scale (40.0) and Doppler scale (20.0).
 */
void AXARTInit(void) {
    __AXARTSoundList = 0;
    AXARTSet3DDistanceScale(40.0f);
    AXARTSet3DDopplerScale(20.0f);
}

/**
 * Shuts the articulator layer down: releases the MIX channel of every registered sound (interrupts disabled)
 * and empties the sound list.
 */
void AXARTQuit(void) {
    BOOL old;
    AXART_SOUND* sound;

    old = OSDisableInterrupts();

    for (sound = __AXARTSoundList; sound != 0; sound = (AXART_SOUND*)sound->next) {
        MIXReleaseChannel(sound->axvpb);
    }

    __AXARTSoundList = 0;
    OSRestoreInterrupts(old);
}

/**
 * Per-frame update: runs AXARTServiceSound on every sound in the active list so envelopes,
 * LFOs and 3D positions are applied to their voices.
 */
void AXARTServiceSounds(void) {
    AXART_SOUND* sound;

    for (sound = __AXARTSoundList; sound != 0; sound = (AXART_SOUND*)sound->next) {
        AXARTServiceSound(sound);
    }
}

/**
 * Prepares an AXART_SOUND for a voice: no articulators yet,
 * bound to the given AX voice and its source sample rate (used to scale the SRC ratio against 32 kHz).
 */
void AXARTInitSound(AXART_SOUND* sound, AXVPB* voice, u32 sampleRate) {
    ASSERTLINE(141, sound);
    ASSERTLINE(142, voice);

    sound->articulators = NULL;
    sound->axvpb = voice;
    sound->sampleRate = sampleRate;
}

/**
 * Starts articulating a voice.
 * Sums the contribution of each attached articulator (pan, surround pan, ITD, SRC type, pitch cents,
 * attenuation, aux A/B sends, LPF), programs the voice's SRC type and ratio and ITD target,
 * calls MIXInitChannel with the resulting levels and pan,
 * and pushes the sound onto the head of the active list (interrupts disabled).
 */
void AXARTAddSound(AXART_SOUND* sound) {
    AXART_ART* articulator;
    AXVPB* axvpb;
    s32 cents;
    s32 atten;
    s32 auxA;
    s32 auxB;
    f32 pitch;
    u8 pan;
    u8 span;
    u8 src;
    u16 itdL;
    u16 itdR;
    BOOL old;

    ASSERTLINE(173, sound);
    ASSERTLINE(174, sound->axvpb);

    AXSetVoiceItdOn(sound->axvpb);

    cents = atten = auxA = auxB = 0;
    pitch = sound->sampleRate / 32000.0f;
    pan = 0x40;
    span = 0x7F;
    src = 1;
    itdL = itdR = 0;
    articulator = sound->articulators;

    while (articulator != 0) {
        switch (articulator->type) {
        case AXART_TYPE_3D:
            AXART3DSound((AXART_3D*)articulator);
            pan = ((AXART_3D*)articulator)->pan;
            span = ((AXART_3D*)articulator)->span;
            itdL = ((AXART_3D*)articulator)->itdL;
            itdR = ((AXART_3D*)articulator)->itdR;
            src = ((AXART_3D*)articulator)->src;
            pitch += ((AXART_3D*)articulator)->pitch;
            atten += ((AXART_3D*)articulator)->attenuation;
            break;
        case AXART_TYPE_PANNING:
            pan = ((AXART_PANNING*)articulator)->pan;
            span = ((AXART_PANNING*)articulator)->span;
            break;
        case AXART_TYPE_ITD:
            itdL = ((AXART_ITD*)articulator)->itdL;
            itdR = ((AXART_ITD*)articulator)->itdR;
            break;
        case AXART_TYPE_SRC:
            src = ((AXART_SRC*)articulator)->src;
            break;
        case AXART_TYPE_PITCH:
            cents += ((AXART_PITCH*)articulator)->cents;
            break;
        case AXART_TYPE_PITCH_ENV:
            cents += ((AXART_PITCH_ENV*)articulator)->cents;
            break;
        case AXART_TYPE_PITCH_MOD:
            cents += (s32)(((AXART_PITCH_MOD*)articulator)->cents * ((AXART_PITCH_MOD*)articulator)->lfo.output);
            break;
        case AXART_TYPE_VOLUME:
            atten += ((AXART_VOLUME*)articulator)->attenuation;
            break;
        case AXART_TYPE_AUX_A_VOLUME:
            auxA += ((AXART_AUXA_VOLUME*)articulator)->attenuation;
            break;
        case AXART_TYPE_AUX_B_VOLUME:
            auxB += ((AXART_AUXB_VOLUME*)articulator)->attenuation;
            break;
        case AXART_TYPE_VOLUME_ENV:
            atten += ((AXART_VOLUME_ENV*)articulator)->attenuation;
            break;
        case AXART_TYPE_AUX_A_VOLUME_ENV:
            auxA += ((AXART_AUXA_VOLUME_ENV*)articulator)->attenuation;
            break;
        case AXART_TYPE_AUX_B_VOLUME_ENV:
            auxB += ((AXART_AUXB_VOLUME_ENV*)articulator)->attenuation;
            break;
        case AXART_TYPE_VOLUME_MOD:
            atten += (s32)(((AXART_VOLUME_MOD*)articulator)->attenuation * ((AXART_VOLUME_MOD*)articulator)->lfo.output);
            break;
        case AXART_TYPE_AUX_A_VOLUME_MOD:
            auxA += (s32)(((AXART_AUXA_VOLUME_MOD*)articulator)->attenuation * ((AXART_AUXA_VOLUME_MOD*)articulator)->lfo.output);
            break;
        case AXART_TYPE_AUX_B_VOLUME_MOD:
            auxB += (s32)(((AXART_AUXB_VOLUME_MOD*)articulator)->attenuation * ((AXART_AUXA_VOLUME_MOD*)articulator)->lfo.output);
            break;
        case AXART_TYPE_LPF:
            AXARTLpf((AXART_LPF*)articulator, sound->axvpb);
            break;
        case AXART_TYPE_NONE:
        default:
            ASSERTMSGLINE(306, 0, "unknown articulator type!\n");
        }

        articulator = articulator->next;
    }

    pitch *= AXARTCents(cents >> 0x10);
    axvpb = sound->axvpb;

    AXSetVoiceSrcType(axvpb, src);
    AXSetVoiceSrcRatio(axvpb, pitch);
    AXSetVoiceItdTarget(axvpb, itdL, itdR);
    MIXInitChannel(sound->axvpb, 0, atten >> 0x10, auxA >> 0x10, auxB >> 0x10, pan, span, 0);
    old = OSDisableInterrupts();

    if (__AXARTSoundList != 0) {
        __AXARTSoundList->prev = sound;
        sound->next = __AXARTSoundList;
    } else {
        sound->next = 0;
    }

    sound->prev = 0;
    __AXARTSoundList = sound;
    OSRestoreInterrupts(old);
}

/** Unlinks a sound from the active list (interrupts disabled) and releases its MIX channel. */
void AXARTRemoveSound(AXART_SOUND* sound) {
    BOOL old;

    ASSERTLINE(369, sound);

    old = OSDisableInterrupts();

    if (sound == __AXARTSoundList) {
        __AXARTSoundList = sound->next;
        if (__AXARTSoundList != 0) {
            __AXARTSoundList->prev = 0;
        }
    } else {
        AXART_SOUND* prev = sound->prev;
        AXART_SOUND* next = sound->next;

        prev->next = next;
        if (next != 0) {
            next->prev = prev;
        }
    }

    OSRestoreInterrupts(old);
    MIXReleaseChannel(sound->axvpb);
}

/**
 * Sets up a low-frequency oscillator on a 'length'-entry sample table;
 * 'delta' is how many table steps it advances per service tick. Resets its phase and output to 0.
 */
void AXARTInitLfo(AXART_LFO* lfo, f32* samples, u32 length, f32 delta) {
    ASSERTLINE(417, samples);
    ASSERTLINE(418, length);

    lfo->lfo = samples;
    lfo->length = length;
    lfo->delta = delta;
    lfo->sampleIndex = 0;
    lfo->counter = lfo->sample1 = lfo->sample = lfo->output = 0.0f;
}

/**
 * Initializes a 3D-positioning articulator: no angle, distance, closing speed or pending update,
 * centre pan (64), surround pan 127, SRC type 1, no ITD, pitch ratio 1.0 and a large initial attenuation.
 */
void AXARTInitArt3D(AXART_3D* articulator) {
    ASSERTLINE(446, articulator);
    
    articulator->art.type = AXART_TYPE_3D;
    articulator->hAngle = articulator->vAngle = articulator->dist = articulator->closingSpeed = articulator->update = 0.0f;
    articulator->pan = 64;
    articulator->span = 127;
    articulator->src = 1;
    articulator->itdL = articulator->itdR = 0;
    articulator->pitch = 1.0f;
    articulator->attenuation = -0x03C00000;
}

/** Initializes a panning articulator to centre (pan 64) with the surround pan at 127. */
void AXARTInitArtPanning(AXART_PANNING* articulator) {
    ASSERTLINE(481, articulator);
    
    articulator->art.type = AXART_TYPE_PANNING;
    articulator->pan = 64;
    articulator->span = 127;
}

/** Initializes an interaural-time-difference articulator with zero delay on both ears. */
void AXARTInitArtItd(AXART_ITD* articulator) {
    ASSERTLINE(503, articulator);

    articulator->art.type = AXART_TYPE_ITD;
    articulator->itdL = articulator->itdR = 0;
}

/** Initializes a sample-rate-converter-type articulator to the default type 1. */
void AXARTInitArtSrctype(AXART_SRC* articulator) {
    ASSERTLINE(526, articulator);

    articulator->art.type = AXART_TYPE_SRC;
    articulator->src = 1;
}

/** Initializes a fixed pitch articulator to 0 cents of offset. */
void AXARTInitArtPitch(AXART_PITCH* articulator) {
    ASSERTLINE(547, articulator);

    articulator->art.type = AXART_TYPE_PITCH;
    articulator->cents = 0;
}

/** Initializes a pitch envelope articulator (current cents, target and per-tick delta all 0). */
void AXARTInitArtPitchEnv(AXART_PITCH_ENV* articulator) {
    ASSERTLINE(569, articulator);

    articulator->art.type = AXART_TYPE_PITCH_ENV;
    articulator->delta = articulator->target = articulator->cents = 0;
}

/** Initializes an LFO pitch-modulation (vibrato) articulator with a zero depth and the sine table at zero speed. */
void AXARTInitArtPitchMod(AXART_PITCH_MOD* articulator) {
    ASSERTLINE(594, articulator);

    articulator->art.type = AXART_TYPE_PITCH_MOD;
    articulator->cents = 0;
    AXARTInitLfo(&articulator->lfo, AXARTSine, AXART_SINE_CNT, 0.0f);
}

/** Initializes a fixed volume articulator with 0 attenuation. */
void AXARTInitArtVolume(AXART_VOLUME* articulator) {
    ASSERTLINE(617, articulator);

    articulator->art.type = AXART_TYPE_VOLUME;
    articulator->attenuation = 0;
}

/** Initializes a fixed aux bus A send articulator with 0 attenuation. */
void AXARTInitArtAuxAVolume(AXART_AUXA_VOLUME* articulator) {
    ASSERTLINE(639, articulator);

    articulator->art.type = AXART_TYPE_AUX_A_VOLUME;
    articulator->attenuation = 0;
}

/** Initializes a fixed aux bus B send articulator with 0 attenuation. */
void AXARTInitArtAuxBVolume(AXART_AUXB_VOLUME* articulator) {
    ASSERTLINE(661, articulator);

    articulator->art.type = AXART_TYPE_AUX_B_VOLUME;
    articulator->attenuation = 0;
}

/** Initializes a volume envelope articulator (attenuation, target and delta all 0). */
void AXARTInitArtVolumeEnv(AXART_VOLUME_ENV* articulator) {
    ASSERTLINE(683, articulator);

    articulator->art.type = AXART_TYPE_VOLUME_ENV;
    articulator->delta = articulator->target = articulator->attenuation = 0;
}

/** Initializes an aux bus A send envelope articulator (attenuation, target and delta all 0). */
void AXARTInitArtAuxAVolumeEnv(AXART_AUXA_VOLUME_ENV* articulator) {
    ASSERTLINE(707, articulator);

    articulator->art.type = AXART_TYPE_AUX_A_VOLUME_ENV;
    articulator->delta = articulator->target = articulator->attenuation = 0;
}

/** Initializes an aux bus B send envelope articulator (attenuation, target and delta all 0). */
void AXARTInitArtAuxBVolumeEnv(AXART_AUXB_VOLUME_ENV* articulator) {
    ASSERTLINE(731, articulator);

    articulator->art.type = AXART_TYPE_AUX_B_VOLUME_ENV;
    articulator->delta = articulator->target = articulator->attenuation = 0;
}

/** Initializes an LFO volume-modulation (tremolo) articulator with zero depth and the sine table at zero speed. */
void AXARTInitArtVolumeMod(AXART_VOLUME_MOD* articulator) {
    ASSERTLINE(756, articulator);

    articulator->art.type = AXART_TYPE_VOLUME_MOD;
    articulator->attenuation = 0;
    AXARTInitLfo(&articulator->lfo, AXARTSine, AXART_SINE_CNT, 0.0f);
}

/** Initializes an LFO modulation articulator for the aux bus A send, zero depth and a sine table. */
void AXARTInitArtAuxAVolumeMod(AXART_AUXA_VOLUME_MOD* articulator) {
    ASSERTLINE(781, articulator);

    articulator->art.type = AXART_TYPE_AUX_A_VOLUME_MOD;
    articulator->attenuation = 0;
    AXARTInitLfo(&articulator->lfo, AXARTSine, AXART_SINE_CNT, 0.0f);
}

/** Initializes an LFO modulation articulator for the aux bus B send, zero depth and a sine table. */
void AXARTInitArtAuxBVolumeMod(AXART_AUXB_VOLUME_MOD* articulator) {
    ASSERTLINE(806, articulator);

    articulator->art.type = AXART_TYPE_AUX_B_VOLUME_MOD;
    articulator->attenuation = 0;
    AXARTInitLfo(&articulator->lfo, AXARTSine, AXART_SINE_CNT, 0.0f);
}

/**
 * Initializes a low-pass filter articulator; the first AXARTLpf call will switch the voice's LPF on
 * and load the coefficients.
 */
void AXARTInitArtLpf(AXART_LPF* articulator) {
    ASSERTLINE(830, articulator);

    articulator->art.type = AXART_TYPE_LPF;
    articulator->initLPF = 1;
    articulator->frequency = 0;
    articulator->update = 1;
}
