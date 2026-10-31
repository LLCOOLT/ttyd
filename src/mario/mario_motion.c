// Mario's motion table and motion changes (marioChgMot), jump and fall parameters, and the checks that start
// jumps, hammer, spin and the paper transformations from the controls.
#include "dolphin/types.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "mario/mario_motion.h"
#include "eff/eff_kemuri.h"
#include "driver/casedrv.h"
#include <string.h>
#include "mot/mot_jump.h"
#include "party.h"
#include "driver/npcdrv.h"
#include "driver/mobjdrv.h"
#include "koopa_motion.h"
#include "mario/mario_cam.h"
#include "mario/mario_hit.h"
#include "mario/mario_party.h"
#include "mot/mot_damage.h"
#include "mot/mot_dokan.h"
#include "mot/mot_hip.h"
#include "mot/mot_jabara.h"
#include "mot/mot_plane.h"
#include "mot/mot_stay.h"
#include "mot/mot_walk.h"
#include "motion/mot_yoshi.h"
#include "party/party_cloud.h"
#include "party/party_yoshi.h"
#include "peach.h"
#include "system.h"
#include "party/party_vivian.h"
#include "koopa.h"
#include "mot/mot_roll.h"
#include "mario/mario_sbr.h"
#include "mot/mot_ship.h"
#include "mot/mot_hammer.h"
#include "mot/mot_slit.h"
#include "pmario_sound.h"
#include "koopa_hit.h"
#include "version.h"
#include <dolphin/pad.h>

typedef struct MarioMotTblEntry {
    void (*main)(void);
    void (*unused)(void); // NULL in every entry
    void (*post)(void);
} MarioMotTblEntry;

static void mot_talk(void);
static void mot_getItem(void);
static void mot_kaze(void);
#if VERSION <= VERSION_DEMO_US
static void mot_cloud(void);
static void mot_cloud_post(void);
#else
void mot_cloud(void);
#endif
static void mot_bottomless(void);
static void mot_forceReset(void);
static void mot_shadow(void);
static void mot_partyUse(void);
static void mot_dummy(void);

#define PCHK(x) pouchCheckItem(x)

MarioMotTblEntry marioMotTbl[] = {
    {mot_stay, NULL, mot_stay_post},
    {mot_walk, NULL, NULL},
    {mot_dash, NULL, NULL},
    {mot_jump, NULL, NULL},
#if VERSION >= VERSION_US
    {mot_jumpNpc, NULL, N_mot_jumpNpc_post},
#else
    {mot_jumpNpc, NULL, NULL},
#endif
    {mot_jumpSw, NULL, NULL},
    {mot_jumpStand, NULL, NULL},
    {mot_jump, NULL, NULL},
    {mot_jump, NULL, NULL},
    {mot_jumpSmall, NULL, NULL},
    {mot_fall, NULL, mot_fall_post},
    {mot_fall, NULL, NULL},
    {mot_upstairs, NULL, NULL},
    {mot_land, NULL, NULL},
    {mot_talk, NULL, NULL},
    {mot_getItem, NULL, NULL},
    {mot_hip, NULL, mot_hip_post},
    {mot_hip, NULL, mot_hip_post},
    {mot_hammer, NULL, NULL},
    {mot_hammer2, NULL, mot_ham2_post},
    {mot_jabara, NULL, mot_jabara_post},
    {mot_slit, NULL, mot_slit_post},
    {mot_roll, NULL, mot_roll_post},
    {mot_kaze, NULL, NULL},
    {mot_plane, NULL, mot_plane_post},
    {mot_ship, NULL, mot_ship_post},
    {mot_yoshi, NULL, mot_yoshi_post},
#if VERSION <= VERSION_DEMO_US
    {mot_cloud, NULL, mot_cloud_post},
#else
    {mot_cloud, NULL, cloudResetAt},
#endif
    {mot_vivian, NULL, mot_vivian_post},
    {mot_dokan, NULL, NULL},
    {mot_grasp, NULL, NULL},
    {mot_damage, NULL, NULL},
    {mot_damageToge, NULL, NULL},
    {mot_bottomless, NULL, NULL},
    {mot_forceReset, NULL, NULL},
    {mot_shadow, NULL, NULL},
    {mot_partyUse, NULL, NULL},
    {kpa_swim, NULL, NULL},
    {kpa_powup, NULL, NULL},
    {kpa_powdown, NULL, NULL},
    {mot_dummy, NULL, NULL},
};

MarioJumpData marioJumpData = {
    {8.0f, -0.84f, 0.08f, -0.02f},
    {-0.1f, -0.2f, 0.024f, -0.004f},
    32.0f,
    -18.0f,
};

void marioChgMoveMotion(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_PLANE) {
        mario_plane_cancel();
        return;
    }
#if VERSION >= VERSION_JP
    if (mario->currMotionId == MARIO_MOTION_ROLL) {
        allPartyForceRideOn();
        return;
    }
#endif
#if VERSION >= VERSION_US
    if ((u16)(mario->currMotionId - MARIO_MOTION_DAMAGE) <= 1) {
        return;
    }
#endif
    if (mario->currMotionId == MARIO_MOTION_YOSHI) {
        return;
    }
    if (!mario->baseSpeed) {
        marioChgStayMotion();
    }
    if (mario->baseSpeed > mario->baseWalkSpeed) {
        marioChgMot(MARIO_MOTION_DASH);
    } else {
        marioChgMot(MARIO_MOTION_WALK);
    }
}

