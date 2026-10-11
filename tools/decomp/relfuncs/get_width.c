// include: party.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(get_width);
USER_FUNC(get_width) {
    s32* args = event->args;
    PartyEntry* party = partyGetPtr(evtGetValue(event, args[0]));

    evtSetFloat(event, args[1], 0.8f * party->width);
    return EVT_RETURN_DONE;
}
