// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// include: party.h
// proto: static USER_FUNC(scale_func);
static USER_FUNC(scale_func) {
    f32 s = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    PartyEntry* party2 = partyGetPtr(1);

    mario->scale = (Vec){s, s, s};
    if (party != NULL) {
        party->scale = (Vec){s, s, s};
    }
    if (party2 != NULL) {
        party2->scale = (Vec){s, s, s};
    }
    return EVT_RETURN_DONE;
}
