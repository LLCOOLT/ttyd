#include <dolphin/ai.h>
#include <dolphin/dtk.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>

static DTKTrack* __DTKCurrentTrack;
static DTKTrack* __DTKPlayListHead;
static DTKTrack* __DTKPlayListTail;
static volatile u32 __DTKState;
static volatile u32 __DTKTempState;
static volatile u32 __DTKRepeatMode;
static volatile u32 __DTKPosition;
static volatile u32 __DTKInterruptFrequency;
static volatile u8 __DTKVolumeL;
static volatile u8 __DTKVolumeR;
static volatile u32 __DTKShutdownFlag;
static volatile u32 __DTKTrackEnded;
static DTKFlushCallback __DTKFlushCallback;
static int __busy_for_ais_address;

static DVDCommandBlock __block_for_run_callback;
static DVDCommandBlock __block_for_prep_callback;
static DVDCommandBlock __block_for_stream_status;
static DVDCommandBlock __block_for_ais_isr;
static DVDCommandBlock __block_for_flushtracks;
static DVDCommandBlock __block_for_repeatmode;
static DVDCommandBlock __block_for_set_state;
static DVDCommandBlock __block_for_next_track;
static DVDCommandBlock __block_for_prev_track;

/**
 * Starts the AI stream: restores the left and right stream volume, resets the sample counter,
 * arms the sample-count trigger at the callback interval and sets the stream play state to playing.
 */
static void __DTKStartAi(void) {
    AISetStreamVolLeft(__DTKVolumeL);
    AISetStreamVolRight(__DTKVolumeR);
    AIResetStreamSampleCount();
    AISetStreamTrigger(__DTKInterruptFrequency);
    AISetStreamPlayState(1);
}

/** Silences the AI stream (volume 0 on both channels) and sets the stream play state to stopped. */
static void __DTKStopAi(void) {
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AISetStreamPlayState(0);
}

/**
 * Calls the track's user callback with the event bits that are both raised
 * and requested in the track's eventMask.
 * The events used in this file are 1 (playing), 2 (stopped), 4 (paused), 8 (queued),
 * 16 (track ended) and 32 (prepared paused).
 */
static void __DTKCheckUserCallback(DTKTrack* track, u32 event) {
    ASSERTLINE(84, track);
    if (track && track->callback && (track->eventMask & event)) {
        track->callback(track->eventMask & event);
    }
}

/** Makes the next track in the playlist the current one, with interrupts off; stays on the last track. */
static void __DTKForward(void) {
    BOOL old = OSDisableInterrupts();
    if (__DTKCurrentTrack && __DTKCurrentTrack->next) {
        __DTKCurrentTrack = __DTKCurrentTrack->next;
    }
    OSRestoreInterrupts(old);
}

/** Makes the previous track in the playlist the current one, with interrupts off; stays on the first track. */
static void __DTKBackward(void) {
    BOOL old = OSDisableInterrupts();
    if (__DTKCurrentTrack && __DTKCurrentTrack->prev) {
        __DTKCurrentTrack = __DTKCurrentTrack->prev;
    }
    OSRestoreInterrupts(old);
}

/**
 * DVD callback for the stream error status query:
 * if the drive reports status 0 in the low byte, marks the track as ended and resets the stored position.
 */
static void __DTKCallbackForStreamStatus(s32 result, DVDCommandBlock* block) {
    if ((result & 0xFF) == 0) {
        __DTKTrackEnded = 1;
        __DTKPosition = 0;
    }
}

/**
 * Runs when the drive has prepared the stream: starts the AI stream,
 * asks the drive to stop the stream at its end, sets the state to running and raises the "playing" event.
 */
static void __DTKCallbackForRun(s32 result, DVDFileInfo* fileInfo) {
    __DTKStartAi();
    DVDStopStreamAtEndAsync(&__block_for_run_callback, 0);
    __DTKState = DTK_STATE_RUN;
    __DTKCheckUserCallback(__DTKCurrentTrack, 1);
}

