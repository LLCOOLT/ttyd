// Case driver: "cases" run an event script when Mario touches, jumps on, stands on or hammers a
// named hit object (or when a custom condition function says so).
#include "driver/casedrv.h"
#include "driver/hitdrv.h"
#include "driver/npcdrv.h"
#include "driver/swdrv.h"
#include "manager/evtmgr.h"
#include "party/party_yoshi.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mariost.h"
#include "memory.h"
#include "party.h"
#include "system.h"
#include "win/win_main.h"
#include <string.h>
#include "version.h"
#include <dolphin/pad.h>
#include <demo/DEMOPad.h>

// FAKE: casedrv.c calls evtEntry through the prototype it was compiled with (an s32 priority, passed without
// the u8 truncation) instead of the one in manager/evtmgr.h; same registers
typedef EventEntry* (*EvtEntryS32PriorityFn)(void* evtCode, s32 priority, u8 flags);

typedef struct CaseWork {
    s32 count;          // 0x0
    CaseEntry* entries; // 0x4
} CaseWork;

//.sbss
static CaseWork work;
/** The table of case entries (64 slots); wp is the pointer the code uses. */
static CaseWork* wp = &work;

/** Allocates and clears the table of 64 case entries at boot. */
void caseInit(void) {
    wp->count = 64;
    wp->entries = __memAlloc(HEAP_DEFAULT, wp->count * sizeof(CaseEntry));
    memset(wp->entries, 0, wp->count * sizeof(CaseEntry));
}

/** Releases every case entry, e.g. on a map change; the table stays allocated. */
void caseReInit(void) {
    CaseEntry* entry = wp->entries;
    int i;

    for (i = 0; i < wp->count; i++, entry++) {
        entry->flags &= ~CASE_ENTRY_FLAG_IN_USE;
    }
}

/**
 * Registers a case from a CaseSetup: the event script to start, its priority,
 * the hit object name and condition (or a save flag or a check function) that fires it.
 * Returns the case id the scripts use to delete it. Called by the evt_case helpers.
 */
s32 caseEntry(CaseSetup* setup) {
    CaseEntry* entry;
    int i = 0;
    for (entry = wp->entries; i < wp->count; i++, entry++) {
        if (!(entry->flags & CASE_ENTRY_FLAG_IN_USE)) {
            break; // unused entry
        }
    }
    memset(entry, 0, sizeof(CaseEntry));
    entry->caseId = i;
    entry->flags = 0;
    entry->conditionId = setup->conditionId & ~CASE_COND_FLAG_BALLOON;
    if (setup->conditionId & CASE_COND_FLAG_BALLOON) {
        entry->flags |= CASE_ENTRY_FLAG_BALLOON;
    }
    entry->flags |= CASE_ENTRY_FLAG_IN_USE;
    strcpy(entry->hitObjName, setup->hitObjName);
    entry->swFlag = setup->swFlag;
    entry->activeFunc = setup->activeFunc;
    entry->evtCode = setup->evtCode;
    entry->priority = setup->priority;
    entry->evtId = 0;
    memcpy(entry->lwData, setup->lwData, sizeof(entry->lwData));
    return i & 0xFFFFFFFFFFFFFFFFu; // FAKE: the no-op 64-bit mask swaps the i and entry registers as in the target; see FAKES.md
}

/** Releases case entry caseId so it no longer fires. */
void caseDelete(s32 caseId) {
    wp->entries[caseId].flags &= ~CASE_ENTRY_FLAG_IN_USE;
}

#define SET_HIT(entry) (entry)->flags |= CASE_ENTRY_FLAG_TRIGGERED

/**
 * Once per field frame: checks every active case against what Mario stands on, faces, pushes,
 * hammers or bumps his head on (plus button and stick presses, Bobbery's blast and flags)
 * and starts each fired case's event script with the case's saved LW values, unless one is still running.
 * Skipped in battle, with a window open, or while Mario can't take case events;
 * the demo checks the field battle mode directly instead of N_fbatPreventMarioEventChk.
 */
