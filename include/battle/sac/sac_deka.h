// Declares the Earth Tremor (sac_deka) special move event.
#pragma once

#include <dolphin/types.h>
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"
#include "evt/evt_word.h"

extern EvtWord marioAttackEvent_Deka[];
s32 weaponGetPower_Deka(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);

extern EvtWord dmg_evt[];
