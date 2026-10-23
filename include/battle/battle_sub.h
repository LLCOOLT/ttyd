#pragma once

#include "battle/battle.h"
#include "manager/evtmgr.h"

void btlsubResetMoveColorLvAll(BattleWork* work);
s32 BattleTransID(EventEntry* event, s32 type);

void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