void marioChgStayMotion(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId != MARIO_MOTION_SHIP && mario->currMotionId != MARIO_MOTION_YOSHI &&
        mario->currMotionId != MARIO_MOTION_SLIT && mario->currMotionId != MARIO_MOTION_ROLL) {
        marioChgMot(MARIO_MOTION_STAY);
    }
}

void marioChgTalkMotion(void) {
    marioChgMot(MARIO_MOTION_TALK);
}

void marioChgGetItemMotion(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_ROLL) {
        marioResetRollSpd();
    } else if (mario->currMotionId == MARIO_MOTION_SLIT) {
        mario->baseSpeed = 0.0f;
    } else if (mario->currMotionId == MARIO_MOTION_SHIP) {
        mario->baseSpeed = 0.0f;
    } else if (mario->currMotionId != MARIO_MOTION_YOSHI) {
        marioChgMot(MARIO_MOTION_GET_ITEM);
    }
}

void marioChgShipMotion(void) {
    marioReInit_ship();
}

void marioChgRollMotion(void) {
    MarioWork* mario = marioGetPtr();
    mario->currSubMotionId = 50;
    mario->currMotionId = MARIO_MOTION_ROLL;
}

void marioChgJumpStandMotion(f32 v) {
    MarioWork* mario = marioGetPtr();
#if VERSION <= VERSION_DEMO_US
    // The demo does not follow the camera up, and in status 0x10 only stores the height.
    if (marioChkSts(0x10)) {
        mario->mot.jump.standHeight = v;
    } else
#else
    camFollowYOn();
    if (marioChkSts(0x10)) {
        mario->mot.jump.standHeight = v;
        effKemuriEntry(0, mario->position.x, mario->position.y, mario->position.z, 0.0f);
        marioChgMot(MARIO_MOTION_JUMP_STAND);
    } else
#endif
        if (mario->currMotionId == MARIO_MOTION_YOSHI) {
        mario->mot.jump.standHeight = v;
        yoshi_jumpStand();
    } else {
        mario->mot.jump.standHeight = v;
        marioChgMot(MARIO_MOTION_JUMP_STAND);
    }
}

void marioChgSmallJumpMotion(void) {
    MarioWork* mario = marioGetPtr();
    mario->trigFlags |= MARIO_TRIG_FLAG_SET_JUMP_PARAMS;
    marioChgMot(MARIO_MOTION_JUMP);
    mario->flags |= MARIO_FLAG_STOP_AIR_MOVEMENT;
    mario->hitobjJumpFrom = mario->hitobjStandOn;
    mario->hitobjStandOn = NULL;
    mario->jumpVelocityY = 6.0f;
    mario->jumpAccelerationY = -0.5f;
    mario->jumpJerkY = 0.0f;
    mario->jumpSnapY = 0.0f;
}

BOOL marioChkItemGetMotion(void) {
    BOOL ret = FALSE;
    MarioWork* mario = marioGetPtr();
    MarioMotion cur = mario->currMotionId;
    if (!cur || cur == MARIO_MOTION_WALK || cur == MARIO_MOTION_DASH ||
        cur == MARIO_MOTION_YOSHI || cur == MARIO_MOTION_ROLL || cur == MARIO_MOTION_SLIT) {
        if (!(mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION)) {
            ret = TRUE;
        }
    } else if (cur == MARIO_MOTION_SHIP) {
        if (marioShipChanging() == 3) {
            ret = TRUE;
        }
    }
    return ret;
}

BOOL marioChkTalkable(void) {
    MarioWork* mario = marioGetPtr();
    BOOL ret = FALSE;
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party != NULL && (s32)(u8)party->currentMemberId == PARTY_MEMBER_YOSHI && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        return FALSE;
    }
    switch (mario->currMotionId) {
        case MARIO_MOTION_STAY:
        case MARIO_MOTION_WALK:
        case MARIO_MOTION_DASH:
            if (!(mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) && marioBgmodeChk() != TRUE && !(mario->dispFlags & MARIO_DISP_FLAG_SLIT)) {
                ret = TRUE;
            }
            break;
    }
    if (vivianGetStatus()) {
        ret = FALSE;
    }
    return ret;
}

void marioBoots(void) {
    MarioWork* mario = marioGetPtr();
    u32 flags = mario->flags;
    if (flags & 0x80000000) {
        return;
    }
    if (flags & 0x100000) {
        return;
    }
    if (mario->characterId == 2) {
        if (mario->jumpPeakAirTime < 6) {
            return;
        }
        if (!kpaHipAttackOk()) {
            return;
        }
        if (!(mario->buttonTrg & PAD_BUTTON_A)) {
            return;
        }
        marioChgMot(MARIO_MOTION_HIP);
        return;
    }
    if (!(flags & 0x80000)) {
        return;
    }
#if VERSION == VERSION_EU
    if (mario->currMotionId == MARIO_MOTION_PLANE) {
        return;
    }
#endif
    if (!marioChkHipAttack()) {
        return;
    }
    marioChgMot(MARIO_MOTION_HIP);
}

void marioMotion(void) {
    MarioWork* mario = marioGetPtr();
    mario->hitobjHammer = NULL;
    do {
        marioMotTbl[mario->currMotionId].main();
    } while (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION);
}

void marioChgMot(MarioMotion id) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_CHG_MOT_DISABLED) {
        return;
    }
    if (mario->prevMotionId == MARIO_MOTION_HIP || mario->prevMotionId == MARIO_MOTION_HIP_2) {
        if (mario->dispFlags & MARIO_DISP_FLAG_BLUR) {
            mario->dispFlags &= ~MARIO_DISP_FLAG_BLUR;
        }
        if (mario->dispFlags & MARIO_DISP_FLAG_FRONT_POSE) {
            mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
        }
    }
    mario->prevMotionId = mario->currMotionId;
    mario->currMotionId = id;
    if (marioMotTbl[mario->prevMotionId].post) {
        marioMotTbl[mario->prevMotionId].post();
    }
    mario->trigFlags |= MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
}

