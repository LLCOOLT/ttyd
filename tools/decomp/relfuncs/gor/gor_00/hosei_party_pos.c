// include: party.h
// decl: extern s32 partyCtrlNo;
// proto: USER_FUNC(hosei_party_pos);
USER_FUNC(hosei_party_pos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    PartyEntry* party = partyGetPtr(partyCtrlNo);

    if (party == NULL) {
        return EVT_RETURN_DONE;
    }
    party->position.x += x;
    party->position.y += y;
    party->position.z += z;
    return EVT_RETURN_DONE;
}
