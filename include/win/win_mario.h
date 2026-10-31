// win_mario.c: the pause menu Mario window (stats, special moves, equipped gear): winMarioInit/Main/Disp.
#pragma once

#include <dolphin/types.h>
#include "win/win_main.h"

const char* winZenkakuStr(s32 n);
char* winZenkakuStrPad(s32 n, s32 digits);

void winMarioInit(WindowWork* w);
void winMarioInit2(WindowWork* w);
void winMarioExit(WindowWork* w);
s32 winMarioMain(WindowWork* w);
void winMarioMain2(WindowWork* w);
void winMarioDisp(s32 camId, void* param, s32 idx);
