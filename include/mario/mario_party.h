#pragma once

#include <dolphin/types.h>
#include "mario/mario_pouch.h"

void partyJoin(PartyId partnerId);


s32 marioGetPartyId(void);
s32 marioGetExtraPartyId(void);
s32 partyGetTechLv(PartyId partnerId);
s32 partyGetHp(PartyId partnerId);
BOOL partyChkJoin(PartyId partnerId);
void partyLeft(PartyId partnerId);
s32 marioGetParty(void);
void marioPartyKill(void);
BOOL marioPartyGoodbye(void);
s32 marioPartyHello(PartyId id);
s32 marioPartyEntry(PartyId id);
s32 marioUsePartyMain(void);
s32 marioUseParty(void);
