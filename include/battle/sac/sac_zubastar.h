// Declares the Supernova (sac_zubastar) special move event.
#pragma once

#include <dolphin/types.h>
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"
#include "evt/evt_word.h"

extern EvtWord marioAttackEvent_ZubaStar[];
s32 weaponGetPower_ZubaStar(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
