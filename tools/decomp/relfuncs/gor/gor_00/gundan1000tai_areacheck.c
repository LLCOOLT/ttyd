// include: mario/mario.h
// include: party.h
// proto: USER_FUNC(gundan1000tai_areacheck);
USER_FUNC(gundan1000tai_areacheck) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(1);
    s32 area;

    if (mario->position.y > 70.0f) {
        area = 0;
    } else if (mario->position.x < 60.0f) {
        area = 0x10;
    } else if (mario->position.x < 80.0f) {
        area = 4;
    } else if (mario->position.x < 100.0f) {
        area = 2;
    } else if (mario->position.x < 120.0f) {
        area = 1;
    } else {
        area = 0;
    }
    evtSetValue(event, args[0], area);
    if (party->position.y > 70.0f) {
        area = 0;
    } else if (party->position.x < 60.0f) {
        area = 0x10;
    } else if (party->position.x < 80.0f) {
        area = 4;
    } else if (party->position.x < 100.0f) {
        area = 2;
    } else if (party->position.x < 120.0f) {
        area = 1;
    } else {
        area = 0;
    }
    evtSetValue(event, args[1], area);
    return EVT_RETURN_DONE;
}
