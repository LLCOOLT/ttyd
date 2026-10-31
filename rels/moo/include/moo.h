#pragma once

// Declarations shared by the moo.rel units (月, the Moon).

#include "version.h"
#include "dolphin/types.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"

extern NpcTerritoryInfo btl_moo_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_moo_tbl[];
extern EvtWord moo_00_init_evt[];
extern EvtWord moo_01_init_evt[];
extern EvtWord moo_02_init_evt[];
extern EvtWord moo_03_init_evt[];
extern EvtWord moo_04_init_evt[];
extern EvtWord moo_05_init_evt[];
extern EvtWord moo_06_init_evt[];
extern EvtWord moo_07_init_evt[];
extern BattleUnitKind unit_kuriboo;
extern BattleUnitKind unit_sinemon;
extern BattleUnitKind unit_barriern_z;
extern BattleUnitKind unit_barriern_z_satellite;

#if VERSION >= VERSION_US
// US and PAL share one rock_main (defined in moo_00); JP gives every map its own static copy.
extern EvtWord rock_main[];
#endif
