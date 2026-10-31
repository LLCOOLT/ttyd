// Action command: power gauge (ac_power_gauge); mash the button to charge the gauge before time runs out.
#include "icon_ids.h"
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "system.h"
#include <string.h>
#include "version.h"
// FAKE: ac_power_gauge.c calls BattleACGetButtonIcon through this prototype (the types it was compiled with) instead of the one in battle/battle_ac.h; same registers, behaviour-identical.
typedef s32 (*BattleACGetButtonIconRetS32Fn)(s32, s32);

// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on

typedef struct PowerGaugeWork {
    s32 frame;     // 0x0
    f32 gauge;     // 0x4
    s32 frame2;    // 0x8
    s32 maxFrames; // 0xC
    s8 autoFail;   // 0x10
    s8 phase;      // 0x11
    s8 mode;       // 0x12
    u32 button;    // 0x14
    s32 endTimer;  // 0x18
} PowerGaugeWork;

#define PG_WORK(ac) ((PowerGaugeWork*)(ac)->work)

#define ICONGX ((void (*)(Vec*, s32, s32, f32))iconDispGx)
static void actionCommandDisp(f32 x, f32 y);

/**
 * Per-frame driver of action command 15, used by Bobbery's Bomb, Yoshi's Gulp and Ms. Mowz's Kiss Thief.
 * A gauge fills over params[1] frames (curve params[3]) and stays full for params[2] more.
 * params[0] 0/1: press L+R or A while it is at params[4] or above;
 * 2/3: hold A or R (within 120 frames) to fill it and release at params[4] or above.
 * acFlags bit 0 fills only while held. Running out of time fails.
 */
s32 battleAcMain_PowerGauge(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    PowerGaugeWork* pw = PG_WORK(ac);
    BOOL isAuto = FALSE;
    BattleACDispParams* disp = (BattleACDispParams*)&ac->disp;

    if (ac->acUnit->badgesEquipped.AutoCommand) {
        isAuto = TRUE;
    }

    switch (ac->acState) {
        case 0:
            memset(disp, 0, 0x2C);
            disp->iconX = -300.0f;
            disp->iconY = 0.0f;
            disp->slideTimer = 20;
            disp->gaugeRatio = 0.0f;
            disp->color = (GXColor){255, 255, 255, 255};
            pw->frame = 0;
            pw->frame2 = 0;
            ac->outputParams[0] = 0;
            ac->acState = 99;
            ac->result = 1;
            pw->maxFrames = ac->params[1] + ac->params[2];
            pw->gauge = 0.0f;
            switch (ac->params[0]) {
                case 0:
                    pw->mode = 1;
                    pw->button = 0x60;
                    pw->phase = 1;
                    ac->outputParams[0] = 1;
                    break;
                case 1:
                    pw->mode = 1;
                    pw->button = 0x100;
                    pw->phase = 1;
                    ac->outputParams[0] = 1;
                    break;
                case 2:
                    pw->mode = 0;
                    pw->button = 0x100;
                    pw->phase = 0;
                    break;
                case 3:
                    pw->mode = 0;
                    pw->button = 0x20;
                    pw->phase = 0;
                    break;
                default:
                    pw->mode = 1;
                    pw->button = 0x100;
                    pw->phase = 1;
                    ac->outputParams[0] = 1;
                    break;
            }
            break;
        case 99:
            break;
        case 100:
            if ((ac->setupFlags & AC_SETUP_FLAG_CONFUSED_AUTO) && (ac->acUnit->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION)) {
                if (irand(100) >= 0) {
                    ac->setupParam = 30;
                    pw->autoFail = 0;
                } else {
                    pw->autoFail = 1;
                    ac->setupParam = 30;
                }
                ac->outputParams[0] = 1;
                ac->acState = 1002;
                break;
            }
            if (pw->mode) {
                ac->acState = 1001;
            } else {
                ac->acState = 1000;
            }
            if (pw->mode) {
                BattleAcGaugeSeInit();
            }
        case 1000:
        case 1001:
            pw->frame++;
            switch (pw->phase) {
                case 0:
                    if (!pw->mode) {
                        if (pw->button == BattlePadGetNow() || isAuto) {
                            pw->phase = 1;
                            ac->acState = 1001;
                            pw->frame = 0;
                            ac->outputParams[0] = 1;
                            BattleAcGaugeSeInit();
                        }
                    }
                    break;
                case 1:
                    if (pw->mode) {
                        if (pw->button == BattlePadGetNow()) {
                            if (BattlePadCheckTrigger(pw->button)) {
                                pw->phase = 2;
                            }
                        }
                    } else {
                        if (!BattlePadCheckNow(pw->button)) {
                            if (BattlePadCheckUp(pw->button)) {
                                pw->phase = 2;
                            }
                        }
                    }
                    break;
            }
            if (!(ac->acFlags & 1)) {
                pw->frame2++;
            } else if (pw->phase == 1) {
                pw->frame2++;
            }
            if (ac->acState == 1000) {
                if (pw->frame > 120) {
                    pw->frame = 0;
                    ac->result = 0;
                    pw->gauge = 0.0f;
                    ac->acState = 1003;
                    ac->outputParams[0] = 2;
                    break;
                }
            } else if (pw->frame > pw->maxFrames) {
                pw->frame = 0;
                ac->result = 0;
                pw->gauge = 101.0f;
                ac->acState = 1003;
                break;
            }
            if (pw->frame <= ac->params[1]) {
                pw->gauge = intplGetValue(ac->params[3], 0.0f, 100.0f, pw->frame2, ac->params[1]);
#if VERSION >= VERSION_US
                if (pw->gauge > 100.0f) {
                    pw->gauge = 100.0f;
                }
#endif
            } else {
                pw->gauge = 100.0f;
            }
            BattleAcGaugeSeUpdate(pw->gauge);
            if (isAuto) {
                if (pw->gauge >= (f32)ac->params[4]) {
                    pw->phase = 2;
                } else {
                    pw->phase = 1;
                }
            }
            if (pw->phase == 2) {
                if (pw->gauge < (f32)ac->params[4]) {
                    ac->result = 0;
                    ac->result &= ~2;
                } else {
                    ac->result = 2;
                    ac->resultCount++;
                }
                ac->acState = 1003;
            }
            break;
        case 1002:
            ac->setupParam--;
            if (ac->setupParam < 0) {
                if (pw->autoFail) {
                    ac->result = 2;
                    ac->resultCount++;
                } else {
                    ac->result = 0;
                }
                ac->doneFlags |= AC_DONE_FLAG_FINISHED;
                pw->endTimer = 60;
                ac->acState = 1005;
                return 0;
            }
            break;
        case 1003:
            ac->acState = 1004;
        case 1004:
            ac->doneFlags |= AC_DONE_FLAG_FINISHED;
            BattleAcGaugeSeDelete();
            pw->endTimer = 60;
            ac->acState = 1005;
        case 1005:
            pw->endTimer--;
            if (pw->endTimer <= 0) {
                ac->acState = 1006;
            }
            break;
        case 1006:
            ac->maincb = NULL;
            ac->dispcb = NULL;
            ac->resultcb = NULL;
            ac->deletecb = NULL;
            return 0;
    }
    return 1;
}

