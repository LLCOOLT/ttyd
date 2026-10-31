// Test map (qiz, JP and PAL only): declares the qiz_00 init event.
#pragma once

#include "dolphin/types.h"
#include "evt/evt_word.h"
#include "version.h"

#if VERSION != VERSION_US && VERSION != VERSION_DEMO_US2 // JP and PAL have this REL
extern EvtWord qiz_00_init_evt[];
#endif