/**
 * Runs when a stream prepared for pause is ready:
 * keeps the AI stream silent, asks the drive to stop at the end of the stream,
 * sets the state to paused and raises the "prepared paused" event.
 */
static void __DTKCallbackForPreparePaused(s32 result, DVDFileInfo* fileInfo) {
    __DTKStopAi();
    DVDStopStreamAtEndAsync(&__block_for_prep_callback, 0);
    __DTKState = DTK_STATE_PAUSE;
    __DTKCheckUserCallback(__DTKCurrentTrack, 32);
}

/** Asks the DVD drive to prepare an audio stream for the current playlist track so playback can start. */
static void __DTKPrepareCurrentTrack(void) {
    DVDPrepareStreamAsync(&__DTKCurrentTrack->dvdFileInfo, 0, 0, __DTKCallbackForRun);
}

/** Same as __DTKPrepareCurrentTrack, but the track is left paused once the drive has it ready. */
static void __DTKPrepareCurrentTrackPaused(void) {
    DVDPrepareStreamAsync(&__DTKCurrentTrack->dvdFileInfo, 0, 0, __DTKCallbackForPreparePaused);
}

/**
 * DVD callback for the stream play address query. Stores the address as the playback position.
 * If the track had ended, raises the "track ended" event and applies the repeat mode:
 * no repeat moves to the next track and stops after the last, repeat all wraps to the first,
 * repeat one restarts the same track. If it had not ended, queries the stream error status to detect the end.
 */
static void __DTKCallbackForPlaylist(s32 result, DVDCommandBlock* block) {
    __DTKPosition = result;
    __busy_for_ais_address = 0;

    if (__DTKTrackEnded) {
        __DTKTrackEnded = 0;
        __DTKCheckUserCallback(__DTKCurrentTrack, 16);
        __DTKState = DTK_STATE_BUSY;

        switch (__DTKRepeatMode) {
        case DTK_MODE_NOREPEAT:
            if (__DTKCurrentTrack) {
                if (__DTKCurrentTrack->next) {
                    __DTKCurrentTrack = __DTKCurrentTrack->next;
                    __DTKStopAi();
                    __DTKPrepareCurrentTrack();
                } else {
                    __DTKCurrentTrack = __DTKPlayListHead;
                    __DTKStopAi();
                    __DTKState = DTK_STATE_STOP;
                }
            }
            break;
        case DTK_MODE_ALLREPEAT:
            if (__DTKCurrentTrack) {
                if (__DTKCurrentTrack->next) {
                    __DTKCurrentTrack = __DTKCurrentTrack->next;
                    __DTKStopAi();
                    __DTKPrepareCurrentTrack();
                } else {
                    __DTKCurrentTrack = __DTKPlayListHead;
                    __DTKStopAi();
                    __DTKPrepareCurrentTrack();
                }
            }
            break;
        case DTK_MODE_REPEAT1:
            if (__DTKCurrentTrack) {
                __DTKStopAi();
                __DTKPrepareCurrentTrack();
            }
            break;
        }
    } else {
        DVDGetStreamErrorStatusAsync(&__block_for_stream_status, __DTKCallbackForStreamStatus);
    }
}

/**
 * AI stream sample-count callback: re-arms the trigger one interval ahead and,
 * unless a query is already pending, asks the drive for the stream's play address (see
 * __DTKCallbackForPlaylist).
 */
static void __DTKCallbackForAIInterrupt(u32 count) {
    AISetStreamTrigger(count + __DTKInterruptFrequency);
    if (__DTKCurrentTrack && !__busy_for_ais_address) {
        __busy_for_ais_address = 1;
        DVDGetStreamPlayAddrAsync(&__block_for_ais_isr, __DTKCallbackForPlaylist);
    }
}

/**
 * Finishes DTKFlushTracks: stops the AI stream, closes every queued file, empties the playlist,
 * sets the state to stopped, runs the flush callback if any
 * and clears the shutdown flag that DTKShutdown waits on.
 */