/** Returns the result word: 1 while running, 2 on success, 0 on failure. */
s32 battleAcResult_PowerGauge(BattleWork* work) {
    return work->actionCommands.result;
}

/**
 * Display callback: slides the gauge in from the left over 20 frames,
 * and once the command ends keeps it up for 40 frames before sliding it back out.
 */
void battleAcDisp_PowerGauge(CameraId cameraId, BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = (BattleACDispParams*)&ac->disp;
    switch (ac->acState) {
        case 99:
            disp->iconX = intplGetValue(4, -300.0f, 30.0f, 20 - disp->slideTimer, 20);
        case 100:
        case 1000:
        case 1001:
        case 1003:
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->slideTimer > 0) {
                disp->slideTimer--;
            }
            break;
        case 1004:
        case 1005:
            if (disp->slideTimer >= 40) {
                disp->iconX = intplGetValue(4, 30.0f, -300.0f, disp->slideTimer - 40, 20);
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

/** Called by btlevtcmd_StopAC: unless the command already finished, stops the gauge sound and starts the end wait. */
void battleAcDelete_PowerGauge(BattleWork* work) {
    if (!(work->actionCommands.doneFlags & AC_DONE_FLAG_FINISHED)) {
        work->actionCommands.acState = 1004;
    }
}

/**
 * Draws the gauge with its params[4] threshold (acFlags bit 1 hides it), the threshold marker or,
 * with acFlags bit 2, a star that lights in the zone (bit 3 shifts it left), and the button icons,
 * flashed as a cue to press or release.
 */
static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    PowerGaugeWork* pw;
    s32 a, b, c, d;
    BattleACDispParams* disp = (BattleACDispParams*)&ac->disp;
    f32 ratio;
    u32 flags;

    camGetPtr(CAMERA_2D);
    pw = PG_WORK(ac);
    ratio = pw->gauge / 100.0f;
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    disp->gaugeRatio = ratio;

    if (ac->acFlags & 2) {
        BattleAcDrawGauge((s32)x, (s32)y, 0xB2, ratio, 1, 100, 100, 100, 0);
    } else {
        BattleAcDrawGauge((s32)x, (s32)y, 0xB2, ratio, 2, ac->params[4], 100, 100, 0);
    }

    flags = ac->acFlags;
    if (!(flags & 4)) {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = -288.0f + x + (f32)(ac->params[4] * 0xB0) / 100.0f;
        pos.y = 45.0f + y;
        ICONGX(&pos, ICON_DISP_2D, ICON_096, 1.0f);
    } else {
        s32 icon;
        if (pw->gauge >= (f32)ac->params[4] && pw->gauge <= 100.0f) {
            icon = ICON_095;
        } else {
            icon = ICON_091;
        }
        if (flags & 8) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = 120.0f + (-200.0f + x) - 12.0f;
            pos.y = 18.0f + y;
            ICONGX(&pos, ICON_DISP_2D, icon, 1.0f);
        } else {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = 120.0f + (-200.0f + x);
            pos.y = 18.0f + y;
            ICONGX(&pos, ICON_DISP_2D, icon, 1.0f);
        }
    }

    switch (ac->params[0]) {
        case 0:
            a = ICON_07F;
            b = ICON_07E;
            c = ICON_081;
            d = ICON_080;
            break;
        case 1:
            a = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_BUTTON_A, 1);
            b = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_BUTTON_A, 0);
            c = 0;
            d = 0;
            break;
        case 2:
            a = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_BUTTON_A, 1);
            b = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_BUTTON_A, 0);
            c = 0;
            d = 0;
            break;
        case 3:
            a = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_TRIGGER_R, 1);
            b = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_TRIGGER_R, 0);
            c = 0;
            d = 0;
            break;
    }

    switch (ac->acState) {
        case 99:
        case 100:
        case 1003:
        case 1004:
        case 1005:
            if ((u16)c) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                f32 px = -225.0f + x;
                f32 py = 80.0f + y;
                pos.x = px;
                pos.y = py;
                ICONGX(&pos, ICON_DISP_2D, b, 1.0f);
                {
                    Vec pos2 = {0.0f, 0.0f, 0.0f};
                    pos2.x = 56.0f + px;
                    pos2.y = py;
                    ICONGX(&pos2, ICON_DISP_2D, d, 1.0f);
                }
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = 28.0f + (-225.0f + x);
                pos.y = 80.0f + y;
                ICONGX(&pos, ICON_DISP_2D, b, 1.0f);
            }
            break;
        case 1000:
        case 1001:
            if (pw->mode) {
                if (pw->gauge >= (f32)ac->params[4] && pw->gauge <= 100.0f) {
                    if ((u16)c) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        f32 px = -225.0f + x;
                        f32 py = 80.0f + y;
                        pos.x = px;
                        pos.y = py;
                        ICONGX(&pos, ICON_DISP_2D, a, 1.0f);
                        {
                            Vec pos2 = {0.0f, 0.0f, 0.0f};
                            pos2.x = 56.0f + px;
                            pos2.y = py;
                            ICONGX(&pos2, ICON_DISP_2D, c, 1.0f);
                        }
                    } else {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = 28.0f + (-225.0f + x);
                        pos.y = 80.0f + y;
                        ICONGX(&pos, ICON_DISP_2D, a, 1.0f);
                    }
                } else {
                    if ((u16)c) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        f32 px = -225.0f + x;
                        f32 py = 80.0f + y;
                        pos.x = px;
                        pos.y = py;
                        ICONGX(&pos, ICON_DISP_2D, b, 1.0f);
                        {
                            Vec pos2 = {0.0f, 0.0f, 0.0f};
                            pos2.x = 56.0f + px;
                            pos2.y = py;
                            ICONGX(&pos2, ICON_DISP_2D, d, 1.0f);
                        }
                    } else {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = 28.0f + (-225.0f + x);
                        pos.y = 80.0f + y;
                        ICONGX(&pos, ICON_DISP_2D, b, 1.0f);
                    }
                }
            } else {
                if ((pw->gauge >= (f32)ac->params[4] && pw->gauge <= 100.0f) || (s32)ac->outputParams[0] == 0) {
                    if ((u16)c) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        f32 px = -225.0f + x;
                        f32 py = 80.0f + y;
                        pos.x = px;
                        pos.y = py;
                        ICONGX(&pos, ICON_DISP_2D, b, 1.0f);
                        {
                            Vec pos2 = {0.0f, 0.0f, 0.0f};
                            pos2.x = 56.0f + px;
                            pos2.y = py;
                            ICONGX(&pos2, ICON_DISP_2D, d, 1.0f);
                        }
                    } else {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = 28.0f + (-225.0f + x);
                        pos.y = 80.0f + y;
                        ICONGX(&pos, ICON_DISP_2D, b, 1.0f);
                    }
                } else {
                    if ((u16)c) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        f32 px = -225.0f + x;
                        f32 py = 80.0f + y;
                        pos.x = px;
                        pos.y = py;
                        ICONGX(&pos, ICON_DISP_2D, a, 1.0f);
                        {
                            Vec pos2 = {0.0f, 0.0f, 0.0f};
                            pos2.x = 56.0f + px;
                            pos2.y = py;
                            ICONGX(&pos2, ICON_DISP_2D, c, 1.0f);
                        }
                    } else {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = 28.0f + (-225.0f + x);
                        pos.y = 80.0f + y;
                        ICONGX(&pos, ICON_DISP_2D, a, 1.0f);
                    }
                }
            }
            break;
    }
}
