// Action command: Tattle targeting (ac_monosiri_target); aim a reticle at an enemy and press the button.
#include <dolphin/pad.h>
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_disp.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/icondrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#include "version.h"

// FAKE: ac_monosiri_target.c calls iconDispGx through this prototype (the types it was compiled with) instead of the one in driver/icondrv.h; same registers, behaviour-identical.
typedef void (*IconDispGxS32S32Fn)(Vec*, s32, s32, f32);
// FAKE: ac_monosiri_target.c calls BattleACGetButtonIcon through this prototype (the types it was compiled with) instead of the one in battle/battle_ac.h; same registers, behaviour-identical.
typedef s32 (*BattleACGetButtonIconRetS32Fn)(s32, s32);
// US battle texture ids are 0x16 higher for these entries.
#define BTL_TEX(id) ((id) + VERSION_PICK(0, 0x16))

// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on

typedef struct MonosiriTargetWork {
    s32 frame;      // 0x0
    s32 maxFrames;  // 0x4
    Vec hitPos;     // 0x8
    Vec pos;        // 0x14
    Vec targetPos;  // 0x20
    f32 angle;      // 0x2C
    s32 inRange;    // 0x30
    s32 inRangeCnt; // 0x34
    u32 sfxId;      // 0x38
    s32 endTimer;   // 0x3C
} MonosiriTargetWork;

static void actionCommandDisp(f32 x, f32 y);

s32 _frame_table[] = {240, 180, 120, 90, 70, 40, 20};

// inlining off for _getmaxcount, as in the original (the object differs without it)
#pragma dont_inline on
/** Frames the Tattle cursor takes to cross the target, by action command difficulty: 240 at the easiest down to 20. */
static s32 _getmaxcount(void) {
    return _frame_table[BattleActionCommandGetDifficulty(_battleWorkPointer)];
}
#pragma dont_inline reset

/**
 * Per-frame driver of action command 21, used by Goombella's Tattle.
 * A cursor sweeps 160 units left to right across the hit point of unit params[0] (part params[1]) over
 * _getmaxcount frames; pressing A while it is within 28 units of the hit point succeeds,
 * any other press or letting it pass fails. Plays the cursor sound meanwhile.
 */
s32 battleAcMain_MonosiriTarget(BattleWork* work) {
    BattleActions* ac;
    MonosiriTargetWork* cw;
    BattleACDispParams* disp;
    BattleUnit* unit;
    BattleUnitPart* parts;
    BOOL autoCommand;

    ac = &work->actionCommands;
    autoCommand = FALSE;
    cw = (MonosiriTargetWork*)ac->work;
    disp = (BattleACDispParams*)&ac->disp;
    if (work->actionCommands.acUnit->badgesEquipped.AutoCommand) {
        autoCommand = TRUE;
    }
    // params: 0 unit id, 1 parts id
    unit = BattleGetUnitPtr(work, ac->params[0]);
    parts = BtlUnit_GetPartsPtr(unit, ac->params[1]);

    switch (work->actionCommands.acState) {
        case 0:
            memset(disp, 0, sizeof(BattleACDispParams));
            disp->iconX = -300.0f;
            disp->iconY = 0.0f;
            disp->slideTimer = 20;
            cw->frame = 0;
            cw->maxFrames = _getmaxcount();
            BtlUnit_GetHitPos(unit, parts, &cw->hitPos.x, &cw->hitPos.y, &cw->hitPos.z);
            cw->pos = cw->hitPos;
            cw->targetPos = cw->hitPos;
            cw->inRange = 0;
            cw->angle = 0.0f;
            work->actionCommands.acState = 99;
            work->actionCommands.result = 1;
            cw->sfxId = -1;
            break;
        case 100:
            cw->frame = 0;
            cw->sfxId = psndSFXOn("SFX_AC_CURSOR_MOVE1");
            work->actionCommands.acState = 1000;
            // fall through
        case 1000:
            cw->frame++;
            cw->pos.x = (cw->hitPos.x - 80.0f) + intplGetValue(0, 0.0f, 160.0f, cw->frame, cw->maxFrames);
            if (__fabs(cw->pos.x - cw->targetPos.x) < 28.0) {
                cw->inRange = 1;
            } else {
                cw->inRange = 0;
            }
            if (cw->inRange == 0) {
                cw->inRangeCnt = 0;
            } else {
                cw->inRangeCnt++;
            }
            if (cw->frame >= cw->maxFrames) {
                work->actionCommands.result = 0;
                work->actionCommands.acState = 1002;
                break;
            }
            if (BattlePadCheckTrigger(PAD_BUTTON_A) || autoCommand) {
                if (cw->inRange) {
                    work->actionCommands.result = 2;
                    work->actionCommands.resultCount++;
                } else {
                    if (autoCommand) {
                        break;
                    }
                    work->actionCommands.result = 0;
                }
                work->actionCommands.acState = 1002;
            }
            break;
        case 1002:
            cw->endTimer = 60;
            work->actionCommands.acState = 1003;
            if (cw->sfxId != -1) {
                psndSFXOff(cw->sfxId);
            }
            // fall through
        case 1003:
            cw->endTimer--;
            if (cw->endTimer <= 0) {
                work->actionCommands.acState = 1004;
            }
            break;
        case 1004:
            work->actionCommands.maincb = NULL;
            work->actionCommands.dispcb = NULL;
            work->actionCommands.resultcb = NULL;
            work->actionCommands.deletecb = NULL;
            return 0;
    }
    return 1;
}