static void __DTKCallbackForFlush(s32 result, DVDCommandBlock* block) {
    DTKTrack* track;

    AISetStreamPlayState(0);
    track = __DTKPlayListHead;
    while (track) {
        DVDClose(&track->dvdFileInfo);
        track = track->next;
    }

    __DTKPlayListHead = NULL;
    __DTKPlayListTail = NULL;
    __DTKCurrentTrack = NULL;
    __DTKState = DTK_STATE_STOP;

    if (__DTKFlushCallback) {
        __DTKFlushCallback();
        __DTKFlushCallback = NULL;
    }

    __DTKState = DTK_STATE_STOP;
    __DTKShutdownFlag = 0;
}

/**
 * Runs after the stream is cancelled for DTKSetState(stop):
 * raises the "stopped" event and sets the state to stopped.
 */
static void __DTKCallbackForStop(s32 result, DVDCommandBlock* block) {
    __DTKCheckUserCallback(__DTKCurrentTrack, 2);
    __DTKState = DTK_STATE_STOP;
}

/**
 * Runs after the stream is cancelled for DTKNextTrack:
 * stops the AI stream, steps to the next track and restores the state saved before the skip with DTKSetState.
 */
static void __DTKCallbackForNextTrack(s32 result, DVDCommandBlock* block) {
    AISetStreamPlayState(0);
    __DTKForward();
    __DTKState = DTK_STATE_STOP;
    DTKSetState(__DTKTempState);
}

/**
 * Runs after the stream is cancelled for DTKPrevTrack:
 * stops the AI stream, steps back one track and restores the state saved before the skip with DTKSetState.
 */
static void __DTKCallbackForPrevTrack(s32 result, DVDCommandBlock* block) {
    AISetStreamPlayState(0);
    __DTKBackward();
    __DTKState = DTK_STATE_STOP;
    DTKSetState(__DTKTempState);
}

/**
 * Resets the DTK player state (empty playlist, stopped, no repeat, 48000 sample callback interval, full volume),
 * silences the AI stream and registers the AI sample-count callback.
 */
void DTKInit(void) {
    __DTKCurrentTrack = NULL;
    __DTKPlayListHead = NULL;
    __DTKPlayListTail = NULL;
    __DTKState = DTK_STATE_STOP;
    __DTKRepeatMode = DTK_MODE_NOREPEAT;
    __DTKPosition = 0;
    __DTKInterruptFrequency = 48000;
    __DTKVolumeL = 255;
    __DTKVolumeR = 255;

    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(__DTKCallbackForAIInterrupt);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
}

/** Silences and unregisters the AI stream, flushes the playlist and waits until the flush callback has finished. */
void DTKShutdown(void) {
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(NULL);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);

    __DTKShutdownFlag = 1;
    DTKFlushTracks(NULL);
    __DTKState = DTK_STATE_STOP;

    while (__DTKShutdownFlag) {}
}

/**
 * Opens a file on the disc and appends it to the playlist, raising the "queued" event.
 * Returns 1 if the file cannot be opened, 0 otherwise.
 * If the player is running with an empty playlist, it starts the new track.
 */
u32 DTKQueueTrack(char* fileName, DTKTrack* track, u32 eventMask, DTKCallback callback) {
    u32 startTrack;
    BOOL old;

    startTrack = 0;
    if (!DVDOpen(fileName, &track->dvdFileInfo)) {
        return 1;
    }

    old = OSDisableInterrupts();
    track->fileName = fileName;
    track->eventMask = eventMask;
    track->callback = callback;

    if (__DTKPlayListHead == NULL) {
        __DTKPlayListHead = track;
        __DTKPlayListTail = track;
        track->prev = NULL;
        track->next = NULL;
        if (__DTKState == DTK_STATE_RUN) {
            startTrack = 1;
        }
    } else {
        __DTKPlayListTail->next = track;
        track->prev = __DTKPlayListTail;
        __DTKPlayListTail = track;
        track->next = NULL;
    }

    if (__DTKCurrentTrack == NULL) {
        __DTKCurrentTrack = track;
    }

    OSRestoreInterrupts(old);
    __DTKCheckUserCallback(track, 8);

    if (startTrack != 0) {
        __DTKState = DTK_STATE_BUSY;
        __DTKPrepareCurrentTrack();
    }

    return 0;
}

