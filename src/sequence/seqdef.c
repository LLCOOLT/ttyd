#include "driver/seqdrv.h"

extern void seq_logoInit(SequenceWork* work);
extern void seq_logoMain(SequenceWork* work);
extern void seq_logoExit(SequenceWork* work);
extern void seq_titleInit(SequenceWork* work);
extern void seq_titleMain(SequenceWork* work);
extern void seq_titleExit(SequenceWork* work);
extern void seq_gameInit(SequenceWork* work);
extern void seq_gameMain(SequenceWork* work);
extern void seq_gameExit(SequenceWork* work);
extern void seq_mapChangeInit(SequenceWork* work);
extern void seq_mapChangeMain(SequenceWork* work);
extern void seq_mapChangeExit(SequenceWork* work);
extern void seq_battleInit(SequenceWork* work);
extern void seq_battleMain(SequenceWork* work);
extern void seq_battleExit(SequenceWork* work);
extern void seq_gameOverInit(SequenceWork* work);
extern void seq_gameOverMain(SequenceWork* work);
extern void seq_gameOverExit(SequenceWork* work);
extern void seq_loadInit(SequenceWork* work);
extern void seq_loadMain(SequenceWork* work);
extern void seq_loadExit(SequenceWork* work);
extern void seq_e3Init(SequenceWork* work);
extern void seq_e3Main(SequenceWork* work);
extern void seq_e3Exit(SequenceWork* work);

SequenceCallback seq_data[8][3] = {
	{seq_logoInit, seq_logoMain, seq_logoExit},
	{seq_titleInit, seq_titleMain, seq_titleExit},
	{seq_gameInit, seq_gameMain, seq_gameExit},
	{seq_mapChangeInit, seq_mapChangeMain, seq_mapChangeExit},
	{seq_battleInit, seq_battleMain, seq_battleExit},
	{seq_gameOverInit, seq_gameOverMain, seq_gameOverExit},
	{seq_loadInit, seq_loadMain, seq_loadExit},
	{seq_e3Init, seq_e3Main, seq_e3Exit},
};
