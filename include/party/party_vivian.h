// party_vivian.c: Vivian's field partner functions (init, move, shadow, unhold) and her Mario motion mot_vivian.
#pragma once

#include <dolphin/types.h>
#include "party.h"

s32 vivianGetStatus(void);

void N_marioForceVivianAnime(void);
void mot_vivian(void);
void mot_vivian_post(void);
void vivian_init(PartyEntry* party);
void vivianUnhold(PartyEntry* party);
void vivianShadow(PartyEntry* party);
void vivian_move(PartyEntry* party);
void vivian_use(PartyEntry* party);
