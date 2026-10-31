// The speech/action balloon over Mario's head ("!" and "?"): which NPC, item box or object it points at.
#include "mario/mario.h"
#include "driver/casedrv.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "driver/npcdrv.h"
#include <string.h>
#include "mario/mario_hit.h"
#include "eff/eff_mario_balloon.h"

/** Clears the balloon effect pointer; run from marioInit and marioReInit (the "Baloon" spelling is the original's). */
void marioBaloonInit(void) {
    marioGetPtr()->balloonEffect = NULL;
}

/**
 * Spawns the balloon effect of the given type over Mario's head unless one is already showing.
 * Called each frame by marioBalloonMain and by the evt_mario balloon script commands (type 0 "!", type 1 the
 * "..." balloon).
 */
void marioBalloonOn(s32 type) {
    MarioWork* mario = marioGetPtr();

    if (!(mario->dispFlags & MARIO_DISP_FLAG_BALLOON_ON)) {
        mario->dispFlags |= MARIO_DISP_FLAG_BALLOON_ON;
        mario->balloonEffect = effMarioBalloonEntry(type, NULL);
    }
}

/**
 * Like marioBalloonOn, but anchors the balloon effect to the NPC Mario can talk to and remembers it in
 * mario->balloonNpc.
 */
static inline void marioBalloonOnNpc(s32 type, NpcEntry* npc) {
    MarioWork* mario = marioGetPtr();

    if (!(mario->dispFlags & MARIO_DISP_FLAG_BALLOON_ON)) {
        mario->dispFlags |= MARIO_DISP_FLAG_BALLOON_ON;
        mario->balloonEffect = effMarioBalloonEntry(type, npc);
        mario->balloonNpc = npc;
    }
}

/** Removes the balloon over Mario's head, if any, and forgets the NPC it pointed at. */
void marioBalloonOff(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->dispFlags & MARIO_DISP_FLAG_BALLOON_ON) {
        mario->dispFlags &= ~MARIO_DISP_FLAG_BALLOON_ON;
        effDelete(mario->balloonEffect);
        mario->balloonEffect = NULL;
        mario->balloonNpc = NULL;
    }
}

/**
 * TRUE when the surface in front of Mario (hitobjFrontA) is something A can act on:
 * a map object whose hint is 1 or a case-event hit flagged for the balloon with the "front + A" condition.
 * Hits with attribute 0x800000 never count.
 */
static inline BOOL chkBalloonStand(HitEntry* hit) {
    BOOL ret = FALSE;
    CaseEntry* entry;
    s32 attr;

    if (hit != NULL) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_PARTY_PASS) {
            ret = FALSE;
        } else if (attr & HIT_ATTR_MOBJ) {
            if (mobjGetHint(mobjHitObjPtrToPtr(hit)) == 1) {
                ret = TRUE;
            }
        } else {
            entry = caseCheckHitObj(hit);
            if (entry != NULL && (entry->flags & CASE_ENTRY_FLAG_BALLOON) && entry->conditionId == CASE_COND_FRONT_A) {
                ret = TRUE;
            }
        }
    }
    return ret;
}

/**
 * TRUE when the hit directly in front of Mario is a hinted map object or a balloon case event triggered by A
 * while facing or pushing it. Hits Mario passes through (marioChkBero) never count.
 */
static inline BOOL chkBalloonJump(HitEntry* hit) {
    BOOL ret = FALSE;
    CaseEntry* entry;

    if (hit != NULL) {
        if (hitGetAttr(hit) & HIT_ATTR_MOBJ) {
            if (mobjGetHint(mobjHitObjPtrToPtr(hit)) == 1) {
                ret = TRUE;
            }
        } else {
            entry = caseCheckHitObj(hit);
            if (entry != NULL) {
                if (entry->flags & CASE_ENTRY_FLAG_BALLOON) {
                    if (entry->conditionId == CASE_COND_FRONT_A || entry->conditionId == CASE_COND_PUSH_A) {
                        ret = TRUE;
                    }
                }
            } else {
                ret = FALSE;
            }
        }
        if (marioChkBero(hit)) {
            ret = FALSE;
        }
    }
    return ret;
}

/**
 * TRUE when the floor Mario stands on is a hinted map object or a balloon case event triggered by A
 * while pushing or standing on it. Attribute 0x800000 hits and pass-through hits (marioChkBero) never count.
 */
static inline BOOL chkBalloonPush(HitEntry* hit) {
    BOOL ret = FALSE;
    CaseEntry* entry;
    s32 attr;

    if (hit != NULL) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_PARTY_PASS) {
            ret = FALSE;
        } else {
            if (attr & HIT_ATTR_MOBJ) {
                if (mobjGetHint(mobjHitObjPtrToPtr(hit)) == 1) {
                    ret = TRUE;
                }
            } else {
                entry = caseCheckHitObj(hit);
                if (entry != NULL) {
                    if (entry->flags & CASE_ENTRY_FLAG_BALLOON) {
                        if (entry->conditionId == CASE_COND_PUSH_A || entry->conditionId == CASE_COND_STAND_ON_A) {
                            ret = TRUE;
                        }
                    }
                } else {
                    ret = FALSE;
                }
            }
            if (marioChkBero(hit)) {
                ret = FALSE;
            }
        }
    }
    return ret;
}

