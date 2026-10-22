#include "motion/mot_yoshi.h"
#include "evt/evt_bero.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "party.h"
#include "pmario_sound.h"

void mot_yoshi(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        mario->flags &= ~0xF0000;
        mario->dispFlags |= 4;
        mario->dispFlags |= 0x1000;
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
        mario->baseSpeed = 0.0f;
        mario->hitobjFrontA = 0;
        mario->hitobjFront = 0;
        mario->hitobjStandOn = NULL;
        mario->hitobjPush = NULL;
        mario->hitobjWall = 0;
        mario->hitobjHead = 0;
        mario->hitobjUnder = 0;
    }
}

void mot_yoshi_post(void) {
    PartyEntry* party;
    MarioWork* mario;

    party = partyGetPtr(marioGetPartyId());
    mario = marioGetPtr();
    if (party->yoshiPsndSFXId != -1) {
        psndSFXOff(party->yoshiPsndSFXId);
        party->yoshiPsndSFXId = -1;
    }
    bero_clear_Offset();
    mario->dispFlags &= ~4;
    mario->dispFlags &= ~0x1000;
    mario->dispOfs = (Vec){ 0.0f, 0.0f, 0.0f };
    mario->dispOfs2 = (Vec){ 0.0f, 0.0f, 0.0f };
}
