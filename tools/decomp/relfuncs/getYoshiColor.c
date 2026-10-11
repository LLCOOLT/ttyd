// include: mario/mario_pouch.h
// proto: USER_FUNC(getYoshiColor);
USER_FUNC(getYoshiColor) {
    s32* args = event->args;
    evtSetValue(event, args[0], pouchGetPartyColor(4));
    return EVT_RETURN_DONE;
}