/**
 * Checks whether the hit is a treasure chest (MOBJ_TreasureBox or MOBJ_BigTreasureBox):
 * -1 if it is not one, 1 if it is still closed, 0 once opened.
 * marioBalloonMain uses it so the "!" shows only over unopened chests.
 */
static inline s32 chkItemBox(HitEntry* hit) {
    MapObjectEntry* mobj;
    s32 ret = -1;

    marioGetPtr();
    if (!(hitGetAttr(hit) & HIT_ATTR_MOBJ)) {
        ret = -1;
    } else {
        mobj = mobjHitObjPtrToPtr(hit);
        if (strcmp(mobj->animName, "MOBJ_TreasureBox") == 0 ||
            strcmp(mobj->animName, "MOBJ_BigTreasureBox") == 0) {
            ret = 1;
            if (mobjCheckItemboxOpen(mobj) != 1) {
                ret = 0;
            }
        }
    }
    return ret;
}

/**
 * Per-frame update of the "!" / talk balloon over Mario,
 * run from marioMain's motion branches and Bowser's main loop (koopa.c).
 * Shows it when A would do something (case events, hinted objects, unopened chests) or an NPC can be talked to,
 * and hides it while airborne, in a paper form, slit sideways, not standing, walking or dashing,
 * or without control. Skipped entirely while a script holds the balloon (MARIO_DISP_FLAG_BALLOON_EVT).
 */
void marioBalloonMain(void) {
    MarioWork* mario;
    NpcEntry* npc;
    s32 type;
    BOOL show;

    mario = marioGetPtr();
    if (mario->dispFlags & MARIO_DISP_FLAG_BALLOON_EVT) {
        return;
    }
    show = FALSE;
    switch (!marioChkKey()) {
        case 0:
            break;
        default:
            marioBalloonOff();
            return;
    }

    if (chkBalloonStand(mario->hitobjFrontA)) {
        type = 0;
        show = TRUE;
    }
    if (chkBalloonJump(mario->hitobjFront)) {
        type = 0;
        show = TRUE;
    }
    if (chkBalloonPush(mario->hitobjStandOn)) {
        type = 0;
        show = TRUE;
    }
    if (mario->hitobjFront != NULL) {
        if (chkItemBox(mario->hitobjFront) >= 0) {
            show = chkItemBox(mario->hitobjFront);
        }
    }

    npc = fbatNpcTalkCheck();
    if (npc != NULL) {
        if (!(npc->flags & 0x80000000)) {
            type = npc->balloonType;
            show = TRUE;
        }
        if (mario->balloonNpc != npc) {
            marioBalloonOff();
        }
    }

    if (mario->airTimer != 0 || (mario->flags & MARIO_FLAG_PAPER_MODE) || (mario->dispFlags & MARIO_DISP_FLAG_SLIT) ||
        (mario->currMotionId != MARIO_MOTION_STAY && (u16)(mario->currMotionId - 1) > 1)) {
        show = FALSE;
    }

    if (show) {
        if (type == 1) {
            marioBalloonOnNpc(type, npc);
        } else {
            marioBalloonOn(type);
            if (npc != NULL) {
                mario->balloonNpc = npc;
            }
        }
    } else {
        marioBalloonOff();
    }
}

/**
 * TRUE when the hit is something the A button acts on:
 * a map object with hint 1 or a balloon-flagged case event with any of the A conditions (front, jump from, push,
 * stand on). Pass-through hits never count. Used by Bowser's collision code (koopa_hit.c).
 */
BOOL chkBalloon(HitEntry* hit) {
    BOOL ret = FALSE;
    CaseEntry* entry;

    if (hit != NULL) {
        if (hitGetAttr(hit) & HIT_ATTR_MOBJ) {
            if (mobjGetHint(mobjHitObjPtrToPtr(hit)) == 1) {
                ret = TRUE;
            }
        } else {
            entry = caseCheckHitObj(hit);
            if (entry != NULL) {
                if (entry->flags & CASE_ENTRY_FLAG_BALLOON) {
                    if (entry->conditionId == CASE_COND_FRONT_A || entry->conditionId == CASE_COND_JUMP_FROM_A || entry->conditionId == CASE_COND_PUSH_A || entry->conditionId == CASE_COND_STAND_ON_A) {
                        ret = TRUE;
                    }
                }
            } else {
                ret = FALSE;
            }
        }
        if (marioChkBero(hit)) {
            ret = FALSE;
        }
    }
    return ret;
}
