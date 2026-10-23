#pragma once

#include "dolphin/types.h"
#include "evt/evt_cmd.h"
#include "driver/npcdrv.h"
#include "data_tables.h"

extern s32 all_party_lecture[];
extern s32 anm_entotsu[];
extern s32 anm_kaji[];
extern s32 anm_neji[];
extern s32 anm_wakka[];
extern NpcTerritoryInfo btl_muj_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_muj_tbl[];
extern s32 korutesu_apper[];
extern s32 korutesu_vanish[];
extern s32 muj_00_init_evt[];
extern s32 muj_01_init_evt[];
extern s32 muj_02_init_evt[];
extern s32 muj_03_init_evt[];
extern s32 muj_04_init_evt[];
extern s32 muj_05_init_evt[];
extern s32 muj_10_init_evt[];
extern s32 muj_11_init_evt[];
extern s32 muj_12_init_evt[];
extern s32 muj_20_init_evt[];
extern s32 muj_21_init_evt[];
USER_FUNC(muj_npc_guruguru);
extern s32 muj_ship_puka[];
extern BattleUnitKind unit_boss_gundan_zako_group1;
extern BattleUnitKind unit_flower_chorobon;
extern BattleUnitKind unit_green_chorobon;
extern BattleUnitKind unit_hermos;
extern BattleUnitKind unit_kuriboo;
extern BattleUnitKind unit_poison_pakkun;

extern s32 korutesu_appear_event[];
extern TreeAccess tree_tbl_treeb_evt[];
