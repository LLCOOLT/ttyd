#pragma once

#include "party.h"
#include "driver/hitdrv.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

void partyChkGnd(PartyEntry* party);
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
#ifdef VERSION_G8ME01_DEMO
HitEntry* partySearchGround(PartyEntry* party, f32* outY, f32* outDepth, f32 range, f32 depth);
HitEntry* partySearchGroundSelf(PartyEntry* party, f32 range, f32 depth);
#else
HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth);
#endif
HitEntry* partySearchWallFront(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
