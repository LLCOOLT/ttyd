// include: party.h
// proto: USER_FUNC(party_scale);
USER_FUNC(party_scale) {
    static const Vec scale = {1.0f, 1.0f, 1.0f};

    partyGetPtr(0)->scale = scale;
    return EVT_RETURN_DONE;
}
