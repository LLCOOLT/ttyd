// src/sequence/seq_game.c: the game sequence (seq_: game sequence) that runs while Mario is in the field.
#pragma once

#include <dolphin/os.h>
#include "driver/seqdrv.h"

void seq_gameInit(SequenceWork* work);
void seq_gameMain(SequenceWork* work);

void seq_gameExit(SequenceWork* wp);
