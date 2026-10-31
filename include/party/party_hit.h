// party_hit.c: partner collision checks (partyChkGnd, partyHitCheck, _partySearchGround, partySearchFrontWall).
#pragma once

#include "party.h"
#include "driver/hitdrv.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include "version.h"

void partyChkGnd(PartyEntry* party);
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
#if VERSION <= VERSION_DEMO_JP
HitEntry* _partySearchGround(PartyEntry* party, f32* outY, f32* outDepth, f32 range, f32 depth);
HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth);
#else
HitEntry* _partySearchGround(PartyEntry* party, f32 range, f32 depth);
#endif
HitEntry* partySearchWallFront(PartyEntry* party, Vec* pos, f32 dist, f32 ang);

void partyChkWallAround(PartyEntry* party, Vec* pos, f32 spd, f32 dir, f32 width, f32 height);
BOOL partyChkBetweenWalls(PartyEntry* party, Vec pos);
HitEntry* partyChkFrontStep(PartyEntry* party, f32 range, f32* outY, f32* outDist, f32* outAng);
void partySearchHead(PartyEntry* party, Vec* pos, f32* dist, f32 angle);
