// Minigame driver of the Pianta Parlor (yuu evt_yuuminigame.c) and its gor copy (evt_goryuugijo.c):
// a script-allocated work that runs one minigame's init/main/disp callbacks every frame.
#pragma once

#include "driver/camdrv.h"
#include "manager/evtmgr.h"
#include <dolphin/types.h>

// MiniGameWork.flags
#define MINIGAME_FLAG_QUIT 0x1    // set by the free call; the main loop acknowledges with MINIGAME_FLAG_STOPPED
#define MINIGAME_FLAG_STOPPED 0x2 // main loop has ended, the work can be freed

typedef struct MiniGameWork {
    EventEntry* event;                                 // 0x00, the main loop script (lwData[0] = this work)
    EventEntry* subEvent;                              // 0x04, script the minigame is waiting on, or NULL
    u16 flags;                                         // 0x08, MINIGAME_FLAG_*
    s32 type;                                          // 0x0C, which minigame
    void (*init)(EventEntry* event, BOOL isFirstCall); // 0x10
    void (*main)(EventEntry* event, BOOL isFirstCall); // 0x14
    void (*disp)(CameraId camera, void* param);        // 0x18, param = this work
    void* data;                                        // 0x1C, the minigame's own work (HikokiWork, SlitWork, ...)
} MiniGameWork;