void marioChgMotSub(MarioMotion id, s32 callPost) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_CHG_MOT_DISABLED) {
        return;
    }
    if (mario->prevMotionId == MARIO_MOTION_HIP || mario->prevMotionId == MARIO_MOTION_HIP_2) {
        if (mario->dispFlags & MARIO_DISP_FLAG_BLUR) {
            mario->dispFlags &= ~MARIO_DISP_FLAG_BLUR;
        }
        if (mario->dispFlags & MARIO_DISP_FLAG_FRONT_POSE) {
            mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
        }
    }
    mario->prevMotionId = mario->currMotionId;
    mario->currMotionId = id;
    if (callPost) {
        if (marioMotTbl[mario->prevMotionId].post) {
            marioMotTbl[mario->prevMotionId].post();
        }
    }
#if VERSION >= VERSION_JP
    else if (mario->prevMotionId == MARIO_MOTION_JABARA) {
        if (marioMotTbl[mario->prevMotionId].post) {
            marioMotTbl[mario->prevMotionId].post();
        }
    }
#endif
    mario->trigFlags |= MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
}

void marioChgMot2(MarioMotion id) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_CHG_MOT_DISABLED) {
        return;
    }
    mario->prevMotionId = mario->currMotionId;
    mario->currMotionId = id;
    mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
    if (marioMotTbl[mario->prevMotionId].post) {
        marioMotTbl[mario->prevMotionId].post();
    }
}

void marioClearJumpPara(void) {
    MarioWork* mario = marioGetPtr();
    mario->jumpVelocityY = 0.0f;
    mario->jumpAccelerationY = 0.0f;
    mario->jumpJerkY = 0.0f;
    mario->jumpSnapY = 0.0f;
}

void marioSetJumpPara(void) {
    MarioWork* mario = marioGetPtr();
    f32* jd;
    switch (mario->currMotionId) {
        case MARIO_MOTION_JUMP_SW:
            mario->jumpVelocityY = marioJumpSwData[0];
            mario->jumpAccelerationY = marioJumpSwData[1];
            mario->jumpJerkY = marioJumpSwData[2];
            mario->jumpSnapY = marioJumpSwData[3];
            break;
        case MARIO_MOTION_JUMP:
        case MARIO_MOTION_UPSTAIRS:
        case MARIO_MOTION_JABARA:
        case MARIO_MOTION_PLANE:
        case MARIO_MOTION_SHIP:
            if (mario->trigFlags & MARIO_TRIG_FLAG_SET_JUMP_PARAMS) {
                jd = marioJumpData.jump;
                if (mario->flags & MARIO_FLAG_PRE_BATTLE_PHYSICS) {
                    mario->jumpVelocityY = 0.5f * jd[0];
                    mario->jumpAccelerationY = 0.5f * jd[1];
                    mario->jumpJerkY = 0.5f * jd[2];
                    mario->jumpSnapY = 0.5f * jd[3];
                }
            } else {
                jd = marioJumpData.jump;
                if (!(mario->flags & MARIO_FLAG_PRE_BATTLE_PHYSICS)) {
                    mario->jumpVelocityY = jd[0];
                    mario->jumpAccelerationY = jd[1];
                    mario->jumpJerkY = jd[2];
                    mario->jumpSnapY = jd[3];
                } else {
                    mario->jumpVelocityY = 0.5f * jd[0];
                    mario->jumpAccelerationY = 0.5f * jd[1];
                    mario->jumpJerkY = 0.5f * jd[2];
                    mario->jumpSnapY = 0.5f * jd[3];
                }
                if (1.0f != mario->playerGravity) {
                    mario->jumpVelocityY = 2.0f;
                    mario->jumpAccelerationY = -0.003f;
                    mario->jumpJerkY = 0.029f;
                    mario->jumpSnapY = -0.003f;
                }
            }
            break;
        case MARIO_MOTION_JUMP_NPC:
            mario->jumpVelocityY = 2.0f;
            mario->jumpAccelerationY = -0.04f;
            mario->jumpJerkY = -0.01f;
            mario->jumpSnapY = -0.003f;
            break;
        case MARIO_MOTION_ROLL:
            mario->jumpVelocityY = (jd = marioJumpData.jump)[0];
            mario->jumpAccelerationY = jd[1];
            mario->jumpJerkY = jd[2];
            mario->jumpSnapY = jd[3];
            if (1.0f != mario->playerGravity) {
                mario->jumpVelocityY = 2.7f;
                mario->jumpAccelerationY = -0.002f;
                mario->jumpJerkY = 0.016f;
                mario->jumpSnapY = -0.002f;
            }
            break;
    }
    if (mario->currMotionId != MARIO_MOTION_JUMP_3 && mario->characterId == 2) {
        kpaSetJumpPara();
    }
}

void marioSetFallPara(void) {
    MarioWork* mario = marioGetPtr();
    f32* fall = marioJumpData.fall;
    if (mario->currMotionId == MARIO_MOTION_JUMP_SW) {
        fall = &marioJumpSwData[4];
    }
    mario->jumpVelocityY = fall[0];
    mario->jumpAccelerationY = fall[1];
    mario->jumpJerkY = fall[2];
    mario->jumpSnapY = fall[3];
    if (1.0f != mario->playerGravity) {
        mario->jumpVelocityY = 0.34f;
        mario->jumpAccelerationY = -0.002f;
        mario->jumpJerkY = -0.01f;
        mario->jumpSnapY = 0.0f;
    }
}

