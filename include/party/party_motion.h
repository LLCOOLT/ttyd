// party_motion.c: partner motions (follow, jump, fall, stay, slit, upstairs).
#pragma once

#include "party.h"

void party_motion_behind_mario(PartyEntry* party);
void party_motion_behind_mario_continue(PartyEntry* party);
void party_motion_behind_mario_fly(PartyEntry* party);
void party_motion_beside_mario(PartyEntry* party);
void party_motion_damage(PartyEntry* party);
void party_motion_homing_fly(PartyEntry* party);
void party_motion_homing_walk(PartyEntry* party);
void party_motion_jump(PartyEntry* party);
void party_motion_jump2(PartyEntry* party);
void party_motion_stay(PartyEntry* party);
void party_motion_upstairs(PartyEntry* party);
void party_motion_wait(PartyEntry* party);

void L_partyForceSlitOff(PartyEntry* party);
void allPartySlitOn(void);
void allPartySlitOff(void);
void allPartyForceSlitOff(void);
void N_partyFollowCloseOn(PartyEntry* party);
void N_partyFollowCloseOff(PartyEntry* party);
void U_allPartySlitOffReq(void);
void partySlitReset(PartyEntry* party);

void party_set_behind_dir(PartyEntry* party, f32 dir);
s32 party_motion_fall(PartyEntry* party);
void partyMoveAnime(PartyEntry* party, f32 speed);
