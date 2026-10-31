#pragma once

// Declarations shared by the kpa.rel units (クッパ, Bowser's side-scrolling stages).

#include "version.h"
#include "dolphin/types.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

extern EvtWord kpa_00_init_evt[];
extern EvtWord kpa_01_init_evt[];
extern EvtWord kpa_02_init_evt[];
extern EvtWord kpa_03_init_evt[];
extern EvtWord kpa_04_init_evt[];
extern EvtWord kpa_05_init_evt[];
extern EvtWord kpa_06_init_evt[];
extern EvtWord kpa_07_init_evt[];
extern EvtWord kpa_bgm_change[];
extern EvtWord kpa_dead[];
extern EvtWord kpa_fall_sub[];
extern EvtWord kpa_init[];
extern EvtWord kpa_read_item[];
extern EvtWord kpa_read_mobj[];
extern EvtWord kpa_stage_start[];
extern EvtWord kpa_time[];

extern EvtWord kpa_status_main_evt[];

USER_FUNC(kpa_status_init);

#if VERSION == VERSION_EU
USER_FUNC(kpa_cancel_attack_mode); // kpa_01, called by kpa_03's jumpstand_evt
#endif
