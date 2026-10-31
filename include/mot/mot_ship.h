// mot_ship.c: Mario's paper boat motion (mot_ship, mot_ship_post), swirl (whirlpool) power and ship-place checks.
#pragma once

#include "dolphin/types.h"

BOOL marioChkShipMoveMode(void);
void marioShipChgFall(void);

struct HitEntry;

s32 marioShipChanging(void);
void marioSetSwirlPower(s32 msec, f32 a, f32 b);
BOOL marioChkSwirlPower(void);
void marioShipForceStop(void);
void marioShipSetDispDir(void);
BOOL marioChkShipPlace(struct HitEntry* hit);
void marioForceShipAnime(void);
void marioReInit_ship(void);
void mot_ship_post(void);
void mot_ship(void);
