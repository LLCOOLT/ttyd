#pragma once

#include "party.h"
#include "dolphin/types.h"

void partyChgMot(PartyEntry* party, s32 mot);
void partyClearFootmark(void);
void partyClearJumpPara(PartyEntry* party);
void partyGetMoveDirSpd(PartyEntry* party, f32* dir, f32* spd);
void partyMove(PartyEntry* party);
void partyMoveNoHosei(PartyEntry* party);
void partyMoveWalk(PartyEntry* party);
void partyRecordFootmark(PartyEntry* party);
void partyWalkMain(PartyEntry* party);
void party_move_mode_behind_mario(PartyEntry* party);
void party_move_mode_beside_mario(PartyEntry* party);
void party_move_mode_stay(PartyEntry* party);
void party_move_mode_walk(PartyEntry* party);

void walkMain(PartyEntry* party);