void caseMain(void) {
    MarioWork* mario;
    PartyEntry* party;
    s32 pressedA;
    CaseEntry* entry;
    s32 i;
    u16 btn;
    HitEntry* standOn;
    HitEntry* under;
    HitEntry* jumpFrom;
    HitEntry* front;
    HitEntry* push;
    HitEntry* hammer;
    HitEntry* head;
#if VERSION <= VERSION_DEMO_JP
    s32 fbatMode;
#endif

    mario = marioGetPtr();
    partyGetPtr(marioGetPartyId());
    standOn = mario->hitobjStandOn;
    under = mario->hitobjUnder;
    jumpFrom = mario->hitobjJumpFrom;
    front = mario->hitobjFront;
    push = mario->hitobjPush;
    hammer = mario->hitobjHammer;
    head = mario->hitobjHead;
    btn = mario->buttonTrg;
#if VERSION <= VERSION_DEMO_JP
    // the demo has no N_fbatPreventMarioEventChk: only field battle modes 0 and 1 allow case events
    if ((u32)marioStGetSystemLevel() == 0 && !winCheck() && gp->inBattle == 0 &&
        ((fbatMode = fbatGetPointer()->mode) == 0 || fbatMode == 1) && marioCaseEventValidChk()) {
#else
    if ((u32)marioStGetSystemLevel() == 0 && !winCheck() && gp->inBattle == 0 &&
        !N_fbatPreventMarioEventChk() && marioCaseEventValidChk()) {
#endif
        if (mario->currMotionId != MARIO_MOTION_STAY && mario->currMotionId != MARIO_MOTION_WALK && mario->currMotionId != MARIO_MOTION_DASH &&
            yoshiGetStatus() != 1) {
            btn = 0;
        }
        pressedA = btn & PAD_BUTTON_A;
        entry = wp->entries;
        for (i = 0; i < wp->count; i++, entry++) {
            if (!(entry->flags & CASE_ENTRY_FLAG_IN_USE))
                continue;
            switch (entry->conditionId) {
                case CASE_COND_STAND_ON:
                    if (standOn != NULL && !strcmp(hitGetName(standOn), entry->hitObjName))
                        SET_HIT(entry);
                    break;
                case CASE_COND_NOT_STAND_ON:
                    if (standOn != NULL) {
                        if (strcmp(hitGetName(standOn), entry->hitObjName) != 0)
                            SET_HIT(entry);
                    } else {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_UNDER:
                    if (under != NULL && !strcmp(hitGetName(under), entry->hitObjName))
                        SET_HIT(entry);
                    break;
                case CASE_COND_NOT_UNDER:
                    if (under != NULL) {
                        if (strcmp(hitGetName(under), entry->hitObjName) != 0)
                            SET_HIT(entry);
                    } else {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_FRONT:
                    if (front != NULL && !strcmp(hitGetName(front), entry->hitObjName))
                        SET_HIT(entry);
                    break;
                case CASE_COND_JUMP_FROM_A:
                    if (jumpFrom != NULL && mario->airTimer == 1 && fbatNpcTalkCheck() == NULL &&
                        !strcmp(hitGetName(jumpFrom), entry->hitObjName) && (mario->buttonTrg & PAD_BUTTON_A)) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_STAND_ON_A:
                    if (standOn != NULL && fbatNpcTalkCheck() == NULL &&
                        !strcmp(hitGetName(standOn), entry->hitObjName) && pressedA) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_STAND_ON_STICK_DOWN:
                    if (standOn != NULL && !strcmp(hitGetName(standOn), entry->hitObjName) &&
                        (s8)mario->wStickDir2 > 30) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_STAND_ON_STICK_UP:
                    if (standOn != NULL && !strcmp(hitGetName(standOn), entry->hitObjName) &&
                        (keyGetDirTrg(0) & DEMO_STICK_UP)) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_FRONT_A:
                    if (front != NULL && fbatNpcTalkCheck() == NULL &&
                        !strcmp(hitGetName(front), entry->hitObjName) && pressedA) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_PUSH:
                    if (push != NULL && !strcmp(hitGetName(push), entry->hitObjName))
                        SET_HIT(entry);
                    break;
                case CASE_COND_NOT_PUSH:
                    if (push == NULL || strcmp(hitGetName(push), entry->hitObjName) != 0)
                        SET_HIT(entry);
                    break;
                case CASE_COND_PUSH_A:
                    if (push != NULL && fbatNpcTalkCheck() == NULL &&
                        !strcmp(hitGetName(push), entry->hitObjName) && pressedA) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_HAMMER:
                    if (hammer != NULL && !strcmp(hitGetName(hammer), entry->hitObjName))
                        SET_HIT(entry);
                    break;
                case CASE_COND_HAMMER_2:
                    if (hammer != NULL && mario->currMotionId == MARIO_MOTION_HAMMER_2 &&
                        !strcmp(hitGetName(hammer), entry->hitObjName)) {
                        SET_HIT(entry);
                    }
                    break;
                case CASE_COND_BOBBERY:
                    party = partyGetPtr(marioGetPartyId());
                    if (party != NULL && party->currentMemberId == PARTY_MEMBER_BOBBERY) {
                        HitEntry* ph = party->hitobjAction;
                        if (ph != NULL && !strcmp(hitGetName(ph), entry->hitObjName))
                            SET_HIT(entry);
                    }
                    break;
                case CASE_COND_HEAD:
                    if (head != NULL && !strcmp(hitGetName(head), entry->hitObjName))
                        SET_HIT(entry);
                    break;
                case CASE_COND_SW:
                    if (swGet(entry->swFlag))
                        SET_HIT(entry);
                    break;
                case CASE_COND_SW_LOCAL:
                    if (_swGet(entry->swFlag))
                        SET_HIT(entry);
                    break;
                case CASE_COND_ACTIVE_FUNC:
                    if (entry->activeFunc != NULL && entry->activeFunc(entry)) {
                        SET_HIT(entry);
                    }
                    break;
            }
        }
        entry = wp->entries;
        for (i = 0; i < wp->count; i++, entry++) {
            if ((entry->flags & CASE_ENTRY_FLAG_IN_USE) && (entry->flags & CASE_ENTRY_FLAG_TRIGGERED)) {
                EventEntry* evt;
                if (!evtCheckID(entry->evtId))
                    entry->evtId = 0;
                if (entry->evtId == 0) {
                    evt = ((EvtEntryS32PriorityFn)evtEntry)(entry->evtCode, entry->priority, 0x20);
                    evt->caseId = entry->caseId;
                    entry->evtId = evt->eventId;
                    memcpy(evt->lwData, entry->lwData, sizeof(entry->lwData));
                    if (entry->priority == 0x14)
                        npcStopForEvent();
                }
                entry->flags &= ~CASE_ENTRY_FLAG_TRIGGERED;
            }
        }
    }
}

/**
 * Returns the active case watching hit object obj (any hit-object condition, not flag or function cases),
 * or NULL; also NULL in battle. Mario's motions use it to tell whether a surface or wall has an event attached.
 */
CaseEntry* caseCheckHitObj(HitEntry* obj) {
    CaseEntry* entry;
    int i;
    if (gp->inBattle != 0)
        return NULL;
    entry = wp->entries;
    for (i = 0; i < wp->count; i++, entry++) {
        if ((entry->flags & CASE_ENTRY_FLAG_IN_USE) && entry->conditionId != CASE_COND_ACTIVE_FUNC &&
            (u32)(entry->conditionId - CASE_COND_SW) > 1) {
            if (!strcmp(hitGetName(obj), entry->hitObjName))
                return entry;
        }
    }
    return NULL;
}

/**
 * Like caseCheckHitObj, but only for cases fired by Bobbery's blast on obj;
 * Bobbery's field code uses it to see whether a wall reacts to a bomb.
 */
CaseEntry* caseCheckHitObj2(HitEntry* obj) {
    CaseEntry* entry;
    int i;
    if (gp->inBattle != 0)
        return NULL;
    entry = wp->entries;
    for (i = 0; i < wp->count; i++, entry++) {
        if ((entry->flags & CASE_ENTRY_FLAG_IN_USE) && entry->conditionId != CASE_COND_ACTIVE_FUNC &&
            (u32)(entry->conditionId - CASE_COND_SW) > 1 && entry->conditionId == CASE_COND_BOBBERY) {
            if (!strcmp(hitGetName(obj), entry->hitObjName))
                return entry;
        }
    }
    return NULL;
}

/** Returns case caseId's entry, or NULL if that slot is no longer in use. */
CaseEntry* caseIdToPtr(s32 caseId) {
    CaseEntry* entry = &wp->entries[caseId];
    if (!(entry->flags & CASE_ENTRY_FLAG_IN_USE))
        return NULL;
    return entry;
}
