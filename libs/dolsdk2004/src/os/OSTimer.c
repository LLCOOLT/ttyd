#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

struct Timer {
    OSTimerCallback callback;
    u32 currval;
    u32 startval;
    u32 mode;
    BOOL stopped;
    BOOL initialized;
};
static struct Timer Timer;

// prototypes
static void DecrementerExceptionHandler(__OSException exception, OSContext* context);

/**
 * Installs the function called when the decrementer timer expires and returns the previous callback.
 * It also stops the timer, so OSStartTimer must be called again.
 */
OSTimerCallback OSSetTimerCallback(OSTimerCallback callback) {
    OSTimerCallback prevCallback;

#if DEBUG
    if(!Timer.initialized) {
        OSPanic(__FILE__, 135, "OSSetTimerCallback(): timer is not initialized.");
    }
#endif

    Timer.stopped = TRUE;
    prevCallback = Timer.callback;
    Timer.callback = callback;
    return prevCallback;
}

/**
 * Sets up the decrementer timer to count time ticks; mode 1 reloads and repeats, mode 2 stops after firing once.
 * The first call registers the decrementer exception handler (exception 8).
 */
void OSInitTimer(u32 time, u32 mode) {
#if DEBUG
    if (time >= 0x80000000) {
        OSPanic(__FILE__, 159, "OSInitTimer(): time param must be less than 0x80000000.");
    }
#endif

    Timer.stopped = TRUE;
    Timer.currval = time;
    Timer.startval = time;
    Timer.mode = mode;

    if (!Timer.initialized) {
        __OSSetExceptionHandler(8, &DecrementerExceptionHandler);
        Timer.initialized = TRUE;
        Timer.callback = 0;
#if DEBUG
        OSReport("Timer initialized\n");
#endif
    }
}

/** Loads the saved count into the decrementer register and marks the timer running. */
void OSStartTimer(void) {
    BOOL enabled;

#if DEBUG
    if (!Timer.initialized) {
        OSPanic(__FILE__, 192, "OSStartTimer(): timer is not initialized.");
    }
#endif
    enabled = OSDisableInterrupts();
    PPCMtdec(Timer.currval);
    Timer.stopped = FALSE;
    OSRestoreInterrupts(enabled);
}

/**
 * Stops the timer and saves the remaining decrementer count
 * so a later start continues from there (0 if it already went negative).
 */
void OSStopTimer(void) {
    BOOL enabled;

#if DEBUG
    if (!Timer.initialized) {
        OSPanic(__FILE__, 216, "OSStopTimer(): timer is not initialized.");
    }
#endif

    enabled = OSDisableInterrupts();
    if (!Timer.stopped) {
        Timer.stopped = TRUE;
        Timer.currval = PPCMfdec();
        if (Timer.currval & 0x80000000) {
            Timer.currval = 0;
        }
    }
    OSRestoreInterrupts(enabled);
}

/**
 * C part of the decrementer exception: in repeat mode reloads the start value, in one-shot mode stops the timer,
 * calls the user callback, then resumes the interrupted context.
 */
static void DecrementerExceptionCallback(__OSException exception, OSContext* context) {
    OSContext exceptionContext;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (!Timer.stopped) {
        if (Timer.mode == 1) {
            PPCMtdec(Timer.startval);
        }
        if (Timer.mode == 2) {
            Timer.stopped = TRUE;
        }
        if (Timer.callback) {
            Timer.callback();
        }
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}

#ifdef __GEKKO__
/**
 * Assembly entry for the decrementer exception:
 * saves r0-r2, r6-r31 and GQR1-7 into the interrupted context, then branches to DecrementerExceptionCallback.
 */
static asm void DecrementerExceptionHandler(__OSException exception,
                                            register OSContext* context) {
    nofralloc

    stw r0, context->gpr[0]
    stw r1, context->gpr[1]
    stw r2, context->gpr[2]
    stmw r6, context->gpr[6]

    mfspr r0, GQR1
    stw r0, context->gqr[1]
    mfspr r0, GQR2
    stw r0, context->gqr[2]
    mfspr r0, GQR3
    stw r0, context->gqr[3]
    mfspr r0, GQR4
    stw r0, context->gqr[4]
    mfspr r0, GQR5
    stw r0, context->gqr[5]
    mfspr r0, GQR6
    stw r0, context->gqr[6]
    mfspr r0, GQR7
    stw r0, context->gqr[7]

    stwu r1, -0x8(r1)
    b DecrementerExceptionCallback
}
#endif
