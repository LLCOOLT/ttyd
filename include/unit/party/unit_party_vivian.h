// unit_party_vivian.c: Vivian's battle weapons, pose table and unit kind as a partner, plus the majo display events.
#pragma once

#include "evt/evt_cmd.h"
#include "battle/battle_database_common.h"
#include "dolphin/types.h"
#include "battle/battle_unit.h"

// Unit work slots of Vivian (btlevtcmd_SetUnitWork / GetUnitWork). Slots 0-2 are also read by btlDispMain (battle_disp.c)
// to draw her shadow tail, and UW_VIVIAN_VEIL_TURNS by BtlUnit_CheckShadowGuard (battle_unit.c).
enum {
    UW_VIVIAN_SHADOW_X = 0,   // floor position of her shadow tail, kept by vivian_shadow_tail_event
    UW_VIVIAN_SHADOW_Y = 1,   // (y of the same position)
    UW_VIVIAN_SHADOW_Z = 2,   // (z of the same position)
    UW_VIVIAN_AWAY = 3,       // 1 while Shade Fist has her away from her spot: the shadow tail stays where it was
    UW_VIVIAN_VEIL_TURNS = 4, // Veil: turns left hidden in the shadow; while above 0 she cannot be hit
};

USER_FUNC(battle_evt_majo_disp_off);
USER_FUNC(battle_evt_majo_disp_on);
extern BattleWeapon partyWeapon_VivianCharmKissAttack;
extern BattleWeapon partyWeapon_VivianMagicalPowder;
extern BattleWeapon partyWeapon_VivianNormalAttack;
extern BattleWeapon partyWeapon_VivianShadowGuard;
extern PoseTableEntry pose_table_vivian_stay[];
extern BattleUnitKind unitdata_Party_Vivian;
extern EvtWord vivian_shadow_tail_event[];
