// proto: USER_FUNC(yuuminigame_get_dataadr);
USER_FUNC(yuuminigame_get_dataadr) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    if (index >= 32) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], dataadr[index]);
    }
    return EVT_RETURN_DONE;
}
