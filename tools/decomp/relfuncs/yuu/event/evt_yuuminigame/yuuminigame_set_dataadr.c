// proto: USER_FUNC(yuuminigame_set_dataadr);
USER_FUNC(yuuminigame_set_dataadr) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    if (index < 32) {
        dataadr[index] = evtGetValue(event, args[1]);
    }
    return EVT_RETURN_DONE;
}
