// include: mario/mario.h
// proto: USER_FUNC(test);
USER_FUNC(test) {
    marioGetPtr()->prevPartyMemberId[0] = 0;
    marioGetPtr()->prevPartyMemberId[1] = 0;
    return EVT_RETURN_DONE;
}
