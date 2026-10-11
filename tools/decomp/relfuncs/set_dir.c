// include: party.h
// proto: USER_FUNC(set_dir);
USER_FUNC(set_dir) {
    s32 dir = evtGetValue(event, event->args[0]);
    PartyEntry* party = partyGetPtr(0);

    if (party != NULL) {
        s32 angle = dir > 180 ? 270 : 90;
        party->field_110 = party->field_10C = 270 - angle;
    }
    return EVT_RETURN_DONE;
}
