// mario_motion.c: motion changes (marioChgMot), jump and fall parameters (MarioJumpData) and the motion-start checks.
#pragma once

#include "dolphin/types.h"
#include "mario/mario.h"

// Mario's jump and fall curves: velocity, acceleration, jerk and snap (the third and fourth derivatives) at the
// start of a jump and of a fall (mario_motion.c marioJumpData; koopa.c reads it as a float array).
typedef struct MarioJumpData {
    f32 jump[4]; // 0x00
    f32 fall[4]; // 0x10
    f32 height;  // 0x20, 32.0, never read (probably the jump height)
    f32 minFall; // 0x24, fall velocity limit
} MarioJumpData;

void marioChgMot(MarioMotion);
BOOL marioChkItemMotion(void);
BOOL marioChkJump(void);
BOOL marioChkTransform(void);

void marioChgJumpStandMotion(f32 v);
void marioChgSmallJumpMotion(void);
f32 marioGetFallSpd(void);
void marioSetFallPara(void);

void marioChgMotSub(MarioMotion id, s32 callPost);
void marioChgShipMotion(void);
void marioChgStayMotion(void);
f32 marioMakeJumpPara(void);

void marioLandOn(void);
void marioClearJumpPara(void);
void marioChgRollMotion(void);
void marioChgTalkMotion(void);
void marioChgGetItemMotion(void);
BOOL marioChkItemGetMotion(void);
void marioBoots(void);
void marioMotion(void);
void marioSetJumpPara(void);
void marioJump(void);
void marioFall(void);
s32 L_marioChkRub(void);
void marioChgMot2(MarioMotion id);
s32 marioRollChgChk(void);
