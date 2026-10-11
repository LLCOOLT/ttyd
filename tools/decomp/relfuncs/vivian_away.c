// include: mario/mario_pouch.h
// proto: USER_FUNC(vivian_away);
USER_FUNC(vivian_away) {
    pouchGetPtr()->partyData[6].flags |= 2;
    return EVT_RETURN_DONE;
}
