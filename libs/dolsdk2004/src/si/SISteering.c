#include <dolphin.h>
#include <dolphin/si.h>

#include "__si.h"

// prototypes
static void DefaultCallback(s32, s32);
static s32 SISteeringBegin(SISteeringControl* sc, SISteeringCallback callback);
static void ResetProc(s32 chan);
static int OnReset(BOOL final);

SISteeringControl __SISteering[4];
BOOL __SIResetSteering;

/** Reset hook registered with the OS (priority 127) so the serial interface is shut down on reset. */
static OSResetFunctionInfo ResetFunctionInfo = {OnReset, 127};

/**
 * Initialises the steering wheel (racing controller) support once:
 * clears each port's state and wait queue, refreshes the sampling rate and registers the reset hook.
 */
void SIInitSteering(void) {
    static BOOL initialized;
    SISteeringControl* sc;
    s32 chan;

    if (!initialized) {
        initialized = TRUE;

        for (chan = 0; chan < 4; chan++) {
            sc = &__SISteering[chan];
            sc->ret = 0;
            OSInitThreadQueue(&sc->threadQueue);
        }

        SIRefreshSamplingRate();
        __SIResetSteering = 0;
        OSRegisterResetFunction(&ResetFunctionInfo);
    }
}

/** Empty callback used when the caller gives none. */
static void DefaultCallback(s32, s32) {}

/**
 * Reserves the port's steering state for a new operation by storing callback;
 * returns -2 if one is already in progress.
 */
static s32 SISteeringBegin(SISteeringControl* sc, SISteeringCallback callback) {
    BOOL enabled;
    s32 ret;

    callback = callback != 0 ? callback : DefaultCallback;

    enabled = OSDisableInterrupts();
    if (sc->callback) {
        ret = -2;
    } else {
        sc->callback = callback;
        ret = 0;
    }

    OSRestoreInterrupts(enabled);
    return ret;
}

/** After the reset command finishes, enables polling of the wheel on chan unless the system is resetting. */
static void ResetProc(s32 chan) {
    SISteeringControl* sc = &__SISteering[chan];

    if (sc->ret == 0 && __SIResetSteering == 0) {
        __SISteeringEnable(chan);
    }
}

/**
 * Sends the reset command (0xFF) to the steering wheel on chan and then starts polling it;
 * callback runs with the result. Returns 0, or -2 if busy.
 */
s32 SIResetSteeringAsync(s32 chan, SISteeringCallback callback) {
    SISteeringControl* sc;
    s32 ret;

    sc = &__SISteering[chan];
    ret = SISteeringBegin(sc, callback);
    if (ret != 0) {
        return ret;
    }

    sc->output[0] = 0xFF;
    return __SISteeringTransfer(chan, 1, 3, ResetProc);
}

/** Blocking version of SIResetSteeringAsync: waits for the reset to finish and returns its result. */
s32 SIResetSteering(s32 chan) {
    SISteeringControl* sc;
    s32 ret;

#ifndef DEBUG
    u32 padding;
#endif

    sc = &__SISteering[chan];
    ret = SIResetSteeringAsync(chan, __SISteeringSyncCallback);
    if (ret != 0) {
        return ret;
    }

    return __SISteeringSync(chan);
}

/**
 * OS reset hook (priority 127): tells enabled wheels to stop (control 0x400, level 0), waits three retraces,
 * then disables their polling and lets the reset proceed.
 */
static int OnReset(BOOL final) {
    static s32 count;
    s32 chan;

    if (!__SIResetSteering) {
        __SIResetSteering = TRUE;

        for (chan = 0; chan < 4; chan++) {
            if ((0x80000000 >> chan) & __SISteeringEnableBits) {
                SIControlSteering(chan, 0x400, 0);
            }
        }

        count = VIGetRetraceCount();
    }

    if ((s32)VIGetRetraceCount() - count > 2) {
        while (__SISteeringEnableBits != 0) {
            __SISteeringDisable(__cntlzw(__SISteeringEnableBits));
        }
        return 1;
    }

    return 0;
}
