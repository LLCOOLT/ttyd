// Test map for THP movie playback (dig, JP and PAL only): the dig_00 init event and the movie start/stop functions.
#pragma once

#include "dolphin/types.h"
#include "evt/evt_word.h"
#include "version.h"

#if VERSION != VERSION_US && VERSION != VERSION_DEMO_US2 // JP and PAL have this REL
extern EvtWord dig_00_init_evt[];

void dig_thpStop(void);
void dig_thpInit(void);

#endif
