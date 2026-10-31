// Action command: press A in time (ac_timing_wide); like ac_timing_a but with a wider success window.
#include "icon_ids.h"
#include "battle/ac/ac_table.h"
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "system.h"
#include <string.h>

// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on

// BattleActions.acFlags for this command (btlevtcmd_AcSetFlag).
enum {
    TIMING_WIDE_NO_SLIDE_IN = 0x1,     // the icons start in place instead of sliding in
    TIMING_WIDE_STAY_ON_SUCCESS = 0x2, // after a success the icons stay instead of sliding out
    TIMING_WIDE_STAY_ON_FAIL = 0x4,    // the same after a failure
    TIMING_WIDE_HOLD_AFTER_END = 0x8,  // when the window closes the command waits (state 0x3EB) with the icons shown
    TIMING_WIDE_SWAP_ICONS = 0x10,     // the two button icons are drawn the other way round
};

typedef struct TimingWideWork {
    s32 button;   // 0x0
    s8 mode;      // 0x4
    s32 frame;    // 0x8
    s32 state;    // 0xC
    s32 endTimer; // 0x10
} TimingWideWork;

#define TW_WORK(ac) ((TimingWideWork*)(ac)->work)

static void actionCommandDisp(f32 x, f32 y);

/**
 * Per-frame driver of action command 11, used by Mario's Fire Drive and Vivian's Infatuate.
 * Within params[1] frames the input must come between frames params[2] and params[3]:
 * params[0] 5 presses A, 0/1 lets go of the stick held left/right, 2/3 the same on the release edge,
 * 4 first waits for a tilt left.
 * outputParams[0] is 1 on success or -1 on a mistimed input, [2] whether the window is open now.
 * Timing out fails.
 */
s32 battleAcMain_TimingWide(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    TimingWideWork* tw = TW_WORK(ac);
    BattleACDispParams* disp = (BattleACDispParams*)&ac->disp;
    s32 autoCmd = 0;
    s32 pressed;

    if (ac->acUnit->badgesEquipped.AutoCommand) {
        autoCmd = 1;
    }

    switch (ac->acState) {
        case 0:
            memset(disp, 0, sizeof(BattleACDispParams));
            disp->iconX = -300.0f;
            disp->iconY = 0.0f;
            disp->slideTimer = 20;
            tw->state = 0;
            tw->frame = 0;
            switch (ac->params[0]) {
                case 5:
                    tw->button = 0x100;
                    tw->mode = 1;
                    break;
                case 0:
                    tw->button = 0x40000;
                    tw->mode = 0;
                    break;
                case 1:
                    tw->button = 0x80000;
                    tw->mode = 0;
                    break;
                case 2:
                    tw->button = 0x40000;
                    tw->mode = -1;
                    break;
                case 3:
                    tw->button = 0x80000;
                    tw->mode = -1;
                    break;
                default:
                    tw->button = 0x40000;
                    tw->mode = 0;
                    break;
            }
            ac->outputParams[0] = 0;
            ac->outputParams[1] = 0;
            ac->outputParams[2] = 0;
            ac->acState = 99;
            ac->result = 1;
            break;
        case 100:
            if ((ac->setupFlags & 1) && (ac->acUnit->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION)) {
                if (irand(100) >= 0) {
                    ac->setupParam = 0;
                    if (ac->params[2] > 0) {
                        ac->setupParam = irand(ac->params[2]);
                    }
                    if (ac->setupParam <= 0) {
                        ac->setupParam = ac->params[1] + 2;
                    }
                } else {
                    ac->setupParam = ac->params[2] + irand(ac->params[3] - ac->params[2]);
                }
                ac->acState = 0x3EA;
                tw->state = 2;
            } else {
                if (ac->params[0] == 4) {
                    ac->acState = 0x3E8;
                } else {
                    ac->acState = 0x3E9;
                }
                tw->state = 1;
            }
            break;
        case 0x3E8:
            if (BattlePadCheckTrigger(tw->button)) {
                ac->outputParams[1] = 1;
                ac->acState = 0x3E9;
            }
            break;
        case 0x3E9:
            tw->frame++;
            if (tw->frame > ac->params[1]) {
                ac->result = 0;
                ac->acState = 0x3EC;
                tw->state = 4;
                if ((s32)ac->acFlags & TIMING_WIDE_HOLD_AFTER_END) {
                    ac->acState = 0x3EB;
                    tw->state = 3;
                }
            } else {
                pressed = 0;
                switch (tw->mode) {
                    case 1:
                        if (BattlePadCheckTrigger(tw->button)) {
                            pressed = 1;
                        }
                        break;
                    case -1:
                        if (BattlePadCheckUp(tw->button)) {
                            pressed = 1;
                        }
                        break;
                    case 0:
                    default:
                        if (!BattlePadCheckNow(tw->button)) {
                            pressed = 1;
                        }
                        break;
                }
                if (tw->frame >= ac->params[2] && tw->frame < ac->params[3]) {
                    ac->outputParams[2] = 1;
                } else {
                    ac->outputParams[2] = 0;
                }
                if (autoCmd) {
                    if (ac->outputParams[2]) {
                        pressed = 1;
                    } else {
                        pressed = 0;
                    }
                }
                if (pressed) {
                    if (ac->outputParams[2]) {
                        ac->result = 2;
                        ac->resultCount++;
                        ac->outputParams[0] = 1;
                    } else {
                        ac->result = 0;
                        ac->outputParams[0] = -1;
                    }
                    ac->acState = 0x3EC;
                    tw->state = 4;
                    if ((s32)ac->acFlags & TIMING_WIDE_HOLD_AFTER_END) {
                        ac->acState = 0x3EB;
                        tw->state = 3;
                    }
                }
            }
            break;
        case 0x3EA:
            tw->frame++;
            ac->setupParam--;
            if (tw->frame > ac->params[1]) {
                ac->result = 0;
                return 0;
            }
            if (ac->setupParam < 0) {
                if (tw->frame >= ac->params[2] && tw->frame < ac->params[3]) {
                    ac->result = 2;
                    ac->resultCount++;
                    ac->outputParams[0] = 1;
                } else {
                    ac->result = 0;
                    ac->outputParams[0] = -1;
                }
                return 0;
            }
            break;
        case 0x3EB:
            break;
        case 0x3EC:
            tw->endTimer = 60;
            ac->acState = 0x3ED;
            tw->state = 5;
        case 0x3ED:
            tw->endTimer--;
            if (tw->endTimer <= 0) {
                ac->acState = 0x3EE;
                tw->state = 6;
            }
            break;
        case 0x3EE:
            ac->maincb = NULL;
            ac->dispcb = NULL;
            ac->resultcb = NULL;
            ac->deletecb = NULL;
            return 0;
    }
    return 1;
}

