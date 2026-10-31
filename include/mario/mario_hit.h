// mario_hit.c: Mario's collision checks against the map hit data (ground, walls, ceiling, slit and entrance checks).
#pragma once

#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "dolphin/mtx.h"
#include "version.h"

BOOL marioChkBero(HitEntry* hit);
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);

HitEntry* dou10_yoko_yari(f32* out);
HitEntry* marioLandonChk_old(f32* outY, f32 spd);
void marioSearchFrontWall_staying(f32 dz);
HitEntry* marioSearchGround(f32* y, f32* b, f32* c, f32 spd, f32 h);
HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h);
HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, s32* side, f32 d);
f32 marioChkOverheadJabara(s32* sideOut, f32* distOut);
HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d);

void marioChkGnd(void);
#if VERSION <= VERSION_DEMO_US
BOOL marioChkWallAround(Vec* pos, f32 unused, f32 dir, f32 w, f32 h); // no mode argument in the demo
#else
BOOL marioChkWallAround(Vec* pos, s32 mode, f32 unused, f32 dir, f32 w, f32 h);
#endif
HitEntry* searchUnder2(f32* out, f32 x, f32 y, f32 z);

HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz);
void clear_hitobj_ride(void);
HitEntry* marioSearchUnder(void);
void marioChkGnd2(void);
void marioChkToge(void);
HitEntry* marioChkLandon2(f32* y, f32 spd, f32 ofs);
void marioCheckWall(f32 dx, f32 dz);
void marioCheckWall_roll(f32 dx, f32 dz);
HitEntry* marioChkFront(f32* out, const Vec* pos, f32 angle, f32 dist);
HitEntry* N_dou10_yoko_yari3(void);
BOOL marioSlitChkWallAround(void);
void marioCheckWallShip(f32 dx, f32 dz);
HitEntry* marioSearchHead(Vec* pos, f32* h, f32 dd);

f32 marioChkOverhead(void);
HitEntry* marioChkLandon(f32* y, f32 spd);
HitEntry* dou10_yoko_yari2(f32* out);
