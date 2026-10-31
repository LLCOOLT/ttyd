// Action command: press the button shown on screen (ac_button_down); face buttons and triggers.
#include "battle/battle.h"
#include <dolphin/pad.h>
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/icondrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#include "icon_ids.h"
#include "libc_decls.h"
// FAKE: ac_button_down.c calls iconDispGx through this prototype (the types it was compiled with) instead of the one in driver/icondrv.h; same registers, behaviour-identical.
typedef void (*IconDispGxS32S32Fn)(Vec*, s32, s32, f32);

typedef struct BDWork {
    s32 timer;
    s32 sndCount;
    u32 button[13];
    s32 pressed[13];
    s32 endTimer;
} BDWork;

/**
 * Buttons the button-press command can ask for: A, B, X, Y, then L, R and Z;
 * random picks use the first four or all seven.
 * Used by Tornado Jump's second part and Vivian's Veil and Fiery Jinx.
 */
static u32 _button_table[7] = {PAD_BUTTON_A, PAD_BUTTON_B, PAD_BUTTON_X, PAD_BUTTON_Y, PAD_TRIGGER_L, PAD_TRIGGER_R, PAD_TRIGGER_Z};

static void actionCommandDisp(s32 unused, f32 x, f32 y);

// FAKE: the button[]/pressed[] indexes are cast (u32) (i, j >= 0 there, same value);
// the cast stops IR strength reduction so the backend emits the target addi/lwzx
// and the shared offset IV. allDone is declared first for the register order.
s32 battleAcMain_ButtonDown(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    BDWork* p = (BDWork*)work->actionCommands.work;
    s32 j;
    BattleACDispParams* disp = &work->actionCommands.disp;
    s32 allDone;
    s32 i;
    s32 done;
    s32 flag = 0;
    const char* sfx;
    if (ac->acUnit->badgesEquipped.AutoCommand) {
        flag = 1;
    }
    sfx = (0, "SFX_AC_BUTTON_PUSH1");
    do {
        allDone = 0;
        switch (ac->acState) {
            case 0: {
                ac->result = 1;
                memset(disp, 0, 0x2c);
                disp->iconX = -300.0f;
                disp->iconY = 0.0f;
                disp->slideTimer = 20;
                memset(p->button, 0, 0x34);
                memset(p->pressed, 1, 0x34);
                for (i = 0; i < (work->actionCommands.params[2]); i++) {
                    switch (work->actionCommands.params[3]) {
                        case -2:
                            p->button[(u32)i] = (irand(100) < 50) ? (0x100) : (0x200);
                            p->pressed[(u32)i] = 0;
                            break;

                        case -4:
                            p->button[(u32)i] = (irand(100) < 50) ? (0x200) : (0x400);
                            p->pressed[(u32)i] = 0;
                            break;

                        case -3:
                            if ((work->actionCommands.acFlags) & 4) {
                                p->button[(u32)i] = _button_table[irand(4)];
                                p->pressed[(u32)i] = 0;
                            } else {
                                s32 found = 0;
                                u32 cand;
                                while (!found) {
                                    s32 j;
                                    s32 ok;
                                    cand = _button_table[irand(4)];
                                    ok = 1;
                                    for (j = i - 1; j >= 0; j--) {
                                        if (p->button[(u32)j] == cand) {
                                            ok = 0;
                                        }
                                    }

                                    if (ok) {
                                        found = 1;
                                    }
                                }

                                p->button[(u32)i] = cand;
                                p->pressed[(u32)i] = 0;
                            }
                            break;

                        default: {
                            s32 found = 0;
                            u32 cand;
                            while (!found) {
                                s32 ok;
                                cand = _button_table[irand(7)];
                                ok = 1;
                                for (j = i - 1; j >= 0; j--) {
                                    if (p->button[(u32)j] == cand) {
                                        ok = 0;
                                    }
                                }

                                if (ok) {
                                    found = 1;
                                }
                            }

                            p->button[(u32)i] = cand;
                            p->pressed[(u32)i] = 0;
                            break;
                        }
                    }
                }

                ac->acState = 99;
                break;
            }

            case 99:
                break;

            case 100:
                ac->acState = 1000;
                p->sndCount = 0;
                p->timer = work->actionCommands.params[0];

            case 1000:
                if ((ac->setupFlags & AC_SETUP_FLAG_CONFUSED_AUTO) && (((u32)ac->acUnit->tokenFlags) & TOKEN_FLAG_CONFUSED_ACTION)) {
                    if (ac->setupFlags & AC_SETUP_FLAG_RETRIES) {
                        ac->setupParam--;
                        if (ac->setupParam >= 0) {
                            break;
                        }
                    }
                    if (irand(100) >= 0) {
                        ac->result = 0;
                    } else {
                        ac->result = 2;
                        ac->resultCount++;
                    }
                    return 0;
                }
                if ((work->actionCommands.countdown) > 0) {
                    (work->actionCommands.countdown)--;
                    ac->result = 2;
                    allDone = 1;
                    ac->acState = 1001;
                    break;
                }
                *((s32*)(&ac->outputParams[0])) = 0;
                done = 1;
                for (i = 0; i < (work->actionCommands.params[2]); i++) {
                    if (p->button[(u32)i]) {
                        if (p->pressed[(u32)i]) {
                            (*((s32*)(&ac->outputParams[0])))++;
                        } else if (((p->button[(u32)i]) == BattlePadGetTrigger()) || flag) {
                            p->pressed[(u32)i] = 1;
                            (*((s32*)(&ac->outputParams[0])))++;
                            if ((work->actionCommands.params[1]) == 1) {
                                if ((i + 1) < (work->actionCommands.params[2])) {
                                    done = 0;
                                }
                                break;
                            }
                        } else if (BattlePadGetTrigger()) {
                            ac->result = 0;
                            ac->acState = 1001;
                            if (((work->actionCommands.acFlags) & 2) && ((*((s32*)(&ac->outputParams[0]))) > 0)) {
                                allDone = 1;
                                ac->result |= 2;
                                ac->result &= ~1;
                                ac->acState = 1001;
                                break;
                            }
                            return 1;
                        } else {
                            done = 0;
                            if ((work->actionCommands.params[1]) == 1) {
                                break;
                            }
                        }
                    }
                }

                if (p->sndCount != (*((s32*)(&ac->outputParams[0])))) {
                    psndSFXOn(sfx);
                    p->sndCount = *((s32*)(&ac->outputParams[0]));
                }
                if (done) {
                    ac->result |= 2;
                    allDone = 1;
                    ac->result &= ~1;
                    ac->acState = 1001;
                    break;
                }
                p->timer--;
                if (p->timer < 0) {
                    ac->result = 0;
                    allDone = 1;
                    ac->acState = 1001;
                    if (((work->actionCommands.acFlags) & 2) && ((*((s32*)(&ac->outputParams[0]))) > 0)) {
                        ac->result |= 2;
                        ac->result &= ~1;
                        ac->acState = 1001;
                    }
                }
                break;

            case 1001:
                ac->acState = 1002;

            case 1002:
                return 0;

            case 1003:
                p->endTimer = 60;
                ac->acState = 1004;
                break;

            case 1004:
                p->endTimer--;
                if (p->endTimer <= 0) {
                    ac->acState = 1005;
                }
                break;

            case 1005:
                ac->maincb = (void*)0;
                ac->dispcb = (void*)0;
                ac->resultcb = (void*)0;
                ac->deletecb = (void*)0;
                break;
        }

    } while (allDone);
    return 1;
}

