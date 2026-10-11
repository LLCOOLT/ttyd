// include: mario/mario_pouch.h
// proto: USER_FUNC(get_yoshi_color);
USER_FUNC(get_yoshi_color) {
    s32* args = event->args;
    evtSetValue(event, args[0], pouchGetPartyColor(4));
    return EVT_RETURN_DONE;
}
