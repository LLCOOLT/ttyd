// Declares the Art Attack (sac_scissor) special move event.
#pragma once

#include <dolphin/types.h>
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"
#include "evt/evt_word.h"

extern EvtWord marioAttackEvent_Scissor[];
s32 weaponGetPower_Scissor(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
