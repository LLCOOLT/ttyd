// mot_slit.c: Mario's paper slit (side-step) motion, with its ability, button, floor and crevice checks.
#pragma once

#include "dolphin/types.h"
#include <dolphin/mtx.h>

BOOL marioSlitAbilityChk(void);
s32 marioSlitButton(void);
void motSlitContinue(void);

BOOL marioChkSlitEnd(void);
BOOL marioChkSlitThrouh(void);
BOOL marioGetMotSlitCancel3(void);

BOOL marioCreviceWallChk(const Vec* p);
void marioSlitReenter(void);
void N_marioSlitSetAfterLand(void);
BOOL marioSlitKeyDisable(void);
BOOL U_marioSlitContinueChk(void);
void marioClearSlitFloor(void);
BOOL marioGetSlitFloorPos(Vec* out);
BOOL marioChkSlitThrouhEnd(void);
void motSlitContinue2(void);
void motSlitCancel(void);
void motSlitCancel2(void);
void motSlitCancel3(void);
void marioSlitForceCancel(void);
void mot_slit_post(void);
void marioForceSlitAnime(void);
void marioReInit_slit(void);
void mot_slit(void);
