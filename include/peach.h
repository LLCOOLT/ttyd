// peach.c: Peach as the player character in the Peach interludes (peach_walk, peach_dash, peachSetSts* states).
#pragma once

#include <dolphin/types.h>

void peach_dash(void);
void peach_walk(void);

void peachTransformOff(void);
void peachSetStsNormal(void);
void peachSetStsAftershower(void);
void peachSetStsInvisible(void);
void peachSetStsHappy(void);
void peachSetStsUneasy(void);
void peachSetStsAngry(void);
void peachSetStsOrdinary(void);
void peachSetStsCarry(void);
void peachTransformOn(void);
void peachPreInit(void);
void peach_stay(void);
void peach_talk(void);
