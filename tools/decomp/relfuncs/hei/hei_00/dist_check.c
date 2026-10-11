// include: mario/mario.h
// include: mario/mario_party.h
// include: party.h
// include: dolphin/mtx.h
// proto: USER_FUNC(dist_check);
USER_FUNC(dist_check) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    Vec pos = {150.0f, 25.0f, 0.0f};

    event->lwData[0] = 0;
    if (party == NULL) {
        return EVT_RETURN_DONE;
    }
    if (PSVECDistance(&pos, &party->position) < 100.0f) {
        event->lwData[0] = 1;
    }
    return EVT_RETURN_DONE;
}
