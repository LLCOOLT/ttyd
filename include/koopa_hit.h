// koopa_hit.c: Bowser's collision in the side-scrolling interludes: ground, head, wall, enemy and flame checks.
#pragma once

#include "driver/hitdrv.h"
#include "version.h"

HitEntry* kpaChkHitobjRide(void);
long kpaClearHitobjRide(void);
#if VERSION == VERSION_DEMO
HitEntry* kpaSearchWallFront(Vec* pos, f32* h, f32 dx, f32 dz);
#endif

s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 h, f32 w);
HitEntry* kpaGetHitobjHead(s32 i);
HitEntry* kpaGetHitobjRide(s32 i);
HitEntry* kpaGetHitobj(void);
HitEntry* kpaGetHitFlame(void);
HitEntry* kpaHitCheck(void);
HitEntry* kpaSearchFrontUnder(void);

HitEntry* kpaFlameHitCheck(f32 x, f32 y, f32 z, f32 r);
HitEntry* kpaGetHitobjHead2(void);
// Head (ceiling) check for Bowser; on a hit it sets pos->y and *h.
HitEntry* kpaSearchHead(Vec* pos, f32* h, f32 hgt);
HitEntry* kpaSearchGround(f32* outY, f32* outDepth, f32* outAng, f32 range);
