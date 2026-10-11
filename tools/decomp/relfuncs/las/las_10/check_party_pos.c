// include: party.h
// decl: extern s32 partyCtrlNo;
// proto: USER_FUNC(check_party_pos);
USER_FUNC(check_party_pos) {
    s32* args = event->args;
    PartyEntry* party = partyGetPtr(partyCtrlNo);

    if (party == NULL) {
        evtSetValue(event, args[0], 1);
        return EVT_RETURN_DONE;
    }
    if (party->position.y >= 360.0f) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
