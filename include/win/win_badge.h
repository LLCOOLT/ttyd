// win_badge.c: the pause menu badge window (equip and unequip badges): winBadgeInit/Main/Disp and winMakeEquipList.
#pragma once

#include <dolphin/types.h>
#include "win/win_main.h"

void winMakeEquipList(WindowWork* w);
void winBadgeInit(WindowWork* w);
void winBadgeInit2(WindowWork* w);
void winBadgeExit(WindowWork* w);
s32 winBadgeMain(WindowWork* w);
void winBadgeMain2(WindowWork* w);
void winBadgeDisp(s32 camId, void* param, s32 n);
