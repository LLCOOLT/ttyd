// mario_sbr.c: Mario subroutines: move-direction maths (toMovedir), bottomless-pit respawn and stick/rub input.
#pragma once

#include <dolphin/types.h>
#include "party.h"

void marioSetBottomlessResetPosition(f32 x, f32 y, f32 z);
f32 revise360(f32 angle);
f32 toMovedir(f32 angle);
void marioAdjustMoveDir(void);

s32 N_marioGetMovementSpeed(void);
void N_marioReloadMapOnBottomlessOn(void);
void marioSetPeakYpos(void);
f32 partyToMovedir(PartyEntry* party, f32 angle);
f32 toMovedir2(f32 angle, f32 ofs);
f32 toMovedirSimple(f32 angle);

void N_marioSetBottomlessRespawnPosOnBeroEntry(f32 x, f32 y, f32 z);

struct HitEntry;

void marioGetRubInit(void);
void marioBottomless(void);
void N_marioSetBottomlessRespawnPos(f32 x, f32 y, f32 z);
void N_marioReloadMapOnBottomlessOff(void);
void marioResetGravity(void);
struct NpcEntry* marioGetTouchNpcPtr(void);
BOOL marioChkPlanePlace(struct HitEntry* hit);
void marioForceMoveMain(void);
void marioSetForceMove(f32 dir, s32 time, f32 speed);

f32 marioGetMoveRate(f32 dir);
s32 marioGetRub(u32 btn, s32* dirOut, s32* countOut, f32* magOut);
