#pragma once

#include "driver/seqdrv.h"

void seq_loadExit(SequenceWork* seq);
void seq_loadInit(SequenceWork* seq);
void seq_loadMain(SequenceWork* seq);

extern s32 evt_continue[];
extern s32 stone_id[];
