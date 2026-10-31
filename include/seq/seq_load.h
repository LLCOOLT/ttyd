// seq_load.c: the file select sequence (seq_: game sequence), with the evt_continue script and stone_id table.
#pragma once

#include "driver/seqdrv.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

void seq_loadExit(SequenceWork* seq);
void seq_loadInit(SequenceWork* seq);
void seq_loadMain(SequenceWork* seq);

extern EvtWord evt_continue[];
extern s32 stone_id[];

USER_FUNC(evt_seq_load_keep_msg_window);
