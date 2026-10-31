// Majolyne / Marilyn / Vivian (the Shadow Sirens): types and scripts shared between the win battle
// (chapter 2) and the las rematch (chapter 8), each built from its own copy of the units.
#pragma once

#include "evt/evt_cmd.h"
#include <dolphin/types.h>

// majo3_sort: one sister and the value she is sorted by (largest first).
typedef struct MajoSortEntry {
    s32 id;    // 0x0
    s32 value; // 0x4
} MajoSortEntry;

// unit_boss_majolyne.c / unit_boss_majolyne_las.c
extern EvtWord btl_majolyne_zoom[];
extern EvtWord btl_marilyn_zoom[];
extern EvtWord btl_vivian_zoom[];
extern EvtWord majo3_shadow_tail_event[];
extern EvtWord majo_unison_phase_event[];
