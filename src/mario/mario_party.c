// Mario's side of the partners: which partner is out, calling them (entry/hello/goodbye/kill), the partner
// button, and partner join/leave, HP and level helpers.
#include "mario/mario_party.h"
#include "mario/mario.h"
#include "driver/npcdrv.h"
#include "party.h"
#include "party/party_yoshi.h"
#include "version.h"
#include <dolphin/pad.h>

static inline void marioPartyKillSlot0(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currPartySlotId[0] >= 0) {
        partyKill(mario->currPartySlotId[0]);
        mario->currPartySlotId[0] = -1;
    }
}

static inline void marioPartyKillSlot1(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currPartySlotId[1] >= 0) {
        partyKill(mario->currPartySlotId[1]);
        mario->currPartySlotId[1] = -1;
    }
}

#if VERSION >= VERSION_JP
s32 marioUseParty(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (N_marioChkUseParty()) {
        mario->partyUseDelay = 0;
        mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
        return 0;
    }
    if ((mario->trigFlags & MARIO_TRIG_FLAG_USE_PARTNER) && marioKeyOffChk()) {
        mario->partyUseDelay = 0;
        mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
        return 0;
    }
    party = partyGetPtr(marioGetPartyId());
    if (party != NULL && party->runMode == 3) {
        return 0;
    }
    if (mario->currPartySlotId[0] < 0) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
        return 0;
    }
    if (mario->flags & MARIO_FLAG_IS_8_BIT) {
        return 0;
    }
    if (N_fbatPreventMarioEventChk()) {
        mario->partyUseDelay = 0;
        mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
        return 0;
    }
    if ((mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING)) || mario->airTimer != 0) {
        mario->partyUseDelay = 0;
        mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
        return 0;
    }
    if (mario->currMotionId != MARIO_MOTION_STAY && mario->currMotionId != MARIO_MOTION_WALK && mario->currMotionId != MARIO_MOTION_DASH) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
        return 0;
    }
    if ((mario->dispFlags & MARIO_DISP_FLAG_SLIT) || party->slitOn == 1) {
        return 0;
    }
    if (partyGetPtr(marioGetPartyId())->flags & 0x100) {
        return 0;
    }
    party = partyGetPtr(marioGetPartyId());
    if (party == NULL) {
        return 0;
    }
    // 1 = PARTY_MEMBER_GOOMBELLA, 4 = PARTY_MEMBER_YOSHI: the char-sized enum constants change the s8 compares
    if (party->currentMemberId == 1 && !(party->flags & PARTY_FLAG_IS_GROUNDED)) {
        return 0;
    }
    if (party->currentMemberId == 4 && yoshiGetStatus()) {
        return 0;
    }
    if (!(mario->trigFlags & MARIO_TRIG_FLAG_USE_PARTNER) && (mario->buttonTrg & PAD_BUTTON_X)) {
        mario->trigFlags |= MARIO_TRIG_FLAG_USE_PARTNER;
        mario->partyUseDelay = 5;
    }
    return 0;
}

s32 marioUsePartyMain(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->trigFlags & MARIO_TRIG_FLAG_USE_PARTNER) {
        if (marioKeyOffChk()) {
            mario->partyUseDelay = 0;
            mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
            return 0;
        }
        if (--mario->partyUseDelay <= 0) {
            mario->partyUseDelay = 0;
            mario->trigFlags &= ~MARIO_TRIG_FLAG_USE_PARTNER;
            return partyDoWork();
        }
    }
    return 0;
}
#endif

s32 marioPartyEntry(PartyId id) {
    MarioWork* mario = marioGetPtr();
    s32 ret;

    if (id < 8) {
        if (!partyChkJoin(id)) {
            return -1;
        }
        if (mario->currPartySlotId[0] >= 0) {
            marioPartyKillSlot0();
        }
        ret = partyEntry(id);
        if (ret >= 0) {
            mario->currPartySlotId[0] = ret;
            partyHello(partyGetPtr(ret));
        }
    } else {
        if (mario->currPartySlotId[1] >= 0) {
            marioPartyKillSlot1();
        }
        ret = partyEntry2(id);
        if (ret >= 0) {
            mario->currPartySlotId[1] = ret;
            partyHello(partyGetPtr(ret));
        }
    }
    return ret;
}

s32 marioPartyHello(PartyId id) {
    s32 ret = -1;
    MarioWork* mario = marioGetPtr();

    if (id < 8) {
        if (!partyChkJoin(id)) {
            return -1;
        }
        if (mario->currPartySlotId[0] < 0) {
            ret = partyEntryHello(id);
            if (ret >= 0) {
                mario->currPartySlotId[0] = ret;
            }
        }
    } else {
        ret = partyEntry2Hello(id);
        if (ret >= 0) {
            mario->currPartySlotId[1] = ret;
        }
    }
    return ret;
}