/**
 * Returns the result word: 1 while running, 2 once every shown button was pressed in time,
 * 0 on a wrong button or timeout (acFlags bit 1 counts a partial sequence as success).
 */
s32 battleAcResult_ButtonDown(BattleWork* work) {
    return work->actionCommands.result;
}

/** Display callback: slides the button row in from the left over 20 frames, then draws it in place. */
void battleAcDisp_ButtonDown(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp;
    f32 x, y;
    disp = &ac->disp;
    switch (ac->acState) {
        case 99:
        case 0:
            if (disp->slideTimer > 0) {
                disp->slideTimer--;
            }
            x = intplGetValue(4, -300.0f, 0.0f, 20 - disp->slideTimer, 20);
            y = 0.0f;
            break;
        default:
            x = y = 0.0f;
            break;
    }
    actionCommandDisp(0, x, y);
}

/** Called by btlevtcmd_StopAC: starts the 60-frame wait after which the command clears its callbacks. */
void battleAcDelete_ButtonDown(BattleWork* work) {
    work->actionCommands.acState = 1003;
}

/**
 * Draws the frame bar behind the row and the button icons (A, B, X, Y, L, R, Z), lit once pressed.
 * With acFlags bit 0 only the buttons up to the next one to press are shown.
 * Used by action command 10 (Tornado Jump's second part, Vivian's Veil and Fiery Jinx).
 */
