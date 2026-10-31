// mario_balloon.c: the "!" / "?" balloon over Mario's head (marioBalloonOn/Off/Main, chkBalloon).
#pragma once

#include "dolphin/types.h"
#include "driver/hitdrv.h"

BOOL chkBalloon(HitEntry* hit);

void marioBaloonInit(void);
void marioBalloonOn(s32 type);
void marioBalloonOff(void);
void marioBalloonMain(void);
