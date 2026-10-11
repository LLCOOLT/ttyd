// include: party.h
// include: mario/mario_party.h
// include: driver/npcdrv.h
// decl: s32 party_hit_check(f32* dir, f32 x, f32 z);
// proto: USER_FUNC(party_hit);
USER_FUNC(party_hit) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    NpcEntry* npc = npcNameToPtr("\x8D\x95\x83\x4A\x83\x8D\x83\x93");
    s32* args = event->args;
    f32 dir;

    if (party_hit_check(&dir, npc->position.x, npc->position.z) &&
        (party->currentMemberId == 2 || party->currentMemberId == 3)) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
