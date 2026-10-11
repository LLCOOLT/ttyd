// include: party.h
// include: manager/evtmgr_cmd.h
// decl: extern s32 partyCtrlNo;
// proto: USER_FUNC(get_party_y_pos);
USER_FUNC(get_party_y_pos) {
    s32* args = event->args;
    PartyEntry* party = partyGetPtr(partyCtrlNo);

    if (party != NULL) {
        evtSetFloat(event, args[0], party->position.y);
    }
    return EVT_RETURN_DONE;
}