f32 marioGetFallSpd(void) {
    MarioWork* mario = marioGetPtr();
    MarioJumpData* jd;
    f32 min;
    mario->jumpJerkY = mario->jumpJerkY + mario->jumpSnapY;
    if (mario->jumpJerkY > 0.0f) {
        mario->jumpJerkY = 0.0f;
    }
    jd = &marioJumpData;
    mario->jumpAccelerationY = mario->jumpAccelerationY + mario->jumpJerkY;
    mario->jumpVelocityY = mario->jumpVelocityY + mario->jumpAccelerationY;
    if (mario->jumpVelocityY <= (min = jd->minFall)) {
        mario->jumpVelocityY = min;
        mario->jumpAccelerationY = 0.0f;
        mario->jumpJerkY = 0.0f;
        mario->jumpSnapY = 0.0f;
    }
    return mario->jumpVelocityY;
}

f32 marioMakeJumpPara(void) {
    MarioWork* mario = marioGetPtr();
    f32 div = (mario->flags & MARIO_FLAG_PRE_BATTLE_PHYSICS) ? 1.7f : 1.0f;
    mario->jumpJerkY = mario->jumpJerkY + mario->jumpSnapY / div;
    mario->jumpAccelerationY = mario->jumpAccelerationY + mario->jumpJerkY / div;
    mario->jumpVelocityY = mario->jumpVelocityY + mario->jumpAccelerationY / div;
    return mario->jumpVelocityY;
}

void marioJump(void) {
    MarioWork* mario = marioGetPtr();
    f32 prev;
    if (getRollEvtFlag()) {
        return;
    }
    switch (mario->currMotionId) {
        case MARIO_MOTION_JUMP_NPC:
            break;
        case MARIO_MOTION_JUMP_SW:
        case MARIO_MOTION_JUMP_STAND:
        case MARIO_MOTION_JUMP_2:
        case MARIO_MOTION_JUMP_3:
            return;
    }
    if ((s32)mario->currSubMotionId < 10) {
        return;
    }
    prev = mario->jumpVelocityY;
    marioMakeJumpPara();
    if (mario->jumpVelocityY > 0.0f && mario->airTimer >= 4 && !(mario->buttonHold & PAD_BUTTON_A)) {
        mario->jumpVelocityY += -0.526f;
    }
    if (mario->jumpVelocityY <= 0.0f) {
        if (prev > 0.0f) {
            mario->jumpPeakAirTime = mario->airTimer;
        }
        marioSetPeakYpos();
        marioSetFallPara();
        marioMakeJumpPara();
        if (!marioChkSts(0x10)) {
            marioChgMot(MARIO_MOTION_FALL);
        } else {
            mario->jumpVelocityY = -0.03f;
            mario->jumpAccelerationY = -0.02f;
            mario->jumpJerkY = -0.02f;
            mario->jumpSnapY = -0.002f;
            mario->flags &= ~MARIO_FLAG_IS_JUMPING;
            mario->flags |= MARIO_FLAG_IS_FALLING;
        }
    }
    mario->position.y += mario->jumpVelocityY;
}

