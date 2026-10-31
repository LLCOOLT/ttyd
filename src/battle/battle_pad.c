/* "battle_pad" - Battle (Game)Pad Helper
 *
 * Function: helper functions for reading/writing controller inputs
 */
#include "battle/battle_pad.h"
#include "battle/battle.h"
#include "mario/mariost.h"

// inlining off for BattlePadInit, BattlePadManager, BtlPad_WorkInit and 13 more, as in the original (the object differs without it)
#pragma dont_inline on
// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on

void BattlePadInit(void) {
    int i;

    for (i = 0; i < 4; i++) {
        BtlPad_WorkInit(&_battleWorkPointer->padWork[i]);
    }
}

void BattlePadManager(void) {
    int i;

    for (i = 0; i < 4; i++) {
        BtlPad_WorkUpdate(&_battleWorkPointer->padWork[i], i);
    }
}

void BtlPad_WorkInit(BattleWorkPad* pad) {
    int i;

    for (i = 0; i < 2; i++) {
        pad->padData[i].button = 0;
        pad->padData[i].stickX = 0;
        pad->padData[i].stickY = 0;
        pad->padData[i].substickX = 0;
        pad->padData[i].substickY = 0;
        pad->padData[i].triggerLeft = 0;
        pad->padData[i].triggerRight = 0;
        pad->padData[i].analogA = 0;
        pad->padData[i].analogB = 0;
        pad->padData[i].err = 0;
    }

    for (i = 0; i < 30; i++) {
        pad->buttonsPressedHistory[i] = 0;
        pad->buttonsRepeatHistory[i] = 0;
        pad->buttonsHistory[i] = 0;
    }

    pad->holdRepeatState = 0;
    pad->holdRepeatFrameCounter = 0;
}

void BtlPad_WorkUpdate(BattleWorkPad* pad, s32 chan) {
    int i, repeat;

    pad->padData[1] = pad->padData[0];

    for (i = 28; i >= 0; i--) {
        pad->buttonsPressedHistory[i + 1] = pad->buttonsPressedHistory[i];
        pad->buttonsRepeatHistory[i + 1] = pad->buttonsRepeatHistory[i];
        pad->buttonsHistory[i + 1] = pad->buttonsHistory[i];
    }

    // after moving old data back, write new data
    pad->padData[0].button = (u16)gp->button[chan];
    pad->padData[0].stickX = gp->stickX[chan];
    pad->padData[0].stickY = gp->stickY[chan];
    pad->padData[0].substickX = gp->substickX[chan];
    pad->padData[0].substickY = gp->substickY[chan];
    pad->padData[0].triggerLeft = gp->triggerLeft[chan];
    pad->padData[0].triggerRight = gp->triggerRight[chan];
    pad->padData[0].analogA = 0;
    pad->padData[0].analogB = 0;
    pad->buttonsHistory[0] = pad->padData[0].button;
    pad->buttonsRepeatHistory[0] = gp->buttonRepeat[chan];
    pad->buttonsPressedHistory[0] = gp->buttonNew[chan];
    pad->buttonsReleasedHistory[0] = gp->buttonUp[chan];

    if (pad->padData[0].stickY >= 30) {
        pad->buttonsHistory[0] |= BTL_PAD_STICK_UP;
    }
    if (pad->padData[0].stickY <= -30) {
        pad->buttonsHistory[0] |= BTL_PAD_STICK_DOWN;
    }

    if (pad->padData[0].stickX <= -30) {
        pad->buttonsHistory[0] |= BTL_PAD_STICK_LEFT;
    }
    if (pad->padData[0].stickX >= 30) {
        pad->buttonsHistory[0] |= BTL_PAD_STICK_RIGHT;
    }

    if (pad->padData[0].substickY >= 30) {
        pad->buttonsHistory[0] |= BTL_PAD_SUBSTICK_UP;
    }
    if (pad->padData[0].substickY <= -30) {
        pad->buttonsHistory[0] |= BTL_PAD_SUBSTICK_DOWN;
    }

    if (pad->padData[0].substickX <= -30) {
        pad->buttonsHistory[0] |= BTL_PAD_SUBSTICK_LEFT;
    }
    if (pad->padData[0].substickX >= 30) {
        pad->buttonsHistory[0] |= BTL_PAD_SUBSTICK_RIGHT;
    }

    pad->buttonsPressedHistory[0] |= pad->buttonsHistory[0] & ~pad->buttonsHistory[1] & 0xFFFF0000;

    if (!pad->buttonsHistory[0]) {
        pad->buttonsRepeatHistory[0] = 0;
        pad->holdRepeatState = 0;
        pad->holdRepeatFrameCounter = 0;
    } else if (pad->buttonsHistory[0] != pad->buttonsHistory[1]) {
        pad->buttonsRepeatHistory[0] |= pad->buttonsHistory[0] & 0xFFFF0000;
        pad->buttonsRepeatHistory[0] &= pad->buttonsPressedHistory[0] & 0xFFFF0000 | 0xFFFF;
        pad->holdRepeatState = 1;
        pad->holdRepeatFrameCounter = 0;
    } else {
        repeat = 8;
        pad->holdRepeatFrameCounter++;
        if (pad->holdRepeatFrameCounter >= (pad->holdRepeatState == 1 ? 16 : repeat)) {
            pad->buttonsRepeatHistory[0] |= pad->buttonsHistory[0] & 0xFFFF0000;
            pad->holdRepeatState = 2;
            pad->holdRepeatFrameCounter = 0;
        }
    }
    pad->buttonsReleasedHistory[0] |= pad->buttonsHistory[1] & (pad->buttonsHistory[1] ^ pad->buttonsHistory[0]) & 0xFFFF0000;
}

u32 BattlePadGetTrigger(void) {
    return _battleWorkPointer->padWork[0].buttonsPressedHistory[0];
}

u32 BattlePadGetNow(void) {
    return _battleWorkPointer->padWork[0].buttonsHistory[0];
}

BOOL BattlePadCheckTrigger(s32 mask) {
    return BattlePadMultiCheckTrigger(0, mask);
}

BOOL BattlePadMultiCheckTrigger(s32 chan, s32 mask) {
    u32* history = _battleWorkPointer->padWork[chan].buttonsPressedHistory;
    return history[0] & mask;
}

BOOL BattlePadCheckRecordTrigger(s32 frame, s32 mask) {
    return BattlePadMultiCheckRecordTrigger(0, frame, mask);
}

u32 BattlePadMultiCheckRecordTrigger(s32 chan, s32 frame, s32 mask) {
    BattleWorkPad* pad = &_battleWorkPointer->padWork[chan];
    return pad->buttonsPressedHistory[frame] & mask;
}

s32 BattlePadCheckNow(s32 mask) {
    return BattlePadMultiCheckNow(0, mask);
}

BOOL BattlePadMultiCheckNow(s32 chan, s32 mask) {
    u32* history = _battleWorkPointer->padWork[chan].buttonsHistory;
    return history[0] & mask;
}

s32 BattlePadCheckUp(s32 mask) {
    return BattlePadMultiCheckUp(0, mask);
}

u32 BattlePadMultiCheckUp(s32 chan, s32 mask) {
    u32* history = _battleWorkPointer->padWork[chan].buttonsReleasedHistory;
    return history[0] & mask;
}

s32 BattlePadCheckRepeat(s32 mask) {
    return BattlePadMultiCheckRepeat(0, mask);
}

u32 BattlePadMultiCheckRepeat(s32 chan, s32 mask) {
    u32* history = _battleWorkPointer->padWork[chan].buttonsRepeatHistory;
    return history[0] & mask;
}
