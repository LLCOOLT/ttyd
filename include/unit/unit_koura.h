// unit_koura.c: the battle unit kind for the Koopa shell (unit_koura), used by Koops.
#pragma once

#include "dolphin/types.h"
#include "battle/battle_unit.h"

// Unit work slots of the Shell Shield shell (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_KOURA_SHIELDED_UNIT = 0, // unit id of the unit under the shell (Mario)
    UW_KOURA_OPEN = 1,          // 1 while the shell is tilted up off Mario for his turn
    UW_KOURA_FOLLOWS_UNIT = 2,  // KouraFollowMode: how btlDispMain moves the shell with the shielded unit
    UW_KOURA_CRACK_STAGE = 3,   // 0 intact, 1 cracked, 2 badly cracked
};

// UW_KOURA_FOLLOWS_UNIT values, read each frame by btlDispMain (battle_disp.c).
enum KouraFollowMode {
    KOURA_FOLLOW_NONE = 0,  // the shell stays where it is
    KOURA_FOLLOW_ON = 1,    // set on the shielded unit (from opening until closing ends; follows Mario's attack)
    KOURA_FOLLOW_TRAIL = 2, // trails the unit, at most 10 units away in x (front-and-back switch)
    KOURA_FOLLOW_SLIDE = 3, // slides 1 unit a frame onto the unit, then becomes KOURA_FOLLOW_ON; scripts wait for that
};

extern BattleUnitKind unit_koura;
