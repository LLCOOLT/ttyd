// Declarations for the Riverside Station (eki) area: battle setup tables, the per-room init events, the key-item lecture event and the area's battle units.
#pragma once

#include "dolphin/types.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

extern EvtWord all_juyoitem_lecture_rel[];
extern NpcTerritoryInfo btl_eki_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_eki_tbl[];
extern EvtWord eki_00_init_evt[];
extern EvtWord eki_01_init_evt[];
extern EvtWord eki_02_init_evt[];
extern EvtWord eki_03_init_evt[];
extern EvtWord eki_04_init_evt[];
extern EvtWord eki_05_init_evt[];
extern EvtWord eki_06_init_evt[];
extern BattleUnitKind unit_kuriboo;
extern BattleUnitKind unit_kurokumorn;
extern BattleUnitKind unit_patatogemet;
extern BattleUnitKind unit_sambo_mummy;

extern EvtWord evt_sw_complete[];
