#pragma once

#include "party.h"
#include "dolphin/mtx.h"

void bomhei_bye(PartyEntry* party);
void bomhei_exit(PartyEntry* party);
void bomhei_use(PartyEntry* party);
void bomhei_use_cancel();
void bomhei_use_post(PartyEntry* party);
void partyGetReturnPos(Vec* out);
