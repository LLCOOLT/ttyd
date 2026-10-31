// Mario's walk and run motion.
#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "pmario_sound.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "driver/casedrv.h"
#include "mot/mot_slit.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "koopa_motion.h"
#include "peach.h"
#include "mario/mario_pouch.h"
#include "version.h"

void marioWalkDashSe(HitEntry* hitObj, u32 interval) {
    s32 hitAttr;
    MarioWork* mario;

    mario = marioGetPtr();
    hitAttr = hitGetAttr(hitObj);
    if ((mario->multiTimer % interval) == 0) {
        if (hitAttr & 0x100) {
            psndSFXOn_3D((char*)0x143, &mario->position);
            return;
        }
        if (hitAttr & 0x200000) {
            psndSFXOn_3D((char*)0x145, &mario->position);
            return;
        }
        if (hitAttr & 0x100000) {
            psndSFXOn_3D((char*)0x147, &mario->position);
            return;
        }
        if (hitAttr & 0x1000) {
            if (strncmp(gp->currentMapName, "mri", 3) != 0) {
                psndSFXOn_3D((char*)0x149, &mario->position);
                return;
            }
            psndSFXOn_3D((char*)0x143, &mario->position);
            return;
        }
        if (hitAttr & 0x400000) {
            psndSFXOn_3D((char*)0x14B, &mario->position);
            return;
        }
        psndSFXOn_3D((char*)0x141, &mario->position);
        return;
    }
    if ((mario->multiTimer % (interval >> 1U)) == 0) {
        if (hitAttr & 0x100) {
            psndSFXOn_3D((char*)0x142, &mario->position);
            return;
        }
        if (hitAttr & 0x200000) {
            psndSFXOn_3D((char*)0x144, &mario->position);
            return;
        }
        if (hitAttr & 0x100000) {
            psndSFXOn_3D((char*)0x146, &mario->position);
            return;
        }
        if (hitAttr & 0x1000) {
            if (strncmp(gp->currentMapName, "mri", 3) != 0) {
                psndSFXOn_3D((char*)0x148, &mario->position);
                return;
            }
            psndSFXOn_3D((char*)0x142, &mario->position);
            return;
        }
        if (hitAttr & 0x400000) {
            psndSFXOn_3D((char*)0x14A, &mario->position);
            return;
        }
        psndSFXOn_3D((char*)0x140, &mario->position);
    }
}

f32 marioGetWalkSpd(void) {
    f32 walkSpeed;
    s8 stickDir2;
    s8 stickDir1;
    MarioWork* mario;

    mario = marioGetPtr();
    walkSpeed = mario->baseWalkSpeed;
    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        stickDir1 = mario->wStickDir1;
        stickDir2 = mario->wStickDir2;
        if ((stickDir1 * stickDir1) + (stickDir2 * stickDir2) <= 0xBD1) {
            walkSpeed *= 0.5f;
        }
    } else if (marioBgmodeChk() == TRUE) {
        walkSpeed *= 0.5f;
    }

    walkSpeed *= mario->playerGravity;
    return walkSpeed;
}

f32 marioGetDashSpd(void) {
    MarioWork* mario;
    f32 dashSpeed;
    s8 stickDir2;
    s8 stickDir1;

    mario = marioGetPtr();
    dashSpeed = mario->baseDashSpeed;
    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        stickDir1 = mario->wStickDir1;
        stickDir2 = mario->wStickDir2;
        dashSpeed = mario->baseWalkSpeed;

        if ((stickDir1 * stickDir1) + (stickDir2 * stickDir2) <= 0xBD1) {
            dashSpeed *= 0.5f;
        }
    } else if (marioBgmodeChk() == TRUE) {
        dashSpeed *= 0.5f;
    }

    dashSpeed *= mario->playerGravity;
    return dashSpeed;
}

