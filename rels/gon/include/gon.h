// Declarations for the Hooktail Castle (gon) module: map init scripts, battle setup tables, the Paper Curse lecture scripts and the area's battle units.
#pragma once

#include "dolphin/types.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

extern NpcTerritoryInfo btl_gon_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_gon_tbl[];
extern EvtWord gon_00_init_evt[];
extern EvtWord gon_01_init_evt[];
extern EvtWord gon_02_init_evt[];
extern EvtWord gon_03_init_evt[];
extern EvtWord gon_04_init_evt[];
extern EvtWord gon_05_init_evt[];
extern EvtWord gon_06_init_evt[];
extern EvtWord gon_07_init_evt[];
extern EvtWord gon_08_init_evt[];
extern EvtWord gon_09_init_evt[];
extern EvtWord gon_10_init_evt[];
extern EvtWord gon_11_init_evt[];
extern EvtWord gon_12_init_evt[];
extern EvtWord gon_13_init_evt[];
extern EvtWord gon_bt00_init_evt[];
extern EvtWord slit_majin_lecture[];
extern EvtWord slit_majin_lecture_init[];
extern BattleUnitKind unit_boss_gonbaba;
extern BattleUnitKind unit_honenoko;
extern BattleUnitKind unit_nokonoko;
extern BattleUnitKind unit_patakuri;
extern BattleUnitKind unit_patapata;
extern BattleUnitKind unit_togekuri;

// User functions defined in the area's files (global symbols in the original REL).
// gon_11.c
USER_FUNC(evt_iri_16_cloud_init);
USER_FUNC(evt_iri_16_cloud_ent);
