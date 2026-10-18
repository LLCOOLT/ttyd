#pragma once

#include "evt/evt_cmd.h"
#include <dolphin/types.h>

typedef struct {
    u16 flags; //0x0, bit 1 = already heard (read flag)
    s16 labelId; //0x2
    s32 initEndPos; //0x4
    s16 tagEndPos; //0x8
    s16 unkA; //0xA
    s16 storyId; //0xC
    s16 unkE; //0xE
} InformantInfo;

typedef struct {
    u8 ketiRead[0xD]; //0x0, read flags by storyId (johoya_keti_newjoho_setreadflag)
    u8 perfectRead[0xD]; //0xD, johoya_perfect_newjoho_setreadflag
    u8 luigiRead[0xD]; //0x1A, johoya_luigi_newjoho_setreadflag
    u8 unk27[0x4]; //0x27
} InformantUnknown;

typedef struct {
    InformantInfo* info; //0x0
    s32 count; //0x4
    const char* prefix; //0x8
    InformantInfo *infoEnd; //0xC
    s32 curIndex; //0x10, info index picked by the makelabel funcs
    InformantUnknown readFlags; //0x14
    u8 unk3F[0x40 - 0x3F]; //0x3F
} InformantWork;

USER_FUNC(johoya_data_alloc);
USER_FUNC(johoya_data_free);
void johoya_init(void);
s32 search_evt_no(const char* label);
