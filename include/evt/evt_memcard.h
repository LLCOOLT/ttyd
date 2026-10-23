#pragma once

#include "dolphin/types.h"

extern s32 evt_memcard_save[];

extern s32 evt_memcard_check[];
extern s32 evt_memcard_copy[];
extern s32 evt_memcard_delete[];
#ifdef VERSION_G8ME01
extern s32 evt_memcard_save_wrapper[];
#endif
extern s32 evt_memcard_start[];
