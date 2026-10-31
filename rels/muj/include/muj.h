// Keelhaul Key (muj, mujinto: desert island): declarations of the area's map init events, battle tables and shared
// events.
#pragma once

#include "dolphin/types.h"
#include "evt/evt_cmd.h"
#include "driver/npcdrv.h"
#include "data_tables.h"
#include "driver/extdrv.h"

extern EvtWord all_party_lecture[];
extern EvtWord anm_entotsu[];
extern EvtWord anm_kaji[];
extern EvtWord anm_neji[];
extern EvtWord anm_wakka[];
extern NpcTerritoryInfo btl_muj_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_muj_tbl[];
extern EvtWord korutesu_apper[];
extern EvtWord korutesu_vanish[];
extern EvtWord muj_00_init_evt[];
extern EvtWord muj_01_init_evt[];
extern EvtWord muj_02_init_evt[];
extern EvtWord muj_03_init_evt[];
extern EvtWord muj_04_init_evt[];
extern EvtWord muj_05_init_evt[];
extern EvtWord muj_10_init_evt[];
extern EvtWord muj_11_init_evt[];
extern EvtWord muj_12_init_evt[];
extern EvtWord muj_20_init_evt[];
extern EvtWord muj_21_init_evt[];
USER_FUNC(muj_npc_guruguru);
extern EvtWord muj_ship_puka[];
extern BattleUnitKind unit_boss_gundan_zako_group1;
extern BattleUnitKind unit_flower_chorobon;
extern BattleUnitKind unit_green_chorobon;
extern BattleUnitKind unit_hermos;
extern BattleUnitKind unit_kuriboo;
extern BattleUnitKind unit_poison_pakkun;

extern EvtWord korutesu_appear_event[];
extern TreeAccess tree_tbl_treeb_evt[];

USER_FUNC(muj_npc_fuwafuwa);
USER_FUNC(muj_npc_buruburu);
USER_FUNC(zakogun_set_target_id);
USER_FUNC(zakogun_damage_pose);
USER_FUNC(zakogun_damage_pose_cancel);
USER_FUNC(zakogun_ext_init1);
USER_FUNC(zakogun_escape1);
USER_FUNC(up_ceil);
USER_FUNC(zakogun_escape2);
USER_FUNC(zakogun_ext_init3);
void zakogun_ext_init123_common(ExtdrvPose* pose, s32 i);
s32 zakogun_get_kanbu_id(void);
BattleUnit* zakogun_get_ptr(void);
void zakogun_ext_main2(void);
extern BattleUnitKind unit_boss_cortez;
extern BattleUnitKind unit_boss_cortez_claw;
extern BattleUnitKind unit_boss_cortez_rapier;
extern BattleUnitKind unit_boss_cortez_saber;
extern BattleUnitKind unit_boss_cortez_sword;
extern EvtWord cortez_weapon_get_home_height[];
extern EvtWord cortez_weapon_set_formation_attribute[];
extern EvtWord cortez_weapon_unison_phase_event[];
extern EvtWord cortez_weapon_phase_event[];
extern EvtWord cortez_weapon_counter_damage_event[];
extern EvtWord cortez_weapon_dead_event[];
extern EvtWord cortez_weapon_break_event[];
extern EvtWord cortez_weapon_blow_dead_event[];
extern EvtWord zakogun_entry[];
extern BattleUnitKind unit_boss_gundan_zako_group2;
extern BattleUnitKind unit_boss_gundan_zako_group3;
extern BattleUnitKind unit_boss_kanbu3;
