// event.c: the story event tables (EventData, EventStage): per-chapter progress points.
#pragma once

#include <dolphin/types.h>
#include "version.h"

typedef struct EventData {
    u8 motionType;      // 0x0
    u8 partners[2];     // 0x1
    u16 id;             // 0x4
    const char* textId; // 0x8
    const char* nameJp; // 0xC
#if VERSION >= VERSION_US
    const char* nameEn; // 0x10
#endif
    const char* mapName;     // 0x10
    const char* beroName;    // 0x14
    void (*initEvent)(void); // 0x18
} EventData;

typedef struct EventStage {
    const char* name; // 0x0
#if VERSION >= VERSION_US
    const char* nameEn; // 0x4
#endif
    EventData* data; // 0x4
    s32 count;       // 0x8
} EventStage;

void stg0_00_init(void);

void N_stg9_02_init(void);

EventStage* eventStgDtPtr(s32 stage);
s32 eventStgNum(void);