BOOL marioPartyGoodbye(void) {
    BOOL ret = FALSE;
    s8 slot = marioGetPtr()->currPartySlotId[0];
    if (slot >= 0) {
        partyGoodbye(slot);
        ret = TRUE;
    }
    return ret;
}

void marioPartyKill(void) {
    marioPartyKillSlot0();
    marioPartyKillSlot1();
}

#if VERSION <= VERSION_DEMO_US
// The demo has one function for the partner button: the request flag is trigFlags 0x100000, and the wait for
// partyDoWork runs here (retail splits it out into marioUsePartyMain).
s32 marioUseParty(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if ((mario->trigFlags & MARIO_TRIG_FLAG_JABARA_CHK) && marioKeyOffChk()) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_JABARA_CHK;
        return 0;
    }
    if (mario->currPartySlotId[0] < 0) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_JABARA_CHK;
        return 0;
    }
    if (mario->flags & MARIO_FLAG_IS_8_BIT) {
        return 0;
    }
    if ((mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING)) || mario->airTimer != 0) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_JABARA_CHK;
        return 0;
    }
    if (mario->currMotionId != MARIO_MOTION_STAY && mario->currMotionId != MARIO_MOTION_WALK && mario->currMotionId != MARIO_MOTION_DASH) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_JABARA_CHK;
        return 0;
    }
    if (mario->dispFlags & MARIO_DISP_FLAG_SLIT) {
        return 0;
    }
    if (partyGetPtr(marioGetPartyId())->flags & 0x100) {
        return 0;
    }
    party = partyGetPtr(marioGetPartyId());
    if (party == NULL) {
        return 0;
    }
    // 1 = PARTY_MEMBER_GOOMBELLA, 4 = PARTY_MEMBER_YOSHI: the char-sized enum constants change the s8 compares
    if (party->currentMemberId == 1 && !(party->flags & PARTY_FLAG_IS_GROUNDED)) {
        return 0;
    }
    if (party->currentMemberId == 4 && yoshiGetStatus()) {
        return 0;
    }
    if (!(mario->trigFlags & MARIO_TRIG_FLAG_JABARA_CHK)) {
        if (mario->buttonTrg & PAD_BUTTON_X) {
            mario->trigFlags |= MARIO_TRIG_FLAG_JABARA_CHK;
            mario->partyUseDelay = 5;
        }
    } else if (--mario->partyUseDelay <= 0) {
        mario->partyUseDelay = 0;
        mario->trigFlags &= ~MARIO_TRIG_FLAG_JABARA_CHK;
        return partyDoWork();
    }
    return 0;
}
#endif

s32 marioGetParty(void) {
    s32 id;

    id = marioGetPartyId();
    if (id >= 0) {
        return partyGetPtr(id)->currentMemberId;
    } else {
        return 0;
    }
}

s32 marioGetPartyId(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    s32 partyId;

    partyId = mario->currPartySlotId[0];
    if (partyId >= 0) {
        party = partyGetPtr(partyId);
        if ((party != NULL) && !(party->flags & PARTY_FLAG_IS_PARTNER)) {
            return partyId;
        }
    }
    partyId = mario->currPartySlotId[1];
    if (partyId >= 0) {
        party = partyGetPtr(partyId);
        if ((party != NULL) && !(party->flags & PARTY_FLAG_IS_PARTNER)) {
            return partyId;
        }
    }
    return -1;
}

s32 marioGetExtraPartyId(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    s32 partyId;

    partyId = mario->currPartySlotId[0];
    if (partyId >= 0) {
        party = partyGetPtr(partyId);
        if ((party != NULL) && (party->flags & PARTY_FLAG_IS_PARTNER)) {
            return partyId;
        }
    }

    partyId = mario->currPartySlotId[1];
    if (partyId >= 0) {
        party = partyGetPtr(partyId);
        if ((party != NULL) && (party->flags & PARTY_FLAG_IS_PARTNER)) {
            return partyId;
        }
    }
    return -1;
}

void partyJoin(PartyId partnerId) {
    if (partnerId < 8) {
        pouchGetPtr()->partyData[partnerId].flags |= 1; // obtained
    }
}

void partyLeft(PartyId partnerId) {
    if (partnerId < 8) {
        pouchGetPtr()->partyData[partnerId].flags &= ~1;
    }
}

BOOL partyChkJoin(PartyId partnerId) {
    BOOL ret = FALSE;
    if (partnerId < 8) {
        u32 joined = pouchGetPtr()->partyData[partnerId].flags & 1;
        ret = joined;
    }
    return ret;
}

s32 partyGetHp(PartyId partnerId) {
    s32 ret = 0;
    if (partnerId < 8) {
        ret = pouchGetPtr()->partyData[partnerId].currentHP;
    }
    return ret;
}

s32 partyGetTechLv(PartyId partnerId) {
    s32 ret = 0;
    if (partnerId < 8) {
        ret = pouchGetPtr()->partyData[partnerId].techLevel;
    }
    return ret;
}
