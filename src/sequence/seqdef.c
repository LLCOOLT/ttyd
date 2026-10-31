#include "driver/seqdrv.h"
#include "evt/evt_snd.h"
#include "seq/seq_logo.h"
#include "seq/seq_title.h"
#include "seq/seq_game.h"
#include "seq/seq_mapchange.h"
#include "seq/seq_gameover.h"
#include "seq/seq_load.h"
#include "seq/seq_e3.h"
#ifdef VERSION_G8ME01_DEMO
#include "seq/seq_demo.h"
#endif

extern void seq_battleInit(SequenceWork* work);
extern void seq_battleMain(SequenceWork* work);
extern void seq_battleExit(SequenceWork* work);

#ifdef VERSION_G8ME01_DEMO
SequenceCallback seq_data[9][3] = {
#else
SequenceCallback seq_data[8][3] = {
#endif
	{seq_logoInit, seq_logoMain, seq_logoExit},
	{seq_titleInit, seq_titleMain, seq_titleExit},
	{seq_gameInit, seq_gameMain, seq_gameExit},
	{seq_mapChangeInit, seq_mapChangeMain, seq_mapChangeExit},
	{seq_battleInit, seq_battleMain, seq_battleExit},
	{seq_gameOverInit, seq_gameOverMain, seq_gameOverExit},
	{seq_loadInit, seq_loadMain, seq_loadExit},
#ifdef VERSION_G8ME01_DEMO
	{seq_demoInit, seq_demoMain, seq_demoExit},
#endif
	{seq_e3Init, seq_e3Main, seq_e3Exit},
};
