// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// include: party.h
// proto: USER_FUNC(scale_func);
USER_FUNC(scale_func) {
    f32 s = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);

    mario->scale = (Vec){s, s, s};
    if (party != NULL) {
        party->scale = (Vec){s, s, s};
    }
    return EVT_RETURN_DONE;
}
