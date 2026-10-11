// include: party.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(set_party_y_pos);
USER_FUNC(set_party_y_pos) {
    s32* args = event->args;
    PartyEntry* party = partyGetPtr(0);

    if (party == NULL) {
        return EVT_RETURN_DONE;
    }
    party->position.y = evtGetFloat(event, args[0]);
    return EVT_RETURN_DONE;
}
