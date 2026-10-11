// include: party.h
// include: manager/evtmgr_cmd.h
// decl: extern s32 partyCtrlNo;
// proto: USER_FUNC(set_party_y_pos);
USER_FUNC(set_party_y_pos) {
    s32* args = event->args;
    f32 y = evtGetFloat(event, args[0]);
    PartyEntry* party = partyGetPtr(partyCtrlNo);

    if (party != NULL) {
        party->position.y = y;
    }
    return EVT_RETURN_DONE;
}
