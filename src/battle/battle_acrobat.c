// Acrobat timing window: a short timed-press prompt and its result, used during Mario and partner attacks.
#include <dolphin/pad.h>
#include "battle/battle_acrobat.h"
#include "battle/battle_ac.h"
#include "battle/battle_unit.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "icon_ids.h"
#include "version.h"

// local prototypes
void _accrobat_timing_icon_disp(CameraId camId, void* param);

s32 BattleAcrobatStart(BattleWork* work, s32 unitId, s32 windowStartFrame,
                       s32 windowEndFrame, s32 endFrame, s32 earlyFrames) {
    work->stylishCurFrame = 0;
    work->stylishWindowStart = windowStartFrame;
    work->stylishWindowEnd = windowEndFrame;
    work->stylishEndFrame = endFrame;
    work->stylishUnitId = unitId;
    work->stylishResult = 0;
    work->stylishEarlyFrames = earlyFrames;
    return 0; //???
}

s32 BattleAcrobatMain(BattleWork* work) {
    BattleActions* manager;
    BattleUnit* unit;
    BOOL doSimplified;
    s32 i;

    manager = &work->actionCommands;
    unit = BattleGetUnitPtr(work, work->stylishUnitId);
    doSimplified = FALSE;
    work->stylishCurFrame++;
    if (!unit) {
        work->stylishResult = 1;
        return EVT_RETURN_YIELD;
    }
    if (unit->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION) {
        work->stylishResult = 1;
        return EVT_RETURN_YIELD;
    }
    if ((work->badgeEquippedFlags & BADGE_FLAG_TIMING_TUTOR) && (work->stylishCurFrame > work->stylishWindowStart && work->stylishCurFrame <= work->stylishWindowEnd)) {
#if VERSION == VERSION_DEMO
        dispEntry(CAMERA_3D, 900.0f, 1, _accrobat_timing_icon_disp, unit);
#else
        Vec v11 = {0};
        v11.x = unit->position.x;
        v11.y = unit->position.y;
        v11.z = 15.0f + unit->position.z;
        dispEntry(CAMERA_3D, dispCalcZ(&v11), 1, _accrobat_timing_icon_disp, unit);
#endif
    }
    if (unit->badgesEquipped.AutoCommand && (work->stylishCurFrame > work->stylishWindowStart && work->stylishCurFrame <= work->stylishWindowEnd)) {
        doSimplified = TRUE;
    }
    if (work->stylishCurFrame <= 1 && work->stylishEarlyFrames > 0) {
        for (i = 0; i < work->stylishEarlyFrames; ++i) {
            if (BattlePadCheckRecordTrigger(i, 0x100)) {
                work->stylishResult = -1;
                return EVT_RETURN_YIELD;
            }
        }
    }
    if (BattlePadCheckTrigger(PAD_BUTTON_A) || doSimplified) {
        if (work->stylishCurFrame <= work->stylishWindowStart) {
            work->stylishResult = -1;
            return EVT_RETURN_YIELD;
        }
        if (work->stylishCurFrame <= work->stylishWindowEnd) {
            work->stylishResult = 2;
            return EVT_RETURN_YIELD;
        }
        work->stylishResult = -2;
        return EVT_RETURN_YIELD;
    }
    if (work->stylishCurFrame >= work->stylishEndFrame) {
        work->stylishResult = 1;
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

void _accrobat_timing_icon_disp(CameraId camId, void* param) {
    BattleUnit* unit = param;
    Vec pos;

    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.y += BtlUnit_GetHeight(unit) + 5;
    pos.x += 15.0f;
    iconDispGx(&pos, 0, ICON_09A, 0.67f);
}

s32 BattleAcrobatGetResult(BattleWork* work, s32* result, s32* curFrame) {
    *result = work->stylishResult;
    *curFrame = work->stylishCurFrame;
    return EVT_RETURN_DONE;
}
