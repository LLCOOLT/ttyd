// Map-side copy of the Flurrie cloud-breath effect (evt_cloud.c) that gon_11, las_14 and mri_00 each
// carry: a map group hidden behind a captured cloud image that Flurrie's breath blows away. Unlike
// evt_cloud.c's CloudWork, one entry covers up to 8 map groups.
#pragma once

#include "evt/evt_word.h"
#include "manager/evtmgr.h"
#include <dolphin/types.h>

// One cloud (`cloud`, _mapAlloc'd array of 16).
typedef struct CloudMapWork {
    s32 used;                 // 0x000
    s32 state;                // 0x004
    char animName[0x20];      // 0x008, "P_oof_cloud_1" / "P_oof_cloud_2"
    char imgName[0x20];       // 0x028
    char offscreenName[0x20]; // 0x048
    char groupNames[8][0x20]; // 0x068, map groups drawn off screen; an empty name ends the list
    char hitName[0x20];       // 0x168, its bounding box sets the capture rectangle
    s32 limit;                // 0x188, 180
    s32 counter;              // 0x18C, +2 per frame of breath
    EventEntry* evt;          // 0x190, evt_cloud_main_evt
    EvtWord* endEvt;          // 0x194, run when the cloud is blown away, or NULL
    s32 timer;                // 0x198
    s32 x;                    // 0x19C, capture rectangle
    s32 y;                    // 0x1A0
    s32 w;                    // 0x1A4
    s32 h;                    // 0x1A8
    f32 lastFrame;            // 0x1AC, image loopTimes seen last frame
} CloudMapWork;
