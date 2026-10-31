// party_data.c: the partner table partyDataTbl (PartyData: init/move/use/exit functions) and the pose name tables.
#pragma once

#include "party.h"

typedef void (*PartyFunc)(PartyEntry* party);

typedef struct PartyData {
    char* name;            // 0x0
    PartyFunc init_func;   // 0x4
    PartyFunc move_func;   // 0x8
    PartyFunc use_func;    // 0xC
    PartyFunc post_func;   // 0x10
    PartyFunc bye_func;    // 0x14
    PartyFunc reserved_18; // 0x18, NULL for every partner, never called
    PartyFunc reserved_1C; // 0x1C, NULL for every partner, never called
    PartyFunc reserved_20; // 0x20, NULL for every partner, never called
    PartyFunc exit_func;   // 0x24
} PartyData;

extern PartyData partyDataTbl[];

extern char* partyDotPoseTbl[8][15];
extern char* partyPoseTbl[20][15];
extern char* yoshiDotPoseTbl[7][15];
