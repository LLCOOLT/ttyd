// proto: USER_FUNC(yuu_atai_pop);
USER_FUNC(yuu_atai_pop) {
    s32* args = event->args;

    if (stackp > 0) {
        stackp--;
        evtSetValue(event, args[0], stackt[stackp]);
    }
    return EVT_RETURN_DONE;
}
