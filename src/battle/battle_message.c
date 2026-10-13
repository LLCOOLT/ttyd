#include "battle/battle.h"
#include "data/item_data.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include <stdio.h>

extern ItemData itemDataTable[];

void _disp(CameraId cameraId, void* param);

// s32 type, s32 x, s32 y, const char* msg, s32 frames
USER_FUNC(btlevtcmd_AnnounceMessage) {
    BattleAnnounce* announce = &_battleWorkPointer->announce;
    s32* args = event->args;
    s32 type, x, y, frames;
    const char* msg;
    const char* text;

    type = evtGetValue(event, args[0]);
    x = evtGetValue(event, args[1]);
    y = evtGetValue(event, args[2]);
    msg = (const char*)evtGetValue(event, args[3]);
    frames = evtGetValue(event, args[4]);
    if (!msg) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        event->userdata[0] = frames;
        announce->x = x;
        announce->y = y;
        text = msgSearch(msg);
        switch (type) {
            case 1:
                sprintf(announce->text, text, itemDataTable[announce->params[0]].id);
                break;
            default:
                sprintf(announce->text, text);
                break;
        }
    }
    dispEntry(CAMERA_2D, 900.0f, 1, _disp, NULL);
    event->userdata[0]--;
    return event->userdata[0] <= 0;
}

void _disp(CameraId cameraId, void* param) {
    static const GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    BattleAnnounce* announce = &_battleWorkPointer->announce;
    u16 lines;
    u16 width;
    f32 x, y;

    x = announce->x;
    y = announce->y + 120;
    width = FontGetMessageWidthLine(announce->text, &lines);
    lines++;
    x -= width / 2;
    windowDispGX_Waku_col(0, color, x - 10.0f, -29.0f + (3.0f + y), width + 20, lines * 29 + 3, 10.0f);
    FontDrawStart();
    FontDrawMessage(x, (s32)y - 29, announce->text);
}

// s32 index, s32 value
USER_FUNC(btlevtcmd_AnnounceSetParam) {
    s32* args = event->args;
    BattleAnnounce* announce = &_battleWorkPointer->announce;
    s32 index;

    index = evtGetValue(event, args[0]);
    announce->params[index] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
