// include: party.h
// decl: extern s32 partyCtrlNo;
// proto: USER_FUNC(party_land_on);
USER_FUNC(party_land_on) {
    PartyEntry* party = partyGetPtr(partyCtrlNo);

    if (party != NULL && party->position.y < 0.0f) {
        party->position.y = 0.0f;
    }
    return EVT_RETURN_DONE;
}