static void actionCommandDisp(s32 unused, f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BDWork* p = (BDWork*)work->actionCommands.work;
    s32 k;
    s32 end = ((work->actionCommands.params[2]) * 3) + 2;
    int size;
    s32 i;
    s32 count;
    s32 off;
    s32 j;
    f32 bx = (-200.0f) + x;
    f32 by;
    f32 lx = bx - 40.0f;
    Vec pos = {0.0f, 0.0f, -2.0f};
    by = 70.0f + y;
    pos.x = lx;
    pos.y = by;
    iconDispGx(&pos, ICON_DISP_2D, ICON_08F, 1.0f);
    lx += 16.0f;
    for (k = 1; k < end; k++) {
        Vec pos2 = {0.0f, 0.0f, -2.0f};
        pos2.x = lx;
        pos2.y = by;
        size = ICON_DISP_2D;
        iconDispGx(&pos2, size, ICON_08E, 1.0f);
        lx += 16.0f;
    }

    {
        Vec pos3 = {0.0f, 0.0f, -2.0f};
        pos3.x = lx;
        pos3.y = by;
        iconDispGx(&pos3, ICON_DISP_2D, ICON_090, 1.0f);
    }
    if ((work->actionCommands.acFlags) & 1) {
        for (count = 0, j = 0; count < (work->actionCommands.params[2]); count++, j += 4) {
            if (!p->pressed[j >> 2]) {
                break;
            }
        }

        if (count < (work->actionCommands.params[2])) {
            count++;
        }
    } else {
        count = work->actionCommands.params[2];
    }
    for (i = 0, off = 0, j = 0; i < count; i++, off += 0x30, j += 4) {
        s32 a;
        s32 b;
        if (p->button[j >> 2] == 0U) {
            continue;
        }
        switch (p->button[(j >> 1) >> 1]) {
            case 0x100:
                a = ICON_065;
                b = ICON_064;
                break;

            case 0x200:
                a = ICON_067;
                b = ICON_066;
                break;

            case 0x400:
                a = ICON_069;
                b = ICON_068;
                break;

            case 0x800:
                a = ICON_06B;
                b = ICON_06A;
                break;

            case 0x40:
                a = ICON_07F;
                b = ICON_07E;
                break;

            case 0x20:
                a = ICON_081;
                b = ICON_080;
                break;

            case 0x10:
                a = ICON_083;
                b = ICON_082;
                break;

            case 0x40000:

            default:
                a = ICON_078;
                b = ICON_079;
                break;
        }

        if (p->pressed[j >> 2]) {
            Vec pos4 = {0.0f, 0.0f, 0.0f};
            pos4.x = bx + ((f32)off);
            pos4.y = by;
            ((IconDispGxS32S32Fn)iconDispGx)(&pos4, size, a, 1.0f);
        } else {
            Vec pos5 = {0.0f, 0.0f, 0.0f};
            pos5.x = bx + ((f32)off);
            pos5.y = by;
            ((IconDispGxS32S32Fn)iconDispGx)(&pos5, size, b, 1.0f);
        }
    }
}
