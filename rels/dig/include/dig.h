// Test map for THP movie playback (dig: JP, PAL and the Japanese demo): the dig_00 init event and the movie
// start/stop functions.
#pragma once

#include "dolphin/types.h"
#include "evt/evt_word.h"

extern EvtWord dig_00_init_evt[];

void dig_thpStop(void);
void dig_thpInit(void);
