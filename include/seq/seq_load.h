#pragma once

#include "driver/seqdrv.h"
#include "evt/evt_word.h"

void seq_loadExit(SequenceWork* seq);
void seq_loadInit(SequenceWork* seq);
void seq_loadMain(SequenceWork* seq);

extern EvtWord evt_continue[];
extern s32 stone_id[];
