// mot_roll.c: Mario's tube (roll) motion (mot_roll_post) and its cancel, key-lock and event-flag helpers.
#pragma once

#include "dolphin/types.h"

extern f32 roll_grx;
extern f32 roll_grz;
void roll_upstairs_on(void);

void marioRollFixOn(void);
s32 marioRollCancelDisable(void);
s32 marioRollKeyDisable(void);
void setRollEvtFlag(void);
void clrRollEvtFlag(void);
s32 getRollEvtFlag(void);
void marioResetRollSpd(void);
void marioForceRollAnime(void);
s32 marioRollTryCancel(void);
s32 marioRollCancel(void);
void mot_roll_post(void);
void marioRollForceCancel(void);
void marioSetRollDispDir(void);
void rollEvtJumpSetup(void);
void marioReInit_roll(void);
void mot_roll(void);
void mot_fall_roll(void);
