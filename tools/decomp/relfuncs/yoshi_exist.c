// include: mario/mario_pouch.h
// proto: USER_FUNC(yoshi_exist);
USER_FUNC(yoshi_exist) {
    s32* args = event->args;
    PouchData* pouch = pouchGetPtr();
    s32 exist = 0;

    if (pouch->partyData[4].flags & 1) {
        exist = 1;
    }
    evtSetValue(event, args[0], exist);
    return EVT_RETURN_DONE;
}
