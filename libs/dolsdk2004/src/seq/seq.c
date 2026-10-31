#include <dolphin.h>
#include <dolphin/seq.h>

/** Number of data bytes after each MIDI status byte 0x80-0xFF. */
static u8 __SEQMidiEventLength[128] = {
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02,
    0x00, 0x00, 0x02, 0x01,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

static SEQSEQUENCE* __SEQSequenceList;

// prototypes
static void __SEQPushSequenceList(SEQSEQUENCE* sequence);
static void __SEQRemoveSequenceFromList(SEQSEQUENCE* sequence);
static u32 __SEQGetIntTrack(SEQTRACK* track);
static void __SEQHandleSysExEvent(SEQTRACK* track);
static void __SEQSetTicksPerFrame(SEQTRACK* track, f32 bps);
static void __SEQTempoMetaEvent(SEQTRACK* track);
static void __SEQTrackEnd(SEQTRACK* track);
static void __SEQHandleMetaEvent(SEQTRACK* track);
static void __SEQHandleSynthEvent(SYNSYNTH* synth, SEQTRACK* track);
static void __SEQRunEvent(SYNSYNTH* synth, SEQTRACK* track);
static void __SEQInitTracks(SEQSEQUENCE* sequence, u8* read, int tracks);
static void __SEQReadHeader(SEQSEQUENCE* sequence, u8* midiStream);

/** Adds a sequence at the head of the list of sequences that SEQRunAudioFrame plays, with interrupts disabled. */
static void __SEQPushSequenceList(SEQSEQUENCE* sequence) {
    BOOL old;

    old = OSDisableInterrupts();
    if (__SEQSequenceList) {
        sequence->next = __SEQSequenceList;
    } else {
        sequence->next = NULL;
    }

    __SEQSequenceList = sequence;
    OSRestoreInterrupts(old);
}

/**
 * Removes a sequence from the list by clearing the list
 * and pushing back every other sequence (so the order of the others is reversed), with interrupts disabled.
 */
static void __SEQRemoveSequenceFromList(SEQSEQUENCE* sequence) {
    BOOL old;
    SEQSEQUENCE* thisSequence;
    SEQSEQUENCE* next;

    old = OSDisableInterrupts();
    thisSequence = __SEQSequenceList;
    __SEQSequenceList = NULL;

    while(thisSequence) {
        next = thisSequence->next;
        if (thisSequence != sequence) {
            __SEQPushSequenceList(thisSequence);
        }
        thisSequence = next;
    }

    OSRestoreInterrupts(old);
}

/**
 * Reads a MIDI variable-length quantity (7 bits per byte, high bit means more bytes follow) at the track's read
 * pointer and advances the pointer past it.
 */
static u32 __SEQGetIntTrack(SEQTRACK* track) {
    u32 value;

    ASSERTLINE(120, track);
    for (value = *track->current & 0x7F; *track->current & 0x80; value = (value << 7) + (*track->current & 0x7F)) {
        track->current++;
    }
    track->current++;
    return value;
}

/** Skips a MIDI system-exclusive event by reading its length and advancing the track pointer past the data. */
static void __SEQHandleSysExEvent(SEQTRACK* track) {
    u32 length;

    ASSERTLINE(143, track);
    length = __SEQGetIntTrack(track);
    track->current += length;
}

/**
 * Stores the track's tempo in beats per second and converts it to 16.16 fixed-point MIDI ticks per audio frame
 * (a frame is 160 samples at 32 kHz) using the file's ticks-per-beat.
 */
static void __SEQSetTicksPerFrame(SEQTRACK* track, f32 bps) {
    SEQSEQUENCE* sequence;

    ASSERTLINE(157, track);
    sequence = track->sequence;
    track->beatsPerSec = bps;
    track->ticksPerFrame = (65536.0f * (160.0f / ((32000.0f / bps) / sequence->timeFormat)));
}

/** Handles the MIDI set-tempo meta event: reads the 24-bit microseconds per beat and sets the track's tempo from it. */
static void __SEQTempoMetaEvent(SEQTRACK* track) {
    u32 data;
    f32 beatsPerSec;

    data = *track->current;
    track->current++;

    data = (data << 8) + *track->current;
    track->current++;

    data = (data << 8) + *track->current;
    track->current++;

    beatsPerSec = 1000000 / (f32)data;
    __SEQSetTicksPerFrame(track, beatsPerSec);
}

/** Marks a track finished; when the last running track ends the sequence is flagged as ended. */
static void __SEQTrackEnd(SEQTRACK* track) {
    SEQSEQUENCE* sequence;
    ASSERTLINE(199, track);

    sequence = track->sequence;
    sequence->tracksRunning--;
    track->state = 0;
    if (sequence->tracksRunning == 0) {
        sequence->end = 1;
    }
}

/**
 * Handles a MIDI meta event: end of track (0x2F) finishes the track, set tempo (0x51) changes the tempo,
 * everything else is skipped by its length.
 */
static void __SEQHandleMetaEvent(SEQTRACK* track) {
    u8 type;
    u32 length;

    ASSERTLINE(218, track);
    type = *track->current;
    track->current++;

    switch(type) {
    case 0x2F:
        __SEQTrackEnd(track);
        return;
    case 0x51:
        length = __SEQGetIntTrack(track);
        __SEQTempoMetaEvent(track);
        return;
    default:
        length = __SEQGetIntTrack(track);
        track->current += length;
        return;
    }
}

/**
 * Reads the data bytes of a MIDI channel event (count from __SEQMidiEventLength),
 * calls the callback registered for that controller number if it is a control change (0xB0),
 * and passes the message to the synthesizer with SYNMidiInput.
 */
static void __SEQHandleSynthEvent(SYNSYNTH* synth, SEQTRACK* track) {
    u8 ch[3];
    u32 bytes;
    void (*callback)(void *, u8);

    bytes = __SEQMidiEventLength[track->status - 0x80];
    ch[0] = track->status;

    switch(bytes) {
    case 0:
        break;
    case 1:
        ch[1] = *track->current; track->current++;
        break;
    case 2:
        ch[1] = *track->current; track->current++;
        ch[2] = *track->current; track->current++;
        break;
    }

    if ((ch[0] & 0xF0) == 0xB0) {
        callback = ((SEQSEQUENCE*)track->sequence)->callback[ch[1]];
        if (callback) {
           callback(track, ch[1]);
        }
    }

    SYNMidiInput(synth, ch);
}

/**
 * Runs the next event of a track: takes a new status byte if present (otherwise uses running status),
 * dispatches sysex, meta or synth events, and ends the track when it reaches the end of its data.
 */
static void __SEQRunEvent(SYNSYNTH* synth, SEQTRACK* track) {
    u8 event;

    ASSERTLINE(303, synth);
    ASSERTLINE(304, track);

    event = *track->current;
    if (event >= 0x80) {
        track->status = event; track->current++;
    }

    switch(track->status) {
    case 0xF7:
    case 0xF0:
        __SEQHandleSysExEvent(track);
        break;
    case 0xFF:
        __SEQHandleMetaEvent(track);
        break;
    default:
        __SEQHandleSynthEvent(synth, track);
        break;
    }

    if (track->current >= track->end) {
        __SEQTrackEnd(track);
    }
}

/**
 * Scans the MIDI chunks after the header and sets up each MTrk chunk as a track of the sequence:
 * data range, read pointer and default tempo (120 beats per minute equivalent).
 */
static void __SEQInitTracks(SEQSEQUENCE* sequence, u8* read, int tracks) {
    int i;
    u8* p;
    u32 chunk;
    u32 bytes;
    SEQTRACK* track;

    i = 0;
    p = read;

    while (tracks) {
        while (1) {
            chunk = *(u32*)p;
            p += 4;
            bytes = *(u32*)p;
            p += 4;
            if (chunk == 'MTrk') {
                track = &sequence->track[i];
                track->sequence = sequence;
                track->start = p;
                track->end = &p[bytes];
                track->current = p;
                track->defaultTicksPerFrame = (u32)(65536.0f * (160.0f / (16000.0f / (f32)sequence->timeFormat)));
                track->state = 0;
                p += bytes;
                break;
            }
            p += bytes;
        }
        tracks--;
        i++;
    }
}

/**
 * Parses the MIDI header chunk (file type 0 or 1, track count, ticks per beat)
 * and initialises the sequence's tracks; a type 0 file has one track.
 */
static void __SEQReadHeader(SEQSEQUENCE* sequence, u8* midiStream) {
    u8* read;
    u32 bytes;
    u32 fileType;

    read = midiStream;
    ASSERTMSGLINE(401, *(u32*)read == 'MThd', "!!!midiStream is not a valid MIDI file\n!!!");
    read += 4;

    bytes = *(u32*)read;
    read += 4;

    fileType = *(u16*)read;
    read+=2;

    sequence->nTracks = *(u16*)read;
    read+=2;

    sequence->timeFormat = *(s16*)read;
    read+=2;

    ASSERTMSGLINE(416, sequence->timeFormat >= 0, "!!!SEQ does not support SMPTE time!!!\n");
    bytes -= 6;
    read += bytes;

    switch(fileType) {
    case 0:
        sequence->nTracks = 1;
        __SEQInitTracks(sequence, read, 1);
        break;
    case 1:
        ASSERTMSGLINE(438, sequence->nTracks < 0x40, "exceeded SEQ_MAX_TRACKS, please increase SEQ_MAX_TRACKS\n");
        __SEQInitTracks(sequence, read, sequence->nTracks);
        break;
    default:
        ASSERTMSGLINE(446, 0, "!!!Invalid MIDI file type\n!!!");
        break;
    }

    sequence->tracksRunning = sequence->nTracks;
}

/** Initialises the sequencer library by emptying the list of sequences. */
void SEQInit(void) {
    __SEQSequenceList = NULL;
}

/** Shuts the sequencer library down by emptying the list of sequences. */
void SEQQuit(void) {
    __SEQSequenceList = NULL;
}

/**
 * Advances every playing sequence (state 1 or 2) by one audio frame:
 * for each running track it subtracts the frame's ticks from the delay and runs all events that fall due.
 * A sequence that has ended is stopped, and restarted if it was in state 2 (looping).
 */
void SEQRunAudioFrame(void) {
    SEQSEQUENCE* sequence;
    u32 i;
    SEQTRACK* track;
    u32 ticks;

    for (sequence = __SEQSequenceList; sequence; sequence = sequence->next) {
        if ((sequence->state == 1) || (sequence->state == 2)) {
            for (i = 0; i < sequence->nTracks; i++) {
                track = &sequence->track[i];
                if ((track->state == 1) || (track->state == 2)) {
                    ticks = track->ticksPerFrame;
                    if (track->delay > ticks) {
                        track->delay -= ticks;
                    } else {
                        while (ticks >= track->delay) {
                            ticks -= track->delay;
                            __SEQRunEvent(&sequence->synth, track);
                            if (track->state != 0) {
                                track->delay = __SEQGetIntTrack(track) << 0x10;
                            } else {
                                break;
                            }
                        }

                        track->delay -= ticks;
                    }
                }
            }
        }

        if (sequence->end != 0) {
            if (sequence->state == 2) {
                SEQSetState(sequence, 0);
                SEQSetState(sequence, 2);
            } else {
                SEQSetState(sequence, 0);
            }
        }
    }
}

/**
 * Registers a MIDI sequence: sets up its synthesizer with the wavetable wt and ARAM addresses (SYNInitSynth),
 * clears the controller callbacks, parses the MIDI data in midiStream
 * and adds it to the play list in the stopped state.
 */
void SEQAddSequence(SEQSEQUENCE* sequence, u8* midiStream, void* wt, u32 aramBase, u32 zeroBase, u32 priorityVoiceAlloc, u32 priorityNoteOn, u32 priorityNoteRelease) {
    int i;

    ASSERTLINE(559, sequence);
    ASSERTLINE(560, midiStream);
    ASSERTLINE(561, wt);
    ASSERTLINE(562, aramBase);
    ASSERTLINE(563, (priorityVoiceAlloc < 32) && (priorityVoiceAlloc > 0));
    ASSERTLINE(564, (priorityNoteOn < 32) && (priorityNoteOn > 0));
    ASSERTLINE(565, (priorityNoteRelease < 32) && (priorityNoteRelease > 0));

    SYNInitSynth(&sequence->synth, wt, aramBase, zeroBase, priorityVoiceAlloc, priorityNoteOn, priorityNoteRelease);
    sequence->state = 0;

    for(i = 0; i < 0x80; i++) {
        sequence->callback[i] = 0;
    }

    __SEQReadHeader(sequence, midiStream);
    __SEQPushSequenceList(sequence);
}

/** Takes a sequence out of the play list and shuts down its synthesizer. */
void SEQRemoveSequence(SEQSEQUENCE* sequence) {
    ASSERTLINE(598, sequence);
    __SEQRemoveSequenceFromList(sequence);
    SYNQuitSynth(&sequence->synth);
}

/**
 * Registers a function called with the track and controller number whenever the sequence sends the given MIDI
 * control change.
 */
void SEQRegisterControllerCallback(SEQSEQUENCE* sequence, u8 controller, void (*callback)(void*, u8)) {
    ASSERTLINE(617, sequence);
    ASSERTLINE(618, controller < 128);
    ASSERTLINE(619, callback);
    sequence->callback[controller] = callback;
}

/**
 * Sets a sequence's state: 1 plays, 2 plays and loops, 0 stops, 3 pauses.
 * Starting from stopped rewinds every track and reads the first delay;
 * stopping or pausing sends all-notes-off (controller 0x7B) on all 16 channels.
 */
void SEQSetState(SEQSEQUENCE* sequence, u32 state) {
    int i;

    ASSERTLINE(632, sequence);

    switch(state) {
    case 1:
    case 2:
        if (sequence->state == 0) {
            int old;

            old = OSDisableInterrupts();
            for (i = 0; i < sequence->nTracks; i++) {
                SEQTRACK* track = &sequence->track[i];
                track->current = track->start;
                track->ticksPerFrame = track->defaultTicksPerFrame;
                track->delay = __SEQGetIntTrack(track) << 0x10;
                track->state = 1;                    
            }
            sequence->tracksRunning = sequence->nTracks;
            OSRestoreInterrupts(old);
        }
        sequence->end = 0;
        break;
    case 0:
    case 3: {
        int old;
        u8 ch[3];

        for (i = 0; i < 16; i++) {
            old = OSDisableInterrupts();
            ch[0] = (i | 0xB0);
            ch[1] = 0x7B;
            ch[2] = 0;
            SYNMidiInput(&sequence->synth, ch);
            OSRestoreInterrupts(old);
        }
        break;
    }
    }

    sequence->state = state;
}

/** Returns the sequence's state (0 stopped, 1 playing, 2 looping, 3 paused). */
u32 SEQGetState(SEQSEQUENCE* sequence) {
    ASSERTLINE(700, sequence);
    return sequence->state;
}

/** Sets the tempo of one track, or of all tracks when trackIndex is -1, from beats per minute. */
void SEQSetTempo(SEQSEQUENCE* sequence, u32 trackIndex, f32 bpm) {
    int i;

    ASSERTLINE(711, sequence);
    ASSERTLINE(712, (trackIndex < sequence->nTracks) || (trackIndex == SEQ_ALL_TRACKS));

    if (trackIndex == -1) {
        for (i = 0; i < sequence->nTracks; i++) {
            __SEQSetTicksPerFrame(&sequence->track[i], bpm / 60.0f);
        }
        return;
    }

    __SEQSetTicksPerFrame(&sequence->track[trackIndex], bpm / 60.0f);
}

/** Returns the track's tempo in beats per minute. */
f32 SEQGetTempo(SEQSEQUENCE* sequence, u32 trackIndex) {
    ASSERTLINE(733, sequence);
    ASSERTLINE(734, trackIndex < sequence->nTracks);
    return 60.0f* sequence->track[trackIndex].beatsPerSec;
}

/** Sets the master volume of the sequence's synthesizer in decibels. */
void SEQSetVolume(SEQSEQUENCE* sequence, s32 dB) {
    ASSERTLINE(745, sequence);
    SYNSetMasterVolume(&sequence->synth, dB);
}

/**
 * Returns the master volume of the sequence's synthesizer.
 * Surprising: the function has no return statement,
 * so the value returned is whatever the call leaves in the return register.
 */
long SEQGetVolume(SEQSEQUENCE* sequence) {
    ASSERTLINE(756, sequence);
    SYNGetMasterVolume(&sequence->synth);
}
