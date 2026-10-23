#include "dolphin/types.h"
#include "mario/mario.h"

void marioChgMot(MarioMotion);
BOOL marioChkItemMotion(void);
BOOL marioChkJump(void);
BOOL marioChkTransform(void);

void marioChgJumpStandMotion(f32 v);
void marioChgSmallJumpMotion(void);
f32 marioGetFallSpd(void);
void marioSetFallPara(void);
