#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

static OSResetCallback ResetCallback;
static BOOL Down;
static BOOL LastState;
static OSTime HoldUp;
static OSTime HoldDown;

/**
 * PI interrupt handler for the console RESET button.
 * Waits up to 100 microseconds for the button to be released;
 * if it is still held it marks the button down,
 * masks the reset interrupt and calls (once) the callback set with OSSetResetCallback,
 * then acknowledges the interrupt in PI register 0.
 */
void __OSResetSWInterruptHandler(s16 exception, OSContext* context) {
    OSResetCallback callback;

    HoldDown = __OSGetSystemTime();
    while (__OSGetSystemTime() - HoldDown < OSMicrosecondsToTicks(100) &&
           !(__PIRegs[0] & 0x00010000)) {
        ;
    }
    if (!(__PIRegs[0] & 0x00010000)) {
        LastState = Down = TRUE;
        __OSMaskInterrupts(OS_INTERRUPTMASK_PI_RSW);
        if (ResetCallback) {
            callback = ResetCallback;
            ResetCallback = NULL;
            callback();
        }
    }
    __PIRegs[0] = 2;
}

/**
 * Installs the function the OS calls when the user presses the RESET button, and returns the previous callback.
 * Setting a callback unmasks the PI reset-switch interrupt (mask 0x200); setting NULL masks it.
 */
OSResetCallback OSSetResetCallback(OSResetCallback callback) {
    BOOL enabled;
    OSResetCallback prevCallback;

    enabled = OSDisableInterrupts();
    prevCallback = ResetCallback;
    ResetCallback = callback;

    if (callback) {
        __PIRegs[0] = 2;
        __OSUnmaskInterrupts(0x200);
    } else {
        __OSMaskInterrupts(0x200);
    }
    OSRestoreInterrupts(enabled);
    return prevCallback;
}

/**
 * Polls the RESET button (bit 16 of PI register 0, active low) and returns TRUE while it counts as pressed:
 * a press must last over 100 microseconds, and a release is held as pressed for 40 ms.
 * Surprising: if a reset-button timer was set with __OSSetResetButtonTimer
 * and that many minutes have passed since boot, it reports a pressed/released toggle every two seconds.
 */
BOOL OSGetResetButtonState(void) {
    BOOL enabled = OSDisableInterrupts();
    int state;
    u32 reg;
    OSTime now;

    now = __OSGetSystemTime();
    ASSERTLINE(158, 0 <= now);
    ASSERTLINE(159, HoldUp == 0 || HoldUp < now);
    ASSERTLINE(160, HoldDown == 0 || HoldDown < now);

    reg = __PIRegs[0];
    if (!(reg & 0x00010000)) {
        if (!Down) {
            Down = TRUE;
            state = HoldUp ? TRUE : FALSE;
            HoldDown = now;
        } else {
            state = HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown)
                        ? TRUE
                        : FALSE;
        }
    } else if (Down) {
        Down = FALSE;
        state = LastState;
        if (state) {
            HoldUp = now;
        } else {
            HoldUp = 0;
        }
    } else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
        state = TRUE;
    } else {
        state = FALSE;
        HoldUp = 0;
    }

    LastState = state;

    if (__gUnknown800030E3 & 0x1F) {
        OSTime fire = (__gUnknown800030E3 & 0x1F) * 60;
        fire = __OSStartTime + OSSecondsToTicks(fire);
        if (fire < now) {
            now -= fire;
            now = OSTicksToSeconds(now) / 2;
            if ((now & 1) == 0) {
                state = TRUE;
            } else {
                state = FALSE;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return state;
}

/** Older name for OSGetResetButtonState; returns the same value. */
int OSGetResetSwitchState(void) {
    return OSGetResetButtonState();
}

/**
 * Sets, in minutes (clamped to 31), the delay after
 * which OSGetResetButtonState starts reporting a simulated button press.
 * Stored in the low 5 bits of the byte at 0x800030E3 in low memory.
 */
void __OSSetResetButtonTimer(u8 min) {
    BOOL enabled = OSDisableInterrupts();
    if (min > 0x1F) {
        min = 0x1F;
    }

    __gUnknown800030E3 &= ~0x1F;
    __gUnknown800030E3 |= min;
    OSRestoreInterrupts(enabled);
}
