// include: mario/mario.h
// include: party.h
// include: driver/hitdrv.h
// include: manager/evtmgr_cmd.h
// decl: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
// proto: USER_FUNC(mario_hosei_all);
USER_FUNC(mario_hosei_all) {
    s32* args = event->args;
    HitEntry* hit = hitNameToPtr((const char*)evtGetValue(event, args[0]));
    f32 value = evtGetFloat(event, args[1]);
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    PartyEntry* party2 = partyGetPtr(1);

    if (mario != NULL && hitIsGroup(mario->hitobjStandOn, hit)) {
        mario->unk174.x = value;
    }
    if (party != NULL && hitIsGroup(party->field_138, hit)) {
        party->field_AC = value;
    }
    if (party2 != NULL && hitIsGroup(party2->field_138, hit)) {
        party2->field_AC = value;
    }
    return EVT_RETURN_DONE;
}
