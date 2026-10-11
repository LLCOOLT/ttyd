// include: mario/mario.h
// proto: USER_FUNC(evt_mario_check_menu);
USER_FUNC(evt_mario_check_menu) {
    s32* args = event->args;

    evtSetValue(event, args[0], marioCheckMenuDisable());
    return EVT_RETURN_DONE;
}
