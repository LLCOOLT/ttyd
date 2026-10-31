// unit_mario.c: Mario's battle unit kind (unitdata_Mario) and faker_mario_makkuro_set.
#pragma once

#include "battle/battle_unit.h"

extern BattleUnitKind unitdata_Mario;

// Turns on the black (makkuro) TEV callback for the Doopliss fight; the unit argument is not read.
void faker_mario_makkuro_set(BattleUnit* unit);