void marioFall(void) {
    MarioWork* mario = marioGetPtr();
    s32 rub;
    f32 spd;
    s32 b;
    s32 a;
    f32 c;
    f32 y;
    void* hit;

    if (!strcmp(gp->currentMapName, "kpa_03") && mario->characterId == 2) {
        mario->hitobjStandOn = NULL;
        kpaClearHitobjRide();
        spd = marioGetFallSpd();
        hit = marioChkLandon(&y, spd);
        if (hit) {
            mario->hitobjStandOn = hit;
            mario->hitobjJumpFrom = NULL;
            mario->position.y = y;
        } else {
            mario->position.y += spd;
        }
        if (mario->hitobjStandOn) {
            marioLandOn();
        }
        return;
    }
    if (!(mario->flags & MARIO_FLAG_FORCED_MOVEMENT) && !marioChkInScreen(mario->screenX, mario->screenY)) {
        mario->flags |= MARIO_FLAG_STOP_AIR_MOVEMENT;
        mario->baseSpeed += 0.1f * -mario->baseSpeed;
    }
    if (getRollEvtFlag()) {
        return;
    }
    if (mario->currMotionId == MARIO_MOTION_HIP || mario->currMotionId == MARIO_MOTION_HIP_2) {
        return;
    }
    if ((!marioKeyOffChk() || !marioCtrlOffChk()) && !(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
        f32 s = mario->baseSpeed;
        s = s + 0.01f * (-0.5f - s);
        if (s < 0.0f) {
            s = 0.0f;
        }
        mario->baseSpeed = s;
    }
    mario->hitobjStandOn = NULL;
    if (mario->characterId == 2) {
        kpaClearHitobjRide();
    }
    if (marioChkSts(0x10) == TRUE) {
        mot_fall_roll();
        return;
    }
#if VERSION >= VERSION_US
    if (!(mario->trigFlags & MARIO_TRIG_FLAG_JABARA_MOVE_CHK) && (mario->trigFlags & MARIO_TRIG_FLAG_JABARA_CHK)) {
        rub = marioGetRub(0x100, &a, &b, &c);
        if (mario->buttonHold & PAD_BUTTON_A) {
            mario->trigFlags |= MARIO_TRIG_FLAG_START_JABARA_SPIN;
        }
    }
#else
    rub = marioGetRub(0x100, &a, &b, &c);
#endif
    spd = marioGetFallSpd();
    hit = marioChkLandon(&y, spd);
    if (hit) {
        mario->hitobjStandOn = hit;
        mario->hitobjJumpFrom = NULL;
        if (hitGetAttr(hit) & 0x200) {
            mario->position.y += spd;
        } else {
            mario->position.y = y;
#if VERSION >= VERSION_US
            if (!(mario->trigFlags & MARIO_TRIG_FLAG_JABARA_MOVE_CHK) && (mario->trigFlags & MARIO_TRIG_FLAG_JABARA_CHK) && marioPriCheckJabara() && a != -1 && rub >= 0) {
#else
            if (marioPriCheckJabara() && a != -1 && rub >= 0) {
#endif
#if VERSION >= VERSION_JP
                camFollowYOn();
#endif
                marioChgMot(MARIO_MOTION_JABARA);
                return;
            }
        }
    } else {
        mario->position.y += spd;
    }
    if (mario->characterId != 2) {
        if (mario->hitobjStandOn) {
            marioLandOn();
        }
    } else if (kpaChkHitobjRide()) {
        marioLandOn();
    }
}

void marioLandOn(void) {
    MarioWork* mario = marioGetPtr();
    MapObjectEntry* mobj;
    Vec pos;
    s32 attr;
    u32 flags;
    s32 sfx;
    void* stand;

    if (!(hitGetAttr(mario->hitobjStandOn) & 0x200)) {
        marioClearJumpPara();
    }
    mario->flags &= ~MARIO_FLAG_STOP_AIR_MOVEMENT;
    mario->flags &= ~MARIO_FLAG_USE_FORCE_DIRECTION;
    mario->airTimer = 0;
    mario->jumpPeakAirTime = 0;
    if (mario->characterId != 2) {
        if (!marioBgmodeChk()) {
            camFollowYOn();
        }
    } else {
        kpaCamFollow();
    }
    stand = mario->hitobjStandOn;
    pos = mario->position;
    if (stand) {
        attr = hitGetAttr(stand);
        if (attr & 0x100) {
            sfx = 0x150;
        } else if (attr & 0x200000) {
            sfx = 0x151;
        } else if (attr & 0x100000) {
            sfx = 0x152;
        } else if (attr & 0x1000) {
            sfx = 0x153;
        } else if (attr & 0x400000) {
            sfx = 0x154;
        } else {
            sfx = 0x14f;
        }
        psndSFXOn_3D((const char*)sfx, &pos);
    }
    if (mario->flags & MARIO_FLAG_TUBE_MODE) {
        mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING);
        mario->hitobjJumpFrom = NULL;
        return;
    }
    mario->mot.jump.dist = __fabsf(distABf(mario->position.x, mario->position.z, mario->lastGroundPos.x, mario->lastGroundPos.z));
    attr = hitGetAttr(mario->hitobjStandOn);
    if (mario->currMotionId != MARIO_MOTION_DAMAGE && (attr & 0x200)) {
        set_damage_root_ypos(mario->position.y);
        marioChgMot(MARIO_MOTION_DAMAGE);
        return;
    }
    if (mario->currMotionId != MARIO_MOTION_DAMAGE_TOGE && (attr & 0x800)) {
        set_damage_root_ypos(mario->position.y);
        marioChgMot(MARIO_MOTION_DAMAGE_TOGE);
        return;
    }
    if (hitGetAttr(mario->hitobjStandOn) & 0x80000000) {
        mobj = mobjHitObjPtrToPtr(mario->hitobjStandOn);
        if (!strcmp(mobj->animName, "MOBJ_RedSwitch")) {
            marioChgMot(MARIO_MOTION_JUMP_SW);
            return;
        }
        if (!strcmp(mobj->animName, "MOBJ_BlueJumpStand")) {
            marioChgJumpStandMotion(100.0f);
            return;
        }
        if (mario->characterId == 2) {
            marioChgMot(MARIO_MOTION_STAY);
            return;
        }
        if (mario->currMotionId != MARIO_MOTION_SLIT) {
            marioChgMot(MARIO_MOTION_STAY);
            return;
        }
        if (mario->flags & MARIO_FLAG_PAPER_MODE) {
#if VERSION <= VERSION_DEMO_US
            marioChgMotSub(MARIO_MOTION_STAY, FALSE); // the demo has no slit re-entry
#else
            marioSlitReenter();
#endif
            return;
        }
        if ((mario->dispFlags & MARIO_DISP_FLAG_SLIT) && !marioChkSlitEnd()) {
            motSlitCancel();
        }
        return;
    }
#if VERSION >= VERSION_US
    if (mario->controlStickSensitivity > 0.0f && !(mario->trigFlags & MARIO_TRIG_FLAG_START_JABARA_SPIN) && !(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
#else
    if (mario->controlStickSensitivity > 0.0f && !(mario->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
#endif
        if (mario->characterId == 2) {
            if (kpaFireAttackCheck()) {
                marioChgMot(MARIO_MOTION_STAY);
            } else {
                marioChgMot(MARIO_MOTION_WALK);
            }
            quake_kpaLandOn();
            return;
        }
#if VERSION <= VERSION_DEMO_US
        marioChgMot(MARIO_MOTION_WALK); // the demo does not stay in the slit after landing
        return;
#else
        if (!(mario->dispFlags & MARIO_DISP_FLAG_SLIT)) {
#if VERSION >= VERSION_US
            if (marioPriCheckJabara()) {
                if (mario->buttonHold & PAD_BUTTON_A) {
                    marioChgMot(MARIO_MOTION_STAY);
                } else {
                    marioChgMot(MARIO_MOTION_WALK);
                }
            } else {
                marioChgMot(MARIO_MOTION_WALK);
            }
#else
            marioChgMot(MARIO_MOTION_WALK);
#endif
            return;
        }
        N_marioSlitSetAfterLand();
        return;
#endif
    }
    flags = mario->flags;
    if (flags & 0x1000000) {
        marioChgRollMotion();
        return;
    }
    if (mario->characterId == 2) {
        marioChgMot(MARIO_MOTION_STAY);
        quake_kpaLandOn();
        return;
    }
    if (mario->currMotionId != MARIO_MOTION_SLIT) {
        if (!(flags & 0x20)) {
            marioChgMot(MARIO_MOTION_STAY);
            return;
        }
        marioChgMot(mario->baseSpeed > mario->baseWalkSpeed ? MARIO_MOTION_DASH : MARIO_MOTION_WALK);
        return;
    }
    if (flags & 0x100000) {
#if VERSION <= VERSION_DEMO_US
        marioChgMotSub(MARIO_MOTION_STAY, FALSE);
#else
        marioSlitReenter();
#endif
        return;
    }
    if ((mario->dispFlags & MARIO_DISP_FLAG_SLIT) && !marioChkSlitEnd()) {
        motSlitCancel();
    }
}

#if VERSION <= VERSION_DEMO_US
// FAKE: unreferenced stand-in (deadstripped by the linker) that only creates the demo's three stray
// .rodata doubles 0.5, 3.0 and 0.0 between the mot_talk and earlier pools; the original function that used
// them is not in the demo DOL. A file-scope const array or <math.h> constants place them at the start of
// the section instead.
static f32 marioDemoHalf(f32 x) {
    if (x < 0.0) {
        return x;
    }
    return 0.5 * x * (3.0 - x);
}
#endif

static void mot_talk(void) {
    MarioWork* mario = marioGetPtr();
    NpcEntry* npc;
    f32 camYaw;
    f32 angle;
    void* fbat;

    if (mario->characterId == 1) {
        peach_talk();
        return;
    }
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
        mario->baseSpeed = 0.0f;
        npc = marioGetTouchNpcPtr();
        if (npc == NULL) {
            marioAdjustMoveDir();
        } else {
            camYaw = camGetPtr(CAMERA_3D)->viewYaw;
            angle = revise360(270.0f - (s32)(10.0f * (angleABf(mario->position.x, mario->position.z,
                                                               ((NpcEntry*)npc)->position.x, ((NpcEntry*)npc)->position.z) -
                                                      camYaw) +
                                             0.5f) /
                                           10.0f);
            if (angle >= 90.0f && angle <= 270.0f) {
                mario->moveDirection = toMovedir(90.0f);
                mario->directionView = mario->moveDirection;
                mario->displayDirectionTarget = 180.0f;
            } else {
                mario->moveDirection = toMovedir(90.0f);
                mario->directionView = mario->moveDirection;
                mario->displayDirectionTarget = 0.0f;
            }
        }
        if (mario->characterId == 2) {
            kpaChgPose("KPA_S_1", "KPA2_S_1");
            return;
        }
        // BUG: fbatGetPointer()->npc is whichever NPC Mario last talked to or battled, from any map. If that
        // NPC slot is unused on the current map, checkPose is not valid and marioChgPose can crash. Known case,
        // all versions: talk to one of about twenty affected NPCs, then enter Petalburg for
        // the first time without talking to another NPC, fighting an enemy, or saving and reloading in between;
        // the first-entry cutscene (Mario waves at the Koopa) then crashes here.
        fbat = fbatGetPointer()->npc;
        if (fbat != NULL) {
            marioChgPose(((NpcEntry*)fbat)->checkPose);
        }
#if VERSION == VERSION_EU
        if (!strcmp(mario->animName, "M_I_3")) {
#else
        if (!strcmp(mario->animName, "M_I_2")) {
#endif
            mario->multiTimer = 60;
            mario->currSubMotionId = 10;
        }
    }
    switch ((s32)mario->currSubMotionId) {
        case 0:
            return;
        case 10:
            if (--mario->multiTimer > 0) {
                break;
            }
            marioChgPose("M_S_1");
            mario->currSubMotionId = 11;
            break;
    }
}

static void mot_getItem(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
        mario->baseSpeed = 0.0f;
        marioAdjustMoveDir();
        marioChgPose("M_I_U");
    }
}

BOOL marioChkJump(void) {
    MarioWork* mario = marioGetPtr();
    CaseEntry* ce;
    if (!(mario->buttonTrg & PAD_BUTTON_A)) {
        return FALSE;
    }
    if (mario->currMotionId == MARIO_MOTION_YOSHI) {
        return FALSE;
    }
    if (mario->hitobjFrontA) {
        if ((hitGetAttr(mario->hitobjFrontA) & 0x80000000) && mobjGetHint(mobjHitObjPtrToPtr(mario->hitobjFrontA)) == 1) {
            return FALSE;
        }
        ce = caseCheckHitObj(mario->hitobjFrontA);
        if (ce && (ce->conditionId == CASE_COND_FRONT_A || ce->conditionId == CASE_COND_JUMP_FROM_A || ce->conditionId == CASE_COND_PUSH_A)) {
            return FALSE;
        }
    }
    if (mario->hitobjFront) {
        if ((hitGetAttr(mario->hitobjFront) & 0x80000000) && mobjGetHint(mobjHitObjPtrToPtr(mario->hitobjFront)) == 1) {
            return FALSE;
        }
        ce = caseCheckHitObj(mario->hitobjFront);
        if (ce && (ce->conditionId == CASE_COND_FRONT_A || ce->conditionId == CASE_COND_JUMP_FROM_A || ce->conditionId == CASE_COND_PUSH_A)) {
            return FALSE;
        }
    }
    if (mario->hitobjStandOn) {
        if ((hitGetAttr(mario->hitobjStandOn) & 0x80000000) && mobjGetHint(mobjHitObjPtrToPtr(mario->hitobjStandOn)) == 1) {
            return FALSE;
        }
        ce = caseCheckHitObj(mario->hitobjStandOn);
        if (ce && ce->conditionId == CASE_COND_STAND_ON_A) {
            return FALSE;
        }
    }
    if (fbatNpcTalkCheck()) {
        return FALSE;
    }
#if VERSION == VERSION_EU
    if (mario->hitobjStandOn && (hitGetAttr(mario->hitobjStandOn) & 0x200)) {
        return FALSE;
    }
#endif
    marioChgMot(MARIO_MOTION_JUMP);
    return TRUE;
}

BOOL marioChkTransform(void) {
    MarioWork* mario = marioGetPtr();
    if (!(mario->buttonTrg & PAD_BUTTON_Y)) {
        return FALSE;
    }
#if VERSION >= VERSION_JP
    if (!(mario->trigFlags & MARIO_TRIG_FLAG_SHIP_PLANE_EVT_ON) && mario->partyUseDelay) {
        return FALSE;
    }
#endif
    if (mario->currMotionId == MARIO_MOTION_YOSHI) {
        return FALSE;
    }
    if (PCHK(5) > 0 && marioChkShipPlace(mario->hitobjStandOn)) {
        marioChgMot(MARIO_MOTION_SHIP);
        return FALSE;
    }
    if (PCHK(4) > 0 && marioChkPlanePlace(mario->hitobjStandOn)) {
        marioChgMot(MARIO_MOTION_PLANE);
        return FALSE;
    }
    return TRUE;
}

BOOL marioChkItemMotion(void) {
    MarioWork* mario = marioGetPtr();
    u32 trig;
    if (mario->flags & MARIO_FLAG_IS_8_BIT) {
        return FALSE;
    }
    if (!marioGetHammerLevel()) {
        return FALSE;
    }
    if (marioChkHammer2()) {
        marioChgMot(MARIO_MOTION_HAMMER_2);
        return TRUE;
    }
    trig = mario->buttonTrg & PAD_BUTTON_B;
    if (!trig) {
        return FALSE;
    }
    if (mario->flags & (MARIO_FLAG_PAPER_MODE | MARIO_FLAG_TUBE_MODE)) {
        return FALSE;
    }
    if (!trig) {
        return FALSE;
    }
    marioChgMot(MARIO_MOTION_HAMMER);
    return TRUE;
}

s32 marioChkRub(void) {
#if VERSION <= VERSION_DEMO_US
    MarioWork* mario = marioGetPtr();
#endif
    return 0;
}

typedef BOOL (*MarioCreviceWallChkByValueFn)(Vec pos);

s32 marioRollChgChk(void) {
    MarioWork* mario = marioGetPtr();
    s32 b;
    s32 a;
    f32 c;
    if (mario->flags & MARIO_FLAG_IS_8_BIT) {
        return 0;
    }
    if (!(mario->buttonHold & PAD_TRIGGER_R)) {
        return 0;
    }
    if (marioGetRub(0x20, &a, &b, &c) != TRUE) {
        return 0;
    }
    if (b < 3) {
        return 0;
    }
    if (!PCHK(3)) {
        return 0;
    }
    // FAKE: the Vec goes by value (the ABI passes a pointer to a copy, which is what the real `const Vec*`
    // receives); copying it into a local first changes the code of this function and of its inlined callers
    if (marioSlitChkWallAround() || ((MarioCreviceWallChkByValueFn)marioCreviceWallChk)(mario->position)) {
        return 0;
    }
    if (mario->buttonHold & PAD_TRIGGER_R) {
        marioChgMot(MARIO_MOTION_ROLL);
        return MARIO_MOTION_ROLL;
    }
    return 0;
}

void marioChgMotJump2(void) {
    MarioWork* mario = marioGetPtr();
#if VERSION <= VERSION_DEMO_US
    if (kpaGetBodyStatus() != 2) {
#else
    if (kpaGetBodyStatus() != 2 && mario->currMotionId != MARIO_MOTION_ROLL) {
#endif
        marioChgMot(MARIO_MOTION_JUMP_NPC);
    }
}

#if VERSION <= VERSION_DEMO_US
// In the demo the Flurrie motion lives here: party_cloud.c has no mot_cloud yet, and the motion's post
// function resets the camera target.
static void mot_cloud(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags &= ~(MARIO_FLAG_HAS_INPUT_JUMP | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_JUMPING);
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
    }
}

static void mot_cloud_post(void) {
    cloudResetAt();
}
#endif

static inline BOOL marioChkBackAngle(f32 a) {
    BOOL ret = FALSE;
    if (a > 90.0f && a < 270.0f) {
        ret = TRUE;
    }
    return ret;
}

static void mot_kaze(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
        mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
        mario->multiTimer = 0;
        mario->currSubMotionId = 0;
        mario->baseSpeed = 0.0f;
        mario->mot.kaze.spinSpeed = 0.0f;
        marioChgPose("M_P_2");
    }
    switch ((s32)mario->currSubMotionId) {
        case 0:
            mario->mot.kaze.spinSpeed += 5.0f;
            if (mario->mot.kaze.spinSpeed > 60.0f) {
                mario->mot.kaze.spinSpeed = 60.0f;
            }
            mario->displayDirection = revise360(mario->displayDirection + mario->mot.kaze.spinSpeed);
            if (mario->buttonHold & PAD_TRIGGER_Z) {
                break;
            }
            mario->displayDirectionTarget = marioChkBackAngle(mario->displayDirection) ? 180.0f : 0.0f;
            mario->currSubMotionId = 100;
            mario->multiTimer = 10;
            break;
        case 100:
            mario->mot.kaze.spinSpeed -= 6.0f;
            if (mario->mot.kaze.spinSpeed < 0.0f) {
                mario->mot.kaze.spinSpeed = 0.0f;
                mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
                marioChgMot(MARIO_MOTION_STAY);
            }
            mario->displayDirection = revise360(mario->displayDirection + mario->mot.kaze.spinSpeed);
            mario->displayDirectionTarget = marioChkBackAngle(mario->displayDirection) ? 180.0f : 0.0f;
            break;
    }
}

static void mot_shadow(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
        mario->dispFlags &= ~MARIO_DISP_FLAG_SLIT;
        mario->multiTimer = 0;
        mario->currSubMotionId = 0;
        marioChgPose("M_S_1");
        mario->rot.x = 90.0f;
        mario->rot.y = 0.0f;
        mario->rot.z = 0.0f;
    }
    switch ((s32)mario->currSubMotionId) {
        case 0:
            if (mario->buttonTrg & PAD_BUTTON_B) {
                mario->rot.x = 0.0f;
                mario->rot.z = 0.0f;
                mario->multiTimer = 0;
                marioChgMot(MARIO_MOTION_STAY);
            }
            break;
    }
}

static void mot_partyUse(void) {
    marioGetPtr();
}

static void mot_dummy(void) {
    marioGetPtr();
}

static void mot_bottomless(void) {
    MarioWork* mario = marioGetPtr();
    Vec pos;
    f32 y;
    f32 sx, sy, sz;
    f32 x;
    f32 step;
    f32 z;
    void* hit;

    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->baseSpeed = 0.0f;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
        if (mario->returnPos.y < -2000.0f) {
            if (!strcmp(gp->currentMapName, "win_03")) {
                x = 250.0f;
                y = 13.0f;
                z = mario->position.z;
            } else if (!strcmp(gp->currentMapName, "win_01")) {
                x = 220.0f;
                y = 1.0f;
                z = mario->position.z;
            } else if (!strcmp(gp->currentMapName, "tik_01")) {
                x = 100.0f;
                y = 120.0f;
                z = mario->position.z;
            }
        } else {
            x = mario->returnPos.x;
            y = mario->returnPos.y;
            z = mario->returnPos.z;
        }
        pos = (Vec){x, 300.0f + y, z};
        step = 10.0f;
        while (TRUE) {
            marioGetScreenPos(pos, &sx, &sy, &sz);
            if (!marioChkInScreen(sx, sy)) {
                break;
            }
            pos.y += step;
        }
        mario->position.y = pos.y;
        mario->mot.bottomless.speed = 8.0f;
        mario->multiTimer = (s16)(distABf(x, z, mario->position.x, mario->position.z) / mario->mot.bottomless.speed);
        mario->mot.bottomless.angle = angleABf(mario->position.x, mario->position.z, x, z);
    }
    switch ((s32)mario->currSubMotionId) {
        case 0:
            movePos(&mario->position.x, &mario->position.z, mario->mot.bottomless.speed, mario->mot.bottomless.angle);
            mario->camTarget.x = mario->position.x;
            mario->camTarget.z = mario->position.z;
            if (--mario->multiTimer > 0) {
                break;
            }
            mario->currSubMotionId = 2;
            mario->flags |= MARIO_FLAG_STOP_AIR_MOVEMENT;
            marioSetFallPara();
            break;
        case 2:
            mario->hitobjStandOn = NULL;
            step = marioGetFallSpd();
            if (step < -10.0f) {
                step = -10.0f;
            }
            hit = marioChkLandon(&y, step);
            if (hit == NULL) {
                mario->position.y += step;
            } else {
                psndSFXOn_3D((const char*)0xb9, &mario->position);
                marioChgPose("M_D_2");
                psndSFXOn_3D((const char*)0x197, &mario->position);
                marioDmgRetQuakeOn();
                mario->hitobjStandOn = hit;
                mario->hitobjJumpFrom = NULL;
                mario->position.y = y;
            }
            if (mario->hitobjStandOn == NULL) {
                break;
            }
        case 10:
            mario->multiTimer = 50;
            mario->currSubMotionId = 11;
        case 11:
            if (--mario->multiTimer > 0) {
                break;
            }
            pouchAddHP(-1);
            if (pouchGetHP() <= 0) {
                mario->currSubMotionId = 13;
                marioUpdateCamPos();
                break;
            }
            marioChgPose("M_U_3");
            mario->multiTimer = 12;
            mario->currSubMotionId = 12;
        case 12:
            if (--mario->multiTimer > 0) {
                break;
            }
            marioChgMot(MARIO_MOTION_STAY);
            marioUpdateCamPos();
            break;
    }
}

static void mot_forceReset(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->currSubMotionId = 0;
    }
    switch ((s32)mario->currSubMotionId) {
        case 0:
            marioSlitForceCancel();
            marioChgMot(MARIO_MOTION_STAY);
            mario->currSubMotionId = 1;
            break;
        case 1:
            marioReset();
            party = partyGetPtr(marioGetPartyId());
            if (party) {
                party->position = mario->position;
            }
            party = partyGetPtr(marioGetExtraPartyId());
            if (party) {
                party->position = mario->position;
            }
            break;
    }
}