/** Returns the result word: 1 while running, 2 on success, 0 on failure. */
s32 battleAcResult_TimingWide(BattleWork* work) {
    return work->actionCommands.result;
}

/**
 * Display callback: slides the icon in from the left over 20 frames (acFlags bit 0 starts it in place),
 * and once the command ends keeps it up for 40 frames before sliding it out
 * unless acFlags bits 1/2 keep it there.
 */
void battleAcDisp_TimingWide(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = (BattleACDispParams*)&ac->disp;
    s32 show;
    switch (TW_WORK(ac)->state) {
        case 0:
        case 1:
        case 2:
            if ((s32)ac->acFlags & TIMING_WIDE_NO_SLIDE_IN) {
                disp->iconX = 30.0f;
            } else {
                disp->iconX = intplGetValue(4, -300.0f, 30.0f, 20 - disp->slideTimer, 20);
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->slideTimer > 0) {
                disp->slideTimer--;
            }
            break;
        case 3:
            actionCommandDisp(disp->iconX, disp->iconY);
            break;
        case 4:
        case 5:
            show = 1;
            if (((s32)ac->acFlags & TIMING_WIDE_STAY_ON_SUCCESS) && (ac->result & 2)) {
                show = 0;
            }
            if (((s32)ac->acFlags & TIMING_WIDE_STAY_ON_FAIL) && !(ac->result & 2)) {
                show = 0;
            }
            if (disp->slideTimer >= 40) {
                if (show) {
                    disp->iconX = intplGetValue(4, 30.0f, -300.0f, disp->slideTimer - 40, 20);
                } else {
                    disp->iconX = 30.0f;
                }
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->slideTimer < 60) {
                disp->slideTimer++;
            }
            break;
    }
}

/** Called by btlevtcmd_StopAC: starts the 60-frame end wait. */
void battleAcDelete_TimingWide(BattleWork* work) {
    work->actionCommands.acState = 0x3EC;
}

#define ICON(id)                                    \
    {                                               \
        Vec pos = {0.0f, 0.0f, 0.0f};               \
        pos.x = -200.0f + x;                        \
        pos.y = 50.0f + y;                          \
        iconDispGx(&pos, ICON_DISP_2D, (id), 1.0f); \
    }
/**
 * Draws the button or stick icon, flipping between its two poses as the cue
 * while the window is open (acFlags bit 4 swaps them after the input).
 */
static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    s32* frame = (s32*)&ac->disp;
    TimingWideWork* tw;
    u16 a;
    u16 b;
    camGetPtr(CAMERA_2D);
    tw = TW_WORK(ac);
    switch (tw->button) {
        case 0x100:
            b = ICON_065;
            a = ICON_064;
            break;
        case 0x200:
            b = ICON_067;
            a = ICON_066;
            break;
        case 0x400:
            b = ICON_069;
            a = ICON_068;
            break;
        case 0x800:
            b = ICON_06B;
            a = ICON_06A;
            break;
        case 0x40000:
            b = ICON_078;
            a = ICON_079;
            break;
        case 0x80000:
            b = ICON_07A;
            a = ICON_079;
            break;
        default:
            b = ICON_078;
            a = ICON_079;
            break;
    }
    switch (tw->state) {
        case 0:
            if (tw->mode > 0) {
                ICON(a)
            } else {
                ICON(b)
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if (!((s32)ac->acFlags & TIMING_WIDE_SWAP_ICONS)) {
                if (tw->mode > 0)
                    ICON(a)
                else
                    ICON(b)
            } else {
                if (tw->mode > 0)
                    ICON(b)
                else
                    ICON(a)
            }
            break;
        case 1:
            if (tw->mode != -1) {
                if (tw->frame >= ac->params[2] && tw->frame < ac->params[3]) {
                    if (tw->mode > 0)
                        ICON(b)
                    else
                        ICON(a)
                } else {
                    if (tw->mode > 0)
                        ICON(a)
                    else
                        ICON(b)
                }
            } else {
                if (tw->frame >= ac->params[2]) {
                    ICON(a)
                } else {
                    ICON(b)
                }
            }
            break;
    }
    (*frame)++;
}
