// party_move.c: partner movement and the footmark trail (PartyFootmark) the followers walk along.
#pragma once

#include "party.h"
#include "dolphin/types.h"

// One point of the trail a partner follows (a ring of 80 per follower, written each frame Mario moves).
typedef struct PartyFootmark {
    u8 flags;  // 0x0, 1: Mario was jumping here, 4: slit floor
    u8 pad[3]; // 0x1
    Vec pos;   // 0x4
} PartyFootmark;

PartyFootmark* partyGetFootmarkPtr(s32 id);

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

struct HitEntry;

s32 partyGetFootmarkReadId(s32 id);
s32 partyGetFootmarkWriteId(s32 id);
s32 partyGetFootmarkId(PartyEntry* party);
f32 partyGetTargetDir(s32 id, f32 x, f32 z);
f32 partyGetTargetDist(s32 id, f32 x, f32 z);
f32 partyGetTargetDist3D(s32 id, Vec* p);
f32 partyGetTargetDistY(s32 id, f32 y);
f32 partyGetTargetMovespd2(PartyEntry* party);
void partyNextReadId(s32 id);
void partyGetReadId(s32 id, f32* x, f32* y, f32* z);
void partyGetReadId2(s32 id, Vec* pos);
void partyClearFootmark2(void);
void L_getTargetPos(s32 id, Vec* pos);
f32 partyGetTargetMovespd(s32 id);
f32 partySetTargetSpd(PartyEntry* party, f32 spd);
f32 partyForceSetSpd(PartyEntry* party, f32 spd);
void N_partyPlaySfxPartyLanding1(PartyEntry* party);
void partyChgStayPose(PartyEntry* party);
void partySetDispDirToMario(PartyEntry* party);
BOOL partyChkNoStandMobj(struct HitEntry* hit);
void partyChgMoveMode(PartyEntry* party, s32 mode);
void partySetDir(PartyEntry* party, f32 x, f32 z);
void partyMoveBehindMario(PartyEntry* party, s32 arg);
void partyMoveBehindMario3(PartyEntry* party, s32 arg);
void partyMoveBesideMario(PartyEntry* party, s32 arg);
void partyMoveCheckWall(PartyEntry* party);
void partyChkWall(PartyEntry* party);
void partyMoveFlyInit(PartyEntry* party, s32 arg);
void partyFlyMain(PartyEntry* party);
BOOL partyGetAppearPos5(PartyEntry* party, struct HitEntry* hit, Vec* out);
s32 partyMarioHosei(PartyEntry* party);

BOOL partyGetAppearPos(PartyEntry* party, Vec* out);
BOOL partyGetAppearPos3(PartyEntry* party, Vec* out);
BOOL partyGetAppearPos4(PartyEntry* party, Vec* out);
void partyWalkInit(PartyEntry* party);
f32 partyUpdMoveSpd(PartyEntry* party);
