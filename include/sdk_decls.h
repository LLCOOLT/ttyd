// Declarations of SDK demo statistics and sound-mode functions (DEMOPrintStats, DEMOUpdateStats, OSSetSoundMode).
#pragma once

#include "dolphin/gx/GXEnum.h"
#include "dolphin/types.h"

extern void DEMOPrintStats(void);
extern void DEMOUpdateStats(GXBool inc);
extern u8 DemoStatEnable;
extern void OSSetSoundMode(u32 mode);
