// include: party.h
// proto: USER_FUNC(party_reset);
USER_FUNC(party_reset) {
    PartyEntry* party = partyGetPtr(0);

    party->scale.x = party->scale.y = party->scale.z = 1.0f;
    party->field_8C = 0.0f;
    party->field_6C = 0.0f;
    return EVT_RETURN_DONE;
}
