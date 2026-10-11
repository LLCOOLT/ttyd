#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_unit.h"
#include "system.h"

static void actionCommandDisp(f32 x, f32 y);

void battleAcDelete_AirGauge(BattleWork* work) {
    work->actionCommands.mAcState = 1002;
}

void battleAcDisp_AirGauge(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleACDispParams* disp = (BattleACDispParams*)((u8*)&work->actionCommands + 0x290);
    s32 i;
    switch (work->actionCommands.mAcState) {
        case 99:
            disp->iconX = intplGetValue(4, 20 - *(s32*)&disp->field_0x1C[4], 20, -300.0f, 30.0f);
        case 100:
            i = 4;
        case 1000:
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[i] > 0) {
                (*(s32*)&disp->field_0x1C[i])--;
            }
            break;
        case 1002:
        case 1003:
            if (*(s32*)&disp->field_0x1C[4] >= 40) {
                disp->iconX = intplGetValue(4, *(s32*)&disp->field_0x1C[4] - 40, 20, 30.0f, -300.0f);
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[4] < 60) {
                (*(s32*)&disp->field_0x1C[4])++;
            }
            break;
    }
}

s32 battleAcResult_AirGauge(BattleWork* work) {
    return work->actionCommands.result;
}
