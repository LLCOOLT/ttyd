// win_item.c: the pause menu item window (items, important items, mail, Koopa book): winItemInit/Main/Disp.
#pragma once

#include "dolphin/types.h"
#include "win/win_main.h"

extern const char** luigi_book_list[];
extern u16 menu_skip_list[];

void winItemInit(WindowWork* w);
void winMakeSkipList(WindowWork* w);
void winItemInit2(WindowWork* w);
void winItemExit(WindowWork* w);
s32 winItemMain(WindowWork* w);
void winItemMain2(WindowWork* w);
void winItemDisp(s32 camId, void* param, s32 n);
