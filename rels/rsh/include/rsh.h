// Declarations for the Excess Express (rsh) area: battle setup tables, per-room init events, shared door/window/random-passenger events and the Smorg (moamoa) battle units.
#pragma once

#include "dolphin/types.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

extern NpcTerritoryInfo btl_rsh_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_rsh_tbl[];
extern EvtWord evt_rsh_01_rnd_npc_entry[];
extern EvtWord evt_rsh_03_rnd_npc_entry[];
extern EvtWord evt_rsh_04_rnd_npc_entry[];
extern EvtWord evt_rsh_door_entry[];
extern EvtWord evt_rsh_door_init[];
extern EvtWord evt_rsh_konarikin_irai_party_talk[];
extern EvtWord evt_rsh_moamoa_on_window[];
extern EvtWord evt_rsh_rnd_npc_init[];
extern EvtWord evt_rsh_window[];
extern EvtWord rsh_00_a_init_evt[];
extern EvtWord rsh_00_a_init_evt_nidome[];
extern EvtWord rsh_00_b_init_evt[];
extern EvtWord rsh_00_b_init_evt_nidome[];
extern EvtWord rsh_00_c_init_evt[];
extern EvtWord rsh_00_c_init_evt_nidome[];
extern EvtWord rsh_01_a_init_evt[];
extern EvtWord rsh_01_a_init_evt_nidome[];
extern EvtWord rsh_01_b_init_evt[];
extern EvtWord rsh_01_b_init_evt_nidome[];
extern EvtWord rsh_01_c_init_evt[];
extern EvtWord rsh_01_c_init_evt_nidome[];
extern EvtWord rsh_02_a_init_evt[];
extern EvtWord rsh_02_a_init_evt_nidome[];
extern EvtWord rsh_02_b_init_evt[];
extern EvtWord rsh_02_b_init_evt_nidome[];
extern EvtWord rsh_02_c_init_evt[];
extern EvtWord rsh_02_c_init_evt_nidome[];
extern EvtWord rsh_03_a_init_evt[];
extern EvtWord rsh_03_a_init_evt_nidome[];
extern EvtWord rsh_03_b_init_evt[];
extern EvtWord rsh_03_b_init_evt_nidome[];
extern EvtWord rsh_03_c_init_evt[];
extern EvtWord rsh_03_c_init_evt_nidome[];
extern EvtWord rsh_04_a_init_evt[];
extern EvtWord rsh_04_a_init_evt_nidome[];
extern EvtWord rsh_04_b_init_evt[];
extern EvtWord rsh_04_b_init_evt_nidome[];
extern EvtWord rsh_04_c_init_evt[];
extern EvtWord rsh_04_c_init_evt_nidome[];
extern EvtWord rsh_05_a_init_evt[];
extern EvtWord rsh_05_a_init_evt_nidome[];
extern EvtWord rsh_06_a_init_evt[];
extern EvtWord rsh_06_a_init_evt_nidome[];
extern EvtWord rsh_07_a_init_evt[];
extern EvtWord rsh_07_b_init_evt[];
extern EvtWord rsh_07_c_init_evt[];
extern EvtWord rsh_08_a_init_evt[];

extern s32 moamoa_defence_no_parts[];
extern PoseTableEntry moamoa1_weakness_pose_table[];
extern BattleUnitKind unit_boss_moamoa;
extern BattleUnitKind unit_boss_moamoa_mouth;
extern BattleUnitKind unit_boss_moamoa_tentacle_a;
extern BattleUnitKind unit_boss_moamoa_tentacle_b;
extern BattleUnitKind unit_boss_moamoa_tentacle_c;

// User functions defined in the area's files (global symbols in the original REL).
// rsh_00.c
USER_FUNC(evt_moamoa_set_one);
USER_FUNC(evt_moamoa_set_seq_all);
// rsh_02.c
USER_FUNC(mario_normalize_wait);
// rsh_03.c
USER_FUNC(iri_22_make_item_tbl);
USER_FUNC(omiseHozon);
USER_FUNC(omiseFukki);
// unit/unit_boss_moamoa.c
USER_FUNC(boss_moamoa_check_zenei_kouei);
USER_FUNC(evt_moamoa_mainUnitIdClear);
USER_FUNC(moamoa_on);
