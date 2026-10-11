// include: mario/mario.h
// include: party.h
// include: manager/evtmgr_cmd.h
// decl: double fmod(double x, double y);
// proto: USER_FUNC(mario_kirimomi);
USER_FUNC(mario_kirimomi) {
    f32 scale = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);

    mario->scale.x = mario->scale.y = scale;
    mario->field_0xB4 = mario->wPlayerCollisionBox.y / 2;
    mario->field_0xB4 *= mario->scale.y;
    mario->field_0xC4 -= 10.0f;
    mario->field_0xC4 = fmod(mario->field_0xC4, 360.0);
    if (party != NULL) {
        party->scale.x = party->scale.y = scale;
        if (party->currentMemberId != 4) {
            party->field_8C = party->field_F0 / 2;
        } else {
            party->field_8C = (party->field_F0 - 10.0f) / 2;
        }
        party->field_8C *= party->scale.y;
        party->field_6C -= 10.0f;
        party->field_6C = fmod(party->field_6C, 360.0);
    }
    return EVT_RETURN_DONE;
}