/**
 * Closes a queued track's file and unlinks it from the playlist.
 * Returns 2 (and does nothing) if it is the current track, otherwise 0.
 */
u32 DTKRemoveTrack(DTKTrack* track) {
    BOOL old;

    if (track == __DTKCurrentTrack) {
        return 2;
    }

    old = OSDisableInterrupts();
    DVDClose(&track->dvdFileInfo);

    if (track == __DTKPlayListHead && track == __DTKPlayListTail) {
        __DTKPlayListHead = NULL;
        __DTKPlayListTail = NULL;
        OSRestoreInterrupts(old);
        return 0;
    }

    if (track == __DTKPlayListHead) {
        __DTKPlayListHead = track->next;
        __DTKPlayListHead->prev = NULL;
        if (__DTKRepeatMode == DTK_MODE_ALLREPEAT) {
            __DTKPlayListTail->next = __DTKPlayListHead;
        }
        OSRestoreInterrupts(old);
        return 0;
    }

    if (track == __DTKPlayListTail) {
        __DTKPlayListTail = track->prev;
        __DTKPlayListTail->next = NULL;
        if (__DTKRepeatMode == DTK_MODE_ALLREPEAT) {
            __DTKPlayListTail->next = __DTKPlayListHead;
        }
        OSRestoreInterrupts(old);
        return 0;
    }

    track->prev->next = track->next;
    track->next->prev = track->prev;
    OSRestoreInterrupts(old);
    return 0;
}

/**
 * Cancels the drive stream if one is running, then closes and clears the whole playlist and calls the callback.
 * Returns 0 if the player is busy, 1 otherwise.
 */
int DTKFlushTracks(DTKFlushCallback callback) {
    u32 temp;

    if (__DTKState == DTK_STATE_BUSY) {
        return 0;
    }

    temp = __DTKState;
    __DTKState = DTK_STATE_BUSY;
    __DTKFlushCallback = callback;
    if (temp == DTK_STATE_RUN) {
        DVDCancelStreamAsync(&__block_for_flushtracks, __DTKCallbackForFlush);
    } else {
        __DTKCallbackForFlush(0, 0);
    }
    return 1;
}

/** Obsolete: does nothing. */
void DTKSetSampleRate(u32 samplerate) {
    // obsolete
}

/** Sets the number of samples between AI stream callbacks and re-arms the AI trigger at that interval. */
void DTKSetInterruptFrequency(u32 samples) {
    __DTKInterruptFrequency = samples;
    AIResetStreamSampleCount();
    AISetStreamTrigger(__DTKInterruptFrequency);
}

/**
 * Stores the repeat mode (no repeat, repeat all, repeat one) that __DTKCallbackForPlaylist uses at the end of a
 * track.
 */
void DTKSetRepeatMode(u32 repeat) {
    __DTKRepeatMode = repeat;
}

/**
 * Changes the player state if it is not already busy.
 * Stop cancels the drive stream; run resumes from pause or prepares the current track;
 * prepare readies the current track paused; pause stops the AI stream. Returns 0 only while busy.
 */