void mot_walk(void) {
    f32 walkSpeed;
    s32 trigFlags;
    s32 flags;
    BOOL pushCaseActive;
    s32 seInterval;
    s8 characterId;
    s8 stickDir2;
    s8 stickDir1;
    MarioWork* mario;
    CaseEntry* caseEntry;

    mario = marioGetPtr();
    characterId = mario->characterId;
    if (characterId == 2) {
        kpa_walk();
        return;
    }
    if (characterId == 1) {
        peach_walk();
        return;
    }
    if (mario->flags & MARIO_FLAG_IS_PUSHING) {
        if (mario->hitobjPush == NULL) {
            pushCaseActive = FALSE;
        } else {
            caseEntry = caseCheckHitObj(mario->hitobjPush);
            if (caseEntry != NULL && caseEntry->conditionId == CASE_COND_PUSH) {
                pushCaseActive = TRUE;
            } else {
                pushCaseActive = FALSE;
            }
        }
        if (!pushCaseActive) {
            mario->flags = mario->flags & ~MARIO_FLAG_IS_PUSHING;
            if (marioChkPushAnime() && !marioBgmodeChk()) {
                marioChgPose("M_W_1");
            }
        }
    }
    trigFlags = mario->trigFlags;
    if (trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags = trigFlags & ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags = mario->flags & ~(MARIO_FLAG_HAS_INPUT_JUMP | MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING |
                                        MARIO_FLAG_IS_STEPPING);
        marioResetCamFollowRate();
        if (mario->flags & MARIO_FLAG_PAPER_MODE) {
            motSlitContinue();
        }
        if (mario->forceMoveTimer == 0) {
            mario->baseSpeed = marioGetWalkSpd();
        }
        flags = mario->flags;
        if (flags & MARIO_FLAG_IS_CARRYING_BOBBERY) {
            marioChgPose("M_W_7");
        } else if (flags & MARIO_FLAG_IS_PUSHING) {
            if (!marioChkPushAnime()) {
                marioChgPose("M_O_1");
            }
        } else if (!marioBgmodeChk()) {
            marioChgPose("M_W_1");
        }
#if VERSION == VERSION_DEMO
        mario->currSubMotionId = 0;
#else
        if (!(mario->dispFlags & (MARIO_DISP_FLAG_HIDDEN << 24))) {
            mario->currSubMotionId = 0;
        }
#endif
        mario->multiTimer = 0;
    }
#if VERSION == VERSION_DEMO
    if (strcmp(mario->animName, "M_I_Y") == 0 || mario->wMotionTimer > 0xA) {
#else
    if (!(mario->flags & MARIO_FLAG_IS_CARRYING_BOBBERY) &&
        (strcmp(mario->animName, "M_I_Y") == 0 || mario->wMotionTimer > 0xA)) {
#endif
        marioChgMot(MARIO_MOTION_STAY);
        return;
    }
    if (mario->flags & MARIO_FLAG_IS_CARRYING_BOBBERY) {
        mario->directionView = mario->controlStickAngle;
        if (!mario->controlStickSensitivity) {
            marioChgMot(MARIO_MOTION_STAY);
        }
    } else {
        if (marioSlitAbilityChk() && marioSlitButton() == 1) {
            marioChgMot(MARIO_MOTION_SLIT);
            return;
        }
        if (!marioChkItemMotion()) {
            marioChkJump();
            marioChkTransform();
            if (pouchEquipCheckBadge(ITEM_SLOW_GO) == 0) {
                stickDir1 = mario->wStickDir1;
                stickDir2 = mario->wStickDir2;
                if ((stickDir1 * stickDir1) + (stickDir2 * stickDir2) > 0xBD1) {
                    marioChgMot(MARIO_MOTION_DASH);
                    return;
                }
            }
            mario->directionView = mario->controlStickAngle;
            if (mario->hitobjStandOn != 0) {
                // Redundant, but doesn't match otherwise
                if (mario->playerGravity == 1.0f) {
                    seInterval = 0x28;
                } else {
                    seInterval = 0x28;
                }
                marioWalkDashSe(mario->hitobjStandOn, seInterval);
            }
            mario->multiTimer = mario->multiTimer + 1;
            if (mario->flags & MARIO_FLAG_IS_PUSHING && !marioChkPushAnime()) {
                marioChgPose("M_O_1");
            }
            if (!mario->controlStickSensitivity) {
                marioChgMot(MARIO_MOTION_STAY);
            }
        }
    }
}

void mot_dash(void) {
    f32 dashSpeed;
    u32 trigFlags;
    BOOL pushCaseActive;
    s32 seInterval;
    s8 characterId;
    s8 stickDir2;
    s8 stickDir1;
    MarioWork* mario;
    CaseEntry* caseEntry;

    mario = marioGetPtr();
    characterId = mario->characterId;
    if (characterId == 2) {
        kpa_dash();
        return;
    }
    if (characterId == 1) {
        peach_dash();
        return;
    }
    if (mario->hitobjPush == NULL) {
        pushCaseActive = FALSE;
    } else {
        caseEntry = caseCheckHitObj(mario->hitobjPush);
        if (caseEntry != NULL && caseEntry->conditionId == CASE_COND_PUSH) {
            pushCaseActive = TRUE;
        } else {
            pushCaseActive = FALSE;
        }
    }
    if (!pushCaseActive && mario->hitobjPush == NULL) {
        mario->flags = mario->flags & ~MARIO_FLAG_IS_PUSHING;
        if (marioChkPushAnime() && !marioBgmodeChk()) {
            marioChgPose("M_R_1");
        }
    }
    trigFlags = mario->trigFlags;
    if (trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags = trigFlags & ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags = mario->flags & ~(MARIO_FLAG_HAS_INPUT_JUMP | MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING |
                                        MARIO_FLAG_IS_STEPPING);
        marioResetCamFollowRate();
        if (mario->flags & MARIO_FLAG_PAPER_MODE) {
            motSlitContinue();
        }
        if (mario->playerGravity == 1.0f) {
            if (mario->flags & MARIO_FLAG_IS_PUSHING) {
                if (!marioChkPushAnime()) {
                    marioChgPose("M_O_1");
                }
            } else if (!marioBgmodeChk()) {
                marioChgPose("M_R_1");
            }
        } else if (mario->flags & MARIO_FLAG_IS_PUSHING) {
            if (!marioChkPushAnime()) {
                marioChgPose("M_O_1");
            }
        } else {
            marioChgPose("M_W_1");
        }
        if (mario->forceMoveTimer == 0) {
            mario->baseSpeed = marioGetDashSpd();
        }
    }
#if VERSION == VERSION_DEMO
    if (strcmp(mario->animName, "M_I_Y") == 0 || mario->wMotionTimer > 0xA) {
#else
    if (!(mario->flags & MARIO_FLAG_IS_CARRYING_BOBBERY) &&
        (strcmp(mario->animName, "M_I_Y") == 0 || mario->wMotionTimer > 0xA)) {
#endif
        marioChgMot(MARIO_MOTION_STAY);
        return;
    }
    if (mario->flags & MARIO_FLAG_IS_CARRYING_BOBBERY) {
        marioChgMot(MARIO_MOTION_WALK);
        return;
    }
    if (marioSlitAbilityChk() && marioSlitButton() == 1) {
        marioChgMot(MARIO_MOTION_SLIT);
        return;
    }
    if (!marioChkItemMotion()) {
        marioChkJump();
        marioChkTransform();
        if (mario->hitobjStandOn != NULL) {
            if (mario->playerGravity == 1.0f) {
                seInterval = 0x14;
            } else {
                seInterval = 0x28;
            }
            marioWalkDashSe(mario->hitobjStandOn, seInterval);
        }
        mario->multiTimer = mario->multiTimer + 1;
        if (!(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
            stickDir1 = mario->wStickDir1;
            stickDir2 = mario->wStickDir2;
#if VERSION >= VERSION_US
            if ((stickDir1 * stickDir1) + (stickDir2 * stickDir2) <= 0xBD1 || pouchEquipCheckBadge(ITEM_SLOW_GO)) {
#else
            if ((stickDir1 * stickDir1) + (stickDir2 * stickDir2) <= 0xBD1) {
#endif
                marioChgMot(MARIO_MOTION_WALK);
                return;
            }
            mario->directionView = mario->controlStickAngle;
            if ((mario->flags & MARIO_FLAG_IS_PUSHING) && !marioChkPushAnime()) {
                marioChgPose("M_O_1");
            }
            if (!mario->controlStickSensitivity) {
                marioChgMot(MARIO_MOTION_STAY);
            }
        }
    }
}
