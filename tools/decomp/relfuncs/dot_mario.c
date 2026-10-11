// include: party.h
// include: mario/mario.h
// include: driver/animdrv.h
// proto: USER_FUNC(dot_mario);
void partySetFamicomMode(PartyEntry* party, s32 mode);

USER_FUNC(dot_mario) {
    PartyEntry* party = partyGetPtr(0);

    if (!animGroupBaseAsync("d_mario", 0, NULL)) {
        return EVT_RETURN_BLOCK;
    }
    marioSetFamicomMode(1);
    partySetFamicomMode(party, 1);
    return EVT_RETURN_DONE;
}
