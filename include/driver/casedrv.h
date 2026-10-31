// casedrv.c: the case driver (CaseSetup, CaseEntry): hit-object triggers that run an event script.
#pragma once

#include <dolphin/types.h>
#include "evt/evt_word.h"

struct HitEntry;

struct CaseEntry;

// CaseSetup/CaseEntry.conditionId and the first argument of evt_run_case_evt: what triggers the case event.
// The "+ A" cases 5, 9 and 12 need A pressed that frame while Mario stands, walks or dashes (or rides Yoshi) and
// there is no NPC to talk to; case 4 reads A directly.
typedef enum CaseCondition {
    CASE_COND_STAND_ON = 0,            // Mario stands on the hit object
    CASE_COND_NOT_STAND_ON = 1,        // Mario does not stand on it
    CASE_COND_UNDER = 2,               // the hit object is under Mario (hitobjUnder)
    CASE_COND_NOT_UNDER = 3,           // it is not
    CASE_COND_JUMP_FROM_A = 4,         // Mario jumps off it with A (first airborne frame)
    CASE_COND_STAND_ON_A = 5,          // standing on it + A
    CASE_COND_STAND_ON_STICK_DOWN = 6, // standing on it with the stick held down (pipes)
    CASE_COND_STAND_ON_STICK_UP = 7,   // standing on it and the stick pushed up this frame
    CASE_COND_FRONT = 8,               // the hit object is in front of Mario
    CASE_COND_FRONT_A = 9,             // in front of Mario + A (doors, signs, chests)
    CASE_COND_PUSH = 10,               // Mario pushes against it
    CASE_COND_NOT_PUSH = 11,           // Mario does not push against it
    CASE_COND_PUSH_A = 12,             // pushing against it + A
    CASE_COND_HAMMER = 13,             // hit by the hammer (hitobjHammer)
    CASE_COND_HAMMER_2 = 14,           // hit by the hammer during MARIO_MOTION_HAMMER_2
    CASE_COND_BOBBERY = 15,            // hit by Bobbery's bomb (PartyEntry.hitobjAction)
    CASE_COND_HEAD = 16,               // Mario hits it with his head (hitobjHead)
    CASE_COND_ACTIVE_FUNC = 17,        // CaseSetup.activeFunc returns nonzero
    CASE_COND_SW = 18,                 // swGet(swFlag) is set
    CASE_COND_SW_LOCAL = 19,           // _swGet(swFlag) is set
} CaseCondition;

// CaseSetup.conditionId: OR-ed in when evt_run_case_evt's second argument is nonzero; sets CASE_ENTRY_FLAG_BALLOON,
// which lets mario_balloon.c show the "!" balloon over Mario at the hit object (cases 5, 9 and 12)
#define CASE_COND_FLAG_BALLOON 0x8000

// CaseEntry.flags
#define CASE_ENTRY_FLAG_IN_USE 0x1
#define CASE_ENTRY_FLAG_TRIGGERED 0x2 // the condition held this frame; caseMain starts the event
#define CASE_ENTRY_FLAG_BALLOON 0x4   // from CASE_COND_FLAG_BALLOON

// CaseSetup/CaseEntry.activeFunc: returns nonzero when the case should trigger.
typedef s32 (*CaseActiveFn)(struct CaseEntry* entry);

typedef struct CaseSetup {
    u16 conditionId;         // 0x0, CaseCondition, | CASE_COND_FLAG_BALLOON
    u8 pad_2[2];             // 0x2
    const char* hitObjName;  // 0x4
    u32 swFlag;              // 0x8
    CaseActiveFn activeFunc; // 0xC, for CASE_COND_ACTIVE_FUNC
    s32 lwData[16];          // 0x10
    u8 pad_50[0x54 - 0x50];  // 0x50, never accessed
    EvtWord* evtCode;        // 0x54
    s32 priority;            // 0x58
} CaseSetup;

typedef struct CaseEntry {
    u16 flags;               // 0x0, CASE_ENTRY_FLAG_*
    u8 pad_2[2];             // 0x2
    s32 conditionId;         // 0x4, CaseCondition
    char hitObjName[0x40];   // 0x8
    s32 caseId;              // 0x48
    u32 swFlag;              // 0x4C
    CaseActiveFn activeFunc; // 0x50
    s32 lwData[16];          // 0x54
    s32 evtId;               // 0x94
    EvtWord* evtCode;        // 0x98
    s32 priority;            // 0x9C
} CaseEntry;

void caseInit(void);
void caseReInit(void);
s32 caseEntry(CaseSetup* setup);
void caseDelete(s32 caseId);
CaseEntry* caseIdToPtr(s32 caseId);
void caseMain(void);
CaseEntry* caseCheckHitObj(struct HitEntry* obj);

CaseEntry* caseCheckHitObj2(struct HitEntry* obj);
