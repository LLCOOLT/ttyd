// src/sequence/seq_logo.c: the boot logo sequence (seq_: game sequence) and its work struct LogoWork.
#pragma once

#include "driver/seqdrv.h"
#include "version.h"
#include "manager/filemgr.h"
#include <dolphin/os.h>

typedef struct LogoWork {
#if VERSION >= VERSION_US
    FileEntry* texture;   // 0x0
    s32 logoId;           // 0x4, screen shown (LogoScreen in seq_logo.c)
    OSTime lastInputTime; // 0x8, OSGetTime of the last pad input (prompt times out after 10 s)
    BOOL skipStory;       // 0x10
    s32 promptStep;       // 0x14, progressive-scan prompt step
    BOOL progressive;     // 0x18
    s32 toggle;           // 0x1C, 0 = yes, 1 = no
#else
    BOOL progressive;       // 0x0
    s32 promptStep;         // 0x4, progressive-scan prompt step
    s32 toggle;             // 0x8, 0 = yes, 1 = no
    FileEntry* texture;     // 0xC
    s32 logoId;             // 0x10, logo shown (LogoScreen in seq_logo.c)
    u8 pad_14[0x18 - 0x14]; // 0x14, never accessed
    OSTime lastInputTime;   // 0x18, OSGetTime of the last pad input (prompt times out after 10 s)
    BOOL skipStory;         // 0x20
    u8 pad_24[0x28 - 0x24]; // 0x24, never accessed
#endif
} LogoWork;

void seq_logoInit(SequenceWork* work);
void seq_logoMain(SequenceWork* work);
void seq_logoExit(SequenceWork* work);
