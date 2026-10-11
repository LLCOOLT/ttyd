// proto: static USER_FUNC(set_fook_evt);
static USER_FUNC(set_fook_evt) {
    s32* args = event->args;
    s32* work = (s32*)evtGetValue(event, args[0]);

    work[1] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
