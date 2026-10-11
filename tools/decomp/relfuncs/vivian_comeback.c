// include: mario/mario_pouch.h
// proto: USER_FUNC(vivian_comeback);
USER_FUNC(vivian_comeback) {
    pouchGetPtr()->partyData[6].flags &= ~2;
    return 1;
}
