// proto: USER_FUNC(yuu_atai_push);
USER_FUNC(yuu_atai_push) {
    s32* args = event->args;

    if (stackp < 4) {
        stackt[stackp] = evtGetValue(event, args[0]);
        stackp++;
    }
    return EVT_RETURN_DONE;
}
