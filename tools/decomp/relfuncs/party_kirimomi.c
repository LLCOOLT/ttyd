// include: party.h
// include: manager/evtmgr_cmd.h
// decl: double fmod(double x, double y);
// proto: USER_FUNC(party_kirimomi);
USER_FUNC(party_kirimomi) {
    f32 angle = evtGetFloat(event, event->args[0]);
    PartyEntry* party = partyGetPtr(0);

    party->scale.x = party->scale.y = party->scale.z = 1.0f;
    party->field_8C = party->field_F0 / 2 * party->scale.y;
    party->field_6C = angle;
    party->field_6C = fmod(party->field_6C, 360.0);
    return EVT_RETURN_DONE;
}
