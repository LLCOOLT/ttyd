#pragma once

#include "dolphin/types.h"
#include "battle/battle_unit.h"
#include "evt/evt_word.h"

extern EvtWord marioAttackEvent_Scissor[];
s32 weaponGetPower_Scissor(void* a, void* b, BattleUnit* unit);
