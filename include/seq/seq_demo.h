// seq_demo.c: the movie sequence (seq_: game sequence) and the THPSimple* movie player it uses.
#pragma once

#include "dolphin/gx/GXStruct.h"
#include "version.h"

BOOL THPSimpleInit(s32 audioSystem);
void THPSimpleQuit(void);
BOOL THPSimpleOpen(char* fileName);
BOOL THPSimpleClose(void);
u32 THPSimpleCalcNeedMemory(void);
BOOL THPSimpleSetBuffer(u8* buffer);
BOOL THPSimplePreLoad(s32 loop);
void THPSimpleAudioStart(void);
void THPSimpleAudioStop(void);
BOOL THPSimpleLoadStop(void);
s32 THPSimpleDecode(s32 audioTrack);
s32 THPSimpleDrawCurrentFrame(GXRenderModeObj* rmode, u32 x, u32 y, u32 polygonW, u32 polygonH);
u32 THPSimpleGetTotalFrame(void);
BOOL THPSimpleSetVolume(s32 vol, s32 time);

#if VERSION <= VERSION_DEMO_JP
#include "driver/seqdrv.h"

// the demo's movie sequence (seq_data[7]), at the end of its seq_demo.c
void seq_demoInit(SequenceWork* work);
void seq_demoMain(SequenceWork* work);
void seq_demoExit(SequenceWork* work);
#endif