int DTKSetState(u32 state) {
    if (__DTKState == state) {
        return 1;
    }

    if (__DTKState == DTK_STATE_BUSY) {
        return 0;
    }

    switch (state) {
    case DTK_STATE_STOP:
        if (__DTKCurrentTrack) {
            __DTKState = DTK_STATE_BUSY;
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            AISetStreamPlayState(0);
            DVDCancelStreamAsync(&__block_for_set_state, __DTKCallbackForStop);
        }
        break;
    case DTK_STATE_RUN:
        if (__DTKState == DTK_STATE_PAUSE) {
            __DTKStartAi();
            __DTKState = DTK_STATE_RUN;
            if (__DTKCurrentTrack) {
                __DTKCheckUserCallback(__DTKCurrentTrack, 1);
            }
        } else if (__DTKCurrentTrack) {
            __DTKState = DTK_STATE_BUSY;
            __DTKPrepareCurrentTrack();
        } else {
            __DTKState = DTK_STATE_RUN;
        }
        __DTKTrackEnded = 0;
        break;
    case DTK_STATE_PREPARE:
        if (__DTKState == DTK_STATE_STOP) {
            if (__DTKCurrentTrack) {
                __DTKState = DTK_STATE_BUSY;
                __DTKPrepareCurrentTrackPaused();
            }
            __DTKTrackEnded = 0;
        }
        break;
    case DTK_STATE_PAUSE:
        AISetStreamPlayState(0);
        if (__DTKState == DTK_STATE_RUN) {
            __DTKState = DTK_STATE_PAUSE;
        }
        __DTKCheckUserCallback(__DTKCurrentTrack, 4);
        break;
    }

    return 1;
}

/**
 * Skips to the next track.
 * If playing, the drive stream is cancelled first and the skip finishes in a callback;
 * otherwise the track just changes. Returns 0 if busy or the playlist is empty.
 */
int DTKNextTrack(void) {
    if (__DTKState == DTK_STATE_BUSY) {
        return 0;
    }

    if (__DTKCurrentTrack) {
        __DTKTempState = __DTKState;
        __DTKState = DTK_STATE_BUSY;
        if (__DTKTempState == DTK_STATE_RUN) {
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            DVDCancelStreamAsync(&__block_for_next_track, __DTKCallbackForNextTrack);
        } else {
            __DTKForward();
            __DTKState = __DTKTempState;
        }

        return 1;
    }

    return 0;
}

/**
 * Goes back one track.
 * If playing, the drive stream is cancelled first and the change finishes in a callback;
 * otherwise the track just changes. Returns 0 if busy or the playlist is empty.
 */
int DTKPrevTrack(void) {
    if (__DTKState == DTK_STATE_BUSY) {
        return 0;
    }

    if (__DTKCurrentTrack) {
        __DTKTempState = __DTKState;
        __DTKState = DTK_STATE_BUSY;
        if (__DTKTempState == DTK_STATE_RUN) {
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            DVDCancelStreamAsync(&__block_for_prev_track, __DTKCallbackForPrevTrack);
        } else {
            __DTKBackward();
            __DTKState = __DTKTempState;
        }

        return 1;
    }

    return 0;
}

/** Obsolete: always returns 1. */
u32 DTKGetSampleRate(void) {
    return 1;  // obsolete
}

/** Returns the current repeat mode. */
u32 DTKGetRepeatMode(void) {
    return __DTKRepeatMode;
}

/** Returns whether the player is stopped, playing or paused. */
u32 DTKGetState(void) {
    return __DTKState;
}

/** Returns the stream play address last reported by the drive (stored by __DTKCallbackForPlaylist). */
u32 DTKGetPosition(void) {
    return __DTKPosition;
}

/** Returns the sample-count interval between track callbacks. */
u32 DTKGetInterruptFrequency(void) {
    return __DTKInterruptFrequency;
}

/** Returns the playlist entry that is the current track (the one playing or next to play). */
DTKTrack* DTKGetCurrentTrack(void) {
    return __DTKCurrentTrack;
}

/** Stores the stream volume and, if the player is running, applies it to the AI stream immediately. */
void DTKSetVolume(u8 left, u8 right) {
    __DTKVolumeL = left;
    __DTKVolumeR = right;
    if (__DTKState == DTK_STATE_RUN) {
        AISetStreamVolLeft(left);
        AISetStreamVolRight(right);
    }
}

/** Returns the stored volumes packed as (left << 8) | right. */
u16 DTKGetVolume(void) {
    return (__DTKVolumeL << 8) | __DTKVolumeR;
}
