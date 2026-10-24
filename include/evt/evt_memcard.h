#pragma once

#include "dolphin/types.h"
#include "evt/evt_word.h"

extern EvtWord evt_memcard_save[];

extern EvtWord evt_memcard_check[];
extern EvtWord evt_memcard_copy[];
extern EvtWord evt_memcard_delete[];
#ifdef VERSION_G8ME01
extern EvtWord evt_memcard_save_wrapper[];
#endif
extern EvtWord evt_memcard_start[];
