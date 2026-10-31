// win_root.c: the pause menu root (tabs, help text, sort menu, shared frames) and the list sort comparers.
#pragma once

#include "dolphin/types.h"
#include "win/win_main.h"

extern u8 enemy_monoshiri_sort_table[];

s32 winRootMain(WindowWork* w);
void winRootDisp(s32 camId, WindowWork* wp);
void winZClear(void);
void winMailGX(WindowWork* wp, f32 x, f32 y);
s32 compare_func5_2(const void* a, const void* b);
s32 compare_func6_2(const void* a, const void* b);
void winHalfBookGX(TEXPalette* tpl, s32 a, f32 x, f32 y);
