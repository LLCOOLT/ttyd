// seq_battle.c: the battle sequence (seq_: game sequences/screens); loads the battle map and runs the battle.
#pragma once

#include "driver/seqdrv.h"

// Battle sequence (SEQ_BATTLE): loads the battle map and runs the battle until it ends.
void seq_battleInit(SequenceWork* work);
void seq_battleMain(SequenceWork* work);
void seq_battleExit(SequenceWork* work);
