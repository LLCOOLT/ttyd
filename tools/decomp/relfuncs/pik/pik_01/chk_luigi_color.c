// include: mario/mario.h
// proto: USER_FUNC(chk_luigi_color);
USER_FUNC(chk_luigi_color) {
    s32* args = event->args;

    if (marioGetColor() == 1) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