/** Returns the result word: 1 while running, 2 on success, 0 on failure. */
s32 battleAcResult_MonosiriTarget(BattleWork* work) {
    return work->actionCommands.result;
}

/** Display callback: draws the cursor and target only while the cursor is moving. */
void battleAcDisp_MonosiriTarget(CameraId cameraId, void* param) {
    BattleWork* work = _battleWorkPointer;
    switch (work->actionCommands.acState) {
        case 1000:
            actionCommandDisp(0.0f, 0.0f);
            break;
    }
}

/** Called by btlevtcmd_StopAC: stops the cursor sound and starts the 60-frame end wait. */
void battleAcDelete_MonosiriTarget(BattleWork* work) {
    work->actionCommands.acState = 1002;
}

// inlining off for actionCommandDisp, as in the original (the object differs without it)
#pragma dont_inline on
/**
 * Draws the moving cursor and the spinning target reticle (each with a grey shadow),
 * pulses the reticle while the cursor is in range,
 * and shows the A icon pressed when the cursor is within 15 units as a cue.
 */
static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    MonosiriTargetWork* cw = (MonosiriTargetWork*)ac->work;
    f32 alpha = 0.0f;
    Vec screen;
    Vec screen2;
    s32 icon;
    s32 pressedIcon;

    btlGetScreenPoint(&cw->pos, &screen);
    btlDispTex4(BTL_TEX(0x42), screen, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, 0.0f}, (GXColor){255, 255, 255, 255});
    screen.x += 4.0f;
    screen.y -= 4.0f;
    screen.z -= 2.0f;
    btlDispTex4(BTL_TEX(0x42), screen, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, 0.0f}, (GXColor){128, 128, 128, 255});

    if (cw->inRange) {
        s32 t = cw->inRangeCnt % 30;
        if (t < 20) {
            alpha = 0.01f * intplGetValue(5, 100.0f, 0.0f, t, 20);
        }
    }

    btlGetScreenPoint(&cw->targetPos, &screen2);
    btlDispTex4(BTL_TEX(0x41), screen2, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, cw->angle}, (GXColor){255, 255, 255, 255});
    if (alpha > 0.0f) {
        btlDispTex4(BTL_TEX(0x41), screen2, (Vec){alpha, alpha, 1.0f}, (Vec){0.0f, 0.0f, cw->angle}, (GXColor){255, 255, 255, 255});
    }
    screen2.x += 4.0f;
    screen2.y -= 4.0f;
    screen2.z -= 2.0f;
    btlDispTex4(BTL_TEX(0x41), screen2, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, cw->angle}, (GXColor){128, 128, 128, 255});
    cw->angle += 2.0f;

    pressedIcon = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_BUTTON_A, 1);
    icon = ((BattleACGetButtonIconRetS32Fn)BattleACGetButtonIcon)(PAD_BUTTON_A, 0);
    if (__fabs(cw->pos.x - cw->targetPos.x) < 15.0) {
        icon = pressedIcon;
    }
    ((IconDispGxS32S32Fn)iconDispGx)(&(Vec){-200.0f + x, 50.0f + y, 0.0f}, ICON_DISP_2D, icon, 1.0f);
}
#pragma dont_inline reset
