#include <dolphin.h>
#include <dolphin/si.h>

static void (*SamplingCallback)();
u32 __SISteeringEnableBits;

/**
 * Starts polling the steering wheel on chan: marks it enabled,
 * discards any stale response and sets its poll command (0x300680).
 */
void __SISteeringEnable(s32 chan) {
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = 0x80000000 >> chan;
    if (!(__SISteeringEnableBits & chanBit)) {
        __SISteeringEnableBits |= chanBit;
        SIGetResponse(chan, &data);

        cmd = 0x300680;
        SISetCommand(chan, cmd);
        SIEnablePolling(__SISteeringEnableBits);
    }
}

/** Stops polling the steering wheel on chan. */
void __SISteeringDisable(s32 chan) {
    u32 chanBit;

    chanBit = 0x80000000 >> chan;
    SIDisablePolling(chanBit);
    __SISteeringEnableBits &= ~chanBit;
}

/**
 * Copies the latest polled state of the wheel on chan (buttons, misc bits,
 * steering position with the 0x80 bias removed, gas, brake, left and right) into status.
 * Returns 0, or -1 no wheel, -2 busy, -3 bad transfer; status->err holds the same code.
 */
s32 SIReadSteering(s32 chan, SISteeringStatus* status) {
    BOOL enabled;
    SISteeringControl* sc;
    u32 data[2];
    u32 chanBit;
    u32 sr;
    s32 ret;

    enabled = OSDisableInterrupts();
    sc = &__SISteering[chan];
    chanBit = 0x80000000 >> chan;

    if (SIIsChanBusy(chan)) {
        sc->ret = -2;
    } else if (!(__SISteeringEnableBits & chanBit)) {
        sc->ret = -1;
    } else {
        sr = SIGetStatus(chan);
        if (sr & 8) {
            SIGetResponse(chan, &data);
            __SISteeringDisable(chan);
            sc->ret = -1;
        } else if ((SIGetResponse(chan, &data) == 0) || (data[0] & 0x80000000)) {
            sc->ret = -3;
        } else {
            sc->ret = 0;
            if (status != 0) {
                status->button = data[0] >> 0x10;
                status->misc = data[0] >> 8;
                status->steering = (data[0] & 0xFF) - 0x80;
                status->gas = data[1] >> 0x18;
                status->brake = data[1] >> 0x10;
                status->left = data[1] >> 8;
                status->right = data[1];
            }
        }
    }

    if (status != 0) {
        status->err = sc->ret;
    }

    ret = sc->ret;
    OSRestoreInterrupts(enabled);
    return ret;
}

/** SI polling handler that runs the user's steering sampling callback inside a scratch OS context. */
static void SamplingHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptionContext;

    if (SamplingCallback != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        SamplingCallback();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void (* SISetSteeringSamplingCallback(void (*callback)()))() {
    void (*prev)() = SamplingCallback;
    SamplingCallback = callback;

    if (callback != 0) {
        SIRegisterPollingHandler(SamplingHandler);
    } else {
        SIUnregisterPollingHandler(SamplingHandler);
    }

    return prev;
}

/**
 * Sends a control command to an enabled wheel: control (masked with 0x600) selects the motor/force action
 * and level (-128 to 128) is its strength, written as the wheel's poll command.
 */
void SIControlSteering(s32 chan, u32 control, s32 level) {
    BOOL enabled;
    u32 chanBit;
    u32 command;

    control &= 0x600;

    if (level <= -0x80) {
        command = 0;
    } else if (level >= 0x80) {
        command = 0x100;
    } else {
        command = level + 0x80;
    }

    command |= control;
    command &= 0x7FF;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    if (__SISteeringEnableBits & chanBit) {
        command |= 0x300000;
        SISetCommand(chan, command);
        SITransferCommands();
    }

    OSRestoreInterrupts(enabled);
}
