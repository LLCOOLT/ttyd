#pragma once

#include "dolphin/types.h"
#include "evt/evt_word.h"

#if !defined(VERSION_G8ME01) || defined(VERSION_G8MP01)  // JP and PAL have this REL
extern EvtWord dig_00_init_evt[];
#endif
