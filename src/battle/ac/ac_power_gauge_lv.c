// Action command: power gauge with levels (ac_power_gauge_lv); the gauge fill is graded into success levels.
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "system.h"
#include <string.h>
#include "icon_ids.h"

// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on

typedef struct PowerGaugeLvWork {
    s32 counter; // 0x0
    f32 gauge;   // 0x4
    s32 presses; // 0x8, never used (air gauge layout)
    s32 limit;   // 0xC
    s32 timer;   // 0x10
} PowerGaugeLvWork;

#define PG_WORK(ac) ((PowerGaugeLvWork*)(ac)->work)

s32 battleAcMain_PowerGaugeLv(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    PowerGaugeLvWork* tw = PG_WORK(ac);
    BattleACDispParams* disp = &ac->disp;

    switch (work->actionCommands.acState) {
        case 99:
            break;
        case 0:
            memset(disp, 0, 0x2C);
            disp->iconX = -300.0f;
            disp->iconY = 0.0f;
            disp->slideTimer = 20;
            disp->gaugeRatio = 0.0f;
            disp->color = (GXColor){255, 255, 255, 255};
            tw->counter = 0;
            work->actionCommands.outputParams[0] = 0;
            work->actionCommands.acState = 99;
            work->actionCommands.result = 1;
            tw->limit = 100;
            tw->gauge = 0.0f;
            break;
        case 100:
            if ((work->actionCommands.setupFlags & 1) && (work->actionCommands.acUnit->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION)) {
                if (irand(100) >= 0) {
                    work->actionCommands.setupParam = 30;
                    work->actionCommands.outputParams[0] = 0;
                } else {
                    work->actionCommands.outputParams[0] = irand(ac->params[1] - 1) + 1;
                    work->actionCommands.setupParam = 30;
                }
                work->actionCommands.acState = 1001;
                break;
            }
            work->actionCommands.acState = 1000;
        case 1000:
            tw->counter++;
            if (tw->counter > tw->limit) {
                work->actionCommands.outputParams[0] = 0;
                work->actionCommands.result = 0;
                tw->gauge = 101.0f;
                return 0;
            }
            tw->gauge = intplGetValue(2, 0.0f, 100.0f, tw->counter, tw->limit);
            if (BattlePadGetNow() == 0x60) {
                if (tw->gauge < (f32)ac->params[2]) {
                    work->actionCommands.result = 0;
                    work->actionCommands.result &= ~2;
                } else {
                    work->actionCommands.result = 2;
                    work->actionCommands.resultCount++;
                    if (ac->params[1] <= 1) {
                        work->actionCommands.outputParams[0] = 1;
                    } else if (tw->gauge < (f32)ac->params[3]) {
                        work->actionCommands.outputParams[0] = 1;
                    } else if (ac->params[1] <= 2) {
                        work->actionCommands.outputParams[0] = 2;
                    } else if (tw->gauge < (f32)ac->params[4]) {
                        work->actionCommands.outputParams[0] = 2;
                    } else if (ac->params[1] <= 3) {
                        work->actionCommands.outputParams[0] = 3;
                    } else if (tw->gauge < (f32)ac->params[5]) {
                        work->actionCommands.outputParams[0] = 3;
                    } else if (ac->params[1] <= 4) {
                        work->actionCommands.outputParams[0] = 4;
                    } else {
                        work->actionCommands.outputParams[0] = 5;
                    }
                }
                work->actionCommands.acState = 1002;
            }
            break;
        case 1001:
            work->actionCommands.setupParam--;
            if (work->actionCommands.setupParam < 0) {
                if ((s32)work->actionCommands.outputParams[0] > 0) {
                    work->actionCommands.result = 2;
                    work->actionCommands.resultCount++;
                } else {
                    work->actionCommands.result = 0;
                }
                return 0;
            }
            break;
        case 1002:
            work->actionCommands.acState = 1003;
        case 1003:
            work->actionCommands.doneFlags |= 1;
            tw->timer = 60;
            work->actionCommands.acState = 1004;
        case 1004:
            tw->timer--;
            if (tw->timer <= 0) {
                work->actionCommands.acState = 1005;
            }
            break;
        case 1005:
            work->actionCommands.maincb = NULL;
            work->actionCommands.dispcb = NULL;
            work->actionCommands.resultcb = NULL;
            work->actionCommands.deletecb = NULL;
            return 0;
    }
    return 1;
}

s32 battleAcResult_PowerGaugeLv(BattleWork* work) {
    return work->actionCommands.result;
}

static void actionCommandDisp(f32 x, f32 y);

void battleAcDisp_PowerGaugeLv(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = &ac->disp;
    switch (ac->acState) {
        case 99:
            disp->iconX = intplGetValue(4, -300.0f, 30.0f, 20 - disp->slideTimer, 20);
        case 100:
        case 1000:
        case 1002:
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->slideTimer > 0) {
                disp->slideTimer--;
            }
            break;
        case 1003:
        case 1004:
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
void battleAcDelete_PowerGaugeLv(BattleWork* work) {
    if (work->actionCommands.doneFlags & 1) {
        return;
    }
    work->actionCommands.acState = 1003;
}

static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = &ac->disp;
    PowerGaugeLvWork* tw;
    f32 ratio;
    camGetPtr(CAMERA_2D);
    tw = PG_WORK(ac);
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = -200.0f + x;
        pos.y = 25.0f + y;
        iconDispGx(&pos, ICON_DISP_2D, ICON_08C, 1.0f);
    }
    ratio = tw->gauge / 100.0f;
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    disp->gaugeRatio = ratio;
    BattleAcDrawGauge((s32)x, (s32)y, 0xB2, disp->gaugeRatio, work->actionCommands.params[1], work->actionCommands.params[2],
                      work->actionCommands.params[3], work->actionCommands.params[4], 0);
    switch (work->actionCommands.acState) {
        case 99:
        case 100:
        case 1002:
        case 1003:
        case 1004: {
            Vec pos = {0.0f, 0.0f, 0.0f};
            x = -220.0f + x;
            y = 70.0f + y;
            pos.x = x;
            pos.y = y;
            iconDispGx(&pos, ICON_DISP_2D, ICON_07E, 1.0f);
            {
                Vec pos2 = {0.0f, 0.0f, 0.0f};
                pos2.x = 56.0f + x;
                pos2.y = y;
                iconDispGx(&pos2, ICON_DISP_2D, ICON_080, 1.0f);
            }
            break;
        }
        case 1000:
            if (tw->gauge >= (f32)work->actionCommands.params[2 + 0] && tw->gauge <= 100.0f) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                x = -220.0f + x;
                y = 70.0f + y;
                pos.x = x;
                pos.y = y;
                iconDispGx(&pos, ICON_DISP_2D, ICON_07F, 1.0f);
                {
                    Vec pos2 = {0.0f, 0.0f, 0.0f};
                    pos2.x = 56.0f + x;
                    pos2.y = y;
                    iconDispGx(&pos2, ICON_DISP_2D, ICON_081, 1.0f);
                }
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                x = -220.0f + x;
                y = 70.0f + y;
                pos.x = x;
                pos.y = y;
                iconDispGx(&pos, ICON_DISP_2D, ICON_07E, 1.0f);
                {
                    Vec pos2 = {0.0f, 0.0f, 0.0f};
                    pos2.x = 56.0f + x;
                    pos2.y = y;
                    iconDispGx(&pos2, ICON_DISP_2D, ICON_080, 1.0f);
                }
            }
            break;
    }
}
