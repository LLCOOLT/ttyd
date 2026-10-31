// Declarations for the Creepy Steeple (jin) area: battle tables, per-room init events, the shadow-Mario party event, the Vivian pose function and the area's battle units.
#pragma once

#include "dolphin/types.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

extern NpcTerritoryInfo btl_jin_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_jin_tbl[];
extern EvtWord evt_usu_kagemario_party_kill[];
extern EvtWord jin_00_init_evt[];
extern EvtWord jin_01_init_evt[];
extern EvtWord jin_02_init_evt[];
extern EvtWord jin_03_init_evt[];
extern EvtWord jin_04_init_evt[];
extern EvtWord jin_05_init_evt[];
extern EvtWord jin_06_init_evt[];
extern EvtWord jin_07_init_evt[];
extern EvtWord jin_08_init_evt[];
extern EvtWord jin_09_init_evt[];
extern EvtWord jin_10_init_evt[];
extern EvtWord jin_11_init_evt[];
extern BattleUnitKind unit_atmic_teresa;
extern BattleUnitKind unit_basabasa;
extern BattleUnitKind unit_boss_rampell;
extern BattleUnitKind unit_met;
extern BattleUnitKind unit_teresa;
extern BattleUnitKind unit_togemet;

USER_FUNC(evt_jin_vivian_pose_set);
extern BattleUnitKind unit_faker_mario;
extern BattleUnitKind unit_gullible_christine;
extern BattleUnitKind unit_gullible_clauda;
extern BattleUnitKind unit_gullible_nokotarou;
extern BattleUnitKind unit_gullible_yoshi;

// User functions defined in the area's files (global symbols in the original REL).
// event/evt_kagemario.c
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_kagemario_change);
// jin_00.c
USER_FUNC(get_npc_color);
USER_FUNC(senteresa_get_seq);
USER_FUNC(senteresa_get_random_position);
USER_FUNC(senteresa_tikaduku_stop);
USER_FUNC(senteresa_syugo);
USER_FUNC(senteresa_dispoff);
USER_FUNC(senteresa_huttobu);
// jin_07.c
USER_FUNC(senteresa_get_position);
USER_FUNC(senteresa_okure_move_init);
USER_FUNC(senteresa_okure_move);
// jin_10.c
USER_FUNC(set_pos);
// unit/unit_faker_mario.c
USER_FUNC(_save_param);
USER_FUNC(_load_param);
