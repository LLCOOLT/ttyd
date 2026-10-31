// win_log.c: the pause menu journal window (logs and the tattle log): winLogInit/Main/Disp.
#pragma once

#include <dolphin/types.h>
#include "driver/camdrv.h"
#include "win/win_main.h"

void winLogInit(WindowWork* w);
void winLogInit2(WindowWork* w);
void winLogExit(WindowWork* w);
const char* winGetMapTplName(void);
s32 winLogMain(WindowWork* w);
void winLogMain2(WindowWork* w);
void winLogDisp(s32 camId, void* param, s32 idx);

// Tattle window (monosiri): the enemy's picture and description, opened from the log and by Goombella's Tattle in
// battle (unit_party_christine). MonosiriWork is allocated by monosiriInit.
typedef struct MonosiriWork {
    s32 state;         // 0x0
    s32 id;            // 0x4
    FileEntry* file1;  // 0x8
    FileEntry* file2;  // 0xC
    f32 curX;          // 0x10
    f32 curY;          // 0x14
    f32 x;             // 0x18
    f32 y;             // 0x1C
    s32 pose1;         // 0x20
    s32 pose2;         // 0x24
    smartEntry* smart; // 0x28
    s32 alpha;         // 0x2C
} MonosiriWork;

MonosiriWork* monosiriInit(s32 id, f32 x, f32 y); // id: the enemy's BattleUnitType
void monosiriMain(MonosiriWork* m);
void monosiriClose(MonosiriWork* m);
BOOL monosiriCloseWait(MonosiriWork* m);
void monosiriExit(MonosiriWork* m);
