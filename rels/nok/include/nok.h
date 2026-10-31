#pragma once

// Declarations shared by the nok.rel units (ハナハナ村, Petalburg).

#include "dolphin/types.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"

extern NpcTerritoryInfo btl_nok_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_nok_tbl[];
extern EvtWord nok_00_init_evt[];
extern EvtWord nok_01_init_evt[];

extern BattleUnitKind unit_act_atmic_teresa;
extern BattleUnitKind unit_act_clauda;
extern BattleUnitKind unit_act_kinopiko;
extern BattleUnitKind unit_act_kinopio;
extern BattleUnitKind unit_act_mario;
extern BattleUnitKind unit_act_teresa;
